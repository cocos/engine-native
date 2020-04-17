#include "scripting/js-bindings/auto/jsb_cocos2dx_network_auto.hpp"
#if (CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_MAC_IOS || CC_PLATFORM == CC_PLATFORM_MAC_OSX || CC_PLATFORM == CC_PLATFORM_WINDOWS)
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "network/CCDownloader.h"

#ifndef JSB_ALLOC
#define JSB_ALLOC(kls, ...) new (std::nothrow) kls(__VA_ARGS__)
#endif

#ifndef JSB_FREE
#define JSB_FREE(ptr) delete ptr
#endif
se::Object* __jsb_cocos2d_network_DownloadTask_proto = nullptr;
se::Class* __jsb_cocos2d_network_DownloadTask_class = nullptr;

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_network_DownloadTask_finalize)

static bool js_network_DownloadTask_constructor(se::State& s) // constructor.c
{
    cocos2d::network::DownloadTask* cobj = JSB_ALLOC(cocos2d::network::DownloadTask);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_network_DownloadTask_constructor, __jsb_cocos2d_network_DownloadTask_class, js_cocos2d_network_DownloadTask_finalize)




static bool js_cocos2d_network_DownloadTask_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::network::DownloadTask)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::network::DownloadTask* cobj = (cocos2d::network::DownloadTask*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_network_DownloadTask_finalize)

