#include "CoreStd.h"
#include "GFXCommandAllocator.h"

namespace cc {
namespace gfx {

CommandAllocator::CommandAllocator(Device *device)
: GFXObject(GFXObjectType::COMMAND_ALLOCATOR), _device(device) {
}

CommandAllocator::~CommandAllocator() {
}

} // namespace gfx
} // namespace cc
