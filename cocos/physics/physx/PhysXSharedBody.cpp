
#include "PhysXSharedBody.h"
#include "PhysXUtils.h"
#include "PhysXWorld.h"
#include "shapes/PhysXShape.h"
#include <math.h>

using namespace physx;
using namespace cc::pipeline;

namespace cc {
namespace physics {
std::map<uint, PhysXSharedBody *> PhysXSharedBody::sharedBodesMap = std::map<uint, PhysXSharedBody *>();

static int idCounter = 0;
PhysXSharedBody::PhysXSharedBody(
    const uint &handle,
    PhysXWorld *const world,
    PhysXRigidBody *const body) : mID(idCounter++),
                                  mRef(0),
                                  mType(ERigidBodyType::STATIC),
                                  mIsStatic(true),
                                  mIndex(-1),
                                  mFilterData(1, 1, 0, 1),
                                  mNodeHandle(handle),
                                  mStaticActor(nullptr),
                                  mDynamicActor(nullptr),
                                  mWrappedWorld(world),
                                  mWrappedBody(body) {
    mImpl.ptr = NULL;
    mNode = GET_NODE(mNodeHandle);
};

PhysXSharedBody *PhysXSharedBody::getSharedBody(const uint &handle, PhysXWorld *const world, PhysXRigidBody *const body) {
    auto iter = sharedBodesMap.find(handle);
    PhysXSharedBody *newSB;
    if (iter != sharedBodesMap.end()) {
        newSB = iter->second;
    } else {
        newSB = new PhysXSharedBody(handle, world, body);
        newSB->mFilterData.word0 = 1;
        newSB->mFilterData.word1 = world->getMaskByIndex(0);
        sharedBodesMap.insert(std::pair<uint, PhysXSharedBody *>(handle, newSB));
    }
    if (body != nullptr) {
        int g = body->getInitialGroup();
        newSB->mFilterData.word0 = g;
        newSB->mFilterData.word1 = world->getMaskByIndex(log2(g));
    }
    return newSB;
}

PhysXSharedBody::~PhysXSharedBody() {
    if (mStaticActor != nullptr) PX_RELEASE(mStaticActor);
    if (mDynamicActor != nullptr) PX_RELEASE(mDynamicActor);
}

PhysXSharedBody::UActor PhysXSharedBody::getImpl() {
    initActor();
    mImpl.ptr = isStatic() ? (intptr_t)mStaticActor : (intptr_t)mDynamicActor;
    return mImpl;
}

void PhysXSharedBody::reference(bool v) {
    v ? mRef++ : mRef--;
    if (mRef == 0) delete this;
}

void PhysXSharedBody::enabled(bool v) {
    if (v) {
        if (mIndex < 0) {
            mIndex = 1;
            mWrappedWorld->addActor(*this);
        }
    } else {
        auto wb = mWrappedBody;
        auto ws = mWrappedShapes;
        auto isRemove = ws.size() == 0 && (wb == nullptr || (wb != nullptr && !wb->isEnabled()));
        if (mIndex >= 0) {
            mIndex = -1;
            mWrappedWorld->removeActor(*this);
        }
    }
}

void PhysXSharedBody::initActor() {
    const bool temp = mIsStatic;
    if (isStatic()) {
        mIsStatic = true;
        initStaticActor();
    } else {
        mIsStatic = false;
        initDynamicActor();
    }
    if (temp != mIsStatic) switchActor(temp);
}

void PhysXSharedBody::switchActor(const bool isStaticBefore) {
    if (mStaticActor == nullptr || mDynamicActor == nullptr) return;
    PxRigidActor &a0 = isStaticBefore ? *(PxRigidActor *)mStaticActor : *(PxRigidActor *)mDynamicActor;
    PxRigidActor &a1 = !isStaticBefore ? *(PxRigidActor *)mStaticActor : *(PxRigidActor *)mDynamicActor;
    if (mIndex >= 0) {
        mWrappedWorld->getScene().removeActor(a0, false);
        mWrappedWorld->getScene().addActor(a1);
    }
    for (auto const &ws : mWrappedShapes) {
        a0.detachShape(ws->getShape(), false);
        a1.attachShape(ws->getShape());
    }
    if (isStaticBefore) {
        mDynamicActor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, isKinematic());
        PxRigidBodyExt::setMassAndUpdateInertia(*mDynamicActor, mMass);
        PxTransform com{PxIdentity};
        for (auto const &ws : mWrappedShapes) {
            if (!ws->isTrigger()) com.p -= ws->getCenter();
        }
        mDynamicActor->setCMassLocalPose(com);
    }
}

void PhysXSharedBody::initStaticActor() {
    if (mStaticActor == nullptr) {
        PxTransform transform{PxIdentity};
        PxSetVec3Ext(transform.p, getNode().worldPosition);
        PxSetQuatExt(transform.q, getNode().worldRotation);
        if (!transform.p.isFinite()) transform.p = PxVec3{PxIdentity};
        if (!transform.q.isUnit()) transform.q = PxQuat{PxIdentity};
        PxPhysics &phy = PxGetPhysics();
        mStaticActor = phy.createRigidStatic(transform);
    }
}

void PhysXSharedBody::initDynamicActor() {
    if (mDynamicActor == nullptr) {
        PxTransform transform{PxIdentity};
        PxSetVec3Ext(transform.p, getNode().worldPosition);
        PxSetQuatExt(transform.q, getNode().worldRotation);
        if (!transform.p.isFinite()) transform.p = PxVec3{PxIdentity};
        if (!transform.q.isUnit()) transform.q = PxQuat{PxIdentity};
        PxPhysics &phy = PxGetPhysics();
        mDynamicActor = phy.createRigidDynamic(transform);
        mDynamicActor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, isKinematic());
    }
}

