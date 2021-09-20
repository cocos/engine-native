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
            _textureIdxMap.insert(std::make_pair<uint8_t, uint8_t>(_gpuBindGroupObj->bindGroupEntries.size() - 1, i));
            dsLayout->updateTextureLayout(texEntry.binding, texture);

            // 2. sampler
            CCWGPUSampler*     sampler  = deviceObj->defaultResources.sampler;
            WGPUBindGroupEntry smpEntry = {
                .binding = bindings[i].binding + CC_WGPU_MAX_ATTACHMENTS,
                .sampler = sampler->gpuSampler(),
            };
            _gpuBindGroupObj->bindGroupEntries.push_back(smpEntry);
            _samplerIdxMap.insert(std::make_pair<uint8_t, uint8_t>(_gpuBindGroupObj->bindGroupEntries.size() - 1, i));
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
            dsLayout->updateTextureLayout(texEntry.binding, texture);
            printf("storage:%d %p\n", i, texture);
        } else {
            printf("**********************unsupport desc type: %d\n", bindings[i].descriptorType);
        }
    }
    for (auto pair : _textureIdxMap) {
        printf("texmap: %d, %d\n", pair.first, pair.second);
    }
    for (auto pair : _samplerIdxMap) {
        printf("smpmap: %d, %d\n", pair.first, pair.second);
    }
    dsLayout->prepare();
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
        printf("desc type: %d\n", bindings[i].descriptorType);
        if (hasFlag(DESCRIPTOR_BUFFER_TYPE, bindings[i].descriptorType)) {
            if (_buffers[i]) {
                auto* buffer           = static_cast<CCWGPUBuffer*>(_buffers[i]);
                auto& bindGroupEntry   = _gpuBindGroupObj->bindGroupEntries[i];
                bindGroupEntry.binding = binding.binding;
                bindGroupEntry.buffer  = buffer->gpuBufferObject()->wgpuBuffer;
                bindGroupEntry.offset  = buffer->getOffset();
                bindGroupEntry.size    = buffer->getSize();
                printf("buffer %p %p %d\n", buffer, buffer->gpuBufferObject()->wgpuBuffer, i);
            }

        } else if (binding.descriptorType == DescriptorType::SAMPLER_TEXTURE) {
            auto texIter = _textureIdxMap.find(i);
            auto smpIter = _samplerIdxMap.find(i);
            assert((texIter != _textureIdxMap.end()) + (smpIter != _samplerIdxMap.end()) == 1);
            uint8_t textureIdx     = texIter != _textureIdxMap.end() ? texIter->second : 255;
            uint8_t samplerIdx     = smpIter != _samplerIdxMap.end() ? smpIter->second : 255;
            auto&   bindGroupEntry = _gpuBindGroupObj->bindGroupEntries[i];
            if (textureIdx != 255 && _textures[textureIdx]) {
                auto* texture              = static_cast<CCWGPUTexture*>(_textures[textureIdx]);
                bindGroupEntry.binding     = binding.binding;
                bindGroupEntry.textureView = texture->gpuTextureObject()->selfView;
                printf("texture %p %d %d\n", texture, textureIdx, i);
            } else if (samplerIdx != 255 && _samplers[samplerIdx]) {
                auto* sampler          = static_cast<CCWGPUSampler*>(_samplers[samplerIdx]);
                bindGroupEntry.binding = binding.binding + CC_WGPU_MAX_ATTACHMENTS;
                bindGroupEntry.sampler = sampler->gpuSampler();
                printf("sampler %p %d %d\n", sampler, samplerIdx, i);
            }
        } else if (binding.descriptorType == DescriptorType::STORAGE_IMAGE || binding.descriptorType == DescriptorType::TEXTURE) {
            if (_textures[i]) {
                auto& bindGroupEntry       = _gpuBindGroupObj->bindGroupEntries[i];
                auto* texture              = static_cast<CCWGPUTexture*>(_textures[i]);
                bindGroupEntry.binding     = binding.binding;
                bindGroupEntry.textureView = texture->gpuTextureObject()->selfView;
                printf("stimg %p %d %d\n", texture, binding.binding, i);
            }
        }

        printf("update3\n");
        if (_gpuBindGroupObj->bindgroup) {
            wgpuBindGroupRelease(_gpuBindGroupObj->bindgroup);
        }
        printf("_gpuBindGroupObj->bindGroupEntries %d\n", _gpuBindGroupObj->bindGroupEntries.size());
        WGPUBindGroupDescriptor bindGroupDesc = {
            .nextInChain = nullptr,
            .label       = nullptr,
            .layout      = dsLayout->gpuLayoutEntryObject()->bindGroupLayout,
            .entryCount  = _gpuBindGroupObj->bindGroupEntries.size(),
            .entries     = _gpuBindGroupObj->bindGroupEntries.data(),
        };
        printf("bindGroupDesc %p\n", bindGroupDesc.layout);
        printf("entries %p\n", bindGroupDesc.entries);
        for (size_t i = 0; i < _gpuBindGroupObj->bindGroupEntries.size(); i++) {
            printf("buffer, tex, samp:%d %p %p %p\n",
                   _gpuBindGroupObj->bindGroupEntries[i].binding,
                   _gpuBindGroupObj->bindGroupEntries[i].buffer,
                   _gpuBindGroupObj->bindGroupEntries[i].textureView,
                   _gpuBindGroupObj->bindGroupEntries[i].sampler);
        }
        _gpuBindGroupObj->bindgroup = wgpuDeviceCreateBindGroup(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &bindGroupDesc);
        printf("update4\n");
    }
    printf("update5\n");
}

} // namespace gfx
} // namespace cc