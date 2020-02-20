#include "GLES2Std.h"
#include "GLES2Commands.h"
#include "GLES2Device.h"
#include "GLES2StateCache.h"

#define BUFFER_OFFSET(idx) (static_cast<char*>(0) + (idx))

NS_CC_BEGIN

GLenum MapGLInternalFormat(GFXFormat format) {
  switch (format) {
    case GFXFormat::A8: return GL_ALPHA;
    case GFXFormat::L8: return GL_LUMINANCE;
    case GFXFormat::LA8: return GL_LUMINANCE_ALPHA;
    case GFXFormat::R8: return GL_LUMINANCE;
    case GFXFormat::R8SN: return GL_LUMINANCE;
    case GFXFormat::R8UI: return GL_LUMINANCE;
    case GFXFormat::R8I: return GL_LUMINANCE;
    case GFXFormat::RG8: return GL_LUMINANCE_ALPHA;
    case GFXFormat::RG8SN: return GL_LUMINANCE_ALPHA;
    case GFXFormat::RG8UI: return GL_LUMINANCE_ALPHA;
    case GFXFormat::RG8I: return GL_LUMINANCE_ALPHA;
    case GFXFormat::RGB8: return GL_RGB;
    case GFXFormat::RGB8SN: return GL_RGB;
    case GFXFormat::RGB8UI: return GL_RGB;
    case GFXFormat::RGB8I: return GL_RGB;
    case GFXFormat::RGBA8: return GL_RGBA;
    case GFXFormat::RGBA8SN: return GL_RGBA;
    case GFXFormat::RGBA8UI: return GL_RGBA;
    case GFXFormat::RGBA8I: return GL_RGBA;
    case GFXFormat::R16I: return GL_LUMINANCE;
    case GFXFormat::R16UI: return GL_LUMINANCE;
    case GFXFormat::R16F: return GL_LUMINANCE;
    case GFXFormat::RG16I: return GL_LUMINANCE_ALPHA;
    case GFXFormat::RG16UI: return GL_LUMINANCE_ALPHA;
    case GFXFormat::RG16F: return GL_LUMINANCE_ALPHA;
    case GFXFormat::RGB16I: return GL_RGB;
    case GFXFormat::RGB16UI: return GL_RGB;
    case GFXFormat::RGB16F: return GL_RGB;
    case GFXFormat::RGBA16I: return GL_RGBA;
    case GFXFormat::RGBA16UI: return GL_RGBA;
    case GFXFormat::RGBA16F: return GL_RGBA;
    case GFXFormat::R32I: return GL_LUMINANCE;
    case GFXFormat::R32UI: return GL_LUMINANCE;
    case GFXFormat::R32F: return GL_LUMINANCE;
    case GFXFormat::RG32I: return GL_LUMINANCE_ALPHA;
    case GFXFormat::RG32UI: return GL_LUMINANCE_ALPHA;
    case GFXFormat::RG32F: return GL_LUMINANCE_ALPHA;
    case GFXFormat::RGB32I: return GL_RGB;
    case GFXFormat::RGB32UI: return GL_RGB;
    case GFXFormat::RGB32F: return GL_RGB;
    case GFXFormat::RGBA32I: return GL_RGBA;
    case GFXFormat::RGBA32UI: return GL_RGBA;
    case GFXFormat::RGBA32F: return GL_RGBA;
    case GFXFormat::R5G6B5: return GL_RGB565;
    case GFXFormat::RGB5A1: return GL_RGB5_A1;
    case GFXFormat::RGBA4: return GL_RGBA4;
    case GFXFormat::RGB10A2: return GL_RGB;
    case GFXFormat::RGB10A2UI: return GL_RGB;
    case GFXFormat::R11G11B10F: return GL_RGB;
    case GFXFormat::D16: return GL_DEPTH_COMPONENT;
    case GFXFormat::D16S8: return GL_DEPTH_STENCIL_OES;
    case GFXFormat::D24: return GL_DEPTH_COMPONENT;
    case GFXFormat::D24S8: return GL_DEPTH_STENCIL_OES;
    case GFXFormat::D32F: return GL_DEPTH_COMPONENT;
    case GFXFormat::D32F_S8: return GL_DEPTH_STENCIL_OES;
      
    case GFXFormat::BC1: return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
    case GFXFormat::BC1_ALPHA: return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
    case GFXFormat::BC1_SRGB: return GL_COMPRESSED_SRGB_S3TC_DXT1_EXT;
    case GFXFormat::BC1_SRGB_ALPHA: return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
    case GFXFormat::BC2: return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
    case GFXFormat::BC2_SRGB: return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT;
    case GFXFormat::BC3: return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
    case GFXFormat::BC3_SRGB: return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT;
      
    case GFXFormat::ETC_RGB8: return GL_ETC1_RGB8_OES;
      
    case GFXFormat::PVRTC_RGB2: return GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
    case GFXFormat::PVRTC_RGBA2: return GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
    case GFXFormat::PVRTC_RGB4: return GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
    case GFXFormat::PVRTC_RGBA4: return GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
      
    default: {
      CCASSERT(false, "Unsupported GFXFormat, convert to GL internal format failed.");
      return GL_RGBA;
    }
  }
}

GLenum MapGLFormat(GFXFormat format) {
  switch (format) {
    case GFXFormat::A8: return GL_ALPHA;
    case GFXFormat::L8: return GL_LUMINANCE;
    case GFXFormat::LA8: return GL_LUMINANCE_ALPHA;
    case GFXFormat::R8:
    case GFXFormat::R8SN:
    case GFXFormat::R8UI:
    case GFXFormat::R8I: return GL_LUMINANCE;
    case GFXFormat::RG8:
    case GFXFormat::RG8SN:
    case GFXFormat::RG8UI:
    case GFXFormat::RG8I: return GL_LUMINANCE_ALPHA;
    case GFXFormat::RGB8:
    case GFXFormat::RGB8SN:
    case GFXFormat::RGB8UI:
    case GFXFormat::RGB8I: return GL_RGB;
    case GFXFormat::RGBA8:
    case GFXFormat::RGBA8SN:
    case GFXFormat::RGBA8UI:
    case GFXFormat::RGBA8I: return GL_RGBA;
    case GFXFormat::R16UI:
    case GFXFormat::R16I:
    case GFXFormat::R16F: return GL_LUMINANCE;
    case GFXFormat::RG16UI:
    case GFXFormat::RG16I:
    case GFXFormat::RG16F: return GL_LUMINANCE_ALPHA;
    case GFXFormat::RGB16UI:
    case GFXFormat::RGB16I:
    case GFXFormat::RGB16F: return GL_RGB;
    case GFXFormat::RGBA16UI:
    case GFXFormat::RGBA16I:
    case GFXFormat::RGBA16F: return GL_RGBA;
    case GFXFormat::R32UI:
    case GFXFormat::R32I:
    case GFXFormat::R32F: return GL_LUMINANCE;
    case GFXFormat::RG32UI:
    case GFXFormat::RG32I:
    case GFXFormat::RG32F: return GL_LUMINANCE_ALPHA;
    case GFXFormat::RGB32UI:
    case GFXFormat::RGB32I:
    case GFXFormat::RGB32F: return GL_RGB;
    case GFXFormat::RGBA32UI:
    case GFXFormat::RGBA32I:
    case GFXFormat::RGBA32F: return GL_RGBA;
    case GFXFormat::RGB10A2: return GL_RGBA;
    case GFXFormat::R11G11B10F: return GL_RGB;
    case GFXFormat::R5G6B5: return GL_RGB;
    case GFXFormat::RGB5A1: return GL_RGBA;
    case GFXFormat::RGBA4: return GL_RGBA;
    case GFXFormat::D16: return GL_DEPTH_COMPONENT;
    case GFXFormat::D16S8: return GL_DEPTH_STENCIL_OES;
    case GFXFormat::D24: return GL_DEPTH_COMPONENT;
    case GFXFormat::D24S8: return GL_DEPTH_STENCIL_OES;
    case GFXFormat::D32F: return GL_DEPTH_COMPONENT;
    case GFXFormat::D32F_S8: return GL_DEPTH_STENCIL_OES;
      
    case GFXFormat::BC1: return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
    case GFXFormat::BC1_ALPHA: return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
    case GFXFormat::BC1_SRGB: return GL_COMPRESSED_SRGB_S3TC_DXT1_EXT;
    case GFXFormat::BC1_SRGB_ALPHA: return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
    case GFXFormat::BC2: return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
    case GFXFormat::BC2_SRGB: return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT;
    case GFXFormat::BC3: return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
    case GFXFormat::BC3_SRGB: return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT;

    case GFXFormat::ETC_RGB8: return GL_ETC1_RGB8_OES;
      
    case GFXFormat::PVRTC_RGB2: return GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
    case GFXFormat::PVRTC_RGBA2: return GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
    case GFXFormat::PVRTC_RGB4: return GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
    case GFXFormat::PVRTC_RGBA4: return GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
      
    default: {
      CCASSERT(false, "Unsupported GFXFormat, convert to WebGL format failed.");
      return GL_RGBA;
    }
  }
}

GLenum MapGLType(GFXType type) {
  switch (type) {
    case GFXType::BOOL: return GL_BOOL;
    case GFXType::BOOL2: return GL_BOOL_VEC2;
    case GFXType::BOOL3: return GL_BOOL_VEC3;
    case GFXType::BOOL4: return GL_BOOL_VEC4;
    case GFXType::INT: return GL_INT;
    case GFXType::INT2: return GL_INT_VEC2;
    case GFXType::INT3: return GL_INT_VEC3;
    case GFXType::INT4: return GL_INT_VEC4;
    case GFXType::UINT: return GL_UNSIGNED_INT;
    case GFXType::FLOAT: return GL_FLOAT;
    case GFXType::FLOAT2: return GL_FLOAT_VEC2;
    case GFXType::FLOAT3: return GL_FLOAT_VEC3;
    case GFXType::FLOAT4: return GL_FLOAT_VEC4;
    case GFXType::MAT2: return GL_FLOAT_MAT2;
    case GFXType::MAT3: return GL_FLOAT_MAT3;
    case GFXType::MAT4: return GL_FLOAT_MAT4;
    case GFXType::SAMPLER2D: return GL_SAMPLER_2D;
    case GFXType::SAMPLER3D: return GL_SAMPLER_3D_OES;
    case GFXType::SAMPLER_CUBE: return GL_SAMPLER_CUBE;
    default: {
      CCASSERT(false, "Unsupported GLType, convert to GL type failed.");
      return GL_NONE;
    }
  }
}

GFXType MapGFXType(GLenum glType) {
  switch (glType) {
    case GL_BOOL: return GFXType::BOOL;
    case GL_BOOL_VEC2: return GFXType::BOOL2;
    case GL_BOOL_VEC3: return GFXType::BOOL3;
    case GL_BOOL_VEC4: return GFXType::BOOL4;
    case GL_INT: return GFXType::INT;
    case GL_INT_VEC2: return GFXType::INT2;
    case GL_INT_VEC3: return GFXType::INT3;
    case GL_INT_VEC4: return GFXType::INT4;
    case GL_UNSIGNED_INT: return GFXType::UINT;
    case GL_FLOAT: return GFXType::FLOAT;
    case GL_FLOAT_VEC2: return GFXType::FLOAT2;
    case GL_FLOAT_VEC3: return GFXType::FLOAT3;
    case GL_FLOAT_VEC4: return GFXType::FLOAT4;
    case GL_FLOAT_MAT2: return GFXType::MAT2;
    case GL_FLOAT_MAT3: return GFXType::MAT3;
    case GL_FLOAT_MAT4: return GFXType::MAT4;
    case GL_SAMPLER_2D: return GFXType::SAMPLER2D;
    case GL_SAMPLER_3D_OES: return GFXType::SAMPLER3D;
    case GL_SAMPLER_CUBE: return GFXType::SAMPLER_CUBE;
    default: {
      CCASSERT(false, "Unsupported GLType, convert to GFXType failed.");
      return GFXType::UNKNOWN;
    }
  }
}

