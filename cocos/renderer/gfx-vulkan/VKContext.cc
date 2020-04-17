#include "VKStd.h"
#include "VKContext.h"

 #define CC_GFX_DEBUG

NS_CC_BEGIN

#ifdef CC_GFX_DEBUG
VKAPI_ATTR VkBool32 VKAPI_CALL debugUtilsMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT *callbackData, void * user_data)
{
    // Log debug messge
    if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
    {
        CC_LOG_WARNING(StringUtil::Format("%s - %s: %s", callbackData->messageIdNumber, callbackData->pMessageIdName, callbackData->pMessage).c_str());
    }
    else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
    {
        CC_LOG_ERROR(StringUtil::Format("%s - %s: %s", callbackData->messageIdNumber, callbackData->pMessageIdName, callbackData->pMessage).c_str());
        assert(0);
    }
    return VK_FALSE;
}

VKAPI_ATTR VkBool32 VKAPI_CALL debugReportCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT type,
    uint64_t object, size_t location, int32_t messageCode, const char *layerPrefix, const char *message, void *userData)
{
  if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
  {
      CC_LOG_ERROR(StringUtil::Format("VError: %s: %s", layerPrefix, message).c_str());
  }
  else if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT)
  {
      CC_LOG_ERROR(StringUtil::Format("VWarning: %s: %s", layerPrefix, message).c_str());
  }
  else if (flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT)
  {
      CC_LOG_INFO(StringUtil::Format("VPerfWarning: %s: %s", layerPrefix, message).c_str());
  }
  else
  {
      CC_LOG_INFO(StringUtil::Format("VInfo: %s: %s", layerPrefix, message).c_str());
  }
  return VK_FALSE;
}
#endif

bool validate_layers(const std::vector<const char *>& required, const std::vector<VkLayerProperties> &available)
{
    for (auto layer : required)
    {
        bool found = false;
        for (auto &availableLayer : available)
        {
            if (strcmp(availableLayer.layerName, layer) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            CC_LOG_INFO(StringUtil::Format("Validation Layer %s not found", layer).c_str());
            return false;
        }
    }

    return true;
}

std::vector<const char *> get_optimal_validation_layers(const std::vector<VkLayerProperties> &supportedInstanceLayers)
{
    std::vector<std::vector<const char *>> validationLayerPriorityList =
    {
        // The preferred validation layer is "VK_LAYER_KHRONOS_validation"
        {"VK_LAYER_KHRONOS_validation"},

        // Otherwise we fallback to using the LunarG meta layer
        {"VK_LAYER_LUNARG_standard_validation"},

        // Otherwise we attempt to enable the individual layers that compose the LunarG meta layer since it doesn't exist
        {
            "VK_LAYER_GOOGLE_threading",
            "VK_LAYER_LUNARG_parameter_validation",
            "VK_LAYER_LUNARG_object_tracker",
            "VK_LAYER_LUNARG_core_validation",
            "VK_LAYER_GOOGLE_unique_objects",
        },

        // Otherwise as a last resort we fallback to attempting to enable the LunarG core layer
        {"VK_LAYER_LUNARG_core_validation"}
    };

    for (auto &validationLayers : validationLayerPriorityList)
    {
        if (validate_layers(validationLayers, supportedInstanceLayers))
        {
            return validationLayers;
        }

        CC_LOG_INFO("Couldn't enable validation layers (see log for error) - falling back");
    }

    // Else return nothing
    return {};
}

bool validateExtensions(const std::vector<const char *>& required, const std::vector<VkExtensionProperties> &available)
{
    for (auto extension : required)
    {
        bool found = false;
        for (auto &availableExtension : available)
        {
            if (strcmp(availableExtension.extensionName, extension) == 0)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            return false;
        }
    }

    return true;
}

CCVKContext::CCVKContext(GFXDevice* device)
    : GFXContext(device){
}

CCVKContext::~CCVKContext() {
}

#if (CC_PLATFORM == CC_PLATFORM_WINDOWS || CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_MAC_OSX)

bool CCVKContext::initialize(const GFXContextInfo &info) {
  
    _vsyncMode = info.vsyncMode;
    _windowHandle = info.windowHandle;

    //////////////////////////////////////////////////////////////////////////

    if (!info.sharedCtx)
    {
        _isPrimaryContex = true;
        _windowHandle = info.windowHandle;

        if (volkInitialize())
        {
            return false;
        }

        uint32_t instanceExtensionCount;
        VK_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, nullptr));

        std::vector<VkExtensionProperties> availableInstanceExtensions(instanceExtensionCount);
        VK_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCount, availableInstanceExtensions.data()));

        std::vector<const char *> enabledExtensions({ VK_KHR_SURFACE_EXTENSION_NAME });

