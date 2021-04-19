
#pragma once

#include "PhysXShape.h"

using namespace physx;

namespace cc {
namespace physics {

class PhysXPlane final : public PhysXShape, public IPlaneShape {
public:
    PhysXPlane();
    virtual ~PhysXPlane();
    virtual void setConstant(float v) override;
    virtual void setNormal(float x, float y, float z) override;
    virtual void updateScale() override;

private:
    PxVec3 mNormal;
    PxReal mConstant;
    void updateGeometry();
    virtual void updateCenter() override;
    virtual void onComponentSet() override;
};

} // namespace physics
} // namespace cc
