/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2017 Chukong Technologies Inc.

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

#import "CCApplication.h"
#import <UIKit/UIKit.h>
#include "base/CCScheduler.h"
#include "base/CCAutoreleasePool.h"
#include "base/CCGLUtils.h"
#include "base/CCConfiguration.h"
#include "renderer/gfx/DeviceGraphics.h"
#include "scripting/js-bindings/event/EventDispatcher.h"
#include "scripting/js-bindings/jswrapper/SeApi.h"
#include "CCEAGLView-ios.h"
#include "base/CCGLUtils.h"
#include "audio/include/AudioEngine.h"


namespace
{
    cocos2d::Vec2 getResolution()
    {
        CGRect bounds = [UIScreen mainScreen].bounds;
        float scale = [[UIScreen mainScreen] scale];
        float width = bounds.size.width * scale;
        float height = bounds.size.height * scale;
        
        return cocos2d::Vec2(width, height);
    }
    
    bool setCanvasCallback(se::Object* global)
    {
        cocos2d::Vec2 resolution = getResolution();
        se::ScriptEngine* se = se::ScriptEngine::getInstance();
        uint8_t devicePixelRatio = cocos2d::Application::getInstance()->getDevicePixelRatio();
        char commandBuf[200] = {0};
        sprintf(commandBuf, "window.innerWidth = %d; window.innerHeight = %d;",
                (int)(resolution.x / devicePixelRatio),
                (int)(resolution.y / devicePixelRatio));
        se->evalString(commandBuf);
        cocos2d::ccViewport(0, 0, resolution.x / devicePixelRatio, resolution.y / devicePixelRatio);
        glDepthMask(GL_TRUE);
        return true;
    }
}

@interface MainLoop : NSObject
{
    id _displayLink;
    int _fps;
    float _systemVersion;
    BOOL _isAppActive;
    cocos2d::ApplicationImpl* _application;
    cocos2d::Scheduler* _scheduler;
}
-(void) startMainLoop;
-(void) stopMainLoop;
-(void) doCaller: (id) sender;
-(void) setPreferredFPS:(int)fps;
-(void) firstStart:(id) view;
@end

@implementation MainLoop

- (instancetype)initWithApplication:(cocos2d::ApplicationImpl*) ApplicationImpl
{
    self = [super init];
    if (self)
    {
        _fps = 60;
        _systemVersion = [[UIDevice currentDevice].systemVersion floatValue];
    
        _application = ApplicationImpl;
        _scheduler = _application->getScheduler();
        
        _isAppActive = [UIApplication sharedApplication].applicationState == UIApplicationStateActive;
        NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
        [nc addObserver:self selector:@selector(appDidBecomeActive) name:UIApplicationDidBecomeActiveNotification object:nil];
        [nc addObserver:self selector:@selector(appDidBecomeInactive) name:UIApplicationWillResignActiveNotification object:nil];
    }
    return self;
}

-(void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [_displayLink release];
    
    [super dealloc];
}

- (void)appDidBecomeActive
{
    _isAppActive = YES;
}

- (void)appDidBecomeInactive
{
    _isAppActive = NO;
}

-(void) firstStart:(id) view
{
    if ([view isReady]) 
    {
        auto scheduler = _application->getScheduler();
        scheduler->removeAllFunctionsToBePerformedInCocosThread();
        scheduler->unscheduleAll();

        se::ScriptEngine::getInstance()->cleanup();
        cocos2d::PoolManager::getInstance()->getCurrentPool()->clear();
        cocos2d::EventDispatcher::init();

        cocos2d::ccInvalidateStateCache();
        se::ScriptEngine* se = se::ScriptEngine::getInstance();
        se->addRegisterCallback(setCanvasCallback);

        if(!_application->applicationDidFinishLaunching())
            return;

        [self startMainLoop];
    }
    else
        [self performSelector:@selector(firstStart:) withObject:view afterDelay:0];
}

