/***************************************************************************
 Copyright (c) 2018-2021 Xiamen Yaji Software Co., Ltd.

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
#include <iostream>
#include <string>
#include "JsObjCEventHandler.h"
#include "JsbBridge.h"

#import <Foundation/Foundation.h>

@implementation JsObjCEventHandler{
    NSMutableDictionary<NSString*, NSMutableArray*> *cbDictionnary;
    
}
static JsObjCEventHandler* instance = nil;
static ICallback cb = ^void (NSString* _arg0, NSString* _arg1){
    [[JsObjCEventHandler sharedInstance] triggerEvent:_arg0 arg1:_arg1];
};
+(instancetype)sharedInstance{
    static dispatch_once_t pred = 0;
    dispatch_once(&pred, ^{
        instance = [[super allocWithZone:NULL]init];
    });
    return instance;
}

+(id)allocWithZone:(struct _NSZone *)zone{
    return [JsObjCEventHandler sharedInstance];
}

-(id)copyWithZone:(struct _NSZone *)zone{
    return [JsObjCEventHandler sharedInstance];
}

-(void)addCallback:(NSString *)arg0 callback:(eventCallback)callback {
    if(![cbDictionnary objectForKey:arg0]){
        [cbDictionnary setValue:[NSMutableArray<eventCallback> new] forKey:arg0];
    }
    
    [[cbDictionnary objectForKey:arg0] addObject:callback];
}

-(void)triggerEvent:(NSString*)name arg1:(NSString*)arg1 {
    if(![cbDictionnary objectForKey:name]){
        return;
    }
    NSMutableArray<eventCallback>* arr = [cbDictionnary objectForKey:name];
    for (int i = 0; i< [arr count]; i++) {
        arr[i](arg1);
    }
}
-(void)removeEvent:(NSString *)arg0 {
    if(![cbDictionnary objectForKey:arg0]){
        return;
    }
    NSMutableArray* arr = [cbDictionnary objectForKey:arg0];
    [arr removeAllObjects];
    [cbDictionnary removeObjectForKey:arg0];
}
-(bool)removeCallback:(NSString *)arg0 callback:(eventCallback)callback {
    if(![cbDictionnary objectForKey:arg0]){
        return false;
    }
    NSMutableArray<eventCallback>* arr = [cbDictionnary objectForKey:arg0];
    for(int i =0;i< arr.count;i++){
        if(arr[i] == callback){
            [arr removeObjectAtIndex:i];
            //Possible to have second callback
        }
    }
    return true;
}
-(void)sendToScript:(NSString *)name arg1:(NSString *)arg1 {
    JsbBridge* m = [JsbBridge sharedInstance];
    [m sendToScript:name arg1:arg1];
}
-(void)sendToScript:(NSString *)name{
    JsbBridge* m = [JsbBridge sharedInstance];
    [m sendToScript:name];
}
-(id)init{
    self = [super init];
    cbDictionnary = [NSMutableDictionary new];
    JsbBridge* m = [JsbBridge sharedInstance];
    [m setCallback:cb];
    return self;
}

@end
