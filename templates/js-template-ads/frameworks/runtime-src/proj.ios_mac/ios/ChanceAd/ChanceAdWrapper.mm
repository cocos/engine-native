//
//  ChanceAdWrapper.m
//  ChanceAdDemo
//
//  Created by Chance_yangjh on 16/8/29.
//
//

#import "ChanceAdWrapper.h"
#import "ChanceAd.h"
#import "CSBannerView.h"
#import "CSInterstitial.h"
#import "CSVideoAD.h"


@interface AdManager : NSObject <CSBannerViewDelegate, CSInterstitialDelegate, CSVideoADDelegate>
@property (nonatomic, strong) CSBannerView *bannerView;
@end
@implementation AdManager

+ (AdManager *)sharedInstance
{
    static AdManager *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[AdManager alloc] init];
    });
    return sharedInstance;
}

- (void)showBannerWithPlacementId:(NSString *)placementId
                         position:(BannerPosition)position
            andAnimationDirection:(BannerMoveDirection)direction
{
    if (nil == self.bannerView) {
        self.bannerView = [[CSBannerView alloc] initWithFrame:CGRectZero];
        self.bannerView.delegate = self;
    }
    
    CGPoint posFrom = CGPointZero, posTo = CGPointZero;
    UIViewController *topVC = [UIApplication sharedApplication].keyWindow.rootViewController;
    // Banner的位置
    switch (position) {
        case BannerPosition_LeftTop:
        {
            posTo = CGPointMake(self.bannerView.bounds.size.width/2, self.bannerView.bounds.size.height/2);
        }
            break;
        case BannerPosition_TopCenter:
        {
            posTo = CGPointMake(topVC.view.bounds.size.width/2, self.bannerView.bounds.size.height/2);
        }
            break;
        case BannerPosition_RightTop:
        {
            posTo = CGPointMake(topVC.view.bounds.size.width-self.bannerView.bounds.size.width/2, self.bannerView.bounds.size.height/2);
        }
            break;
        case BannerPosition_LeftBottom:
        {
            posTo = CGPointMake(self.bannerView.bounds.size.width/2, topVC.view.bounds.size.height-self.bannerView.bounds.size.height/2);
        }
            break;
        case BannerPosition_BottomCenter:
        {
            posTo = CGPointMake(topVC.view.bounds.size.width/2, topVC.view.bounds.size.height-self.bannerView.bounds.size.height/2);
        }
            break;
        case BannerPosition_RightBottom:
        {
            posTo = CGPointMake(topVC.view.bounds.size.width-self.bannerView.bounds.size.width/2, topVC.view.bounds.size.height-self.bannerView.bounds.size.height/2);
        }
            break;
        default:
            break;
    }
    // Banner动画方向
    switch (direction) {
        case BannerMoveDirection_Null:
        {
            posFrom = posTo;
        }
            break;
        case BannerMoveDirection_Up:
        {
            posFrom = CGPointMake(posTo.x, topVC.view.bounds.size.height+self.bannerView.bounds.size.height/2);
        }
            break;
        case BannerMoveDirection_Down:
        {
            posFrom = CGPointMake(posTo.x, -self.bannerView.bounds.size.height/2);
        }
            break;
        case BannerMoveDirection_Left:
        {
            posFrom = CGPointMake(topVC.view.bounds.size.width+self.bannerView.bounds.size.width/2, posTo.y);
        }
            break;
        case BannerMoveDirection_Right:
        {
            posFrom = CGPointMake(-self.bannerView.bounds.size.width/2, posTo.y);
        }
            break;
        default:
            break;
    }
    // 显示并加载Banner
    [topVC.view addSubview:self.bannerView];
    CSADRequest *csRequest = [CSADRequest requestWithRequestInterval:15 andDisplayTime:15];
    csRequest.placementID = placementId;
    [self.bannerView loadRequest:csRequest];
    // 动画
    self.bannerView.center = posFrom;
    [UIView animateWithDuration:0.5 animations:^{
        self.bannerView.center = posTo;
    }];
}
- (void)removeBannerWithAnimationDirection:(BannerMoveDirection)direction
{
    UIView *rootView = self.bannerView.superview;
    CGPoint posFrom = self.bannerView.center, posTo = CGPointZero;
    // Banner动画方向
    switch (direction) {
        case BannerMoveDirection_Null:
        {
            posTo = posFrom;
        }
            break;
        case BannerMoveDirection_Up:
        {
            posTo = CGPointMake(posFrom.x, -self.bannerView.bounds.size.height/2);
        }
            break;
        case BannerMoveDirection_Down:
        {
            posTo = CGPointMake(posFrom.x, rootView.bounds.size.height+self.bannerView.bounds.size.height/2);
        }
            break;
        case BannerMoveDirection_Left:
        {
            posTo = CGPointMake(-self.bannerView.bounds.size.width/2, posFrom.y);
        }
            break;
        case BannerMoveDirection_Right:
        {
            posTo = CGPointMake(rootView.bounds.size.width+self.bannerView.bounds.size.width/2, posFrom.y);
        }
            break;
        default:
            break;
    }
    // 动画
    [UIView animateWithDuration:0.5 animations:^{
        self.bannerView.center = posTo;
    } completion:^(BOOL finished) {
        [self.bannerView removeFromSuperview];
        self.bannerView = nil;
    }];
}


