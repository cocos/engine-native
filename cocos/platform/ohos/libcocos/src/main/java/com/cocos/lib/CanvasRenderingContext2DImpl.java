/****************************************************************************
 * Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.
 *
 * http://www.cocos.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ****************************************************************************/

package com.cocos.lib;

import ohos.agp.render.Canvas;
import ohos.agp.render.Paint;
import ohos.agp.render.Path;
import ohos.agp.render.Texture;
import ohos.agp.text.Font;
import ohos.agp.utils.Color;
import ohos.app.Context;
import ohos.global.resource.RawFileEntry;
import ohos.global.resource.Resource;
import ohos.hiviewdfx.HiLog;
import ohos.hiviewdfx.HiLogLabel;
import ohos.media.image.PixelMap;
import ohos.media.image.common.AlphaType;
import ohos.media.image.common.PixelFormat;
import ohos.media.image.common.Rect;

import java.io.File;
import java.io.FileOutputStream;
import java.lang.ref.WeakReference;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.HashMap;

public class CanvasRenderingContext2DImpl {

    private static final String TAG = "CanvasContext2D";
    private static final HiLogLabel LABEL = new HiLogLabel(HiLog.LOG_APP, 0, TAG);

    private static final int TEXT_ALIGN_LEFT = 0;
    private static final int TEXT_ALIGN_CENTER = 1;
    private static final int TEXT_ALIGN_RIGHT = 2;

    private static final int TEXT_BASELINE_TOP = 0;
    private static final int TEXT_BASELINE_MIDDLE = 1;
    private static final int TEXT_BASELINE_BOTTOM = 2;
    private static final int TEXT_BASELINE_ALPHABETIC = 3;

    private static WeakReference<Context> sContext;
    private Paint mTextPaint;
    private Paint mLinePaint;
    private Path mLinePath;
    private Canvas mCanvas = new Canvas();
    private Texture mTexture;
    private int mTextAlign = TEXT_ALIGN_LEFT;
    private int mTextBaseline = TEXT_BASELINE_BOTTOM;
    private int mFillStyleR = 0;
    private int mFillStyleG = 0;
    private int mFillStyleB = 0;
    private int mFillStyleA = 255;

    private int mStrokeStyleR = 0;
    private int mStrokeStyleG = 0;
    private int mStrokeStyleB = 0;
    private int mStrokeStyleA = 255;

    private String mFontName = "Arial";
    private float mFontSize = 40.0f;
    private float mLineWidth = 0.0f;
    private static float _sApproximatingOblique = -0.25f;//please check paint api documentation
    private boolean mIsBoldFont = false;
    private boolean mIsItalicFont = false;
    private boolean mIsObliqueFont = false;
    private boolean mIsSmallCapsFontVariant = false;
    private String mLineCap = "butt";
    private String mLineJoin = "miter";

    private class Size {
        Size(float w, float h) {
            this.width = w;
            this.height = h;
        }

        Size() {
            this.width = 0;
            this.height = 0;
        }

        public float width;
        public float height;
    }

    private class Point {
        Point(float x, float y) {
            this.x = x;
            this.y = y;
        }

        Point() {
            this.x = this.y = 0.0f;
        }

        Point(Point pt) {
            this.x = pt.x;
            this.y = pt.y;
        }

        void set(float x, float y) {
            this.x = x;
            this.y = y;
        }

        public float x;
        public float y;
    }

    static void init(Context context) {
        sContext = new WeakReference<>(context);
    }

    static void destroy() {
        sContext = null;
    }

    private static HashMap<String, Font.Builder> sTypefaceCache = new HashMap<>();

