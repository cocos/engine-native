
#include "PhysXRevolute.h"
#include "../PhysXSharedBody.h"
#include "../PhysXUtils.h"
#include "math/Quaternion.h"

namespace cc {
namespace physics {

PhysXRevolute::PhysXRevolute() : mPivotA(PxZero),
                                 mPivotB(PxZero),
                                 mAxis(PxZero) {}

void PhysXRevolute::onComponentSet() {
    mJoint = PxRevoluteJointCreate(PxGetPhysics(), &getTempRigidActor(), PxTransform{PxIdentity}, nullptr, PxTransform{PxIdentity});
}

void PhysXRevolute::setPivotA(float x, float y, float z) {
    mPivotA = PxVec3{x, y, z};
    updatePose();
}

void PhysXRevolute::setPivotB(float x, float y, float z) {
    mPivotB = PxVec3{x, y, z};
    updatePose();
}

void PhysXRevolute::setAxis(float x, float y, float z) {
    mAxis = PxVec3{x, y, z};
    updatePose();
}

void PhysXRevolute::updateScale0() {
	updatePose();
}

void PhysXRevolute::updateScale1() {
	updatePose();
}

void PhysXRevolute::updatePose() {
    PxTransform pose0{PxIdentity};
    PxTransform pose1{PxIdentity};
    auto &node0 = mSharedBody->getNode();
    pose0.p = mPivotA * node0.worldScale;
    PxSetFromTwoVectors(pose0.q, PxVec3{1.f, 0.f, 0.f}, mAxis);
    mJoint->setLocalPose(PxJointActorIndex::eACTOR0, pose0);
    pose1.q = pose0.q;
    if (mConnectedBody) {
        auto &node1 = mConnectedBody->getNode();
        pose1.p = mPivotB * node1.worldScale;
    } else {
        pose1.p = mPivotA * node0.worldScale;
        pose1.p += mPivotB + node0.worldPosition;
        const auto &wr = node0.worldRotation;
        pose1.q *= PxQuat{wr.x, wr.y, wr.z, wr.w};
    }
    mJoint->setLocalPose(PxJointActorIndex::eACTOR1, pose1);
}

} // namespace physics
} // namespace cc
