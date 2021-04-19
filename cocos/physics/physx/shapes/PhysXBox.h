
#pragma once

#include "PhysXShape.h"

using namespace physx;

namespace cc {
namespace physics {

class PhysXBox final : public PhysXShape, public IBoxShape {
public:
    PhysXBox();
    virtual ~PhysXBox();
    virtual void setSize(float x, float y, float z) override;
    virtual void onComponentSet() override;
    virtual void updateScale() override;

private:
    PxVec3 mSize;
    void updateGeometry();
};

} // namespace physics
} // namespace cc
