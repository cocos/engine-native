#include "cocos/bindings/auto/jsb_scene_auto.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/bindings/manual/jsb_global.h"
#include "scene/Node.h"
#include "scene/Light.h"
#include "scene/DirectionalLight.h"
#include "scene/SpotLight.h"
#include "scene/SphereLight.h"
#include "scene/Model.h"
#include "scene/SubModel.h"
#include "scene/Pass.h"
#include "scene/RenderScene.h"
#include "scene/DrawBatch2D.h"
#include "scene/Camera.h"
#include "scene/RenderWindow.h"

#ifndef JSB_ALLOC
#define JSB_ALLOC(kls, ...) new (std::nothrow) kls(__VA_ARGS__)
#endif

#ifndef JSB_FREE
#define JSB_FREE(ptr) delete ptr
#endif
se::Object* __jsb_cc_scene_Node_proto = nullptr;
se::Class* __jsb_cc_scene_Node_class = nullptr;

static bool js_scene_Node_getFlagsChanged(se::State& s)
{
    cc::scene::Node* cobj = SE_THIS_OBJECT<cc::scene::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getFlagsChanged : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->getFlagsChanged();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Node_getFlagsChanged : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getFlagsChanged)

static bool js_scene_Node_getLayer(se::State& s)
{
    cc::scene::Node* cobj = SE_THIS_OBJECT<cc::scene::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getLayer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getLayer();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Node_getLayer : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getLayer)

static bool js_scene_Node_getWorldMatrix(se::State& s)
{
    cc::scene::Node* cobj = SE_THIS_OBJECT<cc::scene::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getWorldMatrix : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::Mat4& result = cobj->getWorldMatrix();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Node_getWorldMatrix : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getWorldMatrix)

static bool js_scene_Node_getWorldPosition(se::State& s)
{
    cc::scene::Node* cobj = SE_THIS_OBJECT<cc::scene::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getWorldPosition : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::Vec3& result = cobj->getWorldPosition();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Node_getWorldPosition : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getWorldPosition)

static bool js_scene_Node_getWorldRotation(se::State& s)
{
    cc::scene::Node* cobj = SE_THIS_OBJECT<cc::scene::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getWorldRotation : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::Vec4& result = cobj->getWorldRotation();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Node_getWorldRotation : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getWorldRotation)

static bool js_scene_Node_getWorldScale(se::State& s)
{
    cc::scene::Node* cobj = SE_THIS_OBJECT<cc::scene::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_getWorldScale : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::Vec3& result = cobj->getWorldScale();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Node_getWorldScale : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_getWorldScale)

static bool js_scene_Node_updateWorldTransform(se::State& s)
{
    cc::scene::Node* cobj = SE_THIS_OBJECT<cc::scene::Node>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Node_updateWorldTransform : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->updateWorldTransform();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Node_updateWorldTransform)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_Node_finalize)

static bool js_scene_Node_constructor(se::State& s)  // constructor_overloaded.c
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();
    do {
        if (argc == 0) {
            cc::scene::Node* cobj = JSB_ALLOC(cc::scene::Node);
            s.thisObject()->setPrivateData(cobj);
            se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
            return true;
        }
    } while(false);
    do {
        if (argc == 2) {
            HolderType<void*, false> arg0 = {};
            ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
            if (!ok) { ok = true; break; }
            HolderType<unsigned int, false> arg1 = {};
            ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
            if (!ok) { ok = true; break; }
            cc::scene::Node* cobj = JSB_ALLOC(cc::scene::Node, arg0.value(), arg1.value());
            s.thisObject()->setPrivateData(cobj);
            se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
            return true;
        }
    } while(false);
    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_scene_Node_constructor, __jsb_cc_scene_Node_class, js_cc_scene_Node_finalize)




static bool js_cc_scene_Node_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::Node>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::scene::Node* cobj = SE_THIS_OBJECT<cc::scene::Node>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_Node_finalize)

