/****************************************************************************
 Copyright (c) 2022-2023 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.                                                                    \
 ****************************************************************************/

#include <array>
#include <regex>
#include <memory>

#include "base/csscolorparser.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_platform.h"
#include "math/CCMath.h"
#include "base/CCData.h"
#include "platform/CCCanvasRenderingContext2D.h"

//#include "platform/openharmony/OpenHarmonyPlatform.h"

#include <native_drawing/drawing_text_typography.h>
#include <native_drawing/drawing_canvas.h>
#include <native_drawing/drawing_font_collection.h>
#include <native_drawing/drawing_types.h>
#include <native_drawing/drawing_path.h>
#include <native_drawing/drawing_bitmap.h>
#include <native_drawing/drawing_text_declaration.h>
#include <native_drawing/drawing_brush.h>

using namespace cocos2d;
    
enum class TextAlign {
    LEFT,
    CENTER,
    RIGHT
};

enum class TextBaseline {
    TOP,
    MIDDLE,
    BOTTOM,
    ALPHABETIC
};

class ScopedTypography {
public:
    ScopedTypography(OH_Drawing_Typography* typography) :_typegraphy(typography) {}
    ~ScopedTypography() {
        if(_typegraphy) {
            OH_Drawing_DestroyTypography(_typegraphy);
        }
    }
    OH_Drawing_Typography* get() {
        return _typegraphy;
    }
private:
    OH_Drawing_Typography* _typegraphy{nullptr};
};

class CanvasRenderingContext2DImpl {
public:
    using Point   = std::array<float, 2>;
    using Vec2    = std::array<float, 2>;
    using Size    = std::array<float, 2>;
    using Color4F = std::array<float, 4>;

    CanvasRenderingContext2DImpl() {
        _typographyStyle = OH_Drawing_CreateTypographyStyle();
        OH_Drawing_SetTypographyTextDirection(_typographyStyle, TEXT_DIRECTION_LTR);
        OH_Drawing_SetTypographyTextAlign(_typographyStyle, TEXT_ALIGN_LEFT);

        _fontCollection = OH_Drawing_CreateFontCollection();
        _typographyCreate = OH_Drawing_CreateTypographyHandler(_typographyStyle, _fontCollection);
        _textStyle = OH_Drawing_CreateTextStyle();
    }

    ~CanvasRenderingContext2DImpl() {
        if(_typographyStyle) {
            OH_Drawing_DestroyTypographyStyle(_typographyStyle);
            _typographyStyle = nullptr;
        }

        if(_fontCollection) {
            OH_Drawing_DestroyFontCollection(_fontCollection);
        }

        if(_typographyCreate) {
            OH_Drawing_DestroyTypographyHandler(_typographyCreate);
            _typographyCreate = nullptr;
        }

        if(_textStyle) {
            OH_Drawing_DestroyTextStyle(_textStyle);
            _textStyle = nullptr;
        }

        if(_canvas) {
            OH_Drawing_CanvasDestroy(_canvas);
            _canvas = nullptr;
        }

        if(_bitmap) {
            OH_Drawing_BitmapDestroy(_bitmap);
            _bitmap = nullptr;
        }
    }

    void recreateBuffer(float w, float h) {
        _bufferWidth  = w;
        _bufferHeight = h;
        if (_bufferWidth < 1.0F || _bufferHeight < 1.0F) {
            return;
        }

        if (_canvas) {
            OH_Drawing_CanvasDestroy(_canvas);
            _canvas = nullptr;
        }
        if (_bitmap) {
            OH_Drawing_BitmapDestroy(_bitmap);
            _bitmap = nullptr;
        }

        _bufferSize = static_cast<int>(_bufferWidth * _bufferHeight * 4);
        auto *data  = static_cast<uint8_t *>(malloc(sizeof(uint8_t) * _bufferSize));
        memset(data, 0x00, _bufferSize);
        _imageData.fastSet(data, _bufferSize);

        _bitmap = OH_Drawing_BitmapCreate();
        OH_Drawing_BitmapBuild(_bitmap, _bufferWidth, _bufferHeight, &_format);
        _canvas = OH_Drawing_CanvasCreate();
        OH_Drawing_CanvasBind(_canvas, _bitmap);
    }

