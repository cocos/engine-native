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
#include "2d/CCLabelLayout.h"
#include "2d/CCTTFLabelAtlasCache.h"

#include "base/ccUTF8.h"
#include "MiddlewareMacro.h"
#include "renderer/renderer/Pass.h"
#include "renderer/renderer/Effect.h"
#include "renderer/renderer/Technique.h"
#include "renderer/scene/assembler/CustomAssembler.hpp"
#include "cocos/editor-support/MeshBuffer.h"
#include "cocos/editor-support/IOBuffer.h"
#include "cocos/editor-support/middleware-adapter.h"
#include "cocos/editor-support/MiddlewareManager.h"

#include "renderer/gfx/DeviceGraphics.h"
#include "renderer/gfx/Texture2D.h"

#include <cassert>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <chrono>

#include "base/ccConfig.h"

#if CC_ENABLE_TTF_LABEL_RENDERER

namespace {
    const std::string textureKey = "texture";
    const std::string shadowColor = "shadowColor";
    const std::string outlineSizeKey = "outlineSize";
    const std::string outlineColorKey= "outlineColor";
}

using namespace cocos2d::renderer;
using namespace cocos2d::middleware;

namespace cocos2d {

    namespace {
        void recalculateUV(const Rect &oldRect, const Rect &oldUV, const Rect &newRect, Rect &newUV)
        {
            auto offsetOrigin = newRect.origin - oldRect.origin;
            float uvWidth = newRect.size.width / oldRect.size.width * oldUV.size.width;
            float uvHeight = newRect.size.height / oldRect.size.height * oldUV.size.height;
            float uvOriginX = offsetOrigin.x / oldRect.size.width * oldUV.size.width + oldUV.origin.x;
            float uvOriginY = (oldUV.size.height - uvHeight - offsetOrigin.y / oldRect.size.height * oldUV.size.height) + oldUV.origin.y;
            newUV.setRect(uvOriginX, uvOriginY, uvWidth, uvHeight);
        }

        inline void find_2nd_3rd(float min1, float max1, float min2, float max2, float &second, float &third)
        {
            assert(max1 >= min1 && max2 >= min2);

            if (max1 < max2)
            {
                second = min1 < min2 ? min2 : min1;
                third = max1;
            }
            else
            {
                second = min2 < min1 ? min1 : min2;
                third = max2;
            }
        }

        void rectUnion(const Rect &a, const Rect &b, Rect &out)
        {
            float xMax, yMax;
            find_2nd_3rd(a.getMinX(), a.getMaxX(), b.getMinX(), b.getMaxX(), out.origin.x, xMax);
            find_2nd_3rd(a.getMinY(), a.getMaxY(), b.getMinY(), b.getMaxY(), out.origin.y, yMax);
            out.size.setSize(xMax - out.origin.x, yMax - out.origin.y);
        }

        void subRect(const Rect &rect, const Rect &uv, float offsetX, float width, Rect &out1, Rect &out2)
        {
            out1.origin.set(offsetX + rect.origin.x, rect.origin.y);
            out1.size.setSize(width, rect.size.height);
            out2.origin.set(uv.origin.x + uv.size.width * offsetX / rect.size.width, uv.origin.y);
            out2.size.setSize(uv.size.width * width / rect.size.width, uv.size.height);
        }

        void splitRectIntoThreeParts(int texId, const Rect &defRect,  const Rect &targetRect, const Rect &uv, cocos2d::TextRowSpace &space)
        {
            constexpr float LEFT = 0.3f;
            constexpr float MIDDLE = 0.4f;
            constexpr float RIGHT = 0.3f;
            Rect out1, out2;
            float cursorX = 0.0f;
            //part left
            subRect(targetRect, uv, 0.0f, targetRect.size.width * LEFT, out1, out2);
            cursorX = defRect.size.width *LEFT;
            out1.size.width = cursorX;
            space.fillRect(texId, out1, out2);
            //part middle
            subRect(targetRect, uv, targetRect.size.width * LEFT, targetRect.size.width * MIDDLE, out1, out2);
            out1.origin.x = targetRect.origin.x + cursorX;
            out1.size.width = targetRect.size.width - defRect.size.width * (LEFT + RIGHT);
            cursorX = targetRect.size.width - defRect.size.width * RIGHT;
            space.fillRect(texId, out1, out2);
            //part right
            subRect(targetRect, uv, targetRect.size.width * (LEFT + MIDDLE) , targetRect.size.width *RIGHT, out1, out2);
            out1.origin.x = targetRect.origin.x  + cursorX;
            out1.size.width = defRect.size.width * RIGHT;
            space.fillRect(texId, out1, out2);
        }
    }

