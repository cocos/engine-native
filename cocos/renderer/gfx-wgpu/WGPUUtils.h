#pragma once
#include <webgpu/webgpu.h>
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
        case TextureUsage::None:
            return WGPUTextureUsage::WGPUTextureUsage_None;
        case TextureUsage::CopySrc:
            return WGPUTextureUsage::WGPUTextureUsage_CopySrc;
        case TextureUsage::CopyDst:
            return WGPUTextureUsage::WGPUTextureUsage_CopyDst;
        case TextureUsage::Sampled:
            return WGPUTextureUsage::WGPUTextureUsage_Sampled;
        case TextureUsage::Storage:
            return WGPUTextureUsage::WGPUTextureUsage_Storage;
        case TextureUsage::OutputAttachment:
            return WGPUTextureUsage::WGPUTextureUsage_OutputAttachment;
        case TextureUsage::RenderAttachment:
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
/*
    WGPUTextureFormat_Undefined = 0x00000000,
    WGPUTextureFormat_R8Unorm = 0x00000001,
    WGPUTextureFormat_R8Snorm = 0x00000002,
    WGPUTextureFormat_R8Uint = 0x00000003,
    WGPUTextureFormat_R8Sint = 0x00000004,
    WGPUTextureFormat_R16Uint = 0x00000005,
    WGPUTextureFormat_R16Sint = 0x00000006,
    WGPUTextureFormat_R16Float = 0x00000007,
    WGPUTextureFormat_RG8Unorm = 0x00000008,
    WGPUTextureFormat_RG8Snorm = 0x00000009,
    WGPUTextureFormat_RG8Uint = 0x0000000A,
    WGPUTextureFormat_RG8Sint = 0x0000000B,
    WGPUTextureFormat_R32Float = 0x0000000C,
    WGPUTextureFormat_R32Uint = 0x0000000D,
    WGPUTextureFormat_R32Sint = 0x0000000E,
    WGPUTextureFormat_RG16Uint = 0x0000000F,
    WGPUTextureFormat_RG16Sint = 0x00000010,
    WGPUTextureFormat_RG16Float = 0x00000011,
    WGPUTextureFormat_RGBA8Unorm = 0x00000012,
    WGPUTextureFormat_RGBA8UnormSrgb = 0x00000013,
    WGPUTextureFormat_RGBA8Snorm = 0x00000014,
    WGPUTextureFormat_RGBA8Uint = 0x00000015,
    WGPUTextureFormat_RGBA8Sint = 0x00000016,
    WGPUTextureFormat_BGRA8Unorm = 0x00000017,
    WGPUTextureFormat_BGRA8UnormSrgb = 0x00000018,
    WGPUTextureFormat_RGB10A2Unorm = 0x00000019,
    WGPUTextureFormat_RG11B10Ufloat = 0x0000001A,
    WGPUTextureFormat_RGB9E5Ufloat = 0x0000001B,
    WGPUTextureFormat_RG32Float = 0x0000001C,
    WGPUTextureFormat_RG32Uint = 0x0000001D,
    WGPUTextureFormat_RG32Sint = 0x0000001E,
    WGPUTextureFormat_RGBA16Uint = 0x0000001F,
    WGPUTextureFormat_RGBA16Sint = 0x00000020,
    WGPUTextureFormat_RGBA16Float = 0x00000021,
    WGPUTextureFormat_RGBA32Float = 0x00000022,
    WGPUTextureFormat_RGBA32Uint = 0x00000023,
    WGPUTextureFormat_RGBA32Sint = 0x00000024,
    WGPUTextureFormat_Depth32Float = 0x00000025,
    WGPUTextureFormat_Depth24Plus = 0x00000026,
    WGPUTextureFormat_Stencil8 = 0x00000027,
    WGPUTextureFormat_Depth24PlusStencil8 = 0x00000028,
    WGPUTextureFormat_BC1RGBAUnorm = 0x00000029,
    WGPUTextureFormat_BC1RGBAUnormSrgb = 0x0000002A,
    WGPUTextureFormat_BC2RGBAUnorm = 0x0000002B,
    WGPUTextureFormat_BC2RGBAUnormSrgb = 0x0000002C,
    WGPUTextureFormat_BC3RGBAUnorm = 0x0000002D,
    WGPUTextureFormat_BC3RGBAUnormSrgb = 0x0000002E,
    WGPUTextureFormat_BC4RUnorm = 0x0000002F,
    WGPUTextureFormat_BC4RSnorm = 0x00000030,
    WGPUTextureFormat_BC5RGUnorm = 0x00000031,
    WGPUTextureFormat_BC5RGSnorm = 0x00000032,
    WGPUTextureFormat_BC6HRGBUfloat = 0x00000033,
    WGPUTextureFormat_BC6HRGBFloat = 0x00000034,
    WGPUTextureFormat_BC7RGBAUnorm = 0x00000035,
    WGPUTextureFormat_BC7RGBAUnormSrgb = 0x00000036,
    WGPUTextureFormat_Force32 = 0x7FFFFFFF
*/
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
        case Format::D32F:
            return WGPUTextureFormat::WGPUTextureFormat_Depth32Float;
        case Format::D24S8:
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

static constexpr WGPUColor defaultClearColor{0.2, 0.2, 0.2, 1.0};

static constexpr float defaultClearDepth = 1.0f;

} // namespace gfx
} // namespace cc