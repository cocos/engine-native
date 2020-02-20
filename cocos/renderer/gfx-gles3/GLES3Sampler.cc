#include "GLES3Std.h"
#include "GLES3Sampler.h"
#include "GLES3Commands.h"

NS_CC_BEGIN

GLES3Sampler::GLES3Sampler(GFXDevice* device)
    : GFXSampler(device),
      gpu_sampler_(nullptr) {
}

GLES3Sampler::~GLES3Sampler() {
}

bool GLES3Sampler::initialize(const GFXSamplerInfo &info) {
  _name = info.name;
  _minFilter = info.minFilter;
  _magFilter = info.magFilter;
  _mipFilter = info.mipFilter;
  _addressU = info.addressU;
  _addressV = info.addressV;
  _addressW = info.addressW;
  _maxAnisotropy = info.maxAnisotropy;
  _cmpFunc = info.cmpFunc;
  _borderColor = info.borderColor;
  _minLOD = info.minLOD;
  _maxLOD = info.maxLOD;
  _mipLODBias = info.mipLODBias;
  
  gpu_sampler_ = CC_NEW(GLES3GPUSampler);
  gpu_sampler_->minFilter = _minFilter;
  gpu_sampler_->magFilter = _magFilter;
  gpu_sampler_->mipFilter = _mipFilter;
  gpu_sampler_->addressU = _addressU;
  gpu_sampler_->addressV = _addressV;
  gpu_sampler_->addressW = _addressW;
  gpu_sampler_->minLOD = _minLOD;
  gpu_sampler_->maxLOD = _maxLOD;
  
  GLES3CmdFuncCreateSampler((GLES3Device*)_device, gpu_sampler_);
  
  return true;
}

void GLES3Sampler::destroy() {
  if (gpu_sampler_) {
    GLES3CmdFuncDestroySampler((GLES3Device*)_device, gpu_sampler_);
    CC_DELETE(gpu_sampler_);
    gpu_sampler_ = nullptr;
  }
}

NS_CC_END