    void beginPath() {
    }

    void closePath() {
    }

    void moveTo(float x, float y) {
        // MoveToEx(_DC, static_cast<int>(x), static_cast<int>(-(y - _bufferHeight - _fontSize)), nullptr);
        _x = x;
        _y = y;
    }

    void lineTo(float x, float y) {
    }

    void stroke() {
    }

    void saveContext() {
    }

    void restoreContext() {
    }

    void clearRect(float x, float y, float w, float h) {
        if (_bufferWidth < 1.0F || _bufferHeight < 1.0F) {
            return;
        }

        if (_imageData.isNull()) {
            return;
        }

        recreateBuffer(w, h);
    }

    void fillRect(float x, float y, float w, float h) {
        if (_bufferWidth < 1.0F || _bufferHeight < 1.0F) {
            return;
        }
        uint8_t r = static_cast<uint8_t>(_fillStyle[0]);
        uint8_t g = static_cast<uint8_t>(_fillStyle[1]);
        uint8_t b = static_cast<uint8_t>(_fillStyle[2]);
        uint8_t a = static_cast<uint8_t>(_fillStyle[3]);

        OH_Drawing_Path* path = OH_Drawing_PathCreate();
        OH_Drawing_PathMoveTo(path, x, y);
        OH_Drawing_PathLineTo(path, x + w, y);
        OH_Drawing_PathLineTo(path, x + w, y + h);
        OH_Drawing_PathLineTo(path, x, y + h);
        OH_Drawing_PathLineTo(path, x, y);
        OH_Drawing_PathClose(path);
        OH_Drawing_Brush* brush = OH_Drawing_BrushCreate();
        OH_Drawing_BrushSetColor(brush, OH_Drawing_ColorSetArgb(a, r, g, b));
        OH_Drawing_CanvasAttachBrush(_canvas, brush);
        OH_Drawing_CanvasDrawPath(_canvas, path);
    }

    void fillText(const std::string &text, float x, float y, float /*maxWidth*/) {
        if (text.empty() || _bufferWidth < 1.0F || _bufferHeight < 1.0F) {
            return;
        }
        Size  textSize    = {0, 0};
        Point offsetPoint = convertDrawPoint(Point{x, y}, text);
        drawText(text, offsetPoint[0], offsetPoint[1]);
    }

    void strokeText(const std::string &text, float /*x*/, float /*y*/, float /*maxWidth*/) const {
    }

    Size measureText(const std::string &text) {
        auto typography = createTypography(text);
        return std::array<float, 2>{static_cast<float>(OH_Drawing_TypographyGetMaxIntrinsicWidth(typography->get())),
                                    static_cast<float>(OH_Drawing_TypographyGetHeight(typography->get()))};
    }

    void updateFont(const std::string &fontName,
                    float              fontSize,
                    bool               bold,
                    bool               italic,
                    bool               oblique,
                    bool /* smallCaps */) {
        _fontName = fontName;
        _fontSize = static_cast<int>(fontSize);
        std::string fontPath;
        if (!_fontName.empty()) {
            const char* fontFamilies[1];
            fontFamilies[0] = fontName.c_str();
            OH_Drawing_SetTextStyleFontFamilies(_textStyle, 1, fontFamilies);
            OH_Drawing_SetTextStyleLocale(_textStyle, "en");
        }
        if (_fontSize)
            OH_Drawing_SetTextStyleFontSize(_textStyle, _fontSize);
        if (bold)
            OH_Drawing_SetTextStyleFontWeight(_textStyle, FONT_WEIGHT_700);
        else 
            OH_Drawing_SetTextStyleFontWeight(_textStyle, FONT_WEIGHT_400);
        if(italic) 
            OH_Drawing_SetTextStyleFontStyle(_textStyle, FONT_STYLE_ITALIC);
        else 
            OH_Drawing_SetTextStyleFontStyle(_textStyle, FONT_STYLE_NORMAL);
    }

    void setTextAlign(TextAlign align) {
        _textAlign = align;
    }

    void setTextBaseline(TextBaseline baseline) {
        _textBaseLine = baseline;
    }

