#include "CoreStd.h"
#include "GFXFence.h"

namespace cc {
namespace gfx {

Fence::Fence(Device *device)
: GFXObject(GFXObjectType::FENCE), _device(device) {
}

Fence::~Fence() {
}

} // namespace gfx
} // namespace cc
