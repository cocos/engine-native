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

#include "Allocator.h"

namespace cc {
namespace container {
AllocatorBlock *AllocatorReserveBlock(AllocatorBlock *allocator, uint nodeSize, uint capacity) {
    if (!capacity) {
        capacity = 1;
    }

    auto *blockPtr           = new unsigned char[sizeof(AllocatorBlock) + capacity * (sizeof(AllocatorNode) + nodeSize)];
    auto *newBlock           = reinterpret_cast<AllocatorBlock *>(blockPtr);
    newBlock->_nodeSize      = nodeSize;
    newBlock->_capacity      = capacity;
    newBlock->_free          = nullptr;
    newBlock->_next          = nullptr;

    if (!allocator) {
        allocator = newBlock;
    }
    else {
        newBlock->_next  = allocator->_next;
        allocator->_next = newBlock;
    }

    // Initialize the nodes. Free nodes are always chained to the first (parent) allocator
    unsigned char *nodePtr      = blockPtr + sizeof(AllocatorBlock);
    auto *firstNewNode = reinterpret_cast<AllocatorNode *>(nodePtr);

    for (uint i = 0; i < capacity - 1; ++i) {
        auto *newNode = reinterpret_cast<AllocatorNode *>(nodePtr);
        newNode->_next         = reinterpret_cast<AllocatorNode *>(nodePtr + sizeof(AllocatorNode) + nodeSize);
        nodePtr += sizeof(AllocatorNode) + nodeSize;
    }
    auto *newNode = reinterpret_cast<AllocatorNode *>(nodePtr);
    newNode->_next         = nullptr;

    allocator->_free = firstNewNode;

    return newBlock;
}

AllocatorBlock *AllocatorInitialize(uint nodeSize, uint initialCapacity) {
    AllocatorBlock *block = AllocatorReserveBlock(nullptr, nodeSize, initialCapacity);
    return block;
}

void AllocatorUninitialize(AllocatorBlock *allocator) {
    while (allocator) {
        AllocatorBlock *next = allocator->_next;
        delete[] reinterpret_cast<unsigned char *>(allocator);
        allocator = next;
    }
}

void *AllocatorReserve(AllocatorBlock *allocator) {
    if (!allocator)
        return nullptr;

    if (!allocator->_free) {
        // Free nodes have been exhausted. Allocate a new larger block
        const uint newCapacity = (allocator->_capacity + 1) >> 1;
        AllocatorReserveBlock(allocator, allocator->_nodeSize, newCapacity);
        allocator->_capacity += newCapacity;
    }

    // We should have new free node(s) chained
    AllocatorNode *freeNode = allocator->_free;
    void *         ptr      = (reinterpret_cast<unsigned char *>(freeNode)) + sizeof(AllocatorNode);
    allocator->_free        = freeNode->_next;
    freeNode->_next         = nullptr;

    return ptr;
}

void AllocatorFree(AllocatorBlock *allocator, void *ptr) {
    if (!allocator || !ptr)
        return;

    auto *dataPtr = static_cast<unsigned char *>(ptr);
    auto *node    = reinterpret_cast<AllocatorNode *>(dataPtr - sizeof(AllocatorNode));

    // Chain the node back to free nodes
    node->_next      = allocator->_free;
    allocator->_free = node;
}

}// namespace container
}// namespace cc

