#include "MTLStd.h"
#include "MTLTexture.h"
#include "MTLUtils.h"
#include "MTLDevice.h"

NS_CC_BEGIN

CCMTLTexture::CCMTLTexture(GFXDevice* device) : GFXTexture(device) {}
CCMTLTexture::~CCMTLTexture() { Destroy(); }

bool CCMTLTexture::Initialize(const GFXTextureInfo& info)
{
    type_ = info.type;
    usage_ = info.usage;
    format_ = info.format;
    width_ = info.width;
    height_ = info.height;
    depth_ = info.depth;
    array_layer_ = info.array_layer;
    mip_level_ = info.mip_level;
    samples_ = info.samples;
    flags_ = info.flags;
    size_ = GFXFormatSize(format_, width_, height_, depth_);
    
    if (flags_ & GFXTextureFlags::BAKUP_BUFFER)
    {
        buffer_ = (uint8_t*)CC_MALLOC(size_);
        device_->mem_status().texture_size += size_;
    }
    
    MTLTextureDescriptor* descriptor = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:mu::toMTLPixelFormat(format_)
                                                                                          width:width_
                                                                                         height:height_
                                                                                      mipmapped:flags_ & GFXTextureFlags::GEN_MIPMAP];
    descriptor.usage = mu::toMTLTextureUsage(usage_);
    descriptor.textureType = mu::toMTLTextureType(type_, array_layer_, flags_ & GFXTextureFlags::CUBEMAP);
    descriptor.sampleCount = mu::toMTLSampleCount(samples_);
    descriptor.mipmapLevelCount = mip_level_;
    descriptor.arrayLength = array_layer_;
    
#if (CC_PLATFORM == CC_PLATFORM_MAC_OSX)
    //FIXME: is it correct here for performace optimization?
    // Should change to MTLStorageModeManaged if texture usage is GFXTextureFlags::BAKUP_BUFFER?
    if (usage_ == GFXTextureUsage::COLOR_ATTACHMENT ||
        usage_ == GFXTextureUsage::DEPTH_STENCIL_ATTACHMENT ||
        usage_ == GFXTextureUsage::INPUT_ATTACHMENT ||
        usage_ == GFXTextureUsage::TRANSIENT_ATTACHMENT)
    {
        descriptor.storageMode = MTLStorageModePrivate;
    }
#endif
    
    id<MTLDevice> mtlDevice = id<MTLDevice>(static_cast<CCMTLDevice*>(device_)->getMTLDevice() );
    _mtlTexture = [mtlDevice newTextureWithDescriptor:descriptor];
    
    if (_mtlTexture)
        device_->mem_status().texture_size += size_;
    
    return _mtlTexture != nil;
}

void CCMTLTexture::Destroy()
{
    if (buffer_)
    {
        CC_FREE(buffer_);
        device_->mem_status().texture_size -= size_;
        buffer_ = nullptr;
    }
    
    if (_mtlTexture)
    {
        [_mtlTexture release];
        _mtlTexture = nil;
    }
}

void CCMTLTexture::Resize(uint width, uint height)
{
    //TODO
}

NS_CC_END
