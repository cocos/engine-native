
#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/JniImp.h"
#include "cocos/scripting/js-bindings/manual/jsb_jni_utils.hpp"

#include "cocos/scripting/js-bindings/jswrapper/config.hpp"
#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"

#include "cocos/platform/CCApplication.h"
#include "cocos/base/CCScheduler.h"

using namespace JniUtils;
using namespace cocos2d;

extern std::unordered_map<int, JavaToJSTuple> sJavaObjectMapToJS;
namespace {

    class Defer {
    public:
        explicit Defer(std::function<void()> x) : _cb(std::move(x)) {};

        virtual ~Defer() {
            _cb();
        }

    private:
        std::function<void()> _cb;
    };

}

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_org_cocos2dx_lib_ByteCodeGenerator_registerInstance(JNIEnv *env,
                                                                                jclass klass,
                                                                                jobject self,
                                                                                jint id) {
    auto &item = sJavaObjectMapToJS[id];
    if (item.jThis != nullptr) {
        delete item.jThis;
    }
    item.jThis = new JObject(self);
}


JNIEXPORT jobject JNICALL Java_org_cocos2dx_lib_ByteCodeGenerator_callJS(JNIEnv *env,
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
#ifdef __cplusplus
}
#endif


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
    jmethodID generateMID = env->GetStaticMethodID(bcClass, "newInstance", "(Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;)Ljava/lang/Object;");
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

bool jsb_register_jni_impl(se::Object *obj) {
    se::Value javaVal;
    se::Value helperVal;
    if(!obj->getProperty("java", &javaVal)) {
        se::HandleObject jsobj(se::Object::createPlainObject());
        javaVal.setObject(jsobj);
        obj->setProperty("java", javaVal);
    }

    if (!javaVal.toObject()->getProperty("utils", &helperVal)) {
        se::HandleObject jsobj(se::Object::createPlainObject());
        helperVal.setObject(jsobj);
        javaVal.toObject()->setProperty("utils", helperVal);
    }
    auto *helperObj = helperVal.toObject();
    helperObj->defineFunction("impl", _SE(js_jni_helper_impl));
    return true;
}
