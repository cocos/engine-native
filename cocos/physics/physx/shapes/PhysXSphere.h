
#pragma once

#include "PhysXShape.h"

namespace cc {
namespace physics {

class PhysXSphere final : public PhysXShape, public ISphereShape {
public:
    PhysXSphere();
    ~PhysXSphere() override = default;
    void setRadius(float r) override;
    void updateScale() override;

private:
    float _mRadius;
    void updateGeometry();
    void onComponentSet() override;
};

} // namespace physics
} // namespace cc
