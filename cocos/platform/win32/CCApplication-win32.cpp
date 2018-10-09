/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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
#include "platform/CCApplication.h"
#include "platform/CCStdC.h" // need it to include Windows.h
#include <algorithm>
#include <shellapi.h>
#include <MMSystem.h>
#include "platform/CCFileUtils.h"
#include "platform/desktop/CCGLView-desktop.h"
#include "renderer/gfx/DeviceGraphics.h"
#include "scripting/js-bindings/jswrapper/SeApi.h"
#include "scripting/js-bindings/event/EventDispatcher.h"
#include "base/CCScheduler.h"
#include "base/CCAutoreleasePool.h"
#include "base/CCGLUtils.h"
#include "audio/include/AudioEngine.h"

#define CAST_VIEW(view)    ((GLView*)view)

namespace
{
    /**
    @brief  This function changes the PVRFrame show/hide setting in register.
    @param  bEnable If true show the PVRFrame window, otherwise hide.
    */
    void PVRFrameEnableControlWindow(bool bEnable)
    {
        HKEY hKey = 0;

        // Open PVRFrame control key, if not exist create it.
        if(ERROR_SUCCESS != RegCreateKeyExW(HKEY_CURRENT_USER,
            L"Software\\Imagination Technologies\\PVRVFRame\\STARTUP\\",
            0,
            0,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            0,
            &hKey,
            nullptr))
        {
            return;
        }

        const WCHAR* wszValue = L"hide_gui";
        const WCHAR* wszNewData = (bEnable) ? L"NO" : L"YES";
        WCHAR wszOldData[256] = {0};
        DWORD   dwSize = sizeof(wszOldData);
        LSTATUS status = RegQueryValueExW(hKey, wszValue, 0, nullptr, (LPBYTE)wszOldData, &dwSize);
        if (ERROR_FILE_NOT_FOUND == status              // the key not exist
            || (ERROR_SUCCESS == status                 // or the hide_gui value is exist
            && 0 != wcscmp(wszNewData, wszOldData)))    // but new data and old data not equal
        {
            dwSize = sizeof(WCHAR) * (wcslen(wszNewData) + 1);
            RegSetValueEx(hKey, wszValue, 0, REG_SZ, (const BYTE *)wszNewData, dwSize);
        }

        RegCloseKey(hKey);
    }

    int g_width = 0;
    int g_height = 0;
    bool setCanvasCallback(se::Object* global)
    {
        se::ScriptEngine* se = se::ScriptEngine::getInstance();
        uint8_t devicePixelRatio = cocos2d::Application::getInstance()->getDevicePixelRatio();
        char commandBuf[200] = {0};
        sprintf(commandBuf, "window.innerWidth = %d; window.innerHeight = %d;",
          (int)(g_width / devicePixelRatio),
          (int)(g_height / devicePixelRatio));
        se->evalString(commandBuf);
        cocos2d::ccViewport(0, 0, g_width, g_height);
        glDepthMask(GL_TRUE);
        return true;
    }
}

NS_CC_BEGIN

std::shared_ptr<ApplicationImpl> ApplicationImpl::_instance = nullptr;

ApplicationImpl::ApplicationImpl(const std::string& name, int width, int height)
{
    _scheduler = new Scheduler();

    createView(name, width, height);
    
    _renderTexture = new RenderTexture(width, height);
    _scheduler = new Scheduler();
    
    EventDispatcher::init();
    se::ScriptEngine::getInstance();
}

ApplicationImpl::~ApplicationImpl()
{
    EventDispatcher::destroy();
    se::ScriptEngine::destroyInstance();

    //close audio device
    cocos2d::experimental::AudioEngine::end();

    delete _scheduler;
    _scheduler = nullptr;
    
    delete CAST_VIEW(_view);
    _view = nullptr;
    
    delete _renderTexture;
    _renderTexture = nullptr;
}

