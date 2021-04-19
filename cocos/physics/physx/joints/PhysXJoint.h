
#pragma once

#include "../../spec/IJoint.h"
#include "../PhysXInc.h"
#include "base/Macros.h"

namespace cc {
namespace physics {
class PhysXSharedBody;

class PhysXJoint : virtual public IBaseJoint {
    PX_NOCOPY(PhysXJoint)
    PhysXJoint() = default;

public:
    ~PhysXJoint() override = default;
    CC_INLINE uintptr_t getImpl() override { return reinterpret_cast<uintptr_t>(this); }
    void initialize(uint handle) override;
    void onEnable() override;
    void onDisable() override;
    void onDestroy() override;
    void setConnectedBody(uint handle) override;
    void setEnableCollision(bool v) override;
    virtual void updateScale0() = 0;
    virtual void updateScale1() = 0;

protected:
    physx::PxJoint *_mJoint{nullptr};
    PhysXSharedBody *_mSharedBody{nullptr};
    PhysXSharedBody *_mConnectedBody{nullptr};
    bool _mEnableCollision{false};
    virtual void onComponentSet() = 0;
};

} // namespace physics
} // namespace cc