-(void) startMainLoop
{
    [self stopMainLoop];
    
    _displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(doCaller:)];
    if (_systemVersion >= 10.0f)
        [_displayLink setPreferredFramesPerSecond: _fps];
    else
        [_displayLink setFrameInterval: 60 / _fps];
    [_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

-(void) stopMainLoop
{
    if (_displayLink != nil)
    {
        [_displayLink invalidate];
        _displayLink = nil;
    }
}

-(void) setPreferredFPS:(int)fps
{
    _fps = fps;
    [self startMainLoop];
}

-(void) doCaller: (id) sender
{
    static std::chrono::steady_clock::time_point prevTime;
    static std::chrono::steady_clock::time_point now;
    static float dt = 0.f;

    prevTime = std::chrono::steady_clock::now();
    
    bool downsampleEnabled = _application->isDownsampleEnabled();
    if (downsampleEnabled)
        _application->getRenderTexture()->prepare();
    
    _scheduler->update(dt);
    cocos2d::EventDispatcher::dispatchTickEvent(dt);
    
    if (downsampleEnabled)
        _application->getRenderTexture()->draw();
    
    [(CCEAGLView*)(_application->getView()) swapBuffers];
    cocos2d::PoolManager::getInstance()->getCurrentPool()->clear();
    
    now = std::chrono::steady_clock::now();
    dt = std::chrono::duration_cast<std::chrono::microseconds>(now - prevTime).count() / 1000000.f;
}

@end

NS_CC_BEGIN

std::shared_ptr<ApplicationImpl> ApplicationImpl::_instance = nullptr;

ApplicationImpl::ApplicationImpl(const std::string& name, int width, int height)
{
    _scheduler = new Scheduler();

    createView(name, width, height);
    Configuration::getInstance();
    
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_mainFBO);
    _renderTexture = new RenderTexture(width, height);
    
    se::ScriptEngine::getInstance();
    EventDispatcher::init();
    
    _delegate = [[MainLoop alloc] initWithApplication:this];
}

ApplicationImpl::~ApplicationImpl()
{
    [(CCEAGLView*)_view release];
    _view = nullptr;

    delete _scheduler;
    _scheduler = nullptr;
    
    EventDispatcher::destroy();
    se::ScriptEngine::destroyInstance();

    // close audio device
    cocos2d::experimental::AudioEngine::end();
    
    // stop main loop
    [(MainLoop*)_delegate stopMainLoop];
    [(MainLoop*)_delegate release];
    _delegate = nullptr;
    
    delete _renderTexture;
    _renderTexture = nullptr;
}

void ApplicationImpl::start()
{
    if (_delegate)
        [(MainLoop*)_delegate performSelector:@selector(firstStart:) withObject:(CCEAGLView*)_view afterDelay:0];    
}

void ApplicationImpl::restart()
{
    if (_delegate) {
        [(MainLoop*)_delegate stopMainLoop];
        [(MainLoop*)_delegate performSelector:@selector(firstStart:) withObject:(CCEAGLView*)_view afterDelay:0];
    }
}

void ApplicationImpl::end()
{
    delete this;

    exit(0);
}

void ApplicationImpl::setPreferredFramesPerSecond(int fps)
{
    [(MainLoop*)_delegate setPreferredFPS: fps];
}

std::string ApplicationImpl::getCurrentLanguageCode() const
{
    char code[3]={0};
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSArray *languages = [defaults objectForKey:@"AppleLanguages"];
    NSString *currentLanguage = [languages objectAtIndex:0];

    // get the current language code.(such as English is "en", Chinese is "zh" and so on)
    NSDictionary* temp = [NSLocale componentsFromLocaleIdentifier:currentLanguage];
    NSString * languageCode = [temp objectForKey:NSLocaleLanguageCode];
    [languageCode getCString:code maxLength:3 encoding:NSASCIIStringEncoding];
    code[2]='\0';
    return std::string(code);
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
    // get the current language and country config
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSArray *languages = [defaults objectForKey:@"AppleLanguages"];
    NSString *currentLanguage = [languages objectAtIndex:0];

    // get the current language code.(such as English is "en", Chinese is "zh" and so on)
    NSDictionary* temp = [NSLocale componentsFromLocaleIdentifier:currentLanguage];
    NSString * languageCode = [temp objectForKey:NSLocaleLanguageCode];

    if ([languageCode isEqualToString:@"zh"]) return Application::LanguageType::CHINESE;
    if ([languageCode isEqualToString:@"en"]) return Application::LanguageType::ENGLISH;
    if ([languageCode isEqualToString:@"fr"]) return Application::LanguageType::FRENCH;
    if ([languageCode isEqualToString:@"it"]) return Application::LanguageType::ITALIAN;
    if ([languageCode isEqualToString:@"de"]) return Application::LanguageType::GERMAN;
    if ([languageCode isEqualToString:@"es"]) return Application::LanguageType::SPANISH;
    if ([languageCode isEqualToString:@"nl"]) return Application::LanguageType::DUTCH;
    if ([languageCode isEqualToString:@"ru"]) return Application::LanguageType::RUSSIAN;
    if ([languageCode isEqualToString:@"ko"]) return Application::LanguageType::KOREAN;
    if ([languageCode isEqualToString:@"ja"]) return Application::LanguageType::JAPANESE;
    if ([languageCode isEqualToString:@"hu"]) return Application::LanguageType::HUNGARIAN;
    if ([languageCode isEqualToString:@"pt"]) return Application::LanguageType::PORTUGUESE;
    if ([languageCode isEqualToString:@"ar"]) return Application::LanguageType::ARABIC;
    if ([languageCode isEqualToString:@"nb"]) return Application::LanguageType::NORWEGIAN;
    if ([languageCode isEqualToString:@"pl"]) return Application::LanguageType::POLISH;
    if ([languageCode isEqualToString:@"tr"]) return Application::LanguageType::TURKISH;
    if ([languageCode isEqualToString:@"uk"]) return Application::LanguageType::UKRAINIAN;
    if ([languageCode isEqualToString:@"ro"]) return Application::LanguageType::ROMANIAN;
    if ([languageCode isEqualToString:@"bg"]) return Application::LanguageType::BULGARIAN;
    return Application::LanguageType::ENGLISH;
}

