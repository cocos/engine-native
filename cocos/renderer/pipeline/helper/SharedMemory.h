#pragma once
#include "renderer/core/CoreStd.h"

#include "bindings/dop/ArrayPool.h"
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

//Get buffer pool data
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

class CC_DLL Node {
private:
    bool _hasFlagsChanged = 0;
    uint32_t _layer = 0;
    cc::Vec3 _worldScale;
    cc::Vec3 _worldPosition;
    cc::Vec4 _worldRotation;
    cc::Mat4 _worldMatrix;

public:
    CC_INLINE bool hasFlagsChanged() const { return _hasFlagsChanged; }
    CC_INLINE uint getLayer() const { return _layer; }
    CC_INLINE const cc::Vec3 &getWorldScale() const { return _worldScale; }
    CC_INLINE const cc::Vec3 &getWorldPosition() const { return _worldPosition; }
    CC_INLINE const cc::Vec4 &getWorldRotation() const { return _worldRotation; }
    CC_INLINE const cc::Mat4 &getWorldMatrix() const { return _worldMatrix; }

    const static se::PoolType type;
};

class CC_DLL AABB {
private:
    cc::Vec3 _center;
    cc::Vec3 _halfExtents;

public:
    CC_INLINE const cc::Vec3 &getCenter() const { return _center; }
    CC_INLINE const cc::Vec3 &getHalfExtents() const { return _halfExtents; }

    const static se::PoolType type;
};

class CC_DLL Light {
private:
    uint32_t _useColorTemperature = 0;
    float _illuminance = 0;
    uint32_t _nodeID = 0;
    cc::Vec3 _direction;
    cc::Vec3 _color;
    cc::Vec3 _colorTemperatureRGB;

public:
    CC_INLINE uint getUseColorTemperature() const { return _useColorTemperature; }
    CC_INLINE float getIlluminance() const { return _illuminance; }
    CC_INLINE const Node *getNode() const { return GET_NODE(_nodeID); }
    CC_INLINE const cc::Vec3 &getDirection() const { return _direction; }
    CC_INLINE const cc::Vec3 &getColor() const { return _color; }
    CC_INLINE const cc::Vec3 &getColorTemperatureRGB() const { return _colorTemperatureRGB; }

    const static se::PoolType type;
};

enum class CC_DLL BatchingSchemes {
    INSTANCING = 1,
    VB_MERGING = 2,
};

class CC_DLL PassView {
private:
    uint32_t _priority = 0;
    uint32_t _stage = 0;
    uint32_t _phase = 0;
    uint32_t _batchingScheme = 0;
    uint32_t _primitive = 0;
    uint32_t _dynamicState = 0;
    uint32_t _hash = 0;
    uint32_t _rasterizerStateID = 0;
    uint32_t _depthStencilStateID = 0;
    uint32_t _blendStateID = 0;
    uint32_t _descriptorSetID = 0;
    uint32_t _pipelineLayoutID = 0;

public:
    CC_INLINE uint getPriority() const { return _priority; }
    CC_INLINE uint getStage() const { return _stage; }
    CC_INLINE uint getPhase() const { return _phase; }
    CC_INLINE BatchingSchemes getBatchingScheme() const { return static_cast<BatchingSchemes>(_batchingScheme); }
    CC_INLINE gfx::PrimitiveMode getPrimitive() const { return static_cast<gfx::PrimitiveMode>(_primitive); }
    CC_INLINE gfx::DynamicStateFlags getDynamicState() const { return static_cast<gfx::DynamicStateFlags>(_dynamicState); }
    CC_INLINE uint getHash() const { return _hash; }
    CC_INLINE const gfx::RasterizerState *getRasterizerState() const { return GET_RASTERIZER_STATE(_rasterizerStateID); }
    CC_INLINE const gfx::DepthStencilState *getDepthStencilState() const { return GET_DEPTH_STENCIL_STATE(_depthStencilStateID); }
    CC_INLINE const gfx::BlendState *getBlendState() const { return GET_BLEND_STATE(_blendStateID); }
    CC_INLINE gfx::DescriptorSet *getDescriptorSet() const { return GET_DESCRIPTOR_SET(_descriptorSetID); }
    CC_INLINE gfx::PipelineLayout *getPipelineLayout() const { return GET_PIPELINE_LAYOUT(_pipelineLayoutID); }

    const static se::PoolType type;
};

class CC_DLL SubModelView {
private:
    uint32_t _priority = 0;
    uint32_t _passCount = 0;
    uint32_t _passID[4] = {0, 0, 0, 0};
    uint32_t _shaderID[4] = {0, 0, 0, 0};
    uint32_t _descriptorSetID = 0;
    uint32_t _inputAssemblerID = 0;

public:
    CC_INLINE uint getPriority() const { return _priority; }
    CC_INLINE uint getPassCount() const { return _passCount; }
    CC_INLINE const PassView *getPassView(uint idx) const { return GET_PASS(_passID[idx]); }
    CC_INLINE uint getShaderID(uint idx) const { return _shaderID[idx]; }
    CC_INLINE gfx::Shader *getShader(uint idx) const { return GET_SHADER(_shaderID[idx]); }
    CC_INLINE gfx::DescriptorSet *getDescriptorSet() const { return GET_DESCRIPTOR_SET(_descriptorSetID); }
    CC_INLINE gfx::InputAssembler *getInputAssembler() const { return GET_IA(_inputAssemblerID); }