GLenum GFXFormatToGLType(GFXFormat format) {
  switch (format) {
    case GFXFormat::R8: return GL_UNSIGNED_BYTE;
    case GFXFormat::R8SN: return GL_BYTE;
    case GFXFormat::R8UI: return GL_UNSIGNED_BYTE;
    case GFXFormat::R8I: return GL_BYTE;
    case GFXFormat::R16UI: return GL_UNSIGNED_SHORT;
    case GFXFormat::R16I: return GL_SHORT;
    case GFXFormat::R32F: return GL_FLOAT;
    case GFXFormat::R32UI: return GL_UNSIGNED_INT;
    case GFXFormat::R32I: return GL_INT;
      
    case GFXFormat::RG8: return GL_UNSIGNED_BYTE;
    case GFXFormat::RG8SN: return GL_BYTE;
    case GFXFormat::RG8UI: return GL_UNSIGNED_BYTE;
    case GFXFormat::RG8I: return GL_BYTE;
    case GFXFormat::RG16UI: return GL_UNSIGNED_SHORT;
    case GFXFormat::RG16I: return GL_SHORT;
    case GFXFormat::RG32F: return GL_FLOAT;
    case GFXFormat::RG32UI: return GL_UNSIGNED_INT;
    case GFXFormat::RG32I: return GL_INT;
      
    case GFXFormat::RGB8: return GL_UNSIGNED_BYTE;
    case GFXFormat::SRGB8: return GL_UNSIGNED_BYTE;
    case GFXFormat::RGB8SN: return GL_BYTE;
    case GFXFormat::RGB8UI: return GL_UNSIGNED_BYTE;
    case GFXFormat::RGB8I: return GL_BYTE;
    case GFXFormat::RGB16F: return GL_HALF_FLOAT_OES;
    case GFXFormat::RGB16UI: return GL_UNSIGNED_SHORT;
    case GFXFormat::RGB16I: return GL_SHORT;
    case GFXFormat::RGB32F: return GL_FLOAT;
    case GFXFormat::RGB32UI: return GL_UNSIGNED_INT;
    case GFXFormat::RGB32I: return GL_INT;
      
    case GFXFormat::RGBA8: return GL_UNSIGNED_BYTE;
    case GFXFormat::SRGB8_A8: return GL_UNSIGNED_BYTE;
    case GFXFormat::RGBA8SN: return GL_BYTE;
    case GFXFormat::RGBA8UI: return GL_UNSIGNED_BYTE;
    case GFXFormat::RGBA8I: return GL_BYTE;
    case GFXFormat::RGBA16F: return GL_HALF_FLOAT_OES;
    case GFXFormat::RGBA16UI: return GL_UNSIGNED_SHORT;
    case GFXFormat::RGBA16I: return GL_SHORT;
    case GFXFormat::RGBA32F: return GL_FLOAT;
    case GFXFormat::RGBA32UI: return GL_UNSIGNED_INT;
    case GFXFormat::RGBA32I: return GL_INT;
      
    case GFXFormat::R5G6B5: return GL_UNSIGNED_SHORT_5_6_5;
    case GFXFormat::R11G11B10F: return GL_FLOAT;
    case GFXFormat::RGB5A1: return GL_UNSIGNED_SHORT_5_5_5_1;
    case GFXFormat::RGBA4: return GL_UNSIGNED_SHORT_4_4_4_4;
    case GFXFormat::RGB10A2: return GL_UNSIGNED_BYTE;
    case GFXFormat::RGB10A2UI: return GL_UNSIGNED_INT;
    case GFXFormat::RGB9E5: return GL_FLOAT;
      
    case GFXFormat::D16: return GL_UNSIGNED_SHORT;
    case GFXFormat::D16S8: return GL_UNSIGNED_SHORT;
    case GFXFormat::D24: return GL_UNSIGNED_INT;
    case GFXFormat::D24S8: return GL_UNSIGNED_INT_24_8_OES;
    case GFXFormat::D32F: return GL_FLOAT;
      
    case GFXFormat::BC1: return GL_UNSIGNED_BYTE;
    case GFXFormat::BC1_SRGB: return GL_UNSIGNED_BYTE;
    case GFXFormat::BC2: return GL_UNSIGNED_BYTE;
    case GFXFormat::BC2_SRGB: return GL_UNSIGNED_BYTE;
    case GFXFormat::BC3: return GL_UNSIGNED_BYTE;
    case GFXFormat::BC3_SRGB: return GL_UNSIGNED_BYTE;
    case GFXFormat::BC4: return GL_UNSIGNED_BYTE;
    case GFXFormat::BC4_SNORM: return GL_BYTE;
    case GFXFormat::BC5: return GL_UNSIGNED_BYTE;
    case GFXFormat::BC5_SNORM: return GL_BYTE;
    case GFXFormat::BC6H_SF16: return GL_FLOAT;
    case GFXFormat::BC6H_UF16: return GL_FLOAT;
    case GFXFormat::BC7: return GL_UNSIGNED_BYTE;
    case GFXFormat::BC7_SRGB: return GL_UNSIGNED_BYTE;
      
    case GFXFormat::ETC_RGB8: return GL_UNSIGNED_BYTE;
    case GFXFormat::ETC2_RGB8: return GL_UNSIGNED_BYTE;
    case GFXFormat::ETC2_SRGB8: return GL_UNSIGNED_BYTE;
    case GFXFormat::ETC2_RGB8_A1: return GL_UNSIGNED_BYTE;
    case GFXFormat::ETC2_SRGB8_A1: return GL_UNSIGNED_BYTE;
    case GFXFormat::EAC_R11: return GL_UNSIGNED_BYTE;
    case GFXFormat::EAC_R11SN: return GL_BYTE;
    case GFXFormat::EAC_RG11: return GL_UNSIGNED_BYTE;
    case GFXFormat::EAC_RG11SN: return GL_BYTE;
      
    case GFXFormat::PVRTC_RGB2: return GL_UNSIGNED_BYTE;
    case GFXFormat::PVRTC_RGBA2: return GL_UNSIGNED_BYTE;
    case GFXFormat::PVRTC_RGB4: return GL_UNSIGNED_BYTE;
    case GFXFormat::PVRTC_RGBA4: return GL_UNSIGNED_BYTE;
    case GFXFormat::PVRTC2_2BPP: return GL_UNSIGNED_BYTE;
    case GFXFormat::PVRTC2_4BPP: return GL_UNSIGNED_BYTE;
      
    default: {
      return GL_UNSIGNED_BYTE;
    }
  }
}

uint GLTypeSize(GLenum glType) {
  switch (glType) {
    case GL_BOOL: return 4;
    case GL_BOOL_VEC2: return 8;
    case GL_BOOL_VEC3: return 12;
    case GL_BOOL_VEC4: return 16;
    case GL_INT: return 4;
    case GL_INT_VEC2: return 8;
    case GL_INT_VEC3: return 12;
    case GL_INT_VEC4: return 16;
    case GL_UNSIGNED_INT: return 4;
    case GL_FLOAT: return 4;
    case GL_FLOAT_VEC2: return 8;
    case GL_FLOAT_VEC3: return 12;
    case GL_FLOAT_VEC4: return 16;
    case GL_FLOAT_MAT2: return 16;
    case GL_FLOAT_MAT3: return 36;
    case GL_FLOAT_MAT4: return 64;
    case GL_SAMPLER_2D: return 4;
    case GL_SAMPLER_3D_OES: return 4;
    case GL_SAMPLER_CUBE: return 4;
    case GL_SAMPLER_CUBE_MAP_ARRAY_OES: return 4;
    case GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_OES: return 4;
    case GL_INT_SAMPLER_CUBE_MAP_ARRAY_OES: return 4;
    case GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_OES: return 4;
    default: {
      CCASSERT(false, "Unsupported GLType, get type failed.");
      return 0;
    }
  }
}

uint GLComponentCount (GLenum glType) {
  switch (glType) {
    case GL_FLOAT_MAT2: return 2;
    case GL_FLOAT_MAT3: return 3;
    case GL_FLOAT_MAT4: return 4;
    default: {
      return 1;
    }
  }
}

const GLenum GLES3_WRAPS[] = {
  GL_REPEAT,
  GL_MIRRORED_REPEAT,
  GL_CLAMP_TO_EDGE,
  GL_CLAMP_TO_EDGE,
};

const GLenum GLES2_CMP_FUNCS[] = {
  GL_NEVER,
  GL_LESS,
  GL_EQUAL,
  GL_LEQUAL,
  GL_GREATER,
  GL_NOTEQUAL,
  GL_GEQUAL,
  GL_ALWAYS,
};

const GLenum GLES2_STENCIL_OPS[] = {
  GL_ZERO,
  GL_KEEP,
  GL_REPLACE,
  GL_INCR,
  GL_DECR,
  GL_INVERT,
  GL_INCR_WRAP,
  GL_DECR_WRAP,
};

const GLenum GLES2_BLEND_OPS[] = {
  GL_FUNC_ADD,
  GL_FUNC_SUBTRACT,
  GL_FUNC_REVERSE_SUBTRACT,
  GL_FUNC_ADD,
  GL_FUNC_ADD,
};

const GLenum GLES2_BLEND_FACTORS[] = {
  GL_ZERO,
  GL_ONE,
  GL_SRC_ALPHA,
  GL_DST_ALPHA,
  GL_ONE_MINUS_SRC_ALPHA,
  GL_ONE_MINUS_DST_ALPHA,
  GL_SRC_COLOR,
  GL_DST_COLOR,
  GL_ONE_MINUS_SRC_COLOR,
  GL_ONE_MINUS_DST_COLOR,
  GL_SRC_ALPHA_SATURATE,
  GL_CONSTANT_COLOR,
  GL_ONE_MINUS_CONSTANT_COLOR,
  GL_CONSTANT_ALPHA,
  GL_ONE_MINUS_CONSTANT_ALPHA,
};

void GLES2CmdFuncCreateBuffer(GLES2Device* device, GLES2GPUBuffer* gpuBuffer) {
  GLenum glUsage = (gpuBuffer->memUsage & GFXMemoryUsageBit::HOST ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
  
  if (gpuBuffer->usage & GFXBufferUsageBit::VERTEX) {
    gpuBuffer->glTarget = GL_ARRAY_BUFFER;
    glGenBuffers(1, &gpuBuffer->glBuffer);
    if (gpuBuffer->size) {
      if (device->useVAO()) {
        if (device->state_cache->glVAO) {
          glBindVertexArrayOES(0);
          device->state_cache->glVAO = 0;
        }
      }
      
      if (device->state_cache->glArrayBuffer != gpuBuffer->glBuffer) {
        glBindBuffer(GL_ARRAY_BUFFER, gpuBuffer->glBuffer);
      }
      
      glBufferData(GL_ARRAY_BUFFER, gpuBuffer->size, nullptr, glUsage);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      device->state_cache->glArrayBuffer = 0;
    }
  } else if (gpuBuffer->usage & GFXBufferUsageBit::INDEX) {
    gpuBuffer->glTarget = GL_ELEMENT_ARRAY_BUFFER;
    glGenBuffers(1, &gpuBuffer->glBuffer);
    if (gpuBuffer->size) {
      if (device->useVAO()) {
        if (device->state_cache->glVAO) {
          glBindVertexArrayOES(0);
          device->state_cache->glVAO = 0;
        }
      }
      
      if (device->state_cache->glElementArrayBuffer != gpuBuffer->glBuffer) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gpuBuffer->glBuffer);
      }
      
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, gpuBuffer->size, nullptr, glUsage);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      device->state_cache->glElementArrayBuffer = 0;
    }
  } else if (gpuBuffer->usage & GFXBufferUsageBit::UNIFORM) {
    gpuBuffer->buffer = (uint8_t*)CC_MALLOC(gpuBuffer->size);
    gpuBuffer->glTarget = GL_NONE;
  } else if (gpuBuffer->usage & GFXBufferUsageBit::INDIRECT){
    gpuBuffer->indirectBuff.draws.resize(gpuBuffer->count);
    gpuBuffer->glTarget = GL_NONE;
  } else if ((gpuBuffer->usage & GFXBufferUsageBit::TRANSFER_DST) ||
             (gpuBuffer->usage & GFXBufferUsageBit::TRANSFER_SRC)) {
      gpuBuffer->buffer = (uint8_t*)CC_MALLOC(gpuBuffer->size);
    gpuBuffer->glTarget = GL_NONE;
  } else {
      CCASSERT(false, "Unsupported GFXBufferType, create buffer failed.");
    gpuBuffer->glTarget = GL_NONE;
  }
}

void GLES2CmdFuncDestroyBuffer(GLES2Device* device, GLES2GPUBuffer* gpuBuffer)
{
    if (gpuBuffer->glBuffer)
    {
        glDeleteBuffers(1, &gpuBuffer->glBuffer);
        gpuBuffer->glBuffer = 0;
        if(gpuBuffer->glTarget == GL_ARRAY_BUFFER)
            device->state_cache->glArrayBuffer = 0;
        else if (gpuBuffer->glTarget == GL_ELEMENT_ARRAY_BUFFER)
            device->state_cache->glElementArrayBuffer = 0;

    }

    CC_SAFE_FREE(gpuBuffer->buffer);
}

