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

#include "math/Mat4.h"
#include "math/Vec3.h"
#include "math/Quaternion.h"

namespace cc {
namespace scene {

class Node final {
public:
    Node()             = default;
    Node(const Node &) = delete;
    Node(Node &&)      = delete;
    ~Node()            = default;
    Node &operator=(const Node &) = delete;
    Node &operator=(Node &&) = delete;

    void updateWorldTransform();

    //TODO

private:
    uint32_t   layer{0};
    bool       _flagsChanges{false};
    bool       _dirtyFlags{false};
    bool       _hasChangeFlags{false};
    Node *     _parent{nullptr};
    Vec3       _lPos;
    Vec3       _lScale;
    Quaternion _lScale;
    Vec3       _pos;
    Quaternion _rot;
    Vec3       _scale;
    Mat4       _mat;
};

} // namespace scene
} // namespace cc
