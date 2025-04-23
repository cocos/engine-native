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
#include "HelperMacros.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_OPENHARMONY

#include "platform/CCDevice.h"
#include "platform/openharmony/napi/NapiHelper.h"

NS_CC_BEGIN

int Device::getDPI() {
    auto value = NapiHelper::napiCallFunction("getDPI");
    if (value.IsNumber()) {
        return value.As<Napi::Number>().FloatValue();
    }
    return 0.F;
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
    // screen with enabled cutout area
    auto value = NapiHelper::napiCallFunction("getAvoidSide");
    int32_t avoidSide = 0;
    if (value.IsNumber()) {
        avoidSide = value.As<Napi::Number>().Int32Value();
    }

    float safearea_top = 0.0f;
    float safearea_left = 0.0f;
    float safearea_bottom = 0.0f;
    float safearea_right = 0.0f;

    if(0 == avoidSide) {
        auto top = NapiHelper::napiCallFunction("getCutoutToTop");
        int32_t cutout_top = 0;
        if (top.IsNumber()) {
            cutout_top = top.As<Napi::Number>().Int32Value();
        }
        safearea_top += cutout_top;
    } else if(1 == avoidSide) {
        auto right = NapiHelper::napiCallFunction("getCutoutToRight");
        int32_t cutout_right = 0;
        if (right.IsNumber()) {
            cutout_right = right.As<Napi::Number>().Int32Value();
        }
        safearea_right += cutout_right;
    } else if(2 == avoidSide) {
        auto bottom = NapiHelper::napiCallFunction("getCutoutToBottom");
        int32_t cutout_bottom = 0;
        if (bottom.IsNumber()) {
            cutout_bottom = bottom.As<Napi::Number>().Int32Value();
        }
        safearea_bottom += cutout_bottom;
    } else if(3 == avoidSide) {
        auto left = NapiHelper::napiCallFunction("getCutoutToLeft");
        int32_t cutout_left = 0;
        if (left.IsNumber()) {
            cutout_left = left.As<Napi::Number>().Int32Value();
        }
        safearea_left += cutout_left;
    }
    
    return cocos2d::Vec4(safearea_top, safearea_left, safearea_bottom, safearea_right);
}

Device::Rotation Device::getDeviceRotation() {
    auto value = NapiHelper::napiCallFunction("getDeviceOrientation");
    int32_t result = 0;
    if (value.IsNumber()) {
        result = value.As<Napi::Number>().Int32Value();
    }
    if(result == 0) {
        return cocos2d::Device::Rotation::_0;
    } else if(result == 1) {
        // TODO(qgh): The openharmony platform is rotated clockwise.
        return cocos2d::Device::Rotation::_270;
    } else if(result == 2) {
        return cocos2d::Device::Rotation::_180;
    } else if(result == 3) {
        // TODO(qgh): The openharmony platform is rotated clockwise.
        return cocos2d::Device::Rotation::_90;
    }
    CC_ASSERT(false);
    return cocos2d::Device::Rotation::_0;
}

Device::NetworkType Device::getNetworkType() {
    auto value = NapiHelper::napiCallFunction("getNetworkType");
    int32_t result;
    if (value.IsNumber()) {
        result = value.As<Napi::Number>().Int32Value();
    }
    if(result == 0) {
        return cocos2d::Device::NetworkType::WWAN;
    } else if(result == 1 or result == 3) {
        return cocos2d::Device::NetworkType::LAN;
    }
    return cocos2d::Device::NetworkType::NONE;
}

float Device::getBatteryLevel() {
    auto value = NapiHelper::napiCallFunction("getBatteryLevel");
    if (value.IsNumber()) {
        return value.As<Napi::Number>().FloatValue();
    }
    return 0.F;
}

std::string Device::getDeviceModel() {
    std::string str;
    auto ret = NapiHelper::napiCallFunction("getDeviceModel");
    if (ret.IsString()) {
        str = ret.As<Napi::String>().Utf8Value();
    }
    return str;
}

void Device::vibrate(float duration) {
    NapiHelper::napiCallFunction("vibrate", duration);
}

NS_CC_END

#endif // CC_TARGET_PLATFORM == CC_PLATFORM_OPENHARMONY
