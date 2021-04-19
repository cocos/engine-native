
#pragma once

#include "./PhysXInc.h"

namespace cc {
namespace physics {

constexpr physx::PxU32 QUERY_FILTER         = 1 << 0;
constexpr physx::PxU32 QUERY_CHECK_TRIGGER  = 1 << 1;
constexpr physx::PxU32 QUERY_SINGLE_HIT     = 1 << 2;
constexpr physx::PxU32 DETECT_TRIGGER_EVENT = 1 << 3;
constexpr physx::PxU32 DETECT_CONTACT_EVENT = 1 << 4;
constexpr physx::PxU32 DETECT_CONTACT_POINT = 1 << 5;
constexpr physx::PxU32 DETECT_CONTACT_CCD   = 1 << 6;

physx::PxFilterFlags simpleFilterShader(
    physx::PxFilterObjectAttributes attributes0, physx::PxFilterData fd0,
    physx::PxFilterObjectAttributes attributes1, physx::PxFilterData fd1,
    physx::PxPairFlags &pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize);

physx::PxFilterFlags advanceFilterShader(
    physx::PxFilterObjectAttributes attributes0, physx::PxFilterData fd0,
    physx::PxFilterObjectAttributes attributes1, physx::PxFilterData fd1,
    physx::PxPairFlags &pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize);

class QueryFilterShader : public physx::PxSceneQueryFilterCallback {
public:
    physx::PxQueryHitType::Enum preFilter(const physx::PxFilterData &filterData, const physx::PxShape *shape,
                                                  const physx::PxRigidActor *actor, physx::PxHitFlags &queryFlags) override;
    physx::PxQueryHitType::Enum postFilter(const physx::PxFilterData & filterData, const physx::PxQueryHit & hit) override {
        PX_UNUSED(filterData);
        PX_UNUSED(hit);
        return physx::PxQueryHitType::eNONE;
    };
};

} // namespace physics
} // namespace cc
