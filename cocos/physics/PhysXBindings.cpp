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

#ifndef __PHYSX_BINDINGS_H__
#define __PHYSX_BINDINGS_H__

#include "./PhysXBindings.h"
#include "./PhysX/PhysXInc.h"
#include <stdlib.h>

namespace cc {
namespace physics {
bool PhysXBindings::testAPI() {
    return true;
}

physx::PxVec3 *gPXv3 = new physx::PxVec3();
float PhysXBindings::getLength() {
    return gPXv3->magnitude();
}

const int PhysXBindings::getPtr() {
    return int(gPXv3);
}

void PhysXBindings::modifyByPtr(int ptr, float x, float y, float z) {
    auto v3 = (physx::PxVec3 *)ptr;
    v3->x = x;
    v3->y = y;
    v3->z = z;
}

std::vector<float> &PhysXBindings::getArrayBuffer(uint32_t size, float val) {
    static std::vector<float> vec;
    vec.resize(size, val);
    return vec;
}

std::vector<TestStruct> &PhysXBindings::getTestStructVec() {
    static std::vector<TestStruct> vec;
    vec.push_back(TestStruct{(intptr_t)&vec, (intptr_t)vec.size()});
    return vec;
}

void PhysXBindings::setTestStruct(TestStruct &ts, size_t i) {
    auto &tsv = getTestStructVec();
    if (i >= 0 && tsv.size() > i) {
        tsv[i] = ts;
    }
}

TestResult &PhysXBindings::getTestResult() {
    static TestResult ts;
    ts = TestResult{rand() * 0.1f};
    return ts;
}

std::vector<TestResult> &PhysXBindings::getTestResultVec() {
    static std::vector<TestResult> vec;
    vec.push_back(TestResult{rand() * 0.1f});
    return vec;
}

} // namespace physics
} // namespace cc

#endif