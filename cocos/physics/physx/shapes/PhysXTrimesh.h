
#pragma once

#include "PhysXShape.h"

using namespace physx;

namespace cc {
namespace physics {

class PhysXTrimesh final : public PhysXShape, public ITrimeshShape {
public:
    PhysXTrimesh();
    virtual ~PhysXTrimesh();
    virtual void setMesh(intptr_t v) override;
    virtual void useConvex(bool v) override;
    virtual void updateScale() override;

private:
    uint mMeshHandle;
    bool mConvex;
    void updateGeometry();
    virtual void onComponentSet() override;
};

} // namespace physics
} // namespace cc
