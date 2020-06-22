#ifndef CC_GFXVULKAN_CCVK_DEVICE_H_
#define CC_GFXVULKAN_CCVK_DEVICE_H_

namespace cc {
namespace gfx {

class CCVKGPUContext;
class CCVKGPUDevice;
class CCVKGPUSwapchain;
class CCVKGPUSemaphorePool;
class CCVKGPUFencePool;
class CCVKTexture;
class CCVKRenderPass;
class CCVKBuffer;

class CC_VULKAN_API CCVKDevice : public Device {
public:
    CCVKDevice();
    ~CCVKDevice();

public:
    virtual bool initialize(const DeviceInfo &info) override;
    virtual void destroy() override;
    virtual void resize(uint width, uint height) override;
    virtual void acquire() override;
    virtual void present() override;
    virtual Fence *createFence(const FenceInfo &info) override;
    virtual GFXQueue *createQueue(const GFXQueueInfo &info) override;
    virtual CommandAllocator *createCommandAllocator(const CommandAllocatorInfo &info) override;
    virtual CommandBuffer *createCommandBuffer(const CommandBufferInfo &info) override;
    virtual Buffer *createBuffer(const BufferInfo &info) override;
    virtual Texture *createTexture(const TextureInfo &info) override;
    virtual Texture *createTexture(const TextureViewInfo &info) override;
    virtual GFXSampler *createSampler(const GFXSamplerInfo &info) override;
    virtual GFXShader *createShader(const GFXShaderInfo &info) override;
    virtual GFXInputAssembler *createInputAssembler(const GFXInputAssemblerInfo &info) override;
    virtual GFXRenderPass *createRenderPass(const GFXRenderPassInfo &info) override;
    virtual GFXFramebuffer *createFramebuffer(const GFXFramebufferInfo &info) override;
    virtual BindingLayout *createBindingLayout(const BindingLayoutInfo &info) override;
    virtual GFXPipelineState *createPipelineState(const GFXPipelineStateInfo &info) override;
    virtual GFXPipelineLayout *createPipelineLayout(const GFXPipelineLayoutInfo &info) override;
    virtual void copyBuffersToTexture(const GFXDataArray &buffers, Texture *dst, const BufferTextureCopyList &regions) override;

    CC_INLINE bool checkExtension(const String &extension) const {
        return std::find_if(_extensions.begin(), _extensions.end(),
                            [extension](const char *device_extension) {
                                return std::strcmp(device_extension, extension.c_str()) == 0;
                            }) != _extensions.end();
    }

    CCVKGPUContext *gpuContext() const;
    CC_INLINE CCVKGPUDevice *gpuDevice() const { return _gpuDevice; }
    CC_INLINE CCVKGPUSwapchain *gpuSwapchain() { return _gpuSwapchain; }
    CC_INLINE CCVKGPUSemaphorePool *gpuSemaphorePool() { return _gpuSemaphorePool; }
    CC_INLINE CCVKGPUFencePool *gpuFencePool() { return _gpuFencePool; }
    CC_INLINE CCVKBuffer *stagingBuffer() { return _stagingBuffer; }
    CC_INLINE const std::vector<const char *> &getLayers() const { return _layers; }
    CC_INLINE const std::vector<const char *> &getExtensions() const { return _extensions; }
    CC_INLINE bool isMultiDrawIndirectSupported() const { return _multiDrawIndirectSupported; }
    CC_INLINE bool isSwapchainReady() const { return _swapchainReady; }

    CCVKTexture *nullTexture2D = nullptr;
    CCVKTexture *nullTextureCube = nullptr;

private:
    void buildSwapchain();

    CCVKGPUDevice *_gpuDevice = nullptr;
    CCVKGPUSemaphorePool *_gpuSemaphorePool = nullptr;
    CCVKGPUFencePool *_gpuFencePool = nullptr;
    CCVKGPUSwapchain *_gpuSwapchain = nullptr;
    std::vector<CCVKTexture *> _depthStencilTextures;
    CCVKBuffer *_stagingBuffer = nullptr;

    uint32_t _defaultStagingBufferSize = 1024;

    std::vector<const char *> _layers;
    std::vector<const char *> _extensions;

    bool _swapchainReady = false;
    bool _multiDrawIndirectSupported = false;
};

} // namespace gfx
} // namespace cc

#endif // CC_GFXVULKAN_CCVK_DEVICE_H_
