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

#include "GbufferStage.h"
#include "../BatchedBuffer.h"
#include "../InstancedBuffer.h"
#include "../PlanarShadowQueue.h"
#include "../RenderBatchedQueue.h"
#include "../RenderInstancedQueue.h"
#include "../RenderQueue.h"
#include "DeferredPipeline.h"
#include "MainFlow.h"
#include "gfx-base/GFXCommandBuffer.h"
#include "gfx-base/GFXDevice.h"
#include "gfx-base/GFXFramebuffer.h"
#include "gfx-base/GFXQueue.h"

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

RenderStageInfo GbufferStage::initInfo = {
    "GbufferStage",
    static_cast<uint>(DeferredStagePriority::GBUFFER),
    static_cast<uint>(RenderFlowTag::SCENE),
    {{false, RenderQueueSortMode::FRONT_TO_BACK, {"default"}},
     {true, RenderQueueSortMode::BACK_TO_FRONT, {"default", "planarShadow"}}}};
const RenderStageInfo &GbufferStage::getInitializeInfo() { return GbufferStage::initInfo; }

GbufferStage::GbufferStage() {
    _batchedQueue   = CC_NEW(RenderBatchedQueue);
    _instancedQueue = CC_NEW(RenderInstancedQueue);
}

GbufferStage::~GbufferStage() = default;

bool GbufferStage::initialize(const RenderStageInfo &info) {
    RenderStage::initialize(info);
    _renderQueueDescriptors = info.renderQueues;
    _phaseID                = getPhaseID("deferred");
    return true;
}

void GbufferStage::activate(RenderPipeline *pipeline, RenderFlow *flow) {
    RenderStage::activate(pipeline, flow);

    for (const auto &descriptor : _renderQueueDescriptors) {
        uint                  phase    = convertPhase(descriptor.stages);
        RenderQueueSortFunc   sortFunc = convertQueueSortFunc(descriptor.sortMode);
        RenderQueueCreateInfo info     = {descriptor.isTransparent, phase, sortFunc};
        _renderQueues.emplace_back(CC_NEW(RenderQueue(std::move(info))));
    }
    _planarShadowQueue = CC_NEW(PlanarShadowQueue(_pipeline));
}

void GbufferStage::destroy() {
    CC_SAFE_DELETE(_batchedQueue);
    CC_SAFE_DELETE(_instancedQueue);
    CC_SAFE_DELETE(_planarShadowQueue);
    RenderStage::destroy();
}

void GbufferStage::dispenseRenderObject2Queues() {
    _instancedQueue->clear();
    _batchedQueue->clear();

    const auto &renderObjects = _pipeline->getPipelineSceneData()->getRenderObjects();
    for (auto *queue : _renderQueues) {
        queue->clear();
    }

    uint   subModelIdx = 0;
    uint   passIdx     = 0;
    size_t k           = 0;
    for (auto ro : renderObjects) {
        const auto *const model = ro.model;

        subModelIdx = 0;
        for (auto *subModel : model->getSubModels()) {
            passIdx = 0;
            for (auto *pass : subModel->getPasses()) {
                if (pass->getPhase() != _phaseID) continue;
                if (pass->getBatchingScheme() == scene::BatchingSchemes::INSTANCING) {
                    auto *instancedBuffer = InstancedBuffer::get(pass);
                    instancedBuffer->merge(model, subModel, passIdx);
                    _instancedQueue->add(instancedBuffer);
                } else if (pass->getBatchingScheme() == scene::BatchingSchemes::VB_MERGING) {
                    auto *batchedBuffer = BatchedBuffer::get(pass);
                    batchedBuffer->merge(subModel, passIdx, model);
                    _batchedQueue->add(batchedBuffer);
                } else {
                    for (k = 0; k < _renderQueues.size(); k++) {
                        _renderQueues[k]->insertRenderPass(ro, subModelIdx, passIdx);
                    }
                }

                ++passIdx;
            }

            ++subModelIdx;
        }
    }

    for (auto *queue : _renderQueues) {
        queue->sort();
    }
}

