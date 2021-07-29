
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

#include "PostprocessStage.h"
#include "../PipelineStateManager.h"
#include "../RenderQueue.h"
#include "../forward/UIPhase.h"
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
const String StageName = "PostprocessStage";
}

RenderStageInfo PostprocessStage::initInfo = {
    StageName,
    static_cast<uint>(DeferredStagePriority::POSTPROCESS),
    0,
    {{true, RenderQueueSortMode::BACK_TO_FRONT, {"default"}}},
};
const RenderStageInfo &PostprocessStage::getInitializeInfo() { return PostprocessStage::initInfo; }


PostprocessStage::PostprocessStage() {
    _uiPhase = CC_NEW(UIPhase);
}

bool PostprocessStage::initialize(const RenderStageInfo &info) {
    RenderStage::initialize(info);
    _renderQueueDescriptors = info.renderQueues;

    return true;
}

void PostprocessStage::activate(RenderPipeline *pipeline, RenderFlow *flow) {
    RenderStage::activate(pipeline, flow);
    _uiPhase->activate(pipeline);
    _phaseID = getPhaseID("default");

    for (const auto &descriptor : _renderQueueDescriptors) {
        uint phase = 0;
        for (const auto &stage : descriptor.stages) {
            phase |= getPhaseID(stage);
        }

        std::function<int(const RenderPass &, const RenderPass &)> sortFunc = opaqueCompareFn;
        switch (descriptor.sortMode) {
            case RenderQueueSortMode::BACK_TO_FRONT:
                sortFunc = transparentCompareFn;
                break;
            case RenderQueueSortMode::FRONT_TO_BACK:
                sortFunc = opaqueCompareFn;
            default:
                break;
        }

        RenderQueueCreateInfo info = {descriptor.isTransparent, phase, sortFunc};
        _renderQueues.emplace_back(CC_NEW(RenderQueue(std::move(info))));
    }

    gfx::DescriptorSetLayout *_globalSetlayout = _device->createDescriptorSetLayout({globalDescriptorSetLayout.bindings});
    _globalSet = _device->createDescriptorSet({ _globalSetlayout });
}

void PostprocessStage::destroy() {
    CC_SAFE_DELETE(_globalSetlayout);
    CC_SAFE_DELETE(_globalSet);
    CC_SAFE_DELETE(_uiPhase);
}

void PostprocessStage::render(scene::Camera *camera) {
    struct renderData {
        framegraph::TextureHandle lightingOut;      // read from lighting output
        framegraph::TextureHandle backBuffer;       // write to back buffer
    };

    auto *      pipeline      = static_cast<DeferredPipeline *>(_pipeline);
    auto postSetup = [&] (framegraph::PassNodeBuilder &builder, renderData &data) {
        data.lightingOut = builder.read(framegraph::TextureHandle(builder.readFromBlackboard(DeferredPipeline::fgStrHandleLightingOutTexture)));
        builder.writeToBlackboard(DeferredPipeline::fgStrHandleLightingOutTexture, data.lightingOut);

        // backbuffer is as an attachment
        framegraph::RenderTargetAttachment::Descriptor colorAttachmentInfo;
        colorAttachmentInfo.usage       = framegraph::RenderTargetAttachment::Usage::COLOR;

        gfx::ClearFlagBit clearFlags = static_cast<gfx::ClearFlagBit>(camera->clearFlag);
        if (!hasFlag(clearFlags, gfx::ClearFlagBit::COLOR)) {
            if (hasFlag(clearFlags, static_cast<gfx::ClearFlagBit>(skyboxFlag))) {
                colorAttachmentInfo.loadOp = gfx::LoadOp::DISCARD;
            } else {
                colorAttachmentInfo.loadOp        = gfx::LoadOp::LOAD;
                colorAttachmentInfo.beginAccesses = {gfx::AccessType::PRESENT};
            }
        }

        colorAttachmentInfo.endAccesses = {gfx::AccessType::PRESENT};

        data.backBuffer = builder.write(framegraph::TextureHandle(builder.readFromBlackboard(DeferredPipeline::fgStrHandleBackBufferTexture)), colorAttachmentInfo);
        builder.writeToBlackboard(DeferredPipeline::fgStrHandleBackBufferTexture, data.backBuffer);

        auto renderArea = pipeline->getRenderArea(camera, !camera->window->hasOffScreenAttachments);
        gfx::Viewport viewport{ renderArea.x, renderArea.y, renderArea.width, renderArea.height, 0.F, 1.F};
        builder.setViewport(viewport, renderArea);
    };

    auto postExec = [&] (renderData const &data, const framegraph::DevicePassResourceTable &table) {
        DeferredPipeline *pipeline = static_cast<DeferredPipeline *>(RenderPipeline::getInstance());
        assert(pipeline != nullptr);
        PostprocessStage *stage = (PostprocessStage *)pipeline->getRenderstageByName(StageName);
        assert(stage != nullptr);
        gfx::RenderPass *renderPass = table.getRenderPass().get();
        assert(renderPass != nullptr);

        // bind descriptor
        gfx::Texture *lightingOut    = (gfx::Texture *)(table.getRead(data.lightingOut));

        gfx::SamplerInfo info{
            gfx::Filter::LINEAR,
            gfx::Filter::LINEAR,
            gfx::Filter::NONE,
            gfx::Address::CLAMP,
            gfx::Address::CLAMP,
            gfx::Address::CLAMP,
        };

        stage->getGlobalSet()->bindBuffer(0, pipeline->getDescriptorSet()->getBuffer(0));
        stage->getGlobalSet()->bindBuffer(1, pipeline->getDescriptorSet()->getBuffer(1));

        const auto  samplerHash = SamplerLib::genSamplerHash(info);
        auto *const sampler     = SamplerLib::getSampler(samplerHash);
        stage->getGlobalSet()->bindSampler(static_cast<uint>(PipelineGlobalBindings::SAMPLER_LIGHTING_RESULTMAP), sampler);
        stage->getGlobalSet()->bindTexture(static_cast<uint>(PipelineGlobalBindings::SAMPLER_LIGHTING_RESULTMAP), lightingOut);
        stage->getGlobalSet()->update();

        auto *cmdBf = pipeline->getCommandBuffers()[0];
        uint const globalOffsets[] = {pipeline->getPipelineUBO()->getCurrentCameraUBOOffset()};
        cmdBf->bindDescriptorSet(static_cast<uint>(SetIndex::GLOBAL), stage->getGlobalSet(), 0, nullptr);

        // post proces
        auto *const  sceneData     = pipeline->getPipelineSceneData();
        scene::Pass *pv            = sceneData->getSharedData()->deferredPostPass;
        gfx::Shader *sd            = sceneData->getSharedData()->deferredPostPassShader;

        gfx::InputAssembler *ia = pipeline->getQuadIAOffScreen();
        gfx::PipelineState * pso = PipelineStateManager::getOrCreatePipelineState(pv, sd, ia, renderPass);
        assert(pso != nullptr);

        cmdBf->bindPipelineState(pso);
        cmdBf->bindInputAssembler(ia);
        cmdBf->draw(ia);

        stage->getUIPhase()->render(pipeline->getFrameGraphCamera(), renderPass);
    };

    pipeline->getFrameGraph().addPass<renderData>(static_cast<uint>(DeferredInsertPoint::IP_POSTPROCESS), DeferredPipeline::fgStrHandlePostprocessPass, postSetup, postExec);
    pipeline->getFrameGraph().presentFromBlackboard(DeferredPipeline::fgStrHandleBackBufferTexture);
}
} // namespace pipeline
} // namespace cc
