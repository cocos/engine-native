#pragma once
#include "core/CoreStd.h"

namespace cc {
namespace pipeline {

class CC_DLL SharedMemory : public Object {
public:
    template <typename RET, typename T, typename U>
    static RET get(T mappedIndex, U slot);

    template <typename RET, typename T, typename U>
    static RET get(const T *handle, U memberOffset);
};
} //namespace pipeline
} //namespace cc

