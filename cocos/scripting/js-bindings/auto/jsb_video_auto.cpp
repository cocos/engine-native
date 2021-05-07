#include "scripting/js-bindings/auto/jsb_video_auto.hpp"
#if (USE_VIDEO > 0) && (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) && !defined(CC_TARGET_OS_TVOS)
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "ui/videoplayer/VideoPlayer.h"

se::Object* __jsb_cocos2d_VideoPlayer_proto = nullptr;
se::Class* __jsb_cocos2d_VideoPlayer_class = nullptr;

static bool js_video_VideoPlayer_setFullScreenEnabled(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_setFullScreenEnabled : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        bool arg0;
        ok &= seval_to_boolean(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_setFullScreenEnabled : Error processing arguments");
        cobj->setFullScreenEnabled(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_setFullScreenEnabled)

static bool js_video_VideoPlayer_getFrameWidth(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_getFrameWidth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getFrameWidth();
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_getFrameWidth : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_getFrameWidth)

static bool js_video_VideoPlayer_duration(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_duration : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->duration();
        ok &= float_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_duration : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_duration)

static bool js_video_VideoPlayer_pause(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
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

static bool js_video_VideoPlayer_getFrame(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_getFrame : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->getFrame();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_getFrame)

static bool js_video_VideoPlayer_setShowRawFrame(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_setShowRawFrame : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        bool arg0;
        ok &= seval_to_boolean(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_setShowRawFrame : Error processing arguments");
        cobj->setShowRawFrame(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_setShowRawFrame)

static bool js_video_VideoPlayer_onPlayEvent(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_onPlayEvent : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        int arg0 = 0;
        do { int32_t tmp = 0; ok &= seval_to_int32(args[0], &tmp); arg0 = (int)tmp; } while(false);
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_onPlayEvent : Error processing arguments");
        cobj->onPlayEvent(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_onPlayEvent)

static bool js_video_VideoPlayer_addEventListener(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_addEventListener : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        std::string arg0;
        std::function<void ()> arg1;
        ok &= seval_to_std_string(args[0], &arg0);
        do {
            if (args[1].isObject() && args[1].toObject()->isFunction())
            {
                se::Value jsThis(s.thisObject());
                se::Value jsFunc(args[1]);
                jsThis.toObject()->attachObject(jsFunc.toObject());
                auto lambda = [=]() -> void {
                    se::ScriptEngine::getInstance()->clearException();
                    se::AutoHandleScope hs;
        
                    se::Value rval;
                    se::Object* thisObj = jsThis.isObject() ? jsThis.toObject() : nullptr;
                    se::Object* funcObj = jsFunc.toObject();
                    bool succeed = funcObj->call(se::EmptyValueArray, thisObj, &rval);
                    if (!succeed) {
                        se::ScriptEngine::getInstance()->clearException();
                    }
                };
                arg1 = lambda;
            }
            else
            {
                arg1 = nullptr;
            }
        } while(false)
        ;
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_addEventListener : Error processing arguments");
        cobj->addEventListener(arg0, arg1);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_addEventListener)

static bool js_video_VideoPlayer_seekTo(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_seekTo : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        float arg0 = 0;
        ok &= seval_to_float(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_seekTo : Error processing arguments");
        cobj->seekTo(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_seekTo)

static bool js_video_VideoPlayer_play(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
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

static bool js_video_VideoPlayer_getFrameHeight(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_getFrameHeight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getFrameHeight();
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_getFrameHeight : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_getFrameHeight)

static bool js_video_VideoPlayer_stop(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
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
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_setURL : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        std::string arg0;
        ok &= seval_to_std_string(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_setURL : Error processing arguments");
        cobj->setURL(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_setURL)

static bool js_video_VideoPlayer_update(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_update : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->update();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_update)

static bool js_video_VideoPlayer_pushFrameDataToTexture2D(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_pushFrameDataToTexture2D : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        cocos2d::renderer::Texture* arg0 = nullptr;
        ok &= seval_to_native_ptr(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_pushFrameDataToTexture2D : Error processing arguments");
        cobj->pushFrameDataToTexture2D(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_pushFrameDataToTexture2D)

static bool js_video_VideoPlayer_isKeepAspectRatioEnabled(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_isKeepAspectRatioEnabled : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isKeepAspectRatioEnabled();
        ok &= boolean_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_isKeepAspectRatioEnabled : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_isKeepAspectRatioEnabled)

static bool js_video_VideoPlayer_getFrameChannel(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_getFrameChannel : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getFrameChannel();
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_getFrameChannel : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_getFrameChannel)

static bool js_video_VideoPlayer_getVideoTexDataSize(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_getVideoTexDataSize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getVideoTexDataSize();
        ok &= int32_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_getVideoTexDataSize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_getVideoTexDataSize)

static bool js_video_VideoPlayer_setKeepAspectRatioEnabled(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_setKeepAspectRatioEnabled : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        bool arg0;
        ok &= seval_to_boolean(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_setKeepAspectRatioEnabled : Error processing arguments");
        cobj->setKeepAspectRatioEnabled(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_setKeepAspectRatioEnabled)

static bool js_video_VideoPlayer_currentTime(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_currentTime : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->currentTime();
        ok &= float_to_seval(result, &s.rval());
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_currentTime : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_currentTime)

static bool js_video_VideoPlayer_setFrame(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_setFrame : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        float arg0 = 0;
        float arg1 = 0;
        float arg2 = 0;
        float arg3 = 0;
        ok &= seval_to_float(args[0], &arg0);
        ok &= seval_to_float(args[1], &arg1);
        ok &= seval_to_float(args[2], &arg2);
        ok &= seval_to_float(args[3], &arg3);
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_setFrame : Error processing arguments");
        cobj->setFrame(arg0, arg1, arg2, arg3);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_setFrame)

static bool js_video_VideoPlayer_setVisible(se::State& s)
{
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_video_VideoPlayer_setVisible : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        bool arg0;
        ok &= seval_to_boolean(args[0], &arg0);
        SE_PRECONDITION2(ok, false, "js_video_VideoPlayer_setVisible : Error processing arguments");
        cobj->setVisible(arg0);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_video_VideoPlayer_setVisible)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_VideoPlayer_finalize)

static bool js_video_VideoPlayer_constructor(se::State& s)
{
    cocos2d::VideoPlayer* cobj = new (std::nothrow) cocos2d::VideoPlayer();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_video_VideoPlayer_constructor, __jsb_cocos2d_VideoPlayer_class, js_cocos2d_VideoPlayer_finalize)




static bool js_cocos2d_VideoPlayer_finalize(se::State& s)
{
    // destructor is skipped
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_VideoPlayer_finalize)

static bool js_cocos2d_VideoPlayer_destroy(se::State& s)
{
    CCLOGINFO("jsbindings: destory JS object %p (cocos2d::VideoPlayer)", s.nativeThisObject());
    cocos2d::VideoPlayer* cobj = (cocos2d::VideoPlayer*)s.nativeThisObject();
    cobj->release();
    auto objIter = se::NativePtrToObjectMap::find(s.nativeThisObject());
    if(objIter != se::NativePtrToObjectMap::end())
    {
        objIter->second->clearPrivateData(true);
    }
    return true;
}
SE_BIND_FUNC(js_cocos2d_VideoPlayer_destroy)

bool js_register_video_VideoPlayer(se::Object* obj)
{
    auto cls = se::Class::create("VideoPlayer", obj, nullptr, _SE(js_video_VideoPlayer_constructor));

    cls->defineFunction("setFullScreenEnabled", _SE(js_video_VideoPlayer_setFullScreenEnabled));
    cls->defineFunction("getFrameWidth", _SE(js_video_VideoPlayer_getFrameWidth));
    cls->defineFunction("duration", _SE(js_video_VideoPlayer_duration));
    cls->defineFunction("pause", _SE(js_video_VideoPlayer_pause));
    cls->defineFunction("getFrame", _SE(js_video_VideoPlayer_getFrame));
    cls->defineFunction("setShowRawFrame", _SE(js_video_VideoPlayer_setShowRawFrame));
    cls->defineFunction("onPlayEvent", _SE(js_video_VideoPlayer_onPlayEvent));
    cls->defineFunction("addEventListener", _SE(js_video_VideoPlayer_addEventListener));
    cls->defineFunction("seekTo", _SE(js_video_VideoPlayer_seekTo));
    cls->defineFunction("play", _SE(js_video_VideoPlayer_play));
    cls->defineFunction("getFrameHeight", _SE(js_video_VideoPlayer_getFrameHeight));
    cls->defineFunction("stop", _SE(js_video_VideoPlayer_stop));
    cls->defineFunction("setURL", _SE(js_video_VideoPlayer_setURL));
    cls->defineFunction("update", _SE(js_video_VideoPlayer_update));
    cls->defineFunction("pushFrameDataToTexture2D", _SE(js_video_VideoPlayer_pushFrameDataToTexture2D));
    cls->defineFunction("isKeepAspectRatioEnabled", _SE(js_video_VideoPlayer_isKeepAspectRatioEnabled));
    cls->defineFunction("getFrameChannel", _SE(js_video_VideoPlayer_getFrameChannel));
    cls->defineFunction("getVideoTexDataSize", _SE(js_video_VideoPlayer_getVideoTexDataSize));
    cls->defineFunction("setKeepAspectRatioEnabled", _SE(js_video_VideoPlayer_setKeepAspectRatioEnabled));
    cls->defineFunction("currentTime", _SE(js_video_VideoPlayer_currentTime));
    cls->defineFunction("setFrame", _SE(js_video_VideoPlayer_setFrame));
    cls->defineFunction("setVisible", _SE(js_video_VideoPlayer_setVisible));
    cls->defineFunction("destroy", _SE(js_cocos2d_VideoPlayer_destroy));
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

#endif //#if (USE_VIDEO > 0) && (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS) && !defined(CC_TARGET_OS_TVOS)
