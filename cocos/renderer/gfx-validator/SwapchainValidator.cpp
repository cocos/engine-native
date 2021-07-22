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

#include "SwapchainValidator.h"
#include "ValidationUtils.h"
#include "gfx-base/GFXDef.h"
#include "gfx-validator/DeviceValidator.h"
#include "gfx-validator/TextureValidator.h"

namespace cc {
namespace gfx {

SwapchainValidator::SwapchainValidator(Swapchain *actor)
: Agent<Swapchain>(actor) {
    _typedID = generateObjectID<decltype(this)>();
}

SwapchainValidator::~SwapchainValidator() {
    CC_SAFE_DELETE(_depthStencilTexture);
    CC_SAFE_DELETE(_colorTexture);

    DeviceResourceTracker<Swapchain>::erase(this);
    CC_SAFE_DELETE(_actor);
}

void SwapchainValidator::doInit(const SwapchainInfo &info) {
    _actor->initialize(info);

    auto *colorTexture = CC_NEW(TextureValidator(_actor->getColorTexture()));
    colorTexture->renounceOwnership();
    _colorTexture = colorTexture;
    DeviceResourceTracker<Texture>::push(_colorTexture);

    auto *depthStencilTexture = CC_NEW(TextureValidator(_actor->getDepthStencilTexture()));
    depthStencilTexture->renounceOwnership();
    _depthStencilTexture = depthStencilTexture;
    DeviceResourceTracker<Texture>::push(_depthStencilTexture);

    SwapchainTextureInfo textureInfo;
    textureInfo.swapchain = this;
    textureInfo.format    = _actor->getColorTexture()->getFormat();
    textureInfo.width     = info.width;
    textureInfo.height    = info.height;
    textureInfo.samples   = info.samples;
    initTexture(textureInfo, _colorTexture);

    textureInfo.format = _actor->getDepthStencilTexture()->getFormat();
    initTexture(textureInfo, _depthStencilTexture);
}

void SwapchainValidator::doDestroy() {
    CC_SAFE_DELETE(_depthStencilTexture);
    CC_SAFE_DELETE(_colorTexture);

    _actor->destroy();
}

void SwapchainValidator::doResize(uint32_t width, uint32_t height) {
    _actor->resize(width, height);
}

void SwapchainValidator::doDestroySurface() {
    _actor->destroySurface();
}

void SwapchainValidator::doCreateSurface(void *windowHandle) {
    _actor->createSurface(windowHandle);
}

} // namespace gfx
} // namespace cc
