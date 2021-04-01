#pragma once

#include "../../base/CoreStd.h"
#include "../../math/Vec2.h"
#include "../../math/Vec4.h"
#include "../../renderer/gfx-base/GFXDef.h"
#include "../../renderer/gfx-base/GFXDevice.h"

namespace cc {

using ComputeShaderSource = String;


template <typename T>
struct ShaderSources {
    T glsl4;
    T glsl3;
    T glsl1;
};

class ReflectionComp {

public:
    ReflectionComp();
    ~ReflectionComp();
    void init(gfx::Device* dev, gfx::Texture* tex, int group_size_x, int group_size_y);
    gfx::DescriptorSet* getDescriptorSet();
    gfx::PipelineState* getPipelineState();
    gfx::Texture* getTextureStore();
    int getGroupSizeX();
    int getGroupSizeY();

private:
    template <typename T>
    T &                       getAppropriateShaderSource(ShaderSources<T> &sources);

    gfx::Device*              _device                  = nullptr;
    gfx::Shader*              _compShader              = nullptr;
    gfx::DescriptorSetLayout* _compDescriptorSetLayout = nullptr;
    gfx::PipelineLayout*      _compPipelineLayout      = nullptr;
    gfx::PipelineState*       _compPipelineState       = nullptr;
    gfx::DescriptorSet*       _compDescriptorSet       = nullptr;
    gfx::Buffer *             _compConstantsBuffer     = nullptr;
    gfx::Texture*             _textureSampled          = nullptr;
    gfx::Sampler *            _sampler                 = nullptr;
    gfx::Texture*             _textureStore            = nullptr;
    int                       _group_size_x             = 8;
    int                       _group_size_y             = 8;
};

} // namespace cc
