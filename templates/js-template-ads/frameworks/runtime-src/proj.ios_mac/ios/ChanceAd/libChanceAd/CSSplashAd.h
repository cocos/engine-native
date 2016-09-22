//
//  CSSplashAd.h
//  ChanceAdSDK
//
//  Created by Chance_yangjh on 16/5/10.
//  Copyright © 2016年 Chance. All rights reserved.
//

#ifndef CSSplashAd_h
#define CSSplashAd_h
#import <Foundation/Foundation.h>

@protocol CSSplashAdDelegate;

@interface CSSplashAd : NSObject

// 广告位ID
@property (nonatomic, copy) NSString *placementID;
// 最小展现时长
@property (nonatomic, assign) int minShowDur;
// 自动关闭时长
@property (nonatomic, assign) int minAutoCloseDur;

@property (nonatomic, weak) id <CSSplashAdDelegate> delegate;

// 开屏广告只有一个
+ (CSSplashAd *)sharedInstance;

// 显示开屏广告
- (BOOL)showSplashInWindow:(UIWindow *)window;

@end


@protocol CSSplashAdDelegate <NSObject>

@optional

// 开屏广告关闭完成
- (void)csSplashAdCloseFinished:(CSSplashAd *)splashAd;

@end
#endif
