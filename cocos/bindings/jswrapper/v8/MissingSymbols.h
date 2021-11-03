#include <cstddef>
#include <cerrno>
#include <cstring>

#if SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_V8

//TODO(PatriceJiang): modify this when OHOS llvm upgrade
#if CC_PLATFORM == CC_PLATFORM_OHOS
extern "C" {
int local_bcmp(const void *cs, const void *ct, size_t count) {
return memcmp(cs, ct, count);
}
int bcmp(const void *cs, const void *ct, size_t count) __attribute__((weak, alias("local_bcmp")));
} // extern "C"
#endif


#if CC_PLATFORM == CC_PLATFORM_ANDROID
#if __ANDROID_API__ < 21
extern "C" {
int localSigemptyset(void *set) {
    if (set == NULL) { // NOLINT(modernize-use-nullptr)
        errno = EINVAL;
        return -1;
    }
    memset(set, 0, sizeof(unsigned long)); // NOLINT(google-runtime-int)
    return 0;
}

int sigemptyset(void *set) __attribute__((weak, alias("localSigemptyset")));
}
#endif
#endif
#endif // #if SCRIPT_ENGINE_TYPE == SCRIPT_ENGINE_V8