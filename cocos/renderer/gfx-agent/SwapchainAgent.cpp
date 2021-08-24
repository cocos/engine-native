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

#include "base/CoreStd.h"
#include "base/threading/MessageQueue.h"

#include "DeviceAgent.h"
#include "SwapchainAgent.h"
#include "gfx-agent/TextureAgent.h"

namespace cc {
namespace gfx {

SwapchainAgent::SwapchainAgent(Swapchain *actor)
: Agent<Swapchain>(actor) {
    _typedID = generateObjectID<decltype(this)>();
}

SwapchainAgent::~SwapchainAgent() {
    ENQUEUE_MESSAGE_1(
        DeviceAgent::getInstance()->getMessageQueue(), SwapchainDestruct,
        actor, _actor,
        {
            CC_SAFE_DELETE(actor);
        });
}

void SwapchainAgent::doInit(const SwapchainInfo &info) {
    ENQUEUE_MESSAGE_2(
        DeviceAgent::getInstance()->getMessageQueue(), SwapchainInit,
        actor, getActor(),
        info, info,
        {
            actor->initialize(info);
        });

    DeviceAgent::getInstance()->getMessageQueue()->kickAndWait();

    auto *colorTexture = CC_NEW(TextureAgent(_actor->getColorTexture()));
    colorTexture->renounceOwnership();
    _colorTexture = colorTexture;

    auto *depthStencilTexture = CC_NEW(TextureAgent(_actor->getDepthStencilTexture()));
    depthStencilTexture->renounceOwnership();
    _depthStencilTexture = depthStencilTexture;
}

void SwapchainAgent::doDestroy() {
    CC_SAFE_DELETE(_depthStencilTexture);
    CC_SAFE_DELETE(_colorTexture);

    ENQUEUE_MESSAGE_1(
        DeviceAgent::getInstance()->getMessageQueue(), SwapchainDestroy,
        actor, getActor(),
        {
            actor->destroy();
        });
}

void SwapchainAgent::acquire() {
    ENQUEUE_MESSAGE_1(
        DeviceAgent::getInstance()->getMessageQueue(), SwapchainAcquire,
        actor, _actor,
        {
            actor->acquire();
        });
}

void SwapchainAgent::present() {
    ENQUEUE_MESSAGE_1(
        DeviceAgent::getInstance()->getMessageQueue(), SwapchainPresent,
        actor, _actor,
        {
            actor->present();
        });

    DeviceAgent::getInstance()->frameBoundary();
}

void SwapchainAgent::resize(uint32_t width, uint32_t height) {
    ENQUEUE_MESSAGE_3(
        DeviceAgent::getInstance()->getMessageQueue(), SwapchainResize,
        actor, getActor(),
        width, width,
        height, height,
        {
            actor->resize(width, height);
        });
}

void SwapchainAgent::destroySurface() {
    ENQUEUE_MESSAGE_1(
        DeviceAgent::getInstance()->getMessageQueue(), SwapchaindestroySurface,
        actor, getActor(),
        {
            actor->destroySurface();
        });
}

void SwapchainAgent::doCreateSurface(void *windowHandle) {
    ENQUEUE_MESSAGE_2(
        DeviceAgent::getInstance()->getMessageQueue(), SwapchaincreateSurface,
        actor, getActor(),
        windowHandle, windowHandle,
        {
            actor->createSurface(windowHandle);
        });
}

} // namespace gfx
} // namespace cc
