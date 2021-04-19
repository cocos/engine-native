
#include "PhysXSphere.h"
#include "../PhysXWorld.h"
#include "PhysXShape.h"

namespace cc {
namespace physics {

PhysXSphere::PhysXSphere() : PhysXShape(){};

PhysXSphere::~PhysXSphere(){};

void PhysXSphere::setRadius(float r){};

void PhysXSphere::onComponentSet() {
	updateGeometry();
    auto &phy = PhysXWorld::getPhysics();
    static auto const mat = phy.createMaterial(0.5, 0.5, 0.1);    
    auto &geo = getPxGeometry<PxSphereGeometry>();
    mShape = phy.createShape(geo, *mat);
}

void PhysXSphere::updateScale() {
	updateGeometry();
}

void PhysXSphere::updateGeometry() {
	auto &geo = getPxGeometry<PxSphereGeometry>();
	geo.radius = 0.5;
}

} // namespace physics
} // namespace cc
