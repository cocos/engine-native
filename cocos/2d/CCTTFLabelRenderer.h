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
#pragma once


#include "base/ccMacros.h"

#include "2d/CCTTFTypes.h"

#include "base/ccConfig.h"

#if CC_ENABLE_TTF_LABEL_RENDERER

namespace cocos2d {

    namespace renderer {
        class Texture2D;
        class Effect;
        class EffectVariant;
        class NodeProxy;
    }
    class LabelLayout;

    class LabelRenderer : public cocos2d::Ref {

    private:
        enum UpdateFlags {
            UPDATE_CONTENT = 1,
            UPDATE_FONT = 2,
            UPDATE_EFFECT = 3
        };

    public:


        LabelRenderer();

        virtual ~LabelRenderer();

        void bindNodeProxy(cocos2d::renderer::NodeProxy* node);

        void setEffect(cocos2d::renderer::EffectVariant* effect);

        void render();
 
        void setString(const std::string &str);

        void setFontPath(const std::string &path);

        void setFontSize(float fontSize, float fontSizeRetina = 0.0f);

        void setOutline(float outline);

        void setOutlineColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        void setLineHeight(float lineHeight);

        void setOverFlow(int overflow);

        void setEnableWrap(bool wrap);

        void setVerticalAlign(int vAlign);

        void setHorizontalAlign(int hAlign);

        void setContentSize(float width, float height);

        void setAnchorPoint(float x, float y);

        void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        void setShadow(float x, float y, int blur);

        void setShadowColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        void setItalic(bool);

        void setBold(bool);

        void setUnderline(bool);

    private:

        void genStringLayout();

        void renderIfChange();
        void doRender();

        std::shared_ptr<LabelLayout> _stringLayout = nullptr;

        uint32_t _updateFlags = 0xFFFFFFFF;

        std::string _string;
        std::string _fontPath;
        float _fontSize = 20.0f;
        float _fontSizeRetina = 0.0f;
        
        LabelLayoutInfo _layoutInfo;

        cocos2d::renderer::NodeProxy* _nodeProxy = nullptr;
        cocos2d::renderer::EffectVariant * _effect = nullptr;

    };
}

#endif