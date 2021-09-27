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
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <functional>
#include <queue>
#include "gfx-base/GFXCommandBuffer.h"
namespace cc {
namespace gfx {

struct CCWGPUCommandBufferObject;

typedef std::function<void(CCWGPUCommandBufferObject *)> EncodeFunc;

class CCWGPUCommandBuffer final : public emscripten::wrapper<CommandBuffer> {
public:
    EMSCRIPTEN_WRAPPER(CCWGPUCommandBuffer);
    CCWGPUCommandBuffer();
    ~CCWGPUCommandBuffer() = default;

    virtual void begin(RenderPass *renderPass, uint subpass, Framebuffer *frameBuffer);
    virtual void end();
    virtual void beginRenderPass(RenderPass *renderPass, Framebuffer *fbo, const Rect &renderArea, const Color *colors, float depth, uint stencil, CommandBuffer *const *secondaryCBs, uint secondaryCBCount);
    virtual void endRenderPass();
    virtual void bindPipelineState(PipelineState *pso);
    virtual void bindDescriptorSet(uint set, DescriptorSet *descriptorSet, uint dynamicOffsetCount, const uint *dynamicOffsets);
    virtual void bindInputAssembler(InputAssembler *ia);
    virtual void setViewport(const Viewport &vp);
    virtual void setScissor(const Rect &rect);
    virtual void setLineWidth(float width);
    virtual void setDepthBias(float constant, float clamp, float slope);
    virtual void setBlendConstants(const Color &constants);
    virtual void setDepthBound(float minBounds, float maxBounds);
    virtual void setStencilWriteMask(StencilFace face, uint mask);
    virtual void setStencilCompareMask(StencilFace face, uint ref, uint mask);
    virtual void nextSubpass();
    virtual void draw(const DrawInfo &info);
    virtual void updateBuffer(Buffer *buff, const void *data, uint size);
    virtual void copyBuffersToTexture(const uint8_t *const *buffers, Texture *texture, const BufferTextureCopy *regions, uint count);
    virtual void blitTexture(Texture *srcTexture, Texture *dstTexture, const TextureBlit *regions, uint count, Filter filter);
    virtual void execute(CommandBuffer *const *cmdBuffs, uint32_t count);
    virtual void dispatch(const DispatchInfo &info);
    virtual void pipelineBarrier(const GlobalBarrier *barrier, const TextureBarrier *const *textureBarriers, const Texture *const *textures, uint textureBarrierCount);

    inline CCWGPUCommandBufferObject *gpuCommandBufferObject() { return _gpuCommandBufferObj; }

    void updateIndirectBuffer(Buffer *buffer, const DrawInfoList &list);

    void copyBuffersToTexture(const std::vector<String> &strList, Texture *texture, const BufferTextureCopy *regions, uint count);

    void updateBuffer(Buffer *buff, const emscripten::val &v, uint size) {
        std::vector<uint8_t> buffer = emscripten::convertJSArrayToNumberVector<uint8_t>(v);
        updateBuffer(buff, reinterpret_cast<const void *>(buffer.data()), size);
    }

    void beginRenderPass(RenderPass *renderPass, Framebuffer *fbo, const Rect &renderArea, const ColorList &colors, float depth, uint stencil) {
        this->CommandBuffer::beginRenderPass(renderPass, fbo, renderArea, colors.data(), depth, stencil);
    }

protected:
    virtual void doInit(const CommandBufferInfo &info);
    virtual void doDestroy();

    // delay binding.
    void bindStates();

    CCWGPUCommandBufferObject *_gpuCommandBufferObj = nullptr;

    // command buffer inner impl
    std::queue<EncodeFunc> _renderPassFuncQ;
    std::queue<EncodeFunc> _computeFuncQ;
};

} // namespace gfx
} // namespace cc
