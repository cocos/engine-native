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

#pragma once

#include <vector>
#include <unordered_map>
#include <map>
#include "base/CCRef.h"
#include "base/CCValue.h"
#include "../Macro.h"
#include "Technique.h"
#include "Pass.h"

RENDERER_BEGIN

class EffectBase : public Ref
{
public:
    using Property = Technique::Parameter;
    
    /*
     * @brief The default constructor.
     */
    EffectBase();
    /*
     *  @brief The default destructor.
     */
    virtual ~EffectBase();
    
    virtual Vector<Pass*>& getPasses() = 0;
    virtual const Vector<Pass*>& getPasses() const = 0;
 
    /**
     *  @brief Gets define property value by name.
     */
    const Value* getDefine(const std::string& name, int passIdx = -1) const;
    /**
     *  @brief Sets a define's value.
     */
    void define(const std::string& name, const Value& value, int passIdx = -1);
    /**
     *  @brief Gets uniform property value by name.
     */
    const Property* getProperty(const std::string& name, int passIdx = -1) const;
    /**
     *  @brief Sets uniform property value by name.
     */
    void setProperty(const std::string& name, const Property& property, int passIdx = -1);
    void setProperty(const std::string& name, void* value, int passIdx = -1);
    /**
     *  @brief Sets cull mode.
     *  @param[in] cullMode Cull front or back or both.
     */
    void setCullMode(CullMode cullMode, int passIdx = -1);
    /**
     *  @brief Sets blend mode.
     *  @param[in] blendEq RGB blend equation.
     *  @param[in] blendSrc Src RGB blend factor.
     *  @param[in] blendDst Dst RGB blend factor.
     *  @param[in] blendAlphaEq Alpha blend equation.
     *  @param[in] blendSrcAlpha Src Alpha blend equation.
     *  @param[in] blendDstAlpha Dst Alpha blend equation.
     *  @param[in] blendColor Blend constant color value.
     */
    void setBlend(
        bool blendTest = false,
        BlendOp blendEq = BlendOp::ADD,
        BlendFactor blendSrc = BlendFactor::ONE,
        BlendFactor blendDst = BlendFactor::ZERO,
        BlendOp blendAlphaEq = BlendOp::ADD,
        BlendFactor blendSrcAlpha = BlendFactor::ONE,
        BlendFactor blendDstAlpha = BlendFactor::ZERO,
        uint32_t blendColor = 0xffffffff,
        int passIdx = -1
    );
    /**
     *  @brief Sets stencil front-facing function, reference, mask, fail operation, write mask.
     */
    void setStencil(
        StencilFunc stencilFunc = StencilFunc::ALWAYS,
        uint32_t stencilRef = 0,
        uint8_t stencilMask = 0xff,
        StencilOp stencilFailOp = StencilOp::KEEP,
        StencilOp stencilZFailOp = StencilOp::KEEP,
        StencilOp stencilZPassOp = StencilOp::KEEP,
        uint8_t stencilWriteMask = 0xff,
        int passIdx = -1
    );
    /*
     *  @brief Sets stencil test enabled or not.
     */
    void setStencilTest(bool value, int passIdx = -1);
    
    void setDepth(
        bool depthTest = false,
        bool depthWrite = false,
        DepthFunc depthFunc = DepthFunc::LESS,
        int passIdx = -1
    );
protected:
    bool _dirty = true;
};

RENDERER_END
