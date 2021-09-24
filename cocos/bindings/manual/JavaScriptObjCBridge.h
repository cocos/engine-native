/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2021 Xiamen Yaji Software Co., Ltd.

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
#include "cocos/bindings/jswrapper/SeApi.h"
#include <string>
namespace se {
class Object;
}
#define JSO_ERR_OK                 (0)
#define JSO_ERR_TYPE_NOT_SUPPORT   (-1)
#define JSO_ERR_INVALID_ARGUMENTS  (-2)
#define JSO_ERR_METHOD_NOT_FOUND   (-3)
#define JSO_ERR_EXCEPTION_OCCURRED (-4)
#define JSO_ERR_CLASS_NOT_FOUND    (-5)
#define JSO_ERR_VM_FAILURE         (-6)


class JavaScriptObjCBridge {
public:
    static se::Object* bridgeInstance;
    static JavaScriptObjCBridge* bridgeCxxInstance;
    class CallInfo {
    public:
        CallInfo(const char *className, const char *methodName)
        : _className(className),
          _methodName(methodName) {}

        ~CallInfo() {}

        int getErrorCode() const {
            return _error;
        }

        bool execute(const se::ValueArray &argv, se::Value &rval);
    private:
        int _error = JSO_ERR_OK;
        std::string _className;
        std::string _methodName;
    };

    bool callByNative(std::string arg0, std::string arg1);
    inline bool setCallback(const std::function<void(std::string&, std::string&)>& cb){
        if(!callback){
            callback = cb;
            return true;
        }
        return false;
    }

private:
    
    std::function<void(std::string&, std::string&)> callback;
};

bool register_javascript_objc_bridge(se::Object *obj);
bool callPlatformStringMethod(const std::string &eventName, const std::string &inputArg);
