

#include "base/ccConfig.h"
#include "jsb_conversions.hpp"
#include "jsb_global.h"
#include "jsb_jni_utils.h"
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/JniImp.h"
#include <algorithm>
#include <jni.h>
#include <regex>
#include <stack>
#include <string>
#include <utility>
#include <memory>
#include <vector>
#include <cocos/platform/CCApplication.h>
#include <cocos/base/CCScheduler.h>


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) && CC_ENABLE_JNI_BINDING

#define JS_JNI_DEBUG 1
#define JS_JNI_TAG_TYPE "$jni_obj_type"
#define JS_JNI_JCLASS_TYPE "$class_name"
#define JS_JNI_TAG_PATH "$package_path"
#define JS_JNI_PROXY_TARGET "$proxy_target"
#define JS_JNI_NATIVE_ID_KEY "__native_id__"

#ifndef ORG_BYTECODE_GENERATOR_CLASS_NAME
#define ORG_BYTECODE_GENERATOR_CLASS_NAME org_cocos2dx_lib_ByteCodeGenerator
#endif
#define JNI_BYTECODE_GENERATOR(FUNC)                                           \
  JNI_METHOD1(ORG_BYTECODE_GENERATOR_CLASS_NAME, FUNC)

using cocos2d::JniHelper;
using cocos2d::JniMethodInfo;
using cocos2d::JniLocalRefPostDelete;

SE_DECLARE_FUNC(js_jni_proxy_java_path_base);

#define jstringToString(str) cocos2d::JniHelper::jstring2string((jstring)(str))

namespace {

    se::Class *__jsb_jni_jobject = nullptr;
    se::Class *__jsb_jni_jmethod_invoke_instance = nullptr;

    se::Object *sJavaObjectProxy = nullptr;
    se::Object *sJavaObjectStubProxy = nullptr;
    se::Object *sJavaObjectMethodsUnboundFunc = nullptr;
    se::Object *sJavaObjectFieldsUnboundFunc = nullptr;
    se::Object *sJavaObjectMethodApplyUnboundFunc = nullptr;
    se::Object *sJavaStaticMethodApplyUnboundFunc = nullptr;

    class JValue;

    class JObject;

    class JObjectStub;

    bool getJavaFieldByType(JNIEnv *env, jobject jthis,
                            const JniUtils::JniType &type, jfieldID fieldId,
                            jvalue &ret);

    jvalue seval_to_jvalule(JNIEnv *env, const JniUtils::JniType &def,
                            const se::Value &val, bool &ok);

    bool jobject_to_seval(JNIEnv *env, const JniUtils::JniType &type, jvalue obj,
                          se::Value &out);

    bool jobject_to_seval2(JNIEnv *env, jobject obj, se::Value &out);

    std::vector<jvalue> jsArgs2JavaArgs(JNIEnv *env, const std::string &signature,
                                        const std::vector<se::Value> &args,
                                        int offset, bool &success);

    bool getJavaObjectStaticFieldByType(JNIEnv *env, jclass kls, jfieldID field,
                                        const JniUtils::JniType &type,
                                        se::Value &out);

    bool setJavaObjectStaticFieldByType(JNIEnv *env, jclass kls, jfieldID field,
                                        const JniUtils::JniType &type,
                                        const se::Value &in);


    struct JavaToJSTuple {
        JObject *jThis = nullptr;
        se::Object *jsConfig = nullptr;
    };
    std::unordered_map<int, JavaToJSTuple> sJavaObjectMapToJS;

    class Defer {
    public:
        explicit Defer(std::function<void()> x) : _cb(std::move(x)) {};

        virtual ~Defer() {
            _cb();
        }

    private:
        std::function<void()> _cb;
    };


    /**
     * Get Throwable name
     * @param e
     * @return
     */
    std::string jthrowableToString(jthrowable e) {
        auto *env = JniHelper::getEnv();
        jobject str = JniHelper::callObjectObjectMethod((jobject) e, "java/lang/Throwable", "toString", "Ljava/lang/String;");
        if (str == nullptr) {
            return "call jthrowableToString failed!";
        }
        auto ret = JniHelper::jstring2string((jstring) str);
        env->DeleteLocalRef(str);
        return ret;
    }


    bool setObjectFieldByType(JNIEnv *env, const JniUtils::JniType &type,
                              jobject obj, jfieldID field, const jvalue value) {
        if (type.dim == 0) {
            if (type.isBoolean()) {
                env->SetBooleanField(obj, field, value.z);
            } else if (type.isChar()) {
                env->SetCharField(obj, field, value.c);
            } else if (type.isShort()) {
                env->SetShortField(obj, field, value.s);
            } else if (type.isByte()) {
                env->SetByteField(obj, field, value.b);
            } else if (type.isInt()) {
                env->SetIntField(obj, field, value.i);
            } else if (type.isLong()) {
                env->SetIntField(obj, field, value.j);
            } else if (type.isFloat()) {
                env->SetFloatField(obj, field, value.f);
            } else if (type.isDouble()) {
                env->SetDoubleField(obj, field, value.d);
            } else if (type.isObject()) {
                env->SetObjectField(obj, field, value.l);
            } else {
                assert(false);
            }
        } else {
            // array
            env->SetObjectField(obj, field, value.l);
        }

        return true;
    }

    bool setJavaObjectField(jobject obj, const std::string &fieldName,
                            const se::Value &value, bool &hasField) {
        auto *env = JniHelper::getEnv();
        JniLocalRefPostDelete guard(env);
        bool ok = false;
        jobject fieldObject = JniHelper::getObjectFieldObject(obj, fieldName);
        guard.post_delete(fieldObject);
        if (!fieldObject) {
            hasField = false;
            return true;
        }
        hasField = true;

        // get fieldName & signature
        jobject fieldClassObject = JniHelper::callObjectObjectMethod(fieldObject, "java/lang/reflect/Field", "getType", "Ljava/lang/Class;");
        jobject fieldTypeJNIName = JniHelper::callObjectObjectMethod(fieldClassObject, "java/lang/Class", "getName", "Ljava/lang/String;");
        JniUtils::JniType fieldType = JniUtils::JniType::fromString(jstringToString(fieldTypeJNIName));
        guard.post_delete(fieldClassObject);
        guard.post_delete(fieldTypeJNIName);
        // convert js value to java value
        jvalue ret = seval_to_jvalule(env, fieldType, value, ok);
        if (ok) {
            jfieldID fieldId = env->GetFieldID(env->GetObjectClass(obj), fieldName.c_str(), fieldType.toString().c_str());
            if (!fieldId || env->ExceptionCheck()) {
                env->ExceptionClear();
                return false;
            }
            ok &= setObjectFieldByType(env, fieldType, obj, fieldId, ret);
        }
        return ok;
    }


    jobject callJavaConstructor(JNIEnv *env, const std::string &path, jclass classObj, jobject constructor, se::Object *args) {
        std::vector<se::Value> argVector;
        {
            // init arguments
            uint32_t argLen = 0;
            args->getArrayLength(&argLen);
            argVector.resize(argLen);
            for (int i = 0; i < argLen; i++) {
                args->getArrayElement(i, &argVector[i]);
            }
        }
        auto signature = JniHelper::getConstructorSignature(env, constructor);
        bool ok = false;

        jmethodID initMethod = env->GetMethodID(classObj, "<init>", signature.c_str());
        if (!initMethod || env->ExceptionCheck()) {
            // no constructor found!
            env->ExceptionClear();
            return nullptr;
        }

        std::vector<jvalue> jargs = jsArgs2JavaArgs(env, signature, argVector, 0, ok);
        if (!ok) {
            // bad argument types & convertion error
            return nullptr;
        }

        jobject obj = env->NewObjectA(classObj, initMethod, jargs.data());
        if (!obj || env->ExceptionCheck()) {
            env->ExceptionClear();
            return nullptr;
        }

        return obj;
    }

    jobject constructJavaObjectByClassPath(const std::string &path, se::Object *args) {

        JNIEnv *env = JniHelper::getEnv();
        JniLocalRefPostDelete guard(env);
        std::stack<jclass> classStack;
        jclass pathClass = nullptr;

        std::string classPath = std::regex_replace(path, std::regex("\\."), "/");

        // test class path
        pathClass = JniHelper::findClass(classPath.c_str());
        guard.post_delete(pathClass);
        if (pathClass == nullptr || env->ExceptionCheck()) {
            env->ExceptionClear();
            return nullptr;
        }

        jobjectArray constructors = (jobjectArray) JniHelper::callObjectObjectMethod(
                pathClass, "java/lang/Class", "getConstructors",
                "[Ljava/lang/reflect/Constructor;");
        guard.post_delete(constructors);
        if (constructors == nullptr)
            return nullptr;
        int constructLen = env->GetArrayLength(constructors);
        for (int i = 0; i < constructLen; i++) {
            jobject constructor = env->GetObjectArrayElement(constructors, i);
            jobject ret = callJavaConstructor(env, classPath, pathClass, constructor, args);
            if (ret) {
                env->DeleteLocalRef(constructor);
                return ret;
            }
            env->DeleteLocalRef(constructor);
            env->DeleteLocalRef(ret);
        }

        return nullptr;
    }


