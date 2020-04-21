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
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::network::DownloadTask)", SE_THIS_OBJECT<cocos2d::network::DownloadTask>(s););
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cocos2d::network::DownloadTask>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::network::DownloadTask* cobj = SE_THIS_OBJECT<cocos2d::network::DownloadTask>(s);
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
    
    if constexpr (std::is_standard_layout_v<cocos2d::network::DownloadTask>) {
        auto array = se::Object::createArrayObject(0);
        int idx = 0;
        {
            //identifier : basic_string
            using field_type = decltype(cocos2d::network::DownloadTask::identifier);
            auto attr = se::Object::createPlainObject();
            attr->setProperty("name", se::Value("identifier"));
            attr->setProperty("offset", se::Value(offsetof(cocos2d::network::DownloadTask, identifier)));
            attr->setProperty("size", se::Value(sizeof(field_type)));
            attr->setProperty("type", se::Value(SE_UNDERLYING_TYPE_NAME<field_type>()));
            array->setArrayElement(idx++, se::Value(attr));
            attr->decRef();
        }
        {
            //requestURL : basic_string
            using field_type = decltype(cocos2d::network::DownloadTask::requestURL);
            auto attr = se::Object::createPlainObject();
            attr->setProperty("name", se::Value("requestURL"));
            attr->setProperty("offset", se::Value(offsetof(cocos2d::network::DownloadTask, requestURL)));
            attr->setProperty("size", se::Value(sizeof(field_type)));
            attr->setProperty("type", se::Value(SE_UNDERLYING_TYPE_NAME<field_type>()));
            array->setArrayElement(idx++, se::Value(attr));
            attr->decRef();
        }
        {
            //storagePath : basic_string
            using field_type = decltype(cocos2d::network::DownloadTask::storagePath);
            auto attr = se::Object::createPlainObject();
            attr->setProperty("name", se::Value("storagePath"));
            attr->setProperty("offset", se::Value(offsetof(cocos2d::network::DownloadTask, storagePath)));
            attr->setProperty("size", se::Value(sizeof(field_type)));
            attr->setProperty("type", se::Value(SE_UNDERLYING_TYPE_NAME<field_type>()));
            array->setArrayElement(idx++, se::Value(attr));
            attr->decRef();
        }
        {
            //header : map<std::string, std::string>
            using field_type = decltype(cocos2d::network::DownloadTask::header);
            auto attr = se::Object::createPlainObject();
            attr->setProperty("name", se::Value("header"));
            attr->setProperty("offset", se::Value(offsetof(cocos2d::network::DownloadTask, header)));
            attr->setProperty("size", se::Value(sizeof(field_type)));
            attr->setProperty("type", se::Value(SE_UNDERLYING_TYPE_NAME<field_type>()));
            array->setArrayElement(idx++, se::Value(attr));
            attr->decRef();
        }
        cls->getProto()->setProperty("__attrMeta", se::Value(array));
        //obj->setProperty("__attrMeta_DownloadTask", se::Value(array));
        array->decRef();
    }

    __jsb_cocos2d_network_DownloadTask_proto = cls->getProto();
    __jsb_cocos2d_network_DownloadTask_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_network_DownloaderHints_proto = nullptr;
se::Class* __jsb_cocos2d_network_DownloaderHints_class = nullptr;

