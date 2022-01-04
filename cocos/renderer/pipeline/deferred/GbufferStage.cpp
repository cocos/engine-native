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
#include "frame-graph/DevicePass.h"
#include "frame-graph/DevicePassResourceTable.h"
#include "frame-graph/Resource.h"
#include "gfx-base/GFXCommandBuffer.h"
#include "gfx-base/GFXDevice.h"
#include "gfx-base/GFXFramebuffer.h"
#include "gfx-base/GFXQueue.h"

namespace cc {
namespace pipeline {
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
    _phaseID                = getPhaseID("default");
    return true;
}

void GbufferStage::activate(RenderPipeline *pipeline, RenderFlow *flow) {
    RenderStage::activate(pipeline, flow);

    for (const auto &descriptor : _renderQueueDescriptors) {
        uint                  phase    = convertPhase(descriptor.stages);
        RenderQueueSortFunc   sortFunc = convertQueueSortFunc(descriptor.sortMode);
        RenderQueueCreateInfo info     = {descriptor.isTransparent, phase, sortFunc};
        _renderQueues.emplace_back(CC_NEW(RenderQueue(_pipeline, std::move(info), true)));
    }
    _planarShadowQueue = CC_NEW(PlanarShadowQueue(_pipeline));
}

void GbufferStage::destroy() {
    CC_SAFE_DELETE(_batchedQueue);
    CC_SAFE_DELETE(_instancedQueue);
    CC_SAFE_DESTROY_AND_DELETE(_planarShadowQueue);
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
        const auto *const model         = ro.model;
        const auto &      subModels     = model->getSubModels();
        auto              subModelCount = subModels.size();
        for (subModelIdx = 0; subModelIdx < subModelCount; ++subModelIdx) {
            const auto &subModel  = subModels[subModelIdx];
            const auto &passes    = subModel->getPasses();
            auto        passCount = passes.size();
            for (passIdx = 0; passIdx < passCount; ++passIdx) {
                const auto &pass = passes[passIdx];
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
            }
        }
    }

    for (auto *queue : _renderQueues) {
        queue->sort();
    }
}
void GbufferStage::recordCommands(DeferredPipeline *pipeline, scene::Camera *camera, gfx::RenderPass *renderPass) {
    auto *cmdBuff = pipeline->getCommandBuffers()[0];

    // DescriptorSet bindings
    const std::array<uint, 1> globalOffsets = {_pipeline->getPipelineUBO()->getCurrentCameraUBOOffset()};
    cmdBuff->bindDescriptorSet(globalSet, pipeline->getDescriptorSet(), utils::toUint(globalOffsets.size()), globalOffsets.data());

    // record commands
    _renderQueues[0]->recordCommandBuffer(_device, camera, renderPass, cmdBuff);
    _instancedQueue->recordCommandBuffer(_device, renderPass, cmdBuff);
    _batchedQueue->recordCommandBuffer(_device, renderPass, cmdBuff);
}

