#pragma once
#include "core/CoreStd.h"

namespace cc {
namespace pipeline {

struct CC_DLL SubModel {
    uint priority = 0;
    uint materialID = 0;
    uint psociID = 0;
    uint iaID = 0;
    
    uint passesID = 0;
    uint passesCount = 0;
    
    
};

} //namespace pipeline
} //namespace cc