void GLES2CmdFuncResizeBuffer(GLES2Device* device, GLES2GPUBuffer* gpuBuffer) {
  GLenum glUsage = (gpuBuffer->memUsage & GFXMemoryUsageBit::HOST ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
  
  if (gpuBuffer->usage & GFXBufferUsageBit::VERTEX) {
    gpuBuffer->glTarget = GL_ARRAY_BUFFER;
    if (gpuBuffer->size) {
      if (device->useVAO()) {
        if (device->state_cache->glVAO) {
          glBindVertexArrayOES(0);
          device->state_cache->glVAO = 0;
        }
      }
      
      if (device->state_cache->glArrayBuffer != gpuBuffer->glBuffer) {
        glBindBuffer(GL_ARRAY_BUFFER, gpuBuffer->glBuffer);
      }
      
      glBufferData(GL_ARRAY_BUFFER, gpuBuffer->size, nullptr, glUsage);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      device->state_cache->glArrayBuffer = 0;
    }
  } else if (gpuBuffer->usage & GFXBufferUsageBit::INDEX) {
    gpuBuffer->glTarget = GL_ELEMENT_ARRAY_BUFFER;
    if (gpuBuffer->size) {
      if (device->useVAO()) {
        if (device->state_cache->glVAO) {
          glBindVertexArrayOES(0);
          device->state_cache->glVAO = 0;
        }
      }
      
      if (device->state_cache->glElementArrayBuffer != gpuBuffer->glBuffer) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gpuBuffer->glBuffer);
      }
      
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, gpuBuffer->size, nullptr, glUsage);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      device->state_cache->glElementArrayBuffer = 0;
    }
  } else if (gpuBuffer->usage & GFXBufferUsageBit::UNIFORM) {
    if (gpuBuffer->buffer) {
      CC_FREE(gpuBuffer->buffer);
    }
    gpuBuffer->buffer = (uint8_t*)CC_MALLOC(gpuBuffer->size);
    gpuBuffer->glTarget = GL_NONE;
  } else if (gpuBuffer->usage & GFXBufferUsageBit::INDIRECT) {
    gpuBuffer->indirectBuff.draws.resize(gpuBuffer->count);
    gpuBuffer->glTarget = GL_NONE;
  } else if ((gpuBuffer->usage & GFXBufferUsageBit::TRANSFER_DST) ||
             (gpuBuffer->usage & GFXBufferUsageBit::TRANSFER_SRC)) {
      if (gpuBuffer->buffer) {
          CC_FREE(gpuBuffer->buffer);
      }
      gpuBuffer->buffer = (uint8_t*)CC_MALLOC(gpuBuffer->size);
    gpuBuffer->glTarget = GL_NONE;
  } else {
      CCASSERT(false, "Unsupported GFXBufferType, resize buffer failed.");
    gpuBuffer->glTarget = GL_NONE;
  }
}

void GLES2CmdFuncUpdateBuffer(GLES2Device* device, GLES2GPUBuffer* gpuBuffer, void* buffer, uint offset, uint size) {
  if (gpuBuffer->usage & GFXBufferUsageBit::UNIFORM) {
    memcpy(gpuBuffer->buffer + offset, buffer, size);
  } else if (gpuBuffer->usage & GFXBufferUsageBit::INDIRECT) {
    memcpy((uint8_t*)gpuBuffer->indirectBuff.draws.data() + offset, buffer, size);
  } else if (gpuBuffer->usage & GFXBufferUsageBit::TRANSFER_SRC) {
      memcpy(gpuBuffer->buffer + offset, buffer, size);
  } else {
    switch (gpuBuffer->glTarget) {
      case GL_ARRAY_BUFFER: {
        if (device->state_cache->glVAO) {
          glBindVertexArrayOES(0);
          device->state_cache->glVAO = 0;
        }
        if (device->state_cache->glArrayBuffer != gpuBuffer->glBuffer) {
          glBindBuffer(GL_ARRAY_BUFFER, gpuBuffer->glBuffer);
          device->state_cache->glArrayBuffer = gpuBuffer->glBuffer;
        }
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, buffer);
        break;
      }
      case GL_ELEMENT_ARRAY_BUFFER: {
        if (device->state_cache->glVAO) {
          glBindVertexArrayOES(0);
          device->state_cache->glVAO = 0;
        }
        if (device->state_cache->glElementArrayBuffer != gpuBuffer->glBuffer) {
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gpuBuffer->glBuffer);
          device->state_cache->glElementArrayBuffer = gpuBuffer->glBuffer;
        }
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, buffer);
        break;
      }
      default:
            CCASSERT(false, "Unsupported GFXBufferType, update buffer failed.");
        break;
    }
  }
}

void GLES2CmdFuncCreateTexture(GLES2Device* device, GLES2GPUTexture* gpuTexture) {
  gpuTexture->glInternelFmt = MapGLInternalFormat(gpuTexture->format);
  gpuTexture->glFormat = MapGLFormat(gpuTexture->format);
  gpuTexture->glType = GFXFormatToGLType(gpuTexture->format);
  
  switch (gpuTexture->viewType) {
    case GFXTextureViewType::TV2D: {
      gpuTexture->viewType = GFXTextureViewType::TV2D;
      gpuTexture->glTarget = GL_TEXTURE_2D;
      glGenTextures(1, &gpuTexture->glTexture);
      if (gpuTexture->size > 0) {
        GLuint& glTexture = device->state_cache->glTextures[device->state_cache->texUint];
        if (gpuTexture->glTexture != glTexture) {
          glBindTexture(GL_TEXTURE_2D, gpuTexture->glTexture);
          glTexture = gpuTexture->glTexture;
        }
        uint w = gpuTexture->width;
        uint h = gpuTexture->height;
        if (!GFX_FORMAT_INFOS[(int)gpuTexture->format].isCompressed) {
          for (uint i = 0; i < gpuTexture->mipLevel; ++i) {
            glTexImage2D(GL_TEXTURE_2D, i, gpuTexture->glInternelFmt, w, h, 0, gpuTexture->glFormat, gpuTexture->glType, nullptr);
            w = std::max(1U, w >> 1);
            h = std::max(1U, w >> 1);
          }
        } else {
          for (uint i = 0; i < gpuTexture->mipLevel; ++i) {
            uint img_size = GFXFormatSize(gpuTexture->format, w, h, 1);
            glCompressedTexImage2D(GL_TEXTURE_2D, i, gpuTexture->glInternelFmt, w, h, 0, img_size, nullptr);
            w = std::max(1U, w >> 1);
            h = std::max(1U, w >> 1);
          }
        }
      }
      break;
    }
    case GFXTextureViewType::CUBE: {
      gpuTexture->viewType = GFXTextureViewType::CUBE;
      gpuTexture->glTarget = GL_TEXTURE_CUBE_MAP;
      glGenTextures(1, &gpuTexture->glTexture);
      if (gpuTexture->size > 0) {
        GLuint& glTexture = device->state_cache->glTextures[device->state_cache->texUint];
        if (gpuTexture->glTexture != glTexture) {
          glBindTexture(GL_TEXTURE_CUBE_MAP, gpuTexture->glTexture);
          glTexture = gpuTexture->glTexture;
        }
        if (!GFX_FORMAT_INFOS[(int)gpuTexture->format].isCompressed) {
          for (uint f = 0; f < 6; ++f) {
            uint w = gpuTexture->width;
            uint h = gpuTexture->height;
            for (uint i = 0; i < gpuTexture->mipLevel; ++i) {
              glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + f, i, gpuTexture->glInternelFmt, w, h, 0, gpuTexture->glFormat, gpuTexture->glType, nullptr);
              w = std::max(1U, w >> 1);
              h = std::max(1U, w >> 1);
            }
          }
        } else {
          for (uint f = 0; f < 6; ++f) {
            uint w = gpuTexture->width;
            uint h = gpuTexture->height;
            for (uint i = 0; i < gpuTexture->mipLevel; ++i) {
              uint img_size = GFXFormatSize(gpuTexture->format, w, h, 1);
              glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + f, i, gpuTexture->glInternelFmt, w, h, 0, img_size, nullptr);
              w = std::max(1U, w >> 1);
              h = std::max(1U, w >> 1);
            }
          }
        }
      }
      break;
    }
    default:
      CCASSERT(false, "Unsupported GFXTextureType, create texture failed.");
      break;
  }
}

void GLES2CmdFuncDestroyTexture(GLES2Device* device, GLES2GPUTexture* gpuTexture) {
  if (gpuTexture->glTexture) {
    glDeleteTextures(1, &gpuTexture->glTexture);
    gpuTexture->glTexture = 0;
      device->state_cache->glTextures[device->state_cache->texUint] = 0;
  }
}

void GLES2CmdFuncResizeTexture(GLES2Device* device, GLES2GPUTexture* gpuTexture) {
  gpuTexture->glInternelFmt = MapGLInternalFormat(gpuTexture->format);
  gpuTexture->glFormat = MapGLFormat(gpuTexture->format);
  gpuTexture->glType = GFXFormatToGLType(gpuTexture->format);
  
  switch (gpuTexture->viewType) {
    case GFXTextureViewType::TV2D: {
      gpuTexture->viewType = GFXTextureViewType::TV2D;
      gpuTexture->glTarget = GL_TEXTURE_2D;
      if (gpuTexture->size > 0) {
        GLuint glTexture = device->state_cache->glTextures[device->state_cache->texUint];
        if (gpuTexture->glTexture != glTexture) {
          glBindTexture(GL_TEXTURE_2D, glTexture);
          gpuTexture->glTexture = glTexture;
        }
        uint w = gpuTexture->width;
        uint h = gpuTexture->height;
        if (!GFX_FORMAT_INFOS[(int)gpuTexture->format].isCompressed) {
          for (uint i = 0; i < gpuTexture->mipLevel; ++i) {
            glTexImage2D(GL_TEXTURE_2D, i, gpuTexture->glInternelFmt, w, h, 0, gpuTexture->glFormat, gpuTexture->glType, nullptr);
            w = std::max(1U, w >> 1);
            h = std::max(1U, h >> 1);
          }
        } else {
          for (uint i = 0; i < gpuTexture->mipLevel; ++i) {
            uint img_size = GFXFormatSize(gpuTexture->format, w, h, 1);
            glCompressedTexImage2D(GL_TEXTURE_2D, i, gpuTexture->glInternelFmt, w, h, 0, img_size, nullptr);
            w = std::max(1U, w >> 1);
            h = std::max(1U, h >> 1);
          }
        }
      }
      break;
    }
    case GFXTextureViewType::CUBE: {
      gpuTexture->viewType = GFXTextureViewType::CUBE;
      gpuTexture->glTarget = GL_TEXTURE_CUBE_MAP;
      if (gpuTexture->size > 0) {
        GLuint glTexture = device->state_cache->glTextures[device->state_cache->texUint];
        if (gpuTexture->glTexture != glTexture) {
          glBindTexture(GL_TEXTURE_CUBE_MAP, glTexture);
          gpuTexture->glTexture = glTexture;
        }
        if (!GFX_FORMAT_INFOS[(int)gpuTexture->format].isCompressed) {
          for (uint f = 0; f < 6; ++f) {
            uint w = gpuTexture->width;
            uint h = gpuTexture->height;
            for (uint i = 0; i < gpuTexture->mipLevel; ++i) {
              glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + f, i, gpuTexture->glInternelFmt, w, h, 0, gpuTexture->glFormat, gpuTexture->glType, nullptr);
              w = std::max(1U, w >> 1);
              h = std::max(1U, h >> 1);
            }
          }
        } else {
          for (uint f = 0; f < 6; ++f) {
            uint w = gpuTexture->width;
            uint h = gpuTexture->height;
            for (uint i = 0; i < gpuTexture->mipLevel; ++i) {
              uint img_size = GFXFormatSize(gpuTexture->format, w, h, 1);
              glCompressedTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + f, i, gpuTexture->glInternelFmt, w, h, 0, img_size, nullptr);
              w = std::max(1U, w >> 1);
              h = std::max(1U, h >> 1);
            }
          }
        }
      }
      break;
    }
    default:
      CCASSERT(false, "Unsupported GFXTextureType, resize texture failed.");
      break;
  }
}

