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


#include "2d/CCFontFreetype.h"
#include "2d/CCFontAtlas.h"

#include <unordered_map>
#include <memory>

#include "base/ccConfig.h"
#if CC_ENABLE_TTF_LABEL_RENDERER

#define CC_TTF_LABELATLAS_ENABLE_GC 1

namespace cocos2d {

    class TTFLabelAtlasCache;
    struct LabelLayoutInfo;

    // font atlas of specific size font
    class TTFLabelAtals {
    public:
        
        TTFLabelAtals(const std::string &, float, LabelLayoutInfo *info);

        
        inline FontAtlas * getFontAtlas() const { return _fontAtlas.get(); }
        inline FontFreeType * getTTF() const { return _ttfFont.get(); }

        float getFontSize() const { return _fontSize; }

        bool init();

    private:
        std::string _fontName;
        float _fontSize = 0.f;
        //weak reference
        LabelLayoutInfo *_info =  nullptr;
        std::shared_ptr<FontAtlas> _fontAtlas;
        std::shared_ptr<FontFreeType> _ttfFont;
        
        friend class TTFLabelAtlasCache;
    };

    class TTFLabelAtlasCache {
    public:

        static TTFLabelAtlasCache* getInstance();
        static void destroyInstance();

        void reset();

        std::shared_ptr<TTFLabelAtals> load(const std::string &font, float fontSize, LabelLayoutInfo* info);

        void unload(TTFLabelAtals *);

    protected:

        std::string cacheKeyFor(const std::string &font, int fontSize, LabelLayoutInfo *info);

        TTFLabelAtlasCache() {}
    private:
#if CC_TTF_LABELATLAS_ENABLE_GC
        std::unordered_map< std::string, std::weak_ptr< TTFLabelAtals>> _cache;
#else
        std::unordered_map< std::string, std::shared_ptr< TTFLabelAtals>> _cache;
#endif

    };

}

#endif
