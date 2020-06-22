#include "VKStd.h"

#include "VKBindingLayout.h"
#include "VKBuffer.h"
#include "VKCommands.h"
#include "VKDevice.h"
#include "VKSampler.h"
#include "VKTexture.h"

namespace cc {
namespace gfx {

CCVKBindingLayout::CCVKBindingLayout(Device *device)
: BindingLayout(device) {
}

CCVKBindingLayout::~CCVKBindingLayout() {
}

bool CCVKBindingLayout::initialize(const BindingLayoutInfo &info) {

    const UniformBlockList &blocks = info.shader->getBlocks();
    const UniformSamplerList &samplers = info.shader->getSamplers();
    const uint bindingCount = blocks.size() + samplers.size();

    if (bindingCount) {
        _bindingUnits.resize(bindingCount);
        for (size_t i = 0u; i < blocks.size(); ++i) {
            const UniformBlock &binding = blocks[i];
            BindingUnit &bindingUnit = _bindingUnits[i];
            bindingUnit.shaderStages = binding.shaderStages;
            bindingUnit.type = BindingType::UNIFORM_BUFFER;
            bindingUnit.binding = binding.binding;
            bindingUnit.name = binding.name;
            bindingUnit.count = 1;
        }
        for (size_t i = 0u; i < samplers.size(); ++i) {
            const UniformSampler &binding = samplers[i];
            BindingUnit &bindingUnit = _bindingUnits[blocks.size() + i];
            bindingUnit.shaderStages = binding.shaderStages;
            bindingUnit.type = BindingType::SAMPLER;
            bindingUnit.binding = binding.binding;
            bindingUnit.name = binding.name;
            bindingUnit.count = binding.count;
        }
    }

    _gpuBindingLayout = CC_NEW(CCVKGPUBindingLayout);
    _gpuBindingLayout->descriptorSets.resize(1);
    _gpuBindingLayout->descriptorInfos.resize(1);
    _gpuBindingLayout->descriptorInfos[0].resize(bindingCount);

    _status = Status::SUCCESS;

    return true;
}

void CCVKBindingLayout::destroy() {
    if (_gpuBindingLayout) {
        _gpuBindingLayout->descriptorInfos.clear();
        CC_DELETE(_gpuBindingLayout);
        _gpuBindingLayout = nullptr;
    }

    _status = Status::UNREADY;
}

void CCVKBindingLayout::update() {
    if (_isDirty && _gpuBindingLayout) {
        for (size_t i = 0u; i < _bindingUnits.size(); ++i) {
            BindingUnit &bindingUnit = _bindingUnits[i];
            CCVKDescriptorInfo &descriptorInfo = _gpuBindingLayout->descriptorInfos[0][i];
            switch (bindingUnit.type) {
                case BindingType::UNIFORM_BUFFER: {
                    if (bindingUnit.buffer) {
                        CCVKGPUBuffer *buffer = ((CCVKBuffer *)bindingUnit.buffer)->gpuBuffer();
                        descriptorInfo.buffer.buffer = buffer->vkBuffer;
                        descriptorInfo.buffer.offset = 0;
                        descriptorInfo.buffer.range = buffer->size;
                    }

                    break;
                }
                case BindingType::SAMPLER: {
                    descriptorInfo.image.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

                    if (bindingUnit.texture) {
                        descriptorInfo.image.imageView = ((CCVKTexture *)bindingUnit.texture)->gpuTextureView()->vkImageView;
                    } else {
                        descriptorInfo.image.imageView = ((CCVKDevice *)_device)->nullTexture2D->gpuTextureView()->vkImageView;
                    }

                    if (bindingUnit.sampler) {
                        descriptorInfo.image.sampler = ((CCVKSampler *)bindingUnit.sampler)->gpuSampler()->vkSampler;
                    }

                    break;
                }
            }
        }

        _isDirty = false;
    }
}

} // namespace gfx
} // namespace cc
