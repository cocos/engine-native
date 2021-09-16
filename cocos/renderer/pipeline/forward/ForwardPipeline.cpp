/****************************************************************************
 Copyright (c) 2020-2021 Xiamen Yaji Software Co., Ltd.

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

#include "ForwardPipeline.h"
#include "../SceneCulling.h"
#include "../shadow/ShadowFlow.h"
#include "ForwardFlow.h"
#include "gfx-base/GFXDevice.h"
#include "platform/Application.h"
#include "scene/RenderScene.h"

namespace cc {
namespace pipeline {
namespace {
#define TO_VEC3(dst, src, offset)  \
    (dst)[(offset) + 0] = (src).x; \
    (dst)[(offset) + 1] = (src).y; \
    (dst)[(offset) + 2] = (src).z;
#define TO_VEC4(dst, src, offset)  \
    (dst)[(offset) + 0] = (src).x; \
    (dst)[(offset) + 1] = (src).y; \
    (dst)[(offset) + 2] = (src).z; \
    (dst)[(offset) + 3] = (src).w;
} // namespace

framegraph::StringHandle ForwardPipeline::fgStrHandleForwardColorTexture = framegraph::FrameGraph::stringToHandle("forwardColorTexture");
framegraph::StringHandle ForwardPipeline::fgStrHandleForwardDepthTexture = framegraph::FrameGraph::stringToHandle("forwardDepthTexture");
framegraph::StringHandle ForwardPipeline::fgStrHandleForwardPass         = framegraph::FrameGraph::stringToHandle("forwardPass");

gfx::RenderPass *ForwardPipeline::getOrCreateRenderPass(gfx::ClearFlags clearFlags, gfx::Swapchain *swapchain) {
    if (_renderPasses.count(clearFlags)) {
        return _renderPasses[clearFlags];
    }

    auto *                      device = gfx::Device::getInstance();
    gfx::ColorAttachment        colorAttachment;
    gfx::DepthStencilAttachment depthStencilAttachment;
    colorAttachment.format                = swapchain->getColorTexture()->getFormat();
    depthStencilAttachment.format         = swapchain->getDepthStencilTexture()->getFormat();
    depthStencilAttachment.stencilStoreOp = gfx::StoreOp::STORE;
    depthStencilAttachment.depthStoreOp   = gfx::StoreOp::STORE;

    if (!hasFlag(clearFlags, gfx::ClearFlagBit::COLOR)) {
        if (hasFlag(clearFlags, static_cast<gfx::ClearFlagBit>(skyboxFlag))) {
            colorAttachment.loadOp = gfx::LoadOp::DISCARD;
        } else {
            colorAttachment.loadOp        = gfx::LoadOp::LOAD;
            colorAttachment.beginAccesses = {gfx::AccessType::COLOR_ATTACHMENT_WRITE};
        }
    }

    if (static_cast<gfx::ClearFlagBit>(clearFlags & gfx::ClearFlagBit::DEPTH_STENCIL) != gfx::ClearFlagBit::DEPTH_STENCIL) {
        if (!hasFlag(clearFlags, gfx::ClearFlagBit::DEPTH)) depthStencilAttachment.depthLoadOp = gfx::LoadOp::LOAD;
        if (!hasFlag(clearFlags, gfx::ClearFlagBit::STENCIL)) depthStencilAttachment.stencilLoadOp = gfx::LoadOp::LOAD;
        depthStencilAttachment.beginAccesses = {gfx::AccessType::DEPTH_STENCIL_ATTACHMENT_WRITE};
    }

    auto *renderPass          = device->createRenderPass({
        {colorAttachment},
        depthStencilAttachment,
        {},

    });
    _renderPasses[clearFlags] = renderPass;

    return renderPass;
}

bool ForwardPipeline::initialize(const RenderPipelineInfo &info) {
    RenderPipeline::initialize(info);

    if (_flows.empty()) {
        auto *shadowFlow = CC_NEW(ShadowFlow);
        shadowFlow->initialize(ShadowFlow::getInitializeInfo());
        _flows.emplace_back(shadowFlow);

        auto *forwardFlow = CC_NEW(ForwardFlow);
        forwardFlow->initialize(ForwardFlow::getInitializeInfo());
        _flows.emplace_back(forwardFlow);
    }

    return true;
}

bool ForwardPipeline::activate(gfx::Swapchain *swapchain) {
    if (!RenderPipeline::activate(swapchain)) {
        CC_LOG_ERROR("RenderPipeline active failed.");
        return false;
    }

    if (!activeRenderer()) {
        CC_LOG_ERROR("ForwardPipeline startup failed!");
        return false;
    }

    return true;
}

gfx::Rect ForwardPipeline::getRenderArea(scene::Camera *camera, bool onScreen) {
    gfx::Rect renderArea;

    float w;
    float h;
    if (onScreen) {
        gfx::Swapchain *swapchain = camera->window->swapchain;
        w                         = static_cast<float>(swapchain && toNumber(swapchain->getSurfaceTransform()) % 2 ? camera->height : camera->width);
        h                         = static_cast<float>(swapchain && toNumber(swapchain->getSurfaceTransform()) % 2 ? camera->width : camera->height);
    } else {
        w = static_cast<float>(camera->width);
        h = static_cast<float>(camera->height);
    }

    const auto &viewport = camera->viewPort;
    renderArea.x         = static_cast<int>(viewport.x * w);
    renderArea.y         = static_cast<int>(viewport.y * h);
    renderArea.width     = static_cast<uint>(viewport.z * w * _pipelineSceneData->getSharedData()->shadingScale);
    renderArea.height    = static_cast<uint>(viewport.w * h * _pipelineSceneData->getSharedData()->shadingScale);
    return renderArea;
}

void ForwardPipeline::render(const vector<scene::Camera *> &cameras) {
    _commandBuffers[0]->begin();
    _pipelineUBO->updateGlobalUBO(cameras[0]);
    _pipelineUBO->updateMultiCameraUBO(cameras);

    for (auto *camera : cameras) {
        sceneCulling(this, camera);
        _fg.reset();
        for (auto *const flow : _flows) {
            flow->render(camera);
        }
        _fg.compile();
        _fg.execute();
        _pipelineUBO->incCameraUBOOffset();
    }

    _commandBuffers[0]->end();
    _device->flushCommands(_commandBuffers);
    _device->getQueue()->submit(_commandBuffers);
}

bool ForwardPipeline::activeRenderer() {
    _commandBuffers.push_back(_device->getCommandBuffer());
    auto *const sharedData = _pipelineSceneData->getSharedData();

    gfx::Sampler *const shadowMapSampler = _device->getSampler({
        gfx::Filter::POINT,
        gfx::Filter::POINT,
        gfx::Filter::NONE,
        gfx::Address::CLAMP,
        gfx::Address::CLAMP,
        gfx::Address::CLAMP,
    });

    // Main light sampler binding
    _descriptorSet->bindSampler(SHADOWMAP::BINDING, shadowMapSampler);
    _descriptorSet->bindTexture(SHADOWMAP::BINDING, getDefaultTexture());

    // Spot light sampler binding
    _descriptorSet->bindSampler(SPOTLIGHTINGMAP::BINDING, shadowMapSampler);
    _descriptorSet->bindTexture(SPOTLIGHTINGMAP::BINDING, getDefaultTexture());

    _descriptorSet->update();
    // update global defines when all states initialized.
    _macros.setValue("CC_USE_HDR", static_cast<bool>(sharedData->isHDR));
    _macros.setValue("CC_SUPPORT_FLOAT_TEXTURE", _device->hasFeature(gfx::Feature::TEXTURE_FLOAT));

    return true;
}

void ForwardPipeline::destroy() {
    for (auto &it : _renderPasses) {
        CC_SAFE_DESTROY(it.second);
    }
    _renderPasses.clear();

    _commandBuffers.clear();

    RenderPipeline::destroy();
}

} // namespace pipeline
} // namespace cc
