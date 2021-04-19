
#pragma once

#include "../spec/IBody.h"
#include "base/Macros.h"
#include <memory>

namespace cc {
namespace physics {
class CC_DLL RigidBody final : public IRigidBody {
public:
    RigidBody();
    virtual ~RigidBody();
    virtual CC_INLINE const intptr_t getImpl() override { return _impl->getImpl(); };
    virtual CC_INLINE const uint getNodeHandle() override { return _impl->getNodeHandle(); }
    virtual void initialize(const uint h, const ERigidBodyType t, const uint32_t g) override;
    virtual void onEnable() override;
    virtual void onDisable() override;
    virtual void onDestroy() override;
    virtual bool isAwake() override;
    virtual bool isSleepy() override;
    virtual bool isSleeping() override;
    virtual void setType(ERigidBodyType v) override;
    virtual void setMass(float v) override;
    virtual void setLinearDamping(float v) override;
    virtual void setAngularDamping(float v) override;
    virtual void useGravity(bool v) override;
    virtual void setLinearFactor(float x, float y, float z) override;
    virtual void setAngularFactor(float x, float y, float z) override;
    virtual void setAllowSleep(bool v) override;
    virtual void wakeUp() override;
    virtual void sleep() override;
    virtual void clearState() override;
    virtual void clearForces() override;
    virtual void clearVelocity() override;
    virtual void setSleepThreshold(float v) override;
    virtual float getSleepThreshold() override;
    virtual cc::Vec3 getLinearVelocity() override;
    virtual void setLinearVelocity(float x, float y, float z) override;
    virtual cc::Vec3 getAngularVelocity() override;
    virtual void setAngularVelocity(float x, float y, float z) override;
    virtual void applyForce(float x, float y, float z, float rx, float ry, float rz) override;
    virtual void applyLocalForce(float x, float y, float z, float rx, float ry, float rz) override;
    virtual void applyImpulse(float x, float y, float z, float rx, float ry, float rz) override;
    virtual void applyLocalImpulse(float x, float y, float z, float rx, float ry, float rz) override;
    virtual void applyTorque(float x, float y, float z) override;
    virtual void applyLocalTorque(float x, float y, float z) override;
    virtual uint32_t getGroup() override;
    virtual void setGroup(uint32_t g) override;
    virtual uint32_t getMask() override;
    virtual void setMask(uint32_t m) override;

private:
    std::unique_ptr<IRigidBody> _impl;
};
} // namespace physics
} // namespace cc
