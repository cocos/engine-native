#pragma once

#include "base/ccConfig.h"

#if CC_ENABLE_JNI_BINDING_EXT

namespace se{
    class Object;
}

bool jsb_register_jni_impl(se::Object *obj);

#endif