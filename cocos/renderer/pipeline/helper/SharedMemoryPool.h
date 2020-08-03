#pragma once
#include "core/CoreStd.h"

namespace cc {
namespace gfx {
class Device;
} //namespace gfx

namespace pipeline {

class CC_DLL SharedMemory : public Object {
public:
    template <typename T, typename T1, typename T2>
    static T get(T1 mappedIndex, T2 slot);

    template <typename T, typename T1, typename T2>
    static T get(const T1 *handle, T2 memberOffset);

    static gfx::Device *getDevice();
};
} //namespace pipeline
} //namespace cc

