/****************************************************************************
 Copyright (c) 2021 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#include "MemoryHook.h"
#if USE_MEMORY_LEAK_DETECTOR

#include "base/Log.h"
#include <sstream>


#if CC_PLATFORM == CC_PLATFORM_ANDROID
#define __GNU_SOURCE
#include <dlfcn.h>

#define likely_if(x)   if (__builtin_expect((x), 1))
#define unlikely_if(x) if (__builtin_expect((x), 0))

typedef void* (*MallocType)(size_t size);
typedef void  (*FreeType)(void* ptr);

typedef void (*NewHookType)(const void* ptr, size_t size);
typedef void (*DeleteHookType)(const void* ptr);

NewHookType g_new_hooker = nullptr;
DeleteHookType g_delete_hooker = nullptr;

extern "C" {
void* malloc(size_t __size) __attribute__ ((weak));
void free(void* ptr) __attribute__ ((weak));

void* malloc(size_t size) {
    static MallocType system_malloc = nullptr;
    unlikely_if(system_malloc == nullptr) {
        system_malloc = (MallocType)dlsym(RTLD_NEXT, "malloc");
    }

    void* ptr = system_malloc(size);
    likely_if(g_new_hooker != nullptr) {
        g_new_hooker(ptr, size);
    }

    return ptr;
}

void free(void* ptr) {
    static FreeType system_free = nullptr;
    unlikely_if(system_free == nullptr) {
        system_free = (FreeType)dlsym(RTLD_NEXT, "free");
    }

    system_free(ptr);
    likely_if(g_delete_hooker != nullptr) {
        g_delete_hooker(ptr);
    }
}

}

#elif CC_PLATFORM == CC_PLATFORM_MAC_IOS || CC_PLATFORM == CC_PLATFORM_MAC_OSX
typedef void (*NewHookType)(const void* ptr, size_t size);
typedef void (*DeleteHookType)(const void* ptr);

typedef void
malloc_logger_t(uint32_t aType,
                uintptr_t aArg1, uintptr_t aArg2, uintptr_t aArg3,
                uintptr_t aResult, uint32_t aNumHotFramesToSkip);
extern malloc_logger_t* malloc_logger;
static malloc_logger_t* g_default_malloc_logger;
NewHookType g_new_hooker = nullptr;
DeleteHookType g_delete_hooker = nullptr;

static void
cocos_malloc_logger(uint32_t aType,
                 uintptr_t aArg1, uintptr_t aArg2, uintptr_t aArg3,
                 uintptr_t aResult, uint32_t aNumHotFramesToSkip)
{
    // malloc/calloc/valloc/realloc
    if (aResult != 0) {
        if (g_new_hooker) {
            const void* ptr = reinterpret_cast<const void*>(aResult);
            size_t size = reinterpret_cast<size_t>(aArg2);
            g_new_hooker(ptr, size);
        }
    }
    // free
    else {
        if (g_delete_hooker) {
            const void* ptr = reinterpret_cast<const void*>(aArg2);
            g_delete_hooker(ptr);
        }
    }
}

#elif CC_PLATFORM == CC_PLATFORM_WINDOWS

extern "C" {
typedef void (*MallocHook_NewHook)(const void* ptr, size_t size);
typedef void (*MallocHook_DeleteHook)(const void* ptr);

int MallocHook_AddNewHook(MallocHook_NewHook hook);
int MallocHook_RemoveNewHook(MallocHook_NewHook hook);
int MallocHook_AddDeleteHook(MallocHook_DeleteHook hook);
int MallocHook_RemoveDeleteHook(MallocHook_DeleteHook hook);
}

#endif

namespace cc {

static void newHook(const void* ptr, size_t size) {
    uint64_t address = reinterpret_cast<uint64_t>(ptr);
    MemoryHook::getInstance()->addRecord(address, size);
}

static void deleteHook(const void* ptr) {
    uint64_t address = reinterpret_cast<uint64_t>(ptr);
    MemoryHook::getInstance()->removeRecord(address);
}

MemoryHook* MemoryHook::_instance = nullptr;

MemoryHook* MemoryHook::getInstance() {
    if (_instance == nullptr) {
        _instance = new MemoryHook();        
    }

    return _instance;
}

void MemoryHook::destroyInstance() {
    delete _instance;
    _instance = nullptr;
}

MemoryHook::MemoryHook() {
    registerAll();
}

MemoryHook::~MemoryHook() {
    unRegisterAll();
    dumpMemoryLeak();
}

void MemoryHook::addRecord(uint64_t address, size_t size) {
    std::lock_guard<std::recursive_mutex> lock(_mutex);
    if (_hooking) {
        return;
    }
  
    _hooking = true;

    // {} is necessary here to make variables being destroyed before _hooking = false
    {
        MemoryRecord record;
        record.address      = address;
        record.size         = size;
        record.callstack    = CallStack::backtrace();
        _records.insert({address, record});
    }
    
    _hooking = false;
}

void MemoryHook::removeRecord(uint64_t address) {
    std::lock_guard<std::recursive_mutex> lock(_mutex);
    if (_hooking) {
        return;
    }

    _hooking = true;

    // {} is necessary here to make variables being destroyed before _hooking = false
    {
        auto iter = _records.find(address);
        if (iter != _records.end()) {
            _records.erase(iter);
        }
    }

    _hooking = false;
}

void MemoryHook::dumpMemoryLeak() {
    std::lock_guard<std::recursive_mutex> lock(_mutex);
    
    std::stringstream startStream;
    startStream << std::endl;
    startStream << "---------------------------------------------------------------------------------------------------------" << std::endl;
    startStream << "--------------------------------------memory leak report start-------------------------------------------" << std::endl;
    startStream << "---------------------------------------------------------------------------------------------------------" << std::endl;
    CC_LOG_INFO("%s", startStream.str().c_str());

    if (_records.size() == 0) {
        std::stringstream stream;
        stream << std::endl;
        stream << "Congratulations! There is no memory leak at all." << std::endl;
        CC_LOG_INFO("%s", stream.str().c_str());
    }

    int i = 0;
    for (const auto& iter : _records) {
        std::stringstream stream;
        stream << std::endl;
        stream << "<" << ++i << ">:" << "leak " << iter.second.size 
            << " bytes at 0x" << std::hex << iter.second.address << std::dec << std::endl;
        stream << "\tcallstack:" << std::endl;
        auto frames = CallStack::backtraceSymbols(iter.second.callstack);
        int  k      = 0;
        for (auto& frame : frames) {
            stream << "\t[" << ++k << "]:" << frame.toString() << std::endl;
        }

        CC_LOG_INFO("%s", stream.str().c_str());
    }

    std::stringstream endStream;
    endStream << std::endl;
    endStream << "---------------------------------------------------------------------------------------------------------" << std::endl;
    endStream << "--------------------------------------memory leak report end---------------------------------------------" << std::endl;
    endStream << "---------------------------------------------------------------------------------------------------------" << std::endl;
    CC_LOG_INFO("%s", endStream.str().c_str());
}

void MemoryHook::registerAll() {
#if CC_PLATFORM == CC_PLATFORM_ANDROID
    g_new_hooker = newHook;
    g_delete_hooker = deleteHook;
#elif CC_PLATFORM == CC_PLATFORM_MAC_IOS || CC_PLATFORM == CC_PLATFORM_MAC_OSX
    g_default_malloc_logger = malloc_logger;
    malloc_logger = cocos_malloc_logger;
    g_new_hooker = newHook;
    g_delete_hooker = deleteHook;
#elif CC_PLATFORM_WINDOWS
    MallocHook_AddNewHook(&newHook);
    MallocHook_AddDeleteHook(&deleteHook);
#endif
}

void MemoryHook::unRegisterAll() {
#if CC_PLATFORM == CC_PLATFORM_ANDROID
    g_new_hooker = nullptr;
    g_delete_hooker = nullptr;
#elif CC_PLATFORM == CC_PLATFORM_MAC_IOS || CC_PLATFORM == CC_PLATFORM_MAC_OSX
    malloc_logger = g_default_malloc_logger;
    g_new_hooker = nullptr;
    g_delete_hooker = nullptr;
#elif CC_PLATFORM_WINDOWS
    MallocHook_RemoveNewHook(&newHook);
    MallocHook_RemoveDeleteHook(&deleteHook);
#endif
}

} // namespace cc

#endif
