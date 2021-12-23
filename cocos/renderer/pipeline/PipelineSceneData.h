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
#include "core/geometry/Sphere.h"
#include "gfx-base/GFXBuffer.h"
#include "scene/Ambient.h"
#include "scene/Fog.h"
#include "scene/Light.h"
#include "scene/Pass.h"
#include "scene/Shadow.h"
#include "scene/Skybox.h"

namespace cc {

namespace gfx {
class Framebuffer;
}

namespace pipeline {

class RenderPipeline;

class CC_DLL PipelineSceneData : public Object {
public:
    PipelineSceneData();
    ~PipelineSceneData();
    virtual void activate(gfx::Device *device, RenderPipeline *pipeline);
    void         destroy();

    inline void                                                                setShadowFramebuffer(const scene::Light *light, gfx::Framebuffer *framebuffer) { _shadowFrameBufferMap.emplace(light, framebuffer); }
    inline const std::unordered_map<const scene::Light *, gfx::Framebuffer *> &getShadowFramebufferMap() const { return _shadowFrameBufferMap; }
    inline scene::PipelineSharedSceneData *                                    getSharedData() const { return _sharedSceneData; }
    inline const RenderObjectList &                                            getRenderObjects() const { return _renderObjects; }
    inline const RenderObjectList &                                            getDirShadowObjects() const { return _dirShadowObjects; }
    inline void                                                                setRenderObjects(RenderObjectList &&ro) { _renderObjects = std::forward<RenderObjectList>(ro); }
    inline void                                                                setDirShadowObjects(RenderObjectList &&ro) { _dirShadowObjects = std::forward<RenderObjectList>(ro); }
    inline const RenderObjectList &                                            getCastShadowObjects() const { return _castShadowObjects; }
    inline void                                                                setCastShadowObjects(RenderObjectList &&ro) { _castShadowObjects = std::forward<RenderObjectList>(ro); }
    inline const vector<const scene::Light *> &                                getValidPunctualLights() const { return _validPunctualLights; }
    inline void                                                                setValidPunctualLights(vector<const scene::Light *> &&validPunctualLights) { _validPunctualLights = std::forward<vector<const scene::Light *>>(validPunctualLights); }
    inline float                                                               getShadowCameraFar() const { return _shadowCameraFar; }
    inline void                                                                setShadowCameraFar(float shadowDistance) { _shadowCameraFar = shadowDistance; }
    inline Mat4                                                                getMatShadowView() const { return _matShadowView; }
    inline void                                                                setMatShadowView(const Mat4 &matShadowView) { _matShadowView = matShadowView; }
    inline Mat4                                                                getMatShadowProj() const { return _matShadowProj; }
    inline void                                                                setMatShadowProj(const Mat4 &matShadowProj) { _matShadowProj = matShadowProj; }
    inline Mat4                                                                getMatShadowViewProj() const { return _matShadowViewProj; }
    inline void                                                                setMatShadowViewProj(const Mat4 &matShadowViewProj) { _matShadowViewProj = matShadowViewProj; }
    inline bool                                                                isHDR() const { return _isHDR; }
    inline scene::Shadows *                                                    getShadow() { return _shadow; }

    inline scene::Pass *getOcclusionQueryPass();

private:
    void                 _initOcclusionQuery();
    gfx::InputAssembler *_createOcclusionQueryIA();

private:
    RenderObjectList             _renderObjects;
    RenderObjectList             _dirShadowObjects;
    RenderObjectList             _castShadowObjects;
    vector<const scene::Light *> _validPunctualLights;
    gfx::Buffer *                _occlusionQueryVertexBuffer{nullptr};
    gfx::Buffer *                _occlusionQueryIndicesBuffer{nullptr};
    gfx::InputAssembler *        _occlusionQueryInputAssembler{nullptr};

    cc::Material *_occlusionQueryMaterial{nullptr};
    gfx::Shader * _occlusionQueryShader{nullptr};

    scene::PipelineSharedSceneData *_sharedSceneData{nullptr};
    RenderPipeline *                _pipeline{nullptr};
    gfx::Device *                   _device{nullptr};
    float                           _shadowCameraFar{0.0F};
    Mat4                            _matShadowView;
    Mat4                            _matShadowProj;
    Mat4                            _matShadowViewProj;

    geometry::Sphere *_sphere{nullptr};
    scene::Fog *      _fog{nullptr};
    scene::Ambient *  _ambient{nullptr};
    scene::Skybox *   _skybox{nullptr};
    scene::Shadows *  _shadow{nullptr};
    bool              _isHDR{false};
    float             _shadingScale{1.0F};
    float             _fpScale{1.0F / 1024.F};

    std::unordered_map<const scene::Light *, gfx::Framebuffer *> _shadowFrameBufferMap;
};

} // namespace pipeline
} // namespace cc
