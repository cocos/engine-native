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

#include "ValidationUtils.h"

#include "bindings/jswrapper/SeApi.h"
#include "gfx-base/GFXInputAssembler.h"
#include "gfx-base/GFXPipelineState.h"
#include "gfx-base/GFXRenderPass.h"

namespace cc {

namespace utils {

String getStacktraceJS() {
    return se::ScriptEngine::getInstance()->getCurrentStackTrace();
}

} // namespace utils

namespace gfx {

void CommandRecorder::recordBeginRenderPass(const RenderPassSnapshot &renderPass) {
    RenderPassCommand command;
    command.renderArea   = renderPass.renderArea;
    command.clearColors  = renderPass.clearColors;
    command.clearDepth   = renderPass.clearDepth;
    command.clearStencil = renderPass.clearStencil;

    command.colorAttachments       = renderPass.renderPass->getColorAttachments();
    command.depthStencilAttachment = renderPass.renderPass->getDepthStencilAttachment();

    _commands.push_back(CommandType::BEGIN_RENDER_PASS);
    _renderPassCommands.emplace_back(std::move(command));
}

void CommandRecorder::recordDrawcall(const DrawcallSnapshot &drawcall) {
    DrawcallCommand command;
    command.inputState        = drawcall.pipelineState->getInputState();
    command.rasterizerState   = drawcall.pipelineState->getRasterizerState();
    command.depthStencilState = drawcall.pipelineState->getDepthStencilState();
    command.blendState        = drawcall.pipelineState->getBlendState();
    command.primitive         = drawcall.pipelineState->getPrimitive();
    command.dynamicStates     = drawcall.pipelineState->getDynamicStates();
    command.bindPoint         = drawcall.pipelineState->getBindPoint();

    drawcall.inputAssembler->extractDrawInfo(command.drawInfo);

    command.descriptorSets = drawcall.descriptorSets;
    for (const auto &offsets : drawcall.dynamicOffsets) command.dynamicOffsets.insert(command.dynamicOffsets.end(), offsets.begin(), offsets.end());

    _commands.push_back(CommandType::DRAW);
    _drawcallCommands.emplace_back(std::move(command));
}

void CommandRecorder::recordEndRenderPass() {
    _commands.push_back(CommandType::END_RENDER_PASS);
}

void CommandRecorder::clear() {
    _commands.clear();
    _renderPassCommands.clear();
    _drawcallCommands.clear();
}

void CommandRecorder::serialize(const String &path) {
}

void CommandRecorder::deserialize(const String &path) {
}

bool CommandRecorder::compare(const CommandRecorder &/*recorder*/) {
    return true;
}

} // namespace gfx
} // namespace cc
