#include "scripting/js-bindings/auto/jsb_cocos2dx_audioengine_auto.hpp"
#if (USE_AUDIO > 0) && (CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_MAC_IOS || CC_PLATFORM == CC_PLATFORM_MAC_OSX || CC_PLATFORM == CC_PLATFORM_WINDOWS)
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "audio/include/AudioEngine.h"

#ifndef JSB_ALLOC
#define JSB_ALLOC(kls, ...) new (std::nothrow) kls(__VA_ARGS__)
#endif

#ifndef JSB_FREE
#define JSB_FREE(ptr) delete ptr
#endif
se::Object* __jsb_cocos2d_AudioProfile_proto = nullptr;
se::Class* __jsb_cocos2d_AudioProfile_class = nullptr;

static bool js_audioengine_AudioProfile_get_name(se::State& s)
{
    cocos2d::AudioProfile* cobj = SE_THIS_OBJECT<cocos2d::AudioProfile>(s);
    SE_PRECONDITION2(cobj, false, "js_audioengine_AudioProfile_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_audioengine_AudioProfile_get_name)

static bool js_audioengine_AudioProfile_set_name(se::State& s)
{
    const auto& args = s.args();
    cocos2d::AudioProfile* cobj = SE_THIS_OBJECT<cocos2d::AudioProfile>(s);
    SE_PRECONDITION2(cobj, false, "js_audioengine_AudioProfile_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name, s.thisObject()); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_audioengine_AudioProfile_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_audioengine_AudioProfile_set_name)

static bool js_audioengine_AudioProfile_get_maxInstances(se::State& s)
{
    cocos2d::AudioProfile* cobj = SE_THIS_OBJECT<cocos2d::AudioProfile>(s);
    SE_PRECONDITION2(cobj, false, "js_audioengine_AudioProfile_get_maxInstances : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->maxInstances, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_audioengine_AudioProfile_get_maxInstances)

static bool js_audioengine_AudioProfile_set_maxInstances(se::State& s)
{
    const auto& args = s.args();
    cocos2d::AudioProfile* cobj = SE_THIS_OBJECT<cocos2d::AudioProfile>(s);
    SE_PRECONDITION2(cobj, false, "js_audioengine_AudioProfile_set_maxInstances : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->maxInstances, s.thisObject()); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_audioengine_AudioProfile_set_maxInstances : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_audioengine_AudioProfile_set_maxInstances)

static bool js_audioengine_AudioProfile_get_minDelay(se::State& s)
{
    cocos2d::AudioProfile* cobj = SE_THIS_OBJECT<cocos2d::AudioProfile>(s);
    SE_PRECONDITION2(cobj, false, "js_audioengine_AudioProfile_get_minDelay : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->minDelay, jsret, s.thisObject() /*ctx*/);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_audioengine_AudioProfile_get_minDelay)

static bool js_audioengine_AudioProfile_set_minDelay(se::State& s)
{
    const auto& args = s.args();
    cocos2d::AudioProfile* cobj = SE_THIS_OBJECT<cocos2d::AudioProfile>(s);
    SE_PRECONDITION2(cobj, false, "js_audioengine_AudioProfile_set_minDelay : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->minDelay, s.thisObject()); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_audioengine_AudioProfile_set_minDelay : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_audioengine_AudioProfile_set_minDelay)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_AudioProfile_finalize)

static bool js_audioengine_AudioProfile_constructor(se::State& s) // constructor.c
{
    cocos2d::AudioProfile* cobj = JSB_ALLOC(cocos2d::AudioProfile);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_audioengine_AudioProfile_constructor, __jsb_cocos2d_AudioProfile_class, js_cocos2d_AudioProfile_finalize)




static bool js_cocos2d_AudioProfile_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::AudioProfile)", SE_THIS_OBJECT<cocos2d::AudioProfile>(s););
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(SE_THIS_OBJECT<cocos2d::AudioProfile>(s));
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::AudioProfile* cobj = SE_THIS_OBJECT<cocos2d::AudioProfile>(s);
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_AudioProfile_finalize)

bool js_register_audioengine_AudioProfile(se::Object* obj)
{
    auto cls = se::Class::create("AudioProfile", obj, nullptr, _SE(js_audioengine_AudioProfile_constructor));

    cls->defineProperty("name", _SE(js_audioengine_AudioProfile_get_name), _SE(js_audioengine_AudioProfile_set_name));
    cls->defineProperty("maxInstances", _SE(js_audioengine_AudioProfile_get_maxInstances), _SE(js_audioengine_AudioProfile_set_maxInstances));
    cls->defineProperty("minDelay", _SE(js_audioengine_AudioProfile_get_minDelay), _SE(js_audioengine_AudioProfile_set_minDelay));
    cls->defineFinalizeFunction(_SE(js_cocos2d_AudioProfile_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::AudioProfile>(cls);
    
    if constexpr (std::is_standard_layout_v<cocos2d::AudioProfile>) {
        auto array = se::Object::createArrayObject(0);
        int idx = 0;
        {
            //name : basic_string
            using field_type = decltype(cocos2d::AudioProfile::name);
            auto attr = se::Object::createPlainObject();
            attr->setProperty("name", se::Value("name"));
            attr->setProperty("offset", se::Value(offsetof(cocos2d::AudioProfile, name)));
            attr->setProperty("size", se::Value(sizeof(field_type)));
            attr->setProperty("type", se::Value(SE_UNDERLYING_TYPE_NAME<field_type>()));
            array->setArrayElement(idx++, se::Value(attr));
            attr->decRef();
        }
        {
            //maxInstances : unsigned int
            using field_type = decltype(cocos2d::AudioProfile::maxInstances);
            auto attr = se::Object::createPlainObject();
            attr->setProperty("name", se::Value("maxInstances"));
            attr->setProperty("offset", se::Value(offsetof(cocos2d::AudioProfile, maxInstances)));
            attr->setProperty("size", se::Value(sizeof(field_type)));
            attr->setProperty("type", se::Value(SE_UNDERLYING_TYPE_NAME<field_type>()));
            array->setArrayElement(idx++, se::Value(attr));
            attr->decRef();
        }
        {
            //minDelay : double
            using field_type = decltype(cocos2d::AudioProfile::minDelay);
            auto attr = se::Object::createPlainObject();
            attr->setProperty("name", se::Value("minDelay"));
            attr->setProperty("offset", se::Value(offsetof(cocos2d::AudioProfile, minDelay)));
            attr->setProperty("size", se::Value(sizeof(field_type)));
            attr->setProperty("type", se::Value(SE_UNDERLYING_TYPE_NAME<field_type>()));
            array->setArrayElement(idx++, se::Value(attr));
            attr->decRef();
        }
        cls->getProto()->setProperty("__attrMeta", se::Value(array));
        //obj->setProperty("__attrMeta_AudioProfile", se::Value(array));
        array->decRef();
    }

    __jsb_cocos2d_AudioProfile_proto = cls->getProto();
    __jsb_cocos2d_AudioProfile_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_AudioEngine_proto = nullptr;
se::Class* __jsb_cocos2d_AudioEngine_class = nullptr;

static bool js_audioengine_AudioEngine_lazyInit(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cocos2d::AudioEngine::lazyInit();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_lazyInit : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_lazyInit)

static bool js_audioengine_AudioEngine_setCurrentTime(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<int, false>::local_type arg0 = {};
        HolderType<float, false>::local_type arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1, nullptr); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_setCurrentTime : Error processing arguments");
        bool result = cocos2d::AudioEngine::setCurrentTime(HolderType<int, false>::value(arg0), HolderType<float, false>::value(arg1));
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_setCurrentTime : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_setCurrentTime)

static bool js_audioengine_AudioEngine_getVolume(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_getVolume : Error processing arguments");
        float result = cocos2d::AudioEngine::getVolume(HolderType<int, false>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_getVolume : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_getVolume)

static bool js_audioengine_AudioEngine_uncache(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::string, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_uncache : Error processing arguments");
        cocos2d::AudioEngine::uncache(HolderType<std::string, true>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_uncache)

static bool js_audioengine_AudioEngine_resumeAll(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cocos2d::AudioEngine::resumeAll();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_resumeAll)

static bool js_audioengine_AudioEngine_stopAll(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cocos2d::AudioEngine::stopAll();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_stopAll)

static bool js_audioengine_AudioEngine_pause(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_pause : Error processing arguments");
        cocos2d::AudioEngine::pause(HolderType<int, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_pause)

static bool js_audioengine_AudioEngine_end(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cocos2d::AudioEngine::end();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_end)

static bool js_audioengine_AudioEngine_getMaxAudioInstance(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cocos2d::AudioEngine::getMaxAudioInstance();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_getMaxAudioInstance : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_getMaxAudioInstance)

static bool js_audioengine_AudioEngine_isEnabled(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cocos2d::AudioEngine::isEnabled();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_isEnabled : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_isEnabled)

static bool js_audioengine_AudioEngine_getDurationFromFile(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::string, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_getDurationFromFile : Error processing arguments");
        float result = cocos2d::AudioEngine::getDurationFromFile(HolderType<std::string, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_getDurationFromFile : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_getDurationFromFile)

static bool js_audioengine_AudioEngine_getCurrentTime(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_getCurrentTime : Error processing arguments");
        float result = cocos2d::AudioEngine::getCurrentTime(HolderType<int, false>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_getCurrentTime : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_getCurrentTime)

static bool js_audioengine_AudioEngine_setMaxAudioInstance(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_setMaxAudioInstance : Error processing arguments");
        bool result = cocos2d::AudioEngine::setMaxAudioInstance(HolderType<int, false>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_setMaxAudioInstance : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_setMaxAudioInstance)

static bool js_audioengine_AudioEngine_isLoop(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_isLoop : Error processing arguments");
        bool result = cocos2d::AudioEngine::isLoop(HolderType<int, false>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_isLoop : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_isLoop)

static bool js_audioengine_AudioEngine_pauseAll(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cocos2d::AudioEngine::pauseAll();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_pauseAll)

static bool js_audioengine_AudioEngine_uncacheAll(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cocos2d::AudioEngine::uncacheAll();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_uncacheAll)

static bool js_audioengine_AudioEngine_setVolume(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<int, false>::local_type arg0 = {};
        HolderType<float, false>::local_type arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1, nullptr); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_setVolume : Error processing arguments");
        cocos2d::AudioEngine::setVolume(HolderType<int, false>::value(arg0), HolderType<float, false>::value(arg1));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_setVolume)

static bool js_audioengine_AudioEngine_preload(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();
    do {
        if (argc == 2) {
            HolderType<std::string, true>::local_type arg0 = {};
            ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
            if (!ok) { ok = true; break; }
            HolderType<std::function<void (bool)>, false>::local_type arg1 = {};
            ok &= sevalue_to_native(args[1], &arg1, s.thisObject()); //is_reference False;
            if (!ok) { ok = true; break; }
            cocos2d::AudioEngine::preload(HolderType<std::string, true>::value(arg0), HolderType<std::function<void (bool)>, false>::value(arg1));
            return true;
        }
    } while (false);
    do {
        if (argc == 1) {
            HolderType<std::string, true>::local_type arg0 = {};
            ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
            if (!ok) { ok = true; break; }
            cocos2d::AudioEngine::preload(HolderType<std::string, true>::value(arg0));
            return true;
        }
    } while (false);
    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_preload)

static bool js_audioengine_AudioEngine_setEnabled(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_setEnabled : Error processing arguments");
        cocos2d::AudioEngine::setEnabled(HolderType<bool, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_setEnabled)

static bool js_audioengine_AudioEngine_play2d(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::string, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_play2d : Error processing arguments");
        int result = cocos2d::AudioEngine::play2d(HolderType<std::string, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_play2d : Error processing arguments");
        return true;
    }
    if (argc == 2) {
        HolderType<std::string, true>::local_type arg0 = {};
        HolderType<bool, false>::local_type arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference True;
        ok &= sevalue_to_native(args[1], &arg1, nullptr); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_play2d : Error processing arguments");
        int result = cocos2d::AudioEngine::play2d(HolderType<std::string, true>::value(arg0), HolderType<bool, false>::value(arg1));
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_play2d : Error processing arguments");
        return true;
    }
    if (argc == 3) {
        HolderType<std::string, true>::local_type arg0 = {};
        HolderType<bool, false>::local_type arg1 = {};
        HolderType<float, false>::local_type arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference True;
        ok &= sevalue_to_native(args[1], &arg1, nullptr); //is_reference False;
        ok &= sevalue_to_native(args[2], &arg2, nullptr); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_play2d : Error processing arguments");
        int result = cocos2d::AudioEngine::play2d(HolderType<std::string, true>::value(arg0), HolderType<bool, false>::value(arg1), HolderType<float, false>::value(arg2));
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_play2d : Error processing arguments");
        return true;
    }
    if (argc == 4) {
        HolderType<std::string, true>::local_type arg0 = {};
        HolderType<bool, false>::local_type arg1 = {};
        HolderType<float, false>::local_type arg2 = {};
        HolderType<const cocos2d::AudioProfile*, false>::local_type arg3 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference True;
        ok &= sevalue_to_native(args[1], &arg1, nullptr); //is_reference False;
        ok &= sevalue_to_native(args[2], &arg2, nullptr); //is_reference False;
        ok &= sevalue_to_native(args[3], &arg3, nullptr); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_play2d : Error processing arguments");
        int result = cocos2d::AudioEngine::play2d(HolderType<std::string, true>::value(arg0), HolderType<bool, false>::value(arg1), HolderType<float, false>::value(arg2), HolderType<const cocos2d::AudioProfile*, false>::value(arg3));
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_play2d : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_play2d)

static bool js_audioengine_AudioEngine_getState(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_getState : Error processing arguments");
        int result = (int)cocos2d::AudioEngine::getState(HolderType<int, false>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_getState : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_getState)

static bool js_audioengine_AudioEngine_resume(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_resume : Error processing arguments");
        cocos2d::AudioEngine::resume(HolderType<int, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_resume)

static bool js_audioengine_AudioEngine_stop(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_stop : Error processing arguments");
        cocos2d::AudioEngine::stop(HolderType<int, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_stop)

static bool js_audioengine_AudioEngine_getDuration(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_getDuration : Error processing arguments");
        float result = cocos2d::AudioEngine::getDuration(HolderType<int, false>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_getDuration : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_getDuration)

static bool js_audioengine_AudioEngine_setLoop(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<int, false>::local_type arg0 = {};
        HolderType<bool, false>::local_type arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1, nullptr); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_setLoop : Error processing arguments");
        cocos2d::AudioEngine::setLoop(HolderType<int, false>::value(arg0), HolderType<bool, false>::value(arg1));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_setLoop)

static bool js_audioengine_AudioEngine_getDefaultProfile(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::AudioProfile* result = cocos2d::AudioEngine::getDefaultProfile();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_getDefaultProfile : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_getDefaultProfile)

static bool js_audioengine_AudioEngine_setFinishCallback(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<int, false>::local_type arg0 = {};
        HolderType<std::function<void (int, const std::string&)>, true>::local_type arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1, nullptr); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_setFinishCallback : Error processing arguments");
        cocos2d::AudioEngine::setFinishCallback(HolderType<int, false>::value(arg0), HolderType<std::function<void (int, const std::string&)>, true>::value(arg1));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_setFinishCallback)

static bool js_audioengine_AudioEngine_getProfile(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();
    do {
        if (argc == 1) {
            HolderType<std::string, true>::local_type arg0 = {};
            ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
            if (!ok) { ok = true; break; }
            cocos2d::AudioProfile* result = cocos2d::AudioEngine::getProfile(HolderType<std::string, true>::value(arg0));
            ok &= nativevalue_to_se(result, s.rval(), s.thisObject() /*ctx*/);
            SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_getProfile : Error processing arguments");
            return true;
        }
    } while (false);
    do {
        if (argc == 1) {
            HolderType<int, false>::local_type arg0 = {};
            ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference False;
            if (!ok) { ok = true; break; }
            cocos2d::AudioProfile* result = cocos2d::AudioEngine::getProfile(HolderType<int, false>::value(arg0));
            ok &= nativevalue_to_se(result, s.rval(), s.thisObject() /*ctx*/);
            SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_getProfile : Error processing arguments");
            return true;
        }
    } while (false);
    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_getProfile)

static bool js_audioengine_AudioEngine_getPlayingAudioCount(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cocos2d::AudioEngine::getPlayingAudioCount();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_audioengine_AudioEngine_getPlayingAudioCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_audioengine_AudioEngine_getPlayingAudioCount)




bool js_register_audioengine_AudioEngine(se::Object* obj)
{
    auto cls = se::Class::create("AudioEngine", obj, nullptr, nullptr);

    cls->defineStaticFunction("lazyInit", _SE(js_audioengine_AudioEngine_lazyInit));
    cls->defineStaticFunction("setCurrentTime", _SE(js_audioengine_AudioEngine_setCurrentTime));
    cls->defineStaticFunction("getVolume", _SE(js_audioengine_AudioEngine_getVolume));
    cls->defineStaticFunction("uncache", _SE(js_audioengine_AudioEngine_uncache));
    cls->defineStaticFunction("resumeAll", _SE(js_audioengine_AudioEngine_resumeAll));
    cls->defineStaticFunction("stopAll", _SE(js_audioengine_AudioEngine_stopAll));
    cls->defineStaticFunction("pause", _SE(js_audioengine_AudioEngine_pause));
    cls->defineStaticFunction("end", _SE(js_audioengine_AudioEngine_end));
    cls->defineStaticFunction("getMaxAudioInstance", _SE(js_audioengine_AudioEngine_getMaxAudioInstance));
    cls->defineStaticFunction("isEnabled", _SE(js_audioengine_AudioEngine_isEnabled));
    cls->defineStaticFunction("getDurationFromFile", _SE(js_audioengine_AudioEngine_getDurationFromFile));
    cls->defineStaticFunction("getCurrentTime", _SE(js_audioengine_AudioEngine_getCurrentTime));
    cls->defineStaticFunction("setMaxAudioInstance", _SE(js_audioengine_AudioEngine_setMaxAudioInstance));
    cls->defineStaticFunction("isLoop", _SE(js_audioengine_AudioEngine_isLoop));
    cls->defineStaticFunction("pauseAll", _SE(js_audioengine_AudioEngine_pauseAll));
    cls->defineStaticFunction("uncacheAll", _SE(js_audioengine_AudioEngine_uncacheAll));
    cls->defineStaticFunction("setVolume", _SE(js_audioengine_AudioEngine_setVolume));
    cls->defineStaticFunction("preload", _SE(js_audioengine_AudioEngine_preload));
    cls->defineStaticFunction("setEnabled", _SE(js_audioengine_AudioEngine_setEnabled));
    cls->defineStaticFunction("play2d", _SE(js_audioengine_AudioEngine_play2d));
    cls->defineStaticFunction("getState", _SE(js_audioengine_AudioEngine_getState));
    cls->defineStaticFunction("resume", _SE(js_audioengine_AudioEngine_resume));
    cls->defineStaticFunction("stop", _SE(js_audioengine_AudioEngine_stop));
    cls->defineStaticFunction("getDuration", _SE(js_audioengine_AudioEngine_getDuration));
    cls->defineStaticFunction("setLoop", _SE(js_audioengine_AudioEngine_setLoop));
    cls->defineStaticFunction("getDefaultProfile", _SE(js_audioengine_AudioEngine_getDefaultProfile));
    cls->defineStaticFunction("setFinishCallback", _SE(js_audioengine_AudioEngine_setFinishCallback));
    cls->defineStaticFunction("getProfile", _SE(js_audioengine_AudioEngine_getProfile));
    cls->defineStaticFunction("getPlayingAudioCount", _SE(js_audioengine_AudioEngine_getPlayingAudioCount));
    cls->install();
    JSBClassType::registerClass<cocos2d::AudioEngine>(cls);
    
    if constexpr (std::is_standard_layout_v<cocos2d::AudioEngine>) {
        auto array = se::Object::createArrayObject(0);
        int idx = 0;
        cls->getProto()->setProperty("__attrMeta", se::Value(array));
        //obj->setProperty("__attrMeta_AudioEngine", se::Value(array));
        array->decRef();
    }

    __jsb_cocos2d_AudioEngine_proto = cls->getProto();
    __jsb_cocos2d_AudioEngine_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

bool register_all_audioengine(se::Object* obj)
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

    js_register_audioengine_AudioProfile(ns);
    js_register_audioengine_AudioEngine(ns);
    return true;
}

#endif //#if (USE_AUDIO > 0) && (CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_MAC_IOS || CC_PLATFORM == CC_PLATFORM_MAC_OSX || CC_PLATFORM == CC_PLATFORM_WINDOWS)
