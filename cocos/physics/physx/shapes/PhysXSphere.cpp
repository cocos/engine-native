
#include "PhysXSphere.h"
#include "../PhysXUtils.h"
#include "../PhysXWorld.h"
#include "PhysXShape.h"

namespace cc {
namespace physics {

PhysXSphere::PhysXSphere() : mRadius(0.5f),
                             PhysXShape(){};

PhysXSphere::~PhysXSphere(){};

void PhysXSphere::setRadius(float r) {
    mRadius = r;
    updateGeometry();
    getShape().setGeometry(getPxGeometry<PxSphereGeometry>());
}

void PhysXSphere::onComponentSet() {
    auto &phy = PhysXWorld::getPhysics();
    static auto const mat = phy.createMaterial(0.5, 0.5, 0.1);
    updateGeometry();
    mShape = phy.createShape(getPxGeometry<PxSphereGeometry>(), *mat, true);
}

void PhysXSphere::updateScale() {
    updateGeometry();
    getShape().setGeometry(getPxGeometry<PxSphereGeometry>());
    updateCenter();
}

void PhysXSphere::updateGeometry() {
    PxVec3 scale;
    PxSetVec3Ext(scale, getSharedBody().getNode().worldScale);
    auto &geo = getPxGeometry<PxSphereGeometry>();
    geo.radius = PxMax(mRadius * scale.abs().maxElement(), PX_NORMALIZATION_EPSILON);
}

} // namespace physics
} // namespace cc
