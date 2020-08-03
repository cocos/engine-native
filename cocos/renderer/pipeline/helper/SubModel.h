#pragma once
#include "core/CoreStd.h"

namespace cc {
namespace pipeline {

struct CC_DLL SubModel {
    uint priority = 0;
    uint materialMappedID = UINT_MAX;
    uint psoCIMappendID = UINT_MAX;
    uint iaMappedID = UINT_MAX;
};

} //namespace pipeline
} //namespace cc

