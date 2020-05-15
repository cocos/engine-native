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
#include "scripting/js-bindings/jswrapper/SeApi.h"

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
        _cfg->updateFlags |= UPDATE_EFFECT;
    }

    void LabelRenderer::bindSharedBlock(se::Object * selfObj, void *cfg, void *layout)
    {
        _selfObj = selfObj;
        _cfg = static_cast<decltype(_cfg)>(cfg);
        _layoutInfo = static_cast<decltype(_layoutInfo)>(layout);
    }


    void LabelRenderer::genStringLayout()
    {
        std::string fontPath = getFontPath();
        std::string text = getString();
        if (!fontPath.empty() && !text.empty() && !_stringLayout)
        {
            _stringLayout.reset(new LabelLayout());
            _stringLayout->init(fontPath, text, _cfg->fontSize, _cfg->fontSizeRetina, _layoutInfo);
        }
    }

    void LabelRenderer::render()
    {
        std::string text = getString();
        std::string fontPath = getFontPath();
        if (!_effect || text.empty() || fontPath.empty()) return;

        genStringLayout();

        renderIfChange();

    }

    void LabelRenderer::renderIfChange()
    {
        if (!_stringLayout) return;

        if (_cfg->updateFlags & UPDATE_FONT || _cfg->updateFlags & UPDATE_EFFECT)
        {
            // update font & string
            _stringLayout.reset();
            genStringLayout();

            doRender();            
        }
        else if (_cfg->updateFlags & UPDATE_CONTENT)
        {
            std::string text = getString();            // update content only
            if (_stringLayout->isInited())
            {
                _stringLayout->setString(text, true);
                doRender();
            }
        }

        _cfg->updateFlags = 0;
    }

    void LabelRenderer::doRender()
    {
        if (_stringLayout && _effect && _nodeProxy && _nodeProxy->getAssembler())
        {
            auto *assembler = (CustomAssembler*)_nodeProxy->getAssembler();
            _stringLayout->fillAssembler(assembler, _effect);
        }
    }

    std::string LabelRenderer::getString() {
        se::Value str;
        assert(_selfObj);
        _selfObj->getProperty("string", &str);
        return str.toString();
    }

    std::string LabelRenderer::getFontPath() {
        se::Value str;
        assert(_selfObj);
        _selfObj->getProperty("fontPath", &str);
        return str.toString();
    }
}
#endif
