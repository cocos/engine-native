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

#include <vector>
#include "renderer/gfx-base/GFXBuffer.h"
#include "scene/AABB.h"

namespace cc {
namespace scene {

class Node;
class SubModel;

class Model final {
public:
    Model()              = default;
    Model(const Model &) = delete;
    Model(Model &&)      = delete;
    ~Model()             = default;
    Model &operator=(const Model &) = delete;
    Model &operator=(Model &&) = delete;

    void updateTransform();
    void updateUBOs();

    //TODO

private:
    bool                    _dirtyFlags{false};
    bool                    _enabled{false};
    bool                    _castShadow{false};
    bool                    _receiveShadow{false};
    bool                    _transformUpdated{false};
    uint32_t                _instmatWorldIdx{0};
    uint32_t                _visFlags;
    uint32_t                _updateStamp{0};
    Node *                  _transform{nullptr};
    uint8_t *               _localData{nullptr};
    gfx::Buffer *           _instanceBuffer{nullptr};
    gfx::Buffer *           _localBuffer{nullptr};
    AABB                    _worldBounds;
    AABB                    _modelBounds;
    std::vector<SubModel *> _subModels;
    // TODO _instanceAttributes
};

} // namespace scene
} // namespace cc
