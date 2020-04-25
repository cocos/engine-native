#ifndef CC_GFXCCVK_CCVK_WINDOW_H_
#define CC_GFXCCVK_CCVK_WINDOW_H_

NS_CC_BEGIN

class CCVKGPUSwapchain;

class CC_VULKAN_API CCVKWindow : public GFXWindow
{
public:
    CCVKWindow(GFXDevice* device);
    ~CCVKWindow();

public:
    bool initialize(const GFXWindowInfo& info);
    void destroy();
    void resize(uint width, uint height);
    CC_INLINE GFXFramebuffer* getFramebuffer() const { return _swapchainFramebuffers[_curImageIndex]; }

private:
    uint32_t _curImageIndex;
    std::vector<GFXTexture*> _swapchainTextures;
    std::vector<GFXTextureView*> _swapchainTextureViews;
    std::vector<GFXFramebuffer*> _swapchainFramebuffers;
};

NS_CC_END

#endif
