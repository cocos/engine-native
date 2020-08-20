#include "VKStd.h"

#include "VKCommands.h"
#include "VKDescriptorSetLayout.h"
#include "VKDevice.h"

namespace cc {
namespace gfx {

CCVKDescriptorSetLayout::CCVKDescriptorSetLayout(Device *device)
: DescriptorSetLayout(device) {
}

CCVKDescriptorSetLayout::~CCVKDescriptorSetLayout() {
}

bool CCVKDescriptorSetLayout::initialize(const DescriptorSetLayoutInfo &info) {

    _bindings = info.bindings;

    _gpuDescriptorSetLayout = CC_NEW(CCVKGPUDescriptorSetLayout);

    for (DescriptorSetLayoutBinding binding : _bindings) {
        _gpuDescriptorSetLayout->bindings.push_back(binding);
    }

    CCVKCmdFuncCreateDescriptorSetLayout((CCVKDevice *)_device, _gpuDescriptorSetLayout);

    _status = Status::SUCCESS;

    return true;
}

void CCVKDescriptorSetLayout::destroy() {
    if (_gpuDescriptorSetLayout) {
        ((CCVKDevice *)_device)->gpuRecycleBin()->collect(_gpuDescriptorSetLayout);
        _gpuDescriptorSetLayout = nullptr;
    }

    _status = Status::UNREADY;
}

} // namespace gfx
} // namespace cc
