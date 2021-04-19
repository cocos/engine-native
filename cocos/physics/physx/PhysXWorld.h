
#pragma once

#include "../spec/IWorld.h"
#include "./PhysXInc.h"
#include "PhysXEventManager.h"
#include "PhysXFilterShader.h"
#include "PhysXRigidBody.h"
#include "PhysXSharedBody.h"
#include "base/Macros.h"
#include <memory>

using namespace physx;

namespace cc {
namespace physics {

class PhysXWorld final : virtual public IPhysicsWorld {
public:
    static PhysXWorld &getInstance();
    static PxFoundation &getFundation();
    static PxCooking &getCooking();
    static PxPhysics &getPhysics();
    PhysXWorld();
    virtual ~PhysXWorld();
    virtual void step(float fixedTimeStep) override;
    virtual void setGravity(float x, float y, float z) override;
    virtual void setAllowSleep(bool v) override;
    virtual void emitEvents() override;
    virtual void setCollisionMatrix(uint32_t index, uint32_t mask) override;
    virtual bool raycast(RaycastOptions &opt) override;
    virtual bool raycastClosest(RaycastOptions &opt) override;
    virtual std::vector<RaycastResult> &raycastResult() override;
    virtual RaycastResult &raycastClosestResult() override;
    virtual intptr_t createConvex(ConvexDesc &desc) override;
    virtual intptr_t createTrimesh(TrimeshDesc &desc) override;
    virtual intptr_t createHeightField(HeightFieldDesc &desc) override;
    virtual intptr_t createMaterial(const uint16_t ID, float f, float df, float r,
                                    uint8_t m0, uint8_t m1) override;
    CC_INLINE virtual std::vector<std::shared_ptr<TriggerEventPair>> &getTriggerEventPairs() override {
        return mEventMgr->getTriggerPairs();
    }
    CC_INLINE virtual std::vector<std::shared_ptr<ContactEventPair>> &getContactEventPairs() override {
        return mEventMgr->getConatctPairs();
    }
    virtual void syncSceneToPhysics() override;
    virtual void syncSceneWithCheck() override;
    virtual void destroy() override;

    CC_INLINE PhysXSharedBody *getSharedBody(
        const uint handle,
        PhysXRigidBody *const body = nullptr) {
        return PhysXSharedBody::getSharedBody(handle, this, body);
    }

    CC_INLINE PxScene &getScene() const { return *mScene; }
    int getMaskByIndex(uint32_t i);
    void syncPhysicsToScene();
    void addActor(PhysXSharedBody &sb);
    void removeActor(PhysXSharedBody &sb);

private:
    static PhysXWorld *instance;
    PxFoundation *mFoundation;
    PxCooking *mCooking;
    PxPhysics *mPhysics;
#ifdef CC_DEBUG
    PxPvd *mPvd;
#endif
    PxDefaultCpuDispatcher *mDispatcher;
    PxScene *mScene;
    PhysXEventManager *mEventMgr;
    int mCollisionMatrix[31];
    std::vector<PhysXSharedBody *> mSharedBodies;
};

} // namespace physics
} // namespace cc
