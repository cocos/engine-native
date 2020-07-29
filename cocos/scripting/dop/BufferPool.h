/****************************************************************************
Copyright (c) 2020 Xiamen Yaji Software Co., Ltd.

http://www.cocos.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#pragma once

#include <vector>
#include "cocos/scripting/js-bindings/jswrapper/Object.h"
#include "cocos/base/ccMacros.h"

namespace se {

class CC_DLL BufferPool {
public:
    using Chunk = uint8_t*;
    
    BufferPool(size_t bytesPerEntry, size_t entryBits);
    ~BufferPool();
    void *getData(size_t id);
    template<class Type>
    Type *getTypedObject(size_t id);
    
    Object *getChunkArrayBuffer(size_t chunkId);
protected:
    std::vector<Chunk> _chunks;
    std::vector<Object*> _jsObjs;
    std::vector<size_t> _sizes;
    uint32_t _entryBits;
    size_t _bytesPerChunk;
    size_t _entiesPerChunk;
    size_t _bytesPerEntry;
    uint32_t _chunkMask;
    uint32_t _entryMask;
};

} // namespace se {
