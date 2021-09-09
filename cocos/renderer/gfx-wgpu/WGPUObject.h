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

#pragma once
#include <emscripten/html5_webgpu.h>
#include <utility>
#include "WGPUDef.h"
#include "base/Utils.h"
#include "gfx-base/GFXDef.h"
class WGPURenderPassDescriptor;
class WGPUComputePassDescriptor;

namespace cc {

namespace gfx {

constexpr uint8_t CC_WGPU_MAX_ATTACHMENTS = 16;

constexpr decltype(nullptr) wgpuDefaultHandle = nullptr;

class CCWGPUTexture;
class CCWGPUBuffer;
class CCWGPUSampler;

struct CCWGPUResource {
    CCWGPUTexture* texture = nullptr;
    CCWGPUBuffer*  buffer  = nullptr;
    CCWGPUSampler* sampler = nullptr;
};

struct CCWGPUDeviceObject {
    WGPUDevice wgpuDevice = wgpuDefaultHandle;
    WGPUQueue  wgpuQueue  = wgpuDefaultHandle;

    CCWGPUResource defaultResources;
};

struct CCWGPUSwapchainObject {
    WGPUSwapChain wgpuSwapChain = wgpuDefaultHandle;
    WGPUSurface   wgpuSurface   = wgpuDefaultHandle;
    WGPUInstance  wgpuInstance  = wgpuDefaultHandle;

    CCWGPUTexture* swapchainColor        = nullptr;
    CCWGPUTexture* swapchainDepthStencil = nullptr;
};

struct CCWGPURenderPassObject {
    RenderPassInfo info;
    String         label;

    WGPURenderPassDescriptor* wgpuRenderPassDesc = wgpuDefaultHandle;
};

struct CCWGPUTextureObject {
    WGPUTexture     wgpuTexture     = wgpuDefaultHandle;
    WGPUTextureView wgpuTextureView = wgpuDefaultHandle;
    WGPUTextureView selfView        = wgpuDefaultHandle;
};

struct CCWGPUBufferObject {
    WGPUBuffer wgpuBuffer = wgpuDefaultHandle;
};

struct CCWGPUSamplerObject {
    WGPUSampler wgpuSampler = wgpuDefaultHandle;

    WGPUAddressMode     addressModeU  = WGPUAddressMode_Repeat;
    WGPUAddressMode     addressModeV  = WGPUAddressMode_Repeat;
    WGPUAddressMode     addressModeW  = WGPUAddressMode_Repeat;
    WGPUFilterMode      magFilter     = WGPUFilterMode_Linear;
    WGPUFilterMode      minFilter     = WGPUFilterMode_Linear;
    WGPUFilterMode      mipmapFilter  = WGPUFilterMode_Linear;
    float               lodMinClamp   = 0.1f;
    float               lodMaxClamp   = 1000.0f;
    WGPUCompareFunction compare       = WGPUCompareFunction_Always;
    uint16_t            maxAnisotropy = 0;
};

struct CCWGPUBindGroupLayoutObject {
    WGPUBindGroupLayout                   bindGroupLayout = wgpuDefaultHandle;
    std::vector<WGPUBindGroupLayoutEntry> bindGroupLayoutEntries;
};

struct CCWGPUBindGroupObject {
    WGPUBindGroup                   bindgroup = wgpuDefaultHandle;
    std::vector<WGPUBindGroupEntry> bindGroupEntries;
};

} // namespace gfx

} // namespace cc
