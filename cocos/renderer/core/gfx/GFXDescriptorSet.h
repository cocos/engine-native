#ifndef CC_CORE_GFX_DESCRIPTOR_SET_H_
#define CC_CORE_GFX_DESCRIPTOR_SET_H_

#include "GFXDef.h"

namespace cc {
namespace gfx {

class CC_DLL DescriptorSet : public GFXObject {
public:
    DescriptorSet(Device *device);
    virtual ~DescriptorSet();

public:
    virtual bool initialize(const DescriptorSetInfo &info) = 0;
    virtual void destroy() = 0;
    virtual void update() = 0;

    void bindBuffer(uint binding, Buffer *buffer, uint index);
    void bindTexture(uint binding, Texture *texture, uint index);
    void bindSampler(uint binding, Sampler *sampler, uint index);

    CC_INLINE Device *getDevice() const { return _device; }
    CC_INLINE void bindBuffer(uint binding, Buffer *buffer) { bindBuffer(binding, buffer, 0u); }
    CC_INLINE void bindTexture(uint binding, Texture *texture) { bindTexture(binding, texture, 0u); }
    CC_INLINE void bindSampler(uint binding, Sampler *sampler) { bindSampler(binding, sampler, 0u); }
    CC_INLINE Buffer *getBuffer(uint binding) const { return _buffers[binding]; }
    CC_INLINE Texture *getTexture(uint binding) const { return _textures[binding]; }
    CC_INLINE Sampler *getSampler(uint binding) const { return _samplers[binding]; }

protected:
    Device *_device = nullptr;

    DescriptorSetLayout *_layout;
    BufferList _buffers;
    TextureList _textures;
    SamplerList _samplers;

    bool _isDirty = false;
};

} // namespace gfx
} // namespace cc

#endif // CC_CORE_GFX_DESCRIPTOR_SET_H_
