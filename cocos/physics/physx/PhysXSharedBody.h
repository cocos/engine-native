
#pragma once

#include "../spec/IBody.h"
#include "./PhysXInc.h"
#include "base/Macros.h"
#include "renderer/pipeline/helper/SharedMemory.h"
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
class PhysXJoint;
class PhysXRigidBody;

class PhysXSharedBody final {
public:
    static PhysXSharedBody *getSharedBody(const uint handle, PhysXWorld *const World, PhysXRigidBody *const Body);
    void reference(bool v);
    void enabled(bool v);
    CC_INLINE bool isStatic() { return (int)mType & (int)ERigidBodyType::STATIC; }
    CC_INLINE bool isKinematic() { return (int)mType & (int)ERigidBodyType::KINEMATIC; }
    CC_INLINE bool isStaticOrKinematic() { return (int)mType & (int)ERigidBodyType::STATIC || (int)mType & (int)ERigidBodyType::KINEMATIC; }
    CC_INLINE bool isDynamic() { return !isStaticOrKinematic(); }
	CC_INLINE const uint getNodeHandle() const { return mNodeHandle; }
    CC_INLINE Node &getNode() const { return *mNode; }
    CC_INLINE PhysXWorld &getWorld() const { return *mWrappedWorld; }
    union UActor {
        intptr_t ptr;
        PxRigidActor *rigidActor;
        PxRigidStatic *rigidStatic;
        PxRigidDynamic *rigidDynamic;
    };
    UActor getImpl();
	void setType(ERigidBodyType v);
    void setMass(float v);
    void syncScale();
    void syncSceneToPhysics();
    void syncSceneWithCheck();
    void syncPhysicsToScene();
    void updateCenterOfMass();
    void addShape(PhysXShape &shape);
    void removeShape(PhysXShape &shape);
    void addJoint(PhysXJoint &joint, const PxJointActorIndex::Enum index);
    void removeJoint(PhysXJoint &joint, const PxJointActorIndex::Enum index);
    void setCollisionFilter(PxFilterData &data);
    void clearForces();
    void clearVelocity();
    void setGroup(uint32_t v);
    void setMask(uint32_t v);
    CC_INLINE uint32_t getGroup() const { return mFilterData.word0; }
    CC_INLINE uint32_t getMask() const { return mFilterData.word1; }

private:
    static std::map<uint, PhysXSharedBody *> sharedBodesMap;
    const uint32_t mID;
    const uint mNodeHandle;
    uint8_t mRef;
    bool mIsStatic;
    ERigidBodyType mType;
    float mMass;
    int mIndex;
    PxFilterData mFilterData;
    Node *mNode;
    UActor mImpl;
    PxRigidStatic *mStaticActor;
    PxRigidDynamic *mDynamicActor;
    PhysXWorld *mWrappedWorld;
    PhysXRigidBody *mWrappedBody;
    std::vector<PhysXShape *> mWrappedShapes;
    std::vector<PhysXJoint *> mWrappedJoints0;
    std::vector<PhysXJoint *> mWrappedJoints1;
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
