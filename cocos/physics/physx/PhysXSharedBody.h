
#pragma once

#include "../spec/IRigidBody.h"
#include "base/Macros.h"
#include "renderer/pipeline/helper/SharedMemory.h"
#include <PhysX/PxPhysicsAPI.h>
#include <map>
#include <vector>

using namespace physx;
using namespace cc::pipeline;

namespace cc {

enum TransformBit {
    NONE = 0,
    POSITION = (1 << 0),
    ROTATION = (1 << 1),
    SCALE = (1 << 2),
    RS = TransformBit::ROTATION | TransformBit::SCALE,
    TRS = TransformBit::POSITION | TransformBit::ROTATION | TransformBit::SCALE,
    TRS_MASK = ~TransformBit::TRS,
};

namespace physics {

class PhysXWorld;
class PhysXShape;
class PhysXRigidBody;

class PhysXSharedBody final {
public:
    static PhysXSharedBody *getSharedBody(const uint &handle, PhysXWorld *const World, PhysXRigidBody *const Body);
    void reference(bool v);
    void enabled(bool v);
    CC_INLINE bool isStatic() { return (int)mType & (int)ERigidBodyType::STATIC; }
    CC_INLINE bool isKinematic() { return (int)mType & (int)ERigidBodyType::KINEMATIC; }
    CC_INLINE bool isStaticOrKinematic() { return (int)mType & (int)ERigidBodyType::STATIC || (int)mType & (int)ERigidBodyType::KINEMATIC; }
    CC_INLINE bool isDynamic() { return !isStaticOrKinematic(); }
    CC_INLINE Node &getNode() const { return *mNode; }
    CC_INLINE void setType(ERigidBodyType v) { mType = v; }
    union UActor {
        intptr_t ptr;
        PxRigidActor *rigidActor;
        PxRigidStatic *rigidStatic;
        PxRigidDynamic *rigidDynamic;
    };
    UActor getImpl();
    void syncSceneToPhysics();
    void syncSceneWithCheck();
    void syncPhysicsToScene();
    void addShape(PhysXShape &shape);
    void removeShape(PhysXShape &shape);
    void setCollisionFilter(PxFilterData &data);
    void clearForces();
    void clearVelocity();

private:
    static std::map<uint, PhysXSharedBody *> sharedBodesMap;
    const uint32_t mID;
    const uint mNodeHandle;
    uint8_t mRef;
    bool mIsStatic;
    ERigidBodyType mType;
    int mIndex;
    PxFilterData mFilterData;
    Node *mNode;
    UActor mImpl;
    PxRigidStatic *mStaticActor;
    PxRigidDynamic *mDynamicActor;
    PhysXWorld *mWrappedWorld;
    PhysXRigidBody *mWrappedBody;
    std::vector<PhysXShape *> mWrappedShapes;
    // std::vector<PhysXJoint *> mWrappedJoints0;
    // std::vector<PhysXJoint *> mWrappedJoints1;
    PhysXSharedBody() = delete;
    PhysXSharedBody(const PhysXSharedBody &other) = delete;
    PhysXSharedBody(const uint &handle, PhysXWorld *const world, PhysXRigidBody *const body);
    ~PhysXSharedBody();
    void initActor();
    void switchActor(const bool isStaticBefore);
    void initStaticActor();
    void initDynamicActor();
};

} // namespace physics
} // namespace cc
