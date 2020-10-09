#include "RenderQueue.h"
#include "PipelineStateManager.h"
#include "gfx/GFXCommandBuffer.h"
#include "gfx/GFXShader.h"
#include "helper/SharedMemory.h"

namespace cc {
namespace pipeline {

RenderQueue::RenderQueue(const RenderQueueCreateInfo &desc)
: _passDesc(desc) {
}

void RenderQueue::clear() {
    _queue.clear();
}

bool RenderQueue::insertRenderPass(const RenderObject &renderObj, uint subModelIdx, uint passIdx) {
    const auto subModels = renderObj.model->getSubModels();
    const auto subModel = renderObj.model->getSubModelView(subModels[subModelIdx]);
    const auto pass = subModel->getPassView(passIdx);
    const auto isTransparent = pass->getBlendState()->targets[0].blend;

    if (isTransparent != _passDesc.isTransparent || !(pass->getPhase() & _passDesc.phases)) {
        return false;
    }

    const auto hash = (0 << 30) | (pass->getPriority() << 16) | (subModel->getPriority() << 8) | passIdx;
    uint shaderID = subModel->getShaderID(passIdx);
    RenderPass renderPass = {hash, renderObj.depth, shaderID, passIdx, subModel};
    _queue.emplace_back(std::move(renderPass));
    return true;
}

void RenderQueue::sort() {
    std::sort(_queue.begin(), _queue.end(), _passDesc.sortFunc);
}

void RenderQueue::recordCommandBuffer(gfx::Device *device, gfx::RenderPass *renderPass, gfx::CommandBuffer *cmdBuff) {
    for (size_t i = 0; i < _queue.size(); ++i) {
        const auto subModel = _queue[i].subModel;
        const auto passIdx = _queue[i].passIndex;
        auto inputAssembler = subModel->getInputAssembler();

        const auto pass = subModel->getPassView(passIdx);
        auto shader = subModel->getShader(passIdx);

        auto pso = PipelineStateManager::getOrCreatePipelineState(pass, shader, inputAssembler, renderPass);
        cmdBuff->bindPipelineState(pso);
        cmdBuff->bindDescriptorSet(static_cast<uint>(SetIndex::MATERIAL), pass->getDescriptorSet());
        cmdBuff->bindDescriptorSet(static_cast<uint>(SetIndex::LOCAL), subModel->getDescriptorSet());
        cmdBuff->bindInputAssembler(inputAssembler);
        cmdBuff->draw(inputAssembler);
    }
}

} // namespace pipeline
} // namespace cc
