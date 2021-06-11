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

#include "DummyJobGraph.h"

#define DUMMY_GRAPH_NODE_CHUNK_SIZE 64

namespace {

class DummyGraphNode;
class DummyGraph : public cc::DummyGraphItf {
public:
    DummyGraph() noexcept          = default;
    DummyGraph(const DummyGraph &) = delete;
    DummyGraph(DummyGraph &&)      = delete;
    ~DummyGraph() noexcept;
    size_t addNode(std::function<void()> fn) override;           //NOLINT(bugprone-exception-escape)
    void   run() noexcept;                                       //NOLINT(bugprone-exception-escape)
    void   link(size_t precede, size_t after) noexcept override; //NOLINT(bugprone-exception-escape)
    void   walk(DummyGraphNode *node) noexcept;                  //NOLINT(bugprone-exception-escape)
    void   clear() noexcept;                                     //NOLINT(bugprone-exception-escape)
private:
    inline bool excuted(DummyGraphNode *n) const;

    int                           _generation = 0;
    std::vector<DummyGraphNode *> _nodes;
};

class DummyGraphNode {
private:
    DummyGraphNode *_next       = nullptr;
    int             _generation = 0;

    static void            allocChunk();
    static DummyGraphNode *alloc();
    static void            free(DummyGraphNode *n);
    static void            freeAll();

    std::function<void(DummyGraphNode *)> _callback;
    std::unordered_set<DummyGraphNode *>  _successors{};                           // 后续
    std::unordered_set<DummyGraphNode *>  _predecessors{};                         // 前提
    void                                  succeed(DummyGraphNode *other) noexcept; //NOLINT(bugprone-exception-escape)
    void                                  precede(DummyGraphNode *other) noexcept; //NOLINT(bugprone-exception-escape)

    inline void reset() noexcept {
        _successors.clear();
        _predecessors.clear();
    }

public:
    DummyGraphNode() noexcept              = default;
    DummyGraphNode(const DummyGraphNode &) = delete;
    DummyGraphNode(DummyGraphNode &&)      = delete;
    friend class DummyGraph;
};

void DummyGraphNode::succeed(DummyGraphNode *other) noexcept { //NOLINT(bugprone-exception-escape)
    // Run after other
    this->_predecessors.emplace(other);
    other->_successors.emplace(this);
}

void DummyGraphNode::precede(DummyGraphNode *other) noexcept { //NOLINT(bugprone-exception-escape)
    // Run before other
    other->succeed(this);
}

DummyGraphNode *              freeList = nullptr;
std::vector<DummyGraphNode *> allocatedChunks;

void DummyGraphNode::allocChunk() {
    assert(freeList == nullptr);
    freeList = new DummyGraphNode[DUMMY_GRAPH_NODE_CHUNK_SIZE]();
    allocatedChunks.emplace_back(freeList);
    for (auto i = 0; i < DUMMY_GRAPH_NODE_CHUNK_SIZE - 1; i++) {
        freeList[i]._next = &freeList[i + 1];
    }
    freeList[DUMMY_GRAPH_NODE_CHUNK_SIZE - 1]._next = nullptr;
}

DummyGraphNode *DummyGraphNode::alloc() {
    if (freeList == nullptr) {
        DummyGraphNode::allocChunk();
    }
    auto *p  = freeList;
    freeList = freeList->_next;
    p->reset();
    return p;
}

void DummyGraphNode::free(DummyGraphNode *node) {
    node->_next = freeList;
    freeList    = node;
}

void DummyGraphNode::freeAll() {
    for (auto *chunk : allocatedChunks) {
        delete[] chunk;
    }
    allocatedChunks.clear();
}

DummyGraph::~DummyGraph() noexcept {
    clear();
}

void DummyGraph::clear() noexcept {
    for (auto *node : _nodes) {
        DummyGraphNode::free(node);
    }
    _nodes.clear();
}

size_t DummyGraph::addNode(std::function<void()> fn) {
    DummyGraphNode *n = DummyGraphNode::alloc();
    n->_callback      = [=](DummyGraphNode * /*unused*/) { fn(); };
    n->_generation    = _generation;
    _nodes.emplace_back(n);
    return _nodes.size() - 1;
}

void DummyGraph::link(size_t precede, size_t after) noexcept { //NOLINT(bugprone-exception-escape)
    _nodes[precede]->precede(_nodes[after]);
}

void DummyGraph::run() noexcept { //NOLINT(bugprone-exception-escape)
    for (auto *node : _nodes) {
        if (!excuted(node)) {
            walk(node);
        }
    }
    _generation++;
}
void DummyGraph::walk(DummyGraphNode *node) noexcept { //NOLINT(bugprone-exception-escape,misc-no-recursion)
    for (DummyGraphNode *n : node->_predecessors) {
        if (!excuted(n)) {
            walk(n);
        }
    }
    if (!excuted(node)) {
        node->_callback(node);
        node->_generation++;
    }

    for (DummyGraphNode *n : node->_successors) {
        if (!excuted(n)) {
            walk(n);
        }
    }
}

inline bool DummyGraph::excuted(DummyGraphNode *n) const {
    return n->_generation != _generation;
}

} // namespace

namespace cc {

DummyJobGraph::DummyJobGraph(DummyJobSystem * /*unused*/) noexcept {
    _dummyGraph = new DummyGraph();
}

DummyJobGraph::~DummyJobGraph() noexcept {
    delete static_cast<DummyGraph *>(_dummyGraph);
}

void DummyJobGraph::makeEdge(uint j1, uint j2) noexcept {
    _dummyGraph->link(j1, j2);
}

void DummyJobGraph::run() noexcept { //NOLINT(bugprone-exception-escape)
    auto *g = static_cast<DummyGraph *>(_dummyGraph);
    g->run();
    g->clear();
}

} // namespace cc
