#pragma once

#include "PhysXShape.h"
#include "../PhysXSharedBody.h"
#include "../PhysXUtils.h"
#include "../PhysXWorld.h"

namespace cc {
namespace physics {

intptr_t PhysXShape::getImpl() {
    return (intptr_t)this;
}

void PhysXShape::initialize(const uint& handle) {
    PhysXWorld &ins = PhysXWorld::getInstance();
    mSharedBody = ins.getSharedBody(handle);
    getSharedBody().reference(true);
    onComponentSet();
}

void PhysXShape::onEnable() {
    getSharedBody().addShape(*this);
    getSharedBody().enabled(true);
}

void PhysXShape::onDisable() {
    getSharedBody().removeShape(*this);
    getSharedBody().enabled(false);
}

void PhysXShape::onDestroy() {
    getSharedBody().reference(false);
}

void PhysXShape::setMaterial(float f, float df, float r) {
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
    auto &node = getSharedBody().getNode();
    mLocal.p = PxVec3{x, y, z};
    mLocal.p *= node.worldScale;
    mLocal.q = PxQuat{PxIdentity};
    getShape().setLocalPose(mLocal);
}

void PhysXShape::setCollisionFilter(int g, int m) {
    PxFilterData data{(PxU32)g, (PxU32)m, 0, 0};
    getSharedBody().setCollisionFilter(data);
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

} // namespace physics
} // namespace cc
