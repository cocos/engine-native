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

#include "LightingStage.h"
#include "../BatchedBuffer.h"
#include "../InstancedBuffer.h"
#include "../PipelineStateManager.h"
#include "../PlanarShadowQueue.h"
#include "../RenderBatchedQueue.h"
#include "../RenderInstancedQueue.h"
#include "../RenderQueue.h"
#include "DeferredPipeline.h"
#include "gfx-base/GFXCommandBuffer.h"
#include "gfx-base/GFXDescriptorSet.h"
#include "gfx-base/GFXDevice.h"
#include "gfx-base/GFXFramebuffer.h"
#include "gfx-base/GFXQueue.h"
#include "scene/RenderScene.h"
#include "scene/Sphere.h"
#include "scene/SphereLight.h"
#include "../Define.h"

namespace cc {
namespace pipeline {
namespace {
void srgbToLinear(gfx::Color *out, const gfx::Color &gamma) {
    out->x = gamma.x * gamma.x;
    out->y = gamma.y * gamma.y;
    out->z = gamma.z * gamma.z;
}

void linearToSrgb(gfx::Color *out, const gfx::Color &linear) {
    out->x = std::sqrt(linear.x);
    out->y = std::sqrt(linear.y);
    out->z = std::sqrt(linear.z);
}
} // namespace

RenderStageInfo LightingStage::initInfo = {
    "LightingStage",
    static_cast<uint>(DeferredStagePriority::LIGHTING),
    static_cast<uint>(RenderFlowTag::SCENE),
};

const RenderStageInfo &LightingStage::getInitializeInfo() { return LightingStage::initInfo; }

LightingStage::LightingStage() = default;

LightingStage::~LightingStage() {
    _deferredLitsBufs->destroy();
    _deferredLitsBufs = nullptr;
    _deferredLitsBufView->destroy();
    _deferredLitsBufView = nullptr;
}

bool LightingStage::initialize(const RenderStageInfo &info) {
    RenderStage::initialize(info);
    _renderQueueDescriptors = info.renderQueues;
    _phaseID                = getPhaseID("deferred");
    _reflectionPhaseID      = getPhaseID("reflection");
    return true;
}

void LightingStage::gatherLights(scene::Camera *camera) {
    auto *pipeline = dynamic_cast<DeferredPipeline *>(_pipeline);
    if (!pipeline) {
        return;
    }

    auto *const sceneData  = _pipeline->getPipelineSceneData();
    auto *const sharedData = sceneData->getSharedData();

    gfx::CommandBuffer *cmdBuf = pipeline->getCommandBuffers()[0];
    const auto *        scene  = camera->scene;

    scene::Sphere sphere;
    auto          exposure   = camera->exposure;
    uint          idx        = 0;
    int           elementLen = sizeof(cc::Vec4) / sizeof(float);
    uint          fieldLen   = elementLen * _maxDeferredLights;
    uint          offset     = 0;
    cc::Vec4      tmpArray;

    uint i = 0;
    for (auto *light : scene->getSphereLights()) {
        if (i >= _maxDeferredLights) {
            break;
        }

        const auto &position = light->getPosition();
        sphere.setCenter(position);
        sphere.setRadius(light->getRange());
        if (!sphere.sphereFrustum(camera->frustum)) {
            continue;
        }
        // position
        offset                       = idx * elementLen;
        _lightBufferData[offset]     = position.x;
        _lightBufferData[offset + 1] = position.y;
        _lightBufferData[offset + 2] = position.z;
        _lightBufferData[offset + 3] = 0;

        // color
        const auto &color = light->getColor();
        offset            = idx * elementLen + fieldLen;
        tmpArray.set(color.x, color.y, color.z, 0);
        if (light->getUseColorTemperature()) {
            const auto &colorTemperatureRGB = light->getColorTemperatureRGB();
            tmpArray.x *= colorTemperatureRGB.x;
            tmpArray.y *= colorTemperatureRGB.y;
            tmpArray.z *= colorTemperatureRGB.z;
        }

        if (sharedData->isHDR) {
            tmpArray.w = light->getIlluminance() * sharedData->fpScale * _lightMeterScale;
        } else {
            tmpArray.w = light->getIlluminance() * exposure * _lightMeterScale;
        }

        _lightBufferData[offset + 0] = tmpArray.x;
        _lightBufferData[offset + 1] = tmpArray.y;
        _lightBufferData[offset + 2] = tmpArray.z;
        _lightBufferData[offset + 3] = tmpArray.w;

        // size range angle
        offset                       = idx * elementLen + fieldLen * 2;
        _lightBufferData[offset]     = light->getSize();
        _lightBufferData[offset + 1] = light->getRange();
        _lightBufferData[offset + 2] = 0;

        ++i;
    }

    i = 0;
    for (auto *light : scene->getSpotLights()) {
        if (i >= _maxDeferredLights) {
            break;
        }

        const auto &position = light->getPosition();
        sphere.setCenter(position);
        sphere.setRadius(light->getRange());
        if (!sphere.sphereFrustum(camera->frustum)) {
            continue;
        }
        // position
        offset                       = idx * elementLen;
        _lightBufferData[offset]     = position.x;
        _lightBufferData[offset + 1] = position.y;
        _lightBufferData[offset + 2] = position.z;
        _lightBufferData[offset + 3] = 1;

        // color
        offset            = idx * elementLen + fieldLen;
        const auto &color = light->getColor();
        tmpArray.set(color.x, color.y, color.z, 0);
        if (light->getUseColorTemperature()) {
            const auto &colorTemperatureRGB = light->getColorTemperatureRGB();
            tmpArray.x *= colorTemperatureRGB.x;
            tmpArray.y *= colorTemperatureRGB.y;
            tmpArray.z *= colorTemperatureRGB.z;
        }

        if (sharedData->isHDR) {
            tmpArray.w = light->getIlluminance() * sharedData->fpScale * _lightMeterScale;
        } else {
            tmpArray.w = light->getIlluminance() * exposure * _lightMeterScale;
        }

        _lightBufferData[offset + 0] = tmpArray.x;
        _lightBufferData[offset + 1] = tmpArray.y;
        _lightBufferData[offset + 2] = tmpArray.z;
        _lightBufferData[offset + 3] = tmpArray.w;

        // size range angle
        offset                       = idx * elementLen + fieldLen * 2;
        _lightBufferData[offset]     = light->getSize();
        _lightBufferData[offset + 1] = light->getRange();
        _lightBufferData[offset + 2] = light->getSpotAngle();

        // dir
        const auto &direction        = light->getDirection();
        offset                       = idx * elementLen + fieldLen * 3;
        _lightBufferData[offset]     = direction.x;
        _lightBufferData[offset + 1] = direction.y;
        _lightBufferData[offset + 2] = direction.z;

        ++i;
    }

    // the count of lights is set to cc_lightDir[0].w
    _lightBufferData[fieldLen * 3 + 3] = static_cast<float>(idx);
    cmdBuf->updateBuffer(_deferredLitsBufs, _lightBufferData.data());
}

void LightingStage::initLightingBuffer() {
    auto *const device = _pipeline->getDevice();

    // color/pos/dir/angle 都是vec4存储, 最后一个vec4只要x存储光源个数
    uint totalSize = sizeof(Vec4) * 4 * _maxDeferredLights;
    totalSize      = static_cast<uint>(std::ceil(static_cast<float>(totalSize) / device->getCapabilities().uboOffsetAlignment) * device->getCapabilities().uboOffsetAlignment);

    // create lighting buffer and view
    if (_deferredLitsBufs == nullptr) {
        gfx::BufferInfo bfInfo = {
            gfx::BufferUsageBit::UNIFORM | gfx::BufferUsageBit::TRANSFER_DST,
            gfx::MemoryUsageBit::HOST | gfx::MemoryUsageBit::DEVICE,
            totalSize,
            static_cast<uint>(device->getCapabilities().uboOffsetAlignment),
        };
        _deferredLitsBufs = device->createBuffer(bfInfo);
        assert(_deferredLitsBufs != nullptr);
    }

    if (_deferredLitsBufView == nullptr) {
        gfx::BufferViewInfo bvInfo = {_deferredLitsBufs, 0, totalSize};
        _deferredLitsBufView       = device->createBuffer(bvInfo);
        assert(_deferredLitsBufView != nullptr);
        _descriptorSet->bindBuffer(static_cast<uint>(ModelLocalBindings::UBO_FORWARD_LIGHTS), _deferredLitsBufView);
    }

    _lightBufferData.resize(totalSize / sizeof(float));
}

void LightingStage::activate(RenderPipeline *pipeline, RenderFlow *flow) {
    RenderStage::activate(pipeline, flow);

    auto *const device = pipeline->getDevice();

    for (const auto &descriptor : _renderQueueDescriptors) {
        uint                  phase    = convertPhase(descriptor.stages);
        RenderQueueSortFunc   sortFunc = convertQueueSortFunc(descriptor.sortMode);
        RenderQueueCreateInfo info     = {descriptor.isTransparent, phase, sortFunc};
        _renderQueues.emplace_back(CC_NEW(RenderQueue(std::move(info))));
    }

    // create descriptorset/layout
    gfx::DescriptorSetLayoutInfo layoutInfo = {localDescriptorSetLayout.bindings};
    _descLayout                             = device->createDescriptorSetLayout(layoutInfo);

    gfx::DescriptorSetInfo setInfo = {_descLayout};
    _descriptorSet                 = device->createDescriptorSet(setInfo);

    // create lighting buffer and view
    initLightingBuffer();

    _planarShadowQueue = CC_NEW(PlanarShadowQueue(_pipeline));

    // create reflection resource
    RenderQueueCreateInfo info = {true, _reflectionPhaseID, transparentCompareFn};
    _reflectionComp            = new ReflectionComp();

    gfx::ColorAttachment cAttch = {
        gfx::Format::RGBA8,
        gfx::SampleCount::X1,
        gfx::LoadOp::LOAD,
        gfx::StoreOp::STORE,
        {gfx::AccessType::FRAGMENT_SHADER_READ_TEXTURE},
        {gfx::AccessType::FRAGMENT_SHADER_READ_TEXTURE},
    };

    gfx::RenderPassInfo reflectionPassInfo;
    reflectionPassInfo.colorAttachments.push_back(cAttch);

    reflectionPassInfo.depthStencilAttachment = {
        _device->getDepthStencilFormat(),
        gfx::SampleCount::X1,
        gfx::LoadOp::LOAD,
        gfx::StoreOp::DISCARD,
        gfx::LoadOp::DISCARD,
        gfx::StoreOp::DISCARD,
        {gfx::AccessType::DEPTH_STENCIL_ATTACHMENT_WRITE},
    };

    _reflectionPass        = _device->createRenderPass(reflectionPassInfo);
    _reflectionRenderQueue = CC_NEW(RenderQueue(std::move(info)));
}

void LightingStage::destroy() {
    CC_SAFE_DELETE(_planarShadowQueue);
    CC_SAFE_DELETE(_reflectionRenderQueue);
    RenderStage::destroy();

    if (_reflectionPass != nullptr) {
        _reflectionPass->destroy();
        CC_SAFE_DELETE(_reflectionPass);
    }

    CC_SAFE_DELETE(_reflectionComp);
}

void LightingStage::fgLightingPass(scene::Camera *camera) {
    struct renderData {
        framegraph::TextureHandle gbuffer[4];   // read from gbuffer stage
        framegraph::TextureHandle depth;        // read from gbuffer stage
        framegraph::TextureHandle lightOutput;  // output texture
    };

    auto *      pipeline      = static_cast<DeferredPipeline *>(_pipeline);
    auto lightingSetup = [&] (framegraph::PassNodeBuilder &builder, renderData &data) {
        // read gbuffer
        for (int i = 0; i < 4; i++) {
            data.gbuffer[i] = builder.read(framegraph::TextureHandle(builder.readFromBlackboard(DeferredPipeline::_gbuffer[i])));
            builder.writeToBlackboard(DeferredPipeline::_gbuffer[i], data.gbuffer[i]);
        }

        // read depth
        data.depth = builder.read(framegraph::TextureHandle(builder.readFromBlackboard(DeferredPipeline::_depth)));
        builder.writeToBlackboard(DeferredPipeline::_depth, data.depth);

        // write to lighting output
        gfx::Color clearColor = pipeline->getClearcolor(camera);
        framegraph::RenderTargetAttachment::Descriptor colorAttachmentInfo;
        colorAttachmentInfo.usage       = framegraph::RenderTargetAttachment::Usage::COLOR;
        colorAttachmentInfo.loadOp      = gfx::LoadOp::CLEAR;
        colorAttachmentInfo.clearColor  = clearColor;
        colorAttachmentInfo.endAccesses = {gfx::AccessType::TRANSFER_READ};

        framegraph::Texture::Descriptor colorTexInfo;
        colorTexInfo.format = gfx::Format::RGBA16F;
        colorTexInfo.usage  = gfx::TextureUsageBit::COLOR_ATTACHMENT | gfx::TextureUsageBit::SAMPLED;
        colorTexInfo.width  = _device->getWidth();
        colorTexInfo.height = _device->getHeight();

        builder.create(data.lightOutput, DeferredPipeline::_lightingOut, colorTexInfo);
        data.lightOutput = builder.write(data.lightOutput, colorAttachmentInfo);
        builder.writeToBlackboard(DeferredPipeline::_lightingOut, data.lightOutput);

        // set render area
        auto renderArea = pipeline->getRenderArea(camera);
        gfx::Viewport viewport{ renderArea.x, renderArea.y, renderArea.width, renderArea.height, 0.F, 1.F};
        builder.setViewport(viewport, renderArea);
    };

    auto lightingExec = [&] (renderData const &data, const framegraph::DevicePassResourceTable &table) {
        auto *const sceneData     = _pipeline->getPipelineSceneData();
        auto *const sharedData    = sceneData->getSharedData();
        const auto &renderObjects = sceneData->getRenderObjects();

        // lighting info, ubo
        gatherLights(camera);
        _descriptorSet->update();

        auto *cmdBuff = pipeline->getCommandBuffers()[0];
        vector<uint> dynamicOffsets = {0};
        cmdBuff->bindDescriptorSet(static_cast<uint>(SetIndex::LOCAL), _descriptorSet, dynamicOffsets);

        uint const globalOffsets[] = {_pipeline->getPipelineUBO()->getCurrentCameraUBOOffset()};
        cmdBuff->bindDescriptorSet(static_cast<uint>(SetIndex::GLOBAL), pipeline->getDescriptorSet(), static_cast<uint>(std::size(globalOffsets)), globalOffsets);

        // gbuffer descriptorset setup
        gfx::SamplerInfo info{
            gfx::Filter::LINEAR,
            gfx::Filter::LINEAR,
            gfx::Filter::NONE,
            gfx::Address::CLAMP,
            gfx::Address::CLAMP,
            gfx::Address::CLAMP,
        };
        const auto  samplerHash = SamplerLib::genSamplerHash(info);
        auto *const sampler     = SamplerLib::getSampler(samplerHash);

        pipeline->getDescriptorSet()->bindSampler(static_cast<uint>(PipelineGlobalBindings::SAMPLER_GBUFFER_ALBEDOMAP), sampler);
        pipeline->getDescriptorSet()->bindSampler(static_cast<uint>(PipelineGlobalBindings::SAMPLER_GBUFFER_POSITIONMAP), sampler);
        pipeline->getDescriptorSet()->bindSampler(static_cast<uint>(PipelineGlobalBindings::SAMPLER_GBUFFER_NORMALMAP), sampler);
        pipeline->getDescriptorSet()->bindSampler(static_cast<uint>(PipelineGlobalBindings::SAMPLER_GBUFFER_EMISSIVEMAP), sampler);

        gfx::Texture *gbufferAlbedo    = (gfx::Texture *)(table.getRead(data.gbuffer[0]));
        gfx::Texture *gbufferPosition  = (gfx::Texture *)(table.getRead(data.gbuffer[1]));
        gfx::Texture *gbufferNormal    = (gfx::Texture *)(table.getRead(data.gbuffer[2]));
        gfx::Texture *gbufferEmissive   = (gfx::Texture *)(table.getRead(data.gbuffer[3]));

        pipeline->getDescriptorSet()->bindTexture(static_cast<uint>(PipelineGlobalBindings::SAMPLER_GBUFFER_ALBEDOMAP), gbufferAlbedo);
        pipeline->getDescriptorSet()->bindTexture(static_cast<uint>(PipelineGlobalBindings::SAMPLER_GBUFFER_POSITIONMAP), gbufferPosition);
        pipeline->getDescriptorSet()->bindTexture(static_cast<uint>(PipelineGlobalBindings::SAMPLER_GBUFFER_NORMALMAP), gbufferNormal);
        pipeline->getDescriptorSet()->bindTexture(static_cast<uint>(PipelineGlobalBindings::SAMPLER_GBUFFER_EMISSIVEMAP), gbufferEmissive);

        pipeline->getDescriptorSet()->update();

        // get pso and draw quad
        scene::Pass *pass   = sceneData->getSharedData()->deferredLightPass;
        gfx::Shader *shader = sceneData->getSharedData()->deferredPostPassShader;

        gfx::RenderPass *renderPass;// = table.getDevicePass()->getRenderPass().get();
        gfx::InputAssembler *inputAssembler = pipeline->getQuadIAOffScreen();
        gfx::PipelineState *pState         = PipelineStateManager::getOrCreatePipelineState(
            pass, shader, inputAssembler, renderPass);
        assert(pState != nullptr);

        cmdBuff->bindPipelineState(pState);
        cmdBuff->bindInputAssembler(inputAssembler);
        cmdBuff->draw(inputAssembler);

        //  transparent
        putTransparentObj2Queue();
        for (auto *queue : _renderQueues) {
            queue->sort();
            queue->recordCommandBuffer(_device, renderPass, cmdBuff);
        }

        _planarShadowQueue->recordCommandBuffer(_device, renderPass, cmdBuff);
    };

    pipeline->getFrameGraph().addPass<renderData>(IP_LIGHTING, DeferredPipeline::_passLighting, lightingSetup, lightingExec);
}

void LightingStage::putTransparentObj2Queue() {
    for (auto *queue : _renderQueues) {
        queue->clear();
    }

    auto *const sceneData     = _pipeline->getPipelineSceneData();
    const auto &renderObjects = sceneData->getRenderObjects();

    uint   m = 0;
    uint   p = 0;
    size_t k = 0;
    for (auto ro : renderObjects) {
        const auto *const model = ro.model;
        for (auto *subModel : model->getSubModels()) {
            for (auto *pass : subModel->getPasses()) {
                // TODO(xwx): need fallback of unlit and gizmo material.
                if (pass->getPhase() != _phaseID && pass->getPhase() != _defPhaseID) continue;
                for (k = 0; k < _renderQueues.size(); k++) {
                    _renderQueues[k]->insertRenderPass(ro, m, p);
                }
            }
        }
    }
}

void LightingStage::fgSsprPass(scene::Camera *camera) {
    struct RenderData {

    };

    auto ssprSetup = [&](framegraph::PassNodeBuilder &builder, RenderData &data) {};

    auto ssprExec = [&](RenderData const &data, const framegraph::DevicePassResourceTable &table) {};

}

void LightingStage::render(scene::Camera *camera) {
    auto *      pipeline      = static_cast<DeferredPipeline *>(_pipeline);
    auto *const sceneData     = _pipeline->getPipelineSceneData();
    auto *const sharedData    = sceneData->getSharedData();
    const auto &renderObjects = sceneData->getRenderObjects();

    if (renderObjects.empty()) {
        return;
    }

    auto *cmdBuff = pipeline->getCommandBuffers()[0];

    // lighting info
    gatherLights(camera);
    _descriptorSet->update();

    vector<uint> dynamicOffsets = {0};
    cmdBuff->bindDescriptorSet(static_cast<uint>(SetIndex::LOCAL), _descriptorSet, dynamicOffsets);

    // draw quad
    gfx::Rect renderArea = pipeline->getRenderArea(camera);

    gfx::Color clearColor = {0.0, 0.0, 0.0, 1.0};
    if (camera->clearFlag & static_cast<uint>(gfx::ClearFlagBit::COLOR)) {
        if (sharedData->isHDR) {
            srgbToLinear(&clearColor, camera->clearColor);
            const auto scale = sharedData->fpScale / camera->exposure;
            clearColor.x *= scale;
            clearColor.y *= scale;
            clearColor.z *= scale;
        } else {
            clearColor = camera->clearColor;
        }
    }

    clearColor.w = 0;

    auto *const deferredData = pipeline->getDeferredRenderData();
    auto *      frameBuffer  = deferredData->lightingFrameBuff;
    auto *      renderPass   = frameBuffer->getRenderPass();

    cmdBuff->beginRenderPass(renderPass, frameBuffer, renderArea, &clearColor,
                             camera->clearDepth, camera->clearStencil);

    uint const globalOffsets[] = {_pipeline->getPipelineUBO()->getCurrentCameraUBOOffset()};
    cmdBuff->bindDescriptorSet(static_cast<uint>(SetIndex::GLOBAL), pipeline->getDescriptorSet(), static_cast<uint>(std::size(globalOffsets)), globalOffsets);

    // get pso and draw quad
    scene::Pass *pass   = sceneData->getSharedData()->deferredLightPass;
    gfx::Shader *shader = sceneData->getSharedData()->deferredLightPassShader;

    gfx::InputAssembler *inputAssembler = pipeline->getQuadIAOffScreen();
    gfx::PipelineState * pState         = PipelineStateManager::getOrCreatePipelineState(
        pass, shader, inputAssembler, renderPass);
    assert(pState != nullptr);

    cmdBuff->bindPipelineState(pState);
    cmdBuff->bindInputAssembler(inputAssembler);
    cmdBuff->draw(inputAssembler);

    // transparent
    for (auto *queue : _renderQueues) {
        queue->clear();
    }

    uint   m = 0;
    uint   p = 0;
    size_t k = 0;
    for (auto ro : renderObjects) {
        const auto *const model = ro.model;
        for (auto *subModel : model->getSubModels()) {
            for (auto *pass : subModel->getPasses()) {
                // TODO(xwx): need fallback of unlit and gizmo material.
                if (pass->getPhase() != _phaseID && pass->getPhase() != _defPhaseID) continue;
                for (k = 0; k < _renderQueues.size(); k++) {
                    _renderQueues[k]->insertRenderPass(ro, m, p);
                }
            }
        }
    }

    for (auto *queue : _renderQueues) {
        queue->sort();
        queue->recordCommandBuffer(_device, renderPass, cmdBuff);
    }

    // planerQueue
    _planarShadowQueue->recordCommandBuffer(_device, renderPass, cmdBuff);

    cmdBuff->endRenderPass();

    if (_device->hasFeature(gfx::Feature::COMPUTE_SHADER)) {
        uint   m = 0;
        uint   p = 0;
        size_t k = 0;
        for (const auto &ro : renderObjects) {
            const auto *model = ro.model;
            for (auto *subModel : model->getSubModels()) {
                for (auto *pass : subModel->getPasses()) {
                    if (pass->getPhase() != _reflectionPhaseID) continue;
                    // dispatch for reflection
                    gfx::Texture *denoiseTex = subModel->getDescriptorSet()->getTexture(uint(ModelLocalBindings::STORAGE_REFLECTION));
                    if (!_reflectionComp->isInitialized()) {
                        _reflectionComp->init(_pipeline->getDevice(),
                                              pipeline->getDeferredRenderData()->lightingRenderTarget,
                                              pipeline->getDeferredRenderData()->gbufferFrameBuffer->getColorTextures()[1],
                                              denoiseTex,
                                              camera->matViewProj, 8, 8);
                    }
                    gfx::Rect clearRenderArea = {0, 0, _reflectionComp->getReflectionTex()->getWidth(), _reflectionComp->getReflectionTex()->getHeight()};
                    cmdBuff->beginRenderPass(const_cast<gfx::RenderPass *>(_reflectionComp->getClearPass()), const_cast<gfx::Framebuffer *>(_reflectionComp->getClearFramebuffer()), clearRenderArea, &clearColor, 0, 0);
                    cmdBuff->endRenderPass();

                    cmdBuff->pipelineBarrier(_reflectionComp->getBarrierPre());
                    cmdBuff->bindPipelineState(const_cast<gfx::PipelineState *>(_reflectionComp->getPipelineState()));
                    cmdBuff->bindDescriptorSet(0, const_cast<gfx::DescriptorSet *>(_reflectionComp->getDescriptorSet()));
                    cmdBuff->bindDescriptorSet(1, subModel->getDescriptorSet());

                    cmdBuff->dispatch(_reflectionComp->getDispatchInfo());

                    cmdBuff->pipelineBarrier(nullptr, const_cast<gfx::TextureBarrierList &>(_reflectionComp->getBarrierBeforeDenoise()), {const_cast<gfx::Texture *>(_reflectionComp->getReflectionTex()), denoiseTex});

                    cmdBuff->bindPipelineState(const_cast<gfx::PipelineState *>(_reflectionComp->getDenoisePipelineState()));
                    cmdBuff->bindDescriptorSet(0, const_cast<gfx::DescriptorSet *>(_reflectionComp->getDenoiseDescriptorSet()));
                    cmdBuff->bindDescriptorSet(1, subModel->getDescriptorSet());
                    cmdBuff->dispatch(_reflectionComp->getDenioseDispatchInfo());
                    cmdBuff->pipelineBarrier(nullptr, _reflectionComp->getBarrierAfterDenoise(), {denoiseTex});
                }
            }
        }
    }

    cmdBuff->beginRenderPass(_reflectionPass, frameBuffer, renderArea, &clearColor,
                             camera->clearDepth, camera->clearStencil);

    cmdBuff->bindDescriptorSet(static_cast<uint>(SetIndex::GLOBAL), pipeline->getDescriptorSet());

    // reflection
    _reflectionRenderQueue->clear();

    m = 0;
    p = 0;
    k = 0;
    for (const auto &ro : renderObjects) {
        const auto *model = ro.model;
        for (auto *subModel : model->getSubModels()) {
            for (auto *pass : subModel->getPasses()) {
                if (pass->getPhase() != _reflectionPhaseID) continue;
                _reflectionRenderQueue->insertRenderPass(ro, m, p);
            }
        }
    }

    _reflectionRenderQueue->sort();
    _reflectionRenderQueue->recordCommandBuffer(_device, renderPass, cmdBuff);

    cmdBuff->endRenderPass();
}

} // namespace pipeline
} // namespace cc
