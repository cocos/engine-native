#include "CoreStd.h"
#include "GFXFramebuffer.h"

NS_CC_BEGIN

GFXFramebuffer::GFXFramebuffer(GFXDevice* device)
    : _device(device),
      _renderPass(nullptr),
      depth_stencil_view_(nullptr),
      _isOffscreen(true) {
}

GFXFramebuffer::~GFXFramebuffer() {
}

NS_CC_END
