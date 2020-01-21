#include "CoreStd.h"
#include "GFXTexture.h"

NS_CC_BEGIN

GFXTexture::GFXTexture(GFXDevice* device)
    : _device(device),
      _type(GFXTextureType::TEX2D),
      _usage(GFXTextureUsageBit::NONE),
      format_(GFXFormat::UNKNOWN),
      _width(0),
      _height(0),
      depth_(1),
      array_layer_(1),
      mip_level_(1),
      _size(0),
      samples_(GFXSampleCount::X1),
      _flags(GFXTextureFlagBit::NONE),
      _buffer(nullptr) {
}

GFXTexture::~GFXTexture() {
}

NS_CC_END
