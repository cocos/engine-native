//
//  CocosAds-android.cpp
//  CocosAds
//
//  Created by Jacky on 16/2/15.
//
//

#include "CocosAds.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <cocos2d.h>
#define CLASS_NAME "com/cocos/ads/helper/CocosAdsHelper"

using namespace cocos2d;
using namespace std;

#pragma mark - CocosAds

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
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showBanner", "(Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jstring stringArg1 = t.env->NewStringUTF(placementID);
        jstring stringArg2 = t.env->NewStringUTF(position);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1, stringArg2);
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(stringArg1);
    }
}

void CocosAds::hideBanner()
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "hideBanner", "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
