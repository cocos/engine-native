#include "GLES3Std.h"

#include "GLES3Commands.h"
#include "GLES3DescriptorSetLayout.h"

namespace cc {
namespace gfx {

GLES3DescriptorSetLayout::GLES3DescriptorSetLayout(Device *device)
: DescriptorSetLayout(device) {
}

GLES3DescriptorSetLayout::~GLES3DescriptorSetLayout() {
}

bool GLES3DescriptorSetLayout::initialize(const DescriptorSetLayoutInfo &info) {

    _bindings = info.bindings;

    _gpuDescriptorSetLayout = CC_NEW(GLES3GPUDescriptorSetLayout);

    for (DescriptorSetLayoutBinding binding : _bindings) {
        if ((uint)binding.descriptorType & DESCRIPTOR_DYNAMIC_TYPE) {
            for (uint i = 0u; i < binding.count; i++) {
                _gpuDescriptorSetLayout->dynamicBindings.push_back(i);
            }
        }
        _gpuDescriptorSetLayout->bindings.push_back(binding);
    }

    _status = Status::SUCCESS;

    return true;
}

void GLES3DescriptorSetLayout::destroy() {
    if (_gpuDescriptorSetLayout) {
        CC_DELETE(_gpuDescriptorSetLayout);
        _gpuDescriptorSetLayout = nullptr;
    }

    _status = Status::UNREADY;
}

} // namespace gfx
} // namespace cc
