
#pragma once

#include "physics/spec/ILifecycle.h"
#include "renderer/pipeline/helper/SharedMemory.h"
#include <cstdint>

namespace cc {
namespace physics {

class IBaseJoint : virtual public ILifecycle {
public:
    ~IBaseJoint() override = default;
    virtual void initialize(uint h) = 0;
    virtual uintptr_t getImpl() = 0;
    virtual void setEnableCollision(bool v) = 0;
    virtual void setConnectedBody(uint v) = 0;
};

class IDistanceJoint : virtual public IBaseJoint {
public:
    ~IDistanceJoint() override = default;
    virtual void setPivotA(float x, float y, float z) = 0;
    virtual void setPivotB(float x, float y, float z) = 0;
};

class IRevoluteJoint : virtual public IBaseJoint {
public:
    ~IRevoluteJoint() override = default;
    virtual void setPivotA(float x, float y, float z) = 0;
    virtual void setPivotB(float x, float y, float z) = 0;
    virtual void setAxis(float x, float y, float z) = 0;
};

} // namespace physics
} // namespace cc