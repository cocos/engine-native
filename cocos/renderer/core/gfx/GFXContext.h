#ifndef CC_CORE_GFX_CONTEXT_H_
#define CC_CORE_GFX_CONTEXT_H_

#include "GFXDef.h"

NS_CC_BEGIN

class CC_CORE_API GFXContext : public Object {
 public:
  GFXContext(GFXDevice* device);
  virtual ~GFXContext();
  
 public:
  virtual bool initialize(const GFXContextInfo& info) = 0;
  virtual void destroy() = 0;
  virtual void Present() = 0;

  CC_INLINE GFXDevice* device() const { return _device; }
  CC_INLINE GFXContext* shared_ctx() const { return shared_ctx_; }
  CC_INLINE GFXVsyncMode vsync_mode() const { return vsync_mode_; }
  CC_INLINE GFXFormat colorFormat() const { return _colorFmt; }
  CC_INLINE GFXFormat detphStencilFormat() const { return _depthStencilFmt; }
  
 protected:
  GFXDevice* _device;
  intptr_t window_handle_;
  GFXContext* shared_ctx_;
  GFXVsyncMode vsync_mode_;
  GFXFormat _colorFmt;
  GFXFormat _depthStencilFmt;
};

NS_CC_END

#endif // CC_CORE_GFX_CONTEXT_H_