    class TextRenderGroupItem {
    public:

        enum DirtyFlag {
            VERTEX_DIRTY = 1,
            INDEXES_DIRTY = 2
        };

        TextRenderGroupItem(renderer::Texture *);
        virtual ~TextRenderGroupItem();

        void reset();

        void addRect(const Rect &vert, const Rect &uv, const Color4B &color, bool italics);

        void upload();

        inline int getRectSize() const { return _rectSize; }

        middleware::MeshBuffer* getBuffer() { return _buffer; }

    private:

        void addIndexes();

        middleware::MeshBuffer * _buffer = nullptr;
        renderer::Texture *_texture = nullptr;
        int _rectSize = 0;
        int _indexSize = 0;

        int _dirtyFlags = -1;
    };


    class TextRenderGroup {
    public:

        void reset();
        void addRect(renderer::Texture*, const Rect &vert, const Rect &uv, const Color4B &color, bool italics);

        int fill(CustomAssembler *assembler, int, LabelLayout *layout, EffectVariant *);

    private:
        std::unordered_map<renderer::Texture*, std::shared_ptr<TextRenderGroupItem>> _buffers;
    };


    TextRenderGroupItem::TextRenderGroupItem(renderer::Texture* tex)
    {
        _texture = tex;
        _buffer = new middleware::MeshBuffer(VF_XYUVC);
    }
    TextRenderGroupItem::~TextRenderGroupItem()
    {
        delete _buffer;
    }

    void TextRenderGroupItem::reset() {

        _buffer->reset();
        _rectSize = 0;
        _dirtyFlags = -1;
    }

    void TextRenderGroupItem::addRect(const Rect &rect, const Rect &uv, const Color4B &color, bool italics)
    {
        middleware::IOBuffer &vertexBuffer = _buffer->getVB();
        const int minSize = sizeof(V2F_T2F_C4B) * std::max(16, 4 * _rectSize);
        if (vertexBuffer.getCapacity() < minSize)
        {
            vertexBuffer.checkSpace(minSize << 2, true);
        }

        V2F_T2F_C4B *verts = ((V2F_T2F_C4B*)vertexBuffer.getBuffer()) + 4 * _rectSize;

        float height = rect.size.height;
        float offsetX = 0.0f;
        const float factor = 0.21255f;
        if (italics) {
            offsetX = height * factor;
        }

        verts[0].vertex = { rect.getMinX() + offsetX, rect.getMaxY() };
        verts[1].vertex = { rect.getMaxX() + offsetX, rect.getMaxY() };
        verts[2].vertex = { rect.getMinX() - offsetX, rect.getMinY() };
        verts[3].vertex = { rect.getMaxX() - offsetX, rect.getMinY() };

        verts[0].texCoord = { uv.getMinX(), uv.getMinY() };
        verts[1].texCoord = { uv.getMaxX(), uv.getMinY() };
        verts[2].texCoord = { uv.getMinX(), uv.getMaxY() };
        verts[3].texCoord = { uv.getMaxX(), uv.getMaxY() };

        verts[0].color = color;
        verts[1].color = color;
        verts[2].color = color;
        verts[3].color = color;
        _rectSize += 1;

        _dirtyFlags |= DirtyFlag::VERTEX_DIRTY;
    }

    void TextRenderGroupItem::addIndexes()
    {
        middleware::IOBuffer &indexBuffer = _buffer->getIB();
        int indexSize = sizeof(uint16_t) * _rectSize * 6;
        indexBuffer.checkSpace(indexSize, true);
        uint16_t *indices = (uint16_t*)indexBuffer.getBuffer();
        for (int i = _indexSize; i < _rectSize; i += 1)
        {
            indices[i * 6 + 0] = 0 + 4 * i;
            indices[i * 6 + 1] = 1 + 4 * i;
            indices[i * 6 + 2] = 2 + 4 * i;
            indices[i * 6 + 3] = 1 + 4 * i;
            indices[i * 6 + 4] = 3 + 4 * i;
            indices[i * 6 + 5] = 2 + 4 * i;
        }

        if (_indexSize < _rectSize)
        {
            _indexSize = _rectSize;
            _dirtyFlags |= DirtyFlag::INDEXES_DIRTY;
        }
    }

