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

#include "RefCounted.h"
#include "base/memory/Memory.h"

namespace cc {
namespace container {
RefCounted::RefCounted() :
    _refCount(CC_NEW(RefCount)) {

    // Hold a weak ref to self to avoid possible double delete of the refcount
    _refCount->_weakRefs++;
}

RefCounted::~RefCounted() {
    GP_ASSERT(_refCount);
    GP_ASSERT(_refCount->_refs == 0);
    GP_ASSERT(_refCount->_weakRefs > 0);

    // Mark object as expired, release the self weak ref and delete the refcount if no other weak refs exist
    _refCount->_refs = -1;
    _refCount->_weakRefs--;
    if (!_refCount->_weakRefs) {
        CC_SAFE_DELETE(_refCount);
    }
}

void RefCounted::addRef() const {
    GP_ASSERT(_refCount->_refs >= 0);
    _refCount->_refs++;
}

void RefCounted::releaseRef() const {
    GP_ASSERT(_refCount->_refs > 0);
    _refCount->_refs--;
    if (!_refCount->_refs) {
        delete this;
    }
}

} // namespace container
} // namespace cc
