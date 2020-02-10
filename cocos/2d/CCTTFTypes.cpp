#include "CCTTFTypes.h"

#include <cassert>
#include <cstdarg>
#include <iostream>
#include "base/ccConfig.h"
#if CC_ENABLE_TTF_LABEL_RENDERER
namespace cocos2d {

    GlyphBitmap::GlyphBitmap(std::vector<uint8_t>& data, int width, int height, Rect rect, int adv, PixelMode mode, int outline)
        : _data(std::move(data)), _width(width), _height(height), _rect(rect), _xAdvance(adv), _pixelMode(mode), _outline(outline)
    {
    }
    GlyphBitmap::GlyphBitmap(GlyphBitmap&& other) noexcept
    {
        _data = std::move(other._data);
        _rect = other._rect;
        _width = other._width;
        _height = other._height;
        _xAdvance = other._xAdvance;
        _pixelMode = other._pixelMode;
        _outline = other._outline;
    }


    int PixelModeSize(PixelMode mode)
    {
        switch (mode)
        {
        case PixelMode::AI88:
            return 2;
        case PixelMode::A8:
            return 1;
        case PixelMode::RGB888:
            return 3;
        case PixelMode::BGRA8888:
            return 4;
        default:
            assert(false); // invalidate pixel mode
        }
        return 0;
    }

}

#endif