
/****************************************************************************
 Copyright (c) 2022-2023 Xiamen Yaji Software Co., Ltd.

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
#include "platform/openharmony/napi/NapiHelper.h"
#include "platform/openharmony/OpenHarmonyPlatform.h"
#include "HelperMacros.h"
#include "cocos/platform/openharmony/FileUtils-openharmony.h"
#include "scripting/js-bindings/jswrapper/SeApi.h"
#include "ui/edit-box/EditBox-openharmony.h"
#include "ui/webview/WebViewImpl-openharmony.h"
#include "platform/openharmony/WorkerMessageQueue.h"
#include "platform/CCDevice.h"
#define KEYCODE_BACK_OH 6

namespace cocos2d {

// Must be the same as the value called by js
enum ContextType {
    APP_LIFECYCLE = 0,
    JS_PAGE_LIFECYCLE,
    XCOMPONENT_CONTEXT,
    XCOMPONENT_REGISTER_LIFECYCLE_CALLBACK,
    NATIVE_RENDER_API,
    WORKER_INIT,
    ENGINE_UTILS,
    EDITBOX_UTILS,
    WEBVIEW_UTILS,
    DISPLAY_UTILS,
    UV_ASYNC_SEND,
};

static Napi::Env gWorkerEnv(nullptr);
static Napi::FunctionReference *gPostMessageToUIThreadFunc = nullptr;
static Napi::FunctionReference *gPostSyncMessageToUIThreadFunc = nullptr;

#define DEFINE_FUNCTION_CALLBACK(functionName, cachedFunctionRefPtr)                                             \
    static void functionName(const Napi::CallbackInfo &info) {                                                   \
        Napi::Env env = info.Env();                                                                              \
        if (info.Length() != 1) {                                                                                \
            Napi::Error::New(env, "setPostMessageFunction, 1 argument expected").ThrowAsJavaScriptException();   \
            return;                                                                                              \
        }                                                                                                        \
                                                                                                                 \
        if (!info[0].IsFunction()) {                                                                             \
            Napi::TypeError::New(env, "setPostMessageFunction, function expected").ThrowAsJavaScriptException(); \
            return;                                                                                              \
        }                                                                                                        \
                                                                                                                 \
        delete cachedFunctionRefPtr;                                                                             \
        cachedFunctionRefPtr = new Napi::FunctionReference(Napi::Persistent(info[0].As<Napi::Function>()));      \
    }

DEFINE_FUNCTION_CALLBACK(js_set_PostMessage2UIThreadCallback, gPostMessageToUIThreadFunc)
DEFINE_FUNCTION_CALLBACK(js_set_PostSyncMessage2UIThreadCallback, gPostSyncMessageToUIThreadFunc)

/* static */
void NapiHelper::postMessageToUIThread(const std::string &type, Napi::Value param) {
    if (gPostMessageToUIThreadFunc == nullptr) {
      LOGE("callback was not set %s, type: %s", __FUNCTION__, type.c_str());
      return;
    }
    gPostMessageToUIThreadFunc->Call({Napi::String::New(getWorkerEnv(), type), param});
}

/* static */
Napi::Value NapiHelper::postSyncMessageToUIThread(const std::string &type, Napi::Value param) {
    if (gPostSyncMessageToUIThreadFunc == nullptr) {
        LOGE("callback was not set %s, type: %s", __FUNCTION__, type.c_str());
        return getWorkerEnv().Undefined();
    }

    // it return a promise object
    return gPostSyncMessageToUIThreadFunc->Call({Napi::String::New(getWorkerEnv(), type), param}).As<Napi::Promise>();
}

/* static */
Napi::Value NapiHelper::napiCallFunction(const char *functionName) {
    auto env = getWorkerEnv();
    auto funcVal = env.Global().Get(functionName);
    if (!funcVal.IsFunction()) {
        return {};
    }
    return funcVal.As<Napi::Function>().Call(env.Global(), {});
}

/* static */
Napi::Value NapiHelper::napiCallFunction(const char *functionName, float duration) {
    auto env = getWorkerEnv();
    auto funcVal = env.Global().Get(functionName);
    if (!funcVal.IsFunction()) {
        return {};
    }
    const std::initializer_list<napi_value> args = { Napi::Number::New(env, duration) };
    return funcVal.As<Napi::Function>().Call(env.Global(), args);
}

