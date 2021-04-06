#include "ReflectionComp.h"


namespace cc {

ReflectionComp::ReflectionComp() {}
ReflectionComp::~ReflectionComp() {
    CC_SAFE_DESTROY(_compShader);
    CC_SAFE_DESTROY(_compDescriptorSet);
    CC_SAFE_DESTROY(_compDescriptorSetLayout);
    CC_SAFE_DESTROY(_compPipelineLayout);
    CC_SAFE_DESTROY(_compPipelineState);
    CC_SAFE_DESTROY(_compConstantsBuffer);
    CC_SAFE_DESTROY(_reflectionTex);
    CC_SAFE_DESTROY(_sampler);
}

struct ConstantBuffer {
    Mat4 cc_matViewProj;
    Vec2 texSize;
};

void ReflectionComp::init(gfx::Device *dev, gfx::Texture *lightTex, gfx::Texture* worldPositionTex, Mat4 cc_matViewProj, 
    int group_size_x, int group_size_y) {
    _initlized      = true;
    _device         = dev;
    _lightingTex    = lightTex;
    _cc_matViewProj   = cc_matViewProj;
    _worldPositionTex = worldPositionTex;
    _group_size_x   = group_size_x;
    _group_size_y   = group_size_y;

    _reflectionTex = _device->createTexture({
        gfx::TextureType::TEX2D,
        gfx::TextureUsage::STORAGE | gfx::TextureUsage::TRANSFER_SRC,
        gfx::Format::RGBA8,
        _lightingTex->getWidth(),
        _lightingTex->getHeight(),
        gfx::TextureFlagBit::IMMUTABLE,
    });

    _compConstantsBuffer = _device->createBuffer({
        gfx::BufferUsage::UNIFORM,
        gfx::MemoryUsage::DEVICE | gfx::MemoryUsage::HOST,
        (sizeof(Mat4) + sizeof(Vec2) + 15) / 16 * 16});
    
    ConstantBuffer constants;
    constants.texSize = {float(_reflectionTex->getWidth()),float(_reflectionTex->getHeight())};
    constants.cc_matViewProj = _cc_matViewProj;

    if (_compConstantsBuffer) _compConstantsBuffer->update(&constants, sizeof(constants));

    gfx::SamplerInfo samplerInfo;
    samplerInfo.minFilter = gfx::Filter::POINT;
    samplerInfo.magFilter = gfx::Filter::POINT;
    _sampler = _device->createSampler(samplerInfo);

    if (!_device->hasFeature(gfx::Feature::COMPUTE_SHADER)) return;

    uint maxInvocations = _device->getCapabilities().maxComputeWorkGroupInvocations;
    CCASSERT(_group_size_x * _group_size_y <= maxInvocations);
    CC_LOG_INFO(" work group size: %dx%d", _group_size_x, _group_size_y);

    ShaderSources<ComputeShaderSource> sources;
    sources.glsl4 = StringUtil::Format(
        R"(
        layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

        layout(set = 0, binding = 0) uniform Constants {  mat4 cc_matViewProj; vec2 texSize; };
        layout(set = 0, binding = 1) uniform sampler2D lightingTex;
        layout(set = 0, binding = 2) uniform sampler2D worldPositionTex;
        layout(set = 0, binding = 3, rgba8) writeonly uniform lowp image2D reflectionTex;

        void main() {
            float _HorizontalPlaneHeightWS = 0.01;
            vec2 uv = vec2(gl_GlobalInvocationID.xy) / texSize;
            vec3 posWS = texture(worldPositionTex, uv).xyz;
            if(posWS.y <= _HorizontalPlaneHeightWS) return;

            vec3 reflectedPosWS = posWS;
            reflectedPosWS.y = reflectedPosWS.y * -1.0;

            vec4 reflectedPosCS = cc_matViewProj * vec4(reflectedPosWS, 1);
            vec2 reflectedPosNDCxy = reflectedPosCS.xy / reflectedPosCS.w;//posCS -> posNDC
            vec2 reflectedScreenUV = reflectedPosNDCxy * 0.5 + 0.5; //posNDC

            vec2 earlyExitTest = abs(reflectedScreenUV - 0.5);
            if (earlyExitTest.x >= 0.5 || earlyExitTest.y >= 0.5) 
                return;

            vec4 inputPixelSceneColor = texture(lightingTex, uv);
            imageStore(reflectionTex, ivec2(reflectedScreenUV * texSize), inputPixelSceneColor);
            // imageStore(reflectionTex, ivec2(gl_GlobalInvocationID.xy), vec4(reflectedScreenUV * texSize, 0.0, 1.0));
            // imageStore(reflectionTex, ivec2(gl_GlobalInvocationID.xy), vec4(reflectedPosWS, 1.0));
        })",
        _group_size_x, _group_size_y);
    sources.glsl3 = StringUtil::Format(
        R"(
        layout(local_size_x = %d, local_size_y = %d, local_size_z = 1) in;

        layout(std140) uniform Constants { mat4 cc_matViewProj; vec2 texSize; };
        uniform sampler2D lightingTex;
        uniform sampler2D worldPositionTex;
        layout(rgba8) writeonly uniform lowp image2D reflectionTex;

        void main() {
            float _HorizontalPlaneHeightWS = 0.0;
            vec2 uv = vec2(gl_GlobalInvocationID.xy) / texSize;
            vec3 posWS = texture(worldPositionTex, uv).xyz;
            if(posWS.y <= _HorizontalPlaneHeightWS) return;

            vec3 reflectedPosWS = posWS;
            reflectedPosWS.y = reflectedPosWS.y * -1.0;

            vec4 reflectedPosCS = cc_matViewProj * vec4(reflectedPosWS, 1);
            vec2 reflectedPosNDCxy = reflectedPosCS.xy / reflectedPosCS.w;//posCS -> posNDC
            vec2 reflectedScreenUV = reflectedPosNDCxy * 0.5 + 0.5; //posNDC

            vec2 earlyExitTest = abs(reflectedScreenUV - 0.5);
            if (earlyExitTest.x >= 0.5 || earlyExitTest.y >= 0.5) 
                return;

            vec4 inputPixelSceneColor = texture(lightingTex, uv);
            imageStore(reflectionTex, ivec2(reflectedScreenUV * texSize), inputPixelSceneColor);
        })",
        _group_size_x, _group_size_y);
    // no compute support in GLES2

    gfx::ShaderInfo shaderInfo;
    shaderInfo.name   = "Compute ";
    shaderInfo.stages = {{gfx::ShaderStageFlagBit::COMPUTE, getAppropriateShaderSource(sources)}};
    shaderInfo.blocks = {{0, 0, "Constants", {{"cc_matViewProj", gfx::Type::MAT4, 1}, {"texSize", gfx::Type::FLOAT2, 1}}, 1}};
    shaderInfo.images = {
        {0, 1, "lightingTex", gfx::Type::SAMPLER2D, 1, gfx::MemoryAccessBit::READ_ONLY},
        {0, 2, "worldPositionTex", gfx::Type::SAMPLER2D, 1, gfx::MemoryAccessBit::READ_ONLY},
        {0, 3, "reflectionTex", gfx::Type::IMAGE2D, 1, gfx::MemoryAccessBit::WRITE_ONLY}};
    _compShader     = _device->createShader(shaderInfo);

    gfx::DescriptorSetLayoutInfo dslInfo;
    dslInfo.bindings.push_back({0, gfx::DescriptorType::UNIFORM_BUFFER, 1, gfx::ShaderStageFlagBit::COMPUTE});
    dslInfo.bindings.push_back({1, gfx::DescriptorType::SAMPLER_TEXTURE, 1, gfx::ShaderStageFlagBit::COMPUTE});
    dslInfo.bindings.push_back({2, gfx::DescriptorType::SAMPLER_TEXTURE, 1, gfx::ShaderStageFlagBit::COMPUTE});
    dslInfo.bindings.push_back({3, gfx::DescriptorType::STORAGE_IMAGE, 1, gfx::ShaderStageFlagBit::COMPUTE});
    _compDescriptorSetLayout = _device->createDescriptorSetLayout(dslInfo);

    _compPipelineLayout = _device->createPipelineLayout({{_compDescriptorSetLayout}});

    _compDescriptorSet = _device->createDescriptorSet({_compDescriptorSetLayout});

    _compDescriptorSet->bindBuffer(0, _compConstantsBuffer);
    _compDescriptorSet->bindTexture(1, _lightingTex);
    _compDescriptorSet->bindSampler(1, _sampler);
    _compDescriptorSet->bindTexture(2, _worldPositionTex);
    _compDescriptorSet->bindSampler(2, _sampler);
    _compDescriptorSet->bindTexture(3, _reflectionTex);
    _compDescriptorSet->update();

    gfx::PipelineStateInfo pipelineInfo;
    pipelineInfo.shader         = _compShader;
    pipelineInfo.pipelineLayout = _compPipelineLayout;
    pipelineInfo.bindPoint      = gfx::PipelineBindPoint::COMPUTE;

    _compPipelineState = _device->createPipelineState(pipelineInfo);
}

template <typename T>
T& ReflectionComp::getAppropriateShaderSource(ShaderSources<T> &sources) {
    switch (_device->getGfxAPI()) {
        case gfx::API::GLES2:
            return sources.glsl1;
        case gfx::API::GLES3:
            return sources.glsl3;
        case gfx::API::METAL:
        case gfx::API::VULKAN:
            return sources.glsl4;
        default: break;
    }
    return sources.glsl4;
}

gfx::DescriptorSet *ReflectionComp::getDescriptorSet() {
    return _compDescriptorSet;
}

gfx::PipelineState *ReflectionComp::getPipelineState() {
    return _compPipelineState;
}

gfx::Texture *ReflectionComp::getReflectionTex() {
    return _reflectionTex;
}

int ReflectionComp::getGroupSizeX() {
    return _group_size_x;
}

int ReflectionComp::getGroupSizeY() {
    return _group_size_y;
}

bool ReflectionComp::isInitlized() {
    return _initlized;
}

} // namespace cc
