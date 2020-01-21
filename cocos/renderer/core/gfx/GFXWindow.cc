#include "CoreStd.h"
#include "GFXWindow.h"

NS_CC_BEGIN

GFXWindow::GFXWindow(GFXDevice* device)
    : _device(device),
      _left(0),
      _top(0),
      _width(1024),
      _height(768),
      _nativeWidth(0),
      _nativeHeight(0),
      _colorFmt(GFXFormat::UNKNOWN),
      _depthStencilFmt(GFXFormat::UNKNOWN),
      _isOffscreen(false),
      _isFullscreen(false),
      _renderPass(nullptr),
      color_texture_(nullptr),
      color_tex_view_(nullptr),
      depth_stencil_texture_(nullptr),
      depth_stencil_tex_view_(nullptr),
      framebuffer_(nullptr) {
}

GFXWindow::~GFXWindow() {
}

NS_CC_END