    bool getJavaObjectStaticField(const std::string &longPath, se::Value &ret) {
        JNIEnv *env = JniHelper::getEnv();
        JniLocalRefPostDelete guard(env);

        std::string path = std::regex_replace(longPath, std::regex("\\."), "/");
        std::string fieldName;
        std::string className;
        JniUtils::JniType fieldType;
        {
            // split className & fieldName from path
            // like "com/demo/Game/MAX_LEVEL"
            auto idx = path.rfind("/");
            if (idx == std::string::npos) {
                return false;
            }
            fieldName = path.substr(idx + 1);
            className = path.substr(0, idx);
        }

        jclass kls = JniHelper::findClass(className.c_str());
        guard.post_delete(kls);
        if (kls == nullptr || env->ExceptionCheck()) {
            env->ExceptionClear();
            return false;
        }
        jfieldID f = JniHelper::getClassStaticField(env, kls, fieldName, fieldType);
        if (f == nullptr) {
            return false;
        }

        return getJavaObjectStaticFieldByType(env, kls, f, fieldType, ret);
    }

    bool setJavaObjectStaticField(const std::string &longPath, const se::Value &ret) {
        JNIEnv *env = JniHelper::getEnv();
        JniLocalRefPostDelete guard(env);

        std::string path = std::regex_replace(longPath, std::regex("\\."), "/");
        std::string fieldName;
        std::string className;
        JniUtils::JniType fieldType;
        {
            // split className & fieldName from path
            // like "com/demo/Game/MAX_LEVEL"
            auto idx = path.rfind("/");
            if (idx == std::string::npos) {
                return false;
            }
            fieldName = path.substr(idx + 1);
            className = path.substr(0, idx);
        }

        jclass kls = JniHelper::findClass(className.c_str());
        guard.post_delete(kls);
        if (kls == nullptr || env->ExceptionCheck()) {
            env->ExceptionClear();
            return false;
        }
        jfieldID f = JniHelper::getClassStaticField(env, kls, fieldName, fieldType);
        if (f == nullptr) {
            std::string msg = "field '" + fieldName + "' is not found in '" + className + "'";
            se::ScriptEngine::getInstance()->throwException(msg.c_str());
            return false;
        }

        return setJavaObjectStaticFieldByType(env, kls, f, fieldType, ret);
    }

    struct JValue {
        JValue() = default;

        JValue(const JniUtils::JniType &type_, jvalue v_)
                : type(type_), value(v_) {}

        JValue(const JValue &o) :
                type(o.type), value(o.value) {}

        bool cast(se::Value &out);

        JniUtils::JniType type;
        jvalue value{};
    };


    class JNamedMethodsInfo {
    public:
        JNamedMethodsInfo(std::string methodName, std::vector<cocos2d::JniMethodSignature> _methods,
                          JObject *_self)
                : methodName(std::move(methodName)), methods(std::move(_methods)), self(_self) {}

        se::Object *asJSObject() {
            if (_jsobj)
                return _jsobj;
            _jsobj = se::Object::createObjectWithClass(__jsb_jni_jmethod_invoke_instance);
            _jsobj->setPrivateData(this);
            return _jsobj;
        }

        std::vector<cocos2d::JniMethodSignature> methods;
        JObject *self = nullptr;
        std::string methodName;

    private:
        se::Object *_jsobj = nullptr;
    };

    class JObject {
    public:
        explicit JObject(jobject obj) {
            if (obj) {
                _javaObject = JniHelper::getEnv()->NewGlobalRef(obj);
            }
        }

        virtual ~JObject() {
            if (_javaObject) {
                JniHelper::getEnv()->DeleteGlobalRef(_javaObject);
                _javaObject = nullptr;
            }
        }

        se::Object *asJSObject();

        jobject getJavaObject() const {
            assert(_javaObject);
            return _javaObject;
        }

        jclass getClass() const {
            return JniHelper::getEnv()->GetObjectClass(_javaObject);
        }

        se::Object *getUnderlineJSObject() const { return _jsTarget; }

        bool findMethods(const std::string &name, const std::string &signature,
                         std::vector<cocos2d::JniMethodSignature> &method);

        bool getFieldValue(const std::string &name, JValue &ret);

        std::string toString() const {
            char buff[256] = {0};
            snprintf(buff, 255, "jobject %p, proxy %p, target: %p", (void *) _javaObject, _jsProxy, _jsTarget);
            return buff;
        }

    private:
        jobject _javaObject = nullptr;
        se::Object *_jsProxy = nullptr;
        se::Object *_jsTarget = nullptr;

        std::string _classPath;
    };

    bool JObject::getFieldValue(const std::string &name, JValue &ret) {
        auto *env = JniHelper::getEnv();
        JniLocalRefPostDelete guard(env);

        std::string klassName = JniHelper::getObjectClass(_javaObject);
        jclass klassObject = env->GetObjectClass(_javaObject);
        guard.post_delete(klassObject);
        jobject fieldObj = JniHelper::callObjectObjectMethod(klassObject, "java/lang/Class", "getField", "Ljava/lang/reflect/Field;", name);
        guard.post_delete(fieldObj);
        if (fieldObj == nullptr || env->ExceptionCheck()) {
            env->ExceptionClear();
            return false;
        }
        jobject fieldType = JniHelper::callObjectObjectMethod(
                fieldObj, "java/lang/reflect/Field", "getType", "Ljava/lang/Class;");
        jobject fieldTypeName = JniHelper::callObjectObjectMethod(
                fieldType, "java/lang/Class", "getName", "Ljava/lang/String;");
        guard.post_delete(fieldType);
        guard.post_delete(fieldTypeName);
        std::string fieldNameStr = jstringToString(fieldTypeName);
        JniUtils::JniType jniFieldType =
                JniUtils::JniType::fromString(fieldNameStr);
        jfieldID fieldId =
                env->GetFieldID(env->GetObjectClass(_javaObject), name.c_str(), jniFieldType.toString().c_str());
        if (fieldId == nullptr || env->ExceptionCheck()) {
            jthrowable e = env->ExceptionOccurred();
            auto exceptionString = jthrowableToString(e);
            SE_LOGE("Exception caught when access %s#%s\n %s", klassName.c_str(),
                    name.c_str(), exceptionString.c_str());
            env->ExceptionClear();
            return false;
        }
        jvalue jret;
        if (!getJavaFieldByType(env, _javaObject, jniFieldType, fieldId, jret)) {
            return false;
        }
        ret.type = jniFieldType;
        ret.value = jret;
        return true;
    }

    se::Object *JObject::asJSObject() {
        if (!_javaObject)
            return nullptr;
        if (_jsProxy)
            return _jsProxy;
        _jsTarget = se::Object::createObjectWithClass(__jsb_jni_jobject);
        _jsTarget->setPrivateData(this);
        _jsProxy = _jsTarget->proxyTo(sJavaObjectProxy);

        _classPath = JniHelper::getObjectClass(_javaObject);
        _jsProxy->setProperty(JS_JNI_TAG_TYPE, se::Value("jobject"));
        _jsProxy->setProperty(JS_JNI_JCLASS_TYPE, se::Value(_classPath));
        _jsProxy->setProperty(JS_JNI_PROXY_TARGET, se::Value(_jsTarget));

        _jsProxy->root(); // TODO: prevent GC in script

        return _jsProxy;
    }


    bool JObject::findMethods(const std::string &name,
                              const std::string &signature,
                              std::vector<cocos2d::JniMethodSignature> &list) {
        auto *env = JniHelper::getEnv();
        JniLocalRefPostDelete gurad(env);

        std::string className = JniHelper::getObjectClass(_javaObject);
        jclass jobjClass = env->GetObjectClass(_javaObject);
        gurad.post_delete(jobjClass);

        cocos2d::JniMethodSignature oMethod;
        if (!signature.empty()) {
            jmethodID mid = env->GetMethodID(jobjClass, className.c_str(), signature.c_str());
            if (!mid || env->ExceptionCheck()) {
                env->ExceptionClear();
                return false;
            }
            oMethod.method = mid;
            oMethod.signature = signature;
            list.push_back(oMethod);
        } else {
            jobjectArray methodsArray = (jobjectArray) JniHelper::callObjectObjectMethod(jobjClass, "java/lang/Class", "getMethods", "[Ljava/lang/reflect/Method;");
            gurad.post_delete(methodsArray);
            if (!methodsArray || env->ExceptionCheck()) {
                env->ExceptionClear();
                return false;
            }
            auto len = env->GetArrayLength(methodsArray);
            for (int i = 0; i < len; i++) {
                jobject methodObj = env->GetObjectArrayElement(methodsArray, i);
                std::string methodName = JniHelper::getMethodName(methodObj);
                if (methodName != name) {
                    env->DeleteLocalRef(methodObj);
                    continue;
                }
                auto sig = JniHelper::getMethodSignature(methodObj);
                jmethodID mid = env->GetMethodID(jobjClass, name.c_str(), sig.c_str());
                if (mid == nullptr || env->ExceptionCheck()) {
                    env->DeleteLocalRef(methodObj);
                    env->ExceptionClear();
                    return false;
                }
                assert(mid);
                oMethod.method = mid;
                oMethod.signature = sig;
                list.push_back(oMethod);
                env->DeleteLocalRef(methodObj);
            }
        }

        return true;
    }

    bool JValue::cast(se::Value &out) {
        JNIEnv *env = JniHelper::getEnv();
        return jobject_to_seval(env, type, value, out);
    }

    class JObjectStub {
    public:
        JObjectStub() = default;

        JObjectStub(const std::string &path) : _path(path) {}

        se::Object *asJSObject();

