
#include "../PhysicsSelector.h"
#include "./World.h"
#include <memory>

namespace cc {
namespace physics {

World::World() {
    _impl = std::make_unique<WrappedWorld>();
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

uintptr_t World::createMaterial(uint16_t id, float f, float df, float r,
                               uint8_t m0, uint8_t m1) {
    return _impl->createMaterial(id, f, df, r, m0, m1);
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

std::vector<std::shared_ptr<TriggerEventPair>> &World::getTriggerEventPairs() {
    return _impl->getTriggerEventPairs();
}

std::vector<std::shared_ptr<ContactEventPair>> &World::getContactEventPairs() {
    return _impl->getContactEventPairs();
}

void World::setCollisionMatrix(uint32_t i, uint32_t m) {
    _impl->setCollisionMatrix(i, m);
}

uintptr_t World::createConvex(ConvexDesc &desc) {
    return _impl->createConvex(desc);
}

uintptr_t World::createTrimesh(TrimeshDesc &desc) {
    return _impl->createTrimesh(desc);
}

uintptr_t World::createHeightField(HeightFieldDesc &desc) {
    return _impl->createHeightField(desc);
}

bool World::raycast(RaycastOptions &opt) {
    return _impl->raycast(opt);
}

std::vector<RaycastResult> &World::raycastResult() {
    return _impl->raycastResult();
}

bool World::raycastClosest(RaycastOptions &opt) {
    return _impl->raycastClosest(opt);
}

RaycastResult &World::raycastClosestResult() {
    return _impl->raycastClosestResult();
}

} // namespace physics
} // namespace cc
