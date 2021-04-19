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

        auto &selfIter = getPxShapeMap().find((intptr_t)tp.triggerShape);
        auto &otherIter = getPxShapeMap().find((intptr_t)tp.otherShape);
        if (selfIter == getPxShapeMap().end() || otherIter == getPxShapeMap().end())
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
    for (PxU32 i = 0; i < count; i++) {
        const PxContactPair &cp = pairs[i];
        if (cp.flags & (PxContactPairFlag::eREMOVED_SHAPE_0 | PxContactPairFlag::eREMOVED_SHAPE_1))
            continue;

        auto &selfIter = getPxShapeMap().find((intptr_t)cp.shapes[0]);
        auto &otherIter = getPxShapeMap().find((intptr_t)cp.shapes[1]);
        if (selfIter == getPxShapeMap().end() || otherIter == getPxShapeMap().end())
            continue;

        auto &self = selfIter->second;
        auto &other = otherIter->second;
        auto &pairs = mManager->getConatctPairs();
        auto iter = std::find_if(pairs.begin(), pairs.end(), [self, other](ContactEventPair &pair) {
            return (pair.shapeA == self || pair.shapeA == other) && (pair.shapeB == self || pair.shapeB == other);
        });

        if (cp.events & PxPairFlag::eNOTIFY_TOUCH_PERSISTS) {
            if (iter != pairs.end()) iter->state = ETouchState::STAY;
        } else if (cp.events & PxPairFlag::eNOTIFY_TOUCH_FOUND) {
            if (iter == pairs.end()) {
                pairs.push_back(ContactEventPair{self, other});
                iter = pairs.end() - 1;
            }
        } else if (cp.events & PxPairFlag::eNOTIFY_TOUCH_LOST) {
            if (iter != pairs.end()) iter->state = ETouchState::EXIT;
        }

        if (iter != pairs.end()) {
            const PxU8 &contactCount = cp.contactCount;
            iter->contacts.resize(contactCount);
            if (contactCount > 0)
                cp.extractContacts((PxContactPairPoint *)&iter->contacts[0], contactCount);
        }
    }
}

void PhysXEventManager::refreshPairs() {
    for (auto iter = getTriggerPairs().begin(); iter != getTriggerPairs().end();) {
        auto &selfIter = getPxShapeMap().find((intptr_t)(&((PhysXShape *)iter->shapeA)->getShape()));
        auto &otherIter = getPxShapeMap().find((intptr_t)(&((PhysXShape *)iter->shapeB)->getShape()));
        if (selfIter == getPxShapeMap().end() || otherIter == getPxShapeMap().end()) {
            iter = getTriggerPairs().erase(iter);
        } else if (iter->state == ETouchState::EXIT) {
            iter = getTriggerPairs().erase(iter);
        } else {
            iter->state = ETouchState::STAY;
            iter++;
        }
    }

    for (auto iter = getConatctPairs().begin(); iter != getConatctPairs().end();) {
        auto &selfIter = getPxShapeMap().find((intptr_t)(&((PhysXShape *)iter->shapeA)->getShape()));
        auto &otherIter = getPxShapeMap().find((intptr_t)(&((PhysXShape *)iter->shapeB)->getShape()));
        if (selfIter == getPxShapeMap().end() || otherIter == getPxShapeMap().end()) {
            iter = getConatctPairs().erase(iter);
        } else if (iter->state == ETouchState::EXIT) {
            iter = getConatctPairs().erase(iter);
        } else {
            iter++;
        }
    }
}

} // namespace physics
} // namespace cc