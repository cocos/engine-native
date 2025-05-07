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
#include "scripting/js-bindings/jswrapper/SeApi.h"
#include <sstream>
#include <chrono>
#include "native_window/external_window.h"
#include "native_buffer/native_buffer.h"

namespace {
void sendMsgToWorker(const cocos2d::MessageType& type, void* component, void* window) {
    cocos2d::OpenHarmonyPlatform* platform = cocos2d::OpenHarmonyPlatform::getInstance();
    cocos2d::WorkerMessageData data{type, static_cast<void*>(component), window};
    platform->enqueue(data);
}

void onSurfaceCreatedCB(OH_NativeXComponent* component, void* window) {
    sendMsgToWorker(cocos2d::MessageType::WM_XCOMPONENT_SURFACE_CREATED, component, window);
}

void onSurfaceHideCB(OH_NativeXComponent* component, void* window) {
    int32_t ret;
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    ret = OH_NativeXComponent_GetXComponentId(component, idStr, &idSize);
    if(ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        return;
    }
    sendMsgToWorker(cocos2d::MessageType::WM_XCOMPONENT_SURFACE_HIDE, component, window);
}

void onSurfaceShowCB(OH_NativeXComponent* component, void* window) {
    int32_t ret;
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    ret = OH_NativeXComponent_GetXComponentId(component, idStr, &idSize);
    if(ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        return;
    }
    sendMsgToWorker(cocos2d::MessageType::WM_XCOMPONENT_SURFACE_SHOW, component, window);
}

int ohKeyCodeToCocosKeyCode(OH_NativeXComponent_KeyCode ohKeyCode){
    static const int keyZeroInCocos = 48;
    static const int keyF1InCocos = 112;
    static const int keyAInCocos = 65;
    static std::unordered_map<OH_NativeXComponent_KeyCode, cocos2d::KeyCode> keyCodeMap = {
        {KEY_ESCAPE, cocos2d::KeyCode::ESCAPE},
        {KEY_GRAVE, cocos2d::KeyCode::BACKQUOTE},
        {KEY_MINUS, cocos2d::KeyCode::MINUS},
        {KEY_EQUALS, cocos2d::KeyCode::EQUAL},
        {KEY_DEL, cocos2d::KeyCode::BACKSPACE},
        {KEY_TAB, cocos2d::KeyCode::TAB},
        {KEY_LEFT_BRACKET, cocos2d::KeyCode::BRACKET_LEFT},
        {KEY_RIGHT_BRACKET, cocos2d::KeyCode::BRACKET_RIGHT},
        {KEY_BACKSLASH, cocos2d::KeyCode::BACKSLASH},
        {KEY_CAPS_LOCK, cocos2d::KeyCode::CAPS_LOCK},
        {KEY_SEMICOLON, cocos2d::KeyCode::SEMICOLON},
        {KEY_APOSTROPHE, cocos2d::KeyCode::QUOTE},
        {KEY_ENTER, cocos2d::KeyCode::ENTER},
        {KEY_SHIFT_LEFT, cocos2d::KeyCode::SHIFT_LEFT},
        {KEY_COMMA, cocos2d::KeyCode::COMMA},
        {KEY_PERIOD, cocos2d::KeyCode::PERIOD},
        {KEY_SLASH, cocos2d::KeyCode::SLASH},
        {KEY_SHIFT_RIGHT, cocos2d::KeyCode::SHIFT_RIGHT},
        {KEY_CTRL_LEFT, cocos2d::KeyCode::CONTROL_LEFT},
        {KEY_ALT_LEFT, cocos2d::KeyCode::ALT_LEFT},
        {KEY_SPACE, cocos2d::KeyCode::SPACE},
        {KEY_ALT_RIGHT, cocos2d::KeyCode::ALT_RIGHT},
        {KEY_CTRL_RIGHT, cocos2d::KeyCode::CONTROL_RIGHT},
        {KEY_DPAD_LEFT, cocos2d::KeyCode::ARROW_LEFT},
        {KEY_DPAD_RIGHT, cocos2d::KeyCode::ARROW_RIGHT},
        {KEY_DPAD_DOWN, cocos2d::KeyCode::ARROW_DOWN},
        {KEY_DPAD_UP, cocos2d::KeyCode::ARROW_UP},
        {KEY_INSERT, cocos2d::KeyCode::INSERT},
    };
    if(keyCodeMap.find(ohKeyCode) != keyCodeMap.end()){
        return int(keyCodeMap[ohKeyCode]);
    }
    if(ohKeyCode >= KEY_0 && ohKeyCode <= KEY_9){
        return keyZeroInCocos + ohKeyCode - KEY_0;
    }
    if(ohKeyCode >= KEY_A && ohKeyCode <= KEY_Z){
        return keyAInCocos + ohKeyCode - KEY_A;
    }  
    if(ohKeyCode >= KEY_F1 && ohKeyCode <= KEY_F12){
        return keyF1InCocos + ohKeyCode - KEY_F1;
    }  
    return ohKeyCode;
}

void dispatchKeyEventCB(OH_NativeXComponent* component, void* window) {
    OH_NativeXComponent_KeyEvent* keyEvent;
    if (OH_NativeXComponent_GetKeyEvent(component, &keyEvent) >= 0) {
        static const int keyCodeUnknownInOH = -1;
        static const int keyActionUnknownInOH = -1;
        OH_NativeXComponent_KeyAction action;
        OH_NativeXComponent_GetKeyEventAction(keyEvent, &action);
        OH_NativeXComponent_KeyCode code;
        OH_NativeXComponent_GetKeyEventCode(keyEvent, &code);
        if (code == keyCodeUnknownInOH || action == keyActionUnknownInOH) {
            LOGD("unknown code and action don't callback");
            return;
        }
        cocos2d::KeyboardEvent* ev = new cocos2d::KeyboardEvent;
        ev->action = 0 == action ? cocos2d::KeyboardEvent::Action::PRESS : cocos2d::KeyboardEvent::Action::RELEASE;
        ev->key = ohKeyCodeToCocosKeyCode(code);
        sendMsgToWorker(cocos2d::MessageType::WM_XCOMPONENT_KEY_EVENT, reinterpret_cast<void*>(ev), window);
    } else {
        LOGD("OpenHarmonyPlatform::getKeyEventError");
    }
}

void dispatchMouseEventCB(OH_NativeXComponent* component, void* window) {
    OH_NativeXComponent_MouseEvent mouseEvent;
    int32_t ret = OH_NativeXComponent_GetMouseEvent(component, window, &mouseEvent);
    if (ret == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        if (mouseEvent.action == OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_NONE)
            return;
        cocos2d::MouseEvent* ev = new cocos2d::MouseEvent;
        ev->x = mouseEvent.x;
        ev->y = mouseEvent.y;
        switch (mouseEvent.action) {
            case OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_PRESS:
                ev->type = cocos2d::MouseEvent::Type::DOWN;
                break;
            case OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_RELEASE:
                ev->type = cocos2d::MouseEvent::Type::UP;
                break;
            case OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_MOVE:
                ev->type = cocos2d::MouseEvent::Type::MOVE;
                break;          
            default:
                ev->type = cocos2d::MouseEvent::Type::UNKNOWN;
                break;
        }
        switch (mouseEvent.button) {
            case OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_LEFT_BUTTON:
                ev->button = 0;
                break;
            case OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_RIGHT_BUTTON:
                ev->button = 2;
                break;
            case OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_MIDDLE_BUTTON:
                ev->button = 1;
                break;
            case OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_BACK_BUTTON:
                ev->button = 3;
                break;
            case OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_FORWARD_BUTTON:
                ev->button = 4;
                break;
            case OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_NONE_BUTTON:
                ev->button = -1;
                break;
        }
        if(mouseEvent.action == 1 && mouseEvent.button == 1) {
            cocos2d::OpenHarmonyPlatform::getInstance()->isMouseLeftActive = true;
        }
        if(mouseEvent.action == 2 && mouseEvent.button == 1) {
            cocos2d::OpenHarmonyPlatform::getInstance()->isMouseLeftActive = false;
        }
        sendMsgToWorker(cocos2d::MessageType::WM_XCOMPONENT_MOUSE_EVENT, reinterpret_cast<void*>(ev), window);
    } else {
        LOGD("OpenHarmonyPlatform::getMouseEventError");
    }
}

void dispatchHoverEventCB(OH_NativeXComponent* component, bool isHover) {
    // OpenharmonyPlatform::DispatchHoverEventCB
}


cocos2d::TouchEvent::Type touchTypeTransform(OH_NativeXComponent_TouchEventType touchType) {
    if (touchType == OH_NATIVEXCOMPONENT_DOWN) {
        return cocos2d::TouchEvent::Type::BEGAN;
    } else if (touchType == OH_NATIVEXCOMPONENT_MOVE) {
        return cocos2d::TouchEvent::Type::MOVED;
    } else if (touchType == OH_NATIVEXCOMPONENT_UP) {
        return cocos2d::TouchEvent::Type::ENDED;
    } else if (touchType == OH_NATIVEXCOMPONENT_CANCEL) {
        return cocos2d::TouchEvent::Type::CANCELLED;
    }
    return cocos2d::TouchEvent::Type::UNKNOWN;
}

void dispatchTouchEventCB(OH_NativeXComponent* component, void* window) {
    OH_NativeXComponent_TouchEvent touchEvent;
    int32_t ret = OH_NativeXComponent_GetTouchEvent(component, window, &touchEvent);
    if (ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        return;
    }
    cocos2d::TouchEvent* ev = new cocos2d::TouchEvent;
    ev->type = touchTypeTransform(touchEvent.type);
    for(int i = 0; i < touchEvent.numPoints; ++i) {
        cocos2d::TouchInfo touchInfo;
        touchInfo.index = touchEvent.touchPoints[i].id;
        touchInfo.x = touchEvent.touchPoints[i].x;
        touchInfo.y = touchEvent.touchPoints[i].y;
        ev->touches.push_back(touchInfo);
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
    OH_NativeXComponent_RegisterSurfaceHideCallback(_component, onSurfaceHideCB);
    OH_NativeXComponent_RegisterSurfaceShowCallback(_component, onSurfaceShowCB);
    // register KeyEvent                                     
    OH_NativeXComponent_RegisterKeyEventCallback(_component, dispatchKeyEventCB);
    // register mouseEvent
    _mouseCallback.DispatchMouseEvent = dispatchMouseEventCB;
    _mouseCallback.DispatchHoverEvent = dispatchHoverEventCB;
    OH_NativeXComponent_RegisterMouseEventCallback(_component, &_mouseCallback);
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
            } else if (msgData.type == MessageType::WM_XCOMPONENT_KEY_EVENT) {
                KeyboardEvent* ev = reinterpret_cast<KeyboardEvent*>(msgData.data);
                EventDispatcher::dispatchKeyboardEvent(*ev);
                delete ev;
                ev = nullptr;
            } else if (msgData.type == MessageType::WM_XCOMPONENT_MOUSE_EVENT || msgData.type == MessageType::WM_XCOMPONENT_MOUSE_WHEEL_EVENT ) {
                MouseEvent* ev = reinterpret_cast<MouseEvent*>(msgData.data);
                EventDispatcher::dispatchMouseEvent(*ev);
                delete ev;
                ev = nullptr;
            } else if (msgData.type == MessageType::WM_XCOMPONENT_SURFACE_CHANGED) {
                OH_NativeXComponent* nativexcomponet = reinterpret_cast<OH_NativeXComponent*>(msgData.data);
                CC_ASSERT(nativexcomponet != nullptr);        
                platform->onSurfaceChanged(nativexcomponet, msgData.window);
            } else if (msgData.type == MessageType::WM_XCOMPONENT_SURFACE_SHOW) {
                OH_NativeXComponent* nativexcomponet = reinterpret_cast<OH_NativeXComponent*>(msgData.data);
                CC_ASSERT(nativexcomponet != nullptr);        
                platform->onSurfaceShow(msgData.window);
            } else if (msgData.type == MessageType::WM_XCOMPONENT_SURFACE_HIDE) {
                OH_NativeXComponent* nativexcomponet = reinterpret_cast<OH_NativeXComponent*>(msgData.data);
                CC_ASSERT(nativexcomponet != nullptr);        
                platform->onSurfaceHide();
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
    if (_timerInited) {
        uv_timer_start(&_timerHandle, &OpenHarmonyPlatform::timerCb, 0, 1);
    }
}

void OpenHarmonyPlatform::onHideNative() {
    LOGD("OpenHarmonyPlatform::onHideNative");
    EventDispatcher::dispatchOnPauseEvent();
    if (_timerInited) {
        uv_timer_stop(&_timerHandle);
    }
}

void OpenHarmonyPlatform::onDestroyNative() {
    LOGD("OpenHarmonyPlatform::onDestroyNative");
     if (_timerInited) {
        uv_timer_stop(&_timerHandle);
    }
}

void OpenHarmonyPlatform::timerCb(uv_timer_t* handle) {
    if(OpenHarmonyPlatform::getInstance()->eglCore_ != nullptr){
        OpenHarmonyPlatform::getInstance()->tick();
        OpenHarmonyPlatform::getInstance()->eglCore_->Update();
    }
}

void OpenHarmonyPlatform::restartJSVM() {
    g_started = false;
}

void OpenHarmonyPlatform::workerInit(uv_loop_t* loop) {
    _workerLoop = loop;
    if (_workerLoop) {
        uv_timer_init(_workerLoop, &_timerHandle);
        _timerInited = true;
        uv_async_init(_workerLoop, &_messageSignal, reinterpret_cast<uv_async_cb>(OpenHarmonyPlatform::onMessageCallback));
        if (!_messageQueue.empty()) {
            triggerMessageSignal(); // trigger the signal to handle the pending message
        }
    }
}

void OpenHarmonyPlatform::requestVSync() {
}

int32_t OpenHarmonyPlatform::loop() {
    return 0;
}

void OpenHarmonyPlatform::onSurfaceCreated(OH_NativeXComponent* component, void* window) {
    eglCore_ = new EGLCore();
    int32_t ret=OH_NativeXComponent_GetXComponentSize(component, window, &width_, &height_);
    if (ret == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        int32_t code = SET_USAGE;
        OHNativeWindow *nativeWindow = static_cast<OHNativeWindow *>(window); 
        int32_t ret = OH_NativeWindow_NativeWindowHandleOpt(nativeWindow, code, NATIVEBUFFER_USAGE_MEM_DMA);
        eglCore_->GLContextInit(window, width_, height_);
        se::ScriptEngine *scriptEngine = se::ScriptEngine::getInstance();
        scriptEngine->addRegisterCallback(setCanvasCallback);
        if(g_app!=nullptr){
            OpenHarmonyPlatform* platform = OpenHarmonyPlatform::getInstance();
            g_app->updateViewSize(static_cast<float>(platform->width_), static_cast<float>(platform->height_));
        }
        LOGD("egl init finished.");
    }
    _lastTickInNanoSeconds = std::chrono::steady_clock::now();
}

void OpenHarmonyPlatform::onSurfaceChanged(OH_NativeXComponent* component, void* window) {
    int32_t ret = OH_NativeXComponent_GetXComponentSize(component, window, &width_, &height_);
    // nativeOnSizeChanged is firstly called before Application initiating.
    if (g_app != nullptr) {
        g_app->updateViewSize(width_, height_);
    }
}

void OpenHarmonyPlatform::onSurfaceDestroyed(OH_NativeXComponent* component, void* window) {
    delete eglCore_;
    eglCore_ = nullptr;
}

void OpenHarmonyPlatform::onSurfaceHide() {
    eglCore_->destroySurface();
}

void OpenHarmonyPlatform::onSurfaceShow(void* window) {
    eglCore_->createSurface(window);
}

void OpenHarmonyPlatform::dispatchMouseWheelCB(std::string eventType, float offsetY) {
    if(isMouseLeftActive) {
        return;
    }
    if(eventType == "actionUpdate") {
        float moveScrollY = offsetY - scrollDistance;
        scrollDistance = offsetY;
        cocos2d::MouseEvent* ev = new cocos2d::MouseEvent;
        ev->type = MouseEvent::Type::WHEEL;
        ev->x = 0;
        ev->y = moveScrollY;
        sendMsgToWorker(MessageType::WM_XCOMPONENT_MOUSE_WHEEL_EVENT, reinterpret_cast<void*>(ev), nullptr);
    } else {
        scrollDistance = 0;
    }
}

void OpenHarmonyPlatform::setPreferedFramePersecond(int fps) {
    if (fps == 0) {
        return;
    }
    _prefererredNanosecondsPerFrame = static_cast<long>(1.0 / fps * NANOSECONDS_PER_SECOND); // NOLINT(google-runtime-int)
}

void OpenHarmonyPlatform::tick() {
    if(!g_started) {
        auto scheduler = Application::getInstance()->getScheduler();
        scheduler->removeAllFunctionsToBePerformedInCocosThread();
        scheduler->unscheduleAll();

        se::ScriptEngine::getInstance()->cleanup();
        cocos2d::PoolManager::getInstance()->getCurrentPool()->clear();

        //REFINE: Wait HttpClient, WebSocket, Audio thread to exit
        ccInvalidateStateCache();
          
        se::ScriptEngine* se = se::ScriptEngine::getInstance();
        se->addRegisterCallback(setCanvasCallback);

        EventDispatcher::init();

        if(!g_app->applicationDidFinishLaunching()) {
                return;
        }
        g_started = true;
    }

    static std::chrono::steady_clock::time_point now;
    static float dt = 0.f;
    now = std::chrono::steady_clock::now();
    static double dtNS = NANOSECONDS_60FPS;

    dtNS = static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(now - _lastTickInNanoSeconds).count());
    if(dtNS < static_cast<double>(_prefererredNanosecondsPerFrame)) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(
        _prefererredNanosecondsPerFrame - static_cast<int64_t>(dtNS)));
    }
    _lastTickInNanoSeconds = std::chrono::steady_clock::now();
    std::shared_ptr<Scheduler> scheduler = g_app->getScheduler();
    scheduler->update(dt);
    EventDispatcher::dispatchTickEvent(dt);
    PoolManager::getInstance()->getCurrentPool()->clear();
    dt = static_cast<float>(dtNS) / NANOSECONDS_PER_SECOND;
}

}; // namespace cc