    void TextRenderGroupItem::upload()
    {
        addIndexes();

        middleware::IOBuffer &vertexBuffer = _buffer->getVB();
        middleware::IOBuffer &indexBuffer = _buffer->getIB();

        vertexBuffer.move(_rectSize * 4 * sizeof(V2F_T2F_C4B));
        indexBuffer.move(_rectSize * 6 * sizeof(uint16_t));

        if (_dirtyFlags | DirtyFlag::INDEXES_DIRTY)
        {
            _buffer->uploadIB();
        }

        if (_dirtyFlags | DirtyFlag::VERTEX_DIRTY)
        {
            _buffer->uploadVB();
        }

        _dirtyFlags = 0;
    }

    void TextRenderGroup::addRect(renderer::Texture* tex, const Rect &vert, const Rect &uv, const Color4B &color, bool italics)
    {
        auto &itemPtr = _buffers[tex];
        if (!itemPtr) {
            itemPtr = std::make_shared<TextRenderGroupItem>(tex);
        }
        itemPtr->addRect(vert, uv, color, italics);
    }


    void TextRenderGroup::reset()
    {
        for (auto &it : _buffers)
        {
            it.second->reset();
        }
        _buffers.clear();
    }

    int TextRenderGroup::fill(CustomAssembler *assembler, int startIndex, LabelLayout *layout, EffectVariant *templateEffect)
    {
        int groupIndex = startIndex;
        for (auto &it : _buffers)
        {
            auto &item = it.second;
            if (item->getRectSize() > 0)
            {
                item->upload();

                assembler->updateIABuffer(groupIndex, item->getBuffer()->getGLVB(), item->getBuffer()->getGLIB());

                assembler->updateIARange(groupIndex, 0, item->getRectSize() * 6);

                auto *effect = assembler->getEffect(groupIndex);
                
                if (!effect && templateEffect) {
                    effect = new cocos2d::renderer::EffectVariant();
                    effect->autorelease();
                    effect->copy(templateEffect);
                    assembler->updateEffect(groupIndex, effect);
                }
                
                if(effect->getPasses().at(0)->getDefinesHash() != templateEffect->getPasses().at(0)->getDefinesHash()){
                    effect->copy(templateEffect);
                }

                if (effect) {
                    effect->setProperty(textureKey, it.first);
                }

                groupIndex += 1;
            }
        }
        return groupIndex;
    }



    struct TextSpaceArray {

        void addSpace(TextRowSpace& space)
        {
            if (space.size() > 0)
            {
                _maxWidth = std::max(_maxWidth, space.getWidth());
            }
            _data.emplace_back(std::move(space));
        }

        float _maxWidth = FLT_MIN;
        std::vector<TextRowSpace> _data;
    };


    TextRowSpace::GlyphBlock & TextRowSpace::operator[](size_t i)
    { 
        return _data[i]; 
    }


    TextRowSpace::GlyphBlock & TextRowSpace::appendBlock()
    {
        _data.resize(_data.size() + 1);
        return _data[_data.size() - 1];
    }

    TextRowSpace::TextRowSpace(TextRowSpace &&other)
    {
        _left = other._left;
        _bottom = other._bottom;
        _right = other._right;
        _top = other._top;
        _x = other._x;
        _y = other._y;
        _data = std::move(other._data);
        _ignored = other._ignored;
        other.reset();
    }


    void TextRowSpace::reset()
    {
        _left = FLT_MAX;
        _bottom = FLT_MAX;
        _right = FLT_MIN;
        _top = FLT_MIN;
        _x = 0.0f;
        _y = 0.0f;
        _data.clear();
        _ignored = false;
    }

    void TextRowSpace::fillRect(int texId, Rect &rect, Rect &uv)
    {
        GlyphBlock &block = appendBlock();
        _left = std::min(_left, rect.getMinX());
        _right = std::max(_right, rect.getMaxX());
        _bottom = std::min(_bottom, rect.getMinY());
        _top = std::max(_top, rect.getMaxY());
        block.area = rect;
        block.uv = uv;
        block.ignored = false;
        block.texId = texId;
    }