void GLES2CmdFuncCreateSampler(GLES2Device* device, GLES2GPUSampler* gpuSampler) {
  if (gpuSampler->minFilter == GFXFilter::LINEAR || gpuSampler->minFilter == GFXFilter::ANISOTROPIC) {
    if (gpuSampler->mipFilter == GFXFilter::LINEAR || gpuSampler->mipFilter == GFXFilter::ANISOTROPIC) {
      gpuSampler->glMinFilter = GL_LINEAR_MIPMAP_LINEAR;
    } else if (gpuSampler->mipFilter == GFXFilter::POINT) {
      gpuSampler->glMinFilter = GL_LINEAR_MIPMAP_NEAREST;
    } else {
      gpuSampler->glMinFilter = GL_LINEAR;
    }
  } else {
    if (gpuSampler->mipFilter == GFXFilter::LINEAR || gpuSampler->mipFilter == GFXFilter::ANISOTROPIC) {
      gpuSampler->glMinFilter = GL_NEAREST_MIPMAP_LINEAR;
    } else if (gpuSampler->mipFilter == GFXFilter::POINT) {
      gpuSampler->glMinFilter = GL_NEAREST_MIPMAP_NEAREST;
    } else {
      gpuSampler->glMinFilter = GL_NEAREST;
    }
  }
  
  if (gpuSampler->magFilter == GFXFilter::LINEAR || gpuSampler->magFilter == GFXFilter::ANISOTROPIC) {
    gpuSampler->glMagFilter = GL_LINEAR;
  } else {
    gpuSampler->glMagFilter = GL_NEAREST;
  }
  
  gpuSampler->glWrapS = GLES3_WRAPS[(int)gpuSampler->addressU];
  gpuSampler->glWrapT = GLES3_WRAPS[(int)gpuSampler->addressV];
  gpuSampler->glWrapR = GLES3_WRAPS[(int)gpuSampler->addressW];
}

void GLES2CmdFuncDestroySampler(GLES2Device* device, GLES2GPUSampler* gpuSampler) {
}

void GLES2CmdFuncCreateShader(GLES2Device* device, GLES2GPUShader* gpuShader) {
  GLenum gl_shader_type = 0;
  String shader_type_str;
  GLint status;
  
  for (size_t i = 0; i < gpuShader->gpuStages.size(); ++i) {
    GLES2GPUShaderStage& gpu_stage = gpuShader->gpuStages[i];
    
    switch (gpu_stage.type) {
      case GFXShaderType::VERTEX: {
        gl_shader_type = GL_VERTEX_SHADER;
        shader_type_str = "Vertex Shader";
        break;
      }
      case GFXShaderType::FRAGMENT: {
        gl_shader_type = GL_FRAGMENT_SHADER;
        shader_type_str = "Fragment Shader";
        break;
      }
      default: {
        CCASSERT(false, "Unsupported GFXShaderType");
        return;
      }
    }
    
    gpu_stage.glShader = glCreateShader(gl_shader_type);
    const char* shader_src = gpu_stage.source.c_str();
    glShaderSource(gpu_stage.glShader, 1, (const GLchar**)&shader_src, nullptr);
    glCompileShader(gpu_stage.glShader);
    
    glGetShaderiv(gpu_stage.glShader, GL_COMPILE_STATUS, &status);
    if (status != 1) {
      GLint log_size = 0;
      glGetShaderiv(gpu_stage.glShader, GL_INFO_LOG_LENGTH, &log_size);
      
      ++log_size;
      GLchar* logs = (GLchar*)CC_MALLOC(log_size);
      glGetShaderInfoLog(gpu_stage.glShader, log_size, nullptr, logs);
      
      CC_LOG_ERROR("%s in %s compilation failed.", shader_type_str.c_str(), gpuShader->name.c_str());
      CC_LOG_ERROR("Shader source:%s", gpu_stage.source.c_str());
      CC_LOG_ERROR(logs);
      CC_FREE(logs);
      glDeleteShader(gpu_stage.glShader);
      gpu_stage.glShader = 0;
      return;
    }
  }
  
  gpuShader->glProgram = glCreateProgram();
  
  // link program
  for (size_t i = 0; i < gpuShader->gpuStages.size(); ++i) {
    GLES2GPUShaderStage& gpu_stage = gpuShader->gpuStages[i];
    glAttachShader(gpuShader->glProgram, gpu_stage.glShader);
  }
  
  glLinkProgram(gpuShader->glProgram);

  // detach & delete immediately
  for (size_t i = 0; i < gpuShader->gpuStages.size(); ++i) {
    GLES2GPUShaderStage& gpu_stage = gpuShader->gpuStages[i];
    if (gpu_stage.glShader) {
      glDetachShader(gpuShader->glProgram, gpu_stage.glShader);
      glDeleteShader(gpu_stage.glShader);
      gpu_stage.glShader = 0;
    }
  }

  glGetProgramiv(gpuShader->glProgram, GL_LINK_STATUS, &status);
  if (status != 1) {
    CC_LOG_ERROR("Failed to link Shader [%s].", gpuShader->name.c_str());
    GLint log_size = 0;
    glGetProgramiv(gpuShader->glProgram, GL_INFO_LOG_LENGTH, &log_size);
    if (log_size) {
      ++log_size;
      GLchar* logs = (GLchar*)CC_MALLOC(log_size);
      glGetProgramInfoLog(gpuShader->glProgram, log_size, nullptr, logs);
      
      CC_LOG_ERROR("Failed to link shader '%s'.", gpuShader->name.c_str());
      CC_LOG_ERROR(logs);
      CC_FREE(logs);
      return;
    }
  }
  
  CC_LOG_INFO("Shader '%s' compilation successed.", gpuShader->name.c_str());
  
  GLint attr_max_length = 0;
  GLint attr_count = 0;
  glGetProgramiv(gpuShader->glProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attr_max_length);
  glGetProgramiv(gpuShader->glProgram, GL_ACTIVE_ATTRIBUTES, &attr_count);
  
  GLchar gl_name[256];
  GLsizei gl_length;
  GLsizei gl_size;
  GLenum glType;
  
  gpuShader->glInputs.resize(attr_count);
  for (GLint i = 0; i < attr_count; ++i) {
    GLES2GPUInput& gpu_input = gpuShader->glInputs[i];
    
    memset(gl_name, 0, sizeof(gl_name));
    glGetActiveAttrib(gpuShader->glProgram, i, attr_max_length, &gl_length, &gl_size, &glType, gl_name);
    char* offset = strchr(gl_name, '[');
    if (offset) {
      gl_name[offset - gl_name] = '\0';
    }
    
    gpu_input.glLoc = glGetAttribLocation(gpuShader->glProgram, gl_name);
    gpu_input.binding = gpu_input.glLoc;
    gpu_input.name = gl_name;
    gpu_input.type = MapGFXType(glType);
    gpu_input.stride = GLTypeSize(glType);
    gpu_input.count = gl_size;
    gpu_input.size = gpu_input.stride * gpu_input.count;
    gpu_input.glType = glType;
  }
  
  // create uniform blocks
  if (gpuShader->blocks.size()) {

    gpuShader->glBlocks.resize(gpuShader->blocks.size());

    for (size_t i = 0; i < gpuShader->glBlocks.size(); ++i) {
      GLES2GPUUniformBlock& gpu_block = gpuShader->glBlocks[i];
      GFXUniformBlock& block = gpuShader->blocks[i];

      gpu_block.name = block.name;
      gpu_block.binding = block.binding;
      gpu_block.glUniforms.resize(block.uniforms.size());

      for (size_t j = 0; j < gpu_block.glUniforms.size(); ++j) {
        GLES2GPUUniform& gpu_uniform = gpu_block.glUniforms[j];
        GFXUniform& uniform = block.uniforms[j];

        gpu_uniform.binding = GFX_INVALID_BINDING;
        gpu_uniform.name = uniform.name;
        gpu_uniform.type = uniform.type;
        gpu_uniform.stride = GFX_TYPE_SIZES[(int)uniform.type];
        gpu_uniform.count = uniform.count;
        gpu_uniform.size = gpu_uniform.stride * gpu_uniform.count;
        gpu_uniform.offset = gpu_block.size;
        gpu_uniform.glType = MapGLType(gpu_uniform.type);
        gpu_uniform.glLoc = -1;
        gpu_uniform.buff = nullptr;

        gpu_block.size += gpu_uniform.size;
      }
    }
  } // if

  // create uniform samplers
  if (gpuShader->samplers.size()) {
    gpuShader->glSamplers.resize(gpuShader->samplers.size());

    for (size_t i = 0; i < gpuShader->glSamplers.size(); ++i) {
      GFXUniformSampler& sampler = gpuShader->samplers[i];
      GLES2GPUUniformSampler& gpuSampler = gpuShader->glSamplers[i];
      gpuSampler.binding = sampler.binding;
      gpuSampler.name = sampler.name;
      gpuSampler.type = sampler.type;
      gpuSampler.glType = MapGLType(gpuSampler.type);
      gpuSampler.glLoc = -1;
    }
  }

  // parse glUniforms
  GLint glActiveUniforms;
  glGetProgramiv(gpuShader->glProgram, GL_ACTIVE_UNIFORMS, &glActiveUniforms);

  GLint unit_idx = 0;

  GLES2GPUUniformSamplerList active_gpu_samplers;

  for (GLint i = 0; i < glActiveUniforms; ++i) {
    memset(gl_name, 0, sizeof(gl_name));
    glGetActiveUniform(gpuShader->glProgram, i, 255, &gl_length, &gl_size, &glType, gl_name);
    char* u_offset = strchr(gl_name, '[');
    if (u_offset) {
      gl_name[u_offset - gl_name] = '\0';
    }
    String u_name = gl_name;

    bool is_sampler = (glType == GL_SAMPLER_2D) ||
      (glType == GL_SAMPLER_3D_OES) ||
      (glType == GL_SAMPLER_CUBE) ||
      (glType == GL_SAMPLER_CUBE_MAP_ARRAY_OES) ||
      (glType == GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_OES) ||
      (glType == GL_INT_SAMPLER_CUBE_MAP_ARRAY_OES) ||
      (glType == GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_OES);
    if (is_sampler) {
      for (size_t s = 0; s < gpuShader->glSamplers.size(); ++s) {
        GLES2GPUUniformSampler& gpuSampler = gpuShader->glSamplers[s];
        if (gpuSampler.name == u_name) {
          gpuSampler.units.resize(gl_size);
          for (GLsizei u = 0; u < gl_size; ++u) {
            gpuSampler.units[u] = unit_idx + u;
          }

          gpuSampler.glLoc = glGetUniformLocation(gpuShader->glProgram, gl_name);
          unit_idx += gl_size;

          active_gpu_samplers.push_back(gpuSampler);
          break;
        }
      }
    } else {
      for (size_t b = 0; b < gpuShader->glBlocks.size(); ++b) {
        GLES2GPUUniformBlock& gpu_block = gpuShader->glBlocks[b];
        for (size_t u = 0; u < gpu_block.glUniforms.size(); ++u) {
          if (gpu_block.glUniforms[u].name == u_name) {
            GLES2GPUUniform& gpu_uniform = gpu_block.glUniforms[u];
            gpu_uniform.glLoc = glGetUniformLocation(gpuShader->glProgram, gl_name);
            gpu_uniform.buff = (uint8_t*)CC_MALLOC(gpu_uniform.size);

            gpu_block.glActiveUniforms.emplace_back(gpu_uniform);
            break;
          }
        }
      }
    }
  } // for

  if (active_gpu_samplers.size()) {
    if (device->state_cache->glProgram != gpuShader->glProgram) {
      glUseProgram(gpuShader->glProgram);
      device->state_cache->glProgram = gpuShader->glProgram;
    }

    for (size_t i = 0; i < active_gpu_samplers.size(); ++i) {
      GLES2GPUUniformSampler& gpuSampler = active_gpu_samplers[i];
      glUniform1iv(gpuSampler.glLoc, (GLsizei)gpuSampler.units.size(), gpuSampler.units.data());
    }
  }
}

void GLES2CmdFuncDestroyShader(GLES2Device* device, GLES2GPUShader* gpuShader) {
  if (gpuShader->glProgram) {
    glDeleteProgram(gpuShader->glProgram);
    gpuShader->glProgram = 0;
  }
}

