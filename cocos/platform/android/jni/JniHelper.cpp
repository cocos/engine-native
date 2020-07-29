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
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#include <string.h>
#include <regex>
#include <pthread.h>

#include "base/ccUTF8.h"


#define  LOG_TAG    "JniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static pthread_key_t g_key;

jclass _getClassID(const char *className) {
    if (nullptr == className) {
        return nullptr;
    }

    JNIEnv* env = cocos2d::JniHelper::getEnv();

    jstring _jstrClassName = env->NewStringUTF(className);

    jclass _clazz = (jclass) env->CallObjectMethod(cocos2d::JniHelper::classloader,
                                                   cocos2d::JniHelper::loadclassMethod_methodID,
                                                   _jstrClassName);

    if (nullptr == _clazz || env->ExceptionCheck()) {
        // LOGE("Classloader failed to find class of %s", className);
        env->ExceptionClear();
        _clazz = nullptr;
    }

    env->DeleteLocalRef(_jstrClassName);

    return _clazz;
}

void _detachCurrentThread(void* a) {
    cocos2d::JniHelper::getJavaVM()->DetachCurrentThread();
}


namespace cocos2d {

    JavaVM* JniHelper::_psJavaVM = nullptr;
    jmethodID JniHelper::loadclassMethod_methodID = nullptr;
    jobject JniHelper::classloader = nullptr;
    std::function<void()> JniHelper::classloaderCallback = nullptr;
    
    jobject JniHelper::_activity = nullptr;


    JniLocalRefPostDelete::JniLocalRefPostDelete() {
        _env = JniHelper::getEnv();
    }

    JavaVM* JniHelper::getJavaVM() {
        pthread_t thisthread = pthread_self();
        LOGD("JniHelper::getJavaVM(), pthread_self() = %ld", thisthread);
        return _psJavaVM;
    }

    void JniHelper::setJavaVM(JavaVM *javaVM) {
        pthread_t thisthread = pthread_self();
        LOGD("JniHelper::setJavaVM(%p), pthread_self() = %ld", javaVM, thisthread);
        _psJavaVM = javaVM;

        pthread_key_create(&g_key, _detachCurrentThread);
    }

    JNIEnv* JniHelper::cacheEnv(JavaVM* jvm) {
        JNIEnv* _env = nullptr;
        // get jni environment
        jint ret = jvm->GetEnv((void**)&_env, JNI_VERSION_1_4);
        
        switch (ret) {
        case JNI_OK :
            // Success!
            pthread_setspecific(g_key, _env);
            return _env;

        case JNI_EDETACHED :
            // Thread not attached
            if (jvm->AttachCurrentThread(&_env, nullptr) < 0)
                {
                    LOGE("Failed to get the environment using AttachCurrentThread()");

                    return nullptr;
                } else {
                // Success : Attached and obtained JNIEnv!
                pthread_setspecific(g_key, _env);
                return _env;
            }

        case JNI_EVERSION :
            // Cannot recover from this error
            LOGE("JNI interface version 1.4 not supported");
        default :
            LOGE("Failed to get the environment using GetEnv()");
            return nullptr;
        }
    }

    JNIEnv* JniHelper::getEnv() {
        JNIEnv *_env = (JNIEnv *)pthread_getspecific(g_key);
        if (_env == nullptr)
            _env = JniHelper::cacheEnv(_psJavaVM);
        return _env;
    }
    
    jobject JniHelper::getActivity() {
        return _activity;
    }