    // url is a full path started with '@assets/'
    private static void loadTypeface(String familyName, String url) {
        Context ctx = sContext.get();
        if (!sTypefaceCache.containsKey(familyName)) {
            try {
                Font.Builder typeface = null;

                if (url.startsWith("/")) {
                    typeface = new Font.Builder(url);
                } else if (ctx != null) {
                    final String prefix = "@assets/";
                    if (url.startsWith(prefix)) {
                        url = url.substring(prefix.length());
                    }
                    // TODO: do not copy file
                    RawFileEntry entry = ctx.getResourceManager().getRawFileEntry(url);
                    File fontTmpFile = File.createTempFile("fontfile", "-tmp");
                    FileOutputStream fontOutputStream = new FileOutputStream(fontTmpFile);
                    Resource resource = entry.openRawFile();
                    byte buf[] = new byte[4096];
                    while (resource.available() > 0) {
                        int readn = resource.read(buf, 0, 4096);
                        if (readn > 0)
                            fontOutputStream.write(buf, 0, readn);
                    }
                    fontOutputStream.close();
                    resource.close();
                    typeface = new Font.Builder(fontTmpFile);
                }

                if (typeface != null) {
                    sTypefaceCache.put(familyName, typeface);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    // REFINE:: native should clear font cache before exiting game.
    private static void clearTypefaceCache() {
        sTypefaceCache.clear();
    }

    private static Paint newPaint(String fontName, int fontSize, boolean enableBold, boolean enableItalic, boolean obliqueFont, boolean smallCapsFontVariant) {
        Paint paint = new Paint();
        paint.setTextSize(fontSize);
        paint.setAntiAlias(true);
        paint.setSubpixelAntiAlias(true);

        String key = fontName;
        if (enableBold) {
            key += "-Bold";
            paint.setFakeBoldText(true);
        }
        if (enableItalic) {
            key += "-Italic";
        }

        Font.Builder typeFace;
        if (sTypefaceCache.containsKey(key)) {
            typeFace = sTypefaceCache.get(key);
        } else {
            typeFace = new Font.Builder(fontName);
            int style = Font.REGULAR;
            typeFace.makeItalic(enableItalic);
            typeFace.setWeight(enableBold ? Font.BOLD : Font.REGULAR);
        }
        paint.setFont(typeFace.build());

        if (obliqueFont) {
            // TODO: skewX
//            paint.setTextSkewX(_sApproximatingOblique);
        }
        return paint;
    }

    private CanvasRenderingContext2DImpl() {
        // Log.d(TAG, "constructor");
    }

    private void recreateBuffer(float w, float h) {
        // Log.d(TAG, "recreateBuffer:" + w + ", " + h);
        if (mTexture != null) {
            mTexture.getPixelMap().release();
        }
        PixelMap.InitializationOptions initializationOptions = new PixelMap.InitializationOptions();
        initializationOptions.alphaType = AlphaType.UNPREMUL;
        initializationOptions.pixelFormat = PixelFormat.ARGB_8888;
        initializationOptions.size = new ohos.media.image.common.Size((int) Math.ceil(w), (int) Math.ceil(h));

        PixelMap pixelMap = PixelMap.create(initializationOptions);
        mTexture = new Texture(pixelMap);
        mCanvas.setTexture(mTexture);
    }

    private void beginPath() {
        if (mLinePath == null) {
            mLinePath = new Path();
        }
        mLinePath.reset();
    }

    private void closePath() {
        mLinePath.close();
    }

    private void moveTo(float x, float y) {
        mLinePath.moveTo(x, y);
    }

    private void lineTo(float x, float y) {
        mLinePath.lineTo(x, y);
    }

    private void stroke() {
        if (mLinePaint == null) {
            mLinePaint = new Paint();
            mLinePaint.setAntiAlias(true);
        }

        if (mLinePath == null) {
            mLinePath = new Path();
        }

        Color strokeColor = new Color(Color.argb(mStrokeStyleA, mStrokeStyleR, mStrokeStyleG, mStrokeStyleB));
        mLinePaint.setColor(strokeColor);
        mLinePaint.setStyle(Paint.Style.STROKE_STYLE);
        mLinePaint.setStrokeWidth(mLineWidth);
        this.setStrokeCap(mLinePaint);
        this.setStrokeJoin(mLinePaint);
        mCanvas.drawPath(mLinePath, mLinePaint);
    }

    private void setStrokeCap(Paint paint) {
        switch (mLineCap) {
            case "butt":
                paint.setStrokeCap(Paint.StrokeCap.BUTT_CAP);
                break;
            case "round":
                paint.setStrokeCap(Paint.StrokeCap.ROUND_CAP);
                break;
            case "square":
                paint.setStrokeCap(Paint.StrokeCap.SQUARE_CAP);
                break;
        }
    }

    private void setStrokeJoin(Paint paint) {
        switch (mLineJoin) {
            case "bevel":
                paint.setStrokeJoin(Paint.Join.BEVEL_JOIN);
                break;
            case "round":
                paint.setStrokeJoin(Paint.Join.ROUND_JOIN);
                break;
            case "miter":
                paint.setStrokeJoin(Paint.Join.MITER_JOIN);
                break;
        }
    }

    private void fill() {
        if (mLinePaint == null) {
            mLinePaint = new Paint();
        }

        if (mLinePath == null) {
            mLinePath = new Path();
        }

        Color fillColor = new Color(Color.argb(mFillStyleA, mFillStyleR, mFillStyleG, mFillStyleB));
        mLinePaint.setColor(fillColor);
        mLinePaint.setStyle(Paint.Style.FILL_STYLE);
        mCanvas.drawPath(mLinePath, mLinePaint);
        // workaround: draw a hairline to cover the border
        mLinePaint.setStrokeWidth(0);
        this.setStrokeCap(mLinePaint);
        this.setStrokeJoin(mLinePaint);
        mLinePaint.setStyle(Paint.Style.STROKE_STYLE);
        mCanvas.drawPath(mLinePath, mLinePaint);
        mLinePaint.setStrokeWidth(mLineWidth);
    }

    private void setLineCap(String lineCap) {
        mLineCap = lineCap;
    }

    private void setLineJoin(String lineJoin) {
        mLineJoin = lineJoin;
    }

    private void saveContext() {
        mCanvas.save();
    }

    private void restoreContext() {
        // If there is no saved state, this method should do nothing.
        if (mCanvas.getSaveCount() > 1) {
            mCanvas.restore();
        }
    }

    private void rect(float x, float y, float w, float h) {
        //        Log.d(TAG, "this: " + this + ", rect: " + x + ", " + y + ", " + w + ", " + h);
        beginPath();
        moveTo(x, y);
        lineTo(x, y + h);
        lineTo(x + w, y + h);
        lineTo(x + w, y);
        closePath();
    }

    private void clearRect(float x, float y, float w, float h) {
        mTexture.getPixelMap().writePixels(Color.TRANSPARENT.getValue());
    }

    private void createTextPaintIfNeeded() {
        if (mTextPaint == null) {
            mTextPaint = newPaint(mFontName, (int) mFontSize, mIsBoldFont, mIsItalicFont, mIsObliqueFont, mIsSmallCapsFontVariant);
        }
    }

    private void fillRect(float x, float y, float w, float h) {
        // Log.d(TAG, "fillRect: " + x + ", " + y + ", " + ", " + w + ", " + h);
        int pixelValue = (mFillStyleA & 0xff) << 24 | (mFillStyleR & 0xff) << 16 | (mFillStyleG & 0xff) << 8 | (mFillStyleB & 0xff);
        int fillSize = (int) (w * h);
        int[] fillColors = new int[fillSize];
        for (int i = 0; i < fillSize; ++i) {
            fillColors[i] = pixelValue;
        }
        Rect region = new Rect((int)x,(int)y, (int)w, (int)h );
        mTexture.getPixelMap().writePixels(fillColors, 0, (int)w, region);
    }

    private void scaleX(Paint textPaint, String text, float maxWidth) {
        if (maxWidth < Float.MIN_VALUE) return;
        float measureWidth = this.measureText(text);
        if ((measureWidth - maxWidth) < Float.MIN_VALUE) return;
        float scaleX = maxWidth / measureWidth;
        // TODO: font scale
//        textPaint.setTextScaleX(scaleX);
    }

    private void fillText(String text, float x, float y, float maxWidth) {
//        Log.d(TAG, "this: " + this + ", fillText: " + text + ", " + x + ", " + y + ", " + ", " + maxWidth);
        createTextPaintIfNeeded();
        Color fillColor = new Color(Color.argb(mFillStyleA, mFillStyleR, mFillStyleG, mFillStyleB));
        mTextPaint.setColor(fillColor);
        mTextPaint.setStyle(Paint.Style.FILL_STYLE);
        scaleX(mTextPaint, text, maxWidth);
        Point pt = convertDrawPoint(new Point(x, y), text);
        mCanvas.drawText(mTextPaint, text, pt.x, pt.y);
    }

    private void strokeText(String text, float x, float y, float maxWidth) {
        // Log.d(TAG, "strokeText: " + text + ", " + x + ", " + y + ", " + ", " + maxWidth);
        createTextPaintIfNeeded();
        Color strokeColor = new Color(Color.argb(mStrokeStyleA, mStrokeStyleR, mStrokeStyleG, mStrokeStyleB));
        mTextPaint.setColor(strokeColor);
        mTextPaint.setStyle(Paint.Style.STROKE_STYLE);
        mTextPaint.setStrokeWidth(mLineWidth);
        scaleX(mTextPaint, text, maxWidth);
        Point pt = convertDrawPoint(new Point(x, y), text);
        mCanvas.drawText(mTextPaint, text, pt.x, pt.y );
    }

    private float measureText(String text) {
        createTextPaintIfNeeded();
        float ret = mTextPaint.measureText(text);
        // Log.d(TAG, "measureText: " + text + ", return: " + ret);
        return ret;
    }

    private void updateFont(String fontName, float fontSize, boolean bold, boolean italic, boolean oblique, boolean smallCaps) {
        // Log.d(TAG, "updateFont: " + fontName + ", " + fontSize);
        mFontName = fontName;
        mFontSize = fontSize;
        mIsBoldFont = bold;
        mIsItalicFont = italic;
        mIsObliqueFont = oblique;
        mIsSmallCapsFontVariant = smallCaps;
        mTextPaint = null; // Reset paint to re-create paint object in createTextPaintIfNeeded
    }

    private void setTextAlign(int align) {
        // Log.d(TAG, "setTextAlign: " + align);
        mTextAlign = align;
    }

    private void setTextBaseline(int baseline) {
        // Log.d(TAG, "setTextBaseline: " + baseline);
        mTextBaseline = baseline;
    }

    private void setFillStyle(float r, float g, float b, float a) {
        // Log.d(TAG, "setFillStyle: " + r + ", " + g + ", " + b + ", " + a);
        mFillStyleR = (int) (r * 255.0f);
        mFillStyleG = (int) (g * 255.0f);
        mFillStyleB = (int) (b * 255.0f);
        mFillStyleA = (int) (a * 255.0f);
    }

    private void setStrokeStyle(float r, float g, float b, float a) {
        // Log.d(TAG, "setStrokeStyle: " + r + ", " + g + ", " + b + ", " + a);
        mStrokeStyleR = (int) (r * 255.0f);
        mStrokeStyleG = (int) (g * 255.0f);
        mStrokeStyleB = (int) (b * 255.0f);
        mStrokeStyleA = (int) (a * 255.0f);
    }

    private void setLineWidth(float lineWidth) {
        mLineWidth = lineWidth;
    }

    private void _fillImageData(byte[] imageData, float imageWidth, float imageHeight, float offsetX, float offsetY) {
        int fillSize = (int) (imageWidth * imageHeight);
        int[] fillColors = new int[fillSize];
        int r, g, b, a;
        for (int i = 0; i < fillSize; ++i) {
            // imageData Pixel (RGBA) -> fillColors int (ARGB)
            r = ((int) imageData[4 * i + 0]) & 0xff;
            g = ((int) imageData[4 * i + 1]) & 0xff;
            b = ((int) imageData[4 * i + 2]) & 0xff;
            a = ((int) imageData[4 * i + 3]) & 0xff;
            fillColors[i] = (a & 0xff) << 24 | (r & 0xff) << 16 | (g & 0xff) << 8 | (b & 0xff);
        }
        Rect dstRect = new Rect((int) offsetX, (int) offsetY, (int) imageWidth, (int) imageHeight);
        mTexture.getPixelMap().writePixels(fillColors, 0, (int) imageWidth, dstRect);
    }

    private Point convertDrawPoint(final Point point, String text) {
        // The parameter 'point' is located at left-bottom position.
        // Need to adjust 'point' according 'text align' & 'text base line'.
        Point ret = new Point(point);
        createTextPaintIfNeeded();
        Paint.FontMetrics fm = mTextPaint.getFontMetrics();
        float width = measureText(text);

        if (mTextAlign == TEXT_ALIGN_CENTER) {
            ret.x -= width / 2;
        } else if (mTextAlign == TEXT_ALIGN_RIGHT) {
            ret.x -= width;
        }

        // Canvas.drawText accepts the y parameter as the baseline position, not the most bottom
        if (mTextBaseline == TEXT_BASELINE_TOP) {
            ret.y += -fm.ascent;
        } else if (mTextBaseline == TEXT_BASELINE_MIDDLE) {
            ret.y += (fm.descent - fm.ascent) / 2 - fm.descent;
        } else if (mTextBaseline == TEXT_BASELINE_BOTTOM) {
            ret.y += -fm.descent;
        }

        return ret;
    }

    private byte[] getDataRef() {
        // Log.d(TAG, "this: " + this + ", getDataRef ...");
        if (mTexture != null && mTexture.getPixelMap() != null) {
            final int len = mTexture.getWidth() * mTexture.getHeight() * 4;
            final byte[] pixels = new byte[len];
            final ByteBuffer buf = ByteBuffer.wrap(pixels);
            buf.order(ByteOrder.nativeOrder());
            mTexture.getPixelMap().readPixels(buf);

            return pixels;
        }
        HiLog.error(LABEL, "getDataRef return null");
        return null;
    }
}
