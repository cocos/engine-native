/****************************************************************************
 * Copyright (c) 2021 Xiamen Yaji Software Co., Ltd.
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

import android.content.Context;
import android.hardware.display.DisplayManager;
import android.hardware.display.DisplayManager.DisplayListener;
import android.view.Display;
import android.view.WindowManager;

public class CocosARDisplayRotationHelper implements DisplayListener {
    private boolean mViewportChanged;

    private int mViewportWidth;

    private int mViewportHeight;

    private final Context mContext;

    private final Display mDisplay;

    /**
     * Constructs the DisplayRotationHelper but does not register the listener yet.
     *
     * @param context the Android {@link Context}.
     */
    public CocosARDisplayRotationHelper(Context context) {
        mContext = context;
        mDisplay = ((WindowManager)context.getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay();
    }

    /**
     * Registers the display listener. This method should be called when activity is onResume.
     */
    public void registerDisplayListener() {
        ((DisplayManager)mContext.getSystemService(Context.DISPLAY_SERVICE)).registerDisplayListener(this, null);
    }

    /**
     * Unregisters the display listener. This method should be called when activity is onPause.
     */
    public void unregisterDisplayListener() {
        ((DisplayManager)mContext.getSystemService(Context.DISPLAY_SERVICE)).unregisterDisplayListener(this);
    }

    /**
     * When the device rotates, you need to update the viewport size and the sign of whether the
     * device color has rotated, so that the display geometry information of arsession can be updated correctly.
     * This method should be called when activity is onSurfaceChanged.
     *
     * @param width the updated width of the surface.
     * @param height the updated height of the surface.
     */
    public void updateViewportChanged(int width, int height) {
        mViewportWidth = width;
        mViewportHeight = height;
        mViewportChanged = true;
    }

    /**
     * Updates the session display geometry if a change was posted either by {@link
     * #onSurfaceChanged(int, int)} call or by {@link #onDisplayChanged(int)} system callback. This
     * function should be called explicitly before each call to {@link Session#update()}. This
     * function will also clear the 'pending update' (viewportChanged) flag.
     *
     * @param session the {@link Session} object to update if display geometry changed.
     */
    public void updateDisplayGeometry(CocosARAPI api) {
        if (mViewportChanged) {
            int displayRotation = mDisplay.getRotation();
            api.setDisplayGeometry(displayRotation, mViewportWidth, mViewportHeight);
            mViewportChanged = false;
        }
    }

    @Override
    public void onDisplayAdded(int displayId) {
    }

    @Override
    public void onDisplayRemoved(int displayId) {
    }

    @Override
    public void onDisplayChanged(int displayId) {
        mViewportChanged = true;
    }
}