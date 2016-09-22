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

void CocosAds::showBanner(const char* placementID /*= ""*/)
{
    ChanceAdWrapper::sharedWrapper()->showBanner(placementID, BannerPosition_TopCenter, BannerMoveDirection_Null);
}

void CocosAds::hideBanner()
{
    ChanceAdWrapper::sharedWrapper()->removeBanner(BannerMoveDirection_Null);
}

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS