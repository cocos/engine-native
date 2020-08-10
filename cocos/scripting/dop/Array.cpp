#include "Array.h"
#include "base/memory/Memory.h"
#include "base/Log.h"

// Data type of array element is uint32_t
#define BYTES_PER_ELEMENT 4

namespace se {

cc::map<uint, Array *> Array::_arrayMap;

Array *Array::getArray(uint index) {
    if (Array::_arrayMap.count(index) != 0)
        return Array::_arrayMap.at(index);
    else
        return nullptr;
}

Array::Array(uint index, uint size)
: _index(index), _size(adjustSize(size)) {
    uint bytes = _size * BYTES_PER_ELEMENT;
    _buffer = static_cast<uint8_t *>(CC_MALLOC(bytes));
    if (!_buffer)
        return;

    createJSObject(bytes);
    if (!_jsObj) {
        CC_FREE(_buffer);
        return;
    }

    Array::_arrayMap.emplace(_index, this);
}

Array::~Array() {
    destroyJSObject();
    CC_SAFE_FREE(_buffer);
    Array::_arrayMap.erase(_index);
}

Object *Array::resize(uint size) {
    if (!needToResize(size))
        return _jsObj;

    uint newBytes = (size + 1) * BYTES_PER_ELEMENT;
    uint8_t *tmpBuff = static_cast<uint8_t *>(CC_MALLOC(newBytes));
    if (!tmpBuff) {
        CC_LOG_ERROR("Can not resize array.");
        return _jsObj;
    }

    if (_buffer) {
        memcpy(tmpBuff, _buffer, _size * BYTES_PER_ELEMENT);
        std::swap(_buffer, tmpBuff);
        CC_FREE(tmpBuff);
    }

    _size = adjustSize(size);
    destroyJSObject();
    createJSObject(newBytes);

    return _jsObj;
}

void Array::createJSObject(uint bytes) {
    _jsObj = Object::createArrayBufferObject(_buffer, bytes);
    if (_jsObj) {
        _jsObj->root();
        _jsObj->incRef();
    }
}

void Array::destroyJSObject() {
    if (_jsObj) {
        _jsObj->decRef();
        _jsObj->unroot();
        _jsObj = nullptr;
    }
}

uint Array::adjustSize(uint size) const {
    // First element is the size of the array.
    return size + 1;
}

bool Array::needToResize(uint size) const {
    // First element is the size of the array. So if size == _size, need to resize.
    return size >= _size;
}

} // namespace se
