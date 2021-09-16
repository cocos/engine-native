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
class CCWGPUQueue;
class CCWGPUPipelineState;
class CCWGPUDescriptorSet;
class CCWGPUInputAssembler;

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
    RenderPassInfo            info;
    String                    label;
    uint8_t                   sampleCount        = 1;
    WGPURenderPassDescriptor* wgpuRenderPassDesc = wgpuDefaultHandle;
};

struct CCWGPUTextureObject {
    WGPUTexture     wgpuTexture     = wgpuDefaultHandle;
    WGPUTextureView wgpuTextureView = wgpuDefaultHandle;
    WGPUTextureView selfView        = wgpuDefaultHandle;
};

//The indirect drawIndexed parameters encoded in the buffer must be a tightly packed block
//of five 32-bit unsigned integer values (20 bytes total), given in the same order as the arguments for drawIndexed().
// let drawIndexedIndirectParameters = new Uint32Array(5);
// drawIndexedIndirectParameters[0] = indexCount;
// drawIndexedIndirectParameters[1] = instanceCount;
// drawIndexedIndirectParameters[2] = firstIndex;
// drawIndexedIndirectParameters[3] = baseVertex;
// drawIndexedIndirectParameters[4] = 0; // firstInstance. Must be 0.
struct CCWGPUDrawIndexedIndirectObject {
    uint32_t indexCount    = 0;
    uint32_t instanceCount = 0;
    uint32_t firstIndex    = 0;
    uint32_t baseVertex    = 0;
    uint32_t firstInstance = 0;
};
static_assert(sizeof(CCWGPUDrawIndexedIndirectObject) == 20, "WGPU drawIndexedIndirect structure validation failed!");

//The indirect draw parameters encoded in the buffer must be a tightly packed block
//of four 32-bit unsigned integer values (16 bytes total), given in the same order as the arguments for draw().

// let drawIndirectParameters = new Uint32Array(4);
// drawIndirectParameters[0]  = vertexCount;
// drawIndirectParameters[1]  = instanceCount;
// drawIndirectParameters[2]  = firstVertex;
// drawIndirectParameters[3]  = 0; // firstInstance. Must be 0.
struct CCWGPUDrawIndirectObject {
    uint32_t vertexCount   = 0;
    uint32_t instanceCount = 0;
    uint32_t firstIndex    = 0;
    uint32_t firstInstance = 0;
};
static_assert(sizeof(CCWGPUDrawIndirectObject) == 16, "WGPU drawIndirect structure validation failed!");

struct CCWGPUBufferObject {
    WGPUBuffer                                   wgpuBuffer = wgpuDefaultHandle;
    std::vector<CCWGPUDrawIndexedIndirectObject> indexedIndirectObjs;
    std::vector<CCWGPUDrawIndirectObject>        indirectObjs;
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

struct CCWGPUPipelineLayoutObject {
    WGPUPipelineLayout wgpuPipelineLayout = wgpuDefaultHandle;
};

struct CCWGPUPipelineStateObject {
    WGPURenderPipeline  wgpuRenderPipeline  = wgpuDefaultHandle;
    WGPUComputePipeline wgpuComputePipeline = wgpuDefaultHandle;
};

struct CCWGPUShaderObject {
    WGPUShaderModule wgpuShaderVertexModule   = wgpuDefaultHandle;
    WGPUShaderModule wgpuShaderFragmentModule = wgpuDefaultHandle;
    WGPUShaderModule wgpuShaderComputeModule  = wgpuDefaultHandle;
};

struct CCWGPUInputAssemblerObject {
    WGPUVertexState wgpuVertexState;
};

struct CCWGPUQueueObject {
    WGPUQueue wgpuQueue = wgpuDefaultHandle;
    QueueType type      = QueueType::GRAPHICS;
};

struct CCWGPUDescriptorSetObject {
    uint32_t             index              = 0;
    CCWGPUDescriptorSet* descriptorSet      = nullptr;
    uint32_t             dynamicOffsetCount = 0;
    const uint32_t*      dynamicOffsets     = nullptr;
};

struct CCWGPUStencilMasks {
    uint writeMask   = 0;
    uint compareRef  = 0;
    uint compareMask = 0;
};

struct CCWGPUStateCache {
    CCWGPUPipelineState*  pipelineState  = nullptr;
    CCWGPUInputAssembler* inputAssembler = nullptr;

    float depthBiasConstant = 0.0f;
    float depthBiasClamp    = 0.0f;
    float depthBiasSlope    = 0.0f;
    float depthMinBound     = 0.0f;
    float depthMaxBound     = 100.0f;

    Color    blendConstants;
    Viewport viewport;
    Rect     rect;

    std::vector<CCWGPUDescriptorSetObject>    descriptorSets;
    std::map<StencilFace, CCWGPUStencilMasks> stencilMasks;
};

struct CCWGPUCommandBufferObject {
    bool renderPassBegan = false;

    WGPUCommandBuffer      wgpuCommandBuffer     = wgpuDefaultHandle;
    WGPUCommandEncoder     wgpuCommandEncoder    = wgpuDefaultHandle;
    WGPURenderPassEncoder  wgpuRenderPassEncoder = wgpuDefaultHandle;
    WGPUComputePassEncoder wgpuComputeEncoder    = wgpuDefaultHandle;
    CommandBufferType      type                  = CommandBufferType::PRIMARY;
    CCWGPUQueue*           queue                 = nullptr;

    WGPURenderPassDescriptor renderPassDescriptor;
    CCWGPUStateCache         stateCache;
};

} // namespace gfx

} // namespace cc
