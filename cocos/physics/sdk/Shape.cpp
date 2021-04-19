
#include "Shape.h"
#include "../PhysicsSelector.h"

#define CC_PHYSICS_SHAPE_DEFINITION(Class, Wrapped)       \
                                                          \
    Class::Class() {                                      \
        _impl.reset(new Wrapped());                       \
    }                                                     \
                                                          \
    Class::~Class() {                                     \
        _impl.reset(nullptr);                             \
    }                                                     \
                                                          \
    intptr_t Class::getImpl() {                           \
        return _impl->getImpl();                          \
    }                                                     \
                                                          \
    void Class::initialize(const uint &uuid) {            \
        _impl->initialize(uuid);                          \
    }                                                     \
                                                          \
    void Class::onEnable() {                              \
        _impl->onEnable();                                \
    }                                                     \
                                                          \
    void Class::onDisable() {                             \
        _impl->onDisable();                               \
    }                                                     \
                                                          \
    void Class::onDestroy() {                             \
        _impl->onDestroy();                               \
    }                                                     \
                                                          \
    void Class::setMaterial(float f, float df, float r) { \
        _impl->setMaterial(f, df, r);                     \
    }                                                     \
                                                          \
    void Class::setAsTrigger(bool v) {                    \
        _impl->setAsTrigger(v);                           \
    }                                                     \
                                                          \
    void Class::setCenter(float x, float y, float z) {    \
        _impl->setCenter(x, y, z);                        \
    }                                                     \
                                                          \
    void Class::setCollisionFilter(int g, int m) {        \
        _impl->setCollisionFilter(g, m);                  \
    }                                                     \
                                                          \
    void Class::updateEventListener(EShapeFilterFlag v) { \
        _impl->updateEventListener(v);                    \
    }                                                     \
                                                          \
    cc::pipeline::AABB Class::getAABB() {                 \
        return _impl->getAABB();                          \
    }                                                     \
                                                          \
    cc::pipeline::Sphere Class::getBoundingSphere() {     \
        return _impl->getBoundingSphere();                \
    }

namespace cc {
namespace physics {

/// COMMON ///

CC_PHYSICS_SHAPE_DEFINITION(SphereShape, WrappedSphereShape)
CC_PHYSICS_SHAPE_DEFINITION(BoxShape, WrappedBoxShape)
CC_PHYSICS_SHAPE_DEFINITION(PlaneShape, WrappedPlaneShape)
CC_PHYSICS_SHAPE_DEFINITION(CapsuleShape, WrappedCapsuleShape)
// CC_PHYSICS_SHAPE_DEFINITION(CylinderShape, WrappedCylinderShape)
// CC_PHYSICS_SHAPE_DEFINITION(ConeShape, WrappedConeShape)

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

void CylinderShape::setRadius(float v) {
    _impl->setRadius(v);
}

void CylinderShape::setHeight(float v) {
    _impl->setHeight(v);
}

void CylinderShape::setDirection(EAxisDirection v) {
    _impl->setDirection(v);
}

void ConeShape::setRadius(float v) {
    _impl->setRadius(v);
}

void ConeShape::setHeight(float v) {
    _impl->setHeight(v);
}

void ConeShape::setDirection(EAxisDirection v) {
    _impl->setDirection(v);
}

} // namespace physics
} // namespace cc
