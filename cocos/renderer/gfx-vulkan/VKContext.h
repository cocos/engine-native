#ifndef CC_GFXVULKAN_CCVK_CONTEXT_H_
#define CC_GFXVULKAN_CCVK_CONTEXT_H_

#include <volk.h>

NS_CC_BEGIN

class CC_VULKAN_API CCVKContext : public GFXContext {
public:
    CCVKContext(GFXDevice* device);
    ~CCVKContext();

public:
    bool initialize(const GFXContextInfo& info);
    void destroy();
    void present();
    bool MakeCurrent();

    bool CheckExtension(const String& extension) const;

    CC_INLINE int majorVersion() const { return _majorVersion; }
    CC_INLINE int minorVersion() const { return _minorVersion; }
    CC_INLINE const std::vector<VkPhysicalDevice>& physicalDevices() const { return _physicalDevices; }

private:
    bool MakeCurrentImpl();

private:
    struct SwapchainDimensions
    {
        uint32_t width = 0;
        uint32_t height = 0;
        VkFormat format = VK_FORMAT_UNDEFINED;
    };
    VkInstance _instance = VK_NULL_HANDLE;
    std::vector<VkPhysicalDevice> _physicalDevices;
    VkDevice _device = VK_NULL_HANDLE;
    VkQueue _queue = VK_NULL_HANDLE;
    VkSwapchainKHR _swapchain = VK_NULL_HANDLE;
    SwapchainDimensions _swapchainDimensions;
    VkSurfaceKHR _surface = VK_NULL_HANDLE;
    std::vector<VkImageView> _swapchainImageViews;
    std::vector<VkFramebuffer> _swapchainFramebuffers;
    VkDebugUtilsMessengerEXT _debugUtilsMessenger = VK_NULL_HANDLE;
    VkDebugReportCallbackEXT _debugReport = VK_NULL_HANDLE;

    bool _isPrimaryContex = false;
    int _majorVersion = 0;
    int _minorVersion = 0;
    StringArray _extensions;
    bool _isInitialized = false;
};

NS_CC_END

#endif // CC_GFXVULKAN_CCVK_CONTEXT_H_
