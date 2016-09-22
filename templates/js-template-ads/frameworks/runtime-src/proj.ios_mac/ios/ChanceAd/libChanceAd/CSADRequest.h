//
//  CSADRequest.h
//  CSADSDK
//
//  Created by Chance_yangjh on 13-11-4.
//  Copyright (c) 2013年 Chance. All rights reserved.
//

#ifndef CSADRequest_h
#define CSADRequest_h
#import <Foundation/Foundation.h>


#define Banner_MinRequestInterval           5
#define Banner_MinDisplayTime               5
#define Banner_DefaultRequestInterval       15
#define Banner_DefaultDisplayTime           15

@interface CSADRequest : NSObject

@property (nonatomic, strong) NSString *placementID;      // 广告位ID
@property (nonatomic, assign) NSUInteger requestInterval; // 广告请求间隔，单位为秒，最小值5。只在Banner有效
@property (nonatomic, assign) NSUInteger displayTime;     // 广告展现时长，单位为秒，最小值5。只在Banner有效

+ (id)request;

+ (id)requestWithRequestInterval:(NSUInteger)requestInterval
                  andDisplayTime:(NSUInteger)displayTime;

@end
#endif
