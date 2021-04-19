
#pragma once

#include "./PhysXInc.h"
#include "../spec/IWorld.h"
#include "PhysXEventManager.h"
#include "PhysXFilterShader.h"
#include "PhysXRigidBody.h"
#include "PhysXSharedBody.h"
#include "base/Macros.h"
#include <memory>

namespace cc {
namespace physics {

class PhysXWorld final : virtual public IPhysicsWorld {
public:
    static PhysXWorld &getInstance();
    static physx::PxFoundation &getFundation();
    static physx::PxCooking &getCooking();
    static physx::PxPhysics &getPhysics();
    PhysXWorld();
    ~PhysXWorld() override;
    void step(float fixedTimeStep) override;
    void setGravity(float x, float y, float z) override;
    void setAllowSleep(bool v) override;
    void emitEvents() override;
    void setCollisionMatrix(uint32_t index, uint32_t mask) override;
    bool raycast(RaycastOptions &opt) override;
    bool raycastClosest(RaycastOptions &opt) override;
    std::vector<RaycastResult> &raycastResult() override;
    RaycastResult &raycastClosestResult() override;
    uintptr_t createConvex(ConvexDesc &desc) override;
    uintptr_t createTrimesh(TrimeshDesc &desc) override;
    uintptr_t createHeightField(HeightFieldDesc &desc) override;
    uintptr_t createMaterial(uint16_t id, float f, float df, float r,
                                    uint8_t m0, uint8_t m1) override;
    CC_INLINE std::vector<std::shared_ptr<TriggerEventPair>> &getTriggerEventPairs() override {
        return _mEventMgr->getTriggerPairs();
    }
    CC_INLINE std::vector<std::shared_ptr<ContactEventPair>> &getContactEventPairs() override {
        return _mEventMgr->getConatctPairs();
    }
    void syncSceneToPhysics() override;
    void syncSceneWithCheck() override;
    void destroy() override;

    CC_INLINE PhysXSharedBody *getSharedBody(
        const uint handle,
        PhysXRigidBody *const body = nullptr) {
        return PhysXSharedBody::getSharedBody(handle, this, body);
    }

    CC_INLINE physx::PxScene &getScene() const { return *_mScene; }
    uint32_t getMaskByIndex(uint32_t i);
    void syncPhysicsToScene();
    void addActor(PhysXSharedBody &sb);
    void removeActor(PhysXSharedBody &sb);

private:
    static PhysXWorld *instance;
    physx::PxFoundation *_mFoundation;
    physx::PxCooking *_mCooking;
    physx::PxPhysics *_mPhysics;
#ifdef CC_DEBUG
    physx::PxPvd *_mPvd;
#endif
    physx::PxDefaultCpuDispatcher *_mDispatcher;
    physx::PxScene *_mScene;
    PhysXEventManager *_mEventMgr;
    uint32_t _mCollisionMatrix[31];
    std::vector<PhysXSharedBody *> _mSharedBodies;
};

} // namespace physics
} // namespace cc
