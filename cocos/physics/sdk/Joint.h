
#pragma once

#include "../spec/IJoint.h"
#include "base/Macros.h"
#include "renderer/pipeline/helper/SharedMemory.h"
#include <memory>
#include <cstdint>

#define CC_PHYSICS_JOINT_CLASS(CLASS)                    \
    class CC_DLL CLASS final : virtual public I##CLASS { \
    protected:                                           \
        std::unique_ptr<I##CLASS> _impl;                 \
                                                         \
    public:                                              \
        CLASS();                                         \
        ~CLASS() override;                               \
        uintptr_t getImpl() override;                    \
        void      initialize(uint h) override;           \
        void      onEnable() override;                   \
        void      onDisable() override;                  \
        void      onDestroy() override;                  \
        void      setEnableCollision(bool v) override;   \
        void      setConnectedBody(uint v) override;

namespace cc {
namespace physics {

CC_PHYSICS_JOINT_CLASS(RevoluteJoint)
void setPivotA(float x, float y, float z) override;
void setPivotB(float x, float y, float z) override;
void setAxis(float x, float y, float z) override;
};

CC_PHYSICS_JOINT_CLASS(DistanceJoint)
void setPivotA(float x, float y, float z) override;
void setPivotB(float x, float y, float z) override;
};

} // namespace physics
} // namespace cc
