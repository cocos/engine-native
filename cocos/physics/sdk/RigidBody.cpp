
#include "RigidBody.h"
#include "../PhysicsSelector.h"

namespace cc {
namespace physics {

RigidBody::RigidBody() {
    _impl.reset(new WrappedRigidBody());
}

RigidBody::~RigidBody() {
    _impl.reset(nullptr);
}

void RigidBody::initialize(const uint &h, const ERigidBodyType &t, const uint32_t &g) {
    _impl->initialize(h, t, g);
}

void RigidBody::onEnable() {
    _impl->onEnable();
}

void RigidBody::onDisable() {
    _impl->onDisable();
}

void RigidBody::onDestroy() {
    _impl->onDestroy();
}

bool RigidBody::isAwake() {
    return _impl->isAwake();
}

bool RigidBody::isSleepy() {
    return _impl->isSleepy();
}

bool RigidBody::isSleeping() {
    return _impl->isSleeping();
}

void RigidBody::setType(ERigidBodyType v) {
    _impl->setType(v);
}

void RigidBody::setMass(float v) {
    _impl->setMass(v);
}

void RigidBody::setLinearDamping(float v) {
    _impl->setLinearDamping(v);
}

void RigidBody::setAngularDamping(float v) {
    _impl->setAngularDamping(v);
}

void RigidBody::useGravity(bool v) {
    _impl->useGravity(v);
}

void RigidBody::setLinearFactor(float x, float y, float z) {
    _impl->setLinearFactor(x, y, z);
}

void RigidBody::setAngularFactor(float x, float y, float z) {
    _impl->setAngularFactor(x, y, z);
}

void RigidBody::setAllowSleep(bool v) {
    _impl->setAllowSleep(v);
}

void RigidBody::wakeUp() {
    _impl->wakeUp();
}

void RigidBody::sleep() {
    _impl->sleep();
}

void RigidBody::clearState() {
    _impl->clearState();
}

void RigidBody::clearForces() {
    _impl->clearForces();
}

void RigidBody::clearVelocity() {
    _impl->clearVelocity();
}

void RigidBody::setSleepThreshold(float v) {
    _impl->setSleepThreshold(v);
}

float RigidBody::getSleepThreshold() {
    return _impl->getSleepThreshold();
}

cc::Vec3 RigidBody::getLinearVelocity() {
    return _impl->getLinearVelocity();
}

void RigidBody::setLinearVelocity(float x, float y, float z) {
    _impl->setLinearVelocity(x, y, z);
}

cc::Vec3 RigidBody::getAngularVelocity() {
    return _impl->getAngularVelocity();
}

void RigidBody::setAngularVelocity(float x, float y, float z) {
    _impl->setAngularVelocity(x, y, z);
}

void RigidBody::applyForce(float x, float y, float z, float rx, float ry, float rz) {
    _impl->applyForce(x, y, z, rx, ry, rz);
}

void RigidBody::applyLocalForce(float x, float y, float z, float rx, float ry, float rz) {
    _impl->applyLocalForce(x, y, z, rx, ry, rz);
}

void RigidBody::applyImpulse(float x, float y, float z, float rx, float ry, float rz) {
    _impl->applyImpulse(x, y, z, rx, ry, rz);
}

void RigidBody::applyLocalImpulse(float x, float y, float z, float rx, float ry, float rz) {
    _impl->applyLocalImpulse(x, y, z, rx, ry, rz);
}

void RigidBody::applyTorque(float x, float y, float z) {
    _impl->applyTorque(x, y, z);
}

void RigidBody::applyLocalTorque(float x, float y, float z) {
    _impl->applyLocalTorque(x, y, z);
}

uint32_t RigidBody::getGroup() {
    return _impl->getGroup();
}

void RigidBody::setGroup(uint32_t g) {
    _impl->setGroup(g);
}

uint32_t RigidBody::getMask() {
    return _impl->getMask();
}

void RigidBody::setMask(uint32_t m) {
    _impl->setMask(m);
}

} // namespace physics
} // namespace cc
