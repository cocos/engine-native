

#include <PhysX/PxPhysicsAPI.h>

using namespace physx;

namespace cc {
namespace physics {

PxFilterFlags SimpleFilterShader(
    PxFilterObjectAttributes attributes0, PxFilterData fd0,
    PxFilterObjectAttributes attributes1, PxFilterData fd1,
    PxPairFlags &pairFlags, const void *, PxU32);

PxFilterFlags AdvanceFilterShader(
    PxFilterObjectAttributes attributes0, PxFilterData fd0,
    PxFilterObjectAttributes attributes1, PxFilterData fd1,
    PxPairFlags &pairFlags, const void *, PxU32);

} // namespace physics
} // namespace cc
