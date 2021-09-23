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

#import <Foundation/Foundation.h>
#include <string>
#include <Application.h>
#include "JsbBridge.h"
#include "cocos/bindings/jswrapper/v8/ScriptEngine.h"
#include "cocos/bindings/manual/JavaScriptObjCBridge.h"

//Native method with jni
bool callPlatformStringMethod(const std::string &eventName, const std::string &inputArg){
    NSString *key = [NSString stringWithCString:eventName.c_str() encoding:NSUTF8StringEncoding];
    NSString *arg = [NSString stringWithCString:inputArg.c_str() encoding:NSUTF8StringEncoding];
    JsbBridge * m = [JsbBridge sharedInstance];
    [m applyFunc:key function:arg];
    return true;
}


@implementation JsbBridge {
    ICallback callback;
}
static JsbBridge* instance = nil;
+(instancetype)sharedInstance{
    static dispatch_once_t pred = 0;
    dispatch_once(&pred, ^{
        instance = [[super allocWithZone:NULL]init];
    });
    return instance;
}
+(id)allocWithZone:(struct _NSZone *)zone{
    return [JsbBridge sharedInstance];
}

-(id)copyWithZone:(struct _NSZone *)zone{
    return [JsbBridge sharedInstance];
}
-(id)init{
    self = [super init];
    return self;
}
-(bool)setCallback:(ICallback)cb{
    callback = cb;
}
-(bool)callByScript:(NSString*)arg0 arg1:(NSString *)arg1{
    callback(arg0, arg1);
}

-(void)sendToScript:(NSString *)arg0 arg1:(NSString *)arg1{
    const std::string c_arg0{[arg0 UTF8String]};
    const std::string c_arg1{[arg1 UTF8String]};
    cc::Application::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
        bridgeCxxInstance->callByNative(c_arg0, c_arg1);
        //se::ScriptEngine::getInstance()->evalString(("cc.JsbBridge.applyMethod(\""+ functionKey +"\",\""+ farg +"\")").c_str());
    });
}
@end

