/****************************************************************************
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

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

#include "base/Macros.h"
#include "bindings/manual/jsb_conversions.h"
#include <vector>

namespace cc {
namespace physics {

struct TestStruct {
public:
    intptr_t ptr0;
	intptr_t state;
    static constexpr int DATA_COUNT = 3;
    TestStruct(intptr_t p, intptr_t s)
    : ptr0(p),
      state(s) {}

private:
    TestStruct() {}
};

class CC_DLL PhysXBindings final {
public:
    bool testAPI();
    static const int getPtr();
    static float getLength();
    static void modifyByPtr(int ptr, float x, float y, float z);
    static std::vector<float> &getArrayBuffer(uint32_t, float);
    static std::vector<TestStruct> &getTestStructVec();
};
} // namespace physics
} // namespace cc

template <>
inline bool nativevalue_to_se(const std::vector<cc::physics::TestStruct> &from, se::Value &to, se::Object *ctx) {
    se::Object *array = se::Object::createArrayObject(from.size() * cc::physics::TestStruct::DATA_COUNT);
    for (size_t i = 0; i < from.size(); i++) {
		uint32_t t = i * cc::physics::TestStruct::DATA_COUNT;
        array->setArrayElement(t + 0, se::Value(from[i].ptr0));
		array->setArrayElement(t + 1, se::Value((intptr_t)&from[i]));
		array->setArrayElement(t + 2, se::Value(from[i].state));
    }
    to.setObject(array);
    array->decRef();
    return true;
}
