#include "PhysXEventManager.h"
#include "../spec/IWorld.h"
#include "PhysXUtils.h"
#include "shapes/PhysXShape.h"
#include <algorithm>

using namespace physx;

namespace cc {
namespace physics {

void PhysXEventManager::SimulationEventCallback::onTrigger(PxTriggerPair *pairs, PxU32 count) {
    for (PxU32 i = 0; i < count; i++) {
        const PxTriggerPair &tp = pairs[i];
        if (tp.flags & (PxTriggerPairFlag::eREMOVED_SHAPE_TRIGGER | PxTriggerPairFlag::eREMOVED_SHAPE_OTHER))
            continue;

        auto &selfIter = getPxObjMap().find((intptr_t)tp.triggerShape);
        auto &otherIter = getPxObjMap().find((intptr_t)tp.otherShape);
        if (selfIter == getPxObjMap().end() || otherIter == getPxObjMap().end())
            continue;

        auto &self = selfIter->second;
        auto &other = otherIter->second;
        auto &pairs = mManager->getTriggerPairs();
        auto &iter = std::find_if(pairs.begin(), pairs.end(), [self, other](TriggerEventPair &pair) {
            return (pair.shapeA == self || pair.shapeA == other) && (pair.shapeB == self || pair.shapeB == other);
        });
        if (tp.status & PxPairFlag::eNOTIFY_TOUCH_FOUND) {
            if (iter == pairs.end()) pairs.push_back(TriggerEventPair{self, other});
        } else if (tp.status & PxPairFlag::eNOTIFY_TOUCH_LOST) {
            if (iter != pairs.end()) iter->state = ETouchState::EXIT;
        }
    }
}

void PhysXEventManager::SimulationEventCallback::onContact(const PxContactPairHeader &header, const PxContactPair *pairs, PxU32 count) {
}

void PhysXEventManager::refreshPairs() {
    for (auto iter = getTriggerPairs().begin(); iter != getTriggerPairs().end();) {
        auto &selfIter = getPxObjMap().find((intptr_t)(&((PhysXShape *)iter->shapeA)->getShape()));
        auto &otherIter = getPxObjMap().find((intptr_t)(&((PhysXShape *)iter->shapeB)->getShape()));
        if (selfIter == getPxObjMap().end() || otherIter == getPxObjMap().end()) {
            iter = getTriggerPairs().erase(iter);
        } else if (iter->state == ETouchState::EXIT) {
            iter = getTriggerPairs().erase(iter);
        } else {
            iter->state = ETouchState::STAY;
            iter++;
        }
    }
}

} // namespace physics
} // namespace cc