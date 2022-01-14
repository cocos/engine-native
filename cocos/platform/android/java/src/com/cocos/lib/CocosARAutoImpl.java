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

public class CocosARAutoImpl {
    private static CocosARAPIBase api = null;
    private static CocosARAutoImpl impl = null;

    public static CocosARAutoImpl init() {
        impl = new CocosARAutoImpl();
        if(impl.isHuaweiBrand()) {
            api = new CocosAREngineAPI();
        } else {
            api = new CocosARCoreAPI();
        }
        return impl;
    }

    public static void start(final CocosARAutoImpl impl) {
        api.startSession();
    }
    public static void onDestroy(final CocosARAutoImpl impl) {
        api.closeSession();
    }
    public static void resume(final CocosARAutoImpl impl) {
        api.resumeSession();
    }
    public static void pause(final CocosARAutoImpl impl) {
        api.pauseSession();
    }
    public static void update(final CocosARAutoImpl impl) {
        api.updateSession();
    }

    public static int getAPIState(final CocosARAutoImpl impl) {
        return api.getAPIState();
    }

    public boolean isHuaweiBrand() {
        String brand = android.os.Build.BRAND;
        if(brand.equals("HONOR") || brand.equals("Huawei")) return true;
        return  false;
    }

    //#region ar camera
    public static void setCameraTextureName(final CocosARAutoImpl impl, int id) {
        api.setCameraTextureName(id);
    }

    public static float[] getCameraPose(final CocosARAutoImpl impl) {
        return api.getCameraPose();
    }
    public static float[] getCameraViewMatrix(final CocosARAutoImpl impl) {
        return api.getCameraViewMatrix();
    }
    public static float[] getCameraProjectionMatrix(final CocosARAutoImpl impl) {
        return api.getCameraProjectionMatrix();
    }
    public static float[] getCameraTexCoords(final CocosARAutoImpl impl) {
        return api.getCameraTexCoords();
    }
    //#endregion

    //#region plane detection
    public static void setPlaneDetectionMode(final CocosARAutoImpl impl, int mode) {
        api.setPlaneDetectionMode(mode);
    }

    public static void updatePlaneDetection(final CocosARAutoImpl impl) {
        api.updatePlaneDetection();
    }

    public static float[] getAddedPlanesInfo(final CocosARAutoImpl impl) {
        return api.getAddedPlanesInfo();
    }
    public static int[] getRemovedPlanesInfo(final CocosARAutoImpl impl) {
        return api.getRemovedPlanesInfo();
    }
    public static float[] getUpdatedPlanesInfo(final CocosARAutoImpl impl) {
        return api.getUpdatedPlanesInfo();
    }
    //#endregion
}