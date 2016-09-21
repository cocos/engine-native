#include "jsb_cocos2dx_cocosAds.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "CocosAds.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;
}
JSClass  *jsb_CocosAds_class;
JSObject *jsb_CocosAds_prototype;

bool js_cocos2dx_cocosAds_CocosAds_hideBanner(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CocosAds* cobj = (CocosAds *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_cocosAds_CocosAds_hideBanner : Invalid Native Object");
    if (argc == 0) {
        cobj->hideBanner();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_cocosAds_CocosAds_hideBanner : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_cocosAds_CocosAds_showBanner(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CocosAds* cobj = (CocosAds *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_cocosAds_CocosAds_showBanner : Invalid Native Object");
    if (argc == 0) {
        cobj->showBanner();
        args.rval().setUndefined();
        return true;
    }
    if (argc == 1) {
        const char* arg0 = nullptr;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_cocosAds_CocosAds_showBanner : Error processing arguments");
        cobj->showBanner(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_cocos2dx_cocosAds_CocosAds_showBanner : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_cocos2dx_cocosAds_CocosAds_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {

        CocosAds* ret = CocosAds::getInstance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<CocosAds>(cx, (CocosAds*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_cocosAds_CocosAds_getInstance : wrong number of arguments");
    return false;
}


void js_register_cocos2dx_cocosAds_CocosAds(JSContext *cx, JS::HandleObject global) {
    jsb_CocosAds_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_CocosAds_class->name = "CocosAds";
    jsb_CocosAds_class->addProperty = JS_PropertyStub;
    jsb_CocosAds_class->delProperty = JS_DeletePropertyStub;
    jsb_CocosAds_class->getProperty = JS_PropertyStub;
    jsb_CocosAds_class->setProperty = JS_StrictPropertyStub;
    jsb_CocosAds_class->enumerate = JS_EnumerateStub;
    jsb_CocosAds_class->resolve = JS_ResolveStub;
    jsb_CocosAds_class->convert = JS_ConvertStub;
    jsb_CocosAds_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("hideBanner", js_cocos2dx_cocosAds_CocosAds_hideBanner, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("showBanner", js_cocos2dx_cocosAds_CocosAds_showBanner, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("getInstance", js_cocos2dx_cocosAds_CocosAds_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_CocosAds_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(),
        jsb_CocosAds_class,
        dummy_constructor<CocosAds>, 0, // no constructor
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);

    JS::RootedObject proto(cx, jsb_CocosAds_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "CocosAds"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<CocosAds>(cx, jsb_CocosAds_class, proto, JS::NullPtr());
}

void register_all_cocos2dx_cocosAds(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "cc", &ns);

    js_register_cocos2dx_cocosAds_CocosAds(cx, ns);
}

#endif //#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
