
#include "PhysXTrimesh.h"
#include "../PhysXUtils.h"
#include "../PhysXWorld.h"
#include "PhysXShape.h"
#include "renderer/pipeline/helper/SharedMemory.h"

namespace cc {
namespace physics {

PhysXTrimesh::PhysXTrimesh() : mMeshHandle(NULL),
                               mConvex(false),
                               PhysXShape(){};

void PhysXTrimesh::setMesh(intptr_t handle) {
    if (mMeshHandle == handle) return;
    mMeshHandle = handle;
    if (mShape) {
        // TODO: ...
    }
}

void PhysXTrimesh::useConvex(bool v) {
    if (mConvex == v) return;
    mConvex = v;
    if (mShape) {
        // TODO: ...
    }
}

void PhysXTrimesh::onComponentSet() {
    if (mMeshHandle) {
        const auto &mat = getDefaultMaterial();
        if (mConvex) {
            PxConvexMeshGeometry geom;
            geom.convexMesh = (PxConvexMesh *)mMeshHandle;
            // geom.meshFlags = PxConvexMeshGeometryFlags::eTIGHT_BOUNDS;
            mShape = PxGetPhysics().createShape(geom, mat, true);
        } else {
            PxTriangleMeshGeometry geom;
            geom.triangleMesh = (PxTriangleMesh *)mMeshHandle;
            // geom.meshFlags = PxMeshGeometryFlag::eDOUBLE_SIDED;
            mShape = PxGetPhysics().createShape(geom, mat, true);
        }
        updateGeometry();
    }
}

void PhysXTrimesh::updateScale() {
    updateGeometry();
    updateCenter();
}

void PhysXTrimesh::updateGeometry() {
    static PxMeshScale scale;
    scale.rotation = PxQuat{PxIdentity};
    PxSetVec3Ext(scale.scale, getSharedBody().getNode().worldScale);
    const auto &type = mShape->getGeometryType();
    if (type == PxGeometryType::eCONVEXMESH) {
        PxConvexMeshGeometry geom;
        if (getShape().getConvexMeshGeometry(geom)) {
            geom.scale = scale;
            getShape().setGeometry(geom);
        }
    } else if (type == PxGeometryType::eTRIANGLEMESH) {
        PxTriangleMeshGeometry geom;
        if (getShape().getTriangleMeshGeometry(geom)) {
            geom.scale = scale;
            getShape().setGeometry(geom);
        }
    }
}

} // namespace physics
} // namespace cc
