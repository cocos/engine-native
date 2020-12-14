#include "UIPhase.h"
#include "ForwardPipeline.h"
#include "pipeline/PipelineStateManager.h"
#include "gfx/GFXCommandBuffer.h"

namespace cc {
namespace pipeline {

void UIPhase::activate(RenderPipeline *pipeline){
    _pipeline = pipeline;
};

void UIPhase::render(Camera *camera, gfx::RenderPass *renderPass){
    auto pipeline = static_cast<ForwardPipeline *>(_pipeline);
    auto cmdBuff = pipeline->getCommandBuffers()[0];

    auto batches = camera->getScene()->getUIBatches();
    const auto vis = camera->visibility & static_cast<uint>(LayerList::UI_2D);
    const auto batchCount = batches[0];
    for (size_t i = 1; i < batchCount; ++i) {
        const auto batch = GET_UI_BATCH(batches[i]);
        bool visible = false;
        if (vis) {
            if (camera->visibility == batch->visFlags) {
                visible = true;
            }
        } else {
            if (camera->visibility & batch->visFlags) {
                visible = true;
            }
        }

        if (!visible) continue;
        const auto count = batch->passCount;
        for (auto j = 0; j < count; j++) {
            const auto pass = batch->getPassView(i);
            const auto shader = batch->getShader(i);
            const auto inputAssembler = batch->getInputAssembler();
            const auto ds = batch->getDescriptorSet();
            auto *pso = PipelineStateManager::getOrCreatePipelineState(pass, shader, inputAssembler, renderPass);
            cmdBuff->bindPipelineState(pso);
            cmdBuff->bindDescriptorSet(MATERIAL_SET, pass->getDescriptorSet());
            cmdBuff->bindDescriptorSet(LOCAL_SET, ds);
            cmdBuff->bindInputAssembler(inputAssembler);
            cmdBuff->draw(inputAssembler);
        }
    }
}

}
}