void PhysXSharedBody::updateCenterOfMass() {
    initActor();
    if (isStatic()) return;
    PxTransform com{PxIdentity};
    for (auto const &ws : mWrappedShapes) {
        if (!ws->isTrigger()) com.p -= ws->getCenter();
    }
    mDynamicActor->setCMassLocalPose(com);
}

void PhysXSharedBody::syncSceneToPhysics() {
    if (getNode().flagsChanged) {
        if (getNode().flagsChanged & TransformBit::SCALE) {
            for (auto const &sb : mWrappedShapes)
                sb->updateScale();
        }
        PxTransform &wp = getImpl().rigidActor->getGlobalPose();
        if (getNode().flagsChanged & TransformBit::POSITION)
            PxSetVec3Ext(wp.p, getNode().worldPosition);
        if (getNode().flagsChanged & TransformBit::ROTATION)
            PxSetQuatExt(wp.q, getNode().worldRotation);

        if (isKinematic())
            getImpl().rigidDynamic->setKinematicTarget(wp);
        else
            getImpl().rigidActor->setGlobalPose(wp, true);
    }
}

void PhysXSharedBody::syncSceneWithCheck() {
    if (getNode().flagsChanged & TransformBit::SCALE) {
        for (auto const &sb : mWrappedShapes)
            sb->updateScale();
    }
    PxTransform &wp = getImpl().rigidActor->getGlobalPose();
    bool needUpdate = false;
    if (wp.p != getNode().worldPosition) {
        PxSetVec3Ext(wp.p, getNode().worldPosition);
        needUpdate = true;
    }
    if (wp.q != getNode().worldRotation) {
        PxSetQuatExt(wp.q, getNode().worldRotation);
        needUpdate = true;
    }
    if (needUpdate) {
        getImpl().rigidActor->setGlobalPose(wp, true);
    }
}

void PhysXSharedBody::syncPhysicsToScene() {
    if (isStaticOrKinematic()) return;
    if (mDynamicActor->isSleeping()) return;
    const PxTransform &wp = getImpl().rigidActor->getGlobalPose();
    PxSetVec3Ext(getNode().worldPosition, wp.p);
    PxSetQuatExt(getNode().worldRotation, wp.q);
    getNode().flagsChanged |= TransformBit::POSITION | TransformBit::ROTATION;
}

void PhysXSharedBody::addShape(PhysXShape &shape) {
    auto beg = mWrappedShapes.begin();
    auto end = mWrappedShapes.end();
    auto iter = find(beg, end, &shape);
    if (iter == end) {
        shape.getShape().setSimulationFilterData(mFilterData);
        shape.getShape().setQueryFilterData(mFilterData);
        getImpl().rigidActor->attachShape(shape.getShape());
        mWrappedShapes.push_back(&shape);
        if (!shape.isTrigger()) {
            if (!shape.getCenter().isZero()) updateCenterOfMass();
            if (isDynamic()) PxRigidBodyExt::setMassAndUpdateInertia(*getImpl().rigidDynamic, mMass);
        }
    }
}

void PhysXSharedBody::removeShape(PhysXShape &shape) {
    auto beg = mWrappedShapes.begin();
    auto end = mWrappedShapes.end();
    auto iter = find(beg, end, &shape);
    if (iter != end) {
        mWrappedShapes.erase(iter);
        getImpl().rigidActor->detachShape(shape.getShape());
        if (!shape.isTrigger()) {
            if (!shape.getCenter().isZero()) updateCenterOfMass();
            if (isDynamic()) PxRigidBodyExt::setMassAndUpdateInertia(*getImpl().rigidDynamic, mMass);
        }
    }
}

void PhysXSharedBody::setMass(float v) {
    if (v <= 0) v = 1e-7;
    mMass = v;
    if (isDynamic()) PxRigidBodyExt::setMassAndUpdateInertia(*getImpl().rigidDynamic, mMass);
}

void PhysXSharedBody::setGroup(uint32_t v) {
    mFilterData.word0 = v;
    setCollisionFilter(mFilterData);
}

void PhysXSharedBody::setMask(uint32_t v) {
    mFilterData.word1 = v;
    setCollisionFilter(mFilterData);
}

void PhysXSharedBody::setCollisionFilter(PxFilterData &data) {
    if (isDynamic()) mDynamicActor->wakeUp();
    for (auto const &ws : mWrappedShapes) {
        ws->getShape().setQueryFilterData(data);
        ws->getShape().setSimulationFilterData(data);
    }
}

void PhysXSharedBody::clearForces() {
    if (isStaticOrKinematic()) return;
    mDynamicActor->clearForce(PxForceMode::eFORCE);
    mDynamicActor->clearForce(PxForceMode::eIMPULSE);
    mDynamicActor->clearTorque(PxForceMode::eFORCE);
    mDynamicActor->clearTorque(PxForceMode::eIMPULSE);
}

void PhysXSharedBody::clearVelocity() {
    if (isStaticOrKinematic()) return;
    mDynamicActor->setLinearVelocity(PxVec3{PxIdentity}, false);
    mDynamicActor->setAngularVelocity(PxVec3{PxIdentity}, false);
}

} // namespace physics
} // namespace cc
