
#include "physics/physx/joints/PhysXRevolute.h"
#include "physics/physx/PhysXSharedBody.h"
#include "physics/physx/PhysXUtils.h"
#include "math/Quaternion.h"

namespace cc {
namespace physics {

PhysXRevolute::PhysXRevolute() : _mPivotA(physx::PxZero),
                                 _mPivotB(physx::PxZero),
                                 _mAxis(physx::PxZero) {}

void PhysXRevolute::onComponentSet() {
    _mJoint = PxRevoluteJointCreate(PxGetPhysics(), &getTempRigidActor(), physx::PxTransform{physx::PxIdentity}, nullptr, physx::PxTransform{physx::PxIdentity});
}

void PhysXRevolute::setPivotA(float x, float y, float z) {
    _mPivotA = physx::PxVec3{x, y, z};
    updatePose();
}

void PhysXRevolute::setPivotB(float x, float y, float z) {
    _mPivotB = physx::PxVec3{x, y, z};
    updatePose();
}

void PhysXRevolute::setAxis(float x, float y, float z) {
    _mAxis = physx::PxVec3{x, y, z};
    updatePose();
}

void PhysXRevolute::updateScale0() {
	updatePose();
}

void PhysXRevolute::updateScale1() {
	updatePose();
}

void PhysXRevolute::updatePose() {
    physx::PxTransform pose0{physx::PxIdentity};
    physx::PxTransform pose1{physx::PxIdentity};
    auto &node0 = _mSharedBody->getNode();
    pose0.p = _mPivotA * node0.worldScale;
    pxSetFromTwoVectors(pose0.q, physx::PxVec3{1.F, 0.F, 0.F}, _mAxis);
    _mJoint->setLocalPose(physx::PxJointActorIndex::eACTOR0, pose0);
    pose1.q = pose0.q;
    if (_mConnectedBody) {
        auto &node1 = _mConnectedBody->getNode();
        pose1.p = _mPivotB * node1.worldScale;
    } else {
        pose1.p = _mPivotA * node0.worldScale;
        pose1.p += _mPivotB + node0.worldPosition;
        const auto &wr = node0.worldRotation;
        pose1.q *= physx::PxQuat{wr.x, wr.y, wr.z, wr.w};
    }
    _mJoint->setLocalPose(physx::PxJointActorIndex::eACTOR1, pose1);
}

} // namespace physics
} // namespace cc
