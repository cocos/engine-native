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

#include "WGPUCommandBuffer.h"
#include <webgpu/webgpu.h>
#include "WGPUBuffer.h"
#include "WGPUDescriptorSet.h"
#include "WGPUDevice.h"
#include "WGPUFrameBuffer.h"
#include "WGPUInputAssembler.h"
#include "WGPUObject.h"
#include "WGPUPipelineLayout.h"
#include "WGPUPipelineState.h"
#include "WGPUQueue.h"
#include "WGPUSwapchain.h"
#include "WGPUTexture.h"
#include "WGPUUtils.h"

namespace cc {
namespace gfx {

CCWGPUCommandBuffer::CCWGPUCommandBuffer() : wrapper<CommandBuffer>(val::object()) {
}

void CCWGPUCommandBuffer::doInit(const CommandBufferInfo &info) {
    _gpuCommandBufferObj        = CC_NEW(CCWGPUCommandBufferObject);
    _gpuCommandBufferObj->type  = info.type;
    _gpuCommandBufferObj->queue = static_cast<CCWGPUQueue *>(info.queue);
}

void CCWGPUCommandBuffer::doDestroy() {
    CC_SAFE_DELETE(_gpuCommandBufferObj);
}

void CCWGPUCommandBuffer::begin(RenderPass *renderPass, uint subpass, Framebuffer *frameBuffer) {
    //TODO_Zeqiang: subpass support
    _gpuCommandBufferObj->wgpuCommandEncoder = wgpuDeviceCreateCommandEncoder(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, nullptr);
}

void CCWGPUCommandBuffer::end() {
    auto *pipelineState = _gpuCommandBufferObj->stateCache.pipelineState;
    if (pipelineState->getBindPoint() == PipelineBindPoint::GRAPHICS) {
        auto *queue                             = _gpuCommandBufferObj->queue;
        _gpuCommandBufferObj->wgpuCommandBuffer = wgpuCommandEncoderFinish(_gpuCommandBufferObj->wgpuCommandEncoder, nullptr);
        wgpuQueueSubmit(queue->gpuQueueObject()->wgpuQueue, 1, &_gpuCommandBufferObj->wgpuCommandBuffer);
        wgpuCommandEncoderRelease(_gpuCommandBufferObj->wgpuCommandEncoder);
        _gpuCommandBufferObj->wgpuCommandEncoder = wgpuDefaultHandle;
    } else {
        wgpuComputePassEncoderEndPass(_gpuCommandBufferObj->wgpuComputeEncoder);
        wgpuComputePassEncoderRelease(_gpuCommandBufferObj->wgpuComputeEncoder);
        _gpuCommandBufferObj->wgpuCommandBuffer = wgpuCommandEncoderFinish(_gpuCommandBufferObj->wgpuCommandEncoder, nullptr);
        wgpuQueueSubmit(static_cast<CCWGPUQueue *>(_queue)->gpuQueueObject()->wgpuQueue, 1, &_gpuCommandBufferObj->wgpuCommandBuffer);
        wgpuCommandEncoderRelease(_gpuCommandBufferObj->wgpuCommandEncoder);
        _gpuCommandBufferObj->wgpuComputeEncoder = wgpuDefaultHandle;
        _gpuCommandBufferObj->wgpuCommandEncoder = wgpuDefaultHandle;
    }
}

void CCWGPUCommandBuffer::beginRenderPass(RenderPass *renderPass, Framebuffer *fbo, const Rect &renderArea, const Color *colors, float depth, uint stencil, CommandBuffer *const *secondaryCBs, uint secondaryCBCount) {
    CCWGPUFramebuffer *ccFrameBuffer = static_cast<CCWGPUFramebuffer *>(fbo);

    const ColorAttachmentList &   colorConfigs       = renderPass->getColorAttachments();
    const DepthStencilAttachment &depthStencilConfig = renderPass->getDepthStencilAttachment();
    const TextureList &           textures           = ccFrameBuffer->getColorTextures();
    Texture *                     dsTexture          = ccFrameBuffer->getDepthStencilTexture();
    CCWGPUSwapchain *             swapchain          = ccFrameBuffer->swapchain();

    WGPURenderPassDescriptor &                 renderPassDesc = _gpuCommandBufferObj->renderPassDescriptor;
    std::vector<WGPURenderPassColorAttachment> colorAttachments;
    if (colorConfigs.empty()) {
        renderPassDesc.nextInChain          = nullptr;
        renderPassDesc.label                = "swapchain";
        WGPURenderPassColorAttachment color = {
            .view          = swapchain->gpuSwapchainObject()->swapchainColor->gpuTextureObject()->selfView,
            .resolveTarget = nullptr, //TODO_Zeqiang: wgpu offscr msaa
            .loadOp        = toWGPULoadOp(colorConfigs[0].loadOp),
            .storeOp       = toWGPUStoreOp(colorConfigs[0].storeOp),
            .clearColor    = WGPUColor{0.2, 0.2, 0.2, 1.0},
        };
        colorAttachments.emplace_back(color);
    } else {
        renderPassDesc.nextInChain = nullptr;
        renderPassDesc.label       = "attachments";

        for (size_t i = 0; i < colorConfigs.size(); i++) {
            WGPURenderPassColorAttachment *colorAttchments = new WGPURenderPassColorAttachment[colorConfigs.size()];
            WGPURenderPassColorAttachment  color           = {
                .view          = static_cast<CCWGPUTexture *>(textures[i])->gpuTextureObject()->selfView,
                .resolveTarget = nullptr, //TODO_Zeqiang: wgpu offscr msaa
                .loadOp        = toWGPULoadOp(colorConfigs[i].loadOp),
                .storeOp       = toWGPUStoreOp(colorConfigs[i].storeOp),
                .clearColor    = toWGPUColor(colors[i]),
            };
            colorAttachments.emplace_back(color);
        }
    }

    std::vector<WGPURenderPassDepthStencilAttachment> depthStencils;
    if (dsTexture) {
        WGPURenderPassDepthStencilAttachment depthStencil = {
            .view            = static_cast<CCWGPUTexture *>(dsTexture)->gpuTextureObject()->selfView,
            .depthLoadOp     = toWGPULoadOp(depthStencilConfig.depthLoadOp),
            .depthStoreOp    = toWGPUStoreOp(depthStencilConfig.depthStoreOp),
            .clearDepth      = depth,
            .depthReadOnly   = false,
            .stencilLoadOp   = toWGPULoadOp(depthStencilConfig.stencilLoadOp),
            .stencilStoreOp  = toWGPUStoreOp(depthStencilConfig.stencilStoreOp),
            .clearStencil    = stencil,
            .stencilReadOnly = false,
        };
        depthStencils.emplace_back(depthStencil);
    } else {
        if (depthStencilConfig.format == Format::UNKNOWN) {
            renderPassDesc.depthStencilAttachment = nullptr;
        } else {
            WGPURenderPassDepthStencilAttachment depthStencil = {
                .view            = swapchain->gpuSwapchainObject()->swapchainDepthStencil->gpuTextureObject()->selfView,
                .depthLoadOp     = toWGPULoadOp(depthStencilConfig.depthLoadOp),
                .depthStoreOp    = toWGPUStoreOp(depthStencilConfig.depthStoreOp),
                .clearDepth      = depth,
                .depthReadOnly   = false,
                .stencilLoadOp   = toWGPULoadOp(depthStencilConfig.stencilLoadOp),
                .stencilStoreOp  = toWGPUStoreOp(depthStencilConfig.stencilStoreOp),
                .clearStencil    = stencil,
                .stencilReadOnly = false,
            };
            depthStencils.emplace_back(depthStencil);
        }
    }

    _gpuCommandBufferObj->renderPassBegan = true;

    _gpuCommandBufferObj->stateCache.viewport.left     = renderArea.x;
    _gpuCommandBufferObj->stateCache.viewport.top      = renderArea.y;
    _gpuCommandBufferObj->stateCache.viewport.width    = renderArea.width;
    _gpuCommandBufferObj->stateCache.viewport.height   = renderArea.height;
    _gpuCommandBufferObj->stateCache.viewport.minDepth = 0.0f;
    _gpuCommandBufferObj->stateCache.viewport.maxDepth = 1.0f;
    _gpuCommandBufferObj->stateCache.rect              = renderArea;

    renderPassDesc.colorAttachments             = colorAttachments.data();
    renderPassDesc.colorAttachmentCount         = colorAttachments.size();
    renderPassDesc.depthStencilAttachment       = depthStencils.empty() ? nullptr : depthStencils.data();
    _gpuCommandBufferObj->wgpuRenderPassEncoder = wgpuCommandEncoderBeginRenderPass(_gpuCommandBufferObj->wgpuCommandEncoder, &renderPassDesc);
}

void CCWGPUCommandBuffer::endRenderPass() {
    wgpuRenderPassEncoderEndPass(_gpuCommandBufferObj->wgpuRenderPassEncoder);
    wgpuRenderPassEncoderRelease(_gpuCommandBufferObj->wgpuRenderPassEncoder);
    _gpuCommandBufferObj->wgpuRenderPassEncoder = wgpuDefaultHandle;

    _gpuCommandBufferObj->renderPassBegan = false;
}

void CCWGPUCommandBuffer::bindPipelineState(PipelineState *pso) {
    _gpuCommandBufferObj->stateCache.pipelineState = static_cast<CCWGPUPipelineState *>(pso);
}

void CCWGPUCommandBuffer::bindDescriptorSet(uint set, DescriptorSet *descriptorSet, uint dynamicOffsetCount, const uint *dynamicOffsets) {
    auto &descriptorSets = _gpuCommandBufferObj->stateCache.descriptorSets;
    auto  iter           = std::find_if(descriptorSets.begin(), descriptorSets.end(), [set](const CCWGPUDescriptorSetObject &descriptorSet) {
        return descriptorSet.index == set;
    });

    CCWGPUDescriptorSetObject dsObj = {
        .index              = set,
        .descriptorSet      = static_cast<CCWGPUDescriptorSet *>(descriptorSet),
        .dynamicOffsetCount = dynamicOffsetCount,
        .dynamicOffsets     = dynamicOffsets,
    };

    if (iter != descriptorSets.end()) {
        (*iter) = dsObj;
    } else {
        descriptorSets.push_back(dsObj);
    }
}

void CCWGPUCommandBuffer::bindInputAssembler(InputAssembler *ia) {
    _gpuCommandBufferObj->stateCache.inputAssembler = static_cast<CCWGPUInputAssembler *>(ia);
}

void CCWGPUCommandBuffer::setViewport(const Viewport &vp) {
    _gpuCommandBufferObj->stateCache.viewport = vp;
}

void CCWGPUCommandBuffer::setScissor(const Rect &rect) {
    _gpuCommandBufferObj->stateCache.rect = rect;
}

void CCWGPUCommandBuffer::setLineWidth(float width) {
    CC_LOG_WARNING("linewith not support in webGPU, ignored.");
}

void CCWGPUCommandBuffer::setDepthBias(float constant, float clamp, float slope) {
    _gpuCommandBufferObj->stateCache.depthBiasConstant = constant;
    _gpuCommandBufferObj->stateCache.depthBiasClamp    = clamp;
    _gpuCommandBufferObj->stateCache.depthBiasSlope    = slope;
}

void CCWGPUCommandBuffer::setBlendConstants(const Color &constants) {
    _gpuCommandBufferObj->stateCache.blendConstants = constants;
}

void CCWGPUCommandBuffer::setDepthBound(float minBounds, float maxBounds) {
    _gpuCommandBufferObj->stateCache.depthMinBound = minBounds;
    _gpuCommandBufferObj->stateCache.depthMaxBound = maxBounds;
}

void CCWGPUCommandBuffer::setStencilWriteMask(StencilFace face, uint mask) {
    _gpuCommandBufferObj->stateCache.stencilMasks[face].writeMask = mask;
}

void CCWGPUCommandBuffer::setStencilCompareMask(StencilFace face, uint ref, uint mask) {
    _gpuCommandBufferObj->stateCache.stencilMasks[face].compareRef  = ref;
    _gpuCommandBufferObj->stateCache.stencilMasks[face].compareMask = mask;
}

void CCWGPUCommandBuffer::bindStates() {
    auto *pipelineState = _gpuCommandBufferObj->stateCache.pipelineState;
    if (!pipelineState) {
        return;
    }

    if (pipelineState->getBindPoint() == PipelineBindPoint::GRAPHICS) {
        auto *pipelineState = _gpuCommandBufferObj->stateCache.pipelineState;
        //pipeline state
        wgpuRenderPassEncoderSetPipeline(_gpuCommandBufferObj->wgpuRenderPassEncoder,
                                         pipelineState->gpuPipelineStateObject()->wgpuRenderPipeline);
        //bindgroup & descriptorset
        const auto &descriptorSets = _gpuCommandBufferObj->stateCache.descriptorSets;
        for (size_t i = 0; i < descriptorSets.size(); i++) {
            if (descriptorSets[i].descriptorSet->gpuBindGroupObject()->bindgroup) {
                wgpuRenderPassEncoderSetBindGroup(_gpuCommandBufferObj->wgpuRenderPassEncoder,
                                                  descriptorSets[i].index,
                                                  descriptorSets[i].descriptorSet->gpuBindGroupObject()->bindgroup,
                                                  descriptorSets[i].dynamicOffsetCount,
                                                  descriptorSets[i].dynamicOffsets);
            }
        }

        //input assembler
        const auto *ia               = _gpuCommandBufferObj->stateCache.inputAssembler;
        const auto &vertexBufferList = ia->getVertexBuffers();
        for (size_t i = 0; i < vertexBufferList.size(); i++) {
            const auto *vertexBuffer = static_cast<CCWGPUBuffer *>(vertexBufferList[i]);
            wgpuRenderPassEncoderSetVertexBuffer(_gpuCommandBufferObj->wgpuRenderPassEncoder,
                                                 i,
                                                 vertexBuffer->gpuBufferObject()->wgpuBuffer,
                                                 vertexBuffer->getOffset(),
                                                 vertexBuffer->getSize());
        }

        const auto *indexBuffer = static_cast<CCWGPUBuffer *>(ia->getIndexBuffer());
        wgpuRenderPassEncoderSetIndexBufferWithFormat(_gpuCommandBufferObj->wgpuRenderPassEncoder,
                                                      indexBuffer->gpuBufferObject()->wgpuBuffer,
                                                      indexBuffer->getStride() == 2 ? WGPUIndexFormat::WGPUIndexFormat_Uint16 : WGPUIndexFormat_Uint32,
                                                      indexBuffer->getOffset(),
                                                      indexBuffer->getSize());

        WGPUColor blendColor = toWGPUColor(_gpuCommandBufferObj->stateCache.blendConstants);
        wgpuRenderPassEncoderSetBlendConstant(_gpuCommandBufferObj->wgpuRenderPassEncoder, &blendColor);

        const Viewport &vp = _gpuCommandBufferObj->stateCache.viewport;
        wgpuRenderPassEncoderSetViewport(_gpuCommandBufferObj->wgpuRenderPassEncoder, vp.left, vp.top, vp.width, vp.height, vp.minDepth, vp.maxDepth);

        const Rect &rect = _gpuCommandBufferObj->stateCache.rect;
        wgpuRenderPassEncoderSetScissorRect(_gpuCommandBufferObj->wgpuRenderPassEncoder, rect.x, rect.y, rect.width, rect.height);

    } else if (pipelineState->getBindPoint() == PipelineBindPoint::COMPUTE) {
        auto *pipelineState = _gpuCommandBufferObj->stateCache.pipelineState;
        wgpuComputePassEncoderSetPipeline(_gpuCommandBufferObj->wgpuComputeEncoder,
                                          pipelineState->gpuPipelineStateObject()->wgpuComputePipeline);

        //bindgroup & descriptorset
        const auto &descriptorSets = _gpuCommandBufferObj->stateCache.descriptorSets;
        for (size_t i = 0; i < descriptorSets.size(); i++) {
            if (descriptorSets[i].descriptorSet->gpuBindGroupObject()->bindgroup) {
                wgpuComputePassEncoderSetBindGroup(_gpuCommandBufferObj->wgpuComputeEncoder,
                                                   descriptorSets[i].index,
                                                   descriptorSets[i].descriptorSet->gpuBindGroupObject()->bindgroup,
                                                   descriptorSets[i].dynamicOffsetCount,
                                                   descriptorSets[i].dynamicOffsets);
            }
        }

    } else {
        CC_LOG_ERROR("wrong pipeline state bind point.");
    }
}

void CCWGPUCommandBuffer::nextSubpass() {
    CC_LOG_INFO("@hana-alice to implement.");
}

void CCWGPUCommandBuffer::draw(const DrawInfo &info) {
    bindStates();

    auto *ia = static_cast<CCWGPUInputAssembler *>(_gpuCommandBufferObj->stateCache.inputAssembler);
    if (ia->getIndirectBuffer()) {
        auto *indirectBuffer           = static_cast<CCWGPUBuffer *>(ia->getIndirectBuffer());
        bool  multiDrawIndirectSupport = false;

        // indirectSupport not support, emscripten webgpu ver < 2021
        // https://github.com/gpuweb/gpuweb/issues/1354
        if (multiDrawIndirectSupport) {
            // todo
        } else {
            if (info.indexCount) {
                uint32_t drawInfoCount = indirectBuffer->getCount();
                for (size_t i = 0; i < drawInfoCount; i++) {
                    wgpuRenderPassEncoderDrawIndexedIndirect(_gpuCommandBufferObj->wgpuRenderPassEncoder,
                                                             indirectBuffer->gpuBufferObject()->wgpuBuffer,
                                                             indirectBuffer->getOffset() + i * sizeof(CCWGPUDrawIndexedIndirectObject));
                }
            } else {
                uint32_t drawInfoCount = indirectBuffer->getCount();
                for (size_t i = 0; i < drawInfoCount; i++) {
                    wgpuRenderPassEncoderDrawIndirect(_gpuCommandBufferObj->wgpuRenderPassEncoder,
                                                      indirectBuffer->gpuBufferObject()->wgpuBuffer,
                                                      indirectBuffer->getOffset() + i * sizeof(CCWGPUDrawIndirectObject));
                }
            }
        }
    } else {
        auto *indexBuffer = static_cast<CCWGPUBuffer *>(ia->getIndexBuffer());
        bool  drawIndexed = indexBuffer && info.indexCount;
        if (drawIndexed) {
            wgpuRenderPassEncoderDrawIndexed(_gpuCommandBufferObj->wgpuRenderPassEncoder,
                                             info.indexCount,
                                             info.instanceCount > 1 ? info.instanceCount : 1,
                                             info.firstIndex,
                                             info.vertexOffset,
                                             info.firstInstance);
        } else {
            wgpuRenderPassEncoderDraw(_gpuCommandBufferObj->wgpuRenderPassEncoder,
                                      info.vertexCount,
                                      info.instanceCount > 1 ? info.instanceCount : 1,
                                      info.firstVertex,
                                      info.firstInstance);
        }
    }
}

void CCWGPUCommandBuffer::updateBuffer(Buffer *buff, const void *data, uint size) {
    auto *ccBuffer = static_cast<CCWGPUBuffer *>(buff);
    // queue specific only
    ccBuffer->update(data, size);
}

void CCWGPUCommandBuffer::copyBuffersToTexture(const uint8_t *const *buffers, Texture *texture, const BufferTextureCopy *regions, uint count) {
    for (size_t i = 0; i < count; i++) {
        WGPUOrigin3D origin = {
            .x = static_cast<uint32_t>(regions[i].texOffset.x),
            .y = static_cast<uint32_t>(regions[i].texOffset.y),
            .z = static_cast<uint32_t>(regions[i].texOffset.z),
        };

        WGPUImageCopyTexture imageCopyTexture = {
            .texture  = static_cast<CCWGPUTexture *>(texture)->gpuTextureObject()->wgpuTexture,
            .mipLevel = 0,
            .origin   = origin,
            .aspect   = WGPUTextureAspect_All,
        };

        auto *   ccTex       = static_cast<CCWGPUTexture *>(texture);
        uint32_t width       = regions[i].texExtent.width;
        uint32_t height      = regions[i].texExtent.height;
        uint32_t depth       = regions[i].texExtent.depth;
        uint32_t bytesPerRow = GFX_FORMAT_INFOS[static_cast<uint>(ccTex->getFormat())].size * width;
        uint32_t dataSize    = bytesPerRow * height * depth;

        WGPUTextureDataLayout texLayout = {
            .offset       = 0,
            .bytesPerRow  = bytesPerRow,
            .rowsPerImage = height,
        };

        WGPUExtent3D extent = {
            .width              = width,
            .height             = height,
            .depthOrArrayLayers = depth,
        };

        wgpuQueueWriteTexture(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuQueue, &imageCopyTexture, buffers[i], dataSize, &texLayout, &extent);
    }
}

void CCWGPUCommandBuffer::blitTexture(Texture *srcTexture, Texture *dstTexture, const TextureBlit *regions, uint count, Filter filter) {
    for (size_t i = 0; i < count; i++) {
        auto *srcTex = static_cast<CCWGPUTexture *>(srcTexture);
        auto *dstTex = static_cast<CCWGPUTexture *>(dstTexture);

        WGPUOrigin3D srcOrigin = {
            .x = static_cast<uint32_t>(regions[i].srcOffset.x),
            .y = static_cast<uint32_t>(regions[i].srcOffset.y),
            .z = static_cast<uint32_t>(regions[i].srcOffset.z),
        };

        WGPUImageCopyTexture imageCopyTextureSrc = {
            .texture  = srcTex->gpuTextureObject()->wgpuTexture,
            .mipLevel = 0,
            .origin   = srcOrigin,
            .aspect   = WGPUTextureAspect_All,
        };

        WGPUOrigin3D dstOrigin = {
            .x = static_cast<uint32_t>(regions[i].dstOffset.x),
            .y = static_cast<uint32_t>(regions[i].dstOffset.y),
            .z = static_cast<uint32_t>(regions[i].dstOffset.z),
        };

        WGPUImageCopyTexture imageCopyTextureDst = {
            .texture  = dstTex->gpuTextureObject()->wgpuTexture,
            .mipLevel = 0,
            .origin   = dstOrigin,
            .aspect   = WGPUTextureAspect_All,
        };

        WGPUExtent3D extent = {
            .width              = regions[i].srcExtent.width,
            .height             = regions[i].srcExtent.height,
            .depthOrArrayLayers = regions[i].srcExtent.depth,
        };

        wgpuCommandEncoderCopyTextureToTexture(_gpuCommandBufferObj->wgpuCommandEncoder, &imageCopyTextureSrc, &imageCopyTextureDst, &extent);
    }
}

void CCWGPUCommandBuffer::execute(CommandBuffer *const *cmdBuffs, uint32_t count) {
    CC_LOG_ERROR(".....");
}

void CCWGPUCommandBuffer::dispatch(const DispatchInfo &info) {
    WGPUComputePassDescriptor cmoputeDesc = {};
    if (!_gpuCommandBufferObj->wgpuComputeEncoder) {
        _gpuCommandBufferObj->wgpuComputeEncoder = wgpuCommandEncoderBeginComputePass(_gpuCommandBufferObj->wgpuCommandEncoder, &cmoputeDesc);
    }

    if (info.indirectBuffer) {
        auto *indirectBuffer = static_cast<CCWGPUBuffer *>(info.indirectBuffer);
        wgpuComputePassEncoderDispatchIndirect(_gpuCommandBufferObj->wgpuComputeEncoder,
                                               indirectBuffer->gpuBufferObject()->wgpuBuffer,
                                               info.indirectOffset);

    } else {
        wgpuComputePassEncoderDispatch(_gpuCommandBufferObj->wgpuComputeEncoder,
                                       info.groupCountX,
                                       info.groupCountY,
                                       info.groupCountZ);
    }
}

void CCWGPUCommandBuffer::pipelineBarrier(const GlobalBarrier *barrier, const TextureBarrier *const *textureBarriers, const Texture *const *textures, uint textureBarrierCount) {
}

void CCWGPUCommandBuffer::updateIndirectBuffer(Buffer *buffer, const DrawInfoList &list) {
    buffer->update(list.data(), 0); // indirectBuffer calc size inside.
}

} // namespace gfx
} // namespace cc