#pragma mark - CSBannerViewDelegate


#pragma mark - CSInterstitialDelegate

// 插屏广告加载错误
- (void)csInterstitial:(CSInterstitial *)csInterstitial
loadAdFailureWithError:(CSError *)csError
{
    NSLog(@"%@", csError);
}

// 插屏广告关闭完成
- (void)csInterstitialDidDismissScreen:(CSInterstitial *)csInterstitial
{
    if (ChanceAdWrapper::sharedWrapper()->m_delegate != NULL) {
        ChanceAdWrapper::sharedWrapper()->m_delegate->chanceAdCloseInterstitialFinished();
    }
}


#pragma mark - CSVideoADDelegate

// 视频广告播放完成（广告不会自动关闭）（replay为YES表示重播）
- (void)csVideoAD:(CSVideoAD *)csVideoAD playVideoFinished:(BOOL)replay
{
    if (!replay) {
        if (ChanceAdWrapper::sharedWrapper()->m_delegate != NULL) {
            ChanceAdWrapper::sharedWrapper()->m_delegate->chanceAdPlayVideoFinished();
        }
    }
}

// 视频广告播放过程中点击了下载按钮（replay为YES表示重播）
- (void)csVideoAD:(CSVideoAD *)csVideoAD clickDownload:(BOOL)replay
{
    if (ChanceAdWrapper::sharedWrapper()->m_delegate != NULL) {
        ChanceAdWrapper::sharedWrapper()->m_delegate->chanceAdClickDownloadInVideo();
    }
}

@end


ChanceAdWrapper* ChanceAdWrapper::s_sharedInstance = NULL;
ChanceAdWrapper* ChanceAdWrapper::sharedWrapper()
{
    if (ChanceAdWrapper::s_sharedInstance == NULL)
    {
        ChanceAdWrapper::s_sharedInstance = new ChanceAdWrapper();
        s_sharedInstance->m_delegate = NULL;
    }
    return ChanceAdWrapper::s_sharedInstance;
}
void ChanceAdWrapper::setChanceAdDelegate(ChanceAdDelegate *delegate)
{
    m_delegate = delegate;
}
void ChanceAdWrapper::startSession(const char* publisherId)
{
    [ChanceAd startSession:[NSString stringWithUTF8String:publisherId]];
}
void ChanceAdWrapper::showBanner(const char *placeId, BannerPosition position, BannerMoveDirection direction)
{
    NSString *strPlaceId = [NSString stringWithUTF8String:placeId];
    [[AdManager sharedInstance] showBannerWithPlacementId:strPlaceId position:position andAnimationDirection:direction];
}
void ChanceAdWrapper::removeBanner(BannerMoveDirection direction)
{
    [[AdManager sharedInstance] removeBannerWithAnimationDirection:direction];
}
void ChanceAdWrapper::loadInterstitial(const char *placeId)
{
    [CSInterstitial sharedInterstitial].delegate = [AdManager sharedInstance];
    [CSInterstitial sharedInterstitial].placementID = [NSString stringWithUTF8String:placeId];
    [[CSInterstitial sharedInterstitial] loadInterstitial];
}
void ChanceAdWrapper::showInterstitial(const char *placeId)
{
    [CSInterstitial sharedInterstitial].delegate = [AdManager sharedInstance];
    [CSInterstitial sharedInterstitial].placementID = [NSString stringWithUTF8String:placeId];
    [[CSInterstitial sharedInterstitial] showInterstitial];
}
void ChanceAdWrapper::showVideoAd(const char *placeId, bool portrait)
{
    [CSVideoAD sharedInstance].delegate = [AdManager sharedInstance];
    [CSVideoAD sharedInstance].placementID = [NSString stringWithUTF8String:placeId];
    [[CSVideoAD sharedInstance] showVideoADWithOrientation:portrait];
}
