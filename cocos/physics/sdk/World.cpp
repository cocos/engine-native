
#include "./World.h"
#include "../PhysicsSelector.h"

namespace cc {
namespace physics {

World::World() {
    _impl.reset(new WrappedWorld());
}

World::~World() {
    _impl.reset(nullptr);
}

void World::emitEvents() {
    _impl->emitEvents();
}

void World::step(float fixedTimeStep) {
    _impl->step(fixedTimeStep);
}

void World::setAllowSleep(bool v) {
    _impl->setAllowSleep(v);
}

void World::setGravity(float x, float y, float z) {
    _impl->setGravity(x, y, z);
}

intptr_t World::createMaterial(const uint16_t ID, float f, float df, float r,
                               uint8_t m0, uint8_t m1) {
    return _impl->createMaterial(ID, f, df, r, m0, m1);
}

void World::syncSceneToPhysics() {
    _impl->syncSceneToPhysics();
}

void World::syncSceneWithCheck() {
    _impl->syncSceneWithCheck();
}

void World::destroy() {
    _impl->destroy();
}

std::vector<TriggerEventPair> &World::getTriggerEventPairs() {
    return _impl->getTriggerEventPairs();
}

std::vector<ContactEventPair> &World::getContactEventPairs() {
    return _impl->getContactEventPairs();
}

void World::setCollisionMatrix(uint32_t i, uint32_t m) {
    _impl->setCollisionMatrix(i, m);
}

intptr_t World::createConvex(ConvexDesc &desc) {
    return _impl->createConvex(desc);
}

intptr_t World::createTrimesh(TrimeshDesc &desc) {
    return _impl->createTrimesh(desc);
}

} // namespace physics
} // namespace cc
