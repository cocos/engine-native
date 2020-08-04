#pragma once
#include "core/CoreStd.h"

namespace cc {
namespace pipeline {

class CC_DLL SharedMemory : public Object {
public:
    template <typename RET, typename T>
    static RET get(T index);
};
} //namespace pipeline
} //namespace cc

