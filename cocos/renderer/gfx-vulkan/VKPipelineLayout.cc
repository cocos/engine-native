#include "VKStd.h"
#include "VKPipelineLayout.h"
#include "VKCommands.h"

NS_CC_BEGIN

CCVKPipelineLayout::CCVKPipelineLayout(GFXDevice* device)
    : GFXPipelineLayout(device) {
}

CCVKPipelineLayout::~CCVKPipelineLayout() {
}

bool CCVKPipelineLayout::initialize(const GFXPipelineLayoutInfo &info) {
  
  _layouts = info.layouts;
  _pushConstantsRanges = info.pushConstantsRanges;
  
  _gpuPipelineLayout = CC_NEW(CCVKGPUPipelineLayout);
    _status = GFXStatus::SUCCESS;
  return true;
}

void CCVKPipelineLayout::destroy() {
  if (_gpuPipelineLayout) {
    CC_DELETE(_gpuPipelineLayout);
    _gpuPipelineLayout = nullptr;
  }
    _status = GFXStatus::UNREADY;
}

NS_CC_END
