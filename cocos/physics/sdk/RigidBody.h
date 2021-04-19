
#pragma once

#include "../spec/IBody.h"
#include "base/Macros.h"
#include <memory>

namespace cc {
namespace physics {
class CC_DLL RigidBody final : public IRigidBody {
public:
    RigidBody();
    ~RigidBody() override;
    CC_INLINE uintptr_t getImpl() override { return _impl->getImpl(); };
    CC_INLINE uint getNodeHandle() override { return _impl->getNodeHandle(); }
    void initialize(uint h, ERigidBodyType t, uint32_t g) override;
    void onEnable() override;
    void onDisable() override;
    void onDestroy() override;
    bool isAwake() override;
    bool isSleepy() override;
    bool isSleeping() override;
    void setType(ERigidBodyType v) override;
    void setMass(float v) override;
    void setLinearDamping(float v) override;
    void setAngularDamping(float v) override;
    void useGravity(bool v) override;
    void setLinearFactor(float x, float y, float z) override;
    void setAngularFactor(float x, float y, float z) override;
    void setAllowSleep(bool v) override;
    void wakeUp() override;
    void sleep() override;
    void clearState() override;
    void clearForces() override;
    void clearVelocity() override;
    void setSleepThreshold(float v) override;
    float getSleepThreshold() override;
    cc::Vec3 getLinearVelocity() override;
    void setLinearVelocity(float x, float y, float z) override;
    cc::Vec3 getAngularVelocity() override;
    void setAngularVelocity(float x, float y, float z) override;
    void applyForce(float x, float y, float z, float rx, float ry, float rz) override;
    void applyLocalForce(float x, float y, float z, float rx, float ry, float rz) override;
    void applyImpulse(float x, float y, float z, float rx, float ry, float rz) override;
    void applyLocalImpulse(float x, float y, float z, float rx, float ry, float rz) override;
    void applyTorque(float x, float y, float z) override;
    void applyLocalTorque(float x, float y, float z) override;
    uint32_t getGroup() override;
    void setGroup(uint32_t g) override;
    uint32_t getMask() override;
    void setMask(uint32_t m) override;

private:
    std::unique_ptr<IRigidBody> _impl;
};
} // namespace physics
} // namespace cc
