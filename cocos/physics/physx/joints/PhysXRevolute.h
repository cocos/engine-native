
#pragma once

#include "physics/physx/joints/PhysXJoint.h"

namespace cc {
namespace physics {

class PhysXRevolute final : public PhysXJoint, public IRevoluteJoint {
public:
    PhysXRevolute();
    ~PhysXRevolute() override = default;
    void setPivotA(float x, float y, float z) override;
    void setPivotB(float x, float y, float z) override;
    void setAxis(float x, float y, float z) override;
    void updateScale0() override;
    void updateScale1() override;

private:
    void onComponentSet() override;
    void updatePose();
    physx::PxVec3 _mPivotA;
    physx::PxVec3 _mPivotB;
    physx::PxVec3 _mAxis;
};

} // namespace physics
} // namespace cc
