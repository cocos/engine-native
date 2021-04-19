
#pragma once

#include "bindings/manual/jsb_conversions.h"
#include <stdint.h>
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

struct ContactPoint {
    Vec3 position;
    float separation;
    Vec3 normal;
    uint32_t internalFaceIndex0;
    Vec3 impulse;
    uint32_t internalFaceIndex1;
    static constexpr uint8_t COUNT = 12;
};

struct ContactEventPair {
    intptr_t shapeA;
    intptr_t shapeB;
    ETouchState state;
    std::vector<ContactPoint> contacts;
    static constexpr uint8_t COUNT = 4;

public:
    CC_INLINE ContactEventPair(const intptr_t a, const intptr_t b)
    : shapeA(a),
      shapeB(b),
      state(ETouchState::ENTER) {}
};

struct ConvexDesc {
    void *positions;
    uint32_t positionLength;
};

struct TrimeshDesc : ConvexDesc {
    void *triangles;
    uint32_t triangleLength;
    bool isU16;
};

struct HeightFieldDesc {
    uint32_t rows;
    uint32_t columns;
    void *samples;
};

class IPhysicsWorld {
public:
    virtual ~IPhysicsWorld(){};
    virtual void setGravity(float x, float y, float z) = 0;
    virtual void setAllowSleep(bool v) = 0;
    virtual void step(float fixedTimeStep) = 0;
    // virtual bool raycast (worldRay: Ray, options: IRaycastOptions, pool: RecyclePool<PhysicsRayResult>, results: PhysicsRayResult[])=0;
    // virtual bool raycastClosest (worldRay: Ray, options: IRaycastOptions, out: PhysicsRayResult)=0;
    virtual void emitEvents() = 0;
    virtual void syncSceneToPhysics() = 0;
    virtual void syncSceneWithCheck() = 0;
    virtual void destroy() = 0;
    virtual std::vector<TriggerEventPair> &getTriggerEventPairs() = 0;
    virtual std::vector<ContactEventPair> &getContactEventPairs() = 0;
    virtual void setCollisionMatrix(uint32_t index, uint32_t mask) = 0;
    virtual intptr_t createConvex(ConvexDesc &desc) = 0;
    virtual intptr_t createTrimesh(TrimeshDesc &desc) = 0;
    virtual intptr_t createHeightField(HeightFieldDesc &desc) = 0;
    virtual intptr_t createMaterial(const uint16_t ID, float f, float df, float r,
                                    uint8_t m0, uint8_t m1) = 0;
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

template <>
inline bool nativevalue_to_se(const std::vector<cc::physics::ContactPoint> &from, se::Value &to, se::Object *ctx) {
    const auto contactCount = from.size();
    auto array = se::Object::createArrayObject(contactCount);
    for (size_t i = 0; i < contactCount; i++) {
        uint32_t t = i * cc::physics::ContactPoint::COUNT;
        uint8_t j = 0;
        array->setArrayElement(t + j++, se::Value(from[i].position.x));
        array->setArrayElement(t + j++, se::Value(from[i].position.y));
        array->setArrayElement(t + j++, se::Value(from[i].position.z));
        array->setArrayElement(t + j++, se::Value(from[i].normal.x));
        array->setArrayElement(t + j++, se::Value(from[i].normal.y));
        array->setArrayElement(t + j++, se::Value(from[i].normal.z));
        array->setArrayElement(t + j++, se::Value(from[i].impulse.x));
        array->setArrayElement(t + j++, se::Value(from[i].impulse.y));
        array->setArrayElement(t + j++, se::Value(from[i].impulse.z));
        array->setArrayElement(t + j++, se::Value(from[i].separation));
        array->setArrayElement(t + j++, se::Value(from[i].internalFaceIndex0));
        array->setArrayElement(t + j++, se::Value(from[i].internalFaceIndex1));
    }
    to.setObject(array);
    array->decRef();
    return true;
}

template <>
inline bool nativevalue_to_se(const std::vector<cc::physics::ContactEventPair> &from, se::Value &to, se::Object *ctx) {
    se::Object *array = se::Object::createArrayObject(from.size() * cc::physics::ContactEventPair::COUNT);
    for (size_t i = 0; i < from.size(); i++) {
        uint32_t t = i * cc::physics::ContactEventPair::COUNT;
        array->setArrayElement(t + 0, se::Value((intptr_t)from[i].shapeA));
        array->setArrayElement(t + 1, se::Value((intptr_t)from[i].shapeB));
        array->setArrayElement(t + 2, se::Value((uint8_t)from[i].state));
        array->setArrayElement(t + 3, [&]() -> se::Value {
            auto obj = se::Value();
            nativevalue_to_se(from[i].contacts, obj, ctx);
            return obj;
        }());
    }
    to.setObject(array);
    array->decRef();
    return true;
}

template <>
inline bool sevalue_to_native(const se::Value &from, cc::physics::ConvexDesc *to, se::Object *ctx) {
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto *data = (cc::physics::ConvexDesc *)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }

    se::Value field;
    bool ok = true;

    json->getProperty("positionLength", &field);
    if (!field.isNullOrUndefined()) ok &= sevalue_to_native(field, &to->positionLength, ctx);

    CC_UNUSED size_t dataLength = 0;
    json->getProperty("positions", &field);
    if (!field.isNullOrUndefined()) {
        se::Object *obj = field.toObject();
        if (obj->isArrayBuffer()) {
            ok &= obj->getArrayBufferData((uint8_t **)&to->positions, &dataLength);
            SE_PRECONDITION2(ok, false, "getArrayBufferData failed!");
        } else if (obj->isTypedArray()) {
            ok &= obj->getTypedArrayData((uint8_t **)&to->positions, &dataLength);
            SE_PRECONDITION2(ok, false, "getTypedArrayData failed!");
        } else {
            ok &= false;
        }
    }
    return ok;
}

template <>
inline bool sevalue_to_native(const se::Value &from, cc::physics::TrimeshDesc *to, se::Object *ctx) {
    if (!sevalue_to_native(from, (cc::physics::ConvexDesc *)to, ctx))
        return false;

    assert(from.isObject());
    se::Object *json = from.toObject();
    auto *data = (cc::physics::TrimeshDesc *)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;

    json->getProperty("triangleLength", &field);
    if (!field.isNullOrUndefined()) ok &= sevalue_to_native(field, &(to->triangleLength), ctx);

    json->getProperty("isU16", &field);
    if (!field.isNullOrUndefined()) ok &= sevalue_to_native(field, &(to->isU16), ctx);

    CC_UNUSED size_t dataLength = 0;
    json->getProperty("triangles", &field);
    if (!field.isNullOrUndefined()) {
        se::Object *obj = field.toObject();
        if (obj->isArrayBuffer()) {
            ok &= obj->getArrayBufferData((uint8_t **)&to->triangles, &dataLength);
            SE_PRECONDITION2(ok, false, "getArrayBufferData failed!");
        } else if (obj->isTypedArray()) {
            ok &= obj->getTypedArrayData((uint8_t **)&to->triangles, &dataLength);
            SE_PRECONDITION2(ok, false, "getTypedArrayData failed!");
        } else {
            ok &= false;
        }
    }

    return ok;
}

template <>
inline bool sevalue_to_native(const se::Value &from, cc::physics::HeightFieldDesc *to, se::Object *ctx) {
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto *data = (cc::physics::HeightFieldDesc *)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }

    se::Value field;
    bool ok = true;

    json->getProperty("rows", &field);
    if (!field.isNullOrUndefined()) ok &= sevalue_to_native(field, &to->rows, ctx);

    json->getProperty("columns", &field);
    if (!field.isNullOrUndefined()) ok &= sevalue_to_native(field, &to->columns, ctx);

    CC_UNUSED size_t dataLength = 0;
    json->getProperty("samples", &field);
    if (!field.isNullOrUndefined()) {
        se::Object *obj = field.toObject();
        if (obj->isArrayBuffer()) {
            ok &= obj->getArrayBufferData((uint8_t **)&to->samples, &dataLength);
            SE_PRECONDITION2(ok, false, "getArrayBufferData failed!");
        } else if (obj->isTypedArray()) {
            ok &= obj->getTypedArrayData((uint8_t **)&to->samples, &dataLength);
            SE_PRECONDITION2(ok, false, "getTypedArrayData failed!");
        } else {
            ok &= false;
        }
    }
    return ok;
}

