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

#include <cstdint>
#include "renderer/gfx-base/GFXDef-common.h"
#include "renderer/gfx-base/GFXDescriptorSet.h"
#include "renderer/gfx-base/GFXBuffer.h"
#include "scene/Define.h"

namespace cc {
namespace scene {

class Pass final {
public:
    Pass()             = default;
    Pass(const Pass &) = delete;
    Pass(Pass &&)      = delete;
    ~Pass()            = default;
    Pass &operator=(const Pass &) = delete;
    Pass &operator=(Pass &&) = delete;

    void update();

private:
    bool                     _rootBufferDirty{false};
    uint32_t                 _phase{0};
    // FIXME: is uint32_t enough?
    uint32_t                 _hash{0};
    RenderPriority           _priority{RenderPriority::DEFAULT};
    RenderPassStage          _stage{RenderPassStage::DEFAULT};
    gfx::PrimitiveMode       _primitive{gfx::PrimitiveMode::TRIANGLE_LIST};
    gfx::DynamicStateFlagBit _dynamicStates{gfx::DynamicStateFlagBit::NONE};
    gfx::RasterizerState *   _rasterizerState{nullptr};
    gfx::DepthStencilState * _depthStencilState{nullptr};
    gfx::BlendState *        _blendState{nullptr};
    gfx::DescriptorSet *     _descriptorSet{nullptr};
    gfx::PipelineLayout *    _pipelineLayout{nullptr};
    gfx::Buffer *            _rootBuffer{nullptr};
    // TODO(minggo): rootBlock
};

} // namespace scene
} // namespace cc
