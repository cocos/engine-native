
#pragma once

#include "physics/physx/PhysXInc.h"
#include "physics/spec/IShape.h"
#include "base/Macros.h"

namespace cc {
namespace physics {
class PhysXSharedBody;

template <typename T>
CC_INLINE T &getPxGeometry() {
    static T geo;
    return geo;
}

class PhysXShape : virtual public IBaseShape {
    PX_NOCOPY(PhysXShape)
    PhysXShape() : _mCenter(physx::PxIdentity),
                   _mRotation(physx::PxIdentity){};

public:
    ~PhysXShape() override = default;
    CC_INLINE uintptr_t   getImpl() override { return reinterpret_cast<uintptr_t>(this); }
    void                  initialize(uint handle) override;
    void                  onEnable() override;
    void                  onDisable() override;
    void                  onDestroy() override;
    void                  setMaterial(uint16_t id, float f, float df, float r,
                                      uint8_t m0, uint8_t m1) override;
    void                  setAsTrigger(bool v) override;
    void                  setCenter(float x, float y, float z) override;
    cc::pipeline::AABB &  getAABB() override;
    cc::pipeline::Sphere &getBoundingSphere() override;
    void                  updateEventListener(EShapeFilterFlag flag) override;
    uint32_t              getGroup() override;
    void                  setGroup(uint32_t g) override;
    uint32_t              getMask() override;
    void                  setMask(uint32_t m) override;
    virtual void          updateScale() = 0;
    CC_INLINE physx::PxVec3 &getCenter() { return _mCenter; }
    CC_INLINE physx::PxShape &getShape() const { return *_mShape; }
    CC_INLINE PhysXSharedBody &getSharedBody() const { return *_mSharedBody; }
    CC_INLINE bool             isTrigger() const {
        return getShape().getFlags().isSet(physx::PxShapeFlag::eTRIGGER_SHAPE);
    }
    void updateFilterData(physx::PxFilterData &data);

protected:
    PhysXSharedBody *_mSharedBody{nullptr};
    physx::PxShape * _mShape{nullptr};
    physx::PxVec3    _mCenter;
    physx::PxQuat    _mRotation;
    int8_t           _mIndex{-1};
    uint8_t          _mFlag{0};
    bool             _mEnabled{false};
    virtual void     updateCenter();
    virtual void     onComponentSet() = 0;
};

} // namespace physics
} // namespace cc
