/****************************************************************************
 Copyright (c) 2021 Xiamen Yaji Software Co., Ltd.

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

#include "ARStage.h"
#include "../BatchedBuffer.h"
#include "../Enum.h"
#include "../InstancedBuffer.h"
#include "../PlanarShadowQueue.h"
#include "../RenderAdditiveLightQueue.h"
#include "../RenderBatchedQueue.h"
#include "../RenderInstancedQueue.h"
#include "../RenderQueue.h"
#include "../forward/ForwardPipeline.h"
#include "../helper/Utils.h"
#include "gfx-base/GFXCommandBuffer.h"
#include "gfx-base/GFXDef-common.h"
#include "gfx-base/GFXFramebuffer.h"
#include "gfx-base/GFXTexture.h"
#include "pipeline/RenderPipeline.h"


// ARModule ADD, need remove after modify
//#include "../ar/ARBackground.h"

#include "ar/ARModule.h"
#include "gfx-agent/DeviceAgent.h"

namespace cc {
namespace pipeline {

RenderStageInfo ARStage::initInfo = {
    "ARStage",
    static_cast<uint>(ForwardStagePriority::AR),
    static_cast<uint>(RenderFlowTag::SCENE)};
const RenderStageInfo &ARStage::getInitializeInfo() { return ARStage::initInfo; }

ARStage::ARStage() {
    _arBackground = CC_NEW(ARBackground);
}

ARStage::~ARStage() = default;

bool ARStage::initialize(const RenderStageInfo &info) {
    RenderStage::initialize(info);
    return true;
}

void ARStage::activate(RenderPipeline *pipeline, RenderFlow *flow) {
    RenderStage::activate(pipeline, flow);
    
    _arBackground->activate(pipeline, _device);
}

void ARStage::destroy() {
    CC_SAFE_DELETE(_arBackground);
    CC_SAFE_DELETE(_pipeline);
    CC_SAFE_DELETE(_device);
    RenderStage::destroy();
}

void ARStage::render(scene::Camera *camera) {
    // UI_3D: 8388608 0x00800000 (1 << 23)
    const scene::Node *camNode = camera->node;
    const int flag = (static_cast<int>(camNode->getLayer())) & 0x00800000;
    if(flag == 0) return;
    //return;

    struct RenderData {
        framegraph::TextureHandle outputTex;
        framegraph::TextureHandle depth;
    };

    float shadingScale{_pipeline->getPipelineSceneData()->getSharedData()->shadingScale};

    auto arSetup = [&](framegraph::PassNodeBuilder &builder, RenderData &data) {
        gfx::TextureInfo colorTexInfo = {
            gfx::TextureType::TEX2D,
            gfx::TextureUsageBit::COLOR_ATTACHMENT | gfx::TextureUsageBit::SAMPLED,
            gfx::Format::RGBA16F,
            static_cast<uint>(camera->window->getWidth() * shadingScale),
            static_cast<uint>(camera->window->getHeight() * shadingScale),
        };
        data.outputTex = builder.create(RenderPipeline::fgStrHandleOutColorTexture, colorTexInfo);
        /*
        //if (hasFlag(static_cast<gfx::ClearFlags>(camera->clearFlag), gfx::ClearFlagBit::COLOR)) {
            _clearColors[0].x = camera->clearColor.x;
            _clearColors[0].y = camera->clearColor.y;
            _clearColors[0].z = camera->clearColor.z;
        //}
        _clearColors[0].w = camera->clearColor.w;
        //*/
        framegraph::RenderTargetAttachment::Descriptor colorAttachmentInfo;
        colorAttachmentInfo.usage      = framegraph::RenderTargetAttachment::Usage::COLOR;
        //colorAttachmentInfo.clearColor = _clearColors[0];
        colorAttachmentInfo.loadOp     = gfx::LoadOp::CLEAR;
        /*
        auto clearFlags = static_cast<gfx::ClearFlagBit>(camera->clearFlag);
        if (!hasFlag(clearFlags, gfx::ClearFlagBit::COLOR)) {
            if (hasFlag(clearFlags, static_cast<gfx::ClearFlagBit>(skyboxFlag))) {
                colorAttachmentInfo.loadOp = gfx::LoadOp::DISCARD;
            } else {
                colorAttachmentInfo.loadOp = gfx::LoadOp::LOAD;
            }
        }
        */
        colorAttachmentInfo.endAccesses = {gfx::AccessType::COLOR_ATTACHMENT_WRITE};

        data.outputTex   = builder.write(data.outputTex, colorAttachmentInfo);

        // depth
        gfx::TextureInfo depthTexInfo{
            gfx::TextureType::TEX2D,
            gfx::TextureUsageBit::DEPTH_STENCIL_ATTACHMENT,
            gfx::Format::DEPTH_STENCIL,
            static_cast<uint>(_pipeline->getWidth() * shadingScale),
            static_cast<uint>(_pipeline->getHeight() * shadingScale),
        };
        framegraph::RenderTargetAttachment::Descriptor depthAttachmentInfo;
        depthAttachmentInfo.usage        = framegraph::RenderTargetAttachment::Usage::DEPTH_STENCIL;
        depthAttachmentInfo.loadOp       = gfx::LoadOp::CLEAR;
        depthAttachmentInfo.clearDepth   = camera->clearDepth;
        depthAttachmentInfo.clearStencil = camera->clearStencil;
        depthAttachmentInfo.endAccesses  = {gfx::AccessType::DEPTH_STENCIL_ATTACHMENT_WRITE};

        data.depth = builder.create(RenderPipeline::fgStrHandleOutDepthTexture, depthTexInfo);
        data.depth = builder.write(data.depth, depthAttachmentInfo);
        
        builder.writeToBlackboard(RenderPipeline::fgStrHandleOutColorTexture, data.outputTex);
        builder.writeToBlackboard(RenderPipeline::fgStrHandleOutDepthTexture, data.depth);
        builder.setViewport(_pipeline->getViewport(camera), _pipeline->getScissor(camera));

    };

    auto offset = _pipeline->getPipelineUBO()->getCurrentCameraUBOOffset();
    auto arExec = [this, camera, offset](const RenderData & /*data*/, const framegraph::DevicePassResourceTable &table) {
        auto *cmdBuff = _pipeline->getCommandBuffers()[0];

        auto *renderPass = table.getRenderPass();
        _arBackground->render(camera, renderPass, cmdBuff);
    };

    // add pass
    _pipeline->getFrameGraph().addPass<RenderData>(static_cast<uint>(CommonInsertPoint::DIP_AR_BACKGROUND), ForwardPipeline::fgStrHandleForwardPass, arSetup, arExec);
}

} // namespace pipeline
} // namespace cc
