#include "CoreStd.h"
#include "GFXTexture.h"

namespace cc {
namespace gfx {

GFXTexture::GFXTexture(Device *device)
: GFXObject(GFXObjectType::TEXTURE), _device(device) {
}

GFXTexture::~GFXTexture() {
}

} // namespace gfx
} // namespace cc
