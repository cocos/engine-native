
#pragma once

#include "../spec/IBody.h"
#include "./PhysXInc.h"
#include "base/Macros.h"
#include "PhysXSharedBody.h"

using namespace physx;

namespace cc {
namespace physics {

class PhysXRigidBody final : public IRigidBody {
public:
    PhysXRigidBody();
    virtual ~PhysXRigidBody();
    CC_INLINE const bool isEnabled() const { return mEnabled; }
    CC_INLINE const PhysXSharedBody &getSharedBody() const { return *mSharedBody; }
    CC_INLINE PhysXSharedBody &getSharedBody() { return *mSharedBody; }
    virtual CC_INLINE const intptr_t getImpl() override { return (intptr_t)this; }
    virtual CC_INLINE const uint getNodeHandle() override { return mSharedBody->getNodeHandle(); }
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
    virtual uint32_t getMask() override;
    virtual void setGroup(uint32_t g) override;
    virtual void setMask(uint32_t m) override;
    CC_INLINE const uint32_t getInitialGroup() const { return mGroup; }

protected:
    // PhysXWorld* mWrappedWorld;
    PhysXSharedBody *mSharedBody;
    uint32_t mGroup;
    bool mEnabled;
};

} // namespace physics
} // namespace cc