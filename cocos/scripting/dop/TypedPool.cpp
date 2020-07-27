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

#include "TypedPool.h"
#include "base/ccMacros.h"
#include "base/memory/Memory.h"
#include "cocos/scripting/js-bindings/jswrapper/MappingUtils.h"

using namespace se;

template<class Type, size_t size>
TypedPool<Type, size>::TypedPool()
: _count(0)
, _jsObj(nullptr)
{
    size_t byteLength = sizeof(Type);
    for (size_t i = 0; i < size; ++i)
    {
        Type *obj = &_pool[i];
        Object *jsObj = Object::createArrayBufferObject(obj, byteLength);
        jsObj->root();
        jsObj->incRef();
        _jsObjs[i] = jsObj;
        _idHandles[i] = new IDHandle();
        _idHandles[i]->id = i;
    }
    
//    NonRefNativePtrCreatedByCtorMap::emplace(this);
}

template<class Type, size_t size>
TypedPool<Type, size>::~TypedPool()
{
    if (_jsObj)
    {
        _jsObj->decRef();
        _jsObj->unroot();
//        auto iter = NonRefNativePtrCreatedByCtorMap::find(this);
//        if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
//        {
//            NonRefNativePtrCreatedByCtorMap::erase(iter);
//        }
    }
    
    for (size_t i = 0; i < size; ++i)
    {
        Type *obj = &_pool[i];
        Object *jsObj = _jsObjs[i];
        jsObj->decRef();
        jsObj->unroot();
        _jsObjs[i] = nullptr;
        CC_SAFE_DELETE(_idHandles[i]);
        _idHandles[i] = nullptr;
    }
}

template<class Type, size_t size>
Type *TypedPool<Type, size>::getData(size_t id)
{
    return &_pool[id];
}

template<class Type, size_t size>
Type *TypedPool<Type, size>::getData(IDHandle *idHandle)
{
    return &_pool[idHandle->id];
}

template<class Type, size_t size>
Object *TypedPool<Type, size>::getArrayBuffer(size_t id)
{
    return _jsObjs[id];
}

template<class Type, size_t size>
Object *TypedPool<Type, size>::getArrayBuffer(IDHandle *idHandle)
{
    return _jsObjs[idHandle->id];
}

template<class Type, size_t size>
Object *TypedPool<Type, size>::getJSObject()
{
    return _jsObj;
}

template<class Type, size_t size>
void TypedPool<Type, size>::setJSObject(Object *jsObj)
{
    if (_jsObj)
    {
        _jsObj->setPrivateData(nullptr);
        _jsObj->decRef();
        _jsObj->unroot();
    }
    _jsObj = jsObj;
    _jsObj->root();
    _jsObj->incRef();
    _jsObj->setPrivateData(this);
}

template<class Type, size_t size>
IDHandle *TypedPool<Type, size>::alloc(SwapCallback swapCallback)
{
    IDHandle *handle = _idHandles[_count];
    handle->swapCallback = swapCallback;
    _count++;
    return handle;
}

template<class Type, size_t size>
bool TypedPool<Type, size>::free(IDHandle *handle)
{
    size_t freeId = handle->id;
    CCASSERT(freeId < _count, "Id is out of range of the allocated pool space");
    CCASSERT(handle == _idHandles[freeId], "The given handle doesn't match stored handle in the current pool, it might be from another pool or you are using an invalid handle");
    
    size_t swapId = _count - 1;
    size_t byteLength = sizeof(Type);
    // Copy the last data object to the freed location
    memcpy(&_pool[freeId], &_pool[swapId], byteLength);
    // Reset the swapped object
    memcpy(&_pool[swapId], &_defaultValue, byteLength);
    // free the old id handle
    CC_SAFE_DELETE(handle);
    // Swap the last data handle to the current place
    IDHandle *swapHandle = _idHandles[swapId];
    _idHandles[freeId] = swapHandle;
    _idHandles[swapId] = new IDHandle();
    _idHandles[swapId]->id = swapId;
    // Cound down to release
    _count--;
    
    // Call swap callback, useful when JS object need to switch to the correct TypedArray object
    swapHandle->swapCallback(swapId, freeId);
}
