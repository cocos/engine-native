/****************************************************************************
 Copyright (c) 2021-2023 Xiamen Yaji Software Co., Ltd.

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
#include "platform/openharmony/OpenHarmonyPlatform.h"
#include "platform/CCPlatformDefine.h"

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <napi/native_api.h>

#include "cocos2d.h"

#include "cocos/scripting/js-bindings/manual/jsb_module_register.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_global.h"
#include "cocos/scripting/js-bindings/event/EventDispatcher.h"
#include "cocos/scripting/js-bindings/manual/jsb_classtype.hpp"
#include "base/CCScheduler.h"
#include "cocos/scripting/js-bindings/event/EventDispatcher.h"

#include <sstream>
#include <chrono>

namespace {
void sendMsgToWorker(const cocos2d::MessageType& type, void* component, void* window) {
    cocos2d::OpenHarmonyPlatform* platform = cocos2d::OpenHarmonyPlatform::getInstance();
    cocos2d::WorkerMessageData data{type, static_cast<void*>(component), window};
    platform->enqueue(data);
}

void onSurfaceCreatedCB(OH_NativeXComponent* component, void* window) {
    sendMsgToWorker(cocos2d::MessageType::WM_XCOMPONENT_SURFACE_CREATED, component, window);
}

void dispatchTouchEventCB(OH_NativeXComponent* component, void* window) {
    OH_NativeXComponent_TouchEvent touchEvent;
    int32_t ret = OH_NativeXComponent_GetTouchEvent(component, window, &touchEvent);
    if (ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        return;
    }
    cocos2d::TouchEvent* ev = new cocos2d::TouchEvent;
    if (touchEvent.type == OH_NATIVEXCOMPONENT_DOWN) {
        ev->type = cocos2d::TouchEvent::Type::BEGAN;
    } else if (touchEvent.type == OH_NATIVEXCOMPONENT_MOVE) {
        ev->type = cocos2d::TouchEvent::Type::MOVED;
    } else if (touchEvent.type == OH_NATIVEXCOMPONENT_UP) {
        ev->type = cocos2d::TouchEvent::Type::ENDED;
    } else if (touchEvent.type == OH_NATIVEXCOMPONENT_CANCEL) {
        ev->type = cocos2d::TouchEvent::Type::CANCELLED;
    }
    for(int i = 0; i < touchEvent.numPoints; ++i) {
        cocos2d::TouchInfo touchInfo;
        touchInfo.index = touchEvent.touchPoints[i].id;
        touchInfo.x = touchEvent.touchPoints[i].x;
        touchInfo.y = touchEvent.touchPoints[i].y;
        if (touchEvent.id == touchInfo.index) {
            ev->touches.push_back(touchInfo);
        }
    }
    sendMsgToWorker(cocos2d::MessageType::WM_XCOMPONENT_TOUCH_EVENT, reinterpret_cast<void*>(ev), window);
}

void onSurfaceChangedCB(OH_NativeXComponent* component, void* window) {
    sendMsgToWorker(cocos2d::MessageType::WM_XCOMPONENT_SURFACE_CHANGED, component, window);
}

void onSurfaceDestroyedCB(OH_NativeXComponent* component, void* window) {
    sendMsgToWorker(cocos2d::MessageType::WM_XCOMPONENT_SURFACE_DESTROY, component, window);
}

bool setCanvasCallback(se::Object* global) {
    cocos2d::OpenHarmonyPlatform* platform = cocos2d::OpenHarmonyPlatform::getInstance();
    uint32_t innerWidth = (uint32_t)platform->width_;
    uint32_t innerHeight = (uint32_t)platform->height_;
    global->setProperty("innerWidth", se::Value(innerWidth));
    global->setProperty("innerHeight", se::Value(innerHeight));
    LOGD("exit setCanvasCallback setCanvasCallback");
    return true;
}

} // namespace

namespace cocos2d {

OpenHarmonyPlatform::OpenHarmonyPlatform() {
    _callback.OnSurfaceCreated   = onSurfaceCreatedCB;
    _callback.OnSurfaceChanged   = onSurfaceChangedCB;
    _callback.OnSurfaceDestroyed = onSurfaceDestroyedCB;
    _callback.DispatchTouchEvent = dispatchTouchEventCB;
}

int32_t OpenHarmonyPlatform::init() {
    return 0;
}

OpenHarmonyPlatform* OpenHarmonyPlatform::getInstance() {
    static OpenHarmonyPlatform platform;
    return &platform;
}

int32_t OpenHarmonyPlatform::run(int argc, const char** argv) {
    LOGD("begin openharmonyplatform run");

    int width = static_cast<int>(width_);
    int height = static_cast<int>(height_);
    g_app = new AppDelegate(width, height);
    g_app->applicationDidFinishLaunching();
    EventDispatcher::init();
    g_started = true;
    LOGD("end openharmonyplatform run");
    return 0;
}

void OpenHarmonyPlatform::setNativeXComponent(OH_NativeXComponent* component) {
    _component = component;
    OH_NativeXComponent_RegisterCallback(_component, &_callback);
}

void OpenHarmonyPlatform::enqueue(const WorkerMessageData& msg) {
    _messageQueue.enqueue(msg);
    triggerMessageSignal();
}

void OpenHarmonyPlatform::triggerMessageSignal() {
    if(_workerLoop != nullptr) {
        // It is possible that when the message is sent, the worker thread has not yet started.
        uv_async_send(&_messageSignal);
    }
}

bool OpenHarmonyPlatform::dequeue(WorkerMessageData* msg) {
    return _messageQueue.dequeue(msg);
}

// static
void OpenHarmonyPlatform::onMessageCallback(const uv_async_t* /* req */) {
    void*             window          = nullptr;
    WorkerMessageData msgData;
    OpenHarmonyPlatform* platform = OpenHarmonyPlatform::getInstance();

    while (true) {
        //loop until all msg dispatch
        if (!platform->dequeue(reinterpret_cast<WorkerMessageData*>(&msgData))) {
            // Queue has no data
            break;
        }

        if ((msgData.type >= MessageType::WM_XCOMPONENT_SURFACE_CREATED) && (msgData.type <= MessageType::WM_XCOMPONENT_SURFACE_DESTROY)) {
            if (msgData.type == MessageType::WM_XCOMPONENT_TOUCH_EVENT) {
                TouchEvent* ev = reinterpret_cast<TouchEvent*>(msgData.data);
                EventDispatcher::dispatchTouchEvent(*ev);
                delete ev;
                ev = nullptr;
            } else if (msgData.type == MessageType::WM_XCOMPONENT_SURFACE_CREATED) {
                OH_NativeXComponent* nativexcomponet = reinterpret_cast<OH_NativeXComponent*>(msgData.data);
                CC_ASSERT(nativexcomponet != nullptr);
                platform->onSurfaceCreated(nativexcomponet, msgData.window);
            } else if (msgData.type == MessageType::WM_XCOMPONENT_SURFACE_CHANGED) {
                OH_NativeXComponent* nativexcomponet = reinterpret_cast<OH_NativeXComponent*>(msgData.data);
                CC_ASSERT(nativexcomponet != nullptr);        
                platform->onSurfaceChanged(nativexcomponet, msgData.window);
            } else if (msgData.type == MessageType::WM_XCOMPONENT_SURFACE_DESTROY) {
                OH_NativeXComponent* nativexcomponet = reinterpret_cast<OH_NativeXComponent*>(msgData.data);
                CC_ASSERT(nativexcomponet != nullptr);            
                platform->onSurfaceDestroyed(nativexcomponet, msgData.window);
            } else {
                CC_ASSERT(false);
            }
            continue;
        }

        if (msgData.type == MessageType::WM_APP_SHOW) {
            platform->onShowNative();
        } else if (msgData.type == MessageType::WM_APP_HIDE) {
            platform->onHideNative();
        } else if (msgData.type == MessageType::WM_APP_DESTROY) {
            platform->onDestroyNative();
        }
    }
}

