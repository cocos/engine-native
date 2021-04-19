
#pragma once

#include "PhysXShape.h"

using namespace physx;

namespace cc {
namespace physics {

class PhysXCylinder final : public PhysXShape, public ICylinderShape {
public:
    PhysXCylinder();
    virtual ~PhysXCylinder(){};
    virtual void setConvex(intptr_t v) override;
    virtual void setCylinder(float r, float h, EAxisDirection d) override;
    virtual void updateScale() override;

    struct Cylinder {
        float radius;
        float height;
        EAxisDirection direction;
    };

private:
    PxConvexMesh *mMesh;
    Cylinder mData;
    void updateGeometry();
    virtual void onComponentSet() override;
};

} // namespace physics
} // namespace cc
