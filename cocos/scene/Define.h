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

#include "math/Vec4.h"
#include "math/Vec3.h"
#include "math/Vec2.h"
#include "math/Mat4.h"
#include "scene/Model.h"
#include "renderer/gfx-base/GFXShader.h"

namespace cc {
namespace scene {

// As Pass.h will include Define.h, so use forward declaration.
class Pass;

struct Fog {
    bool     enabled{false};
    uint32_t type{0};
    float    density{0};
    float    start{0};
    float    end{0};
    float    atten{0};
    float    top{0};
    float    range{0};
    Vec4     color;
};

struct Shadow {
    bool     enabled{false};
    bool     dirty{false};
    bool     shadowMapDirty{false};
    bool     selfShadow{false};
    bool     autoAdapt{false};
    uint32_t shadowType{0};
    float    distance{0};
    uint32_t instancePass{0};
    uint32_t planarPass{0};
    float    nearValue{0};
    float    farValue{0};
    float    aspect{0};
    uint32_t pcfType{0};
    float    bias{0};
    uint32_t packing{0};
    uint32_t linear{0};
    float    normalBias{0};
    float    orthoSize{0};

    Vec4 color;
    Vec2 size;
    Vec3 normal;
    Mat4 matLight;
};

struct SkyBox {
    bool   enabled{false};
    bool   isRGBE{false};
    bool   useIBL{false};
    Model *model{nullptr};
};

struct PipelineSharedSceneData {
    bool         isHDR{false};
    uint32_t     shadingScale{0};
    uint32_t     fpScale{0};
    uint32_t     ambient{0};
    Shadow *     shadow{nullptr};
    SkyBox *     skybox{nullptr};
    Fog *        fog{nullptr};
    Pass *       deferredLightPass{nullptr};
    gfx::Shader *deferredLightPassShader{nullptr};
    Pass *       deferredPostPass{nullptr};
    gfx::Shader *deferredPostPassShader{nullptr};
};

// TODO(mingo)
struct RenderingSubMesh {
    uint32_t flatBuffersID = 0; // array pool id
};

enum class RenderPriority {
    MIN     = 0,
    MAX     = 0xff,
    DEFAULT = 0x80,
};

enum class RenderPassStage {
    DEFAULT = 100,
    UI      = 200,
};

enum class BatchingSchemes {
    INSTANCING = 1,
    VB_MERGING = 2,
};

} // namespace scene
} // namespace cc
