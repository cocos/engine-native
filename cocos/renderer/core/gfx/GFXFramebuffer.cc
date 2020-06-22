#include "CoreStd.h"
#include "GFXFramebuffer.h"

namespace cc {
namespace gfx {

Framebuffer::Framebuffer(Device *device)
: GFXObject(GFXObjectType::FRAMEBUFFER), _device(device) {
}

Framebuffer::~Framebuffer() {
}

} // namespace gfx
} // namespace cc