#ifdef CC_GFX_DEBUG
        // Check if VK_EXT_debug_utils is supported, which supersedes VK_EXT_Debug_Report
        bool debugUtils = false;
        for (auto &availableExtension : availableInstanceExtensions)
        {
            if (strcmp(availableExtension.extensionName, VK_EXT_DEBUG_UTILS_EXTENSION_NAME) == 0)
            {
                debugUtils = true;
                CC_LOG_INFO(StringUtil::Format("%s is available, enabling it", VK_EXT_DEBUG_UTILS_EXTENSION_NAME).c_str());
                enabledExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            }
        }
        if (!debugUtils)
        {
            enabledExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
        }
#endif

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
        enabledExtensions.push_back(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_WIN32_KHR)
        enabledExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
        enabledExtensions.push_back(VK_MVK_MACOS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_XCB_KHR)
        enabledExtensions.push_back(VK_KHR_XCB_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_DISPLAY_KHR)
        enabledExtensions.push_back(VK_KHR_DISPLAY_EXTENSION_NAME);
#else
#   pragma error Platform not supported
#endif

        uint32_t instanceLayerCount;
        VK_CHECK(vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr));

        std::vector<VkLayerProperties> supportedValidationLayers(instanceLayerCount);
        VK_CHECK(vkEnumerateInstanceLayerProperties(&instanceLayerCount, supportedValidationLayers.data()));

        std::vector<const char *> requestedValidationLayers;

#ifdef CC_GFX_DEBUG
        // Determine the optimal validation layers to enable that are necessary for useful debugging
        std::vector<const char *> optimalValidationLayers = get_optimal_validation_layers(supportedValidationLayers);
        requestedValidationLayers.insert(requestedValidationLayers.end(), optimalValidationLayers.begin(), optimalValidationLayers.end());
