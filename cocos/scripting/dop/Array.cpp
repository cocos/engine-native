#include "Array.h"
#include "base/memory/Memory.h"
#include "base/Log.h"

// Data type of array element is uint32_t
#define BYTES_PER_ELEMENT 4

namespace se {

cc::map<PoolType, cc::map<uint, uint8_t *>> ArrayPool::_arrayMap;

ArrayPool::ArrayPool(PoolType type, uint size)
: _type(type), _size(size) {
    ArrayPool::_arrayMap[_type] = {};
}

ArrayPool::~ArrayPool() {
    ArrayPool::_arrayMap.erase(_type);
}

Object *ArrayPool::alloc(uint index) {
    uint bytes = _size * BYTES_PER_ELEMENT;
    uint8_t *buffer = static_cast<uint8_t *>(CC_MALLOC(bytes));
    if (!buffer)
        return nullptr;

    auto obj = Object::createArrayBufferObject(buffer, bytes);
    CC_FREE(buffer);
    return obj;
}

Object *ArrayPool::resize(Object *origin, uint size) {
    uint bytes = size * BYTES_PER_ELEMENT;
    uint8_t *buffer = static_cast<uint8_t *>(CC_MALLOC(bytes));
    if (!buffer) {
        CC_LOG_ERROR("Can not resize array.");
        return origin;
    }

    uint8_t *originData = nullptr;
    size_t len = 0;
    origin->getTypedArrayData(&originData, &len);
    memcpy(buffer, originData, len);
    
    auto obj = Object::createArrayBufferObject(buffer, bytes);
    CC_FREE(buffer);
    return obj;
}

uint8_t *ArrayPool::getArray(PoolType type, uint index) {
    if (ArrayPool::_arrayMap.count(type) != 0) {
        const auto &arrays = ArrayPool::_arrayMap[type];
        if (arrays.count(index) != 0)
            return arrays.at(index);
        else
            return nullptr;
    } else {
        return nullptr;
    }
}

} // namespace se
