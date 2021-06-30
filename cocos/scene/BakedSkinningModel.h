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

#include <utility>

#include "scene/MorphModel.h"

namespace cc {
namespace scene {
struct BakedAnimInfo {
    gfx::Buffer *buffer{nullptr};
    uint8_t *    data;
    bool         dirty;
};
struct BakedJointInfo {
    std::vector<AABB *> boundsInfo;
    uint8_t *           jointTextureInfo;
    BakedAnimInfo       animInfo;
    gfx::Buffer *       buffer{nullptr};
};
class BakedSkinningModel : public MorphModel {
public:
    BakedSkinningModel()                           = default;
    BakedSkinningModel(const BakedSkinningModel &) = delete;
    BakedSkinningModel(BakedSkinningModel &&)      = delete;
    ~BakedSkinningModel() override                 = default;
    BakedSkinningModel &operator=(const BakedSkinningModel &) = delete;
    BakedSkinningModel &operator=(BakedSkinningModel &&) = delete;

    void        updateTransform(uint32_t stamp) override;
    void        updateUBOs(uint32_t stamp) override;
    inline void setJointMedium(bool isUploadAnim, BakedJointInfo jointMedium) {
        _isUploadAnim = isUploadAnim;
        _jointMedium  = std::move(jointMedium);
    }

private:
    BakedJointInfo _jointMedium;
    bool           _isUploadAnim = false;
};

} // namespace scene
} // namespace cc