        se::Object *getUnderlineJSObject() {
            if (!_jsTarget)
                asJSObject();
            return _jsTarget;
        }

    private:
        se::Object *_jsTarget = nullptr;
        se::Object *_jsProxy = nullptr;
        std::string _path;
    };

    se::Object *JObjectStub::asJSObject() {
        if (_jsProxy) {
            return _jsProxy;
        }
        _jsTarget = se::Object::createFunctionObject(nullptr, _SE(js_jni_proxy_java_path_base));
        _jsTarget->setPrivateData(this);
        _jsTarget->_setFinalizeCallback([](void *data) {
            if (data) {
                delete (JObjectStub *) data;
            }
        });
        _jsProxy = _jsTarget->proxyTo(sJavaObjectStubProxy);
        _jsProxy->setProperty(JS_JNI_TAG_PATH, se::Value(_path));
        _jsProxy->setProperty(JS_JNI_TAG_TYPE, se::Value("jpath"));
        _jsProxy->attachObject(_jsTarget);
        return _jsProxy;
    }

    bool getJavaFieldByType(JNIEnv *env, jobject jthis,
                            const JniUtils::JniType &type, jfieldID fieldId,
                            jvalue &ret) {
        if (type.dim == 0) {
            if (type.isBoolean()) {
                ret.z = env->GetBooleanField(jthis, fieldId);
            } else if (type.isByte()) {
                ret.b = env->GetByteField(jthis, fieldId);
            } else if (type.isChar()) {
                ret.c = env->GetCharField(jthis, fieldId);
            } else if (type.isShort()) {
                ret.s = env->GetShortField(jthis, fieldId);
            } else if (type.isInt()) {
                ret.i = env->GetIntField(jthis, fieldId);
            } else if (type.isLong()) {
                ret.j = env->GetLongField(jthis, fieldId);
            } else if (type.isFloat()) {
                ret.f = env->GetFloatField(jthis, fieldId);
            } else if (type.isDouble()) {
                ret.d = env->GetDoubleField(jthis, fieldId);
            } else if (type.isObject()) {
                ret.l = env->GetObjectField(jthis, fieldId);
            } else {
                assert(false);
                return false;
            }
        } else {
            ret.l = env->GetObjectField(jthis, fieldId);
        }
        return true;
    }

    bool callJMethodByReturnType(const JniUtils::JniType &rType, jobject jthis,
                                 jmethodID method,
                                 const std::vector<jvalue> &jvalueArray,
                                 se::Value &out) {
        auto *env = JniHelper::getEnv();
        jvalue jRet = {};

        if (rType.isVoid()) {
            env->CallVoidMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isBoolean()) {
            jRet.z = env->CallBooleanMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isChar()) {
            jRet.c = env->CallCharMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isShort()) {
            jRet.s = env->CallShortMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isByte()) {
            jRet.b = env->CallByteMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isInt()) {
            jRet.i = env->CallIntMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isLong()) {
            jRet.j = env->CallIntMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isFloat()) {
            jRet.f = env->CallFloatMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isDouble()) {
            jRet.d = env->CallDoubleMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isObject()) {
            jRet.l = env->CallObjectMethodA(jthis, method, jvalueArray.data());
        } else {
            assert(false);
            return false;
        }
        JValue wrap(rType, jRet);
        wrap.cast(out);
        return true;
    }

    bool callStaticMethodByType(const JniUtils::JniType &rType, jclass jthis,
                                jmethodID method,
                                const std::vector<jvalue> &jvalueArray,
                                se::Value &out) {
        auto *env = JniHelper::getEnv();
        jvalue jRet = {};
        if (rType.isVoid()) {
            env->CallStaticVoidMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isBoolean()) {
            jRet.z = env->CallStaticBooleanMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isChar()) {
            jRet.c = env->CallStaticCharMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isShort()) {
            jRet.s = env->CallStaticShortMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isByte()) {
            jRet.b = env->CallStaticByteMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isInt()) {
            jRet.i = env->CallStaticIntMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isLong()) {
            jRet.j = env->CallStaticIntMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isFloat()) {
            jRet.f = env->CallStaticFloatMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isDouble()) {
            jRet.d = env->CallStaticDoubleMethodA(jthis, method, jvalueArray.data());
        } else if (rType.isObject()) {
            jRet.l = env->CallStaticObjectMethodA(jthis, method, jvalueArray.data());
        } else {
            assert(false);
            return false;
        }
        JValue wrap(rType, jRet);
        wrap.cast(out);
        return true;
    }

    jvalue seval_to_jvalule(JNIEnv *env, const JniUtils::JniType &def,
                            const se::Value &val, bool &ok) {
        jvalue ret = {};
        ok = false;
        if (def.dim == 0) {
            if (def.isBoolean() && val.isBoolean()) {
                ret.z = val.toBoolean();
            } else if (def.isByte() && val.isNumber()) {
                ret.b = val.toInt8();
            } else if (def.isChar() && val.isNumber()) {
                ret.c = val.toInt16();
            } else if (def.isShort() && val.isNumber()) {
                ret.s = val.toInt16();
            } else if (def.isInt() && val.isNumber()) {
                ret.i = val.toInt32();
            } else if (def.isLong() && val.isNumber()) {
                ret.j = static_cast<jlong>(val.toNumber()); // int 64
            } else if (def.isFloat() && val.isNumber()) {
                ret.f = val.toFloat();
            } else if (def.isDouble() && val.isNumber()) {
                ret.d = val.toNumber();
            } else if (def.isObject()) {

                if (def.getClassName() == "java/lang/String") {
                    std::string jsstring = val.toStringForce();
                    ret.l = env->NewStringUTF(jsstring.c_str());
                } else if (val.isObject()) {
                    se::Object *seObj = val.toObject();
                    se::Value target;
                    seObj->getProperty(JS_JNI_PROXY_TARGET, &target);
                    if (target.isObject()) {
                        auto *jo = (JObject *) target.toObject()->getPrivateData();
                        if (!jo) {
                            ok = false;
                            SE_LOGE("incorrect jni type, don't know how to convert pure js "
                                    "object %s to java value %s, object_type: %s",
                                    val.toStringForce().c_str(), def.toString().c_str(), target.toStringForce().c_str());

                        } else {
                            ret.l = jo->getJavaObject();
                        }

                    } else {
                        ok = false;
                        SE_LOGE("incorrect jni type, not a proxy object");
                    }
                } else {
                    ok = false;
                    SE_LOGE(
                            "incorrect jni type, don't know how to convert %s to java value %s",
                            val.toStringForce().c_str(), def.toString().c_str());
                }

            } else {
                SE_LOGE("incorrect jni type, don't know how to convert %s from js value "
                        "%s:%s",
                        def.toString().c_str(), val.getTypeName().c_str(),
                        val.toStringForce().c_str());
                return ret;
            }
            ok = true;
            return ret;
        } else if (def.dim == 1) {

            if (!val.isObject() || !val.toObject()->isArray()) {
                SE_LOGE("incorrect jni type, don't know how to convert %s from js value "
                        "%s:%s",
                        def.toString().c_str(), val.getTypeName().c_str(),
                        val.toStringForce().c_str());
                return ret;
            }

            JniUtils::JniType decayDef = def;
            decayDef.dim -= 1;

            se::Object *jsArray = val.toObject();
            uint32_t len = 0;
            jsArray->getArrayLength(&len);
            se::Value jsTmp;
            if (def.isBoolean()) {
                auto dst = (jbooleanArray) env->NewBooleanArray(len);
                std::vector<jboolean> tmpArray;
                tmpArray.resize(len);
                for (auto i = 0; i < len; i++) {
                    jsArray->getArrayElement(i, &jsTmp);
                    tmpArray[i] = jsTmp.toBoolean();
                }
                env->SetBooleanArrayRegion(dst, 0, len, tmpArray.data());
                ret.l = dst;
            } else if (def.isChar()) {
                auto dst = (jcharArray) env->NewCharArray(len);
                std::vector<jchar> tmpArray;
                tmpArray.resize(len);
                for (auto i = 0; i < len; i++) {
                    jsArray->getArrayElement(i, &jsTmp);
                    tmpArray[i] = jsTmp.toUint16();
                }
                env->SetCharArrayRegion(dst, 0, len, tmpArray.data());
                ret.l = dst;
            } else if (def.isShort()) {
                auto dst = (jshortArray) env->NewShortArray(len);
                std::vector<jshort> tmpArray;
                tmpArray.resize(len);
                for (auto i = 0; i < len; i++) {
                    jsArray->getArrayElement(i, &jsTmp);
                    tmpArray[i] = jsTmp.toInt16();
                }
                env->SetShortArrayRegion(dst, 0, len, tmpArray.data());
                ret.l = dst;
            } else if (def.isByte()) {
                auto dst = (jbyteArray) env->NewByteArray(len);
                std::vector<jbyte> tmpArray;
                tmpArray.resize(len);
                for (auto i = 0; i < len; i++) {
                    jsArray->getArrayElement(i, &jsTmp);
                    tmpArray[i] = jsTmp.toUint8();
                }
                env->SetByteArrayRegion(dst, 0, len, tmpArray.data());
                ret.l = dst;
            } else if (def.isInt()) {
                auto dst = (jintArray) env->NewIntArray(len);
                std::vector<jint> tmpArray;
                tmpArray.resize(len);
                for (auto i = 0; i < len; i++) {
                    jsArray->getArrayElement(i, &jsTmp);
                    tmpArray[i] = jsTmp.toInt32();
                }
                env->SetIntArrayRegion(dst, 0, len, tmpArray.data());
                ret.l = dst;
            } else if (def.isLong()) {
                auto dst = (jlongArray) env->NewLongArray(len);
                std::vector<jlong> tmpArray;
                tmpArray.resize(len);
                for (auto i = 0; i < len; i++) {
                    jsArray->getArrayElement(i, &jsTmp);
                    tmpArray[i] = (jlong) jsTmp.toNumber();
                }
                env->SetLongArrayRegion(dst, 0, len, tmpArray.data());
                ret.l = dst;
            } else if (def.isFloat()) {
                auto dst = (jfloatArray) env->NewFloatArray(len);
                std::vector<jfloat> tmpArray;
                tmpArray.resize(len);
                for (auto i = 0; i < len; i++) {
                    jsArray->getArrayElement(i, &jsTmp);
                    tmpArray[i] = jsTmp.toFloat();
                }
                env->SetFloatArrayRegion(dst, 0, len, tmpArray.data());
                ret.l = dst;
            } else if (def.isDouble()) {
                auto dst = (jdoubleArray) env->NewDoubleArray(len);
                std::vector<jdouble> tmpArray;
                tmpArray.resize(len);
                for (auto i = 0; i < len; i++) {
                    jsArray->getArrayElement(i, &jsTmp);
                    tmpArray[i] = jsTmp.toNumber();
                }
                env->SetDoubleArrayRegion(dst, 0, len, tmpArray.data());
                ret.l = dst;
            } else if (def.isObject()) {
                jclass kls = JniHelper::findClass(def.getClassName().c_str());
                if (!kls || env->ExceptionCheck()) {
                    env->ExceptionClear();
                    ok = false;
                    SE_LOGE("class '%s' is not found!", def.getClassName().c_str());
                    return ret;
                }
                auto dst = (jobjectArray) env->NewObjectArray(len, kls, nullptr);
                for (auto i = 0; i < len; i++) {
                    jsArray->getArrayElement(i, &jsTmp);
                    jvalue jtmp = seval_to_jvalule(env, decayDef, jsTmp, ok);
                    if (!ok) {
                        ok = false;
                        return ret;
                    }
                    env->SetObjectArrayElement(dst, i, jtmp.l);
                }
                ret.l = dst;
            } else {
                SE_LOGE("incorrect jni type, don't know how to convert %s from js value "
                        "%s:%s",
                        def.toString().c_str(), val.getTypeName().c_str(),
                        val.toStringForce().c_str());
                return ret;
            }

            ok = true;
            return ret;

        } else {
            JniUtils::JniType decayDef = def;
            decayDef.dim -= 1;
            if (!val.isObject() || !val.toObject()->isArray()) {
                SE_LOGE("incorrect jni type, don't know how to convert %s from js value "
                        "%s:%s",
                        def.toString().c_str(), val.getTypeName().c_str(),
                        val.toStringForce().c_str());
                return ret;
            }

            uint32_t len;
            se::Object *jsArray = val.toObject();
            jsArray->getArrayLength(&len);
            jclass kls = JniHelper::findClass("java/lang/Object");
            if (!kls || env->ExceptionCheck()) {
                env->ExceptionClear();
                ok = false;
                SE_LOGE("class '%s' is not found!", def.getClassName().c_str());
                return ret;
            }
            auto jArr = (jobjectArray) env->NewObjectArray(len, kls, nullptr);
            se::Value jsTmp;
            for (int i = 0; i < len; i++) {
                jsArray->getArrayElement(i, &jsTmp);
                jvalue x = seval_to_jvalule(env, decayDef, jsTmp, ok);
                if (!ok) {
                    ok = false;
                    return ret;
                }
                env->SetObjectArrayElement(jArr, i, x.l);
            }
            ret.l = jArr;
            ok = true;
            return ret;
        }
        ok = false;
        return ret;
    }

