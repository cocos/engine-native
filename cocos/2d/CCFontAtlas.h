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

#include "CCFontFreetype.h"

#include <unordered_map>
#include <algorithm>

#include "base/ccConfig.h"
#if CC_ENABLE_TTF_LABEL_RENDERER

namespace cocos2d {

    namespace renderer {
        class Texture2D;
    }

    class FontAtlas;

    struct FontLetterDefinition
    {
        float texX = 0, texY = 0;
        float texWidth = 0, texHeight = 0;
        Rect rect;
        int textureID = -1;
        float xAdvance = 0;
        int outline = 0;
        bool validate = false;
    };

    class FontAtlasFrame
    {
    public:

        enum class FrameResult {
            SUCCESS,
            E_FULL,
            E_ERROR
        };

        FontAtlasFrame();
        FontAtlasFrame(FontAtlasFrame&&); //move

        virtual ~FontAtlasFrame();

        void reinit(PixelMode mode, int width, int height);
        FrameResult append(int width, int height, std::vector<uint8_t> &, Rect &out);


        float getWidth() const { return _WIDTH; }
        float getHeight() const { return _HEIGHT; }

        renderer::Texture2D* getTexture();

    private:

        enum DirtyType {
            DIRTY_RECT = 1,
            DIRTY_ALL= 2,
        };

        bool hasSpace(int width, int height);

        int remainRowXSpace() const;
        int remainYSpace() const;
        bool hasRowXSpace(int x) const;
        bool hasYSpace(int y) const;
        bool hasNextRowXSpace(int x) const;
        bool hasNextRowYSpace(int y) const;

        void moveToNextRow();
        void moveToNextCursor(int width, int height);

#if CC_ENABLE_CACHE_TTF_FONT_TEXTURE
        mutable std::vector<uint8_t> _buffer;
        int _dirtyFlag = 0;
        Rect _dirtyRegion;
#endif

        int _WIDTH = 0;
        int _HEIGHT = 0;
        int _currentRowY = 0;
        int _currentRowX = 0;
        int _currRowHeight = 0;
        PixelMode _pixelMode = PixelMode::A8;
        renderer::Texture2D *_texture = nullptr;
        
        friend class FontAtlas;
    };

    class FontAtlas {

    public:

        FontAtlas(PixelMode mode, int width, int height, bool hasoutline);
        virtual ~FontAtlas();

        bool init();

        bool prepareLetter(unsigned long ch, std::shared_ptr<GlyphBitmap> bitmap);

        bool prepareLetters(const std::u32string &text, cocos2d::FontFreeType *font);

        FontLetterDefinition* getOrLoad(unsigned long ch, FontFreeType* font);

        FontAtlasFrame& frameAt(int idx);
    private:

        void addLetterDef(unsigned long ch, std::shared_ptr<GlyphBitmap> bitmap, const Rect& rect);

        std::unordered_map<uint64_t, FontLetterDefinition> _letterMap;

        FontAtlasFrame   _textureFrame;
        std::vector<FontAtlasFrame> _buffers;
        int _textureBufferIndex = 0;
        int _width = 0;
        int _height = 0;
        PixelMode _pixelMode = PixelMode::A8;
        bool _useSDF = false;
    };

}

#endif