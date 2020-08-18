#ifndef CC_GFXGLES2_GLES2_DESCRIPTOR_SET_H_
#define CC_GFXGLES2_GLES2_DESCRIPTOR_SET_H_

namespace cc {
namespace gfx {

class GLES2GPUDescriptorSet;

class CC_GLES2_API GLES2DescriptorSet : public DescriptorSet {
public:
    GLES2DescriptorSet(Device *device);
    ~GLES2DescriptorSet();

public:
    virtual bool initialize(const DescriptorSetInfo &info) override;
    virtual void destroy() override;
    virtual void update() override;

    CC_INLINE GLES2GPUDescriptorSet *gpuBindingLayout() const { return _gpuBindingLayout; }

private:
    GLES2GPUDescriptorSet *_gpuBindingLayout = nullptr;
};

} // namespace gfx
} // namespace cc

#endif // CC_GFXGLES2_GLES2_DESCRIPTOR_SET_H_
