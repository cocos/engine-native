
#pragma once

#include "base/ccConfig.h"
#include "jsb_global.h"
#include <sstream>
#include <string>
#include <vector>
#include "jni.h"
#include "platform/android/jni/JniHelper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) && CC_ENABLE_JNI_BINDING

#define JS_JNI_TAG_TYPE "$jni_obj_type"
#define JS_JNI_JCLASS_TYPE "$class_name"
#define JS_JNI_TAG_PATH "$package_path"
#define JS_JNI_PROXY_TARGET "$proxy_target"
#define JS_JNI_NATIVE_ID_KEY "__native_id__"

#define jstringToString(str) cocos2d::JniHelper::jstring2string((jstring)(str))

extern se::Class *__jsb_jni_jmethod_invoke_instance;
extern se::Object *sJavaObjectStubProxy;
extern se::Class *__jsb_jni_jobject;
extern se::Object *sJavaObjectProxy;


namespace JniUtils {

    enum class JniTypeEnum : uint8_t {
        None,
        Void_V,
        Boolean_Z,
        Char_C,
        Short_S,
        Byte_B,
        Int_I,
        Long_J,
        Float_F,
        Double_D,
        Object_L,
        MAX_TYPE
    };



    struct JniType {
        int dim = 0;
        JniTypeEnum type = JniTypeEnum::None;
        std::string klassName;

        JniType() = default;

        JniType(const JniType &o) {
            type = o.type;
            dim = o.dim;
            klassName = o.klassName;
        }

        JniType(JniType &&other) {
            this->dim = other.dim;
            this->type = other.type;
            this->klassName = std::move(other.klassName);
            other.dim = 0;
            other.type = JniTypeEnum::None;
        }
        JniType& operator = (const JniType &o) {
            type = o.type;
            dim = o.dim;
            klassName = o.klassName;
            return *this;
        }

        JniType rankDec() const {
            JniType b(*this);
            b.dim -= 1;
            return b;
        }

        static JniType from(JniTypeEnum e);

        static JniType fromString(const std::string &name);

        static std::string reparse(const std::string &);

        std::string toString() const;

        inline bool isNone() const { return type == JniTypeEnum::None; }

        inline bool isVoid() const { return type == JniTypeEnum::Void_V; }

        inline bool isBoolean() const { return type == JniTypeEnum::Boolean_Z; }

        inline bool isChar() const { return type == JniTypeEnum::Char_C; }

        inline bool isShort() const { return type == JniTypeEnum::Short_S; }

        inline bool isByte() const { return type == JniTypeEnum::Byte_B; }

        inline bool isInt() const { return type == JniTypeEnum::Int_I; }

        inline bool isLong() const { return type == JniTypeEnum::Long_J; }

        inline bool isFloat() const { return type == JniTypeEnum::Float_F; }

        inline bool isDouble() const { return type == JniTypeEnum::Double_D; }

        inline bool isObject() const { return type == JniTypeEnum::Object_L; }

        inline bool isMAX() const { return type == JniTypeEnum::MAX_TYPE; }

        inline const std::string &getClassName() const { return klassName; }
    };

    std::vector<JniUtils::JniType> exactArgsFromSignature(const std::string &signature, bool &success);

    bool parseSigType(const char *data, size_t max_length, size_t *len, JniType *type);

    std::string jthrowableToString(jthrowable e);

    bool getJavaFieldByType(JNIEnv *env, jobject jthis, const JniUtils::JniType &type, jfieldID fieldId, jvalue &ret);

    bool setJavaObjectField(jobject obj, const std::string &fieldName, const se::Value &value, bool &hasField);

    jvalue seval_to_jvalule(JNIEnv *env, const JniUtils::JniType &def, const se::Value &val, bool &ok);

    bool jobject_to_seval(JNIEnv *env, const JniUtils::JniType &type, jvalue obj, se::Value &out);

    bool jobject_to_seval2(JNIEnv *env, jobject obj, se::Value &out);

    std::vector<jvalue> jsArgs2JavaArgs(JNIEnv *env, const std::string &signature, const std::vector<se::Value> &args, int offset, bool &success);

    bool getJavaObjectStaticFieldByType(JNIEnv *env, jclass kls, jfieldID field, const JniUtils::JniType &type, se::Value &out);

    bool setJavaObjectStaticFieldByType(JNIEnv *env, jclass kls, jfieldID field, const JniUtils::JniType &type, const se::Value &in);

    bool callStaticJMethod(const std::string &longPath, const std::vector<se::Value> &args, se::Value &out);

    bool setJavaObjectField(jobject obj, const std::string &fieldName, const se::Value &value, bool &hasField);

    jobject constructJavaObjectByClassPath(const std::string &path, se::Object *args);

    bool getJavaObjectStaticField(const std::string &longPath, se::Value &ret);

    bool setJavaObjectStaticField(const std::string &longPath, const se::Value &ret);

    bool callJMethodByReturnType(const JniUtils::JniType &rType, jobject jthis, jmethodID method, const std::vector<jvalue> &jvalueArray, se::Value &out);

    jobject seval_to_jobject(JNIEnv *env, const se::Value &input);

    bool hasStaticMethod(const std::string &longPath);

    bool callStaticJMethod(const std::string &longPath, const std::vector<se::Value> &args, se::Value &out);

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

    class JObject {
    public:
        explicit JObject(jobject obj) {
            if (obj) {
                _javaObject = cocos2d::JniHelper::getEnv()->NewGlobalRef(obj);
            }
        }

        virtual ~JObject() {
            if (_javaObject) {
                cocos2d::JniHelper::getEnv()->DeleteGlobalRef(_javaObject);
                _javaObject = nullptr;
            }
        }

        se::Object *asJSObject();

        jobject getJavaObject() const {
            assert(_javaObject);
            return _javaObject;
        }

        jclass getClass() const {
            return cocos2d::JniHelper::getEnv()->GetObjectClass(_javaObject);
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

    struct JavaToJSTuple {
        JObject *jThis = nullptr;
        se::Object *jsConfig = nullptr;
    };


} // namespace jni_utils

#endif