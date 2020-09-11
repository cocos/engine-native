#pragma once
#include "renderer/core/CoreStd.h"

#include "bindings/dop/ArrayPool.h"
#include "bindings/dop/BufferPool.h"
#include "bindings/dop/ObjectPool.h"

namespace cc {
namespace gfx {
class DescriptorSet;
}

namespace pipeline {
struct RenderingSubMesh;
struct FlatBuffer;
class RenderPipeline;

#define X 0
#define Y 1
#define Z 2
#define W 3

struct CC_DLL ModelView {
    uint32_t enabled = 0;
    uint32_t visFlags = 0;
    uint32_t castShadow = 0;
    uint32_t worldBoundsID = 0; // aabb
    uint32_t nodeID = 0;
    uint32_t transformID = 0;
    uint32_t subModelsID = 0; // array pool id
    //    InstancedAttributeBlock instancedAttributeBlock;

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
    float _width = 0;
    float _height = 0;
    float _exposure = 0;
    float _clearFlag = 0;
    float _clearDepth = 0;
    float _clearStencil = 0;
    float _nodeID = 0;
    float _sceneID = 0;
    float _frustumID = 0;
    float _forward[3];
    float _position[3];
    float _viewportX;
    float _viewportY;
    float _viewportWidth;
    float _viewportHeight;
    float _clearColor[4];
    float _matView[16];
    float _matViewProj[16];
    float _matViewProjInv[16];
    float _matProj[16];
    float _matProjInv[16];

public:
    float getWidth() const { return _width; }
    float getHeight() const { return _height; }
    float getExposure() const { return _exposure; }
    float getClearDepth() const { return _clearDepth; }
    uint getClearFlag() const { return static_cast<uint>(_clearFlag); }
    uint getClearStencil() const { return static_cast<uint>(_clearStencil); }
    uint getNodeID() const { return static_cast<uint>(_nodeID); }
    uint getSceneID() const { return static_cast<uint>(_sceneID); }
    uint getFrustumID() const { return static_cast<uint>(_frustumID); }
    uint getViewportX() const { return static_cast<uint>(_viewportX); }
    uint getViewportY() const { return static_cast<uint>(_viewportY); }
    uint getViewportWidth() const { return static_cast<uint>(_viewportWidth); }
    uint getViewportHeight() const { return static_cast<uint>(_viewportHeight); }
    const float *getClearColor() const { return _clearColor; }
    const float *getForward() const { return _forward; }
    const float *getPosition() const { return _position; }
    const float *getMatView() const { return _matView; }
    const float *getMatViewProj() const { return _matViewProj; }
    const float *getMatViewProjInv() const { return _matViewProjInv; }
    const float *getMatProj() const { return _matProj; }
    const float *getMatProjInv() const { return _matProjInv; }

    const static se::PoolType type;
};

class CC_DLL AABB {
private:
    float _center[3];
    float _halfExtents[3];

public:
    const float *getCenter() const { return _center; }
    const float *getHalfExtents() const { return _halfExtents; }

    const static se::PoolType type;
};

class CC_DLL Plane {
private:
    float _normal[3];
    float _distance;

public:
    float getDistance() const { return _distance; }
    const float *getNormal() const { return _normal; }
};

typedef float Vertices[3][8];
class CC_DLL Frustum {
private:
    Vertices _vertices;
    Plane _planes[6];

public:
    const Vertices &getVertices() const { return _vertices; }
    const Plane *getPlanes() const { return _planes; }

    const static se::PoolType type;
};

struct CC_DLL Scene {
    uint32_t mainLightID = 0;
    uint32_t ambientID = 0;
    uint32_t fogID = 0;
    uint32_t skyboxID = 0;
    uint32_t planarShadowID = 0;
    uint32_t modelsID = 0; //array pool

