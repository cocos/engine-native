#ifndef CC_CORE_GFX_DEVICE_H_
#define CC_CORE_GFX_DEVICE_H_

#include "GFXDef.h"

NS_CC_BEGIN

class CC_CORE_API GFXDevice : public Object {
 public:
  GFXDevice();
  virtual ~GFXDevice();
  
 public:
  virtual bool Initialize(const GFXDeviceInfo& info) = 0;
  virtual void Destroy() = 0;
  virtual void Resize(uint width, uint height) = 0;
  virtual void Present() = 0;
  virtual GFXWindow* CreateGFXWindow(const GFXWindowInfo& info) = 0;
  virtual GFXQueue* CreateGFXQueue(const GFXQueueInfo& info) = 0;
  virtual GFXCommandAllocator* CreateGFXCommandAllocator(const GFXCommandAllocatorInfo& info) = 0;
  virtual GFXCommandBuffer* CreateGFXCommandBuffer(const GFXCommandBufferInfo& info) = 0;
  virtual GFXBuffer* CreateGFXBuffer(const GFXBufferInfo& info) = 0;
  virtual GFXTexture* CreateGFXTexture(const GFXTextureInfo& info) = 0;
  virtual GFXTextureView* CreateGFXTextureView(const GFXTextureViewInfo& info) = 0;
  virtual GFXSampler* CreateGFXSampler(const GFXSamplerInfo& info) = 0;
  virtual GFXShader* CreateGFXShader(const GFXShaderInfo& info) = 0;
  virtual GFXInputAssembler* CreateGFXInputAssembler(const GFXInputAssemblerInfo& info) = 0;
  virtual GFXRenderPass* CreateGFXRenderPass(const GFXRenderPassInfo& info) = 0;
  virtual GFXFramebuffer* CreateGFXFramebuffer(const GFXFramebufferInfo& info) = 0;
  virtual GFXBindingLayout* CreateGFXBindingLayout(const GFXBindingLayoutInfo& info) = 0;
  virtual GFXPipelineState* CreateGFXPipelineState(const GFXPipelineStateInfo& info) = 0;
  virtual GFXPipelineLayout* CreateGFXPipelieLayout(const GFXPipelineLayoutInfo& info) = 0;
  virtual void CopyBuffersToTexture(GFXBuffer* src, GFXTexture* dst, const GFXBufferTextureCopyList& regions) = 0;
  
  CC_INLINE GFXAPI gfxAPI() const { return _api; }
  CC_INLINE uint width() { return _width; }
  CC_INLINE uint height() { return _height; }
  CC_INLINE uint nativeWidth() { return _nativeWidth; }
  CC_INLINE uint nativeHeight() { return _nativeHeight; }
  CC_INLINE const GFXMemoryStatus& memoryStatus() const { return _memoryStatus; }
  CC_INLINE GFXContext* context() const { return _context; }
  CC_INLINE GFXWindow* mainWindow() const { return _window; }
  CC_INLINE GFXQueue* queue() const { return _queue; }
  CC_INLINE GFXCommandAllocator* commandAllocator() const { return _cmdAllocator; }
  CC_INLINE const String& renderer() const { return _renderer; }
  CC_INLINE const String& vendor() const { return _vendor; }
  CC_INLINE uint numDrawCalls() const { return _numDrawCalls; }
  CC_INLINE uint numTris() const { return _numTriangles; }
  CC_INLINE bool HasFeature(GFXFeature feature) const { return _features[(int)feature]; }
  
 protected:
  GFXAPI _api = GFXAPI::UNKNOWN;
  String _device_name;
  String _renderer;
  String _vendor;
  String _version;
  bool _features[(int)GFXFeature::COUNT];
  uint _width = 0;
  uint _height = 0;
  uint _nativeWidth = 0;
  uint _nativeHeight = 0;
  GFXMemoryStatus _memoryStatus;
  intptr_t _windowHandle = 0;
  GFXContext* _context = nullptr;
  GFXWindow* _window = nullptr;
  GFXQueue* _queue = nullptr;
  GFXCommandAllocator* _cmdAllocator = nullptr;
  uint _numDrawCalls = 0;
  uint _numTriangles = 0;
};

NS_CC_END

#endif // CC_CORE_GFX_DEVICE_H_
