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

namespace anoymous {
CCWGPUTexture *defaultTexture = nullptr;
}

using namespace emscripten;

CCWGPUTexture::CCWGPUTexture() : wrapper<Texture>(val::object()) {
    _gpuTextureObj = CC_NEW(CCWGPUTextureObject);
}

void CCWGPUTexture::doInit(const TextureInfo &info) {
    WGPUTextureDescriptor descriptor = {
        .nextInChain   = nullptr,
        .label         = nullptr,
        .usage         = toWGPUTextureUsage(info.usage),
        .dimension     = toWGPUTextureDimension(info.type),
        .size          = {info.width, info.height, info.depth},
        .format        = toWGPUTextureFormat(info.format),
        .mipLevelCount = info.levelCount,
        .sampleCount   = toWGPUSampleCount(info.samples),
    };

    _gpuTextureObj->wgpuTexture = wgpuDeviceCreateTexture(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &descriptor);

    WGPUTextureViewDescriptor texViewDesc = {
        .nextInChain     = nullptr,
        .label           = nullptr,
        .format          = descriptor.format,
        .dimension       = toWGPUTextureViewDimension(info.type),
        .baseMipLevel    = 0,
        .mipLevelCount   = 0,
        .baseArrayLayer  = 0,
        .arrayLayerCount = 0,
        .aspect          = WGPUTextureAspect_All,
    };
    _gpuTextureObj->selfView = wgpuTextureCreateView(_gpuTextureObj->wgpuTexture, &texViewDesc);
} // namespace gfx

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

    auto *      ccTexture           = static_cast<CCWGPUTexture *>(info.texture);
    WGPUTexture wgpuTexture         = ccTexture->gpuTextureObject()->wgpuTexture;
    _gpuTextureObj->wgpuTextureView = wgpuTextureCreateView(wgpuTexture, &descriptor);
    _gpuTextureObj->selfView        = ccTexture->gpuTextureObject()->selfView;
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
        CC_DELETE(_gpuTextureObj);
    }
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

CCWGPUTexture *CCWGPUTexture::defaultTexture() {
    if (!anoymous::defaultTexture) {
        TextureInfo info = {
            .type        = TextureType::TEX2D,
            .usage       = TextureUsageBit::NONE,
            .format      = Format::BGRA8,
            .width       = 2,
            .height      = 2,
            .flags       = TextureFlagBit::NONE,
            .layerCount  = 1,
            .levelCount  = 1,
            .samples     = SampleCount::ONE,
            .depth       = 1,
            .externalRes = nullptr,
        };
        anoymous::defaultTexture = CC_NEW(CCWGPUTexture);
        anoymous::defaultTexture->initialize(info);
    }

    return anoymous::defaultTexture;
}

CCWGPUSwapchain *CCWGPUTexture::swapchain() {
    return static_cast<CCWGPUSwapchain *>(_swapchain);
}

} // namespace gfx
} // namespace cc
