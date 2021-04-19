#pragma once

#include "PhysXShape.h"
#include "../PhysXSharedBody.h"
#include "../PhysXUtils.h"
#include "../PhysXWorld.h"
#include <unordered_map>

namespace cc {
namespace physics {

intptr_t PhysXShape::getImpl() {
    return (intptr_t)this;
}

void PhysXShape::initialize(const uint &handle) {
    PhysXWorld &ins = PhysXWorld::getInstance();
    mSharedBody = ins.getSharedBody(handle);
    getSharedBody().reference(true);
    onComponentSet();
    getPxEventPairMap().insert(std::pair<intptr_t, intptr_t>((intptr_t)&getShape(), getImpl()));
}

void PhysXShape::onEnable() {
    mEnabled = true;
    getSharedBody().addShape(*this);
    getSharedBody().enabled(true);
}

void PhysXShape::onDisable() {
    mEnabled = false;
    getSharedBody().removeShape(*this);
    getSharedBody().enabled(false);
}

void PhysXShape::onDestroy() {
    getSharedBody().reference(false);
    getPxEventPairMap().erase((intptr_t)&getShape());
}

void PhysXShape::setMaterial(const uint16_t ID, float f, float df, float r,
                             uint8_t m0, uint8_t m1) {
    auto &m = getPxMaterialMap();
    PxMaterial *mat = (PxMaterial *)getSharedBody().getWorld().createMaterial(ID, f, df, r, m0, m1);
    getShape().setMaterials(&mat, 1);
}

void PhysXShape::setAsTrigger(bool v) {
    if (v) {
        getShape().setFlag(PxShapeFlag::eSIMULATION_SHAPE, !v);
        getShape().setFlag(PxShapeFlag::eTRIGGER_SHAPE, v);
    } else {
        getShape().setFlag(PxShapeFlag::eTRIGGER_SHAPE, v);
        getShape().setFlag(PxShapeFlag::eSIMULATION_SHAPE, !v);
    }
    if (mIndex >= 0) {
        getSharedBody().removeShape(*this);
        getSharedBody().addShape(*this);
    }
}

void PhysXShape::setCenter(float x, float y, float z) {
    mCenter = PxVec3{x, y, z};
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

cc::pipeline::AABB PhysXShape::getAABB() {
    static cc::pipeline::AABB aabb;
    return aabb;
}

cc::pipeline::Sphere PhysXShape::getBoundingSphere() {
    static cc::pipeline::Sphere s;
    return s;
}

void PhysXShape::updateFilterData(PxFilterData &data) {
}

void PhysXShape::updateCenter() {
    auto &sb = getSharedBody();
    auto &node = sb.getNode();
    PxTransform local{mCenter * node.worldScale, mRotation};
    getShape().setLocalPose(local);
    if (mEnabled && !isTrigger()) sb.updateCenterOfMass();
}

} // namespace physics
} // namespace cc
