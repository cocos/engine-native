/****************************************************************************
 Copyright (c) 2020-2021 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#include "WGPUDescriptorSet.h"
#include <emscripten/html5_webgpu.h>
#include "WGPUBuffer.h"
#include "WGPUDescriptorSetLayout.h"
#include "WGPUDevice.h"
#include "WGPUObject.h"
#include "WGPUSampler.h"
#include "WGPUTexture.h"

namespace cc {
namespace gfx {

using namespace emscripten;

CCWGPUDescriptorSet::CCWGPUDescriptorSet() : wrapper<DescriptorSet>(val::object()) {
}

void CCWGPUDescriptorSet::doInit(const DescriptorSetInfo& info) {
    _gpuBindGroupObj = CC_NEW(CCWGPUBindGroupObject);

    auto*                        dsLayout      = static_cast<CCWGPUDescriptorSetLayout*>(_layout);
    CCWGPUBindGroupLayoutObject* layoutEntries = dsLayout->gpuLayoutEntryObject();
    const auto&                  bindings      = dsLayout->getBindings();
    CCWGPUDeviceObject*          deviceObj     = CCWGPUDevice::getInstance()->gpuDeviceObject();
    for (size_t i = 0; i < bindings.size(); i++) {
        if (bindings[i].descriptorType == DescriptorType::SAMPLER_TEXTURE) {
            //1. texture
            CCWGPUTexture*     texture  = deviceObj->defaultResources.texture;
            WGPUBindGroupEntry texEntry = {
                .binding     = bindings[i].binding,
                .textureView = texture->gpuTextureObject()->selfView,
            };
            _gpuBindGroupObj->bindGroupEntries.push_back(texEntry);
            _textureIdxMap.insert(std::make_pair<uint8_t, uint8_t>(bindings[i].binding, _gpuBindGroupObj->bindGroupEntries.size() - 1));
            dsLayout->updateLayout(texEntry.binding, nullptr, texture);

            // 2. sampler
            CCWGPUSampler*     sampler  = deviceObj->defaultResources.sampler;
            WGPUBindGroupEntry smpEntry = {
                .binding = bindings[i].binding + CC_WGPU_MAX_ATTACHMENTS,
                .sampler = sampler->gpuSampler(),
            };
            _gpuBindGroupObj->bindGroupEntries.push_back(smpEntry);
            _samplerIdxMap.insert(std::make_pair<uint8_t, uint8_t>(bindings[i].binding, _gpuBindGroupObj->bindGroupEntries.size() - 1));
            dsLayout->updateLayout(smpEntry.binding, nullptr, nullptr, sampler);
        } else if (hasFlag(DESCRIPTOR_BUFFER_TYPE, bindings[i].descriptorType)) {
            CCWGPUBuffer*      buffer      = deviceObj->defaultResources.buffer;
            WGPUBindGroupEntry bufferEntry = {
                .binding = bindings[i].binding,
                .buffer  = buffer->gpuBufferObject()->wgpuBuffer,
                .size    = buffer->getSize(),
                .offset  = buffer->getOffset(),
            };
            _gpuBindGroupObj->bindGroupEntries.push_back(bufferEntry);
        } else if (bindings[i].descriptorType == DescriptorType::STORAGE_IMAGE) {
            CCWGPUTexture*     texture  = deviceObj->defaultResources.texture;
            WGPUBindGroupEntry texEntry = {
                .binding     = bindings[i].binding,
                .textureView = texture->gpuTextureObject()->selfView,
            };
            _gpuBindGroupObj->bindGroupEntries.push_back(texEntry);
            dsLayout->updateLayout(texEntry.binding, nullptr, texture);
        }
    }
    // for (size_t i = 0; i < _gpuBindGroupObj->bindGroupEntries.size(); i++) {
    //     printf("i: %d %d %p %p %p \n", i, _gpuBindGroupObj->bindGroupEntries[i].binding,
    //            _gpuBindGroupObj->bindGroupEntries[i].buffer, _gpuBindGroupObj->bindGroupEntries[i].textureView, _gpuBindGroupObj->bindGroupEntries[i].sampler);
    // }
} // namespace gfx

void CCWGPUDescriptorSet::doDestroy() {
    CC_DELETE(_gpuBindGroupObj);
}

void CCWGPUDescriptorSet::update() {
    if (!_isDirty || !_layout) {
        return;
    }
    auto*       dsLayout = static_cast<CCWGPUDescriptorSetLayout*>(_layout);
    const auto& bindings = dsLayout->getBindings();

    for (size_t i = 0; i < bindings.size(); i++) {
        const auto& binding = bindings[i];
        if (hasFlag(DESCRIPTOR_BUFFER_TYPE, bindings[i].descriptorType)) {
            if (_buffers[i]) {
                auto* buffer           = static_cast<CCWGPUBuffer*>(_buffers[i]);
                auto& bindGroupEntry   = _gpuBindGroupObj->bindGroupEntries[i];
                bindGroupEntry.binding = binding.binding;
                bindGroupEntry.buffer  = buffer->gpuBufferObject()->wgpuBuffer;
                bindGroupEntry.offset  = buffer->getOffset();
                bindGroupEntry.size    = buffer->getSize();
            }

        } else if (binding.descriptorType == DescriptorType::SAMPLER_TEXTURE) {
            auto texIter = _textureIdxMap.find(binding.binding);
            auto smpIter = _samplerIdxMap.find(binding.binding);
            //assert((texIter != _textureIdxMap.end()) + (smpIter != _samplerIdxMap.end()) == 1);
            uint8_t textureIdx = texIter != _textureIdxMap.end() ? texIter->second : 255;
            uint8_t samplerIdx = smpIter != _samplerIdxMap.end() ? smpIter->second : 255;
            if (textureIdx != 255 && _textures[i]) {
                auto& bindGroupEntry       = _gpuBindGroupObj->bindGroupEntries[textureIdx];
                auto* texture              = static_cast<CCWGPUTexture*>(_textures[i]);
                bindGroupEntry.binding     = binding.binding;
                bindGroupEntry.textureView = texture->gpuTextureObject()->selfView;
                dsLayout->updateLayout(bindGroupEntry.binding, nullptr, texture);
            }
            if (samplerIdx != 255 && _samplers[i]) {
                auto& bindGroupEntry   = _gpuBindGroupObj->bindGroupEntries[samplerIdx];
                auto* sampler          = static_cast<CCWGPUSampler*>(_samplers[i]);
                bindGroupEntry.binding = binding.binding + CC_WGPU_MAX_ATTACHMENTS;
                bindGroupEntry.sampler = sampler->gpuSampler();
                dsLayout->updateLayout(bindGroupEntry.binding, nullptr, nullptr, sampler);
            }
        } else if (binding.descriptorType == DescriptorType::STORAGE_IMAGE || binding.descriptorType == DescriptorType::TEXTURE) {
            if (_textures[i]) {
                auto& bindGroupEntry       = _gpuBindGroupObj->bindGroupEntries[i];
                auto* texture              = static_cast<CCWGPUTexture*>(_textures[i]);
                bindGroupEntry.binding     = binding.binding;
                bindGroupEntry.textureView = texture->gpuTextureObject()->selfView;
                dsLayout->updateLayout(bindGroupEntry.binding, nullptr, texture);
            }
        }

        dsLayout->prepare();

        if (_gpuBindGroupObj->bindgroup) {
            wgpuBindGroupRelease(_gpuBindGroupObj->bindgroup);
        }

        WGPUBindGroupDescriptor bindGroupDesc = {
            .nextInChain = nullptr,
            .label       = nullptr,
            .layout      = dsLayout->gpuLayoutEntryObject()->bindGroupLayout,
            .entryCount  = _gpuBindGroupObj->bindGroupEntries.size(),
            .entries     = _gpuBindGroupObj->bindGroupEntries.data(),
        };
        // for (size_t i = 0; i < _gpuBindGroupObj->bindGroupEntries.size(); i++) {
        //     printf("c: %d %d %p %p %p \n", i, _gpuBindGroupObj->bindGroupEntries[i].binding,
        //            _gpuBindGroupObj->bindGroupEntries[i].buffer, _gpuBindGroupObj->bindGroupEntries[i].textureView, _gpuBindGroupObj->bindGroupEntries[i].sampler);
        // }

        _gpuBindGroupObj->bindgroup = wgpuDeviceCreateBindGroup(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &bindGroupDesc);
    }
}

} // namespace gfx
} // namespace cc