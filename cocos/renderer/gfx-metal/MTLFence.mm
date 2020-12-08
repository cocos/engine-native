#include "MTLStd.h"

#include "MTLDevice.h"
#include "MTLFence.h"

namespace cc {
namespace gfx {

CCMTLFence::CCMTLFence(Device *device)
: Fence(device),
  _semaphore(dispatch_semaphore_create(1)) {
}

CCMTLFence::~CCMTLFence() {
    destroy();
}

bool CCMTLFence::initialize(const FenceInfo &info) {
    // TODO

    return true;
}

void CCMTLFence::destroy() {
    dispatch_semaphore_signal(_semaphore);
}

void CCMTLFence::signal() {
    dispatch_semaphore_signal(_semaphore);
}

void CCMTLFence::wait() {
    dispatch_semaphore_wait(_semaphore, DISPATCH_TIME_FOREVER);
}

void CCMTLFence::reset() {
    dispatch_semaphore_signal(_semaphore);
}

} // namespace gfx
} // namespace cc
