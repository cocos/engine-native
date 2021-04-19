
#pragma once

#include "physics/physx/shapes/PhysXShape.h"

namespace cc {
namespace physics {

class PhysXTrimesh final : public PhysXShape, public ITrimeshShape {
public:
    PhysXTrimesh();
    ~PhysXTrimesh() override = default;
    void setMesh(uintptr_t handle) override;
    void useConvex(bool v) override;
    void updateScale() override;

private:
    bool         _mConvex;
    uintptr_t    _mMeshHandle;
    void         updateGeometry();
    void onComponentSet() override;
};

} // namespace physics
} // namespace cc
