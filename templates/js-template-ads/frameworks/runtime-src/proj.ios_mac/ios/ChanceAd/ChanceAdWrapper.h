//
//  ChanceAdWrapper.h
//  ChanceAdDemo
//
//  Created by Chance_yangjh on 16/8/29.
//
//


typedef enum {
    BannerPosition_LeftTop,
    BannerPosition_TopCenter,
    BannerPosition_RightTop,
    BannerPosition_LeftBottom,
    BannerPosition_BottomCenter,
    BannerPosition_RightBottom,
}BannerPosition;
typedef enum {
    BannerMoveDirection_Null,
    BannerMoveDirection_Up,
    BannerMoveDirection_Down,
    BannerMoveDirection_Left,
    BannerMoveDirection_Right,
}BannerMoveDirection;


class ChanceAdDelegate
{
public:
    // 插屏广告关闭完成
    virtual void chanceAdCloseInterstitialFinished() = 0;
    // 视频广告首播播放成功
    virtual void chanceAdPlayVideoFinished() = 0;
    // 点击视频广告中的下载按钮
    virtual void chanceAdClickDownloadInVideo() = 0;
};


class ChanceAdWrapper
{
public:
    static ChanceAdWrapper* sharedWrapper();
    void setChanceAdDelegate(ChanceAdDelegate *delegate);
    
    void startSession(const char* publisherId);
    void showBanner(const char *placeId, BannerPosition position, BannerMoveDirection direction);
    void removeBanner(BannerMoveDirection direction);
    void loadInterstitial(const char *placeId);
    void showInterstitial(const char *placeId);
    void showVideoAd(const char *placeId, bool portrait);
    
    ChanceAdDelegate *m_delegate;
private:
    static ChanceAdWrapper * s_sharedInstance;
};
