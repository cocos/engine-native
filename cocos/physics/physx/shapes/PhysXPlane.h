
#pragma once

#include "PhysXShape.h"

namespace cc {
namespace physics {

class PhysXPlane final : public PhysXShape, public IPlaneShape {
public:
    PhysXPlane();
    ~PhysXPlane() override = default;
    void setConstant(float x) override;
    void setNormal(float x, float y, float z) override;
    void updateScale() override;

private:
    physx::PxVec3 _mNormal;
    physx::PxReal _mConstant;
    void  updateCenter() override;
    void  onComponentSet() override;
};

} // namespace physics
} // namespace cc
