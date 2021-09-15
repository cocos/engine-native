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
#include "WGPUDevice.h"
#include "WGPUObject.h"
#include "WGPUUtils.h"

namespace cc {
namespace gfx {

CCWGPUCommandBuffer::CCWGPUCommandBuffer() {
}

void CCWGPUCommandBuffer::doInit(const CommandBufferInfo &info) {
    _gpuCommandBufferObj        = CC_NEW(CCWGPUCommandBufferObject);
    _gpuCommandBufferObj->type  = info.type;
    _gpuCommandBufferObj->queue = info.queue;
}

void CCWGPUCommandBuffer::doDestroy() {
    CC_SAFE_DELETE(_gpuCommandBufferObj);
}

void CCWGPUCommandBuffer::begin(RenderPass *renderPass, uint subpass, Framebuffer *frameBuffer) {
    //TODO_Zeqiang: subpass support
}

void CCWGPUCommandBuffer::end() {
}

// typedef struct WGPURenderPassDescriptor {
//     WGPUChainedStruct const * nextInChain;
//     char const * label;
//     uint32_t colorAttachmentCount;
//     WGPURenderPassColorAttachment const * colorAttachments;
//     WGPURenderPassDepthStencilAttachment const * depthStencilAttachment;
//     WGPUQuerySet occlusionQuerySet;
// } WGPURenderPassDescriptor;

void CCWGPUCommandBuffer::beginRenderPass(RenderPass *renderPass, Framebuffer *fbo, const Rect &renderArea, const Color *colors, float depth, uint stencil, CommandBuffer *const *secondaryCBs, uint secondaryCBCount) {
    const ColorAttachmentList &   colorConfigs       = renderPass->getColorAttachments();
    const DepthStencilAttachment &depthStencilConfig = renderPass->getDepthStencilAttachment();
    const TextureList &           textures           = fbo->getColorTextures();
    Texture *                     dsTexture          = fbo->getDepthStencilTexture();
    CCWGPUSwapchain *             swapchain          = fbo->swapchain();

    WGPURenderPassDescriptor &renderPassDesc = _gpuCommandBufferObj->renderPassDescriptor;

    if (colorConfigs.empty()) {
        renderPassDesc.nextInChain          = nullptr;
        renderPassDesc.label                = "swapchain";
        renderPassDesc.colorAttachmentCount = 1;

        WGPURenderPassColorAttachment *color = new WGPURenderPassColorAttachment{
            swapchain->gpuSwapchainObject()->swapchainColor->selfView,
            nullptr, //TODO_Zeqiang: wgpu offscr msaa
            toWGPULoadOp(colorConfigs[0].loadOp),
            toWGPUStoreOp(colorConfigs[0].storeOp),
            toWGPUColor(colors[0])};
        renderPassDesc.colorAttachments = color;
    } else {
        renderPassDesc.nextInChain            = nullptr;
        renderPassDesc.label                  = "attachments";
        WGPURenderPassColorAttachment *colors = new WGPURenderPassColorAttachment[colorConfigs.size()];
        for (size_t i = 0; i < colorConfigs.size(); i++) {
            renderPassDesc.colorAttachmentCount = colorConfigs.size();
            colors[i].view                      = static_cast<CCWGPUTexture *>(textures[i])->gpuTextureObject()->selfView;
            colors[i].resolveTarget             = nullptr; //TODO_Zeqiang: wgpu offscr msaa
            colors[i].loadOp                    = toWGPULoadOp(colorConfigs[i].loadOp);
            colors[i].storeOp                   = toWGPUStoreOp(colorConfigs[i].storeOp);
            colors[i].clearColor                = toWGPUColor(colors[i]);
        }
        renderPassDesc.colorAttachments = colors;
    }

    if (dsTexture) {
        WGPURenderPassDepthStencilAttachment *depthStencil = new WGPURenderPassDepthStencilAttachment{
            static_cast<CCWGPUTexture *>(dsTexture)->gpuTextureObject()->selfView,
            toWGPULoadOp(depthStencilConfig.depthLoadOp),
            toWGPUStoreOp(depthStencilAttachment.depthStoreOp),
            depth,
            false,
            toWGPULoadOp(depthStencilConfig.stencilLoadOp),
            toWGPUStoreOp(depthStencilAttachment.stencilStoreOp),
            stencil,
            false,
        };
        renderPassDesc.depthStencilAttachment = depthStencil;
    } else {
        if (depthStencilConfig.format == Format::UNKNOWN) {
            renderPassDesc.depthStencilAttachment = nullptr;
        } else {
            WGPURenderPassDepthStencilAttachment *depthStencil = new WGPURenderPassDepthStencilAttachment{
                swapchain->gpuSwapchainObject()->swapchainDepthStencil->selfView,
                toWGPULoadOp(depthStencilConfig.depthLoadOp),
                toWGPUStoreOp(depthStencilAttachment.depthStoreOp),
                depth,
                false,
                toWGPULoadOp(depthStencilConfig.stencilLoadOp),
                toWGPUStoreOp(depthStencilAttachment.stencilStoreOp),
                stencil,
                false,
            };
            renderPassDesc.depthStencilAttachment = depthStencil;
        }
    }

    auto vpFunc = [renderArea](const CCWGPUCommandBufferObject *gpuCommandBufferObj) {
        WGPUCommandEncoder encoder = gpuCommandBufferObj->wgpuRenderPassEncoder;
        wgpuRenderPassEncoderSetViewport(encoder, renderArea.x, renderArea.y, renderArea.width, renderArea.height, 0.0f, 1.0f);
        wgpuRenderPassEncoderSetScissorRect(encoder, renderArea.x, renderArea.y, renderArea.width, renderArea.height);
    };
    _renderPassFuncQ.push(vpFunc);

} // namespace gfx

void CCWGPUCommandBuffer::bindPipelineState(PipelineState *pso) {
}

void CCWGPUCommandBuffer::bindDescriptorSet(uint set, DescriptorSet *descriptorSet, uint dynamicOffsetCount, const uint *dynamicOffsets) {
}

void CCWGPUCommandBuffer::bindInputAssembler(InputAssembler *ia) {
}

void CCWGPUCommandBuffer::setViewport(const Viewport &vp) {
}

void CCWGPUCommandBuffer::setScissor(const Rect &rect) {
}

void CCWGPUCommandBuffer::setLineWidth(float width) {
}

void CCWGPUCommandBuffer::setDepthBias(float constant, float clamp, float slope) {
}

void CCWGPUCommandBuffer::setBlendConstants(const Color &constants) {
}

void CCWGPUCommandBuffer::setDepthBound(float minBounds, float maxBounds) {
}

void CCWGPUCommandBuffer::setStencilWriteMask(StencilFace face, uint mask) {
}

void CCWGPUCommandBuffer::setStencilCompareMask(StencilFace face, uint ref, uint mask)) {
}

void CCWGPUCommandBuffer::nextSubpass() {
}

void CCWGPUCommandBuffer::draw(const DrawInfo &info) {
}

void CCWGPUCommandBuffer::updateBuffer(Buffer *buff, const void *data, uint size) {
}

void CCWGPUCommandBuffer::copyBuffersToTexture(const uint8_t *const *buffers, Texture *texture, const BufferTextureCopy *regions, uint count) {
}

void CCWGPUCommandBuffer::blitTexture(Texture *srcTexture, Texture *dstTexture, const TextureBlit *regions, uint count, Filter filter) {
}

void CCWGPUCommandBuffer::execute(CommandBuffer *const *cmdBuffs, uint32_t count) {
}

void CCWGPUCommandBuffer::dispatch(const DispatchInfo &info) {
}

void CCWGPUCommandBuffer::pipelineBarrier(const GlobalBarrier *barrier, const TextureBarrier *const *textureBarriers, const Texture *const *textures, uint textureBarrierCount) {
}

} // namespace gfx
} // namespace cc
