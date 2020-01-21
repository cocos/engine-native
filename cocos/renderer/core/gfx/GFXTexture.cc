#include "CoreStd.h"
#include "GFXTexture.h"

NS_CC_BEGIN

GFXTexture::GFXTexture(GFXDevice* device)
    : _device(device),
      type_(GFXTextureType::TEX2D),
      usage_(GFXTextureUsageBit::NONE),
      format_(GFXFormat::UNKNOWN),
      _width(0),
      _height(0),
      depth_(1),
      array_layer_(1),
      mip_level_(1),
      size_(0),
      samples_(GFXSampleCount::X1),
      flags_(GFXTextureFlagBit::NONE),
      buffer_(nullptr) {
}

GFXTexture::~GFXTexture() {
}

NS_CC_END
