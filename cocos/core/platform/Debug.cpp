/****************************************************************************
 Copyright (c) 2021 Xiamen Yaji Software Co., Ltd.

 http =//www.cocos.com

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

#include "Debug.h"

namespace cc {
namespace debug {
extern const char *CONSOLE_LOG   = "log";
extern const char *CONSOLE_WARN  = "warn";
extern const char *CONSOLE_ERROR = "error";
extern const char *CONSOLE_ASSET = "assert";

std::string getTypedFormatter(const char *tag, uint32_t id) {
    std::string msg;
#if CC_DEBUG > 0
    if (debugInfos.find(id) == debugInfos.end()) {
        msg = "unknown id";
    } else {
        msg = debugInfos[id];
    }
#else
    char szTmp[1024] = {0};
    snprintf(szTmp, sizeof(szTmp), "%s %d, please go to %s#%d to see details.", tag, id, ERROR_MAP_URL.c_str(), id);
    msg = szTmp;
#endif

    return msg;
}

void callConsoleFunction(const char *jsFunctionName, std::string msg, cc::any *arr, int paramsLength) {
    se::AutoHandleScope scope;
    se::ValueArray      args;
    args.push_back(se::Value(msg));

    auto      global = se::ScriptEngine::getInstance()->getGlobalObject();
    se::Value consoleVal;
    se::Value consoleFunction;
    if (global->getProperty("console", &consoleVal) && consoleVal.isObject()) {
        consoleVal.toObject()->getProperty(jsFunctionName, &consoleFunction);
    }

    for (int i = 1; i <= paramsLength; i++) {
        if (arr[i].type() == typeid(const std::string)) {
            const std::string s = cc::any_cast<const std::string>(arr[i]);
            args.push_back(se::Value(s));
        } else if (arr[i].type() == typeid(std::string)) {
            std::string s = cc::any_cast<std::string>(arr[i]);
            args.push_back(se::Value(s));
        } else if (arr[i].type() == typeid(int)) {
            int value = cc::any_cast<int>(arr[i]);
            args.push_back(se::Value(value));
        } else if (arr[i].type() == typeid(float)) {
            float value = cc::any_cast<float>(arr[i]);
            args.push_back(se::Value(value));
        } else if (arr[i].type() == typeid(const char *)) {
            const char *s = cc::any_cast<const char *>(arr[i]);
            args.push_back(se::Value(s));
        } else {
            CC_LOG_ERROR("unsupport params data type");
            return;
        }
    }
    if (consoleFunction.isObject()) {
        consoleFunction.toObject()->call(args, nullptr);
    }
}

} // namespace debug
} //namespace cc