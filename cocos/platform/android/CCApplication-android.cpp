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
#include <EGL/egl.h>
#include <cstring>
#include "platform/android/jni/JniImp.h"
#include "platform/android/CCGL-android.h"
#include "base/CCScheduler.h"
#include "base/CCConfiguration.h"
#include "audio/include/AudioEngine.h"
#include "scripting/js-bindings/jswrapper/SeApi.h"
#include "scripting/js-bindings/event/EventDispatcher.h"

#define  LOG_TAG    "CCApplication_android Debug"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

// IDEA: using ndk-r10c will cause the next function could not be found. It may be a bug of ndk-r10c.
// Here is the workaround method to fix the problem.
#ifdef __aarch64__
extern "C" size_t __ctype_get_mb_cur_max(void) 
{
    return (size_t) sizeof(wchar_t);
}
#endif

PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOESEXT = 0;
PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOESEXT = 0;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOESEXT = 0;

NS_CC_BEGIN

std::shared_ptr<ApplicationImpl> ApplicationImpl::_instance = nullptr;

ApplicationImpl::ApplicationImpl(const std::string& name, int width, int height)
{
    Configuration::getInstance();

    _scheduler = new Scheduler();

    PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOESEXT = (PFNGLGENVERTEXARRAYSOESPROC)eglGetProcAddress("glGenVertexArraysOES");
    PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOESEXT = (PFNGLBINDVERTEXARRAYOESPROC)eglGetProcAddress("glBindVertexArrayOES");
    PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOESEXT = (PFNGLDELETEVERTEXARRAYSOESPROC)eglGetProcAddress("glDeleteVertexArraysOES");

    _renderTexture = new RenderTexture(width, height);
}

ApplicationImpl::~ApplicationImpl()
{
    EventDispatcher::destroy();
    se::ScriptEngine::destroyInstance();

    // close audio device
    cocos2d::experimental::AudioEngine::end();
    
    delete _scheduler;
    _scheduler = nullptr;

    delete _renderTexture;
    _renderTexture = nullptr;
}

void ApplicationImpl::start()
{
    if(!applicationDidFinishLaunching())
        return;
}

void ApplicationImpl::restart()
{
    restartJSVM();
}

void ApplicationImpl::end()
{
    exitApplication();
}

void ApplicationImpl::setMultitouch(bool /*value*/)
{

}

void ApplicationImpl::setPreferredFramesPerSecond(int fps) 
{
    _fps = fps;
    setPreferredFramesPerSecondJNI(_fps);
}

std::string ApplicationImpl::getCurrentLanguageCode() const
{
    std::string language = getCurrentLanguageJNI();
    return language.substr(0, 2);
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

Application::LanguageType ApplicationImpl::getCurrentLanguage() const
{
    std::string languageName = getCurrentLanguageJNI();
    const char* pLanguageName = languageName.c_str();
    Application::LanguageType ret = Application::LanguageType::ENGLISH;

    if (0 == strcmp("zh", pLanguageName))
    {
        ret = Application::LanguageType::CHINESE;
    }
    else if (0 == strcmp("en", pLanguageName))
    {
        ret = Application::LanguageType::ENGLISH;
    }
    else if (0 == strcmp("fr", pLanguageName))
    {
        ret = Application::LanguageType::FRENCH;
    }
    else if (0 == strcmp("it", pLanguageName))
    {
        ret = Application::LanguageType::ITALIAN;
    }
    else if (0 == strcmp("de", pLanguageName))
    {
        ret = Application::LanguageType::GERMAN;
    }
    else if (0 == strcmp("es", pLanguageName))
    {
        ret = Application::LanguageType::SPANISH;
    }
    else if (0 == strcmp("ru", pLanguageName))
    {
        ret = Application::LanguageType::RUSSIAN;
    }
    else if (0 == strcmp("nl", pLanguageName))
    {
        ret = Application::LanguageType::DUTCH;
    }
    else if (0 == strcmp("ko", pLanguageName))
    {
        ret = Application::LanguageType::KOREAN;
    }
    else if (0 == strcmp("ja", pLanguageName))
    {
        ret = Application::LanguageType::JAPANESE;
    }
    else if (0 == strcmp("hu", pLanguageName))
    {
        ret = Application::LanguageType::HUNGARIAN;
    }
    else if (0 == strcmp("pt", pLanguageName))
    {
        ret = Application::LanguageType::PORTUGUESE;
    }
    else if (0 == strcmp("ar", pLanguageName))
    {
        ret = Application::LanguageType::ARABIC;
    }
    else if (0 == strcmp("nb", pLanguageName))
    {
        ret = Application::LanguageType::NORWEGIAN;
    }
    else if (0 == strcmp("pl", pLanguageName))
    {
        ret = Application::LanguageType::POLISH;
    }
    else if (0 == strcmp("tr", pLanguageName))
    {
        ret = Application::LanguageType::TURKISH;
    }
    else if (0 == strcmp("uk", pLanguageName))
    {
        ret = Application::LanguageType::UKRAINIAN;
    }
    else if (0 == strcmp("ro", pLanguageName))
    {
        ret = Application::LanguageType::ROMANIAN;
    }
    else if (0 == strcmp("bg", pLanguageName))
    {
        ret = Application::LanguageType::BULGARIAN;
    }
    return ret;
}

Application::Platform ApplicationImpl::getPlatform() const
{
    return Application::Platform::ANDROIDOS;
}

float ApplicationImpl::getScreenScale() const
{
    return 1.f;
}

GLint ApplicationImpl::getMainFBO() const
{
    return _mainFBO;
}

void ApplicationImpl::onCreateView(Application::PixelFormat& /*pixelformat*/, Application::DepthFormat& /*depthFormat*/, int& /*multisamplingCount*/)
{

}

bool ApplicationImpl::openURL(const std::string &url)
{
    return openURLJNI(url);
}

std::string ApplicationImpl::getSystemVersion()
{
    return getSystemVersionJNI();
}



std::shared_ptr<ApplicationImpl> Application::getInstance() 
{ 
    return ApplicationImpl::getInstance();
}

Application::Application(const std::string &appName, int width, int height) 
{
    impl = ApplicationImpl::create(appName, width, height);
    impl->setAppDeletate(this);
}

Application::~Application() 
{
    ApplicationImpl::destroy();
}

void Application::start() { impl->start(); }

void Application::restart() { impl->restart(); }

void Application::end() { impl->end(); }


NS_CC_END
