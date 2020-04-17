#include "VKStd.h"
#include "VKDevice.h"
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

    GFXContextInfo ctx_info;
    ctx_info.windowHandle = _windowHandle;
    ctx_info.sharedCtx = info.sharedCtx;

    _context = CC_NEW(CCVKContext(this));
    if (!_context->initialize(ctx_info))
    {
        destroy();
        return false;
    }

    auto physicalDevices = ((CCVKContext*)_context)->physicalDevices();
    auto &physicalDevice = physicalDevices[0];
    for (auto &device : physicalDevices)
    {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(device, &properties);
        CC_LOG_INFO(StringUtil::Format("Found Physical Device: %s", properties.deviceName).c_str());
        if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            physicalDevice = device;
        }
    }

    // Prepare the device queues
    /*
    uint32_t                             queue_family_properties_count = to_u32(gpu.get_queue_family_properties().size());
    std::vector<VkDeviceQueueCreateInfo> queue_create_infos(queue_family_properties_count, { VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO });
    std::vector<std::vector<float>>      queue_priorities(queue_family_properties_count);

    for (uint32_t queue_family_index = 0U; queue_family_index < queue_family_properties_count; ++queue_family_index)
    {
        const VkQueueFamilyProperties &queue_family_property = gpu.get_queue_family_properties()[queue_family_index];

        queue_priorities[queue_family_index].resize(queue_family_property.queueCount, 1.0f);

        VkDeviceQueueCreateInfo &queue_create_info = queue_create_infos[queue_family_index];

        queue_create_info.queueFamilyIndex = queue_family_index;
        queue_create_info.queueCount = queue_family_property.queueCount;
        queue_create_info.pQueuePriorities = queue_priorities[queue_family_index].data();
    }

    // Check extensions to enable Vma Dedicated Allocation
    uint32_t device_extension_count;
    VK_CHECK(vkEnumerateDeviceExtensionProperties(gpu.get_handle(), nullptr, &device_extension_count, nullptr));
    device_extensions = std::vector<VkExtensionProperties>(device_extension_count);
    VK_CHECK(vkEnumerateDeviceExtensionProperties(gpu.get_handle(), nullptr, &device_extension_count, device_extensions.data()));

    // Display supported extensions
    if (device_extensions.size() > 0)
    {
        LOGD("Device supports the following extensions:");
        for (auto &extension : device_extensions)
        {
            LOGD("  \t{}", extension.extensionName);
        }
    }

    bool can_get_memory_requirements = is_extension_supported("VK_KHR_get_memory_requirements2");
    bool has_dedicated_allocation = is_extension_supported("VK_KHR_dedicated_allocation");

    if (can_get_memory_requirements && has_dedicated_allocation)
    {
        enabled_extensions.push_back("VK_KHR_get_memory_requirements2");
        enabled_extensions.push_back("VK_KHR_dedicated_allocation");
        LOGI("Dedicated Allocation enabled");
    }

    // Check that extensions are supported before trying to create the device
    std::vector<const char *> unsupported_extensions{};
    for (auto &extension : requested_extensions)
    {
        if (is_extension_supported(extension.first))
        {
            enabled_extensions.emplace_back(extension.first);
        }
        else
        {
            unsupported_extensions.emplace_back(extension.first);
        }
    }

    if (enabled_extensions.size() > 0)
    {
        LOGI("Device supports the following requested extensions:");
        for (auto &extension : enabled_extensions)
        {
            LOGI("  \t{}", extension);
        }
    }

    if (unsupported_extensions.size() > 0)
    {
        auto error = false;
        for (auto &extension : unsupported_extensions)
        {
            auto extension_is_optional = requested_extensions[extension];
            if (extension_is_optional)
            {
                LOGW("Optional device extension {} not available, some features may be disabled", extension);
            }
            else
            {
                LOGE("Required device extension {} not available, cannot run", extension);
            }
            error = !extension_is_optional;
        }

        if (error)
        {
            throw VulkanException(VK_ERROR_EXTENSION_NOT_PRESENT, "Extensions not present");
        }
    }

    VkDeviceCreateInfo create_info{ VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO };

    // Latest requested feature will have the pNext's all set up for device creation.
    create_info.pNext = gpu.get_requested_extension_features();

    create_info.pQueueCreateInfos = queue_create_infos.data();
    create_info.queueCreateInfoCount = to_u32(queue_create_infos.size());
    const auto requested_gpu_features = gpu.get_requested_features();
    create_info.pEnabledFeatures = &requested_gpu_features;
    create_info.enabledExtensionCount = to_u32(enabled_extensions.size());
    create_info.ppEnabledExtensionNames = enabled_extensions.data();

    VkResult result = vkCreateDevice(gpu.get_handle(), &create_info, nullptr, &handle);

    if (result != VK_SUCCESS)
    {
        throw VulkanException{ result, "Cannot create device" };
    }

    queues.resize(queue_family_properties_count);

    for (uint32_t queue_family_index = 0U; queue_family_index < queue_family_properties_count; ++queue_family_index)
    {
        const VkQueueFamilyProperties &queue_family_property = gpu.get_queue_family_properties()[queue_family_index];

        VkBool32 present_supported = gpu.is_present_supported(surface, queue_family_index);

        // Only check if surface is valid to allow for headless applications
        if (surface != VK_NULL_HANDLE)
        {
            VK_CHECK(vkGetPhysicalDeviceSurfaceSupportKHR(gpu.get_handle(), queue_family_index, surface, &present_supported));
        }

        for (uint32_t queue_index = 0U; queue_index < queue_family_property.queueCount; ++queue_index)
        {
            queues[queue_family_index].emplace_back(*this, queue_family_index, queue_family_property, present_supported, queue_index);
        }
    }
    */
    /*
    String extStr = (const char*)glGetString(GL_EXTENSIONS);
    _extensions = StringUtil::Split(extStr, " ");

    _features[(int)GFXFeature::TEXTURE_FLOAT] = true;
    _features[(int)GFXFeature::TEXTURE_HALF_FLOAT] = true;
    _features[(int)GFXFeature::FORMAT_R11G11B10F] = true;
    _features[(int)GFXFeature::FORMAT_D24S8] = true;
    _features[(int)GFXFeature::MSAA] = true;
    _features[(int)GFXFeature::INSTANCED_ARRAYS] = true;

    if (checkExtension("color_buffer_float"))
        _features[(int)GFXFeature::COLOR_FLOAT] = true;
    
    if (checkExtension("color_buffer_half_float"))
        _features[(int)GFXFeature::COLOR_HALF_FLOAT] = true;
    
    if (checkExtension("texture_float_linear"))
        _features[(int)GFXFeature::TEXTURE_FLOAT_LINEAR] = true;
    
    if (checkExtension("texture_half_float_linear"))
        _features[(int)GFXFeature::TEXTURE_HALF_FLOAT_LINEAR] = true;

    String compressed_fmts;

    if (checkExtension("compressed_ETC1"))
    {
        _features[(int)GFXFeature::FORMAT_ETC1] = true;
        compressed_fmts += "etc1 ";
    }

    _features[(int)GFXFeature::FORMAT_ETC2] = true;
    compressed_fmts += "etc2 ";

    if (checkExtension("texture_compression_pvrtc"))
    {
        _features[(int)GFXFeature::FORMAT_PVRTC] = true;
        compressed_fmts += "pvrtc ";
    }

    if (checkExtension("texture_compression_astc"))
    {
        _features[(int)GFXFeature::FORMAT_ASTC] = true;
        compressed_fmts += "astc ";
    }

    _renderer = (const char*)glGetString(GL_RENDERER);
    _vendor = (const char*)glGetString(GL_VENDOR);
    _version = (const char*)glGetString(GL_VERSION);

    CC_LOG_INFO("RENDERER: %s", _renderer.c_str());
    CC_LOG_INFO("VENDOR: %s", _vendor.c_str());
    CC_LOG_INFO("VERSION: %s", _version.c_str());
    CC_LOG_INFO("SCREEN_SIZE: %d x %d", _width, _height);
    CC_LOG_INFO("NATIVE_SIZE: %d x %d", _nativeWidth, _nativeHeight);
    CC_LOG_INFO("USE_VAO: %s", _useVAO ? "true" : "false");
    CC_LOG_INFO("COMPRESSED_FORMATS: %s", compressed_fmts.c_str());

    GFXWindowInfo window_info;
    window_info.colorFmt = _context->getColorFormat();
    window_info.depthStencilFmt = _context->getDepthStencilFormat();
    window_info.isOffscreen = false;
    _window = createWindow(window_info);

    GFXQueueInfo queue_info;
    queue_info.type = GFXQueueType::GRAPHICS;
    _queue = createQueue(queue_info);

    GFXCommandAllocatorInfo cmd_alloc_info;
    _cmdAllocator = createCommandAllocator(cmd_alloc_info);

    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_maxVertexAttributes);
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &_maxVertexUniformVectors);
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &_maxFragmentUniformVectors);
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &_maxTextureUnits);
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &_maxVertexTextureUnits);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTextureSize);
    glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &_maxCubeMapTextureSize);
    glGetIntegerv(GL_DEPTH_BITS, &_depthBits);
    glGetIntegerv(GL_STENCIL_BITS, &_stencilBits);
    glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &_maxCubeMapTextureSize);
    */
    return true;
}

void CCVKDevice::destroy()
{
    CC_SAFE_DESTROY(_cmdAllocator);
    CC_SAFE_DESTROY(_queue);
    CC_SAFE_DESTROY(_window);
    CC_SAFE_DESTROY(_context);
    CC_SAFE_DELETE(stateCache);
}

void CCVKDevice::resize(uint width, uint height)
{
  
}

void CCVKDevice::present()
{
    ((CCVKCommandAllocator*)_cmdAllocator)->releaseCmds();
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
