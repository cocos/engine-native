#include "ShadowMapBatchedQueue.h"
#include "BatchedBuffer.h"
#include "Define.h"
#include "InstancedBuffer.h"
#include "PipelineStateManager.h"
#include "RenderBatchedQueue.h"
#include "RenderInstancedQueue.h"
#include "gfx/GFXCommandBuffer.h"
#include "helper/SharedMemory.h"
#include "forward/ForwardPipeline.h"
#include "forward/SceneCulling.h"
#include "gfx/GFXDescriptorSet.h"
#include "gfx/GFXDevice.h"

namespace cc {
namespace pipeline {

const uint phaseID(PassPhase::getPhaseID("shadow-caster"));

int getShadowPassIndex(const ModelView *model) {
    const auto subModelArrayID = model->getSubModelID();
    const auto count = subModelArrayID[0];
    for (unsigned i = 1; i <= count; i++) {
        const auto subModel = model->getSubModelView(subModelArrayID[i]);
        for (unsigned passIdx = 0; passIdx < subModel->passCount; passIdx++) {
            const auto pass = subModel->getPassView(passIdx);
            if (pass->phase == phaseID) {
                return passIdx;
            }
        }
    }
    return -1;
}

ShadowMapBatchedQueue::ShadowMapBatchedQueue(ForwardPipeline *pipeline)
: _pipeline(pipeline),
    _device(gfx::Device::getInstance()) {
    _buffer = pipeline->getDescriptorSet()->getBuffer(UBOShadow::BLOCK.layout.binding);
    _instancedQueue = CC_NEW(RenderInstancedQueue);
    _batchedQueue = CC_NEW(RenderBatchedQueue);
}

void ShadowMapBatchedQueue::gatherLightPasses(const Light *light) {
    clear();

    const auto *shadowInfo = _pipeline->getShadows();
    const auto &shadowObjects = _pipeline->getShadowObjects();
    if (light && shadowInfo->getShadowType() == ShadowType::SHADOWMAP) {
        updateUBOs(light);

        for (const auto ro : shadowObjects) {
            const auto *model = ro.model;

            switch (light->getType()) {
                case LightType::DIRECTIONAL:
                    add(model);
                    break;
                case LightType::SPOT:
                    if (model->getWorldBounds() &&
                        (!aabb_aabb(model->getWorldBounds(), light->getAABB()) ||
                         !aabb_frustum(model->getWorldBounds(), light->getFrustum()))) {
                        add(model);
                    }
                    break;
                default:;
            }
        }
    }
}

void ShadowMapBatchedQueue::clear() {
    _subModels.clear();
    _shaders.clear();
    _passes.clear();
    if (_instancedQueue) _instancedQueue->clear();
    if (_batchedQueue) _batchedQueue->clear();
}

void ShadowMapBatchedQueue::add(const ModelView *model) {
    // this assumes light pass index is the same for all submodels
    const auto shadowPassIdx = getShadowPassIndex(model);
    if (shadowPassIdx < 0) {
        return;
    }

    const auto subModelID = model->getSubModelID();
    const auto subModelCount = subModelID[0];
    for (unsigned m = 1; m <= subModelCount; ++m) {
        const auto subModel = model->getSubModelView(subModelID[m]);
        const auto pass = subModel->getPassView(shadowPassIdx);
        const auto batchingScheme = pass->getBatchingScheme();
        subModel->getDescriptorSet()->bindBuffer(UBOShadow::BLOCK.layout.binding, _buffer);
        subModel->getDescriptorSet()->update();

        for (unsigned p = 0; p < subModel->passCount; ++p) {
            if (batchingScheme == BatchingSchemes::INSTANCING) {
                auto *instancedBuffer = InstancedBuffer::get(subModel->passID[p]);
                instancedBuffer->merge(model, subModel, p);
                _instancedQueue->add(instancedBuffer);

            } else if (batchingScheme == BatchingSchemes::VB_MERGING) {
                auto *batchedBuffer = BatchedBuffer::get(subModel->passID[p]);
                batchedBuffer->merge(subModel, p, model);
                _batchedQueue->add(batchedBuffer);
            } else { // standard draw
                _subModels.emplace_back(subModel);
                _shaders.emplace_back(subModel->getShader(shadowPassIdx));
                _passes.emplace_back(pass);
            }
        } 
    }
}

void ShadowMapBatchedQueue::recordCommandBuffer(gfx::Device *device, gfx::RenderPass *renderPass, gfx::CommandBuffer *cmdBuffer) const {
    _instancedQueue->recordCommandBuffer(device, renderPass, cmdBuffer);
    _batchedQueue->recordCommandBuffer(device, renderPass, cmdBuffer);

    for (size_t i = 0; i < _subModels.size(); i++) {
        const auto subModel = _subModels[i];
        const auto shader = _shaders[i];
        const auto pass = _passes[i];
        const auto ia = subModel->getInputAssembler();
        const auto pso = PipelineStateManager::getOrCreatePipelineState(pass, shader, ia, renderPass);

        cmdBuffer->bindPipelineState(pso);
        cmdBuffer->bindDescriptorSet(MATERIAL_SET, pass->getDescriptorSet());
        cmdBuffer->bindDescriptorSet(LOCAL_SET, subModel->getDescriptorSet());
        cmdBuffer->bindInputAssembler(ia);
        cmdBuffer->draw(ia);
    }
}

void ShadowMapBatchedQueue::destroy() {
    CC_SAFE_DELETE(_batchedQueue);
    
    CC_SAFE_DELETE(_instancedQueue);

    _buffer = nullptr;
}

void ShadowMapBatchedQueue::updateUBOs(const Light *light) const {
    const auto *shadowInfo = _pipeline->getShadows();
    auto shadowUBO = _pipeline->getShadowUBO();

    switch (light->getType()) {
        case LightType::DIRECTIONAL: {
            // light view
            cc::Mat4 lightView;

            float x = 0, y = 0, farClamp = 0;
            if (shadowInfo->autoAdapt) {
                getShadowWorldMatrix(_pipeline->getSphere(), light->getNode()->worldRotation, light->direction, lightView);
                const auto radius = _pipeline->getSphere()->radius;
                x = radius * shadowInfo->aspect;
                y = radius;

                farClamp = std::min(_pipeline->getReceivedSphere()->radius * COEFFICIENT_OF_EXPANSION, SHADOW_CAMERA_MAX_FAR);
            } else {
                lightView = light->getNode()->worldMatrix;
                x = shadowInfo->orthoSize * shadowInfo->aspect;
                y = shadowInfo->orthoSize;

                farClamp = shadowInfo->farValue;
            }

            const auto &matLightView = lightView.getInversed();

            const auto projectionSinY = _device->getScreenSpaceSignY() * _device->getUVSpaceSignY();
            Mat4 matLightViewProj;
            Mat4::createOrthographicOffCenter(-x, x, -y, y, shadowInfo->nearValue, farClamp, _device->getClipSpaceMinZ(), projectionSinY, &matLightViewProj);

            matLightViewProj.multiply(matLightView);
            memcpy(shadowUBO.data() + UBOShadow::MAT_LIGHT_VIEW_PROJ_OFFSET, matLightViewProj.m, sizeof(matLightViewProj));
        } break;
        case LightType::SPOT: {
            // light view
            const cc::Mat4 lightView = light->getNode()->worldMatrix.getInversed();

            // light proj
            cc::Mat4 lightProj;
            Mat4::createPerspective(light->spotAngle, light->aspect, 0.001f, light->range, &lightProj);

            // light voewProj
            cc::Mat4 lightViewProj = lightProj * lightView;
            memcpy(shadowUBO.data() + UBOShadow::MAT_LIGHT_VIEW_PROJ_OFFSET, lightViewProj.m, sizeof(lightViewProj));
        } break;
        default:;
    }

    float shadowInfos[4] = {shadowInfo->size.x, shadowInfo->size.y, (float)shadowInfo->pcfType, shadowInfo->bias};
    float shadowColor[4] = {shadowInfo->color.x, shadowInfo->color.y, shadowInfo->color.z, shadowInfo->color.w};
    memcpy(shadowUBO.data() + UBOShadow::SHADOW_COLOR_OFFSET, &shadowColor, sizeof(shadowColor));
    memcpy(shadowUBO.data() + UBOShadow::SHADOW_INFO_OFFSET, &shadowInfos, sizeof(shadowInfos));

    _pipeline->getCommandBuffers()[0]->updateBuffer(_pipeline->getDescriptorSet()->getBuffer(UBOShadow::BLOCK.layout.binding), shadowUBO.data(), UBOShadow::SIZE);
}

} // namespace pipeline
} // namespace cc
