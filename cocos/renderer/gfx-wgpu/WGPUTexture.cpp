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

#include "WGPUTexture.h"
#include <webgpu/webgpu.h>
#include "WGPUDevice.h"
#include "WGPUObject.h"
#include "WGPUSwapchain.h"
#include "WGPUUtils.h"

namespace cc {
namespace gfx {

using namespace emscripten;

CCWGPUTexture::CCWGPUTexture() : wrapper<Texture>(val::object()) {
    _gpuTextureObj = CC_NEW(CCWGPUTextureObject);
}

void CCWGPUTexture::doInit(const TextureInfo &info) {
    WGPUTextureDescriptor descriptor;
    descriptor.usage         = toWGPUTextureUsage(info.usage);
    descriptor.dimension     = toWGPUTextureDimension(info.type);
    descriptor.size          = {info.width, info.height, info.depth};
    descriptor.format        = toWGPUTextureFormat(info.format);
    descriptor.mipLevelCount = info.levelCount;
    descriptor.sampleCount   = toWGPUSampleCount(info.samples);

    _gpuTextureObj->wgpuTexture = wgpuDeviceCreateTexture(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &descriptor);
}

void CCWGPUTexture::doInit(const TextureViewInfo &info) {
    WGPUTextureViewDescriptor descriptor = {
        .nextInChain     = nullptr,
        .label           = nullptr,
        .format          = toWGPUTextureFormat(info.format),
        .dimension       = toWGPUTextureViewDimension(info.type),
        .baseMipLevel    = info.baseLevel,
        .mipLevelCount   = info.levelCount,
        .baseArrayLayer  = info.baseLayer,
        .arrayLayerCount = info.layerCount,
        .aspect          = textureAspectTrait(info.format),
    };

    auto *      ccTexture   = static_cast<CCWGPUTexture *>(info.texture);
    WGPUTexture wgpuTexture = ccTexture->gpuTextureObject()->wgpuTexture;

    _gpuTextureObj->wgpuTextureView = wgpuTextureCreateView(wgpuTexture, &descriptor);
}

void CCWGPUTexture::doInit(const SwapchainTextureInfo &info) {
    if (_swapchain) {
        auto *swapchain                 = static_cast<CCWGPUSwapchain *>(_swapchain);
        _gpuTextureObj->wgpuTextureView = wgpuSwapChainGetCurrentTextureView(swapchain->gpuSwapchainObject()->wgpuSwapChain);
    }
}

void CCWGPUTexture::doDestroy() {
    if (_gpuTextureObj) {
        if (_gpuTextureObj->wgpuTexture) {
            wgpuTextureDestroy(_gpuTextureObj->wgpuTexture);
        }
    }

    CC_SAFE_DELETE(_gpuTextureObj);
}

void CCWGPUTexture::doResize(uint32_t width, uint32_t height, uint32_t size) {
    if (_isTextureView) {
        CC_LOG_ERROR("Resize is not support on texture view!");
        return;
    }
    if (_gpuTextureObj->wgpuTexture) {
        wgpuTextureDestroy(_gpuTextureObj->wgpuTexture);
    }

    WGPUTextureDescriptor descriptor;
    descriptor.usage         = toWGPUTextureUsage(_info.usage);
    descriptor.dimension     = toWGPUTextureDimension(_info.type);
    descriptor.size          = {_info.width, _info.height, _info.depth};
    descriptor.format        = toWGPUTextureFormat(_info.format);
    descriptor.mipLevelCount = _info.levelCount;
    descriptor.sampleCount   = toWGPUSampleCount(_info.samples);

    _gpuTextureObj->wgpuTexture = wgpuDeviceCreateTexture(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &descriptor);
}

} // namespace gfx
} // namespace cc
