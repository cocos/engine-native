
#include "PhysXJoint.h"
#include "../PhysXSharedBody.h"
#include "../PhysXUtils.h"
#include "../PhysXWorld.h"

namespace cc {
namespace physics {

void PhysXJoint::initialize(const uint handle) {
    auto &ins = PhysXWorld::getInstance();
    _mSharedBody = ins.getSharedBody(handle);
    _mSharedBody->reference(true);
    onComponentSet();
}

void PhysXJoint::onEnable() {
    _mSharedBody->addJoint(*this, physx::PxJointActorIndex::eACTOR0);
    if (_mConnectedBody) {
        _mConnectedBody->addJoint(*this, physx::PxJointActorIndex::eACTOR1);
        _mJoint->setActors(_mSharedBody->getImpl().rigidActor, _mConnectedBody->getImpl().rigidActor);
    } else {
        _mJoint->setActors(_mSharedBody->getImpl().rigidActor, nullptr);
    }
}

void PhysXJoint::onDisable() {
    _mJoint->setActors(&getTempRigidActor(), nullptr);
    _mSharedBody->removeJoint(*this, physx::PxJointActorIndex::eACTOR0);
    if (_mConnectedBody) _mConnectedBody->removeJoint(*this, physx::PxJointActorIndex::eACTOR1);
}

void PhysXJoint::onDestroy() {
    _mSharedBody->reference(false);
}

void PhysXJoint::setConnectedBody(const uint handle) {
    if (handle) {
        auto &ins = PhysXWorld::getInstance();
        _mConnectedBody = ins.getSharedBody(handle);
    } else {
        _mConnectedBody = nullptr;
    }
    if (_mJoint) {
        _mJoint->setActors(_mSharedBody->getImpl().rigidActor, _mConnectedBody ? _mConnectedBody->getImpl().rigidActor : nullptr);
    }
}

void PhysXJoint::setEnableCollision(const bool v) {
    _mEnableCollision = v;
    if (_mJoint) {
        _mJoint->setConstraintFlag(physx::PxConstraintFlag::eCOLLISION_ENABLED, _mEnableCollision);
    }
}

} // namespace physics
} // namespace cc