void GbufferStage::renderFG(scene::Camera *camera) {
    struct renderData {
        framegraph::TextureHandle gbuffer[4];
        framegraph::TextureHandle depth;
    };

    auto *      pipeline      = static_cast<DeferredPipeline *>(_pipeline);
    auto gbufferSetup = [&](framegraph::PassNodeBuilder &builder, renderData &data) {
        // gbuffer setup
        gfx::Color clearColor = {0.0, 0.0, 0.0, 0.0};
        for (int i = 0; i < 4; ++i) {
            framegraph::RenderTargetAttachment::Descriptor colorAttachmentInfo;
            colorAttachmentInfo.usage       = framegraph::RenderTargetAttachment::Usage::COLOR;
            colorAttachmentInfo.loadOp      = gfx::LoadOp::CLEAR;
            colorAttachmentInfo.clearColor  = clearColor;
            colorAttachmentInfo.endAccesses = {gfx::AccessType::TRANSFER_READ};

            framegraph::Texture::Descriptor colorTexInfo;
            colorTexInfo.format = gfx::Format::RGBA8;
            colorTexInfo.usage  = gfx::TextureUsageBit::COLOR_ATTACHMENT | gfx::TextureUsageBit::SAMPLED;
            colorTexInfo.width  = device->getWidth();
            colorTexInfo.height = device->getHeight();

            builder.create(data.gbuffer[i], DeferredPipeline::_gbuffer[i], colorTexInfo);
            data.colorTex = builder.write(data.gbuffer[i], colorAttachmentInfo);
            builder.writeToBlackboard(DeferredPipeline::_gbuffer[i], data.gbuffer[i]);
        }

        // depth setup
        framegraph::RenderTargetAttachment::Descriptor depthInfo;
        depthInfo.usage = framegraph::RenderTargetAttachment::Usage::DEPTH_STENCIL;
        depthInfo.loadOp = gfx::LoadOp::CLEAR;
        depthInfo.clearDepth = camera->clearDepth;
        depthInfo.clearStencil = camera->clearStencil;
        depthInfo.endAccesses = {gfx::AccessType::DEPTH_STENCIL_ATTACHMENT_WRITE};

        framegraph::Texture::Descriptor depthTexInfo;
        depthTexInfo.format = _device->getDepthStencilFormat();
        depthTexInfo.usage  = gfx::TextureUsageBit::DEPTH_STENCIL_ATTACHMENT;
        depthTexInfo.width  = device->getWidth();
        depthTexInfo.height = device->getHeight();

        builder.create(data.depth, DeferredPipeline::_depth, depthTexInfo);
        data.colorTex = builder.write(data.depth, depthInfo);
        builder.writeToBlackboard(DeferredPipeline::_depth, data.depth);

        // viewport setup
        builder.setViewport(camera->viewPort, pipeline->getRenderArea(camera));
    };

    auto gbufferExec = [&] (DrawData const &data, const framegraph::DevicePassResourceTable &table) {
        dispenseRenderObject2Queues();
        auto *cmdBuff = pipeline->getCommandBuffers()[0];

        _instancedQueue->uploadBuffers(cmdBuff);
        _batchedQueue->uploadBuffers(cmdBuff);

        // render area is not oriented
        _renderArea = pipeline->getRenderArea(camera);
        pipeline->updateQuadVertexData(_renderArea);
        gfx::RenderPass *renderPass = table.getDevicePass()->getRenderPass().get();

        // descriptorset bindings
        uint const globalOffsets[] = {_pipeline->getPipelineUBO()->getCurrentCameraUBOOffset()};
        cmdBuff->bindDescriptorSet(globalSet, _pipeline->getDescriptorSet(), static_cast<uint>(std::size(globalOffsets)), globalOffsets);

        // record commands
        _renderQueues[0]->recordCommandBuffer(_device, renderPass, cmdBuff);
        _instancedQueue->recordCommandBuffer(_device, renderPass, cmdBuff);
        _batchedQueue->recordCommandBuffer(_device, renderPass, cmdBuff);
    };

    _pipeline->getFrameGraph()->addPass<renderData>(IP_GBUFFER, gbufferSetup, gbufferExec);
}

void GbufferStage::render(scene::Camera *camera) {
    _instancedQueue->clear();
    _batchedQueue->clear();
    auto *      pipeline      = static_cast<DeferredPipeline *>(_pipeline);
    const auto &renderObjects = _pipeline->getPipelineSceneData()->getRenderObjects();
    if (renderObjects.empty()) {
        return;
    }

    for (auto *queue : _renderQueues) {
        queue->clear();
    }

    uint   subModelIdx = 0;
    uint   passIdx     = 0;
    size_t k           = 0;
    for (auto ro : renderObjects) {
        const auto *const model = ro.model;

        subModelIdx = 0;
        for (auto *subModel : model->getSubModels()) {
            passIdx = 0;
            for (auto *pass : subModel->getPasses()) {
                if (pass->getPhase() != _phaseID) continue;
                if (pass->getBatchingScheme() == scene::BatchingSchemes::INSTANCING) {
                    auto *instancedBuffer = InstancedBuffer::get(pass);
                    instancedBuffer->merge(model, subModel, passIdx);
                    _instancedQueue->add(instancedBuffer);
                } else if (pass->getBatchingScheme() == scene::BatchingSchemes::VB_MERGING) {
                    auto *batchedBuffer = BatchedBuffer::get(pass);
                    batchedBuffer->merge(subModel, passIdx, model);
                    _batchedQueue->add(batchedBuffer);
                } else {
                    for (k = 0; k < _renderQueues.size(); k++) {
                        _renderQueues[k]->insertRenderPass(ro, subModelIdx, passIdx);
                    }
                }

                ++passIdx;
            }

            ++subModelIdx;
        }
    }
    for (auto *queue : _renderQueues) {
        queue->sort();
    }

    auto *cmdBuff = pipeline->getCommandBuffers()[0];

    _instancedQueue->uploadBuffers(cmdBuff);
    _batchedQueue->uploadBuffers(cmdBuff);

    // render area is not oriented
    _renderArea = pipeline->getRenderArea(camera);
    pipeline->updateQuadVertexData(_renderArea);
    auto *const deferredData = pipeline->getDeferredRenderData();
    auto *      framebuffer  = deferredData->gbufferFrameBuffer;
    auto *      renderPass   = framebuffer->getRenderPass();

    cmdBuff->beginRenderPass(renderPass, framebuffer, _renderArea, _clearColors, camera->clearDepth, camera->clearStencil);

    uint const globalOffsets[] = {_pipeline->getPipelineUBO()->getCurrentCameraUBOOffset()};
    cmdBuff->bindDescriptorSet(globalSet, _pipeline->getDescriptorSet(), static_cast<uint>(std::size(globalOffsets)), globalOffsets);

    _renderQueues[0]->recordCommandBuffer(_device, renderPass, cmdBuff);
    _instancedQueue->recordCommandBuffer(_device, renderPass, cmdBuff);
    _batchedQueue->recordCommandBuffer(_device, renderPass, cmdBuff);
    //_renderQueues[1]->recordCommandBuffer(_device, renderPass, cmdBuff);

    cmdBuff->endRenderPass();
}

} // namespace pipeline
} // namespace cc
