//
//  ProjectManifestReader_Apple.hpp
//  cocos2d_libs
//
//  Created by gumin on 2016/11/22.
//
//

#ifndef ProjectManifestReader_Apple_hpp
#define ProjectManifestReader_Apple_hpp

#include <stdio.h>
#include "../BaiyouPlugin.h"

namespace baiyou {
    class BaiyouPlugin_Android : public BaiyouPlugin{
        ~BaiyouPlugin_Android();
        std::string getProperty(const std::string& key) const;
        bool init();
    };
}

#endif /* ProjectManifestReader_Apple_hpp */
