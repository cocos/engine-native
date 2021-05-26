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
#include "scene/Node.h"

#ifndef JSB_ALLOC
    #define JSB_ALLOC(kls, ...) new (std::nothrow) kls(__VA_ARGS__)
#endif

#ifndef JSB_FREE
    #define JSB_FREE(ptr) delete ptr
#endif

static bool js_scene_Model_setInstancedBuffer(se::State& s) {
    auto* cobj = static_cast<cc::scene::Model*>(s.nativeThisObject());
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setInstancedBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t      argc = args.size();

    if (argc == 1) {
        SE_PRECONDITION2(args[0].isObject() && args[0].toObject()->isArrayBuffer(), false, "js_gfx_Device_createBuffer: expected Array Buffer!");

        uint8_t* data{nullptr};
        args[0].toObject()->getArrayBufferData(&data, nullptr);
        cobj->setInstancedBuffer(data);

        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setInstancedBuffer)

se::Object* __jsb_cc_scene_Node_proto = nullptr;
se::Class*  __jsb_cc_scene_Node_class = nullptr;

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_Node_finalize)

static bool js_scene_Node_constructor(se::State& s) // constructor_overloaded.c
{
    CC_UNUSED bool ok   = true;
    const auto&    args = s.args();
    size_t         argc = args.size();
    do {
        if (argc == 0) {
            auto* cobj = JSB_ALLOC(cc::scene::Node);
            s.thisObject()->setPrivateData(cobj);
            se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
            return true;
        }
    } while (false);
    do {
        if (argc == 3) {
            SE_PRECONDITION2(args[0].isObject() && args[0].toObject()->isArrayBuffer(), false, "js_scene_Node_constructor: expected Array Buffer!");

            uint8_t* data{nullptr};
            args[0].toObject()->getArrayBufferData(&data, nullptr);

            HolderType<unsigned int, false> arg1 = {};
            ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
            if (!ok) {
                ok = true;
                SE_REPORT_ERROR("js_scene_Node_constructor: invalid arg1!");
                break;
            }
            
            HolderType<unsigned int, false> arg2 = {};
            ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
            if (!ok) {
                ok = true;
                SE_REPORT_ERROR("js_scene_Node_constructor: invalid arg2!");
                break;
            }
            auto* cobj = JSB_ALLOC(cc::scene::Node, data, arg1.value(), arg2.value());
            s.thisObject()->setPrivateData(cobj);
            se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
            return true;
        }
    } while (false);
    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_scene_Node_constructor, __jsb_cc_scene_Node_class, js_cc_scene_Node_finalize)

static bool js_cc_scene_Node_finalize(se::State& s) {
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::Node>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end()) {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::scene::Node>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_Node_finalize)

bool js_register_scene_Node(se::Object* obj) {
    auto *cls = se::Class::create("Node", obj, nullptr, _SE(js_scene_Node_constructor));

    cls->defineFunction("updateWorldTransform", _SE(js_scene_Node_updateWorldTransform));
    cls->defineFinalizeFunction(_SE(js_cc_scene_Node_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::Node>(cls);

    __jsb_cc_scene_Node_proto = cls->getProto();
    __jsb_cc_scene_Node_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

bool register_all_scene_manual(se::Object* obj) {
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("ns", &nsVal)) {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("ns", nsVal);
    }
    se::Object* ns = nsVal.toObject();

    js_register_scene_Node(ns);

    __jsb_cc_scene_Model_proto->defineFunction("setInstancedBuffer", _SE(js_scene_Model_setInstancedBuffer));

    return true;
}
