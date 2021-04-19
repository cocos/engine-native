
#include "PhysXBox.h"
#include "../PhysXWorld.h"
#include "PhysXShape.h"

namespace cc {
namespace physics {

PhysXBox::PhysXBox() : PhysXShape(){};

PhysXBox::~PhysXBox(){};

void PhysXBox::setSize(float x, float y, float z) {
}

void PhysXBox::onComponentSet() {
    updateGeometry();
    auto &phy = PhysXWorld::getPhysics();
    static auto mat = phy.createMaterial(0.5, 0.5, 0.1);
    mShape = phy.createShape(getPxGeometry<PxBoxGeometry>(), *mat);
}

void PhysXBox::updateScale() {
    updateGeometry();
    getShape().setGeometry(getPxGeometry<PxBoxGeometry>());
}

void PhysXBox::updateGeometry() {
    auto &geo = getPxGeometry<PxBoxGeometry>();
    geo.halfExtents = PxVec3{0.5, 0.5, 0.5};
    auto &node = getSharedBody().getNode();
}

} // namespace physics
} // namespace cc
