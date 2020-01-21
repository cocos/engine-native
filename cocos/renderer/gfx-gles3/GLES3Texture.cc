#include "GLES3Std.h"
#include "GLES3Texture.h"
#include "GLES3Commands.h"

NS_CC_BEGIN

GLES3Texture::GLES3Texture(GFXDevice* device)
    : GFXTexture(device),
      gpu_texture_(nullptr) {
}

GLES3Texture::~GLES3Texture() {
}

bool GLES3Texture::initialize(const GFXTextureInfo &info) {
  
  type_ = info.type;
  _usage = info.usage;
  format_ = info.format;
  _width = info.width;
  _height = info.height;
  depth_ = info.depth;
  array_layer_ = info.array_layer;
  mip_level_ = info.mip_level;
  samples_ = info.samples;
  _flags = info.flags;
  _size = GFXFormatSize(format_, _width, _height, depth_);
  
  if (_flags & GFXTextureFlags::BAKUP_BUFFER) {
    _buffer = (uint8_t*)CC_MALLOC(_size);
    _device->memoryStatus().texture_size += _size;
  }
  
  gpu_texture_ = CC_NEW(GLES3GPUTexture);
  gpu_texture_->type = type_;
  
  switch (type_) {
    case GFXTextureType::TEX1D: {
      if (array_layer_) {
        gpu_texture_->view_type = array_layer_ <= 1 ? GFXTextureViewType::TV1D : GFXTextureViewType::TV1D_ARRAY;
      } else {
        gpu_texture_->view_type = GFXTextureViewType::TV1D;
      }
      break;
    }
    case GFXTextureType::TEX2D: {
      if (array_layer_) {
        if (array_layer_ <= 1) {
          gpu_texture_->view_type = GFXTextureViewType::TV2D;
        } else if (_flags & GFXTextureFlagBit::CUBEMAP) {
          gpu_texture_->view_type = GFXTextureViewType::CUBE;
        } else {
          gpu_texture_->view_type = GFXTextureViewType::TV2D_ARRAY;
        }
      } else {
        gpu_texture_->view_type = GFXTextureViewType::TV2D;
      }
      break;
    }
    case GFXTextureType::TEX3D: {
      gpu_texture_->view_type = GFXTextureViewType::TV3D;
      break;
    }
    default: {
      gpu_texture_->view_type = GFXTextureViewType::TV2D;
    }
  }
  
  gpu_texture_->format = format_;
  gpu_texture_->usage = _usage;
  gpu_texture_->width = _width;
  gpu_texture_->height = _height;
  gpu_texture_->depth = depth_;
  gpu_texture_->size = _size;
  gpu_texture_->array_layer = array_layer_;
  gpu_texture_->mip_level = mip_level_;
  gpu_texture_->samples = samples_;
  gpu_texture_->flags = _flags;
    gpu_texture_->is_pot = math::IsPowerOfTwo(_width) && math::IsPowerOfTwo(_height);
  
  GLES3CmdFuncCreateTexture((GLES3Device*)_device, gpu_texture_);
  _device->memoryStatus().texture_size += _size;
  
  return true;
}

void GLES3Texture::destroy() {
  if (gpu_texture_) {
    GLES3CmdFuncDestroyTexture((GLES3Device*)_device, gpu_texture_);
    _device->memoryStatus().texture_size -= _size;
    CC_DELETE(gpu_texture_);
    gpu_texture_ = nullptr;
  }
  
  if (_buffer) {
    CC_FREE(_buffer);
    _device->memoryStatus().texture_size -= _size;
    _buffer = nullptr;
  }
}

void GLES3Texture::resize(uint width, uint height) {
  uint size = GFXFormatSize(format_, width, height, depth_);
  if (_size != size) {
    const uint old_size = _size;
    _width = width;
    _height = height;
    _size = size;
    
    GFXMemoryStatus& status = _device->memoryStatus();
    gpu_texture_->width = _width;
    gpu_texture_->height = _height;
    gpu_texture_->size = _size;
    GLES3CmdFuncResizeTexture((GLES3Device*)_device, gpu_texture_);
    status.buffer_size -= old_size;
    status.buffer_size += _size;
    
    if (_buffer) {
      const uint8_t* old_buff = _buffer;
      _buffer = (uint8_t*)CC_MALLOC(_size);
      memcpy(_buffer, old_buff, old_size);
      CC_FREE(_buffer);
      status.buffer_size -= old_size;
      status.buffer_size += _size;
    }
  }
}

NS_CC_END
