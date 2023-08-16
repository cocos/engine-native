import hilog from '@ohos.hilog';
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

import worker from '@ohos.worker';
import cocos from "libcocos.so";
import { ContextType } from "../common/Constants"
import { launchEngine } from '../cocos/game'
import { PortProxy } from '../common/PortProxy';

const nativeContext = cocos.getContext(ContextType.WORKER_INIT);
nativeContext.workerInit()

const nativeEditBox = cocos.getContext(ContextType.EDITBOX_UTILS);
const nativeWebView = cocos.getContext(ContextType.WEBVIEW_UTILS);
const appLifecycle = cocos.getContext(ContextType.APP_LIFECYCLE);

let uiPort = new PortProxy(worker.parentPort);

nativeContext.postMessage = function(msgType: string, msgData:string) {
    uiPort.postMessage(msgType, msgData);
}

nativeContext.postSyncMessage = async function(msgType: string, msgData:string) {
    const result = await uiPort.postSyncMessage(msgType, msgData);
   return result;
}

// The purpose of this is to avoid being GC
nativeContext.setPostMessageFunction.call(nativeContext, nativeContext.postMessage)
nativeContext.setPostSyncMessageFunction.call(nativeContext, nativeContext.postSyncMessage)

uiPort._messageHandle = function(e) {
    var data = e.data;
    var msg = data.data;
    hilog.info(0x0000, 'testTag',msg.name,msg.param);

    switch(msg.name) {
        case "onXCLoad":
            hilog.info(0x0000, 'testTag', '%{public}s', '_messageHandle onXCLoad');
            console.info("cocos worker:_messageHandle onXCLoad");
            const renderContext = cocos.getContext(ContextType.NATIVE_RENDER_API);
            renderContext.nativeEngineInit();
            hilog.info(0x0000, 'testTag', '%{public}s', 'begin invoke launchEngine');
            launchEngine().then(() => {
                hilog.info(0x0000, 'testTag', '%{public}s', 'launch CC engine finished');
                console.info('launch CC engine finished');
            }).catch(e => {
                hilog.info(0x0000, 'testTag', '%{public}s', 'launch CC engine failed');
                console.error('launch CC engine failed');
            });

           // @ts-ignore
            globalThis.oh.postMessage = nativeContext.postMessage;
           // @ts-ignore
            globalThis.oh.postSyncMessage = nativeContext.postSyncMessage;
            renderContext.nativeEngineStart();
            break;
        case "onTextInput":
            nativeEditBox.onTextChange(msg.param);
            break;
        case "onComplete":
            nativeEditBox.onComplete(msg.param);
            break;
        case "onPageBegin":
            nativeWebView.shouldStartLoading(msg.param.viewTag, msg.param.url);
            break;
        case "onPageEnd":
            nativeWebView.finishLoading(msg.param.viewTag, msg.param.url);
            break;
        case "onErrorReceive":
            nativeWebView.failLoading(msg.param.viewTag, msg.param.url);
            break;
        case "onVideoEvent":
            // @ts-ignore
            if(globalThis.oh && typeof globalThis.oh.onVideoEvent === "function") {
                // @ts-ignore
                globalThis.oh.onVideoEvent(msg.param.videoTag, msg.param.videoEvent, msg.param.args);
            }
            break;
        case "backPress":
                appLifecycle.onBackPress();
                break;
        default:
            hilog.info(0x0000, 'testTag', 'cocos worker: message type unknown:%{public}s', msg.name);
            console.error("cocos worker: message type unknown");
            break;
    }
}
