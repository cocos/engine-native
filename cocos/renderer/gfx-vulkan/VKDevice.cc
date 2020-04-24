#include "VKStd.h"
#include "VKDevice.h"
#include "VKUtils.h"
#include "VKStateCache.h"
#include "VKContext.h"
#include "VKWindow.h"
#include "VKQueue.h"
#include "VKCommandAllocator.h"
#include "VKCommandBuffer.h"
#include "VKBuffer.h"
#include "VKTexture.h"
#include "VKTextureView.h"
#include "VKSampler.h"
#include "VKShader.h"
#include "VKInputAssembler.h"
#include "VKRenderPass.h"
#include "VKFramebuffer.h"
#include "VKBindingLayout.h"
#include "VKPipelineLayout.h"
#include "VKPipelineState.h"

NS_CC_BEGIN

CCVKDevice::CCVKDevice()
{
}

CCVKDevice::~CCVKDevice()
{
}

bool CCVKDevice::initialize(const GFXDeviceInfo& info)
{
    _gfxAPI = GFXAPI::VULKAN;
    _deviceName = "Vulkan";
    _width = info.width;
    _height = info.height;
    _nativeWidth = info.nativeWidth;
    _nativeHeight = info.nativeHeight;
    _windowHandle = info.windowHandle;

    stateCache = CC_NEW(CCVKStateCache);

    GFXContextInfo contextCreateInfo;
    contextCreateInfo.windowHandle = _windowHandle;
    contextCreateInfo.sharedCtx = info.sharedCtx;

    _context = CC_NEW(CCVKContext(this));
    if (!_context->initialize(contextCreateInfo))
    {
        destroy();
        return false;
    }
    auto context = ((CCVKContext*)_context)->gpuContext();
    auto &deviceFeatures = context->physicalDeviceFeatures;

    // only enable the absolute essentials for now
    std::vector<const char *> requestedValidationLayers
    {

    };
    std::vector<const char *> requestedExtensions
    {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    };
    VkPhysicalDeviceFeatures requestedFeatures{};
    // features should be enabled like this
    requestedFeatures.textureCompressionETC2 = deviceFeatures.textureCompressionETC2;

    ///////////////////// Device Creation /////////////////////

    _gpuDevice = CC_NEW(CCVKGPUDevice);

    // check extensions
    uint32_t availableLayerCount;
    VK_CHECK(vkEnumerateDeviceLayerProperties(context->physicalDevice, &availableLayerCount, nullptr));
    _gpuDevice->layers.resize(availableLayerCount);
    VK_CHECK(vkEnumerateDeviceLayerProperties(context->physicalDevice, &availableLayerCount, _gpuDevice->layers.data()));

    uint32_t availableExtensionCount;
    VK_CHECK(vkEnumerateDeviceExtensionProperties(context->physicalDevice, nullptr, &availableExtensionCount, nullptr));
    _gpuDevice->extensions.resize(availableExtensionCount);
    VK_CHECK(vkEnumerateDeviceExtensionProperties(context->physicalDevice, nullptr, &availableExtensionCount, _gpuDevice->extensions.data()));

    // just filter out the unsupported layers & extensions
    for (auto &layer : requestedValidationLayers)
    {
        if (isLayerSupported(layer, _gpuDevice->layers))
        {
            _layers.push_back(layer);
        }
    }
    for (auto &extension : requestedExtensions)
    {
        if (isExtensionSupported(extension, _gpuDevice->extensions))
        {
            _extensions.push_back(extension);
        }
    }

    // prepare the device queues
    uint32_t                             queueFamilyPropertiesCount = toU32(context->queueFamilyProperties.size());
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos(queueFamilyPropertiesCount, { VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO });
    std::vector<std::vector<float>>      queuePriorities(queueFamilyPropertiesCount);

    for (uint32_t queueFamilyIndex = 0u; queueFamilyIndex < queueFamilyPropertiesCount; ++queueFamilyIndex)
    {
        const VkQueueFamilyProperties &queueFamilyProperty = context->queueFamilyProperties[queueFamilyIndex];

        queuePriorities[queueFamilyIndex].resize(queueFamilyProperty.queueCount, 1.0f);

        VkDeviceQueueCreateInfo &queueCreateInfo = queueCreateInfos[queueFamilyIndex];

        queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        queueCreateInfo.queueCount = queueFamilyProperty.queueCount;
        queueCreateInfo.pQueuePriorities = queuePriorities[queueFamilyIndex].data();
    }

    VkDeviceCreateInfo deviceCreateInfo{ VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO };

    deviceCreateInfo.queueCreateInfoCount = toU32(queueCreateInfos.size());
    deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
    deviceCreateInfo.enabledLayerCount = toU32(_layers.size());
    deviceCreateInfo.ppEnabledLayerNames = _layers.data();
    deviceCreateInfo.enabledExtensionCount = toU32(_extensions.size());
    deviceCreateInfo.ppEnabledExtensionNames = _extensions.data();
    deviceCreateInfo.pEnabledFeatures = &requestedFeatures;
    deviceCreateInfo.pNext = nullptr;

    VK_CHECK(vkCreateDevice(context->physicalDevice, &deviceCreateInfo, nullptr, &_gpuDevice->vkDevice));

    ///////////////////// Resource Initialization /////////////////////

    buildSwapchain();

    GFXWindowInfo windowInfo;
    windowInfo.colorFmt = _context->getColorFormat();
    windowInfo.depthStencilFmt = _context->getDepthStencilFormat();
    windowInfo.isOffscreen = false;
    _window = createWindow(windowInfo);

    GFXQueueInfo queueInfo;
    queueInfo.type = GFXQueueType::GRAPHICS;
    _queue = createQueue(queueInfo);

    GFXCommandAllocatorInfo cmd_alloc_info;
    _cmdAllocator = createCommandAllocator(cmd_alloc_info);

    String instanceLayers, instanceExtensions, deviceLayers, deviceExtensions;
    for (auto layer : ((CCVKContext*)_context)->getLayers())
    {
        instanceLayers += layer + String(" ");
    }
    for (auto extension : ((CCVKContext*)_context)->getExtensions())
    {
        instanceExtensions += extension + String(" ");
    }
    for (auto layer : _layers)
    {
        deviceLayers += layer + String(" ");
    }
    for (auto extension : _extensions)
    {
        deviceExtensions += extension + String(" ");
    }

    CC_LOG_INFO("Vulkan device initialized.");
    CC_LOG_INFO("DEVICE_NAME: %s", context->physicalDeviceProperties.deviceName);
    CC_LOG_INFO("VULKAN_VERSION: %d.%d", ((CCVKContext*)_context)->majorVersion(), ((CCVKContext*)_context)->minorVersion());
    CC_LOG_INFO("SCREEN_SIZE: %d x %d", _width, _height);
    CC_LOG_INFO("NATIVE_SIZE: %d x %d", _nativeWidth, _nativeHeight);
    CC_LOG_INFO("INSTANCE_LAYERS: %s", instanceLayers.c_str());
    CC_LOG_INFO("INSTANCE_EXTENSIONS: %s", instanceExtensions.c_str());
    CC_LOG_INFO("DEVICE_LAYERS: %s", deviceLayers.c_str());
    CC_LOG_INFO("DEVICE_EXTENSIONS: %s", deviceExtensions.c_str());

    return true;
}

