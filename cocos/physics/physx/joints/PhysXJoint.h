
#pragma once

#include "../../spec/IJoint.h"
#include "../PhysXInc.h"
#include "base/Macros.h"

using namespace physx;

namespace cc {
namespace physics {
class PhysXSharedBody;

class PhysXJoint : virtual public IBaseJoint {
    PX_NOCOPY(PhysXJoint)
    PhysXJoint() : mJoint(nullptr),
                   mSharedBody(nullptr),
                   mConnectedBody(nullptr),
                   mEnableCollision(false){};

public:
    virtual ~PhysXJoint(){};
    virtual CC_INLINE const intptr_t getImpl() override { return (intptr_t)this; }
    virtual void initialize(const uint handle) override;
    virtual void onEnable() override;
    virtual void onDisable() override;
    virtual void onDestroy() override;
    virtual void setConnectedBody(const uint handle) override;
    virtual void setEnableCollision(const bool v) override;
    virtual void updateScale0() = 0;
    virtual void updateScale1() = 0;

protected:
    PxJoint *mJoint;
    PhysXSharedBody *mSharedBody;
    PhysXSharedBody *mConnectedBody;
    bool mEnableCollision;
    virtual void onComponentSet() = 0;
};

} // namespace physics
} // namespace cc