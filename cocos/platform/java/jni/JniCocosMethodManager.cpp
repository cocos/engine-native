#include <jni.h>
#include <thread>
#include <platform/Application.h>
#include <platform/java/jni/JniHelper.h>
#include <cocos/bindings/jswrapper/v8/ScriptEngine.h>
extern "C"
JNIEXPORT void JNICALL
Java_com_cocos_lib_CocosMethodManager_informScript(JNIEnv *env, jclass clazz,
                                                                    jstring methodName, jstring arg) {
    // TODO: implement dispatchJsCustomEvent()
    std::string c_methodName {cc::JniHelper::jstring2string(methodName)};
    std::string c_arg{cc::JniHelper::jstring2string(arg)};

    std::string scriptStr { "cc.MethodManager.applyMethod(\"" + c_methodName + "\",\"" + c_arg + "\")" };
    cc::Application::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
        bool ok = se::ScriptEngine:: getInstance()->evalString(scriptStr.c_str());
    });
}