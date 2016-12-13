//
//  ProjectManifestReader.hpp
//  cocos2d_libs
//
//  Created by gumin on 2016/11/22.
//
//

#ifndef ProjectManifestReader_hpp
#define ProjectManifestReader_hpp

#include <stdio.h>
#include <string>

namespace baiyou {
    class BaiyouPlugin {
    public:
            virtual ~BaiyouPlugin();
            static BaiyouPlugin* getInstance();
            virtual std::string getProperty(const std::string& key) const;
            virtual bool init();
    protected:
        static BaiyouPlugin* s_sharedBaiyouPlugin;
    };
}

#endif /* ProjectManifestReader_hpp */
