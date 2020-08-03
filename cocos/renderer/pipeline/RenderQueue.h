#pragma once

#include "Define.h"

namespace cc {
namespace pipeline {

class CC_DLL RenderQueue : public Object {
public:
    RenderQueue(const RenderQueueDesc &desc);

    void clear();
    bool insertRenderPass(const RenderObject &renderObj, uint subModelIdx, uint passIdx);
    void recordCommandBuffer(gfx::Device *device, gfx::RenderPass *renderPass, gfx::CommandBuffer *cmdBuff);
    void sort();

private:
    RenderPassList _queue;
    RenderQueueDesc _passDesc;
};

} // namespace pipeline
} // namespace cc
