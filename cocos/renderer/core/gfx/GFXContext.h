#ifndef CC_CORE_GFX_CONTEXT_H_
#define CC_CORE_GFX_CONTEXT_H_

#include "GFXDef.h"

namespace cc {
namespace gfx {

class CC_DLL Context : public Object {
public:
    Context(Device *device);
    virtual ~Context();

public:
    virtual bool initialize(const ContextInfo &info) = 0;
    virtual void destroy() = 0;
    virtual void present() = 0;

    CC_INLINE Device *getDevice() const { return _device; }
    CC_INLINE Context *getSharedContext() const { return _sharedContext; }
    CC_INLINE GFXVsyncMode getVsyncMode() const { return _vsyncMode; }
    CC_INLINE GFXFormat getColorFormat() const { return _colorFmt; }
    CC_INLINE GFXFormat getDepthStencilFormat() const { return _depthStencilFmt; }

protected:
    Device *_device = nullptr;
    uintptr_t _windowHandle = 0;
    Context *_sharedContext = nullptr;
    GFXVsyncMode _vsyncMode = GFXVsyncMode::OFF;
    GFXFormat _colorFmt = GFXFormat::UNKNOWN;
    GFXFormat _depthStencilFmt = GFXFormat::UNKNOWN;
};

} // namespace gfx
} // namespace cc

#endif // CC_CORE_GFX_CONTEXT_H_
