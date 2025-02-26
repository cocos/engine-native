/*
 * Copyright (c) 2013-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "scripting/js-bindings/manual/JavaScriptArkTsBridge.h"
#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "cocos/scripting/js-bindings/manual/jsb_conversions.hpp"
#include "bundle/native_interface_bundle.h"
#include "platform/openharmony/napi/NapiHelper.h"
#include <future>

#define JSA_ERR_OK                 (0)
#define JSA_ERR_TYPE_NOT_SUPPORT   (-1)
#define JSA_ERR_INVALID_SIGNATURES (-2)
#define JSA_ERR_METHOD_NOT_FOUND   (-3)
#define JSA_ERR_EXCEPTION_OCCURRED (-4)
#define JSA_ERR_VM_THREAD_DETACHED (-5)
#define JSA_ERR_VM_FAILURE         (-6)
#define JSA_ERR_CLASS_NOT_FOUND    (-7)

class JavaScriptArkTsBridge
{
public:
    class CallInfo
    {
    public:
        CallInfo(bool isSyn, const char *clsPath, const char *methodName, const char *paramStr)
        : _error(JSA_ERR_OK)
        , _isSyn(isSyn)
        , _clsPath(clsPath)
        , _methodName(methodName)
        , _paramStr(paramStr)
        {
        }
        ~CallInfo();

        int getErrorCode() const { return _error; }

        bool execute(se::Value& rval);


    private:
        int _error;
        bool _isSyn;
        const char *_clsPath;
        const char *_methodName;
        const char *_paramStr;
    };
public :
    static char* __getModuleInfo(const char* module_name);
    static char* bundle_name;
};

char* JavaScriptArkTsBridge::bundle_name = nullptr;

JavaScriptArkTsBridge::CallInfo::~CallInfo() {}

char* JavaScriptArkTsBridge::__getModuleInfo(const char* module_name)
{
    if (bundle_name == NULL) {
        OH_NativeBundle_ApplicationInfo info = OH_NativeBundle_GetCurrentApplicationInfo();
        bundle_name = info.bundleName;
    }
    
    char* module_info = (char*)malloc((strlen(bundle_name) + strlen(module_name) + 1) * sizeof(char*));
    strcpy(module_info, "");
    strcat(module_info, bundle_name);
    strcat(module_info, "/");
    strcat(module_info, module_name);
    
    return module_info;
}

se::Value convertToSeValue(const cocos2d::CallbackParamType& value) {
    return std::visit([](auto&& arg) -> se::Value {
       return se::Value(arg);
    },value);
}

bool JavaScriptArkTsBridge::CallInfo::execute(se::Value &rval)
{
    const char* module_name;
    const char* method;
    
    std::string methodStr = _methodName;
    std::string::size_type pos = methodStr.find("/");
    if (pos != std::string::npos) {
        std::string str1 = methodStr.substr(0, pos);
        module_name = str1.c_str();
        std::string str2 = methodStr.substr(pos + 1);
        method = str2.c_str();
    } else {
        method = _methodName;
        std::string pathStr = _clsPath;
        pos = pathStr.find("/");
        module_name = pos != std::string::npos ? pathStr.substr(0, pos).c_str() : "entry";
    }

    char *module_info = __getModuleInfo(module_name);

    std::promise<cocos2d::CallbackParamType> promise;
    std::function<void(cocos2d::CallbackParamType)> cb = [&promise](cocos2d::CallbackParamType message) {
        promise.set_value(message);
    };
    cocos2d::CallParam *callParam = new cocos2d::CallParam{_isSyn, cb, _paramStr, module_info, _clsPath, method};
    if (_isSyn) {
        cocos2d::JSFunction::getFunction("executeMethodSync").invoke(callParam);
    } else {
        cocos2d::JSFunction::getFunction("executeMethodAsync").invoke(callParam);
    }
    cocos2d::CallbackParamType methodResult = promise.get_future().get();
    free(module_info);
    delete callParam;
    rval = se::Value(convertToSeValue(methodResult));
    return true;
}

se::Class* __jsb_JavaScriptArkTsBridge_class = nullptr;

static bool JavaScriptArkTsBridge_finalize(se::State& s)
{
    JavaScriptArkTsBridge* cobj = (JavaScriptArkTsBridge*)s.nativeThisObject();
    delete cobj;
    return true;
}
SE_BIND_FINALIZE_FUNC(JavaScriptArkTsBridge_finalize)

static bool JavaScriptArkTsBridge_constructor(se::State& s)
{
    JavaScriptArkTsBridge* cobj = new (std::nothrow) JavaScriptArkTsBridge();
    s.thisObject()->setPrivateData(cobj);
    return true;
}
SE_BIND_CTOR(JavaScriptArkTsBridge_constructor, __jsb_JavaScriptArkTsBridge_class, JavaScriptArkTsBridge_finalize)

static bool JavaScriptArkTsBridge_callStaticMethod(se::State& s)
{
    const auto& args = s.args();
    int argc = (int)args.size();

    if (argc == 4)
    {
        bool ok = false;
        bool isSyn;
        std::string clsPath, methodName, paramStr;

        ok = seval_to_boolean(args[0], &isSyn);
        SE_PRECONDITION2(ok, false, "Converting isSyn failed!");

        ok = seval_to_std_string(args[1], &clsPath);
        SE_PRECONDITION2(ok, false, "Converting clsPath failed!");

        ok = seval_to_std_string(args[2], &methodName);
        SE_PRECONDITION2(ok, false, "Converting methodName failed!");

        ok = seval_to_std_string(args[3], &paramStr);
        SE_PRECONDITION2(ok, false, "Converting paramStr failed!");

        JavaScriptArkTsBridge::CallInfo call(isSyn, clsPath.c_str(), methodName.c_str(), paramStr.c_str());
        ok = call.execute(s.rval());
        if(!ok) {
            s.rval().setUndefined();
            SE_REPORT_ERROR("call (%s.%s) failed, result code: %d",clsPath.c_str(), methodName.c_str(),
                            call.getErrorCode());
            return false;
        }
    } else {
        SE_REPORT_ERROR("wrong number of arguments: %d, was expecting ==4", argc);
        return false;
    }
    return true;
}
SE_BIND_FUNC(JavaScriptArkTsBridge_callStaticMethod)

bool register_javascript_arkTs_bridge(se::Object* obj)
{
    se::Class* cls = se::Class::create("JavaScriptArkTsBridge", obj, nullptr, _SE(JavaScriptArkTsBridge_constructor));
    cls->defineFinalizeFunction(_SE(JavaScriptArkTsBridge_finalize));

    cls->defineFunction("callStaticMethod", _SE(JavaScriptArkTsBridge_callStaticMethod));

    cls->install();
    __jsb_JavaScriptArkTsBridge_class = cls;

    se::ScriptEngine::getInstance()->clearException();

    return true;
}