void CCVKDevice::destroy()
{
    CC_SAFE_DESTROY(_cmdAllocator);
    CC_SAFE_DESTROY(_queue);
    CC_SAFE_DESTROY(_window);

    if (_gpuDevice)
    {
        if (_gpuDevice->vkSwapchain != VK_NULL_HANDLE)
        {
            for (uint32_t i = 0; i < _gpuDevice->vkSwapchainImageViews.size(); i++)
            {
                vkDestroyImageView(_gpuDevice->vkDevice, _gpuDevice->vkSwapchainImageViews[i], nullptr);
            }
            vkDestroySwapchainKHR(_gpuDevice->vkDevice, _gpuDevice->vkSwapchain, nullptr);

            _gpuDevice->vkSwapchainImages.clear();
            _gpuDevice->vkSwapchainImageViews.clear();
            _gpuDevice->vkSwapchain = VK_NULL_HANDLE;
        }

        if (_gpuDevice->vkDevice != VK_NULL_HANDLE)
        {
            vkDestroyDevice(_gpuDevice->vkDevice, nullptr);
            _gpuDevice->vkDevice = VK_NULL_HANDLE;
        }

        CC_DELETE(_gpuDevice);
        _gpuDevice = nullptr;
    }
}

void CCVKDevice::resize(uint width, uint height)
{
  
}

void CCVKDevice::present()
{
    //((CCVKCommandAllocator*)_cmdAllocator)->releaseCmds();
    CCVKQueue* queue = (CCVKQueue*)_queue;
    _numDrawCalls = queue->_numDrawCalls;
    _numInstances = queue->_numInstances;
    _numTriangles = queue->_numTriangles;

    _context->present();

    // Clear queue stats
    queue->_numDrawCalls = 0;
    queue->_numInstances = 0;
    queue->_numTriangles = 0;
}

