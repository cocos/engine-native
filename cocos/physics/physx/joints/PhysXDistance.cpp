
#include "PhysXDistance.h"
#include "../PhysXSharedBody.h"
#include "../PhysXUtils.h"
#include "math/Quaternion.h"

namespace cc {
namespace physics {

PhysXDistance::PhysXDistance() : mPivotA(PxZero),
                                 mPivotB(PxZero) {}

void PhysXDistance::onComponentSet() {
    mJoint = PxDistanceJointCreate(PxGetPhysics(), &getTempRigidActor(), PxTransform{PxIdentity}, nullptr, PxTransform{PxIdentity});
}

void PhysXDistance::setPivotA(float x, float y, float z) {
    mPivotA = PxVec3{x, y, z};
    updatePose();
}

void PhysXDistance::setPivotB(float x, float y, float z) {
    mPivotB = PxVec3{x, y, z};
    updatePose();
}

void PhysXDistance::updateScale0() {
    updatePose();
}

void PhysXDistance::updateScale1() {
    updatePose();
}

void PhysXDistance::updatePose() {
    PxTransform pose0{PxIdentity};
    PxTransform pose1{PxIdentity};
    auto &node0 = mSharedBody->getNode();
    pose0.p = mPivotA * node0.worldScale;
    mJoint->setLocalPose(PxJointActorIndex::eACTOR0, pose0);
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
