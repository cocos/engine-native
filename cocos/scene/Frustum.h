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

#include <array>
#include "math/Vec3.h"
#include <vector>

namespace cc {
namespace scene {

struct Plane final {
    float d{0.F};
    Vec3  n;
};

const std::vector<cc::Vec3*> _vecVal{
    new cc::Vec3(1, 1, 1),
    new cc::Vec3(-1, 1, 1),
    new cc::Vec3(-1, -1, 1),
    new cc::Vec3(1, -1, 1),
    new cc::Vec3(1, 1, -1),
    new cc::Vec3(-1, 1, -1),
    new cc::Vec3(-1, -1, -1),
    new cc::Vec3(1, -1, -1)};

struct Frustum final {
    std::array<Vec3, 8>  vertices;
    std::array<Plane, 6> planes;
    
    int getType() {
        return 1 << 8;
    }

    void update(Mat4 m, Mat4 inv) {
        // left plane
        planes[0].n.set(m.m[3] + m.m[0], m.m[7] + m.m[4], m.m[11] + m.m[8]);
        planes[0].d = -(m.m[15] + m.m[12]);
        // right plane
        planes[1].n.set(m.m[3] - m.m[0], m.m[7] - m.m[4], m.m[11] - m.m[8]);
        planes[1].d = -(m.m[15] - m.m[12]);
        // bottom plane
        planes[2].n.set(m.m[3] + m.m[1], m.m[7] + m.m[5], m.m[11] + m.m[9]);
        planes[2].d = -(m.m[15] - m.m[12]);
        // top plane
        planes[3].n.set(m.m[3] - m.m[1], m.m[7] - m.m[5], m.m[11] - m.m[9]);
        planes[3].d = -(m.m[15] - m.m[13]);
        // near plane
        planes[4].n.set(m.m[3] + m.m[2], m.m[7] + m.m[6], m.m[11] + m.m[10]);
        planes[4].d = -(m.m[15] + m.m[14]);
        // far plane
        planes[5].n.set(m.m[3] - m.m[2], m.m[7] - m.m[6], m.m[11] - m.m[10]);
        planes[5].d = -(m.m[15] - m.m[14]);
        
        for (Plane &plane: planes) {
            int invDist = 1 / plane.n.length();
            plane.n *= invDist;
            plane.d *= invDist;
        }
        for (int i = 0; i < 8; i++) {
            vertices[i].transformMat4(*_vecVal[i], inv);
        }
    }
    
};

} // namespace scene
} // namespace cc