    std::vector<jvalue> jsArgs2JavaArgs(JNIEnv *env, const std::string &signature,
                                        const std::vector<se::Value> &args,
                                        int offset, bool &success) {
        bool convertOk = false;
        success = false;
        std::vector<JniUtils::JniType> argTypes = JniUtils::exactArgsFromSignature(signature, convertOk);
        if (!convertOk) {
            SE_LOGE("failed to parse signature \"%s\"", signature.c_str());
            return {};
        }

        if (argTypes.size() != args.size() - offset) {
            return {};
        }

        std::vector<jvalue> ret;
        for (size_t i = 0; i < argTypes.size(); i++) {
            jvalue arg = seval_to_jvalule(env, argTypes[i], args[i + offset], convertOk);
            if (!convertOk || env->ExceptionCheck()) {
                env->ExceptionClear();
                success = false;
                return {};
            }
            assert(convertOk);
            ret.push_back(arg);
        }

        success = true;
        return ret;
    }

    bool jobject_to_seval(JNIEnv *env, const JniUtils::JniType &type, jvalue v,
                          se::Value &out) {
        if (type.dim == 0) {
            if (type.isVoid()) {
                out.setUndefined();
            } else if (type.isBoolean()) {
                out.setBoolean(v.z);
            } else if (type.isChar()) {
                out.setUint16(v.c);
            } else if (type.isShort()) {
                out.setInt16(v.s);
            } else if (type.isByte()) {
                out.setUint8(v.b);
            } else if (type.isInt()) {
                out.setInt32(v.i);
            } else if (type.isLong()) {
                out.setLong(v.j);
            } else if (type.isFloat()) {
                out.setFloat(v.f);
            } else if (type.isDouble()) {
                out.setNumber(v.d);
            } else if (type.isObject()) {
                auto l = v.l;
                if (type.klassName == "java/lang/Boolean") {
                    out.setBoolean(JniHelper::callObjectBooleanMethod(l, "java/lang/Boolean", "booleanValue"));
                } else if (type.klassName == "java/lang/Character") {
                    out.setUint16(JniHelper::callObjectCharMethod(l, "java/lang/Character", "charValue"));
                } else if (type.klassName == ("java/lang/Byte")) {
                    out.setInt8(JniHelper::callObjectByteMethod(l, "java/lang/Byte", "byteValue"));
                } else if (type.klassName == "java/lang/Short") {
                    out.setInt8(JniHelper::callObjectShortMethod(l, "java/lang/Short", "shortValue"));
                } else if (type.klassName == "java/lang/Integer") {
                    out.setInt32(JniHelper::callObjectIntMethod(l, "java/lang/Integer", "intValue"));
                } else if (type.klassName == "java/lang/Long") {
                    out.setInt32(JniHelper::callObjectLongMethod(l, "java/lang/Long", "longValue"));
                } else if (type.klassName == "java/lang/Float") {
                    out.setFloat(JniHelper::callObjectFloatMethod(l, "java/lang/Float", "floatValue"));
                } else if (type.klassName == "java/lang/Double") {
                    out.setNumber(JniHelper::callObjectDoubleMethod(l, "java/lang/Double", "doubleValue"));
                } else if (type.klassName == "java/lang/String") {
                    out.setString(jstringToString(l));
                } else {
                    auto *w = new JObject(v.l);
                    out.setObject(w->asJSObject());
                }

            } else {
                assert(false);
                return false;
            }
        } else if (type.dim == 1) {
            auto arr = (jarray) (v.l);
            auto len = env->GetArrayLength(arr);
            se::Object *jsArr = se::Object::createArrayObject(len);
            jboolean copyOut = false;
            if (type.isBoolean()) {
                auto *data = env->GetBooleanArrayElements((jbooleanArray) arr, &copyOut);
                for (int i = 0; i < len; i++) {
                    jsArr->setArrayElement(i, se::Value((bool) data[i]));
                }
            } else if (type.isChar()) {
                auto *data = env->GetCharArrayElements((jcharArray) arr, &copyOut);
                for (int i = 0; i < len; i++) {
                    jsArr->setArrayElement(i, se::Value((uint16_t) data[i]));
                }
            } else if (type.isShort()) {
                auto *data = env->GetShortArrayElements((jshortArray) arr, &copyOut);
                for (int i = 0; i < len; i++) {
                    jsArr->setArrayElement(i, se::Value((int16_t) data[i]));
                }
            } else if (type.isByte()) {
                auto *data = env->GetByteArrayElements((jbyteArray) arr, &copyOut);
                for (int i = 0; i < len; i++) {
                    jsArr->setArrayElement(i, se::Value((int8_t) data[i]));
                }
            } else if (type.isInt()) {
                auto *data = env->GetIntArrayElements((jintArray) arr, &copyOut);
                for (int i = 0; i < len; i++) {
                    jsArr->setArrayElement(i, se::Value((jint) data[i]));
                }
            } else if (type.isLong()) {
                auto *data = env->GetLongArrayElements((jlongArray) arr, &copyOut);
                for (int i = 0; i < len; i++) {
                    jsArr->setArrayElement(i, se::Value((int32_t) data[i]));
                }
            } else if (type.isFloat()) {
                auto *data = env->GetFloatArrayElements((jfloatArray) arr, &copyOut);
                for (int i = 0; i < len; i++) {
                    jsArr->setArrayElement(i, se::Value((float) data[i]));
                }
            } else if (type.isDouble()) {
                auto *data = env->GetDoubleArrayElements((jdoubleArray) arr, &copyOut);
                for (int i = 0; i < len; i++) {
                    jsArr->setArrayElement(i, se::Value((jdouble) data[i]));
                }
            } else if (type.isObject()) {
                for (int i = 0; i < len; i++) {
                    jobject t = env->GetObjectArrayElement((jobjectArray) arr, i);
                    se::Value tmp;
                    jobject_to_seval2(env, t, tmp);
                    jsArr->setArrayElement(i, tmp);
                }
            } else {
                assert(false);
                return false;
            }
            out.setObject(jsArr);
        } else {
            auto sub = type.rankDec();
            auto arr = (jarray) (v.l);
            auto len = env->GetArrayLength(arr);
            se::Object *jsArr = se::Object::createArrayObject(len);
            for (auto i = 0; i < len; i++) {
                auto ele = env->GetObjectArrayElement((jobjectArray) arr, i);
                jvalue t;
                t.l = ele;
                se::Value jtmp;
                if (!jobject_to_seval(env, sub, t, jtmp)) {
                    return false;
                }
                jsArr->setArrayElement(i, jtmp);
            }
            out.setObject(jsArr);
        }
        return true;
    }

