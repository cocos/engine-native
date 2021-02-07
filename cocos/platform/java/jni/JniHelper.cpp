/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "platform/java/jni/JniHelper.h"
#if ANDROID
    #include <android/log.h>
#else
    #include "cocos/base/Log.h"
#endif
#include <pthread.h>
#include <string.h>

#include "base/UTF8.h"

#if ANDROID
    #define LOG_TAG   "JniHelper"
    #define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
    #define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#else
    #define LOGD(...) CC_LOG_DEBUG(__VA_ARGS__)
    #define LOGE(...) CC_LOG_ERROR(__VA_ARGS__)
#endif
static pthread_key_t g_key;

namespace {
class JClassWrapper final {
public:
    JClassWrapper(jclass kls) {
        if (kls) {
            _globalKls = static_cast<jclass>(cc::JniHelper::getEnv()->NewGlobalRef((jobject)kls));
        }
    }
    ~JClassWrapper() {
        if (_globalKls) {
            cc::JniHelper::getEnv()->DeleteGlobalRef(_globalKls);
        }
        _globalKls = nullptr;
    }
    jclass operator*() const {
        return _globalKls;
    }

private:
    jclass _globalKls = {};
};

std::unordered_map<const char *, JClassWrapper> _cachedJClasses;
}; // namespace

jclass _getClassID(const char *className) {
    if (nullptr == className) {
        return nullptr;
    }
    auto it = _cachedJClasses.find(className);
    if (it != _cachedJClasses.end()) {
        return *it->second;
    }

    JNIEnv *env = cc::JniHelper::getEnv();

    jstring _jstrClassName = env->NewStringUTF(className);

    jclass _clazz = (jclass)env->CallObjectMethod(cc::JniHelper::classloader,
                                                  cc::JniHelper::loadclassMethod_methodID,
                                                  _jstrClassName);

    if (nullptr == _clazz || env->ExceptionCheck()) {
        LOGE("Classloader failed to find class of %s", className);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
        }
        env->ExceptionClear();
        _clazz = nullptr;
    }

    env->DeleteLocalRef(_jstrClassName);
    LOGE("1. delete 0x%p", _jstrClassName);

    if (_clazz) {
        _cachedJClasses.emplace(className, _clazz);
    }
    return _clazz;
}

void _detachCurrentThread(void *a) {
    cc::JniHelper::getJavaVM()->DetachCurrentThread();
}

