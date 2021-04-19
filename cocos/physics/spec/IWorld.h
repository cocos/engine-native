#pragma once

namespace cc {
namespace physics {

class IPhysicsWorld {
public:
    virtual ~IPhysicsWorld(){};
    virtual void setGravity(float x, float y, float z) = 0;
    virtual void setAllowSleep(bool v) = 0;
    virtual void setDefaultMaterial(float f, float dy, float r) = 0;
    virtual void step(float fixedTimeStep) = 0;
    // virtual bool raycast (worldRay: Ray, options: IRaycastOptions, pool: RecyclePool<PhysicsRayResult>, results: PhysicsRayResult[])=0;
    // virtual bool raycastClosest (worldRay: Ray, options: IRaycastOptions, out: PhysicsRayResult)=0;
    virtual void emitEvents() = 0;
    virtual void syncSceneToPhysics() = 0;
    virtual void syncSceneWithCheck() = 0;
    virtual void destroy() = 0;
};

} // namespace physics
} // namespace cc
