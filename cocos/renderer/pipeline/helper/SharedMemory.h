#pragma once
#include "renderer/core/CoreStd.h"

#include "bindings/dop/BufferAllocator.h"
#include "bindings/dop/BufferPool.h"
#include "bindings/dop/ObjectPool.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

namespace cc {
namespace gfx {
class DescriptorSet;
}

namespace pipeline {
struct RenderingSubMesh;
struct FlatBuffer;
class RenderPipeline;

struct CC_DLL ModelView {
    uint32_t enabled = 0;
    uint32_t visFlags = 0;
    uint32_t castShadow = 0;
    uint32_t worldBoundsID = 0; // aabb
    uint32_t nodeID = 0;
    uint32_t transformID = 0;
    uint32_t subModelsID = 0;       // array pool id
    uint32_t instancedBufferID = 0; // raw buffer id
    uint32_t instancedAttrsID = 0;  // array pool id
    const static se::PoolType type;
};

struct CC_DLL SubModelView {
    uint32_t priority = 0;
    uint32_t passCount = 0;
    uint32_t pass0ID = 0;
    uint32_t pass1ID = 0;
    uint32_t pass2ID = 0;
    uint32_t pass3ID = 0;
    uint32_t shader0ID = 0;
    uint32_t shader1ID = 0;
    uint32_t shader2ID = 0;
    uint32_t shader3ID = 0;
    uint32_t descriptorSetID = 0;
    uint32_t inputAssemblerID = 0;

    const static se::PoolType type;
};

struct CC_DLL PassView {
    uint32_t priority = 0;
    uint32_t stage = 0;
    uint32_t phase = 0;
    uint32_t batchingScheme = 0;
    uint32_t primitive = 0;
    uint32_t dynamicState = 0;
    uint32_t hash = 0;
    uint32_t rasterizerStateID = 0;
    uint32_t depthStencilStateID = 0;
    uint32_t blendStateID = 0;
    uint32_t descriptorSetID = 0;
    uint32_t pipelineLayoutID = 0;

    const static se::PoolType type;
};

//
//struct CC_DLL InstancedAttributeBlock {
//    uint32_t bufferViewID = 0;
//    uint32_t bufferViewSize = 0;
//
//    uint32_t instancedAttributesID = 0; //array pool
//};

class CC_DLL Camera {
private:
    uint32_t width = 0;
    uint32_t height = 0;
    float exposure = 0;
    uint32_t clearFlag = 0;
    float clearDepth = 0;
    uint32_t clearStencil = 0;
    uint32_t nodeID = 0;
    uint32_t sceneID = 0;
    uint32_t frustumID = 0;
    cc::Vec3 forward;
    cc::Vec3 position;
    uint32_t viewportX;
    uint32_t viewportY;
    uint32_t viewportWidth;
    uint32_t viewportHeight;
    gfx::Color clearColor;
    cc::Mat4 matView;
    cc::Mat4 matViewProj;
    cc::Mat4 matViewProjInv;
    cc::Mat4 matProj;
    cc::Mat4 matProjInv;

public:
    uint getWidth() const { return width; }
    uint getHeight() const { return height; }
    float getExposure() const { return exposure; }
    float getClearDepth() const { return clearDepth; }
    uint getClearFlag() const { return clearFlag; }
    uint getClearStencil() const { return clearStencil; }
    uint getNodeID() const { return nodeID; }
    uint getSceneID() const { return sceneID; }
    uint getFrustumID() const { return frustumID; }
    uint getViewportX() const { return viewportX; }
    uint getViewportY() const { return viewportY; }
    uint getViewportWidth() const { return viewportWidth; }
    uint getViewportHeight() const { return viewportHeight; }
    const cc::Vec3 &getForward() const { return forward; }
    const cc::Vec3 &getPosition() const { return position; }
    const gfx::Color &getClearColor() const { return clearColor; }
    const cc::Mat4 &getMatView() const { return matView; }
    const cc::Mat4 &getMatViewProj() const { return matViewProj; }
    const cc::Mat4 &getMatViewProjInv() const { return matViewProjInv; }
    const cc::Mat4 &getMatProj() const { return matProj; }
    const cc::Mat4 &getMatProjInv() const { return matProjInv; }

