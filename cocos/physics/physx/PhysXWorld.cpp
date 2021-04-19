#include "../spec/IWorld.h"
#include "PhysXWorld.h"
#include "PhysXFilterShader.h"
#include "PhysXUtils.h"
#include <PhysX/extensions/PxDefaultAllocator.h>
#include <PhysX/extensions/PxDefaultErrorCallback.h>

using namespace physx;

namespace cc {
namespace physics {

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

    mEventMgr = new PhysXEventManager();

    PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
    sceneDesc.gravity = PxVec3(0.0f, -10.0f, 0.0f);
    sceneDesc.cpuDispatcher = mDispatcher;
    sceneDesc.kineKineFilteringMode = PxPairFilteringMode::eKEEP;
    sceneDesc.staticKineFilteringMode = PxPairFilteringMode::eKEEP;
    sceneDesc.flags |= PxSceneFlag::eENABLE_CCD;
    sceneDesc.filterShader = SimpleFilterShader;
    sceneDesc.simulationEventCallback = &mEventMgr->getEventCallback();
    mScene = mPhysics->createScene(sceneDesc);
}

PhysXWorld::~PhysXWorld() {
    delete mEventMgr;
    PX_RELEASE(mScene);
    PX_RELEASE(mDispatcher);
    PxCloseExtensions();
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
    mEventMgr->refreshPairs();
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