    bool jobject_to_seval2(JNIEnv *env, jobject v, se::Value &out) {
        jvalue tmp;
        if (v == nullptr) {
            out.setNull();
            return true;
        }
        tmp.l = v;
        std::string typeString = JniHelper::getObjectClass(v);
        auto type = JniUtils::JniType::fromString(typeString);
        return jobject_to_seval(env, type, tmp, out);
    }

    jobject seval_to_jobject(JNIEnv *env, const se::Value &input) {
        jobject ret = nullptr;
        if (input.isBoolean()) {
            jclass kls = JniHelper::findClass("java/lang/Boolean");
            jmethodID methodId = env->GetMethodID(kls, "<init>", "(Z)V");
            ret = env->NewObject(kls, methodId, input.toBoolean());
        } else if (input.isNumber()) {
            jclass kls = JniHelper::findClass("java/lang/Double");
            jmethodID methodId = env->GetMethodID(kls, "<init>", "(D)V");
            ret = env->NewObject(kls, methodId, (jdouble) input.toNumber());
        } else if (input.isString()) {
            ret = env->NewStringUTF(input.toString().c_str());
        } else if (input.isNullOrUndefined()) {
            return nullptr;
        } else if (input.isObject()) {
            se::Object *obj = input.toObject();
            auto *data = (JObject *) obj->getPrivateData();
            if (data) {
                return data->getJavaObject();
            } else {
                bool ok = false;
                JniUtils::JniType def = JniUtils::JniType::from(JniUtils::JniTypeEnum::Object_L);
                //TODO: mutiple dimension
                jvalue rt = seval_to_jvalule(env, def, input, ok);
                return rt.l;
            }
        }
        return ret;
    }

    bool getJavaObjectStaticFieldByType(JNIEnv *env, jclass kls, jfieldID field,
                                        const JniUtils::JniType &type,
                                        se::Value &out) {
        if (type.dim == 0) {
            if (type.isBoolean()) {
                auto v = env->GetStaticBooleanField(kls, field);
                out.setBoolean(v);
            } else if (type.isChar()) {
                auto v = env->GetStaticCharField(kls, field);
                out.setUint16(v);
            } else if (type.isShort()) {
                auto v = env->GetStaticShortField(kls, field);
                out.setInt16(v);
            } else if (type.isByte()) {
                auto v = env->GetStaticByteField(kls, field);
                out.setUint8(v);
            } else if (type.isInt()) {
                auto v = env->GetStaticIntField(kls, field);
                out.setInt32(v);
            } else if (type.isLong()) {
                auto v = env->GetStaticLongField(kls, field);
                out.setLong(v);
            } else if (type.isFloat()) {
                auto v = env->GetStaticFloatField(kls, field);
                out.setFloat(v);
            } else if (type.isDouble()) {
                auto v = env->GetStaticDoubleField(kls, field);
                out.setNumber(v);
            } else if (type.isObject()) {
                auto v = env->GetStaticObjectField(kls, field);
                if (env->IsInstanceOf(v, JniHelper::findClass("java/lang/String"))) {
                    out.setString(jstringToString(v));
                } else {
                    auto *w = new JObject(v);
                    out.setObject(w->asJSObject());
                }
            } else {
                assert(false);
            }
        } else {
            jobject arr = env->GetStaticObjectField(kls, field);
            jvalue t;
            t.l = arr;
            return jobject_to_seval(env, type, t, out);
        }
        return true;
    }

    bool setJavaObjectStaticFieldByType(JNIEnv *env, jclass kls, jfieldID field,
                                        const JniUtils::JniType &type,
                                        const se::Value &in) {
        if (type.dim == 0) {
            if (type.isBoolean() && in.isBoolean()) {
                env->SetStaticBooleanField(kls, field, (jboolean) in.toBoolean());
            } else if (type.isChar() && in.isNumber()) {
                env->SetStaticCharField(kls, field, (jchar) in.toUint16());
            } else if (type.isShort() && in.isNumber()) {
                env->SetStaticShortField(kls, field, (jshort) in.toInt16());
            } else if (type.isByte() && in.isNumber()) {
                env->SetStaticByteField(kls, field, (jbyte) in.toInt8());
            } else if (type.isInt() && in.isNumber()) {
                env->SetStaticIntField(kls, field, (jint) in.toInt32());
            } else if (type.isLong() && in.isNumber()) {
                env->SetStaticLongField(kls, field, (jlong) in.toNumber());
            } else if (type.isFloat() && in.isNumber()) {
                env->SetStaticFloatField(kls, field, (jfloat) in.toFloat());
            } else if (type.isDouble() && in.isNumber()) {
                env->SetStaticDoubleField(kls, field, (jdouble) in.toNumber());
            } else if (type.isObject()) {
                if (in.isString()) {
                    jobject str = env->NewStringUTF(in.toString().c_str());
                    env->SetStaticObjectField(kls, field, str);
                } else {
                    if (!in.isObject()) {
                        return false;
                    }
                    se::Object *jsObj = in.toObject();
                    JObject *jo = (JObject *) jsObj->getPrivateData();
                    if (jo == nullptr) {
                        return false;
                    }
                    env->SetStaticObjectField(kls, field, jo->getJavaObject());
                }
            } else {
                assert(false);
            }
        } else {
            if (!in.isObject() || in.toObject()->isArray()) {
                return false;
            }
            bool ok = false;
            jvalue jobj = seval_to_jvalule(env, type, in, ok);
            if (!ok) {
                return false;
            }
            env->SetStaticObjectField(kls, field, jobj.l);
            if (env->ExceptionCheck()) {
                env->ExceptionClear();
                return false;
            }
        }
        return true;
    }

    bool hasStaticMethod(const std::string &longPath) {
        JNIEnv *env = JniHelper::getEnv();
        JniLocalRefPostDelete guard(env);

        std::string path = std::regex_replace(longPath, std::regex("\\."), "/");
        std::string fieldName;
        std::string className;
        JniUtils::JniType fieldType;
        {
            auto idx = path.rfind("/");
            if (idx == std::string::npos) {
                return false;
            }
            fieldName = path.substr(idx + 1);
            className = path.substr(0, idx);
        }

        jclass kls = JniHelper::findClass(className.c_str());
        guard.post_delete(kls);
        if (kls == nullptr || env->ExceptionCheck()) {
            env->ExceptionClear();
            return false;
        }
        std::vector<cocos2d::JniMethodSignature> methods = JniHelper::getStaticMethodsByName(env, kls, fieldName);

        return !methods.empty();
    }

    bool callStaticJMethod(const std::string &longPath,
                           const std::vector<se::Value> &args, se::Value &out) {
        JNIEnv *env = JniHelper::getEnv();
        JniLocalRefPostDelete guard(env);

        bool ok = false;
        std::string path = std::regex_replace(longPath, std::regex("\\."), "/");
        std::string fieldName;
        std::string className;
        JniUtils::JniType fieldType;
        {
            auto idx = path.rfind("/");
            if (idx == std::string::npos) {
                return false;
            }
            fieldName = path.substr(idx + 1);
            className = path.substr(0, idx);
        }

        jclass kls = JniHelper::findClass(className.c_str());
        guard.post_delete(kls);
        if (kls == nullptr || env->ExceptionCheck()) {
            env->ExceptionClear();
            return false;
        }
        std::vector<cocos2d::JniMethodSignature> methods = JniHelper::getStaticMethodsByName(env, kls, fieldName);

        for (cocos2d::JniMethodSignature &m : methods) {
            std::vector<jvalue> newArgs = jsArgs2JavaArgs(env, m.signature, args, 0, ok);
            if (ok) {
                auto rType = JniUtils::JniType::fromString(m.signature.substr(m.signature.rfind(")") + 1));
                ok = callStaticMethodByType(rType, kls, m.method, newArgs, out);
                if (ok) {
                    return true;
                }
            }
        }
        return false;
    }

} // namespace

SE_DECLARE_FUNC(js_jni_proxy_methods);

static bool js_jni_jobject_finalize(se::State &s) {
    auto *cobj = (JObject *) s.nativeThisObject();
    se::Value propNativeId;
    if(s.thisObject()->getProperty(JS_JNI_NATIVE_ID_KEY, &propNativeId) && propNativeId.isNumber()) {
        sJavaObjectMapToJS.erase(propNativeId.toInt32());
    }
    delete cobj;
    return true;
}