// NAPI Interface
static bool exportFunctions(Napi::Object exports) {
    Napi::MaybeOrValue<Napi::Value> xcomponentObject = exports.Get(OH_NATIVE_XCOMPONENT_OBJ);
    if (!xcomponentObject.IsObject()) {
        LOGE("Could not get property: %s", OH_NATIVE_XCOMPONENT_OBJ);
        return false;
    }

    auto *nativeXComponent = Napi::ObjectWrap<OH_NativeXComponent>::Unwrap(xcomponentObject.As<Napi::Object>());
    if (nativeXComponent == nullptr) {
        LOGE("nativeXComponent is nullptr");
        return false;
    }

    OpenHarmonyPlatform::getInstance()->setNativeXComponent(nativeXComponent);
    return true;
}

// APP Lifecycle
static void napiOnCreate(const Napi::CallbackInfo &info) {
    LOGI("NapiHelper::napiOnCreate");
}

static void napiOnShow(const Napi::CallbackInfo &info) {
    LOGI("NapiHelper::napiOnShow");
    cocos2d::WorkerMessageData data{cocos2d::MessageType::WM_APP_SHOW, nullptr, nullptr};
    OpenHarmonyPlatform::getInstance()->enqueue(data);

    Application* app = OpenHarmonyPlatform::getInstance()->g_app;
    if (app) {
        app->onResume();
    }
}

static void napiOnHide(const Napi::CallbackInfo &info) {
    LOGI("NapiHelper::napiOnHide");
    cocos2d::WorkerMessageData data{cocos2d::MessageType::WM_APP_HIDE, nullptr, nullptr};
    OpenHarmonyPlatform::getInstance()->enqueue(data);
    Application* app = OpenHarmonyPlatform::getInstance()->g_app;
    if (app) {
        app->onPause();
    }
}

static void napiOnBackPress(const Napi::CallbackInfo &info) {
    LOGI("NapiHelper::napiOnBackPress");
    KeyboardEvent event;
    event.key = KEYCODE_BACK_OH;
    event.action = KeyboardEvent::Action::RELEASE;
    EventDispatcher::dispatchKeyboardEvent(event);
}

static void napiOnDestroy(const Napi::CallbackInfo &info) {
    LOGI("NapiHelper::napiOnDestroy");
    cocos2d::WorkerMessageData data{cocos2d::MessageType::WM_APP_DESTROY, nullptr, nullptr};
    OpenHarmonyPlatform::getInstance()->enqueue(data);
}



// JS Page : Lifecycle
static void napiOnPageShow(const Napi::CallbackInfo &info) {
    LOGI("NapiHelper::napiOnPageShow");
}

static void napiOnPageHide(const Napi::CallbackInfo &info) {
    LOGI("NapiHelper::napiOnPageHide");
}

static void napiNativeEngineInit(const Napi::CallbackInfo &info) {
#if SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_NAPI
    se::ScriptEngine::setEnv(info.Env());
#endif
    LOGI("napiNativeEngineInit before run");
    OpenHarmonyPlatform::getInstance()->run(0, nullptr);
    LOGI("napiNativeEngineInit after run");
}

static void napiNativeEngineStart(const Napi::CallbackInfo &info) {
    LOGD("NapiHelper::napiNativeEngineStart");
    OpenHarmonyPlatform::getInstance()->requestVSync();
}

static void napiWorkerInit(const Napi::CallbackInfo &info) {
    LOGI("NapiHelper::napiWorkerInit ...");
    Napi::Env env = info.Env();
    uv_loop_t *loop = nullptr;
    napi_status status = napi_get_uv_event_loop(napi_env(env), &loop);
    if (status != napi_ok) {
        LOGE("napi_get_uv_event_loop failed!");
        return;
    }
    OpenHarmonyPlatform::getInstance()->workerInit(loop);
}

static void napiOnDisplayChange(const Napi::CallbackInfo &info) {
    if (info.Length() != 1) {
        Napi::Error::New(info.Env(), "1 argument expected").ThrowAsJavaScriptException();
        return;
    }

     int32_t value = info[0].As<Napi::Number>().Int32Value();
     cocos2d::Device::Rotation rotation = cocos2d::Device::Rotation::_0;
    if(value == 0) {
        rotation = cocos2d::Device::Rotation::_0;
    } else if(value == 1) {
        // TODO(qgh): The openharmony platform is rotated clockwise.
        rotation = cocos2d::Device::Rotation::_270;
    } else if(value == 2) {
        rotation = cocos2d::Device::Rotation::_180;
    } else if(value == 3) {
        // TODO(qgh): The openharmony platform is rotated clockwise.
        rotation = cocos2d::Device::Rotation::_90;
    }
    EventDispatcher::dispatchOrientationChangeEvent((int)rotation);
}