    void setFillStyle(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        _fillStyle = {static_cast<float>(r), static_cast<float>(g), static_cast<float>(b), static_cast<float>(a)};
        OH_Drawing_SetTextStyleColor(_textStyle, OH_Drawing_ColorSetArgb(a, r, g, b));
    }

    void setStrokeStyle(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        _strokeStyle = {static_cast<float>(r), static_cast<float>(g), static_cast<float>(b), static_cast<float>(a)};
    }

    void setLineWidth(float lineWidth) {
        _lineWidth = lineWidth;
    }

    const Data &getDataRef() const {

        return _imageData;
    }

    void removeCustomFont() {
    }

    // x, y offset value
    int drawText(const std::string &text, float x, float y) {
        auto typography = createTypography(text);
        OH_Drawing_TypographyPaint(typography->get(), _canvas, (double)x, (double)y);
        void* bitmapAddr = OH_Drawing_BitmapGetPixels(_bitmap);
        memcpy(_imageData.getBytes(), bitmapAddr, _bufferSize);
        return 0;
    }

    Size sizeWithText(const wchar_t *pszText, int nLen) {
        return std::array<float, 2>{0.0F, 0.0F};
    }

    void prepareBitmap(int nWidth, int nHeight) {
    }

    void deleteBitmap() {
    }

    void fillTextureData() {
    }

    std::array<float, 2> convertDrawPoint(Point point, const std::string &text) {
        auto typography = createTypography(text);
        Size textSize {static_cast<float>(OH_Drawing_TypographyGetMaxIntrinsicWidth(typography->get())),
                    static_cast<float>(OH_Drawing_TypographyGetHeight(typography->get()))};
        if (_textAlign == TextAlign::CENTER) {
            point[0] -= textSize[0] / 2.0f;
        } else if (_textAlign == TextAlign::RIGHT) {
            point[0] -= textSize[0];
        }
        double alphabeticBaseLine = OH_Drawing_TypographyGetAlphabeticBaseline(typography->get());
        if (_textBaseLine == TextBaseline::TOP) {
            //point[1] += -alphabeticBaseLine;
        } else if (_textBaseLine == TextBaseline::MIDDLE) {
            point[1] += -textSize[1] / 2.0f;
        } else if (_textBaseLine == TextBaseline::BOTTOM) {
            point[1] += -textSize[1];
        } else if (_textBaseLine == TextBaseline::ALPHABETIC) {
            //GetTextMetrics(_DC, &_tm);
            //point[1] -= _tm.tmAscent;
            point[1] -= alphabeticBaseLine;
        }
        return point;
    }

    std::unique_ptr<ScopedTypography> createTypography(const std::string &text) {
        OH_Drawing_TypographyHandlerPushTextStyle(_typographyCreate, _textStyle);
        OH_Drawing_TypographyHandlerAddText(_typographyCreate, text.c_str());
        OH_Drawing_TypographyHandlerPopTextStyle(_typographyCreate);
        OH_Drawing_Typography* typography = OH_Drawing_CreateTypography(_typographyCreate);
        OH_Drawing_TypographyLayout(typography, _bufferWidth);
        return std::make_unique<ScopedTypography>(typography);
    }

    void fill() {
    }

    void setLineCap(const std::string &lineCap) {
    }

    void setLineJoin(const std::string &lineJoin) {
    }

    void fillImageData(const Data & /* imageData */,
                    float /* imageWidth */,
                    float /* imageHeight */,
                    float /* offsetX */,
                    float /* offsetY */) {
    }

    void strokeText(const std::string & /* text */,
                    float /* x */,
                    float /* y */,
                    float /* maxWidth */) {
    }

    void rect(float /* x */,
                float /* y */,
                float /* w */,
                float /* h */) {
    }

    void updateData() {
    }

private:
    int32_t _x{0};
    int32_t _y{0};
    int32_t _lineCap{0};
    int32_t _lineJoin{0};
    
