
#pragma once

#include "base/TypeDef.h"
#include <stdint.h>

namespace cc {
namespace physics {
class ILifecycle {
public:
    virtual ~ILifecycle(){};
    virtual void initialize(const uint& handle) = 0;
    virtual void onEnable() = 0;
    virtual void onDisable() = 0;
    virtual void onDestroy() = 0;
};
} // namespace physics
} // namespace cc