    const static se::PoolType type;
};

class CC_DLL ModelView {
private:
    uint32_t _enabled = 0;
    uint32_t _visFlags = 0;
    uint32_t _castShadow = 0;
    uint32_t _worldBoundsID = 0; // aabb
    uint32_t _nodeID = 0;
    uint32_t _transformID = 0;
    uint32_t _subModelsID = 0; // array pool id
    //    InstancedAttributeBlock instancedAttributeBlock;

public:
    CC_INLINE bool isEnabled() const { return _enabled; }
    CC_INLINE bool isCastShadow() const { return _castShadow; }
    CC_INLINE bool isNodeValid() const { return _nodeID; }
    CC_INLINE bool isWorldBoundsValid() const { return _worldBoundsID; }
    CC_INLINE uint getVisFlags() const { return _visFlags; }
    CC_INLINE const AABB *getWroldBounds() const { return GET_AABB(_worldBoundsID); }
    CC_INLINE const Node *getNode() const { return GET_NODE(_nodeID); }
    CC_INLINE const Node *getTransform() const { return GET_NODE(_transformID); }
    CC_INLINE const uint *getSubModels() const { return GET_SUBMODEL_ARRAY(_subModelsID); }
    CC_INLINE const SubModelView *getSubModelView(uint idx) const { return GET_SUBMODEL(idx); }
    const static se::PoolType type;
};

class CC_DLL Scene {
private:
    uint32_t _mainLightID = 0;
    uint32_t _modelsID = 0; //array pool

public:
    CC_INLINE bool useMainLight() const { return _mainLightID; }
    CC_INLINE const Light *getMainLight() const { return GET_LIGHT(_mainLightID); }
    CC_INLINE const uint *getModels() const { return GET_MODEL_ARRAY(_modelsID); }
    CC_INLINE const ModelView *getModelView(uint idx) const { return GET_MODEL(idx); }

    const static se::PoolType type;
};

struct CC_DLL Plane {
    cc::Vec3 normal;
    float distance;
};

constexpr uint PLANE_LENGTH = 6;
class CC_DLL Frustum {
private:
    cc::Vec3 vertices[8];
    Plane planes[PLANE_LENGTH];

public:
    CC_INLINE const cc::Vec3 &getVertex(uint idx) const { return vertices[idx]; }
    CC_INLINE const Plane &getPlane(uint idx) const { return planes[idx]; }

    const static se::PoolType type;
};

class CC_DLL Camera {
private:
    uint32_t _width = 0;
    uint32_t _height = 0;
    float _exposure = 0;
    uint32_t _clearFlag = 0;
    float _clearDepth = 0;
    uint32_t _clearStencil = 0;
    uint32_t _nodeID = 0;
    uint32_t _sceneID = 0;
    uint32_t _frustumID = 0;
    cc::Vec3 _forward;
    cc::Vec3 _position;
    uint32_t _viewportX = 0;
    uint32_t _viewportY = 0;
    uint32_t _viewportWidth = 0;
    uint32_t _viewportHeight = 0;
    gfx::Color _clearColor;
    cc::Mat4 _matView;
    cc::Mat4 _matViewProj;
    cc::Mat4 _matViewProjInv;
    cc::Mat4 _matProj;
    cc::Mat4 _matProjInv;

public:
    CC_INLINE uint getWidth() const { return _width; }
    CC_INLINE uint getHeight() const { return _height; }
    CC_INLINE float getExposure() const { return _exposure; }
    CC_INLINE float getClearDepth() const { return _clearDepth; }
    CC_INLINE uint getClearFlag() const { return _clearFlag; }
    CC_INLINE uint getClearStencil() const { return _clearStencil; }
    CC_INLINE const Node *getNode() const { return GET_NODE(_nodeID); }
    CC_INLINE const Scene *getScene() const { return GET_SCENE(_sceneID); }
    CC_INLINE const Frustum *getFrustum() const { return GET_FRUSTUM(_frustumID); }
    CC_INLINE uint getViewportX() const { return _viewportX; }
    CC_INLINE uint getViewportY() const { return _viewportY; }
    CC_INLINE uint getViewportWidth() const { return _viewportWidth; }
    CC_INLINE uint getViewportHeight() const { return _viewportHeight; }
    CC_INLINE const cc::Vec3 &getForward() const { return _forward; }
    CC_INLINE const cc::Vec3 &getPosition() const { return _position; }
    CC_INLINE const gfx::Color &getClearColor() const { return _clearColor; }
    CC_INLINE const cc::Mat4 &getMatView() const { return _matView; }
    CC_INLINE const cc::Mat4 &getMatViewProj() const { return _matViewProj; }
    CC_INLINE const cc::Mat4 &getMatViewProjInv() const { return _matViewProjInv; }
    CC_INLINE const cc::Mat4 &getMatProj() const { return _matProj; }
    CC_INLINE const cc::Mat4 &getMatProjInv() const { return _matProjInv; }

