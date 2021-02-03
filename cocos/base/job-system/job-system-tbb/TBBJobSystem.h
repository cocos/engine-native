#pragma once

#include "tbb/global_control.h"
#include <thread>
#include <algorithm>

namespace cc {

class TBBJobGraph;

class TBBJobSystem final {
public:
    static TBBJobSystem *getInstance() {
        if (!_instance) {
            _instance = CC_NEW(TBBJobSystem);
        }
        return _instance;
    }

    static void destroyInstance() {
        CC_SAFE_DELETE(_instance);
    }

    TBBJobSystem() noexcept : TBBJobSystem(std::max(2u, std::thread::hardware_concurrency() - 2u)) {}
    TBBJobSystem(uint threadCount) noexcept;

    CC_INLINE uint threadCount() { return _threadCount; }

private:
    static TBBJobSystem *_instance;

    tbb::global_control _control;
    uint _threadCount = 0u;
};

} // namespace cc