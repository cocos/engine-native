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

#include <array>
#include "cocos/scripting/js-bindings/jswrapper/Object.h"
#include "cocos/base/ccMacros.h"

namespace se {

typedef void (*SwapCallback)(uint32_t oldId, uint32_t newId);

struct IDHandle {
    uint32_t id;
    SwapCallback swapCallback;
};

template<class Type, size_t pageSize>
class CC_DLL TypedPool {
public:
    using Page = std::array<Type, pageSize>;
//    using FreeList =
    
    TypedPool();
    ~TypedPool();
    Type *getData(size_t id);
    Type *getData(IDHandle *idHandle);
    Object *getArrayBuffer(size_t id);
    Object *getArrayBuffer(IDHandle *idHandle);
    
    void setJSObject(Object *jsObj);
    Object *getJSObject();
    
    IDHandle *alloc(SwapCallback swapCallback);
    bool free(IDHandle *handle);
protected:
//    std::vector<Page *> _pages;
    std::array<Type, pageSize> _pool;
    std::array<IDHandle*, pageSize> _idHandles;
    std::array<Object*, pageSize> _jsObjs;
    Type _defaultValue;
    Object* _jsObj;
    size_t _count;
};

} // namespace se {
