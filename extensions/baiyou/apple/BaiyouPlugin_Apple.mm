//
//  ProjectManifestReader_Apple.cpp
//  cocos2d_libs
//
//  Created by gumin on 2016/11/22.
//
//

#include "BaiyouPlugin_Apple.h"
namespace baiyou {
    
    BaiyouPlugin_Apple::~BaiyouPlugin_Apple(){
        
    }
    
    BaiyouPlugin* BaiyouPlugin::getInstance(){
        if (s_sharedBaiyouPlugin == nullptr)
        {
            s_sharedBaiyouPlugin = new (std::nothrow) BaiyouPlugin_Apple();
            if(!s_sharedBaiyouPlugin->init())
            {
                delete s_sharedBaiyouPlugin;
                s_sharedBaiyouPlugin = nullptr;
                NSLog(@"cocos2dx ERROR: Could not init BaiyouPlugin");
            }
        }
        return s_sharedBaiyouPlugin;
    }
    
    bool BaiyouPlugin_Apple::init(){
        return true;
    }
    std::string BaiyouPlugin_Apple::getProperty(const std::string& key) const{
        NSString* str = [[NSBundle mainBundle] objectForInfoDictionaryKey:[NSString stringWithUTF8String:key.c_str()]];
        if (str == NULL){
            return "";
        }else{
            return std::string(str.UTF8String);
        }
    }
}
