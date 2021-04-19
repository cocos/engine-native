
#include "PhysXShape.h"
#include "PhysXPlane.h"
#include "../PhysXUtils.h"
#include "../PhysXWorld.h"

namespace cc {
namespace physics {

PhysXPlane::PhysXPlane() : _mConstant(0.F),
                           _mNormal(0.F, 1.F, 0.F)
                           {};

void PhysXPlane::setConstant(float x) {
    _mConstant = x;
    updateCenter();
}

void PhysXPlane::setNormal(float x, float y, float z) {
    _mNormal = physx::PxVec3{x, y, z};
    updateCenter();
}

void PhysXPlane::onComponentSet() {
    _mShape = PxGetPhysics().createShape(getPxGeometry<physx::PxPlaneGeometry>(), getDefaultMaterial(), true);
    updateCenter();
}

void PhysXPlane::updateScale() {
    updateCenter();
}

void PhysXPlane::updateCenter() {
    auto &node = getSharedBody().getNode();
    auto &geo = getPxGeometry<physx::PxPlaneGeometry>();
    physx::PxTransform local;
    pxSetFromTwoVectors(local.q, physx::PxVec3{1.F, 0.F, 0.F}, _mNormal);
    local.p = _mNormal * _mConstant + _mCenter;
    getShape().setLocalPose(local);
}

} // namespace physics
} // namespace cc
