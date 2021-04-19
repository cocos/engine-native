
#pragma once

#include "ILifecycle.h"
#include "renderer/pipeline/helper/SharedMemory.h"
#include <stdint.h>

namespace cc {
namespace physics {

enum class EAxisDirection : uint8_t {
    X_AXIS,
    Y_AXIS,
    Z_AXIS,
};

enum class EShapeFilterFlag : uint8_t {
    NONE = 0,
    IS_TRIGGER = 1 << 0,
    NEED_EVENT = 1 << 1,
    NEED_CONTACT_DATA = 1 << 2,
    DETECT_CONTACT_CCD = 1 << 3,
};

class IBaseShape : virtual public ILifecycle {
public:
    virtual ~IBaseShape(){};
    virtual void initialize(const uint &h) = 0;
    virtual intptr_t getImpl() = 0;
    virtual void setMaterial(const uint16_t ID, float f, float df, float r,
                             uint8_t m0, uint8_t m1) = 0;
    virtual void setAsTrigger(bool v) = 0;
    virtual void setCenter(float x, float y, float z) = 0;
    virtual cc::pipeline::AABB getAABB() = 0;
    virtual cc::pipeline::Sphere getBoundingSphere() = 0;
    virtual void updateEventListener(EShapeFilterFlag flag) = 0;
    virtual uint32_t getGroup() = 0;
    virtual void setGroup(uint32_t g) = 0;
    virtual uint32_t getMask() = 0;
    virtual void setMask(uint32_t m) = 0;
};

class ISphereShape : virtual public IBaseShape {
public:
    virtual ~ISphereShape(){};
    virtual void setRadius(float v) = 0;
};

class IBoxShape : virtual public IBaseShape {
public:
    virtual ~IBoxShape(){};
    virtual void setSize(float x, float y, float z) = 0;
};

class ICapsuleShape : virtual public IBaseShape {
public:
    virtual ~ICapsuleShape(){};
    virtual void setRadius(float v) = 0;
    virtual void setCylinderHeight(float v) = 0;
    virtual void setDirection(EAxisDirection v) = 0;
};

class ICylinderShape : virtual public IBaseShape {
public:
    virtual ~ICylinderShape(){};
    virtual void setRadius(float v) = 0;
    virtual void setHeight(float v) = 0;
    virtual void setDirection(EAxisDirection v) = 0;
};

class IConeShape : virtual public IBaseShape {
public:
    virtual ~IConeShape(){};
    virtual void setRadius(float v) = 0;
    virtual void setHeight(float v) = 0;
    virtual void setDirection(EAxisDirection v) = 0;
};

class IPlaneShape : virtual public IBaseShape {
public:
    virtual ~IPlaneShape(){};
    virtual void setConstant(float v) = 0;
    virtual void setNormal(float x, float y, float z) = 0;
};

class ITrimeshShape : virtual public IBaseShape {
public:
    virtual ~ITrimeshShape(){};
    virtual void setMesh(intptr_t v) = 0;
    virtual void useConvex(bool v) = 0;
};

} // namespace physics
} // namespace cc
