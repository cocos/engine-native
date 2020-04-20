#include "scripting/js-bindings/auto/jsb_webview_auto.hpp"
#if (USE_WEB_VIEW > 0) && (CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_MAC_IOS) && !defined(CC_TARGET_OS_TVOS)
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "ui/webview/WebView.h"

#ifndef JSB_ALLOC
#define JSB_ALLOC(kls, ...) new (std::nothrow) kls(__VA_ARGS__)
#endif

#ifndef JSB_FREE
#define JSB_FREE(ptr) delete ptr
#endif
se::Object* __jsb_cocos2d_WebView_proto = nullptr;
se::Class* __jsb_cocos2d_WebView_class = nullptr;

static bool js_webview_WebView_setOnShouldStartLoading(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_setOnShouldStartLoading : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::function<bool (cocos2d::WebView *, const std::string&)>, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_webview_WebView_setOnShouldStartLoading : Error processing arguments");
        cobj->setOnShouldStartLoading(HolderType<std::function<bool (cocos2d::WebView *, const std::string&)>, true>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_setOnShouldStartLoading)

static bool js_webview_WebView_setOnDidFailLoading(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_setOnDidFailLoading : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::function<void (cocos2d::WebView *, const std::string&)>, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_webview_WebView_setOnDidFailLoading : Error processing arguments");
        cobj->setOnDidFailLoading(HolderType<std::function<void (cocos2d::WebView *, const std::string&)>, true>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_setOnDidFailLoading)

static bool js_webview_WebView_canGoBack(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_canGoBack : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->canGoBack();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_webview_WebView_canGoBack : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_canGoBack)

static bool js_webview_WebView_loadHTMLString(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_loadHTMLString : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::string, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_webview_WebView_loadHTMLString : Error processing arguments");
        cobj->loadHTMLString(HolderType<std::string, true>::value(arg0));
        return true;
    }
    if (argc == 2) {
        HolderType<std::string, true>::local_type arg0 = {};
        HolderType<std::string, true>::local_type arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject()); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_webview_WebView_loadHTMLString : Error processing arguments");
        cobj->loadHTMLString(HolderType<std::string, true>::value(arg0), HolderType<std::string, true>::value(arg1));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_loadHTMLString)

static bool js_webview_WebView_goForward(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_goForward : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->goForward();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_goForward)

static bool js_webview_WebView_goBack(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_goBack : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->goBack();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_goBack)

static bool js_webview_WebView_setScalesPageToFit(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_setScalesPageToFit : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_webview_WebView_setScalesPageToFit : Error processing arguments");
        cobj->setScalesPageToFit(HolderType<bool, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_setScalesPageToFit)

static bool js_webview_WebView_getOnDidFailLoading(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_getOnDidFailLoading : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::WebView::ccWebViewCallback result = cobj->getOnDidFailLoading();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_webview_WebView_getOnDidFailLoading : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_getOnDidFailLoading)

static bool js_webview_WebView_loadFile(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_loadFile : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::string, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_webview_WebView_loadFile : Error processing arguments");
        cobj->loadFile(HolderType<std::string, true>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_loadFile)

static bool js_webview_WebView_loadURL(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_loadURL : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::string, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_webview_WebView_loadURL : Error processing arguments");
        cobj->loadURL(HolderType<std::string, true>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_loadURL)

static bool js_webview_WebView_setBounces(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_setBounces : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_webview_WebView_setBounces : Error processing arguments");
        cobj->setBounces(HolderType<bool, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_setBounces)

static bool js_webview_WebView_evaluateJS(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_evaluateJS : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::string, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_webview_WebView_evaluateJS : Error processing arguments");
        cobj->evaluateJS(HolderType<std::string, true>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_evaluateJS)

static bool js_webview_WebView_setOnJSCallback(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_setOnJSCallback : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::function<void (cocos2d::WebView *, const std::string&)>, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_webview_WebView_setOnJSCallback : Error processing arguments");
        cobj->setOnJSCallback(HolderType<std::function<void (cocos2d::WebView *, const std::string&)>, true>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_setOnJSCallback)

static bool js_webview_WebView_setBackgroundTransparent(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_setBackgroundTransparent : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_webview_WebView_setBackgroundTransparent : Error processing arguments");
        cobj->setBackgroundTransparent(HolderType<bool, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_setBackgroundTransparent)

static bool js_webview_WebView_setJavascriptInterfaceScheme(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_setJavascriptInterfaceScheme : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::string, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_webview_WebView_setJavascriptInterfaceScheme : Error processing arguments");
        cobj->setJavascriptInterfaceScheme(HolderType<std::string, true>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_setJavascriptInterfaceScheme)

static bool js_webview_WebView_getOnJSCallback(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_getOnJSCallback : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::WebView::ccWebViewCallback result = cobj->getOnJSCallback();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_webview_WebView_getOnJSCallback : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_getOnJSCallback)

static bool js_webview_WebView_canGoForward(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_canGoForward : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->canGoForward();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_webview_WebView_canGoForward : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_canGoForward)

static bool js_webview_WebView_getOnShouldStartLoading(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_getOnShouldStartLoading : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        std::function<bool (cocos2d::WebView *, const std::string&)> result = cobj->getOnShouldStartLoading();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_webview_WebView_getOnShouldStartLoading : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_getOnShouldStartLoading)

static bool js_webview_WebView_stopLoading(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_stopLoading : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->stopLoading();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_stopLoading)

static bool js_webview_WebView_setFrame(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_setFrame : Invalid Native Object");
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
        SE_PRECONDITION2(ok, false, "js_webview_WebView_setFrame : Error processing arguments");
        cobj->setFrame(HolderType<float, false>::value(arg0), HolderType<float, false>::value(arg1), HolderType<float, false>::value(arg2), HolderType<float, false>::value(arg3));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_setFrame)

static bool js_webview_WebView_setVisible(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_setVisible : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_webview_WebView_setVisible : Error processing arguments");
        cobj->setVisible(HolderType<bool, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_setVisible)

static bool js_webview_WebView_reload(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_reload : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->reload();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_reload)

static bool js_webview_WebView_loadData(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_loadData : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        HolderType<cocos2d::Data, true>::local_type arg0 = {};
        HolderType<std::string, true>::local_type arg1 = {};
        HolderType<std::string, true>::local_type arg2 = {};
        HolderType<std::string, true>::local_type arg3 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject()); //is_reference True;
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject()); //is_reference True;
        ok &= sevalue_to_native(args[3], &arg3, s.thisObject()); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_webview_WebView_loadData : Error processing arguments");
        cobj->loadData(HolderType<cocos2d::Data, true>::value(arg0), HolderType<std::string, true>::value(arg1), HolderType<std::string, true>::value(arg2), HolderType<std::string, true>::value(arg3));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_loadData)

static bool js_webview_WebView_setOnDidFinishLoading(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_setOnDidFinishLoading : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::function<void (cocos2d::WebView *, const std::string&)>, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, s.thisObject()); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_webview_WebView_setOnDidFinishLoading : Error processing arguments");
        cobj->setOnDidFinishLoading(HolderType<std::function<void (cocos2d::WebView *, const std::string&)>, true>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_setOnDidFinishLoading)

static bool js_webview_WebView_getOnDidFinishLoading(se::State& s)
{
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_webview_WebView_getOnDidFinishLoading : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::WebView::ccWebViewCallback result = cobj->getOnDidFinishLoading();
        ok &= nativevalue_to_se(result, s.rval(), nullptr /*ctx*/);
        SE_PRECONDITION2(ok, false, "js_webview_WebView_getOnDidFinishLoading : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_getOnDidFinishLoading)

static bool js_webview_WebView_create(se::State& s)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        auto result = cocos2d::WebView::create();
        result->retain();
        auto obj = se::Object::createObjectWithClass(__jsb_cocos2d_WebView_class);
        obj->setPrivateData(result);
        s.rval().setObject(obj);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_webview_WebView_create)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_WebView_finalize)

static bool js_webview_WebView_constructor(se::State& s) // constructor.c
{
    cocos2d::WebView* cobj = JSB_ALLOC(cocos2d::WebView);
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(js_webview_WebView_constructor, __jsb_cocos2d_WebView_class, js_cocos2d_WebView_finalize)




static bool js_cocos2d_WebView_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::WebView)", s.nativeThisObject());
    cocos2d::WebView* cobj = (cocos2d::WebView*)s.nativeThisObject();
    cobj->release();
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_WebView_finalize)

bool js_register_webview_WebView(se::Object* obj)
{
    auto cls = se::Class::create("WebView", obj, nullptr, _SE(js_webview_WebView_constructor));

    cls->defineFunction("setOnShouldStartLoading", _SE(js_webview_WebView_setOnShouldStartLoading));
    cls->defineFunction("setOnDidFailLoading", _SE(js_webview_WebView_setOnDidFailLoading));
    cls->defineFunction("canGoBack", _SE(js_webview_WebView_canGoBack));
    cls->defineFunction("loadHTMLString", _SE(js_webview_WebView_loadHTMLString));
    cls->defineFunction("goForward", _SE(js_webview_WebView_goForward));
    cls->defineFunction("goBack", _SE(js_webview_WebView_goBack));
    cls->defineFunction("setScalesPageToFit", _SE(js_webview_WebView_setScalesPageToFit));
    cls->defineFunction("getOnDidFailLoading", _SE(js_webview_WebView_getOnDidFailLoading));
    cls->defineFunction("loadFile", _SE(js_webview_WebView_loadFile));
    cls->defineFunction("loadURL", _SE(js_webview_WebView_loadURL));
    cls->defineFunction("setBounces", _SE(js_webview_WebView_setBounces));
    cls->defineFunction("evaluateJS", _SE(js_webview_WebView_evaluateJS));
    cls->defineFunction("setOnJSCallback", _SE(js_webview_WebView_setOnJSCallback));
    cls->defineFunction("setBackgroundTransparent", _SE(js_webview_WebView_setBackgroundTransparent));
    cls->defineFunction("setJavascriptInterfaceScheme", _SE(js_webview_WebView_setJavascriptInterfaceScheme));
    cls->defineFunction("getOnJSCallback", _SE(js_webview_WebView_getOnJSCallback));
    cls->defineFunction("canGoForward", _SE(js_webview_WebView_canGoForward));
    cls->defineFunction("getOnShouldStartLoading", _SE(js_webview_WebView_getOnShouldStartLoading));
    cls->defineFunction("stopLoading", _SE(js_webview_WebView_stopLoading));
    cls->defineFunction("setFrame", _SE(js_webview_WebView_setFrame));
    cls->defineFunction("setVisible", _SE(js_webview_WebView_setVisible));
    cls->defineFunction("reload", _SE(js_webview_WebView_reload));
    cls->defineFunction("loadData", _SE(js_webview_WebView_loadData));
    cls->defineFunction("setOnDidFinishLoading", _SE(js_webview_WebView_setOnDidFinishLoading));
    cls->defineFunction("getOnDidFinishLoading", _SE(js_webview_WebView_getOnDidFinishLoading));
    cls->defineStaticFunction("create", _SE(js_webview_WebView_create));
    cls->defineFinalizeFunction(_SE(js_cocos2d_WebView_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::WebView>(cls);

    __jsb_cocos2d_WebView_proto = cls->getProto();
    __jsb_cocos2d_WebView_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

bool register_all_webview(se::Object* obj)
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

    js_register_webview_WebView(ns);
    return true;
}

#endif //#if (USE_WEB_VIEW > 0) && (CC_PLATFORM == CC_PLATFORM_ANDROID || CC_PLATFORM == CC_PLATFORM_MAC_IOS) && !defined(CC_TARGET_OS_TVOS)
