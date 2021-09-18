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
#include "jsb_dispatch_platform_event.h"
#include <functional>
#include <unordered_map>
#include <iostream>


#if CC_PLATFORM == CC_PLATFORM_ANDROID
#include "cocos/platform/java/jni/JniHelper.h"

namespace cc {

	bool callPlatformStringMethod(const std::string &eventName, const std::string &inputArg) {
    try{
        JniHelper::callStaticVoidMethod(
                "com/cocos/lib/CocosMethodManager", "applyMethod", eventName, inputArg);
        return true;
    }
    catch (std::exception e) {
        return false;
    }
}




} // namespace cc

#elif CC_PLATFORM == CC_PLATFORM_WINDOWS

namespace cc {
using ccCustomEventCallBack = std::function<std::string(const std::string &)>;
class CocosMethodManager {
private:
    static std::unordered_map<std::string, ccCustomEventCallBack> customEventMap;

public:
    static CocosMethodManager getInstance() {
        static CocosMethodManager c;
        return c;
    }
    bool dispatchCustomEvent(const std::string &eventName, const std::string &arg, std::string &retVal) {
        if (customEventMap.find(eventName)==customEventMap.end()) {
            return false;
        }
        retVal = customEventMap[eventName](arg);
        return true;
    }
    bool registerCustomEvent(const std::string &eventName, ccCustomEventCallBack f) {
        if (customEventMap.find(eventName)==customEventMap.end()) {
            customEventMap[eventName] = f;
            return true;
        }
        return false;
    }
};
bool callPlatformStringMethod(const std::string &eventName, const std::string &inputArg) {
    try{
		CocosMethodManager::getInstance().dispatchCustomEvent(eventName, inputArg, returnVal[1]);
		return true;
	}
	catch(std::exception exp){
		return false;
	}
    //temperary only send result field
}
} // namespace cc

#endif
