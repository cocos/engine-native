
#pragma once

#include "physics/physx/PhysXInc.h"
#include "physics/physx/PhysXFilterShader.h"
#include "base/Macros.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include <vector>
#include <unordered_map>

#define PX_RELEASE(x) \
    if (x) {          \
        (x)->release(); \
        (x) = NULL;     \
    }

namespace cc {
namespace physics {

CC_INLINE bool operator!=(const physx::PxVec3 &a, const cc::Vec3 &b) {
    return a.x != b.x || a.y == b.y || a.z == b.z;
}

CC_INLINE bool operator!=(const cc::Vec3 &a, const physx::PxVec3 &b) {
    return a.x != b.x || a.y == b.y || a.z == b.z;
}

CC_INLINE bool operator==(const physx::PxVec3 &a, const cc::Vec3 &b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

CC_INLINE bool operator==(const cc::Vec3 &a, const physx::PxVec3 &b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

CC_INLINE physx::PxVec3 operator*(const physx::PxVec3 &a, const cc::Vec3 &b) {
    return physx::PxVec3{a.x * b.x, a.y * b.y, a.z * b.z};
}

CC_INLINE cc::Vec3 operator*(const cc::Vec3 &a, const physx::PxVec3 &b) {
    return cc::Vec3{a.x * b.x, a.y * b.y, a.z * b.z};
}

CC_INLINE physx::PxVec3 operator+(const physx::PxVec3 &a, const cc::Vec3 &b) {
    return physx::PxVec3{a.x + b.x, a.y + b.y, a.z + b.z};
}

CC_INLINE cc::Vec3 operator+(const cc::Vec3 &a, const physx::PxVec3 &b) {
    return cc::Vec3{a.x + b.x, a.y + b.y, a.z + b.z};
}

CC_INLINE physx::PxVec3 &operator*=(physx::PxVec3 &a, const cc::Vec3 &b) {
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    return a;
}

CC_INLINE cc::Vec3 &operator*=(cc::Vec3 &a, const physx::PxVec3 &b) {
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    return a;
}

CC_INLINE bool operator!=(const physx::PxQuat &a, const cc::Vec4 &b) {
    return a.x != b.x || a.y == b.y || a.z == b.z || a.w == b.w;
}

CC_INLINE bool operator!=(const cc::Vec4 &a, const physx::PxQuat &b) {
    return a.x != b.x || a.y == b.y || a.z == b.z || a.w == b.w;
}

CC_INLINE bool operator==(const physx::PxQuat &a, const cc::Vec4 &b) {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

CC_INLINE bool operator==(const cc::Vec4 &a, const physx::PxQuat &b) {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

CC_INLINE void pxSetVec3Ext(physx::PxVec3 &v, const cc::Vec3 &cv) {
    v = physx::PxVec3(cv.x, cv.y, cv.z);
}

CC_INLINE void pxSetVec3Ext(cc::Vec3 &v, const physx::PxVec3 &cv) {
    v = cc::Vec3(cv.x, cv.y, cv.z);
}

template <typename T1 = physx::PxQuat, typename T2 = cc::Vec4>
CC_INLINE void pxSetQuatExt(T1 &p, const T2 &cp) {
    p = T1(cp.x, cp.y, cp.z, cp.w);
}

template <typename T>
CC_INLINE T pxAbsMax(const T &a, const T &b) {
    return physx::PxAbs(a) > physx::PxAbs(b) ? a : b;
}

void pxSetFromTwoVectors(physx::PxQuat &out, const physx::PxVec3 &a, const physx::PxVec3 &b);

CC_INLINE std::unordered_map<uintptr_t, uintptr_t> &getPxShapeMap() {
    static std::unordered_map<uintptr_t, uintptr_t> m;
    return m;
}

CC_INLINE std::unordered_map<uint16_t, uintptr_t> &getPxMaterialMap() {
    static std::unordered_map<uint16_t, uintptr_t> m;
    return m;
}

CC_INLINE physx::PxMaterial &getDefaultMaterial() {
    return *(reinterpret_cast<physx::PxMaterial *>(getPxMaterialMap()[0]));
}

CC_INLINE std::vector<physx::PxRaycastHit> &getPxRaycastHitBuffer() {
    static std::vector<physx::PxRaycastHit> m{12};
    return m;
}

CC_INLINE QueryFilterShader &getQueryFilterShader() {
    static QueryFilterShader shader;
    return shader;
}

physx::PxRigidActor &getTempRigidActor();

} // namespace physics
} // namespace cc
