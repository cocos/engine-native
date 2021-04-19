#pragma once

#include "../../spec/IShape.h"
#include "base/Macros.h"
#include <PhysX/PxPhysicsAPI.h>

using namespace physx;

namespace cc {
namespace physics {
class PhysXSharedBody;

PxMaterial &getSharedMaterial();

template <typename T>
T &getPxGeometry() {
    static T geo;
    return geo;
}

class PhysXShape : virtual public IBaseShape {
    PX_NOCOPY(PhysXShape)
    PhysXShape() : mIndex(-1),
                   mFlag(0),
                   mCenter(PxIdentity){};

public:
    virtual ~PhysXShape(){};
    virtual intptr_t getImpl() override;
    virtual void initialize(const uint &handle) override;
    virtual void onEnable() override;
    virtual void onDisable() override;
    virtual void onDestroy() override;
    virtual void setMaterial(float f, float df, float r) override;
    virtual void setAsTrigger(bool v) override;
    virtual void setCenter(float x, float y, float z) override;
    virtual void setCollisionFilter(int g, int m) override;
    virtual cc::pipeline::AABB getAABB() override;
    virtual cc::pipeline::Sphere getBoundingSphere() override;
    virtual void updateEventListener(EShapeFilterFlag flag) override;
    virtual void onComponentSet() = 0;
    virtual void updateScale() = 0;
    CC_INLINE PxShape &getShape() const { return *mShape; }
    CC_INLINE PhysXSharedBody &getSharedBody() const { return *mSharedBody; }
    void updateFilterData(PxFilterData &data);

protected:
    PhysXSharedBody *mSharedBody;
    PxShape *mShape;
    PxVec3 mCenter;
    int8_t mIndex;
    uint8_t mFlag;
    void updateCenter();
};

} // namespace physics
} // namespace cc