    OH_Drawing_Bitmap* _bitmap{nullptr};
    OH_Drawing_BitmapFormat _format {COLOR_FORMAT_RGBA_8888, ALPHA_FORMAT_OPAQUE};
    OH_Drawing_Canvas* _canvas{nullptr};
    OH_Drawing_TypographyStyle* _typographyStyle{nullptr};
    OH_Drawing_TypographyCreate* _typographyCreate{nullptr};
    OH_Drawing_FontCollection* _fontCollection{nullptr};
    OH_Drawing_TextStyle* _textStyle{nullptr};
    Data    _imageData;
    std::string _curFontPath;
    int         _savedDC{0};
    float       _lineWidth{0.0F};
    float       _bufferWidth{0.0F};
    float       _bufferHeight{0.0F};
    int32_t     _bufferSize{0};

    std::string      _fontName;
    int                _fontSize{0};
    Size               _textSize;
    TextAlign          _textAlign{TextAlign::CENTER};
    TextBaseline       _textBaseLine{TextBaseline::TOP};
    Color4F            _fillStyle{0};
    Color4F            _strokeStyle{0};
};

NS_CC_BEGIN

CanvasGradient::CanvasGradient()
{
    // SE_LOGD("CanvasGradient constructor: %p\n", this);
}

CanvasGradient::~CanvasGradient()
{
    // SE_LOGD("CanvasGradient destructor: %p\n", this);
}

void CanvasGradient::addColorStop(float offset, const std::string& color)
{
    // SE_LOGD("CanvasGradient::addColorStop: %p\n", this);
}

// CanvasRenderingContext2D

CanvasRenderingContext2D::CanvasRenderingContext2D(float width, float height)
: __width(width)
, __height(height)
{
    // SE_LOGD("CanvasRenderingContext2D constructor: %p, width: %f, height: %f\n", this, width, height);
    _impl = new CanvasRenderingContext2DImpl();
    recreateBufferIfNeeded();
}

CanvasRenderingContext2D::~CanvasRenderingContext2D()
{
    // SE_LOGD("CanvasRenderingContext2D destructor: %p\n", this);
    delete _impl;
}

void CanvasRenderingContext2D::clearRect(float x, float y, float width, float height)
{
    // SE_LOGD("CanvasRenderingContext2D::clearRect: %p, %f, %f, %f, %f\n", this, x, y, width, height);
    recreateBufferIfNeeded();
    _impl->clearRect(x, y, width, height);
}

void CanvasRenderingContext2D::fillRect(float x, float y, float width, float height)
{
    recreateBufferIfNeeded();
    _impl->fillRect(x, y, width, height);

    if (_canvasBufferUpdatedCB != nullptr)
        _canvasBufferUpdatedCB(_impl->getDataRef());
}

void CanvasRenderingContext2D::fillText(const std::string& text, float x, float y, float maxWidth)
{
    // SE_LOGD("CanvasRenderingContext2D::fillText: %s, %f, %f, %f\n", text.c_str(), x, y, maxWidth);
    if (text.empty())
        return;
    recreateBufferIfNeeded();
    _impl->fillText(text, x, y, maxWidth);

    if (_canvasBufferUpdatedCB != nullptr)
        _canvasBufferUpdatedCB(_impl->getDataRef());
}

void CanvasRenderingContext2D::strokeText(const std::string& text, float x, float y, float maxWidth)
{
    // SE_LOGD("CanvasRenderingContext2D::strokeText: %s, %f, %f, %f\n", text.c_str(), x, y, maxWidth);
    if (text.empty())
        return;
    recreateBufferIfNeeded();
    _impl->strokeText(text, x, y, maxWidth);

   if (_canvasBufferUpdatedCB != nullptr)
       _canvasBufferUpdatedCB(_impl->getDataRef());
}

cocos2d::Size CanvasRenderingContext2D::measureText(const std::string& text)
{
    // SE_LOGD("CanvasRenderingContext2D::measureText: %s\n", text.c_str());
    auto s = _impl->measureText(text);
    s[0] = ceil(s[0] * 100) / 100;
    s[1] = ceil(s[1] * 100) / 100;
    return cocos2d::Size(s[0], s[1]);
}

CanvasGradient* CanvasRenderingContext2D::createLinearGradient(float x0, float y0, float x1, float y1)
{
    return nullptr;
}

void CanvasRenderingContext2D::save()
{
    _impl->saveContext();
}

void CanvasRenderingContext2D::beginPath()
{
    _impl->beginPath();
}

