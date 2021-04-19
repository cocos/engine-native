
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
    virtual void step(float fixedTimeStep) override;
    virtual void emitEvents() override;
    virtual void syncSceneToPhysics() override;
    virtual void syncSceneWithCheck() override;
    virtual void setCollisionMatrix(uint32_t i, uint32_t m) override;
    virtual std::vector<std::shared_ptr<TriggerEventPair>> &getTriggerEventPairs() override;
    virtual std::vector<std::shared_ptr<ContactEventPair>> &getContactEventPairs() override;
    virtual bool raycast(RaycastOptions &opt) override;
    virtual bool raycastClosest(RaycastOptions &opt) override;
    virtual std::vector<RaycastResult> &raycastResult() override;
    virtual RaycastResult &raycastClosestResult() override;
    virtual intptr_t createConvex(ConvexDesc &desc) override;
    virtual intptr_t createTrimesh(TrimeshDesc &desc) override;
    virtual intptr_t createHeightField(HeightFieldDesc &desc) override;
    virtual intptr_t createMaterial(const uint16_t ID, float f, float df, float r,
                                    uint8_t m0, uint8_t m1) override;
    virtual void destroy() override;

private:
    std::unique_ptr<IPhysicsWorld> _impl;
};
} // namespace physics
} // namespace cc
