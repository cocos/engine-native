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

import com.google.ar.core.Anchor;
import com.google.ar.core.ArCoreApk;
import com.google.ar.core.Camera;
import com.google.ar.core.Config;
import com.google.ar.core.Config.InstantPlacementMode;
import com.google.ar.core.DepthPoint;
import com.google.ar.core.Frame;
import com.google.ar.core.Pose;
import com.google.ar.core.HitResult;
import com.google.ar.core.InstantPlacementPoint;
import com.google.ar.core.LightEstimate;
import com.google.ar.core.Plane;
import com.google.ar.core.Point;
import com.google.ar.core.Point.OrientationMode;
import com.google.ar.core.PointCloud;
import com.google.ar.core.Session;
import com.google.ar.core.Trackable;
import com.google.ar.core.TrackingFailureReason;
import com.google.ar.core.TrackingState;
import com.google.ar.core.Coordinates2d;
import com.google.ar.core.exceptions.CameraNotAvailableException;
import com.google.ar.core.exceptions.UnavailableApkTooOldException;
import com.google.ar.core.exceptions.UnavailableArcoreNotInstalledException;
import com.google.ar.core.exceptions.UnavailableDeviceNotCompatibleException;
import com.google.ar.core.exceptions.UnavailableSdkTooOldException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class CocosARCoreAPI implements CocosARAPI {
    private static CocosARCoreAPI api = null;

    private CocosARDisplayRotationHelper mDisplayRotationHelper;

    private Session mSession;
    private Frame mFrame;
    private Camera mCamera;

    private float[] _cameraPose = new float[7];
    private float[] _viewMatrix = new float[16];
    private float[] _projMatrix = new float[16];

    private float[] _quadCoords = {-1f, -1f, -1f, 1f, 1f, -1f, 1f, 1f};
    private float[] _cameraTexCoords = new float[8];

    public static CocosARCoreAPI init() {
        api = new CocosARCoreAPI();
        return api;
    }

    public static void start(final CocosARCoreAPI api) {
        api.createSession();
    }
    public static void onDestroy(final CocosARCoreAPI api) {
        api.closeSession();
    }
    public static void update(final CocosARCoreAPI api) {
        api.updateSession();
        api.updateCameraPose();
        api.updateCameraTexCoords();
    }

    public static void setCameraTextureName(final CocosARCoreAPI api, int id) {
        api.mSession.setCameraTextureName(id);
    }

    public static float[] getCameraPose(final CocosARCoreAPI api) {
        return api._cameraPose;
    }
    public static float[] getCameraViewMatrix(final CocosARCoreAPI api) {
        api.mCamera.getViewMatrix(api._viewMatrix, 0);
        return api._viewMatrix;
    }
    public static float[] getCameraProjectionMatrix(final CocosARCoreAPI api) {
        api.mCamera.getProjectionMatrix(api._projMatrix, 0, 0.01f, 1000.0f);
        return api._projMatrix;
    }
    public static float[] getCameraTexCoords(final CocosARCoreAPI api) {
        return api._cameraTexCoords;
    }

    // for CocosARDisplayRotationHelper 
    public void setDisplayGeometry(int displayRotation, int width, int height) {
        mSession.setDisplayGeometry(displayRotation, width, height);
    }

    private void updateCameraPose() {
        Pose pose = mCamera.getDisplayOrientedPose();
        _cameraPose[0] = pose.tx();
        _cameraPose[1] = pose.ty();
        _cameraPose[2] = pose.tz();
        _cameraPose[3] = pose.qx();
        _cameraPose[4] = pose.qy();
        _cameraPose[5] = pose.qz();
        _cameraPose[6] = pose.qw();
    }

    private void updateCameraTexCoords() {
        if (mFrame.hasDisplayGeometryChanged()) {
            // If display rotation changed (also includes view size change), we need to re-query the UV
            // coordinates for the screen rect, as they may have changed as well.
            mFrame.transformCoordinates2d(
                Coordinates2d.OPENGL_NORMALIZED_DEVICE_COORDINATES,
                _quadCoords,
                Coordinates2d.TEXTURE_NORMALIZED,
                _cameraTexCoords);
        }
    }

    private void createSession() {
        try {
            mSession = new Session(GlobalObject.getActivity());
        } catch (UnavailableArcoreNotInstalledException e) {
            e.printStackTrace();
        } catch (UnavailableApkTooOldException e) {
            e.printStackTrace();
        } catch (UnavailableSdkTooOldException e) {
            e.printStackTrace();
        } catch (UnavailableDeviceNotCompatibleException e) {
            e.printStackTrace();
        }
        
        mDisplayRotationHelper = new CocosARDisplayRotationHelper(GlobalObject.getActivity());

        try {
            mSession.resume();
            CocosActivity activity = (CocosActivity)GlobalObject.getActivity();
            int width = activity.getSurfaceView().getWidth();
            int height = activity.getSurfaceView().getHeight();
            mDisplayRotationHelper.updateViewportChanged(width, height);

        } catch (CameraNotAvailableException e) {
            mSession = null;
            return;
        }
    }

    private void closeSession() {
        mSession.close();
    }

    private void updateSession() {
        mDisplayRotationHelper.updateDisplayGeometry(api);

        try {
            mFrame = mSession.update();
        } catch (CameraNotAvailableException e) {
            e.printStackTrace();
        }

        mCamera = mFrame.getCamera();
    }
}