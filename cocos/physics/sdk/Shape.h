
#pragma once

#include "../spec/IShape.h"
#include "base/Macros.h"
#include "renderer/pipeline/helper/SharedMemory.h"
#include <memory>
#include <stdint.h>

#define CC_PHYSICS_SHAPE_CLASS(Class)                                           \
    class CC_DLL Class final : virtual public I##Class {                        \
                                                                                \
    public:                                                                     \
        Class();                                                                \
        virtual ~Class();                                                       \
        virtual intptr_t getImpl() override;                                    \
        virtual void initialize(const uint &uuid) override;                     \
        virtual void onEnable() override;                                       \
        virtual void onDisable() override;                                      \
        virtual void onDestroy() override;                                      \
        virtual void setMaterial(const uint16_t ID, float f, float df, float r, \
                                 uint8_t m0, uint8_t m1) override;              \
        virtual void setAsTrigger(bool v) override;                             \
        virtual void setCenter(float x, float y, float z) override;             \
        virtual void updateEventListener(EShapeFilterFlag v) override;          \
        virtual cc::pipeline::AABB getAABB() override;                          \
        virtual cc::pipeline::Sphere getBoundingSphere() override;              \
        virtual uint32_t getGroup() override;                                   \
        virtual void setGroup(uint32_t g) override;                             \
        virtual uint32_t getMask() override;                                    \
        virtual void setMask(uint32_t m) override;                              \
                                                                                \
    protected:                                                                  \
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
};

CC_PHYSICS_SHAPE_CLASS(PlaneShape)
public:
virtual void setConstant(float v) override;
virtual void setNormal(float x, float y, float z) override;
};

CC_PHYSICS_SHAPE_CLASS(TrimeshShape)
public:
virtual void setMesh(intptr_t v) override;
virtual void useConvex(bool v) override;
};

CC_PHYSICS_SHAPE_CLASS(CylinderShape)
public:
virtual void setConvex(intptr_t v) override;
virtual void setCylinder(float r, float h, EAxisDirection d) override;
};

CC_PHYSICS_SHAPE_CLASS(ConeShape)
public:
virtual void setConvex(intptr_t v) override;
virtual void setCone(float r, float h, EAxisDirection d) override;
};

CC_PHYSICS_SHAPE_CLASS(TerrainShape)
public:
virtual void setTerrain(intptr_t v, float rs, float cs, float hs) override;
};

} // namespace physics
} // namespace cc
