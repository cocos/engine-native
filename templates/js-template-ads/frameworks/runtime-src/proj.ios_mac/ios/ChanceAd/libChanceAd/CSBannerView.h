//
//  CSBannerView.h
//  CSADSDK
//
//  Created by cassano on 13-10-14.
//  Copyright (c) 2013年 Chance. All rights reserved.
//

#ifndef CSBannerView_h
#define CSBannerView_h
#import <UIKit/UIKit.h>
#import "CSADRequest.h"
#import "CSError.h"


#define CSBannerSize  ((UI_USER_INTERFACE_IDIOM()==UIUserInterfaceIdiomPhone)?CGSizeMake(320.0f, 50.0f):CGSizeMake(728.0f, 90.0f))

// Banner展现失败
typedef void (^CSBannerShowFailure)(CSError *error);
// Banner将要显示
typedef void (^CSBannerWillPresent)();
// Banner移除完成
typedef void (^CSBannerDidDismiss)();

@protocol CSBannerViewDelegate;

// iPhone和iPod Touch的Banner广告大小为320x50.
// iPad的Banner广告大小为728x90.
@interface CSBannerView : UIView

@property (nonatomic, weak) id <CSBannerViewDelegate> delegate;

// Banner展现失败的block
@property (nonatomic, copy) CSBannerShowFailure showFailure;
// Banner将要显示的block
@property (nonatomic, copy) CSBannerWillPresent willPresent;
// Banner移除完成的block
@property (nonatomic, copy) CSBannerDidDismiss didDismiss;

/**
 *	@brief	加载Banner广告
 *
 *	@param 	csRequest 	请求Banner广告时的参数
 */
- (void)loadRequest:(CSADRequest *)csRequest;

@end


@protocol CSBannerViewDelegate <NSObject>

@optional

// Banner广告发出请求
- (void)csBannerViewRequestAD:(CSBannerView *)csBannerView;

// Banner广告展现失败
- (void)csBannerView:(CSBannerView *)csBannerView
       showAdFailure:(CSError *)csError;

// 将要展示Banner广告
- (void)csBannerViewWillPresentScreen:(CSBannerView *)csBannerView;

// 移除Banner广告
- (void)csBannerViewDidDismissScreen:(CSBannerView *)csBannerView;

@end
#endif
