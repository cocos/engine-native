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

/// Singly-linked list node base class.
struct CC_DLL LinkedListNode {
    /// Construct.
    LinkedListNode() : _next(nullptr) {
    }

    /// Pointer to next node.
    LinkedListNode *_next;
};

/// Singly-linked list template class. Elements must inherit from LinkedListNode.
template <class T> class LinkedList {
public:
    /// Construct empty.
    LinkedList() : _head(nullptr) {
    }

     /// Destruct.
    ~LinkedList() {
        clear();
    }

    /// Remove all elements.
    void clear() const {
        T *element = _head;
        while (element) {
            T *next = next(element);
            if (next) {
                delete element;
            }
            element = next;
        }
    }

    /// Insert an element at the beginning.
    void insertFront(T *element) {
        if (element) {
            element->_next = _head;
            _head          = element;
        }
    }

    /// Insert an element at the end.
    void insert(T *element) {
        if (_head) {
            T *tail        = last();
            element->_next = tail->_next;
            tail->_next    = element;
        } else {
            element->_next = _head;
            _head          = element;
        }
    }

    /// Erase an element. Return true if successful.
    bool erase(T *element) {
        if (element && _head) {
            if (element == _head) {
                _head = next(element);
                delete element;
                return true;
            }

            T *tail = _head;
            while (tail && tail->_next != element)
                tail = next(tail);
            if (tail) {
                tail->_next = element->_next;
                delete element;
                return true;
            }
        }

        return false;
    }

    /// Erase an element when the previous element is known (optimization.) Return true if successful.
    bool erase(T *element, T *previous) {
        if (previous && previous->_next == element) {
            previous->_next = element->_next;
            delete element;
            return true;
        }

        if (!previous) {
            if (_head == element) {
                _head = next(element);
                delete element;
                return true;
            }
        }

        return false;
    }

    /// Return first element, or null if empty.
    T *first() const { return _head; }

    /// Return last element, or null if empty.
    T *last() const {
        T *element = _head;
        if (element) {
            while (element->_next)
                element = next(element);
        }
        return element;
    }

    /// Return next element, or null if no more elements.
    T *next(T *element) const { return element ? static_cast<T*>(element->_next) : nullptr; }

    /// Return whether is empty.
    bool empty() const { return _head == nullptr; }

private:
    /// First element.
    T *_head;
};

} // namespace container
} // namespace cc