#pragma once
#include "WGPUBuffer.h"
#include "WGPUDef.h"
#include "WGPUDescriptorSet.h"
#include "WGPUDescriptorSetLayout.h"
#include "WGPUDevice.h"
#include "WGPUFrameBuffer.h"
#include "WGPURenderPass.h"
#include "WGPUSampler.h"
#include "WGPUSwapchain.h"
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

Offset OffsetInstance() {
    return Offset();
}

Extent ExtentInstance() {
    return Extent();
}

TextureSubresLayers TextureSubresLayersInstance() {
    return TextureSubresLayers();
}

BufferTextureCopy BufferTextureCopyInstance() {
    return BufferTextureCopy();
}

SamplerInfo SamplerInfoInstance() {
    return SamplerInfo();
}

BufferInfo BufferInfoInstance() {
    return BufferInfo();
}

DescriptorSetLayoutInfo DescriptorSetLayoutInfoInstance() {
    return DescriptorSetLayoutInfo();
}

DescriptorSetLayoutBinding DescriptorSetLayoutBindingInstance() {
    return DescriptorSetLayoutBinding();
}

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
        .value("RGBA32F", Format::RGBA32F)
        .value("DEPTH", Format::DEPTH)
        .value("DEPTH_STENCIL", Format::DEPTH_STENCIL);
    // ... so on

    enum_<VsyncMode>("VsyncMode")
        .value("OFF", VsyncMode::OFF)
        .value("ON", VsyncMode::ON)
        .value("RELAXED", VsyncMode::RELAXED)
        .value("MAILBOX", VsyncMode::MAILBOX)
        .value("HALF", VsyncMode::HALF);

    enum_<SampleCount>("SampleCount")
        .value("ONE", SampleCount::ONE)
        .value("MULTIPLE_PERFORMANCE", SampleCount::MULTIPLE_PERFORMANCE)
        .value("MULTIPLE_BALANCE", SampleCount::MULTIPLE_BALANCE)
        .value("MULTIPLE_QUALITY", SampleCount::MULTIPLE_QUALITY);

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
        .value("RESIZABLE", TextureFlagBit::RESIZABLE)
        .value("GENERAL_LAYOUT", TextureFlagBit::GENERAL_LAYOUT);

    enum_<SurfaceTransform>("SurfaceTransform")
        .value("IDENTITY", SurfaceTransform::IDENTITY)
        .value("ROTATE_90", SurfaceTransform::ROTATE_90)
        .value("ROTATE_180", SurfaceTransform::ROTATE_180)
        .value("ROTATE_270", SurfaceTransform::ROTATE_270);

    enum_<Filter>("Filter")
        .value("NONE", Filter::NONE)
        .value("POINT", Filter::POINT)
        .value("LINEAR", Filter::LINEAR)
        .value("ANISOTROPIC", Filter::ANISOTROPIC);

    enum_<Address>("Address")
        .value("WRAP", Address::WRAP)
        .value("MIRROR", Address::MIRROR)
        .value("CLAMP", Address::CLAMP)
        .value("BORDER", Address::BORDER);

    enum_<ComparisonFunc>("ComparisonFunc")
        .value("NEVER", ComparisonFunc::NEVER)
        .value("LESS", ComparisonFunc::LESS)
        .value("EQUAL", ComparisonFunc::EQUAL)
        .value("LESS_EQUAL", ComparisonFunc::LESS_EQUAL)
        .value("GREATER", ComparisonFunc::GREATER)
        .value("NOT_EQUAL", ComparisonFunc::NOT_EQUAL)
        .value("GREATER_EQUAL", ComparisonFunc::GREATER_EQUAL)
        .value("ALWAYS", ComparisonFunc::ALWAYS);

    enum_<BufferUsage>("BufferUsage")
        .value("NONE", BufferUsageBit::NONE)
        .value("TRANSFER_SRC", BufferUsageBit::TRANSFER_SRC)
        .value("TRANSFER_DST", BufferUsageBit::TRANSFER_DST)
        .value("INDEX", BufferUsageBit::INDEX)
        .value("VERTEX", BufferUsageBit::VERTEX)
        .value("UNIFORM", BufferUsageBit::UNIFORM)
        .value("STORAGE", BufferUsageBit::STORAGE)
        .value("INDIRECT", BufferUsageBit::INDIRECT);

    enum_<MemoryUsage>("MemoryUsage")
        .value("NONE", MemoryUsageBit::NONE)
        .value("DEVICE", MemoryUsageBit::DEVICE)
        .value("HOST", MemoryUsageBit::HOST);

    enum_<BufferFlags>("BufferFlags")
        .value("NONE", BufferFlagBit::NONE);

    enum_<DescriptorType>("DescriptorType")
        .value("UNKNOWN", DescriptorType::UNKNOWN)
        .value("UNIFORM_BUFFER", DescriptorType::UNIFORM_BUFFER)
        .value("DYNAMIC_UNIFORM_BUFFER", DescriptorType::DYNAMIC_UNIFORM_BUFFER)
        .value("STORAGE_BUFFER", DescriptorType::STORAGE_BUFFER)
        .value("DYNAMIC_STORAGE_BUFFER", DescriptorType::DYNAMIC_STORAGE_BUFFER)
        .value("SAMPLER_TEXTURE", DescriptorType::SAMPLER_TEXTURE)
        .value("SAMPLER", DescriptorType::SAMPLER)
        .value("TEXTURE", DescriptorType::TEXTURE)
        .value("STORAGE_IMAGE", DescriptorType::STORAGE_IMAGE)
        .value("INPUT_ATTACHMENT", DescriptorType::INPUT_ATTACHMENT);

    enum_<ShaderStageFlags>("ShaderStageFlags")
        .value("NONE", ShaderStageFlagBit::NONE)
        .value("VERTEX", ShaderStageFlagBit::VERTEX)
        .value("CONTROL", ShaderStageFlagBit::CONTROL)
        .value("EVALUATION", ShaderStageFlagBit::EVALUATION)
        .value("GEOMETRY", ShaderStageFlagBit::GEOMETRY)
        .value("FRAGMENT", ShaderStageFlagBit::FRAGMENT)
        .value("COMPUTE", ShaderStageFlagBit::COMPUTE)
        .value("ALL", ShaderStageFlagBit::ALL);

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
        .field("bindingMappingInfo", &DeviceInfo::bindingMappingInfo);
    function("DeviceInfoInstance", &cc::gfx::DeviceInfoInstance);

    value_object<Offset>("Offset")
        .field("x", &Offset::x)
        .field("y", &Offset::y)
        .field("z", &Offset::z);
    function("OffsetInstance", &cc::gfx::OffsetInstance);

    value_object<Extent>("Extent")
        .field("width", &Extent::width)
        .field("height", &Extent::height)
        .field("depth", &Extent::depth);
    function("ExtentInstance", &cc::gfx::ExtentInstance);

    value_object<TextureSubresLayers>("TextureSubresLayers")
        .field("mipLevel", &TextureSubresLayers::mipLevel)
        .field("baseArrayLayer", &TextureSubresLayers::baseArrayLayer)
        .field("layerCount", &TextureSubresLayers::layerCount);
    function("TextureSubresLayersInstance", &cc::gfx::TextureSubresLayersInstance);

    value_object<BufferTextureCopy>("BufferTextureCopy")
        .field("buffStride", &BufferTextureCopy::buffStride)
        .field("buffTexHeight", &BufferTextureCopy::buffTexHeight)
        .field("texOffset", &BufferTextureCopy::texOffset)
        .field("texExtent", &BufferTextureCopy::texExtent)
        .field("texSubres", &BufferTextureCopy::texSubres);
    function("BufferTextureCopyInstance", &cc::gfx::BufferTextureCopyInstance);

    value_object<SamplerInfo>("SamplerInfo")
        .field("minFilter", &SamplerInfo::minFilter)
        .field("magFilter", &SamplerInfo::magFilter)
        .field("mipFilter", &SamplerInfo::mipFilter)
        .field("addressU", &SamplerInfo::addressU)
        .field("addressV", &SamplerInfo::addressV)
        .field("addressW", &SamplerInfo::addressW)
        .field("maxAnisotropy", &SamplerInfo::maxAnisotropy)
        .field("cmpFunc", &SamplerInfo::cmpFunc);
    function("SamplerInfoInstance", &cc::gfx::SamplerInfoInstance);

    value_object<BufferInfo>("BufferInfo")
        .field("usage", &BufferInfo::usage)
        .field("memUsage", &BufferInfo::memUsage)
        .field("size", &BufferInfo::size)
        .field("stride", &BufferInfo::stride)
        .field("flags", &BufferInfo::flags);
    function("BufferInfoInstance", &cc::gfx::BufferInfoInstance);

    value_object<DescriptorSetLayoutInfo>("DescriptorSetLayoutInfo")
        .field("bindings", &DescriptorSetLayoutInfo::bindings);
    function("DescriptorSetLayoutInfoInstance", &cc::gfx::DescriptorSetLayoutInfoInstance);

    value_object<DescriptorSetLayoutBinding>("DescriptorSetLayoutBinding")
        .field("binding", &DescriptorSetLayoutBinding::binding)
        .field("descriptorType", &DescriptorSetLayoutBinding::descriptorType)
        .field("count", &DescriptorSetLayoutBinding::count)
        .field("stageFlags", &DescriptorSetLayoutBinding::stageFlags)
        .field("immutableSamplers", &DescriptorSetLayoutBinding::immutableSamplers);
    function("DescriptorSetLayoutBindingInstance", &cc::gfx::DescriptorSetLayoutBindingInstance);

    // struct with pointers
    class_<TextureInfoInstance>("TextureInfoInstance")
        .constructor<>()
        .function("setType", &TextureInfoInstance::setType)
        .function("setUsage", &TextureInfoInstance::setUsage)
        .function("setFormat", &TextureInfoInstance::setFormat)
        .function("setWidth", &TextureInfoInstance::setWidth)
        .function("setHeight", &TextureInfoInstance::setHeight)
        .function("setFlags", &TextureInfoInstance::setFlags)
        .function("setLevelCount", &TextureInfoInstance::setLevelCount)
        .function("setLayerCount", &TextureInfoInstance::setLayerCount)
        .function("setSamples", &TextureInfoInstance::setSamples)
        .function("setDepth", &TextureInfoInstance::setDepth)
        .function("setImageBuffer", &TextureInfoInstance::setImageBuffer, allow_raw_pointer<arg<0>>());

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
        .function("setColorTextures", &FramebufferInfoInstance::setColorTextures, allow_raw_pointer<arg<0>>())
        .function("setDepthStencilTexture", &FramebufferInfoInstance::setDepthStencilTexture, allow_raw_pointer<arg<0>>());

    class_<SwapchainInfoInstance>("SwapchainInfoInstance")
        .constructor<>()
        .function("setTexture", &SwapchainInfoInstance::setWindowHandle, allow_raw_pointer<arg<0>>())
        .function("setType", &SwapchainInfoInstance::setVsyncMode)
        .function("setFormat", &SwapchainInfoInstance::setWidth)
        .function("setBaseLevel", &SwapchainInfoInstance::setHeight);

    class_<BufferViewInfoInstance>("BufferViewInfoInstance")
        .constructor<>()
        .function("setBuffer", &BufferViewInfoInstance::setBuffer, allow_raw_pointer<arg<0>>())
        .function("setOffset", &BufferViewInfoInstance::setOffset)
        .function("setRange", &BufferViewInfoInstance::setRange);

    class_<DescriptorSetInfoInstance>("DescriptorSetInfoInstance")
        .constructor<>()
        .function("setDescriptorSetLayout", &DescriptorSetInfoInstance::setDescriptorSetLayout, allow_raw_pointer<arg<0>>());

    //--------------------------------------------------CLASS---------------------------------------------------------------------------
    class_<cc::gfx::Swapchain>("Swapchain")
        .function("initialize", &cc::gfx::Swapchain::initialize, allow_raw_pointer<arg<0>>())
        .function("destroy", &cc::gfx::Swapchain::destroy)
        .function("resize", select_overload<void(uint32_t, uint32_t, SurfaceTransform)>(&cc::gfx::Swapchain::resize))
        .function("destroySurface", &cc::gfx::Swapchain::destroySurface)
        .function("createSurface", &cc::gfx::Swapchain::createSurface, allow_raw_pointer<arg<0>>())
        .function("getWidth", &cc::gfx::Swapchain::getWidth)
        .function("getHeight", &cc::gfx::Swapchain::getHeight);
    class_<CCWGPUSwapchain, base<Swapchain>>("CCWGPUSwapchain")
        .function("getColorTexture", select_overload<CCWGPUTexture *(void)>(&cc::gfx::CCWGPUSwapchain::getColorTexture), allow_raw_pointer<arg<0>>())
        .function("getDepthStencilTexture", select_overload<CCWGPUTexture *(void)>(&cc::gfx::CCWGPUSwapchain::getDepthStencilTexture), allow_raw_pointer<arg<0>>());

    class_<Device>("Device")
        .function("initialize", &Device::initialize, allow_raw_pointer<arg<0>>())
        .function("destroy", &Device::destroy, pure_virtual())
        .function("present", &Device::present, pure_virtual())
        .function("createCommandBuffer", select_overload<CommandBuffer *(const CommandBufferInfo &)>(&Device::createCommandBuffer),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createQueue", select_overload<Queue *(const QueueInfo &)>(&Device::createQueue),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createBuffer", select_overload<Buffer *(const BufferInfo &)>(&Device::createBuffer),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("getSampler", &Device::getSampler, allow_raw_pointer<arg<0>>())
        .function("createShader", select_overload<Shader *(const ShaderInfo &)>(&Device::createShader),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createInputAssembler", select_overload<InputAssembler *(const InputAssemblerInfo &)>(&Device::createInputAssembler),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createRenderPass", select_overload<RenderPass *(const RenderPassInfo &)>(&Device::createRenderPass),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createDescriptorSetLayout", select_overload<DescriptorSetLayout *(const DescriptorSetLayoutInfo &)>(&Device::createDescriptorSetLayout),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createPipelineLayout", select_overload<PipelineLayout *(const PipelineLayoutInfo &)>(&Device::createPipelineLayout),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createPipelineState", select_overload<PipelineState *(const PipelineStateInfo &)>(&Device::createPipelineState),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        // .function("createGlobalBarrier", select_overload<GlobalBarrier*(const GlobalBarrierInfo&)>(&Device::createGlobalBarrier),
        //           /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        // .function("createTextureBarrier", select_overload<TextureBarrier*(const TextureBarrierInfo&)>(&Device::createTextureBarrier),
        //           /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("copyBuffersToTexture", select_overload<void(const BufferDataList &, Texture *, const BufferTextureCopyList &)>(&Device::copyBuffersToTexture),
                  /* pure_virtual(), */ allow_raw_pointers())
        .function("copyTextureToBuffers", select_overload<void(Texture *, BufferSrcList &, const BufferTextureCopyList &)>(&Device::copyTextureToBuffers),
                  /* pure_virtual(), */ allow_raw_pointers())
        .function("acquire", select_overload<void(Swapchain *const *, uint32_t)>(&Device::acquire),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("present", select_overload<void(void)>(&Device::present),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>());
    class_<CCWGPUDevice, base<Device>>("CCWGPUDevice")
        .class_function("getInstance", &CCWGPUDevice::getInstance, allow_raw_pointer<arg<0>>())
        .function("createSwapchain", select_overload<Swapchain *(const SwapchainInfoInstance &)>(&CCWGPUDevice::createSwapchain),
                  /* pure_virtual(), */ allow_raw_pointers())
        .function("createFramebuffer", select_overload<Framebuffer *(const FramebufferInfoInstance &)>(&CCWGPUDevice::createFramebuffer),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createTexture", select_overload<Texture *(const TextureInfoInstance &)>(&CCWGPUDevice::createTexture),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createTextureView", select_overload<Texture *(const TextureViewInfoInstance &)>(&CCWGPUDevice::createTexture),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createBufferView", select_overload<Buffer *(const BufferViewInfoInstance &)>(&CCWGPUDevice::createBuffer),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>())
        .function("createDescriptorSet", select_overload<DescriptorSet *(const DescriptorSetInfoInstance &)>(&CCWGPUDevice::createDescriptorSet),
                  /* pure_virtual(), */ allow_raw_pointer<arg<0>>());

    class_<cc::gfx::RenderPass>("RenderPass")
        .class_function("computeHash", select_overload<uint(const RenderPassInfo &)>(&RenderPass::computeHash), allow_raw_pointer<arg<0>>())
        .function("initialize", &cc::gfx::RenderPass::initialize, allow_raw_pointer<arg<0>>())
        .function("destroy", &cc::gfx::RenderPass::destroy)
        .function("getColorAttachments", &cc::gfx::RenderPass::getColorAttachments)
        .function("DepthStencilAttachment", &cc::gfx::RenderPass::getDepthStencilAttachment)
        .function("SubpassInfoList", &cc::gfx::RenderPass::getSubpasses)
        .function("SubpassDependencyList", &cc::gfx::RenderPass::getDependencies)
        .function("getHash", &cc::gfx::RenderPass::getHash);
    class_<CCWGPURenderPass, base<RenderPass>>("CCWGPURenderPass")
        .constructor<>()
        .function("getThis", select_overload<CCWGPURenderPass *(CCWGPURenderPass *)>(&cc::gfx::getThis), allow_raw_pointer<arg<0>>());

    class_<cc::gfx::Texture>("Texture")
        .class_function("computeHash", select_overload<uint(const TextureInfo &)>(&Texture::computeHash), allow_raw_pointer<arg<0>>())
        .function("initialize", select_overload<void(const TextureInfo &)>(&cc::gfx::Texture::initialize), allow_raw_pointer<arg<0>>())
        .function("initialize", select_overload<void(const TextureViewInfo &)>(&cc::gfx::Texture::initialize), allow_raw_pointer<arg<0>>())
        .function("destroy", &cc::gfx::Texture::destroy)
        .function("resize", &cc::gfx::Texture::resize);
    class_<CCWGPUTexture, base<cc::gfx::Texture>>("CCWGPUTexture")
        .constructor<>();

    class_<cc::gfx::Framebuffer>("Framebuffer")
        .class_function("computeHash", select_overload<uint(const FramebufferInfo &)>(&Framebuffer::computeHash), allow_raw_pointer<arg<0>>())
        .function("initialize", &cc::gfx::Framebuffer::initialize, allow_raw_pointer<arg<0>>())
        .function("destroy", &cc::gfx::Framebuffer::destroy)
        .function("getRenderPass", &cc::gfx::Framebuffer::getRenderPass, allow_raw_pointer<arg<0>>())
        .function("getColorTextures", &cc::gfx::Framebuffer::getColorTextures, allow_raw_pointer<arg<0>>())
        .function("getDepthStencilTexture", &cc::gfx::Framebuffer::getDepthStencilTexture, allow_raw_pointer<arg<0>>());
    class_<CCWGPUFramebuffer, base<Framebuffer>>("CCWGPUFramebuffer")
        .constructor<>();

    class_<Sampler>("Sampler")
        .function("getInfo", &Sampler::getInfo);
    class_<CCWGPUSampler, base<Sampler>>("CCWGPUSampler")
        .constructor<const SamplerInfo &>();

    class_<Buffer>("Buffer")
        .function("initialize", select_overload<void(const BufferInfo &)>(&Buffer::initialize), allow_raw_pointer<arg<0>>())
        .function("initialize", select_overload<void(const BufferViewInfo &)>(&Buffer::initialize), allow_raw_pointer<arg<0>>())
        .function("resize", &Buffer::resize)
        .function("desctroy", &Buffer::destroy)
        .function("update", select_overload<void(const void *, uint)>(&Buffer::update), allow_raw_pointer<arg<0>>())
        .function("update", select_overload<void(const void *)>(&Buffer::update), allow_raw_pointer<arg<0>>());
    class_<CCWGPUBuffer, base<Buffer>>("CCWGPUBuffer")
        .constructor<>();

    class_<DescriptorSetLayout>("DescriptorSetLayout")
        .function("initialize", &DescriptorSetLayout::initialize)
        .function("destroy", &DescriptorSetLayout::destroy);
    class_<CCWGPUDescriptorSetLayout, base<DescriptorSetLayout>>("CCWGPUDescriptorSetLayout")
        .constructor<>();

    class_<DescriptorSet>("DescriptorSet")
        .function("initialize", &DescriptorSet::initialize)
        .function("destroy", &DescriptorSet::destroy)
        .function("update", &DescriptorSet::update);
    class_<CCWGPUDescriptorSet, base<DescriptorSet>>("CCWGPUDescriptorSet")
        .constructor<>();

    //--------------------------------------------------CONTAINER-----------------------------------------------------------------------
    register_vector<int>("vector_int");
    register_vector<uint>("vector_uint");
    register_vector<AccessType>("AccessTypeList");
    register_vector<SubpassInfo>("SubpassInfoList");
    register_vector<ColorAttachment>("ColorAttachmentList");
    register_vector<SubpassDependency>("SubpassDependencyList");
    register_vector<Texture *>("TextureList");
    register_vector<const uint8_t *>("BufferDataList");
    register_vector<BufferTextureCopy>("BufferTextureCopyList");
    register_vector<Sampler *>("SamplerList");
    register_vector<DescriptorSetLayoutBinding>("DescriptorSetLayoutBindingList");
};

} // namespace gfx
} // namespace cc