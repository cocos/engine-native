#include "CoreStd.h"
#include "GFXFramebuffer.h"

namespace cc {
namespace gfx {

GFXFramebuffer::GFXFramebuffer(Device *device)
: GFXObject(GFXObjectType::FRAMEBUFFER), _device(device) {
}

GFXFramebuffer::~GFXFramebuffer() {
}

} // namespace gfx
} // namespace cc
