#pragma once
#include "base/ccConfig.h"
#include <type_traits>
#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "cocos/scripting/js-bindings/manual/jsb_conversions.hpp"
#include "cocos/renderer/gfx-metal/GFXMTL.h"

extern se::Object* __jsb_cocos2d_CCMTLDevice_proto;
extern se::Class* __jsb_cocos2d_CCMTLDevice_class;

bool js_register_cocos2d_CCMTLDevice(se::Object* obj);
bool register_all_mtl(se::Object* obj);

JSB_REGISTER_OBJECT_TYPE(cocos2d::CCMTLDevice);
SE_DECLARE_FUNC(js_mtl_CCMTLDevice_getMTKView);
SE_DECLARE_FUNC(js_mtl_CCMTLDevice_getMTLDevice);
SE_DECLARE_FUNC(js_mtl_CCMTLDevice_CCMTLDevice);