Application::Platform ApplicationImpl::getPlatform() const
{
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) // idiom for iOS <= 3.2, otherwise: [UIDevice userInterfaceIdiom] is faster.
        return Application::Platform::IPAD;
    else
        return Application::Platform::IPHONE;
}

float ApplicationImpl::getScreenScale() const
{
    return 1.f;
}

GLint ApplicationImpl::getMainFBO() const
{
    return _mainFBO;
}

bool ApplicationImpl::openURL(const std::string &url)
{
    NSString* msg = [NSString stringWithCString:url.c_str() encoding:NSUTF8StringEncoding];
    NSURL* nsUrl = [NSURL URLWithString:msg];
    return [[UIApplication sharedApplication] openURL:nsUrl];
}

void ApplicationImpl::setMultitouch(bool value)
{
    if (value != _multiTouch)
    {
        _multiTouch = value;
        if (_view)
            [(CCEAGLView*)_view setMultipleTouchEnabled:_multiTouch];
    }
}

void ApplicationImpl::onCreateView(Application::PixelFormat& pixelformat, Application::DepthFormat& depthFormat, int& multisamplingCount)
{
    pixelformat = Application::PixelFormat::RGB565;
    depthFormat = Application::DepthFormat::DEPTH24_STENCIL8;

    multisamplingCount = 0;
}

namespace
{
    GLenum depthFormatMap[] =
    {
        0,                        // NONE: no depth and no stencil
        GL_DEPTH_COMPONENT24_OES, // DEPTH_COMPONENT16: unsupport, convert to GL_DEPTH_COMPONENT24_OES
        GL_DEPTH_COMPONENT24_OES, // DEPTH_COMPONENT24
        GL_DEPTH_COMPONENT24_OES, // DEPTH_COMPONENT32F: unsupport, convert to GL_DEPTH_COMPONENT24_OES
        GL_DEPTH24_STENCIL8_OES,  // DEPTH24_STENCIL8
        GL_DEPTH24_STENCIL8_OES,  // DEPTH32F_STENCIL8: unsupport, convert to GL_DEPTH24_STENCIL8_OES
        GL_DEPTH_STENCIL_OES      // STENCIL_INDEX8
    };
    
    GLenum depthFormat2GLDepthFormat(cocos2d::Application::DepthFormat depthFormat)
    {
        return depthFormatMap[(int)depthFormat];
    }
}

void ApplicationImpl::createView(const std::string& /*name*/, int width, int height)
{
    Application::PixelFormat pixelFormat = Application::PixelFormat::RGB565;
    Application::DepthFormat depthFormat = Application::DepthFormat::DEPTH24_STENCIL8;
    int multisamplingCount = 0;
    
    onCreateView(pixelFormat,
                 depthFormat,
                 multisamplingCount);
    
    CGRect bounds;
    bounds.origin.x = 0;
    bounds.origin.y = 0;
    bounds.size.width = width;
    bounds.size.height = height;
    
    //IDEA: iOS only support these pixel format?
    // - RGB565
    // - RGBA8
    NSString *pixelString = kEAGLColorFormatRGB565;
    if (Application::PixelFormat::RGB565 != pixelFormat &&
        Application::PixelFormat::RGBA8 != pixelFormat)
        NSLog(@"Unsupported pixel format is set, iOS only support RGB565 or RGBA8. Change to use RGB565");
    else if (Application::PixelFormat::RGBA8 == pixelFormat)
        pixelString = kEAGLColorFormatRGBA8;
    
    // create view
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: bounds
                                         pixelFormat: pixelString
                                         depthFormat: depthFormat2GLDepthFormat(depthFormat)
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: multisamplingCount != 0
                                     numberOfSamples: multisamplingCount];
    
    [eaglView setMultipleTouchEnabled:_multiTouch];
    
    [eaglView retain];
    _view = eaglView;
}

std::string ApplicationImpl::getSystemVersion()
{
    NSString* systemVersion = [UIDevice currentDevice].systemVersion;
    return [systemVersion UTF8String];
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