void OpenHarmonyPlatform::onCreateNative(napi_env env, uv_loop_t* loop) {
    LOGD("OpenHarmonyPlatform::onCreateNative");
}

void OpenHarmonyPlatform::onShowNative() {
    LOGD("OpenHarmonyPlatform::onShowNative");
    EventDispatcher::dispatchOnResumeEvent();
}

void OpenHarmonyPlatform::onHideNative() {
    LOGD("OpenHarmonyPlatform::onHideNative");
    EventDispatcher::dispatchOnPauseEvent();
}

void OpenHarmonyPlatform::onDestroyNative() {
    LOGD("OpenHarmonyPlatform::onDestroyNative");
}

void OpenHarmonyPlatform::timerCb(uv_timer_t* handle) {
    if(OpenHarmonyPlatform::getInstance()->eglCore_ != nullptr){
        OpenHarmonyPlatform::getInstance()->tick();
        OpenHarmonyPlatform::getInstance()->eglCore_->Update();
    }
}

void OpenHarmonyPlatform::workerInit(napi_env env, uv_loop_t* loop) {
    _workerLoop = loop;
    if (_workerLoop) {
        uv_async_init(_workerLoop, &_messageSignal, reinterpret_cast<uv_async_cb>(OpenHarmonyPlatform::onMessageCallback));
        if (!_messageQueue.empty()) {
            triggerMessageSignal(); // trigger the signal to handle the pending message
        }
    }
}