static bool js_network_DownloaderHints_get_countOfMaxProcessingTasks(se::State& s)
{
    cocos2d::network::DownloaderHints* cobj = SE_THIS_OBJECT<cocos2d::network::DownloaderHints>(s);
    SE_PRECONDITION2(cobj, false, "js_network_DownloaderHints_get_countOfMaxProcessingTasks : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->countOfMaxProcessingTasks, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_network_DownloaderHints_get_countOfMaxProcessingTasks)

static bool js_network_DownloaderHints_set_countOfMaxProcessingTasks(se::State& s)
{
    const auto& args = s.args();
    cocos2d::network::DownloaderHints* cobj = SE_THIS_OBJECT<cocos2d::network::DownloaderHints>(s);
    SE_PRECONDITION2(cobj, false, "js_network_DownloaderHints_set_countOfMaxProcessingTasks : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->countOfMaxProcessingTasks, s.thisObject()); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_network_DownloaderHints_set_countOfMaxProcessingTasks : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_network_DownloaderHints_set_countOfMaxProcessingTasks)

static bool js_network_DownloaderHints_get_timeoutInSeconds(se::State& s)
{
    cocos2d::network::DownloaderHints* cobj = SE_THIS_OBJECT<cocos2d::network::DownloaderHints>(s);
    SE_PRECONDITION2(cobj, false, "js_network_DownloaderHints_get_timeoutInSeconds : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->timeoutInSeconds, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_network_DownloaderHints_get_timeoutInSeconds)

static bool js_network_DownloaderHints_set_timeoutInSeconds(se::State& s)
{
    const auto& args = s.args();
    cocos2d::network::DownloaderHints* cobj = SE_THIS_OBJECT<cocos2d::network::DownloaderHints>(s);
    SE_PRECONDITION2(cobj, false, "js_network_DownloaderHints_set_timeoutInSeconds : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->timeoutInSeconds, s.thisObject()); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_network_DownloaderHints_set_timeoutInSeconds : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_network_DownloaderHints_set_timeoutInSeconds)

static bool js_network_DownloaderHints_get_tempFileNameSuffix(se::State& s)
{
    cocos2d::network::DownloaderHints* cobj = SE_THIS_OBJECT<cocos2d::network::DownloaderHints>(s);
    SE_PRECONDITION2(cobj, false, "js_network_DownloaderHints_get_tempFileNameSuffix : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->tempFileNameSuffix, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_network_DownloaderHints_get_tempFileNameSuffix)

static bool js_network_DownloaderHints_set_tempFileNameSuffix(se::State& s)
{
    const auto& args = s.args();
    cocos2d::network::DownloaderHints* cobj = SE_THIS_OBJECT<cocos2d::network::DownloaderHints>(s);
    SE_PRECONDITION2(cobj, false, "js_network_DownloaderHints_set_tempFileNameSuffix : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->tempFileNameSuffix, s.thisObject()); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_network_DownloaderHints_set_tempFileNameSuffix : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_network_DownloaderHints_set_tempFileNameSuffix)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::network::DownloaderHints * to, se::Object *ctx)
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
        ok &= sevalue_to_native(field, &(to->countOfMaxProcessingTasks), ctx);
    }
    json->getProperty("timeoutInSeconds", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->timeoutInSeconds), ctx);
    }
    json->getProperty("tempFileNameSuffix", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->tempFileNameSuffix), ctx);
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
    else if(argc == 3)
    {
        cocos2d::network::DownloaderHints* cobj = JSB_ALLOC(cocos2d::network::DownloaderHints);
        unsigned int arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference False;
            cobj->countOfMaxProcessingTasks = arg0;
        }
        unsigned int arg1 = {};
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1, nullptr); //is_reference False;
            cobj->timeoutInSeconds = arg1;
        }
        std::string arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2, nullptr); //is_reference False;
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
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::network::DownloaderHints)", SE_THIS_OBJECT<cocos2d::network::DownloaderHints>(s););
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cocos2d::network::DownloaderHints>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::network::DownloaderHints* cobj = SE_THIS_OBJECT<cocos2d::network::DownloaderHints>(s);
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
    
    if constexpr (std::is_standard_layout_v<cocos2d::network::DownloaderHints>) {
        auto array = se::Object::createArrayObject(0);
        int idx = 0;
        {
            //countOfMaxProcessingTasks : unsigned int
            using field_type = decltype(cocos2d::network::DownloaderHints::countOfMaxProcessingTasks);
            auto attr = se::Object::createPlainObject();
            attr->setProperty("name", se::Value("countOfMaxProcessingTasks"));
            attr->setProperty("offset", se::Value(offsetof(cocos2d::network::DownloaderHints, countOfMaxProcessingTasks)));
            attr->setProperty("size", se::Value(sizeof(field_type)));
            attr->setProperty("type", se::Value(SE_UNDERLYING_TYPE_NAME<field_type>()));
            array->setArrayElement(idx++, se::Value(attr));
            attr->decRef();
        }
        {
            //timeoutInSeconds : unsigned int
            using field_type = decltype(cocos2d::network::DownloaderHints::timeoutInSeconds);
            auto attr = se::Object::createPlainObject();
            attr->setProperty("name", se::Value("timeoutInSeconds"));
            attr->setProperty("offset", se::Value(offsetof(cocos2d::network::DownloaderHints, timeoutInSeconds)));
            attr->setProperty("size", se::Value(sizeof(field_type)));
            attr->setProperty("type", se::Value(SE_UNDERLYING_TYPE_NAME<field_type>()));
            array->setArrayElement(idx++, se::Value(attr));
            attr->decRef();
        }
        {
            //tempFileNameSuffix : basic_string
            using field_type = decltype(cocos2d::network::DownloaderHints::tempFileNameSuffix);
            auto attr = se::Object::createPlainObject();
            attr->setProperty("name", se::Value("tempFileNameSuffix"));
            attr->setProperty("offset", se::Value(offsetof(cocos2d::network::DownloaderHints, tempFileNameSuffix)));
            attr->setProperty("size", se::Value(sizeof(field_type)));
            attr->setProperty("type", se::Value(SE_UNDERLYING_TYPE_NAME<field_type>()));
            array->setArrayElement(idx++, se::Value(attr));
            attr->decRef();
        }
        cls->getProto()->setProperty("__attrMeta", se::Value(array));
        //obj->setProperty("__attrMeta_DownloaderHints", se::Value(array));
        array->decRef();
    }

    __jsb_cocos2d_network_DownloaderHints_proto = cls->getProto();
    __jsb_cocos2d_network_DownloaderHints_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_network_Downloader_proto = nullptr;
se::Class* __jsb_cocos2d_network_Downloader_class = nullptr;

static bool js_network_Downloader_setOnTaskProgress(se::State& s)
{
    cocos2d::network::Downloader* cobj = SE_THIS_OBJECT<cocos2d::network::Downloader>(s);
    SE_PRECONDITION2(cobj, false, "js_network_Downloader_setOnTaskProgress : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::function<void (const cocos2d::network::DownloadTask &, long long, long long, long long)>, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
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
            HolderType<cocos2d::network::DownloaderHints, false>::local_type arg0 = {};
            ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference False;
            if (!ok) { ok = true; break; }
            cocos2d::network::Downloader* cobj = JSB_ALLOC(cocos2d::network::Downloader, HolderType<cocos2d::network::DownloaderHints, false>::value(arg0));
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
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::network::Downloader)", SE_THIS_OBJECT<cocos2d::network::Downloader>(s););
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cocos2d::network::Downloader>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::network::Downloader* cobj = SE_THIS_OBJECT<cocos2d::network::Downloader>(s);
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
    
    if constexpr (std::is_standard_layout_v<cocos2d::network::Downloader>) {
        auto array = se::Object::createArrayObject(0);
        int idx = 0;
        {
            //onDataTaskSuccess : std::function
            using field_type = decltype(cocos2d::network::Downloader::onDataTaskSuccess);
            auto attr = se::Object::createPlainObject();
            attr->setProperty("name", se::Value("onDataTaskSuccess"));
            attr->setProperty("offset", se::Value(offsetof(cocos2d::network::Downloader, onDataTaskSuccess)));
            attr->setProperty("size", se::Value(sizeof(field_type)));
            attr->setProperty("type", se::Value(SE_UNDERLYING_TYPE_NAME<field_type>()));
            array->setArrayElement(idx++, se::Value(attr));
            attr->decRef();
        }
        {
            //onFileTaskSuccess : std::function
            using field_type = decltype(cocos2d::network::Downloader::onFileTaskSuccess);
            auto attr = se::Object::createPlainObject();
            attr->setProperty("name", se::Value("onFileTaskSuccess"));
            attr->setProperty("offset", se::Value(offsetof(cocos2d::network::Downloader, onFileTaskSuccess)));
            attr->setProperty("size", se::Value(sizeof(field_type)));
            attr->setProperty("type", se::Value(SE_UNDERLYING_TYPE_NAME<field_type>()));
            array->setArrayElement(idx++, se::Value(attr));
            attr->decRef();
        }
        {
            //onTaskProgress : std::function
            using field_type = decltype(cocos2d::network::Downloader::onTaskProgress);
            auto attr = se::Object::createPlainObject();
            attr->setProperty("name", se::Value("onTaskProgress"));
            attr->setProperty("offset", se::Value(offsetof(cocos2d::network::Downloader, onTaskProgress)));
            attr->setProperty("size", se::Value(sizeof(field_type)));
            attr->setProperty("type", se::Value(SE_UNDERLYING_TYPE_NAME<field_type>()));
            array->setArrayElement(idx++, se::Value(attr));
            attr->decRef();
        }
        {
            //onTaskError : std::function
            using field_type = decltype(cocos2d::network::Downloader::onTaskError);
            auto attr = se::Object::createPlainObject();
            attr->setProperty("name", se::Value("onTaskError"));
            attr->setProperty("offset", se::Value(offsetof(cocos2d::network::Downloader, onTaskError)));
            attr->setProperty("size", se::Value(sizeof(field_type)));
            attr->setProperty("type", se::Value(SE_UNDERLYING_TYPE_NAME<field_type>()));
            array->setArrayElement(idx++, se::Value(attr));
            attr->decRef();
        }
        cls->getProto()->setProperty("__attrMeta", se::Value(array));
        //obj->setProperty("__attrMeta_Downloader", se::Value(array));
        array->decRef();
    }

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
