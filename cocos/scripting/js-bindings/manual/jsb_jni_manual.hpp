
#pragma once

#include "base/ccConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) && CC_ENABLE_JNI_BINDING
namespace se {
    class Object;
}

bool jsb_register_jni_manual(se::Object *global);
#endif