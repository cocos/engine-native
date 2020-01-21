#include "CoreStd.h"
#include "GFXContext.h"

NS_CC_BEGIN

GFXContext::GFXContext(GFXDevice* device)
    : _device(device),
      window_handle_(0),
      shared_ctx_(nullptr),
      vsync_mode_(GFXVsyncMode::OFF),
      _colorFmt(GFXFormat::UNKNOWN),
      _depthStencilFmt(GFXFormat::UNKNOWN) {
}

GFXContext::~GFXContext() {
}

NS_CC_END
