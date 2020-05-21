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

#include "Pass.h"
#include "math/MathUtil.h"
#include "Texture2D.h"

RENDERER_BEGIN

uint32_t* Pass::DEFAULT_STATES = new uint32_t[PASS_VALUE_LENGTH] {
    // cull
    (uint32_t)GL_BACK,                              // 0 cullMode
    
    // blend
    (uint32_t)false,                                 // 1 blend
    (uint32_t)BlendOp::ADD,                         // 2 blendEq
    (uint32_t)BlendFactor::SRC_ALPHA,               // 3 blendSrc
    (uint32_t)BlendFactor::ONE_MINUS_SRC_ALPHA,     // 4 blendDst
    (uint32_t)BlendOp::ADD,                         // 5 blendAlphaEq
    (uint32_t)BlendFactor::SRC_ALPHA,               // 6 blendSrcAlpha
    (uint32_t)BlendFactor::ONE_MINUS_SRC_ALPHA,     // 7 blendDstAlpha
    (uint32_t)0xffffffff,                           // 8 blendColor
    
    // depth
    (uint32_t)false,                                // 9  depthTest
    (uint32_t)false,                                // 10 depthWrite
    (uint32_t)DepthFunc::LESS,                      // 11 depthFunc
    
    // stencil
    (uint32_t)2,                                    // 12 stencilTest inherit
    // stencil front
    (uint32_t)StencilFunc::ALWAYS,                  // 13 stencilFuncFront
    (uint32_t)0,                                    // 14 stencilRefFront
    (uint32_t)0xff,                                 // 15 stencilMaskFront
    (uint32_t)StencilOp::KEEP,                      // 16 stencilFailOpFront
    (uint32_t)StencilOp::KEEP,                      // 17 stencilZFailOpFront
    (uint32_t)StencilOp::KEEP,                      // 18 stencilZPassOpFront
    (uint32_t)0xff,                                 // 19 stencilWriteMaskFront
    
    // stencil back
    (uint32_t)StencilFunc::ALWAYS,                  // 20 stencilFuncBack
    (uint32_t)0,                                    // 21 stencilRefBack
    (uint32_t)0xff,                                 // 22 stencilMaskBack
    (uint32_t)StencilOp::KEEP,                      // 23 stencilFailOpBack
    (uint32_t)StencilOp::KEEP,                      // 24 stencilZFailOpBack
    (uint32_t)StencilOp::KEEP,                      // 25 stencilZPassOpBack
    (uint32_t)0xff,                                 // 26 stencilWriteMaskBack
    
};


Pass::Pass(const std::string& programName, Pass* parent)
: _programName(programName),
  _parent(parent)
{
    _hashName = std::hash<std::string>{}(programName);
    reset();
}

Pass::Pass(
    const std::string& programName,
    std::unordered_map<size_t, Technique::Parameter>& properties,
    ValueMap& defines
): _programName(programName)
{
    _hashName = std::hash<std::string>{}(programName);
    _properties = properties;
    _defines.insert(defines.begin(), defines.end());
    generateDefinesKey();
    reset();
}

Pass::~Pass()
{
}

void Pass::generateDefinesKey()
{
    std::string key = "";
    for (auto& def : _defines) {
        key += def.first + std::to_string(def.second.asUnsignedInt());
    }

    _definesHash = 0;
    MathUtil::combineHash(_definesHash, std::hash<std::string>{}(key));
}

void Pass::extractDefines(size_t& hash, std::vector<const OrderedValueMap*>& defines) const
{
    if (_parent) {
        _parent->extractDefines(hash, defines);
    }
    
    MathUtil::combineHash(hash, _definesHash);
    defines.push_back(&_defines);
}

void Pass::setCullMode(CullMode cullMode)
{
    _states[0] = (uint32_t)cullMode;
}

void Pass::setBlend(bool blendTest,
                    BlendOp blendEq,
                    BlendFactor blendSrc,
                    BlendFactor blendDst,
                    BlendOp blendAlphaEq,
                    BlendFactor blendSrcAlpha,
                    BlendFactor blendDstAlpha,
                    uint32_t blendColor)
{
    _states[1] = (uint32_t)blendTest;
    _states[2] = (uint32_t)blendEq;
    _states[3] = (uint32_t)blendSrc;
    _states[4] = (uint32_t)blendDst;
    _states[5] = (uint32_t)blendAlphaEq;
    _states[6] = (uint32_t)blendSrcAlpha;
    _states[7] = (uint32_t)blendDstAlpha;
    _states[8] = (uint32_t)blendColor;
}

void Pass::setDepth(bool depthTest, bool depthWrite, DepthFunc depthFunc)
{
    _states[9] = (uint32_t)depthTest;
    _states[10] = (uint32_t)depthWrite;
    _states[11] = (uint32_t)depthFunc;
}

