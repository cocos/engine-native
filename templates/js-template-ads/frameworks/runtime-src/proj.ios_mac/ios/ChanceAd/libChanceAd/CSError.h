//
//  CSError.h
//  CSADSDK
//
//  Created by Chance_yangjh on 13-11-1.
//  Copyright (c) 2013年 Chance. All rights reserved.
//

#ifndef CSError_h
#define CSError_h
#import <Foundation/Foundation.h>

typedef NS_ENUM(unsigned int, CSErrorCode) {
    // 1000~1999 为服务器端错误
    CSErrorCode_Success,
    CSErrorCode_ExistVideoAD = CSErrorCode_Success,
    CSErrorCode_NoServices = 1000,     // 服务未开启
    CSErrorCode_HttpMethodError,       // http方法错误
    CSErrorCode_InvalidParameter,      // 参数错误
    CSErrorCode_InvalidPostData,       // POST数据错误
    CSErrorCode_EventSwitchClosed,     // 事件关闭
    CSErrorCode_ChanceClosed = 1005,   // Chance关闭，或PublisherID错误
    CSErrorCode_NoAdGroup,             // 无广告适合的广告组
    CSErrorCode_NoAdIdea,              // 无广告创意可用
    CSErrorCode_NoIdeaURL,             // 创意URL不存在
    CSErrorCode_NoAdTemplate,          // 广告模板不存在
    CSErrorCode_AppClosed = 1010,      // App关闭
    CSErrorCode_VersionClosed,         // App版本关闭
    CSErrorCode_UnsupportedAdType,     // 未支持的广告类型
    CSErrorCode_FrequentRequest,       // 频繁的请求
    CSErrorCode_RegionSwitchClosed,    // 地域开关关闭
    CSErrorCode_Cheat = 1015,          // 作弊
    CSErrorCode_UncompressError = 1016,// 解压失败
    CSErrorCode_NoCoin = 1030,         // 未得到积分
    // 2000~2999为SDK错误码
    CSErrorCode_NetError = 2001,       // 网络错误
    CSErrorCode_NoData,                // 服务器返回内容为空
    CSErrorCode_LoadingTimeout = 9998, // 加载超时
    CSErrorCode_Unknown = 9999,        // 未知错误
};

@interface CSError : NSError

+ (NSString *)localizedDescriptionOf:(CSErrorCode)errorCode;

@end
#endif
