/****************************************************************************
Copyright (c) 2020 Xiamen Yaji Software Co., Ltd.

http://www.cocos.com

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
#include "cocos/2d/CCTTFLabelRenderer.h"

#include "MiddlewareMacro.h"
#include "renderer/renderer/Pass.h"
#include "renderer/renderer/Technique.h"
#include "renderer/scene/RenderFlow.hpp"
#include "renderer/scene/assembler/CustomAssembler.hpp"
#include "cocos/editor-support/IOBuffer.h"
#include "cocos/editor-support/middleware-adapter.h"
#include "cocos/editor-support/MiddlewareManager.h"
#include "cocos/platform/CCApplication.h"
#include "cocos/platform/CCFileUtils.h"


#include "CCLabelLayout.h"
#include "base/ccConfig.h"
#if CC_ENABLE_TTF_LABEL_RENDERER

USING_NS_CC;
USING_NS_MW;
using namespace renderer;

namespace cocos2d {

    LabelRenderer::LabelRenderer()
    {
    }

    LabelRenderer::~LabelRenderer()
    {
        CC_SAFE_RELEASE(_effect);
    }


    void LabelRenderer::bindNodeProxy(cocos2d::renderer::NodeProxy* node) {
        if (node == _nodeProxy) return;
        CC_SAFE_RELEASE(_nodeProxy);
        _nodeProxy = node;
        CC_SAFE_RETAIN(_nodeProxy);
    }
    
    void LabelRenderer::setEffect(cocos2d::renderer::EffectVariant* arg) {
        if (_effect == arg) return;

        CC_SAFE_RELEASE(_effect);
        _effect = arg;
        CC_SAFE_RETAIN(arg);
        _updateFlags |= UPDATE_EFFECT;
    }
    
    void LabelRenderer::setString(const std::string &str)
    {
        if (str == _string || str.empty()) return;
        _string = str;
        _updateFlags |= UPDATE_CONTENT;
    }

    void LabelRenderer::setFontPath(const std::string &path)
    {
        if (path == _fontPath || path.empty()) return;

        _fontPath = path;
        _updateFlags |= UPDATE_FONT;
    }


    void LabelRenderer::setFontSize(float fontSize, float fontSizeRetina)
    {
        if (fontSize == _fontSize) return;
        _fontSize = fontSize;
        _fontSizeRetina = fontSizeRetina;

        _updateFlags |= UPDATE_FONT;
    }


    void LabelRenderer::setOutline(float outline)
    {
        if ((_layoutInfo.outlineSize > 0) != (outline > 0))
        {
            _updateFlags |= UPDATE_FONT;
        }
        if (_layoutInfo.outlineSize != outline)
        {
            _updateFlags |= UPDATE_CONTENT;
        }
        _layoutInfo.outlineSize = outline;
    }

    void LabelRenderer::setOutlineColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        _layoutInfo.outlineColor = Color4B(r, g, b, a);
        _updateFlags |= UPDATE_CONTENT;
    }

    void LabelRenderer::setLineHeight(float lineHeight)
    {
        _layoutInfo.lineHeight = lineHeight;
        _updateFlags |= UPDATE_CONTENT;
    }

    void LabelRenderer::setOverFlow(int overflow)
    {
        _layoutInfo.overflow = static_cast<LabelOverflow>(overflow);
        _updateFlags |= UPDATE_CONTENT;
    }

    void LabelRenderer::setEnableWrap(bool wrap)
    {
        _layoutInfo.wrap= wrap;
        _updateFlags |= UPDATE_CONTENT;
    }

    void LabelRenderer::setVerticalAlign(int vAlign)
    {
        _layoutInfo.valign= static_cast<LabelAlignmentV>(vAlign);
        _updateFlags |= UPDATE_CONTENT;
    }

    void LabelRenderer::setHorizontalAlign(int hAlign)
    {
        _layoutInfo.halign = static_cast<LabelAlignmentH>(hAlign);
        _updateFlags |= UPDATE_CONTENT;
    }


    void LabelRenderer::setContentSize(float width, float height)
    {
        _layoutInfo.width = width;
        _layoutInfo.height = height;
        _updateFlags |= UPDATE_CONTENT;
    }


    void LabelRenderer::setAnchorPoint(float x, float y)
    {
        _layoutInfo.anchorX = x;
        _layoutInfo.anchorY = y;
        _updateFlags |= UPDATE_CONTENT;
    }

    void LabelRenderer::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        _layoutInfo.color = Color4B(r, g, b, a);
        _updateFlags |= UPDATE_CONTENT;
    }

    void LabelRenderer::setShadow(float x, float y, int blur)
    {
        if((_layoutInfo.shadowBlur > 0) != (blur > 0)) 
        {
            _updateFlags |= UPDATE_FONT;
        }

        _layoutInfo.shadowX = x;
        _layoutInfo.shadowY = y;
        _layoutInfo.shadowBlur = blur;
        _updateFlags |= UPDATE_CONTENT;
    }

    void LabelRenderer::setShadowColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        _layoutInfo.shadowColor = Color4B(r, g, b, a);
        _updateFlags |= UPDATE_CONTENT;
    }

    void LabelRenderer::setItalic(bool italic)
    {
        if (_layoutInfo.italic != italic)
        {
            _updateFlags |= UPDATE_CONTENT;
        }
        _layoutInfo.italic = italic;
    }

    void LabelRenderer::setBold(bool bold)
    {
        if (_layoutInfo.bold != bold)
        {
            _updateFlags |= UPDATE_FONT;
        }
        _layoutInfo.bold = bold;
    }

    void LabelRenderer::setUnderline(bool underline)
    {
        if (_layoutInfo.underline != underline)
        {
            _updateFlags |= UPDATE_CONTENT;
        }
        _layoutInfo.underline = underline;
    }


    void LabelRenderer::genStringLayout()
    {
        if (!_fontPath.empty() && !_string.empty() && !_stringLayout)
        {
            _stringLayout = std::make_shared<LabelLayout>();
            _stringLayout->init(_fontPath, _string, _fontSize, _fontSizeRetina, &_layoutInfo);
        }
    }

    void LabelRenderer::render()
    {
        if (!_effect || _string.empty() || _fontPath.empty()) return;

        genStringLayout();

        renderIfChange();

    }

    void LabelRenderer::renderIfChange()
    {
        if (!_stringLayout) return;

        if (_updateFlags & UPDATE_FONT || _updateFlags & UPDATE_EFFECT)
        {
            // update font & string
            _stringLayout.reset();
            genStringLayout();

            doRender();            
        }
        else if (_updateFlags & UPDATE_CONTENT)
        {
            // update content only
            if (_stringLayout->isInited())
            {
                _stringLayout->setString(_string, true);
                doRender();
            }
        }

        _updateFlags = 0;
    }

    void LabelRenderer::doRender()
    {
        if (_stringLayout && _effect && _nodeProxy && _nodeProxy->getAssembler())
        {
            auto *assembler = (CustomAssembler*)_nodeProxy->getAssembler();
            _stringLayout->fillAssembler(assembler, _effect);
        }
    }
}
#endif