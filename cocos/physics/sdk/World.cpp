
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

void World::setDefaultMaterial(float f, float df, float r) {
    _impl->setDefaultMaterial(f, df, r);
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

} // namespace physics
} // namespace cc
