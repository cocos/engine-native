#pragma once
#include "WGPUDevice.h"
#include "WGPUFrameBuffer.h"
#include "WGPURenderPass.h"
#include "WGPUTexture.h"
namespace cc {
namespace gfx {
DeviceInfo DeviceInfoInstance() {
    return DeviceInfo();
}

BindingMappingInfo BindingMappingInfoInstance() {
    return BindingMappingInfo();
}

ColorAttachment ColorAttachmentInstance() {
    return ColorAttachment();
}

DepthStencilAttachment DepthStencilAttachmentInstance() {
    return DepthStencilAttachment();
}

SubpassInfo SubpassInfoInstance() {
    return SubpassInfo();
}

SubpassDependency SubpassDependencyInstance() {
    return SubpassDependency();
}

RenderPassInfo RenderPassInfoInstance() {
    return RenderPassInfo();
}

TextureInfo TextureInfoInstance() {
    return TextureInfo();
}

// struct with pointers
class TextureViewInfoInstance {
public:
    TextureViewInfoInstance() = default;

    inline void setTexture(Texture* tex) { info.texture = tex; }
    inline void setType(TextureType type) { info.type = type; }
    inline void setFormat(Format format) { info.format = format; }
    inline void setBaseLevel(uint baseLevel) { info.baseLevel = baseLevel; }
    inline void setLevelCount(uint levelCount) { info.levelCount = levelCount; }
    inline void setBaseLayer(uint baseLayer) { info.baseLayer = baseLayer; }
    inline void setLayerCount(uint layerCount) { info.layerCount = layerCount; }

    operator TextureViewInfo() { return info; }

private:
    TextureViewInfo info;
};

// value_object<FramebufferInfo>("FramebufferInfo")
//     .field("renderPass", &FramebufferInfo::renderPass)
//     .field("colorTextures", &FramebufferInfo::colorTextures)
//     .field("depthStencilTexture", &FramebufferInfo::depthStencilTexture);
// function("FramebufferInfoInstance", &cc::gfx::FramebufferInfoInstance, allow_raw_pointers());

class FramebufferInfoInstance {
public:
    FramebufferInfoInstance() = default;

    inline void setRenderPass(RenderPass* renderPass) { info.renderPass = renderPass; }
    inline void setColorTextures(TextureList colors) { info.colorTextures = colors; }
    inline void setDepthStencilTexture(Texture* tex) { info.depthStencilTexture = tex; }