void Pass::setStencilFront(StencilFunc stencilFunc,
                           uint32_t stencilRef,
                           uint8_t stencilMask,
                           StencilOp stencilFailOp,
                           StencilOp stencilZFailOp,
                           StencilOp stencilZPassOp,
                           uint8_t stencilWriteMask)
{
    _states[12] = true;
    _states[13] = (uint32_t)stencilFunc;
    _states[14] = (uint32_t)stencilRef;
    _states[15] = (uint32_t)stencilMask;
    _states[16] = (uint32_t)stencilFailOp;
    _states[17] = (uint32_t)stencilZFailOp;
    _states[18] = (uint32_t)stencilZPassOp;
    _states[19] = (uint32_t)stencilWriteMask;
}

void Pass::setStencilBack(StencilFunc stencilFunc,
                          uint32_t stencilRef,
                          uint8_t stencilMask,
                          StencilOp stencilFailOp,
                          StencilOp stencilZFailOp,
                          StencilOp stencilZPassOp,
                          uint8_t stencilWriteMask)
{
    _states[12] = true;
    _states[20] = (uint32_t)stencilFunc;
    _states[21] = (uint32_t)stencilRef;
    _states[22] = (uint32_t)stencilMask;
    _states[23] = (uint32_t)stencilFailOp;
    _states[24] = (uint32_t)stencilZFailOp;
    _states[25] = (uint32_t)stencilZPassOp;
    _states[26] = (uint32_t)stencilWriteMask;
}

uint32_t Pass::getState(uint32_t index) const {
    const Pass* parent = this;
    while (parent) {
        if (parent->_states[index] != (uint32_t)-1) {
            return parent->_states[index];
        }
        parent = parent->_parent;
    }
    
    return DEFAULT_STATES[index];
}

const std::string& Pass::getStage() const {
    const Pass* parent = this;
    while (parent) {
        if (parent->_stage != "") {
            return parent->_stage;
        }
        parent = parent->_parent;
    }
    
    return _stage;
}

void Pass::copy(const Pass& pass)
{
    _programName = pass._programName;
    _hashName = pass._hashName;
    _parent = pass._parent;
    
    _stage = pass._stage;
    
    _defines = pass._defines;
    _properties = pass._properties;
    _definesHash = pass._definesHash;
    
    memcpy(_states, pass._states, PASS_VALUE_LENGTH * sizeof(uint32_t));
}

const Technique::Parameter* Pass::getProperty(const std::string& name) const
{
    return getProperty(std::hash<std::string>{}(name));
}

const Technique::Parameter* Pass::getProperty(const size_t hashName) const
{
    const auto& iter = _properties.find(hashName);
    if (_properties.end() == iter) {
        if (_parent) {
            return _parent->getProperty(hashName);
        }
        return nullptr;
    }
    else
        return &iter->second;
}

const Value* Pass::getDefine(const std::string& name) const
{
    const auto& iter = _defines.find(name);
    if (_defines.end() == iter) {
        if (_parent) {
            return _parent->getDefine(name);
        }
        return nullptr;
    }
    else
        return &iter->second;
}

void Pass::setProperty(size_t hashName, const Technique::Parameter& property)
{
    _properties[hashName] = property;
}

void Pass::setProperty(size_t hashName, void* value)
{
    Technique::Parameter* prop = nullptr;
    const auto& iter = _properties.find(hashName);
    if (_properties.end() == iter)
    {
        if (!_parent) return;
        auto parentProp = _parent->getProperty(hashName);
        if (!parentProp) return;
        prop = &_properties[hashName];
        *prop = *parentProp;
    }
    else
    {
        prop = &iter->second;
    }
    
    prop->setValue(value);
    
    if (prop->getType() == Technique::Parameter::Type::TEXTURE_2D) {
        if (prop->getTexture()) {
            bool isAlphaAtlas = prop->getTexture()->isAlphaAtlas();
            auto key = "CC_USE_ALPHA_ATLAS_" + prop->getName();
            auto def = getDefine(key);
            if (isAlphaAtlas || def) {
                define(key, Value(isAlphaAtlas));
            }
        }
    }
}

void Pass::setProperty(const std::string& name, const Technique::Parameter& property)
{
    setProperty(std::hash<std::string>{}(name), property);
}

void Pass::setProperty(const std::string& name, void* value)
{
    setProperty(std::hash<std::string>{}(name), value);
}

void Pass::define(const std::string& name, const Value& value)
{
    if (_defines[name] == value)
    {
        return;
    };

    _defines[name] = value;
    
    generateDefinesKey();
}

RENDERER_END
