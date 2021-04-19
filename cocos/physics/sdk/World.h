
#pragma once

#include "../spec/IWorld.h"
#include "base/Macros.h"
#include <memory>

namespace cc {
namespace physics {
class CC_DLL World final : public IPhysicsWorld {
public:
    World();
    virtual ~World();
    virtual void setGravity(float x, float y, float z) override;
    virtual void setAllowSleep(bool v) override;
    virtual void setDefaultMaterial(float f, float dy, float r) override;
    virtual void step(float fixedTimeStep) override;
    // virtual bool raycast (worldRay: Ray, options: IRaycastOptions, pool: RecyclePool<PhysicsRayResult>, results: PhysicsRayResult[])=0;
    // virtual bool raycastClosest (worldRay: Ray, options: IRaycastOptions, out: PhysicsRayResult)=0;
    virtual void emitEvents() override;
    virtual std::vector<TriggerEventPair> &getTriggerEventPairs() override;
    virtual std::vector<ContactEventPair> &getContactEventPairs() override;
    virtual void syncSceneToPhysics() override;
    virtual void syncSceneWithCheck() override;
    virtual void destroy() override;

private:
    std::unique_ptr<IPhysicsWorld> _impl;
};
} // namespace physics
} // namespace cc
