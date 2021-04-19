
#include "physics/physx/joints/PhysXDistance.h"
#include "physics/physx/PhysXSharedBody.h"
#include "physics/physx/PhysXUtils.h"
#include "math/Quaternion.h"

namespace cc {
namespace physics {

PhysXDistance::PhysXDistance() : _mPivotA(physx::PxZero),
                                 _mPivotB(physx::PxZero) {}

void PhysXDistance::onComponentSet() {
    _mJoint = PxDistanceJointCreate(PxGetPhysics(), &getTempRigidActor(), physx::PxTransform{physx::PxIdentity}, nullptr, physx::PxTransform{physx::PxIdentity});
}

void PhysXDistance::setPivotA(float x, float y, float z) {
    _mPivotA = physx::PxVec3{x, y, z};
    updatePose();
}

void PhysXDistance::setPivotB(float x, float y, float z) {
    _mPivotB = physx::PxVec3{x, y, z};
    updatePose();
}

void PhysXDistance::updateScale0() {
    updatePose();
}

void PhysXDistance::updateScale1() {
    updatePose();
}

void PhysXDistance::updatePose() {
    physx::PxTransform pose0{physx::PxIdentity};
    physx::PxTransform pose1{physx::PxIdentity};
    auto &node0 = _mSharedBody->getNode();
    pose0.p = _mPivotA * node0.worldScale;
    _mJoint->setLocalPose(physx::PxJointActorIndex::eACTOR0, pose0);
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
