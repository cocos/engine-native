/****************************************************************************
 Copyright (c) 2020-2021 Xiamen Yaji Software Co., Ltd.

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

#include "base/CoreStd.h"
#include "base/job-system/JobSystem.h"
#include "base/threading/MessageQueue.h"

#include "CommandBufferAgent.h"
#include "DeviceAgent.h"
#include "QueryAgent.h"

namespace cc {
namespace gfx {

QueryAgent::QueryAgent(Query *actor)
: Agent<Query>(actor) {
    _typedID = actor->getTypedID();
}

QueryAgent::~QueryAgent() {
    ENQUEUE_MESSAGE_1(
        DeviceAgent::getInstance()->getMessageQueue(),
        QueryDestruct,
        actor, _actor,
        {
            CC_SAFE_DELETE(actor);
        });
}

void QueryAgent::doInit(const QueryInfo &info) {
    ENQUEUE_MESSAGE_2(
        DeviceAgent::getInstance()->getMessageQueue(),
        QueryInit,
        actor, getActor(),
        info, info,
        {
            actor->initialize(info);
        });
}

void QueryAgent::doDestroy() {
    ENQUEUE_MESSAGE_1(
        DeviceAgent::getInstance()->getMessageQueue(),
        QueryDestroy,
        actor, getActor(),
        {
            actor->destroy();
        });
}

void QueryAgent::getResults() {
    MessageQueue *msgQ = DeviceAgent::getInstance()->getMessageQueue();

    ENQUEUE_MESSAGE_1(
        DeviceAgent::getInstance()->getMessageQueue(),
        QueryGetResults,
        actor, getActor(),
        {
            actor->getResults();
        });
}

void QueryAgent::copyResults(std::unordered_map<uint32_t, uint64_t> &results) {
    _actor->copyResults(results);
}

} // namespace gfx
} // namespace cc
