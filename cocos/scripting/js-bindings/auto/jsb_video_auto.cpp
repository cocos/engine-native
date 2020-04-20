#include "scripting/js-bindings/auto/jsb_video_auto.hpp"
#if (USE_VIDEO > 0) && (CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_MAC_IOS) && !defined(CC_TARGET_OS_TVOS)
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "ui/videoplayer/VideoPlayer.h"

#ifndef JSB_ALLOC
#define JSB_ALLOC(kls, ...) new (std::nothrow) kls(__VA_ARGS__)
#endif

#ifndef JSB_FREE
#define JSB_FREE(ptr) delete ptr
#endif
se::Object* __jsb_cocos2d_VideoPlayer_proto = nullptr;
se::Class* __jsb_cocos2d_VideoPlayer_class = nullptr;

static bool js_video_VideoPlayer_setFrame(se::State& s)
{
    cocos2d::VideoPlayer* cobj = SE_THIS_OBJECT<cocos2d::VideoPlayer>(s);
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_setFrame : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        HolderType<float, false>::local_type arg0 = {};
        HolderType<float, false>::local_type arg1 = {};
        HolderType<float, false>::local_type arg2 = {};
        HolderType<float, false>::local_type arg3 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject()); //is_reference False;
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject()); //is_reference False;
        ok &= sevalue_to_native(args[3], &arg3, s.thisObject()); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_setFrame : Error processing arguments");
        cobj->setFrame(HolderType<float, false>::value(arg0), HolderType<float, false>::value(arg1), HolderType<float, false>::value(arg2), HolderType<float, false>::value(arg3));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_setFrame)

static bool js_video_VideoPlayer_play(se::State& s)
{
    cocos2d::VideoPlayer* cobj = SE_THIS_OBJECT<cocos2d::VideoPlayer>(s);
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_play : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->play();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_play)

static bool js_video_VideoPlayer_pause(se::State& s)
{
    cocos2d::VideoPlayer* cobj = SE_THIS_OBJECT<cocos2d::VideoPlayer>(s);
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_pause : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->pause();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_pause)

