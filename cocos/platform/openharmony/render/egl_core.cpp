/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "egl_core.h"
#include "platform/openharmony/napi/NapiHelper.h"

EGLConfig getConfig(int version, EGLDisplay eglDisplay) {
    int attribList[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_STENCIL_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_NONE
    };
    EGLConfig configs = NULL;
    int configsNum;
    if (!eglChooseConfig(eglDisplay, attribList, &configs, 1, &configsNum)) {
        LOGE("eglChooseConfig ERROR");
        return NULL;
    }
    return configs;
}

void EGLCore::GLContextInit(void* window, int w, int h)
{
    LOGD("EGLCore::GLContextInit window = %{public}p, w = %{public}d, h = %{public}d.", window, w, h);
    width_ = w;
    height_ = h;
    mEglWindow = (EGLNativeWindowType)(window);

    // 1. create sharedcontext
    mEGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (mEGLDisplay == EGL_NO_DISPLAY) {
        LOGE("EGLCore::unable to get EGL display.");
        return;
    }

    EGLint eglMajVers, eglMinVers;
    if (!eglInitialize(mEGLDisplay, &eglMajVers, &eglMinVers)) {
        mEGLDisplay = EGL_NO_DISPLAY;
        LOGE("EGLCore::unable to initialize display");
        return;
    }

    mEGLConfig = getConfig(3, mEGLDisplay);
    if (mEGLConfig == nullptr) {
        LOGE("EGLCore::GLContextInit config ERROR");
        return;
    }

    // 2. Create EGL Surface from Native Window
    if (mEglWindow) {
        mEGLSurface = eglCreateWindowSurface(mEGLDisplay, mEGLConfig, mEglWindow, nullptr);
        if (mEGLSurface == nullptr) {
            LOGE("EGLCore::eglCreateContext eglSurface is null");
            return;
        }
    }

    // 3. Create EGLContext from
    int attrib3_list[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    mEGLContext = eglCreateContext(mEGLDisplay, mEGLConfig, mSharedEGLContext, attrib3_list);

    if (!eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext)) {
        LOGE("EGLCore::eglMakeCurrent error = %{public}d", eglGetError());
    }
}

void EGLCore::Update()
{
    eglSwapBuffers(mEGLDisplay, mEGLSurface);
}

bool EGLCore::checkGlError(const char* op)
{
    LOGE("EGL ERROR CODE = %{public}x", eglGetError());
    GLint error;
    for (error = glGetError(); error; error = glGetError()) {
        LOGE("ERROR: %{public}s, ERROR CODE = %{public}x", op, error);
        return true;
    }
    return false;
}