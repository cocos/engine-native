#include "GLES3Std.h"
#include "GLES3RenderPass.h"
#include "GLES3Commands.h"

NS_CC_BEGIN

GLES3RenderPass::GLES3RenderPass(GFXDevice* device)
    : GFXRenderPass(device),
      gpu_render_pass_(nullptr) {
}

GLES3RenderPass::~GLES3RenderPass() {
}

bool GLES3RenderPass::initialize(const GFXRenderPassInfo &info) {
  
  _colorAttachments = info.colorAttachments;
  _depthStencilAttachment = info.depthStencilAttachment;
  
  gpu_render_pass_ = CC_NEW(GLES3GPURenderPass);
  gpu_render_pass_->colorAttachments = _colorAttachments;
  gpu_render_pass_->depthStencilAttachment = _depthStencilAttachment;
  
  return true;
}

void GLES3RenderPass::destroy() {
  if (gpu_render_pass_) {
    CC_DELETE(gpu_render_pass_);
    gpu_render_pass_ = nullptr;
  }
}

NS_CC_END
