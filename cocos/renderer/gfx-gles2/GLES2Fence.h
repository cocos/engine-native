#ifndef CC_GFXGLES2_GLES2_FENCE_H_
#define CC_GFXGLES2_GLES2_FENCE_H_

NS_CC_BEGIN

class GLES2GPUFence;

class CC_GLES2_API GLES2Fence : public GFXFence {
public:
    GLES2Fence(GFXDevice* device);
    ~GLES2Fence();

public:
    bool initialize(const GFXFenceInfo& info);
    void destroy();
    void wait();
    void reset();

private:
    GLES2GPUFence* _gpuFence;
};

NS_CC_END

#endif
