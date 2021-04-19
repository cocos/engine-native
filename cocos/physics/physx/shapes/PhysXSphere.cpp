
#include "PhysXShape.h"
#include "PhysXSphere.h"
#include "../PhysXUtils.h"
#include "../PhysXWorld.h"

namespace cc {
namespace physics {

PhysXSphere::PhysXSphere() : _mRadius(0.5F),
                             PhysXShape(){};

void PhysXSphere::setRadius(float r) {
    _mRadius = r;
    updateGeometry();
    getShape().setGeometry(getPxGeometry<physx::PxSphereGeometry>());
}

void PhysXSphere::onComponentSet() {
    updateGeometry();
    _mShape = PxGetPhysics().createShape(getPxGeometry<physx::PxSphereGeometry>(), getDefaultMaterial(), true);
}

void PhysXSphere::updateScale() {
    updateGeometry();
    getShape().setGeometry(getPxGeometry<physx::PxSphereGeometry>());
    updateCenter();
}

void PhysXSphere::updateGeometry() {
    physx::PxVec3 scale;
    pxSetVec3Ext(scale, getSharedBody().getNode().worldScale);
    auto &geo = getPxGeometry<physx::PxSphereGeometry>();
    geo.radius = physx::PxMax(_mRadius * scale.abs().maxElement(), PX_NORMALIZATION_EPSILON);
}

} // namespace physics
} // namespace cc
