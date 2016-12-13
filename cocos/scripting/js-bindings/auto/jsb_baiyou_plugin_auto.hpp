#include "base/ccConfig.h"
#ifndef __baiyou_plugin_h__
#define __baiyou_plugin_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_baiyou_BaiyouPlugin_class;
extern JSObject *jsb_baiyou_BaiyouPlugin_prototype;

bool js_baiyou_plugin_BaiyouPlugin_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_baiyou_plugin_BaiyouPlugin_finalize(JSContext *cx, JSObject *obj);
void js_register_baiyou_plugin_BaiyouPlugin(JSContext *cx, JS::HandleObject global);
void register_all_baiyou_plugin(JSContext* cx, JS::HandleObject obj);
bool js_baiyou_plugin_BaiyouPlugin_init(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_BaiyouPlugin_getProperty(JSContext *cx, uint32_t argc, jsval *vp);
bool js_baiyou_plugin_BaiyouPlugin_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

#endif // __baiyou_plugin_h__
