#include "MTLStd.h"
#include "MTLPipelineLayout.h"

namespace cc {
namespace gfx {

CCMTLPipelineLayout::CCMTLPipelineLayout(Device *device) : GFXPipelineLayout(device) {}
CCMTLPipelineLayout::~CCMTLPipelineLayout() { destroy(); }

bool CCMTLPipelineLayout::initialize(const GFXPipelineLayoutInfo &info) {
    _layouts = info.layouts;
    _pushConstantsRanges = info.pushConstantsRanges;
    _status = GFXStatus::SUCCESS;

    return true;
}

void CCMTLPipelineLayout::destroy() {
    _status = GFXStatus::UNREADY;
}

} // namespace gfx
} // namespace cc
