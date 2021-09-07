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

#pragma once

#if (CC_PLATFORM == CC_PLATFORM_WINDOWS)
    #include <windows.h>
#endif

#include <emscripten/bind.h>
#include "WGPUDef.h"
#include "gfx-base/GFXDevice.h"

namespace cc {
namespace gfx {

struct CCWGPUDeviceObject;

class CCWGPUSwapchain;
class CCWGPUTexture;

using namespace emscripten;

class CCWGPUDevice final : public wrapper<Device> {
public:
    EMSCRIPTEN_WRAPPER(CCWGPUDevice);

    static CCWGPUDevice *getInstance();

    ~CCWGPUDevice();

    void acquire(Swapchain *const *swapchains, uint32_t count) override;
    void present() override;

    using Device::copyBuffersToTexture;
    using Device::createBuffer;
    using Device::createCommandBuffer;
    using Device::createDescriptorSet;
    using Device::createDescriptorSetLayout;
    using Device::createFramebuffer;
    using Device::createGlobalBarrier;
    using Device::createInputAssembler;
    using Device::createPipelineLayout;
    using Device::createPipelineState;
    using Device::createQueue;
    using Device::createRenderPass;
    using Device::createSampler;
    using Device::createShader;
    using Device::createTexture;
    using Device::createTextureBarrier;

    inline CCWGPUDeviceObject *gpuDeviceObject() { return _gpuDeviceObj; }

    inline void registerSwapchain(CCWGPUSwapchain *swapchain) { _swapchains.push_back(swapchain); }
    inline void unRegisterSwapchain(CCWGPUSwapchain *swapchain) {
        auto iter = std::find(_swapchains.begin(), _swapchains.end(), swapchain);
        if (iter != _swapchains.end()) {
            _swapchains.erase(iter);
        }
    }

    // ems export override
    Swapchain *createSwapchain(const SwapchainInfoInstance &info) {
        return this->Device::createSwapchain(static_cast<const SwapchainInfo &>(info));
    }

    Framebuffer *createFramebuffer(const FramebufferInfoInstance &info) {
        return this->Device::createFramebuffer(static_cast<const FramebufferInfo &>(info));
    }

    Texture *createTexture(const TextureInfoInstance &info) {
        return this->Device::createTexture(static_cast<const TextureInfo &>(info));
    }

    Texture *createTexture(const TextureViewInfoInstance &info) {
        return this->Device::createTexture(static_cast<const TextureViewInfo &>(info));
    }

protected:
    static CCWGPUDevice *instance;

    CCWGPUDevice();

    bool                 doInit(const DeviceInfo &info) override;
    void                 doDestroy() override;
    CommandBuffer *      createCommandBuffer(const CommandBufferInfo &info, bool hasAgent) override;
    Queue *              createQueue() override;
    Buffer *             createBuffer() override;
    Texture *            createTexture() override;
    Shader *             createShader() override;
    InputAssembler *     createInputAssembler() override;
    RenderPass *         createRenderPass() override;
    Framebuffer *        createFramebuffer() override;
    DescriptorSet *      createDescriptorSet() override;
    DescriptorSetLayout *createDescriptorSetLayout() override;
    PipelineLayout *     createPipelineLayout() override;
    PipelineState *      createPipelineState() override;
    GlobalBarrier *      createGlobalBarrier(const GlobalBarrierInfo &info) override;
    TextureBarrier *     createTextureBarrier(const TextureBarrierInfo &info) override;
    Sampler *            createSampler(const SamplerInfo &info) override;
    Swapchain *          createSwapchain() override;
    void                 copyBuffersToTexture(const uint8_t *const *buffers, Texture *dst, const BufferTextureCopy *regions, uint count) override;
    void                 copyTextureToBuffers(Texture *src, uint8_t *const *buffers, const BufferTextureCopy *region, uint count) override;

    CCWGPUDeviceObject *           _gpuDeviceObj = nullptr;
    std::vector<CCWGPUSwapchain *> _swapchains;
};

} // namespace gfx

} // namespace cc
