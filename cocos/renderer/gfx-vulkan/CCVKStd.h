#ifndef __CC_GFXCCVK_CCVK_STD_H__
#define __CC_GFXCCVK_CCVK_STD_H__

#include <Core.h>

#if (CC_PLATFORM == CC_PLATFORM_WINDOWS)
#    if defined(CC_STATIC)
#       define CC_VULKAN_API
#    else
#	    ifdef CC_CCVK_EXPORTS
#		    define CC_VULKAN_API __declspec(dllexport)
#	    else
#		    define CC_VULKAN_API __declspec(dllimport)
#	    endif
#	endif
#else
#	define CC_VULKAN_API
#endif

#endif
