
/****************************************************************************
 Copyright (c) 2020-2021 Huawei Technologies Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "BloomStage.h"
#include "../PipelineStateManager.h"
#include "../RenderQueue.h"
#include "DeferredPipeline.h"
#include "gfx-base/GFXCommandBuffer.h"
#include "gfx-base/GFXDevice.h"
#include "gfx-base/GFXFramebuffer.h"
#include "scene/SubModel.h"
#include "frame-graph/PassNodeBuilder.h"
#include "frame-graph/DevicePass.h"
#include "frame-graph/Resource.h"

namespace cc {
namespace pipeline {
namespace {
const String STAGE_NAME = "BloomStage";

framegraph::StringHandle prefilterTexHandle = framegraph::FrameGraph::stringToHandle("prefilterTex");
framegraph::StringHandle downsampleTexHandles[BloomStage::MaxScalingSamplePassNum];
framegraph::StringHandle upsampleTexHandles[BloomStage::MaxScalingSamplePassNum];
framegraph::StringHandle prefilterPassHandle;
framegraph::StringHandle downsamplePassHandles[BloomStage::MaxScalingSamplePassNum];
framegraph::StringHandle upsamplePassHandles[BloomStage::MaxScalingSamplePassNum];
framegraph::StringHandle combinePassHandle;

void initStrHandle() {
    prefilterPassHandle = framegraph::FrameGraph::stringToHandle("bloomPrefilterPass");

    std::string tmp;
    for (int i = 0; i < BloomStage::MaxScalingSamplePassNum; ++i) {
        tmp = std::string("bloomDownsamplePass") + std::to_string(i);
        downsamplePassHandles[i] = framegraph::FrameGraph::stringToHandle(tmp.c_str());

        tmp = std::string("bloomDownsampleTex") + std::to_string(i);
        downsampleTexHandles[i] = framegraph::FrameGraph::stringToHandle(tmp.c_str());

        tmp = std::string("bloomUpsamplePass") + std::to_string(i);
        upsamplePassHandles[i] = framegraph::FrameGraph::stringToHandle(tmp.c_str());

        tmp = std::string("bloomUpsampleTex") + std::to_string(i);
        upsampleTexHandles[i] = framegraph::FrameGraph::stringToHandle(tmp.c_str());
    }

    combinePassHandle = framegraph::FrameGraph::stringToHandle("bloomCombinePass");
    DeferredPipeline::fgStrHandleBloomOutTexture = framegraph::FrameGraph::stringToHandle("combineTex");
}
} // namespace

RenderStageInfo BloomStage::initInfo = {
    STAGE_NAME,
    static_cast<uint>(DeferredStagePriority::BLOOM),
    0,
    {{true, RenderQueueSortMode::BACK_TO_FRONT, {"default"}}},
};
const RenderStageInfo &BloomStage::getInitializeInfo() { return BloomStage::initInfo; }

BloomStage::BloomStage() {}

bool BloomStage::initialize(const RenderStageInfo &info) {
    RenderStage::initialize(info);
    initStrHandle();

    return true;
}

void BloomStage::activate(RenderPipeline *pipeline, RenderFlow *flow) {
    if (DeferredPipeline::bloomSwitch == false) return;

    RenderStage::activate(pipeline, flow);
    _phaseID = getPhaseID("default");

    _DSLayout    = _device->createDescriptorSetLayout({globalDescriptorSetLayout.bindings});
    _prefilterDS = _device->createDescriptorSet({_DSLayout});

    for (int i = 0; i < BloomStage::MaxScalingSamplePassNum; ++i) {
        _downsampleGlobalUBO[i] = _device->createBuffer(
            {gfx::BufferUsage::UNIFORM, gfx::MemoryUsage::DEVICE | gfx::MemoryUsage::HOST, UBOGlobal::SIZE});
        _downsampleDS[i] = _device->createDescriptorSet({_DSLayout});

        _upsampleGlobalUBO[i] = _device->createBuffer(
            {gfx::BufferUsage::UNIFORM, gfx::MemoryUsage::DEVICE | gfx::MemoryUsage::HOST, UBOGlobal::SIZE});
        _upsampleDS[i] = _device->createDescriptorSet({_DSLayout});
    }

    _combineDS = _device->createDescriptorSet({_DSLayout});

    gfx::SamplerInfo info{
        gfx::Filter::LINEAR,
        gfx::Filter::LINEAR,
        gfx::Filter::NONE,
        gfx::Address::CLAMP,
        gfx::Address::CLAMP,
        gfx::Address::CLAMP,
    };
    const auto samplerHash = SamplerLib::genSamplerHash(info);
    _sampler               = SamplerLib::getSampler(samplerHash);
}

void BloomStage::destroy() {
    CC_SAFE_DELETE(_DSLayout);
    CC_SAFE_DELETE(_prefilterDS);

    for (int i = 0; i < BloomStage::MaxScalingSamplePassNum; ++i) {
        CC_SAFE_DELETE(_downsampleGlobalUBO[i]);
        CC_SAFE_DELETE(_downsampleDS[i]);

        CC_SAFE_DELETE(_upsampleGlobalUBO[i]);
        CC_SAFE_DELETE(_upsampleDS[i]);
    }

    CC_SAFE_DELETE(_combineDS);
}

int calcScalingFilterPassNum(scene::Camera *camera) {
    /*
     * The down/upsample pass number should be calculated using the data passed by user
     * through the camera, but for now we always return 2.
     */
    return 2;
}

