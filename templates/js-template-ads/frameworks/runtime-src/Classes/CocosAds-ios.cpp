//
//  CocosAds-android.cpp
//  CocosAds
//
//  Created by Jacky on 16/2/15.
//
//

#include "CocosAds.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <cocos2d.h>
#include "ChanceAdWrapper.h"

using namespace cocos2d;
using namespace std;

CocosAds* CocosAds::_instance = nullptr;

CocosAds::CocosAds()
{
}

CocosAds* CocosAds::getInstance()
{
    if(_instance == nullptr)
    {
        _instance = new CocosAds();
    }
    return _instance;
}

#pragma mark - Banner

void CocosAds::showBanner(const char* placementID, const char* position)
{
    if (strcmp(position, "LEFT_TOP") == 0) {
        ChanceAdWrapper::sharedWrapper()->showBanner(placementID, BannerPosition_LeftTop, BannerMoveDirection_Null);
    } else if (strcmp(position, "CENTER_TOP") == 0) {
        ChanceAdWrapper::sharedWrapper()->showBanner(placementID, BannerPosition_TopCenter, BannerMoveDirection_Null);
    } else if (strcmp(position, "RIGHT_TOP") == 0) {
        ChanceAdWrapper::sharedWrapper()->showBanner(placementID, BannerPosition_RightTop, BannerMoveDirection_Null);
    } else if (strcmp(position, "LEFT_BOTTOM") == 0) {
        ChanceAdWrapper::sharedWrapper()->showBanner(placementID, BannerPosition_LeftBottom, BannerMoveDirection_Null);
    } else if (strcmp(position, "CENTER_BOTTOM") == 0) {
        ChanceAdWrapper::sharedWrapper()->showBanner(placementID, BannerPosition_BottomCenter, BannerMoveDirection_Null);
    } else if (strcmp(position, "RIGHT_BOTTOM") == 0) {
        ChanceAdWrapper::sharedWrapper()->showBanner(placementID, BannerPosition_RightBottom, BannerMoveDirection_Null);
    }
}

void CocosAds::hideBanner()
{
    ChanceAdWrapper::sharedWrapper()->removeBanner(BannerMoveDirection_Null);
}

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS
