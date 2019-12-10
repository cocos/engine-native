/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "EffectBase.h"
#include "Config.h"

RENDERER_BEGIN

EffectBase::EffectBase()
{}

EffectBase::~EffectBase()
{
}

const Value* EffectBase::getDefine(const std::string& name, int passIdx) const
{
    auto& passes = getPasses();
    size_t start = 0, end = passes.size();
    if (passIdx != -1) {
        if (passIdx >= passes.size()) {
            RENDERER_LOGD("EffectBase::getDefine error passIdx [%d]", passIdx);
            return nullptr;
        }
        start = passIdx; end = passIdx + 1;
    }
    for (size_t i = start; i < end; i++)
    {
        const auto& pass = passes.at(i);
        auto value = pass->getDefine(name);
        if (value) {
            return value;
        }
    }
    
    return nullptr;
}

void EffectBase::define(const std::string& name, const Value& value, int passIdx)
{
    auto& passes = getPasses();
    size_t start = 0, end = passes.size();
    if (passIdx != -1) {
        if (passIdx >= passes.size()) {
            RENDERER_LOGD("EffectBase::define error passIdx [%d]", passIdx);
            return;
        }
        start = passIdx; end = passIdx + 1;
    }
    for (size_t i = start; i < end; i++)
    {
        const auto& pass = passes.at(i);
        pass->define(name, value);
    }

    _dirty = true;
}

const EffectBase::Property* EffectBase::getProperty(const std::string& name, int passIdx) const
{
    auto& passes = getPasses();
    size_t start = 0, end = passes.size();
    if (passIdx != -1) {
        if (passIdx >= passes.size()) {
            RENDERER_LOGD("EffectBase::getProperty error passIdx [%d]", passIdx);
            return nullptr;
        }
        start = passIdx; end = passIdx + 1;
    }
    for (size_t i = start; i < end; i++)
    {
        const auto& pass = passes.at(i);
        auto value = pass->getProperty(name);
        if (value) {
            return value;
        }
    }
    
    return nullptr;
}

void EffectBase::setProperty(const std::string& name, const Property& property, int passIdx)
{
    auto& passes = getPasses();
    size_t start = 0, end = passes.size();
    if (passIdx != -1) {
        if (passIdx >= passes.size()) {
            RENDERER_LOGD("EffectBase::setProperty error passIdx [%d]", passIdx);
            return;
        }
        start = passIdx; end = passIdx + 1;
    }
    for (size_t i = start; i < end; i++)
    {
        const auto& pass = passes.at(i);
        pass->setProperty(name, property);
    }

    _dirty = true;
}

void EffectBase::setProperty(const std::string& name, void* value, int passIdx)
{
    auto& passes = getPasses();
    size_t start = 0, end = passes.size();
    if (passIdx != -1) {
        if (passIdx >= passes.size()) {
            RENDERER_LOGD("EffectBase::setProperty error passIdx [%d]", passIdx);
            return;
        }
        start = passIdx; end = passIdx + 1;
    }
    for (size_t i = start; i < end; i++)
    {
        const auto& pass = passes.at(i);
        pass->setProperty(name, value);
    }

    _dirty = true;
}

void EffectBase::setCullMode(CullMode cullMode, int passIdx)
{
    auto& passes = getPasses();
    size_t start = 0, end = passes.size();
    if (passIdx != -1) {
        if (passIdx >= passes.size()) {
            RENDERER_LOGD("EffectBase::setCullMode error passIdx [%d]", passIdx);
            return;
        }
        start = passIdx; end = passIdx + 1;
    }
    for (size_t i = start; i < end; i++)
    {
        const auto& pass = passes.at(i);
        pass->setCullMode(cullMode);
    }
}

void EffectBase::setBlend(bool blendTest, BlendOp blendEq, BlendFactor blendSrc, BlendFactor blendDst, BlendOp blendAlphaEq, BlendFactor blendSrcAlpha, BlendFactor blendDstAlpha, uint32_t blendColor, int passIdx)
{
    auto& passes = getPasses();
    size_t start = 0, end = passes.size();
    if (passIdx != -1) {
        if (passIdx >= passes.size()) {
            RENDERER_LOGD("EffectBase::setBlend error passIdx [%d]", passIdx);
            return;
        }
        start = passIdx; end = passIdx + 1;
    }
    for (size_t i = start; i < end; i++)
    {
        const auto& pass = passes.at(i);
        pass->setBlend(blendTest, blendEq, blendSrc, blendDst, blendAlphaEq, blendSrcAlpha, blendDstAlpha, blendColor);
    }
}

void EffectBase::setStencilTest(bool value, int passIdx)
{
    auto& passes = getPasses();
    size_t start = 0, end = passes.size();
    if (passIdx != -1) {
        if (passIdx >= passes.size()) {
            RENDERER_LOGD("EffectBase::setStencilTest error passIdx [%d]", passIdx);
            return;
        }
        start = passIdx; end = passIdx + 1;
    }
    for (size_t i = start; i < end; i++)
    {
        const auto& pass = passes.at(i);
        pass->setStencilTest(value);
    }
}

void EffectBase::setStencil(StencilFunc stencilFunc, uint32_t stencilRef, uint8_t stencilMask, StencilOp stencilFailOp, StencilOp stencilZFailOp, StencilOp stencilZPassOp, uint8_t stencilWriteMask, int passIdx)
{
    auto& passes = getPasses();
    size_t start = 0, end = passes.size();
    if (passIdx != -1) {
        if (passIdx >= passes.size()) {
            RENDERER_LOGD("EffectBase::setStencil error passIdx [%d]", passIdx);
            return;
        }
        start = passIdx; end = passIdx + 1;
    }
    for (size_t i = start; i < end; i++)
    {
        const auto& pass = passes.at(i);
        pass->setStencilFront(stencilFunc, stencilRef, stencilMask, stencilFailOp, stencilZFailOp, stencilZPassOp, stencilWriteMask);
        pass->setStencilBack(stencilFunc, stencilRef, stencilMask, stencilFailOp, stencilZFailOp, stencilZPassOp, stencilWriteMask);
    }
}

void EffectBase::setDepth(bool depthTest, bool depthWrite, DepthFunc depthFunc, int passIdx)
{
    auto& passes = getPasses();
    size_t start = 0, end = passes.size();
    if (passIdx != -1) {
        if (passIdx >= passes.size()) {
            RENDERER_LOGD("EffectBase::setDepth error passIdx [%d]", passIdx);
            return;
        }
        start = passIdx; end = passIdx + 1;
    }
    for (size_t i = start; i < end; i++)
    {
        const auto& pass = passes.at(i);
        pass->setDepth(depthTest, depthWrite, depthFunc);
    }
}

RENDERER_END
