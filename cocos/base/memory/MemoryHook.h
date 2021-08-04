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

#pragma once

#include "../Config.h"
#if USE_MEMORY_LEAK_DETECTOR

#include "../Macros.h"
#include "CallStack.h"

#include <unordered_map>
#include <vector>
#include <mutex>

namespace cc {


struct CC_DLL MemoryRecord {
    uint64_t            address{0};
    size_t              size{0};
    std::vector<void*>  callstack;
};

class CC_DLL MemoryHook {
public:
    /**
     *  @brief Gets or creates the instance of MemoryHook.
     *  @return The MemoryHook instance.
     */
    static MemoryHook* getInstance();

    /**
     *  @brief Destroys the instance of MemoryHook.
     */
    static void destroyInstance();

    /**
     * RecordMap's key is memory address.
     */
    using RecordMap = std::unordered_map<uint64_t, MemoryRecord>;

    void addRecord(uint64_t address, size_t size);
    void removeRecord(uint64_t address);

    /**
     * Dump all memory leaks to output window
     */
    void dumpMemoryLeak();

private:
    MemoryHook();
    ~MemoryHook();

    /**
     * Register all malloc hooks
     */
    void registerAll();

    /**
     * Unregister all malloc hooks
     */
    void unRegisterAll();

private:
    static MemoryHook*   _instance;
    std::recursive_mutex _mutex;
    bool                 _hooking;
    RecordMap            _records;
};

class MemoryHookGuard {
public:
    MemoryHookGuard() {
        MemoryHook::getInstance();
    }

    ~MemoryHookGuard() {
        MemoryHook::destroyInstance();
    }

    MemoryHookGuard(const MemoryHookGuard&) = delete;
    MemoryHookGuard(MemoryHookGuard&&) = delete;
    MemoryHookGuard& operator=(const MemoryHookGuard&) = delete;
    MemoryHookGuard& operator=(MemoryHookGuard&&) = delete;
};

} // namespace cc

#endif
