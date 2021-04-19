
#include "physics/physx/shapes/PhysXShape.h"
#include "physics/physx/shapes/PhysXBox.h"
#include "physics/physx/PhysXUtils.h"
#include "physics/physx/PhysXWorld.h"

namespace cc {
namespace physics {

PhysXBox::PhysXBox() : _mHalfExtents(0.5),
                       PhysXShape(){};

void PhysXBox::setSize(float x, float y, float z) {
    _mHalfExtents = physx::PxVec3{x / 2, y / 2, z / 2};
    updateGeometry();
    getShape().setGeometry(getPxGeometry<physx::PxBoxGeometry>());
}

void PhysXBox::onComponentSet() {
    updateGeometry();
    _mShape = PxGetPhysics().createShape(getPxGeometry<physx::PxBoxGeometry>(), getDefaultMaterial(), true);
}

void PhysXBox::updateScale() {
    updateGeometry();
    getShape().setGeometry(getPxGeometry<physx::PxBoxGeometry>());
    updateCenter();
}

void PhysXBox::updateGeometry() {
    auto &node = getSharedBody().getNode();
    auto &geo = getPxGeometry<physx::PxBoxGeometry>();
    geo.halfExtents = _mHalfExtents;
    geo.halfExtents *= node.worldScale;
    geo.halfExtents = geo.halfExtents.abs();
    if (geo.halfExtents.minElement() <= 0.0) {
        geo.halfExtents = geo.halfExtents.maximum(physx::PxVec3{PX_NORMALIZATION_EPSILON});
    }
}

} // namespace physics
} // namespace cc
