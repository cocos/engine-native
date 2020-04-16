#ifndef CC_GFXCCVK_CCVK_DEVICE_H_
#define CC_GFXCCVK_CCVK_DEVICE_H_

NS_CC_BEGIN

class CCVKStateCache;

class CC_VULKAN_API CCVKDevice : public GFXDevice {
public:
  CCVKDevice();
  ~CCVKDevice();
  
  CCVKStateCache* stateCache = nullptr;
  
public:
  bool initialize(const GFXDeviceInfo& info) override;
  void destroy() override;
  void resize(uint width, uint height) override;
  void present() override;
  GFXWindow* createWindow(const GFXWindowInfo& info) override;
  GFXQueue* createQueue(const GFXQueueInfo& info) override;
  GFXCommandAllocator* createCommandAllocator(const GFXCommandAllocatorInfo& info) override;
  GFXCommandBuffer* createCommandBuffer(const GFXCommandBufferInfo& info) override;
  GFXBuffer* createBuffer(const GFXBufferInfo& info) override;
  GFXTexture* createTexture(const GFXTextureInfo& info) override;
  GFXTextureView* createTextureView(const GFXTextureViewInfo& info) override;
  GFXSampler* createSampler(const GFXSamplerInfo& info) override;
  GFXShader* createShader(const GFXShaderInfo& info) override;
  GFXInputAssembler* createInputAssembler(const GFXInputAssemblerInfo& info) override;
  GFXRenderPass* createRenderPass(const GFXRenderPassInfo& info) override;
  GFXFramebuffer* createFramebuffer(const GFXFramebufferInfo& info) override;
  GFXBindingLayout* createBindingLayout(const GFXBindingLayoutInfo& info) override;
  virtual GFXPipelineState* createPipelineState(const GFXPipelineStateInfo& info) override;
  virtual GFXPipelineLayout* createPipelineLayout(const GFXPipelineLayoutInfo& info) override;
    virtual void copyBuffersToTexture(const GFXDataArray& buffers, GFXTexture* dst, const GFXBufferTextureCopyList& regions) override;
  
  CC_INLINE bool useVAO() const { return _useVAO; }

  CC_INLINE bool checkExtension(const String& extension) const {
    for (size_t i = 0; i < _extensions.size(); ++i) {
      if (_extensions[i].find(extension) != String::npos) {
        return true;
      }
    }
    return false;
  }
  
 private:
  StringArray _extensions;
  bool _useVAO = true;
};

NS_CC_END

#endif
