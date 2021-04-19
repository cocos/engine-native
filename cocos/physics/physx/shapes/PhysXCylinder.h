
#pragma once

#include "PhysXShape.h"

namespace cc {
namespace physics {

class PhysXCylinder final : public PhysXShape, public ICylinderShape {
public:
    PhysXCylinder();
    ~PhysXCylinder() override = default;
    void setConvex(uintptr_t handle) override;
    void setCylinder(float r, float h, EAxisDirection d) override;
    void updateScale() override;

    struct Cylinder {
        float          radius;
        float          height;
        EAxisDirection direction;
    };

private:
    physx::PxConvexMesh *_mMesh;
    Cylinder             _mData;
    void                 updateGeometry();
    void         onComponentSet() override;
};

} // namespace physics
} // namespace cc
