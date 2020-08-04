#pragma once
#include "core/CoreStd.h"

namespace cc {
namespace pipeline {

struct CC_DLL Model {
    uint isDynamicBatching = 0;
    uint subModelsID = 0;
    uint subModelsCount = 0;
};

} //namespace pipeline
} // namespace cc

