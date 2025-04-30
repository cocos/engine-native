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
import { ThreadWorkerGlobalScope } from '@ohos.worker';
import { MessageEvent } from '@ohos.worker';
import { WorkerMessage } from '../common/Constants';
import { worker } from '@kit.ArkTS';

export class PortProxy {
  private autoId: number = 0;
  public actionHandleMap = new Map<number, Function>();
  private port: ThreadWorkerGlobalScope | worker.ThreadWorker | null = null;
  public _messageHandle?: (e: MessageEvent<WorkerMessage>) => void;

  constructor(worker: ThreadWorkerGlobalScope | worker.ThreadWorker) {
    this.port = worker;
    this.port.onmessage = this.onMessage.bind(this);
  }

  public onMessage(e: MessageEvent<WorkerMessage>) {
    const data = e['data'];
    if (data.type != "syncResult" && this._messageHandle) {
      this._messageHandle(e);
    } else if (data.type == "syncResult") {
      const id = data.data.id || 0;
      const response = data.data.param;
      if (!this.actionHandleMap.has(id)) {
        return;
      }
      const cb = this.actionHandleMap.get(id);
      if (cb) {
        cb(response);
        this.actionHandleMap.delete(id);
      }

    }
  }

  public postReturnMessage(e: WorkerMessage, res: boolean | string | number | null) {
    if (e.type == "sync" && res != null && res != undefined) {
      const message: WorkerMessage = { type: "syncResult", data: { id: e.data.id, param: res } }
      this.port?.postMessage(message);
    }
  }

  public postMessage(msgName: string, msgData: string | number | boolean | object) {
    const message: WorkerMessage = { type: "async", data: { name: msgName, param: msgData } }
    this.port?.postMessage(message);
  }

  public postSyncMessage(msgName: string, msgData: string) {
    const id = ++this.autoId;
    return new Promise<string>((resolve: (value: string) => void) => {
      const message: WorkerMessage = {
        type: "sync",
        data: { id: id, name: msgName, param: msgData }
      }
      this.port?.postMessage(message);
      this.actionHandleMap.set(id, (response: string) => {
        resolve(response);
      });
    });
  }
}
