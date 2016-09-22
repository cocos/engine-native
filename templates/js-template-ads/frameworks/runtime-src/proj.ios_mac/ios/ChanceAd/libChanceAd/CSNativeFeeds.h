//
//  CSNativeFeeds.h
//  ChanceAdSDK
//
//  Created by Chance_yangjh on 16/4/1.
//  Copyright © 2016年 Chance. All rights reserved.
//

#ifndef CSNativeFeeds_h
#define CSNativeFeeds_h
#import <Foundation/Foundation.h>
#import "CSNativeFeedsView.h"
#import "CSError.h"


@interface CSNativeFeedsItem : NSObject
@property (nonatomic, readonly) NSString *title;
@property (nonatomic, readonly) NSString *content;
@property (nonatomic, readonly) NSString *iconUrl;
@property (nonatomic, readonly) NSArray<NSString *> *picUrls;
@property (nonatomic, readonly) CGSize size;
@property (nonatomic, readonly) int clickEffect;  // 点击效果：1、普通点击；2、二次确认
@end


// 信息流广告请求成功
typedef void (^CSNativeFeedsRequestSuccess)(NSArray<CSNativeFeedsItem *> *arrNativeFeedsItem);
// 信息流广告请求失败
typedef void (^CSNativeFeedsRequestFailure)(CSError *error);


@protocol CSNativeFeedsDelegate;

@interface CSNativeFeeds : NSObject

@property (nonatomic, strong) NSString *placementID;

// 信息流广告请求成功的block
@property (nonatomic, copy) CSNativeFeedsRequestSuccess requestSuccess;
// 信息流广告请求失败的block
@property (nonatomic, copy) CSNativeFeedsRequestFailure requestFailure;

@property (nonatomic, weak) id <CSNativeFeedsDelegate> delegate;

+ (CSNativeFeeds *)sharedInstance;

- (void)requestAD;

@end


@protocol CSNativeFeedsDelegate <NSObject>

@optional

// 请求广告成功
- (void)csNativeFeeds:(CSNativeFeeds *)nativeFeeds
     requestADSuccess:(NSArray<CSNativeFeedsItem *> *)arrNativeFeedsItem;

// 请求广告失败
- (void)csNativeFeeds:(CSNativeFeeds *)nativeFeeds
     requestADFailure:(CSError *)csError;

// 广告图标及广告图片下载完成
- (void)csNativeFeeds:(CSNativeFeeds *)nativeFeeds
         loadFinished:(CSNativeFeedsView *)nativeFeedsView;

@end
#endif
