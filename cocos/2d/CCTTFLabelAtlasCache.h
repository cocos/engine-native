#pragma once


#include "2d/CCFontFreetype.h"
#include "2d/CCFontAtlas.h"

#include <unordered_map>
#include <memory>

#include "base/ccConfig.h"
#if CC_ENABLE_TTF_LABEL_RENDERER

#define CC_TTF_LABELATLAS_ENABLE_GC 0

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

    private:

        void init();

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