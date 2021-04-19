
#pragma once

#include "PhysXShape.h"

using namespace physx;

namespace cc {
namespace physics {

class PhysXSphere final : public PhysXShape, public ISphereShape {
public:
    PhysXSphere();
    virtual ~PhysXSphere();
    virtual void setRadius(float r) override;
    virtual void onComponentSet() override;
    virtual void updateScale() override;

private:
    float mRadius;
    void updateGeometry();    
};

} // namespace physics
} // namespace cc