    const static se::PoolType type;
};

class CC_DLL MainLight {
private:
    float _useColorTemperature = 0;
    float _illuminance = 0;
    float _direction[3];
    float _color[3];
    float _colorTemperatureRGB[3];
    float _nodeID = 0;

public:
    float getUseColorTemperature() const { return _useColorTemperature; }
    float getIlluminance() const { return _illuminance; }
    const float *getDirection() const { return _direction; }
    const float *getColor() const { return _color; }
    const float *getColorTemperatureRGB() const { return _colorTemperatureRGB; }
    uint getNodeID() const { return static_cast<uint>(_nodeID); }

    const static se::PoolType type;
};

class CC_DLL Ambient {
private:
    float _enabled = 0;
    float _skyIllum = 0;
    float _skyColor[4];
    float _groundAlbedo[4];

public:
    bool isEnabled() const { return gfx::math::IsEqualF(_enabled, 0); }
    float getSkyIllum() const { return _skyIllum; }
    const float *getSkyColor() const { return _skyColor; }
    const float *getGroundAlbedo() const { return _groundAlbedo; }

    const static se::PoolType type;
};

class CC_DLL Fog {
private:
    float _enabled = 0;
    float _fogType = 0;
    float _fogDensity = 0;
    float _fogStart = 0;
    float _fogEnd = 0;
    float _fogAtten = 0;
    float _fogTop = 0;
    float _fogRange = 0;
    float _fogColor[4];

public:
    bool isEnabled() const { return gfx::math::IsEqualF(_enabled, 0); }
    uint getFogType() const { return static_cast<uint>(_fogType); }
    float getFogDensity() const { return _fogDensity; }
    float getFogStart() const { return _fogStart; }
    float getFogEnd() const { return _fogEnd; }
    float getFogAtten() const { return _fogAtten; }
    float getFogTop() const { return _fogTop; }
    float getFogRange() const { return _fogRange; }
    const float *getFogColor() const { return _fogColor; }

    const static se::PoolType type;
};

class CC_DLL Shadows {
private:
    float _enabled = 0;
    float _dirty = 0;
    float _shadowType = 0;
    float _distance = 0;
    float _instancePass = 0;
    float _planarPass = 0;
    float _nearValue = 0;
    float _farValue = 0;
    float _aspect = 0;
    float _pcfType = 0;
    float _orthoSize = 0;
    float _size[2];
    float _normal[3];
    float _color[4];
    float _sphere[4];

public:
    bool isEnabled() const { return gfx::math::IsEqualF(_enabled, 0); }
    bool isDirty() const { return gfx::math::IsEqualF(_dirty, 0); }
    uint getShadowType() const { return static_cast<uint>(_shadowType); }
    float getDistance() const { return _distance; }
    float getInstancePass() const { return _instancePass; }
    float getPlanarPass() const { return _planarPass; }
    float getNearValue() const { return _nearValue; }
    float getFarValue() const { return _farValue; }
    float getAspect() const { return _aspect; }
    uint getPcfType() const { return static_cast<uint>(_pcfType); }
    uint getOrthoSize() const { return static_cast<uint>(_orthoSize); }
    const float *getSize() const { return _size; }
    const float *getNormal() const { return _normal; }
    const float *getColor() const { return _color; }
    const float *getSphere() const { return _sphere; }

    const static se::PoolType type;
};

struct CC_DLL InstancedAttribute {
    uint32_t nameID = 0;
    uint32_t format = 0;
    uint32_t isNormalized = 0;
    uint32_t viewID = 0;

    const static se::PoolType type;
};

struct CC_DLL Skybox {
    uint32_t enabled = 0;
    uint32_t isRGBE = 0;
    uint32_t useIBL = 0;
    uint32_t model = 0;

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
    float _layer = 0;
    float _worldScale[3];
    float _worldPosition[3];
    float _worldRotation[4];
    float _worldMatrix[16];

public:
    uint getLayer() const { return static_cast<uint>(_layer); }
    const float *getWorldScale() const { return _worldScale; }
    const float *getWorldPosition() const { return _worldPosition; }
    const float *getWorldRotation() const { return _worldRotation; }
    const float *getWorldMatrix() const { return _worldMatrix; }

    const static se::PoolType type;
};

struct CC_DLL Root {
    float cumulativeTime = 0;
    float frameTime = 0;

