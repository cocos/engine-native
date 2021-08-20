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
#include "WGPUContext.h"
#include "WGPUExports.h"
#include "WGPUObject.h"
#include "WGPURenderPass.h"
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
}

bool CCWGPUDevice::doInit(const DeviceInfo& info) {
    _gpuDeviceObj             = CC_NEW(CCWGPUDeviceObject);
    _gpuDeviceObj->wgpuDevice = emscripten_webgpu_get_device();
    _gpuDeviceObj->wgpuQueue  = wgpuDeviceGetQueue(_gpuDeviceObj->wgpuDevice);
    _context                  = CC_NEW(CCWGPUContext(this));
    ContextInfo ctxInfo;
    ctxInfo.msaaEnabled = info.isAntiAlias;
    ctxInfo.performance = Performance::HIGH_QUALITY;
    if (!_context->initialize(ctxInfo)) {
        destroy();
        return false;
    }
    return true;
}

void CCWGPUDevice::doDestroy() {
}

Queue* CCWGPUDevice::createQueue() {
    return nullptr;
}

Buffer* CCWGPUDevice::createBuffer() {
    return nullptr;
}

Texture* CCWGPUDevice::createTexture() {
    return nullptr;
}

Sampler* CCWGPUDevice::createSampler() {
    return nullptr;
}

Shader* CCWGPUDevice::createShader() {
    return nullptr;
}

InputAssembler* CCWGPUDevice::createInputAssembler() {
    return nullptr;
}

RenderPass* CCWGPUDevice::createRenderPass() {
    return CC_NEW(CCWGPURenderPass);
}

Framebuffer* CCWGPUDevice::createFramebuffer() {
    return nullptr;
}

DescriptorSet* CCWGPUDevice::createDescriptorSet() {
    return nullptr;
}

DescriptorSetLayout* CCWGPUDevice::createDescriptorSetLayout() {
    return nullptr;
}

PipelineLayout* CCWGPUDevice::createPipelineLayout() {
    return nullptr;
}

PipelineState* CCWGPUDevice::createPipelineState() {
    return nullptr;
}

GlobalBarrier* CCWGPUDevice::createGlobalBarrier() {
    return nullptr;
}

TextureBarrier* CCWGPUDevice::createTextureBarrier() {
    return nullptr;
}

void CCWGPUDevice::acquireSurface(uintptr_t window) {
}

void CCWGPUDevice::releaseSurface(uintptr_t window) {
}

CommandBuffer* CCWGPUDevice::createCommandBuffer(const CommandBufferInfo& info, bool hasAgent) {
    return nullptr;
}

void CCWGPUDevice::copyBuffersToTexture(const uint8_t* const* buffers, Texture* dst, const BufferTextureCopy* regions, uint count) {
}

void CCWGPUDevice::copyTextureToBuffers(Texture* src, uint8_t* const* buffers, const BufferTextureCopy* region, uint count) {
}

void CCWGPUDevice::resize(uint32_t width, uint32_t height) {
}

void CCWGPUDevice::acquire() {
}

void CCWGPUDevice::present() {
}

} // namespace gfx

} // namespace cc