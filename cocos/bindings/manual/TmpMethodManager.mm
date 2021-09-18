/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2021 Xiamen Yaji Software Co., Ltd.

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

#include "jsb_dispatch_platform_event.h"
#include "TmpMethodManager.h"
#import <Foundation/Foundation.h>
#include <string>
#include <Application.h>
#include "cocos/bindings/jswrapper/v8/ScriptEngine.h"
namespace cc {
//Native method with jni
bool callPlatformStringMethod(const std::string &eventName, const std::string &inputArg){
    NSString *key = [NSString stringWithCString:eventName.c_str() encoding:NSUTF8StringEncoding];
    NSString *arg = [NSString stringWithCString:inputArg.c_str() encoding:NSUTF8StringEncoding];
    MethodManager * m = [MethodManager sharedInstance];
    [m applyFunc:key function:arg];
    return true;
}
}

@implementation MethodManager {
    NSMutableDictionary* funcDic;
}
static MethodManager* instance = nil;
+(instancetype)sharedInstance{
    static dispatch_once_t pred = 0;
    dispatch_once(&pred, ^{
        instance = [[super allocWithZone:NULL]init];
    });
    return instance;
}
+(id)allocWithZone:(struct _NSZone *)zone{
    return [MethodManager sharedInstance];
}

-(id)copyWithZone:(struct _NSZone *)zone{
    return [MethodManager sharedInstance];
}
-(id)init{
    if(self = [super init]){
        funcDic = [NSMutableDictionary new];
    }
    return self;
}
-(bool)addFunc:(NSString*)key function:(strFunc)f{
    if(![funcDic objectForKey:key]){
        NSLog(@"Great, this is a new key here");
        [funcDic setObject:f forKey:key];
        return true;
    }
    NSLog(@"Oh no, func already exist");
    return false;
}
-(bool)applyFunc:(NSString*)key function:(NSString *)arg{
    strFunc f = [funcDic objectForKey:key];
    if(f){
        NSLog(@"Wow, function exist!");
        f(arg);
        return true;
    }
    NSLog(@"Oh no, failed to find  function for key");
    return false;
}
-(strFunc)removeFunc:(NSString*)key{
    strFunc f = [funcDic objectForKey:key];
    if(!f){
        NSLog(@"Wow, function not exist!");
    }
    return f;
}
-(void)invokeScript:(NSString *)key arg:(NSString *)arg{
    std::string functionKey {[key UTF8String]};
    std::string farg = {[arg UTF8String]};
    cc::Application::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
        se::ScriptEngine::getInstance()->evalString(("cc.MethodManager.applyMethod(\""+ functionKey +"\",\""+ farg +"\")").c_str());
    });
}
@end

