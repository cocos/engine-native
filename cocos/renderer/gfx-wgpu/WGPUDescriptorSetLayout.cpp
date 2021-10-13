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

#include "WGPUDescriptorSetLayout.h"
#include <emscripten/html5_webgpu.h>
#include <algorithm>
#include "WGPUBuffer.h"
#include "WGPUDevice.h"
#include "WGPUObject.h"
#include "WGPUSampler.h"
#include "WGPUTexture.h"
#include "WGPUUtils.h"

namespace cc {
namespace gfx {

namespace anoymous {
WGPUBindGroupLayout defaultBindgroupLayout = wgpuDefaultHandle;
}

using namespace emscripten;

CCWGPUDescriptorSetLayout::CCWGPUDescriptorSetLayout() : wrapper<DescriptorSetLayout>(val::object()) {
}

void CCWGPUDescriptorSetLayout::doInit(const DescriptorSetLayoutInfo& info) {
    _gpuLayoutEntryObj = CC_NEW(CCWGPUBindGroupLayoutObject);
    for (size_t i = 0; i < _bindings.size(); i++) {
        if (_bindings[i].descriptorType == DescriptorType::UNKNOWN)
            continue;
        if (_bindings[i].descriptorType == DescriptorType::SAMPLER_TEXTURE) {
            // 1. texture
            WGPUBindGroupLayoutEntry textureLayout = {
                .nextInChain        = nullptr,
                .binding            = _bindings[i].binding,
                .visibility         = toWGPUShaderStageFlag(_bindings[i].stageFlags),
                .texture.sampleType = WGPUTextureSampleType_Uint,

            };
            _gpuLayoutEntryObj->bindGroupLayoutEntries.push_back(textureLayout);

            // 2. sampler
            WGPUBindGroupLayoutEntry samplerLayout = {
                .nextInChain  = nullptr,
                .binding      = _bindings[i].binding + CC_WGPU_MAX_ATTACHMENTS,
                .visibility   = toWGPUShaderStageFlag(_bindings[i].stageFlags),
                .sampler.type = WGPUSamplerBindingType_Comparison,
            };
            _gpuLayoutEntryObj->bindGroupLayoutEntries.push_back(samplerLayout);
        } else if (hasFlag(DESCRIPTOR_BUFFER_TYPE, _bindings[i].descriptorType)) {
            if (hasFlag(_bindings[i].descriptorType, DescriptorType::STORAGE_BUFFER | DescriptorType::DYNAMIC_STORAGE_BUFFER)) {
                WGPUBindGroupLayoutEntry layout = {
                    .nextInChain = nullptr,
                    .binding     = _bindings[i].binding,
                    .visibility  = toWGPUShaderStageFlag(_bindings[i].stageFlags),
                    .buffer      = {nullptr, WGPUBufferBindingType::WGPUBufferBindingType_Storage, false, 0},
                };
                _gpuLayoutEntryObj->bindGroupLayoutEntries.push_back(layout);
            } else if (hasFlag(_bindings[i].descriptorType, DescriptorType::UNIFORM_BUFFER | DescriptorType::DYNAMIC_UNIFORM_BUFFER)) {
                WGPUBindGroupLayoutEntry layout = {
                    .nextInChain = nullptr,
                    .binding     = _bindings[i].binding,
                    .visibility  = toWGPUShaderStageFlag(_bindings[i].stageFlags),
                    .buffer      = {nullptr, WGPUBufferBindingType::WGPUBufferBindingType_Uniform, false, 0},
                };
                _gpuLayoutEntryObj->bindGroupLayoutEntries.push_back(layout);
            } else {
                CC_LOG_ERROR("unsupport buffer descriptor type.");
            }
        } else if (_bindings[i].descriptorType == DescriptorType::SAMPLER) {
            WGPUBindGroupLayoutEntry layout = {
                .nextInChain = nullptr,
                .binding     = _bindings[i].binding,
                .visibility  = toWGPUShaderStageFlag(_bindings[i].stageFlags),
                .sampler     = {nullptr, WGPUSamplerBindingType::WGPUSamplerBindingType_Comparison},
            };
            _gpuLayoutEntryObj->bindGroupLayoutEntries.push_back(layout);
        } else {
            WGPUBindGroupLayoutEntry layout = {
                .nextInChain = nullptr,
                .binding     = _bindings[i].binding,
                .visibility  = toWGPUShaderStageFlag(_bindings[i].stageFlags),
            };
            _gpuLayoutEntryObj->bindGroupLayoutEntries.push_back(layout);
        }
    }
    (void)defaultBindGroupLayout();
}

void CCWGPUDescriptorSetLayout::updateLayout(uint8_t binding, const CCWGPUBuffer* buffer, const CCWGPUTexture* tex, const CCWGPUSampler* sampler) {
    auto iter = std::find_if(_gpuLayoutEntryObj->bindGroupLayoutEntries.begin(), _gpuLayoutEntryObj->bindGroupLayoutEntries.end(), [binding](const WGPUBindGroupLayoutEntry& entry) {
        return entry.binding == binding;
    });

    if (iter != _gpuLayoutEntryObj->bindGroupLayoutEntries.end()) {
        if (buffer) {
            if (buffer->hasDynamicOffset()) {
                (*iter).buffer.hasDynamicOffset = true;
            } else {
                (*iter).buffer.hasDynamicOffset = false;
            }
        }
        if (sampler) {
            const SamplerInfo& info = sampler->getInfo();
            if (info.minFilter != Filter::LINEAR && info.magFilter != Filter::LINEAR && info.mipFilter != Filter::LINEAR)
                (*iter).sampler.type = WGPUSamplerBindingType::WGPUSamplerBindingType_NonFiltering;
            else
                (*iter).sampler.type = WGPUSamplerBindingType::WGPUSamplerBindingType_Filtering;
        }
        if (tex) {
            if (tex->getInfo().usage == TextureUsageBit::STORAGE) {
                (*iter).storageTexture.nextInChain   = nullptr;
                (*iter).storageTexture.access        = WGPUStorageTextureAccess::WGPUStorageTextureAccess_Force32;
                (*iter).storageTexture.format        = toWGPUTextureFormat(tex->getFormat());
                TextureType type                     = tex->isTextureView() ? tex->getViewInfo().type : tex->getInfo().type;
                (*iter).storageTexture.viewDimension = toWGPUTextureViewDimension(type);
            } else {
                (*iter).texture.nextInChain   = nullptr;
                (*iter).texture.sampleType    = textureSampleTypeTrait(tex->getFormat());
                const CCWGPUTexture* ccTex    = static_cast<const CCWGPUTexture*>(tex->isTextureView() ? tex->getViewInfo().texture : tex);
                TextureType          type     = ccTex->getViewInfo().type;
                (*iter).texture.viewDimension = toWGPUTextureViewDimension(type);
                (*iter).texture.multisampled  = ccTex->getInfo().samples != SampleCount::ONE;
            }
        }
    }
}

void CCWGPUDescriptorSetLayout::prepare(const std::set<uint8_t>& bindingInUse) {
    if (_gpuLayoutEntryObj->bindGroupLayout) {
        return;
    }
    std::vector<WGPUBindGroupLayoutEntry> bindGroupLayoutEntries;

    bindGroupLayoutEntries.assign(_gpuLayoutEntryObj->bindGroupLayoutEntries.begin(), _gpuLayoutEntryObj->bindGroupLayoutEntries.end());
    // bindGroupLayoutEntries.erase(std::remove_if(
    //                                  bindGroupLayoutEntries.begin(), bindGroupLayoutEntries.end(), [&bindingInUse, &bindGroupLayoutEntries](const WGPUBindGroupLayoutEntry& entry) {
    //                                      return bindingInUse.find(entry.binding) == bindingInUse.end();
    //                                  }),
    //                              bindGroupLayoutEntries.end());

    if (_gpuLayoutEntryObj->bindGroupLayout && _gpuLayoutEntryObj->bindGroupLayout != anoymous::defaultBindgroupLayout) {
        wgpuBindGroupLayoutRelease(_gpuLayoutEntryObj->bindGroupLayout);
    }

    if (bindGroupLayoutEntries.empty()) {
        _gpuLayoutEntryObj->bindGroupLayout = anoymous::defaultBindgroupLayout;
    } else {
        WGPUBindGroupLayoutDescriptor descriptor = {
            .nextInChain = nullptr,
            .label       = nullptr,
            .entryCount  = bindGroupLayoutEntries.size(),
            .entries     = bindGroupLayoutEntries.data(),
        };
        _gpuLayoutEntryObj->bindGroupLayout = wgpuDeviceCreateBindGroupLayout(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &descriptor);
    }
}

void* CCWGPUDescriptorSetLayout::defaultBindGroupLayout() {
    if (!anoymous::defaultBindgroupLayout) {
        // default bindgroupLayout: for empty set
        WGPUBindGroupLayoutEntry layout = {
            .nextInChain = nullptr,
            .binding     = 0,
            .visibility  = WGPUShaderStage_Vertex | WGPUShaderStage_Fragment | WGPUShaderStage_Compute,
            .buffer      = {nullptr, WGPUBufferBindingType::WGPUBufferBindingType_Uniform, false, 0},
        };

        WGPUBindGroupLayoutDescriptor descriptor = {
            .nextInChain = nullptr,
            .label       = nullptr,
            .entryCount  = 1,
            .entries     = &layout,
        };
        anoymous::defaultBindgroupLayout = wgpuDeviceCreateBindGroupLayout(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &descriptor);
    }
    return anoymous::defaultBindgroupLayout;
}

void CCWGPUDescriptorSetLayout::doDestroy() {
    CC_DELETE(_gpuLayoutEntryObj);
}

} // namespace gfx
} // namespace cc