void CanvasRenderingContext2D::closePath()
{
    _impl->closePath();
}

void CanvasRenderingContext2D::moveTo(float x, float y)
{
    _impl->moveTo(x, y);
}

void CanvasRenderingContext2D::lineTo(float x, float y)
{
    _impl->lineTo(x, y);
}

void CanvasRenderingContext2D::stroke()
{
    _impl->stroke();

    if (_canvasBufferUpdatedCB != nullptr)
        _canvasBufferUpdatedCB(_impl->getDataRef());
}

void CanvasRenderingContext2D::restore()
{
    _impl->restoreContext();
}

void CanvasRenderingContext2D::setCanvasBufferUpdatedCallback(const CanvasBufferUpdatedCallback& cb)
{
    _canvasBufferUpdatedCB = cb;
}

void CanvasRenderingContext2D::setPremultiply(bool multiply)
{
    _premultiply = multiply;
}

void CanvasRenderingContext2D::set__width(float width)
{
    // SE_LOGD("CanvasRenderingContext2D::set__width: %f\n", width);
    __width = width;
    _isBufferSizeDirty = true;
    recreateBufferIfNeeded();
}

void CanvasRenderingContext2D::set__height(float height)
{
    // SE_LOGD("CanvasRenderingContext2D::set__height: %f\n", height);
    __height = height;
    _isBufferSizeDirty = true;
    recreateBufferIfNeeded();
}

void CanvasRenderingContext2D::set_lineWidth(float lineWidth)
{
    _lineWidth = lineWidth;
    _impl->setLineWidth(lineWidth);
}

void CanvasRenderingContext2D::set_lineCap(const std::string& lineCap)
{
    if(lineCap.empty()) return ;
    _impl->setLineCap(lineCap);
}

void CanvasRenderingContext2D::set_lineJoin(const std::string& lineJoin)
{
    if(lineJoin.empty()) return ;
    _impl->setLineJoin(lineJoin);
}


void CanvasRenderingContext2D::fill()
{
    _impl->fill();

    if (_canvasBufferUpdatedCB != nullptr)
        _canvasBufferUpdatedCB(_impl->getDataRef());
}

void CanvasRenderingContext2D::rect(float x, float y, float width, float height)
{
    // SE_LOGD("CanvasRenderingContext2D::rect: %p, %f, %f, %f, %f\n", this, x, y, width, height);
    recreateBufferIfNeeded();
    _impl->rect(x, y, width, height);
}

/*
 * support format e.g.: "oblique bold small-caps 18px Arial"
 *                      "italic bold small-caps 25px Arial"
 *                      "italic 25px Arial"
 * */
void CanvasRenderingContext2D::set_font(const std::string& font)
{
    if (_font != font) {
        _font = font;
        std::string fontName = "sans-serif";
        std::string fontSizeStr = "30";
        std::regex re(R"(\s*((\d+)([\.]\d+)?)px\s+([^\r\n]*))");
        std::match_results<std::string::const_iterator> results;
        if (std::regex_search(_font.cbegin(), _font.cend(), results, re)) {
            fontSizeStr = results[2].str();
            // support get font name from `60px American` or `60px "American abc-abc_abc"`
            // support get font name contain space,example `times new roman`
            // if regex rule that does not conform to the rules,such as Chinese,it defaults to sans-serif
            std::match_results<std::string::const_iterator> fontResults;
            std::regex fontRe(R"(([\w\s-]+|"[\w\s-]+"$))");
            std::string tmp(results[4].str());
            if (std::regex_match(tmp, fontResults, fontRe)) {
                fontName = results[4].str();
            }
        }

        double fontSize = atof(fontSizeStr.c_str());
        bool isBold = font.find("bold", 0) != std::string::npos || font.find("Bold", 0) != std::string::npos;
        bool isItalic = font.find("italic", 0) != std::string::npos || font.find("Italic", 0) != std::string::npos;
        bool isSmallCaps = font.find("small-caps", 0) != std::string::npos || font.find("Small-Caps") != std::string::npos;
        bool isOblique = font.find("oblique", 0) != std::string::npos || font.find("Oblique", 0) != std::string::npos;
        //font-style: italic, oblique, normal
        //font-weight: normal, bold
        //font-variant: normal, small-caps
        _impl->updateFont(fontName, fontSize, isBold, isItalic, isOblique, isSmallCaps);
    }
}

