#pragma once
#include <webgpu/webgpu.h>
#include "cocos/base/Log.h"
#include "cocos/base/Macros.h"
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

static constexpr WGPUColor defaultClearColor{0.2, 0.2, 0.2, 1.0};

static constexpr float defaultClearDepth = 1.0f;

} // namespace gfx
} // namespace cc