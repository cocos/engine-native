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
RenderStageInfo PostprocessStage::initInfo = {
    "PostprocessStage",
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
}

void PostprocessStage::destroy() {
}

void PostprocessStage::renderFG(scene::Camera *camera) {
    auto *      pipeline      = static_cast<DeferredPipeline *>(_pipeline);

    struct renderData {
        framegraph::TextureHandle lightingOut;      // read from lighting output
        framegraph::TextureHandle depth;            // read from depth
        framegraph::TextureHandle backBuffer;       // write to back buffer
    };

    auto postSetup = [&] (framegraph::PassNodeBuilder &builder, renderData &data) {
        data.lightingOut = builder.read(framegraph::TextureHandle(builder.readFromBlackboard(DeferredPipeline::_lightingOut)));
        builder.writeToBlackboard(DeferredPipeline::_lightingOut, data.lightingOut);

        data.depth = builder.read(framegraph::TextureHandle(builder.readFromBlackboard(DeferredPipeline::_depth)));
        builder.writeToBlackboard(DeferredPipeline::_depth, data.depth);

        data.backBuffer = builder.read(framegraph::TextureHandle(builder.readFromBlackboard(DeferredPipeline::_backBuffer)));
        builder.writeToBlackboard(DeferredPipeline::_backBuffer, data.backBuffer);
    };

    auto postExec = [&] (renderData const &data, const framegraph::DevicePassResourceTable &table) {
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
        const auto  samplerHash = SamplerLib::genSamplerHash(info);
        auto *const sampler     = SamplerLib::getSampler(samplerHash);
        pipeline->getDescriptorSet()->bindSampler(static_cast<uint>(PipelineGlobalBindings::SAMPLER_LIGHTING_RESULTMAP), sampler);
        pipeline->getDescriptorSet()->bindTexture(static_cast<uint>(PipelineGlobalBindings::SAMPLER_LIGHTING_RESULTMAP), lightingOut);

        auto *cmdBf = pipeline->getCommandBuffers()[0];
        uint const globalOffsets[] = {_pipeline->getPipelineUBO()->getCurrentCameraUBOOffset()};
        cmdBf->bindDescriptorSet(static_cast<uint>(SetIndex::GLOBAL), pipeline->getDescriptorSet(), static_cast<uint>(std::size(globalOffsets)), globalOffsets);

        // post proces
        auto *const  sceneData     = _pipeline->getPipelineSceneData();
        scene::Pass *pv            = sceneData->getSharedData()->deferredPostPass;
        gfx::Shader *sd            = sceneData->getSharedData()->deferredPostPassShader;

        gfx::InputAssembler *ia = pipeline->getQuadIAOffScreen();

        gfx::RenderPass *rp;// = table.getDevicePass()->getRenderPass().get();
        gfx::PipelineState * pso = PipelineStateManager::getOrCreatePipelineState(pv, sd, ia, rp);
        assert(pso != nullptr);

        cmdBf->bindPipelineState(pso);
        cmdBf->bindInputAssembler(ia);
        cmdBf->draw(ia);
    };

    pipeline->getFrameGraph().addPass<renderData>(IP_POSTPROCESS, DeferredPipeline::_passPostprocess, postSetup, postExec);
    pipeline->getFrameGraph().presentFromBlackboard(DeferredPipeline::_backBuffer);
}

void PostprocessStage::render(scene::Camera *camera) {
    auto *pp = dynamic_cast<DeferredPipeline *>(_pipeline);
    assert(pp != nullptr);
    gfx::CommandBuffer *cmdBf  = pp->getCommandBuffers()[0];

    _pipeline->getPipelineUBO()->updateCameraUBO(camera);
    gfx::Rect renderArea = pp->getRenderArea(camera);

    if (hasFlag(static_cast<gfx::ClearFlags>(camera->clearFlag), gfx::ClearFlagBit::COLOR)) {
        _clearColors[0].x = camera->clearColor.x;
        _clearColors[0].y = camera->clearColor.y;
        _clearColors[0].z = camera->clearColor.z;
    }

    _clearColors[0].w = camera->clearColor.w;

    gfx::Framebuffer *fb            = camera->window->frameBuffer;
    const auto &      colorTextures = fb->getColorTextures();
    gfx::RenderPass * rp            = !colorTextures.empty() && colorTextures[0] ? fb->getRenderPass() : pp->getOrCreateRenderPass(static_cast<gfx::ClearFlags>(camera->clearFlag));

    cmdBf->beginRenderPass(rp, fb, renderArea, _clearColors, camera->clearDepth, camera->clearStencil);
    uint const globalOffsets[] = {_pipeline->getPipelineUBO()->getCurrentCameraUBOOffset()};
    cmdBf->bindDescriptorSet(static_cast<uint>(SetIndex::GLOBAL), pp->getDescriptorSet(), static_cast<uint>(std::size(globalOffsets)), globalOffsets);

    // post proces
    auto *const  sceneData     = _pipeline->getPipelineSceneData();
    scene::Pass *pv            = sceneData->getSharedData()->deferredPostPass;
    gfx::Shader *sd            = sceneData->getSharedData()->deferredPostPassShader;
    const auto & renderObjects = sceneData->getRenderObjects();

    if (!renderObjects.empty()) {
        gfx::InputAssembler *ia  = pp->getQuadIAOffScreen();
        gfx::PipelineState * pso = PipelineStateManager::getOrCreatePipelineState(pv, sd, ia, rp);
        assert(pso != nullptr);

        cmdBf->bindPipelineState(pso);
        cmdBf->bindInputAssembler(ia);
        cmdBf->draw(ia);
    }

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
                // TODO(xwx): need fallback of ulit and gizmo material.
                if (pass->getPhase() != _phaseID) continue;
                for (k = 0; k < _renderQueues.size(); k++) {
                    _renderQueues[k]->insertRenderPass(ro, m, p);
                }
            }
        }
    }

    for (auto *queue : _renderQueues) {
        queue->sort();
        queue->recordCommandBuffer(_device, rp, cmdBf);
    }

    _uiPhase->render(camera, rp);
    cmdBf->endRenderPass();
}
} // namespace pipeline
} // namespace cc
