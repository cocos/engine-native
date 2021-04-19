
#pragma once

#include "physics/physx/shapes/PhysXShape.h"

namespace cc {
namespace physics {

class PhysXBox final : public PhysXShape, public IBoxShape {
public:
    PhysXBox();
    ~PhysXBox() override = default;
    void setSize(float x, float y, float z) override;
    void updateScale() override;

private:
    physx::PxVec3 _mHalfExtents;
    void updateGeometry();
    void onComponentSet() override;
};

} // namespace physics
} // namespace cc
