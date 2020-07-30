

#include "base/ccConfig.h"
#include "jsb_conversions.hpp"
#include "jsb_global.h"
#include "jsb_jni_utils.hpp"
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



using cocos2d::JniHelper;
using cocos2d::JniMethodInfo;
using cocos2d::JniLocalRefPostDelete;
using namespace JniUtils;

SE_DECLARE_FUNC(js_jni_proxy_java_path_base);

#define jstringToString(str) cocos2d::JniHelper::jstring2string((jstring)(str))

se::Class *__jsb_jni_jobject = nullptr;
se::Class *__jsb_jni_jmethod_invoke_instance = nullptr;
se::Object *sJavaObjectProxy = nullptr;
se::Object *sJavaObjectStubProxy = nullptr;
namespace {
    se::Object *sJavaObjectMethodsUnboundFunc = nullptr;
    se::Object *sJavaObjectFieldsUnboundFunc = nullptr;
    se::Object *sJavaObjectMethodApplyUnboundFunc = nullptr;
    se::Object *sJavaStaticMethodApplyUnboundFunc = nullptr;
}

std::unordered_map<int, JavaToJSTuple> sJavaObjectMapToJS;

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



#endif