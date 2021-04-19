
#pragma once

#include "PhysXShape.h"

using namespace physx;

namespace cc {
namespace physics {

class PhysXCone final : public PhysXShape, public IConeShape {
public:
    PhysXCone();
    virtual ~PhysXCone(){};
    virtual void setConvex(intptr_t v) override;
    virtual void setCone(float r, float h, EAxisDirection d) override;
    virtual void updateScale() override;

    struct Cone {
        float radius;
        float height;
        EAxisDirection direction;
    };

private:
    PxConvexMesh *mMesh;
    Cone mData;
    void updateGeometry();
    virtual void onComponentSet() override;
};

} // namespace physics
} // namespace cc
