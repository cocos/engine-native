#include "cocos/bindings/auto/jsb_ar_auto.h"
#if USE_AR_MODULE > 0
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/bindings/manual/jsb_global.h"
#include "ar/ARModule.h"

#ifndef JSB_ALLOC
#define JSB_ALLOC(kls, ...) new (std::nothrow) kls(__VA_ARGS__)
#endif

#ifndef JSB_FREE
#define JSB_FREE(ptr) delete ptr
#endif
se::Object* __jsb_cc_ar_ARModule_proto = nullptr;
se::Class* __jsb_cc_ar_ARModule_class = nullptr;

static bool js_ar_ARModule_setCameraTextureName(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ar::ARModule>(s);
    SE_PRECONDITION2(cobj, false, "js_ar_ARModule_setCameraTextureName : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<int, false> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_ar_ARModule_setCameraTextureName : Error processing arguments");
        cobj->setCameraTextureName(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_ar_ARModule_setCameraTextureName)

static bool js_ar_ARModule_start(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ar::ARModule>(s);
    SE_PRECONDITION2(cobj, false, "js_ar_ARModule_start : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->start();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_ar_ARModule_start)

static bool js_ar_ARModule_onResume(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ar::ARModule>(s);
    SE_PRECONDITION2(cobj, false, "js_ar_ARModule_onResume : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onResume();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_ar_ARModule_onResume)

static bool js_ar_ARModule_onPause(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ar::ARModule>(s);
    SE_PRECONDITION2(cobj, false, "js_ar_ARModule_onPause : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->onPause();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_ar_ARModule_onPause)

static bool js_ar_ARModule_update(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto* cobj = SE_THIS_OBJECT<cc::ar::ARModule>(s);
    SE_PRECONDITION2(cobj, false, "js_ar_ARModule_update : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->update();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_ar_ARModule_update)

SE_DECLARE_FINALIZE_FUNC(js_cc_ar_ARModule_finalize)

static bool js_ar_ARModule_constructor(se::State& s) // NOLINT(readability-identifier-naming) constructor.c
{
    cc::ar::ARModule* cobj = JSB_ALLOC(cc::ar::ARModule);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_ar_ARModule_constructor, __jsb_cc_ar_ARModule_class, js_cc_ar_ARModule_finalize)



static bool js_cc_ar_ARModule_finalize(se::State& s) // NOLINT(readability-identifier-naming)
{
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cc::ar::ARModule>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        auto* cobj = SE_THIS_OBJECT<cc::ar::ARModule>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cc_ar_ARModule_finalize)

bool js_register_ar_ARModule(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("ARModule", obj, nullptr, _SE(js_ar_ARModule_constructor));

    cls->defineFunction("setCameraTextureName", _SE(js_ar_ARModule_setCameraTextureName));
    cls->defineFunction("start", _SE(js_ar_ARModule_start));
    cls->defineFunction("onResume", _SE(js_ar_ARModule_onResume));
    cls->defineFunction("onPause", _SE(js_ar_ARModule_onPause));
    cls->defineFunction("update", _SE(js_ar_ARModule_update));
    cls->defineFinalizeFunction(_SE(js_cc_ar_ARModule_finalize));
    cls->install();
    JSBClassType::registerClass<cc::ar::ARModule>(cls);

    __jsb_cc_ar_ARModule_proto = cls->getProto();
    __jsb_cc_ar_ARModule_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
bool register_all_ar(se::Object* obj)
{
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("jsb", &nsVal))
    {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("jsb", nsVal);
    }
    se::Object* ns = nsVal.toObject();

    js_register_ar_ARModule(ns);
    return true;
}

#endif //#if USE_AR_MODULE > 0
