
#pragma once

#include "../spec/IJoint.h"
#include "base/Macros.h"
#include "renderer/pipeline/helper/SharedMemory.h"
#include <memory>
#include <stdint.h>

#define CC_PHYSICS_JOINT_CLASS(CLASS)                           \
    class CC_DLL CLASS final : virtual public I##CLASS {        \
                                                                \
    protected:                                                  \
        std::unique_ptr<I##CLASS> _impl;                        \
                                                                \
    public:                                                     \
        CLASS();                                                \
        virtual ~CLASS();                                       \
        virtual const intptr_t getImpl() override;              \
        virtual void initialize(const uint h) override;         \
        virtual void onEnable() override;                       \
        virtual void onDisable() override;                      \
        virtual void onDestroy() override;                      \
        virtual void setEnableCollision(const bool v) override; \
        virtual void setConnectedBody(const uint v) override;

namespace cc {
namespace physics {

CC_PHYSICS_JOINT_CLASS(RevoluteJoint)
virtual void setPivotA(float x, float y, float z) override;
virtual void setPivotB(float x, float y, float z) override;
virtual void setAxis(float x, float y, float z) override;
};

CC_PHYSICS_JOINT_CLASS(DistanceJoint)
virtual void setPivotA(float x, float y, float z) override;
virtual void setPivotB(float x, float y, float z) override;
};

} // namespace physics
} // namespace cc
