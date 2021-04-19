
#pragma once

#include "ILifecycle.h"
#include "math/Vec3.h"

namespace cc {
namespace physics {

enum class ERigidBodyType : uint8_t {
    DYNAMIC = 1,
    STATIC = 2,
    KINEMATIC = 4,
};

class IRigidBody : public ILifecycle {
public:
    virtual ~IRigidBody(){};
    virtual void initialize(const uint &h, const ERigidBodyType &t, const uint32_t &g) = 0;
    virtual bool isAwake() = 0;
    virtual bool isSleepy() = 0;
    virtual bool isSleeping() = 0;
    virtual void setType(ERigidBodyType v) = 0;
    virtual void setMass(float v) = 0;
    virtual void setLinearDamping(float v) = 0;
    virtual void setAngularDamping(float v) = 0;
    virtual void useGravity(bool v) = 0;
    virtual void setLinearFactor(float x, float y, float z) = 0;
    virtual void setAngularFactor(float x, float y, float z) = 0;
    virtual void setAllowSleep(bool v) = 0;
    virtual void wakeUp() = 0;
    virtual void sleep() = 0;
    virtual void clearState() = 0;
    virtual void clearForces() = 0;
    virtual void clearVelocity() = 0;
    virtual void setSleepThreshold(float v) = 0;
    virtual float getSleepThreshold() = 0;
    virtual cc::Vec3 getLinearVelocity() = 0;
    virtual void setLinearVelocity(float x, float y, float z) = 0;
    virtual cc::Vec3 getAngularVelocity() = 0;
    virtual void setAngularVelocity(float x, float y, float z) = 0;
    virtual void applyForce(float x, float y, float z, float rx, float ry, float rz) = 0;
    virtual void applyLocalForce(float x, float y, float z, float rx, float ry, float rz) = 0;
    virtual void applyImpulse(float x, float y, float z, float rx, float ry, float rz) = 0;
    virtual void applyLocalImpulse(float x, float y, float z, float rx, float ry, float rz) = 0;
    virtual void applyTorque(float x, float y, float z) = 0;
    virtual void applyLocalTorque(float x, float y, float z) = 0;
    virtual uint32_t getGroup() = 0;
    virtual void setGroup(uint32_t g) = 0;
    virtual uint32_t getMask() = 0;
    virtual void setMask(uint32_t m) = 0;
};
} // namespace physics
} // namespace cc