void BloomStage::render(scene::Camera *camera) {
    if (DeferredPipeline::bloomSwitch == false) return;

    int   scalingSampleNum = calcScalingFilterPassNum(camera);
    auto *pipeline         = static_cast<DeferredPipeline *>(_pipeline);
    assert(pipeline != nullptr);

    if (hasFlag(static_cast<gfx::ClearFlags>(camera->clearFlag), gfx::ClearFlagBit::COLOR)) {
        _clearColors[0].x = camera->clearColor.x;
        _clearColors[0].y = camera->clearColor.y;
        _clearColors[0].z = camera->clearColor.z;
    }
    _clearColors[0].w = camera->clearColor.w;

    framegraph::RenderTargetAttachment::Descriptor colorAttachmentInfo;
    colorAttachmentInfo.usage       = framegraph::RenderTargetAttachment::Usage::COLOR;
    colorAttachmentInfo.loadOp      = gfx::LoadOp::CLEAR;
    colorAttachmentInfo.clearColor  = _clearColors[0];
    colorAttachmentInfo.endAccesses = {gfx::AccessType::FRAGMENT_SHADER_WRITE};

    uint insertPoint = static_cast<uint>(DeferredInsertPoint::IP_BLOOM);

    // prefilter pass
    struct PrefilterRenderData {
        framegraph::TextureHandle inputTexHandle;
        framegraph::TextureHandle outputTexHandle;
    };

    auto renderArea = pipeline->getRenderArea(camera, false);
    renderArea.width >>= 1;
    renderArea.height >>= 1;

    auto prefilterSetup = [&](framegraph::PassNodeBuilder &builder, PrefilterRenderData &data) {
        // read lightingout as input
        data.inputTexHandle = framegraph::TextureHandle(
            builder.readFromBlackboard(DeferredPipeline::fgStrHandleLightingOutTexture));
        if (!data.inputTexHandle.isValid()) {
            framegraph::Texture::Descriptor colorTexInfo;
            colorTexInfo.format = gfx::Format::RGBA16F;
            colorTexInfo.usage  = gfx::TextureUsageBit::COLOR_ATTACHMENT | gfx::TextureUsageBit::SAMPLED;
            colorTexInfo.width  = pipeline->getWidth();
            colorTexInfo.height = pipeline->getHeight();

            data.inputTexHandle = builder.create<framegraph::Texture>(
                DeferredPipeline::fgStrHandleLightingOutTexture, colorTexInfo);
        }
        data.inputTexHandle = builder.read(data.inputTexHandle);
        builder.writeToBlackboard(DeferredPipeline::fgStrHandleLightingOutTexture, data.inputTexHandle);

        // write to bloom prefilter texture
        data.outputTexHandle = framegraph::TextureHandle(builder.readFromBlackboard(prefilterTexHandle));
        if (!data.outputTexHandle.isValid()) {
            framegraph::Texture::Descriptor colorTexInfo;
            colorTexInfo.format = gfx::Format::RGBA16F;
            colorTexInfo.usage  = gfx::TextureUsageBit::COLOR_ATTACHMENT | gfx::TextureUsageBit::SAMPLED;
            colorTexInfo.width  = renderArea.width;
            colorTexInfo.height = renderArea.height;
            colorTexInfo.flags  = gfx::TextureFlagBit::IMMUTABLE;

            data.outputTexHandle = builder.create<framegraph::Texture>(prefilterTexHandle, colorTexInfo);
        }
        data.outputTexHandle = builder.write(data.outputTexHandle, colorAttachmentInfo);
        builder.writeToBlackboard(prefilterTexHandle, data.outputTexHandle);

        gfx::Viewport viewport{renderArea.x, renderArea.y, renderArea.width, renderArea.height, 0.F, 1.F};
        builder.setViewport(viewport, renderArea);
    };

    auto prefilterExec = [&](PrefilterRenderData const &data, const framegraph::DevicePassResourceTable &table) {
        auto *pipeline = static_cast<DeferredPipeline *>(RenderPipeline::getInstance());
        assert(pipeline != nullptr);
        auto *stage = static_cast<BloomStage *>(pipeline->getRenderstageByName(STAGE_NAME));
        assert(stage != nullptr);

        auto *inputTex = static_cast<gfx::Texture *>(table.getRead(data.inputTexHandle));

        gfx::RenderPass *renderPass = table.getRenderPass().get();
        assert(renderPass != nullptr);

        auto *cmdBf = pipeline->getCommandBuffers()[0];
        auto *ds    = stage->getPrefilterDS();
        ds->bindBuffer(0, pipeline->getDescriptorSet()->getBuffer(0));
        ds->bindBuffer(1, pipeline->getDescriptorSet()->getBuffer(1));
        ds->bindSampler(static_cast<uint>(PipelineGlobalBindings::SAMPLER_LIGHTING_RESULTMAP), stage->getSampler());
        ds->bindTexture(static_cast<uint>(PipelineGlobalBindings::SAMPLER_LIGHTING_RESULTMAP), inputTex);
        ds->update();

        cmdBf->bindDescriptorSet(static_cast<uint>(SetIndex::GLOBAL), ds);
        auto *const          sharedData     = pipeline->getPipelineSceneData()->getSharedData();
        scene::Pass *        pass           = sharedData->deferredBloomPrefilterPass;
        gfx::Shader *        shader         = sharedData->deferredBloomPrefilterPassShader;
        auto *               camera         = pipeline->getFrameGraphCamera();
        auto                 rendeArea      = pipeline->getRenderArea(camera, !camera->window->hasOffScreenAttachments);
        gfx::InputAssembler *inputAssembler = pipeline->getIAByRenderArea(rendeArea);
        gfx::PipelineState * pso            = PipelineStateManager::getOrCreatePipelineState(
            pass, shader, inputAssembler, renderPass);
        assert(pso != nullptr);

        cmdBf->bindPipelineState(pso);
        cmdBf->bindInputAssembler(inputAssembler);
        cmdBf->draw(inputAssembler);
    };

    pipeline->getFrameGraph().addPass<PrefilterRenderData>(insertPoint, prefilterPassHandle,
        prefilterSetup, prefilterExec);

    struct ScalingSampleRenderData {
        framegraph::TextureHandle inputTexHandle;
        framegraph::TextureHandle outputTexHandle;
        int                       index;
    };
    // downsample pass
    for (int i = 0; i < scalingSampleNum; ++i) {
        renderArea.width >>= 1;
        renderArea.height >>= 1;

        auto downsampleSetup = [&, i](framegraph::PassNodeBuilder &builder, ScalingSampleRenderData &data) {
            data.index = i;
            // read from prefilter texture or last downsample texture
            if (data.index == 0) {
                data.inputTexHandle = builder.read(framegraph::TextureHandle(
                    builder.readFromBlackboard(prefilterTexHandle)));
                builder.writeToBlackboard(prefilterTexHandle, data.inputTexHandle);
            } else {
                data.inputTexHandle = builder.read(framegraph::TextureHandle(
                    builder.readFromBlackboard(downsampleTexHandles[data.index - 1])));
                builder.writeToBlackboard(downsampleTexHandles[data.index - 1], data.inputTexHandle);
            }

            // write to downsample texture
            data.outputTexHandle = framegraph::TextureHandle(
                builder.readFromBlackboard(downsampleTexHandles[data.index]));
            if (!data.outputTexHandle.isValid()) {
                framegraph::Texture::Descriptor colorTexInfo;
                colorTexInfo.format = gfx::Format::RGBA16F; // TODO: Change lighting result to RGBA16F
                colorTexInfo.usage  = gfx::TextureUsageBit::COLOR_ATTACHMENT | gfx::TextureUsageBit::SAMPLED;
                colorTexInfo.width  = renderArea.width;
                colorTexInfo.height = renderArea.height;
                colorTexInfo.flags  = gfx::TextureFlagBit::IMMUTABLE;

                data.outputTexHandle = builder.create<framegraph::Texture>(downsampleTexHandles[data.index],
                                                                           colorTexInfo);
            }
            data.outputTexHandle = builder.write(data.outputTexHandle, colorAttachmentInfo);
            builder.writeToBlackboard(downsampleTexHandles[data.index], data.outputTexHandle);

            gfx::Viewport viewport{renderArea.x, renderArea.y, renderArea.width, renderArea.height, 0.F, 1.F};
            builder.setViewport(viewport, renderArea);

            // Update cc_textureSize
            auto *stage = static_cast<BloomStage *>(pipeline->getRenderstageByName(STAGE_NAME));
            assert(stage != nullptr);
            gfx::Buffer *globalUBO                      = stage->getDownsampelGlobalUBO()[data.index];
            auto         content                        = pipeline->getPipelineUBO()->getGlobalUBO();
            content[UBOGlobal::TEXTURE_SIZE_OFFSET]     = renderArea.width << 1;
            content[UBOGlobal::TEXTURE_SIZE_OFFSET + 1] = renderArea.height << 1;
            globalUBO->update(content.data(), UBOGlobal::SIZE);
        };

        auto downsampleExec = [&](ScalingSampleRenderData const &            data,
                                  const framegraph::DevicePassResourceTable &table) {
            auto *pipeline = static_cast<DeferredPipeline *>(RenderPipeline::getInstance());
            assert(pipeline != nullptr);
            auto *stage = static_cast<BloomStage *>(pipeline->getRenderstageByName(STAGE_NAME));
            assert(stage != nullptr);

            auto *inputTex = static_cast<gfx::Texture *>(table.getRead(data.inputTexHandle));
            auto *ds       = stage->getDownsampleDS()[data.index];
            ds->bindBuffer(0, stage->getDownsampelGlobalUBO()[data.index]);
            ds->bindBuffer(1, pipeline->getDescriptorSet()->getBuffer(1));
            ds->bindSampler(static_cast<uint>(PipelineGlobalBindings::SAMPLER_BLOOM), stage->getSampler());
            ds->bindTexture(static_cast<uint>(PipelineGlobalBindings::SAMPLER_BLOOM), inputTex);
            ds->update();

            auto *cmdBf = pipeline->getCommandBuffers()[0];
            cmdBf->bindDescriptorSet(static_cast<uint>(SetIndex::GLOBAL), ds);

            gfx::RenderPass *renderPass = table.getRenderPass().get();
            assert(renderPass != nullptr);
            auto *const          sharedData     = pipeline->getPipelineSceneData()->getSharedData();
            scene::Pass *        pass           = sharedData->deferredBloomDownsamplePass;
            gfx::Shader *        shader         = sharedData->deferredBloomDownsamplePassShader;
            auto *               camera         = pipeline->getFrameGraphCamera();
            auto                 rendeArea      = pipeline->getRenderArea(camera,
                                                     !camera->window->hasOffScreenAttachments);
            gfx::InputAssembler *inputAssembler = pipeline->getIAByRenderArea(rendeArea);
            gfx::PipelineState * pso            = PipelineStateManager::getOrCreatePipelineState(
                pass, shader, inputAssembler, renderPass);
            assert(pso != nullptr);

            cmdBf->bindPipelineState(pso);
            cmdBf->bindInputAssembler(inputAssembler);
            cmdBf->draw(inputAssembler);
        };

        pipeline->getFrameGraph().addPass<ScalingSampleRenderData>(++insertPoint, downsamplePassHandles[i],
                                                                   downsampleSetup, downsampleExec);
    }

    // upsample pass
    for (int i = 0; i < scalingSampleNum; ++i) {
        renderArea.width <<= 1;
        renderArea.height <<= 1;

        auto upsampleSetup = [&, i](framegraph::PassNodeBuilder &builder, ScalingSampleRenderData &data) {
            data.index = i;
            // read from last downsample texture or last upsample texture
            if (data.index == 0) {
                data.inputTexHandle = builder.read(framegraph::TextureHandle(
                    builder.readFromBlackboard(downsampleTexHandles[scalingSampleNum - 1])));
                builder.writeToBlackboard(downsampleTexHandles[scalingSampleNum - 1], data.inputTexHandle);
            } else {
                data.inputTexHandle = builder.read(framegraph::TextureHandle(
                    builder.readFromBlackboard(upsampleTexHandles[data.index - 1])));
                builder.writeToBlackboard(upsampleTexHandles[data.index - 1], data.inputTexHandle);
            }

            // write to downsample texture
            data.outputTexHandle = framegraph::TextureHandle(
                builder.readFromBlackboard(upsampleTexHandles[data.index]));
            if (!data.outputTexHandle.isValid()) {
                framegraph::Texture::Descriptor colorTexInfo;
                colorTexInfo.format = gfx::Format::RGBA16F; // TODO: Change lighting result to RGBA16F
                colorTexInfo.usage  = gfx::TextureUsageBit::COLOR_ATTACHMENT | gfx::TextureUsageBit::SAMPLED;
                colorTexInfo.width  = renderArea.width;
                colorTexInfo.height = renderArea.height;
                colorTexInfo.flags  = gfx::TextureFlagBit::IMMUTABLE;

                data.outputTexHandle = builder.create<framegraph::Texture>(
                    upsampleTexHandles[data.index], colorTexInfo);
            }
            data.outputTexHandle = builder.write(data.outputTexHandle, colorAttachmentInfo);
            builder.writeToBlackboard(upsampleTexHandles[data.index], data.outputTexHandle);

            gfx::Viewport viewport{renderArea.x, renderArea.y, renderArea.width, renderArea.height, 0.F, 1.F};
            builder.setViewport(viewport, renderArea);

            // Update cc_textureSize
            auto *stage = static_cast<BloomStage *>(pipeline->getRenderstageByName(STAGE_NAME));
            assert(stage != nullptr);
            gfx::Buffer *globalUBO                      = stage->getUpsampleGlobalUBO()[data.index];
            auto         content                        = pipeline->getPipelineUBO()->getGlobalUBO();
            content[UBOGlobal::TEXTURE_SIZE_OFFSET]     = renderArea.width >> 1;
            content[UBOGlobal::TEXTURE_SIZE_OFFSET + 1] = renderArea.height >> 1;
            globalUBO->update(content.data(), UBOGlobal::SIZE);
        };

        auto upsampleExec = [&](ScalingSampleRenderData const &data, const framegraph::DevicePassResourceTable &table) {
            auto *pipeline = static_cast<DeferredPipeline *>(RenderPipeline::getInstance());
            assert(pipeline != nullptr);
            auto *stage = static_cast<BloomStage *>(pipeline->getRenderstageByName(STAGE_NAME));
            assert(stage != nullptr);

            auto *inputTex = static_cast<gfx::Texture *>(table.getRead(data.inputTexHandle));
            auto *ds       = stage->getUpsampleDS()[data.index];
            ds->bindBuffer(0, stage->getUpsampleGlobalUBO()[data.index]);
            ds->bindBuffer(1, pipeline->getDescriptorSet()->getBuffer(1));
            ds->bindSampler(static_cast<uint>(PipelineGlobalBindings::SAMPLER_BLOOM), stage->getSampler());
            ds->bindTexture(static_cast<uint>(PipelineGlobalBindings::SAMPLER_BLOOM), inputTex);
            ds->update();

            auto *cmdBf = pipeline->getCommandBuffers()[0];
            cmdBf->bindDescriptorSet(static_cast<uint>(SetIndex::GLOBAL), ds);

            gfx::RenderPass *renderPass = table.getRenderPass().get();
            assert(renderPass != nullptr);
            auto *const          sharedData     = pipeline->getPipelineSceneData()->getSharedData();
            scene::Pass *        pass           = sharedData->deferredBloomUpsamplePass;
            gfx::Shader *        shader         = sharedData->deferredBloomUpsamplePassShader;
            auto *               camera         = pipeline->getFrameGraphCamera();
            auto                 rendeArea      = pipeline->getRenderArea(camera,
                                                     !camera->window->hasOffScreenAttachments);
            gfx::InputAssembler *inputAssembler = pipeline->getIAByRenderArea(rendeArea);
            gfx::PipelineState * pso            = PipelineStateManager::getOrCreatePipelineState(
                pass, shader, inputAssembler, renderPass);
            assert(pso != nullptr);

            cmdBf->bindPipelineState(pso);
            cmdBf->bindInputAssembler(inputAssembler);
            cmdBf->draw(inputAssembler);
        };

        pipeline->getFrameGraph().addPass<ScalingSampleRenderData>(++insertPoint, upsamplePassHandles[i],
            upsampleSetup, upsampleExec);
    }

    // combine pass
    struct CombineRenderData {
        framegraph::TextureHandle lightingOutTexHandle;
        framegraph::TextureHandle upsampleTexHandle;
        framegraph::TextureHandle bloomOutTexHandle;
    };

    renderArea.width <<= 1;
    renderArea.height <<= 1;

    auto combineSetup = [&](framegraph::PassNodeBuilder &builder, CombineRenderData &data) {
        // read lighting result or last upsample texture
        data.lightingOutTexHandle = builder.read(framegraph::TextureHandle(
            builder.readFromBlackboard(DeferredPipeline::fgStrHandleLightingOutTexture)));
        builder.writeToBlackboard(DeferredPipeline::fgStrHandleLightingOutTexture, data.lightingOutTexHandle);

        data.upsampleTexHandle = builder.read(framegraph::TextureHandle(
            builder.readFromBlackboard(upsampleTexHandles[scalingSampleNum - 1])));
        builder.writeToBlackboard(upsampleTexHandles[scalingSampleNum - 1], data.upsampleTexHandle);

        // write to bloomOut texture
        data.bloomOutTexHandle = framegraph::TextureHandle(
            builder.readFromBlackboard(DeferredPipeline::fgStrHandleBloomOutTexture));
        if (!data.bloomOutTexHandle.isValid()) {
            framegraph::Texture::Descriptor colorTexInfo;
            colorTexInfo.format = gfx::Format::RGBA16F; // TODO: Change lighting result to RGBA16F
            colorTexInfo.usage  = gfx::TextureUsageBit::COLOR_ATTACHMENT | gfx::TextureUsageBit::SAMPLED;
            colorTexInfo.width  = renderArea.width;
            colorTexInfo.height = renderArea.height;
            colorTexInfo.flags  = gfx::TextureFlagBit::IMMUTABLE;

            data.bloomOutTexHandle = builder.create<framegraph::Texture>(
                DeferredPipeline::fgStrHandleBloomOutTexture, colorTexInfo);
        }
        data.bloomOutTexHandle = builder.write(data.bloomOutTexHandle, colorAttachmentInfo);
        builder.writeToBlackboard(DeferredPipeline::fgStrHandleBloomOutTexture, data.bloomOutTexHandle);

        gfx::Viewport viewport{renderArea.x, renderArea.y, renderArea.width, renderArea.height, 0.F, 1.F};
        builder.setViewport(viewport, renderArea);
    };

    auto combineExec = [&](CombineRenderData const &data, const framegraph::DevicePassResourceTable &table) {
        auto *pipeline = static_cast<DeferredPipeline *>(RenderPipeline::getInstance());
        assert(pipeline != nullptr);
        auto *stage = static_cast<BloomStage *>(pipeline->getRenderstageByName(STAGE_NAME));
        assert(stage != nullptr);

        auto *lightingOut = static_cast<gfx::Texture *>(table.getRead(data.lightingOutTexHandle));
        auto *upsampleTex = static_cast<gfx::Texture *>(table.getRead(data.upsampleTexHandle));

        gfx::RenderPass *renderPass = table.getRenderPass().get();
        assert(renderPass != nullptr);

        auto *cmdBf = pipeline->getCommandBuffers()[0];
        auto *ds    = stage->getCombineDS();
        ds->bindBuffer(0, pipeline->getDescriptorSet()->getBuffer(0));
        ds->bindBuffer(1, pipeline->getDescriptorSet()->getBuffer(1));
        ds->bindSampler(static_cast<uint>(PipelineGlobalBindings::SAMPLER_LIGHTING_RESULTMAP), stage->getSampler());
        ds->bindTexture(static_cast<uint>(PipelineGlobalBindings::SAMPLER_LIGHTING_RESULTMAP), lightingOut);
        ds->bindSampler(static_cast<uint>(PipelineGlobalBindings::SAMPLER_BLOOM), stage->getSampler());
        ds->bindTexture(static_cast<uint>(PipelineGlobalBindings::SAMPLER_BLOOM), upsampleTex);
        ds->update();

        cmdBf->bindDescriptorSet(static_cast<uint>(SetIndex::GLOBAL), ds);
        auto *const          sharedData     = pipeline->getPipelineSceneData()->getSharedData();
        scene::Pass *        pass           = sharedData->deferredBloomCombinePass;
        gfx::Shader *        shader         = sharedData->deferredBloomCombinePassShader;
        auto *               camera         = pipeline->getFrameGraphCamera();
        auto                 rendeArea      = pipeline->getRenderArea(camera, !camera->window->hasOffScreenAttachments);
        gfx::InputAssembler *inputAssembler = pipeline->getIAByRenderArea(rendeArea);
        gfx::PipelineState * pso            = PipelineStateManager::getOrCreatePipelineState(
            pass, shader, inputAssembler, renderPass);
        assert(pso != nullptr);

        cmdBf->bindPipelineState(pso);
        cmdBf->bindInputAssembler(inputAssembler);
        cmdBf->draw(inputAssembler);
    };

    pipeline->getFrameGraph().addPass<CombineRenderData>(++insertPoint, combinePassHandle, combineSetup, combineExec);
}
} // namespace pipeline
} // namespace cc
