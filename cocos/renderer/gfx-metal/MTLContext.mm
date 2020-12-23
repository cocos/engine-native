#include "MTLStd.h"

#include "MTLContext.h"
#include "MTLDevice.h"

#import <MetalKit/MTKView.h>

namespace cc {
namespace gfx {

namespace {
Format toFormat(MTLPixelFormat format) {
    switch (format) {
        case MTLPixelFormatRGBA8Unorm: return Format::RGBA8;
        case MTLPixelFormatBGRA8Unorm: return Format::BGRA8;
#if (CC_PLATFORM == CC_PLATFORM_MAC_OSX)
        case MTLPixelFormatDepth24Unorm_Stencil8: return Format::D24S8;
#endif
        case MTLPixelFormatDepth32Float_Stencil8: return Format::D32F_S8;
        default:
            CC_LOG_ERROR("invalid MTLPixelFormat.");
            return Format::UNKNOWN;
    }
}
}

CCMTLContext::CCMTLContext(Device *device)
: Context(device) {
}

bool CCMTLContext::initialize(const ContextInfo &info) {
    _vsyncMode = info.vsyncMode;
    _windowHandle = info.windowHandle;
    
    CCMTLDevice *device = (CCMTLDevice *)_device;
    CAMetalLayer *layer = (CAMetalLayer *)device->getMTLLayer();
    _colorFmt = toFormat(layer.pixelFormat);
    id<MTLTexture> dssTex = (id<MTLTexture>)device->getDSSTexture();
    _depthStencilFmt = toFormat(dssTex.pixelFormat);

    return true;
}

} // namespace gfx
} // namespace cc
