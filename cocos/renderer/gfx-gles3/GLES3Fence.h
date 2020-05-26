#ifndef CC_GFXGLES3_GLES3_FENCE_H_
#define CC_GFXGLES3_GLES3_FENCE_H_

NS_CC_BEGIN

class GLES3GPUFence;

class CC_GLES3_API GLES3Fence : public GFXFence {
public:
    GLES3Fence(GFXDevice* device);
    ~GLES3Fence();

public:
    bool initialize(const GFXFenceInfo& info);
    void destroy();
    void wait();
    void reset();

private:
    GLES3GPUFence* _gpuFence;
};

NS_CC_END

#endif
