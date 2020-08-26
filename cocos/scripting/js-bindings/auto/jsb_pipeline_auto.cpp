#include "scripting/js-bindings/auto/jsb_pipeline_auto.h"
#if (CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_MAC_IOS || CC_PLATFORM == CC_PLATFORM_MAC_OSX || CC_PLATFORM == CC_PLATFORM_WINDOWS)
#include "scripting/js-bindings/manual/jsb_conversions.h"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "renderer/pipeline/pipeline-bindings.h"

#ifndef JSB_ALLOC
#define JSB_ALLOC(kls, ...) new (std::nothrow) kls(__VA_ARGS__)
#endif

#ifndef JSB_FREE
#define JSB_FREE(ptr) delete ptr
#endif