void GLES2CmdFuncCreateInputAssembler(GLES2Device* device, GLES2GPUInputAssembler* gpu_ia) {
  
  if (gpu_ia->gpuIndexBuffer) {
    switch (gpu_ia->gpuIndexBuffer->stride) {
      case 1: gpu_ia->glIndexType = GL_UNSIGNED_BYTE; break;
      case 2: gpu_ia->glIndexType = GL_UNSIGNED_SHORT; break;
      case 4: gpu_ia->glIndexType = GL_UNSIGNED_INT; break;
      default: {
        CC_LOG_ERROR("Illegal index buffer stride.");
      }
    }
  }
  
  uint stream_offsets[GFX_MAX_VERTEX_ATTRIBUTES] = {0};
  
  gpu_ia->glAttribs.resize(gpu_ia->attributes.size());
  for (size_t i = 0; i < gpu_ia->glAttribs.size(); ++i) {
    GLES2GPUAttribute& gpu_attrib = gpu_ia->glAttribs[i];
    const GFXAttribute& attrib = gpu_ia->attributes[i];
    
    GLES2GPUBuffer* gpu_vb = (GLES2GPUBuffer*)gpu_ia->gpuVertexBuffers[attrib.stream];
    
    gpu_attrib.name = attrib.name;
    gpu_attrib.glType = GFXFormatToGLType(attrib.format);
    gpu_attrib.size = GFX_FORMAT_INFOS[(int)attrib.format].size;
    gpu_attrib.count = GFX_FORMAT_INFOS[(int)attrib.format].count;
    gpu_attrib.componentCount = GLComponentCount(gpu_attrib.glType);
    gpu_attrib.isNormalized = attrib.isNormalized;
    gpu_attrib.isInstanced = attrib.isInstanced;
    gpu_attrib.offset = stream_offsets[attrib.stream];
    
    if (gpu_vb) {
      gpu_attrib.glBuffer = gpu_vb->glBuffer;
      gpu_attrib.stride = gpu_vb->stride;
    }
      stream_offsets[attrib.stream] += gpu_attrib.size;
  }
}

void GLES2CmdFuncDestroyInputAssembler(GLES2Device* device, GLES2GPUInputAssembler* gpu_ia) {
  for (auto it = gpu_ia->glVAOs.begin(); it != gpu_ia->glVAOs.end(); ++it) {
    glDeleteVertexArraysOES(1, &it->second);
  }
  gpu_ia->glVAOs.clear();
    device->state_cache->glVAO = 0;
}

void GLES2CmdFuncCreateFramebuffer(GLES2Device* device, GLES2GPUFramebuffer* gpu_fbo) {
  if (gpu_fbo->isOffscreen) {
    glGenFramebuffers(1, &gpu_fbo->glFramebuffer);
    if (device->state_cache->glFramebuffer != gpu_fbo->glFramebuffer) {
      glBindFramebuffer(GL_FRAMEBUFFER, gpu_fbo->glFramebuffer);
      device->state_cache->glFramebuffer = gpu_fbo->glFramebuffer;
    }

    GLenum attachments[GFX_MAX_ATTACHMENTS] = {0};
    uint attachment_count = 0;
    
    for (size_t i = 0; i < gpu_fbo->gpuColorViews.size(); ++i) {
      GLES2GPUTextureView* gpu_color_view = gpu_fbo->gpuColorViews[i];
      if (gpu_color_view && gpu_color_view->gpuTexture) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, (GLenum)(GL_COLOR_ATTACHMENT0 + i), gpu_color_view->gpuTexture->glTarget, gpu_color_view->gpuTexture->glTexture, gpu_color_view->baseLevel);
        
        attachments[attachment_count++] = (GLenum)(GL_COLOR_ATTACHMENT0 + i);
      }
    }
    
    if (gpu_fbo->gpuDepthStencilView) {
      GLES2GPUTextureView* gpu_dsv = gpu_fbo->gpuDepthStencilView;
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, gpu_dsv->gpuTexture->glTarget, gpu_dsv->gpuTexture->glTexture, gpu_dsv->baseLevel);
      
      if (GFX_FORMAT_INFOS[(int)gpu_dsv->format].hasStencil) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, gpu_dsv->gpuTexture->glTarget, gpu_dsv->gpuTexture->glTexture, gpu_dsv->baseLevel);
      }
    }
    
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
      switch (status) {
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: {
          CC_LOG_ERROR("glCheckFramebufferStatus() - FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
          break;
        }
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: {
          CC_LOG_ERROR("glCheckFramebufferStatus() - FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
          break;
        }
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS: {
          CC_LOG_ERROR("glCheckFramebufferStatus() - FRAMEBUFFER_INCOMPLETE_DIMENSIONS");
          break;
        }
        case GL_FRAMEBUFFER_UNSUPPORTED: {
          CC_LOG_ERROR("glCheckFramebufferStatus() - FRAMEBUFFER_UNSUPPORTED");
          break;
        }
        default:;
      }
    }
  }
}

void GLES2CmdFuncDestroyFramebuffer(GLES2Device* device, GLES2GPUFramebuffer* gpu_fbo) {
  if (gpu_fbo->glFramebuffer) {
    glDeleteFramebuffers(1, &gpu_fbo->glFramebuffer);
    gpu_fbo->glFramebuffer = 0;
      device->state_cache->glFramebuffer = 0;
  }
}

