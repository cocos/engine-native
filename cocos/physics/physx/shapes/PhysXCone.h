
#pragma once

#include "physics/physx/shapes/PhysXShape.h"

namespace cc {
namespace physics {

class PhysXCone final : public PhysXShape, public IConeShape {
public:
    PhysXCone();
    ~PhysXCone() override = default;
    void setConvex(uintptr_t handle) override;
    void setCone(float r, float h, EAxisDirection d) override;
    void updateScale() override;

    struct Cone {
        float          radius;
        float          height;
        EAxisDirection direction;
    };

private:
    physx::PxConvexMesh *_mMesh;
    Cone                 _mData;
    void                 updateGeometry();
    void         onComponentSet() override;
};

} // namespace physics
} // namespace cc
