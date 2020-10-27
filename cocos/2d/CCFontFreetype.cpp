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

#include "CCFontFreetype.h"

#include <cassert>
#include "platform/CCFileUtils.h"
#include "platform/CCDevice.h"
#include "external/sources/edtaa3func/edtaa3func.h"
#include "base/ccConfig.h"

#if CC_ENABLE_TTF_LABEL_RENDERER

/**
 * By enable FFT_USE_SCREEN_DPI, text will be much more clear in mobile devices, 
 * and more memory will be consumed.
 */
#define FFT_USE_SCREEN_DPI 0

#if FFT_USE_SCREEN_DPI
#define SCALE_BY_DPI(x) (int)((x) * 72 / _dpi)
#else
#define SCALE_BY_DPI(x) (int)(x)
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
// `thread_local` can not compile on iOS 9.0 below device
#   define FFT_SDF_TMP_VECTOR (__IPHONE_OS_VERSION_MIN_REQUIRED >= 90000)
#else
#   define FFT_SDF_TMP_VECTOR 1
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#if FFT_SDF_TMP_VECTOR
namespace {
    //cache vector in thread
    thread_local std::vector<short> xdistV;
    thread_local std::vector<short> ydistV;
    thread_local std::vector<double> gxV;
    thread_local std::vector<double> gyV;
    thread_local std::vector<double> dataV;
    thread_local std::vector<double> outsideV;
    thread_local std::vector<double> insideV;
}
#endif

namespace cocos2d {

    class FontFreeTypeLibrary {
    public:
        FontFreeTypeLibrary() {
            memset(&_library, 0, sizeof(FT_Library));
            FT_Init_FreeType(&_library);
        }
        ~FontFreeTypeLibrary()
        {
            _faceCache.clear();
            FT_Done_FreeType(_library);
        }

        FT_Library * get() { return &_library; }

        std::unordered_map<std::string, std::shared_ptr<Data>> &getFaceCache() {
            return _faceCache;
        }
        
    private:
        std::unordered_map<std::string, std::shared_ptr<Data>> _faceCache;
        FT_Library _library;
    };

    namespace {
        std::shared_ptr<FontFreeTypeLibrary> _sFTLibrary;

        PixelMode FTtoPixelModel(FT_Pixel_Mode mode)
        {
            switch (mode)
            {
            case FT_PIXEL_MODE_GRAY:
                return PixelMode::A8;
            case FT_PIXEL_MODE_LCD:
                return PixelMode::RGB888;
            case FT_PIXEL_MODE_BGRA:
                return PixelMode::BGRA8888;
            default:
                assert(false); //invalidate pixelmode
                return PixelMode::INVAL;
            }
        }

