/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OPENHARMONY

#include "platform/CCDevice.h"
#include "platform/openharmony/napi/NapiHelper.h"

NS_CC_BEGIN

int Device::getDPI() {
    float value;
    NapiHelper::napiCallFunction("getDPI", &value);
    return value;
}

int Device::getDevicePixelRatio() {
    // float value;
    // NapiHelper::napiCallFunction("getPixelRation", &value);
    // return value;
    // TODO(qgh):openharmony does support this interface, but returning a value of 1.5 will cause the entire page to zoom in.
    return 1;
}

void Device::setKeepScreenOn(bool value) {
    CC_UNUSED_PARAM(value);
}

cocos2d::Vec4 Device::getSafeAreaEdge() {
    return cocos2d::Vec4();
}

Device::Rotation Device::getDeviceRotation() {
    int32_t value = 0;
    NapiHelper::napiCallFunction("getDeviceOrientation", &value);
    if(value == 0) {
        return cocos2d::Device::Rotation::_0;
    } else if(value == 1) {
        return cocos2d::Device::Rotation::_90;
    } else if(value == 2) {
        return cocos2d::Device::Rotation::_180;
    } else if(value == 3) {
        return cocos2d::Device::Rotation::_270;
    }
    CC_ASSERT(false);
    return cocos2d::Device::Rotation::_0;
}

Device::NetworkType Device::getNetworkType() {
    int32_t value;
    NapiHelper::napiCallFunction("getNetworkType", &value);
    if(value == 0) {
        return cocos2d::Device::NetworkType::WWAN;
    } else if(value == 1 or value == 3) {
        return cocos2d::Device::NetworkType::LAN;
    } else {
        return cocos2d::Device::NetworkType::NONE;
    }
}
float Device::getBatteryLevel() {
    int32_t value;
    NapiHelper::napiCallFunction("getBatteryLevel", &value);
    return value;
}

const Device::MotionValue& Device::getDeviceMotionValue() {
    std::vector<float>  v;
    NapiHelper::napiCallFunction<std::vector<float> >("getDeviceMotionValue", &v);
    static MotionValue motionValue;
    if (!v.empty()) {
        
        motionValue.accelerationIncludingGravityX = v[0];
        motionValue.accelerationIncludingGravityY = v[1];
        motionValue.accelerationIncludingGravityZ = v[2];

        motionValue.accelerationX = v[3];
        motionValue.accelerationY = v[4];
        motionValue.accelerationZ = v[5];

        motionValue.rotationRateAlpha = v[6];
        motionValue.rotationRateBeta = v[7];
        motionValue.rotationRateGamma = v[8];
    } else {
        memset(&motionValue, 0, sizeof(motionValue));
    }
    return motionValue;
}

std::string Device::getDeviceModel() {
    std::string str;
    NapiHelper::napiCallFunction<std::string>("getDeviceModel", &str);
    return str;
}

void Device::setAccelerometerEnabled(bool isEnabled) {
    // if (isEnabled)
    // {
    //     JniHelper::callStaticVoidMethod(JCLS_HELPER, "enableAccelerometer");
    // }
    // else
    // {
    //     JniHelper::callStaticVoidMethod(JCLS_HELPER, "disableAccelerometer");
    // }
}

void Device::setAccelerometerInterval(float interval) {
    // JniHelper::callStaticVoidMethod(JCLS_HELPER, "setAccelerometerInterval", interval);
}

void Device::vibrate(float duration) {
    int32_t value = 0;
    NapiHelper::napiCallFunctionByFloatArgs("vibrate", duration, &value);
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OPENHARMONY
