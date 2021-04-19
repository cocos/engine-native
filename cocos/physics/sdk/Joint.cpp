
#include "Joint.h"
#include "../PhysicsSelector.h"

#define CC_PHYSICS_JOINT_DEFINITION(CLASS, WRAPPED) \
                                                    \
    CLASS::CLASS() {                                \
        _impl.reset(new WRAPPED());                 \
    }                                               \
                                                    \
    CLASS::~CLASS() {                               \
        _impl.reset(nullptr);                       \
    }                                               \
                                                    \
    const intptr_t CLASS::getImpl() {               \
        return _impl->getImpl();                    \
    }                                               \
                                                    \
    void CLASS::initialize(const uint h) {          \
        _impl->initialize(h);                       \
    }                                               \
                                                    \
    void CLASS::onEnable() {                        \
        _impl->onEnable();                          \
    }                                               \
                                                    \
    void CLASS::onDisable() {                       \
        _impl->onDisable();                         \
    }                                               \
                                                    \
    void CLASS::onDestroy() {                       \
        _impl->onDestroy();                         \
    }                                               \
                                                    \
    void CLASS::setConnectedBody(const uint v) {    \
        _impl->setConnectedBody(v);                 \
    }                                               \
                                                    \
    void CLASS::setEnableCollision(const bool v) {  \
        _impl->setEnableCollision(v);               \
    }

namespace cc {
namespace physics {

/// COMMON ///

CC_PHYSICS_JOINT_DEFINITION(RevoluteJoint, WrappedRevoluteJoint)

void RevoluteJoint::setPivotA(float x, float y, float z) {
    _impl->setPivotA(x, y, z);
}

void RevoluteJoint::setPivotB(float x, float y, float z) {
    _impl->setPivotB(x, y, z);
}

void RevoluteJoint::setAxis(float x, float y, float z) {
    _impl->setAxis(x, y, z);
}

} // namespace physics
} // namespace cc