void ApplicationImpl::start()
{
    if (!_view)
        return;

    PVRFrameEnableControlWindow(false);

    ///////////////////////////////////////////////////////////////////////////
    /////////////// changing timer resolution
    ///////////////////////////////////////////////////////////////////////////
    UINT TARGET_RESOLUTION = 1; // 1 millisecond target resolution
    TIMECAPS tc;
    UINT wTimerRes = 0;
    if (TIMERR_NOERROR == timeGetDevCaps(&tc, sizeof(TIMECAPS)))
    {
        wTimerRes = std::min(std::max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);
        timeBeginPeriod(wTimerRes);
    }
    
    float dt = 0.f;
    const DWORD _16ms = 16;

    // Main message loop:
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nLast;
    LARGE_INTEGER nNow;

    LONGLONG actualInterval = 0LL; // actual frame internal
    LONGLONG desiredInterval = 0LL; // desired frame internal, 1 / fps
    LONG waitMS = 0L;

    QueryPerformanceCounter(&nLast);
    QueryPerformanceFrequency(&nFreq);
    se::ScriptEngine* se = se::ScriptEngine::getInstance();
    while (!CAST_VIEW(_view)->windowShouldClose())
    {       
        desiredInterval = (LONGLONG)(1.0 / _fps * nFreq.QuadPart);
        if (!_isStarted)
        {
            auto scheduler = Application::getInstance()->getScheduler();
            scheduler->removeAllFunctionsToBePerformedInCocosThread();
            scheduler->unscheduleAll();

            se::ScriptEngine::getInstance()->cleanup();
            cocos2d::PoolManager::getInstance()->getCurrentPool()->clear();
            cocos2d::EventDispatcher::init();

            ccInvalidateStateCache();
            se->addRegisterCallback(setCanvasCallback);

            if(!applicationDidFinishLaunching())
                return;

            _isStarted = true;
        }

        // should be invoked at the begin of rendering a frame
        if (_isDownsampleEnabled)
            _renderTexture->prepare();
        CAST_VIEW(_view)->pollEvents();
        if(_isStarted)
        {
            QueryPerformanceCounter(&nNow);
            actualInterval = nNow.QuadPart - nLast.QuadPart;
            if (actualInterval >= desiredInterval)
            {
                nLast.QuadPart = nNow.QuadPart;
                dt = (float)actualInterval / nFreq.QuadPart;
                _scheduler->update(dt);

                EventDispatcher::dispatchTickEvent(dt);

                if (_isDownsampleEnabled)
                    _renderTexture->draw();

                CAST_VIEW(_view)->swapBuffers();
            }
            else
            {
                // The precision of timer on Windows is set to highest (1ms) by 'timeBeginPeriod' from above code,
                // but it's still not precise enough. For example, if the precision of timer is 1ms,
                // Sleep(3) may make a sleep of 2ms or 4ms. Therefore, we subtract 1ms here to make Sleep time shorter.
                // If 'waitMS' is equal or less than 1ms, don't sleep and run into next loop to
                // boost CPU to next frame accurately.
                waitMS = (desiredInterval - actualInterval) * 1000LL / nFreq.QuadPart - 1L;
                if (waitMS > 1L)
                    Sleep(waitMS);
            } 
        }
        else
        {
            Sleep(_16ms);
        }

    }

    if (wTimerRes != 0)
        timeEndPeriod(wTimerRes);
}

void ApplicationImpl::restart()
{
    _isStarted = false;
}

void ApplicationImpl::end()
{
    glfwSetWindowShouldClose(CAST_VIEW(_view)->getGLFWWindow(), 1);
}

void ApplicationImpl::setPreferredFramesPerSecond(int fps)
{
    _fps = fps;
}

