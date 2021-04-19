
#pragma once

#include "physics/spec/IBody.h"
#include "physics/physx/PhysXInc.h"
#include "base/Macros.h"
#include "renderer/pipeline/helper/SharedMemory.h"
#include <map>
#include <vector>

namespace cc {

enum class TransformBit {
    NONE     = 0,
    POSITION = (1 << 0),
    ROTATION = (1 << 1),
    SCALE    = (1 << 2),
    RS       = TransformBit::ROTATION | TransformBit::SCALE,
    TRS      = TransformBit::POSITION | TransformBit::ROTATION | TransformBit::SCALE,
    TRS_MASK = ~TransformBit::TRS,
};

namespace physics {

class PhysXWorld;
class PhysXShape;
class PhysXJoint;
class PhysXRigidBody;

class PhysXSharedBody final {
public:
    static PhysXSharedBody *getSharedBody(uint handle, PhysXWorld *world, PhysXRigidBody *body);
    PhysXSharedBody()                        = delete;
    PhysXSharedBody(PhysXSharedBody &other)  = delete;
    PhysXSharedBody(PhysXSharedBody &&other) = delete;
    void           reference(bool v);
    void           enabled(bool v);
    CC_INLINE bool isStatic() { return static_cast<int>(_mType) & static_cast<int>(ERigidBodyType::STATIC); }
    CC_INLINE bool isKinematic() { return static_cast<int>(_mType) & static_cast<int>(ERigidBodyType::KINEMATIC); }
    CC_INLINE bool isStaticOrKinematic() { return static_cast<int>(_mType) & static_cast<int>(ERigidBodyType::STATIC) || static_cast<int>(_mType) & static_cast<int>(ERigidBodyType::KINEMATIC); }
    CC_INLINE bool isDynamic() { return !isStaticOrKinematic(); }
    CC_INLINE uint getNodeHandle() const { return _mNodeHandle; }
    CC_INLINE cc::pipeline::Node &getNode() const { return *_mNode; }
    CC_INLINE PhysXWorld &getWorld() const { return *_mWrappedWorld; }
    union UActor {
        uintptr_t              ptr;
        physx::PxRigidActor *  rigidActor;
        physx::PxRigidStatic * rigidStatic;
        physx::PxRigidDynamic *rigidDynamic;
    };
    UActor             getImpl();
    void               setType(ERigidBodyType v);
    void               setMass(float v);
    void               syncScale();
    void               syncSceneToPhysics();
    void               syncSceneWithCheck();
    void               syncPhysicsToScene();
    void               updateCenterOfMass();
    void               addShape(PhysXShape &shape);
    void               removeShape(PhysXShape &shape);
    void               addJoint(PhysXJoint &joint, physx::PxJointActorIndex::Enum index);
    void               removeJoint(PhysXJoint &joint, physx::PxJointActorIndex::Enum index);
    void               setCollisionFilter(physx::PxFilterData &data);
    void               clearForces();
    void               clearVelocity();
    void               setGroup(uint32_t v);
    void               setMask(uint32_t v);
    CC_INLINE uint32_t getGroup() const { return _mFilterData.word0; }
    CC_INLINE uint32_t getMask() const { return _mFilterData.word1; }

private:
    static std::map<uint, PhysXSharedBody *> sharedBodesMap;
    const uint32_t                           _mID;
    const uint                               _mNodeHandle;
    uint8_t                                  _mRef;
    bool                                     _mIsStatic;
    ERigidBodyType                           _mType;
    float                                    _mMass;
    int                                      _mIndex;
    physx::PxFilterData                      _mFilterData;
    cc::pipeline::Node *                     _mNode;
    UActor                                   _mImpl;
    physx::PxRigidStatic *                   _mStaticActor;
    physx::PxRigidDynamic *                  _mDynamicActor;
    PhysXWorld *                             _mWrappedWorld;
    PhysXRigidBody *                         _mWrappedBody;
    std::vector<PhysXShape *>                _mWrappedShapes;
    std::vector<PhysXJoint *>                _mWrappedJoints0;
    std::vector<PhysXJoint *>                _mWrappedJoints1;
    PhysXSharedBody(const uint &handle, PhysXWorld *world, PhysXRigidBody *body);
    ~PhysXSharedBody();
    void initActor();
    void switchActor(bool isStaticBefore);
    void initStaticActor();
    void initDynamicActor();
};

} // namespace physics
} // namespace cc
