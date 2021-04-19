
#pragma once

#include "bindings/manual/jsb_conversions.h"
#include <vector>

namespace cc {
namespace physics {

enum ETouchState : uint8_t {
    ENTER = 0,
    STAY = 1,
    EXIT = 2,
};

struct TriggerEventPair {
    intptr_t shapeA;
    intptr_t shapeB;
    ETouchState state;
    static constexpr uint8_t COUNT = 3;

public:
    CC_INLINE TriggerEventPair(const intptr_t a, const intptr_t b)
    : shapeA(a),
      shapeB(b),
      state(ETouchState::ENTER) {}
};

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
    virtual std::vector<TriggerEventPair> &getTriggerEventPairs() = 0;
    virtual void syncSceneToPhysics() = 0;
    virtual void syncSceneWithCheck() = 0;
    virtual void destroy() = 0;
};

} // namespace physics
} // namespace cc

template <>
inline bool nativevalue_to_se(const std::vector<cc::physics::TriggerEventPair> &from, se::Value &to, se::Object *ctx) {
    se::Object *array = se::Object::createArrayObject(from.size() * cc::physics::TriggerEventPair::COUNT);
    for (size_t i = 0; i < from.size(); i++) {
        uint32_t t = i * cc::physics::TriggerEventPair::COUNT;
        array->setArrayElement(t + 0, se::Value((intptr_t)from[i].shapeA));
        array->setArrayElement(t + 1, se::Value((intptr_t)from[i].shapeB));
        array->setArrayElement(t + 2, se::Value((uint8_t)from[i].state));
    }
    to.setObject(array);
    array->decRef();
    return true;
}
