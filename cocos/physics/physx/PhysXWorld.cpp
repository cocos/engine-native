#include "PhysXWorld.h"
#include "PhysXUtils.h"
#include <PhysX/extensions/PxDefaultAllocator.h>
#include <PhysX/extensions/PxDefaultErrorCallback.h>

using namespace physx;

namespace cc {
namespace physics {
PxFilterFlags AdvanceFilterShader(
    PxFilterObjectAttributes attributes0, PxFilterData fd0,
    PxFilterObjectAttributes attributes1, PxFilterData fd1,
    PxPairFlags &pairFlags, const void *, PxU32) {
    // constexpr PxU32 QUERY_FILTER = 1 << 0;
    // constexpr PxU32 QUERY_CHECK_TRIGGER = 1 << 1;
    // constexpr PxU32 QUERY_SINGLE_HIT = 1 << 2;
    constexpr PxU32 DETECT_TRIGGER_EVENT = 1 << 3;
    constexpr PxU32 DETECT_CONTACT_EVENT = 1 << 4;
    constexpr PxU32 DETECT_CONTACT_POINT = 1 << 5;
    constexpr PxU32 DETECT_CONTACT_CCD = 1 << 6;
    // group mask filter
    if (!(fd0.word0 & fd1.word1) || !(fd0.word1 & fd1.word0)) {
        return PxFilterFlag::eSUPPRESS;
    }

    pairFlags = PxPairFlags(0);

    // trigger filter
    if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1)) {
        pairFlags |= PxPairFlag::eDETECT_DISCRETE_CONTACT;

        // need trigger event?
        const PxU16 needTriggerEvent = (fd0.word3 & DETECT_TRIGGER_EVENT) | (fd1.word3 & DETECT_TRIGGER_EVENT);
        if (needTriggerEvent) {
            pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND | PxPairFlag::eNOTIFY_TOUCH_LOST;
            return PxFilterFlag::eDEFAULT;
        } else {
            return PxFilterFlag::eSUPPRESS;
        }
    }

    // need detect ccd contact?
    const PxU16 needDetectCCD = (fd0.word3 & DETECT_CONTACT_CCD) | (fd1.word3 & DETECT_CONTACT_CCD);
    if (needDetectCCD) pairFlags |= PxPairFlag::eDETECT_CCD_CONTACT;

    // simple collision process
    pairFlags |= PxPairFlag::eCONTACT_DEFAULT;

    // need contact event?
    const PxU16 needContactEvent = (fd0.word3 & DETECT_CONTACT_EVENT) | (fd1.word3 & DETECT_CONTACT_EVENT);
    if (needContactEvent) pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND | PxPairFlag::eNOTIFY_TOUCH_LOST | PxPairFlag::eNOTIFY_TOUCH_PERSISTS;

    // need contact point?
    const PxU16 needContactPoint = (fd0.word3 & DETECT_CONTACT_POINT) | (fd1.word3 & DETECT_CONTACT_POINT);
    if (needContactPoint) pairFlags |= PxPairFlag::eNOTIFY_CONTACT_POINTS;

    return PxFilterFlag::eDEFAULT;
}

PhysXWorld *PhysXWorld::instance = nullptr;
PhysXWorld &PhysXWorld::getInstance() {
    return *instance;
}

PxFoundation &PhysXWorld::getFundation() {
    return *getInstance().mFoundation;
}

PxPhysics &PhysXWorld::getPhysics() {
    return *getInstance().mPhysics;
}

PhysXWorld::PhysXWorld() {
    instance = this; // TODO
    static PxDefaultAllocator gAllocator;
    static PxDefaultErrorCallback gErrorCallback;
    mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
    mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, PxTolerancesScale(), true, nullptr);
    mDispatcher = PxDefaultCpuDispatcherCreate(0);

    PxInitExtensions(*mPhysics, nullptr);

    PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
    sceneDesc.gravity = PxVec3(0.0f, -10.0f, 0.0f);
    sceneDesc.cpuDispatcher = mDispatcher;
    sceneDesc.kineKineFilteringMode = PxPairFilteringMode::eKEEP;
    sceneDesc.staticKineFilteringMode = PxPairFilteringMode::eKEEP;
    sceneDesc.flags |= PxSceneFlag::eENABLE_CCD;
    sceneDesc.filterShader = AdvanceFilterShader;
    mScene = mPhysics->createScene(sceneDesc);
}

PhysXWorld::~PhysXWorld() {
    PX_RELEASE(mScene);
    PX_RELEASE(mDispatcher);
    PX_RELEASE(mPhysics);
    PX_RELEASE(mFoundation);
}

void PhysXWorld::step(float fixedTimeStep) {
    mScene->simulate(fixedTimeStep);
    mScene->fetchResults(true);
	syncPhysicsToScene();
}

void PhysXWorld::setGravity(float x, float y, float z) {
    mScene->setGravity(PxVec3(x, y, z));
}

void PhysXWorld::destroy() {
}

void PhysXWorld::emitEvents() {
}

void PhysXWorld::syncSceneToPhysics() {
    for (auto const &sb : mSharedBodies) {
        sb->syncSceneToPhysics();
    }
}

void PhysXWorld::syncPhysicsToScene() {
	for (auto const &sb : mSharedBodies) {
		sb->syncPhysicsToScene();
	}
}

void PhysXWorld::syncSceneWithCheck() {
    for (auto const &sb : mSharedBodies) {
        sb->syncSceneWithCheck();
    }
}

void PhysXWorld::setAllowSleep(bool val) {
}

void PhysXWorld::setDefaultMaterial(float f, float dy, float r) {
}

PhysXSharedBody *PhysXWorld::getSharedBody(const uint &handle, PhysXRigidBody *const body) {
    return PhysXSharedBody::getSharedBody(handle, this, body);
}

void PhysXWorld::addActor(PhysXSharedBody &sb) {
    auto beg = mSharedBodies.begin();
    auto end = mSharedBodies.end();
    auto iter = find(beg, end, &sb);
    if (iter == end) {
        mScene->addActor(*sb.getImpl().rigidActor);
        mSharedBodies.push_back(&sb);
    }
}

void PhysXWorld::removeActor(PhysXSharedBody &sb) {
    auto beg = mSharedBodies.begin();
    auto end = mSharedBodies.end();
    auto iter = find(beg, end, &sb);
    if (iter != end) {
        mScene->removeActor(*sb.getImpl().rigidActor, true);
        mSharedBodies.erase(iter);
    }
}

} // namespace physics
} // namespace cc
