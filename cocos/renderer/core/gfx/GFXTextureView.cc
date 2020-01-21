#include "CoreStd.h"
#include "GFXTextureView.h"

NS_CC_BEGIN

GFXTextureView::GFXTextureView(GFXDevice* device)
    : _device(device),
      texture_(nullptr),
      _type(GFXTextureViewType::TV2D),
      _format(GFXFormat::UNKNOWN),
      base_level_(0),
      level_count_(1),
      base_layer_(0),
      layer_count_(1) {
}

GFXTextureView::~GFXTextureView() {
}

NS_CC_END
