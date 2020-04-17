#pragma once
#include "base/ccConfig.h"
#include <type_traits>
#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "cocos/scripting/js-bindings/manual/jsb_conversions.hpp"
#include "renderer/gfx-gles3/GFXGLES3.h"

extern se::Object* __jsb_cocos2d_GLES3Device_proto;
extern se::Class* __jsb_cocos2d_GLES3Device_class;

bool js_register_cocos2d_GLES3Device(se::Object* obj);
bool register_all_gles3(se::Object* obj);

JSB_REGISTER_OBJECT_TYPE(cocos2d::GLES3Device);
SE_DECLARE_FUNC(js_gles3_GLES3Device_checkExtension);
SE_DECLARE_FUNC(js_gles3_GLES3Device_useVAO);
SE_DECLARE_FUNC(js_gles3_GLES3Device_GLES3Device);

