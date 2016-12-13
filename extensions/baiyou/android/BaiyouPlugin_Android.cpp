//
//  ProjectManifestReader_Apple.cpp
//  cocos2d_libs
//
//  Created by gumin on 2016/11/22.
//
//

#include "BaiyouPlugin_Android.h"
#include "platform/android/jni/JniHelper.h"

#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, "baiyou BaiyouPlugin" ,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, "baiyou BaiyouPlugin", __VA_ARGS__)

namespace baiyou {
    
    BaiyouPlugin_Android::~BaiyouPlugin_Android(){
        
    }
    
    BaiyouPlugin* BaiyouPlugin::getInstance(){
        if (s_sharedBaiyouPlugin == nullptr)
        {
            s_sharedBaiyouPlugin = new (std::nothrow) BaiyouPlugin_Android();
            if(!s_sharedBaiyouPlugin->init())
            {
                delete s_sharedBaiyouPlugin;
                s_sharedBaiyouPlugin = nullptr;
                LOGD("Init not succ");
            }
        }
        return s_sharedBaiyouPlugin;
    }
    
    bool BaiyouPlugin_Android::init(){
        return true;
    }
    std::string BaiyouPlugin_Android::getProperty(const std::string& key) const{
        return cocos2d::JniHelper::callStaticStringMethod("org/baiyou/BaiyouPlugin", "getProperty",key);
    }
}
