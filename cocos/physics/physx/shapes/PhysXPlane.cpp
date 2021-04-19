
#include "PhysXPlane.h"
#include "../PhysXUtils.h"
#include "../PhysXWorld.h"
#include "PhysXShape.h"

namespace cc {
namespace physics {

PhysXPlane::PhysXPlane() : mConstant(0.f),
                           mNormal(0.f, 1.f, 0.f),
                           PhysXShape(){};

PhysXPlane::~PhysXPlane(){};

void PhysXPlane::setConstant(float x) {
    mConstant = x;
    updateCenter();
}

void PhysXPlane::setNormal(float x, float y, float z) {
    mNormal = PxVec3{x, y, z};
    updateCenter();
}

void PhysXPlane::onComponentSet() {
    auto &phy = PhysXWorld::getPhysics();
    static auto mat = phy.createMaterial(0.5, 0.5, 0.1);
    mShape = phy.createShape(getPxGeometry<PxPlaneGeometry>(), *mat);
    updateCenter();
}

void PhysXPlane::updateScale() {
    updateCenter();
}

void PhysXPlane::updateCenter() {
    auto &node = getSharedBody().getNode();
    auto &geo = getPxGeometry<PxPlaneGeometry>();
    PxTransform local;
    PxVec3 a{PxIdentity};
    PxSetVec3Ext(a, mNormal);
    PxSetFromTwoVectors(local.q, PxVec3{1.f, 0.f, 0.f}, a);
    local.p = mNormal * mConstant + mCenter;
    getShape().setLocalPose(local);
}

} // namespace physics
} // namespace cc
