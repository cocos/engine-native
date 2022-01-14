#pragma once
#include "base/Config.h"
#if USE_AR_MODULE > 0
#include <type_traits>
#include "cocos/bindings/jswrapper/SeApi.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/ar/ARModule.h"

extern se::Object* __jsb_cc_ar_ARModule_proto; // NOLINT(readability-identifier-naming, bugprone-reserved-identifier)
extern se::Class* __jsb_cc_ar_ARModule_class; // NOLINT(readability-identifier-naming, bugprone-reserved-identifier)

bool js_register_cc_ar_ARModule(se::Object* obj); // NOLINT(readability-identifier-naming)
bool register_all_ar(se::Object* obj); // NOLINT(readability-identifier-naming)

JSB_REGISTER_OBJECT_TYPE(cc::ar::ARModule);
SE_DECLARE_FUNC(js_ar_ARModule_setCameraTextureName);
SE_DECLARE_FUNC(js_ar_ARModule_start);
SE_DECLARE_FUNC(js_ar_ARModule_onResume);
SE_DECLARE_FUNC(js_ar_ARModule_onPause);
SE_DECLARE_FUNC(js_ar_ARModule_beforeUpdate);
SE_DECLARE_FUNC(js_ar_ARModule_update);
SE_DECLARE_FUNC(js_ar_ARModule_ARModule);

#endif //#if USE_AR_MODULE > 0
