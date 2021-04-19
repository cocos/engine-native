
#pragma once

#include "PhysXShape.h"

namespace cc {
namespace physics {

class PhysXCapsule final : public PhysXShape, public ICapsuleShape {
public:
    PhysXCapsule();
    ~PhysXCapsule() override = default;
    void setRadius(float r) override;
    void setCylinderHeight(float v) override;
    void setDirection(EAxisDirection v) override;
    void updateScale() override;

private:
    float _mRadius;
    float _mCylinderHeight;
    EAxisDirection _mDirection;
    void updateGeometry();
    void onComponentSet() override;
};

} // namespace physics
} // namespace cc