SE_BIND_FINALIZE_FUNC(js_jni_jobject_finalize)

static bool js_jni_jobject_root(se::State &s) {
    JObject *cobj = nullptr;
    if(s.getJSThisObject()->isProxy()) {
        cobj = (JObject *) s.getJSThisObject()->getProxyTargetPrivateData();
    }else {
        cobj = (JObject *) s.nativeThisObject();
    }
    if(cobj) {
        se::Object *underline = cobj->getUnderlineJSObject();
        underline->root();
        s.rval().setInt32(underline->_getRootCount());
    }else{
        s.rval().setInt32(-1);
    }
    return true;
}
SE_BIND_FUNC(js_jni_jobject_root);

static bool js_jni_jobject_unroot(se::State &s) {
    JObject *cobj = nullptr;
    if(s.getJSThisObject()->isProxy()) {
        cobj = (JObject *) s.getJSThisObject()->getProxyTargetPrivateData();
    }else {
        cobj = (JObject *) s.nativeThisObject();
    }
    if(cobj) {
        se::Object *underline = cobj->getUnderlineJSObject();
        underline->unroot();
        s.rval().setInt32(underline->_getRootCount());
    }else{
        s.rval().setInt32(-1);
    }
    return true;
}
SE_BIND_FUNC(js_jni_jobject_unroot);

static bool js_register_jni_jobject(se::Object *obj) {
    auto cls = se::Class::create("jobject", obj, nullptr, nullptr);
    cls->defineFunction("root", _SE(js_jni_jobject_root));
    cls->defineFunction("unroot", _SE(js_jni_jobject_unroot));
    cls->defineFinalizeFunction(_SE(js_jni_jobject_finalize));
    __jsb_jni_jobject = cls;
    return true;
}

static bool js_jni_jmethod_invoke_instance_finalize(se::State &s) {
    auto *cobj = (JNamedMethodsInfo *) s.nativeThisObject();
    delete cobj;
    return true;
}

SE_BIND_FINALIZE_FUNC(js_jni_jmethod_invoke_instance_finalize)

static bool js_register_jni_jmethod_invoke_instance(se::Object *obj) {
    auto cls = se::Class::create("jmethod_invoke_instance", obj, nullptr, nullptr);
    cls->defineFinalizeFunction(_SE(js_jni_jmethod_invoke_instance_finalize));
    __jsb_jni_jmethod_invoke_instance = cls;
    return true;
}

static bool js_jni_helper_getActivity(se::State &s) {
    auto *obj = new JObject(JniHelper::getActivity());
    s.rval().setObject(obj->asJSObject());
    return true;
}

SE_BIND_FUNC(js_jni_helper_getActivity)

static bool js_jni_helper_newObject(se::State &s) {
    const int argCnt = s.args().size();
    std::string signature;
    jobject ret = nullptr;
    bool ok;

    JniLocalRefPostDelete guard;
    JniMethodInfo methodInfo;
    if (argCnt == 0) {
        SE_REPORT_ERROR("wrong number of arguments: %d", (int) argCnt);
        return false;
    } else if (argCnt == 1) {
        // no arguments
        auto klassPath = s.args()[0].toString();
        signature = "()V";
        if (JniHelper::getMethodInfo(methodInfo, klassPath.c_str(), "<init>", signature.c_str())) {
            ret = methodInfo.env->NewObject(methodInfo.classID, methodInfo.methodID);
        } else {
            JniHelper::reportError(klassPath, "<init>", signature);
            return false;
        }
    } else {
        // arg0 : class
        // arg1 : signature
        // arg2 : arg 0 for constructor
        // arg3 : arg 1 for constructor
        // ...
        auto klassPath = s.args()[0].toString();
        signature = s.args()[1].toString();
        std::vector<jvalue> jvalueArray = jsArgs2JavaArgs(JniHelper::getEnv(), signature, s.args(), 2, ok);

        if (JniHelper::getMethodInfo(methodInfo, klassPath.c_str(), "<init>", signature.c_str())) {
            ret = methodInfo.env->NewObjectA(methodInfo.classID, methodInfo.methodID, jvalueArray.data());
        } else {
            JniHelper::reportError(klassPath, "<init>", signature);
            return false;
        }
    }
    guard.post_delete(ret);
    auto *jobjWrapper = new JObject(ret);
    s.rval().setObject(jobjWrapper->asJSObject());
    return true;
}

SE_BIND_FUNC(js_jni_helper_newObject)

static jobject genAnonymousJavaObject(const std::string &parentClassStr, const std::vector<std::string> &interfacesList) {
    JNIEnv *env = JniHelper::getEnv();

    JniLocalRefPostDelete guard(env);
    jclass stringClass = JniHelper::findClass("java/lang/String");
    jobject superClassNameJ = env->NewStringUTF(parentClassStr.c_str());
    jobjectArray interfacesJ = env->NewObjectArray(interfacesList.size(), stringClass, nullptr);
    guard.post_delete(stringClass);
    guard.post_delete(superClassNameJ);
    guard.post_delete(interfacesJ);
    for (int i = 0; i < interfacesList.size(); i++) {
        jobject tmpStr = env->NewStringUTF(interfacesList[i].c_str());
        env->SetObjectArrayElement(interfacesJ, i, tmpStr);
        env->DeleteLocalRef(tmpStr);
    }

    jclass bcClass = JniHelper::findClass("org/cocos2dx/lib/ByteCodeGenerator");
    guard.post_delete(bcClass);

    if (bcClass == nullptr || env->ExceptionCheck()) {
        env->ExceptionClear();
        return nullptr;
    }
    jmethodID generateMID = env->GetStaticMethodID(bcClass, "newInstance", "(Ljava/lang/String;[Ljava/lang/String;)Ljava/lang/Object;");
    jobject ret = env->CallStaticObjectMethod(bcClass, generateMID, superClassNameJ, interfacesJ);
    if(env->ExceptionCheck()) {
        jthrowable e = env->ExceptionOccurred();
        guard.post_delete(e);
        env->ExceptionClear();
        SE_LOGE("Failed to call newInstance:");
        jmethodID ps = env->GetMethodID(env->GetObjectClass(e), "printStackTrace", "()V");
        env->CallVoidMethod(e, ps);
    }

    return ret;
}

static se::Object *registerAnonymousJavaObject(JNIEnv *env, jobject ret, se::Object *instanceCfg) {

    JniLocalRefPostDelete guard(env);

    jclass tmpClass = env->GetObjectClass(ret);
    jfieldID idField = env->GetFieldID(tmpClass, JS_JNI_NATIVE_ID_KEY, "I");
    int instID = env->GetIntField(ret, idField);

    guard.post_delete(tmpClass);

    auto *wrap = new JObject(ret);
    auto *jsObj = wrap->asJSObject();

    jsObj->setProperty(JS_JNI_NATIVE_ID_KEY, se::Value(instID));

    auto &item = sJavaObjectMapToJS[instID];
    item.jsConfig = instanceCfg;
    jsObj->attachObject(instanceCfg);
    instanceCfg->incRef(); //prevent reset from se::Value

    return jsObj;
}

static bool js_jni_helper_impl(se::State &s) {
    static int genObjId = 10000;
    const int argCnt = s.args().size();
    std::string signature;
    jobject ret = nullptr;
    bool ok;

    if (argCnt == 0 || argCnt > 2) {
        SE_REPORT_ERROR("wrong number of arguments: %d", (int) argCnt);
        return false;
    }
    assert(s.args()[0].isObject());
    if (argCnt == 2) {
        if (!s.args()[1].isObject() || !s.args()[1].toObject()->isFunction()) {
            SE_REPORT_ERROR("arg 1 : function expected");
            return false;
        }
    }
    se::Object *instanceCfg = s.args()[0].toObject();
    if (!instanceCfg->hasRealNamedProperty("parentClass") && !instanceCfg->hasRealNamedProperty("interfaces")) {
        se::ScriptEngine::getInstance()->throwException("both `parentClass` & `interfaces` are not set!");
        return false;
    }
    se::Value parentClass;
    se::Value interfaces;
    std::string parentClassStr;
    std::vector<std::string> interfacesList;
    instanceCfg->getProperty("parentClass", &parentClass);
    instanceCfg->getProperty("interfaces", &interfaces);

    if (parentClass.isString()) parentClassStr = parentClass.toString();
    if (interfaces.isObject() && interfaces.toObject()->isArray()) {
        se::Object *array = interfaces.toObject();
        uint32_t len = 0;
        array->getArrayLength(&len);
        se::Value tmp;
        for (int i = 0; i < len; i++) {
            array->getArrayElement(i, &tmp);
            if (tmp.isString()) {
                interfacesList.push_back(tmp.toString());
            }
        }
    }

    auto *env = JniHelper::getEnv();
    JniLocalRefPostDelete guard(env);

    if (argCnt == 1) {
        jobject wrap = genAnonymousJavaObject(parentClassStr, interfacesList);
        guard.post_delete(wrap);
        if (wrap) {
            s.rval().setObject(registerAnonymousJavaObject(env, wrap, instanceCfg));
        }
    } else if (argCnt == 2) {
        se::Object *cb = s.args()[1].toObject();
        cb->incRef();
        instanceCfg->incRef();
        std::thread t([cb, instanceCfg, parentClassStr, interfacesList]() {
            auto *env = JniHelper::getEnv();
            jobject anonyJObj = genAnonymousJavaObject(parentClassStr, interfacesList);
            jobject globlAnonyJobj = env->NewGlobalRef(anonyJObj);
            cocos2d::Application::getInstance()->getScheduler()->performFunctionInCocosThread([instanceCfg, cb, globlAnonyJobj]() {
                auto *env = JniHelper::getEnv();
                se::AutoHandleScope scope;
                se::ValueArray cbArgs;
                cbArgs.resize(1);
                cbArgs[0].setUndefined();
                if (!globlAnonyJobj) {
                    cb->call(cbArgs, nullptr);
                } else {
                    se::Object *wrap = registerAnonymousJavaObject(env, globlAnonyJobj, instanceCfg);
                    cbArgs[0].setObject(wrap);
                    cb->call(cbArgs, nullptr);
                }
                instanceCfg->decRef();
                cb->decRef();
                env->DeleteGlobalRef(globlAnonyJobj);
            });
            env->DeleteLocalRef(anonyJObj);
        });
        t.detach();
        s.rval().setUndefined();
    }
    return true;
}

