#include "GLES2Std.h"
#include "GLES2TextureView.h"
#include "GLES2Texture.h"
#include "GLES2Commands.h"

NS_CC_BEGIN

GLES2TextureView::GLES2TextureView(GFXDevice* device)
    : GFXTextureView(device),
      gpu_tex_view_(nullptr) {
}

GLES2TextureView::~GLES2TextureView() {
}

bool GLES2TextureView::initialize(const GFXTextureViewInfo &info) {
  
  _texture = info.texture;
  _type = info.type;
  _format = info.format;
  _baseLevel = info.baseLevel;
  _levelCount = info.levelCount;
  _baseLayer = info.baseLayer;
  _layerCount = info.layerCount;
  
  gpu_tex_view_ = CC_NEW(GLES2GPUTextureView);
  gpu_tex_view_->gpu_texture = static_cast<GLES2Texture*>(_texture)->gpu_texture();
  gpu_tex_view_->type = _type;
  gpu_tex_view_->format = _format;
  gpu_tex_view_->baseLevel = info.baseLevel;
  gpu_tex_view_->levelCount = info.levelCount;
  
  return true;
}

void GLES2TextureView::destroy() {
  if (gpu_tex_view_) {
    CC_DELETE(gpu_tex_view_);
    gpu_tex_view_ = nullptr;
  }
  _texture = nullptr;
}

NS_CC_END