void GLES2CmdFuncExecuteCmds(GLES2Device* device, GLES2CmdPackage* cmd_package) {
  static uint cmd_indices[(int)GFXCmdType::COUNT] = {0};
  static GLenum gl_attachments[GFX_MAX_ATTACHMENTS] = {0};
  
  memset(cmd_indices, 0, sizeof(cmd_indices));
  
  GLES2StateCache* cache = device->state_cache;
  GLES2GPURenderPass* gpuRenderPass = nullptr;
  bool is_shader_changed = false;
  GLES2GPUPipelineState* gpu_pso = nullptr;
  GLenum glPrimitive = 0;
  GLES2GPUInputAssembler* gpu_ia = nullptr;
  GLES2CmdBeginRenderPass* cmd_begin_render_pass = nullptr;
  GLenum glWrapS;
  GLenum glWrapT;
  GLenum glMinFilter;
  
  for (uint i = 0; i < cmd_package->cmd_types.size(); ++i) {
    GFXCmdType cmd_type = cmd_package->cmd_types[i];
    uint& cmd_idx = cmd_indices[(int)cmd_type];
    
    switch (cmd_type) {
      case GFXCmdType::BEGIN_RENDER_PASS: {
        GLES2CmdBeginRenderPass* cmd = cmd_package->begin_render_pass_cmds[cmd_idx];
        cmd_begin_render_pass = cmd;
        if (cmd->gpu_fbo) {
          if (cache->glFramebuffer != cmd->gpu_fbo->glFramebuffer) {
            glBindFramebuffer(GL_FRAMEBUFFER, cmd->gpu_fbo->glFramebuffer);
            cache->glFramebuffer = cmd->gpu_fbo->glFramebuffer;
          }
          
          if (cache->viewport.left != cmd->render_area.x ||
              cache->viewport.top != cmd->render_area.y ||
              cache->viewport.width != cmd->render_area.width ||
              cache->viewport.height != cmd->render_area.height) {
            glViewport(cmd->render_area.x, cmd->render_area.y, cmd->render_area.width, cmd->render_area.height);
            cache->viewport.left = cmd->render_area.x;
            cache->viewport.top = cmd->render_area.y;
            cache->viewport.width = cmd->render_area.width;
            cache->viewport.height = cmd->render_area.height;
          }
          
          if (cache->scissor.x != cmd->render_area.x ||
              cache->scissor.y != cmd->render_area.y ||
              cache->scissor.width != cmd->render_area.width ||
              cache->scissor.height != cmd->render_area.height) {
            glScissor(cmd->render_area.x, cmd->render_area.y, cmd->render_area.width, cmd->render_area.height);
            cache->scissor.x = cmd->render_area.x;
            cache->scissor.y = cmd->render_area.y;
            cache->scissor.width = cmd->render_area.width;
            cache->scissor.height = cmd->render_area.height;
          }
          
          GLbitfield gl_clears = 0;
          uint num_attachments = 0;
          
          gpuRenderPass = cmd->gpu_fbo->gpuRenderPass;
          for (uint j = 0; j < cmd->num_clear_colors; ++j) {
            const GFXColorAttachment& color_attachment = gpuRenderPass->colorAttachments[j];
            if (color_attachment.format != GFXFormat::UNKNOWN) {
              switch (color_attachment.loadOp) {
                case GFXLoadOp::LOAD: break; // GL default behaviour
                case GFXLoadOp::CLEAR: {
                  if (cmd->clear_flags & GFXClearFlagBit::COLOR) {
                    if (cache->bs.targets[0].blendColorMask != GFXColorMask::ALL) {
                      glColorMask(true, true, true, true);
                    }
                    
                    if (!cmd->gpu_fbo->isOffscreen) {
                      const GFXColor& color = cmd->clear_colors[j];
                      glClearColor(color.r, color.g, color.b, color.a);
                      gl_clears |= GL_COLOR_BUFFER_BIT;
                    }
                  }
                  break;
                }
                case GFXLoadOp::DISCARD: {
                  // invalidate fbo
                  gl_attachments[num_attachments++] = (cmd->gpu_fbo->isOffscreen ? GL_COLOR_ATTACHMENT0 + j : GL_COLOR_EXT);
                  break;
                }
                default:;
              }
            }
          } // for
          
          if (gpuRenderPass->depthStencilAttachment.format != GFXFormat::UNKNOWN) {
            bool hasDepth = GFX_FORMAT_INFOS[(int)gpuRenderPass->depthStencilAttachment.format].hasDepth;
            if (hasDepth) {
              switch (gpuRenderPass->depthStencilAttachment.depthLoadOp) {
                case GFXLoadOp::LOAD: break; // GL default behaviour
                case GFXLoadOp::CLEAR: {
                    glDepthMask(true);
                    cache->dss.depthWrite = true;
                  glClearDepthf(cmd->clear_depth);
                  gl_clears |= GL_DEPTH_BUFFER_BIT;
                  break;
                }
                case GFXLoadOp::DISCARD: {
                  // invalidate fbo
                  gl_attachments[num_attachments++] = (cmd->gpu_fbo->isOffscreen ? GL_DEPTH_ATTACHMENT : GL_DEPTH_EXT);
                  break;
                }
                default:;
              }
            } // if (hasDepth)
            bool has_stencils = GFX_FORMAT_INFOS[(int)gpuRenderPass->depthStencilAttachment.format].hasStencil;
            if (has_stencils) {
              switch (gpuRenderPass->depthStencilAttachment.depthLoadOp) {
                case GFXLoadOp::LOAD: break; // GL default behaviour
                case GFXLoadOp::CLEAR: {
                  if (!cache->dss.stencilWriteMaskFront) {
                    glStencilMaskSeparate(GL_FRONT, 0xffffffff);
                  }
                  if (!cache->dss.stencilWriteMaskBack) {
                    glStencilMaskSeparate(GL_BACK, 0xffffffff);
                  }
                  glClearStencil(cmd->clear_stencil);
                  gl_clears |= GL_STENCIL_BUFFER_BIT;
                  break;
                }
                case GFXLoadOp::DISCARD: {
                  // invalidate fbo
                  gl_attachments[num_attachments++] = (cmd->gpu_fbo->isOffscreen ? GL_STENCIL_ATTACHMENT : GL_STENCIL_EXT);
                  break;
                }
                default:;
              }
            } // if (has_stencils)
          } // if
          
          if (num_attachments && device->useDiscardFramebuffer()) {
            glDiscardFramebufferEXT(GL_FRAMEBUFFER, num_attachments, gl_attachments);
          }
          
          if (gl_clears) {
            glClear(gl_clears);
          }
          
          // restore states
          if (gl_clears & GL_COLOR_BUFFER_BIT) {
            GFXColorMask color_mask = cache->bs.targets[0].blendColorMask;
            if (color_mask != GFXColorMask::ALL) {
              glColorMask((GLboolean)(color_mask & GFXColorMask::R),
                (GLboolean)(color_mask & GFXColorMask::G),
                (GLboolean)(color_mask & GFXColorMask::B),
                (GLboolean)(color_mask & GFXColorMask::A));
            }
          }
          
          if ((gl_clears & GL_COLOR_BUFFER_BIT) && !cache->dss.depthWrite) {
            glDepthMask(false);
          }
          
          if (gl_clears & GL_STENCIL_BUFFER_BIT) {
            if (!cache->dss.stencilWriteMaskFront) {
              glStencilMaskSeparate(GL_FRONT, 0);
            }
            if (!cache->dss.stencilWriteMaskBack) {
              glStencilMaskSeparate(GL_BACK, 0);
            }
          }
        }
        break;
      }
      case GFXCmdType::END_RENDER_PASS: {
        GLES2CmdBeginRenderPass* cmd = cmd_begin_render_pass;
        uint num_attachments = 0;
        for (uint j = 0; j < cmd->num_clear_colors; ++j) {
          const GFXColorAttachment& color_attachment = gpuRenderPass->colorAttachments[j];
          if (color_attachment.format != GFXFormat::UNKNOWN) {
            switch (color_attachment.loadOp) {
              case GFXLoadOp::LOAD: break; // GL default behaviour
              case GFXLoadOp::CLEAR: break;
              case GFXLoadOp::DISCARD: {
                // invalidate fbo
                gl_attachments[num_attachments++] = (cmd->gpu_fbo->isOffscreen ? GL_COLOR_ATTACHMENT0 + j : GL_COLOR_EXT);
                break;
              }
              default:;
            }
          }
        } // for
        
        if (gpuRenderPass->depthStencilAttachment.format != GFXFormat::UNKNOWN) {
          bool hasDepth = GFX_FORMAT_INFOS[(int)gpuRenderPass->depthStencilAttachment.format].hasDepth;
          if (hasDepth) {
            switch (gpuRenderPass->depthStencilAttachment.depthLoadOp) {
              case GFXLoadOp::LOAD: break; // GL default behaviour
              case GFXLoadOp::CLEAR: break;
              case GFXLoadOp::DISCARD: {
                // invalidate fbo
                gl_attachments[num_attachments++] = (cmd->gpu_fbo->isOffscreen ? GL_DEPTH_ATTACHMENT : GL_DEPTH_EXT);
                break;
              }
              default:;
            }
          } // if (hasDepth)
          bool has_stencils = GFX_FORMAT_INFOS[(int)gpuRenderPass->depthStencilAttachment.format].hasStencil;
          if (has_stencils) {
            switch (gpuRenderPass->depthStencilAttachment.depthLoadOp) {
              case GFXLoadOp::LOAD: break; // GL default behaviour
              case GFXLoadOp::CLEAR: break;
              case GFXLoadOp::DISCARD: {
                // invalidate fbo
                gl_attachments[num_attachments++] = (cmd->gpu_fbo->isOffscreen ? GL_STENCIL_ATTACHMENT : GL_STENCIL_EXT);
                break;
              }
              default:;
            }
          } // if (has_stencils)
        } // if
        
        if (num_attachments && device->useDiscardFramebuffer()) {
          glDiscardFramebufferEXT(GL_FRAMEBUFFER, num_attachments, gl_attachments);
        }
        break;
      }
      case GFXCmdType::BIND_STATES: {
        GLES2CmdBindStates* cmd = cmd_package->bind_states_cmds[cmd_idx];
        is_shader_changed = false;
          
          if (cache->viewport.left != cmd->viewport.left ||
              cache->viewport.top != cmd->viewport.top ||
              cache->viewport.width != cmd->viewport.width ||
              cache->viewport.height != cmd->viewport.height) {
              glViewport(cmd->viewport.left, cmd->viewport.top, cmd->viewport.width, cmd->viewport.height);
              cache->viewport.left = cmd->viewport.left;
              cache->viewport.top = cmd->viewport.top;
              cache->viewport.width = cmd->viewport.width;
              cache->viewport.height = cmd->viewport.height;
          }
          
        if (cmd->gpu_pso) {
          gpu_pso = cmd->gpu_pso;
          glPrimitive = gpu_pso->glPrimitive;
          
          if (gpu_pso->gpuShader) {
            if (cache->glProgram != gpu_pso->gpuShader->glProgram) {
              glUseProgram(gpu_pso->gpuShader->glProgram);
              cache->glProgram = gpu_pso->gpuShader->glProgram;
              is_shader_changed = true;
            }
          }
          
          // bind rasterizer state
          if (cache->rs.cullMode != gpu_pso->rs.cullMode) {
            switch (gpu_pso->rs.cullMode) {
              case GFXCullMode::NONE: {
                if (cache->isCullFaceEnabled) {
                  glDisable(GL_CULL_FACE);
                  cache->isCullFaceEnabled = false;
                }
              } break;
              case GFXCullMode::FRONT: {
                if (!cache->isCullFaceEnabled) {
                  glEnable(GL_CULL_FACE);
                  cache->isCullFaceEnabled = true;
                }
                glCullFace(GL_FRONT);
              } break;
              case GFXCullMode::BACK: {
                if (!cache->isCullFaceEnabled) {
                  glEnable(GL_CULL_FACE);
                  cache->isCullFaceEnabled = true;
                }
                glCullFace(GL_BACK);
              } break;
              default:
                break;
            }
            cache->rs.cullMode = gpu_pso->rs.cullMode;
          }
        }
        if (cache->rs.isFrontFaceCCW != gpu_pso->rs.isFrontFaceCCW) {
          glFrontFace(gpu_pso->rs.isFrontFaceCCW? GL_CCW : GL_CW);
          cache->rs.isFrontFaceCCW = gpu_pso->rs.isFrontFaceCCW;
        }
        if ((cache->rs.depthBias != gpu_pso->rs.depthBias) ||
            (cache->rs.depthBiasSlop != gpu_pso->rs.depthBiasSlop)){
          glPolygonOffset(cache->rs.depthBias, cache->rs.depthBiasSlop);
          cache->rs.depthBiasSlop = gpu_pso->rs.depthBiasSlop;
        }
        if (cache->rs.lineWidth != gpu_pso->rs.lineWidth) {
          glLineWidth(gpu_pso->rs.lineWidth);
          cache->rs.lineWidth = gpu_pso->rs.lineWidth;
        }
        
        // bind depth-stencil state
        if (cache->dss.depthTest != gpu_pso->dss.depthTest) {
          if (gpu_pso->dss.depthTest) {
              glEnable(GL_DEPTH_TEST);
          } else {
              glDisable(GL_DEPTH_TEST);
          }
          cache->dss.depthTest = gpu_pso->dss.depthTest;
        }
        if (cache->dss.depthWrite != gpu_pso->dss.depthWrite) {
          glDepthMask(gpu_pso->dss.depthWrite);
          cache->dss.depthWrite = gpu_pso->dss.depthWrite;
        }
        if (cache->dss.depthFunc != gpu_pso->dss.depthFunc) {
          glDepthFunc(GLES2_CMP_FUNCS[(int)gpu_pso->dss.depthFunc]);
          cache->dss.depthFunc = gpu_pso->dss.depthFunc;
        }
        
        // bind depth-stencil state - front
          if (gpu_pso->dss.stencilTestFront || gpu_pso->dss.stencilTestBack) {
            if (!cache->isStencilTestEnabled) {
              glEnable(GL_STENCIL_TEST);
              cache->isStencilTestEnabled = true;
            }
          } else {
            if (cache->isStencilTestEnabled) {
              glDisable(GL_STENCIL_TEST);
              cache->isStencilTestEnabled = false;
            }
          }
        if (cache->dss.stencilFuncFront != gpu_pso->dss.stencilFuncFront ||
            cache->dss.stencilRefFront != gpu_pso->dss.stencilRefFront ||
            cache->dss.stencilReadMaskFront != gpu_pso->dss.stencilReadMaskFront) {
          glStencilFuncSeparate(GL_FRONT,
                                GLES2_CMP_FUNCS[(int)gpu_pso->dss.stencilFuncFront],
                                gpu_pso->dss.stencilRefFront,
                                gpu_pso->dss.stencilReadMaskFront);
        }
        if (cache->dss.stencilFailOpFront != gpu_pso->dss.stencilFailOpFront ||
            cache->dss.stencilZFailOpFront != gpu_pso->dss.stencilZFailOpFront ||
            cache->dss.stencilPassOpFront != gpu_pso->dss.stencilPassOpFront) {
          glStencilOpSeparate(GL_FRONT,
                              GLES2_STENCIL_OPS[(int)gpu_pso->dss.stencilFailOpFront],
                              GLES2_STENCIL_OPS[(int)gpu_pso->dss.stencilZFailOpFront],
                              GLES2_STENCIL_OPS[(int)gpu_pso->dss.stencilPassOpFront]);
        }
        if (cache->dss.stencilWriteMaskFront != gpu_pso->dss.stencilWriteMaskFront) {
          glStencilMaskSeparate(GL_FRONT, gpu_pso->dss.stencilWriteMaskFront);
          cache->dss.stencilWriteMaskFront = gpu_pso->dss.stencilWriteMaskFront;
        }
        
        // bind depth-stencil state - back
        if (cache->dss.stencilFuncBack != gpu_pso->dss.stencilFuncBack ||
            cache->dss.stencilRefBack != gpu_pso->dss.stencilRefBack ||
            cache->dss.stencilReadMaskBack != gpu_pso->dss.stencilReadMaskBack) {
          glStencilFuncSeparate(GL_BACK,
                                GLES2_CMP_FUNCS[(int)gpu_pso->dss.stencilFuncBack],
                                gpu_pso->dss.stencilRefBack,
                                gpu_pso->dss.stencilReadMaskBack);
        }
        if (cache->dss.stencilFailOpBack != gpu_pso->dss.stencilFailOpBack ||
            cache->dss.stencilZFailOpBack != gpu_pso->dss.stencilZFailOpBack ||
            cache->dss.stencilPassOpBack != gpu_pso->dss.stencilPassOpBack) {
          glStencilOpSeparate(GL_BACK,
                              GLES2_STENCIL_OPS[(int)gpu_pso->dss.stencilFailOpBack],
                              GLES2_STENCIL_OPS[(int)gpu_pso->dss.stencilZFailOpBack],
                              GLES2_STENCIL_OPS[(int)gpu_pso->dss.stencilPassOpBack]);
        }
        if (cache->dss.stencilWriteMaskBack != gpu_pso->dss.stencilWriteMaskBack) {
          glStencilMaskSeparate(GL_BACK, gpu_pso->dss.stencilWriteMaskBack);
          cache->dss.stencilWriteMaskBack = gpu_pso->dss.stencilWriteMaskBack;
        }
        
        // bind blend state
        if (cache->bs.isA2C != gpu_pso->bs.isA2C) {
          if (cache->bs.isA2C) {
            glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
          } else {
            glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE);
          }
        }
        if (cache->bs.blendColor.r != gpu_pso->bs.blendColor.r ||
            cache->bs.blendColor.g != gpu_pso->bs.blendColor.g ||
            cache->bs.blendColor.b != gpu_pso->bs.blendColor.b ||
            cache->bs.blendColor.a != gpu_pso->bs.blendColor.a) {
          
          glBlendColor(gpu_pso->bs.blendColor.r,
                       gpu_pso->bs.blendColor.g,
                       gpu_pso->bs.blendColor.b,
                       gpu_pso->bs.blendColor.a);
          cache->bs.blendColor = gpu_pso->bs.blendColor;
        }
        
        GFXBlendTarget& cache_target = cache->bs.targets[0];
        const GFXBlendTarget& target = gpu_pso->bs.targets[0];
        if (cache_target.blend != target.blend) {
          if (!cache_target.blend) {
            glEnable(GL_BLEND);
          } else {
            glDisable(GL_BLEND);
          }
          cache_target.blend = target.blend;
        }
        if (cache_target.blendEq != target.blendEq ||
            cache_target.blendAlphaEq != target.blendAlphaEq) {
          glBlendEquationSeparate(GLES2_BLEND_OPS[(int)target.blendEq],
                                  GLES2_BLEND_OPS[(int)target.blendAlphaEq]);
          cache_target.blendEq = target.blendEq;
          cache_target.blendAlphaEq = target.blendAlphaEq;
        }
        if (cache_target.blendSrc != target.blendSrc ||
            cache_target.blendDst != target.blendDst ||
            cache_target.blendSrcAlpha != target.blendSrcAlpha ||
            cache_target.blendDstAlpha != target.blendDstAlpha) {
          glBlendFuncSeparate(GLES2_BLEND_FACTORS[(int)target.blendSrc],
                              GLES2_BLEND_FACTORS[(int)target.blendDst],
                              GLES2_BLEND_FACTORS[(int)target.blendSrcAlpha],
                              GLES2_BLEND_FACTORS[(int)target.blendDstAlpha]);
          cache_target.blendSrc = target.blendSrc;
          cache_target.blendDst = target.blendDst;
          cache_target.blendSrcAlpha = target.blendSrcAlpha;
          cache_target.blendDstAlpha = target.blendDstAlpha;
        }
        if (cache_target.blendColorMask != target.blendColorMask) {
          glColorMask((GLboolean)(target.blendColorMask & GFXColorMask::R),
            (GLboolean)(target.blendColorMask & GFXColorMask::G),
            (GLboolean)(target.blendColorMask & GFXColorMask::B),
            (GLboolean)(target.blendColorMask & GFXColorMask::A));
          cache_target.blendColorMask = target.blendColorMask;
        }
        
        // bind shader resources
        if (cmd->gpu_binding_layout && gpu_pso->gpuShader) {
          uint8_t* uniform_buff;

          for(size_t j = 0; j < cmd->gpu_binding_layout->gpuBindings.size(); ++j) {
            const GLES2GPUBinding& gpu_binding = cmd->gpu_binding_layout->gpuBindings[j];
            switch (gpu_binding.type) {
              case GFXBindingType::UNIFORM_BUFFER: {
                if (gpu_binding.gpuBuffer) {
                  for (size_t k = 0; k < gpu_pso->gpuShader->glBlocks.size(); ++k) {
                    const GLES2GPUUniformBlock& gpu_block = gpu_pso->gpuShader->glBlocks[k];

                    if (gpu_binding.binding == gpu_block.binding &&
                        gpu_binding.gpuBuffer &&
                        gpu_binding.gpuBuffer->buffer) {
                      for (size_t u = 0; u < gpu_block.glActiveUniforms.size(); ++u) {
                        const GLES2GPUUniform& gpu_uniform = gpu_block.glActiveUniforms[u];
                        uniform_buff = (gpu_binding.gpuBuffer->buffer + gpu_uniform.offset);
                        switch (gpu_uniform.glType)
                        {
                        case GL_BOOL:
                        case GL_INT: {
                          if (memcmp(gpu_uniform.buff, uniform_buff, gpu_uniform.size) != 0) {
                            glUniform1iv(gpu_uniform.glLoc, gpu_uniform.count, (const GLint*)uniform_buff);
                            memcpy(gpu_uniform.buff, uniform_buff, gpu_uniform.size);
                          }
                          break;
                        }
                        case GL_BOOL_VEC2:
                        case GL_INT_VEC2: {
                          if (memcmp(gpu_uniform.buff, uniform_buff, gpu_uniform.size) != 0) {
                            glUniform2iv(gpu_uniform.glLoc, gpu_uniform.count, (const GLint*)uniform_buff);
                            memcpy(gpu_uniform.buff, uniform_buff, gpu_uniform.size);
                          }
                          break;
                        }
                        case GL_BOOL_VEC3:
                        case GL_INT_VEC3: {
                          if (memcmp(gpu_uniform.buff, uniform_buff, gpu_uniform.size) != 0) {
                            glUniform3iv(gpu_uniform.glLoc, gpu_uniform.count, (const GLint*)uniform_buff);
                            memcpy(gpu_uniform.buff, uniform_buff, gpu_uniform.size);
                          }
                          break;
                        }
                        case GL_BOOL_VEC4:
                        case GL_INT_VEC4: {
                          if (memcmp(gpu_uniform.buff, uniform_buff, gpu_uniform.size) != 0) {
                            glUniform4iv(gpu_uniform.glLoc, gpu_uniform.count, (const GLint*)uniform_buff);
                            memcpy(gpu_uniform.buff, uniform_buff, gpu_uniform.size);
                          }
                          break;
                        }
                        case GL_FLOAT: {
                          if (memcmp(gpu_uniform.buff, uniform_buff, gpu_uniform.size) != 0) {
                            glUniform1fv(gpu_uniform.glLoc, gpu_uniform.count, (const GLfloat*)uniform_buff);
                            memcpy(gpu_uniform.buff, uniform_buff, gpu_uniform.size);
                          }
                          break;
                        }
                        case GL_FLOAT_VEC2: {
                          if (memcmp(gpu_uniform.buff, uniform_buff, gpu_uniform.size) != 0) {
                            glUniform2fv(gpu_uniform.glLoc, gpu_uniform.count, (const GLfloat*)uniform_buff);
                            memcpy(gpu_uniform.buff, uniform_buff, gpu_uniform.size);
                          }
                          break;
                        }
                        case GL_FLOAT_VEC3: {
                          if (memcmp(gpu_uniform.buff, uniform_buff, gpu_uniform.size) != 0) {
                            glUniform3fv(gpu_uniform.glLoc, gpu_uniform.count, (const GLfloat*)uniform_buff);
                            memcpy(gpu_uniform.buff, uniform_buff, gpu_uniform.size);
                          }
                          break;
                        }
                        case GL_FLOAT_VEC4: {
                          if (memcmp(gpu_uniform.buff, uniform_buff, gpu_uniform.size) != 0) {
                            glUniform4fv(gpu_uniform.glLoc, gpu_uniform.count, (const GLfloat*)uniform_buff);
                            memcpy(gpu_uniform.buff, uniform_buff, gpu_uniform.size);
                          }
                          break;
                        }
                        case GL_FLOAT_MAT2: {
                          if (memcmp(gpu_uniform.buff, uniform_buff, gpu_uniform.size) != 0) {
                            glUniformMatrix2fv(gpu_uniform.glLoc, gpu_uniform.count, GL_FALSE, (const GLfloat*)uniform_buff);
                            memcpy(gpu_uniform.buff, uniform_buff, gpu_uniform.size);
                          }
                          break;
                        }
                        case GL_FLOAT_MAT3: {
                          if (memcmp(gpu_uniform.buff, uniform_buff, gpu_uniform.size) != 0) {
                            glUniformMatrix3fv(gpu_uniform.glLoc, gpu_uniform.count, GL_FALSE, (const GLfloat*)uniform_buff);
                            memcpy(gpu_uniform.buff, uniform_buff, gpu_uniform.size);
                          }
                          break;
                        }
                        case GL_FLOAT_MAT4: {
                          if (memcmp(gpu_uniform.buff, uniform_buff, gpu_uniform.size) != 0) {
                            glUniformMatrix4fv(gpu_uniform.glLoc, gpu_uniform.count, GL_FALSE, (const GLfloat*)uniform_buff);
                            memcpy(gpu_uniform.buff, uniform_buff, gpu_uniform.size);
                          }
                          break;
                        }
                        default:
                          break;
                        }
                      } // for
                      break;
                    }
                  }
                }
                break;
              }
              case GFXBindingType::SAMPLER: {
                if (gpu_binding.gpuSampler) {
                  for (size_t k = 0; k < gpu_pso->gpuShader->glSamplers.size(); ++k) {
                    const GLES2GPUUniformSampler& gpuSampler = gpu_pso->gpuShader->glSamplers[k];
                    if (gpuSampler.binding == gpu_binding.binding) {
                      for (size_t u = 0; u < gpuSampler.units.size(); ++u) {
                        uint unit = (uint)gpuSampler.units[u];
                        if (gpu_binding.gpuTexView && (gpu_binding.gpuTexView->gpuTexture->size > 0)) {
                          GLES2GPUTexture* gpuTexture = gpu_binding.gpuTexView->gpuTexture;
                          GLuint glTexture = gpuTexture->glTexture;
                          if (cache->glTextures[unit] != glTexture) {
                            if (cache->texUint != unit) {
                              glActiveTexture(GL_TEXTURE0 + unit);
                              cache->texUint = unit;
                            }
                            glBindTexture(gpuTexture->glTarget, glTexture);
                            cache->glTextures[unit] = glTexture;
                          }

                          if (gpu_binding.gpuTexView->gpuTexture->isPowerOf2) {
                            glWrapS = gpu_binding.gpuSampler->glWrapS;
                            glWrapT = gpu_binding.gpuSampler->glWrapT;

                            if (gpu_binding.gpuTexView->gpuTexture->mipLevel <= 1 &&
                                !(gpu_binding.gpuTexView->gpuTexture->flags & GFXTextureFlagBit::GEN_MIPMAP) &&
                                (gpu_binding.gpuSampler->glMinFilter == GL_LINEAR_MIPMAP_NEAREST ||
                                 gpu_binding.gpuSampler->glMinFilter == GL_LINEAR_MIPMAP_LINEAR)) {
                              glMinFilter = GL_LINEAR;
                            } else {
                              glMinFilter = gpu_binding.gpuSampler->glMinFilter;
                            }
                          } else {
                            glWrapS = GL_CLAMP_TO_EDGE;
                            glWrapT = GL_CLAMP_TO_EDGE;

                            if (gpu_binding.gpuSampler->glMinFilter == GL_LINEAR || 
                                gpu_binding.gpuSampler->glMinFilter == GL_LINEAR_MIPMAP_NEAREST ||
                                gpu_binding.gpuSampler->glMinFilter == GL_LINEAR_MIPMAP_LINEAR) {
                              glMinFilter = GL_LINEAR;
                            } else {
                              glMinFilter = GL_NEAREST;
                            }
                          }

                          if (gpuTexture->glWrapS != glWrapS) {
                            if (cache->texUint != unit) {
                              glActiveTexture(GL_TEXTURE0 + unit);
                              cache->texUint = unit;
                            }
                            glTexParameteri(gpuTexture->glTarget, GL_TEXTURE_WRAP_S, glWrapS);
                            gpuTexture->glWrapS = glWrapS;
                          }

                          if (gpuTexture->glWrapT != glWrapT) {
                            if (cache->texUint != unit) {
                              glActiveTexture(GL_TEXTURE0 + unit);
                              cache->texUint = unit;
                            }
                            glTexParameteri(gpuTexture->glTarget, GL_TEXTURE_WRAP_T, glWrapT);
                            gpuTexture->glWrapT = glWrapT;
                          }

                          if (gpuTexture->glMinFilter != glMinFilter) {
                            if (cache->texUint != unit) {
                              glActiveTexture(GL_TEXTURE0 + unit);
                              cache->texUint = unit;
                            }
                            glTexParameteri(gpuTexture->glTarget, GL_TEXTURE_MIN_FILTER, glMinFilter);
                            gpuTexture->glMinFilter = glMinFilter;
                          }

                          if (gpuTexture->glMagFilter != gpu_binding.gpuSampler->glMagFilter) {
                            if (cache->texUint != unit) {
                              glActiveTexture(GL_TEXTURE0 + unit);
                              cache->texUint = unit;
                            }
                            glTexParameteri(gpuTexture->glTarget, GL_TEXTURE_MAG_FILTER, gpu_binding.gpuSampler->glMagFilter);
                            gpuTexture->glMagFilter = gpu_binding.gpuSampler->glMagFilter;
                          }
                        }
                      }
                      break;
                    }
                  }
                }
                break;
              }
              default:
                break;
            }
          }
        } // if
        
        // bind vao
        if (cmd->gpu_ia && gpu_pso->gpuShader &&
            (is_shader_changed || gpu_ia != cmd->gpu_ia)) {
          gpu_ia = cmd->gpu_ia;
          if (device->useVAO()) {
            const auto it = gpu_ia->glVAOs.find(gpu_pso->gpuShader->glProgram);
            if (it != gpu_ia->glVAOs.end()) {
              GLuint glVAO = it->second;
              if (!glVAO) {
                glGenVertexArraysOES(1, &glVAO);
                gpu_ia->glVAOs.insert(std::make_pair(gpu_pso->gpuShader->glProgram, glVAO));
                glBindVertexArrayOES(glVAO);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                
                for (size_t j = 0; j < gpu_pso->gpuShader->glInputs.size(); ++j) {
                  const GLES2GPUInput& gpu_input = gpu_pso->gpuShader->glInputs[j];
                  for (size_t a = 0; a < gpu_ia->attributes.size(); ++a) {
                    const GLES2GPUAttribute& gpu_attrib = gpu_ia->glAttribs[a];
                    if (gpu_attrib.name == gpu_input.name) {
                      glBindBuffer(GL_ARRAY_BUFFER, gpu_attrib.glBuffer);
                      
                      for (uint c = 0; c < gpu_attrib.componentCount; ++c) {
                        GLint glLoc = gpu_input.glLoc + c;
                        uint attrib_offset = gpu_attrib.offset + gpu_attrib.size * c;
                        glEnableVertexAttribArray(glLoc);
                        
                        cache->glEnabledAttribLocs[glLoc] = true;
                        glVertexAttribPointer(glLoc, gpu_attrib.count, gpu_attrib.glType, gpu_attrib.isNormalized, gpu_attrib.stride, BUFFER_OFFSET(attrib_offset));

                        if (device->useInstancedArrays()) {
                          glVertexAttribDivisorEXT(glLoc, gpu_attrib.isInstanced ? 1 : 0);
                        }
                      }
                      break;
                    }
                  } // for
                } // for
                
                if (gpu_ia->gpuIndexBuffer) {
                  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gpu_ia->gpuIndexBuffer->glBuffer);
                }
                
                glBindVertexArrayOES(0);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                cache->glVAO = 0;
                cache->glArrayBuffer = 0;
                cache->glElementArrayBuffer = 0;
              }
              
              if (cache->glVAO != glVAO) {
                glBindVertexArrayOES(glVAO);
                cache->glVAO = glVAO;
              }
            } else {
              for (uint a = 0; a < GFX_MAX_VERTEX_ATTRIBUTES; ++a) {
                cache->glCurrentAttribLocs[a] = false;
              }

              for (size_t j = 0; j < gpu_pso->gpuShader->glInputs.size(); ++j) {
                const GLES2GPUInput& gpu_input = gpu_pso->gpuShader->glInputs[j];
                for (size_t a = 0; a < gpu_ia->attributes.size(); ++a) {
                  const GLES2GPUAttribute& gpu_attrib = gpu_ia->glAttribs[a];
                  if (gpu_attrib.name == gpu_input.name) {
                    glBindBuffer(GL_ARRAY_BUFFER, gpu_attrib.glBuffer);

                    for (uint c = 0; c < gpu_attrib.componentCount; ++c) {
                      GLint glLoc = gpu_input.glLoc + c;
                      uint attrib_offset = gpu_attrib.offset + gpu_attrib.size * c;
                      glEnableVertexAttribArray(glLoc);
                      cache->glEnabledAttribLocs[glLoc] = true;
                      cache->glCurrentAttribLocs[glLoc] = true;
                      glVertexAttribPointer(glLoc, gpu_attrib.count, gpu_attrib.glType, gpu_attrib.isNormalized, gpu_attrib.stride, BUFFER_OFFSET(attrib_offset));

                      if (device->useInstancedArrays()) {
                        glVertexAttribDivisorEXT(glLoc, gpu_attrib.isInstanced ? 1 : 0);
                      }
                    }
                    break;
                  }
                } // for
              } // for

              if (gpu_ia->gpuIndexBuffer) {
                if (cache->glElementArrayBuffer != gpu_ia->gpuIndexBuffer->glBuffer) {
                  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gpu_ia->gpuIndexBuffer->glBuffer);
                  cache->glElementArrayBuffer = gpu_ia->gpuIndexBuffer->glBuffer;
                }
              }

              for (uint a = 0; a < GFX_MAX_VERTEX_ATTRIBUTES; ++a) {
                if (cache->glEnabledAttribLocs[a] != cache->glCurrentAttribLocs[a]) {
                  glDisableVertexAttribArray(a);
                  cache->glEnabledAttribLocs[a] = false;
                }
              }
            }
          } // if
        }
        
        break;
      }
      case GFXCmdType::DRAW: {
        GLES2CmdDraw* cmd = cmd_package->draw_cmds[cmd_idx];
        if (gpu_ia && gpu_pso) {
          if (!gpu_ia->gpuIndirectBuffer) {

            if (gpu_ia->gpuIndexBuffer && cmd->draw_info.indexCount >= 0) {
              uint8_t* offset = 0;
              offset += cmd->draw_info.firstIndex * gpu_ia->gpuIndexBuffer->stride;
              if (cmd->draw_info.instanceCount == 0) {
                glDrawElements(glPrimitive, cmd->draw_info.indexCount, gpu_ia->glIndexType, offset);
              } else {
                if (device->useDrawInstanced()) {
                  glDrawElementsInstancedEXT(glPrimitive, cmd->draw_info.indexCount, gpu_ia->glIndexType, offset, cmd->draw_info.instanceCount);
                }
              }
            } else {
              if (cmd->draw_info.instanceCount == 0) {
                glDrawArrays(glPrimitive, cmd->draw_info.firstIndex, cmd->draw_info.vertexCount);
              } else {
                if (device->useDrawInstanced()) {
                  glDrawArraysInstancedEXT(glPrimitive, cmd->draw_info.firstIndex, cmd->draw_info.vertexCount, cmd->draw_info.instanceCount);
                }
              }
            }
          } else {
            for (size_t j = 0; j < gpu_ia->gpuIndirectBuffer->indirectBuff.draws.size(); ++j) {
              GFXDrawInfo& draw = gpu_ia->gpuIndirectBuffer->indirectBuff.draws[j];
              if (gpu_ia->gpuIndexBuffer && draw.indexCount >= 0) {
                uint8_t* offset = 0;
                offset += draw.firstIndex * gpu_ia->gpuIndexBuffer->stride;
                if (cmd->draw_info.instanceCount == 0) {
                  glDrawElements(glPrimitive, draw.indexCount, gpu_ia->glIndexType, offset);
                } else {
                  if (device->useDrawInstanced()) {
                    glDrawElementsInstancedEXT(glPrimitive, draw.indexCount, gpu_ia->glIndexType, offset, cmd->draw_info.instanceCount);
                  }
                }
              } else {
                if (cmd->draw_info.instanceCount == 0) {
                  glDrawArrays(glPrimitive, draw.firstIndex, draw.vertexCount);
                } else {
                  if (device->useDrawInstanced()) {
                    glDrawArraysInstancedEXT(glPrimitive, draw.firstIndex, draw.vertexCount, cmd->draw_info.instanceCount);
                  }
                }
              }
            }
          }
        }
        break;
      }
      case GFXCmdType::UPDATE_BUFFER: {
        GLES2CmdUpdateBuffer* cmd = cmd_package->update_buffer_cmds[cmd_idx];
        GLES2CmdFuncUpdateBuffer(device, cmd->gpuBuffer, cmd->buffer, cmd->offset, cmd->size);
        break;
      }
      case GFXCmdType::COPY_BUFFER_TO_TEXTURE: {
        GLES2CmdCopyBufferToTexture* cmd = cmd_package->copy_buffer_to_texture_cmds[cmd_idx];
        GLES2CmdFuncCopyBuffersToTexture(device, &(cmd->gpuBuffer->buffer), 1, cmd->gpuTexture, cmd->regions);
        break;
      }
      default:
        break;
    }
      cmd_idx++;
  }
}

