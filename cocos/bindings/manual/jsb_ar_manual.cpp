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

#include "jsb_ar_manual.h"

#if USE_AR_MODULE > 0

#include "bindings/manual/jsb_conversions.h"
#include "bindings/manual/jsb_global.h"
#include "ar/ARModule.h"
#include "bindings/auto/jsb_ar_auto.h"

static bool js_ar_ARModule_getCameraPose(se::State& s)
{
    cc::ar::ARModule* cobj = (cc::ar::ARModule*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_ar_ARModule_getCameraPose : Invalid Native Object");

    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        float* buffer = cobj->getCameraPose();
        se::Object* pose = se::Object::createTypedArray(se::Object::TypedArrayType::FLOAT32, buffer, 28);
        s.rval().setObject(pose);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_ar_ARModule_getCameraPose)

static bool js_ar_ARModule_getCameraViewMatrix(se::State& s)
{
    cc::ar::ARModule* cobj = (cc::ar::ARModule*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_ar_ARModule_getCameraViewMatrix : Invalid Native Object");

    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        float* buffer = cobj->getCameraViewMatrix();
        se::Object* viewMatrix = se::Object::createTypedArray(se::Object::TypedArrayType::FLOAT32, buffer, 64);
        s.rval().setObject(viewMatrix);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_ar_ARModule_getCameraViewMatrix)

static bool js_ar_ARModule_getCameraProjectionMatrix(se::State& s)
{
    cc::ar::ARModule* cobj = (cc::ar::ARModule*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_ar_ARModule_getCameraProjectionMatrix : Invalid Native Object");

    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        float* buffer = cobj->getCameraProjectionMatrix();
        se::Object* projMatrix = se::Object::createTypedArray(se::Object::TypedArrayType::FLOAT32, buffer, 64);
        s.rval().setObject(projMatrix);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_ar_ARModule_getCameraProjectionMatrix)

bool register_all_ar_manual(se::Object *obj) {
    __jsb_cc_ar_ARModule_proto->defineFunction("getCameraPose", _SE(js_ar_ARModule_getCameraPose));
    __jsb_cc_ar_ARModule_proto->defineFunction("getCameraViewMatrix", _SE(js_ar_ARModule_getCameraViewMatrix));
    __jsb_cc_ar_ARModule_proto->defineFunction("getCameraProjectionMatrix", _SE(js_ar_ARModule_getCameraProjectionMatrix));
    return true;
}

#endif //#if USE_AR_MODULE > 0
