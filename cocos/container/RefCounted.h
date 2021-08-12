/****************************************************************************
 Copyright (c) 2020-2021 Xiamen Yaji Software Co., Ltd.

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

#include "../base/Macros.h"

namespace cc {
namespace container {

/// Reference count structure.
struct RefCount {
    RefCount() : _refs(0),
                 _weakRefs(0) {
    }

    ~RefCount() {
        // Set reference counts below zero to fire asserts if this object is still accessed
        _refs     = -1;
        _weakRefs = -1;
    }

    /// Reference count. If below zero, the object has been destroyed.
    int _refs;

    /// Weak reference count.
    int _weakRefs;
};

/// Base class for intrusively reference-counted objects. These are noncopyable and non-assignable.
class CC_DLL RefCounted {
public:
    /// Allocate the reference count structure and set an initial self weak reference.
    RefCounted();

    virtual ~RefCounted();

    /// Increment reference count. Can also be called outside of a SharedPtr for traditional reference counting.
    void addRef() const;

    /// Decrement reference count and delete self if no more references. Can also be called outside of a SharedPtr for traditional reference counting.
    void releaseRef() const;

    /// Return reference count.
    inline int refs() const { return _refCount->_refs; };

    /// Return weak reference count.Subtract one to not return the internally held reference.
    inline int weakRefs() const { return _refCount->_weakRefs - 1; }

    /// Return pointer to the reference count structure.
    inline RefCount* refCountPtr() const { return _refCount; }

private:
    /// Prevent copy construction.
    RefCounted(const RefCounted& rhs) = delete;

    /// Prevent assignment.
    RefCounted& operator= (const RefCounted& rhs) = delete;

    /// Pointer to the reference count structure.
    RefCount* _refCount;
};

} // namespace container
} // namespace cc