SE_BIND_FUNC(js_jni_helper_impl)

static bool js_register_jni_helper(se::Object *obj) {
    se::Value helperVal;
    if (!obj->getProperty("utils", &helperVal)) {
        se::HandleObject jsobj(se::Object::createPlainObject());
        helperVal.setObject(jsobj);
        obj->setProperty("utils", helperVal);
    }
    auto *helperObj = helperVal.toObject();
    helperObj->defineFunction("getActivity", _SE(js_jni_helper_getActivity));
    helperObj->defineFunction("newObject", _SE(js_jni_helper_newObject));
    helperObj->defineFunction("impl", _SE(js_jni_helper_impl));
    return true;
}

static bool js_jni_proxy_apply(se::State &s) { return true; }

SE_BIND_FUNC(js_jni_proxy_apply)

static bool js_jni_proxy_get(se::State &s) {
    int argCnt = s.args().size();
    if (argCnt < 2) {
        SE_REPORT_ERROR("wrong number of arguments: %d, 2+ expected", (int) argCnt);
        return false;
    }
    assert(s.args()[0].isObject());
    assert(s.args()[1].isString());

    auto *target = s.args()[0].toObject();
    auto method = s.args()[1].toString();
    auto *receive = s.args()[2].toObject();

    if (method == "$methods") {
        se::Object *funcObj = sJavaObjectMethodsUnboundFunc->bindThis(target);
        s.rval().setObject(funcObj);
        return true;
    } else if (method == "$fields") {
        se::Object *funcObj = sJavaObjectFieldsUnboundFunc->bindThis(target);
        s.rval().setObject(funcObj);
        return true;
    }

    se::Value outvalue;

    auto *inner = (JObject *) target->getPrivateData();
    if (inner) {

        if(method == "root" || method == "unroot") {
            if(inner->getUnderlineJSObject()->getProperty(method.c_str(), &outvalue)) {
                s.rval() = outvalue;
                return true;
            }
        }

        if (inner->getUnderlineJSObject()->getRealNamedProperty(method.c_str(), &outvalue)) {
            s.rval() = outvalue;
            return true;
        }

        {
            JValue fieldValue;
            auto ok = inner->getFieldValue(method, fieldValue);
            if (ok) {
                fieldValue.cast(outvalue);
                s.rval() = outvalue;
                return true;
            }
        }
        {
            std::vector<cocos2d::JniMethodSignature> methods;
            if (inner->findMethods(method, "", methods) && !methods.empty()) {
                auto *ctx = new JNamedMethodsInfo(method, methods, inner);
                s.rval().setObject(sJavaObjectMethodApplyUnboundFunc->bindThis(ctx->asJSObject()));
                return true;
            }
        }
    }

    return true;
}

SE_BIND_FUNC(js_jni_proxy_get)

static bool js_jni_proxy_set(se::State &s) {
    int argCnt = s.args().size();
    if (argCnt < 3) {
        SE_REPORT_ERROR("wrong number of arguments: %d, 3+ expected", (int) argCnt);
        return false;
    }
    assert(s.args()[0].isObject());
    assert(s.args()[1].isString());

    auto *target = s.args()[0].toObject();
    auto prop = s.args()[1].toString();
    s.rval().setBoolean(true); // always return true

    auto *inner = (JObject *) target->getPrivateData();
    if (inner) {
        bool fieldFound = false;
        auto ok =
                setJavaObjectField(inner->getJavaObject(), prop, s.args()[2], fieldFound);
        if (fieldFound) {
            if (!ok) {
                se::ScriptEngine::getInstance()->throwException("failed to set field '" + prop + "'");
                return false;
            }
            return true;
        }
        inner->getUnderlineJSObject()->setProperty(prop.c_str(), s.args()[2]);
    }
    return true;
}

SE_BIND_FUNC(js_jni_proxy_set)

// query public methods of instance
static bool js_jni_proxy_methods(se::State &s) {
    auto *jsThis = s.getJSThisObject();
    if(!jsThis) {
        return false;
    }
    auto *jobjWrapper = (JObject *) jsThis->getPrivateData();
    jobject jobj = jobjWrapper->getJavaObject();
    auto methodNames = JniHelper::getObjectMethods(jobj);
    auto *array = se::Object::createArrayObject(methodNames.size());
    for (int i = 0; i < methodNames.size(); i++) {
        array->setArrayElement(i, se::Value(methodNames[i]));
    }
    s.rval().setObject(array);
    return true;
}

SE_BIND_FUNC(js_jni_proxy_methods)

// query fields of instance
static bool js_jni_proxy_fields(se::State &s) {
    auto *jsThis = s.getJSThisObject();
    if(!jsThis) {
        return false;
    }
    auto *wrapper = (JObject *) jsThis->getPrivateData();
    jobject jThis = wrapper->getJavaObject();
    auto fieldNames = JniHelper::getObjectFields(jThis);
    auto *array = se::Object::createArrayObject(fieldNames.size());
    for (int i = 0; i < fieldNames.size(); i++) {
        array->setArrayElement(i, se::Value(fieldNames[i]));
    }
    s.rval().setObject(array);
    return true;
}

SE_BIND_FUNC(js_jni_proxy_fields)

// query fields of instance

static bool js_jni_proxy_static_method_apply(se::State &s) {
    auto *self = s.getJSThisObject();

    if(!self) {
        return false;
    }

    auto *stub = (JObjectStub *) self->getPrivateData();

    if (stub) {
        se::Object *underline = stub->getUnderlineJSObject();
        se::Value path;
        underline->getProperty(JS_JNI_TAG_PATH, &path);
        std::string pathStr = path.toString();

        if (callStaticJMethod(pathStr, s.args(), s.rval())) {
            return true;
        }

        std::string message = "call '" + pathStr + "' failed!";
        se::ScriptEngine::getInstance()->throwException(message);
    }

    return false;
}

SE_BIND_FUNC(js_jni_proxy_static_method_apply)

static bool js_jni_proxy_object_method_apply(se::State &s) {
    auto *env = JniHelper::getEnv();
    auto *self = s.getJSThisObject();
    auto argCnt = s.args().size();
    bool ok = false;

    auto *ctx = (JNamedMethodsInfo *) self->getPrivateData();
    auto jThis = ctx->self->getJavaObject();
    auto throwException = "method '" + ctx->methodName + "' is not found, or signature mismatch!";
    if (ctx->methods.size() == 1) {
        auto &m = ctx->methods[0];
        std::vector<jvalue> jArgs = jsArgs2JavaArgs(env, m.signature, s.args(), 0, ok);
        if (!ok) {
            se::ScriptEngine::getInstance()->throwException(throwException);
            return false;
        }
        std::string returnType = m.signature.substr(m.signature.find(')') + 1);
        JniUtils::JniType rType = JniUtils::JniType::fromString(returnType);
        ok = callJMethodByReturnType(rType, jThis, m.method, jArgs, s.rval());
        if (env->ExceptionCheck()) {
            JniLocalRefPostDelete guard(env);
            jthrowable e = env->ExceptionOccurred();
            guard.post_delete(e);
            env->ExceptionClear();
            if (e) {
                auto printStackTrace = env->GetMethodID(env->GetObjectClass(e), "printStackTrace", "()V");
                env->CallVoidMethod(e, printStackTrace);
            }
            se::ScriptEngine::getInstance()->throwException("java exception caught");
        }
        return ok;
    } else {
        for (const cocos2d::JniMethodSignature &m : ctx->methods) {
            auto argsFromSignature = JniUtils::exactArgsFromSignature(m.signature, ok);
            if (argsFromSignature.size() == argCnt) {
                std::vector<jvalue> jArgs = jsArgs2JavaArgs(env, m.signature, s.args(), 0, ok);
                if (!ok)
                    continue;
                std::string returnType = m.signature.substr(m.signature.find(')') + 1);
                JniUtils::JniType rType = JniUtils::JniType::fromString(returnType);
                ok = callJMethodByReturnType(rType, jThis, m.method, jArgs, s.rval());
                if (!ok || env->ExceptionCheck()) {
                    env->ExceptionClear();
                    continue;
                }
                return true;
            }
        }
    }
    se::ScriptEngine::getInstance()->throwException(throwException);
    return false;
}

SE_BIND_FUNC(js_jni_proxy_object_method_apply)

// base function of jpath
static bool js_jni_proxy_java_path_base(se::State &s) { return true; }

