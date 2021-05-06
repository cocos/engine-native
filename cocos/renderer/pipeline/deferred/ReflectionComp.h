#pragma once

#include "../../base/CoreStd.h"
#include "../../math/Vec2.h"
#include "../../math/Vec4.h"
#include "../../math/Mat4.h"
#include "../../renderer/gfx-base/GFXDef.h"
#include "../../renderer/gfx-base/GFXDevice.h"
#include "../../base/TypeDef.h"

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
    void init(gfx::Device *dev, gfx::Texture *lightTex, gfx::Texture *worldPositionTex, gfx::Texture* reflectionTex, 
        Mat4 cc_matViewProj, uint group_size_x, uint group_size_y);
    void initFirstComp();
    void initDenoiseComp();

    gfx::DescriptorSet* getDescriptorSet();
    gfx::PipelineState* getPipelineState();
    gfx::DescriptorSet* getDenoiseDescriptorSet();
    gfx::PipelineState* getDenoisePipelineState();
    gfx::Texture* getReflectionTex();

    gfx::RenderPass* getClearPass();
    gfx::Framebuffer* getClearFramebuffer();
    gfx::GlobalBarrier* getBarrierPre();
    gfx::GlobalBarrier* getBarrierBeforeDenoise();
    gfx::GlobalBarrier* getBarrierAfterDenoise();

    gfx::DispatchInfo getDispatchInfo();
    gfx::DispatchInfo getDenioseDispatchInfo();

    int getGroupSizeX();
    int getGroupSizeY();
    bool  isInitlized();

private:
    template <typename T>
    T &                       getAppropriateShaderSource(ShaderSources<T> &sources);

    gfx::Device*              _device                  = nullptr;

    gfx::RenderPass* _clearPass = nullptr;
    gfx::Framebuffer* _clearFramebuffer = nullptr;

    gfx::Shader*              _compShader              = nullptr;
    gfx::DescriptorSetLayout* _compDescriptorSetLayout = nullptr;
    gfx::PipelineLayout*      _compPipelineLayout      = nullptr;    
    gfx::PipelineState*       _compPipelineState       = nullptr;
    gfx::DescriptorSet*       _compDescriptorSet       = nullptr;

    gfx::Shader*              _compDenoiseShader                = nullptr;
    gfx::DescriptorSetLayout* _compDenoiseDescriptorSetLayout   = nullptr;
    gfx::PipelineLayout*      _compDenoisePipelineLayout        = nullptr;
    gfx::PipelineState*       _compDenoisePipelineState          = nullptr;
    gfx::DescriptorSet*       _compDenoiseDescriptorSet          = nullptr;

    gfx::DescriptorSetLayout* _localDescriptorSetLayout = nullptr;

    gfx::Buffer *             _compConstantsBuffer     = nullptr;
    gfx::Texture*             _lightingTex             = nullptr;
    gfx::Texture*             _worldPositionTex        = nullptr;
    gfx::Sampler*             _sampler                 = nullptr;
    gfx::Texture*             _reflectionTex           = nullptr;
    gfx::Texture*             _denoiseTex              = nullptr;
    Mat4                      _cc_matViewProj;

    gfx::GlobalBarrier* _barrier_pre            = nullptr;
    gfx::GlobalBarrier* _barrier_before_denoise = nullptr;
    gfx::GlobalBarrier* _barrier_after_denoise  = nullptr;

    gfx::DispatchInfo _dispatchInfo;
    gfx::DispatchInfo _denoiseDispatchInfo;

    uint                      _group_size_x             = 8;
    uint                      _group_size_y             = 8;
    bool                      _initlized                = false;
};

} // namespace cc