#endif

        if (validate_layers(requestedValidationLayers, supportedValidationLayers))
        {
            CC_LOG_INFO("Enabled Validation Layers:");
            for (const auto &layer : requestedValidationLayers)
            {
                CC_LOG_INFO(StringUtil::Format("	\t%s", layer).c_str());
            }
        }
        else
        {
            return false;
        }

        VkApplicationInfo app{ VK_STRUCTURE_TYPE_APPLICATION_INFO };
        app.pApplicationName = "";
        app.pEngineName = "Cocos Creator 3D";
        app.apiVersion = VK_MAKE_VERSION(1, 0, 0);

        VkInstanceCreateInfo instanceInfo{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
        instanceInfo.pApplicationInfo = &app;
        instanceInfo.enabledExtensionCount = static_cast<uint32_t>(enabledExtensions.size());
        instanceInfo.ppEnabledExtensionNames = enabledExtensions.data();
        instanceInfo.enabledLayerCount = static_cast<uint32_t>(requestedValidationLayers.size());
        instanceInfo.ppEnabledLayerNames = requestedValidationLayers.data();

#ifdef CC_GFX_DEBUG
        VkDebugUtilsMessengerCreateInfoEXT debugUtilsCreateInfo = { VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT };
        VkDebugReportCallbackCreateInfoEXT debugReportCreateInfo = { VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT };
        if (debugUtils)
        {
            debugUtilsCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
            debugUtilsCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
            debugUtilsCreateInfo.pfnUserCallback = debugUtilsMessengerCallback;

            instanceInfo.pNext = &debugUtilsCreateInfo;
        }
        else
        {
            debugReportCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
            debugReportCreateInfo.pfnCallback = debugReportCallback;

            instanceInfo.pNext = &debugReportCreateInfo;
        }
#endif

        // Create the Vulkan instance
        VK_CHECK(vkCreateInstance(&instanceInfo, nullptr, &_instance));

        volkLoadInstance(_instance);

#ifdef CC_GFX_DEBUG
        if (debugUtils)
        {
            VK_CHECK(vkCreateDebugUtilsMessengerEXT(_instance, &debugUtilsCreateInfo, nullptr, &_debugUtilsMessenger));
        }
        else
        {
            VK_CHECK(vkCreateDebugReportCallbackEXT(_instance, &debugReportCreateInfo, nullptr, &_debugReport));
        }
#endif

        // Querying valid physical devices on the machine
        uint32_t physicalDeviceCount{ 0 };
        VK_CHECK(vkEnumeratePhysicalDevices(_instance, &physicalDeviceCount, nullptr));

        if (physicalDeviceCount < 1)
        {
            return false;
        }

        _physicalDevices.resize(physicalDeviceCount);
        VK_CHECK(vkEnumeratePhysicalDevices(_instance, &physicalDeviceCount, _physicalDevices.data()));

      /*
  #if (CC_PLATFORM == CC_PLATFORM_WINDOWS)
      _nativeDisplay = (NativeDisplayType)GetDC((HWND)_windowHandle);
      if (!_nativeDisplay) {
        return false;
      }

      _eglDisplay = eglGetDisplay(_nativeDisplay);
      if (_eglDisplay == EGL_NO_DISPLAY) {
        _eglDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
      }
  #else
      _eglDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
  #endif
      // If a display still couldn't be obtained, return an error.
      if (_eglDisplay == EGL_NO_DISPLAY) {
        CC_LOG_ERROR("eglGetDisplay() - FAILED.");
        return false;
      }

      EGLint major = 0;
      EGLint minor = 0;
      if (eglInitialize(_eglDisplay, &major, &minor) != EGL_TRUE) {
        CC_LOG_ERROR("Couldn't initialize EGLDisplay.");
        return false;
      }

      //	Make OpenGL ES the current API.
      //	EGL needs a way to know that any subsequent EGL calls are going to be affecting OpenGL ES,
      //	rather than any other API (such as OpenVG).
      eglBindAPI(EGL_OPENGL_ES_API);

      if (!gles3wInit())
      {
        return false;
      }

      _colorFmt = GFXFormat::RGBA8;
      _depthStencilFmt = GFXFormat::D24S8;

      const EGLint attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT | EGL_PBUFFER_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
        // EGL_BUFFER_SIZE, colorBuffSize,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_STENCIL_SIZE, 8,
        EGL_NONE
      };

      //	Find a suitable EGLConfig
      //	eglChooseConfig is provided by EGL to provide an easy way to select an appropriate configuration. It takes in the capabilities
      //	specified in the attribute list, and returns a list of available configurations that match or exceed the capabilities requested.
      //	Details of all the possible attributes and how they are selected for by this function are available in the EGL reference pages here:
      //	http://www.khronos.org/registry/egl/sdk/docs/man/xhtml/eglChooseConfig.html
      //	It is also possible to simply get the entire list of configurations and use a custom algorithm to choose a suitable one, as many
      //	advanced applications choose to do. For this application however, taking the first EGLConfig that the function returns suits
      //	its needs perfectly, so we limit it to returning a single EGLConfig.

      EGLint num_configs;
      if (eglChooseConfig(_eglDisplay, attribs, &_eglConfig, 1, &num_configs) == EGL_FALSE || num_configs <= 0)
      {
        CC_LOG_ERROR("Choosing configuration failed.");
        return false;
      }

      EGLint depth = attribs[13];
      EGLint stencil = attribs[15];
      CC_LOG_INFO("Setup EGLConfig: depth [%d] stencil [%d]", depth, stencil);

      if (depth == 16 && stencil == 0) {
        _depthStencilFmt = GFXFormat::D16;
      } else if (depth == 16 && stencil == 8) {
        _depthStencilFmt = GFXFormat::D16S8;
      } else if (depth == 24 && stencil == 0) {
        _depthStencilFmt = GFXFormat::D24;
      } else if (depth == 24 && stencil == 8) {
        _depthStencilFmt = GFXFormat::D24S8;
      } else if (depth == 32 && stencil == 0) {
        _depthStencilFmt = GFXFormat::D32F;
      } else if (depth == 32 && stencil == 8) {
        _depthStencilFmt = GFXFormat::D32F_S8;
      } else {
        CC_LOG_ERROR("Unknown depth stencil format.");
        return false;
      }
      CC_LOG_INFO("Chosen EGLConfig: color [%s], depth stencil [%s].",
        GFX_FORMAT_INFOS[(int)_colorFmt].name.c_str(),
        GFX_FORMAT_INFOS[(int)_depthStencilFmt].name.c_str());
      */

      /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
      * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
      * As soon as we picked a EGLConfig, we can safely reconfigure the
      * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
      /*
  #if (CC_PLATFORM == CC_PLATFORM_ANDROID)
      EGLint n_fmt;
      if (eglGetConfigAttrib(_eglDisplay, _eglConfig, EGL_NATIVE_VISUAL_ID, &n_fmt) == EGL_FALSE) {
        CC_LOG_ERROR("Getting configuration attributes failed.");
        return false;
      }

      uint width = _device->getWidth();
      uint height = _device->getHeight();
      ANativeWindow_setBuffersGeometry((ANativeWindow*)_windowHandle, width, height, n_fmt);
  #endif

      _eglSurface = eglCreateWindowSurface(_eglDisplay, _eglConfig, (EGLNativeWindowType)_windowHandle, NULL);
      if (_eglSurface == EGL_NO_SURFACE) {
        CC_LOG_ERROR("Window surface created failed.");
        return false;
      }

      //String egl_vendor = eglQueryString(_eglDisplay, EGL_VENDOR);
      //String egl_version = eglQueryString(_eglDisplay, EGL_VERSION);

      _extensions = StringUtil::Split((const char*)eglQueryString(_eglDisplay, EGL_EXTENSIONS), " ");

      _majorVersion = 3;
      _minorVersion = 0;
      EGLint ctx_attribs[32];
      uint n = 0;

      bool has_khr_create_ctx = CheckExtension(CC_TOSTR(EGL_KHR_create_context));
      if (has_khr_create_ctx) {
        for (int m = 2; m >= 0; --m) {
          n = 0;
          ctx_attribs[n++] = EGL_CONTEXT_MAJOR_VERSION_KHR;
          ctx_attribs[n++] = _majorVersion;
          ctx_attribs[n++] = EGL_CONTEXT_MINOR_VERSION_KHR;
          ctx_attribs[n++] = m;

  #ifdef CC_GFX_DEBUG
          ctx_attribs[n++] = EGL_CONTEXT_FLAGS_KHR;
          ctx_attribs[n++] = EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR;
  #endif
          ctx_attribs[n] = EGL_NONE;

          _eglContext = eglCreateContext(_eglDisplay, _eglConfig, NULL, ctx_attribs);
          if (_eglContext) {
            _minorVersion = m;
            break;
          }
        }
      } else {
        ctx_attribs[n++] = EGL_CONTEXT_CLIENT_VERSION;
        ctx_attribs[n++] = _majorVersion;
        ctx_attribs[n] = EGL_NONE;
        _eglContext = eglCreateContext(_eglDisplay, _eglConfig, NULL, ctx_attribs);
      }

      if (!_eglContext) {
        CC_LOG_ERROR("Create EGL context failed.");
        return false;
      }

      _eglSharedContext = _eglContext;
      */
    } else {
      CCVKContext* sharedCtx = (CCVKContext*)info.sharedCtx;

      _majorVersion = sharedCtx->majorVersion();
      _minorVersion = sharedCtx->minorVersion();
      /*
      _nativeDisplay = sharedCtx->native_display();
      _eglDisplay = sharedCtx->egl_display();
      _eglConfig = sharedCtx->egl_config();
      _eglSharedContext = sharedCtx->egl_shared_ctx();
      _colorFmt = sharedCtx->getColorFormat();
      _depthStencilFmt = sharedCtx->getDepthStencilFormat();

      EGLint pbuff_attribs[] =
      {
        EGL_WIDTH, 2,
        EGL_HEIGHT, 2,
        EGL_LARGEST_PBUFFER, EGL_TRUE,
        EGL_TEXTURE_FORMAT, EGL_NO_TEXTURE,
        EGL_TEXTURE_TARGET, EGL_NO_TEXTURE,
        EGL_NONE
      };

      _eglSurface = eglCreatePbufferSurface(_eglDisplay, _eglConfig, pbuff_attribs);
      if (_eglSurface == EGL_NO_SURFACE) {
        CC_LOG_ERROR("eglCreatePbufferSurface - FAILED");
        return false;
      }

      _majorVersion = 3;
      _minorVersion = sharedCtx->minor_ver();

      bool has_khr_create_ctx = CheckExtension(CC_TOSTR(EGL_KHR_create_context));
      if (!has_khr_create_ctx)
      {
        CC_LOG_INFO("EGL context creation: EGL_KHR_create_context not supported. Minor version will be discarded, and debug disabled.");
        _minorVersion = 0;
      }

      EGLint ctx_attribs[32];
      uint n = 0;

      if (has_khr_create_ctx)
      {
        ctx_attribs[n++] = EGL_CONTEXT_MAJOR_VERSION_KHR;
        ctx_attribs[n++] = _majorVersion;
        ctx_attribs[n++] = EGL_CONTEXT_MINOR_VERSION_KHR;
        ctx_attribs[n++] = _minorVersion;

  #ifdef CC_GFX_DEBUG
        ctx_attribs[n++] = EGL_CONTEXT_FLAGS_KHR;
        ctx_attribs[n++] = EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR;
  #endif
      }
      else
      {
        ctx_attribs[n++] = EGL_CONTEXT_CLIENT_VERSION;
        ctx_attribs[n++] = _majorVersion;
      }

      ctx_attribs[n] = EGL_NONE;

      _eglContext = eglCreateContext(_eglDisplay, _eglConfig, _eglSharedContext, ctx_attribs);
      if (!_eglContext) {
        CC_LOG_ERROR("Create EGL context with share context [0x%p] failed.", _eglSharedContext);
        return false;
      }
    */
    }
    if (!MakeCurrent()) {
        return false;
    }

    return true;
}

