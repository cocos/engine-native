#include "CoreStd.h"
#include "GFXBuffer.h"

namespace cc {
namespace gfx {

Buffer::Buffer(Device *device)
: GFXObject(GFXObjectType::BUFFER), _device(device) {
}

Buffer::~Buffer() {
}

} // namespace gfx
} // namespace cc
