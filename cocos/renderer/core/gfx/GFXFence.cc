#include "CoreStd.h"
#include "GFXFence.h"

namespace cc {
namespace gfx {

GFXFence::GFXFence(Device *device)
: GFXObject(GFXObjectType::FENCE), _device(device) {
}

GFXFence::~GFXFence() {
}

} // namespace gfx
} // namespace cc
