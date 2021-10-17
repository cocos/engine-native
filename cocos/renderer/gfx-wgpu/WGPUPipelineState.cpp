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
    _gpuPipelineStateObj = CC_NEW(CCWGPUPipelineStateObject);
}

void CCWGPUPipelineState::prepare(const std::set<uint8_t>& setInUse) {
    auto* pipelineLayout = static_cast<CCWGPUPipelineLayout*>(_pipelineLayout);

    const DepthStencilAttachment& dsAttachment = _renderPass->getDepthStencilAttachment();
    if (_bindPoint == PipelineBindPoint::GRAPHICS) {
        if (_gpuPipelineStateObj->wgpuRenderPipeline)
            return;
        const AttributeList&             attrs  = _shader->getAttributes();
        uint64_t                         offset = 0;
        std::vector<WGPUVertexAttribute> wgpuAttrs;
        bool                             isInstance = attrs[0].isInstanced;
        uint8_t                          index      = 0;
        for (size_t i = 0; i < attrs.size(); i++) {
            String attrName = attrs[i].name;
            auto   iter     = std::find_if(_inputState.attributes.begin(), _inputState.attributes.end(), [attrName](const Attribute& attr) {
                return strcmp(attrName.c_str(), attr.name.c_str()) == 0;
            });

            Format   format     = attrs[i].format;
            uint64_t realOffset = 0;
            if (iter != _inputState.attributes.end()) {
                realOffset = offset;
                format     = (*iter).format;
            }

            WGPUVertexAttribute attr = {
                .format         = toWGPUVertexFormat(format),
                .offset         = realOffset,
                .shaderLocation = attrs[i].location,
            };
            wgpuAttrs.push_back(attr);
            if (iter != _inputState.attributes.end())
                offset += GFX_FORMAT_INFOS[static_cast<uint>(format)].size;
        }

        WGPUVertexBufferLayout vertexBufferLayout = {
            .arrayStride    = offset,
            .stepMode       = isInstance ? WGPUInputStepMode_Instance : WGPUInputStepMode_Vertex,
            .attributeCount = wgpuAttrs.size(),
            .attributes     = wgpuAttrs.data(),
        };

        WGPUVertexState vertexState = {
            .nextInChain = nullptr,
            .module      = static_cast<CCWGPUShader*>(_shader)->gpuShaderObject()->wgpuShaderVertexModule,
            .entryPoint  = "main",
            .bufferCount = 1,
            .buffers     = &vertexBufferLayout,
        };

        bool stripTopology = (_primitive == PrimitiveMode::LINE_STRIP || _primitive == PrimitiveMode::TRIANGLE_STRIP);

        WGPUPrimitiveState primitiveState = {
            .nextInChain      = nullptr,
            .topology         = toWGPUPrimTopology(_primitive),
            .stripIndexFormat = WGPUIndexFormat_Undefined, //TODO_Zeqiang: ???
            .frontFace        = _rasterizerState.isFrontFaceCCW ? WGPUFrontFace::WGPUFrontFace_CCW : WGPUFrontFace::WGPUFrontFace_CW,
            .cullMode         = _rasterizerState.cullMode == CullMode::FRONT ? WGPUCullMode::WGPUCullMode_Front
                                                                     : _rasterizerState.cullMode == CullMode::BACK ? WGPUCullMode::WGPUCullMode_Back
                                                                                                                   : WGPUCullMode::WGPUCullMode_None,
        };

        WGPUStencilFaceState stencilFront = {
            .compare     = toWGPUCompareFunction(_depthStencilState.stencilFuncFront),
            .failOp      = toWGPUStencilOperation(_depthStencilState.stencilFailOpFront),
            .depthFailOp = toWGPUStencilOperation(_depthStencilState.stencilZFailOpFront),
            .passOp      = toWGPUStencilOperation(_depthStencilState.stencilPassOpFront),
        };

        WGPUStencilFaceState stencilBack = {
            .compare     = toWGPUCompareFunction(_depthStencilState.stencilFuncBack),
            .failOp      = toWGPUStencilOperation(_depthStencilState.stencilFailOpBack),
            .depthFailOp = toWGPUStencilOperation(_depthStencilState.stencilZFailOpBack),
            .passOp      = toWGPUStencilOperation(_depthStencilState.stencilPassOpBack),
        };

        WGPUDepthStencilState dsState = {
            .nextInChain         = nullptr,
            .format              = toWGPUTextureFormat(dsAttachment.format),
            .depthWriteEnabled   = _depthStencilState.depthWrite != 0,
            .depthCompare        = toWGPUCompareFunction(_depthStencilState.depthFunc),
            .stencilFront        = stencilFront,
            .stencilBack         = stencilBack,
            .stencilReadMask     = _depthStencilState.stencilReadMaskFront,
            .stencilWriteMask    = _depthStencilState.stencilWriteMaskFront,
            .depthBias           = static_cast<int32_t>(_rasterizerState.depthBias),
            .depthBiasSlopeScale = _rasterizerState.depthBiasSlop,
            .depthBiasClamp      = _rasterizerState.depthBiasClamp,
        };

        WGPUMultisampleState msState = {
            .count                  = static_cast<CCWGPURenderPass*>(_renderPass)->gpuRenderPassObject()->sampleCount,
            .mask                   = 0xFFFFFFFF,
            .alphaToCoverageEnabled = _blendState.isA2C != 0,
        };

        const ColorAttachmentList&        colors = _renderPass->getColorAttachments();
        std::vector<WGPUColorTargetState> colorTargetStates(colors.size());

        std::vector<WGPUBlendState> blendState(colors.size());

        for (size_t i = 0; i < colors.size(); i++) {
            colorTargetStates[i].format = toWGPUTextureFormat(colors[i].format);
            blendState[i]
                .color = {
                .operation = toWGPUBlendOperation(_blendState.targets[i].blendAlphaEq),
                .srcFactor = toWGPUBlendFactor(_blendState.targets[i].blendSrc),
                .dstFactor = toWGPUBlendFactor(_blendState.targets[i].blendDst),
            };
            blendState[i].alpha = {
                .operation = toWGPUBlendOperation(_blendState.targets[i].blendAlphaEq),
                .srcFactor = toWGPUBlendFactor(_blendState.targets[i].blendSrc),
                .dstFactor = toWGPUBlendFactor(_blendState.targets[i].blendDst),
            };
            colorTargetStates[i].blend     = &blendState[i];
            colorTargetStates[i].writeMask = toWGPUColorWriteMask(_blendState.targets[i].blendColorMask);
        }

        WGPUFragmentState fragmentState = {
            .module      = static_cast<CCWGPUShader*>(_shader)->gpuShaderObject()->wgpuShaderFragmentModule,
            .entryPoint  = "main",
            .targetCount = colorTargetStates.size(),
            .targets     = colorTargetStates.data(),
        };

        pipelineLayout->prepare(setInUse);
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
        _gpuPipelineStateObj->wgpuRenderPipeline = wgpuDeviceCreateRenderPipeline2(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &piplineDesc);
    } else if (_bindPoint == PipelineBindPoint::COMPUTE) {
        if (_gpuPipelineStateObj->wgpuComputePipeline)
            return;
        WGPUProgrammableStageDescriptor psDesc = {
            .module     = static_cast<CCWGPUShader*>(_shader)->gpuShaderObject()->wgpuShaderComputeModule,
            .entryPoint = "main",
        };
        pipelineLayout->prepare(setInUse);
        WGPUComputePipelineDescriptor piplineDesc = {
            .layout       = pipelineLayout->gpuPipelineLayoutObject()->wgpuPipelineLayout,
            .computeStage = psDesc,
        };
        _gpuPipelineStateObj->wgpuComputePipeline = wgpuDeviceCreateComputePipeline(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &piplineDesc);
        printf("ppshn: %s\n", static_cast<CCWGPUShader*>(_shader)->gpuShaderObject()->name.c_str());
    } else {
        CC_LOG_ERROR("unsupport pipeline bind point");
    }
}

void CCWGPUPipelineState::doDestroy() {
    printf("pso des %p\n", this);
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