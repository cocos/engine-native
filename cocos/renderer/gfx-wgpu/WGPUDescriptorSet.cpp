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
            CCWGPUTexture* texture = deviceObj->defaultResources.texture;
            _gpuBindGroupObj->bindGroupEntries.push_back(WGPUBindGroupEntry());
            auto&& texEntry      = _gpuBindGroupObj->bindGroupEntries[i];
            texEntry.binding     = bindings[i].binding;
            texEntry.textureView = texture->gpuTextureObject()->selfView;
            texEntry.sampler     = wgpuDefaultHandle;
            texEntry.buffer      = wgpuDefaultHandle;
            _textureIdxMap.insert(std::make_pair<uint8_t, uint8_t>(_gpuBindGroupObj->bindGroupEntries.size() - 1, i));
            dsLayout->updateTextureLayout(texEntry.binding, texture);

            // 2. sampler
            CCWGPUSampler* sampler = deviceObj->defaultResources.sampler;
            _gpuBindGroupObj->bindGroupEntries.push_back(WGPUBindGroupEntry());
            auto&& smpEntry      = _gpuBindGroupObj->bindGroupEntries[i];
            smpEntry.binding     = bindings[i].binding + CC_WGPU_MAX_ATTACHMENTS;
            smpEntry.sampler     = sampler->gpuSampler();
            smpEntry.textureView = wgpuDefaultHandle;
            smpEntry.buffer      = wgpuDefaultHandle;
            _samplerIdxMap.insert(std::make_pair<uint8_t, uint8_t>(_gpuBindGroupObj->bindGroupEntries.size() - 1, i));
        } else if (hasFlag(DESCRIPTOR_BUFFER_TYPE, bindings[i].descriptorType)) {
            CCWGPUBuffer* buffer = deviceObj->defaultResources.buffer;
            _gpuBindGroupObj->bindGroupEntries.push_back(WGPUBindGroupEntry());
            auto&& entry      = _gpuBindGroupObj->bindGroupEntries[i];
            entry.binding     = bindings[i].binding;
            entry.buffer      = buffer->gpuBufferObject()->wgpuBuffer;
            entry.sampler     = wgpuDefaultHandle;
            entry.textureView = wgpuDefaultHandle;
            entry.size        = buffer->getSize();
            entry.offset      = buffer->getOffset();
        }
    }
    dsLayout->prepare();
}

void CCWGPUDescriptorSet::doDestroy() {
    CC_DELETE(_gpuBindGroupObj);
}

void CCWGPUDescriptorSet::update() {
    if (!_isDirty || !_layout) {
        return;
    }

    auto*       dsLayout = static_cast<CCWGPUDescriptorSetLayout*>(_layout);
    const auto& bindings = dsLayout->getBindings();

    for (size_t i = 0; i < _gpuBindGroupObj->bindGroupEntries.size(); i++) {
        auto&& bindGroupEntry = _gpuBindGroupObj->bindGroupEntries[i];
        if (_gpuBindGroupObj->bindGroupEntries[i].buffer != wgpuDefaultHandle && _buffers[i]) {
            auto&& buffer          = static_cast<CCWGPUBuffer*>(_buffers[i]);
            bindGroupEntry.binding = bindings[i].binding;
            bindGroupEntry.buffer  = buffer->gpuBufferObject()->wgpuBuffer;
            bindGroupEntry.offset  = buffer->getOffset();
            bindGroupEntry.size    = buffer->getSize();
        } else if (_gpuBindGroupObj->bindGroupEntries[i].textureView != wgpuDefaultHandle && _textures[i]) {
            auto iter = _textureIdxMap.find(i);
            if (iter != _textureIdxMap.end()) {
                uint8_t textureIdx         = iter->second;
                auto&&  texture            = static_cast<CCWGPUTexture*>(_textures[textureIdx]);
                bindGroupEntry.binding     = bindings[textureIdx].binding;
                bindGroupEntry.textureView = texture->gpuTextureObject()->selfView;
            }
        } else if (_gpuBindGroupObj->bindGroupEntries[i].sampler != wgpuDefaultHandle && _samplers[i]) {
            auto iter = _samplerIdxMap.find(i);
            if (iter != _samplerIdxMap.end()) {
                uint8_t samplerIdx     = iter->second;
                auto&&  sampler        = static_cast<CCWGPUSampler*>(_samplers[samplerIdx]);
                bindGroupEntry.binding = bindings[samplerIdx].binding + CC_WGPU_MAX_ATTACHMENTS;
                bindGroupEntry.sampler = sampler->gpuSampler();
            }
        }

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
        _gpuBindGroupObj->bindgroup = wgpuDeviceCreateBindGroup(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &bindGroupDesc);
    }
}

} // namespace gfx
} // namespace cc