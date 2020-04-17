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
    auto cls = se::Class::create("DownloaderHints", obj, nullptr, nullptr);

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
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
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
            ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
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
