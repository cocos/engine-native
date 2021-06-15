/****************************************************************************
 Copyright (c) 2021 Xiamen Yaji Software Co., Ltd.
 
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

#include "math/Vec3.h"
#include "scene/Frustum.h"
#include "math/Quaternion.h"
#include "math/Mat3.h"
#include <algorithm>
using namespace cc;

namespace cc {
namespace scene {

struct AABB final {
    Vec3 center;
    Vec3 halfExtents;

    bool aabbAabb(const AABB &aabb) const;
    bool aabbFrustum(const Frustum &) const;
    int  aabbPlane(const Plane &) const;
    void getBoundary(cc::Vec3 *minPos, cc::Vec3 *maxPos) const;
    void merge(const AABB &aabb);
    void set(const cc::Vec3 &centerVal, const cc::Vec3 &halfExtentVal);
    void transform(const Mat4& m, AABB *out) const;
    static void fromPoints(const Vec3& minPos, const Vec3& maxPos, AABB* dst);
};

} // namespace scene
} // namespace cc
