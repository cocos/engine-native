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
#include <string>
#include <vector>
#include "platform/java/jni/JniHelper.h"
#include "cocos/bindings/jswrapper/SeApi.h"
namespace se {
class Object;
}
#define JSJ_ERR_OK                 (0)
#define JSJ_ERR_TYPE_NOT_SUPPORT   (-1)
#define JSJ_ERR_INVALID_SIGNATURES (-2)
#define JSJ_ERR_METHOD_NOT_FOUND   (-3)
#define JSJ_ERR_EXCEPTION_OCCURRED (-4)
#define JSJ_ERR_VM_THREAD_DETACHED (-5)
#define JSJ_ERR_VM_FAILURE         (-6)
#define JSJ_ERR_CLASS_NOT_FOUND    (-7)
using JsCallback = std::function<void(const std::string&, const std::string&)>;
class JavaScriptJavaBridge {
public:
    enum class ValueType : char {
        INVALID,
        VOID,
        INTEGER,
        LONG,
        FLOAT,
        BOOLEAN,
        STRING,
        VECTOR,
        FUNCTION
    };

    using ValueTypes = std::vector<ValueType>;

    using ReturnValue = union {
        int          intValue;
        int64_t      longValue;
        float        floatValue;
        int          boolValue;
        std::string *stringValue;
    };

    class CallInfo {
    public:
        CallInfo(const char *className, const char *methodName, const char *methodSig)
        : _mValid(false),
          _mError(JSJ_ERR_OK),
          _mClassName(className),
          _mMethodName(methodName),
          _mMethodSig(methodSig),
          _mReturnType(ValueType::VOID),
          _mArgumentsCount(0),
          _mRetjstring(nullptr),
          _mEnv(nullptr),
          _mClassID(nullptr),
          _mMethodID(nullptr) {
            memset(&_mRet, 0, sizeof(_mRet));
            _mValid = validateMethodSig() && getMethodInfo();
        }
        ~CallInfo();

        bool isValid() const {
            return _mValid;
        }

        int getErrorCode() const {
            return _mError;
        }

        void tryThrowJSException() const {
            if (_mError != JSJ_ERR_OK) {
                se::ScriptEngine::getInstance()->throwException(getErrorMessage());
            }
        }

        const char *getErrorMessage() const {
            switch (_mError) {
                case JSJ_ERR_TYPE_NOT_SUPPORT:
                    return "argument type is not supported";
                case JSJ_ERR_INVALID_SIGNATURES:
                    return "invalid signature";
                case JSJ_ERR_METHOD_NOT_FOUND:
                    return "method not found";
                case JSJ_ERR_EXCEPTION_OCCURRED:
                    return "excpected occurred";
                case JSJ_ERR_VM_THREAD_DETACHED:
                    return "vm thread detached";
                case JSJ_ERR_VM_FAILURE:
                    return "vm failure";
                case JSJ_ERR_CLASS_NOT_FOUND:
                    return "class not found";
                case JSJ_ERR_OK:
                default:
                    return "NOERROR";
            }
        }

        JNIEnv *getEnv() {
            return _mEnv;
        }

        ValueType argumentTypeAtIndex(size_t index) {
            return _mArgumentsType.at(index);
        }

        int getArgumentsCount() const {
            return _mArgumentsCount;
        }

        ValueType getReturnValueType() {
            return _mReturnType;
        }

        ReturnValue getReturnValue() {
            return _mRet;
        }

        bool execute();
        bool executeWithArgs(jvalue *args);

    private:
        bool _mValid;
        int  _mError;

        std::string _mClassName;
        std::string _mMethodName;
        std::string _mMethodSig;
        int         _mArgumentsCount;
        ValueTypes  _mArgumentsType;
        ValueType   _mReturnType;

        ReturnValue _mRet;
        jstring     _mRetjstring;

        JNIEnv *  _mEnv;
        jclass    _mClassID;
        jmethodID _mMethodID;

        bool      validateMethodSig();
        bool      getMethodInfo();
        ValueType checkType(const std::string &sig, size_t *pos);
    };

    static bool convertReturnValue(ReturnValue retValue, ValueType type, se::Value *ret);
    //Store js object as CXX pointer
    static JavaScriptJavaBridge* bridgeCxxInstance;

    void callByNative(const std::string& arg0, const std::string& arg1);
    inline void setCallback(const JsCallback& cb){
        callback = cb;
    }
private:
    JsCallback callback; // NOLINT(readability-identifier-naming)
};

bool register_javascript_java_bridge(se::Object *obj); // NOLINT(readability-identifier-naming)
bool callPlatformStringMethod(const std::string &arg0, const std::string &arg1); // NOLINT(readability-identifier-naming)
