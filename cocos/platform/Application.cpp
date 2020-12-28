
#include "cocos/platform/Application.h"
#include "cocos/bindings/jswrapper/SeApi.h"

#if USE_AUDIO
#include "cocos/audio/include/AudioEngine.h"
#endif

#if USE_SOCKET
#include "cocos/network/WebSocket.h"
#endif

#include "cocos/network/HttpClient.h"

namespace cc {
void Application::restartVM() {

    cc::EventDispatcher::dispatchRestartVM();

    auto scriptEngine = se::ScriptEngine::getInstance();
    
    cc::PoolManager::getInstance()->getCurrentPool()->clear();
#if USE_AUDIO
    cc::AudioEngine::stopAll();
#endif
#if USE_SOCKET
    cc::network::WebSocket::closeAllConnections();
#endif
    cc::network::HttpClient::destroyInstance();
    
    _scheduler->removeAllFunctionsToBePerformedInCocosThread();
    _scheduler->unscheduleAll();

    scriptEngine->cleanup();
    cc::EventDispatcher::destroy();
    
    // start
    
    cc::EventDispatcher::init();
    init();
}


void Application::tick() {
    
    if(_needRestart)
    {
        restartVM();
        _needRestart = false;
    }
    
    static std::chrono::steady_clock::time_point prevTime;
    static std::chrono::steady_clock::time_point now;
    static float dt = 0.f;
    static double dtNS = NANOSECONDS_60FPS;
    
    ++_totalFrames;

    // iOS/macOS use its own fps limitation algorithm.
#if (CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_WINDOWS)
    if (dtNS < _prefererredNanosecondsPerFrame) {
        std::this_thread::sleep_for(
                std::chrono::nanoseconds(_prefererredNanosecondsPerFrame - dtNS));
        dtNS = _prefererredNanosecondsPerFrame;
    }
#endif

    prevTime = std::chrono::steady_clock::now();

    _scheduler->update(dt);
    cc::EventDispatcher::dispatchTickEvent(dt);

    PoolManager::getInstance()->getCurrentPool()->clear();

    now = std::chrono::steady_clock::now();
    dtNS = dtNS * 0.1 + 0.9 * std::chrono::duration_cast<std::chrono::nanoseconds>(now - prevTime).count();
    dt = (float)dtNS / NANOSECONDS_PER_SECOND;
}

}
