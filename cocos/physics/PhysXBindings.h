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

    TestStruct() {}

private:
};

struct TestResult {
    cc::Vec3 hitPoint;
    float distance;
    cc::Vec3 hitNormal;
    TestResult() {}
    TestResult(float rand) : distance(rand) {}
};

class CC_DLL PhysXBindings final {
public:
    bool testAPI();
    static const int getPtr();
    static float getLength();
    static void modifyByPtr(int ptr, float x, float y, float z);
    static std::vector<float> &getArrayBuffer(uint32_t, float);
    static std::vector<TestStruct> &getTestStructVec();
    static void setTestStruct(TestStruct &, size_t);
    static TestResult &getTestResult();
    static std::vector<TestResult> &getTestResultVec();
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

template <>
inline bool nativevalue_to_se(const cc::physics::TestResult &from, se::Value &to, se::Object *ctx) {
    se::HandleObject obj(se::Object::createPlainObject());
    obj->setProperty("distance", se::Value(from.distance));
    se::Value obj0;
    if (nativevalue_to_se(from.hitPoint, obj0, ctx)) {
        obj->setProperty("hitPoint", obj0);
    }
    if (nativevalue_to_se(from.hitNormal, obj0, ctx)) {
        obj->setProperty("hitNormal", obj0);
    }
	to.setObject(obj);
    return true;
}

template <>
inline bool sevalue_to_native(const se::Value &from, cc::physics::TestStruct *to, se::Object *ctx) {
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto *data = (cc::physics::TestStruct *)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("ptr0", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->ptr0), ctx);
    }
    json->getProperty("state", &field);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->state), ctx);
    }
    return ok;
}