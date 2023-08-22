/****************************************************************************
 Copyright (c) 2022-2023 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#pragma once

#include <napi/native_api.h>
#include <uv.h>
#include "scripting/js-bindings/jswrapper/SeApi.h"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"

namespace cocos2d {

class NapiHelper {
public:

    static napi_value getContext(napi_env env, napi_callback_info info);
    // APP Lifecycle
    static napi_value napiOnCreate(napi_env env, napi_callback_info info);
    static napi_value napiOnShow(napi_env env, napi_callback_info info);
    static napi_value napiOnHide(napi_env env, napi_callback_info info);
    static napi_value napiOnDestroy(napi_env env, napi_callback_info info);
    static napi_value napiOnBackPress(napi_env env, napi_callback_info info);

    // JS Page : Lifecycle
    static napi_value napiOnPageShow(napi_env env, napi_callback_info info);
    static napi_value napiOnPageHide(napi_env env, napi_callback_info info);

    // Worker Func
    static napi_value napiWorkerInit(napi_env env, napi_callback_info info);
    static napi_value napiASend(napi_env env, napi_callback_info info);
    static napi_value napiNativeEngineInit(napi_env env, napi_callback_info info);
    static napi_value napiNativeEngineStart(napi_env env, napi_callback_info info);

    static napi_value napiWritablePathInit(napi_env env, napi_callback_info info);
    static napi_value napiResourceManagerInit(napi_env env, napi_callback_info info);

    template <class ReturnType>
    static napi_value napiCallFunction(const std::string& functionName, ReturnType* value) {
        if (!se::ScriptEngine::getInstance()->isValid()) {
            return nullptr;
        }
        se::Value tickVal;
        se::AutoHandleScope scope;
        if (tickVal.isUndefined()) {
            se::ScriptEngine::getInstance()->getGlobalObject()->getProperty(functionName, &tickVal);
        }
        se::Value rval;
        se::ValueArray tickArgsValArr(1);
        if (!tickVal.isUndefined()) {
            tickVal.toObject()->call(tickArgsValArr, nullptr, &rval);
        }
        if(rval.isNullOrUndefined()) {
            return nullptr;
        }
        bool ok = true;
        ok &= seval_to_native_base_type(rval, value);
        SE_PRECONDITION2(ok, nullptr, "Error processing arguments");
        return nullptr;
    }

    static napi_value napiCallFunctionByStrArgs(const std::string& functionName, const std::string& args1, int32_t* value) {
        if (!se::ScriptEngine::getInstance()->isValid()) {
            return nullptr;
        }
        se::Value tickVal;
        se::AutoHandleScope scope;
        if (tickVal.isUndefined()) {
            se::ScriptEngine::getInstance()->getGlobalObject()->getProperty(functionName, &tickVal);
        }
        se::Value rval;
        se::ValueArray tickArgsValArr;
        tickArgsValArr.push_back(se::Value(args1));
        if (!tickVal.isUndefined()) {
            tickVal.toObject()->call(tickArgsValArr, nullptr, &rval);
        }
        if(rval.isNullOrUndefined()) {
            return nullptr;
        }
        bool ok = true;
        ok &= seval_to_native_base_type(rval, value);
        SE_PRECONDITION2(ok, nullptr, "Error processing arguments");
        return nullptr;
    }

    static napi_value napiCallFunctionByFloatArgs(const std::string& functionName, float& sec, int32_t* value) {
        if (!se::ScriptEngine::getInstance()->isValid()) {
            return nullptr;
        }
        se::Value tickVal;
        se::AutoHandleScope scope;
        if (tickVal.isUndefined()) {
            se::ScriptEngine::getInstance()->getGlobalObject()->getProperty(functionName, &tickVal);
        }
        se::Value rval;
        se::ValueArray tickArgsValArr;
        tickArgsValArr.push_back(se::Value(sec));
        if (!tickVal.isUndefined()) {
            tickVal.toObject()->call(tickArgsValArr, nullptr, &rval);
        }
        if(rval.isNullOrUndefined()) {
            return nullptr;
        }
        bool ok = true;
        ok &= seval_to_native_base_type(rval, value);
        SE_PRECONDITION2(ok, nullptr, "Error processing arguments");
        return nullptr;
    }

    static napi_value napiSetPostMessageFunction(napi_env env, napi_callback_info info);
    // Napi export
    static bool exportFunctions(napi_env env, napi_value exports);

    static void postStringMessageToUIThread(const std::string& type, std::string param) {
        if (!_postMsg2UIThreadCb) {
            return;
        }
        CC_UNUSED bool ok = true;
        se::Value value;
        ok &= std_string_to_seval(param, &value);
        _postMsg2UIThreadCb(type, value);
    }

    static void postIntMessageToUIThread(const std::string& type, int param) {
        if (!_postMsg2UIThreadCb) {
            return;
        }
        CC_UNUSED bool ok = true;
        se::Value value;
        ok &= native_int_to_se(param, value, nullptr /*ctx*/);
        _postMsg2UIThreadCb(type, value);
    }

    static void postUnorderedMapMessageToUIThread(const std::string& type, std::unordered_map<std::string, cocos2d::Value> param) {
        if (!_postMsg2UIThreadCb) {
            return;
        }
        CC_UNUSED bool ok = true;
        se::Value value;
        ok &= native_unorderedmap_to_se(param, value, nullptr /*ctx*/);
        _postMsg2UIThreadCb(type, value);
    }

public:
    using PostMessage2UIThreadCb = std::function<void(const std::string&, const se::Value&)>;
    static PostMessage2UIThreadCb _postMsg2UIThreadCb;
    using PostSyncMessage2UIThreadCb = std::function<void(const std::string&, const se::Value&, se::Value*)>;
    static PostSyncMessage2UIThreadCb _postSyncMsg2UIThreadCb;
};

}
