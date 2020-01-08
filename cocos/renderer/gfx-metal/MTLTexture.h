#pragma once

#import <Metal/MTLTexture.h>

NS_CC_BEGIN

class CCMTLTexture : public GFXTexture
{
public:
    CCMTLTexture(GFXDevice* device);
    ~CCMTLTexture();
    
    virtual bool Initialize(const GFXTextureInfo& info) override;
    virtual void Destroy() override;
    virtual void Resize(uint width, uint height) override;
    
    CC_INLINE id<MTLTexture> getMTLTexture() const { return _mtlTexture; }
    
private:
    id<MTLTexture> _mtlTexture = nil;
};

NS_CC_END