bool js_register_network_DownloadTask(se::Object* obj)
{
    auto cls = se::Class::create("DownloadTask", obj, nullptr, _SE(js_network_DownloadTask_constructor));

    cls->defineFinalizeFunction(_SE(js_cocos2d_network_DownloadTask_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::network::DownloadTask>(cls);

    __jsb_cocos2d_network_DownloadTask_proto = cls->getProto();
    __jsb_cocos2d_network_DownloadTask_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_network_DownloaderHints_proto = nullptr;
se::Class* __jsb_cocos2d_network_DownloaderHints_class = nullptr;

static bool js_network_DownloaderHints_get_countOfMaxProcessingTasks(se::State& s)
{
    cocos2d::network::DownloaderHints* cobj = (cocos2d::network::DownloaderHints*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_network_DownloaderHints_get_countOfMaxProcessingTasks : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= NATIVEVALUE_TO_SE(cobj->countOfMaxProcessingTasks, jsret, nullptr /*ctx*/);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_network_DownloaderHints_get_countOfMaxProcessingTasks)

static bool js_network_DownloaderHints_set_countOfMaxProcessingTasks(se::State& s)
{
    const auto& args = s.args();
    cocos2d::network::DownloaderHints* cobj = (cocos2d::network::DownloaderHints*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_network_DownloaderHints_set_countOfMaxProcessingTasks : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= SEVALUE_TO_NATIVE(args[0], &cobj->countOfMaxProcessingTasks, nullptr); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_network_DownloaderHints_set_countOfMaxProcessingTasks : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_network_DownloaderHints_set_countOfMaxProcessingTasks)

static bool js_network_DownloaderHints_get_timeoutInSeconds(se::State& s)
{
    cocos2d::network::DownloaderHints* cobj = (cocos2d::network::DownloaderHints*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_network_DownloaderHints_get_timeoutInSeconds : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= NATIVEVALUE_TO_SE(cobj->timeoutInSeconds, jsret, nullptr /*ctx*/);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_network_DownloaderHints_get_timeoutInSeconds)

static bool js_network_DownloaderHints_set_timeoutInSeconds(se::State& s)
{
    const auto& args = s.args();
    cocos2d::network::DownloaderHints* cobj = (cocos2d::network::DownloaderHints*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_network_DownloaderHints_set_timeoutInSeconds : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= SEVALUE_TO_NATIVE(args[0], &cobj->timeoutInSeconds, nullptr); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_network_DownloaderHints_set_timeoutInSeconds : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_network_DownloaderHints_set_timeoutInSeconds)

static bool js_network_DownloaderHints_get_tempFileNameSuffix(se::State& s)
{
    cocos2d::network::DownloaderHints* cobj = (cocos2d::network::DownloaderHints*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_network_DownloaderHints_get_tempFileNameSuffix : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= NATIVEVALUE_TO_SE(cobj->tempFileNameSuffix, jsret, nullptr /*ctx*/);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_network_DownloaderHints_get_tempFileNameSuffix)

static bool js_network_DownloaderHints_set_tempFileNameSuffix(se::State& s)
{
    const auto& args = s.args();
    cocos2d::network::DownloaderHints* cobj = (cocos2d::network::DownloaderHints*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_network_DownloaderHints_set_tempFileNameSuffix : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= SEVALUE_TO_NATIVE(args[0], &cobj->tempFileNameSuffix, nullptr); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_network_DownloaderHints_set_tempFileNameSuffix : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_network_DownloaderHints_set_tempFileNameSuffix)


template<>
bool SEVALUE_TO_NATIVE(const se::Value &from, cocos2d::network::DownloaderHints * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::network::DownloaderHints*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("countOfMaxProcessingTasks", &field);
    if(!field.isNullOrUndefined()) {
        ok &= SEVALUE_TO_NATIVE(field, &(to->countOfMaxProcessingTasks), ctx);
    }
    json->getProperty("timeoutInSeconds", &field);
    if(!field.isNullOrUndefined()) {
        ok &= SEVALUE_TO_NATIVE(field, &(to->timeoutInSeconds), ctx);
    }
    json->getProperty("tempFileNameSuffix", &field);
    if(!field.isNullOrUndefined()) {
        ok &= SEVALUE_TO_NATIVE(field, &(to->tempFileNameSuffix), ctx);
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_network_DownloaderHints_finalize)

static bool js_network_DownloaderHints_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::network::DownloaderHints* cobj = JSB_ALLOC(cocos2d::network::DownloaderHints);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::network::DownloaderHints* cobj = JSB_ALLOC(cocos2d::network::DownloaderHints);
        ok &= SEVALUE_TO_NATIVE(args[0], cobj, s.thisObject());
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 3)
    {
        cocos2d::network::DownloaderHints* cobj = JSB_ALLOC(cocos2d::network::DownloaderHints);
        unsigned int arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= SEVALUE_TO_NATIVE(args[0], &arg0, nullptr); //is_reference False;
            cobj->countOfMaxProcessingTasks = arg0;
        }
        unsigned int arg1 = {};
        if (!args[1].isNullOrUndefined()) {
            ok &= SEVALUE_TO_NATIVE(args[1], &arg1, nullptr); //is_reference False;
            cobj->timeoutInSeconds = arg1;
        }
        std::string arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= SEVALUE_TO_NATIVE(args[2], &arg2, nullptr); //is_reference False;
            cobj->tempFileNameSuffix = arg2;
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
SE_BIND_CTOR(js_network_DownloaderHints_constructor, __jsb_cocos2d_network_DownloaderHints_class, js_cocos2d_network_DownloaderHints_finalize)




static bool js_cocos2d_network_DownloaderHints_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::network::DownloaderHints)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::network::DownloaderHints* cobj = (cocos2d::network::DownloaderHints*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_network_DownloaderHints_finalize)

bool js_register_network_DownloaderHints(se::Object* obj)
{
    auto cls = se::Class::create("DownloaderHints", obj, nullptr, _SE(js_network_DownloaderHints_constructor));

    cls->defineProperty("countOfMaxProcessingTasks", _SE(js_network_DownloaderHints_get_countOfMaxProcessingTasks), _SE(js_network_DownloaderHints_set_countOfMaxProcessingTasks));
    cls->defineProperty("timeoutInSeconds", _SE(js_network_DownloaderHints_get_timeoutInSeconds), _SE(js_network_DownloaderHints_set_timeoutInSeconds));
    cls->defineProperty("tempFileNameSuffix", _SE(js_network_DownloaderHints_get_tempFileNameSuffix), _SE(js_network_DownloaderHints_set_tempFileNameSuffix));
    cls->defineFinalizeFunction(_SE(js_cocos2d_network_DownloaderHints_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::network::DownloaderHints>(cls);

    __jsb_cocos2d_network_DownloaderHints_proto = cls->getProto();
    __jsb_cocos2d_network_DownloaderHints_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_network_Downloader_proto = nullptr;
se::Class* __jsb_cocos2d_network_Downloader_class = nullptr;

static bool js_network_Downloader_setOnTaskProgress(se::State& s)
{
    cocos2d::network::Downloader* cobj = (cocos2d::network::Downloader*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_network_Downloader_setOnTaskProgress : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::function<void (const cocos2d::network::DownloadTask &, long long, long long, long long)>, true>::local_type arg0 = {};
        ok &= SEVALUE_TO_NATIVE(args[0], &arg0, s.thisObject()); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_network_Downloader_setOnTaskProgress : Error processing arguments");
        cobj->setOnTaskProgress(HolderType<std::function<void (const cocos2d::network::DownloadTask &, long long, long long, long long)>, true>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_network_Downloader_setOnTaskProgress)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_network_Downloader_finalize)

static bool js_network_Downloader_constructor(se::State& s)  // constructor_overloaded.c
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();
    do {
        if (argc == 1) {
            HolderType<cocos2d::network::DownloaderHints, true>::local_type arg0 = {};
            ok &= SEVALUE_TO_NATIVE(args[0], &arg0, s.thisObject()); //is_reference True;
            if (!ok) { ok = true; break; }
            cocos2d::network::Downloader* cobj = JSB_ALLOC(cocos2d::network::Downloader, HolderType<cocos2d::network::DownloaderHints, true>::value(arg0));
            s.thisObject()->setPrivateData(cobj);
            se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
            return true;
        }
    } while(false);
    do {
        if (argc == 0) {
            cocos2d::network::Downloader* cobj = JSB_ALLOC(cocos2d::network::Downloader);
            s.thisObject()->setPrivateData(cobj);
            se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
            return true;
        }
    } while(false);
    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_network_Downloader_constructor, __jsb_cocos2d_network_Downloader_class, js_cocos2d_network_Downloader_finalize)




static bool js_cocos2d_network_Downloader_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::network::Downloader)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::network::Downloader* cobj = (cocos2d::network::Downloader*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_network_Downloader_finalize)

bool js_register_network_Downloader(se::Object* obj)
{
    auto cls = se::Class::create("Downloader", obj, nullptr, _SE(js_network_Downloader_constructor));

    cls->defineFunction("setOnTaskProgress", _SE(js_network_Downloader_setOnTaskProgress));
    cls->defineFinalizeFunction(_SE(js_cocos2d_network_Downloader_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::network::Downloader>(cls);

    __jsb_cocos2d_network_Downloader_proto = cls->getProto();
    __jsb_cocos2d_network_Downloader_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

bool register_all_network(se::Object* obj)
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

    js_register_network_DownloaderHints(ns);
    js_register_network_DownloadTask(ns);
    js_register_network_Downloader(ns);
    return true;
}

#endif //#if (CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_MAC_IOS || CC_PLATFORM == CC_PLATFORM_MAC_OSX || CC_PLATFORM == CC_PLATFORM_WINDOWS)
