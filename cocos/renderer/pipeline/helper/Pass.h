#pragma once
#include "core/CoreStd.h"

namespace cc {
namespace pipeline {

struct CC_DLL Pass {
    uint priority = 0;
    uint hash = 0;
    uint phaseMappendID = UINT_MAX;
};

} //namespace pipeline
} //namespace cc

