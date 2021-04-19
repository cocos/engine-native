
#pragma once

#include "PhysXShape.h"

using namespace physx;

namespace cc {
namespace physics {

class PhysXCapsule final : public PhysXShape, public ICapsuleShape {
public:
    PhysXCapsule();
    virtual ~PhysXCapsule(){};
    virtual void setRadius(float v) override;
    virtual void setCylinderHeight(float v) override;
    virtual void setDirection(EAxisDirection v) override;
    virtual void updateScale() override;

private:
    float mRadius;
    float mCylinderHeight;
    EAxisDirection mDirection;
    void updateGeometry();
    virtual void onComponentSet() override;
};

} // namespace physics
} // namespace cc
