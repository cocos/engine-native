#ifndef CC_GFXGLES3_GLES3_COMMAND_BUFFER_H_
#define CC_GFXGLES3_GLES3_COMMAND_BUFFER_H_

#include "GLES3Commands.h"

namespace cc {
namespace gfx {

class GLES3CommandAllocator;

class CC_GLES3_API GLES3CommandBuffer : public CommandBuffer {
    friend class GLES3Queue;

public:
    GLES3CommandBuffer(Device *device);
    ~GLES3CommandBuffer();

public:
    virtual bool initialize(const CommandBufferInfo &info) override;
    virtual void destroy() override;

    virtual void begin(GFXRenderPass *renderPass = nullptr, uint subpass = 0, Framebuffer *frameBuffer = nullptr) override;
    virtual void end() override;
    virtual void beginRenderPass(Framebuffer *fbo, const GFXRect &render_area, GFXClearFlags clear_flags, const std::vector<GFXColor> &colors, float depth, int stencil) override;
    virtual void endRenderPass() override;
    virtual void bindPipelineState(PipelineState *pso) override;
    virtual void bindBindingLayout(BindingLayout *layout) override;
    virtual void bindInputAssembler(InputAssembler *ia) override;
    virtual void setViewport(const GFXViewport &vp) override;
    virtual void setScissor(const GFXRect &rect) override;
    virtual void setLineWidth(const float width) override;
    virtual void setDepthBias(float constant, float clamp, float slope) override;
    virtual void setBlendConstants(const GFXColor &constants) override;
    virtual void setDepthBound(float min_bounds, float max_bounds) override;
    virtual void setStencilWriteMask(GFXStencilFace face, uint mask) override;
    virtual void setStencilCompareMask(GFXStencilFace face, int ref, uint mask) override;
    virtual void draw(InputAssembler *ia) override;
    virtual void updateBuffer(Buffer *buff, void *data, uint size, uint offset) override;
    virtual void copyBufferToTexture(Buffer *src, Texture *dst, TextureLayout layout, const BufferTextureCopyList &regions) override;
    virtual void execute(const std::vector<CommandBuffer *> &cmd_buffs, uint32_t count) override;

private:
    void BindStates();

private:
    GLES3CmdPackage *_cmdPackage = nullptr;
    GLES3CommandAllocator *_gles3Allocator = nullptr;
    bool _isInRenderPass = false;
    GLES3GPUPipelineState *_curGPUPipelineState = nullptr;
    GLES3GPUBindingLayout *_curGPUBlendLayout = nullptr;
    GLES3GPUInputAssembler *_curGPUInputAssember = nullptr;
    GFXViewport _curViewport;
    GFXRect _curScissor;
    float _curLineWidth = 1.0f;
    GLES3DepthBias _curDepthBias;
    GFXColor _curBlendConstants;
    GLES3DepthBounds _curDepthBounds;
    GLES3StencilWriteMask _curStencilWriteMask;
    GLES3StencilCompareMask _curStencilCompareMask;
    bool _isStateInvalid = false;
};

} // namespace gfx
} // namespace cc

#endif
