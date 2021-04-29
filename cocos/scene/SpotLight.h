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

#include "scene/RenderScene.h"

namespace cc {
namespace scene {

class SpotLight : public Light {
public:
    SpotLight()                  = default;
    SpotLight(const SpotLight &) = delete;
    SpotLight(SpotLight &&)      = delete;
    ~SpotLight() override        = default;
    SpotLight &operator=(const SpotLight &) = delete;
    SpotLight &operator=(SpotLight &&) = delete;

    void update();

    void setAABB(AABB);
    void setAngle(float);
    void setAspect(float);
    void setDir(Vec3 dir);
    void setFrustum(Frustum);
    void setIlluminace(float);
    void setNeedUpdate(bool);
    void setRange(float);
    void setPos(Vec3);
    void setSize(float);

    inline const const AABB &getAABB() const { return _aabb; }
    inline float             getAngle() const { return _angle; }
    inline float             getAspect() const { return _aspect; }
    inline const const Vec3 &getDir() const { return _dir; }
    inline const Frustum &   getFrustum() const { return _frustum; }
    inline float             getIlluminance() const { return _illuminance; }
    inline bool              getNeedUpdate() const { return _needUpdate; }
    inline float             getRange() const { return _range; }
    inline const Vec3 &      getPos() const { return _pos; }
    inline float             getSize() const { return _size; }

private:
    bool    _needUpdate{false};
    float   _illuminance{0.f};
    float   _range{0.f};
    float   _size{0.f};
    float   _angle{0.f};
    float   _aspect{0.f};
    Vec3    _dir;
    Vec3    _pos;
    AABB    _aabb;
    Frustum _frustum;
};

} // namespace scene
} // namespace cc
