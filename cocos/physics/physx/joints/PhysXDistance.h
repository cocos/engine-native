
#pragma once

#include "PhysXJoint.h"

namespace cc {
namespace physics {

class PhysXDistance final : public PhysXJoint, public IDistanceJoint {
public:
    PhysXDistance();
    virtual ~PhysXDistance(){};
    virtual void setPivotA(float x, float y, float z) override;
    virtual void setPivotB(float x, float y, float z) override;
    virtual void updateScale0() override;
    virtual void updateScale1() override;

private:
    virtual void onComponentSet() override;
    void updatePose();
    PxVec3 mPivotA;
    PxVec3 mPivotB;
};

} // namespace physics
} // namespace cc
