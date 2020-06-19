#include "CoreStd.h"
#include "GFXCommandBuffer.h"

namespace cc {
namespace gfx {

CommandBuffer::CommandBuffer(Device *device)
: GFXObject(GFXObjectType::COMMAND_BUFFER), _device(device) {
}

CommandBuffer::~CommandBuffer() {
}

} // namespace gfx
} // namespace cc
