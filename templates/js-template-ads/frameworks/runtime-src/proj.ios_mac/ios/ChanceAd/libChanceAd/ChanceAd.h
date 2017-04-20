//
//  ChanceAd.h
//  ChanceAd
//
//  Created by Chance_yangjh on 13-10-15.
//  Copyright (c) 2013年 Chance. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "CSError.h"


// SDK_Version仅供参考，以[ChanceAd sdkVersion];得到的版本号为准
#define SDK_Version  @"6.4.1"


@interface ChanceAd : NSObject

/**
 *	@brief	开启会话，在程序启动的时候调用
 *          建议放在协议方法application:didFinishLaunchingWithOptions:中调用
 *
 *	@param 	publisherID 	publisherID
 */
+ (void)startSession:(NSString *)publisherID;

/**
 *	@brief	获取SDK版本号
 *
 *	@return	SDK版本号
 */
+ (NSString *)sdkVersion;

/**
 *	@brief	清空视频文件缓存
 */
+ (void)clearVideoCaches;

/**
 *	@brief	非越狱设备上是否应用内打开（越狱设备上直接强制跳转）
 *
 *	@param 	openInApp 	YES表示iTunes链接要应用内打开。默认为YES。
 */
+ (void)openInAppWhenNoJailBroken:(BOOL)openInApp;

/**
 *  是否越狱设备
 *
 *  @return 越狱设备返回YES
 */
+ (BOOL)isJailBroken;

@end

