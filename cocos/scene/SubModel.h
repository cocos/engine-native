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
#include "renderer/gfx-base/GFXShader.h"
#include "renderer/gfx-base/GFXDescriptorSet.h"
#include "renderer/gfx-base/GFXInputAssembler.h"
#include "scene/Define.h"

namespace cc {
namespace scene {

class Pass;

class SubModel final {
public:
    SubModel()                 = default;
    SubModel(const SubModel &) = delete;
    SubModel(SubModel &&)      = delete;
    ~SubModel()                = default;
    SubModel &operator=(const SubModel &) = delete;
    SubModel &operator=(SubModel &&) = delete;

    void update();

    const Pass *getPass(int) const;

    inline gfx::DescriptorSet *getDescriptorSet() const { return _descriptSet; }
    inline gfx::InputAssembler *getInputAssembler() const { return _ia; }
    inline RenderingSubMesh *getSubMesh() const { return _subMesh; }

private:
    RenderPriority       _priority{RenderPriority::DEFAULT};
    gfx::Shader *        _planarShader{nullptr};
    gfx::Shader *        _planarInstanceShader{nullptr};
    gfx::DescriptorSet * _descriptSet{nullptr};
    gfx::InputAssembler *_ia{nullptr};
    RenderingSubMesh *   _subMesh{nullptr};
    std::vector<Pass *>  _passes;
};

} // namespace scene
} // namespace cc
