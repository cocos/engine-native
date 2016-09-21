//
//  CocosAds.h
//  CocosAds
//
//  Created by Jacky on 16/2/15.
//
//

#ifndef CocosAds_h
#define CocosAds_h

class CocosAds
{
public:
    //获取CocosAds单例
    static CocosAds* getInstance();
    
    //Banner 广告
    void showBanner(const char* placementID = "");
    
    void hideBanner();
    
private:
    
    CocosAds();
    
    static CocosAds* _instance;
};

#endif /* CocosAds_h */
