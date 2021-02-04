/****************************************************************************
Copyright (c) 2020 Xiamen Yaji Software Co., Ltd.

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
#include "platform/ohos/jni/JniCocosAbility.h"
#include "platform/Application.h"
#include "platform/android/View.h"
#include "platform/java/jni/JniHelper.h"
#include "platform/ohos/FileUtils-ohos.h"
#include "platform/ohos/jni/AbilityConsts.h"
#include <fcntl.h>
#include <hilog/log.h>
#include <jni.h>
#include <native_layer.h>
#include <native_layer_jni.h>
#include <netdb.h>
#include <platform/FileUtils.h>
#include <thread>
#include <unistd.h>
#include <vector>

#define LOGV(...) HILOG_INFO(LOG_APP, __VA_ARGS__)

extern "C" cc::Application *cocos_main(int, int) __attribute__((weak));

namespace cc {
CocosApp cocosApp;
}

using namespace cc::ohos;

namespace {
int messagePipe[2];
int pipeRead = 0;
int pipeWrite = 0;
cc::Application *game = nullptr;

void createGame(NativeLayer *window) {
    int width = NativeLayerHandle(window, NativeLayerOps::GET_WIDTH);
    int height = NativeLayerHandle(window, NativeLayerOps::GET_HEIGHT);
    game = cocos_main(width, height);
    game->init();
}

void writeCommand(int8_t cmd) {
    write(pipeWrite, &cmd, sizeof(cmd));
}

int readCommand(int8_t &cmd) {
    return read(pipeRead, &cmd, sizeof(cmd));
}

void handlePauseResume(int8_t cmd) {
    LOGV("activityState=%d", cmd);
    std::unique_lock<std::mutex> lk(cc::cocosApp.mutex);
    cc::cocosApp.activityState = cmd;
    lk.unlock();
    cc::cocosApp.cond.notify_all();
}

void preExecCmd(int8_t cmd) {
    switch (cmd) {
        case ABILITY_CMD_INIT_WINDOW: {
            LOGV("ABILITY_CMD_INIT_WINDOW");
            std::unique_lock<std::mutex> lk(cc::cocosApp.mutex);
            cc::cocosApp.window = cc::cocosApp.pendingWindow;
            lk.unlock();
            cc::cocosApp.cond.notify_all();
            cc::cocosApp.animating = true;

            if (!game) {
                createGame(cc::cocosApp.window);
            }
        } break;
        case ABILITY_CMD_TERM_WINDOW:
            LOGV("ABILITY_CMD_TERM_WINDOW");
            cc::cocosApp.animating = false;
            cc::cocosApp.cond.notify_all();
            break;
        case ABILITY_CMD_RESUME:
            LOGV("ABILITY_CMD_RESUME");
            handlePauseResume(cmd);
            break;
        case ABILITY_CMD_PAUSE:
            LOGV("ABILITY_CMD_PAUSE");
            handlePauseResume(cmd);
            break;
        case ABILITY_CMD_DESTROY:
            LOGV("ABILITY_CMD_DESTROY");
            cc::cocosApp.destroyRequested = true;
            break;
        default:
            break;
    }
}

void postExecCmd(int8_t cmd) {
    switch (cmd) {
        case ABILITY_CMD_TERM_WINDOW: {
            std::unique_lock<std::mutex> lk(cc::cocosApp.mutex);
            cc::cocosApp.window = nullptr;
            lk.unlock();
            cc::cocosApp.cond.notify_all();
        } break;
        default:
            break;
    }
}

void glThreadEntry() {
    std::unique_lock<std::mutex> lk(cc::cocosApp.mutex);
    cc::cocosApp.running = true;
    lk.unlock();
    cc::cocosApp.cond.notify_all();

    int8_t cmd = 0;
    while (1) {
        if (readCommand(cmd) > 0) {
            preExecCmd(cmd);
            cc::View::engineHandleCmd(cmd);
            postExecCmd(cmd);
        }

        if (!cc::cocosApp.animating) continue;

        if (game) {
            // Handle java events send by UI thread. Input events are handled here too.
            cc::JniHelper::callStaticVoidMethod("com.cocos.lib.CocosHelper",
                                                "flushTasksOnGameThread");
            game->tick();
        }

        if (cc::cocosApp.destroyRequested) break;
    }

    close(pipeRead);
    close(pipeWrite);

    delete game;
    game = nullptr;
}

void setWindow(NativeLayer *window) {
    std::unique_lock<std::mutex> lk(cc::cocosApp.mutex);
    if (cc::cocosApp.pendingWindow) {
        writeCommand(ABILITY_CMD_TERM_WINDOW);
    }
    cc::cocosApp.pendingWindow = window;
    if (window) {
        writeCommand(ABILITY_CMD_INIT_WINDOW);
    }
    while (cc::cocosApp.window != cc::cocosApp.pendingWindow) {
        cc::cocosApp.cond.wait(lk);
    }
}

void setActivityState(int8_t cmd) {
    std::unique_lock<std::mutex> lk(cc::cocosApp.mutex);
    writeCommand(cmd);
    while (cc::cocosApp.activityState != cmd) {
        cc::cocosApp.cond.wait(lk);
    }
}
} // namespace

extern "C" {

JNIEXPORT void JNICALL Java_com_cocos_lib_CocosAbilitySlice_onCreateNative(JNIEnv *env, jobject obj, jobject ability,
                                                                           jstring assetPath, jobject resourceManager, jint sdkVersion) {
    if (cc::cocosApp.running) {
        return;
    }

    jboolean isCopy = false;
    const char *assetPathStr = env->GetStringUTFChars(assetPath, &isCopy);

    cc::cocosApp.sdkVersion = sdkVersion;
    cc::JniHelper::init(env, ability);
    cc::cocosApp.resourceManager = InitNativeResourceManager(env, resourceManager);
    cc::FileUtilsOHOS::initResourceManager(cc::cocosApp.resourceManager, assetPathStr);

    if (isCopy) {
        env->ReleaseStringUTFChars(assetPath, assetPathStr);
        assetPathStr = nullptr;
    }

    if (pipe(messagePipe)) {
        LOGV("Can not create pipe: %s", strerror(errno));
    }
    pipeRead = messagePipe[0];
    pipeWrite = messagePipe[1];
    if (fcntl(pipeRead, F_SETFL, O_NONBLOCK) < 0) {
        LOGV("Can not make pipe read to non blocking mode.");
    }

    std::thread glThread(glThreadEntry);
    glThread.detach();

    std::unique_lock<std::mutex> lk(cc::cocosApp.mutex);
    while (!cc::cocosApp.running) {
        cc::cocosApp.cond.wait(lk);
    }
}

JNIEXPORT void JNICALL Java_com_cocos_lib_CocosAbilitySlice_onSurfaceCreatedNative(JNIEnv *env, jobject obj, jobject surface) {
    setWindow(GetNativeLayer(env, surface));
}
JNIEXPORT void JNICALL Java_com_cocos_lib_CocosAbilitySlice_onStartNative(JNIEnv *env, jobject obj) {
}

JNIEXPORT void JNICALL Java_com_cocos_lib_CocosAbilitySlice_onPauseNative(JNIEnv *env, jobject obj) {
    setActivityState(ABILITY_CMD_PAUSE);
}

JNIEXPORT void JNICALL Java_com_cocos_lib_CocosAbilitySlice_onResumeNative(JNIEnv *env, jobject obj) {
    setActivityState(ABILITY_CMD_RESUME);
}

JNIEXPORT void JNICALL Java_com_cocos_lib_CocosAbilitySlice_onStopNative(JNIEnv *env, jobject obj) {
}

JNIEXPORT void JNICALL Java_com_cocos_lib_CocosAbilitySlice_onLowMemoryNative(JNIEnv *env, jobject obj) {
    writeCommand(ABILITY_CMD_LOW_MEMORY);
}

JNIEXPORT void JNICALL Java_com_cocos_lib_CocosAbilitySlice_onWindowFocusChangedNative(JNIEnv *env, jobject obj, jboolean has_focus) {
}

JNIEXPORT void JNICALL Java_com_cocos_lib_CocosAbilitySlice_onSurfaceChangedNative(JNIEnv *env, jobject obj, jint width, jint height) {
}

JNIEXPORT void JNICALL Java_com_cocos_lib_CocosAbilitySlice_onSurfaceDestroyNative(JNIEnv *env, jobject obj) {
    setWindow(nullptr);
}
}
