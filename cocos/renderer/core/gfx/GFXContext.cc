#include "CoreStd.h"
#include "GFXContext.h"

namespace cc {
namespace gfx {

GFXContext::GFXContext(Device *device)
: _device(device) {
}

GFXContext::~GFXContext() {
}

} // namespace gfx
} // namespace cc