        std::vector<uint8_t> makeDistanceMap(unsigned char *img, long width, long height, int distanceMapSpread)
        {
            long pixelAmount = (width + 2 * distanceMapSpread) * (height + 2 * distanceMapSpread);

#if FFT_SDF_TMP_VECTOR
            xdistV.resize(pixelAmount);
            ydistV.resize(pixelAmount);
            gxV.resize(pixelAmount);
            gyV.resize(pixelAmount);
            dataV.resize(pixelAmount);
            outsideV.resize(pixelAmount);
            insideV.resize(pixelAmount);

            std::fill(gxV.begin(), gxV.end(), 0.0);
            std::fill(gyV.begin(), gyV.end(), 0.0);
            std::fill(dataV.begin(), dataV.end(), 0.0);
            std::fill(outsideV.begin(), outsideV.end(), 0.0);
            std::fill(insideV.begin(), insideV.end(), 0.0);

            short * xdist = xdistV.data();
            short * ydist = ydistV.data();
            double * gx = gxV.data();
            double * gy = gyV.data();
            double * data = dataV.data();
            double * outside = outsideV.data();
            double * inside = insideV.data();
#else
            short * xdist = (short *)malloc(pixelAmount * sizeof(short));
            short * ydist = (short *)malloc(pixelAmount * sizeof(short));
            double * gx = (double *)calloc(pixelAmount, sizeof(double));
            double * gy = (double *)calloc(pixelAmount, sizeof(double));
            double * data = (double *)calloc(pixelAmount, sizeof(double));
            double * outside = (double *)calloc(pixelAmount, sizeof(double));
            double * inside = (double *)calloc(pixelAmount, sizeof(double));
#endif
            long i, j;

            // Convert img into double (data) rescale image levels between 0 and 1
            long outWidth = width + 2 * distanceMapSpread;
            for (i = 0; i < width; ++i)
            {
                for (j = 0; j < height; ++j)
                {
                    data[(j + distanceMapSpread) * outWidth + distanceMapSpread + i] = img[j * width + i] / 255.0;
                }
            }

            width += 2 * distanceMapSpread;
            height += 2 * distanceMapSpread;

            // Transform background (outside contour, in areas of 0's)   
            computegradient(data, (int)width, (int)height, gx, gy);
            edtaa3(data, gx, gy, (int)width, (int)height, xdist, ydist, outside);
            for (i = 0; i < pixelAmount; i++)
                if (outside[i] < 0.0)
                    outside[i] = 0.0;

            // Transform foreground (inside contour, in areas of 1's)   
            for (i = 0; i < pixelAmount; i++)
                data[i] = 1 - data[i];
            computegradient(data, (int)width, (int)height, gx, gy);
            edtaa3(data, gx, gy, (int)width, (int)height, xdist, ydist, inside);
            for (i = 0; i < pixelAmount; i++)
                if (inside[i] < 0.0)
                    inside[i] = 0.0;

            // The bipolar distance field is now outside-inside
            double dist;
            /* Single channel 8-bit output (bad precision and range, but simple) */
            std::vector<uint8_t> out;
            out.resize(pixelAmount);
            for (i = 0; i < pixelAmount; i++)
            {
                dist = outside[i] - inside[i];
                dist = 128.0 - dist * 16;
                if (dist < 0) dist = 0;
                if (dist > 255) dist = 255;
                out[i] = (unsigned char)dist;
            }
            /* Dual channel 16-bit output (more complicated, but good precision and range) */
            /*unsigned char *out = (unsigned char *) malloc( pixelAmount * 3 * sizeof(unsigned char) );
            for( i=0; i< pixelAmount; i++)
            {
                dist = outside[i] - inside[i];
                dist = 128.0 - dist*16;
                if( dist < 0.0 ) dist = 0.0;
                if( dist >= 256.0 ) dist = 255.999;
                // R channel is a copy of the original grayscale image
                out[3*i] = img[i];
                // G channel is fraction
                out[3*i + 1] = (unsigned char) ( 256 - (dist - floor(dist)* 256.0 ));
                // B channel is truncated integer part
                out[3*i + 2] = (unsigned char)dist;
            }*/
#if !FFT_SDF_TMP_VECTOR
            free(xdist);
            free(ydist);
            free(gx);
            free(gy);
            free(data);
            free(outside);
            free(inside);
#endif
            return out;
        }


    }


    FontFreeType::FontFreeType(const std::string& fontName, float fontSize, LabelLayoutInfo *info)
    {
        if (!_sFTLibrary)
        {
            _sFTLibrary = std::make_shared< FontFreeTypeLibrary>();
        }

        _fontName = fontName;
        _fontSize = fontSize;
        _info = info;

#if FFT_USE_SCREEN_DPI
        _dpi = Device::getDPI();
#else
        _dpi = 72;
#endif
    }

    FontFreeType::~FontFreeType()
    {
        //CCLOG("~FontFreeType");
        if (_stroker) FT_Stroker_Done(_stroker);
        if (_face) FT_Done_Face(_face);
    }

    FT_Library& FontFreeType::getFTLibrary()
    {
        return *(_sFTLibrary->get());
    }

    bool FontFreeType::loadFont()
    {
        std::shared_ptr<Data> faceData;
        auto itr = _sFTLibrary->getFaceCache().find(_fontName);
        if (itr == _sFTLibrary->getFaceCache().end()) {
            faceData = std::make_shared<Data>(FileUtils::getInstance()->getDataFromFile(_fontName));
            _sFTLibrary->getFaceCache()[_fontName] = faceData;
        } else {
            faceData = itr->second;
        }
        
        if (FT_New_Memory_Face(getFTLibrary(), faceData->getBytes(), faceData->getSize(), 0, &_face))
        {
            cocos2d::log("[error] failed to parse font %s", _fontName.c_str());
            return false;
        }

        _fontFaceData = faceData;
    

        if (FT_Select_Charmap(_face, _encoding))
        {
            int foundIndex = -1;
            for (int charmapIndex = 0; charmapIndex < _face->num_charmaps; charmapIndex++)
            {
                if (_face->charmaps[charmapIndex]->encoding != FT_ENCODING_NONE)
                {
                    foundIndex = charmapIndex;
                    break;
                }
            }
            if (foundIndex == -1)
            {
                return false;
            }
            _encoding = _face->charmaps[foundIndex]->encoding;
            if (FT_Select_Charmap(_face, _encoding))
            {
                return false;
            }
        }

        int fontSizeInPoints = (int)(64.0f * _fontSize);

        if (FT_Set_Char_Size(_face, fontSizeInPoints, fontSizeInPoints, _dpi, _dpi))
        {
            return false;
        }

        _lineHeight = SCALE_BY_DPI((_face->size->metrics.ascender - _face->size->metrics.descender) >> 6);

        return true;
    }

