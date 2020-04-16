#include "CCVKStd.h"
#include "CCVKRenderPass.h"
#include "CCVKCommands.h"

NS_CC_BEGIN

CCVKRenderPass::CCVKRenderPass(GFXDevice* device)
    : GFXRenderPass(device) {
}

CCVKRenderPass::~CCVKRenderPass() {
}

bool CCVKRenderPass::initialize(const GFXRenderPassInfo &info) {
  
  _colorAttachments = info.colorAttachments;
  _depthStencilAttachment = info.depthStencilAttachment;
  
  _gpuRenderPass = CC_NEW(CCVKGPURenderPass);
  _gpuRenderPass->colorAttachments = _colorAttachments;
  _gpuRenderPass->depthStencilAttachment = _depthStencilAttachment;
    
    _status = GFXStatus::SUCCESS;
  
  return true;
}

void CCVKRenderPass::destroy() {
  if (_gpuRenderPass) {
    CC_DELETE(_gpuRenderPass);
    _gpuRenderPass = nullptr;
  }
    
    _status = GFXStatus::UNREADY;
}

NS_CC_END
