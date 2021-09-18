//
//  TmpMethodManager.h
//  CXJ
//
//  Created by LX on 17/09/2021.
//
#pragma once
//#if (CC_PLATFORM == CC_PLATFORM_MAC_OSX) || (CC_PLATFORM == CC_PLATFORM_MAC_IOS)
#import <Foundation/Foundation.h>

typedef void (^strFunc)(NSString* );
//typedef int64_t strFunc;

@interface MethodManager : NSObject

+(instancetype)sharedInstance;
-(bool)addFunc:(NSString*)key function:(strFunc)f;
-(bool)applyFunc:(NSString*)key function:(NSString*)arg;
-(strFunc)removeFunc:(NSString*)key;
-(void)invokeScript:(NSString*)key arg:(NSString*)arg;
@end

//#endif // CC_PLATFORM == CC_PLATFORM_MAC
