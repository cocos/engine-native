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

#include "WGPUSwapchain.h"
#include "WGPUDevice.h"
#include "WGPUObject.h"

namespace cc {
namespace gfx {

CCWGPUSwapchain::CCWGPUSwapchain(CCWGPUDevice* device) {
    _device = device;
}

CCWGPUSwapchain::~CCWGPUSwapchain() {
    _device = nullptr;
}

void CCWGPUSwapchain::present() {
}

bool CCWGPUSwapchain::doInit(const ContextInfo& info) {
    WGPUSurfaceDescriptorFromCanvasHTMLSelector canvDesc = {};
    canvDesc.chain.sType                                 = WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector;
    canvDesc.selector                                    = "canvas";

    WGPUSurfaceDescriptor surfDesc = {};
    surfDesc.nextInChain           = reinterpret_cast<WGPUChainedStruct*>(&canvDesc);
    WGPUSurface surface            = wgpuInstanceCreateSurface(nullptr, &surfDesc);

    WGPUPresentMode presentMode;
    switch (info.vsyncMode) {
        case VsyncMode::OFF:
            presentMode = WGPUPresentMode_Immediate;
            break;
        case VsyncMode::ON:
            presentMode = WGPUPresentMode_Fifo;
            break;
        case VsyncMode::RELAXED:
            presentMode = WGPUPresentMode_Fifo;
            break;
        case VsyncMode::MAILBOX:
            presentMode = WGPUPresentMode_Mailbox;
            break;
        case VsyncMode::HALF:
            presentMode = WGPUPresentMode_Force32;
            break;
    }

    const auto*             device = CCWGPUDevice::getInstance();
    WGPUSwapChainDescriptor swapChainDesc;
    swapChainDesc.nextInChain = nullptr;
    swapChainDesc.label       = "defaultSwapChain";
    swapChainDesc.usage       = WGPUTextureUsage_RenderAttachment;
    swapChainDesc.format      = WGPUTextureFormat_BGRA8Unorm;
    swapChainDesc.width       = device->getWidth();
    swapChainDesc.height      = device->getHeight();
    swapChainDesc.presentMode = presentMode;

    CCWGPUDeviceObject* gpuDeviceObj = device->gpuDeviceObject();
    WGPUSwapChain       swapChain    = wgpuDeviceCreateSwapChain(gpuDeviceObj->wgpuDevice, surface, &swapChainDesc);

    _gpuSwapchainObj                = CC_NEW(CCWGPUSwapchainObject);
    _gpuSwapchainObj->wgpuSwapChain = swapChain;
    _gpuSwapchainObj->wgpuSurface   = surface;

    // TextureType  type       = TextureType::TEX2D;
    // TextureUsage usage      = TextureUsageBit::NONE;
    // Format       format     = Format::UNKNOWN;
    // uint         width      = 0U;
    // uint         height     = 0U;
    // TextureFlags flags      = TextureFlagBit::NONE;
    // uint         layerCount = 1U;
    // uint         levelCount = 1U;
    // SampleCount  samples    = SampleCount::X1;
    // uint         depth      = 1U;
    // uint         swapchain  = 0; // 0: none, 1: yes
    TextureInfo info{
        .type      = TextureType::TEX2D,
        .usage     = TextureUsageBit::COLOR_ATTACHMENT,
        .width     = device->getWidth(),
        .height    = device->getHeight(),
        .swapchain = 1,
    };
    _gpuSwapchainObj->swapchainColor = static_cast<CCWGPUTexture*>(device->createTexture(info));

    info.usage = TextureUsageBit::DEPTH_STENCIL_ATTACHMENT;

    _gpuSwapchainObj->swapchainDepthStencil = static_cast<CCWGPUTexture*>(device->createTexture(info));
    // TODO: wgpuInstance
    return true;
}

void CCWGPUSwapchain::doDestroy() {
    // wgpuSurfaceRelease(_gpuSwapchainObj->wgpuSurface);
    // wgpuSwapChainRelease(_gpuSwapchainObj->wgpuSwapChain);

    CC_DELETE(_gpuSwapchainObj);
}

} // namespace gfx
} // namespace cc