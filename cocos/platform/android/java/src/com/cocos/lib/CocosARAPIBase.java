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

import java.util.EnumSet;

public abstract class CocosARAPIBase {
    // ar camera
    protected int mTextureId = 0;
    protected float mNearClipPlane = 0.01F;
    protected float mFarClipPlane = 1000F;
    protected float[] mCameraPose = new float[7];
    protected float[] mViewMatrix = new float[16];
    protected float[] mProjMatrix = new float[16];
    protected float[] mCameraTexCoords = new float[8];

    // plane detection
    public enum PlaneDetectionMode {
        HORIZONTAL_UPWARD, HORIZONTAL_DOWNWARD, VERTICAL;

        public static final EnumSet<PlaneDetectionMode> ALL = EnumSet.allOf(PlaneDetectionMode.class);
    }
    protected EnumSet<PlaneDetectionMode> mPlaneDetectionMode = EnumSet.of(PlaneDetectionMode.HORIZONTAL_UPWARD, PlaneDetectionMode.VERTICAL);
    protected boolean mEnablePlaneDetection = false;
    protected boolean mEnablePolygonPlane = false;
    protected int mMaxPlaneProcessCount =  5;

    public abstract void startSession();
    public abstract void closeSession();
    public abstract void resumeSession();
    public abstract void pauseSession();
    public abstract void updateSession();
    // -1: not started, 0: arkit, 1: arcore, 2: arengine
    public abstract int getAPIState();

    public abstract float[] getCameraPose();
    public abstract float[] getCameraViewMatrix();
    public abstract float[] getCameraProjectionMatrix();
    public abstract float[] getCameraTexCoords();
    public abstract void setDisplayGeometry(int displayRotation, int width, int height);
    public void setCameraTextureName(int id) {
        mTextureId = id;
    }
    public void setCameraClipPlane(float near, float far) {
        mNearClipPlane = near;
        mFarClipPlane = far;
    }

    //#region plane detection
    /**
     * set plane detection mode
     * @param mode HORIZONTAL_UPWARD(1) HORIZONTAL_DOWNWARD(2) VERTICAL(4)
     */
    public void setPlaneDetectionMode(int mode) {
        mPlaneDetectionMode.removeAll(PlaneDetectionMode.ALL);
        if((mode & 1) == 1) mPlaneDetectionMode.add(PlaneDetectionMode.HORIZONTAL_UPWARD);

        if((mode & 2) == 1) mPlaneDetectionMode.add(PlaneDetectionMode.HORIZONTAL_DOWNWARD);

        if((mode & 4) == 1) mPlaneDetectionMode.add(PlaneDetectionMode.VERTICAL);
    }

    public void enablePlaneDetection(boolean isEnable) {
        mEnablePlaneDetection = isEnable;
    }
    public void setMaxPlaneProcessCount(int count) { mMaxPlaneProcessCount = count; }
    public abstract void updatePlaneDetection();
    public abstract float[] getAddedPlanesInfo();
    public abstract int[] getRemovedPlanesInfo();
    public abstract float[] getUpdatedPlanesInfo();
    //#endregion
}