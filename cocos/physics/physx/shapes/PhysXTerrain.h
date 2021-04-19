
#pragma once

#include "physics/physx/shapes/PhysXShape.h"

namespace cc {
namespace physics {

class PhysXTerrain final : public PhysXShape, public ITerrainShape {
public:
    PhysXTerrain();
    ~PhysXTerrain() override = default;
    void setTerrain(uintptr_t handle, float rs, float cs, float hs) override;
    void updateScale() override;
    void updateCenter() override;

private:
    physx::PxHeightField *_mTerrain;
    float                 _mRowScale;
    float                 _mColScale;
    float                 _mHeightScale;
    void          onComponentSet() override;
};

} // namespace physics
} // namespace cc