static bool js_video_VideoPlayer_setKeepAspectRatioEnabled(se::State& s)
{
    cocos2d::VideoPlayer* cobj = SE_THIS_OBJECT<cocos2d::VideoPlayer>(s);
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_setKeepAspectRatioEnabled : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_setKeepAspectRatioEnabled : Error processing arguments");
        cobj->setKeepAspectRatioEnabled(HolderType<bool, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_setKeepAspectRatioEnabled)

static bool js_video_VideoPlayer_currentTime(se::State& s)
{
    cocos2d::VideoPlayer* cobj = SE_THIS_OBJECT<cocos2d::VideoPlayer>(s);
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_currentTime : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->currentTime();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_currentTime : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_currentTime)

static bool js_video_VideoPlayer_setFullScreenEnabled(se::State& s)
{
    cocos2d::VideoPlayer* cobj = SE_THIS_OBJECT<cocos2d::VideoPlayer>(s);
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_setFullScreenEnabled : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_setFullScreenEnabled : Error processing arguments");
        cobj->setFullScreenEnabled(HolderType<bool, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_setFullScreenEnabled)

static bool js_video_VideoPlayer_addEventListener(se::State& s)
{
    cocos2d::VideoPlayer* cobj = SE_THIS_OBJECT<cocos2d::VideoPlayer>(s);
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_addEventListener : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<std::string, true>::local_type arg0 = {};
        HolderType<std::function<void ()>, true>::local_type arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject()); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_addEventListener : Error processing arguments");
        cobj->addEventListener(HolderType<std::string, true>::value(arg0), HolderType<std::function<void ()>, true>::value(arg1));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_addEventListener)

static bool js_video_VideoPlayer_stop(se::State& s)
{
    cocos2d::VideoPlayer* cobj = SE_THIS_OBJECT<cocos2d::VideoPlayer>(s);
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_stop : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->stop();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_stop)

static bool js_video_VideoPlayer_setURL(se::State& s)
{
    cocos2d::VideoPlayer* cobj = SE_THIS_OBJECT<cocos2d::VideoPlayer>(s);
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_setURL : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::string, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_setURL : Error processing arguments");
        cobj->setURL(HolderType<std::string, true>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_setURL)

static bool js_video_VideoPlayer_isKeepAspectRatioEnabled(se::State& s)
{
    cocos2d::VideoPlayer* cobj = SE_THIS_OBJECT<cocos2d::VideoPlayer>(s);
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_isKeepAspectRatioEnabled : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isKeepAspectRatioEnabled();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_isKeepAspectRatioEnabled : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_isKeepAspectRatioEnabled)

static bool js_video_VideoPlayer_onPlayEvent(se::State& s)
{
    cocos2d::VideoPlayer* cobj = SE_THIS_OBJECT<cocos2d::VideoPlayer>(s);
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_onPlayEvent : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_onPlayEvent : Error processing arguments");
        cobj->onPlayEvent(HolderType<int, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_onPlayEvent)

static bool js_video_VideoPlayer_duration(se::State& s)
{
    cocos2d::VideoPlayer* cobj = SE_THIS_OBJECT<cocos2d::VideoPlayer>(s);
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_duration : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->duration();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_duration : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_duration)

static bool js_video_VideoPlayer_setVisible(se::State& s)
{
    cocos2d::VideoPlayer* cobj = SE_THIS_OBJECT<cocos2d::VideoPlayer>(s);
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_setVisible : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_setVisible : Error processing arguments");
        cobj->setVisible(HolderType<bool, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_setVisible)

static bool js_video_VideoPlayer_seekTo(se::State& s)
{
    cocos2d::VideoPlayer* cobj = SE_THIS_OBJECT<cocos2d::VideoPlayer>(s);
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_seekTo : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_seekTo : Error processing arguments");
        cobj->seekTo(HolderType<float, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_seekTo)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_VideoPlayer_finalize)

static bool js_video_VideoPlayer_constructor(se::State& s) // constructor.c
{
    cocos2d::VideoPlayer* cobj = JSB_ALLOC(cocos2d::VideoPlayer);
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_video_VideoPlayer_constructor, __jsb_cocos2d_VideoPlayer_class, js_cocos2d_VideoPlayer_finalize)




static bool js_cocos2d_VideoPlayer_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::VideoPlayer)", SE_THIS_OBJECT<cocos2d::VideoPlayer>(s););
    cocos2d::VideoPlayer* cobj =SE_THIS_OBJECT<cocos2d::VideoPlayer>(s);
    cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_VideoPlayer_finalize)

bool js_register_video_VideoPlayer(se::Object* obj)
{
    auto cls = se::Class::create("VideoPlayer", obj, nullptr, _SE(js_video_VideoPlayer_constructor));

    cls->defineFunction("setFrame", _SE(js_video_VideoPlayer_setFrame));
    cls->defineFunction("play", _SE(js_video_VideoPlayer_play));
    cls->defineFunction("pause", _SE(js_video_VideoPlayer_pause));
    cls->defineFunction("setKeepAspectRatioEnabled", _SE(js_video_VideoPlayer_setKeepAspectRatioEnabled));
    cls->defineFunction("currentTime", _SE(js_video_VideoPlayer_currentTime));
    cls->defineFunction("setFullScreenEnabled", _SE(js_video_VideoPlayer_setFullScreenEnabled));
    cls->defineFunction("addEventListener", _SE(js_video_VideoPlayer_addEventListener));
    cls->defineFunction("stop", _SE(js_video_VideoPlayer_stop));
    cls->defineFunction("setURL", _SE(js_video_VideoPlayer_setURL));
    cls->defineFunction("isKeepAspectRatioEnabled", _SE(js_video_VideoPlayer_isKeepAspectRatioEnabled));
    cls->defineFunction("onPlayEvent", _SE(js_video_VideoPlayer_onPlayEvent));
    cls->defineFunction("duration", _SE(js_video_VideoPlayer_duration));
    cls->defineFunction("setVisible", _SE(js_video_VideoPlayer_setVisible));
    cls->defineFunction("seekTo", _SE(js_video_VideoPlayer_seekTo));
    cls->defineFinalizeFunction(_SE(js_cocos2d_VideoPlayer_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::VideoPlayer>(cls);

    __jsb_cocos2d_VideoPlayer_proto = cls->getProto();
    __jsb_cocos2d_VideoPlayer_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

bool register_all_video(se::Object* obj)
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

    js_register_video_VideoPlayer(ns);
    return true;
}

#endif //#if (USE_VIDEO > 0) && (CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_MAC_IOS) && !defined(CC_TARGET_OS_TVOS)
