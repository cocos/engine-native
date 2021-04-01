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
    CC_SAFE_DESTROY(_textureStore);
    CC_SAFE_DESTROY(_textureSampled);
    CC_SAFE_DESTROY(_sampler);
}



void ReflectionComp::init(gfx::Device *dev, gfx::Texture *tex, int group_size_x, int group_size_y) {
    _device         = dev;
    _textureSampled = tex;
    _group_size_x   = group_size_x;
    _group_size_y   = group_size_y;

    _textureStore = _device->createTexture({
        gfx::TextureType::TEX2D,
        gfx::TextureUsage::STORAGE | gfx::TextureUsage::TRANSFER_SRC,
        gfx::Format::RGBA8,
        _textureSampled->getWidth(),
        _textureSampled->getHeight(),
        gfx::TextureFlagBit::IMMUTABLE,
    });

    _compConstantsBuffer = _device->createBuffer({
        gfx::BufferUsage::UNIFORM,
        gfx::MemoryUsage::DEVICE | gfx::MemoryUsage::HOST,
        (sizeof(Vec2) + 15) / 16 * 16});
    Vec2 constants{float(_textureSampled->getWidth()), float(_textureSampled->getHeight())};
    if (_compConstantsBuffer) _compConstantsBuffer->update(&constants, sizeof(constants));

    gfx::SamplerInfo samplerInfo;
    _sampler = _device->createSampler(samplerInfo);

    if (!_device->hasFeature(gfx::Feature::COMPUTE_SHADER)) return;

    uint maxInvocations = _device->getCapabilities().maxComputeWorkGroupInvocations;
    CCASSERT(_group_size_x * _group_size_y <= maxInvocations);
    CC_LOG_INFO(" work group size: %dx%d", _group_size_x, _group_size_y);

    ShaderSources<ComputeShaderSource> sources;
    sources.glsl4 = StringUtil::Format(
        R"(
        layout(local_size_x = %d, local_size_y = %d, local_size_z = 1) in;

        layout(set = 0, binding = 0) uniform Constants { vec2 texSize; };

        layout(set = 0, binding = 1) uniform sampler2D texIn;

        layout(set = 0, binding = 2, rgba8) writeonly uniform image2D texOut;

        void main() {
            if (any(greaterThanEqual(gl_GlobalInvocationID.xy, texSize))) return;

            vec2 uv = vec2(gl_GlobalInvocationID.xy) / texSize;
            imageStore(texOut, ivec2(gl_GlobalInvocationID.xy), texture(texIn, vec2(uv.x, 1-uv.y)));
        })",
        _group_size_x, _group_size_y);
    sources.glsl3 = StringUtil::Format(
        R"(
        layout(local_size_x = %d, local_size_y = %d, local_size_z = 1) in;

        layout(std140) uniform Constants { vec2 texSize; };

        uniform sampler2D texIn;

        layout(rgba8) writeonly uniform lowp image2D texOut;

        void main() {
            if (any(greaterThanEqual(vec2(gl_GlobalInvocationID.xy), texSize))) return;

            vec2 uv = vec2(gl_GlobalInvocationID.xy) / texSize;
            imageStore(texOut, ivec2(gl_GlobalInvocationID.xy), texture(texIn, vec2(uv.x, 1-uv.y)));
        })",
        _group_size_x, _group_size_y);
    // no compute support in GLES2

    gfx::ShaderInfo shaderInfo;
    shaderInfo.name   = "Compute ";
    shaderInfo.stages = {{gfx::ShaderStageFlagBit::COMPUTE, getAppropriateShaderSource(sources)}};
    shaderInfo.blocks = {{0, 0, "Constants", {{"texSize", gfx::Type::FLOAT2, 1}}, 1}};
    shaderInfo.images = {
        {0, 1, "texIn", gfx::Type::SAMPLER2D, 1, gfx::MemoryAccessBit::READ_ONLY},
        {0, 2, "texOut", gfx::Type::IMAGE2D, 1, gfx::MemoryAccessBit::WRITE_ONLY}};
    _compShader     = _device->createShader(shaderInfo);

    gfx::DescriptorSetLayoutInfo dslInfo;
    dslInfo.bindings.push_back({0, gfx::DescriptorType::UNIFORM_BUFFER, 1, gfx::ShaderStageFlagBit::COMPUTE});
    dslInfo.bindings.push_back({1, gfx::DescriptorType::SAMPLER_TEXTURE, 1, gfx::ShaderStageFlagBit::COMPUTE});
    dslInfo.bindings.push_back({2, gfx::DescriptorType::STORAGE_IMAGE, 1, gfx::ShaderStageFlagBit::COMPUTE});
    _compDescriptorSetLayout = _device->createDescriptorSetLayout(dslInfo);

    _compPipelineLayout = _device->createPipelineLayout({{_compDescriptorSetLayout}});

    _compDescriptorSet = _device->createDescriptorSet({_compDescriptorSetLayout});

    _compDescriptorSet->bindBuffer(0, _compConstantsBuffer);
    _compDescriptorSet->bindTexture(1, _textureSampled);
    _compDescriptorSet->bindSampler(1, _sampler);
    _compDescriptorSet->bindTexture(2, _textureStore);
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

gfx::Texture *ReflectionComp::getTextureStore() {
    return _textureStore;
}

int ReflectionComp::getGroupSizeX() {
    return _group_size_x;
}

int ReflectionComp::getGroupSizeY() {
    return _group_size_y;
}

} // namespace cc
