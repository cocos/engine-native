
#pragma once

#include "../../spec/IShape.h"
#include "../PhysXInc.h"
#include "base/Macros.h"

using namespace physx;

namespace cc {
namespace physics {
class PhysXSharedBody;

template <typename T>
T &getPxGeometry() {
    static T geo;
    return geo;
}

class PhysXShape : virtual public IBaseShape {
    PX_NOCOPY(PhysXShape)
    PhysXShape() : mIndex(-1),
                   mFlag(0),
                   mEnabled(false),
                   mCenter(PxIdentity),
                   mRotation(PxIdentity),
                   mShape(nullptr),
                   mSharedBody(nullptr){};

public:
    virtual ~PhysXShape(){};
    virtual intptr_t getImpl() override;
    virtual void initialize(const uint &handle) override;
    virtual void onEnable() override;
    virtual void onDisable() override;
    virtual void onDestroy() override;
    virtual void setMaterial(const uint16_t ID, float f, float df, float r,
                             uint8_t m0, uint8_t m1) override;
    virtual void setAsTrigger(bool v) override;
    virtual void setCenter(float x, float y, float z) override;
    virtual cc::pipeline::AABB getAABB() override;
    virtual cc::pipeline::Sphere getBoundingSphere() override;
    virtual void updateEventListener(EShapeFilterFlag flag) override;
    virtual uint32_t getGroup() override;
    virtual void setGroup(uint32_t g) override;
    virtual uint32_t getMask() override;
    virtual void setMask(uint32_t m) override;
    virtual void updateScale() = 0;
    CC_INLINE PxVec3 &getCenter() { return mCenter; }
    CC_INLINE PxShape &getShape() const { return *mShape; }
    CC_INLINE PhysXSharedBody &getSharedBody() const { return *mSharedBody; }
    CC_INLINE const bool isTrigger() const {
        return getShape().getFlags().isSet(PxShapeFlag::eTRIGGER_SHAPE);
    }
    void updateFilterData(PxFilterData &data);

protected:
    PhysXSharedBody *mSharedBody;
    PxShape *mShape;
    PxVec3 mCenter;
    PxQuat mRotation;
    int8_t mIndex;
    uint8_t mFlag;
    bool mEnabled;
    virtual void updateCenter();
    virtual void onComponentSet() = 0;
};

} // namespace physics
} // namespace cc
