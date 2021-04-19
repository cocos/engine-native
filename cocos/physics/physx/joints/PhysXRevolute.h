
#pragma once

#include "PhysXJoint.h"

namespace cc {
namespace physics {

class PhysXRevolute final : public PhysXJoint, public IRevoluteJoint {
public:
    PhysXRevolute();
    virtual ~PhysXRevolute(){};
    virtual void setPivotA(float x, float y, float z) override;
    virtual void setPivotB(float x, float y, float z) override;
    virtual void setAxis(float x, float y, float z) override;
    virtual void updateScale0() override;
    virtual void updateScale1() override;

private:
    virtual void onComponentSet() override;
    void updatePose();
    PxVec3 mPivotA;
    PxVec3 mPivotB;
    PxVec3 mAxis;
};

} // namespace physics
} // namespace cc
