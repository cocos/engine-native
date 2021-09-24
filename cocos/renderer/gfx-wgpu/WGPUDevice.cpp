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

#include "WGPUDevice.h"
#include <emscripten/val.h>
#include "WGPUBuffer.h"
#include "WGPUCommandBuffer.h"
#include "WGPUDescriptorSet.h"
#include "WGPUDescriptorSetLayout.h"
#include "WGPUDevice.h"
#include "WGPUExports.h"
#include "WGPUFrameBuffer.h"
#include "WGPUObject.h"
#include "WGPUPipelineLayout.h"
#include "WGPUPipelineState.h"
#include "WGPUQueue.h"
#include "WGPURenderPass.h"
#include "WGPUSampler.h"
#include "WGPUShader.h"
#include "WGPUSwapchain.h"
#include "WGPUUtils.h"

namespace cc {

namespace gfx {

CCWGPUDevice* CCWGPUDevice::instance = nullptr;

CCWGPUDevice* CCWGPUDevice::getInstance() {
    // if JS
    if (!instance) {
        instance = new CCWGPUDevice();
    }
    // endif
    return instance;
}

CCWGPUDevice::CCWGPUDevice() : wrapper<Device>(val::object()) {
    _api                   = API::WEBGPU;
    _deviceName            = "WebGPU";
    _caps.clipSpaceMinZ    = 0.0F;
    _caps.screenSpaceSignY = -1.0F;
    _caps.clipSpaceSignY   = -1.0F;
    instance               = this;
}

CCWGPUDevice::~CCWGPUDevice() {
    instance = nullptr;
    CC_DELETE(_gpuDeviceObj);
    delete this;
}

bool CCWGPUDevice::doInit(const DeviceInfo& info) {
    _gpuDeviceObj                           = CC_NEW(CCWGPUDeviceObject);
    _gpuDeviceObj->wgpuDevice               = emscripten_webgpu_get_device();
    _gpuDeviceObj->wgpuQueue                = wgpuDeviceGetQueue(_gpuDeviceObj->wgpuDevice);
    _gpuDeviceObj->defaultResources.texture = CCWGPUTexture::defaultTexture();
    _gpuDeviceObj->defaultResources.buffer  = CCWGPUBuffer::defaultBuffer();
    _gpuDeviceObj->defaultResources.sampler = CCWGPUSampler::defaultSampler();

    QueueInfo queueInfo = {
        .type = QueueType::GRAPHICS,
    };
    _queue = this->Device::createQueue(queueInfo);

    CommandBufferInfo cmdInfo = {
        .queue = _queue,
        .type  = CommandBufferType::PRIMARY,
    };
    _cmdBuff = this->Device::createCommandBuffer(cmdInfo);
    return true;
}

void CCWGPUDevice::doDestroy() {
}

Swapchain* CCWGPUDevice::createSwapchain() {
    return new CCWGPUSwapchain(this);
}

Queue* CCWGPUDevice::createQueue() {
    return CC_NEW(CCWGPUQueue);
}

Buffer* CCWGPUDevice::createBuffer() {
    return CC_NEW(CCWGPUBuffer);
}

Texture* CCWGPUDevice::createTexture() {
    return CC_NEW(CCWGPUTexture);
}

Shader* CCWGPUDevice::createShader() {
    return CC_NEW(CCWGPUShader);
}

InputAssembler* CCWGPUDevice::createInputAssembler() {
    return CC_NEW(CCWGPUInputAssembler);
}

RenderPass* CCWGPUDevice::createRenderPass() {
    return CC_NEW(CCWGPURenderPass);
}

Framebuffer* CCWGPUDevice::createFramebuffer() {
    return CC_NEW(CCWGPUFramebuffer);
}

DescriptorSet* CCWGPUDevice::createDescriptorSet() {
    return CC_NEW(CCWGPUDescriptorSet);
}

DescriptorSetLayout* CCWGPUDevice::createDescriptorSetLayout() {
    return CC_NEW(CCWGPUDescriptorSetLayout);
}

PipelineLayout* CCWGPUDevice::createPipelineLayout() {
    return CC_NEW(CCWGPUPipelineLayout);
}

PipelineState* CCWGPUDevice::createPipelineState() {
    return CC_NEW(CCWGPUPipelineState);
}

CommandBuffer* CCWGPUDevice::createCommandBuffer(const CommandBufferInfo& info, bool hasAgent) {
    return CC_NEW(CCWGPUCommandBuffer);
}

void CCWGPUDevice::copyBuffersToTexture(const uint8_t* const* buffers, Texture* dst, const BufferTextureCopy* regions, uint count) {
}

void CCWGPUDevice::copyTextureToBuffers(Texture* src, uint8_t* const* buffers, const BufferTextureCopy* region, uint count) {
}

void CCWGPUDevice::acquire(Swapchain* const* swapchains, uint32_t count) {
    for (auto* swapchain : _swapchains) {
        swapchain->update();
    }
}

Shader* CCWGPUDevice::createShader(const SPVShaderInfoInstance& info) {
    CCWGPUShader* shader = CC_NEW(CCWGPUShader);
    shader->initialize(info);
    return shader;
}

void CCWGPUDevice::present() {
}

GlobalBarrier* CCWGPUDevice::createGlobalBarrier(const GlobalBarrierInfo& info) {
}

TextureBarrier* CCWGPUDevice::createTextureBarrier(const TextureBarrierInfo& info) {
}

Sampler* CCWGPUDevice::createSampler(const SamplerInfo& info) {
    return new CCWGPUSampler(info);
}

void CCWGPUDevice::debug() {
    auto wgpuCommandEncoder = wgpuDeviceCreateCommandEncoder(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, nullptr);
    auto wgpuCommandBuffer  = wgpuCommandEncoderFinish(wgpuCommandEncoder, nullptr);
    wgpuQueueSubmit(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuQueue, 1, &wgpuCommandBuffer);
}

} // namespace gfx

} // namespace cc