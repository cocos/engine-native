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
#include "WGPUDevice.h"
#include "WGPUObject.h"
#include "WGPUTexture.h"
#include "WGPUUtils.h"
namespace cc {
namespace gfx {

using namespace emscripten;

CCWGPUDescriptorSetLayout::CCWGPUDescriptorSetLayout() : wrapper<DescriptorSetLayout>(val::object()) {
}

void CCWGPUDescriptorSetLayout::doInit(const DescriptorSetLayoutInfo& info) {
    _gpuLayoutEntryObj = CC_NEW(CCWGPUBindGroupLayoutObject);
    for (size_t i = 0; i < _bindings.size(); i++) {
        _gpuLayoutEntryObj->bindGroupLayoutEntries.push_back(WGPUBindGroupLayoutEntry());
        WGPUBindGroupLayoutEntry& layoutEntry = _gpuLayoutEntryObj->bindGroupLayoutEntries[i];
        layoutEntry.binding                   = _bindings[i].binding;
        layoutEntry.visibility                = toWGPUShaderStageFlag(_bindings[i].stageFlags);
        switch (_bindings[i].descriptorType) {
            case DescriptorType::UNIFORM_BUFFER:
                layoutEntry.buffer = {nullptr, WGPUBufferBindingType::WGPUBufferBindingType_Uniform, false, 0};
                break;
            case DescriptorType::DYNAMIC_UNIFORM_BUFFER:
                layoutEntry.buffer = {nullptr, WGPUBufferBindingType::WGPUBufferBindingType_Uniform, true, 0};
                break;
            case DescriptorType::STORAGE_BUFFER:
                layoutEntry.buffer = {nullptr, WGPUBufferBindingType::WGPUBufferBindingType_Storage, false, 0};
                break;
            case DescriptorType::DYNAMIC_STORAGE_BUFFER:
                layoutEntry.buffer = {nullptr, WGPUBufferBindingType::WGPUBufferBindingType_Storage, true, 0};
                break;
            case DescriptorType::SAMPLER_TEXTURE: {
                // combined sampler texture.
                WGPUBindGroupLayoutEntry layoutEntrySampler = _gpuLayoutEntryObj->bindGroupLayoutEntries[i];
                layoutEntrySampler.binding                  = _bindings[i].binding + CC_WGPU_MAX_ATTACHMENTS;
                _gpuLayoutEntryObj->bindGroupLayoutEntries.push_back(layoutEntrySampler);
            } break;
            case DescriptorType::SAMPLER:
                layoutEntry.sampler = {nullptr, WGPUSamplerBindingType::WGPUSamplerBindingType_Filtering};
                break;
            case DescriptorType::STORAGE_IMAGE:
                break; // not enough information, reserved.
            case DescriptorType::TEXTURE:
                break; // not enough information, reserved.
            case DescriptorType::INPUT_ATTACHMENT:
                break; // not enough information, reserved.
            default:
                break;
        }
    }
}

void CCWGPUDescriptorSetLayout::updateTextureLayout(uint8_t binding, const CCWGPUTexture* tex) {
    auto iter = std::find_if(_gpuLayoutEntryObj->bindGroupLayoutEntries.begin(), _gpuLayoutEntryObj->bindGroupLayoutEntries.end(), [binding](const WGPUBindGroupLayoutEntry& entry) {
        return entry.binding == binding;
    });

    if (iter != _gpuLayoutEntryObj->bindGroupLayoutEntries.end()) {
        if (tex->getInfo().usage == TextureUsageBit::STORAGE) {
            (*iter).storageTexture.nextInChain   = nullptr;
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

void CCWGPUDescriptorSetLayout::prepare() {
    WGPUBindGroupLayoutDescriptor descriptor = {
        .nextInChain = nullptr,
        .label       = nullptr,
        .entryCount  = _gpuLayoutEntryObj->bindGroupLayoutEntries.size(),
        .entries     = _gpuLayoutEntryObj->bindGroupLayoutEntries.data(),
    };

    if (_gpuLayoutEntryObj->bindGroupLayout) {
        wgpuBindGroupLayoutRelease(_gpuLayoutEntryObj->bindGroupLayout);
    }
    _gpuLayoutEntryObj->bindGroupLayout = wgpuDeviceCreateBindGroupLayout(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &descriptor);
}

void CCWGPUDescriptorSetLayout::doDestroy() {
    CC_DELETE(_gpuLayoutEntryObj);
}

} // namespace gfx
} // namespace cc