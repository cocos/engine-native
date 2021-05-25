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

#include "jsb_scene_manual.h"
#include "bindings/auto/jsb_scene_auto.h"
#include "scene/Model.h"

static bool js_scene_Model_setInstancedBuffer(se::State &s) {
    cc::scene::Model *cobj = (cc::scene::Model *)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setInstancedBuffer : Invalid Native Object");
    const auto &args = s.args();
    size_t      argc = args.size();

    if (argc == 1) {
        SE_PRECONDITION2(args[0].isObject() && args[0].toObject()->isArrayBuffer(), false, "js_gfx_Device_createBuffer: expected Array Buffer!");

        uint8_t *data{nullptr};
        args[0].toObject()->getArrayBufferData(&data, nullptr);
        cobj->setInstancedBuffer(data);

        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setInstancedBuffer)

bool register_all_scene_manual(se::Object *obj) {
    // Get the ns
    se::Value nrVal;
    if (!obj->getProperty("ns", &nrVal)) {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nrVal.setObject(jsobj);
        obj->setProperty("ns", nrVal);
    }
    se::Object *nr = nrVal.toObject();

    __jsb_cc_scene_Model_proto->defineFunction("setInstancedBuffer", _SE(js_scene_Model_setInstancedBuffer));

    return true;
}
