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

#include <string>

#include "2d/CCTTFLabelAtlasCache.h"

#include "math/Vec3.h"
#include "math/Vec4.h"
#include "base/ccConfig.h"
#if CC_ENABLE_TTF_LABEL_RENDERER

namespace cocos2d {

    namespace renderer {
        class CustomAssembler;
        class Texture2D;
        class MeshBuffer;
        class Effect;
        class EffectVariant;
    }

    namespace middleware {
        class MeshBuffer;
    }

    class TextRenderGroup;
    class LabelRenderer;


    class TextRowSpace {
        /**
        *   Y
        *   ^
        *   |
        *   |
        *   +------> X
        */
    public:

        struct GlyphBlock {
            Rect area;
            Rect uv;
            int texId = 0;
            bool ignored = false;
        };

        TextRowSpace() = default;
        TextRowSpace(TextRowSpace &&other);

        void fillRect(int texId, Rect &rect, Rect &uv);
        void translate(float x, float y);
        Vec2 center() const;

        float getWidth() const { return  _data.size() > 0 ? _right - _left : 0; }
        float getHeight() const { return _data.size() > 0 ? _top - _bottom : 0; }
        
        float getExtentedWidth(float left, float right) const;

        Vec2 getOffset() const { return Vec2(_x, _y); }

        GlyphBlock & operator[] (size_t i);

        bool isIgnored() const { return _ignored; }

        bool isIgnored(int i) const { return _data[i].ignored; }

        void clip(const Rect &rec);

        size_t size() const { return _data.size(); }

        bool validate() const { return _data.size() > 0; }

        Rect asRect() const;

        float getLeft() const { return _left; }

        float getRight() const { return _right; }

        float getTop() const { return _top; }

        float getBottom() const { return _bottom; }

    private:
        void reset();

        GlyphBlock & appendBlock();

    private:

        float _left = FLT_MAX;
        float _bottom = FLT_MAX;
        float _right = FLT_MIN;
        float _top = FLT_MIN;
        float _x = 0.0f;
        float _y = 0.0f;
        std::vector<GlyphBlock>  _data;
        bool _ignored = false;
    };




    class LabelLayout {
    public:
        LabelLayout() = default;
        bool init(const std::string& font, const std::string& text, float fontSize, float retinaFontSize, LabelLayoutInfo *info);
        virtual ~LabelLayout();

        void setString(const std::string &txt, bool forceUpdate);

        bool isInited() const { return _inited; }

        void fillAssembler(renderer::CustomAssembler *assembeler, renderer::EffectVariant *effect);

    private:

        bool updateContent();

    private:
        std::string _string;
        std::u32string _u32string;
        std::string _font;
        float         _fontSize = 0.0f;
        float         _retinaFontSize = 0.0f;
        float      _fontScale = 1.0f;
        float       _scale = 1.0f;

        //weak reference
        LabelLayoutInfo *_layoutInfo = nullptr;

        std::shared_ptr<TTFLabelAtals> _fontAtlas;

        bool        _enableKerning = true;
        bool        _inited = false;

        std::vector<TextRowSpace> _textSpace;

        std::shared_ptr<TextRenderGroup> _groups;
        std::shared_ptr<TextRenderGroup> _shadowGroups;
    };

}

#endif