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