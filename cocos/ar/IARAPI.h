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

#include "base/Log.h"

#define CC_ARAPI_DEBUG
#ifdef  CC_ARAPI_DEBUG
#define DLLOG(...)      CC_LOG_DEBUG(__VA_ARGS__)
#else
#define DLLOG(...)       do {} while (0)
#endif

namespace cc {
namespace ar{

using Pose = std::array<float, 7>;
using Matrix = std::array<float, 16>;
using TexCoords = std::array<float, 8>;

class IARAPI {
public:
    virtual ~IARAPI() = default;
    virtual void start() = 0;
    virtual void resume() = 0;
    virtual void pause() = 0;
    virtual void beforeUpdate() {}
    virtual void update() = 0;
    virtual int getAPIState() = 0;

    virtual float* getCameraPose() = 0;
    virtual float* getCameraViewMatrix() = 0;
    virtual float* getCameraProjectionMatrix() = 0;
    virtual float* getCameraTexCoords() = 0;
    virtual void setCameraTextureName(int id) = 0;
    virtual void* getCameraTextureRef() = 0;

    //virtual void setPlaneFeatureEnable(bool isOn) = 0;
    virtual int getAddedPlanesCount() = 0;
    virtual int getRemovedPlanesCount() = 0;
    virtual int getUpdatedPlanesCount() = 0;
    virtual void updatePlanesInfo() = 0;
    virtual float* getAddedPlanesInfo() = 0;
    virtual unsigned long* getRemovedPlanesInfo() = 0;
    virtual float* getUpdatedPlanesInfo() = 0;
    virtual int getInfoLength() {}
};

} // namespace ar
} // namespace cc