    const static se::PoolType type;
};

struct CC_DLL RenderWindow {
    uint32_t hasOnScreenAttachments = 0;
    uint32_t hasOffScreenAttachments = 0;
    uint32_t framebufferID = 0;

    const static se::PoolType type;
};

//Get buffer pool data
#define GET_SUBMODEL(index) SharedMemory::getBuffer<SubModelView>(index)
#define GET_PASS(index)     SharedMemory::getBuffer<PassView>(index)
#define GET_MODEL(index)    SharedMemory::getBuffer<ModelView>(index)

#define GET_INSTANCE_ATTRIBUTE(index, offset) (SharedMemory::getBuffer<InstancedAttribute>(index) + offset)
#define GET_RENDER_SUBMESH(index)             SharedMemory::getBuffer<RenderingSubMesh>(index)
#define GET_FLAT_BUFFER(index, offset)        (SharedMemory::getBuffer<FlatBuffer>(index) + offset)
#define GET_BUFFERVIEW(index)                 SharedMemory::getBuffer<BufferView>(index)
#define GET_NODE(index)                       SharedMemory::getBuffer<Node>(index)
#define GET_ROOT(index)                       SharedMemory::getBuffer<Root>(index)
#define GET_CAMERA(index)                     SharedMemory::getBuffer<Camera>(index)
#define GET_SCENE(index)                      SharedMemory::getBuffer<Scene>(index)
#define GET_MAIN_LIGHT(index)                 SharedMemory::getBuffer<MainLight>(index)
#define GET_AMBIENT(index)                    SharedMemory::getBuffer<Ambient>(index)
#define GET_FOG(index)                        SharedMemory::getBuffer<Fog>(index)
#define GET_SKYBOX(index)                     SharedMemory::getBuffer<Skybox>(index)
#define GET_FRUSTUM(index)                    SharedMemory::getBuffer<Frustum>(index)
#define GET_AABB(index)                       SharedMemory::getBuffer<AABB>(index)
#define GET_WINDOW(index)                     SharedMemory::getBuffer<RenderWindow>(index)
#define GET_SHADOWS(index)                    SharedMemory::getBuffer<Shadows>(index)

//TODO
#define GET_NAME(index) (String(0))

//Get object pool data
#define GET_DESCRIPTOR_SET(index)      SharedMemory::getObject<gfx::DescriptorSet, se::PoolType::DESCRIPTOR_SETS>(index)
#define GET_IA(index)                  SharedMemory::getObject<gfx::InputAssembler, se::PoolType::INPUT_ASSEMBLER>(index)
#define GET_SHADER(index)              SharedMemory::getObject<gfx::Shader, se::PoolType::SHADER>(index)
#define GET_RASTERIZER_STATE(index)    SharedMemory::getObject<gfx::RasterizerState, se::PoolType::RASTERIZER_STATE>(index)
#define GET_DEPTH_STENCIL_STATE(index) SharedMemory::getObject<gfx::DepthStencilState, se::PoolType::DEPTH_STENCIL_STATE>(index)
#define GET_BLEND_STATE(index)         SharedMemory::getObject<gfx::BlendState, se::PoolType::BLEND_STATE>(index)
#define GET_FRAMEBUFFER(index)         SharedMemory::getObject<gfx::Framebuffer, se::PoolType::FRAMEBUFFER>(index)
#define GET_PIPELINE_LAYOUT(index)     SharedMemory::getObject<gfx::PipelineLayout, se::PoolType::PIPELINE_LAYOUT>(index)

//Get array pool data
#define GET_MODEL_ARRAY(index)    SharedMemory::getArray(se::PoolType::MODEL_ARRAY, index)
#define GET_SUBMODEL_ARRAY(index) SharedMemory::getArray(se::PoolType::SUB_MODEL_ARRAY, index)
#define GET_PLANE_ARRAY(index)    (static_cast<uint32_t *>(0))

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

    static uint32_t *getArray(se::PoolType type, uint index) {
        return se::ArrayPool::getArray(type, index);
    }
};

} //namespace pipeline
} //namespace cc
