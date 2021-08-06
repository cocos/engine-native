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

#include "WGPUContext.h"
#include "WGPUObject.h"

namespace cc {
namespace gfx {

CCWGPUContext::CCWGPUContext(CCWGPUDevice* device) {
    _device = device;
}

CCWGPUContext::~CCWGPUContext() {
    _device = nullptr;
}

void CCWGPUContext::present() {
}

bool CCWGPUContext::doInit(const ContextInfo& info) {
    WGPUChainedStruct chainedStruct;
    chainedStruct.next  = nullptr;
    chainedStruct.sType = WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector;

    WGPUSurfaceDescriptor surfDesc;
    surfDesc.nextInChain = &chainedStruct;
    surfDesc.label       = "defaultSurfaceDesc";

    WGPUSurface surface = wgpuInstanceCreateSurface(nullptr, &surfDesc);

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

    WGPUSwapChainDescriptor swapChainDesc;
    swapChainDesc.nextInChain = nullptr;
    swapChainDesc.label       = "defaultSwapChain";
    swapChainDesc.usage       = WGPUTextureUsage_RenderAttachment;
    swapChainDesc.format      = WGPUTextureFormat_BGRA8Unorm;
    swapChainDesc.width       = _device->getWidth();
    swapChainDesc.height      = _device->getHeight();
    swapChainDesc.presentMode = presentMode;

    CCWGPUDeviceObject* gpuDeviceObj = static_cast<CCWGPUDevice*>(_device)->gpuDeviceObject();
    WGPUSwapChain       swapChain    = wgpuDeviceCreateSwapChain(gpuDeviceObj->wgpuDevice, surface, &swapChainDesc);

    _gpuContextObj                = CC_NEW(CCWGPUContextObject);
    _gpuContextObj->wgpuSwapChain = swapChain;
    _gpuContextObj->wgpuSurface   = surface;

    return true;
}

void CCWGPUContext::doDestroy() {
    wgpuSurfaceRelease(_gpuContextObj->wgpuSurface);
    wgpuSwapChainRelease(_gpuContextObj->wgpuSwapChain);

    CC_DELETE(_gpuContextObj);
}

} // namespace gfx
} // namespace cc