    const static se::PoolType type;
};

struct CC_DLL AABB {
    cc::Vec3 center;
    cc::Vec3 halfExtents;

    const static se::PoolType type;
};

struct CC_DLL Plane {
    cc::Vec3 normal;
    float distance;
};

struct CC_DLL Frustum {
    cc::Vec3 vertices[8];
    Plane planes[6];

    const static se::PoolType type;
};

struct CC_DLL Scene {
    uint32_t mainLightID = 0;
    uint32_t modelsID = 0; //array pool

    const static se::PoolType type;
};

class CC_DLL Light {
    uint32_t _useColorTemperature = 0;
    float _illuminance = 0;
    uint32_t _nodeID = 0;
    cc::Vec3 _direction;
    cc::Vec3 _color;
    cc::Vec3 _colorTemperatureRGB;

public:
    uint getUseColorTemperature() const { return _useColorTemperature; }
    float getIlluminance() const { return _illuminance; }
    uint getNodeID() const { return _nodeID; }
    const cc::Vec3 &getDirection() const { return _direction; }
    const cc::Vec3 &getColor() const { return _color; }
    const cc::Vec3 &getColorTemperatureRGB() const { return _colorTemperatureRGB; }

    const static se::PoolType type;
};

class CC_DLL Ambient {
    uint32_t _enabled = 0;
    float _skyIllum = 0;
    cc::Vec4 _skyColor;
    cc::Vec4 _groundAlbedo;

public:
    bool isEnabled() const { return _enabled; }
    float getSkyIllum() const { return _skyIllum; }
    const cc::Vec4 &getSkyColor() const { return _skyColor; }
    const cc::Vec4 &getGroundAlbedo() const { return _groundAlbedo; }

    const static se::PoolType type;
};

class CC_DLL Fog {
    uint32_t _enabled = 0;
    uint32_t _fogType = 0;
    float _fogDensity = 0;
    float _fogStart = 0;
    float _fogEnd = 0;
    float _fogAtten = 0;
    float _fogTop = 0;
    float _fogRange = 0;
    cc::Vec4 _fogColor;

public:
    bool isEnabled() const { return _enabled; }
    uint getFogType() const { return _fogType; }
    float getFogDensity() const { return _fogDensity; }
    float getFogStart() const { return _fogStart; }
    float getFogEnd() const { return _fogEnd; }
    float getFogAtten() const { return _fogAtten; }
    float getFogTop() const { return _fogTop; }
    float getFogRange() const { return _fogRange; }
    const cc::Vec4 &getFogColor() const { return _fogColor; }

    const static se::PoolType type;
};

enum class CC_DLL ShadowType {
    PLANAR = 0,
    SHADOWMAP = 1
};

class CC_DLL Shadows {
    uint32_t _enabled = 0;
    uint32_t _dirty = 0;
    float _shadowType = 0;
    float _distance = 0;
    float _instancePass = 0;
    float _planarPass = 0;
    float _nearValue = 0;
    float _farValue = 0;
    float _aspect = 0;
    uint32_t _pcfType = 0;
    float _bias = 0;
    float _orthoSize = 0;
    uint32_t _sphereID = 0;

    cc::Vec2 _size;
    cc::Vec3 _normal;
    cc::Vec4 _color;

public:
    bool isEnabled() const { return _enabled; }
    bool isDirty() const { return _dirty; }
    uint getShadowType() const { return static_cast<uint>(_shadowType); }
    float getDistance() const { return _distance; }
    float getInstancePass() const { return _instancePass; }
    float getPlanarPass() const { return _planarPass; }
    float getNearValue() const { return _nearValue; }
    float getFarValue() const { return _farValue; }
    float getAspect() const { return _aspect; }
    uint getPCFType() const { return static_cast<uint>(_pcfType); }
    float getOrthoSize() const { return _orthoSize; }
    float getBias() const { return _bias; }
    uint getSphereID() const { return static_cast<uint>(_sphereID); }
    const cc::Vec2 &getSize() const { return _size; }
    const cc::Vec3 &getNormal() const { return _normal; }
    const cc::Vec4 &getColor() const { return _color; }

