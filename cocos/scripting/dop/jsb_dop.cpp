/****************************************************************************
Copyright (c) 2020 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "jsb_dop.h"
#include "TypedPool.h"
#include "cocos/renderer/core/PipelineState.h"
#include "cocos/renderer/core/gfx/GFXDef.h"
#include "cocos/scripting/js-bindings/manual/jsb_global.h"
#include "cocos/scripting/js-bindings/manual/jsb_classtype.h"

template<class Type, size_t pageSize>
bool js_register_se_TypedPool(se::Object* obj, const std::string &name, se::Object** proto, se::Class** cls)
{
    *cls = se::Class::create(name, obj, nullptr, nullptr);

//    cls->defineFunction("getDevicePixelRatio", _SE(js_engine_Device_getDevicePixelRatio));
//    cls->defineStaticFunction("getDeviceModel", _SE(js_engine_Device_getDeviceModel));
    (*cls)->install();
    JSBClassType::registerClass<se::TypedPool<Type, pageSize>>(*cls);

    *proto = (*cls)->getProto();

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* jsb_DepthStencilState_TypedPool_proto = nullptr;
se::Class* jsb_DepthStencilState_TypedPool_class = nullptr;

bool register_all_dop_bindings(se::Object* obj)
{
    js_register_se_TypedPool<cc::gfx::DepthStencilState, cc::gfx::DepthStencilStatePageSize>(obj, "DepthStencilStateTypedPool", &jsb_DepthStencilState_TypedPool_proto, &jsb_DepthStencilState_TypedPool_class);
    return true;
}
