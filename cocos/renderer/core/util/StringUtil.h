#ifndef CC_CORE_KERNEL_UTIL_STRING_UTIL_H_
#define CC_CORE_KERNEL_UTIL_STRING_UTIL_H_

#include "base/ccMacros.h"
#include <vector>

NS_CC_BEGIN

class CC_DLL StringUtil {
 public:
	static int VPrintf(char* buf, char* last, const char* fmt, va_list args);
	static int Printf(char* buf, char* last, const char* fmt, ...);
	static std::string Format(const char* fmt, ...);
    static std::vector<std::string> Split(const std::string &str, const std::string &delims, uint32_t max_splits = 0);
};

NS_CC_END

#endif // CC_CORE_KERNEL_UTIL_STRING_UTIL_H_
