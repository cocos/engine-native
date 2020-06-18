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

#include "CCFontAtlas.h"
#include "renderer/gfx/Texture2D.h"
#include "renderer/gfx/DeviceGraphics.h"
#include "base/ccConfig.h"
#include <cassert>

#if CC_ENABLE_TTF_LABEL_RENDERER

static const int PIXEL_PADDING = 2;

namespace cocos2d {

    FontAtlasFrame::FontAtlasFrame()
    {
        _currentRowX = PIXEL_PADDING;
        _currentRowY = PIXEL_PADDING;
    }

    FontAtlasFrame::FontAtlasFrame(FontAtlasFrame&& o)
    {
#if CC_ENABLE_CACHE_TTF_FONT_TEXTURE
        // move buffer instead of copy
        std::swap(_buffer, o._buffer);
        _dirtyFlag = o._dirtyFlag;
        _dirtyRegion = o._dirtyRegion;
#endif
        _WIDTH = o._WIDTH;
        _HEIGHT = o._HEIGHT;
        _currentRowX = o._currentRowX;
        _currentRowY = o._currentRowY;
        _currRowHeight = o._currRowHeight;
        _pixelMode = o._pixelMode;
        _texture = o._texture;

        o._texture = nullptr;
    }

    FontAtlasFrame::~FontAtlasFrame()
    {
        CC_SAFE_RELEASE(_texture);
    }

    void FontAtlasFrame::reinit(PixelMode pixelMode, int width, int height)
    {
        _pixelMode = pixelMode;
        _WIDTH = width;
        _HEIGHT = height;
        _currentRowY = PIXEL_PADDING;
        _currentRowY = PIXEL_PADDING;
        _currRowHeight = 0;
#if CC_ENABLE_CACHE_TTF_FONT_TEXTURE 
        _buffer.resize(PixelModeSize(pixelMode) * width * height);
        std::fill(_buffer.begin(), _buffer.end(), 0);
        _dirtyFlag = 0;
#endif

        getTexture(); // init texture
    }

    FontAtlasFrame::FrameResult FontAtlasFrame::append(int width, int height, std::vector<uint8_t> &data, Rect &out)
    {
#if CC_ENABLE_CACHE_TTF_FONT_TEXTURE 
        assert(_buffer.size() > 0);
        assert(width <= _WIDTH && height <= _HEIGHT);
#endif
        if (!hasSpace(width, height)) {
            return FrameResult::E_FULL;
        }

#if CC_ENABLE_CACHE_TTF_FONT_TEXTURE 
        //update texture-data in CPU memory
        const int pixelSize = PixelModeSize(_pixelMode);
        uint8_t* dst = _buffer.data();
        uint8_t* src = data.data();
        uint8_t* dstOrigin = pixelSize * (_currentRowY * _WIDTH + _currentRowX) + dst;
        const int BytesEachRow = pixelSize * width;
        for (int i = 0; i < height; i++)
        {
            memcpy(dstOrigin + i * _WIDTH * pixelSize, src + i * BytesEachRow, BytesEachRow);
        }

        if (_dirtyFlag == 0)
        {
            _dirtyFlag |= DIRTY_RECT;
            _dirtyRegion = Rect(_currentRowX, _currentRowY, width, height);
        }
        else
        {
            _dirtyRegion.merge(Rect(_currentRowX, _currentRowY, width, height));
        }
#else 
        //update GPU texture immediately
        renderer::Texture::SubImageOption opt;
        opt.imageData = data.data();
        opt.x = _currentRowX;
        opt.y = _currentRowY;
        opt.width = width;
        opt.height = height;
        opt.imageDataLength = data.size();
        _texture->updateSubImage(opt);
#endif


        out.origin.set(_currentRowX, _currentRowY);
        out.size.width = width;
        out.size.height = height;
        // move cursor
        moveToNextCursor(width, height);
        return FrameResult::SUCCESS;

    }

    bool FontAtlasFrame::hasSpace(int width, int height)
    {
        if (hasRowXSpace(width) && hasYSpace(height)) {
            return true;
        }
        if (hasNextRowXSpace(width) && hasNextRowYSpace(height))
        {
            moveToNextRow();
            return true;
        }
        return false;
    }


    int FontAtlasFrame::remainRowXSpace() const 
    { 
        return _WIDTH - _currentRowX; 
    }

    int FontAtlasFrame::remainYSpace() const 
    { 
        return _HEIGHT - _currentRowY; 
    }

    bool FontAtlasFrame::hasRowXSpace(int x) const 
    { 
        return x + PIXEL_PADDING <= remainRowXSpace();
    }

    bool FontAtlasFrame::hasYSpace(int y) const 
    {
        return y + PIXEL_PADDING <= remainYSpace();
    }

    bool FontAtlasFrame::hasNextRowXSpace(int x) const 
    { 
        return x + PIXEL_PADDING <= _WIDTH;
    }

    bool FontAtlasFrame::hasNextRowYSpace(int y) const 
    { 
        return y + PIXEL_PADDING <= remainYSpace() - _currRowHeight;
    }


    void FontAtlasFrame::moveToNextRow()
    {
        _currentRowY += _currRowHeight + PIXEL_PADDING;
        _currentRowX = PIXEL_PADDING;
        _currRowHeight = 0;
    }

    void FontAtlasFrame::moveToNextCursor(int width, int height)
    {
        _currRowHeight = std::max(_currRowHeight, height);
        _currentRowX += width + PIXEL_PADDING;
    }