static void napiResourceManagerInit(const Napi::CallbackInfo &info) {
    if (info.Length() != 1) {
        Napi::Error::New(info.Env(), "1 argument expected").ThrowAsJavaScriptException();
        return;
    }

    FileUtilsOpenHarmony::initResourceManager(napi_env(info.Env()), napi_value(info[0]));
}

static void napiWritablePathInit(const Napi::CallbackInfo &info) {
    if (info.Length() != 1) {
        Napi::Error::New(info.Env(), "1 argument expected").ThrowAsJavaScriptException();
        return;
    }

    if (!info[0].IsString()) {
        Napi::Error::New(info.Env(), "string expected").ThrowAsJavaScriptException();
        return;
    }

    FileUtilsOpenHarmony::_ohWritablePath = info[0].As<Napi::String>().Utf8Value();
}

static void napiASend(const Napi::CallbackInfo &info) {
    OpenHarmonyPlatform::getInstance()->triggerMessageSignal();
}

// NAPI Interface
static Napi::Value getContext(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    size_t argc = info.Length();
    if (argc != 1) {
        Napi::Error::New(env, "Wrong argument count, 1 expected!").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    if (!info[0].IsNumber()) {
        Napi::TypeError::New(env, "number expected!").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    auto exports = Napi::Object::New(env);
    int64_t value = info[0].As<Napi::Number>().Int64Value();

    switch (value) {
        case APP_LIFECYCLE: {
            exports["onCreate"] = Napi::Function::New(env, napiOnCreate);
            exports["onDestroy"] = Napi::Function::New(env, napiOnDestroy);
            exports["onShow"] = Napi::Function::New(env, napiOnShow);
            exports["onHide"] = Napi::Function::New(env, napiOnHide);
            exports["onBackPress"] = Napi::Function::New(env, napiOnBackPress);
        } break;
        case JS_PAGE_LIFECYCLE: {
            exports["onPageShow"] = Napi::Function::New(env, napiOnPageShow);
            exports["onPageHide"] = Napi::Function::New(env, napiOnPageHide);
        } break;
        case XCOMPONENT_REGISTER_LIFECYCLE_CALLBACK: {
        } break;
        case NATIVE_RENDER_API: {
            exports["nativeEngineInit"] = Napi::Function::New(env, napiNativeEngineInit);
            exports["nativeEngineStart"] = Napi::Function::New(env, napiNativeEngineStart);
        } break;
        case WORKER_INIT: {
#if SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_NAPI
            se::ScriptEngine::setEnv(env);
#endif
            gWorkerEnv = env;
            exports["workerInit"] = Napi::Function::New(env, napiWorkerInit);
            exports["setPostMessageFunction"] = Napi::Function::New(env, js_set_PostMessage2UIThreadCallback);
            exports["setPostSyncMessageFunction"] = Napi::Function::New(env, js_set_PostSyncMessage2UIThreadCallback);

        } break;
        case ENGINE_UTILS: {
            exports["resourceManagerInit"] = Napi::Function::New(env, napiResourceManagerInit);
            exports["writablePathInit"] = Napi::Function::New(env, napiWritablePathInit);
        } break;
        case EDITBOX_UTILS: {
            exports["onTextChange"] = Napi::Function::New(env, OpenHarmonyEditBox::napiOnTextChange);
            exports["onComplete"] = Napi::Function::New(env, OpenHarmonyEditBox::napiOnComplete);
        } break;
        case WEBVIEW_UTILS: {
            exports["shouldStartLoading"] = Napi::Function::New(env, OpenHarmonyWebView::napiShouldStartLoading);
            exports["finishLoading"] = Napi::Function::New(env, OpenHarmonyWebView::napiFinishLoading);
            exports["failLoading"] = Napi::Function::New(env, OpenHarmonyWebView::napiFailLoading);
            exports["jsCallback"] = Napi::Function::New(env, OpenHarmonyWebView::napiJsCallback);
        } break;
        case DISPLAY_UTILS: {
            exports["onDisplayChange"] = Napi::Function::New(env, napiOnDisplayChange);
        } break;
        case UV_ASYNC_SEND: {
            exports["send"] = Napi::Function::New(env, napiASend);
        } break;

        default:
            LOGE("unknown type");
    }

    return exports;
}


/* static */
Napi::Env NapiHelper::getWorkerEnv() {
    return gWorkerEnv;
}

/* static */
Napi::Object NapiHelper::init(Napi::Env env, Napi::Object exports) {
    exports["getContext"] = Napi::Function::New(env, getContext);
    bool ret = exportFunctions(exports);
    if (!ret) {
        LOGE("NapiHelper init failed");
    }
    return exports;
}

} // namespace cocos2d