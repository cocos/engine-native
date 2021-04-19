
#pragma once

#include "../spec/IWorld.h"
#include "./PhysXInc.h"
#include "base/Macros.h"
#include <memory>
#include <vector>

using namespace physx;

namespace cc {
namespace physics {

class PhysXEventManager final {
public:
    PhysXEventManager() {
        mCallback = new SimulationEventCallback(this);
    }

    ~PhysXEventManager() {
        delete mCallback;
    }

    struct SimulationEventCallback : public PxSimulationEventCallback {
        virtual void onConstraintBreak(PxConstraintInfo *, PxU32) override{};
        virtual void onWake(PxActor **, PxU32) override{};
        virtual void onSleep(PxActor **, PxU32) override{};
        virtual void onTrigger(PxTriggerPair *, PxU32) override;
        virtual void onContact(const PxContactPairHeader &, const PxContactPair *, PxU32) override;
        virtual void onAdvance(const PxRigidBody *const *, const PxTransform *, const PxU32) override{};
        PhysXEventManager *mManager;

    public:
        SimulationEventCallback(PhysXEventManager *m) : mManager(m) {}
    };

    CC_INLINE SimulationEventCallback &getEventCallback() { return *mCallback; }
    CC_INLINE std::vector<std::shared_ptr<TriggerEventPair>> &getTriggerPairs() { return mTriggerPairs; }
    CC_INLINE std::vector<std::shared_ptr<ContactEventPair>> &getConatctPairs() { return mConatctPairs; }
    void refreshPairs();

private:
    std::vector<std::shared_ptr<TriggerEventPair>> mTriggerPairs;
    std::vector<std::shared_ptr<ContactEventPair>> mConatctPairs;
    SimulationEventCallback *mCallback;
};

} // namespace physics
} // namespace cc
