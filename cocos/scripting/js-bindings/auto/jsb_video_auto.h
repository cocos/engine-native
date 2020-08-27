#pragma once
#include "base/Config.h"
#if (USE_VIDEO > 0) && (CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_MAC_IOS) && !defined(CC_TARGET_OS_TVOS)

#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
