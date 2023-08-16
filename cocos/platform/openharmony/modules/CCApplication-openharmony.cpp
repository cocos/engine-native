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
#include "platform/openharmony/napi/NapiHelper.h"
#include "base/CCScheduler.h"
#include "base/CCConfiguration.h"
#include "audio/include/AudioEngine.h"
#include "scripting/js-bindings/event/EventDispatcher.h"
#include "platform/openharmony/OpenHarmonyPlatform.h"

PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOESEXT = 0;
PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOESEXT = 0;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOESEXT = 0;

NS_CC_BEGIN

void Application::updateViewSize(int width, int height)
{
    if(width <= 0 || height <= 0)
    {
        return;
    }
    _viewSize.x = width;
    _viewSize.y = height;
    
    // handle resize event
    Application::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
        EventDispatcher::dispatchResizeEvent(width, height);
    });
}

Application* Application::_instance = nullptr;
std::shared_ptr<Scheduler> Application::_scheduler = nullptr;

Application::Application(const std::string& name, int width, int height)
{
    Application::_instance = this;
    Configuration::getInstance();

    _scheduler = std::make_shared<Scheduler>();

    _renderTexture = new RenderTexture(width, height);
    updateViewSize(width, height);
}

Application::~Application()
{
#if USE_AUDIO
    AudioEngine::end();
#endif

    EventDispatcher::destroy();
    se::ScriptEngine::destroyInstance();

    delete _renderTexture;
    _renderTexture = nullptr;

    Application::_instance = nullptr;
}

void Application::start()
{
    if(!applicationDidFinishLaunching())
        return;
}

void Application::restart()
{
    // restartJSVM();
}

void Application::end()
{
    int32_t value;
    NapiHelper::napiCallFunction("terminateProcess", &value);
}

void Application::setMultitouch(bool /*value*/)
{

}

bool Application::applicationDidFinishLaunching()
{
    return true;
}

void Application::onPause()
{

}

void Application::onResume()
{

}

void Application::setPreferredFramesPerSecond(int fps)
{
    _fps = fps;
    // setPreferredFramesPerSecondJNI(_fps);
}

bool Application::isDisplayStats() {
    se::AutoHandleScope hs;
    se::Value ret;
    char commandBuf[100] = "cc.debug.isDisplayStats();";
    se::ScriptEngine::getInstance()->evalString(commandBuf, 100, &ret);
    return ret.toBoolean();
}

void Application::setDisplayStats(bool isShow) {
    se::AutoHandleScope hs;
    char commandBuf[100] = {0};
    sprintf(commandBuf, "cc.debug.setDisplayStats(%s);", isShow ? "true" : "false");
    se::ScriptEngine::getInstance()->evalString(commandBuf);
}

std::string Application::getCurrentLanguageCode() const {
    std::string str;
    NapiHelper::napiCallFunction<std::string>("getSystemLanguage", &str);
    std::string::size_type pos = str.find('-');
    if(pos != std::string::npos) {
        str = str.substr(0, pos);
    }
    return str;
}

Application::LanguageType Application::getCurrentLanguage() const
{
    std::string languageName = getCurrentLanguageCode(); // NOLINT
    const char* pLanguageName = languageName.c_str();
    LanguageType ret = LanguageType::ENGLISH;

    if (0 == strcmp("zh", pLanguageName))
    {
        ret = LanguageType::CHINESE;
    }
    else if (0 == strcmp("en", pLanguageName))
    {
        ret = LanguageType::ENGLISH;
    }
    else if (0 == strcmp("fr", pLanguageName))
    {
        ret = LanguageType::FRENCH;
    }
    else if (0 == strcmp("it", pLanguageName))
    {
        ret = LanguageType::ITALIAN;
    }
    else if (0 == strcmp("de", pLanguageName))
    {
        ret = LanguageType::GERMAN;
    }
    else if (0 == strcmp("es", pLanguageName))
    {
        ret = LanguageType::SPANISH;
    }
    else if (0 == strcmp("ru", pLanguageName))
    {
        ret = LanguageType::RUSSIAN;
    }
    else if (0 == strcmp("nl", pLanguageName))
    {
        ret = LanguageType::DUTCH;
    }
    else if (0 == strcmp("ko", pLanguageName))
    {
        ret = LanguageType::KOREAN;
    }
    else if (0 == strcmp("ja", pLanguageName))
    {
        ret = LanguageType::JAPANESE;
    }
    else if (0 == strcmp("hu", pLanguageName))
    {
        ret = LanguageType::HUNGARIAN;
    }
    else if (0 == strcmp("pt", pLanguageName))
    {
        ret = LanguageType::PORTUGUESE;
    }
    else if (0 == strcmp("ar", pLanguageName))
    {
        ret = LanguageType::ARABIC;
    }
    else if (0 == strcmp("nb", pLanguageName))
    {
        ret = LanguageType::NORWEGIAN;
    }
    else if (0 == strcmp("pl", pLanguageName))
    {
        ret = LanguageType::POLISH;
    }
    else if (0 == strcmp("tr", pLanguageName))
    {
        ret = LanguageType::TURKISH;
    }
    else if (0 == strcmp("uk", pLanguageName))
    {
        ret = LanguageType::UKRAINIAN;
    }
    else if (0 == strcmp("ro", pLanguageName))
    {
        ret = LanguageType::ROMANIAN;
    }
    else if (0 == strcmp("bg", pLanguageName))
    {
        ret = LanguageType::BULGARIAN;
    }
    return ret;
}

Application::Platform Application::getPlatform() const
{
    return Platform::OpenHarmony;
}

float Application::getScreenScale() const
{
    return 1.f;
}

GLint Application::getMainFBO() const
{
    return _mainFBO;
}

void Application::onCreateView(PixelFormat& /*pixelformat*/, DepthFormat& /*depthFormat*/, int& /*multisamplingCount*/)
{

}

bool Application::openURL(const std::string &url)
{
    return false;
}

void Application::copyTextToClipboard(const std::string &text)
{
    // copyTextToClipboardJNI(text);
}


std::string Application::getSystemVersion()
{
    std::string str;
    NapiHelper::napiCallFunction<std::string>("getOSFullName", &str);
    return str;
}

const cocos2d::Vec2& Application::getViewSize() const
{
    return _viewSize;
}

NS_CC_END