    bool JniHelper::setClassLoaderFrom(jobject activityinstance) {
        JniMethodInfo _getclassloaderMethod;
        if (!JniHelper::getMethodInfo_DefaultClassLoader(_getclassloaderMethod,
                                                         "android/content/Context",
                                                         "getClassLoader",
                                                         "()Ljava/lang/ClassLoader;")) {
            return false;
        }

        jobject _c = cocos2d::JniHelper::getEnv()->CallObjectMethod(activityinstance,
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

        JniHelper::classloader = cocos2d::JniHelper::getEnv()->NewGlobalRef(_c);
        JniHelper::loadclassMethod_methodID = _m.methodID;
        JniHelper::_activity = cocos2d::JniHelper::getEnv()->NewGlobalRef(activityinstance);
        if (JniHelper::classloaderCallback != nullptr){
            JniHelper::classloaderCallback();
        }

        return true;
    }

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
        if (! classID) {
            LOGE("Failed to find class %s", className);
            env->ExceptionClear();
            return false;
        }

        jmethodID methodID = env->GetStaticMethodID(classID, methodName, paramCode);
        if (! methodID) {
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
        if (! classID) {
            LOGE("Failed to find class %s", className);
            env->ExceptionClear();
            return false;
        }

        jmethodID methodID = env->GetMethodID(classID, methodName, paramCode);
        if (! methodID) {
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

        if(env->ExceptionCheck()) {
            jthrowable e = env->ExceptionOccurred();
            env->ExceptionClear();
            jmethodID printStackTrace = env->GetMethodID(env->FindClass("java/lang/Throwable"), "printStackTrace", "()V");
            LOGE("Pending Java Exception found: ");
            env->CallVoidMethod(e, printStackTrace);
        }

        jclass classID = _getClassID(className);
        if (! classID) {
            LOGE("Failed to find class %s", className);
            env->ExceptionClear();
            return false;
        }

        jmethodID methodID = env->GetMethodID(classID, methodName, paramCode);
        if (! methodID) {
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

        std::string strValue = cocos2d::StringUtils::getStringUTFCharsJNI(env, jstr);

        return strValue;
    }

    jstring JniHelper::convert(JniHelper::LocalRefMapType &localRefs, cocos2d::JniMethodInfo& t, const char* x) {
        jstring ret = nullptr;
        if (x)
          ret = cocos2d::StringUtils::newStringUTFJNI(t.env, x);

        localRefs[t.env].push_back(ret);
        return ret;
    }

    jstring JniHelper::convert(JniHelper::LocalRefMapType &localRefs, cocos2d::JniMethodInfo& t, const std::string& x) {
        return convert(localRefs, t, x.c_str());
    }

    void JniHelper::deleteLocalRefs(JNIEnv* env, JniHelper::LocalRefMapType &localRefs) {
        if (!env) {
            return;
        }

        for (const auto& ref : localRefs[env]) {
            env->DeleteLocalRef(ref);
        }
        localRefs[env].clear();
    }

    void JniHelper::reportError(const std::string& className, const std::string& methodName, const std::string& signature) {
        LOGE("Failed to find static java method. Class name: %s, method name: %s, signature: %s ",  className.c_str(), methodName.c_str(), signature.c_str());
    }
#if CC_ENABLE_JNI_BINDING
    std::vector<JniMethodSignature> JniHelper::getStaticMethodsByName(JNIEnv *env, jclass klass, const std::string &methodName) {
        std::vector<JniMethodSignature> ret;
        JniLocalRefPostDelete guard(env);
        jobject methods = callObjectObjectMethod(klass, "java/lang/Class", "getMethods", "[Ljava/lang/reflect/Method;");
        guard.post_delete(methods);
        int len = env->GetArrayLength((jarray) methods);
        for (int i = 0; i < len; i++) {
            jobject method = env->GetObjectArrayElement((jobjectArray) methods, i);
            jobject methodNameObj = callObjectObjectMethod(method, "java/lang/reflect/Method", "getName", "Ljava/lang/String;");
            if (jstring2string((jstring)methodNameObj) == methodName) {
                JniMethodSignature m;
                m.signature = getMethodSignature(method);
                m.method = env->GetStaticMethodID(klass, methodName.c_str(), m.signature.c_str());
                ret.push_back(m);
            }
            env->DeleteLocalRef(method);
            env->DeleteLocalRef(methodNameObj);
        }
        return ret;
    }

    std::vector<std::string> JniHelper::getObjectMethods(jobject obj) {
        auto *env = JniHelper::getEnv();
        JniLocalRefPostDelete guard(env);
        jobject classObject = env->GetObjectClass(obj);
        jobjectArray methods = (jobjectArray) JniHelper::callObjectObjectMethod(classObject, "java/lang/Class", "getMethods","[Ljava/lang/reflect/Method;");
        guard.post_delete(classObject);
        guard.post_delete(methods);
        std::vector<std::string> methodList;
        auto len = env->GetArrayLength(methods);
        for (auto i = 0; i < len; i++) {
            jobject method = env->GetObjectArrayElement(methods, i);
            std::stringstream ss;
            ss << getMethodName(method);
            ss << " # ";
            ss << getMethodSignature(method);
            methodList.push_back(ss.str());
            env->DeleteLocalRef(method);
        }

        return methodList;
    }


    std::string JniHelper::getMethodSignature(jobject method) {
        std::stringstream ss;
        auto *env = JniHelper::getEnv();
        JniLocalRefPostDelete guard(env);
        jobjectArray paramTypes = (jobjectArray) callObjectObjectMethod(method, "java/lang/reflect/Method", "getParameterTypes","[Ljava/lang/Class;");
        guard.post_delete(paramTypes);
        auto len = env->GetArrayLength(paramTypes);
        ss << "(";
        for (auto j = 0; j < len; j++) {
            jobject m = env->GetObjectArrayElement(paramTypes, 0);
            jobject paramName = callObjectObjectMethod(m, "java/lang/Class", "getName", "Ljava/lang/String;");
            ss << JniUtils::JniType::reparse(jstring2string((jstring)paramName));
            env->DeleteLocalRef(m);
            env->DeleteLocalRef(paramName);
        }
        ss << ")";
        ss << getMethodReturnType(method);
        return ss.str();
    }

    std::string JniHelper::getMethodName(jobject method) {
        JniLocalRefPostDelete guard;
        jobject methodName = callObjectObjectMethod(method, "java/lang/reflect/Method", "getName", "Ljava/lang/String;");
        guard.post_delete(methodName);
        return jstring2string((jstring)methodName);
    }

    std::string JniHelper::getMethodReturnType(jobject method) {
        JniLocalRefPostDelete guard;
        jobject returnType = callObjectObjectMethod(method, "java/lang/reflect/Method", "getReturnType", "Ljava/lang/Class;");
        jobject returnTypeName = callObjectObjectMethod(returnType, "java/lang/Class", "getName", "Ljava/lang/String;");
        guard.post_delete(returnType);
        guard.post_delete(returnTypeName);
        return JniUtils::JniType::fromString(jstring2string((jstring)returnTypeName)).toString();
    }

    std::string JniHelper::getConstructorSignature(JNIEnv *env, jobject constructor) {
        std::stringstream ss;
        JniLocalRefPostDelete guard(env);
        jobjectArray paramTypes = (jobjectArray) callObjectObjectMethod(constructor, "java/lang/reflect/Constructor", "getParameterTypes", "[Ljava/lang/Class;");
        guard.post_delete(paramTypes);
        auto len = env->GetArrayLength(paramTypes);
        ss << "(";
        for (auto j = 0; j < len; j++) {
            jobject m = env->GetObjectArrayElement(paramTypes, 0);
            jobject paramName = callObjectObjectMethod(m, "java/lang/Class", "getName", "Ljava/lang/String;");
            ss << JniUtils::JniType::reparse(jstring2string((jstring)paramName));
            env->DeleteLocalRef(m);
            env->DeleteLocalRef(paramName);
        }
        ss << ")";
        ss << "V";
        return ss.str();
    }

    std::string JniHelper::getObjectClass(jobject obj) {
        auto *env = JniHelper::getEnv();
        JniLocalRefPostDelete guard(env);

        jobject classObject = env->GetObjectClass(obj);
        jobject classNameString = JniHelper::callObjectObjectMethod(
                classObject, "java/lang/Class", "getName", "Ljava/lang/String;");

        std::string buff = jstring2string((jstring)classNameString);

        guard.post_delete(classObject);
        guard.post_delete(classNameString);

        return buff;
    }

    std::vector<std::string> JniHelper::getObjectFields(jobject obj) {
        auto *env = JniHelper::getEnv();
        JniLocalRefPostDelete guard(env);
        jobject classObject = env->GetObjectClass(obj);
        guard.post_delete(classObject);
        jobjectArray fields = (jobjectArray) JniHelper::callObjectObjectMethod(classObject, "java/lang/Class", "getFields", "[Ljava/lang/reflect/Field;");
        guard.post_delete(fields);
        std::vector<std::string> fieldList;
        auto len = env->GetArrayLength(fields);
        for (auto i = 0; i < len; i++) {
            jobject fieldObj = env->GetObjectArrayElement(fields, i);
            jobject fieldName = JniHelper::callObjectObjectMethod(fieldObj, "java/lang/reflect/Field", "getName", "Ljava/lang/String;");
            std::string name = jstring2string((jstring)fieldName);

            jobject fieldClass = JniHelper::callObjectObjectMethod(fieldObj, "java/lang/reflect/Field", "getType", "Ljava/lang/Class;");
            jobject fieldTypeName = JniHelper::callObjectObjectMethod(fieldClass, "java/lang/Class", "getName", "Ljava/lang/String;");
            std::string fieldTypeNameStr = jstring2string((jstring)fieldTypeName);
            name.append(" # ").append(fieldTypeNameStr);
            fieldList.push_back(name);
            env->DeleteLocalRef(fieldObj);
            env->DeleteLocalRef(fieldName);
            env->DeleteLocalRef(fieldClass);
            env->DeleteLocalRef(fieldTypeName);
        }

        return fieldList;
    }

    jobject JniHelper::getObjectFieldObject(jobject obj, const std::string &fieldName)
    {
        auto *env = JniHelper::getEnv();
        JniLocalRefPostDelete guard(env);
        jobject classObj = env->GetObjectClass(obj);
        guard.post_delete(classObj);
        jobject fid = callObjectObjectMethod(classObj, "java/lang/Class", "getField", "Ljava/lang/reflect/Field;", fieldName);
        if(fid == nullptr || env->ExceptionCheck()) {
            env->ExceptionClear();
            return nullptr;
        }
        return fid;
    }

    jfieldID JniHelper::getClassStaticField(JNIEnv *env, jclass classObj,
                                  const std::string &fieldName,
                                  JniUtils::JniType &fieldType) {

        JniLocalRefPostDelete guard(env);
        jobject fieldObj = callObjectObjectMethod(classObj, "java/lang/Class", "getField","Ljava/lang/reflect/Field;", fieldName);
        guard.post_delete(fieldObj);
        if (!fieldObj || env->ExceptionCheck()) {
            env->ExceptionClear();
            return nullptr;
        }
        jclass modifierClass = env->FindClass("java/lang/reflect/Modifier");
        jfieldID modifierStaticField = env->GetStaticFieldID(modifierClass, "STATIC", "I");
        const auto STATIC_FLAG = (unsigned int) env->GetStaticIntField(modifierClass, modifierStaticField);
        unsigned int modifiers = callObjectIntMethod(fieldObj, "java/lang/reflect/Field", "getModifiers");

        guard.post_delete(modifierClass);

        if (env->ExceptionCheck()) {
            env->ExceptionClear();
            return nullptr;
        }

        if ((modifiers & STATIC_FLAG) == 0) {
            return nullptr;
        }

        jobject fieldClassObj = JniHelper::callObjectObjectMethod(fieldObj, "java/lang/reflect/Field", "getType", "Ljava/lang/Class;");
        jobject fieldTypeName = JniHelper::callObjectObjectMethod(fieldClassObj, "java/lang/Class", "getName", "Ljava/lang/String;");
        fieldType = JniUtils::JniType::fromString(jstring2string((jstring)fieldTypeName));
        jfieldID fid = env->GetStaticFieldID(classObj, fieldName.c_str(),
                                             fieldType.toString().c_str());

        guard.post_delete(fieldClassObj);
        guard.post_delete(fieldTypeName);

        if (!fid || env->ExceptionCheck()) {
            env->ExceptionClear();
            return nullptr;
        }

        return fid;
    }


    bool JniHelper::hasStaticField(const std::string &longPath) {
        JNIEnv *env = JniHelper::getEnv();
        JniLocalRefPostDelete guard(env);
        std::string path = std::regex_replace(longPath, std::regex("\\."), "/");
        std::string fieldName;
        std::string className;
        JniUtils::JniType fieldType;
        {
            auto idx = path.rfind('/');
            if (idx == std::string::npos) {
                return false;
            }
            fieldName = path.substr(idx + 1);
            className = path.substr(0, idx);
        }

        jclass kls = _getClassID(className.c_str());
        guard.post_delete(kls);
        if (kls == nullptr || env->ExceptionCheck()) {
            env->ExceptionClear();
            return false;
        }
        jfieldID f = getClassStaticField(env, kls, fieldName, fieldType);
        return f != nullptr;
    }

    jclass JniHelper::findClass(const char *classPath) {
        return _getClassID(classPath);
    }

#endif

} //namespace cocos2d
