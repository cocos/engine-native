#pragma once
#include "WGPUBuffer.h"
#include "WGPUDef.h"
#include "WGPUDescriptorSet.h"
#include "WGPUDescriptorSetLayout.h"
#include "WGPUDevice.h"
#include "WGPUFrameBuffer.h"
#include "WGPUPipelineLayout.h"
#include "WGPURenderPass.h"
#include "WGPUSampler.h"
#include "WGPUShader.h"
#include "WGPUSwapchain.h"
#include "WGPUTexture.h"

// #define OBJECT_EXPORT(c) \
//     static c c##Instance() { return c(); }
namespace cc::gfx {

template <typename T>
struct GenInstance {
    static T instance() {
        return T();
    }
};

// template <typename T, class... Ts>
// struct GenInstances {
//     OBJECT_EXPORT(T);
//     GenInstance<Ts...>;
// };

// template <typename T>
// struct GenInstances<T> {
//     OBJECT_EXPORT(T);
// };

// GenInstances<DeviceInfo, BindingMappingInfo, ColorAttachment, DepthStencilAttachment, SubpassInfo, SubpassDependency, RenderPassInfo, Offset, Extent, TextureSubresLayers, BufferTextureCopy, SamplerInfo, BufferInfo,
//              DescriptorSetLayoutInfo, DescriptorSetLayoutBinding, PipelineLayoutInfo, UniformStorageImage, ShaderStage, Attribute, UniformBlock, UniformStorageBuffer>;

EMSCRIPTEN_BINDINGS(WEBGPU_DEVICE_WASM_EXPORT) {
    // TODO_Zeqiang: compile time traverse enum

    //------------------------------------------------ENUM------------------------------------------------------------
    enum_<Format>("Format")
        .value("UNKNOWN", Format::UNKNOWN)
        .value("R32F", Format::R32F)
        .value("RGB8", Format::RGB8)
        .value("RGBA8", Format::RGBA8)
        .value("BGRA8", Format::BGRA8)
        .value("RG32F", Format::RG32F)
        .value("RGB8", Format::RGB8)
        .value("RGB16F", Format::RGB16F)
        .value("RGBA32F", Format::RGBA32F)
        .value("RGB32F", Format::RGB32F)
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

    enum_<MemoryAccess>("MemoryAccess")
        .value("NONE", MemoryAccessBit::NONE)
        .value("READ_ONLY", MemoryAccessBit::READ_ONLY)
        .value("WRITE_ONLY", MemoryAccessBit::WRITE_ONLY)
        .value("READ_WRITE", MemoryAccessBit::READ_WRITE);

    enum_<Type>("Type")
        .value("UNKNOWN", Type::UNKNOWN)
        .value("BOOL", Type::BOOL)
        .value("BOOL2", Type::BOOL2)
        .value("BOOL3", Type::BOOL3)
        .value("BOOL4", Type::BOOL4)
        .value("INT", Type::INT)
        .value("INT2", Type::INT2)
        .value("INT3", Type::INT3)
        .value("INT4", Type::INT4)
        .value("UINT", Type::UINT)
        .value("UINT2", Type::UINT2)
        .value("UINT3", Type::UINT3)
        .value("UINT4", Type::UINT4)
        .value("FLOAT", Type::FLOAT)
        .value("FLOAT2", Type::FLOAT2)
        .value("FLOAT3", Type::FLOAT3)
        .value("FLOAT4", Type::FLOAT4)
        .value("MAT2", Type::MAT2)
        .value("MAT2X3", Type::MAT2X3)
        .value("MAT2X4", Type::MAT2X4)
        .value("MAT3X2", Type::MAT3X2)
        .value("MAT3X4", Type::MAT3X4)
        .value("MAT4X2", Type::MAT4X2)
        .value("MAT4X3", Type::MAT4X3)
        .value("MAT4", Type::MAT4)
        .value("SAMPLER1D", Type::SAMPLER1D)
        .value("SAMPLER1D_ARRAY", Type::SAMPLER1D_ARRAY)
        .value("SAMPLER2D", Type::SAMPLER2D)
        .value("SAMPLER2D_ARRAY", Type::SAMPLER2D_ARRAY)
        .value("SAMPLER3D", Type::SAMPLER3D)
        .value("SAMPLER_CUBE", Type::SAMPLER_CUBE)
        .value("SAMPLER", Type::SAMPLER)
        .value("TEXTURE1D", Type::TEXTURE1D)
        .value("TEXTURE1D_ARRAY", Type::TEXTURE1D_ARRAY)
        .value("TEXTURE2D", Type::TEXTURE2D)
        .value("TEXTURE2D_ARRAY", Type::TEXTURE2D_ARRAY)
        .value("TEXTURE3D", Type::TEXTURE3D)
        .value("TEXTURE_CUBE", Type::TEXTURE_CUBE)
        .value("IMAGE1D", Type::IMAGE1D)
        .value("IMAGE1D_ARRAY", Type::IMAGE1D_ARRAY)
        .value("IMAGE2D", Type::IMAGE2D)
        .value("IMAGE2D_ARRAY", Type::IMAGE2D_ARRAY)
        .value("IMAGE3D", Type::IMAGE3D)
        .value("IMAGE_CUBE", Type::IMAGE_CUBE)
        .value("IMAGE3D", Type::IMAGE3D)
        .value("SUBPASS_INPUT", Type::SUBPASS_INPUT)
        .value("COUNT", Type::COUNT);

    //-----------------------------------------------STRUCT-------------------------------------------------------------------
    value_object<ColorAttachment>("ColorAttachment")
        .field("format", &ColorAttachment::format)
        .field("sampleCount", &ColorAttachment::sampleCount)
        .field("loadOp", &ColorAttachment::loadOp)
        .field("storeOp", &ColorAttachment::storeOp)
        .field("beginAccesses", &ColorAttachment::beginAccesses)
        .field("endAccesses", &ColorAttachment::endAccesses)
        .field("isGeneralLayout", &ColorAttachment::isGeneralLayout);
    function("ColorAttachmentInstance", &GenInstance<ColorAttachment>::instance);

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
    function("DepthStencilAttachmentInstance", &GenInstance<DepthStencilAttachment>::instance);

    value_object<SubpassInfo>("SubpassInfo")
        .field("inputs", &SubpassInfo::inputs)
        .field("colors", &SubpassInfo::colors)
        .field("resolves", &SubpassInfo::resolves)
        .field("preserves", &SubpassInfo::preserves)
        .field("depthStencil", &SubpassInfo::depthStencil)
        .field("depthStencilResolve", &SubpassInfo::depthStencilResolve)
        .field("depthResolveMode", &SubpassInfo::depthResolveMode)
        .field("stencilResolveMode", &SubpassInfo::stencilResolveMode);
    function("SubpassInfoInstance", &GenInstance<SubpassInfo>::instance);

    value_object<SubpassDependency>("SubpassDependency")
        .field("srcSubpass", &SubpassDependency::srcSubpass)
        .field("dstSubpass", &SubpassDependency::dstSubpass)
        .field("srcAccesses", &SubpassDependency::srcAccesses)
        .field("dstAccesses", &SubpassDependency::dstAccesses);
    function("SubpassDependencyInstance", &GenInstance<SubpassDependency>::instance);

    value_object<RenderPassInfo>("RenderPassInfo")
        .field("colorAttachments", &RenderPassInfo::colorAttachments)
        .field("depthStencilAttachment", &RenderPassInfo::depthStencilAttachment)
        .field("subpasses", &RenderPassInfo::subpasses)
        .field("dependencies", &RenderPassInfo::dependencies);
    function("RenderPassInfoInstance", &GenInstance<RenderPassInfo>::instance);

    value_object<BindingMappingInfo>("BindingMappingInfo")
        .field("bufferOffsets", &BindingMappingInfo::bufferOffsets)
        .field("samplerOffsets", &BindingMappingInfo::samplerOffsets)
        .field("flexibleSet", &BindingMappingInfo::flexibleSet);
    function("BindingMappingInfoInstance", &GenInstance<BindingMappingInfo>::instance);

    value_object<DeviceInfo>("DeviceInfo")
        .field("bindingMappingInfo", &DeviceInfo::bindingMappingInfo);
    function("DeviceInfoInstance", &GenInstance<DeviceInfo>::instance);

    value_object<Offset>("Offset")
        .field("x", &Offset::x)
        .field("y", &Offset::y)
        .field("z", &Offset::z);
    function("OffsetInstance", &GenInstance<Offset>::instance);

    value_object<Extent>("Extent")
        .field("width", &Extent::width)
        .field("height", &Extent::height)
        .field("depth", &Extent::depth);
    function("ExtentInstance", &GenInstance<Extent>::instance);

    value_object<TextureSubresLayers>("TextureSubresLayers")
        .field("mipLevel", &TextureSubresLayers::mipLevel)
        .field("baseArrayLayer", &TextureSubresLayers::baseArrayLayer)
        .field("layerCount", &TextureSubresLayers::layerCount);
    function("TextureSubresLayersInstance", &GenInstance<TextureSubresLayers>::instance);

    value_object<BufferTextureCopy>("BufferTextureCopy")
        .field("buffStride", &BufferTextureCopy::buffStride)
        .field("buffTexHeight", &BufferTextureCopy::buffTexHeight)
        .field("texOffset", &BufferTextureCopy::texOffset)
        .field("texExtent", &BufferTextureCopy::texExtent)
        .field("texSubres", &BufferTextureCopy::texSubres);
    function("BufferTextureCopyInstance", &GenInstance<BufferTextureCopy>::instance);

    value_object<SamplerInfo>("SamplerInfo")
        .field("minFilter", &SamplerInfo::minFilter)
        .field("magFilter", &SamplerInfo::magFilter)
        .field("mipFilter", &SamplerInfo::mipFilter)
        .field("addressU", &SamplerInfo::addressU)
        .field("addressV", &SamplerInfo::addressV)
        .field("addressW", &SamplerInfo::addressW)
        .field("maxAnisotropy", &SamplerInfo::maxAnisotropy)
        .field("cmpFunc", &SamplerInfo::cmpFunc);
    function("SamplerInfoInstance", &GenInstance<SamplerInfo>::instance);

    value_object<BufferInfo>("BufferInfo")
        .field("usage", &BufferInfo::usage)
        .field("memUsage", &BufferInfo::memUsage)
        .field("size", &BufferInfo::size)
        .field("stride", &BufferInfo::stride)
        .field("flags", &BufferInfo::flags);
    function("BufferInfoInstance", &GenInstance<BufferInfo>::instance);

    value_object<DescriptorSetLayoutInfo>("DescriptorSetLayoutInfo")
        .field("bindings", &DescriptorSetLayoutInfo::bindings);
    function("DescriptorSetLayoutInfoInstance", &GenInstance<DescriptorSetLayoutInfo>::instance);

    value_object<DescriptorSetLayoutBinding>("DescriptorSetLayoutBinding")
        .field("binding", &DescriptorSetLayoutBinding::binding)
        .field("descriptorType", &DescriptorSetLayoutBinding::descriptorType)
        .field("count", &DescriptorSetLayoutBinding::count)
        .field("stageFlags", &DescriptorSetLayoutBinding::stageFlags)
        .field("immutableSamplers", &DescriptorSetLayoutBinding::immutableSamplers);
    function("DescriptorSetLayoutBindingInstance", &GenInstance<DescriptorSetLayoutBinding>::instance);

    value_object<PipelineLayoutInfo>("PipelineLayoutInfo")
        .field("setLayouts", &PipelineLayoutInfo::setLayouts);
    function("PipelineLayoutInfoInstance", &GenInstance<PipelineLayoutInfo>::instance);

    value_object<UniformStorageImage>("UniformStorageImage")
        .field("set", &UniformStorageImage::set)
        .field("binding", &UniformStorageImage::binding)
        .field("name", &UniformStorageImage::name)
        .field("type", &UniformStorageImage::type)
        .field("count", &UniformStorageImage::count)
        .field("memoryAccess", &UniformStorageImage::memoryAccess);
    function("UniformStorageImageInstance", &GenInstance<UniformStorageImage>::instance);

    value_object<ShaderStage>("ShaderStage")
        .field("stage", &ShaderStage::stage)
        .field("source", &ShaderStage::source);
    function("ShaderStageInstance", &GenInstance<ShaderStage>::instance);

    value_object<Attribute>("Attribute")
        .field("name", &Attribute::name)
        .field("format", &Attribute::format)
        .field("isNormalized", &Attribute::isNormalized)
        .field("stream", &Attribute::stream)
        .field("isInstanced", &Attribute::isInstanced)
        .field("location", &Attribute::location);
    function("AttributeInstance", &GenInstance<Attribute>::instance);

    value_object<Uniform>("Uniform")
        .field("name", &Uniform::name)
        .field("type", &Uniform::type)
        .field("count", &Uniform::count);
    function("UniformInstance", &GenInstance<Uniform>::instance);

    value_object<UniformBlock>("UniformBlock")
        .field("set", &UniformBlock::set)
        .field("binding", &UniformBlock::binding)
        .field("name", &UniformBlock::name)
        .field("members", &UniformBlock::members)
        .field("count", &UniformBlock::count);
    function("UniformBlockInstance", &GenInstance<UniformBlock>::instance);

    value_object<UniformStorageBuffer>("UniformStorageBuffer")
        .field("set", &UniformStorageBuffer::set)
        .field("binding", &UniformStorageBuffer::binding)
        .field("name", &UniformStorageBuffer::name)
        .field("count", &UniformStorageBuffer::count)
        .field("memoryAccess", &UniformStorageBuffer::memoryAccess);
    function("UniformStorageBufferInstance", &GenInstance<UniformStorageBuffer>::instance);

    value_object<UniformSamplerTexture>("UniformSamplerTexture")
        .field("set", &UniformSamplerTexture::set)
        .field("binding", &UniformSamplerTexture::binding)
        .field("name", &UniformSamplerTexture::name)
        .field("type", &UniformSamplerTexture::type)
        .field("count", &UniformSamplerTexture::count);
    function("UniformSamplerTextureInstance", &GenInstance<UniformSamplerTexture>::instance);

    value_object<UniformSampler>("UniformSampler")
        .field("set", &UniformSampler::set)
        .field("binding", &UniformSampler::binding)
        .field("name", &UniformSampler::name)
        .field("count", &UniformSampler::count);
    function("UniformSamplerInstance", &GenInstance<UniformSampler>::instance);

    value_object<UniformTexture>("UniformTexture")
        .field("set", &UniformTexture::set)
        .field("binding", &UniformTexture::binding)
        .field("name", &UniformTexture::name)
        .field("type", &UniformTexture::type)
        .field("count", &UniformTexture::count);
    function("UniformTextureInstance", &GenInstance<UniformTexture>::instance);

    value_object<UniformInputAttachment>("UniformInputAttachment")
        .field("set", &UniformInputAttachment::set)
        .field("binding", &UniformInputAttachment::binding)
        .field("name", &UniformInputAttachment::name)
        .field("count", &UniformInputAttachment::count);
    function("UniformInputAttachmentInstance", &GenInstance<UniformInputAttachment>::instance);

    value_object<ShaderInfo>("ShaderInfo")
        .field("name", &ShaderInfo::name)
        .field("stages", &ShaderInfo::stages)
        .field("attributes", &ShaderInfo::attributes)
        .field("blocks", &ShaderInfo::blocks)
        .field("buffers", &ShaderInfo::buffers)
        .field("samplerTextures", &ShaderInfo::samplerTextures)
        .field("samplers", &ShaderInfo::samplers)
        .field("textures", &ShaderInfo::textures)
        .field("images", &ShaderInfo::images)
        .field("imsubpassInputsages", &ShaderInfo::subpassInputs);
    function("ShaderInfoInstance", &GenInstance<ShaderInfo>::instance);

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
        .function("desctroy", &Buffer::destroy);
    class_<CCWGPUBuffer, base<Buffer>>("CCWGPUBuffer")
        .function("update", select_overload<void(String, uint)>(&CCWGPUBuffer::update), allow_raw_pointer<arg<0>>())
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

    class_<PipelineLayout>("PipelineLayout")
        .function("initialize", &PipelineLayout::initialize)
        .function("destroy", &PipelineLayout::destroy);
    class_<CCWGPUPipelineLayout, base<PipelineLayout>>("CCWGPUPipelineLayout")
        .constructor<>();

    class_<Shader>("Shader")
        .function("initialize", &Shader::initialize)
        .function("destroy", &Shader::destroy);
    class_<CCWGPUShader>("CCWGPUShader")
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
    register_vector<DescriptorSetLayout *>("DescriptorSetLayoutList");
    register_vector<UniformStorageImage>("UniformStorageImageList");
    register_vector<ShaderStage>("ShaderStageList");
    register_vector<Attribute>("AttributeList");
    register_vector<UniformBlock>("UniformBlockList");
    register_vector<UniformStorageBuffer>("UniformStorageBufferList");
    register_vector<UniformSamplerTexture>("UniformSamplerTextureList");
    register_vector<UniformTexture>("UniformTextureList");
    register_vector<UniformSampler>("UniformSamplerList");
    register_vector<UniformInputAttachment>("UniformInputAttachmentList");
    register_vector<Uniform>("UniformList");
};

} // namespace cc::gfx