SE_BIND_FUNC(js_jni_proxy_java_path_base)

// construct class / or inner class
static bool js_jni_proxy_java_path_construct(se::State &s) {
    auto argCnt = s.args().size();
    if (argCnt < 2) {
        SE_REPORT_ERROR("wrong number of arguments: %d, 2+ expected", (int) argCnt);
        return false;
    }
    assert(s.args()[0].isObject());
    assert(s.args()[1].isObject());

    auto *target = s.args()[0].toObject();
    auto *args = s.args()[1].toObject(); // Array

    auto *stub = (JObjectStub *) target->getPrivateData();
    if (stub) {
        se::Value path;
        se::Object *underline = stub->getUnderlineJSObject();
        underline->getProperty(JS_JNI_TAG_PATH, &path);
        std::string pathStr = path.toString();
        JniLocalRefPostDelete guard;
        jobject ret = constructJavaObjectByClassPath(pathStr, args);
        guard.post_delete(ret);
        if (ret) {
            auto *jThis = new JObject(ret);
            s.rval().setObject(jThis->asJSObject());
            return true;
        }
        se::ScriptEngine::getInstance()->throwException("constructor of " + pathStr + " not found or parameters mismatch!");
    }
    auto *poj = se::Object::createPlainObject();
    s.rval().setObject(poj);
    return true;
}

SE_BIND_FUNC(js_jni_proxy_java_path_construct)

//// query fields of instance
static bool js_jni_proxy_java_path_set(se::State &s) {
    auto *env = JniHelper::getEnv();
    auto argCnt = s.args().size();
    if (argCnt < 3) {
        SE_REPORT_ERROR("wrong number of arguments: %d, 3+ expected", (int) argCnt);
        return false;
    }
    assert(s.args()[0].isObject());
    assert(s.args()[1].isString());

    auto *target = s.args()[0].toObject();
    auto field = s.args()[1].toString();

    s.rval().setBoolean(true);

    auto *stub = (JObjectStub *) target->getPrivateData();
    if (stub) {
        se::Value path;
        se::Object *underline = stub->getUnderlineJSObject();
        underline->getProperty(JS_JNI_TAG_PATH, &path);
        if (path.isString()) {
            auto &pathStr = path.toString();
            std::string newPath = pathStr.empty() ? field : pathStr + "." + field;

            se::Value fieldValue;
            if (JniHelper::hasStaticField(newPath)) {
                if (!setJavaObjectStaticField(newPath, s.args()[2])) {
                    se::ScriptEngine::getInstance()->throwException("can not set static property");
                    return false;
                }
                return true;
            }
        }

        underline->setProperty(field.c_str(), s.args()[2]);
        return true;
    }

    return false;
}

SE_BIND_FUNC(js_jni_proxy_java_path_set)

// query fields of instance
static bool js_jni_proxy_java_path_get(se::State &s) {
    auto *env = JniHelper::getEnv();
    auto argCnt = s.args().size();
    if (argCnt < 2) {
        SE_REPORT_ERROR("wrong number of arguments: %d, 2+ expected", (int) argCnt);
        return false;
    }
    assert(s.args()[0].isObject());
    assert(s.args()[1].isString());

    auto *target = s.args()[0].toObject();
    auto field = s.args()[1].toString();

    auto *stub = (JObjectStub *) target->getPrivateData();
    if (stub) {
        se::Value path;
        se::Object *underline = stub->getUnderlineJSObject();

        if (underline->getRealNamedProperty(field.c_str(), &path)) {
            s.rval() = path;
            return true;
        }
        if (field[0] != '_') {

            underline->getProperty(JS_JNI_TAG_PATH, &path);
            std::string pathStr = path.toString();
            std::string newPath = pathStr.empty() ? field : pathStr + "." + field;

            se::Value fieldValue;
            if (getJavaObjectStaticField(newPath, fieldValue)) {
                s.rval() = fieldValue;
                return true;
            }

            auto *newStub = new JObjectStub(newPath);
            if (hasStaticMethod(newPath)) {
                se::Object *func = sJavaStaticMethodApplyUnboundFunc->bindThis(newStub->getUnderlineJSObject());
                s.rval().setObject(func);
                return true;
            }

            s.rval().setObject(newStub->asJSObject());
            return true;
        }
    }
    return true;
}

SE_BIND_FUNC(js_jni_proxy_java_path_get)

static void setup_proxy_object() {
    sJavaObjectProxy = se::Object::createPlainObject();
    sJavaObjectProxy->defineFunction("apply", _SE(js_jni_proxy_apply));
    sJavaObjectProxy->defineFunction("get", _SE(js_jni_proxy_get));
    sJavaObjectProxy->defineFunction("set", _SE(js_jni_proxy_set));
    sJavaObjectProxy->root();

    sJavaObjectStubProxy = se::Object::createPlainObject();
    sJavaObjectStubProxy->defineFunction("construct", _SE(js_jni_proxy_java_path_construct));
    sJavaObjectStubProxy->defineFunction("get", _SE(js_jni_proxy_java_path_get));
    sJavaObjectStubProxy->defineFunction("set", _SE(js_jni_proxy_java_path_set));
    sJavaObjectStubProxy->root();

    sJavaObjectMethodsUnboundFunc = se::Object::createFunctionObject(nullptr, _SE(js_jni_proxy_methods));
    sJavaObjectMethodsUnboundFunc->root();

    sJavaObjectFieldsUnboundFunc = se::Object::createFunctionObject(nullptr, _SE(js_jni_proxy_fields));
    sJavaObjectFieldsUnboundFunc->root();

    sJavaObjectMethodApplyUnboundFunc = se::Object::createFunctionObject(nullptr, _SE(js_jni_proxy_object_method_apply));
    sJavaObjectMethodApplyUnboundFunc->root();

    sJavaStaticMethodApplyUnboundFunc = se::Object::createFunctionObject(nullptr, _SE(js_jni_proxy_static_method_apply));
    sJavaStaticMethodApplyUnboundFunc->root();
}

bool jsb_register_jni_manual(se::Object *obj) {
    setup_proxy_object();
    se::Value nsVal;
    if (!obj->getProperty("java", &nsVal)) {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("java", nsVal);
    }
    auto *ns = nsVal.toObject();
    js_register_jni_jobject(ns);
    js_register_jni_helper(ns);
    js_register_jni_jmethod_invoke_instance(ns);

    {
        // java object in global object
        auto *p = new JObjectStub();
        ns->setProperty("import", se::Value(p->asJSObject()));
    }
    return true;
}

extern "C" {
JNIEXPORT void JNICALL JNI_BYTECODE_GENERATOR(registerInstance)(JNIEnv *env,
                                                                jclass klass,
                                                                jobject self,
                                                                jint id) {
    auto &item = sJavaObjectMapToJS[id];
    if (item.jThis != nullptr) {
        delete item.jThis;
    }
    item.jThis = new JObject(self);
}


JNIEXPORT jobject JNICALL JNI_BYTECODE_GENERATOR(callJS)(JNIEnv *env,
                                                         jclass klass,
                                                         jobject finished,
                                                         jstring methodName,
                                                         jobjectArray args) {
    JniLocalRefPostDelete guard(env);
    se::AutoHandleScope scope;
    Defer setState([&]() {
        JniHelper::callObjectVoidMethod(finished, "java/util/concurrent/atomic/AtomicBoolean", "set", true);
    });

    int argCnt = env->GetArrayLength(args);
    jobject mapKey = env->GetObjectArrayElement(args, 0);
    jobject thisObject = env->GetObjectArrayElement(args, 1);

    guard.post_delete(mapKey);
    guard.post_delete(thisObject);

    std::string functionName = jstringToString(methodName);

    int keyInt = JniHelper::callObjectIntMethod(mapKey, "java/lang/Integer", "intValue");
    auto &item = sJavaObjectMapToJS[keyInt];

    assert(env->IsSameObject(thisObject, item.jThis->getJavaObject()));

    std::vector<se::Value> jsArgs;
    for (int i = 2; i < argCnt; i++) {
        se::Value tmp;
        jobject argI = env->GetObjectArrayElement(args, i);
        jobject_to_seval2(env, argI, tmp);
        jsArgs.push_back(tmp);
        env->DeleteLocalRef(argI);
    }

    se::Object *configObject = item.jsConfig;
    if (!configObject) {
        SE_LOGE("js config object not found!");
        return nullptr;
    }
    se::Value jsProperty;
    configObject->getProperty(functionName.c_str(), &jsProperty);

    if (!jsProperty.isObject() || !jsProperty.toObject()->isFunction()) {
        SE_LOGE("funtion '%s' not found in js config object, id %d", functionName.c_str(), keyInt);
        auto keys = configObject->keys();
        SE_LOGE(" %d keys", (int) keys.size());
        for (auto &k : keys) {
            SE_LOGE("   %s", k.c_str());
        }
        SE_LOGE(" config object: %s, addr: %p, keys: ", configObject->toString().c_str(), configObject);
        return nullptr;
    }

    se::Object *jsFunction = jsProperty.toObject();
    se::Value ret;
    if (!jsFunction->call(jsArgs, item.jThis->asJSObject(), &ret)) {
        SE_LOGE("failed to call js function '%s' from js config object", functionName.c_str());
        return nullptr;
    }

    if (ret.isNullOrUndefined()) {
        return nullptr;
    } else {
        return seval_to_jobject(env, ret);
    }
}
}

#endif