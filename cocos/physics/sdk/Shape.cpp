
#include "Shape.h"
#include "../PhysicsSelector.h"

#define CC_PHYSICS_SHAPE_DEFINITION(CLASS, WRAPPED)                        \
                                                                           \
    CLASS::CLASS() {                                                       \
        _impl.reset(new WRAPPED());                                        \
    }                                                                      \
                                                                           \
    CLASS::~CLASS() {                                                      \
        _impl.reset(nullptr);                                              \
    }                                                                      \
                                                                           \
    intptr_t CLASS::getImpl() {                                            \
        return _impl->getImpl();                                           \
    }                                                                      \
                                                                           \
    void CLASS::initialize(const uint uuid) {                              \
        _impl->initialize(uuid);                                           \
    }                                                                      \
                                                                           \
    void CLASS::onEnable() {                                               \
        _impl->onEnable();                                                 \
    }                                                                      \
                                                                           \
    void CLASS::onDisable() {                                              \
        _impl->onDisable();                                                \
    }                                                                      \
                                                                           \
    void CLASS::onDestroy() {                                              \
        _impl->onDestroy();                                                \
    }                                                                      \
                                                                           \
    void CLASS::setMaterial(const uint16_t ID, float f, float df, float r, \
                            uint8_t m0, uint8_t m1) {                      \
        _impl->setMaterial(ID, f, df, r, m0, m1);                          \
    }                                                                      \
                                                                           \
    void CLASS::setAsTrigger(bool v) {                                     \
        _impl->setAsTrigger(v);                                            \
    }                                                                      \
                                                                           \
    void CLASS::setCenter(float x, float y, float z) {                     \
        _impl->setCenter(x, y, z);                                         \
    }                                                                      \
                                                                           \
    void CLASS::setGroup(uint32_t g) {                                     \
        _impl->setGroup(g);                                                \
    }                                                                      \
                                                                           \
    uint32_t CLASS::getGroup() {                                           \
        return _impl->getGroup();                                          \
    }                                                                      \
                                                                           \
    void CLASS::setMask(uint32_t m) {                                      \
        _impl->setMask(m);                                                 \
    }                                                                      \
                                                                           \
    uint32_t CLASS::getMask() {                                            \
        return _impl->getMask();                                           \
    }                                                                      \
                                                                           \
    void CLASS::updateEventListener(EShapeFilterFlag v) {                  \
        _impl->updateEventListener(v);                                     \
    }                                                                      \
                                                                           \
    cc::pipeline::AABB CLASS::getAABB() {                                  \
        return _impl->getAABB();                                           \
    }                                                                      \
                                                                           \
    cc::pipeline::Sphere CLASS::getBoundingSphere() {                      \
        return _impl->getBoundingSphere();                                 \
    }

namespace cc {
namespace physics {

/// COMMON ///

CC_PHYSICS_SHAPE_DEFINITION(SphereShape, WrappedSphereShape)
CC_PHYSICS_SHAPE_DEFINITION(BoxShape, WrappedBoxShape)
CC_PHYSICS_SHAPE_DEFINITION(PlaneShape, WrappedPlaneShape)
CC_PHYSICS_SHAPE_DEFINITION(CapsuleShape, WrappedCapsuleShape)
CC_PHYSICS_SHAPE_DEFINITION(CylinderShape, WrappedCylinderShape)
CC_PHYSICS_SHAPE_DEFINITION(ConeShape, WrappedConeShape)
CC_PHYSICS_SHAPE_DEFINITION(TrimeshShape, WrappedTrimeshShape)
CC_PHYSICS_SHAPE_DEFINITION(TerrainShape, WrappedTerrainShape)

/// EXTRAS ///

void SphereShape::setRadius(float v) {
    _impl->setRadius(v);
}

void BoxShape::setSize(float x, float y, float z) {
    _impl->setSize(x, y, z);
}

void CapsuleShape::setRadius(float v) {
    _impl->setRadius(v);
}

void CapsuleShape::setCylinderHeight(float v) {
    _impl->setCylinderHeight(v);
}

void CapsuleShape::setDirection(EAxisDirection v) {
    _impl->setDirection(v);
}

void PlaneShape::setConstant(float v) {
    _impl->setConstant(v);
}

void PlaneShape::setNormal(float x, float y, float z) {
    _impl->setNormal(x, y, z);
}

void TrimeshShape::setMesh(intptr_t v) {
    _impl->setMesh(v);
}

void TrimeshShape::useConvex(bool v) {
    _impl->useConvex(v);
}

void TerrainShape::setTerrain(intptr_t v, float rs, float cs, float hs) {
    _impl->setTerrain(v, rs, cs, hs);
}

void CylinderShape::setConvex(intptr_t v) {
    _impl->setConvex(v);
}

void CylinderShape::setCylinder(float r, float h, EAxisDirection d) {
    _impl->setCylinder(r, h, d);
}

void ConeShape::setConvex(intptr_t v) {
    _impl->setConvex(v);
}

void ConeShape::setCone(float r, float h, EAxisDirection d) {
    _impl->setCone(r, h, d);
}

} // namespace physics
} // namespace cc
