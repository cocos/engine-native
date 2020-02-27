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

#include <string>
#include <base/CCRef.h>
#include "../Macro.h"
#include "../Types.h"
#include "Technique.h"

RENDERER_BEGIN

/**
 * @addtogroup renderer
 * @{
 */

/**
 * @brief Pass describes base render pass configurations, including program, cull face, blending, depth testing and stencil testing configs.\n
 * JS API: renderer.Pass
 * @code
 * let pass = new renderer.Pass('sprite');
 * pass.setDepth(false, false);
 * pass.setCullMode(gfx.CULL_NONE);
 * pass.setBlend(
 *     gfx.BLEND_FUNC_ADD,
 *     gfx.BLEND_SRC_ALPHA, gfx.BLEND_ONE_MINUS_SRC_ALPHA,
 *     gfx.BLEND_FUNC_ADD,
 *     gfx.BLEND_SRC_ALPHA, gfx.BLEND_ONE_MINUS_SRC_ALPHA
 * );
 * @endcode
 */
class Pass : public Ref
{
public:

    Pass(const std::string& programName, Pass* parent = nullptr);
    Pass(const std::string& programName,
         std::unordered_map<size_t, Technique::Parameter>& properties,
         ValueMap& defines
    );
    Pass() {};
    ~Pass();
    
    inline void setProgramName(const std::string& programName) { _programName = programName; }
    inline const std::string& getProgramName() const { return _programName; }
    
    inline size_t getHashName() const { return _hashName; }
    
    void copy(const Pass& pass);
    
    // cull mode
    CullMode getCullMode() const { return (CullMode)getState(0); }
    
    void setCullMode(CullMode cullMode);
    
    // blending
    inline bool isBlend () const { return getState(1); };
    inline BlendOp getBlendEq () const { return (BlendOp)getState(2); };
    inline BlendFactor getBlendSrc () const { return (BlendFactor)getState(3); };
    inline BlendFactor getBlendDst () const { return (BlendFactor)getState(4); };
    inline BlendOp getBlendAlphaEq () const { return (BlendOp)getState(5); };
    inline BlendFactor getBlendSrcAlpha () const { return (BlendFactor)getState(6); };
    inline BlendFactor getBlendDstAlpha () const { return (BlendFactor)getState(7); };
    inline uint32_t getBlendColor () const { return getState(8); };
    
    void setBlend(bool blendTest = false,
                  BlendOp blendEq = BlendOp::ADD,
                  BlendFactor blendSrc = BlendFactor::ONE,
                  BlendFactor blendDst = BlendFactor::ZERO,
                  BlendOp blendAlphaEq = BlendOp::ADD,
                  BlendFactor blendSrcAlpha = BlendFactor::ONE,
                  BlendFactor blendDstAlpha = BlendFactor::ZERO,
                  uint32_t blendColor = 0xffffffff);
    
    // depth
    inline bool isDepthTest () const { return getState(9); };
    inline bool isDepthWrite () const { return getState(10); };
    inline DepthFunc getDepthFunc () const { return (DepthFunc)getState(11); };
    
    void setDepth(bool depthTest = false,
                  bool depthWrite = false,
                  DepthFunc depthFunc = DepthFunc::LESS);
    
    // stencil
    inline void setStencilTest(bool value)     { _states[12] = value; }
    inline void disableStencilTest()           { _states[12] = false; }
    inline bool isStencilTest()                const { return getState(12); }
    
    // stencil front
    inline StencilFunc getStencilFuncFront()     const { return (StencilFunc)getState(13); }
    inline uint32_t getStencilRefFront()         const { return getState(14); }
    inline uint8_t getStencilMaskFront()         const { return getState(15); }
    inline StencilOp getStencilFailOpFront()     const { return (StencilOp)getState(16); }
    inline StencilOp getStencilZFailOpFront()    const { return (StencilOp)getState(17); }
    inline StencilOp getStencilZPassOpFront()    const { return (StencilOp)getState(18); }
    inline uint8_t getStencilWriteMaskFront()    const { return getState(19); }
    
    void setStencilFront(StencilFunc stencilFunc = StencilFunc::ALWAYS,
                         uint32_t stencilRef = 0,
                         uint8_t stencilMask = 0xff,
                         StencilOp stencilFailOp = StencilOp::KEEP,
                         StencilOp stencilZFailOp = StencilOp::KEEP,
                         StencilOp stencilZPassOp = StencilOp::KEEP,
                         uint8_t stencilWriteMask = 0xff);
    
    // stencil back
    inline StencilFunc getStencilFuncBack()      const { return (StencilFunc)getState(20); }
    inline uint32_t getStencilRefBack()          const { return getState(21); }
    inline uint8_t getStencilMaskBack()          const { return getState(22); }
    inline StencilOp getStencilFailOpBack()      const { return (StencilOp)getState(23); }
    inline StencilOp getStencilZFailOpBack()     const { return (StencilOp)getState(24); }
    inline StencilOp getStencilZPassOpBack()     const { return (StencilOp)getState(25); }
    inline uint8_t getStencilWriteMaskBack()     const { return getState(26); }
    
    void setStencilBack(StencilFunc stencilFunc = StencilFunc::ALWAYS,
                        uint32_t stencilRef = 0,
                        uint8_t stencilMask = 0xff,
                        StencilOp stencilFailOp = StencilOp::KEEP,
                        StencilOp stencilZFailOp = StencilOp::KEEP,
                        StencilOp stencilZPassOp = StencilOp::KEEP,
                        uint8_t stencilWriteMask = 0xff);
    
    uint32_t getState(uint32_t index) const;
    
    // stage
    void setStage (const std::string& stage) { _stage = stage; }
    const std::string& getStage() const;
    
    inline void reset () { memset(_states, -1, PASS_VALUE_LENGTH * sizeof(uint32_t)); }
    
    inline void setParent(Pass* parent) { _parent = parent; }
    inline const Pass* getParent() { return _parent; }
    
    void extractDefines (size_t& hash, std::vector<const ValueMap*>& defines) const;
    
    void generateDefinesKey ();
    
    const Technique::Parameter* getProperty(const std::string& name) const;
    void setProperty(const std::string& name, const Technique::Parameter& property);
    void setProperty(const std::string& name, void* value);
    
    const Technique::Parameter* getProperty(size_t hashName) const;
    void setProperty(size_t hashName, const Technique::Parameter& property);
    void setProperty(size_t hashName, void* value);
    
    const Value* getDefine(const std::string& name) const;
    void define(const std::string& name, const Value& value);
private:
    std::string _programName = "";
    size_t _hashName = 0;
    
    Pass* _parent = nullptr;
    
    std::unordered_map<size_t, Technique::Parameter> _properties;
    ValueMap _defines;
    size_t _definesHash;
    
    static const int PASS_VALUE_LENGTH = 27;
    
    uint32_t _states[PASS_VALUE_LENGTH];
    static uint32_t* DEFAULT_STATES;
    
    std::string _stage = "";
};

// end of renderer group
/// @}
RENDERER_END
