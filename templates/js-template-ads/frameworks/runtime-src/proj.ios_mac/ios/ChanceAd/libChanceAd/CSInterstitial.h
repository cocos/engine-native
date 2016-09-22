//
//  CSInterstitial.h
//  CSADSDK
//
//  Created by Chance_yangjh on 13-10-28.
//  Copyright (c) 2013年 Chance. All rights reserved.
//

#ifndef CSInterstitial_h
#define CSInterstitial_h
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "CSError.h"


typedef NS_ENUM(unsigned int, CSInterstitialStatus) {
    CSInterstitialStatus_Hide,
    CSInterstitialStatus_Showing,
    CSInterstitialStatus_Show,
    CSInterstitialStatus_Hiding,
};


// 插屏广告加载完成
typedef void (^CSInterstitialDidLoadAD)();
// 插屏广告加载出错
typedef void (^CSInterstitialLoadFailure)(CSError *error);
// 插屏广告打开完成
typedef void (^CSInterstitialDidPresent)();
// 插屏广告倒计时结束
typedef void (^CSInterstitialCountDownFinished)();
// 插屏广告将要关闭
typedef void (^CSInterstitialWillDismiss)();
// 插屏广告关闭完成
typedef void (^CSInterstitialDidDismiss)();


@protocol CSInterstitialDelegate;

@interface CSInterstitial : NSObject

// 广告位ID
@property (nonatomic, copy) NSString *placementID;
// 关闭按钮显示前的倒计时时长（秒）
@property (nonatomic, assign) unsigned int countdown;
// 倒计时后是否自动关闭，默认为NO
@property (nonatomic, assign) BOOL autoCloseAfterCountDown;
// 是否显示关闭按钮，默认为YES
@property (nonatomic, assign) BOOL showCloseButton;
// 广告是否准备好。准备好则show或fill马上就能展现，否则可能需要等待
@property (nonatomic, readonly) BOOL isReady;
// 关闭时是否加载下一个广告，默认为YES
@property (nonatomic, assign) BOOL loadNextWhenClose;
// 点击广告后是否关闭广告
@property (nonatomic, assign) BOOL closeWhenClick;
// 插屏广告当前状态
@property (nonatomic, readonly) CSInterstitialStatus status;
// 插屏广告尺寸
@property (nonatomic, readonly) CGSize interstitialSize;
// 插屏广告回调代理
@property (nonatomic, weak) id <CSInterstitialDelegate> delegate;

// 插屏广告加载完成的block
@property (nonatomic, copy) CSInterstitialDidLoadAD didLoadAD;
// 插屏广告加载出错的block
@property (nonatomic, copy) CSInterstitialLoadFailure loadADFailure;
// 插屏广告打开完成的block
@property (nonatomic, copy) CSInterstitialDidPresent didPresent;
// 插屏广告倒计时结束的block
@property (nonatomic, copy) CSInterstitialCountDownFinished countDownFinished;
// 插屏广告将要关闭的block
@property (nonatomic, copy) CSInterstitialWillDismiss willDismiss;
// 插屏广告关闭完成的block
@property (nonatomic, copy) CSInterstitialDidDismiss didDismiss;

// 插屏广告只有一个
+ (CSInterstitial *)sharedInterstitial;

/**
 *	@brief	加载插屏广告数据
 */
- (void)loadInterstitial;

/**
 *	@brief	显示插屏广告
 */
- (void)showInterstitial;

/**
 *	@brief	显示插屏广告
 *
 *	@param 	rootView 	插屏广告的父视图
 */
- (void)showInterstitialOnRootView:(UIView *)rootView;

/**
 *	@brief	用插屏广告填充view
 *
 *	@param 	view   插屏广告的展现容器
 */
- (void)fillInterstitialInView:(UIView *)view;

/**
 *	@brief	关闭插屏广告
 */
- (void)closeInterstitial;

@end


@protocol CSInterstitialDelegate <NSObject>

@optional

// 插屏广告发出请求
- (void)csInterstitialRequestAD:(CSInterstitial *)csInterstitial;

// 插屏广告加载完成
- (void)csInterstitialDidLoadAd:(CSInterstitial *)csInterstitial;

// 插屏广告加载错误
- (void)csInterstitial:(CSInterstitial *)csInterstitial
loadAdFailureWithError:(CSError *)csError;

// 插屏广告打开完成
- (void)csInterstitialDidPresentScreen:(CSInterstitial *)csInterstitial;

// 倒计时结束
- (void)csInterstitialCountDownFinished:(CSInterstitial *)csInterstitial;

// 插屏广告将要关闭
- (void)csInterstitialWillDismissScreen:(CSInterstitial *)csInterstitial;

// 插屏广告关闭完成
- (void)csInterstitialDidDismissScreen:(CSInterstitial *)csInterstitial;

@end
#endif