    operator FramebufferInfo() { return info; }

private:
    FramebufferInfo info;
};

EMSCRIPTEN_BINDINGS(WEBGPU_DEVICE_WASM_EXPORT) {
    // TODO_Zeqiang: compile time traverse enum

    //------------------------------------------------ENUM------------------------------------------------------------
    enum_<Format>("Format")
        .value("UNKNOWN", Format::UNKNOWN)
        .value("RGB8", Format::RGB8)
        .value("RGBA8", Format::RGBA8)
        .value("BGRA8", Format::BGRA8)
        .value("RG32F", Format::RG32F)
        .value("RGB8", Format::RGB8)
        .value("RGB16F", Format::RGB16F)
        .value("RGBA32F", Format::RGBA32F);
    // ... so on

    enum_<SampleCount>("SampleCount")
        .value("X1", SampleCount::X1)
        .value("X2", SampleCount::X2)
        .value("X4", SampleCount::X4)
        .value("X8", SampleCount::X8)
        .value("X16", SampleCount::X16)
        .value("X32", SampleCount::X32)
        .value("X64", SampleCount::X64);

    enum_<LoadOp>("LoadOp")
        .value("LOAD", LoadOp::LOAD)
        .value("CLEAR", LoadOp::CLEAR)
        .value("DISCARD", LoadOp::DISCARD);

    enum_<StoreOp>("StoreOp")
        .value("STORE", StoreOp::STORE)
        .value("DISCARD", StoreOp::DISCARD);

    enum_<AccessType>("AccessType")
        .value("NONE", AccessType::NONE)
        .value("INDIRECT_BUFFER", AccessType::INDIRECT_BUFFER)
        .value("INDEX_BUFFER", AccessType::INDEX_BUFFER)
        .value("VERTEX_BUFFER", AccessType::VERTEX_BUFFER)
        .value("VERTEX_SHADER_READ_UNIFORM_BUFFER", AccessType::VERTEX_SHADER_READ_UNIFORM_BUFFER)
        .value("VERTEX_SHADER_READ_TEXTURE", AccessType::VERTEX_SHADER_READ_TEXTURE)
        .value("VERTEX_SHADER_READ_OTHER", AccessType::VERTEX_SHADER_READ_OTHER);

    enum_<ResolveMode>("ResolveMode")
        .value("NONE", ResolveMode::NONE)
        .value("SAMPLE_ZERO", ResolveMode::SAMPLE_ZERO)
        .value("AVERAGE", ResolveMode::AVERAGE)
        .value("MIN", ResolveMode::MIN)
        .value("MAX", ResolveMode::MAX);

    enum_<TextureType>("TextureType")
        .value("TEX1D", TextureType::TEX1D)
        .value("TEX2D", TextureType::TEX2D)
        .value("TEX3D", TextureType::TEX3D)
        .value("CUBE", TextureType::CUBE)
        .value("TEX1D_ARRAY", TextureType::TEX1D_ARRAY)
        .value("TEX2D_ARRAY", TextureType::TEX2D_ARRAY);

    enum_<TextureUsage>("TextureUsage")
        .value("NONE", TextureUsageBit::NONE)
        .value("TRANSFER_SRC", TextureUsageBit::TRANSFER_SRC)
        .value("TRANSFER_DST", TextureUsageBit::TRANSFER_DST)
        .value("SAMPLED", TextureUsageBit::SAMPLED)
        .value("STORAGE", TextureUsageBit::STORAGE)
        .value("COLOR_ATTACHMENT", TextureUsageBit::COLOR_ATTACHMENT)
        .value("DEPTH_STENCIL_ATTACHMENT", TextureUsageBit::DEPTH_STENCIL_ATTACHMENT)
        .value("INPUT_ATTACHMENT", TextureUsageBit::INPUT_ATTACHMENT);

    enum_<TextureFlags>("TextureFlags")
        .value("NONE", TextureFlagBit::NONE)
        .value("GEN_MIPMAP", TextureFlagBit::GEN_MIPMAP)
        .value("IMMUTABLE", TextureFlagBit::IMMUTABLE)
        .value("GENERAL_LAYOUT", TextureFlagBit::GENERAL_LAYOUT);

    //-----------------------------------------------STRUCT-------------------------------------------------------------------
    value_object<ColorAttachment>("ColorAttachment")
        .field("format", &ColorAttachment::format)
        .field("sampleCount", &ColorAttachment::sampleCount)
        .field("loadOp", &ColorAttachment::loadOp)
        .field("storeOp", &ColorAttachment::storeOp)
        .field("beginAccesses", &ColorAttachment::beginAccesses)
        .field("endAccesses", &ColorAttachment::endAccesses)
        .field("isGeneralLayout", &ColorAttachment::isGeneralLayout);
    function("ColorAttachmentInstance", &cc::gfx::ColorAttachmentInstance);

    value_object<DepthStencilAttachment>("DepthStencilAttachment")
        .field("format", &DepthStencilAttachment::format)
        .field("sampleCount", &DepthStencilAttachment::sampleCount)
        .field("depthLoadOp", &DepthStencilAttachment::depthLoadOp)
        .field("depthStoreOp", &DepthStencilAttachment::depthStoreOp)
        .field("stencilLoadOp", &DepthStencilAttachment::stencilLoadOp)
        .field("stencilStoreOp", &DepthStencilAttachment::stencilStoreOp)
        .field("beginAccesses", &DepthStencilAttachment::beginAccesses)
        .field("endAccesses", &DepthStencilAttachment::endAccesses)
        .field("isGeneralLayout", &DepthStencilAttachment::isGeneralLayout);
    function("DepthStencilAttachmentInstance", &cc::gfx::DepthStencilAttachmentInstance);

    value_object<SubpassInfo>("SubpassInfo")
        .field("inputs", &SubpassInfo::inputs)
        .field("colors", &SubpassInfo::colors)
        .field("resolves", &SubpassInfo::resolves)
        .field("preserves", &SubpassInfo::preserves)
        .field("depthStencil", &SubpassInfo::depthStencil)
        .field("depthStencilResolve", &SubpassInfo::depthStencilResolve)
        .field("depthResolveMode", &SubpassInfo::depthResolveMode)
        .field("stencilResolveMode", &SubpassInfo::stencilResolveMode);
    function("SubpassInfoInstance", &cc::gfx::SubpassInfoInstance);

    value_object<SubpassDependency>("SubpassDependency")
        .field("srcSubpass", &SubpassDependency::srcSubpass)
        .field("dstSubpass", &SubpassDependency::dstSubpass)
        .field("srcAccesses", &SubpassDependency::srcAccesses)
        .field("dstAccesses", &SubpassDependency::dstAccesses);
    function("SubpassDependencyInstance", &cc::gfx::SubpassDependencyInstance);

    value_object<RenderPassInfo>("RenderPassInfo")
        .field("colorAttachments", &RenderPassInfo::colorAttachments)
        .field("depthStencilAttachment", &RenderPassInfo::depthStencilAttachment)
        .field("subpasses", &RenderPassInfo::subpasses)
        .field("dependencies", &RenderPassInfo::dependencies);
    function("RenderPassInfoInstance", &cc::gfx::RenderPassInfoInstance);

    value_object<BindingMappingInfo>("BindingMappingInfo")
        .field("bufferOffsets", &BindingMappingInfo::bufferOffsets)
        .field("samplerOffsets", &BindingMappingInfo::samplerOffsets)
        .field("flexibleSet", &BindingMappingInfo::flexibleSet);
    function("BindingMappingInfoInstance", &cc::gfx::BindingMappingInfoInstance);

    value_object<DeviceInfo>("DeviceInfo")
        .field("isAntiAlias", &DeviceInfo::isAntiAlias)
        .field("windowHandle", &DeviceInfo::windowHandle)
        .field("width", &DeviceInfo::width)
        .field("height", &DeviceInfo::height)
        .field("pixelRatio", &DeviceInfo::pixelRatio)
        .field("bindingMappingInfo", &DeviceInfo::bindingMappingInfo);
    function("DeviceInfoInstance", &cc::gfx::DeviceInfoInstance);

    value_object<TextureInfo>("TextureInfo")
        .field("type", &TextureInfo::type)
        .field("usage", &TextureInfo::usage)
        .field("format", &TextureInfo::format)
        .field("width", &TextureInfo::width)
        .field("height", &TextureInfo::height)
        .field("flags", &TextureInfo::flags)
        .field("layerCount", &TextureInfo::layerCount)
        .field("levelCount", &TextureInfo::levelCount)
        .field("samples", &TextureInfo::samples)
        .field("depth", &TextureInfo::depth);
    function("TextureInfoInstance", &cc::gfx::TextureInfoInstance);

    // struct with pointers
    class_<TextureViewInfoInstance>("TextureViewInfoInstance")
        .constructor<>()
        .function("setTexture", &TextureViewInfoInstance::setTexture, allow_raw_pointer<arg<0>>())
        .function("setType", &TextureViewInfoInstance::setType)
        .function("setFormat", &TextureViewInfoInstance::setFormat)
        .function("setBaseLevel", &TextureViewInfoInstance::setBaseLevel)
        .function("setLevelCount", &TextureViewInfoInstance::setLevelCount)
        .function("setBaseLayer", &TextureViewInfoInstance::setBaseLayer)
        .function("setLayerCount", &TextureViewInfoInstance::setLayerCount);

    class_<FramebufferInfoInstance>("FramebufferInfoInstance")
        .constructor<>()
        .function("setRenderPass", &FramebufferInfoInstance::setRenderPass, allow_raw_pointer<arg<0>>())
        .function("setColorTextures", &FramebufferInfoInstance::setDepthStencilTexture, allow_raw_pointer<arg<0>>())
        .function("setDepthStencilTextures", &FramebufferInfoInstance::setDepthStencilTexture, allow_raw_pointer<arg<0>>());

    // value_object<TextureViewInfo>("TextureViewInfo")
    //     //.field("texture", &TextureViewInfo::texture)
    //     .field("type", &TextureViewInfo::type)
    //     .field("format", &TextureViewInfo::format)
    //     .field("baseLevel", &TextureViewInfo::baseLevel)
    //     .field("levelCount", &TextureViewInfo::levelCount)
    //     .field("baseLayer", &TextureViewInfo::baseLayer)
    //     .field("layerCount", &TextureViewInfo::layerCount);
    //function("TextureViewInfoInstance", &cc::gfx::TextureViewInfoInstance, allow_raw_pointers());

    // struct TextureViewInfo {
    //     Texture *   texture    = nullptr;
    //     TextureType type       = TextureType::TEX2D;
    //     Format      format     = Format::UNKNOWN;
    //     uint        baseLevel  = 0U;
    //     uint        levelCount = 1U;
    //     uint        baseLayer  = 0U;
    //     uint        layerCount = 1U;
    // };

    //--------------------------------------------------CLASS---------------------------------------------------------------------------
    class_<Device>("Device")
        .function("initialize", &Device::initialize, allow_raw_pointer<arg<0>>())
        .function("destroy", &Device::destroy, pure_virtual())
        .function("resize", &Device::resize, pure_virtual())
        .function("acquire", &Device::acquire, pure_virtual())
        .function("present", &Device::present, pure_virtual())
        .function("createQueue", select_overload<Queue*(const QueueInfo&)>(&Device::createQueue),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createBuffer", select_overload<Buffer*(const BufferInfo&)>(&Device::createBuffer),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createBuffer", select_overload<Buffer*(const BufferViewInfo&)>(&Device::createBuffer),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createTexture", select_overload<Texture*(const TextureInfo&)>(&Device::createTexture),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createTexture", select_overload<Texture*(const TextureViewInfo&)>(&Device::createTexture),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createSampler", select_overload<Sampler*(const SamplerInfo&)>(&Device::createSampler),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createShader", select_overload<Shader*(const ShaderInfo&)>(&Device::createShader),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createInputAssembler", select_overload<InputAssembler*(const InputAssemblerInfo&)>(&Device::createInputAssembler),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createRenderPass", select_overload<RenderPass*(const RenderPassInfo&)>(&Device::createRenderPass),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createFramebuffer", select_overload<Framebuffer*(const FramebufferInfo&)>(&Device::createFramebuffer),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createDescriptorSet", select_overload<DescriptorSet*(const DescriptorSetInfo&)>(&Device::createDescriptorSet),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createDescriptorSetLayout", select_overload<DescriptorSetLayout*(const DescriptorSetLayoutInfo&)>(&Device::createDescriptorSetLayout),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createPipelineLayout", select_overload<PipelineLayout*(const PipelineLayoutInfo&)>(&Device::createPipelineLayout),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createPipelineState", select_overload<PipelineState*(const PipelineStateInfo&)>(&Device::createPipelineState),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createGlobalBarrier", select_overload<GlobalBarrier*(const GlobalBarrierInfo&)>(&Device::createGlobalBarrier),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createTextureBarrier", select_overload<TextureBarrier*(const TextureBarrierInfo&)>(&Device::createTextureBarrier),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("copyBuffersToTexture", select_overload<void(const BufferDataList&, Texture*, const BufferTextureCopyList&)>(&Device::copyBuffersToTexture),
                  /* pure_virtual(), */ allow_raw_pointers())
        .function("copyTextureToBuffers", select_overload<void(Texture*, uint8_t* const*, const BufferTextureCopy*, uint)>(&Device::copyTextureToBuffers),
                  /* pure_virtual(), */ allow_raw_pointers());
    class_<CCWGPUDevice, base<Device>>("CCWGPUDevice")
        .class_function("getInstance", &CCWGPUDevice::getInstance, allow_raw_pointers());

    class_<cc::gfx::RenderPass>("RenderPass")
        .class_function("computeHash", select_overload<uint(const RenderPassInfo&)>(&RenderPass::computeHash), allow_raw_pointer<arg<0>>())
        .function("initialize", &cc::gfx::RenderPass::initialize, allow_raw_pointer<arg<0>>())
        .function("destroy", &cc::gfx::RenderPass::destroy)
        .function("getColorAttachments", &cc::gfx::RenderPass::getColorAttachments)
        .function("DepthStencilAttachment", &cc::gfx::RenderPass::getDepthStencilAttachment)
        .function("SubpassInfoList", &cc::gfx::RenderPass::getSubpasses)
        .function("SubpassDependencyList", &cc::gfx::RenderPass::getDependencies)
        .function("getHash", &cc::gfx::RenderPass::getHash);
    class_<CCWGPURenderPass, base<RenderPass>>("CCWGPURenderPass")
        .constructor<>()
        .function("getThis", select_overload<CCWGPURenderPass*(CCWGPURenderPass*)>(&cc::gfx::getThis), allow_raw_pointer<arg<0>>());

    class_<cc::gfx::Texture>("Texture")
        .class_function("computeHash", select_overload<uint(const TextureInfo&)>(&Texture::computeHash), allow_raw_pointer<arg<0>>())
        .function("initialize", select_overload<void(const TextureInfo&)>(&cc::gfx::Texture::initialize), allow_raw_pointer<arg<0>>())
        .function("initialize", select_overload<void(const TextureViewInfo&)>(&cc::gfx::Texture::initialize), allow_raw_pointer<arg<0>>())
        .function("destroy", &cc::gfx::Texture::destroy)
        .function("resize", &cc::gfx::Texture::resize);
    class_<CCWGPUTexture, base<cc::gfx::Texture>>("CCWGPUTexture")
        .constructor<>()
        .function("getThis", select_overload<CCWGPUTexture*(CCWGPUTexture*)>(&cc::gfx::getThis), allow_raw_pointer<arg<0>>());

    class_<cc::gfx::Framebuffer>("Framebuffer")
        .class_function("computeHash", select_overload<uint(const FramebufferInfo&)>(&Framebuffer::computeHash), allow_raw_pointer<arg<0>>())
        .function("initialize", &cc::gfx::Framebuffer::initialize, allow_raw_pointer<arg<0>>())
        .function("destroy", &cc::gfx::Framebuffer::destroy)
        .function("getRenderPass", &cc::gfx::Framebuffer::getRenderPass, allow_raw_pointer<arg<0>>())
        .function("getColorTextures", &cc::gfx::Framebuffer::getColorTextures, allow_raw_pointer<arg<0>>())
        .function("getDepthStencilTexture", &cc::gfx::Framebuffer::getDepthStencilTexture, allow_raw_pointer<arg<0>>());
    class_<CCWGPUFramebuffer, base<Framebuffer>>("CCWGPUFramebuffer")
        .constructor<>();

    //--------------------------------------------------CONTAINER-----------------------------------------------------------------------
    register_vector<int>("vector_int");
    register_vector<uint>("vector_uint");
    register_vector<AccessType>("AccessTypeList");
    register_vector<SubpassInfo>("SubpassInfoList");
    register_vector<ColorAttachment>("ColorAttachmentList");
    register_vector<SubpassDependency>("SubpassDependencyList");
    register_vector<Texture*>("TextureList");
};

} // namespace gfx
} // namespace cc