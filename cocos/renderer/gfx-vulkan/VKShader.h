#ifndef CC_GFXVULKAN_CCVK_SHADER_H_
#define CC_GFXVULKAN_CCVK_SHADER_H_

namespace cc {
namespace gfx {

class CCVKGPUShader;

class CC_VULKAN_API CCVKShader : public GFXShader {
public:
    CCVKShader(GFXDevice *device);
    ~CCVKShader();

public:
    bool initialize(const GFXShaderInfo &info);
    void destroy();

    CC_INLINE CCVKGPUShader *gpuShader() const { return _gpuShader; }

private:
    CCVKGPUShader *_gpuShader = nullptr;
};

} // namespace gfx
} // namespace cc

#endif
