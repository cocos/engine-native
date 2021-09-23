//
//  TmpMethodManager.h
//  CXJ
//
//  Created by LX on 17/09/2021.
//
#pragma once
//#if (CC_PLATFORM == CC_PLATFORM_MAC_OSX) || (CC_PLATFORM == CC_PLATFORM_MAC_IOS)
#import <Foundation/Foundation.h>

typedef void (^ICallback)(NSString*, NSString*);
//typedef int64_t strFunc;

@interface JsbBridge : NSObject
+(instancetype)sharedInstance;
-(bool)setCallback:(ICallback)cb;
-(bool)callByScript:(NSString*)arg0 arg1:(NSString*)arg1;
-(void)sendToScript:(NSString*)arg0 arg1:(NSString*)arg1;
@end

//#endif // CC_PLATFORM == CC_PLATFORM_MAC