    void TextRowSpace::translate(float x, float y)
    {
        _x += x;
        _y += y;
    }

    Vec2 TextRowSpace::center() const
    {
        Vec2 ret((_left + _right) / 2.0f, (_bottom + _top) / 2.0f);
        return ret;
    }

    float TextRowSpace::getExtentedWidth(float left, float right) const
    {
        if (_data.size() == 0) 
        {
            return right - left;
        }
        return std::max(_right, right) - std::min(_left, left);
    }


    void TextRowSpace::clip(const Rect &rect)
    {
        Rect contentRect(_x + _left, _y + _bottom, _right - _left, _top - _bottom);

        if (!rect.intersectsRect(contentRect)) {
            _ignored = true;
            return;
        }

        const auto size = _data.size();
        const auto offset = getOffset();
        Rect letter;
        Rect unionRect;
        for (int i = 0; i < size; i++)
        {
            letter.size = _data[i].area.size;
            letter.origin = offset + _data[i].area.origin;

            if (!rect.intersectsRect(letter))
            {
                _data[i].ignored = true;
            }
            else if (rect.containsPoint(letter.origin) && rect.containsPoint(Vec2(letter.getMaxX(), letter.getMaxY())))
            {
                _data[i].area.origin = letter.origin;
            }
            else
            {
                //Rect unionRect = letter.unionWithRect(rect); // incorrect result
                rectUnion(letter, rect, unionRect);
                _data[i].area = unionRect;
                recalculateUV(letter, _data[i].uv, unionRect, _data[i].uv);
            }

        }
        //ignore translate
        _x = 0.0f;
        _y = 0.0f;
    }

    Rect TextRowSpace::asRect() const {
        return Rect(_left + _x, _bottom + _y, _right - _left, _top - _bottom);
    }

    bool LabelLayout::init(const std::string& font, const std::string& text, float fontSize, float retinaFontSize, LabelLayoutInfo *info)
    {
        _inited = true;
        _layoutInfo = info;
        _retinaFontSize = std::max(fontSize, retinaFontSize);
        _fontAtlas = TTFLabelAtlasCache::getInstance()->load(font, _retinaFontSize, info);
        if(!_fontAtlas) {
            return false;
        }
        _fontScale = fontSize / _fontAtlas->getFontSize();
        _groups = std::make_shared<TextRenderGroup>();
        if (info->shadowBlur >= 0)
        {
            _shadowGroups = std::make_shared<TextRenderGroup>();
        }
        _string = text;
        _font = font;
        _fontSize = fontSize;
        cocos2d::StringUtils::UTF8ToUTF32(text.c_str(), _u32string);

        _textSpace.clear();

        updateContent();
        return true;
    }

    LabelLayout::~LabelLayout()
    {
    }


    void LabelLayout::setString(const std::string &txt, bool forceUpdate)
    {
        if (_string != txt) {
            _string = txt;
            cocos2d::StringUtils::UTF8ToUTF32(txt.c_str(), _u32string);
            updateContent();
        }
        else if (forceUpdate)
        {
            updateContent();
        }

    }


