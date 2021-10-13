/****************************************************************************
 Copyright (c) 2021 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#include "ar/android/ARCoreAPIImpl.h"
#include "platform/java/jni/JniHelper.h"
#include "platform/java/jni/JniImp.h"

#ifndef JCLS_ARAPI
#define JCLS_ARAPI "com/cocos/lib/CocosARCoreAPI"
#endif
#define JARG_ARAPI "L" JCLS_ARAPI ";"

namespace cc {
namespace ar {

ARCoreAPIImpl::ARCoreAPIImpl() : _impl(nullptr) {
    DLLOG("Construct ARCoreImpl: %p", this);
    JniMethodInfo methodInfo;
    if (JniHelper::getStaticMethodInfo(methodInfo, 
                                        JCLS_ARAPI,
                                        "init",
                                        "()" JARG_ARAPI)) {
        jobject jObj = methodInfo.env->CallStaticObjectMethod(
                methodInfo.classID,
                methodInfo.methodID
        );
        _impl = methodInfo.env->NewGlobalRef(jObj);
        DLLOG("ARCoreImpl: jObj: %p, _impl: %p", jObj, _impl);
        methodInfo.env->DeleteLocalRef(jObj);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
}

ARCoreAPIImpl::~ARCoreAPIImpl() {
    if(_impl != nullptr) {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                            JCLS_ARAPI,
                                            "onDestroy",
                                            "(" JARG_ARAPI ")V")) {
            methodInfo.env->CallStaticVoidMethod(
                    methodInfo.classID,
                    methodInfo.methodID,
                    _impl
            );
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
        JniHelper::getEnv()->DeleteGlobalRef(_impl);
    }
    DLLOG("Destruct ARCoreImpl: %p", this);
}

void ARCoreAPIImpl::start() {
    if(_impl != nullptr) {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                            JCLS_ARAPI,
                                            "start",
                                            "(" JARG_ARAPI ")V")) {
            methodInfo.env->CallStaticVoidMethod(
                    methodInfo.classID,
                    methodInfo.methodID,
                    _impl
            );
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }
}

void ARCoreAPIImpl::update() {
    if(_impl != nullptr) {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                            JCLS_ARAPI,
                                            "update",
                                            "(" JARG_ARAPI ")V")) {
            methodInfo.env->CallStaticVoidMethod(
                    methodInfo.classID,
                    methodInfo.methodID,
                    _impl
            );
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }
}

void ARCoreAPIImpl::setCameraTextureName(int id) {
    if(_impl != nullptr) {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                            JCLS_ARAPI,
                                            "setCameraTextureName",
                                            "(" JARG_ARAPI "I" ")V")) {
            methodInfo.env->CallStaticVoidMethod(
                    methodInfo.classID,
                    methodInfo.methodID,
                    _impl,
                    id
            );
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }
}

float* ARCoreAPIImpl::getCameraPose() {
    if(_impl != nullptr) {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                            JCLS_ARAPI,
                                            "getCameraPose",
                                            "(" JARG_ARAPI ")[F"))
        {
            auto *array = static_cast<jfloatArray>(methodInfo.env->CallStaticObjectMethod(
                    methodInfo.classID,
                    methodInfo.methodID,
                    _impl
            ));
            jsize len = methodInfo.env->GetArrayLength(array);
            if (len <= 7) {
                jfloat* elems = methodInfo.env->GetFloatArrayElements(array, nullptr);
                if (elems) {
                    memcpy(_cameraPose, elems, sizeof(float) * len);
                    methodInfo.env->ReleaseFloatArrayElements(array, elems, 0);
                };
            }
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }
    return _cameraPose->data();
}

float* ARCoreAPIImpl::getCameraViewMatrix() {
    if(_impl != nullptr) {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                            JCLS_ARAPI,
                                            "getCameraViewMatrix",
                                            "(" JARG_ARAPI ")[F")) {
            auto *array = static_cast<jfloatArray>(methodInfo.env->CallStaticObjectMethod(
                    methodInfo.classID,
                    methodInfo.methodID,
                    _impl
            ));
            jsize len = methodInfo.env->GetArrayLength(array);
            if (len <= 16) {
                jfloat* elems = methodInfo.env->GetFloatArrayElements(array, nullptr);
                if (elems) {
                    memcpy(_viewMatrix, elems, sizeof(float) * len);
                    methodInfo.env->ReleaseFloatArrayElements(array, elems, 0);
                };
            }
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }
    return _viewMatrix->data();
}

float* ARCoreAPIImpl::getCameraProjectionMatrix() {
    if(_impl != nullptr) {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                            JCLS_ARAPI,
                                            "getCameraProjectionMatrix",
                                            "(" JARG_ARAPI ")[F")) {
            auto *array = static_cast<jfloatArray>(methodInfo.env->CallStaticObjectMethod(
                    methodInfo.classID,
                    methodInfo.methodID,
                    _impl
            ));
            jsize len = methodInfo.env->GetArrayLength(array);
            if (len <= 16) {
                jfloat* elems = methodInfo.env->GetFloatArrayElements(array, nullptr);
                if (elems) {
                    memcpy(_projMatrix, elems, sizeof(float) * len);
                    methodInfo.env->ReleaseFloatArrayElements(array, elems, 0);
                };
            }
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }
    return _projMatrix->data();
}

float* ARCoreAPIImpl::getCameraTexCoords() {
    if(_impl != nullptr) {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo,
                                            JCLS_ARAPI,
                                            "getCameraTexCoords",
                                            "(" JARG_ARAPI ")[F")) {
            auto *array = static_cast<jfloatArray>(methodInfo.env->CallStaticObjectMethod(
                    methodInfo.classID,
                    methodInfo.methodID,
                    _impl
            ));
            jsize len = methodInfo.env->GetArrayLength(array);
            if (len <= 8) {
                jfloat* elems = methodInfo.env->GetFloatArrayElements(array, nullptr);
                if (elems) {
                    memcpy(_cameraTexCoords, elems, sizeof(float) * len);
                    methodInfo.env->ReleaseFloatArrayElements(array, elems, 0);
                };
            }
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
    }
    return _cameraTexCoords->data();
}

} // namespace ar
} // namespace cc