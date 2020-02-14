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

//#include "freetype2/ft2build.h"

#include "freetype/ft2build.h"

#include FT_FREETYPE_H
#include FT_STROKER_H


#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "CCTTFTypes.h"
#include "base/CCData.h"

#include "base/ccConfig.h"
#if CC_ENABLE_TTF_LABEL_RENDERER
namespace cocos2d {

    class FontFreeTypeLibrary;

    struct LabelLayoutInfo;

    class FontFreeType
    {
    public:

        //const static int DistanceMapSpread;

        FontFreeType(const std::string& fontName, float fontSize, LabelLayoutInfo* info);
        virtual ~FontFreeType();

        FT_Library& getFTLibrary();

        bool loadFont();

        int getHorizontalKerningForChars(uint64_t a, uint64_t b) const;
        std::unique_ptr<std::vector<int>> getHorizontalKerningForUTF32Text(const std::u32string &text) const;

        int getFontAscender() const;
        const char* getFontFamily() const;


        std::shared_ptr<GlyphBitmap> getGlyphBitmap(unsigned long ch, bool hasOutline = false);

    private:

        std::shared_ptr<GlyphBitmap> getNormalGlyphBitmap(unsigned long ch);
        std::shared_ptr<GlyphBitmap> getSDFGlyphBitmap(unsigned long ch);

        std::shared_ptr<FontFreeTypeLibrary> _ftLibrary;
        //weak reference
        LabelLayoutInfo *_info = nullptr;
        float _fontSize = 0.0f;
        float _lineHeight = 0.0f;
        std::string _fontName;

        Data _fontData;

        FT_Stroker _stroker = { 0 };
        FT_Face    _face = { 0 };
        FT_Encoding _encoding = FT_ENCODING_UNICODE;

        int _dpi = 72;
    };

}
#endif