    const static se::PoolType type;
};

class CC_DLL Sphere {
    float _radius = 0;
    cc::Vec3 _center;

public:
    float getRadius() const { return _radius; }
    const cc::Vec3 &getCenter() const { return _center; }

    const static se::PoolType type;
};

struct CC_DLL InstancedAttribute {
    uint32_t nameID = 0;
    uint32_t format = 0;
    uint32_t isNormalized = 0;
    uint32_t viewID = 0;

    const static se::PoolType type;
};

class CC_DLL Skybox {
    uint32_t _enabled = 0;
    uint32_t _isRGBE = 0;
    uint32_t _useIBL = 0;
    uint32_t _modelID = 0;

public:
    bool isEnabled() const { return _enabled; }
    bool isRGBE() const { return _isRGBE; }
    bool useIBL() const { return _useIBL; }
    uint getModelID() const { return _modelID; }

    const static se::PoolType type;
};

struct CC_DLL BufferView {
    uint8_t *data = nullptr;

    const static se::PoolType type;
};

struct CC_DLL FlatBuffer {
    uint32_t stride = 0;
    uint32_t count = 0;
    uint32_t bufferViewID = 0;
    uint32_t bufferViewSize = 0;

    const static se::PoolType type;
};

struct CC_DLL RenderingSubMesh {
    uint32_t vertexBuffersID = 0;

    uint32_t attributesID = 0;

    uint32_t flatBuffersID = 0;

    uint32_t primitiveMode = 0;
    uint32_t indexBufferID = 0;
    uint32_t indirectBufferID = 0;
    uint32_t meshID = 0;
    uint32_t subMeshIndex = 0;

    const static se::PoolType type;
};

class CC_DLL Node {
private:
    bool _hasFlagsChanged = 0;
    uint32_t _layer = 0;
    cc::Vec3 _worldScale;
    cc::Vec3 _worldPosition;
    cc::Vec4 _worldRotation;
    cc::Mat4 _worldMatrix;

public:
    bool hasFlagsChanged() const { return _hasFlagsChanged; }
    uint getLayer() const { return _layer; }
    const cc::Vec3 &getWorldScale() const { return _worldScale; }
    const cc::Vec3 &getWorldPosition() const { return _worldPosition; }
    const cc::Vec4 &getWorldRotation() const { return _worldRotation; }
    const cc::Mat4 &getWorldMatrix() const { return _worldMatrix; }

    const static se::PoolType type;
};

class CC_DLL Root {
    float _cumulativeTime = 0;
    float _frameTime = 0;

public:
    float getCumulativeTime() const { return _cumulativeTime; }
    float getFrameTime() const { return _frameTime; }

    const static se::PoolType type;
};

struct CC_DLL RenderWindow {
    uint32_t hasOnScreenAttachments = 0;
    uint32_t hasOffScreenAttachments = 0;
    uint32_t framebufferID = 0;

