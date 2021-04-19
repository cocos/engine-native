
#pragma once

#include "ILifecycle.h"
#include "renderer/pipeline/helper/SharedMemory.h"
#include <stdint.h>

namespace cc {
namespace physics {

class IBaseJoint : virtual public ILifecycle {
public:
    virtual ~IBaseJoint(){};
    virtual void initialize(const uint h) = 0;
    virtual const intptr_t getImpl() = 0;
    virtual void setEnableCollision(const bool v) = 0;
    virtual void setConnectedBody(const uint v) = 0;
};

class IDistanceJoint : virtual public IBaseJoint {
public:
    virtual ~IDistanceJoint(){};
    virtual void setPivotA(float x, float y, float z) = 0;
    virtual void setPivotB(float x, float y, float z) = 0;
};

class IRevoluteJoint : virtual public IBaseJoint {
public:
    virtual ~IRevoluteJoint(){};
    virtual void setPivotA(float x, float y, float z) = 0;
    virtual void setPivotB(float x, float y, float z) = 0;
    virtual void setAxis(float x, float y, float z) = 0;
};

} // namespace physics
} // namespace cc