    bool LabelLayout::updateContent()
    {
        if(!_fontAtlas)
        {
            return false;
        }
        auto *atlas = _fontAtlas->getFontAtlas();
        auto *ttf = _fontAtlas->getTTF();

        FontLetterDefinition* letterDef = nullptr;
        Rect row;


        const float LineHeight = _layoutInfo->lineHeight;
        const float SpaceX = _layoutInfo->spaceX;
        const LabelOverflow OverFlow = _layoutInfo->overflow;
        const bool ClampAndWrap = _layoutInfo->wrap && OverFlow == LabelOverflow::CLAMP;
        const bool ResizeHeight = OverFlow == LabelOverflow::RESIZE_HEIGHT;
        const int ContentWidth = _layoutInfo->width;
        const int ContentHeight = _layoutInfo->height;
        const LabelAlignmentH HAlign = _layoutInfo->halign;
        const LabelAlignmentV VAlign = _layoutInfo->valign;
        const float AnchorX = _layoutInfo->anchorX;
        const float AnchorY = _layoutInfo->anchorY;
        const bool Underline = _layoutInfo->underline;

        //LabelCursor cursor;
        float cursorX = 0;

        TextSpaceArray textSpaces;
        TextRowSpace rowSpace;

        Rect letterRect;

        std::unique_ptr<std::vector<int> > kerning = nullptr;
        if (_enableKerning) {
            kerning = ttf->getHorizontalKerningForUTF32Text(_u32string);
        }


        atlas->prepareLetters(_u32string, ttf);

        for (int i = 0; i < _u32string.size(); i++)
        {
            auto ch = _u32string[i];

            if (ch == u'\r')
            {
                cursorX = 0;
                continue;
            }

            if (ch == u'\n')
            {
                textSpaces.addSpace(rowSpace);
                cursorX = 0;
                continue;
            }

            letterDef = atlas->getOrLoad(ch, ttf);
            if (!letterDef) continue;
            
            letterRect = letterDef->rect;
            letterRect.origin *= _fontScale;
            letterRect.size = Size(letterRect.size.width * _fontScale, letterRect.size.height * _fontScale);

            if (_enableKerning && kerning) {
                auto const kerningX = kerning->at(i) * _fontScale;
                cursorX += kerningX;
            }

            float left = cursorX - letterDef->outline * _fontScale + letterRect.getMinX();
            float bottom = letterDef->outline * _fontScale - letterRect.getMaxY();

            if ((ResizeHeight || ClampAndWrap) && rowSpace.getExtentedWidth(left, left + letterRect.size.width) > ContentWidth)
            {
                // RESIZE_HEIGHT or (CLAMP & Enable Wrap)
                textSpaces.addSpace(rowSpace);
                cursorX = 0;
                left = cursorX - letterDef->outline * _fontScale + letterRect.getMinX();
            }

            float width = letterRect.size.width;
            float height = letterRect.size.height;

            Rect letterRectInline(left, bottom, width, height);
            Rect letterTexture(letterDef->texX, letterDef->texY, letterDef->texWidth, letterDef->texHeight);

            rowSpace.fillRect(letterDef->textureID, letterRectInline, letterTexture);

            cursorX += SpaceX + letterDef->xAdvance * _fontScale;
        }

        textSpaces.addSpace(rowSpace);

        auto& list = textSpaces._data;

        //add underline
        if(Underline){
            auto underline = atlas->getOrLoad('_', ttf);

            for (auto &space : list) {
                Rect letterRect = underline->rect;
                letterRect.origin *= _fontScale;
                letterRect.size = Size(letterRect.size.width * _fontScale, letterRect.size.height * _fontScale);
                float bottom = underline->outline * _fontScale - letterRect.getMaxY();
                float left =  -letterDef->outline * _fontScale + space.getLeft();

                Rect letterRectInline(left, bottom, space.getWidth(), letterRect.size.height);
                Rect letterTexture(underline->texX, underline->texY, underline->texWidth, underline->texHeight);
                splitRectIntoThreeParts(underline->textureID, letterRect, letterRectInline, letterTexture, space);
            }
        }

        Vec2 newCenter;
        Vec2 delta;
        // default value in LabelOverflow::None mode
        float maxLineWidth = textSpaces._maxWidth;
        const float TotalTextHeight = textSpaces._data.size() * LineHeight;
        float topMost = (TotalTextHeight - LineHeight) * (1.0f - AnchorY);
        float leftMost =  - AnchorX * maxLineWidth;
        float rightMost = (1.0f - AnchorX) * maxLineWidth;
        float centerX = (0.5f - AnchorX) * ContentWidth;

        Rect textArea(0, 0, 0, 0);

        for (int i = 0; i < list.size(); i++)
        {
            auto& s = list[i];
            if (!s.validate()) 
            {
                continue;
            }
            if (HAlign == LabelAlignmentH::CENTER)
            {
                newCenter.set(centerX, topMost - i * LineHeight);
            }
            else if (HAlign == LabelAlignmentH::LEFT)
            {
                newCenter.set(leftMost + s.getWidth() * 0.5, topMost - i * LineHeight);
            }
            else // right
            {
                newCenter.set(rightMost - s.getWidth() * 0.5f, topMost - i * LineHeight);
            }
            delta = newCenter - s.center();

            s.translate(delta.x, delta.y);

            textArea.merge(s.asRect());
            
        }

        //no resize
        if (OverFlow == LabelOverflow::NONE || OverFlow == LabelOverflow::CLAMP || OverFlow == LabelOverflow::RESIZE_HEIGHT)
        {
            Vec2 centerArea(textArea.origin.x + textArea.size.width / 2.0, textArea.origin.y + textArea.size.height / 2.0);
            float tPosX, tPosY;
            
            float halfAreaWidth = textArea.size.width * 0.5f;
            float halfAreaHeight = textArea.size.height * 0.5f;
            float contentWidth = ContentWidth;
            float contentHeight = ContentHeight;
            if (OverFlow == LabelOverflow::NONE)
            {
                contentWidth = textArea.size.width;
                contentHeight = textArea.size.height;
            }

            switch (HAlign)
            {
            case LabelAlignmentH::LEFT:
                tPosX = halfAreaWidth - AnchorX * contentWidth;
                break;
            case LabelAlignmentH::CENTER:
                tPosX = (0.5f - AnchorX) * contentWidth;
                break;
            case LabelAlignmentH::RIGHT:
                tPosX = (1.0f - AnchorX) * contentWidth - halfAreaWidth;
                break;
            default:
                assert(false);
            }

            switch (VAlign)
            {
            case LabelAlignmentV::TOP:
                tPosY = (1.0f - AnchorY) * contentHeight - halfAreaHeight;
                break;
            case LabelAlignmentV::CENTER:
                tPosY = (0.5f - AnchorY) * ContentHeight;
                break;
            case LabelAlignmentV::BOTTOM:
                tPosY = halfAreaHeight - AnchorY * contentHeight;
                break;
            default:
                assert(false);
            }

            delta = Vec2(tPosX, tPosY) - centerArea;

            for (auto &textSpace : textSpaces._data) {
                textSpace.translate(delta.x, delta.y);
            }

            if (OverFlow == LabelOverflow::CLAMP)
            {
                // clipping 
                Rect displayRegion(-ContentWidth * AnchorX, -ContentHeight * AnchorY, ContentWidth, ContentHeight);
                for (auto &textSpace : textSpaces._data) {
                    textSpace.clip(displayRegion);
                }

            }
        }
        else if (OverFlow == LabelOverflow::SHRINK)
        {
            float scale = std::min(ContentWidth / textArea.size.width, ContentHeight / textArea.size.height);
            scale = std::min(1.0f, scale);
            _scale = scale;
            Vec2 centerArea(textArea.origin.x + textArea.size.width * 0.5f, textArea.origin.y + textArea.size.height * 0.5f);
            float tPosXScale, tPosYScale;

            float halfTextWidth = textArea.size.width * 0.5f * _scale;
            float halfTextHeight = textArea.size.height * 0.5f * _scale;

            switch (HAlign)
            {
            case LabelAlignmentH::LEFT:
                tPosXScale = halfTextWidth - AnchorX * ContentWidth;
                break;
            case LabelAlignmentH::CENTER:
                tPosXScale = (0.5f - AnchorX) * ContentWidth;
                break;
            case LabelAlignmentH::RIGHT:
                tPosXScale = (1.0f - AnchorX) * ContentWidth -  halfTextWidth;
                break;
            default:
                assert(false);
            }

            switch (VAlign)
            {
            case LabelAlignmentV::TOP:
                tPosYScale = (1.0f - AnchorY) * ContentHeight - halfTextHeight;
                break;
            case LabelAlignmentV::CENTER:
                tPosYScale = (0.5f - AnchorY) * ContentHeight;
                break;
            case LabelAlignmentV::BOTTOM:
                tPosYScale = halfTextHeight -AnchorY * ContentHeight;
                break;
            default:
                assert(false);
            }
            delta = Vec2(tPosXScale/ _scale, tPosYScale/_scale) - centerArea;
            for (auto &textSpace : textSpaces._data) {
                textSpace.translate(delta.x, delta.y);
            }
        }


        _textSpace = std::move(textSpaces._data);

        return true;
    }

