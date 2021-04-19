
#include "physics/physx/PhysXUtils.h"

namespace cc {
namespace physics {

void pxSetFromTwoVectors(physx::PxQuat &out, const physx::PxVec3 &a, const physx::PxVec3 &b) {
    float dot = a.dot(b);
    if (dot < -0.999999) {
        physx::PxVec3 c = (physx::PxVec3{1., 0., 0.}).cross(a);
        if (c.magnitude() < 0.000001) c = (physx::PxVec3{0., 1., 0.}).cross(a);
        c.normalize();
        out = physx::PxQuat(physx::PxPi, c);
    } else if (dot > 0.999999) {
        out = physx::PxQuat{physx::PxIdentity};
    } else {
        physx::PxVec3 c = a.cross(b);
        out             = physx::PxQuat{c.x, c.y, c.z, 1 + dot};
        out.normalize();
    }
}

physx::PxRigidActor &getTempRigidActor() {
    static physx::PxRigidActor *tempRigidActor = nullptr;
    if (!tempRigidActor) {
        tempRigidActor = PxGetPhysics().createRigidDynamic(physx::PxTransform{physx::PxIdentity});
    }
    return *tempRigidActor;
}

} // namespace physics
} // namespace cc
