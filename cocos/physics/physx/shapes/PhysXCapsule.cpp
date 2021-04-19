
#include "physics/physx/shapes/PhysXShape.h"
#include "physics/physx/shapes/PhysXCapsule.h"
#include "physics/physx/PhysXUtils.h"
#include "physics/physx/PhysXWorld.h"

namespace cc {
namespace physics {

PhysXCapsule::PhysXCapsule() : _mRadius(0.5F),
                               _mCylinderHeight(1.0F),
                               _mDirection(EAxisDirection::Y_AXIS)
                               {};

void PhysXCapsule::setRadius(float r) {
    _mRadius = r;
    updateGeometry();
    getShape().setGeometry(getPxGeometry<physx::PxCapsuleGeometry>());
}

void PhysXCapsule::setCylinderHeight(float v) {
    _mCylinderHeight = v;
    updateGeometry();
    getShape().setGeometry(getPxGeometry<physx::PxCapsuleGeometry>());
}

void PhysXCapsule::setDirection(EAxisDirection v) {
    _mDirection = v;
    updateGeometry();
    getShape().setGeometry(getPxGeometry<physx::PxCapsuleGeometry>());
}

void PhysXCapsule::onComponentSet() {
    updateGeometry();
    _mShape = PxGetPhysics().createShape(getPxGeometry<physx::PxCapsuleGeometry>(), getDefaultMaterial(), true);
}

void PhysXCapsule::updateScale() {
    updateGeometry();
    getShape().setGeometry(getPxGeometry<physx::PxCapsuleGeometry>());
    updateCenter();
}

void PhysXCapsule::updateGeometry() {
    auto &node = getSharedBody().getNode();
    auto &geo = getPxGeometry<physx::PxCapsuleGeometry>();
    float rs = 1.F;
    float hs = 1.F;
    switch (_mDirection) {
        case EAxisDirection::X_AXIS:
            hs = physx::PxAbs(node.worldScale.x);
            rs = pxAbsMax(node.worldScale.y, node.worldScale.z);
            _mRotation = physx::PxQuat{physx::PxIdentity};
            break;
        case EAxisDirection::Z_AXIS:
            hs = physx::PxAbs(node.worldScale.z);
            rs = pxAbsMax(node.worldScale.x, node.worldScale.y);
            _mRotation = physx::PxQuat(physx::PxPiDivTwo, physx::PxVec3{0.F, 1.F, 0.F});
            break;
        case EAxisDirection::Y_AXIS:
        default:
            hs = physx::PxAbs(node.worldScale.y);
            rs = pxAbsMax(node.worldScale.x, node.worldScale.z);
            _mRotation = physx::PxQuat(physx::PxPiDivTwo, physx::PxVec3{0.F, 0.F, 1.F});
            break;
    }
    geo.radius = physx::PxMax(physx::PxAbs(_mRadius * rs), PX_NORMALIZATION_EPSILON);
    geo.halfHeight = physx::PxMax(physx::PxAbs(_mCylinderHeight / 2 * hs), PX_NORMALIZATION_EPSILON);
}

} // namespace physics
} // namespace cc
