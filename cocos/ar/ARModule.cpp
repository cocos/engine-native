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

#include <memory>

#include "ar/ARModule.h"

#if CC_PLATFORM == CC_PLATFORM_ANDROID
#include "ar/android/ARAndroidAPIImpl.h"
using ARAPIImpl = cc::ar::ARAndroidAPIImpl;
#elif CC_PLATFORM == CC_PLATFORM_MAC_IOS
#include "ar/ios/ARKitAPIImpl.h"
using ARAPIImpl = cc::ar::ARKitAPIImpl;
#elif CC_PLATFORM == CC_PLATFORM_WINDOWS
#include "ar/IARAPI.h"
#endif

#include  "bindings/jswrapper/SeApi.h"

namespace cc {
namespace ar {

ARModule::ARModule() {
#if CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_MAC_IOS
    _impl = std::make_unique<ARAPIImpl>();
    arModuleInstance.reset(this);
#endif
}

ARModule::~ARModule()
{
    DLLOG("Destruct ARModule %p", this);
}

// jsb skip
ARModule* ARModule::get() {
    return arModuleInstance.get();
}

void ARModule::start() {
    _impl->start();
}

void ARModule::onResume() {
    _impl->resume();
}

void ARModule::onPause() {
    _impl->pause();
}

void ARModule::beforeUpdate() {
    //_impl->beforeUpdate();
    //_impl->update();
}

void ARModule::update() {
    _impl->update();
}

// -1: not started, 0: arkit, 1: arcore, 2: arengine
int ARModule::getAPIState() {
    return _impl->getAPIState();
}

void ARModule::setCameraTextureName(int id) {
    _impl->setCameraTextureName(id);
}

// jsb manual
float* ARModule::getCameraPose() const {
    return _impl->getCameraPose();
}

float* ARModule::getCameraViewMatrix() const {
    return _impl->getCameraViewMatrix();
}

float* ARModule::getCameraProjectionMatrix() const {
    return _impl->getCameraProjectionMatrix();
}

// jsb skip
float* ARModule::getCameraTexCoords() const {
    return _impl->getCameraTexCoords();
}

void* ARModule::getCameraTextureRef() const {
    return _impl->getCameraTextureRef();
}

int ARModule::getAddedPlanesCount() const {
    //return _impl->getAddedPlanesCount();
    return _impl->getInfoLength() / 12;
}
int ARModule::getRemovedPlanesCount() const {
    //return _impl->getRemovedPlanesCount();
    return _impl->getInfoLength();
}
int ARModule::getUpdatedPlanesCount() const {
    //return _impl->getUpdatedPlanesCount();
    return _impl->getInfoLength() / 12;
}
void ARModule::updatePlanesInfo() const {
    _impl->updatePlanesInfo();
}
float* ARModule::getAddedPlanesInfo() const {
    return _impl->getAddedPlanesInfo();
}

unsigned long* ARModule::getRemovedPlanesInfo() const {
    return _impl->getRemovedPlanesInfo();
}
float* ARModule::getUpdatedPlanesInfo() const {
    return _impl->getUpdatedPlanesInfo();
}

int ARModule::getInfoLength() const {
    return _impl->getInfoLength();
}

} // namespace ar
} // namespace cc
