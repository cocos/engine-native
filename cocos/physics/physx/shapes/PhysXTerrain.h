
#pragma once

#include "PhysXShape.h"

using namespace physx;

namespace cc {
namespace physics {

class PhysXTerrain final : public PhysXShape, public ITerrainShape {
public:
    PhysXTerrain();
    virtual ~PhysXTerrain();
    virtual void setTerrain(intptr_t v, float rs, float cs, float hs) override;
    virtual void updateScale() override;
    virtual void updateCenter() override;

private:
    PxHeightField* mTerrain;
    float mRowScale;
    float mColScale;
    float mHeightScale;
    virtual void onComponentSet() override;
};

} // namespace physics
} // namespace cc
