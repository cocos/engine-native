#include "GLES2Std.h"
#include "GLES2RenderPass.h"
#include "GLES2Commands.h"

NS_CC_BEGIN

GLES2RenderPass::GLES2RenderPass(GFXDevice* device)
    : GFXRenderPass(device),
      gpu_render_pass_(nullptr) {
}

GLES2RenderPass::~GLES2RenderPass() {
}

bool GLES2RenderPass::initialize(const GFXRenderPassInfo &info) {
  
  _colorAttachments = info.colorAttachments;
  _depthStencilAttachment = info.depthStencilAttachment;
  
  gpu_render_pass_ = CC_NEW(GLES2GPURenderPass);
  gpu_render_pass_->colorAttachments = _colorAttachments;
  gpu_render_pass_->depthStencilAttachment = _depthStencilAttachment;
  
  return true;
}

void GLES2RenderPass::destroy() {
  if (gpu_render_pass_) {
    CC_DELETE(gpu_render_pass_);
    gpu_render_pass_ = nullptr;
  }
}

NS_CC_END
