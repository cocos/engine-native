
#include "PhysXUtils.h"

namespace cc {
namespace physics {

void PxSetFromTwoVectors(PxQuat &out, const PxVec3 &a, const PxVec3 &b) {
    float dot = a.dot(b);
    if (dot < -0.999999) {
        PxVec3 c = (PxVec3{1., 0., 0.}).cross(a);
        if (c.magnitude() < 0.000001) c = (PxVec3{0., 1., 0.}).cross(a);
        c.normalize();
        out = PxQuat(PxPi, c);
    } else if (dot > 0.999999) {
        out = PxQuat{PxIdentity};
    } else {
        PxVec3 c = a.cross(b);
        out = PxQuat{c.x, c.y, c.z, 1 + dot};
        out.normalize();
    }
}

PxRigidActor &getTempRigidActor() {
    static PxRigidActor *tempRigidActor = nullptr;
    if (!tempRigidActor)
        tempRigidActor = PxGetPhysics().createRigidDynamic(PxTransform{PxIdentity});
    return *tempRigidActor;
}

} // namespace physics
} // namespace cc