void OpenHarmonyPlatform::requestVSync() {
    // OH_NativeVSync_RequestFrame(OpenHarmonyPlatform::getInstance()->_nativeVSync, OnVSync, nullptr);
     if (_workerLoop) {
        // Todo: Starting the timer in this way is inaccurate and will be fixed later.
        uv_timer_init(_workerLoop, &_timerHandle);
        // The tick function needs to be called as quickly as possible because it is controlling the frame rate inside the engine.
        uv_timer_start(&_timerHandle, &OpenHarmonyPlatform::timerCb, 0, 1);
     }
}

int32_t OpenHarmonyPlatform::loop() {
    return 0;
}

void OpenHarmonyPlatform::onSurfaceCreated(OH_NativeXComponent* component, void* window) {
    eglCore_ = new EGLCore();
    int32_t ret=OH_NativeXComponent_GetXComponentSize(component, window, &width_, &height_);
    if (ret == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        eglCore_->GLContextInit(window, width_, height_);
        se::ScriptEngine *scriptEngine = se::ScriptEngine::getInstance();
        scriptEngine->addRegisterCallback(setCanvasCallback);
        if(g_app!=nullptr){
            OpenHarmonyPlatform* platform = OpenHarmonyPlatform::getInstance();
            g_app->updateViewSize(static_cast<float>(platform->width_), static_cast<float>(platform->height_));
        }
        LOGD("egl init finished.");
    }
}

void OpenHarmonyPlatform::onSurfaceChanged(OH_NativeXComponent* component, void* window) {
    int32_t ret = OH_NativeXComponent_GetXComponentSize(component, window, &width_, &height_);
    // nativeOnSizeChanged is firstly called before Application initiating.
    if (g_app != nullptr) {
        g_app->updateViewSize(width_, height_);
    }
}

void OpenHarmonyPlatform::onSurfaceDestroyed(OH_NativeXComponent* component, void* window) {
}

void OpenHarmonyPlatform::tick() {
        static std::chrono::steady_clock::time_point prevTime;
        static std::chrono::steady_clock::time_point now;
        static float dt = 0.f;
        static float dtSum = 0.f;
        static uint32_t jsbInvocationTotalCount = 0;
        static uint32_t jsbInvocationTotalFrames = 0;
        std::shared_ptr<Scheduler> scheduler = g_app->getScheduler();
        scheduler->update(dt);
        EventDispatcher::dispatchTickEvent(dt);
        PoolManager::getInstance()->getCurrentPool()->clear();
        now = std::chrono::steady_clock::now();
        dt = std::chrono::duration_cast<std::chrono::microseconds>(now - prevTime).count() / 1000000.f;
        prevTime = std::chrono::steady_clock::now();
}
}; // namespace cc
