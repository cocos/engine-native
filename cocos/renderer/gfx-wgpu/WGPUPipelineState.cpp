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

#include "WGPUPipelineState.h"
#include <emscripten/html5_webgpu.h>
#include "WGPUDescriptorSetLayout.h"
#include "WGPUDevice.h"
#include "WGPUObject.h"
#include "WGPUPipelineLayout.h"
#include "WGPURenderPass.h"
#include "WGPUShader.h"
#include "WGPUUtils.h"
namespace cc {
namespace gfx {

using namespace emscripten;

CCWGPUPipelineState::CCWGPUPipelineState() : wrapper<PipelineState>(val::object()) {
}

void CCWGPUPipelineState::doInit(const PipelineStateInfo& info) {
    _gpuPipelineStateObj                         = CC_NEW(CCWGPUPipelineStateObject);
    auto*                         pipelineLayout = static_cast<CCWGPUPipelineLayout*>(info.pipelineLayout);
    const DepthStencilAttachment& dsAttachment   = info.renderPass->getDepthStencilAttachment();
    if (info.bindPoint == PipelineBindPoint::GRAPHICS) {
        const AttributeList&             attrs  = info.shader->getAttributes();
        uint64_t                         offset = 0;
        std::vector<WGPUVertexAttribute> wgpuAttrs(attrs.size());
        bool                             isInstance = attrs[0].isInstanced;
        for (size_t i = 0; i < attrs.size(); i++) {
            wgpuAttrs[i].format         = toWGPUVertexFormat(attrs[i].format);
            wgpuAttrs[i].offset         = offset;
            wgpuAttrs[i].shaderLocation = attrs[i].location;
            offset += GFX_FORMAT_INFOS[static_cast<uint>(attrs[i].format)].size;
        }

        WGPUVertexBufferLayout vertexBufferLayout = {
            .arrayStride    = offset,
            .stepMode       = isInstance ? WGPUInputStepMode_Instance : WGPUInputStepMode_Vertex,
            .attributeCount = wgpuAttrs.size(),
            .attributes     = wgpuAttrs.data(),
        };

        WGPUVertexState vertexState = {
            .nextInChain = nullptr,
            .module      = static_cast<CCWGPUShader*>(info.shader)->gpuShaderObject()->wgpuShaderVertexModule,
            .entryPoint  = "main",
            .bufferCount = 1,
            .buffers     = &vertexBufferLayout,
        };

        bool stripTopology = (info.primitive == PrimitiveMode::LINE_STRIP || info.primitive == PrimitiveMode::TRIANGLE_STRIP);

        WGPUPrimitiveState primitiveState = {
            .nextInChain      = nullptr,
            .topology         = toWGPUPrimTopology(info.primitive),
            .stripIndexFormat = stripTopology ? WGPUIndexFormat_Uint16 : WGPUIndexFormat_Undefined, //TODO_Zeqiang: ???
            .frontFace        = info.rasterizerState.isFrontFaceCCW ? WGPUFrontFace::WGPUFrontFace_CCW : WGPUFrontFace::WGPUFrontFace_CW,
            .cullMode         = info.rasterizerState.cullMode == CullMode::FRONT ? WGPUCullMode::WGPUCullMode_Front
                                                                         : info.rasterizerState.cullMode == CullMode::BACK ? WGPUCullMode::WGPUCullMode_Back
                                                                                                                           : WGPUCullMode::WGPUCullMode_None,
        };

        WGPUStencilFaceState stencilFront = {
            .compare     = toWGPUCompareFunction(info.depthStencilState.stencilFuncFront),
            .failOp      = toWGPUStencilOperation(info.depthStencilState.stencilFailOpFront),
            .depthFailOp = toWGPUStencilOperation(info.depthStencilState.stencilZFailOpFront),
            .passOp      = toWGPUStencilOperation(info.depthStencilState.stencilPassOpFront),
        };

        WGPUStencilFaceState stencilBack = {
            .compare     = toWGPUCompareFunction(info.depthStencilState.stencilFuncBack),
            .failOp      = toWGPUStencilOperation(info.depthStencilState.stencilFailOpBack),
            .depthFailOp = toWGPUStencilOperation(info.depthStencilState.stencilZFailOpBack),
            .passOp      = toWGPUStencilOperation(info.depthStencilState.stencilPassOpBack),
        };

        WGPUDepthStencilState dsState = {
            .nextInChain         = nullptr,
            .format              = toWGPUTextureFormat(dsAttachment.format),
            .depthWriteEnabled   = info.depthStencilState.depthWrite != 0,
            .depthCompare        = toWGPUCompareFunction(info.depthStencilState.depthFunc),
            .stencilFront        = stencilFront,
            .stencilBack         = stencilBack,
            .stencilReadMask     = info.depthStencilState.stencilReadMaskFront,
            .stencilWriteMask    = info.depthStencilState.stencilWriteMaskFront,
            .depthBias           = static_cast<int32_t>(info.rasterizerState.depthBias),
            .depthBiasSlopeScale = info.rasterizerState.depthBiasSlop,
            .depthBiasClamp      = info.rasterizerState.depthBiasClamp,
        };

        WGPUMultisampleState msState = {
            .count                  = static_cast<CCWGPURenderPass*>(info.renderPass)->gpuRenderPassObject()->sampleCount,
            .mask                   = 0xFFFFFFFF,
            .alphaToCoverageEnabled = info.blendState.isA2C != 0,
        };

        const ColorAttachmentList&        colors = info.renderPass->getColorAttachments();
        std::vector<WGPUColorTargetState> colorTargetStates(colors.size());

        std::vector<WGPUBlendState> blendState(colors.size());

        for (size_t i = 0; i < colors.size(); i++) {
            colorTargetStates[i].format = toWGPUTextureFormat(colors[i].format);
            blendState[i]
                .color = {
                .operation = toWGPUBlendOperation(info.blendState.targets[i].blendAlphaEq),
                .srcFactor = toWGPUBlendFactor(info.blendState.targets[i].blendSrc),
                .dstFactor = toWGPUBlendFactor(info.blendState.targets[i].blendDst),
            };
            blendState[i].alpha = {
                .operation = toWGPUBlendOperation(info.blendState.targets[i].blendAlphaEq),
                .srcFactor = toWGPUBlendFactor(info.blendState.targets[i].blendSrc),
                .dstFactor = toWGPUBlendFactor(info.blendState.targets[i].blendDst),
            };
            colorTargetStates[i].blend     = &blendState[i];
            colorTargetStates[i].writeMask = toWGPUColorWriteMask(info.blendState.targets[i].blendColorMask);
            printf("bs sec, dst: %d, %dn", info.blendState.targets[i].blendSrc, info.blendState.targets[i].blendDst);
        }

        WGPUFragmentState fragmentState = {
            .module      = static_cast<CCWGPUShader*>(info.shader)->gpuShaderObject()->wgpuShaderFragmentModule,
            .entryPoint  = "main",
            .targetCount = colorTargetStates.size(),
            .targets     = colorTargetStates.data(),
        };

        pipelineLayout->prepare();
        WGPURenderPipelineDescriptor2 piplineDesc = {
            .nextInChain  = nullptr,
            .label        = nullptr,
            .layout       = pipelineLayout->gpuPipelineLayoutObject()->wgpuPipelineLayout,
            .vertex       = vertexState,
            .primitive    = primitiveState,
            .depthStencil = dsState.format == WGPUTextureFormat_Undefined ? nullptr : &dsState,
            .multisample  = msState,
            .fragment     = &fragmentState,
        };
        printf("ppshn: %s\n", static_cast<CCWGPUShader*>(info.shader)->gpuShaderObject()->name.c_str());
        _gpuPipelineStateObj->wgpuRenderPipeline = wgpuDeviceCreateRenderPipeline2(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &piplineDesc);
    } else if (info.bindPoint == PipelineBindPoint::COMPUTE) {
        WGPUProgrammableStageDescriptor psDesc = {
            .module     = static_cast<CCWGPUShader*>(info.shader)->gpuShaderObject()->wgpuShaderComputeModule,
            .entryPoint = "main",
        };
        pipelineLayout->prepare();
        WGPUComputePipelineDescriptor piplineDesc = {
            .layout       = pipelineLayout->gpuPipelineLayoutObject()->wgpuPipelineLayout,
            .computeStage = psDesc,
        };
        _gpuPipelineStateObj->wgpuComputePipeline = wgpuDeviceCreateComputePipeline(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &piplineDesc);
        printf("ppshn: %s\n", static_cast<CCWGPUShader*>(info.shader)->gpuShaderObject()->name.c_str());
    } else {
        CC_LOG_ERROR("unsupport pipeline bind point");
    }
}

void CCWGPUPipelineState::doDestroy() {
    if (_gpuPipelineStateObj) {
        if (_gpuPipelineStateObj->wgpuRenderPipeline) {
            wgpuRenderPipelineRelease(_gpuPipelineStateObj->wgpuRenderPipeline);
        }
        if (_gpuPipelineStateObj->wgpuComputePipeline) {
            wgpuComputePipelineRelease(_gpuPipelineStateObj->wgpuComputePipeline);
        }

        CC_DELETE(_gpuPipelineStateObj);
    }
}

} // namespace gfx
} // namespace cc