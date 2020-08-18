#include "GLES2Std.h"

#include "GLES2Commands.h"
#include "GLES2DescriptorSetLayout.h"

namespace cc {
namespace gfx {

GLES2DescriptorSetLayout::GLES2DescriptorSetLayout(Device *device)
: DescriptorSetLayout(device) {
}

GLES2DescriptorSetLayout::~GLES2DescriptorSetLayout() {
}

bool GLES2DescriptorSetLayout::initialize(const DescriptorSetLayoutInfo &info) {

    _bindings = info.bindings;

    _gpuDescriptorSetLayout = CC_NEW(GLES2GPUDescriptorSetLayout);

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

void GLES2DescriptorSetLayout::destroy() {
    if (_gpuDescriptorSetLayout) {
        CC_DELETE(_gpuDescriptorSetLayout);
        _gpuDescriptorSetLayout = nullptr;
    }

    _status = Status::UNREADY;
}

} // namespace gfx
} // namespace cc
