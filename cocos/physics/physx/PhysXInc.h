
#pragma once

#if defined(_MSC_VER)
    #pragma warning(disable : 4250)
    #pragma warning(disable : 4996)
#endif

#include "base/Macros.h"

#if !defined(NDEBUG) ^ defined(_DEBUG)
    #ifdef CC_DEBUG
        #define _DEBUG
    #else
        #define NDEBUG
    #endif
#endif

#include <PxConfig.h>
#include <PxPhysicsAPI.h>
#include <extensions/PxDefaultAllocator.h>
#include <extensions/PxDefaultErrorCallback.h>
