#pragma once

#include "cocos/base/Object.h"
#include "cocos/scripting/js-bindings/jswrapper/Object.h"
#include "cocos/base/memory/StlAlloc.h"
#include "cocos/base/ccMacros.h"
#include "cocos/base/TypeDef.h"
#include "PoolType.h"

namespace se {

class CC_DLL Array final : public cc::Object {
public:
    static Array *getArray(uint index);
    
    Array(uint index, uint size);
    ~Array();

    Object *resize(uint size);
    CC_INLINE Object *getJSArray() const { return _jsObj; }

private:
    void createJSObject(uint bytes);
    void destroyJSObject();

private:
    static cc::map<uint, Array *> _arrayMap;

    Object *_jsObj = nullptr;
    uint8_t *_buffer = nullptr;
    uint _index = UINT_MAX;
    uint _size = 0;
};

} // namespace se
