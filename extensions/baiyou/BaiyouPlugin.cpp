//
//  ProjectManifestReader.cpp
//  cocos2d_libs
//
//  Created by gumin on 2016/11/22.
//
//

#include "BaiyouPlugin.h"

namespace baiyou {
    BaiyouPlugin* BaiyouPlugin::s_sharedBaiyouPlugin = nullptr;
    
    BaiyouPlugin::~BaiyouPlugin(){
        
    }
    std::string BaiyouPlugin::getProperty(const std::string& key) const{
        return "";
    }
    bool BaiyouPlugin::init(){
        return true;
    }
    
}