void GLES2CmdFuncCopyBuffersToTexture(GLES2Device* device, uint8_t** buffers, uint count, GLES2GPUTexture* gpuTexture, const GFXBufferTextureCopyList& regions) {
  GLuint glTexture = device->state_cache->glTextures[device->state_cache->texUint];
  if (glTexture != gpuTexture->glTexture) {
    glBindTexture(gpuTexture->glTarget, gpuTexture->glTexture);
    device->state_cache->glTextures[device->state_cache->texUint] = glTexture;
  }

  bool isCompressed = GFX_FORMAT_INFOS[(int)gpuTexture->format].isCompressed;
  uint n = 0;

  switch (gpuTexture->glTarget) {
  case GL_TEXTURE_2D: {
    uint w;
    uint h;
    for (size_t i = 0; i < regions.size(); ++i) {
      const GFXBufferTextureCopy& region = regions[i];
      n = 0;
      w = region.texExtent.width;
      h = region.texExtent.height;
      for (uint m = region.texSubres.baseMipLevel; m < region.texSubres.baseMipLevel + region.texSubres.levelCount; ++m) {
        uint8_t* buff = region.buffOffset + region.buffTexHeight * region.buffStride + buffers[n++];
        if (!isCompressed) {
          glTexSubImage2D(GL_TEXTURE_2D, m, region.texOffset.x, region.texOffset.y, w, h, gpuTexture->glFormat, gpuTexture->glType, (GLvoid*)buff);
        } else {
          GLsizei memSize = (GLsizei)GFXFormatSize(gpuTexture->format, w, h, 1);
          glCompressedTexSubImage2D(GL_TEXTURE_2D, m, region.texOffset.x, region.texOffset.y, w, h, gpuTexture->glFormat, memSize, (GLvoid*)buff);
        }

        w = std::max(w >> 1, 1U);
        h = std::max(h >> 1, 1U);
      }
    }
    break;
  }
  case GL_TEXTURE_2D_ARRAY: {
    uint w;
    uint h;
    for (size_t i = 0; i < regions.size(); ++i) {
      const GFXBufferTextureCopy& region = regions[i];
      n = 0;
      uint d = region.texSubres.layerCount;
      uint layerCount = d + region.texSubres.baseArrayLayer;

      for (uint z = region.texSubres.baseArrayLayer; z < layerCount; ++z) {
        w = region.texExtent.width;
        h = region.texExtent.height;
        for (uint m = region.texSubres.baseMipLevel; m < region.texSubres.baseMipLevel + region.texSubres.levelCount; ++m) {
          uint8_t* buff = region.buffOffset + region.buffTexHeight * region.buffStride + buffers[n++];
          if (!isCompressed) {
            glTexSubImage3DOES(GL_TEXTURE_2D_ARRAY, m, region.texOffset.x, region.texOffset.y, z, 
              w, h, d, gpuTexture->glFormat, gpuTexture->glType, (GLvoid*)buff);
          }
          else {
            GLsizei memSize = (GLsizei)GFXFormatSize(gpuTexture->format, w, h, 1);
            glCompressedTexSubImage3DOES(GL_TEXTURE_2D_ARRAY, m, region.texOffset.x, region.texOffset.y, z,
              w, h, d, gpuTexture->glFormat, memSize, (GLvoid*)buff);
          }

          w = std::max(w >> 1, 1U);
          h = std::max(h >> 1, 1U);
        }
      }
    }
    break;
  }
  case GL_TEXTURE_3D: {
    uint w;
    uint h;
    uint d;
    for (size_t i = 0; i < regions.size(); ++i) {
      const GFXBufferTextureCopy& region = regions[i];
      n = 0;
      w = region.texExtent.width;
      h = region.texExtent.height;
      d = region.texExtent.depth;
      for (uint m = region.texSubres.baseMipLevel; m < region.texSubres.baseMipLevel + region.texSubres.levelCount; ++m) {
        uint8_t* buff = region.buffOffset + region.buffTexHeight * region.buffStride + buffers[n++];
        if (!isCompressed) {
          glTexSubImage3DOES(GL_TEXTURE_3D, m, region.texOffset.x, region.texOffset.y, region.texOffset.z, 
            w, h, d, gpuTexture->glFormat, gpuTexture->glType, (GLvoid*)buff);
        }
        else {
          GLsizei memSize = (GLsizei)GFXFormatSize(gpuTexture->format, w, d + 1, 1);
          glCompressedTexSubImage3DOES(GL_TEXTURE_3D, m, region.texOffset.x, region.texOffset.y, region.texOffset.z, 
            w, h, d, gpuTexture->glFormat, memSize, (GLvoid*)buff);
        }

        w = std::max(w >> 1, 1U);
        h = std::max(h >> 1, 1U);
        d = std::max(d >> 1, 1U);
      }
    }
    break;
  }
  case GL_TEXTURE_CUBE_MAP: {
    uint w;
    uint h;
    uint f;
    for (size_t i = 0; i < regions.size(); ++i) {
      const GFXBufferTextureCopy& region = regions[i];
      n = 0;
      
      uint face_count = region.texSubres.baseArrayLayer + region.texSubres.layerCount;
      for (f = region.texSubres.baseArrayLayer; f < face_count; ++f) {
        w = region.texExtent.width;
        h = region.texExtent.height;

        for (uint m = region.texSubres.baseMipLevel; m < region.texSubres.baseMipLevel + region.texSubres.levelCount; ++m) {
          uint8_t* buff = region.buffOffset + region.buffTexHeight * region.buffStride + buffers[n++];
          if (!isCompressed) {
            glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + f, m, region.texOffset.x, region.texOffset.y, w, h, gpuTexture->glFormat, gpuTexture->glType, (GLvoid*)buff);
          }
          else {
            GLsizei memSize = (GLsizei)GFXFormatSize(gpuTexture->format, w, h, 1);
            glCompressedTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + f, m, region.texOffset.x, region.texOffset.y, w, h, gpuTexture->glFormat, memSize, (GLvoid*)buff);
          }

          w = std::max(w >> 1, 1U);
          h = std::max(h >> 1, 1U);
        }
      }
    }
    break;
  }
  default:
    CCASSERT(false, "Unsupported GFXTextureType, copy buffers to texture failed.");
    break;
  }
    
    if(gpuTexture->flags & GFXTextureFlagBit::GEN_MIPMAP)
    {
        glBindTexture(gpuTexture->glTarget, gpuTexture->glTexture);
        glGenerateMipmap(gpuTexture->glTarget);
    }
}


NS_CC_END
