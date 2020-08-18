#include "GLES2Std.h"

#include "GLES2Buffer.h"
#include "GLES2Commands.h"
#include "GLES2DescriptorSet.h"
#include "GLES2Sampler.h"
#include "GLES2Texture.h"

namespace cc {
namespace gfx {

GLES2DescriptorSet::GLES2DescriptorSet(Device *device)
: DescriptorSet(device) {
}

GLES2DescriptorSet::~GLES2DescriptorSet() {
}

bool GLES2DescriptorSet::initialize(const DescriptorSetInfo &info) {

    _layout = info.layout;

    const DescriptorSetLayoutBindingList &bindings = _layout->getBindings();
    const size_t descriptorCount = bindings.size();

    _buffers.resize(descriptorCount);
    _textures.resize(descriptorCount);
    _samplers.resize(descriptorCount);

    _gpuBindingLayout = CC_NEW(GLES2GPUDescriptorSet);
    _gpuBindingLayout->gpuDescriptors.resize(descriptorCount);
    for (size_t i = 0u; i < descriptorCount; i++) {
        _gpuBindingLayout->gpuDescriptors[i].type = bindings[i].descriptorType;
    }

    _status = Status::SUCCESS;

    return true;
}

void GLES2DescriptorSet::destroy() {
    _layout = nullptr;

    if (_gpuBindingLayout) {
        CC_DELETE(_gpuBindingLayout);
        _gpuBindingLayout = nullptr;
    }

    _status = Status::UNREADY;
}

void GLES2DescriptorSet::update() {
    if (_isDirty && _gpuBindingLayout) {
        const DescriptorSetLayoutBindingList &bindings = _layout->getBindings();
        for (size_t i = 0; i < bindings.size(); i++) {
            if ((uint)bindings[i].descriptorType & DESCRIPTOR_BUFFER_TYPE) {
                GLES2Buffer *buffer = (GLES2Buffer *)_buffers[i];
                if (buffer) {
                    if (buffer->gpuBuffer()) {
                        _gpuBindingLayout->gpuDescriptors[i].gpuBuffer = buffer->gpuBuffer();
                    } else if (buffer->gpuBufferView()) {
                        _gpuBindingLayout->gpuDescriptors[i].gpuBufferView = buffer->gpuBufferView();
                    }
                }
            } else if ((uint)bindings[i].descriptorType & DESCRIPTOR_SAMPLER_TYPE) {
                if (_textures[i]) {
                    _gpuBindingLayout->gpuDescriptors[i].gpuTexture = ((GLES2Texture *)_textures[i])->gpuTexture();
                }
                if (_samplers[i]) {
                    _gpuBindingLayout->gpuDescriptors[i].gpuSampler = ((GLES2Sampler *)_samplers[i])->gpuSampler();
                }
            }
        }
        _isDirty = false;
    }
}

} // namespace gfx
} // namespace cc
