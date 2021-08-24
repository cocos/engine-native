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

#include "base/Macros.h"
#include "base/TypeDef.h"

namespace cc {
namespace container {

struct AllocatorBlock;
struct AllocatorNode;

/// %Allocator memory block.
struct AllocatorBlock {
    /// Size of a node.
    uint _nodeSize;
    /// Number of nodes in this block.
    uint _capacity;
    /// First free node.
    AllocatorNode *_free;
    /// Next allocator block.
    AllocatorBlock *_next;
};

/// %Allocator node.
struct AllocatorNode {
    /// Next free node.
    AllocatorNode* _next;
};

/// Initialize a fixed-size allocator with the node size and initial capacity.
CC_DLL AllocatorBlock *AllocatorInitialize(unsigned nodeSize, unsigned initialCapacity = 1);
/// Uninitialize a fixed-size allocator. Frees all blocks in the chain.
CC_DLL void AllocatorUninitialize(AllocatorBlock *allocator);
/// Reserve a node. Creates a new block if necessary.
CC_DLL void* AllocatorReserve(AllocatorBlock *allocator);
/// Free a node. Does not free any blocks.
CC_DLL void AllocatorFree(AllocatorBlock *allocator, void *ptr);

/// %Allocator template class. Allocates objects of a specific class.
template <class T> class Allocator {
public:
    /// Construct.
    Allocator(uint initialCapacity = 0) : _allocator(nullptr) {
        if (initialCapacity > 0)
            _allocator = AllocatorInitialize(static_cast<uint>(sizeof(T)), initialCapacity);
    }

    /// Destruct.
    ~Allocator() {
        AllocatorUninitialize(_allocator);
    }

    /// Reserve and default-construct an object.
    T *Reserve() {
        if (!_allocator) {
            _allocator = AllocatorInitialize(static_cast<uint>(sizeof(T)));
        }

        T *newObject = static_cast<T *>(AllocatorReserve(_allocator));
        new (newObject) T();

        return newObject;
    }

     /// Reserve and copy-construct an object.
    T *Reserve(const T &object) {
        if (!_allocator) {
            _allocator = AllocatorInitialize(static_cast<uint>(sizeof(T)));
        }

        T *newObject = static_cast<T *>(AllocatorReserve(_allocator));
        new (newObject) T(object);

        return newObject;
    }

    /// Destruct and free an object.
    void Free(T *object) {
        (object)->~T();
        AllocatorFree(_allocator, object);
    }

private:
    /// Prevent copy construction.
    Allocator(const Allocator<T> &rhs) = delete;
    /// Prevent assignment.
    Allocator<T> &operator=(const Allocator<T> &rhs) = delete;
    /// Allocator block.
    Allocator *_allocator;
};

} // namespace container
} // namespace cc
