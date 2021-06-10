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

#pragma once

#include <functional>
#include "cocos/base/Macros.h"
#include "cocos/base/TypeDef.h"

namespace cc {

class DummyJobSystem;

class DummyGraphItf {
public:
    virtual size_t addNode(std::function<void()> fn)           = 0;
    virtual void   link(size_t precede, size_t after) noexcept = 0;
};

class DummyJobGraph final {
public:
    explicit DummyJobGraph(DummyJobSystem * /*system*/) noexcept;

    ~DummyJobGraph() noexcept;

    template <typename Function>
    uint createJob(Function &&func) noexcept;

    template <typename Function>
    uint createForEachIndexJob(uint begin, uint end, uint step, Function &&func) noexcept;

    void makeEdge(uint j1, uint j2) noexcept;

    void run() noexcept;

    CC_INLINE void waitForAll() { run(); }

private:
    DummyGraphItf *_dummyGraph = nullptr;
};

template <typename Function>
uint DummyJobGraph::createJob(Function &&func) noexcept {
    return _dummyGraph->addNode([fn = std::forward<Function>(func)]() {
        fn();
    });
}

template <typename Function>
uint DummyJobGraph::createForEachIndexJob(uint begin, uint end, uint step, Function &&func) noexcept {
    return _dummyGraph->addNode([callable = std::forward<Function>(func), first = begin, last = end, step = step]() {
        for (auto i = first; i < last; i += step) {
            callable(i);
        }
    });
}

} // namespace cc
