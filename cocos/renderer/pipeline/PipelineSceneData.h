/****************************************************************************
 Copyright (c) 2020-2021 Xiamen Yaji Software Co., Ltd.

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

#include "Define.h"
#include "scene/Define.h"
#include "scene/Light.h"
#include "scene/Sphere.h"

namespace cc {

namespace gfx {
class Framebuffer;
}

namespace pipeline {

class RenderPipeline;

class CC_DLL PipelineSceneData : public Object {
public:
    PipelineSceneData()           = default;
    ~PipelineSceneData() override = default;
    void activate(gfx::Device *device, RenderPipeline *pipeline);
    void setPipelineSharedSceneData(scene::PipelineSharedSceneData *data);
    void destroy();

    inline void                                                                setShadowFramebuffer(const scene::Light *light, gfx::Framebuffer *framebuffer) { _shadowFrameBufferMap.emplace(light, framebuffer); }
    inline const std::unordered_map<const scene::Light *, gfx::Framebuffer *> &getShadowFramebufferMap() const { return _shadowFrameBufferMap; }
    inline scene::PipelineSharedSceneData *                                    getSharedData() const { return _sharedSceneData; }
    inline const RenderObjectList &                                            getRenderObjects() const { return _renderObjects; }
    inline const RenderObjectList &                                            getShadowObjects() const { return _shadowObjects; }
    inline void                                                                setRenderObjects(RenderObjectList &&ro) { _renderObjects = std::forward<RenderObjectList>(ro); }
    inline void                                                                setShadowObjects(RenderObjectList &&ro) { _shadowObjects = std::forward<RenderObjectList>(ro); }
    inline scene::Sphere *                                                     getSphere() const { return _sphere; }
    inline scene::Sphere *                                                     getCameraBoundingSphere() const { return _cameraBoundingSphere; }
    inline scene::Frustum *                                                    getDirLightFrustum() const { return _dirLightFrustum; }
    inline scene::Frustum *                                                    getValidFrustum() const  { return _validFrustum; }
    inline scene::AABB *                                                       getCastBoundingBox() const { return _castBoundingBox; }

private:
    RenderObjectList _renderObjects;
    RenderObjectList _shadowObjects;

    scene::PipelineSharedSceneData *_sharedSceneData      = nullptr;
    RenderPipeline *                _pipeline             = nullptr;
    gfx::Device *                   _device               = nullptr;
    scene::Sphere *                 _sphere               = nullptr;
    scene::Sphere *                 _cameraBoundingSphere = nullptr;
    scene::Frustum *                _dirLightFrustum      = nullptr;
    scene::Frustum *                _validFrustum         = nullptr;
    scene::AABB *                   _castBoundingBox      = nullptr;

    std::unordered_map<const scene::Light *, gfx::Framebuffer *> _shadowFrameBufferMap;
};

} // namespace pipeline
} // namespace cc
