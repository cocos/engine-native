
#pragma once

#include "physics/spec/IWorld.h"
#include "physics/physx/PhysXInc.h"
#include "base/Macros.h"
#include <memory>
#include <vector>

namespace cc {
namespace physics {

class PhysXEventManager final {
public:
    PhysXEventManager() {
        _mCallback = new SimulationEventCallback(this);
    }

    ~PhysXEventManager() {
        delete _mCallback;
    }

    struct SimulationEventCallback : public physx::PxSimulationEventCallback {
        void onConstraintBreak(physx::PxConstraintInfo * /*constraints*/, physx::PxU32 /*count*/) override{};
        void onWake(physx::PxActor ** /*actors*/, physx::PxU32 /*count*/) override{};
        void onSleep(physx::PxActor ** /*actors*/, physx::PxU32 /*count*/) override{};
        void onTrigger(physx::PxTriggerPair * /*pairs*/, physx::PxU32 /*count*/) override;
        void onContact(const physx::PxContactPairHeader & /*pairHeader*/, const physx::PxContactPair * /*pairs*/, physx::PxU32 /*nbPairs*/) override;
        void onAdvance(const physx::PxRigidBody *const * /*bodyBuffer*/, const physx::PxTransform * /*poseBuffer*/, const physx::PxU32 /*count*/) override{};
        PhysXEventManager *mManager;

    public:
        explicit SimulationEventCallback(PhysXEventManager *m) : mManager(m) {}
    };

    CC_INLINE SimulationEventCallback &getEventCallback() { return *_mCallback; }
    CC_INLINE std::vector<std::shared_ptr<TriggerEventPair>> &getTriggerPairs() { return _mTriggerPairs; }
    CC_INLINE std::vector<std::shared_ptr<ContactEventPair>> &getConatctPairs() { return _mConatctPairs; }
    void refreshPairs();

private:
    std::vector<std::shared_ptr<TriggerEventPair>> _mTriggerPairs;
    std::vector<std::shared_ptr<ContactEventPair>> _mConatctPairs;
    SimulationEventCallback *_mCallback;
};

} // namespace physics
} // namespace cc
