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