Application::LanguageType ApplicationImpl::getCurrentLanguage() const
{
    Application::LanguageType ret = Application::LanguageType::ENGLISH;

    LCID localeID = GetUserDefaultLCID();
    unsigned short primaryLanguageID = localeID & 0xFF;

    switch (primaryLanguageID)
    {
        case LANG_CHINESE:
            ret = Application::LanguageType::CHINESE;
            break;
        case LANG_ENGLISH:
            ret = Application::LanguageType::ENGLISH;
            break;
        case LANG_FRENCH:
            ret = Application::LanguageType::FRENCH;
            break;
        case LANG_ITALIAN:
            ret = Application::LanguageType::ITALIAN;
            break;
        case LANG_GERMAN:
            ret = Application::LanguageType::GERMAN;
            break;
        case LANG_SPANISH:
            ret = Application::LanguageType::SPANISH;
            break;
        case LANG_DUTCH:
            ret = Application::LanguageType::DUTCH;
            break;
        case LANG_RUSSIAN:
            ret = Application::LanguageType::RUSSIAN;
            break;
        case LANG_KOREAN:
            ret = Application::LanguageType::KOREAN;
            break;
        case LANG_JAPANESE:
            ret = Application::LanguageType::JAPANESE;
            break;
        case LANG_HUNGARIAN:
            ret = Application::LanguageType::HUNGARIAN;
            break;
        case LANG_PORTUGUESE:
            ret = Application::LanguageType::PORTUGUESE;
            break;
        case LANG_ARABIC:
            ret = Application::LanguageType::ARABIC;
            break;
        case LANG_NORWEGIAN:
            ret = Application::LanguageType::NORWEGIAN;
            break;
        case LANG_POLISH:
            ret = Application::LanguageType::POLISH;
            break;
        case LANG_TURKISH:
            ret = Application::LanguageType::TURKISH;
            break;
        case LANG_UKRAINIAN:
            ret = Application::LanguageType::UKRAINIAN;
            break;
        case LANG_ROMANIAN:
            ret = Application::LanguageType::ROMANIAN;
            break;
        case LANG_BULGARIAN:
            ret = Application::LanguageType::BULGARIAN;
            break;
    }

    return ret;
}

std::string ApplicationImpl::getCurrentLanguageCode() const
{
    LANGID lid = GetUserDefaultUILanguage();
    const LCID locale_id = MAKELCID(lid, SORT_DEFAULT);
    static char code[3] = { 0 };
    GetLocaleInfoA(locale_id, LOCALE_SISO639LANGNAME, code, sizeof(code));
    code[2] = '\0';
    return code;
}

bool ApplicationImpl::isDisplayStats() {
    se::AutoHandleScope hs;
    se::Value ret;
    char commandBuf[100] = "cc.debug.isDisplayStats();";
    se::ScriptEngine::getInstance()->evalString(commandBuf, 100, &ret);
    return ret.toBoolean();
}

void ApplicationImpl::setDisplayStats(bool isShow) {
    se::AutoHandleScope hs;
    char commandBuf[100] = {0};
    sprintf(commandBuf, "cc.debug.setDisplayStats(%s);", isShow ? "true" : "false");
    se::ScriptEngine::getInstance()->evalString(commandBuf);
}

float ApplicationImpl::getScreenScale() const
{
    return CAST_VIEW(_view)->getScale();
}

GLint ApplicationImpl::getMainFBO() const
{
    return CAST_VIEW(_view)->getMainFBO();
}

Application::Platform ApplicationImpl::getPlatform() const
{
    return Application::Platform::WINDOWS;
}

bool ApplicationImpl::openURL(const std::string &url)
{
    WCHAR *temp = new WCHAR[url.size() + 1];
    int wchars_num = MultiByteToWideChar(CP_UTF8, 0, url.c_str(), url.size() + 1, temp, url.size() + 1);
    HINSTANCE r = ShellExecuteW(NULL, L"open", temp, NULL, NULL, SW_SHOWNORMAL);
    delete[] temp;
    return (size_t)r>32;
}


void ApplicationImpl::setMultitouch(bool)
{
}

void ApplicationImpl::onCreateView(Application::PixelFormat& pixelformat, Application::DepthFormat& depthFormat, int& multisamplingCount)
{  
    pixelformat = Application::PixelFormat::RGBA8;
    depthFormat = Application::DepthFormat::DEPTH24_STENCIL8;

    multisamplingCount = 0;
}

void ApplicationImpl::createView(const std::string& name, int width, int height)
{
    int multisamplingCount = 0;
    Application::PixelFormat pixelformat;
    Application::DepthFormat depthFormat;
    
    onCreateView(pixelformat,
                 depthFormat,
                 multisamplingCount);

    _view = new GLView(_app, name, 0, 0, width, height, pixelformat, depthFormat, multisamplingCount);
    
    g_width = width;
    g_height = height;
}

std::string ApplicationImpl::getSystemVersion()
{
    // REFINE
    return std::string("unknown Windows version");
}
NS_CC_END
