#include "GLES3Swapchain.h"
#include "GLES3Device.h"
#include "GLES3GPUObjects.h"
#include "GLES3Texture.h"

#if (CC_PLATFORM == CC_PLATFORM_ANDROID)
    #include "android/native_window.h"
#elif CC_PLATFORM == CC_PLATFORM_OHOS
    #include <native_layer.h>
    #include <native_layer_jni.h>
#endif

namespace cc {
namespace gfx {

GLES3Swapchain::GLES3Swapchain() {
    _typedID = generateObjectID<decltype(this)>();
}

GLES3Swapchain::~GLES3Swapchain() {
    destroy();
}

void GLES3Swapchain::doInit(const SwapchainInfo& info) {
    const auto* context = GLES3Device::getInstance()->context();
    _gpuSwapchain       = CC_NEW(GLES3GPUSwapchain);
    auto* window        = reinterpret_cast<EGLNativeWindowType>(info.windowHandle);

#if CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_OHOS
    EGLint nFmt;
    if (eglGetConfigAttrib(context->eglDisplay, context->eglConfig, EGL_NATIVE_VISUAL_ID, &nFmt) == EGL_FALSE) {
        CC_LOG_ERROR("Getting configuration attributes failed.");
        return;
    }

    auto width  = static_cast<int32_t>(info.width);
    auto height = static_cast<int32_t>(info.height);

    #if CC_PLATFORM == CC_PLATFORM_ANDROID
    ANativeWindow_setBuffersGeometry(window, width, height, nFmt);
    #elif CC_PLATFORM == CC_PLATFORM_OHOS
    NativeLayerHandle(window, NativeLayerOps::SET_WIDTH_AND_HEIGHT, width, height);
    NativeLayerHandle(window, NativeLayerOps::SET_FORMAT, nFmt);
    #endif
#endif

    EGL_CHECK(_gpuSwapchain->eglSurface = eglCreateWindowSurface(context->eglDisplay, context->eglConfig, window, nullptr));
    if (_gpuSwapchain->eglSurface == EGL_NO_SURFACE) {
        CC_LOG_ERROR("Create window surface failed.");
        return;
    }

    switch (_vsyncMode) {
        case VsyncMode::OFF: _gpuSwapchain->eglSwapInterval = 0; break;
        case VsyncMode::ON:
        case VsyncMode::RELAXED: _gpuSwapchain->eglSwapInterval = 1; break;
        case VsyncMode::MAILBOX: _gpuSwapchain->eglSwapInterval = 0; break;
        case VsyncMode::HALF: _gpuSwapchain->eglSwapInterval = 2; break;
        default: break;
    }

    ///////////////////// Texture Creation /////////////////////

    _colorTexture        = CC_NEW(GLES3Texture);
    _depthStencilTexture = CC_NEW(GLES3Texture);

    SwapchainTextureInfo textureInfo;
    textureInfo.swapchain = this;
    textureInfo.format    = Format::RGBA8;
    textureInfo.width     = 1;
    textureInfo.height    = 1;
    initTexture(textureInfo, _colorTexture);

    textureInfo.format = Format::DEPTH_STENCIL;
    initTexture(textureInfo, _depthStencilTexture);
}

void GLES3Swapchain::doDestroy() {
    if (!_gpuSwapchain) return;

    CC_SAFE_DESTROY(_depthStencilTexture)
    CC_SAFE_DESTROY(_colorTexture)

    doDestroySurface();
    CC_SAFE_DELETE(_gpuSwapchain);
}

void GLES3Swapchain::doResize(uint32_t width, uint32_t height) {
    _colorTexture->resize(width, height);
    _depthStencilTexture->resize(width, height);
}

void GLES3Swapchain::doDestroySurface() {
    if (_gpuSwapchain->eglSurface != EGL_NO_SURFACE) {
        const auto* context = GLES3Device::getInstance()->context();
        eglDestroySurface(context->eglDisplay, _gpuSwapchain->eglSurface);
        EGL_CHECK(eglMakeCurrent(context->eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT));
        _gpuSwapchain->eglSurface = EGL_NO_SURFACE;
    }
}

void GLES3Swapchain::doCreateSurface(void* windowHandle) {
    auto* context = GLES3Device::getInstance()->context();
    auto* window  = reinterpret_cast<EGLNativeWindowType>(windowHandle);

    EGLint nFmt = 0;
    if (eglGetConfigAttrib(context->eglDisplay, context->eglConfig, EGL_NATIVE_VISUAL_ID, &nFmt) == EGL_FALSE) {
        CC_LOG_ERROR("Getting configuration attributes failed.");
        return;
    }

// Device's size will be updated after recreate window (in resize event) and is incorrect for now.
#if CC_PLATFORM == CC_PLATFORM_ANDROID
    int32_t width  = ANativeWindow_getWidth(window);
    int32_t height = ANativeWindow_getHeight(window);
    ANativeWindow_setBuffersGeometry(window, width, height, nFmt);
#elif CC_PLATFORM == CC_PLATFORM_OHOS
    int32_t width  = NativeLayerHandle(window, NativeLayerOps::GET_WIDTH);
    int32_t height = NativeLayerHandle(window, NativeLayerOps::GET_HEIGHT);
#endif

    EGL_CHECK(_gpuSwapchain->eglSurface = eglCreateWindowSurface(context->eglDisplay, context->eglConfig, window, nullptr));
    if (_gpuSwapchain->eglSurface == EGL_NO_SURFACE) {
        CC_LOG_ERROR("Recreate window surface failed.");
        return;
    }
}

} // namespace gfx
} // namespace cc