void CanvasRenderingContext2D::set_textAlign(const std::string& textAlign)
{
    // SE_LOGD("CanvasRenderingContext2D::set_textAlign: %s\n", textAlign.c_str());
    if (textAlign == "left") {
        _impl->setTextAlign(TextAlign::LEFT);
    } else if (textAlign == "center" || textAlign == "middle") {
        _impl->setTextAlign(TextAlign::CENTER);
    } else if (textAlign == "right") {
        _impl->setTextAlign(TextAlign::RIGHT);
    } else {
        CC_ASSERT(false);
    }
}

void CanvasRenderingContext2D::set_textBaseline(const std::string& textBaseline)
{
    // SE_LOGD("CanvasRenderingContext2D::set_textBaseline: %s\n", textBaseline.c_str());
    if (textBaseline == "top") {
        _impl->setTextBaseline(TextBaseline::TOP);
    } else if (textBaseline == "middle") {
        _impl->setTextBaseline(TextBaseline::MIDDLE);
    } else if (textBaseline == "bottom") //REFINE:, how to deal with alphabetic, currently we handle it as bottom mode.
    {
        _impl->setTextBaseline(TextBaseline::BOTTOM);
    } else if (textBaseline == "alphabetic") {
        _impl->setTextBaseline(TextBaseline::ALPHABETIC);
    } else {
        CC_ASSERT(false);
    }
}

void CanvasRenderingContext2D::set_fillStyle(const std::string& fillStyle)
{
    CSSColorParser::Color color = CSSColorParser::parse(fillStyle);
    _impl->setFillStyle(color.r, color.g, color.b, static_cast<uint8_t>(color.a * 255));
    // SE_LOGD("CanvasRenderingContext2D::set_fillStyle: %s, (%d, %d, %d, %f)\n", fillStyle.c_str(), color.r, color.g, color.b, color.a);
}

void CanvasRenderingContext2D::set_strokeStyle(const std::string& strokeStyle)
{
    CSSColorParser::Color color = CSSColorParser::parse(strokeStyle);
    _impl->setStrokeStyle(color.r, color.g, color.b, static_cast<uint8_t>(color.a * 255));
}

void CanvasRenderingContext2D::set_globalCompositeOperation(const std::string& globalCompositeOperation)
{
    // SE_LOGE("%s isn't implemented!\n", __FUNCTION__);
}

void CanvasRenderingContext2D::_fillImageData(const Data& imageData, float imageWidth, float imageHeight, float offsetX, float offsetY)
{
    _impl->fillImageData(imageData, imageWidth, imageHeight, offsetX, offsetY);
    if (_canvasBufferUpdatedCB != nullptr)
        _canvasBufferUpdatedCB(_impl->getDataRef());
}
// transform
//REFINE:

void CanvasRenderingContext2D::translate(float x, float y)
{
    // SE_LOGE("%s isn't implemented!\n", __FUNCTION__);
}

void CanvasRenderingContext2D::scale(float x, float y)
{
    // SE_LOGE("%s isn't implemented!\n", __FUNCTION__);
}

void CanvasRenderingContext2D::rotate(float angle)
{
    // SE_LOGE("%s isn't implemented!\n", __FUNCTION__);
}

void CanvasRenderingContext2D::transform(float a, float b, float c, float d, float e, float f)
{
    // SE_LOGE("%s isn't implemented!\n", __FUNCTION__);
}

void CanvasRenderingContext2D::setTransform(float a, float b, float c, float d, float e, float f)
{
    // SE_LOGE("%s isn't implemented!\n", __FUNCTION__);
}

void CanvasRenderingContext2D::recreateBufferIfNeeded()
{
    if (_isBufferSizeDirty) {
        _isBufferSizeDirty = false;
        // SE_LOGD("Recreate buffer %p, w: %f, h:%f\n", this, __width, __height);
        _impl->recreateBuffer(__width, __height);
        if (_canvasBufferUpdatedCB != nullptr)
            _canvasBufferUpdatedCB(_impl->getDataRef());
    }
}

NS_CC_END