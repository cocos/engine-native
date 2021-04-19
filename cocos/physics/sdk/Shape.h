
#pragma once

#include "../spec/IShape.h"
#include "renderer/pipeline/helper/SharedMemory.h"
#include "base/Macros.h"
#include <memory>
#include <stdint.h>

#define CC_PHYSICS_SHAPE_CLASS(Class)                                  \
    class CC_DLL Class final : virtual public I##Class {               \
                                                                       \
    public:                                                            \
        Class();                                                       \
        virtual ~Class();                                              \
        virtual intptr_t getImpl() override;                           \
        virtual void initialize(const uint &uuid) override;            \
        virtual void onEnable() override;                              \
        virtual void onDisable() override;                             \
        virtual void onDestroy() override;                             \
        virtual void setMaterial(float f, float df, float r) override; \
        virtual void setAsTrigger(bool v) override;                    \
        virtual void setCenter(float x, float y, float z) override;    \
        virtual void setCollisionFilter(int g, int m) override;        \
        virtual void updateEventListener(EShapeFilterFlag v) override; \
        virtual cc::pipeline::AABB getAABB() override;                 \
        virtual cc::pipeline::Sphere getBoundingSphere() override;     \
                                                                       \
    protected:                                                         \
        std::unique_ptr<I##Class> _impl;

namespace cc {
namespace physics {

CC_PHYSICS_SHAPE_CLASS(SphereShape)
public:
virtual void setRadius(float v) override;
};

CC_PHYSICS_SHAPE_CLASS(BoxShape)
public:
virtual void setSize(float x, float y, float z) override;
};

CC_PHYSICS_SHAPE_CLASS(CapsuleShape)
public:
virtual void setRadius(float v) override;
virtual void setCylinderHeight(float v) override;
virtual void setDirection(EAxisDirection v) override;
}
;

CC_PHYSICS_SHAPE_CLASS(CylinderShape)
public:
virtual void setRadius(float v) override;
virtual void setHeight(float v) override;
virtual void setDirection(EAxisDirection v) override;
}
;

CC_PHYSICS_SHAPE_CLASS(ConeShape)
public:
virtual void setRadius(float v) override;
virtual void setHeight(float v) override;
virtual void setDirection(EAxisDirection v) override;
}
;

CC_PHYSICS_SHAPE_CLASS(PlaneShape)
public:
virtual void setConstant(float v) override;
virtual void setNormal(float x, float y, float z) override;
}
;

} // namespace physics
} // namespace cc