    const static se::PoolType type;
};

class CC_DLL Ambient {
private:
    uint32_t _enabled = 0;
    float _skyIllum = 0;
    cc::Vec4 _skyColor;
    cc::Vec4 _groundAlbedo;

public:
    CC_INLINE bool isEnabled() const { return _enabled; }
    CC_INLINE float getSkyIllum() const { return _skyIllum; }
    CC_INLINE const cc::Vec4 &getSkyColor() const { return _skyColor; }
    CC_INLINE const cc::Vec4 &getGroundAlbedo() const { return _groundAlbedo; }

    const static se::PoolType type;
};

class CC_DLL Fog {
private:
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
    CC_INLINE bool isEnabled() const { return _enabled; }
    CC_INLINE uint getFogType() const { return _fogType; }
    CC_INLINE float getFogDensity() const { return _fogDensity; }
    CC_INLINE float getFogStart() const { return _fogStart; }
    CC_INLINE float getFogEnd() const { return _fogEnd; }
    CC_INLINE float getFogAtten() const { return _fogAtten; }
    CC_INLINE float getFogTop() const { return _fogTop; }
    CC_INLINE float getFogRange() const { return _fogRange; }
    CC_INLINE const cc::Vec4 &getFogColor() const { return _fogColor; }

    const static se::PoolType type;
};

class CC_DLL Sphere {
private:
    float _radius = 0;
    cc::Vec3 _center;

public:
    CC_INLINE float getRadius() const { return _radius; }
    CC_INLINE const cc::Vec3 &getCenter() const { return _center; }

    const static se::PoolType type;
};

enum class CC_DLL ShadowType {
    PLANAR = 0,
    SHADOWMAP = 1
};

class CC_DLL Shadows {
private:
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
    CC_INLINE bool isEnabled() const { return _enabled; }
    CC_INLINE bool isDirty() const { return _dirty; }
    CC_INLINE ShadowType getShadowType() const { return static_cast<ShadowType>(_shadowType); }
    CC_INLINE float getDistance() const { return _distance; }
    CC_INLINE float getInstancePass() const { return _instancePass; }
    CC_INLINE float getPlanarPass() const { return _planarPass; }
    CC_INLINE float getNearValue() const { return _nearValue; }
    CC_INLINE float getFarValue() const { return _farValue; }
    CC_INLINE float getAspect() const { return _aspect; }
    CC_INLINE uint getPCFType() const { return static_cast<uint>(_pcfType); }
    CC_INLINE float getOrthoSize() const { return _orthoSize; }
    CC_INLINE float getBias() const { return _bias; }
    CC_INLINE const Sphere *getSphere() const { return GET_SPHERE(_sphereID); }
    CC_INLINE const cc::Vec2 &getSize() const { return _size; }
    CC_INLINE const cc::Vec3 &getNormal() const { return _normal; }
    CC_INLINE const cc::Vec4 &getColor() const { return _color; }

    const static se::PoolType type;
};

class CC_DLL Skybox {
private:
    uint32_t _enabled = 0;
    uint32_t _isRGBE = 0;
    uint32_t _useIBL = 0;
    uint32_t _modelID = 0;

public:
    CC_INLINE bool isEnabled() const { return _enabled; }
    CC_INLINE bool isRGBE() const { return _isRGBE; }
    CC_INLINE bool useIBL() const { return _useIBL; }
    CC_INLINE bool isModelValid() const { return _modelID; }
    CC_INLINE const ModelView *getModel() const { return GET_MODEL(_modelID); }

    const static se::PoolType type;
};

class CC_DLL Root {
    float _cumulativeTime = 0;
    float _frameTime = 0;

public:
    CC_INLINE float getCumulativeTime() const { return _cumulativeTime; }
    CC_INLINE float getFrameTime() const { return _frameTime; }

    const static se::PoolType type;
};

class CC_DLL RenderWindow {
private:
    uint32_t _hasOnScreenAttachments = 0;
    uint32_t _hasOffScreenAttachments = 0;
    uint32_t _framebufferID = 0;

public:
    CC_INLINE bool hasOnScreenAttachments() const { return _hasOnScreenAttachments; }
    CC_INLINE bool hasOffScreenAttachments() const { return _hasOffScreenAttachments; }
    CC_INLINE gfx::Framebuffer *getFramebuffer() const { return GET_FRAMEBUFFER(_framebufferID); }

    const static se::PoolType type;
};

struct CC_DLL InstancedAttribute {
    uint32_t nameID = 0;
    uint32_t format = 0;
    uint32_t isNormalized = 0;
    uint32_t viewID = 0;

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

} //namespace pipeline
} //namespace cc