namespace cc {
jmethodID JniHelper::loadclassMethod_methodID = nullptr;
jobject JniHelper::classloader = nullptr;
std::function<void()> JniHelper::classloaderCallback = nullptr;
jobject JniHelper::_activity = nullptr;
JavaVM *JniHelper::_javaVM = nullptr;

JavaVM *JniHelper::getJavaVM() {
    pthread_t thisthread = pthread_self();
    LOGD("JniHelper::getJavaVM(), pthread_self() = %ld", thisthread);
    return JniHelper::_javaVM;
}

void JniHelper::init(JNIEnv *env, jobject activity) {
    env->GetJavaVM(&JniHelper::_javaVM);
    JniHelper::_activity = activity;

    pthread_key_create(&g_key, _detachCurrentThread);
    auto ok = JniHelper::setClassLoaderFrom(activity);
    assert(ok);
}

JNIEnv *JniHelper::cacheEnv() {
    JavaVM *jvm = JniHelper::_javaVM;
    JNIEnv *_env = nullptr;
    // get jni environment
    jint ret = jvm->GetEnv((void **)&_env, JNI_VERSION_1_4);

    switch (ret) {
        case JNI_OK:
            // Success!
            pthread_setspecific(g_key, _env);
            return _env;

        case JNI_EDETACHED:
            // Thread not attached
            if (jvm->AttachCurrentThread((void **)&_env, nullptr) < 0) {
                LOGE("Failed to get the environment using AttachCurrentThread()");

                return nullptr;
            } else {
                // Success : Attached and obtained JNIEnv!
                pthread_setspecific(g_key, _env);
                return _env;
            }

        case JNI_EVERSION:
            // Cannot recover from this error
            LOGE("JNI interface version 1.4 not supported");
        default:
            LOGE("Failed to get the environment using GetEnv()");
            return nullptr;
    }
}

JNIEnv *JniHelper::getEnv() {
    JNIEnv *_env = (JNIEnv *)pthread_getspecific(g_key);
    if (_env == nullptr)
        _env = JniHelper::cacheEnv();
    return _env;
}

jobject JniHelper::getActivity() {
    return _activity;
}

#if CC_PLATFORM == CC_PLATFORM_OHOS
bool JniHelper::setClassLoaderFrom(jobject activityinstance) {
    JniMethodInfo _getclassloaderMethod;
    if (!JniHelper::getMethodInfo_DefaultClassLoader(_getclassloaderMethod,
                                                     "ohos/app/Context",
                                                     "getClassloader", // typo ?
                                                     "()Ljava/lang/ClassLoader;")) {
        return false;
    }

    jobject _c = cc::JniHelper::getEnv()->CallObjectMethod(activityinstance,
                                                           _getclassloaderMethod.methodID);

    if (nullptr == _c) {
        return false;
    }

    JniMethodInfo _m;
    if (!JniHelper::getMethodInfo_DefaultClassLoader(_m,
                                                     "java/lang/ClassLoader",
                                                     "loadClass",
                                                     "(Ljava/lang/String;)Ljava/lang/Class;")) {
        return false;
    }

    JniHelper::classloader = cc::JniHelper::getEnv()->NewGlobalRef(_c);
    JniHelper::loadclassMethod_methodID = _m.methodID;
    JniHelper::_activity = cc::JniHelper::getEnv()->NewGlobalRef(activityinstance);
    if (JniHelper::classloaderCallback != nullptr) {
        JniHelper::classloaderCallback();
    }

    return true;
}
#elif CC_PLATFORM == CC_PLATFORM_ANDROID
bool JniHelper::setClassLoaderFrom(jobject activityinstance) {
    JniMethodInfo _getclassloaderMethod;
    if (!JniHelper::getMethodInfo_DefaultClassLoader(_getclassloaderMethod,
                                                     "android/content/Context",
                                                     "getClassLoader",
                                                     "()Ljava/lang/ClassLoader;")) {
        return false;
    }

    jobject _c = cc::JniHelper::getEnv()->CallObjectMethod(activityinstance,
                                                           _getclassloaderMethod.methodID);

    if (nullptr == _c) {
        return false;
    }

    JniMethodInfo _m;
    if (!JniHelper::getMethodInfo_DefaultClassLoader(_m,
                                                     "java/lang/ClassLoader",
                                                     "loadClass",
                                                     "(Ljava/lang/String;)Ljava/lang/Class;")) {
        return false;
    }

    JniHelper::classloader = cc::JniHelper::getEnv()->NewGlobalRef(_c);
    JniHelper::loadclassMethod_methodID = _m.methodID;
    JniHelper::_activity = cc::JniHelper::getEnv()->NewGlobalRef(activityinstance);
    if (JniHelper::classloaderCallback != nullptr) {
        JniHelper::classloaderCallback();
    }

    return true;
}
#endif

bool JniHelper::getStaticMethodInfo(JniMethodInfo &methodinfo,
                                    const char *className,
                                    const char *methodName,
                                    const char *paramCode) {
    if ((nullptr == className) ||
        (nullptr == methodName) ||
        (nullptr == paramCode)) {
        return false;
    }

    JNIEnv *env = JniHelper::getEnv();
    if (!env) {
        LOGE("Failed to get JNIEnv");
        return false;
    }

    jclass classID = _getClassID(className);
    if (!classID) {
        LOGE("Failed to find class %s", className);
        env->ExceptionClear();
        return false;
    }

    jmethodID methodID = env->GetStaticMethodID(classID, methodName, paramCode);
    if (!methodID) {
        LOGE("Failed to find static method id of %s", methodName);
        env->ExceptionClear();
        return false;
    }

    methodinfo.classID = classID;
    methodinfo.env = env;
    methodinfo.methodID = methodID;
    return true;
}

bool JniHelper::getMethodInfo_DefaultClassLoader(JniMethodInfo &methodinfo,
                                                 const char *className,
                                                 const char *methodName,
                                                 const char *paramCode) {
    if ((nullptr == className) ||
        (nullptr == methodName) ||
        (nullptr == paramCode)) {
        return false;
    }

    JNIEnv *env = JniHelper::getEnv();
    if (!env) {
        return false;
    }

    jclass classID = env->FindClass(className);
    if (!classID) {
        LOGE("Failed to find class %s", className);
        env->ExceptionClear();
        return false;
    }

    jmethodID methodID = env->GetMethodID(classID, methodName, paramCode);
    if (!methodID) {
        LOGE("Failed to find method id of %s", methodName);
        env->ExceptionClear();
        return false;
    }

    methodinfo.classID = classID;
    methodinfo.env = env;
    methodinfo.methodID = methodID;

    return true;
}

bool JniHelper::getMethodInfo(JniMethodInfo &methodinfo,
                              const char *className,
                              const char *methodName,
                              const char *paramCode) {
    if ((nullptr == className) ||
        (nullptr == methodName) ||
        (nullptr == paramCode)) {
        return false;
    }

    JNIEnv *env = JniHelper::getEnv();
    if (!env) {
        return false;
    }

    jclass classID = _getClassID(className);
    if (!classID) {
        LOGE("Failed to find class %s", className);
        env->ExceptionClear();
        return false;
    }

    jmethodID methodID = env->GetMethodID(classID, methodName, paramCode);
    if (!methodID) {
        LOGE("Failed to find method id of %s", methodName);
        env->ExceptionClear();
        return false;
    }

    methodinfo.classID = classID;
    methodinfo.env = env;
    methodinfo.methodID = methodID;

    return true;
}

std::string JniHelper::jstring2string(jstring jstr) {
    if (jstr == nullptr) {
        return "";
    }

    JNIEnv *env = JniHelper::getEnv();
    if (!env) {
        return "";
    }

    std::string strValue = cc::StringUtils::getStringUTFCharsJNI(env, jstr);

    return strValue;
}

jstring JniHelper::convert(JniHelper::LocalRefMapType &localRefs, cc::JniMethodInfo &t, const char *x) {
    jstring ret = nullptr;
    if (x)
        ret = cc::StringUtils::newStringUTFJNI(t.env, x);

    localRefs[t.env].push_back(ret);
    return ret;
}

jstring JniHelper::convert(JniHelper::LocalRefMapType &localRefs, cc::JniMethodInfo &t, const std::string &x) {
    return convert(localRefs, t, x.c_str());
}

void JniHelper::deleteLocalRefs(JNIEnv *env, JniHelper::LocalRefMapType &localRefs) {
    if (!env) {
        return;
    }

    for (const auto &ref : localRefs[env]) {
        env->DeleteLocalRef(ref);
        LOGE("2. delete 0x%p", ref);
    }
    localRefs[env].clear();
}

void JniHelper::reportError(const std::string &className, const std::string &methodName, const std::string &signature) {
    LOGE("Failed to find static java method. Class name: %s, method name: %s, signature: %s ", className.c_str(), methodName.c_str(), signature.c_str());
}

} //namespace cc
