#include "MTLStd.h"
#include "MTLTexture.h"
#include "MTLUtils.h"
#include "MTLDevice.h"

NS_CC_BEGIN

namespace
{
    uint8_t* convertRGB8ToRGBA8(uint8_t* source, uint length)
    {
        uint finalLength = length * 4;
        uint8* out = (uint8*)CC_MALLOC(finalLength);
        if (!out)
        {
            CC_LOG_WARNING("Failed to alloc memory in convertRGB8ToRGBA8().");
            return source;
        }
        
        uint8_t* src = source;
        uint8_t* dst = out;
        for (uint i = 0; i < length; ++i)
        {
            *dst++ = *src++;
            *dst++ = *src++;
            *dst++ = *src++;
            *dst++ = 255;
        }
        
        return out;
    }
    
    uint8_t* convertData(uint8_t* source, uint length, GFXFormat type)
    {
        switch (type) {
            case GFXFormat::RGB8: return convertRGB8ToRGBA8(source, length);
            default: return source;
        }
    }
}

CCMTLTexture::CCMTLTexture(GFXDevice* device) : GFXTexture(device) {}
CCMTLTexture::~CCMTLTexture() { destroy(); }

bool CCMTLTexture::initialize(const GFXTextureInfo& info)
{
    type_ = info.type;
    _usage = info.usage;
    format_ = info.format;
    _width = info.width;
    _height = info.height;
    depth_ = info.depth;
    array_layer_ = info.array_layer;
    mip_level_ = info.mip_level;
    samples_ = info.samples;
    _flags = info.flags;
    _size = GFXFormatSize(format_, _width, _height, depth_);
    
    if (_flags & GFXTextureFlags::BAKUP_BUFFER)
    {
        _buffer = (uint8_t*)CC_MALLOC(_size);
        _device->memoryStatus().texture_size += _size;
    }
    
    _convertedFormat = mu::convertGFXPixelFormat(format_);
    MTLPixelFormat mtlFormat = mu::toMTLPixelFormat(_convertedFormat);
    if (mtlFormat == MTLPixelFormatInvalid)
        return false;
    
    MTLTextureDescriptor* descriptor = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:mtlFormat
                                                                                          width:_width
                                                                                         height:_height
                                                                                      mipmapped:_flags & GFXTextureFlags::GEN_MIPMAP];
    descriptor.usage = mu::toMTLTextureUsage(_usage);
    descriptor.textureType = mu::toMTLTextureType(type_, array_layer_, _flags & GFXTextureFlags::CUBEMAP);
    descriptor.sampleCount = mu::toMTLSampleCount(samples_);
    descriptor.mipmapLevelCount = mip_level_;
    descriptor.arrayLength = array_layer_;
    
#if (CC_PLATFORM == CC_PLATFORM_MAC_OSX)
    //FIXME: is it correct here for performace optimization?
    // Should change to MTLStorageModeManaged if texture usage is GFXTextureFlags::BAKUP_BUFFER?
    if (_usage == GFXTextureUsage::COLOR_ATTACHMENT ||
        _usage == GFXTextureUsage::DEPTH_STENCIL_ATTACHMENT ||
        _usage == GFXTextureUsage::INPUT_ATTACHMENT ||
        _usage == GFXTextureUsage::TRANSIENT_ATTACHMENT)
    {
        descriptor.storageMode = MTLStorageModePrivate;
    }
#endif
    
    id<MTLDevice> mtlDevice = id<MTLDevice>(static_cast<CCMTLDevice*>(_device)->getMTLDevice() );
    _mtlTexture = [mtlDevice newTextureWithDescriptor:descriptor];
    
    if (_mtlTexture)
        _device->memoryStatus().texture_size += _size;
    
    return _mtlTexture != nil;
}

void CCMTLTexture::destroy()
{
    if (_buffer)
    {
        CC_FREE(_buffer);
        _device->memoryStatus().texture_size -= _size;
        _buffer = nullptr;
    }
    
    if (_mtlTexture)
    {
        [_mtlTexture release];
        _mtlTexture = nil;
    }
}

void CCMTLTexture::resize(uint width, uint height)
{
    //TODO
}

void CCMTLTexture::update(uint8_t* data, const GFXBufferTextureCopy& region)
{
    if (!_mtlTexture)
        return;
    
    uint8_t* convertedData = convertData(data,
                                         region.tex_extent.width * region.tex_extent.height,
                                         format_);
    
    MTLRegion mtlRegion =
    {
        {(uint)region.tex_offset.x, (uint)region.tex_offset.y, (uint)region.tex_offset.z},
        {region.tex_extent.width, region.tex_extent.height, region.tex_extent.depth}
    };
    
    [_mtlTexture replaceRegion:mtlRegion
                   mipmapLevel:region.tex_subres.base_mip_level
                     withBytes:convertedData
                   bytesPerRow:GFX_FORMAT_INFOS[(uint)_convertedFormat].size * region.tex_extent.width];
    
    if (convertedData != data)
        CC_FREE(convertedData);
}

NS_CC_END
