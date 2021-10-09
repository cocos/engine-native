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

#include "VKStd.h"

#include "VKCommandBuffer.h"
#include "VKCommands.h"
#include "VKDevice.h"
#include "VKQuery.h"
#include "vulkan/vulkan_core.h"

namespace cc {
namespace gfx {

CCVKQuery::CCVKQuery() {
    _typedID = generateObjectID<decltype(this)>();
}

CCVKQuery::~CCVKQuery() {
    destroy();
}

void CCVKQuery::doInit(const QueryInfo& /*info*/) {
    CCVKDevice* device = CCVKDevice::getInstance();
    if (device->hasFeature(gfx::Feature::OCCLUSION_QUERY)) {
        _gpuQuery       = CC_NEW(CCVKGPUQuery);
        _gpuQuery->type = _type;
        cmdFuncCCVKCreateQuery(device, _gpuQuery);
    }
}

void CCVKQuery::doDestroy() {
    if (_gpuQuery) {
        CCVKDevice::getInstance()->gpuRecycleBin()->collect(_gpuQuery);
        _gpuQuery = nullptr;
    }
}

void CCVKQuery::getResults() {
    auto queryCount = static_cast<uint32_t>(_ids.size());
    CCASSERT(queryCount <= MAX_QUERY_OBJECTS, "Too many query commands.");
    std::vector<uint64_t> results(queryCount, 0ULL);

    if (queryCount > 0U) {
        CCVKDevice* device = CCVKDevice::getInstance();

        VK_CHECK(vkGetQueryPoolResults(
            device->gpuDevice()->vkDevice,
            _gpuQuery->pool,
            0,
            queryCount,
            queryCount * sizeof(uint64_t),
            results.data(),
            sizeof(uint64_t),
            VK_QUERY_RESULT_64_BIT | VK_QUERY_RESULT_WAIT_BIT));
    }

    {
        std::lock_guard<std::mutex> lock(_mutex);
        _results.clear();
        for (auto queryId = 0U; queryId < queryCount; queryId++) {
            uint32_t id = _ids[queryId];

            if (_results.count(id) == 0) {
                _results[id] = 0;
            }

            _results[id] += results[queryId];
        }
    }
}

void CCVKQuery::copyResults(std::unordered_map<uint32_t, uint64_t>& results) {
    std::lock_guard<std::mutex> lock(_mutex);
    results = _results;
}

} // namespace gfx
} // namespace cc