    const static se::PoolType type;
};

// Get buffer pool data
#define GET_SUBMODEL(index) SharedMemory::getBuffer<SubModelView>(index)
#define GET_PASS(index)     SharedMemory::getBuffer<PassView>(index)
#define GET_MODEL(index)    SharedMemory::getBuffer<ModelView>(index)

#define GET_INSTANCE_ATTRIBUTE(index, offset) (SharedMemory::getBuffer<InstancedAttribute>(index) + offset)
#define GET_RENDER_SUBMESH(index)             SharedMemory::getBuffer<RenderingSubMesh>(index)
#define GET_FLAT_BUFFER(index, offset)        (SharedMemory::getBuffer<FlatBuffer>(index) + offset)
#define GET_BUFFERVIEW(index)                 SharedMemory::getBuffer<BufferView>(index)
#define GET_NODE(index)                       SharedMemory::getBuffer<Node>(index)
#define GET_ROOT()                            SharedMemory::getBuffer<Root>(se::BufferPool::getPoolFlag())
#define GET_CAMERA(index)                     SharedMemory::getBuffer<Camera>(index)
#define GET_SCENE(index)                      SharedMemory::getBuffer<Scene>(index)
#define GET_LIGHT(index)                      SharedMemory::getBuffer<Light>(index)
#define GET_AMBIENT(index)                    SharedMemory::getBuffer<Ambient>(index)
#define GET_FOG(index)                        SharedMemory::getBuffer<Fog>(index)
#define GET_SKYBOX(index)                     SharedMemory::getBuffer<Skybox>(index)
#define GET_FRUSTUM(index)                    SharedMemory::getBuffer<Frustum>(index)
#define GET_AABB(index)                       SharedMemory::getBuffer<AABB>(index)
#define GET_WINDOW(index)                     SharedMemory::getBuffer<RenderWindow>(index)
#define GET_SHADOWS(index)                    SharedMemory::getBuffer<Shadows>(index)
#define GET_SPHERE(index)                     SharedMemory::getBuffer<Sphere>(index)

// TODO
#define GET_NAME(index) (String(0))

// Get object pool data
#define GET_DESCRIPTOR_SET(index)      SharedMemory::getObject<gfx::DescriptorSet, se::PoolType::DESCRIPTOR_SETS>(index)
#define GET_IA(index)                  SharedMemory::getObject<gfx::InputAssembler, se::PoolType::INPUT_ASSEMBLER>(index)
#define GET_SHADER(index)              SharedMemory::getObject<gfx::Shader, se::PoolType::SHADER>(index)
#define GET_RASTERIZER_STATE(index)    SharedMemory::getObject<gfx::RasterizerState, se::PoolType::RASTERIZER_STATE>(index)
#define GET_DEPTH_STENCIL_STATE(index) SharedMemory::getObject<gfx::DepthStencilState, se::PoolType::DEPTH_STENCIL_STATE>(index)
#define GET_BLEND_STATE(index)         SharedMemory::getObject<gfx::BlendState, se::PoolType::BLEND_STATE>(index)
#define GET_ATTRIBUTE(index)           SharedMemory::getObject<gfx::Attribute, se::PoolType::ATTRIBUTE>(index)
#define GET_PIPELINE_LAYOUT(index)     SharedMemory::getObject<gfx::PipelineLayout, se::PoolType::PIPELINE_LAYOUT>(index)
#define GET_FRAMEBUFFER(index)         SharedMemory::getObject<gfx::Framebuffer, se::PoolType::FRAMEBUFFER>(index)

// Get array pool data
#define GET_MODEL_ARRAY(index)     SharedMemory::getHandleArray(se::PoolType::MODEL_ARRAY, index)
#define GET_SUBMODEL_ARRAY(index)  SharedMemory::getHandleArray(se::PoolType::SUB_MODEL_ARRAY, index)
#define GET_ATTRIBUTE_ARRAY(index) SharedMemory::getHandleArray(se::PoolType::ATTRIBUTE_ARRAY, index)
#define GET_PLANE_ARRAY(index)     (static_cast<uint32_t *>(0))

#define GET_RAW_BUFFER(index) SharedMemory::getRawBuffer<uint8_t>(se::PoolType::RAW_BUFFER, index)

class CC_DLL SharedMemory : public Object {
public:
    template <typename T>
    static T *getBuffer(uint index) {
        const auto &bufferMap = se::BufferPool::getPoolMap();
        if (bufferMap.count(T::type) != 0) {
            const se::BufferPool *bufferPool = bufferMap.at(T::type);
            return bufferPool->getTypedObject<T>(index);
        } else {
            return nullptr;
        }
    }

    template <typename T, se::PoolType p>
    static T *getObject(uint index) {
        const auto &poolMap = se::ObjectPool::getPoolMap();
        if (poolMap.count(p) != 0) {
            const se::ObjectPool *objectPool = poolMap.at(p);
            return objectPool->getTypedObject<T>(index);
        } else {
            return nullptr;
        }
    }

    static uint32_t *getHandleArray(se::PoolType type, uint index) {
        return se::BufferAllocator::getBuffer<uint32_t>(type, index);
    }

    template <typename T>
    static T *getRawBuffer(se::PoolType type, uint index) {
        return se::BufferAllocator::getBuffer<T>(type, index);
    }
};

} //namespace pipeline
} //namespace cc
