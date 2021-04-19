
#include "Shape.h"
#include "../PhysicsSelector.h"

#define CC_PHYSICS_SHAPE_DEFINITION(Class, Wrapped)                        \
                                                                           \
    Class::Class() {                                                       \
        _impl.reset(new Wrapped());                                        \
    }                                                                      \
                                                                           \
    Class::~Class() {                                                      \
        _impl.reset(nullptr);                                              \
    }                                                                      \
                                                                           \
    intptr_t Class::getImpl() {                                            \
        return _impl->getImpl();                                           \
    }                                                                      \
                                                                           \
    void Class::initialize(const uint &uuid) {                             \
        _impl->initialize(uuid);                                           \
    }                                                                      \
                                                                           \
    void Class::onEnable() {                                               \
        _impl->onEnable();                                                 \
    }                                                                      \
                                                                           \
    void Class::onDisable() {                                              \
        _impl->onDisable();                                                \
    }                                                                      \
                                                                           \
    void Class::onDestroy() {                                              \
        _impl->onDestroy();                                                \
    }                                                                      \
                                                                           \
    void Class::setMaterial(const uint16_t ID, float f, float df, float r, \
                            uint8_t m0, uint8_t m1) {                      \
        _impl->setMaterial(ID, f, df, r, m0, m1);                          \
    }                                                                      \
                                                                           \
    void Class::setAsTrigger(bool v) {                                     \
        _impl->setAsTrigger(v);                                            \
    }                                                                      \
                                                                           \
    void Class::setCenter(float x, float y, float z) {                     \
        _impl->setCenter(x, y, z);                                         \
    }                                                                      \
                                                                           \
    void Class::setGroup(uint32_t g) {                                     \
        _impl->setGroup(g);                                                \
    }                                                                      \
                                                                           \
    uint32_t Class::getGroup() {                                           \
        return _impl->getGroup();                                          \
    }                                                                      \
                                                                           \
    void Class::setMask(uint32_t m) {                                      \
        _impl->setMask(m);                                                 \
    }                                                                      \
                                                                           \
    uint32_t Class::getMask() {                                            \
        return _impl->getMask();                                           \
    }                                                                      \
                                                                           \
    void Class::updateEventListener(EShapeFilterFlag v) {                  \
        _impl->updateEventListener(v);                                     \
    }                                                                      \
                                                                           \
    cc::pipeline::AABB Class::getAABB() {                                  \
        return _impl->getAABB();                                           \
    }                                                                      \
                                                                           \
    cc::pipeline::Sphere Class::getBoundingSphere() {                      \
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
// CC_PHYSICS_SHAPE_DEFINITION(TerrainShape, WrappedTerrainShape)

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