bool js_register_scene_Node(se::Object* obj)
{
    auto cls = se::Class::create("Node", obj, nullptr, _SE(js_scene_Node_constructor));

    cls->defineFunction("getFlagsChanged", _SE(js_scene_Node_getFlagsChanged));
    cls->defineFunction("getLayer", _SE(js_scene_Node_getLayer));
    cls->defineFunction("getWorldMatrix", _SE(js_scene_Node_getWorldMatrix));
    cls->defineFunction("getWorldPosition", _SE(js_scene_Node_getWorldPosition));
    cls->defineFunction("getWorldRotation", _SE(js_scene_Node_getWorldRotation));
    cls->defineFunction("getWorldScale", _SE(js_scene_Node_getWorldScale));
    cls->defineFunction("updateWorldTransform", _SE(js_scene_Node_updateWorldTransform));
    cls->defineFinalizeFunction(_SE(js_cc_scene_Node_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::Node>(cls);

    __jsb_cc_scene_Node_proto = cls->getProto();
    __jsb_cc_scene_Node_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_scene_Light_proto = nullptr;
se::Class* __jsb_cc_scene_Light_class = nullptr;

static bool js_scene_Light_getColor(se::State& s)
{
    cc::scene::Light* cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_getColor : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::Vec3& result = cobj->getColor();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Light_getColor : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Light_getColor)

static bool js_scene_Light_getColorTemperatureRGB(se::State& s)
{
    cc::scene::Light* cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_getColorTemperatureRGB : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::Vec3& result = cobj->getColorTemperatureRGB();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Light_getColorTemperatureRGB : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Light_getColorTemperatureRGB)

static bool js_scene_Light_getNode(se::State& s)
{
    cc::scene::Light* cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_getNode : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::scene::Node* result = cobj->getNode();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Light_getNode : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Light_getNode)

static bool js_scene_Light_getType(se::State& s)
{
    cc::scene::Light* cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_getType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getType();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Light_getType : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Light_getType)

static bool js_scene_Light_getUseColorTemperature(se::State& s)
{
    cc::scene::Light* cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_getUseColorTemperature : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->getUseColorTemperature();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Light_getUseColorTemperature : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Light_getUseColorTemperature)

static bool js_scene_Light_setColor(se::State& s)
{
    cc::scene::Light* cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_setColor : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::Vec3, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Light_setColor : Error processing arguments");
        cobj->setColor(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Light_setColor)

static bool js_scene_Light_setColorTemperatureRGB(se::State& s)
{
    cc::scene::Light* cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_setColorTemperatureRGB : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::Vec3, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Light_setColorTemperatureRGB : Error processing arguments");
        cobj->setColorTemperatureRGB(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Light_setColorTemperatureRGB)

static bool js_scene_Light_setNode(se::State& s)
{
    cc::scene::Light* cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_setNode : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::Node*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Light_setNode : Error processing arguments");
        cobj->setNode(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Light_setNode)

static bool js_scene_Light_setType(se::State& s)
{
    cc::scene::Light* cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_setType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::LightType, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Light_setType : Error processing arguments");
        cobj->setType(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Light_setType)

static bool js_scene_Light_setUseColorTemperature(se::State& s)
{
    cc::scene::Light* cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_setUseColorTemperature : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Light_setUseColorTemperature : Error processing arguments");
        cobj->setUseColorTemperature(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Light_setUseColorTemperature)

static bool js_scene_Light_update(se::State& s)
{
    cc::scene::Light* cobj = SE_THIS_OBJECT<cc::scene::Light>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Light_update : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->update();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Light_update)




bool js_register_scene_Light(se::Object* obj)
{
    auto cls = se::Class::create("Light", obj, nullptr, nullptr);

    cls->defineFunction("getColor", _SE(js_scene_Light_getColor));
    cls->defineFunction("getColorTemperatureRGB", _SE(js_scene_Light_getColorTemperatureRGB));
    cls->defineFunction("getNode", _SE(js_scene_Light_getNode));
    cls->defineFunction("getType", _SE(js_scene_Light_getType));
    cls->defineFunction("getUseColorTemperature", _SE(js_scene_Light_getUseColorTemperature));
    cls->defineFunction("setColor", _SE(js_scene_Light_setColor));
    cls->defineFunction("setColorTemperatureRGB", _SE(js_scene_Light_setColorTemperatureRGB));
    cls->defineFunction("setNode", _SE(js_scene_Light_setNode));
    cls->defineFunction("setType", _SE(js_scene_Light_setType));
    cls->defineFunction("setUseColorTemperature", _SE(js_scene_Light_setUseColorTemperature));
    cls->defineFunction("update", _SE(js_scene_Light_update));
    cls->install();
    JSBClassType::registerClass<cc::scene::Light>(cls);

    __jsb_cc_scene_Light_proto = cls->getProto();
    __jsb_cc_scene_Light_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_scene_DirectionalLight_proto = nullptr;
se::Class* __jsb_cc_scene_DirectionalLight_class = nullptr;

static bool js_scene_DirectionalLight_getDir(se::State& s)
{
    cc::scene::DirectionalLight* cobj = SE_THIS_OBJECT<cc::scene::DirectionalLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_DirectionalLight_getDir : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::Vec3& result = cobj->getDir();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_DirectionalLight_getDir : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_DirectionalLight_getDir)

static bool js_scene_DirectionalLight_getIlluminance(se::State& s)
{
    cc::scene::DirectionalLight* cobj = SE_THIS_OBJECT<cc::scene::DirectionalLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_DirectionalLight_getIlluminance : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getIlluminance();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_DirectionalLight_getIlluminance : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_DirectionalLight_getIlluminance)

static bool js_scene_DirectionalLight_setDir(se::State& s)
{
    cc::scene::DirectionalLight* cobj = SE_THIS_OBJECT<cc::scene::DirectionalLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_DirectionalLight_setDir : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::Vec3, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_DirectionalLight_setDir : Error processing arguments");
        cobj->setDir(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_DirectionalLight_setDir)

static bool js_scene_DirectionalLight_setIlluminance(se::State& s)
{
    cc::scene::DirectionalLight* cobj = SE_THIS_OBJECT<cc::scene::DirectionalLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_DirectionalLight_setIlluminance : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_DirectionalLight_setIlluminance : Error processing arguments");
        cobj->setIlluminance(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_DirectionalLight_setIlluminance)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_DirectionalLight_finalize)

static bool js_scene_DirectionalLight_constructor(se::State& s) // constructor.c
{
    cc::scene::DirectionalLight* cobj = JSB_ALLOC(cc::scene::DirectionalLight);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_DirectionalLight_constructor, __jsb_cc_scene_DirectionalLight_class, js_cc_scene_DirectionalLight_finalize)



extern se::Object* __jsb_cc_scene_Light_proto;

static bool js_cc_scene_DirectionalLight_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::DirectionalLight>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::scene::DirectionalLight* cobj = SE_THIS_OBJECT<cc::scene::DirectionalLight>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_DirectionalLight_finalize)

bool js_register_scene_DirectionalLight(se::Object* obj)
{
    auto cls = se::Class::create("DirectionalLight", obj, __jsb_cc_scene_Light_proto, _SE(js_scene_DirectionalLight_constructor));

    cls->defineFunction("getDir", _SE(js_scene_DirectionalLight_getDir));
    cls->defineFunction("getIlluminance", _SE(js_scene_DirectionalLight_getIlluminance));
    cls->defineFunction("setDir", _SE(js_scene_DirectionalLight_setDir));
    cls->defineFunction("setIlluminance", _SE(js_scene_DirectionalLight_setIlluminance));
    cls->defineFinalizeFunction(_SE(js_cc_scene_DirectionalLight_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::DirectionalLight>(cls);

    __jsb_cc_scene_DirectionalLight_proto = cls->getProto();
    __jsb_cc_scene_DirectionalLight_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_scene_Plane_proto = nullptr;
se::Class* __jsb_cc_scene_Plane_class = nullptr;

static bool js_scene_Plane_get_d(se::State& s)
{
    cc::scene::Plane* cobj = SE_THIS_OBJECT<cc::scene::Plane>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Plane_get_d : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->d, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->d, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Plane_get_d)

static bool js_scene_Plane_set_d(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Plane* cobj = SE_THIS_OBJECT<cc::scene::Plane>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Plane_set_d : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->d, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Plane_set_d : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Plane_set_d)

static bool js_scene_Plane_get_n(se::State& s)
{
    cc::scene::Plane* cobj = SE_THIS_OBJECT<cc::scene::Plane>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Plane_get_n : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->n, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->n, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Plane_get_n)

static bool js_scene_Plane_set_n(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Plane* cobj = SE_THIS_OBJECT<cc::scene::Plane>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Plane_set_n : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->n, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Plane_set_n : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Plane_set_n)


template<>
bool sevalue_to_native(const se::Value &from, cc::scene::Plane * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cc::scene::Plane*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("d", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->d), ctx);
    }
    json->getProperty("n", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->n), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_Plane_finalize)

static bool js_scene_Plane_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cc::scene::Plane* cobj = JSB_ALLOC(cc::scene::Plane);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::scene::Plane* cobj = JSB_ALLOC(cc::scene::Plane);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else
    {
        cc::scene::Plane* cobj = JSB_ALLOC(cc::scene::Plane);
        if (argc > 0 && !args[0].isUndefined()) {
            ok &= sevalue_to_native(args[0], &(cobj->d), nullptr);
        }
        if (argc > 1 && !args[1].isUndefined()) {
            ok &= sevalue_to_native(args[1], &(cobj->n), nullptr);
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_scene_Plane_constructor, __jsb_cc_scene_Plane_class, js_cc_scene_Plane_finalize)




static bool js_cc_scene_Plane_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::Plane>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::scene::Plane* cobj = SE_THIS_OBJECT<cc::scene::Plane>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_Plane_finalize)

bool js_register_scene_Plane(se::Object* obj)
{
    auto cls = se::Class::create("Plane", obj, nullptr, _SE(js_scene_Plane_constructor));

    cls->defineProperty("d", _SE(js_scene_Plane_get_d), _SE(js_scene_Plane_set_d));
    cls->defineProperty("n", _SE(js_scene_Plane_get_n), _SE(js_scene_Plane_set_n));
    cls->defineFinalizeFunction(_SE(js_cc_scene_Plane_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::Plane>(cls);

    __jsb_cc_scene_Plane_proto = cls->getProto();
    __jsb_cc_scene_Plane_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_scene_Frustum_proto = nullptr;
se::Class* __jsb_cc_scene_Frustum_class = nullptr;

static bool js_scene_Frustum_get_vertices(se::State& s)
{
    cc::scene::Frustum* cobj = SE_THIS_OBJECT<cc::scene::Frustum>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Frustum_get_vertices : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->vertices, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->vertices, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Frustum_get_vertices)

static bool js_scene_Frustum_set_vertices(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Frustum* cobj = SE_THIS_OBJECT<cc::scene::Frustum>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Frustum_set_vertices : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->vertices, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Frustum_set_vertices : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Frustum_set_vertices)

static bool js_scene_Frustum_get_planes(se::State& s)
{
    cc::scene::Frustum* cobj = SE_THIS_OBJECT<cc::scene::Frustum>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Frustum_get_planes : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->planes, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->planes, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Frustum_get_planes)

static bool js_scene_Frustum_set_planes(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Frustum* cobj = SE_THIS_OBJECT<cc::scene::Frustum>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Frustum_set_planes : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->planes, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Frustum_set_planes : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Frustum_set_planes)


template<>
bool sevalue_to_native(const se::Value &from, cc::scene::Frustum * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cc::scene::Frustum*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("vertices", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->vertices), ctx);
    }
    json->getProperty("planes", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->planes), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_Frustum_finalize)

static bool js_scene_Frustum_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cc::scene::Frustum* cobj = JSB_ALLOC(cc::scene::Frustum);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::scene::Frustum* cobj = JSB_ALLOC(cc::scene::Frustum);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else
    {
        cc::scene::Frustum* cobj = JSB_ALLOC(cc::scene::Frustum);
        if (argc > 0 && !args[0].isUndefined()) {
            ok &= sevalue_to_native(args[0], &(cobj->vertices), nullptr);
        }
        if (argc > 1 && !args[1].isUndefined()) {
            ok &= sevalue_to_native(args[1], &(cobj->planes), nullptr);
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_scene_Frustum_constructor, __jsb_cc_scene_Frustum_class, js_cc_scene_Frustum_finalize)




static bool js_cc_scene_Frustum_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::Frustum>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::scene::Frustum* cobj = SE_THIS_OBJECT<cc::scene::Frustum>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_Frustum_finalize)

bool js_register_scene_Frustum(se::Object* obj)
{
    auto cls = se::Class::create("Frustum", obj, nullptr, _SE(js_scene_Frustum_constructor));

    cls->defineProperty("vertices", _SE(js_scene_Frustum_get_vertices), _SE(js_scene_Frustum_set_vertices));
    cls->defineProperty("planes", _SE(js_scene_Frustum_get_planes), _SE(js_scene_Frustum_set_planes));
    cls->defineFinalizeFunction(_SE(js_cc_scene_Frustum_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::Frustum>(cls);

    __jsb_cc_scene_Frustum_proto = cls->getProto();
    __jsb_cc_scene_Frustum_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_scene_SpotLight_proto = nullptr;
se::Class* __jsb_cc_scene_SpotLight_class = nullptr;

static bool js_scene_SpotLight_getAABB(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_getAABB : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::scene::AABB& result = cobj->getAABB();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_getAABB : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_getAABB)

static bool js_scene_SpotLight_getAngle(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_getAngle : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getAngle();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_getAngle : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_getAngle)

static bool js_scene_SpotLight_getAspect(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_getAspect : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getAspect();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_getAspect : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_getAspect)

static bool js_scene_SpotLight_getDir(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_getDir : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::Vec3& result = cobj->getDir();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_getDir : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_getDir)

static bool js_scene_SpotLight_getFrustum(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_getFrustum : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::scene::Frustum& result = cobj->getFrustum();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_getFrustum : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_getFrustum)

static bool js_scene_SpotLight_getIlluminance(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_getIlluminance : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getIlluminance();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_getIlluminance : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_getIlluminance)

static bool js_scene_SpotLight_getNeedUpdate(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_getNeedUpdate : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->getNeedUpdate();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_getNeedUpdate : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_getNeedUpdate)

static bool js_scene_SpotLight_getPos(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_getPos : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::Vec3& result = cobj->getPos();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_getPos : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_getPos)

static bool js_scene_SpotLight_getRange(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_getRange : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getRange();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_getRange : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_getRange)

static bool js_scene_SpotLight_getSize(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_getSize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getSize();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_getSize : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_getSize)

static bool js_scene_SpotLight_setAABB(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_setAABB : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::AABB, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_setAABB : Error processing arguments");
        cobj->setAABB(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_setAABB)

static bool js_scene_SpotLight_setAngle(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_setAngle : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_setAngle : Error processing arguments");
        cobj->setAngle(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_setAngle)

static bool js_scene_SpotLight_setAspect(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_setAspect : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_setAspect : Error processing arguments");
        cobj->setAspect(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_setAspect)

static bool js_scene_SpotLight_setDir(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_setDir : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::Vec3, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_setDir : Error processing arguments");
        cobj->setDir(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_setDir)

static bool js_scene_SpotLight_setFrustum(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_setFrustum : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::Frustum, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_setFrustum : Error processing arguments");
        cobj->setFrustum(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_setFrustum)

static bool js_scene_SpotLight_setIlluminace(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_setIlluminace : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_setIlluminace : Error processing arguments");
        cobj->setIlluminace(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_setIlluminace)

static bool js_scene_SpotLight_setNeedUpdate(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_setNeedUpdate : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_setNeedUpdate : Error processing arguments");
        cobj->setNeedUpdate(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_setNeedUpdate)

static bool js_scene_SpotLight_setPos(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_setPos : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::Vec3, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_setPos : Error processing arguments");
        cobj->setPos(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_setPos)

static bool js_scene_SpotLight_setRange(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_setRange : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_setRange : Error processing arguments");
        cobj->setRange(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_setRange)

static bool js_scene_SpotLight_setSize(se::State& s)
{
    cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SpotLight_setSize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SpotLight_setSize : Error processing arguments");
        cobj->setSize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SpotLight_setSize)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_SpotLight_finalize)

static bool js_scene_SpotLight_constructor(se::State& s) // constructor.c
{
    cc::scene::SpotLight* cobj = JSB_ALLOC(cc::scene::SpotLight);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_SpotLight_constructor, __jsb_cc_scene_SpotLight_class, js_cc_scene_SpotLight_finalize)



extern se::Object* __jsb_cc_scene_Light_proto;

static bool js_cc_scene_SpotLight_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::SpotLight>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::scene::SpotLight* cobj = SE_THIS_OBJECT<cc::scene::SpotLight>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_SpotLight_finalize)

bool js_register_scene_SpotLight(se::Object* obj)
{
    auto cls = se::Class::create("SpotLight", obj, __jsb_cc_scene_Light_proto, _SE(js_scene_SpotLight_constructor));

    cls->defineFunction("getAABB", _SE(js_scene_SpotLight_getAABB));
    cls->defineFunction("getAngle", _SE(js_scene_SpotLight_getAngle));
    cls->defineFunction("getAspect", _SE(js_scene_SpotLight_getAspect));
    cls->defineFunction("getDir", _SE(js_scene_SpotLight_getDir));
    cls->defineFunction("getFrustum", _SE(js_scene_SpotLight_getFrustum));
    cls->defineFunction("getIlluminance", _SE(js_scene_SpotLight_getIlluminance));
    cls->defineFunction("getNeedUpdate", _SE(js_scene_SpotLight_getNeedUpdate));
    cls->defineFunction("getPos", _SE(js_scene_SpotLight_getPos));
    cls->defineFunction("getRange", _SE(js_scene_SpotLight_getRange));
    cls->defineFunction("getSize", _SE(js_scene_SpotLight_getSize));
    cls->defineFunction("setAABB", _SE(js_scene_SpotLight_setAABB));
    cls->defineFunction("setAngle", _SE(js_scene_SpotLight_setAngle));
    cls->defineFunction("setAspect", _SE(js_scene_SpotLight_setAspect));
    cls->defineFunction("setDir", _SE(js_scene_SpotLight_setDir));
    cls->defineFunction("setFrustum", _SE(js_scene_SpotLight_setFrustum));
    cls->defineFunction("setIlluminace", _SE(js_scene_SpotLight_setIlluminace));
    cls->defineFunction("setNeedUpdate", _SE(js_scene_SpotLight_setNeedUpdate));
    cls->defineFunction("setPos", _SE(js_scene_SpotLight_setPos));
    cls->defineFunction("setRange", _SE(js_scene_SpotLight_setRange));
    cls->defineFunction("setSize", _SE(js_scene_SpotLight_setSize));
    cls->defineFinalizeFunction(_SE(js_cc_scene_SpotLight_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::SpotLight>(cls);

    __jsb_cc_scene_SpotLight_proto = cls->getProto();
    __jsb_cc_scene_SpotLight_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_scene_SphereLight_proto = nullptr;
se::Class* __jsb_cc_scene_SphereLight_class = nullptr;

static bool js_scene_SphereLight_getAABB(se::State& s)
{
    cc::scene::SphereLight* cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SphereLight_getAABB : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::scene::AABB& result = cobj->getAABB();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SphereLight_getAABB : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SphereLight_getAABB)

static bool js_scene_SphereLight_getIllumiance(se::State& s)
{
    cc::scene::SphereLight* cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SphereLight_getIllumiance : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getIllumiance();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SphereLight_getIllumiance : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SphereLight_getIllumiance)

static bool js_scene_SphereLight_getPos(se::State& s)
{
    cc::scene::SphereLight* cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SphereLight_getPos : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::Vec3& result = cobj->getPos();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SphereLight_getPos : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SphereLight_getPos)

static bool js_scene_SphereLight_getRange(se::State& s)
{
    cc::scene::SphereLight* cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SphereLight_getRange : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getRange();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SphereLight_getRange : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SphereLight_getRange)

static bool js_scene_SphereLight_getSize(se::State& s)
{
    cc::scene::SphereLight* cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SphereLight_getSize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getSize();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_SphereLight_getSize : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SphereLight_getSize)

static bool js_scene_SphereLight_setAABB(se::State& s)
{
    cc::scene::SphereLight* cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SphereLight_setAABB : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::AABB, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SphereLight_setAABB : Error processing arguments");
        cobj->setAABB(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SphereLight_setAABB)

static bool js_scene_SphereLight_setIllumiance(se::State& s)
{
    cc::scene::SphereLight* cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SphereLight_setIllumiance : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SphereLight_setIllumiance : Error processing arguments");
        cobj->setIllumiance(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SphereLight_setIllumiance)

static bool js_scene_SphereLight_setPos(se::State& s)
{
    cc::scene::SphereLight* cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SphereLight_setPos : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::Vec3, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SphereLight_setPos : Error processing arguments");
        cobj->setPos(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SphereLight_setPos)

static bool js_scene_SphereLight_setRange(se::State& s)
{
    cc::scene::SphereLight* cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SphereLight_setRange : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SphereLight_setRange : Error processing arguments");
        cobj->setRange(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SphereLight_setRange)

static bool js_scene_SphereLight_setSize(se::State& s)
{
    cc::scene::SphereLight* cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SphereLight_setSize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_SphereLight_setSize : Error processing arguments");
        cobj->setSize(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_SphereLight_setSize)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_SphereLight_finalize)

static bool js_scene_SphereLight_constructor(se::State& s) // constructor.c
{
    cc::scene::SphereLight* cobj = JSB_ALLOC(cc::scene::SphereLight);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_SphereLight_constructor, __jsb_cc_scene_SphereLight_class, js_cc_scene_SphereLight_finalize)



extern se::Object* __jsb_cc_scene_Light_proto;

static bool js_cc_scene_SphereLight_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::SphereLight>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::scene::SphereLight* cobj = SE_THIS_OBJECT<cc::scene::SphereLight>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_SphereLight_finalize)

bool js_register_scene_SphereLight(se::Object* obj)
{
    auto cls = se::Class::create("SphereLight", obj, __jsb_cc_scene_Light_proto, _SE(js_scene_SphereLight_constructor));

    cls->defineFunction("getAABB", _SE(js_scene_SphereLight_getAABB));
    cls->defineFunction("getIllumiance", _SE(js_scene_SphereLight_getIllumiance));
    cls->defineFunction("getPos", _SE(js_scene_SphereLight_getPos));
    cls->defineFunction("getRange", _SE(js_scene_SphereLight_getRange));
    cls->defineFunction("getSize", _SE(js_scene_SphereLight_getSize));
    cls->defineFunction("setAABB", _SE(js_scene_SphereLight_setAABB));
    cls->defineFunction("setIllumiance", _SE(js_scene_SphereLight_setIllumiance));
    cls->defineFunction("setPos", _SE(js_scene_SphereLight_setPos));
    cls->defineFunction("setRange", _SE(js_scene_SphereLight_setRange));
    cls->defineFunction("setSize", _SE(js_scene_SphereLight_setSize));
    cls->defineFinalizeFunction(_SE(js_cc_scene_SphereLight_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::SphereLight>(cls);

    __jsb_cc_scene_SphereLight_proto = cls->getProto();
    __jsb_cc_scene_SphereLight_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_scene_SubModel_proto = nullptr;
se::Class* __jsb_cc_scene_SubModel_class = nullptr;

static bool js_scene_SubModel_update(se::State& s)
{
    cc::scene::SubModel* cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_SubModel_update : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->update();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_SubModel_update)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_SubModel_finalize)

static bool js_scene_SubModel_constructor(se::State& s) // constructor.c
{
    cc::scene::SubModel* cobj = JSB_ALLOC(cc::scene::SubModel);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_SubModel_constructor, __jsb_cc_scene_SubModel_class, js_cc_scene_SubModel_finalize)




static bool js_cc_scene_SubModel_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::SubModel>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::scene::SubModel* cobj = SE_THIS_OBJECT<cc::scene::SubModel>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_SubModel_finalize)

bool js_register_scene_SubModel(se::Object* obj)
{
    auto cls = se::Class::create("SubModel", obj, nullptr, _SE(js_scene_SubModel_constructor));

    cls->defineFunction("update", _SE(js_scene_SubModel_update));
    cls->defineFinalizeFunction(_SE(js_cc_scene_SubModel_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::SubModel>(cls);

    __jsb_cc_scene_SubModel_proto = cls->getProto();
    __jsb_cc_scene_SubModel_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_scene_Model_proto = nullptr;
se::Class* __jsb_cc_scene_Model_class = nullptr;

static bool js_scene_Model_getCastShadow(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getCastShadow : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->getCastShadow();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getCastShadow : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getCastShadow)

static bool js_scene_Model_getEnabled(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getEnabled : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->getEnabled();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getEnabled : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getEnabled)

static bool js_scene_Model_getInstanceBuffer(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getInstanceBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::gfx::Buffer* result = cobj->getInstanceBuffer();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getInstanceBuffer : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getInstanceBuffer)

static bool js_scene_Model_getInstancedAttributeBlock(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getInstancedAttributeBlock : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::scene::InstancedAttributeBlock* result = cobj->getInstancedAttributeBlock();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getInstancedAttributeBlock : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getInstancedAttributeBlock)

static bool js_scene_Model_getInstmatWorldIdx(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getInstmatWorldIdx : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getInstmatWorldIdx();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getInstmatWorldIdx : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getInstmatWorldIdx)

static bool js_scene_Model_getLocalBuffer(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getLocalBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::gfx::Buffer* result = cobj->getLocalBuffer();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getLocalBuffer : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getLocalBuffer)

static bool js_scene_Model_getLocalData(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getLocalData : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float* result = cobj->getLocalData();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getLocalData : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getLocalData)

static bool js_scene_Model_getModelBounds(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getModelBounds : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::scene::AABB& result = cobj->getModelBounds();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getModelBounds : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getModelBounds)

static bool js_scene_Model_getReceiveShadow(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getReceiveShadow : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->getReceiveShadow();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getReceiveShadow : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getReceiveShadow)

static bool js_scene_Model_getSubModels(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getSubModels : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cc::scene::SubModel *>& result = cobj->getSubModels();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getSubModels : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getSubModels)

static bool js_scene_Model_getTransform(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getTransform : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::scene::Node* result = cobj->getTransform();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getTransform : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getTransform)

static bool js_scene_Model_getTransformUpdated(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getTransformUpdated : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->getTransformUpdated();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getTransformUpdated : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getTransformUpdated)

static bool js_scene_Model_getUpdatStamp(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getUpdatStamp : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getUpdatStamp();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getUpdatStamp : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getUpdatStamp)

static bool js_scene_Model_getVisFlags(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getVisFlags : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getVisFlags();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getVisFlags : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getVisFlags)

static bool js_scene_Model_getWorldBounds(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_getWorldBounds : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cc::scene::AABB& result = cobj->getWorldBounds();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Model_getWorldBounds : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_getWorldBounds)

static bool js_scene_Model_seVisFlag(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_seVisFlag : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_seVisFlag : Error processing arguments");
        cobj->seVisFlag(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_seVisFlag)

static bool js_scene_Model_setCastShadow(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setCastShadow : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setCastShadow : Error processing arguments");
        cobj->setCastShadow(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setCastShadow)

static bool js_scene_Model_setEnabled(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setEnabled : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setEnabled : Error processing arguments");
        cobj->setEnabled(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setEnabled)

static bool js_scene_Model_setInstanceBuffer(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setInstanceBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::gfx::Buffer*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setInstanceBuffer : Error processing arguments");
        cobj->setInstanceBuffer(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setInstanceBuffer)

static bool js_scene_Model_setInstmatWorldIdx(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setInstmatWorldIdx : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setInstmatWorldIdx : Error processing arguments");
        cobj->setInstmatWorldIdx(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setInstmatWorldIdx)

static bool js_scene_Model_setLocalBuffer(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setLocalBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::gfx::Buffer*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setLocalBuffer : Error processing arguments");
        cobj->setLocalBuffer(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setLocalBuffer)

static bool js_scene_Model_setReceiveShadow(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setReceiveShadow : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setReceiveShadow : Error processing arguments");
        cobj->setReceiveShadow(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setReceiveShadow)

static bool js_scene_Model_setTransform(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setTransform : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::Node*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setTransform : Error processing arguments");
        cobj->setTransform(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setTransform)

static bool js_scene_Model_setWolrdBounds(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_setWolrdBounds : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::AABB, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_setWolrdBounds : Error processing arguments");
        cobj->setWolrdBounds(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_setWolrdBounds)

static bool js_scene_Model_updateTransform(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_updateTransform : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->updateTransform();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Model_updateTransform)

static bool js_scene_Model_updateUBOs(se::State& s)
{
    cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Model_updateUBOs : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Model_updateUBOs : Error processing arguments");
        cobj->updateUBOs(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Model_updateUBOs)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_Model_finalize)

static bool js_scene_Model_constructor(se::State& s) // constructor.c
{
    cc::scene::Model* cobj = JSB_ALLOC(cc::scene::Model);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_Model_constructor, __jsb_cc_scene_Model_class, js_cc_scene_Model_finalize)




static bool js_cc_scene_Model_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::Model>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::scene::Model* cobj = SE_THIS_OBJECT<cc::scene::Model>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_Model_finalize)

bool js_register_scene_Model(se::Object* obj)
{
    auto cls = se::Class::create("Model", obj, nullptr, _SE(js_scene_Model_constructor));

    cls->defineFunction("getCastShadow", _SE(js_scene_Model_getCastShadow));
    cls->defineFunction("getEnabled", _SE(js_scene_Model_getEnabled));
    cls->defineFunction("getInstanceBuffer", _SE(js_scene_Model_getInstanceBuffer));
    cls->defineFunction("getInstancedAttributeBlock", _SE(js_scene_Model_getInstancedAttributeBlock));
    cls->defineFunction("getInstmatWorldIdx", _SE(js_scene_Model_getInstmatWorldIdx));
    cls->defineFunction("getLocalBuffer", _SE(js_scene_Model_getLocalBuffer));
    cls->defineFunction("getLocalData", _SE(js_scene_Model_getLocalData));
    cls->defineFunction("getModelBounds", _SE(js_scene_Model_getModelBounds));
    cls->defineFunction("getReceiveShadow", _SE(js_scene_Model_getReceiveShadow));
    cls->defineFunction("getSubModels", _SE(js_scene_Model_getSubModels));
    cls->defineFunction("getTransform", _SE(js_scene_Model_getTransform));
    cls->defineFunction("getTransformUpdated", _SE(js_scene_Model_getTransformUpdated));
    cls->defineFunction("getUpdatStamp", _SE(js_scene_Model_getUpdatStamp));
    cls->defineFunction("getVisFlags", _SE(js_scene_Model_getVisFlags));
    cls->defineFunction("getWorldBounds", _SE(js_scene_Model_getWorldBounds));
    cls->defineFunction("seVisFlag", _SE(js_scene_Model_seVisFlag));
    cls->defineFunction("setCastShadow", _SE(js_scene_Model_setCastShadow));
    cls->defineFunction("setEnabled", _SE(js_scene_Model_setEnabled));
    cls->defineFunction("setInstanceBuffer", _SE(js_scene_Model_setInstanceBuffer));
    cls->defineFunction("setInstmatWorldIdx", _SE(js_scene_Model_setInstmatWorldIdx));
    cls->defineFunction("setLocalBuffer", _SE(js_scene_Model_setLocalBuffer));
    cls->defineFunction("setReceiveShadow", _SE(js_scene_Model_setReceiveShadow));
    cls->defineFunction("setTransform", _SE(js_scene_Model_setTransform));
    cls->defineFunction("setWolrdBounds", _SE(js_scene_Model_setWolrdBounds));
    cls->defineFunction("updateTransform", _SE(js_scene_Model_updateTransform));
    cls->defineFunction("updateUBOs", _SE(js_scene_Model_updateUBOs));
    cls->defineFinalizeFunction(_SE(js_cc_scene_Model_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::Model>(cls);

    __jsb_cc_scene_Model_proto = cls->getProto();
    __jsb_cc_scene_Model_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_scene_Pass_proto = nullptr;
se::Class* __jsb_cc_scene_Pass_class = nullptr;

static bool js_scene_Pass_getBatchingScheme(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getBatchingScheme : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getBatchingScheme();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getBatchingScheme : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getBatchingScheme)

static bool js_scene_Pass_getBlendState(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getBlendState : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::gfx::BlendState* result = cobj->getBlendState();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getBlendState : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getBlendState)

static bool js_scene_Pass_getDepthStencilState(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getDepthStencilState : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::gfx::DepthStencilState* result = cobj->getDepthStencilState();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getDepthStencilState : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getDepthStencilState)

static bool js_scene_Pass_getDescriptorSet(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getDescriptorSet : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::gfx::DescriptorSet* result = cobj->getDescriptorSet();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getDescriptorSet : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getDescriptorSet)

static bool js_scene_Pass_getDynamicState(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getDynamicState : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getDynamicState();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getDynamicState : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getDynamicState)

static bool js_scene_Pass_getHash(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getHash : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getHash();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getHash : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getHash)

static bool js_scene_Pass_getPhase(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getPhase : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getPhase();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getPhase : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getPhase)

static bool js_scene_Pass_getPipelineState(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getPipelineState : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::gfx::PipelineLayout* result = cobj->getPipelineState();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getPipelineState : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getPipelineState)

static bool js_scene_Pass_getPrimitive(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getPrimitive : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getPrimitive();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getPrimitive : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getPrimitive)

static bool js_scene_Pass_getPriority(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getPriority : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getPriority();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getPriority : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getPriority)

static bool js_scene_Pass_getRasterizerStage(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getRasterizerStage : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::gfx::RasterizerState* result = cobj->getRasterizerStage();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getRasterizerStage : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getRasterizerStage)

static bool js_scene_Pass_getStage(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_getStage : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getStage();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_Pass_getStage : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_getStage)

static bool js_scene_Pass_setBatchingScheme(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_setBatchingScheme : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::BatchingSchemes, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_setBatchingScheme : Error processing arguments");
        cobj->setBatchingScheme(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_setBatchingScheme)

static bool js_scene_Pass_setBlendState(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_setBlendState : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::gfx::BlendState*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_setBlendState : Error processing arguments");
        cobj->setBlendState(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_setBlendState)

static bool js_scene_Pass_setDepthStencilState(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_setDepthStencilState : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::gfx::DepthStencilState*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_setDepthStencilState : Error processing arguments");
        cobj->setDepthStencilState(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_setDepthStencilState)

static bool js_scene_Pass_setDescriptorSet(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_setDescriptorSet : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::gfx::DescriptorSet*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_setDescriptorSet : Error processing arguments");
        cobj->setDescriptorSet(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_setDescriptorSet)

static bool js_scene_Pass_setDynamicState(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_setDynamicState : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::gfx::DynamicStateFlagBit, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_setDynamicState : Error processing arguments");
        cobj->setDynamicState(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_setDynamicState)

static bool js_scene_Pass_setHash(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_setHash : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_setHash : Error processing arguments");
        cobj->setHash(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_setHash)

static bool js_scene_Pass_setPhase(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_setPhase : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_setPhase : Error processing arguments");
        cobj->setPhase(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_setPhase)

static bool js_scene_Pass_setPipelineLayout(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_setPipelineLayout : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::gfx::PipelineLayout*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_setPipelineLayout : Error processing arguments");
        cobj->setPipelineLayout(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_setPipelineLayout)

static bool js_scene_Pass_setPrimitive(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_setPrimitive : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::gfx::PrimitiveMode, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_setPrimitive : Error processing arguments");
        cobj->setPrimitive(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_setPrimitive)

static bool js_scene_Pass_setPriority(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_setPriority : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::RenderPriority, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_setPriority : Error processing arguments");
        cobj->setPriority(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_setPriority)

static bool js_scene_Pass_setRasterizerState(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_setRasterizerState : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::gfx::RasterizerState*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_setRasterizerState : Error processing arguments");
        cobj->setRasterizerState(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_setRasterizerState)

static bool js_scene_Pass_setStage(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_setStage : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::RenderPassStage, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_Pass_setStage : Error processing arguments");
        cobj->setStage(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_setStage)

static bool js_scene_Pass_update(se::State& s)
{
    cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Pass_update : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->update();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_Pass_update)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_Pass_finalize)

static bool js_scene_Pass_constructor(se::State& s) // constructor.c
{
    cc::scene::Pass* cobj = JSB_ALLOC(cc::scene::Pass);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_Pass_constructor, __jsb_cc_scene_Pass_class, js_cc_scene_Pass_finalize)




static bool js_cc_scene_Pass_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::Pass>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::scene::Pass* cobj = SE_THIS_OBJECT<cc::scene::Pass>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_Pass_finalize)

bool js_register_scene_Pass(se::Object* obj)
{
    auto cls = se::Class::create("Pass", obj, nullptr, _SE(js_scene_Pass_constructor));

    cls->defineFunction("getBatchingScheme", _SE(js_scene_Pass_getBatchingScheme));
    cls->defineFunction("getBlendState", _SE(js_scene_Pass_getBlendState));
    cls->defineFunction("getDepthStencilState", _SE(js_scene_Pass_getDepthStencilState));
    cls->defineFunction("getDescriptorSet", _SE(js_scene_Pass_getDescriptorSet));
    cls->defineFunction("getDynamicState", _SE(js_scene_Pass_getDynamicState));
    cls->defineFunction("getHash", _SE(js_scene_Pass_getHash));
    cls->defineFunction("getPhase", _SE(js_scene_Pass_getPhase));
    cls->defineFunction("getPipelineState", _SE(js_scene_Pass_getPipelineState));
    cls->defineFunction("getPrimitive", _SE(js_scene_Pass_getPrimitive));
    cls->defineFunction("getPriority", _SE(js_scene_Pass_getPriority));
    cls->defineFunction("getRasterizerStage", _SE(js_scene_Pass_getRasterizerStage));
    cls->defineFunction("getStage", _SE(js_scene_Pass_getStage));
    cls->defineFunction("setBatchingScheme", _SE(js_scene_Pass_setBatchingScheme));
    cls->defineFunction("setBlendState", _SE(js_scene_Pass_setBlendState));
    cls->defineFunction("setDepthStencilState", _SE(js_scene_Pass_setDepthStencilState));
    cls->defineFunction("setDescriptorSet", _SE(js_scene_Pass_setDescriptorSet));
    cls->defineFunction("setDynamicState", _SE(js_scene_Pass_setDynamicState));
    cls->defineFunction("setHash", _SE(js_scene_Pass_setHash));
    cls->defineFunction("setPhase", _SE(js_scene_Pass_setPhase));
    cls->defineFunction("setPipelineLayout", _SE(js_scene_Pass_setPipelineLayout));
    cls->defineFunction("setPrimitive", _SE(js_scene_Pass_setPrimitive));
    cls->defineFunction("setPriority", _SE(js_scene_Pass_setPriority));
    cls->defineFunction("setRasterizerState", _SE(js_scene_Pass_setRasterizerState));
    cls->defineFunction("setStage", _SE(js_scene_Pass_setStage));
    cls->defineFunction("update", _SE(js_scene_Pass_update));
    cls->defineFinalizeFunction(_SE(js_cc_scene_Pass_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::Pass>(cls);

    __jsb_cc_scene_Pass_proto = cls->getProto();
    __jsb_cc_scene_Pass_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_scene_DrawBatch2D_proto = nullptr;
se::Class* __jsb_cc_scene_DrawBatch2D_class = nullptr;

static bool js_scene_DrawBatch2D_get_visFlags(se::State& s)
{
    cc::scene::DrawBatch2D* cobj = SE_THIS_OBJECT<cc::scene::DrawBatch2D>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_DrawBatch2D_get_visFlags : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->visFlags, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->visFlags, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_DrawBatch2D_get_visFlags)

static bool js_scene_DrawBatch2D_set_visFlags(se::State& s)
{
    const auto& args = s.args();
    cc::scene::DrawBatch2D* cobj = SE_THIS_OBJECT<cc::scene::DrawBatch2D>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_DrawBatch2D_set_visFlags : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->visFlags, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_DrawBatch2D_set_visFlags : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_DrawBatch2D_set_visFlags)

static bool js_scene_DrawBatch2D_get_descriptSet(se::State& s)
{
    cc::scene::DrawBatch2D* cobj = SE_THIS_OBJECT<cc::scene::DrawBatch2D>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_DrawBatch2D_get_descriptSet : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->descriptSet, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->descriptSet, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_DrawBatch2D_get_descriptSet)

static bool js_scene_DrawBatch2D_set_descriptSet(se::State& s)
{
    const auto& args = s.args();
    cc::scene::DrawBatch2D* cobj = SE_THIS_OBJECT<cc::scene::DrawBatch2D>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_DrawBatch2D_set_descriptSet : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->descriptSet, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_DrawBatch2D_set_descriptSet : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_DrawBatch2D_set_descriptSet)

static bool js_scene_DrawBatch2D_get_inputAssembler(se::State& s)
{
    cc::scene::DrawBatch2D* cobj = SE_THIS_OBJECT<cc::scene::DrawBatch2D>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_DrawBatch2D_get_inputAssembler : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->inputAssembler, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->inputAssembler, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_DrawBatch2D_get_inputAssembler)

static bool js_scene_DrawBatch2D_set_inputAssembler(se::State& s)
{
    const auto& args = s.args();
    cc::scene::DrawBatch2D* cobj = SE_THIS_OBJECT<cc::scene::DrawBatch2D>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_DrawBatch2D_set_inputAssembler : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->inputAssembler, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_DrawBatch2D_set_inputAssembler : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_DrawBatch2D_set_inputAssembler)

static bool js_scene_DrawBatch2D_get_passes(se::State& s)
{
    cc::scene::DrawBatch2D* cobj = SE_THIS_OBJECT<cc::scene::DrawBatch2D>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_DrawBatch2D_get_passes : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->passes, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->passes, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_DrawBatch2D_get_passes)

static bool js_scene_DrawBatch2D_set_passes(se::State& s)
{
    const auto& args = s.args();
    cc::scene::DrawBatch2D* cobj = SE_THIS_OBJECT<cc::scene::DrawBatch2D>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_DrawBatch2D_set_passes : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->passes, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_DrawBatch2D_set_passes : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_DrawBatch2D_set_passes)


template<>
bool sevalue_to_native(const se::Value &from, cc::scene::DrawBatch2D * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cc::scene::DrawBatch2D*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("visFlags", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->visFlags), ctx);
    }
    json->getProperty("descriptSet", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->descriptSet), ctx);
    }
    json->getProperty("inputAssembler", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->inputAssembler), ctx);
    }
    json->getProperty("passes", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->passes), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_DrawBatch2D_finalize)

static bool js_scene_DrawBatch2D_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cc::scene::DrawBatch2D* cobj = JSB_ALLOC(cc::scene::DrawBatch2D);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::scene::DrawBatch2D* cobj = JSB_ALLOC(cc::scene::DrawBatch2D);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else
    {
        cc::scene::DrawBatch2D* cobj = JSB_ALLOC(cc::scene::DrawBatch2D);
        if (argc > 0 && !args[0].isUndefined()) {
            ok &= sevalue_to_native(args[0], &(cobj->visFlags), nullptr);
        }
        if (argc > 1 && !args[1].isUndefined()) {
            ok &= sevalue_to_native(args[1], &(cobj->descriptSet), nullptr);
        }
        if (argc > 2 && !args[2].isUndefined()) {
            ok &= sevalue_to_native(args[2], &(cobj->inputAssembler), nullptr);
        }
        if (argc > 3 && !args[3].isUndefined()) {
            ok &= sevalue_to_native(args[3], &(cobj->passes), nullptr);
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_scene_DrawBatch2D_constructor, __jsb_cc_scene_DrawBatch2D_class, js_cc_scene_DrawBatch2D_finalize)




static bool js_cc_scene_DrawBatch2D_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::DrawBatch2D>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::scene::DrawBatch2D* cobj = SE_THIS_OBJECT<cc::scene::DrawBatch2D>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_DrawBatch2D_finalize)

bool js_register_scene_DrawBatch2D(se::Object* obj)
{
    auto cls = se::Class::create("DrawBatch2D", obj, nullptr, _SE(js_scene_DrawBatch2D_constructor));

    cls->defineProperty("visFlags", _SE(js_scene_DrawBatch2D_get_visFlags), _SE(js_scene_DrawBatch2D_set_visFlags));
    cls->defineProperty("descriptSet", _SE(js_scene_DrawBatch2D_get_descriptSet), _SE(js_scene_DrawBatch2D_set_descriptSet));
    cls->defineProperty("inputAssembler", _SE(js_scene_DrawBatch2D_get_inputAssembler), _SE(js_scene_DrawBatch2D_set_inputAssembler));
    cls->defineProperty("passes", _SE(js_scene_DrawBatch2D_get_passes), _SE(js_scene_DrawBatch2D_set_passes));
    cls->defineFinalizeFunction(_SE(js_cc_scene_DrawBatch2D_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::DrawBatch2D>(cls);

    __jsb_cc_scene_DrawBatch2D_proto = cls->getProto();
    __jsb_cc_scene_DrawBatch2D_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_scene_RenderScene_proto = nullptr;
se::Class* __jsb_cc_scene_RenderScene_class = nullptr;

static bool js_scene_RenderScene_addBatch(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_addBatch : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::DrawBatch2D*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_addBatch : Error processing arguments");
        cobj->addBatch(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_addBatch)

static bool js_scene_RenderScene_addModel(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_addModel : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::Model*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_addModel : Error processing arguments");
        cobj->addModel(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_addModel)

static bool js_scene_RenderScene_addSphereLight(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_addSphereLight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::SphereLight*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_addSphereLight : Error processing arguments");
        cobj->addSphereLight(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_addSphereLight)

static bool js_scene_RenderScene_addSpotLight(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_addSpotLight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::SpotLight*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_addSpotLight : Error processing arguments");
        cobj->addSpotLight(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_addSpotLight)

static bool js_scene_RenderScene_getDrawBatch2Ds(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_getDrawBatch2Ds : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cc::scene::DrawBatch2D *>& result = cobj->getDrawBatch2Ds();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_getDrawBatch2Ds : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_getDrawBatch2Ds)

static bool js_scene_RenderScene_getMainLight(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_getMainLight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cc::scene::DirectionalLight* result = cobj->getMainLight();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_getMainLight : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_getMainLight)

static bool js_scene_RenderScene_getModels(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_getModels : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cc::scene::Model *>& result = cobj->getModels();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_getModels : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_getModels)

static bool js_scene_RenderScene_getSphereLights(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_getSphereLights : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cc::scene::SphereLight *>& result = cobj->getSphereLights();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_getSphereLights : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_getSphereLights)

static bool js_scene_RenderScene_getSpotLights(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_getSpotLights : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cc::scene::SpotLight *>& result = cobj->getSpotLights();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_getSpotLights : Error processing arguments");
        SE_HOLD_RETURN_VALUE(result, s.thisObject(), s.rval());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_getSpotLights)

static bool js_scene_RenderScene_removeBatch(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeBatch : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::DrawBatch2D*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_removeBatch : Error processing arguments");
        cobj->removeBatch(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeBatch)

static bool js_scene_RenderScene_removeBatches(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeBatches : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->removeBatches();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeBatches)

static bool js_scene_RenderScene_removeModel(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeModel : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::Model*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_removeModel : Error processing arguments");
        cobj->removeModel(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeModel)

static bool js_scene_RenderScene_removeModels(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeModels : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->removeModels();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeModels)

static bool js_scene_RenderScene_removeSphereLight(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeSphereLight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::SphereLight*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_removeSphereLight : Error processing arguments");
        cobj->removeSphereLight(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeSphereLight)

static bool js_scene_RenderScene_removeSphereLights(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeSphereLights : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->removeSphereLights();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeSphereLights)

static bool js_scene_RenderScene_removeSpotLight(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeSpotLight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::SpotLight*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_removeSpotLight : Error processing arguments");
        cobj->removeSpotLight(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeSpotLight)

static bool js_scene_RenderScene_removeSpotLights(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_removeSpotLights : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->removeSpotLights();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_removeSpotLights)

static bool js_scene_RenderScene_setMainLight(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_setMainLight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cc::scene::DirectionalLight*, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_scene_RenderScene_setMainLight : Error processing arguments");
        cobj->setMainLight(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_setMainLight)

static bool js_scene_RenderScene_update(se::State& s)
{
    cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderScene_update : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->update();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_scene_RenderScene_update)

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_RenderScene_finalize)

static bool js_scene_RenderScene_constructor(se::State& s) // constructor.c
{
    cc::scene::RenderScene* cobj = JSB_ALLOC(cc::scene::RenderScene);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_scene_RenderScene_constructor, __jsb_cc_scene_RenderScene_class, js_cc_scene_RenderScene_finalize)




static bool js_cc_scene_RenderScene_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::RenderScene>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::scene::RenderScene* cobj = SE_THIS_OBJECT<cc::scene::RenderScene>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_RenderScene_finalize)

bool js_register_scene_RenderScene(se::Object* obj)
{
    auto cls = se::Class::create("RenderScene", obj, nullptr, _SE(js_scene_RenderScene_constructor));

    cls->defineFunction("addBatch", _SE(js_scene_RenderScene_addBatch));
    cls->defineFunction("addModel", _SE(js_scene_RenderScene_addModel));
    cls->defineFunction("addSphereLight", _SE(js_scene_RenderScene_addSphereLight));
    cls->defineFunction("addSpotLight", _SE(js_scene_RenderScene_addSpotLight));
    cls->defineFunction("getDrawBatch2Ds", _SE(js_scene_RenderScene_getDrawBatch2Ds));
    cls->defineFunction("getMainLight", _SE(js_scene_RenderScene_getMainLight));
    cls->defineFunction("getModels", _SE(js_scene_RenderScene_getModels));
    cls->defineFunction("getSphereLights", _SE(js_scene_RenderScene_getSphereLights));
    cls->defineFunction("getSpotLights", _SE(js_scene_RenderScene_getSpotLights));
    cls->defineFunction("removeBatch", _SE(js_scene_RenderScene_removeBatch));
    cls->defineFunction("removeBatches", _SE(js_scene_RenderScene_removeBatches));
    cls->defineFunction("removeModel", _SE(js_scene_RenderScene_removeModel));
    cls->defineFunction("removeModels", _SE(js_scene_RenderScene_removeModels));
    cls->defineFunction("removeSphereLight", _SE(js_scene_RenderScene_removeSphereLight));
    cls->defineFunction("removeSphereLights", _SE(js_scene_RenderScene_removeSphereLights));
    cls->defineFunction("removeSpotLight", _SE(js_scene_RenderScene_removeSpotLight));
    cls->defineFunction("removeSpotLights", _SE(js_scene_RenderScene_removeSpotLights));
    cls->defineFunction("setMainLight", _SE(js_scene_RenderScene_setMainLight));
    cls->defineFunction("update", _SE(js_scene_RenderScene_update));
    cls->defineFinalizeFunction(_SE(js_cc_scene_RenderScene_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::RenderScene>(cls);

    __jsb_cc_scene_RenderScene_proto = cls->getProto();
    __jsb_cc_scene_RenderScene_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_scene_RenderWindow_proto = nullptr;
se::Class* __jsb_cc_scene_RenderWindow_class = nullptr;

static bool js_scene_RenderWindow_get_hasOnScreenAttachments(se::State& s)
{
    cc::scene::RenderWindow* cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_get_hasOnScreenAttachments : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->hasOnScreenAttachments, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->hasOnScreenAttachments, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_RenderWindow_get_hasOnScreenAttachments)

static bool js_scene_RenderWindow_set_hasOnScreenAttachments(se::State& s)
{
    const auto& args = s.args();
    cc::scene::RenderWindow* cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_set_hasOnScreenAttachments : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->hasOnScreenAttachments, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_RenderWindow_set_hasOnScreenAttachments : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_RenderWindow_set_hasOnScreenAttachments)

static bool js_scene_RenderWindow_get_hasOffScreenAttachments(se::State& s)
{
    cc::scene::RenderWindow* cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_get_hasOffScreenAttachments : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->hasOffScreenAttachments, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->hasOffScreenAttachments, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_RenderWindow_get_hasOffScreenAttachments)

static bool js_scene_RenderWindow_set_hasOffScreenAttachments(se::State& s)
{
    const auto& args = s.args();
    cc::scene::RenderWindow* cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_set_hasOffScreenAttachments : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->hasOffScreenAttachments, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_RenderWindow_set_hasOffScreenAttachments : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_RenderWindow_set_hasOffScreenAttachments)

static bool js_scene_RenderWindow_get_frameBuffer(se::State& s)
{
    cc::scene::RenderWindow* cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_get_frameBuffer : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->frameBuffer, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->frameBuffer, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_RenderWindow_get_frameBuffer)

static bool js_scene_RenderWindow_set_frameBuffer(se::State& s)
{
    const auto& args = s.args();
    cc::scene::RenderWindow* cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_RenderWindow_set_frameBuffer : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->frameBuffer, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_RenderWindow_set_frameBuffer : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_RenderWindow_set_frameBuffer)


template<>
bool sevalue_to_native(const se::Value &from, cc::scene::RenderWindow * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cc::scene::RenderWindow*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("hasOnScreenAttachments", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->hasOnScreenAttachments), ctx);
    }
    json->getProperty("hasOffScreenAttachments", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->hasOffScreenAttachments), ctx);
    }
    json->getProperty("frameBuffer", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->frameBuffer), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_RenderWindow_finalize)

static bool js_scene_RenderWindow_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cc::scene::RenderWindow* cobj = JSB_ALLOC(cc::scene::RenderWindow);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::scene::RenderWindow* cobj = JSB_ALLOC(cc::scene::RenderWindow);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else
    {
        cc::scene::RenderWindow* cobj = JSB_ALLOC(cc::scene::RenderWindow);
        if (argc > 0 && !args[0].isUndefined()) {
            ok &= sevalue_to_native(args[0], &(cobj->hasOnScreenAttachments), nullptr);
        }
        if (argc > 1 && !args[1].isUndefined()) {
            ok &= sevalue_to_native(args[1], &(cobj->hasOffScreenAttachments), nullptr);
        }
        if (argc > 2 && !args[2].isUndefined()) {
            ok &= sevalue_to_native(args[2], &(cobj->frameBuffer), nullptr);
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_scene_RenderWindow_constructor, __jsb_cc_scene_RenderWindow_class, js_cc_scene_RenderWindow_finalize)




static bool js_cc_scene_RenderWindow_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::RenderWindow>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::scene::RenderWindow* cobj = SE_THIS_OBJECT<cc::scene::RenderWindow>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_RenderWindow_finalize)

bool js_register_scene_RenderWindow(se::Object* obj)
{
    auto cls = se::Class::create("RenderWindow", obj, nullptr, _SE(js_scene_RenderWindow_constructor));

    cls->defineProperty("hasOnScreenAttachments", _SE(js_scene_RenderWindow_get_hasOnScreenAttachments), _SE(js_scene_RenderWindow_set_hasOnScreenAttachments));
    cls->defineProperty("hasOffScreenAttachments", _SE(js_scene_RenderWindow_get_hasOffScreenAttachments), _SE(js_scene_RenderWindow_set_hasOffScreenAttachments));
    cls->defineProperty("frameBuffer", _SE(js_scene_RenderWindow_get_frameBuffer), _SE(js_scene_RenderWindow_set_frameBuffer));
    cls->defineFinalizeFunction(_SE(js_cc_scene_RenderWindow_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::RenderWindow>(cls);

    __jsb_cc_scene_RenderWindow_proto = cls->getProto();
    __jsb_cc_scene_RenderWindow_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cc_scene_Camera_proto = nullptr;
se::Class* __jsb_cc_scene_Camera_class = nullptr;

static bool js_scene_Camera_get_width(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->width, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->width, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_width)

static bool js_scene_Camera_set_width(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->width, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_width : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_width)

static bool js_scene_Camera_get_height(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->height, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->height, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_height)

static bool js_scene_Camera_set_height(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->height, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_height : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_height)

static bool js_scene_Camera_get_clearFlag(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_clearFlag : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->clearFlag, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->clearFlag, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_clearFlag)

static bool js_scene_Camera_set_clearFlag(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_clearFlag : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->clearFlag, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_clearFlag : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_clearFlag)

static bool js_scene_Camera_get_exposure(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_exposure : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->exposure, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->exposure, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_exposure)

static bool js_scene_Camera_set_exposure(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_exposure : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->exposure, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_exposure : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_exposure)

static bool js_scene_Camera_get_clearDepth(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_clearDepth : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->clearDepth, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->clearDepth, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_clearDepth)

static bool js_scene_Camera_set_clearDepth(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_clearDepth : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->clearDepth, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_clearDepth : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_clearDepth)

static bool js_scene_Camera_get_viewPort(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_viewPort : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->viewPort, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->viewPort, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_viewPort)

static bool js_scene_Camera_set_viewPort(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_viewPort : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->viewPort, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_viewPort : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_viewPort)

static bool js_scene_Camera_get_clearStencil(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_clearStencil : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->clearStencil, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->clearStencil, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_clearStencil)

static bool js_scene_Camera_set_clearStencil(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_clearStencil : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->clearStencil, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_clearStencil : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_clearStencil)

static bool js_scene_Camera_get_visibility(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_visibility : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->visibility, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->visibility, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_visibility)

static bool js_scene_Camera_set_visibility(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_visibility : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->visibility, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_visibility : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_visibility)

static bool js_scene_Camera_get_node(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_node : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->node, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->node, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_node)

static bool js_scene_Camera_set_node(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_node : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->node, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_node : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_node)

static bool js_scene_Camera_get_scene(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_scene : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->scene, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->scene, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_scene)

static bool js_scene_Camera_set_scene(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_scene : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->scene, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_scene : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_scene)

static bool js_scene_Camera_get_window(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_window : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->window, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->window, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_window)

static bool js_scene_Camera_set_window(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_window : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->window, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_window : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_window)

static bool js_scene_Camera_get_frustum(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_frustum : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->frustum, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->frustum, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_frustum)

static bool js_scene_Camera_set_frustum(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_frustum : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->frustum, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_frustum : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_frustum)

static bool js_scene_Camera_get_forward(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_forward : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->forward, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->forward, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_forward)

static bool js_scene_Camera_set_forward(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_forward : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->forward, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_forward : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_forward)

static bool js_scene_Camera_get_position(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_position : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->position, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->position, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_position)

static bool js_scene_Camera_set_position(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_position : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->position, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_position : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_position)

static bool js_scene_Camera_get_clearColor(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_clearColor : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->clearColor, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->clearColor, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_clearColor)

static bool js_scene_Camera_set_clearColor(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_clearColor : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->clearColor, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_clearColor : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_clearColor)

static bool js_scene_Camera_get_matView(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_matView : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->matView, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->matView, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_matView)

static bool js_scene_Camera_set_matView(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_matView : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->matView, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_matView : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_matView)

static bool js_scene_Camera_get_matViewProj(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_matViewProj : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->matViewProj, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->matViewProj, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_matViewProj)

static bool js_scene_Camera_set_matViewProj(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_matViewProj : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->matViewProj, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_matViewProj : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_matViewProj)

static bool js_scene_Camera_get_matViewProjInv(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_matViewProjInv : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->matViewProjInv, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->matViewProjInv, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_matViewProjInv)

static bool js_scene_Camera_set_matViewProjInv(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_matViewProjInv : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->matViewProjInv, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_matViewProjInv : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_matViewProjInv)

static bool js_scene_Camera_get_matProj(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_matProj : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->matProj, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->matProj, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_matProj)

static bool js_scene_Camera_set_matProj(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_matProj : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->matProj, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_matProj : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_matProj)

static bool js_scene_Camera_get_matProjInv(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_matProjInv : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->matProjInv, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->matProjInv, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_matProjInv)

static bool js_scene_Camera_set_matProjInv(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_matProjInv : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->matProjInv, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_matProjInv : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_matProjInv)

static bool js_scene_Camera_get_matViewProjOffscreen(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_matViewProjOffscreen : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->matViewProjOffscreen, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->matViewProjOffscreen, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_matViewProjOffscreen)

static bool js_scene_Camera_set_matViewProjOffscreen(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_matViewProjOffscreen : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->matViewProjOffscreen, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_matViewProjOffscreen : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_matViewProjOffscreen)

static bool js_scene_Camera_get_matViewProjInvOffscreen(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_matViewProjInvOffscreen : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->matViewProjInvOffscreen, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->matViewProjInvOffscreen, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_matViewProjInvOffscreen)

static bool js_scene_Camera_set_matViewProjInvOffscreen(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_matViewProjInvOffscreen : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->matViewProjInvOffscreen, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_matViewProjInvOffscreen : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_matViewProjInvOffscreen)

static bool js_scene_Camera_get_matProjOffscreen(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_matProjOffscreen : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->matProjOffscreen, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->matProjOffscreen, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_matProjOffscreen)

static bool js_scene_Camera_set_matProjOffscreen(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_matProjOffscreen : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->matProjOffscreen, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_matProjOffscreen : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_matProjOffscreen)

static bool js_scene_Camera_get_matProjInvOffscreen(se::State& s)
{
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_get_matProjInvOffscreen : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->matProjInvOffscreen, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    SE_HOLD_RETURN_VALUE(cobj->matProjInvOffscreen, s.thisObject(), s.rval());
    return true;
}
SE_BIND_PROP_GET(js_scene_Camera_get_matProjInvOffscreen)

static bool js_scene_Camera_set_matProjInvOffscreen(se::State& s)
{
    const auto& args = s.args();
    cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
    SE_PRECONDITION2(cobj, false, "js_scene_Camera_set_matProjInvOffscreen : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->matProjInvOffscreen, s.thisObject());
    SE_PRECONDITION2(ok, false, "js_scene_Camera_set_matProjInvOffscreen : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_scene_Camera_set_matProjInvOffscreen)


template<>
bool sevalue_to_native(const se::Value &from, cc::scene::Camera * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cc::scene::Camera*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("width", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->width), ctx);
    }
    json->getProperty("height", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->height), ctx);
    }
    json->getProperty("clearFlag", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->clearFlag), ctx);
    }
    json->getProperty("exposure", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->exposure), ctx);
    }
    json->getProperty("clearDepth", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->clearDepth), ctx);
    }
    json->getProperty("viewPort", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->viewPort), ctx);
    }
    json->getProperty("clearStencil", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->clearStencil), ctx);
    }
    json->getProperty("visibility", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->visibility), ctx);
    }
    json->getProperty("node", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->node), ctx);
    }
    json->getProperty("scene", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->scene), ctx);
    }
    json->getProperty("window", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->window), ctx);
    }
    json->getProperty("frustum", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->frustum), ctx);
    }
    json->getProperty("forward", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->forward), ctx);
    }
    json->getProperty("position", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->position), ctx);
    }
    json->getProperty("clearColor", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->clearColor), ctx);
    }
    json->getProperty("matView", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->matView), ctx);
    }
    json->getProperty("matViewProj", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->matViewProj), ctx);
    }
    json->getProperty("matViewProjInv", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->matViewProjInv), ctx);
    }
    json->getProperty("matProj", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->matProj), ctx);
    }
    json->getProperty("matProjInv", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->matProjInv), ctx);
    }
    json->getProperty("matViewProjOffscreen", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->matViewProjOffscreen), ctx);
    }
    json->getProperty("matViewProjInvOffscreen", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->matViewProjInvOffscreen), ctx);
    }
    json->getProperty("matProjOffscreen", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->matProjOffscreen), ctx);
    }
    json->getProperty("matProjInvOffscreen", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->matProjInvOffscreen), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cc_scene_Camera_finalize)

static bool js_scene_Camera_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cc::scene::Camera* cobj = JSB_ALLOC(cc::scene::Camera);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cc::scene::Camera* cobj = JSB_ALLOC(cc::scene::Camera);
        ok &= sevalue_to_native(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else
    {
        cc::scene::Camera* cobj = JSB_ALLOC(cc::scene::Camera);
        if (argc > 0 && !args[0].isUndefined()) {
            ok &= sevalue_to_native(args[0], &(cobj->width), nullptr);
        }
        if (argc > 1 && !args[1].isUndefined()) {
            ok &= sevalue_to_native(args[1], &(cobj->height), nullptr);
        }
        if (argc > 2 && !args[2].isUndefined()) {
            ok &= sevalue_to_native(args[2], &(cobj->clearFlag), nullptr);
        }
        if (argc > 3 && !args[3].isUndefined()) {
            ok &= sevalue_to_native(args[3], &(cobj->exposure), nullptr);
        }
        if (argc > 4 && !args[4].isUndefined()) {
            ok &= sevalue_to_native(args[4], &(cobj->clearDepth), nullptr);
        }
        if (argc > 5 && !args[5].isUndefined()) {
            ok &= sevalue_to_native(args[5], &(cobj->viewPort), nullptr);
        }
        if (argc > 6 && !args[6].isUndefined()) {
            ok &= sevalue_to_native(args[6], &(cobj->clearStencil), nullptr);
        }
        if (argc > 7 && !args[7].isUndefined()) {
            ok &= sevalue_to_native(args[7], &(cobj->visibility), nullptr);
        }
        if (argc > 8 && !args[8].isUndefined()) {
            ok &= sevalue_to_native(args[8], &(cobj->node), nullptr);
        }
        if (argc > 9 && !args[9].isUndefined()) {
            ok &= sevalue_to_native(args[9], &(cobj->scene), nullptr);
        }
        if (argc > 10 && !args[10].isUndefined()) {
            ok &= sevalue_to_native(args[10], &(cobj->window), nullptr);
        }
        if (argc > 11 && !args[11].isUndefined()) {
            ok &= sevalue_to_native(args[11], &(cobj->frustum), nullptr);
        }
        if (argc > 12 && !args[12].isUndefined()) {
            ok &= sevalue_to_native(args[12], &(cobj->forward), nullptr);
        }
        if (argc > 13 && !args[13].isUndefined()) {
            ok &= sevalue_to_native(args[13], &(cobj->position), nullptr);
        }
        if (argc > 14 && !args[14].isUndefined()) {
            ok &= sevalue_to_native(args[14], &(cobj->clearColor), nullptr);
        }
        if (argc > 15 && !args[15].isUndefined()) {
            ok &= sevalue_to_native(args[15], &(cobj->matView), nullptr);
        }
        if (argc > 16 && !args[16].isUndefined()) {
            ok &= sevalue_to_native(args[16], &(cobj->matViewProj), nullptr);
        }
        if (argc > 17 && !args[17].isUndefined()) {
            ok &= sevalue_to_native(args[17], &(cobj->matViewProjInv), nullptr);
        }
        if (argc > 18 && !args[18].isUndefined()) {
            ok &= sevalue_to_native(args[18], &(cobj->matProj), nullptr);
        }
        if (argc > 19 && !args[19].isUndefined()) {
            ok &= sevalue_to_native(args[19], &(cobj->matProjInv), nullptr);
        }
        if (argc > 20 && !args[20].isUndefined()) {
            ok &= sevalue_to_native(args[20], &(cobj->matViewProjOffscreen), nullptr);
        }
        if (argc > 21 && !args[21].isUndefined()) {
            ok &= sevalue_to_native(args[21], &(cobj->matViewProjInvOffscreen), nullptr);
        }
        if (argc > 22 && !args[22].isUndefined()) {
            ok &= sevalue_to_native(args[22], &(cobj->matProjOffscreen), nullptr);
        }
        if (argc > 23 && !args[23].isUndefined()) {
            ok &= sevalue_to_native(args[23], &(cobj->matProjInvOffscreen), nullptr);
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_scene_Camera_constructor, __jsb_cc_scene_Camera_class, js_cc_scene_Camera_finalize)




static bool js_cc_scene_Camera_finalize(se::State& s)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::scene::Camera>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cc::scene::Camera* cobj = SE_THIS_OBJECT<cc::scene::Camera>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_scene_Camera_finalize)

bool js_register_scene_Camera(se::Object* obj)
{
    auto cls = se::Class::create("Camera", obj, nullptr, _SE(js_scene_Camera_constructor));

    cls->defineProperty("width", _SE(js_scene_Camera_get_width), _SE(js_scene_Camera_set_width));
    cls->defineProperty("height", _SE(js_scene_Camera_get_height), _SE(js_scene_Camera_set_height));
    cls->defineProperty("clearFlag", _SE(js_scene_Camera_get_clearFlag), _SE(js_scene_Camera_set_clearFlag));
    cls->defineProperty("exposure", _SE(js_scene_Camera_get_exposure), _SE(js_scene_Camera_set_exposure));
    cls->defineProperty("clearDepth", _SE(js_scene_Camera_get_clearDepth), _SE(js_scene_Camera_set_clearDepth));
    cls->defineProperty("viewPort", _SE(js_scene_Camera_get_viewPort), _SE(js_scene_Camera_set_viewPort));
    cls->defineProperty("clearStencil", _SE(js_scene_Camera_get_clearStencil), _SE(js_scene_Camera_set_clearStencil));
    cls->defineProperty("visibility", _SE(js_scene_Camera_get_visibility), _SE(js_scene_Camera_set_visibility));
    cls->defineProperty("node", _SE(js_scene_Camera_get_node), _SE(js_scene_Camera_set_node));
    cls->defineProperty("scene", _SE(js_scene_Camera_get_scene), _SE(js_scene_Camera_set_scene));
    cls->defineProperty("window", _SE(js_scene_Camera_get_window), _SE(js_scene_Camera_set_window));
    cls->defineProperty("frustum", _SE(js_scene_Camera_get_frustum), _SE(js_scene_Camera_set_frustum));
    cls->defineProperty("forward", _SE(js_scene_Camera_get_forward), _SE(js_scene_Camera_set_forward));
    cls->defineProperty("position", _SE(js_scene_Camera_get_position), _SE(js_scene_Camera_set_position));
    cls->defineProperty("clearColor", _SE(js_scene_Camera_get_clearColor), _SE(js_scene_Camera_set_clearColor));
    cls->defineProperty("matView", _SE(js_scene_Camera_get_matView), _SE(js_scene_Camera_set_matView));
    cls->defineProperty("matViewProj", _SE(js_scene_Camera_get_matViewProj), _SE(js_scene_Camera_set_matViewProj));
    cls->defineProperty("matViewProjInv", _SE(js_scene_Camera_get_matViewProjInv), _SE(js_scene_Camera_set_matViewProjInv));
    cls->defineProperty("matProj", _SE(js_scene_Camera_get_matProj), _SE(js_scene_Camera_set_matProj));
    cls->defineProperty("matProjInv", _SE(js_scene_Camera_get_matProjInv), _SE(js_scene_Camera_set_matProjInv));
    cls->defineProperty("matViewProjOffscreen", _SE(js_scene_Camera_get_matViewProjOffscreen), _SE(js_scene_Camera_set_matViewProjOffscreen));
    cls->defineProperty("matViewProjInvOffscreen", _SE(js_scene_Camera_get_matViewProjInvOffscreen), _SE(js_scene_Camera_set_matViewProjInvOffscreen));
    cls->defineProperty("matProjOffscreen", _SE(js_scene_Camera_get_matProjOffscreen), _SE(js_scene_Camera_set_matProjOffscreen));
    cls->defineProperty("matProjInvOffscreen", _SE(js_scene_Camera_get_matProjInvOffscreen), _SE(js_scene_Camera_set_matProjInvOffscreen));
    cls->defineFinalizeFunction(_SE(js_cc_scene_Camera_finalize));
    cls->install();
    JSBClassType::registerClass<cc::scene::Camera>(cls);

    __jsb_cc_scene_Camera_proto = cls->getProto();
    __jsb_cc_scene_Camera_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
bool register_all_scene(se::Object* obj)
{
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("ns", &nsVal))
    {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("ns", nsVal);
    }
    se::Object* ns = nsVal.toObject();

    js_register_scene_Node(ns);
    js_register_scene_RenderScene(ns);
    js_register_scene_Camera(ns);
    js_register_scene_Frustum(ns);
    js_register_scene_Light(ns);
    js_register_scene_DrawBatch2D(ns);
    js_register_scene_SphereLight(ns);
    js_register_scene_SubModel(ns);
    js_register_scene_RenderWindow(ns);
    js_register_scene_Plane(ns);
    js_register_scene_Pass(ns);
    js_register_scene_DirectionalLight(ns);
    js_register_scene_Model(ns);
    js_register_scene_SpotLight(ns);
    return true;
}

