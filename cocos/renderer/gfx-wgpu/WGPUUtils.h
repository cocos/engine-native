#pragma once
#include <webgpu/webgpu.h>
#include "cocos/base/Log.h"
#include "cocos/base/Macros.h"
#include "cocos/base/TypeDef.h"
#include "gfx-base/GFXDef-common.h"
namespace cc {
namespace gfx {

static WGPULoadOp toWGPULoadOp(LoadOp op) {
    switch (op) {
        case LoadOp::CLEAR:
            return WGPULoadOp::WGPULoadOp_Clear;
        case LoadOp::LOAD:
            return WGPULoadOp::WGPULoadOp_Load;
        case LoadOp::DISCARD:
            return WGPULoadOp::WGPULoadOp_Force32;
        default:
            return WGPULoadOp::WGPULoadOp_Force32;
    }
}

static WGPUStoreOp toWGPUStoreOp(StoreOp op) {
    switch (op) {
        case StoreOp::STORE:
            return WGPUStoreOp::WGPUStoreOp_Store;
        case StoreOp::DISCARD:
            return WGPUStoreOp::WGPUStoreOp_Clear;
        default:
            return WGPUStoreOp::WGPUStoreOp_Force32;
    }
}

static WGPUTextureUsage toWGPUTextureUsage(TextureUsage usage) {
    switch (usage) {
        case cc::gfx::TextureUsageBit::NONE:
            return WGPUTextureUsage::WGPUTextureUsage_None;
        case cc::gfx::TextureUsageBit::TRANSFER_SRC:
            return WGPUTextureUsage::WGPUTextureUsage_CopySrc;
        case cc::gfx::TextureUsageBit::TRANSFER_DST:
            return WGPUTextureUsage::WGPUTextureUsage_CopyDst;
        case cc::gfx::TextureUsageBit::SAMPLED:
            return WGPUTextureUsage::WGPUTextureUsage_Sampled;
        case cc::gfx::TextureUsageBit::STORAGE:
            return WGPUTextureUsage::WGPUTextureUsage_Storage;
        case cc::gfx::TextureUsageBit::INPUT_ATTACHMENT:
            return WGPUTextureUsage::WGPUTextureUsage_Sampled;
        case cc::gfx::TextureUsageBit::COLOR_ATTACHMENT:
            return WGPUTextureUsage::WGPUTextureUsage_OutputAttachment;
        case cc::gfx::TextureUsageBit::DEPTH_STENCIL_ATTACHMENT:
            return WGPUTextureUsage::WGPUTextureUsage_RenderAttachment;
        default:
            return WGPUTextureUsage::WGPUTextureUsage_Force32;
    }
}

static WGPUTextureDimension toWGPUTextureDimension(TextureType type) {
    switch (type) {
        case TextureType::TEX1D:
        case TextureType::TEX1D_ARRAY:
            return WGPUTextureDimension::WGPUTextureDimension_1D;
        case TextureType::TEX2D:
        case TextureType::TEX2D_ARRAY:
            return WGPUTextureDimension::WGPUTextureDimension_2D;
        case TextureType::TEX3D:
        case TextureType::CUBE:
            return WGPUTextureDimension::WGPUTextureDimension_3D;
        default:
            return WGPUTextureDimension::WGPUTextureDimension_Force32;
    }
}

static WGPUTextureViewDimension toWGPUTextureViewDimension(TextureType type) {
    switch (type) {
        case TextureType::TEX1D:
        case TextureType::TEX1D_ARRAY:
            return WGPUTextureViewDimension::WGPUTextureViewDimension_1D;
        case TextureType::TEX2D:
        case TextureType::TEX2D_ARRAY:
            return WGPUTextureViewDimension::WGPUTextureViewDimension_2D;
        case TextureType::TEX3D:
        case TextureType::CUBE:
            return WGPUTextureViewDimension::WGPUTextureViewDimension_3D;
        default:
            return WGPUTextureViewDimension::WGPUTextureViewDimension_Undefined;
    }
}

static WGPUTextureSampleType textureSampleTypeTrait(Format format) {
    switch (format) {
        case Format::R8:
        case Format::R8UI:
        case Format::R16UI:
        case Format::RG8SN:
        case Format::RG8UI:
        case Format::RG8:
        case Format::R32UI:
        case Format::RG16UI:
        case Format::RGBA8:
        case Format::BGRA8:
        case Format::RGBA8UI:
        case Format::RG32UI:
        case Format::SRGB8_A8:
        case Format::RGBA32UI:
        case Format::RGBA16UI:
        case Format::RGB10A2:
            return WGPUTextureSampleType::WGPUTextureSampleType_Uint;
        case Format::R8SN:
        case Format::R8I:
        case Format::R16I:
        case Format::RG8I:
        case Format::RG16I:
        case Format::RGBA8SN:
        case Format::RGBA8I:
        case Format::RG32I:
        case Format::RGBA16I:
        case Format::RGBA32I:
        case Format::R32I:
            return WGPUTextureSampleType::WGPUTextureSampleType_Sint;
        case Format::R16F:
        case Format::R32F:
        case Format::RG16F:
        case Format::R11G11B10F:
        case Format::RGB9E5:
        case Format::RG32F:
        case Format::RGBA16F:
        case Format::RGBA32F:
            return WGPUTextureSampleType::WGPUTextureSampleType_Float;
        case Format::DEPTH:
            return WGPUTextureSampleType::WGPUTextureSampleType_Depth;
        default:
            CC_LOG_ERROR("unsupport texture sample type yet, github@hana-alice to fix.");
    }
}

static WGPUTextureAspect textureAspectTrait(Format format) {
    switch (format) {
        case Format::DEPTH:
            return WGPUTextureAspect_DepthOnly;
        case Format::DEPTH_STENCIL:
            return WGPUTextureAspect_All;
    }
}

static WGPUTextureFormat toWGPUTextureFormat(Format format) {
    switch (format) {
        case Format::UNKNOWN:
            return WGPUTextureFormat::WGPUTextureFormat_Undefined;
        case Format::R8:
            return WGPUTextureFormat::WGPUTextureFormat_R8Unorm;
        case Format::R8SN:
            return WGPUTextureFormat::WGPUTextureFormat_R8Snorm;
        case Format::R8UI:
            return WGPUTextureFormat::WGPUTextureFormat_R8Uint;
        case Format::R8I:
            return WGPUTextureFormat::WGPUTextureFormat_R8Sint;
        case Format::R16UI:
            return WGPUTextureFormat::WGPUTextureFormat_R16Uint;
        case Format::R16I:
            return WGPUTextureFormat::WGPUTextureFormat_R16Sint;
        case Format::R16F:
            return WGPUTextureFormat::WGPUTextureFormat_R16Float;
        case Format::RG8:
            return WGPUTextureFormat::WGPUTextureFormat_RG8Unorm;
        case Format::RG8SN:
            return WGPUTextureFormat::WGPUTextureFormat_RG8Snorm;
        case Format::RG8UI:
            return WGPUTextureFormat::WGPUTextureFormat_RG8Uint;
        case Format::RG8I:
            return WGPUTextureFormat::WGPUTextureFormat_RG8Sint;
        case Format::R32F:
            return WGPUTextureFormat::WGPUTextureFormat_R32Float;
        case Format::R32UI:
            return WGPUTextureFormat::WGPUTextureFormat_R32Uint;
        case Format::R32I:
            return WGPUTextureFormat::WGPUTextureFormat_R32Sint;
        case Format::RG16UI:
            return WGPUTextureFormat::WGPUTextureFormat_RG16Uint;
        case Format::RG16I:
            return WGPUTextureFormat::WGPUTextureFormat_RG16Sint;
        case Format::RG16F:
            return WGPUTextureFormat::WGPUTextureFormat_RG16Float;
        case Format::RGBA8:
            return WGPUTextureFormat::WGPUTextureFormat_RGBA8Unorm;
        case Format::SRGB8_A8:
            return WGPUTextureFormat::WGPUTextureFormat_RGBA8UnormSrgb;
        case Format::RGBA8SN:
            return WGPUTextureFormat::WGPUTextureFormat_RGBA8Snorm;
        case Format::RGBA8UI:
            return WGPUTextureFormat::WGPUTextureFormat_RGBA8Uint;
        case Format::RGBA8I:
            return WGPUTextureFormat::WGPUTextureFormat_RGBA8Sint;
        case Format::BGRA8:
            return WGPUTextureFormat::WGPUTextureFormat_BGRA8Unorm;
        case Format::RGB10A2:
            return WGPUTextureFormat::WGPUTextureFormat_RGB10A2Unorm;
        case Format::R11G11B10F:
            return WGPUTextureFormat::WGPUTextureFormat_RG11B10Ufloat;
        case Format::RGB9E5:
            return WGPUTextureFormat::WGPUTextureFormat_RGB9E5Ufloat;
        case Format::RG32F:
            return WGPUTextureFormat::WGPUTextureFormat_RG32Float;
        case Format::RG32UI:
            return WGPUTextureFormat::WGPUTextureFormat_RG32Uint;
        case Format::RG32I:
            return WGPUTextureFormat::WGPUTextureFormat_RG32Sint;
        case Format::RGBA16UI:
            return WGPUTextureFormat::WGPUTextureFormat_RGBA16Uint;
        case Format::RGBA16I:
            return WGPUTextureFormat::WGPUTextureFormat_RGBA16Sint;
        case Format::RGBA16F:
            return WGPUTextureFormat::WGPUTextureFormat_RGBA16Float;
        case Format::RGBA32F:
            return WGPUTextureFormat::WGPUTextureFormat_RGBA32Float;
        case Format::RGBA32UI:
            return WGPUTextureFormat::WGPUTextureFormat_RGBA32Uint;
        case Format::RGBA32I:
            return WGPUTextureFormat::WGPUTextureFormat_RGBA32Sint;
        case Format::DEPTH:
            return WGPUTextureFormat::WGPUTextureFormat_Depth32Float;
        case Format::DEPTH_STENCIL:
            return WGPUTextureFormat::WGPUTextureFormat_Depth24PlusStencil8;
        case Format::BC1:
            return WGPUTextureFormat::WGPUTextureFormat_BC1RGBAUnorm;
        case Format::BC1_SRGB:
            return WGPUTextureFormat::WGPUTextureFormat_BC1RGBAUnormSrgb;
        case Format::BC2:
            return WGPUTextureFormat::WGPUTextureFormat_BC2RGBAUnorm;
        case Format::BC2_SRGB:
            return WGPUTextureFormat::WGPUTextureFormat_BC2RGBAUnormSrgb;
        case Format::BC3:
            return WGPUTextureFormat::WGPUTextureFormat_BC3RGBAUnorm;
        case Format::BC4:
            return WGPUTextureFormat::WGPUTextureFormat_BC4RUnorm;
        case Format::BC4_SNORM:
            return WGPUTextureFormat::WGPUTextureFormat_BC4RSnorm;
        case Format::BC5:
            return WGPUTextureFormat::WGPUTextureFormat_BC5RGUnorm;
        case Format::BC5_SNORM:
            return WGPUTextureFormat::WGPUTextureFormat_BC5RGSnorm;
        case Format::BC6H_UF16:
            return WGPUTextureFormat::WGPUTextureFormat_BC6HRGBUfloat;
        case Format::BC6H_SF16:
            return WGPUTextureFormat::WGPUTextureFormat_BC6HRGBFloat;
        case Format::BC7:
            return WGPUTextureFormat::WGPUTextureFormat_BC7RGBAUnorm;
        case Format::BC7_SRGB:
            return WGPUTextureFormat::WGPUTextureFormat_BC7RGBAUnormSrgb;
        default:
            CC_LOG_ERROR("unsupport WebGPU texture format.");
            return WGPUTextureFormat::WGPUTextureFormat_Force32;
    }
}

static WGPUAddressMode toWGPUAddressMode(Address addrMode) {
    switch (addrMode) {
        case Address::WRAP:
            return WGPUAddressMode::WGPUAddressMode_Repeat;
        case Address::CLAMP:
            return WGPUAddressMode::WGPUAddressMode_ClampToEdge;
        case Address::BORDER:
            return WGPUAddressMode::WGPUAddressMode_ClampToEdge;
        case Address::MIRROR:
            return WGPUAddressMode::WGPUAddressMode_MirrorRepeat;
    }
}

static WGPUFilterMode toWGPUFilterMode(Filter filter) {
    switch (filter) {
        case Filter::NONE:
            return WGPUFilterMode::WGPUFilterMode_Force32;
        case Filter::POINT:
            return WGPUFilterMode::WGPUFilterMode_Nearest;
        case Filter::LINEAR:
            return WGPUFilterMode::WGPUFilterMode_Linear;
        case Filter::ANISOTROPIC:
            return WGPUFilterMode::WGPUFilterMode_Linear;
    }
}

static WGPUCompareFunction toWGPUCompareFunction(ComparisonFunc compareFunc) {
    switch (compareFunc) {
        case ComparisonFunc::NEVER:
            return WGPUCompareFunction::WGPUCompareFunction_Never;
        case ComparisonFunc::LESS:
            return WGPUCompareFunction::WGPUCompareFunction_Less;
        case ComparisonFunc::EQUAL:
            return WGPUCompareFunction::WGPUCompareFunction_Equal;
        case ComparisonFunc::LESS_EQUAL:
            return WGPUCompareFunction::WGPUCompareFunction_LessEqual;
        case ComparisonFunc::GREATER:
            return WGPUCompareFunction::WGPUCompareFunction_Greater;
        case ComparisonFunc::NOT_EQUAL:
            return WGPUCompareFunction::WGPUCompareFunction_NotEqual;
        case ComparisonFunc::GREATER_EQUAL:
            return WGPUCompareFunction::WGPUCompareFunction_GreaterEqual;
        case ComparisonFunc::ALWAYS:
            return WGPUCompareFunction::WGPUCompareFunction_Always;
    }
}

static WGPUShaderStageFlags toWGPUShaderStageFlag(ShaderStageFlagBit flag) {
    WGPUShaderStageFlags result = WGPUShaderStage::WGPUShaderStage_None;
    if (flag == ShaderStageFlagBit::NONE) {
        return WGPUShaderStage_None;
    }

    if (flag & ShaderStageFlagBit::ALL || flag & ShaderStageFlagBit::VERTEX) {
        result |= WGPUShaderStage::WGPUShaderStage_Vertex;
    }

    if (flag & ShaderStageFlagBit::ALL || flag & ShaderStageFlagBit::FRAGMENT) {
        result |= WGPUShaderStage::WGPUShaderStage_Fragment;
    }

    if (flag & ShaderStageFlagBit::ALL || flag & ShaderStageFlagBit::COMPUTE) {
        result |= WGPUShaderStage::WGPUShaderStage_Compute;
    }

    if (result == WGPUShaderStage_None) {
        CC_LOG_ERROR("unsupport shader stage detected");
    }
    return result;
}

//TODO_Zeqiang: more flexible strategy
static uint32_t toWGPUSampleCount(SampleCount sampleCount) {
    switch (sampleCount) {
        case SampleCount::ONE:
            return 1;
        case SampleCount::MULTIPLE_PERFORMANCE:
            return 2;
        case SampleCount::MULTIPLE_BALANCE:
            return 4;
        case SampleCount::MULTIPLE_QUALITY:
            return 8;
        default:
            return 1;
    }
}

// NONE         = 0,
// TRANSFER_SRC = 0x1,
// TRANSFER_DST = 0x2,
// INDEX        = 0x4,
// VERTEX       = 0x8,
// UNIFORM      = 0x10,
// STORAGE      = 0x20,
// INDIRECT     = 0x40,

static WGPUBufferUsageFlags toWGPUBufferUsage(BufferUsageBit usage) {
    switch (usage) {
        case BufferUsageBit::NONE:
            return WGPUBufferUsage_None;
        case BufferUsageBit::TRANSFER_SRC:
            return WGPUBufferUsage_CopySrc;
        case BufferUsageBit::TRANSFER_DST:
            return WGPUBufferUsage_CopyDst;
        case BufferUsageBit::INDEX:
            return WGPUBufferUsage_Index;
        case BufferUsageBit::VERTEX:
            return WGPUBufferUsage_Vertex;
        case BufferUsageBit::UNIFORM:
            return WGPUBufferUsage_Uniform;
        case BufferUsageBit::STORAGE:
            return WGPUBufferUsage_Storage;
        case BufferUsageBit::INDIRECT:
            return WGPUBufferUsage_Indirect;
        default:
            return WGPUBufferUsage_Force32;
    }
}

static constexpr WGPUColor defaultClearColor{0.2, 0.2, 0.2, 1.0};

static constexpr float defaultClearDepth = 1.0f;

static constexpr uint16_t maxTextureSlot = 16;

} // namespace gfx
} // namespace cc