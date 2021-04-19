#include "PhysXFilterShader.h"

namespace cc {
namespace physics {

PxFilterFlags SimpleFilterShader(
    PxFilterObjectAttributes attributes0, PxFilterData fd0,
    PxFilterObjectAttributes attributes1, PxFilterData fd1,
    PxPairFlags &pairFlags, const void *, PxU32) {
    // group mask filter
    if (!(fd0.word0 & fd1.word1) || !(fd0.word1 & fd1.word0)) {
        return PxFilterFlag::eSUPPRESS;
    }

    if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1)) {
        pairFlags = PxPairFlag::eTRIGGER_DEFAULT | PxPairFlag::eDETECT_CCD_CONTACT;
        return PxFilterFlag::eDEFAULT;
    }
    pairFlags = PxPairFlag::eCONTACT_DEFAULT | PxPairFlag::eNOTIFY_TOUCH_FOUND | PxPairFlag::eNOTIFY_TOUCH_LOST | PxPairFlag::eNOTIFY_TOUCH_PERSISTS | PxPairFlag::eDETECT_CCD_CONTACT | PxPairFlag::eNOTIFY_CONTACT_POINTS;
    return PxFilterFlag::eDEFAULT;
}

PxFilterFlags AdvanceFilterShader(
    PxFilterObjectAttributes attributes0, PxFilterData fd0,
    PxFilterObjectAttributes attributes1, PxFilterData fd1,
    PxPairFlags &pairFlags, const void *, PxU32) {
    // constexpr PxU32 QUERY_FILTER = 1 << 0;
    // constexpr PxU32 QUERY_CHECK_TRIGGER = 1 << 1;
    // constexpr PxU32 QUERY_SINGLE_HIT = 1 << 2;
    constexpr PxU32 DETECT_TRIGGER_EVENT = 1 << 3;
    constexpr PxU32 DETECT_CONTACT_EVENT = 1 << 4;
    constexpr PxU32 DETECT_CONTACT_POINT = 1 << 5;
    constexpr PxU32 DETECT_CONTACT_CCD = 1 << 6;
    // group mask filter
    if (!(fd0.word0 & fd1.word1) || !(fd0.word1 & fd1.word0)) {
        return PxFilterFlag::eSUPPRESS;
    }

    pairFlags = PxPairFlags(0);

    // trigger filter
    if (PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1)) {
        pairFlags |= PxPairFlag::eDETECT_DISCRETE_CONTACT;

        // need trigger event?
        const PxU16 needTriggerEvent = (fd0.word3 & DETECT_TRIGGER_EVENT) | (fd1.word3 & DETECT_TRIGGER_EVENT);
        if (needTriggerEvent) {
            pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND | PxPairFlag::eNOTIFY_TOUCH_LOST;
            return PxFilterFlag::eDEFAULT;
        } else {
            return PxFilterFlag::eSUPPRESS;
        }
    }

    // need detect ccd contact?
    const PxU16 needDetectCCD = (fd0.word3 & DETECT_CONTACT_CCD) | (fd1.word3 & DETECT_CONTACT_CCD);
    if (needDetectCCD) pairFlags |= PxPairFlag::eDETECT_CCD_CONTACT;

    // simple collision process
    pairFlags |= PxPairFlag::eCONTACT_DEFAULT;

    // need contact event?
    const PxU16 needContactEvent = (fd0.word3 & DETECT_CONTACT_EVENT) | (fd1.word3 & DETECT_CONTACT_EVENT);
    if (needContactEvent) pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND | PxPairFlag::eNOTIFY_TOUCH_LOST | PxPairFlag::eNOTIFY_TOUCH_PERSISTS;

    // need contact point?
    const PxU16 needContactPoint = (fd0.word3 & DETECT_CONTACT_POINT) | (fd1.word3 & DETECT_CONTACT_POINT);
    if (needContactPoint) pairFlags |= PxPairFlag::eNOTIFY_CONTACT_POINTS;

    return PxFilterFlag::eDEFAULT;
}

} // namespace physics
} // namespace cc