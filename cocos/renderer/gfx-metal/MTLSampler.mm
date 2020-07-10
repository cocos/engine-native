#include "MTLStd.h"

#include "MTLDevice.h"
#include "MTLSampler.h"
#include "MTLUtils.h"

#import <Metal/MTLDevice.h>

namespace cc {
namespace gfx {

CCMTLSampler::CCMTLSampler(Device *device) : Sampler(device) {}
CCMTLSampler::~CCMTLSampler() { destroy(); }

bool CCMTLSampler::initialize(const SamplerInfo &info) {
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

    _mtlSamplerState = mu::getMTLSamplerState(id<MTLDevice>(((CCMTLDevice *)_device)->getMTLDevice()), info);

    _status = Status::SUCCESS;

    return _mtlSamplerState != nil;
}

void CCMTLSampler::destroy() {
    _status = Status::UNREADY;
}

} // namespace gfx
} // namespace cc
