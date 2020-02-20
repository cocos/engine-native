#include "GLES2Std.h"
#include "GLES2Sampler.h"
#include "GLES2Commands.h"

NS_CC_BEGIN

GLES2Sampler::GLES2Sampler(GFXDevice* device)
    : GFXSampler(device),
      gpu_sampler_(nullptr) {
}

GLES2Sampler::~GLES2Sampler() {
}

bool GLES2Sampler::initialize(const GFXSamplerInfo &info) {
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
  _minLod = info.minLOD;
  _maxLod = info.maxLOD;
  _mipLodBias = info.mipLODBias;
  
  gpu_sampler_ = CC_NEW(GLES2GPUSampler);
  gpu_sampler_->minFilter = _minFilter;
  gpu_sampler_->magFilter = _magFilter;
  gpu_sampler_->mipFilter = _mipFilter;
  gpu_sampler_->addressU = _addressU;
  gpu_sampler_->addressV = _addressV;
  gpu_sampler_->addressW = _addressW;
  gpu_sampler_->minLOD = _minLod;
  gpu_sampler_->maxLOD = _maxLod;
  
  GLES2CmdFuncCreateSampler((GLES2Device*)_device, gpu_sampler_);
  
  return true;
}

void GLES2Sampler::destroy() {
  if (gpu_sampler_) {
    GLES2CmdFuncDestroySampler((GLES2Device*)_device, gpu_sampler_);
    CC_DELETE(gpu_sampler_);
    gpu_sampler_ = nullptr;
  }
}

NS_CC_END
