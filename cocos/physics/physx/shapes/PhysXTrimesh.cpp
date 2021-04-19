
#include "physics/physx/shapes/PhysXShape.h"
#include "physics/physx/shapes/PhysXTrimesh.h"
#include "physics/physx/PhysXUtils.h"
#include "physics/physx/PhysXWorld.h"
#include "renderer/pipeline/helper/SharedMemory.h"

namespace cc {
namespace physics {

PhysXTrimesh::PhysXTrimesh() : _mMeshHandle(0),
                               _mConvex(false){};

void PhysXTrimesh::setMesh(uintptr_t handle) {
    if (_mMeshHandle == handle) return;
    _mMeshHandle = handle;
    if (_mShape) {
    }
}

void PhysXTrimesh::useConvex(bool v) {
    if (_mConvex == v) return;
    _mConvex = v;
    if (_mShape) {
    }
}

void PhysXTrimesh::onComponentSet() {
    if (_mMeshHandle) {
        const auto &mat = getDefaultMaterial();
        if (_mConvex) {
            physx::PxConvexMeshGeometry geom;
            geom.convexMesh = reinterpret_cast<physx::PxConvexMesh *>(_mMeshHandle);
            // geom.meshFlags = PxConvexMeshGeometryFlags::eTIGHT_BOUNDS;
            _mShape = PxGetPhysics().createShape(geom, mat, true);
        } else {
            physx::PxTriangleMeshGeometry geom;
            geom.triangleMesh = reinterpret_cast<physx::PxTriangleMesh *>(_mMeshHandle);
            // geom.meshFlags = PxMeshGeometryFlag::eDOUBLE_SIDED;
            _mShape = PxGetPhysics().createShape(geom, mat, true);
        }
        updateGeometry();
    }
}

void PhysXTrimesh::updateScale() {
    updateGeometry();
    updateCenter();
}

void PhysXTrimesh::updateGeometry() {
    static physx::PxMeshScale scale;
    scale.rotation = physx::PxQuat{physx::PxIdentity};
    pxSetVec3Ext(scale.scale, getSharedBody().getNode().worldScale);
    const auto &type = _mShape->getGeometryType();
    if (type == physx::PxGeometryType::eCONVEXMESH) {
        physx::PxConvexMeshGeometry geom;
        if (getShape().getConvexMeshGeometry(geom)) {
            geom.scale = scale;
            getShape().setGeometry(geom);
        }
    } else if (type == physx::PxGeometryType::eTRIANGLEMESH) {
        physx::PxTriangleMeshGeometry geom;
        if (getShape().getTriangleMeshGeometry(geom)) {
            geom.scale = scale;
            getShape().setGeometry(geom);
        }
    }
}

} // namespace physics
} // namespace cc
