#include "StringUtil.h"
#include "base/ccMacros.h"
#include "platform/CCPlatformConfig.h"

#include <string>
#include <vector>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif
#  include <Windows.h>
#endif

NS_CC_BEGIN

#if defined(_WIN32)
int StringUtil::VPrintf(char* buf, char* last, const char* fmt, va_list args) {
  if (last <= buf) return 0;
  
  int count = (int)(last - buf);
  int ret = _vsnprintf_s(buf, count, _TRUNCATE, fmt, args);
  if (ret < 0) {
    if (errno == 0) {
      return count - 1;
    } else {
      return 0;
    }
  } else {
    return ret;
  }
}
#else
int StringUtil::VPrintf(char* buf, char* last, const char* fmt, va_list args) {
  if (last <= buf) return 0;

  int count = (int)(last - buf);
  int ret = vsnprintf(buf, count, fmt, args);
  if (ret >= count - 1) {
    return count - 1;
  } else if (ret < 0) {
    return 0;
  }
  return ret;
}
#endif

int StringUtil::Printf(char* buf, char* last, const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int ret = VPrintf(buf, last, fmt, args);
	va_end(args);
	return ret;
}

std::string StringUtil::Format(const char* fmt, ...) {
	char sz[4096];
	va_list args;
	va_start(args, fmt);
	VPrintf(sz, sz + sizeof(sz) - 1, fmt, args);
	va_end(args);
	return sz;
}

std::vector<std::string> StringUtil::Split(const std::string &str, const std::string &delims, uint32_t max_splits) {
  std::vector<std::string> strs;
  if (str.empty())
    return strs;

  // Pre-allocate some space for performance
  strs.reserve(max_splits ? max_splits + 1 : 16);    // 16 is guessed capacity for most case

  uint32_t num_splits = 0;

  // Use STL methods
  size_t start, pos;
  start = 0;
  do {
    pos = str.find_first_of(delims, start);
    if (pos == start) {
      // Do nothing
      start = pos + 1;
    } else if (pos == std::string::npos || (max_splits && num_splits == max_splits)) {
      // Copy the rest of the string
      strs.push_back(str.substr(start));
      break;
    } else {
      // Copy up to delimiter
      strs.push_back(str.substr(start, pos - start));
      start = pos + 1;
    }
    // parse up to next real data
    start = str.find_first_not_of(delims, start);
    ++num_splits;
  } while (pos != std::string::npos);

  return strs;
}

NS_CC_END
