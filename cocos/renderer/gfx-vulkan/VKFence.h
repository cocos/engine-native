#ifndef CC_GFXVULKAN_CCVK_FENCE_H_
#define CC_GFXVULKAN_CCVK_FENCE_H_

NS_CC_BEGIN

class CCVKGPUFence;

class CC_VULKAN_API CCVKFence : public GFXFence {
public:
    CCVKFence(GFXDevice* device);
    ~CCVKFence();

public:
    bool initialize(const GFXFenceInfo& info);
    void destroy();
    void wait();
    void reset();

    CC_INLINE CCVKGPUFence* gpuFence() { return _gpuFence; }

private:
    CCVKGPUFence* _gpuFence;
};

NS_CC_END

#endif
