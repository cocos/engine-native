
#include "physics/physx/shapes/PhysXShape.h"
#include "physics/physx/PhysXSharedBody.h"
#include "physics/physx/PhysXUtils.h"
#include "physics/physx/PhysXWorld.h"
#include <unordered_map>

namespace cc {
namespace physics {

void PhysXShape::initialize(uint handle) {
    PhysXWorld &ins = PhysXWorld::getInstance();
    _mSharedBody = ins.getSharedBody(handle);
    getSharedBody().reference(true);
    onComponentSet();
    getPxShapeMap().insert(std::pair<uintptr_t, uintptr_t>(reinterpret_cast<uintptr_t>(&getShape()), getImpl()));
}

void PhysXShape::onEnable() {
    _mEnabled = true;
    getSharedBody().addShape(*this);
    getSharedBody().enabled(true);
}

void PhysXShape::onDisable() {
    _mEnabled = false;
    getSharedBody().removeShape(*this);
    getSharedBody().enabled(false);
}

void PhysXShape::onDestroy() {
    getSharedBody().reference(false);
    getPxShapeMap().erase(reinterpret_cast<uintptr_t>(&getShape()));
}

void PhysXShape::setMaterial(uint16_t id, float f, float df, float r,
                             uint8_t m0, uint8_t m1) {    
    auto *mat = reinterpret_cast<physx::PxMaterial *>(getSharedBody().getWorld().createMaterial(id, f, df, r, m0, m1));
    getShape().setMaterials(&mat, 1);
}

void PhysXShape::setAsTrigger(bool v) {
    if (v) {
        getShape().setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, !v);
        getShape().setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, v);
    } else {
        getShape().setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, v);
        getShape().setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, !v);
    }
    if (_mIndex >= 0) {
        getSharedBody().removeShape(*this);
        getSharedBody().addShape(*this);
    }
}

void PhysXShape::setCenter(float x, float y, float z) {
    _mCenter = physx::PxVec3{x, y, z};
    updateCenter();
}

uint32_t PhysXShape::getGroup() {
    return getSharedBody().getGroup();
}

void PhysXShape::setGroup(uint32_t g) {
    getSharedBody().setGroup(g);
}

uint32_t PhysXShape::getMask() {
    return getSharedBody().getMask();
}

void PhysXShape::setMask(uint32_t m) {
    getSharedBody().setMask(m);
}

void PhysXShape::updateEventListener(EShapeFilterFlag flag) {
}

cc::pipeline::AABB& PhysXShape::getAABB() {
    static cc::pipeline::AABB aabb;
    return aabb;
}

cc::pipeline::Sphere& PhysXShape::getBoundingSphere() {
    static cc::pipeline::Sphere s;
    return s;
}

void PhysXShape::updateFilterData(physx::PxFilterData &data) {
}

void PhysXShape::updateCenter() {
    auto &sb = getSharedBody();
    auto &node = sb.getNode();
    physx::PxTransform local{_mCenter * node.worldScale, _mRotation};
    getShape().setLocalPose(local);
    if (_mEnabled && !isTrigger()) sb.updateCenterOfMass();
}

} // namespace physics
} // namespace cc
