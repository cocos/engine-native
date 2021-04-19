
#include "PhysXBox.h"
#include "../PhysXUtils.h"
#include "../PhysXWorld.h"
#include "PhysXShape.h"

namespace cc {
namespace physics {

PhysXBox::PhysXBox() : mHalfExtents(0.5f),
                       PhysXShape(){};

PhysXBox::~PhysXBox(){};

void PhysXBox::setSize(float x, float y, float z) {
    mHalfExtents = PxVec3{x / 2, y / 2, z / 2};
    updateGeometry();
    getShape().setGeometry(getPxGeometry<PxBoxGeometry>());
}

void PhysXBox::onComponentSet() {
    auto &phy = PxGetPhysics();
    static auto mat = phy.createMaterial(0.5, 0.5, 0.1);
    updateGeometry();
    mShape = phy.createShape(getPxGeometry<PxBoxGeometry>(), *mat, true);
}

void PhysXBox::updateScale() {
    updateGeometry();
    getShape().setGeometry(getPxGeometry<PxBoxGeometry>());
    updateCenter();
}

void PhysXBox::updateGeometry() {
    auto &node = getSharedBody().getNode();
    auto &geo = getPxGeometry<PxBoxGeometry>();
    geo.halfExtents = mHalfExtents;
    geo.halfExtents *= node.worldScale;
    geo.halfExtents = geo.halfExtents.abs();
    if (geo.halfExtents.minElement() <= 0.0) {
        geo.halfExtents = geo.halfExtents.maximum(PxVec3{PX_NORMALIZATION_EPSILON});
    }
}

} // namespace physics
} // namespace cc