void CCVKDevice::buildSwapchain()
{
    auto context = ((CCVKContext*)_context)->gpuContext();
    context->swapchainCreateInfo.oldSwapchain = _gpuDevice->vkSwapchain;

    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    VK_CHECK(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(context->physicalDevice, context->vkSurface, &surfaceCapabilities));
    if (surfaceCapabilities.currentExtent.width == (uint32_t)-1)
    {
        context->swapchainCreateInfo.imageExtent.width = _width;
        context->swapchainCreateInfo.imageExtent.height = _height;
    }
    else
    {
        _width = context->swapchainCreateInfo.imageExtent.width = surfaceCapabilities.currentExtent.width;
        _height = context->swapchainCreateInfo.imageExtent.height = surfaceCapabilities.currentExtent.height;
    }
    VK_CHECK(vkCreateSwapchainKHR(_gpuDevice->vkDevice, &context->swapchainCreateInfo, nullptr, &_gpuDevice->vkSwapchain));

    if (context->swapchainCreateInfo.oldSwapchain != VK_NULL_HANDLE)
    {
        for (uint32_t i = 0; i < _gpuDevice->vkSwapchainImageViews.size(); i++)
        {
            vkDestroyImageView(_gpuDevice->vkDevice, _gpuDevice->vkSwapchainImageViews[i]->vkImageView, nullptr);
            CC_DELETE(_gpuDevice->vkSwapchainImageViews[i]->gpuTexture);
            CC_DELETE(_gpuDevice->vkSwapchainImageViews[i]);
        }
        vkDestroySwapchainKHR(_gpuDevice->vkDevice, context->swapchainCreateInfo.oldSwapchain, nullptr);
    }

    uint32_t imageCount;
    VK_CHECK(vkGetSwapchainImagesKHR(_gpuDevice->vkDevice, _gpuDevice->vkSwapchain, &imageCount, nullptr));
    _gpuDevice->vkSwapchainImages.resize(imageCount);
    VK_CHECK(vkGetSwapchainImagesKHR(_gpuDevice->vkDevice, _gpuDevice->vkSwapchain, &imageCount, _gpuDevice->vkSwapchainImages.data()));

    _gpuDevice->vkSwapchainImageViews.resize(imageCount);
    for (uint32_t i = 0; i < imageCount; i++)
    {
        auto format = ((CCVKContext*)_context)->getColorFormat();
        auto gpuTexture = CC_NEW(CCVKGPUTexture);
        gpuTexture->width = _width;
        gpuTexture->height = _height;
        gpuTexture->size = GFXFormatSize(format, _width, _height, 1);
        gpuTexture->format = format;
        gpuTexture->usage = GFXTextureUsageBit::COLOR_ATTACHMENT;
        gpuTexture->vkImage = _gpuDevice->vkSwapchainImages[i];
        gpuTexture->isPowerOf2 = math::IsPowerOfTwo(_width) && math::IsPowerOfTwo(_height);
        auto gpuTextureView = CC_NEW(CCVKGPUTextureView);
        gpuTextureView->gpuTexture = gpuTexture;
        gpuTextureView->format = format;
        VkImageViewCreateInfo colorAttachmentView{ VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
        colorAttachmentView.image = _gpuDevice->vkSwapchainImages[i];
        colorAttachmentView.viewType = VK_IMAGE_VIEW_TYPE_2D;
        colorAttachmentView.format = context->swapchainCreateInfo.imageFormat;
        colorAttachmentView.components = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A };
        colorAttachmentView.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
        VK_CHECK(vkCreateImageView(_gpuDevice->vkDevice, &colorAttachmentView, nullptr, &gpuTextureView->vkImageView));
        _gpuDevice->vkSwapchainImageViews[i] = gpuTextureView;
    }
}

GFXWindow* CCVKDevice::createWindow(const GFXWindowInfo& info)
{
    GFXWindow* gfx_window = CC_NEW(CCVKWindow(this));
    if (gfx_window->initialize(info))
        return gfx_window;

    CC_SAFE_DESTROY(gfx_window);
    return nullptr;
}

GFXQueue* CCVKDevice::createQueue(const GFXQueueInfo& info)
{
    GFXQueue* gfx_queue = CC_NEW(CCVKQueue(this));
    if (gfx_queue->initialize(info))
        return gfx_queue;

    CC_SAFE_DESTROY(gfx_queue);
    return nullptr;
}

GFXCommandAllocator* CCVKDevice::createCommandAllocator(const GFXCommandAllocatorInfo& info)
{
    GFXCommandAllocator* gfx_cmd_allocator = CC_NEW(CCVKCommandAllocator(this));
    if (gfx_cmd_allocator->initialize(info))
        return gfx_cmd_allocator;

    CC_SAFE_DESTROY(gfx_cmd_allocator);
    return nullptr;
}