void GbufferStage::render(scene::Camera *camera) {
    struct RenderData {
        framegraph::TextureHandle gbuffer[4];
        framegraph::TextureHandle depth;
    };

    auto  *pipeline = static_cast<DeferredPipeline *>(_pipeline);
    float  shadingScale{_pipeline->getPipelineSceneData()->getShadingScale()};
    _renderArea = RenderPipeline::getRenderArea(camera);

    auto gbufferSetup = [&](framegraph::PassNodeBuilder &builder, RenderData &data) {
        builder.subpass();

        // gbuffer setup
        gfx::TextureInfo gbufferInfo = {
            gfx::TextureType::TEX2D,
            gfx::TextureUsageBit::COLOR_ATTACHMENT | gfx::TextureUsageBit::INPUT_ATTACHMENT,
            gfx::Format::RGBA8,
            static_cast<uint>(static_cast<float>(pipeline->getWidth()) * shadingScale),
            static_cast<uint>(static_cast<float>(pipeline->getHeight()) * shadingScale),
        };
        gfx::TextureInfo gbufferInfoFloat = {
            gfx::TextureType::TEX2D,
            gfx::TextureUsageBit::COLOR_ATTACHMENT | gfx::TextureUsageBit::INPUT_ATTACHMENT,
            gfx::Format::RGBA16F,
            static_cast<uint>(static_cast<float>(pipeline->getWidth()) * shadingScale),
            static_cast<uint>(static_cast<float>(pipeline->getHeight()) * shadingScale),
        };
        for (int i = 0; i < DeferredPipeline::GBUFFER_COUNT - 1; ++i) {
            if (i != 0) { // positions & normals need more precision
                data.gbuffer[i] = builder.create(DeferredPipeline::fgStrHandleGbufferTexture[i], gbufferInfoFloat);
            } else {
                data.gbuffer[i] = builder.create(DeferredPipeline::fgStrHandleGbufferTexture[i], gbufferInfo);
            }
        }

        auto subpassEnabled = _device->hasFeature(gfx::Feature::INPUT_ATTACHMENT_BENEFIT);
        if (subpassEnabled) {
            // when subpass enabled, the color result (gles2/gles3) will write to gbuffer[3] and the blit to color texture, so the format should be RGBA16F
            data.gbuffer[3] = builder.create(DeferredPipeline::fgStrHandleGbufferTexture[3], gbufferInfoFloat);
        } else {
            data.gbuffer[3] = builder.create(DeferredPipeline::fgStrHandleGbufferTexture[3], gbufferInfo);
        }

        gfx::Color clearColor{0.0, 0.0, 0.0, 0.0};

        framegraph::RenderTargetAttachment::Descriptor colorInfo;
        colorInfo.usage         = framegraph::RenderTargetAttachment::Usage::COLOR;
        colorInfo.loadOp        = gfx::LoadOp::CLEAR;
        colorInfo.clearColor    = clearColor;
        colorInfo.beginAccesses = {gfx::AccessType::FRAGMENT_SHADER_READ_COLOR_INPUT_ATTACHMENT};
        colorInfo.endAccesses   = {gfx::AccessType::FRAGMENT_SHADER_READ_COLOR_INPUT_ATTACHMENT};
        for (int i = 0; i < DeferredPipeline::GBUFFER_COUNT; ++i) {
            data.gbuffer[i] = builder.write(data.gbuffer[i], colorInfo);
            builder.writeToBlackboard(DeferredPipeline::fgStrHandleGbufferTexture[i], data.gbuffer[i]);
        }

        // depth setup
        gfx::TextureInfo depthTexInfo = {
            gfx::TextureType::TEX2D,
            gfx::TextureUsageBit::DEPTH_STENCIL_ATTACHMENT | gfx::TextureUsageBit::SAMPLED,
            gfx::Format::DEPTH_STENCIL,
            static_cast<uint>(static_cast<float>(pipeline->getWidth()) * shadingScale),
            static_cast<uint>(static_cast<float>(pipeline->getHeight()) * shadingScale),
        };
        data.depth = builder.create(DeferredPipeline::fgStrHandleOutDepthTexture, depthTexInfo);

        framegraph::RenderTargetAttachment::Descriptor depthInfo;
        depthInfo.usage        = framegraph::RenderTargetAttachment::Usage::DEPTH_STENCIL;
        depthInfo.loadOp       = gfx::LoadOp::CLEAR;
        depthInfo.clearDepth   = camera->getClearDepth();
        depthInfo.clearStencil = camera->getClearStencil();
        depthInfo.endAccesses  = {gfx::AccessType::DEPTH_STENCIL_ATTACHMENT_WRITE};
        data.depth             = builder.write(data.depth, depthInfo);
        builder.writeToBlackboard(DeferredPipeline::fgStrHandleOutDepthTexture, data.depth);

        // viewport setup
        builder.setViewport(pipeline->getViewport(camera), pipeline->getScissor(camera));
    };

    auto gbufferExec = [this, camera](const RenderData & /*data*/, const framegraph::DevicePassResourceTable &table) {
        recordCommands(static_cast<DeferredPipeline *>(_pipeline), camera, table.getRenderPass());
    };

    // Command 'updateBuffer' must be recorded outside render passes, cannot put them in execute lambda
    dispenseRenderObject2Queues();
    auto *cmdBuff = pipeline->getCommandBuffers()[0];
    _instancedQueue->uploadBuffers(cmdBuff);
    _batchedQueue->uploadBuffers(cmdBuff);

    // if empty == true, gbuffer and lightig passes will be ignored
    bool empty = _renderQueues[0]->empty() && _instancedQueue->empty() && _batchedQueue->empty();
    if (!empty) {
        pipeline->getFrameGraph().addPass<RenderData>(static_cast<uint>(DeferredInsertPoint::DIP_GBUFFER), DeferredPipeline::fgStrHandleGbufferPass, gbufferSetup, gbufferExec);
    }
}
} // namespace pipeline
} // namespace cc
