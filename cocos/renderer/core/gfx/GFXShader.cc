#include "CoreStd.h"
#include "GFXShader.h"

NS_CC_BEGIN

GFXShader::GFXShader(GFXDevice* device)
    : _device(device),
      hash_(0) {
}

GFXShader::~GFXShader() {
}

NS_CC_END