    int FontFreeType::getHorizontalKerningForChars(uint64_t a, uint64_t b) const
    {
        auto idx1 = FT_Get_Char_Index(_face, static_cast<FT_ULong>(a));
        if (!idx1)
            return 0;
        auto idx2 = FT_Get_Char_Index(_face, static_cast<FT_ULong>(b));
        if (!idx2)
            return 0;
        FT_Vector kerning;
        if (FT_Get_Kerning(_face, idx1, idx2, FT_KERNING_DEFAULT, &kerning))
            return 0;

        return SCALE_BY_DPI(kerning.x >> 6);
    }

    std::unique_ptr<std::vector<int>> FontFreeType::getHorizontalKerningForUTF32Text(const std::u32string& text) const
    {
        if (!_face) return nullptr;
        if (FT_HAS_KERNING(_face) == 0) return nullptr;

        const auto letterNum = text.length();
        std::vector<int>* sizes = new std::vector<int>(letterNum, 0);

        for (int i = 1; i < letterNum; i++)
        {
            (*sizes)[i] = SCALE_BY_DPI(getHorizontalKerningForChars(text[i - 1], text[i]));
        }
        return std::unique_ptr<std::vector<int>>(sizes);
    }


    int FontFreeType::getFontAscender() const
    {
        return SCALE_BY_DPI(_face->size->metrics.ascender >> 6);
    }

    const char* FontFreeType::getFontFamily() const
    {
        if (!_face) return nullptr;
        return _face->family_name;
    }

    std::shared_ptr<GlyphBitmap> FontFreeType::getGlyphBitmap(unsigned long ch, bool hasOutline)
    {
        return hasOutline ? getSDFGlyphBitmap(ch) : getNormalGlyphBitmap(ch);
    }


    std::shared_ptr<GlyphBitmap> FontFreeType::getNormalGlyphBitmap(unsigned long ch)
    {
        if (!_face) return nullptr;
        const auto load_char_flag = FT_LOAD_RENDER | FT_LOAD_NO_AUTOHINT;
        if (FT_Load_Char(_face, static_cast<FT_ULong>(ch), load_char_flag))
        {
            return nullptr;
        }

        auto& metrics = _face->glyph->metrics;
        int x = SCALE_BY_DPI(metrics.horiBearingX >> 6);
        int y = SCALE_BY_DPI(-(metrics.horiBearingY >> 6));
        int w = SCALE_BY_DPI(metrics.width >> 6);
        int h = SCALE_BY_DPI(metrics.height >> 6);

        int adv = SCALE_BY_DPI(metrics.horiAdvance >> 6);


        auto& bitmap = _face->glyph->bitmap;
        int bmWidth = bitmap.width;
        int bmHeight = bitmap.rows;
        PixelMode mode = FTtoPixelModel(static_cast<FT_Pixel_Mode>(bitmap.pixel_mode));
        int size = PixelModeSize(mode) * bmWidth * bmHeight;
        std::vector<uint8_t> data((uint8_t*)bitmap.buffer, (uint8_t*)bitmap.buffer + size);
        auto* ret = new GlyphBitmap(data, bmWidth, bmHeight, Rect(x, y, w, h), adv, mode, 0);
        return std::shared_ptr<GlyphBitmap>(ret);
    }

    std::shared_ptr<GlyphBitmap> FontFreeType::getSDFGlyphBitmap(unsigned long ch)
    {
        if (!_face) return nullptr;
        const auto load_char_flag = FT_LOAD_RENDER | FT_LOAD_NO_AUTOHINT;
        if (FT_Load_Char(_face, static_cast<FT_ULong>(ch), load_char_flag))
        {
            return nullptr;
        }

        auto& metrics = _face->glyph->metrics;
        int x = SCALE_BY_DPI(metrics.horiBearingX >> 6);
        int y = SCALE_BY_DPI(-(metrics.horiBearingY >> 6));
        int w = SCALE_BY_DPI(metrics.width >> 6);
        int h = SCALE_BY_DPI(metrics.height >> 6);

        int adv = SCALE_BY_DPI(metrics.horiAdvance >> 6);

        auto& bitmap = _face->glyph->bitmap;
        int bmWidth = bitmap.width;
        int bmHeight = bitmap.rows;
        PixelMode mode = FTtoPixelModel(static_cast<FT_Pixel_Mode>(bitmap.pixel_mode));

        assert(mode == PixelMode::A8);

        int dms = std::max(3, (int)std::max(0.2 * bmWidth, 0.2 * bmHeight));

//        int size = PixelModeSize(mode) * bmWidth * bmHeight;
        std::vector<uint8_t> data = makeDistanceMap(bitmap.buffer, bmWidth, bmHeight, dms);
        auto* ret = new GlyphBitmap(data, bmWidth + 2 * dms, bmHeight + 2 * dms, Rect(x, y, w + 2 * dms, h +  2 * dms), adv, mode, dms);

        return std::shared_ptr<GlyphBitmap>(ret);
    }
}

#endif
