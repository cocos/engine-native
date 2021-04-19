
#pragma once

#include "../spec/IShape.h"
#include "base/Macros.h"
#include "renderer/pipeline/helper/SharedMemory.h"
#include <memory>
#include <cstdint>

#define CC_PHYSICS_SHAPE_CLASS(CLASS)                                              \
    class CC_DLL CLASS final : public I##CLASS {                                   \
    protected:                                                                     \
        std::unique_ptr<I##CLASS> _impl;                                           \
                                                                                   \
    public:                                                                        \
        CLASS();                                                                   \
        ~CLASS() override;                                                         \
        uintptr_t             getImpl() override;                                  \
        void                  initialize(uint uuid) override;                      \
        void                  onEnable() override;                                 \
        void                  onDisable() override;                                \
        void                  onDestroy() override;                                \
        void                  setMaterial(uint16_t ID, float f, float df, float r, \
                                          uint8_t m0, uint8_t m1) override;        \
        void                  setAsTrigger(bool v) override;                       \
        void                  setCenter(float x, float y, float z) override;       \
        void                  updateEventListener(EShapeFilterFlag v) override;    \
        cc::pipeline::AABB&   getAABB() override;                                  \
        cc::pipeline::Sphere& getBoundingSphere() override;                        \
        uint32_t              getGroup() override;                                 \
        void                  setGroup(uint32_t g) override;                       \
        uint32_t              getMask() override;                                  \
        void                  setMask(uint32_t m) override;

namespace cc {
namespace physics {

CC_PHYSICS_SHAPE_CLASS(SphereShape)
void setRadius(float v) override;
};

CC_PHYSICS_SHAPE_CLASS(BoxShape)
void setSize(float x, float y, float z) override;
};

CC_PHYSICS_SHAPE_CLASS(CapsuleShape)
void setRadius(float v) override;
void setCylinderHeight(float v) override;
void setDirection(EAxisDirection v) override;
};

CC_PHYSICS_SHAPE_CLASS(PlaneShape)
void setConstant(float v) override;
void setNormal(float x, float y, float z) override;
};

CC_PHYSICS_SHAPE_CLASS(TrimeshShape)
void setMesh(uintptr_t v) override;
void useConvex(bool v) override;
};

CC_PHYSICS_SHAPE_CLASS(CylinderShape)
void setConvex(uintptr_t v) override;
void setCylinder(float r, float h, EAxisDirection d) override;
};

CC_PHYSICS_SHAPE_CLASS(ConeShape)
void setConvex(uintptr_t v) override;
void setCone(float r, float h, EAxisDirection d) override;
};

CC_PHYSICS_SHAPE_CLASS(TerrainShape)
void setTerrain(uintptr_t v, float rs, float cs, float hs) override;
};

} // namespace physics
} // namespace cc
