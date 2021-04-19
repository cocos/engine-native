
#pragma once

#include "../spec/IWorld.h"
#include "base/Macros.h"
#include <memory>

namespace cc {
namespace physics {
class CC_DLL World final : public IPhysicsWorld {
public:
    World();
    ~World() override;
    void setGravity(float x, float y, float z) override;
    void setAllowSleep(bool v) override;
    void step(float fixedTimeStep) override;
    void emitEvents() override;
    void syncSceneToPhysics() override;
    void syncSceneWithCheck() override;
    void setCollisionMatrix(uint32_t i, uint32_t m) override;
    std::vector<std::shared_ptr<TriggerEventPair>> &getTriggerEventPairs() override;
    std::vector<std::shared_ptr<ContactEventPair>> &getContactEventPairs() override;
    bool raycast(RaycastOptions &opt) override;
    bool raycastClosest(RaycastOptions &opt) override;
    std::vector<RaycastResult> &raycastResult() override;
    RaycastResult &raycastClosestResult() override;
    uintptr_t createConvex(ConvexDesc &desc) override;
    uintptr_t createTrimesh(TrimeshDesc &desc) override;
    uintptr_t createHeightField(HeightFieldDesc &desc) override;
    uintptr_t createMaterial(uint16_t id, float f, float df, float r,
                                    uint8_t m0, uint8_t m1) override;
    void destroy() override;

private:
    std::unique_ptr<IPhysicsWorld> _impl;
};
} // namespace physics
} // namespace cc