    void LabelLayout::fillAssembler(renderer::CustomAssembler *assembler, EffectVariant *templateEffect)
    {
        assembler->reset();
        if(!_groups) {
            return;
        }
        _groups->reset();
        int groupIndex = 0;
        if (_textSpace.empty())
            return;

        if (_shadowGroups)
        {
            _shadowGroups->reset();
        }

        assembler->setUseModel(true);

        auto *fontAtals = _fontAtlas->getFontAtlas();

        Color4B textColor = _layoutInfo->color;

        // apply transform to all rectangles
        Rect rect;
        float scale = _scale;

        const bool Italics = _layoutInfo->italic;

        if (_shadowGroups && _layoutInfo->shadowBlur >= 0)
        {
            Vec2 offset(_layoutInfo->shadowX, _layoutInfo->shadowY);
            Color4B shadowColor = _layoutInfo->shadowColor;
            for (auto &textSpace : _textSpace) {

                if (textSpace.isIgnored()) continue;

                Vec2 shadowOffset = textSpace.getOffset();
                auto size = textSpace.size();
                for (int i = 0; i < size; i++)
                {
                    TextRowSpace::GlyphBlock item = textSpace[i];
                    if (textSpace.isIgnored(i)) continue;

                    item.area.size = item.area.size * scale;
                    item.area.origin = (offset + item.area.origin + shadowOffset) * scale;

                    _shadowGroups->addRect(fontAtals->frameAt(item.texId).getTexture(), item.area, item.uv, shadowColor, Italics);
                }
            }

            groupIndex = _shadowGroups->fill(assembler, groupIndex,  this, templateEffect);

            Technique::Parameter outlineSizeP(outlineSizeKey, Technique::Parameter::Type::FLOAT, (float*)&(_layoutInfo->outlineSize));
            if (_layoutInfo->outlineSize > 0.0f)
            {
                // use shadow color to replace outline color
                Color4F outlineColor(_layoutInfo->shadowColor);
                Technique::Parameter outlineColorP(outlineColorKey, Technique::Parameter::Type::COLOR4, (float*)&outlineColor);
                for (auto i = 0; i < groupIndex; i++)
                {
                    auto *e = assembler->getEffect(i);
                    e->setProperty(outlineColorKey, outlineColorP);
                    e->setProperty(outlineSizeKey, outlineSizeP);
                }
            }
            else {
                for (auto i = 0; i < groupIndex; i++)
                {
                    auto *e = assembler->getEffect(i);
                    e->setProperty(outlineSizeKey, outlineSizeP);
                }
            }
            
        }

        for (auto &textSpace : _textSpace) {

            if (textSpace.isIgnored()) continue;

            Vec2 offset = textSpace.getOffset();
            auto size = textSpace.size();
            for (int i = 0; i < size; i++) 
            {
                auto &item = textSpace[i];
                if (textSpace.isIgnored(i)) continue;

                item.area.size = item.area.size * scale;
                item.area.origin = (offset + item.area.origin) * scale;

                _groups->addRect(fontAtals->frameAt(item.texId).getTexture(), item.area, item.uv, textColor, Italics);
            }
        }
        int textStartIndex = groupIndex;
        groupIndex = _groups->fill(assembler, groupIndex, this,  templateEffect);

        if (_layoutInfo->outlineSize > 0.0f)
        {
            Color4F outlineColor(_layoutInfo->outlineColor);
            Technique::Parameter outlineColorP(outlineColorKey, Technique::Parameter::Type::COLOR4, (float*)&outlineColor);
            Technique::Parameter outlineSizeP(outlineSizeKey, Technique::Parameter::Type::FLOAT, (float*)&(_layoutInfo->outlineSize));
            for (auto i = textStartIndex; i < groupIndex; i++) 
            {
                auto *e = assembler->getEffect(i);
                e->setProperty(outlineColorKey, outlineColorP);
                e->setProperty(outlineSizeKey, outlineSizeP);
            }
        }
        else {
            Color4F outlineColor(_layoutInfo->outlineColor);
            Technique::Parameter outlineSizeP(outlineSizeKey, Technique::Parameter::Type::FLOAT, (float*)&(_layoutInfo->outlineSize));
            for (auto i = textStartIndex; i < groupIndex; i++)
            {
                auto *e = assembler->getEffect(i);
                e->setProperty(outlineSizeKey, outlineSizeP);
            }
        }

    }

}

#endif
