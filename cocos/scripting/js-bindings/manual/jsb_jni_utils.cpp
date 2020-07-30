
#include "base/ccConfig.h"
#include "jsb_jni_utils.hpp"
#include "cocos/scripting/js-bindings/jswrapper/config.hpp"
#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "jsb_global.h"

#include <cassert>
#include <regex>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) && CC_ENABLE_JNI_BINDING

SE_DECLARE_FUNC(js_jni_proxy_java_path_base);

namespace JniUtils {

    using namespace cocos2d;

    JniType JniType::from(JniTypeEnum e) {
        JniType ret;
        switch (e) {
            case JniTypeEnum::Void_V:
            case JniTypeEnum::Boolean_Z:
            case JniTypeEnum::Char_C:
            case JniTypeEnum::Byte_B:
            case JniTypeEnum::Short_S:
            case JniTypeEnum::Int_I:
            case JniTypeEnum::Long_J:
            case JniTypeEnum::Float_F:
            case JniTypeEnum::Double_D:
                ret.type = e;
                return ret;
            default:
                break;
        }
        return ret;
    }

    JniType JniType::fromString(const std::string &name_) {
        JniType ret;
        std::regex reg("^\\[*(V|Z|C|S|B|I|J|F|D|L.*;)$");

        if (std::regex_match(name_, reg)) {
            size_t offset;
            std::regex dot_reg("\\.");
            auto name = std::regex_replace(name_, dot_reg, "/");
            parseSigType(name.c_str(), name.length(), &offset, &ret);
            return ret;
        }

        ret.dim = std::count(name_.c_str(), name_.c_str() + name_.size(), ']');
        auto p = name_.find('[');
        auto name = name_;
        if (p != std::string::npos) {
            name.resize(p);
        }
        if (name == "int") {
            ret.type = JniTypeEnum::Int_I;
        } else if (name == "float") {
            ret.type = JniTypeEnum::Float_F;
        } else if (name == "void") {
            ret.type = JniTypeEnum::Void_V;
        } else if (name == "double") {
            ret.type = JniTypeEnum::Double_D;
        } else if (name == "long") {
            ret.type = JniTypeEnum::Long_J;
        } else if (name == "char") {
            ret.type = JniTypeEnum::Char_C;
        } else if (name == "byte") {
            ret.type = JniTypeEnum::Byte_B;
        } else if (name == "short") {
            ret.type = JniTypeEnum::Short_S;
        } else if (name == "boolean") {
            ret.type = JniTypeEnum::Boolean_Z;
        } else {
            ret.type = JniTypeEnum::Object_L;
            std::regex regex("\\.");
            ret.klassName = std::regex_replace(name, regex, "/");
        }
        return ret;
    }

    std::string JniType::reparse(const std::string &name) {
        return fromString(name).toString();
    }

    std::string JniType::toString() const {
        std::stringstream ss;
        auto d = this->dim;
        while (d > 0) {
            ss << "[";
            d--;
        }
        switch (type) {
            case JniUtils::JniTypeEnum::None:
                ss << "";
                break;
            case JniUtils::JniTypeEnum::Void_V:
                ss << "V";
                break;
            case JniUtils::JniTypeEnum::Boolean_Z:
                ss << "Z";
                break;
            case JniUtils::JniTypeEnum::Char_C:
                ss << "C";
                break;
            case JniUtils::JniTypeEnum::Byte_B:
                ss << "B";
                break;
            case JniUtils::JniTypeEnum::Short_S:
                ss << "S";
                break;
            case JniUtils::JniTypeEnum::Int_I:
                ss << "I";
                break;
            case JniUtils::JniTypeEnum::Long_J:
                ss << "J";
                break;
            case JniUtils::JniTypeEnum::Float_F:
                ss << "F";
                break;
            case JniUtils::JniTypeEnum::Double_D:
                ss << "D";
                break;
            case JniUtils::JniTypeEnum::Object_L:
                ss << "L" << klassName << ";";
                break;
            default:
                assert(false);
                break;
        }
        return ss.str();
    }

    bool parseSigType(const char *data, size_t max_length, size_t *len,
                      JniType *type) {
        size_t i = 0;
        const char f = data[i];
        *len += 1;
        switch (f) {
            case 'V':
                type->type = JniTypeEnum::Void_V;
                return true;
            case 'Z':
                type->type = JniTypeEnum::Boolean_Z;
                return true;
            case 'C':
                type->type = JniTypeEnum::Char_C;
                return true;
            case 'S':
                type->type = JniTypeEnum::Short_S;
                return true;
            case 'B':
                type->type = JniTypeEnum::Byte_B;
                return true;
            case 'I':
                type->type = JniTypeEnum::Int_I;
                return true;
            case 'J':
                type->type = JniTypeEnum::Long_J;
                return true;
            case 'F':
                type->type = JniTypeEnum::Float_F;
                return true;
            case 'D':
                type->type = JniTypeEnum::Double_D;
                return true;
                //            case ';':
                //                return true;
            default:;
        }

        if (f == '[') {
            type->dim += 1;
            return parseSigType(data + 1, max_length - 1, len, type);
        } else if (f == 'L') {
            i = 1;
            while (i < max_length && data[i] != ';') {
                i++;
            }
            if (i == max_length) {
                return false;
            }
            type->klassName = std::string(data + 1, i - 1);
            type->type = JniTypeEnum::Object_L;
            *len += i;
            return true;
        }
        return false;
    }

    std::vector<JniUtils::JniType>
    exactArgsFromSignature(const std::string &signature, bool &success) {
        int i = 0;
        const int e = signature.length();
        if (signature[i] != '(') {
            success = false;
            return {};
        }
        auto qtR = signature.find_last_of(')');
        if (qtR == std::string::npos) {
            success = false;
            return {};
        }
        const char *data = signature.data() + 1;
        size_t max_length = qtR - 1;
        size_t delta = 0;
        JniUtils::JniType localType;
        bool ok = false;
        std::vector<JniUtils::JniType> argTypeList;
        do {
            ok = JniUtils::parseSigType(data, max_length, &delta, &localType);
            if (ok) {
                argTypeList.push_back(std::move(localType));
                data += delta;
                max_length -= delta;
                delta = 0;
            }
        } while (ok);

        success = true;

        return argTypeList;
    }



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
                              std::vector<JniMethodSignature> &list) {
        auto *env = JniHelper::getEnv();
        JniLocalRefPostDelete gurad(env);

        std::string className = JniHelper::getObjectClass(_javaObject);
        jclass jobjClass = env->GetObjectClass(_javaObject);
        gurad.post_delete(jobjClass);

        JniMethodSignature oMethod;
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

    bool setJavaObjectField(jobject obj, const std::string &fieldName, const se::Value &value, bool &hasField) {
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


    bool getJavaFieldByType(JNIEnv *env, jobject jthis, const JniUtils::JniType &type, jfieldID fieldId, jvalue &ret) {
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

    bool callStaticJMethod(const std::string &longPath, const std::vector<se::Value> &args, se::Value &out) {
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



} // namespace jni_utils


#endif