GFXCommandBuffer* CCVKDevice::createCommandBuffer(const GFXCommandBufferInfo& info)
{
    GFXCommandBuffer* gfx_cmd_buff = CC_NEW(CCVKCommandBuffer(this));
    if (gfx_cmd_buff->initialize(info))
        return gfx_cmd_buff;

    CC_SAFE_DESTROY(gfx_cmd_buff)
    return nullptr;
}

GFXBuffer* CCVKDevice::createBuffer(const GFXBufferInfo& info)
{
    GFXBuffer* gfx_buffer = CC_NEW(CCVKBuffer(this));
    if (gfx_buffer->initialize(info))
        return gfx_buffer;

    CC_SAFE_DESTROY(gfx_buffer);
    return nullptr;
}

GFXTexture* CCVKDevice::createTexture(const GFXTextureInfo& info)
{
    GFXTexture* gfx_texture = CC_NEW(CCVKTexture(this));
    if (gfx_texture->initialize(info))
        return gfx_texture;

    CC_SAFE_DESTROY(gfx_texture);
    return nullptr;
}

GFXTextureView* CCVKDevice::createTextureView(const GFXTextureViewInfo& info)
{
    GFXTextureView* gfx_tex_view = CC_NEW(CCVKTextureView(this));
    if (gfx_tex_view->initialize(info))
        return gfx_tex_view;

    CC_SAFE_DESTROY(gfx_tex_view);
    return nullptr;
}

GFXSampler* CCVKDevice::createSampler(const GFXSamplerInfo& info)
{
    GFXSampler* gfx_sampler = CC_NEW(CCVKSampler(this));
    if (gfx_sampler->initialize(info))
        return gfx_sampler;

    CC_SAFE_DESTROY(gfx_sampler);
    return nullptr;
}

GFXShader* CCVKDevice::createShader(const GFXShaderInfo& info)
{
    GFXShader* gfx_shader = CC_NEW(CCVKShader(this));
    if (gfx_shader->initialize(info))
        return gfx_shader;

    CC_SAFE_DESTROY(gfx_shader);
    return nullptr;
}

GFXInputAssembler* CCVKDevice::createInputAssembler(const GFXInputAssemblerInfo& info)
{
    GFXInputAssembler* gfx_input_assembler = CC_NEW(CCVKInputAssembler(this));
    if (gfx_input_assembler->initialize(info))
        return gfx_input_assembler;

    CC_SAFE_DESTROY(gfx_input_assembler);
    return nullptr;
}

GFXRenderPass* CCVKDevice::createRenderPass(const GFXRenderPassInfo& info)
{
    GFXRenderPass* gfx_render_pass = CC_NEW(CCVKRenderPass(this));
    if (gfx_render_pass->initialize(info))
        return gfx_render_pass;

    CC_SAFE_DESTROY(gfx_render_pass);
    return nullptr;
}

GFXFramebuffer* CCVKDevice::createFramebuffer(const GFXFramebufferInfo& info)
{
    GFXFramebuffer* gfx_framebuffer = CC_NEW(CCVKFramebuffer(this));
    if (gfx_framebuffer->initialize(info))
        return gfx_framebuffer;

    CC_SAFE_DESTROY(gfx_framebuffer);
    return nullptr;
}

GFXBindingLayout* CCVKDevice::createBindingLayout(const GFXBindingLayoutInfo& info)
{
    GFXBindingLayout* gfx_binding_layout = CC_NEW(CCVKBindingLayout(this));
    if (gfx_binding_layout->initialize(info))
        return gfx_binding_layout;

    CC_SAFE_DESTROY(gfx_binding_layout);
    return nullptr;
}


GFXPipelineState* CCVKDevice::createPipelineState(const GFXPipelineStateInfo& info)
{
    GFXPipelineState* pipelineState = CC_NEW(CCVKPipelineState(this));
    if (pipelineState->initialize(info))
        return pipelineState;

    CC_SAFE_DESTROY(pipelineState);
    return nullptr;
}

GFXPipelineLayout* CCVKDevice::createPipelineLayout(const GFXPipelineLayoutInfo& info)
{
    GFXPipelineLayout* layout = CC_NEW(CCVKPipelineLayout(this));
    if (layout->initialize(info))
        return layout;

    CC_SAFE_DESTROY(layout);
    return nullptr;
}

void CCVKDevice::copyBuffersToTexture(const GFXDataArray& buffers, GFXTexture* dst, const GFXBufferTextureCopyList& regions)
{
    
   CCVKCmdFuncCopyBuffersToTexture(this, buffers.datas.data(), ((CCVKTexture*)dst)->gpuTexture(), regions);
}

NS_CC_END
