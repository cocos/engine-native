#ifndef CC_CORE_GFX_SHADER_H_
#define CC_CORE_GFX_SHADER_H_

#include "GFXDef.h"

NS_CC_BEGIN

class CC_CORE_API GFXShader : public Object {
 public:
  GFXShader(GFXDevice* device);
  virtual ~GFXShader();
  
 public:
  virtual bool initialize(const GFXShaderInfo& info) = 0;
  virtual void destroy() = 0;
  
  CC_INLINE GFXDevice* device() const { return _device; }
  CC_INLINE uint hash() const { return hash_; }
  CC_INLINE const String& name() const { return _name; }
  CC_INLINE const GFXShaderStageList& stages() const { return stages_; }
  CC_INLINE const GFXUniformBlockList& blocks() const { return blocks_; }
  CC_INLINE const GFXUniformSamplerList& samplers() const { return samplers_; }
  
 protected:
  GFXDevice* _device;
  uint hash_;
  String _name;
  GFXShaderStageList stages_;
  GFXUniformBlockList blocks_;
  GFXUniformSamplerList samplers_;
};

NS_CC_END

#endif // CC_CORE_GFX_TEXTURE_VIEW_H_
