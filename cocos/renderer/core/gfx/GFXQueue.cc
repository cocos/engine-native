#include "CoreStd.h"
#include "GFXQueue.h"

namespace cc {
namespace gfx {

Queue::Queue(Device *device)
: GFXObject(GFXObjectType::QUEUE), _device(device) {
}

Queue::~Queue() {
}

} // namespace gfx
} // namespace cc