    renderer::Texture2D * FontAtlasFrame::getTexture()
    {
        if (!_texture)
        {
            auto* device = renderer::DeviceGraphics::getInstance();
            _texture = new cocos2d::renderer::Texture2D();

            cocos2d::renderer::Texture::Options option;
            option.width = _WIDTH;
            option.height = _HEIGHT;
            // alpha only
            option.glFormat = GL_ALPHA;
            option.glInternalFormat = GL_ALPHA;

            option.glType = GL_UNSIGNED_BYTE;
            option.bpp = 8 * PixelModeSize(_pixelMode);

            renderer::Texture::Image img;
#if CC_ENABLE_CACHE_TTF_FONT_TEXTURE 
            img.data = _buffer.data();
            img.length = _buffer.size();
#else
            std::vector<uint8_t> buffer(_WIDTH * _HEIGHT * PixelModeSize(_pixelMode), 0);
            img.length = buffer.size();
            img.data = buffer.data();
#endif
            option.images.push_back(img);
            _texture->init(device, option);
        }


#if CC_ENABLE_CACHE_TTF_FONT_TEXTURE
        if (_dirtyFlag & DIRTY_ALL)
        {
            renderer::Texture::SubImageOption opt;
            opt.imageData = _buffer.data();
            opt.x = 0;
            opt.y = 0;
            opt.width = _WIDTH;
            opt.height = _HEIGHT;
            opt.imageDataLength = (uint32_t)_buffer.size();
            _texture->updateSubImage(opt);
        }
        else if (_dirtyFlag & DIRTY_RECT)
        {
            int yMin = _dirtyRegion.getMinY();
            int yHeight = _dirtyRegion.size.height;
            renderer::Texture::SubImageOption opt;
            opt.imageData = _buffer.data() + PixelModeSize(_pixelMode) * _WIDTH * yMin;
            opt.x = 0;
            opt.y = yMin;
            opt.width = _WIDTH;
            opt.height = yHeight;
            opt.imageDataLength = PixelModeSize(_pixelMode) * _WIDTH * yHeight;
            _texture->updateSubImage(opt);
        }
        _dirtyFlag = 0;
#endif
        return _texture;
    }


    FontAtlas::FontAtlas(PixelMode pixelMode, int width, int height, bool hasoutline)
        :_pixelMode(pixelMode), _width(width), _height(height), _useSDF(hasoutline)
    {
    }

    FontAtlas::~FontAtlas() 
    {
    }


    bool FontAtlas::init()
    {
        _textureFrame.reinit(_pixelMode, _width, _height);
        _letterMap.clear();
        return true;
    }

    bool FontAtlas::prepareLetter(unsigned long ch, std::shared_ptr<GlyphBitmap> bitmap)
    {

        if (_letterMap.find(ch) != _letterMap.end())
        {
            return true;
        }

        Rect rect;
        FontAtlasFrame::FrameResult ret = _textureFrame.append(bitmap->getWidth(), bitmap->getHeight(), bitmap->getData(), rect);

        switch (ret) {
        case FontAtlasFrame::FrameResult::E_ERROR:
            //TODO: ERROR LOG
            assert(false);
            return false;
        case FontAtlasFrame::FrameResult::E_FULL:
            // Allocate a new frame & add bitmap the frame
            _buffers.push_back(std::move(_textureFrame));
            _textureBufferIndex += 1;
            _textureFrame.reinit(_pixelMode, _width, _height);
            return prepareLetter(ch, bitmap);
        case FontAtlasFrame::FrameResult::SUCCESS:
            addLetterDef(ch, bitmap, rect);
            return true;
        default:
            //TODO: LOG
            assert(false);
        }
        return false;
    }

    void FontAtlas::addLetterDef(unsigned long ch, std::shared_ptr<GlyphBitmap> bitmap, const Rect& rect)
    {
        assert(bitmap->getPixelMode() == _pixelMode);

        auto& def = _letterMap[ch];
        def.validate = true;
        def.textureID = _textureBufferIndex;
        def.xAdvance = bitmap->getXAdvance();
        def.rect = bitmap->getRect();
        def.texX = (rect.origin.x - 0.5f) / _textureFrame.getWidth();
        def.texY = (rect.origin.y -0.5f)/ _textureFrame.getHeight();
        def.texWidth = (rect.size.width + 1.0f) / _textureFrame.getWidth();
        def.texHeight = (rect.size.height + 1.0f) / _textureFrame.getHeight();
        def.outline = bitmap->getOutline();
    }

    bool FontAtlas::prepareLetters(const std::u32string &text, cocos2d::FontFreeType *font)
    {
        bool ok = true;
        for (int i = 0; i < text.length(); i++) 
        {
            auto it = _letterMap.find(text[i]);
            if(it == _letterMap.end())
            {
                auto glyph = font->getGlyphBitmap(text[i], _useSDF);
                ok &= prepareLetter(text[i], glyph);
            }
        }
        return ok;
    }

    FontLetterDefinition* FontAtlas::getOrLoad(unsigned long ch, cocos2d::FontFreeType* font)
    {
        auto it = _letterMap.find(ch);
        if (it != _letterMap.end()) return &it->second;

        if (font) {
            auto bitmap = font->getGlyphBitmap(ch, _useSDF);
            if (bitmap) {
                if (prepareLetter(ch, bitmap)) {
                    return getOrLoad(ch, nullptr);
                }
            }
        }
        return nullptr;
    }


    FontAtlasFrame& FontAtlas::frameAt(int idx)
    {
        return idx == _textureBufferIndex ? _textureFrame : _buffers.at(idx);
    }

}

#endif