void CCVKContext::destroy() {
    /*
  if (_eglContext != EGL_NO_CONTEXT) {
    eglDestroyContext(_eglDisplay, _eglContext);
    _eglContext = EGL_NO_CONTEXT;
  }

  if (_eglSurface != EGL_NO_SURFACE) {
    eglDestroySurface(_eglDisplay, _eglSurface);
    _eglSurface = EGL_NO_SURFACE;
  }

  eglMakeCurrent(_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

#if (CC_PLATFORM == CC_PLATFORM_WINDOWS)
  if (_isPrimaryContex && _nativeDisplay)
  {
    ReleaseDC((HWND)_windowHandle, _nativeDisplay);
  }
#endif

  _isPrimaryContex = false;
  _windowHandle = 0;
  _nativeDisplay = 0;
  _vsyncMode = GFXVsyncMode::OFF;
  _isInitialized = false;
    */

#ifdef CC_GFX_DEBUG
    if (_debugUtilsMessenger != VK_NULL_HANDLE)
    {
        vkDestroyDebugUtilsMessengerEXT(_instance, _debugUtilsMessenger, nullptr);
    }
    if (_debugReport != VK_NULL_HANDLE)
    {
        vkDestroyDebugReportCallbackEXT(_instance, _debugReport, nullptr);
    }
#endif

    if (_instance != VK_NULL_HANDLE)
    {
        vkDestroyInstance(_instance, nullptr);
    }
}

