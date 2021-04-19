
#pragma once

#include "./PhysXInc.h"

using namespace physx;

namespace cc {
namespace physics {

constexpr PxU32 QUERY_FILTER = 1 << 0;
constexpr PxU32 QUERY_CHECK_TRIGGER = 1 << 1;
constexpr PxU32 QUERY_SINGLE_HIT = 1 << 2;
constexpr PxU32 DETECT_TRIGGER_EVENT = 1 << 3;
constexpr PxU32 DETECT_CONTACT_EVENT = 1 << 4;
constexpr PxU32 DETECT_CONTACT_POINT = 1 << 5;
constexpr PxU32 DETECT_CONTACT_CCD = 1 << 6;

PxFilterFlags SimpleFilterShader(
    PxFilterObjectAttributes attributes0, PxFilterData fd0,
    PxFilterObjectAttributes attributes1, PxFilterData fd1,
    PxPairFlags &pairFlags, const void *, PxU32);

PxFilterFlags AdvanceFilterShader(
    PxFilterObjectAttributes attributes0, PxFilterData fd0,
    PxFilterObjectAttributes attributes1, PxFilterData fd1,
    PxPairFlags &pairFlags, const void *, PxU32);

class QueryFilterShader : public PxSceneQueryFilterCallback {
public:
    virtual PxQueryHitType::Enum preFilter(const PxFilterData &filterData, const PxShape *shape,
                                           const PxRigidActor *actor, PxHitFlags &queryFlags) override;
    virtual PxQueryHitType::Enum postFilter(const PxFilterData &filterData, const PxQueryHit &hit) override {
        return PxQueryHitType::eNONE;
    };
};

} // namespace physics
} // namespace cc
