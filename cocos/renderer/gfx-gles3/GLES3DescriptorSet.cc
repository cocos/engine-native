#include "GLES3Std.h"

#include "GLES3Buffer.h"
#include "GLES3Commands.h"
#include "GLES3DescriptorSet.h"
#include "GLES3Sampler.h"
#include "GLES3Texture.h"

namespace cc {
namespace gfx {

GLES3DescriptorSet::GLES3DescriptorSet(Device *device)
: DescriptorSet(device) {
}

GLES3DescriptorSet::~GLES3DescriptorSet() {
}

bool GLES3DescriptorSet::initialize(const DescriptorSetInfo &info) {

    _layout = info.layout;

    const DescriptorSetLayoutBindingList &bindings = _layout->getBindings();
    const size_t descriptorCount = bindings.size();

    _buffers.resize(descriptorCount);
    _textures.resize(descriptorCount);
    _samplers.resize(descriptorCount);

    _gpuBindingLayout = CC_NEW(GLES3GPUDescriptorSet);
    _gpuBindingLayout->gpuDescriptors.resize(descriptorCount);
    for (size_t i = 0u; i < descriptorCount; i++) {
        _gpuBindingLayout->gpuDescriptors[i].type = bindings[i].descriptorType;
    }

    _status = Status::SUCCESS;

    return true;
}

void GLES3DescriptorSet::destroy() {
    _layout = nullptr;

    if (_gpuBindingLayout) {
        CC_DELETE(_gpuBindingLayout);
        _gpuBindingLayout = nullptr;
    }

    _status = Status::UNREADY;
}

void GLES3DescriptorSet::update() {
    if (_isDirty && _gpuBindingLayout) {
        const DescriptorSetLayoutBindingList &bindings = _layout->getBindings();
        for (size_t i = 0; i < bindings.size(); i++) {
            if ((uint)bindings[i].descriptorType & DESCRIPTOR_BUFFER_TYPE) {
                if (_buffers[i]) {
                    _gpuBindingLayout->gpuDescriptors[i].gpuBuffer = ((GLES3Buffer *)_buffers[i])->gpuBuffer();
                }
            } else if ((uint)bindings[i].descriptorType & DESCRIPTOR_SAMPLER_TYPE) {
                if (_textures[i]) {
                    _gpuBindingLayout->gpuDescriptors[i].gpuTexture = ((GLES3Texture *)_textures[i])->gpuTexture();
                }
                if (_samplers[i]) {
                    _gpuBindingLayout->gpuDescriptors[i].gpuSampler = ((GLES3Sampler *)_samplers[i])->gpuSampler();
                }
            }
        }
        _isDirty = false;
    }
}

} // namespace gfx
} // namespace cc
