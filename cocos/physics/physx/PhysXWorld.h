
#pragma once

#include "../spec/IWorld.h"
#include "PhysXEventManager.h"
#include "PhysXRigidBody.h"
#include "PhysXSharedBody.h"
#include "base/Macros.h"
#include <PhysX/PxPhysicsAPI.h>

using namespace physx;

namespace cc {
namespace physics {

class PhysXWorld final : virtual public IPhysicsWorld {
public:
    static PhysXWorld &getInstance();
    static PxFoundation &getFundation();
    static PxPhysics &getPhysics();
    PhysXWorld();
    virtual ~PhysXWorld();
    virtual void step(float fixedTimeStep) override;
    virtual void setGravity(float x, float y, float z) override;
    virtual void setAllowSleep(bool v) override;
    virtual void setDefaultMaterial(float f, float dy, float r) override;
    virtual void emitEvents() override;
    CC_INLINE virtual std::vector<TriggerEventPair> &getTriggerEventPairs() override {
        return mEventMgr->getTriggerPairs();
    }
    virtual void syncSceneToPhysics() override;
    virtual void syncSceneWithCheck() override;
    virtual void destroy() override;

    CC_INLINE PhysXSharedBody *getSharedBody(
        const uint &handle,
        PhysXRigidBody *const body = nullptr) {
        return PhysXSharedBody::getSharedBody(handle, this, body);
    }

    CC_INLINE PxScene &getScene() const { return *mScene; }
    void syncPhysicsToScene();
    void addActor(PhysXSharedBody &sb);
    void removeActor(PhysXSharedBody &sb);

private:
    static PhysXWorld *instance;
    PxFoundation *mFoundation;
    PxPhysics *mPhysics;
    PxDefaultCpuDispatcher *mDispatcher;

    PxScene *mScene;
    PhysXEventManager *mEventMgr;
    std::vector<PhysXSharedBody *> mSharedBodies;
};

} // namespace physics
} // namespace cc
