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

#include "WGPUPipelineLayout.h"
#include <emscripten/html5_webgpu.h>
#include "WGPUDescriptorSetLayout.h"
#include "WGPUDevice.h"
#include "WGPUObject.h"

namespace cc {
namespace gfx {

using namespace emscripten;

CCWGPUPipelineLayout::CCWGPUPipelineLayout() : wrapper<PipelineLayout>(val::object()) {
}

void CCWGPUPipelineLayout::doInit(const PipelineLayoutInfo& info) {
    _gpuPipelineLayoutObj = CC_NEW(CCWGPUPipelineLayoutObject);
}

void CCWGPUPipelineLayout::prepare() {
    std::vector<WGPUBindGroupLayout> layouts;
    for (size_t i = 0; i < _setLayouts.size(); i++) {
        auto* descriptorSetLayout = static_cast<CCWGPUDescriptorSetLayout*>(_setLayouts[i]);
        // const auto& bindGroupLayoutEntries = descriptorSetLayout->gpuLayoutEntryObject()->bindGroupLayoutEntries;
        // for (size_t j = 0; j < bindGroupLayoutEntries.size(); j++) {
        //     // const auto &entryLayout = layout->gpuLayoutEntryObject()->bindGroupLayoutEntries[j];
        //     // printf("set, binding, b, t, s %d, %d, %p, %p, %p\n", i, entry.binding, entry.buffer, entry.textureView, entry.sampler);
        //     const auto& entry = bindGroupLayoutEntries[j];
        //     if ((entry.buffer.type != WGPUBufferBindingType_Undefined) +
        //             (entry.sampler.type != WGPUSamplerBindingType_Undefined) +
        //             (entry.texture.sampleType != WGPUTextureSampleType_Undefined) +
        //             (entry.storageTexture.access != WGPUStorageTextureAccess_Undefined) !=
        //         1) {
        //         printf("******missing %d, %d, %d, %d, %d\n", entry.binding, entry.buffer.type, entry.sampler.type, entry.texture.sampleType, entry.storageTexture.access);
        //     }
        //     printf("l binding, b, t, s  %d, %d, %d, %d, %d\n", entry.binding, entry.buffer.type, entry.sampler.type, entry.texture.sampleType, entry.storageTexture.access);
        // }

        if (!descriptorSetLayout->gpuLayoutEntryObject()->bindGroupLayout) {
            descriptorSetLayout->prepare({});
        }
        layouts.push_back(descriptorSetLayout->gpuLayoutEntryObject()->bindGroupLayout);
    }

    WGPUPipelineLayoutDescriptor descriptor = {
        .nextInChain          = nullptr,
        .label                = nullptr,
        .bindGroupLayoutCount = layouts.size(),
        .bindGroupLayouts     = layouts.data(),
    };

    // for (size_t i = 0; i < descriptor.bindGroupLayoutCount; i++) {
    //     auto* descriptorSetLayout = static_cast<CCWGPUDescriptorSetLayout*>(info.setLayouts[i]);
    //     for (size_t j = 0; j < descriptorSetLayout->gpuLayoutEntryObject()->bindGroupLayoutEntries.size(); j++) {
    //         printf("set, idx, bd, buf, tex, spl, tv %d, %d, %d\n", i, j,
    //                descriptorSetLayout->gpuLayoutEntryObject()->bindGroupLayoutEntries[j].binding);
    //     }
    // }

    _gpuPipelineLayoutObj->wgpuPipelineLayout = wgpuDeviceCreatePipelineLayout(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &descriptor);
}

void CCWGPUPipelineLayout::doDestroy() {
    if (_gpuPipelineLayoutObj) {
        if (_gpuPipelineLayoutObj->wgpuPipelineLayout) {
            wgpuPipelineLayoutRelease(_gpuPipelineLayoutObj->wgpuPipelineLayout);
        }
        CC_DELETE(_gpuPipelineLayoutObj);
    }
}

} // namespace gfx
} // namespace cc