bool CCVKContext::MakeCurrentImpl() {
  //return eglMakeCurrent(_eglDisplay, _eglSurface, _eglSurface, _eglContext);
    return true;
}

void CCVKContext::present() {
  //eglSwapBuffers(_eglDisplay, _eglSurface);
}

#endif

bool CCVKContext::MakeCurrent() {
//  if (MakeCurrentImpl()) {
//    if (!_isInitialized) {
//#if (CC_PLATFORM == CC_PLATFORM_WINDOWS || CC_PLATFORM == CC_PLATFORM_ANDROID)
//      // Turn on or off the vertical sync depending on the input bool value.
//      int interval = 1;
//      switch (_vsyncMode) {
//      case GFXVsyncMode::OFF: interval = 0; break;
//      case GFXVsyncMode::ON: interval = 1; break;
//      case GFXVsyncMode::RELAXED: interval = -1; break;
//      case GFXVsyncMode::MAILBOX: interval = 0; break;
//      case GFXVsyncMode::HALF: interval = 2; break;
//      default:;
//      }
//
//      if (eglSwapInterval(_eglDisplay, interval) != 1) {
//        CC_LOG_ERROR("wglSwapInterval() - FAILED.");
//        return false;
//      }
//#endif
//
//#if defined(CC_GFX_DEBUG)
//      glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR);
//      glDebugMessageControlKHR(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
//      glDebugMessageCallbackKHR(VKEGLDebugProc, NULL);
//#endif
//
//      //////////////////////////////////////////////////////////////////////////
//
//      glPixelStorei(GL_PACK_ALIGNMENT, 1);
//      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//      glActiveTexture(GL_TEXTURE0);
//
//      //////////////////////////////////////////////////////////////////////////
//
//      glEnable(GL_CULL_FACE);
//      glCullFace(GL_BACK);
//
//      glFrontFace(GL_CCW);
//
//      //glDisable(GL_MULTISAMPLE);
//
//      //////////////////////////////////////////////////////////////////////////
//      // DepthStencilState
//      glEnable(GL_DEPTH_TEST);
//      glDepthMask(GL_TRUE);
//      glDepthFunc(GL_LESS);
//
//      glStencilFuncSeparate(GL_FRONT, GL_ALWAYS, 1, 0xffffffff);
//      glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_KEEP, GL_KEEP);
//      glStencilMaskSeparate(GL_FRONT, 0xffffffff);
//      glStencilFuncSeparate(GL_BACK, GL_ALWAYS, 1, 0xffffffff);
//      glStencilOpSeparate(GL_BACK, GL_KEEP, GL_KEEP, GL_KEEP);
//      glStencilMaskSeparate(GL_BACK, 0xffffffff);
//
//      glDisable(GL_STENCIL_TEST);
//
//      //////////////////////////////////////////////////////////////////////////
//      // BlendState
//
//      glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
//      glDisable(GL_BLEND);
//      glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
//      glBlendFuncSeparate(GL_ONE, GL_ZERO, GL_ONE, GL_ZERO);
//      glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
//      glBlendColor((GLclampf)0.0f, (GLclampf)0.0f, (GLclampf)0.0f, (GLclampf)0.0f);
//
//      _isInitialized = true;
//    }
//
//    CC_LOG_DEBUG("eglMakeCurrent() - SUCCESSED, Context: 0x%p", this);
//    return true;
//  } else {
//    CC_LOG_ERROR("MakeCurrent() - FAILED, Context: 0x%p", this);
//    return false;
//  }
    return true;
}

bool CCVKContext::CheckExtension(const String& extension) const {
  //return (std::find(_extensions.begin(), _extensions.end(), extension) != _extensions.end());
    return false;
}

NS_CC_END
