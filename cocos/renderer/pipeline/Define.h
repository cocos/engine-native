#pragma once

#include "core/CoreStd.h"

namespace cc {
struct PSOCreateInfo;
class SubModel;

namespace pipeline {

class RenderStage;
class RenderFlow;

struct CC_DLL RenderObject {
    //TODO
};
typedef vector<struct RenderObject> RenderObjectList;

struct CC_DLL RenderTargetInfo {
    uint width = 0;
    uint height = 0;
};

struct CC_DLL RenderPass {
    uint hash = 0;
    uint depth = 0;
    uint shaderID = 0;
    uint index = 0;
    SubModel *subModel = nullptr;
};
typedef vector<RenderPass> RenderPassList;

typedef gfx::ColorAttachment ColorDesc;
typedef vector<ColorDesc> ColorDescList;

typedef gfx::DepthStencilAttachment DepthStencilDesc;

struct RenderPassDesc {
    uint index = 0;
    ColorDescList colorAttachments;
    DepthStencilDesc depthStencilAttachment;
};
typedef vector<RenderPassDesc> RenderPassDescList;

struct RenderTextureDesc {
    String name;
    gfx::TextureType type = gfx::TextureType::TEX2D;
    gfx::TextureUsage usage = gfx::TextureUsage::COLOR_ATTACHMENT;
    gfx::Format format = gfx::Format::UNKNOWN;
    int width = -1;
    int height = -1;
};
typedef vector<RenderTextureDesc> RenderTextureDescList;

struct FrameBufferDesc {
    String name;
    uint renderPass = 0;
    vector<String> colorTextures;
    String depthStencilTexture;
};
typedef vector<FrameBufferDesc> FrameBufferDescList;

enum class RenderFlowType : uint8_t {
    SCENE,
    POSTPROCESS,
    UI,
};

typedef vector<RenderStage *> RenderStageList;
typedef vector<RenderFlow *> RenderFlowList;

enum class RenderPassStage : uint8_t {
    DEFAULT = 100,
    UI = 200,
};

struct InternalBindingDesc {
    gfx::BindingType type;
    gfx::UniformBlock blockInfo;
    gfx::UniformSampler samplerInfo;
    String defaultStringValue;
    uint8_t *defaultDataValue = nullptr;

    template <class T>
    const std::enable_if_t<std::is_same<String, T>::value || std::is_same<uint8_t, T>::value> *
    getDefaultValue() const {
        if (defaultDataValue)
            return static_cast<T *>(defaultDataValue);
        else
            return static_cast<T *>(&defaultStringValue);
    }
};

struct InternalBindingInst : public InternalBindingDesc {
    gfx::Buffer *buffer = nullptr;
    gfx::Sampler *sampler = nullptr;
    gfx::Texture *texture = nullptr;
};

//TODO
const uint CAMERA_DEFAULT_MASK = 1;
//constexpr CAMERA_DEFAULT_MASK = Layers.makeMaskExclude([Layers.BitMask.UI_2D, Layers.BitMask.GIZMOS, Layers.BitMask.EDITOR,
//                                                           Layers.BitMask.SCENE_GIZMO, Layers.BitMask.PROFILER]);

} // namespace pipeline
} // namespace cc
