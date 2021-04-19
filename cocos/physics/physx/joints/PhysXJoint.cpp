
#include "PhysXJoint.h"
#include "../PhysXSharedBody.h"
#include "../PhysXUtils.h"
#include "../PhysXWorld.h"

namespace cc {
namespace physics {

void PhysXJoint::initialize(const uint handle) {
    auto &ins = PhysXWorld::getInstance();
    mSharedBody = ins.getSharedBody(handle);
    mSharedBody->reference(true);
    onComponentSet();
}

void PhysXJoint::onEnable() {
    mSharedBody->addJoint(*this, PxJointActorIndex::eACTOR0);
    if (mConnectedBody) {
        mConnectedBody->addJoint(*this, PxJointActorIndex::eACTOR1);
        mJoint->setActors(mSharedBody->getImpl().rigidActor, mConnectedBody->getImpl().rigidActor);
    } else {
        mJoint->setActors(mSharedBody->getImpl().rigidActor, nullptr);
    }
}

void PhysXJoint::onDisable() {
    mJoint->setActors(&getTempRigidActor(), nullptr);
    mSharedBody->removeJoint(*this, PxJointActorIndex::eACTOR0);
    if (mConnectedBody) mConnectedBody->removeJoint(*this, PxJointActorIndex::eACTOR1);
}

void PhysXJoint::onDestroy() {
    mSharedBody->reference(false);
}

void PhysXJoint::setConnectedBody(const uint handle) {
    if (handle) {
        auto &ins = PhysXWorld::getInstance();
        mConnectedBody = ins.getSharedBody(handle);
    } else {
        mConnectedBody = nullptr;
    }
    if (mJoint) {
        mJoint->setActors(mSharedBody->getImpl().rigidActor, mConnectedBody ? mConnectedBody->getImpl().rigidActor : nullptr);
    }
}

void PhysXJoint::setEnableCollision(const bool v) {
    mEnableCollision = v;
    if (mJoint) {
        mJoint->setConstraintFlag(PxConstraintFlag::eCOLLISION_ENABLED, mEnableCollision);
    }
}

} // namespace physics
} // namespace cc
