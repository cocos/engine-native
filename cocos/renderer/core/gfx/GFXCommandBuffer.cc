#include "CoreStd.h"
#include "GFXCommandBuffer.h"

namespace cc {
namespace gfx {

GFXCommandBuffer::GFXCommandBuffer(Device *device)
: GFXObject(GFXObjectType::COMMAND_BUFFER), _device(device) {
}

GFXCommandBuffer::~GFXCommandBuffer() {
}

} // namespace gfx
} // namespace cc
