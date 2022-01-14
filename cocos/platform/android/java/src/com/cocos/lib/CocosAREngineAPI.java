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

import com.huawei.hiar.AREnginesApk;
import com.huawei.hiar.ARCamera;
//import com.huawei.hiar.Config;
//import com.huawei.hiar.Config.InstantPlacementMode;
import com.huawei.hiar.ARConfigBase;
import com.huawei.hiar.ARWorldTrackingConfig;
//import com.huawei.hiar.DepthPoint;
import com.huawei.hiar.ARFrame;
import com.huawei.hiar.ARPose;
//import com.huawei.hiar.InstantPlacementPoint;
//import com.huawei.hiar.LightEstimate;
import com.huawei.hiar.ARPlane;
import com.huawei.hiar.ARPlane.PlaneType;
//import com.huawei.hiar.Point.OrientationMode;
//import com.huawei.hiar.PointCloud;
import com.huawei.hiar.ARSession;
import com.huawei.hiar.ARTrackable;
//import com.huawei.hiar.TrackingFailureReason;
//import com.huawei.hiar.TrackingState;
//import com.huawei.hiar.Coordinates2d;
import com.huawei.hiar.exceptions.ARCameraNotAvailableException;
import com.huawei.hiar.exceptions.ARUnSupportedConfigurationException;
import com.huawei.hiar.exceptions.ARUnavailableClientSdkTooOldException;
import com.huawei.hiar.exceptions.ARUnavailableServiceApkTooOldException;
import com.huawei.hiar.exceptions.ARUnavailableServiceNotInstalledException;
//import com.huawei.hiar.exceptions.UnavailableApkTooOldException;
//import com.huawei.hiar.exceptions.UnavailableArcoreNotInstalledException;
//import com.huawei.hiar.exceptions.UnavailableDeviceNotCompatibleException;
//import com.huawei.hiar.exceptions.UnavailableSdkTooOldException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.List;

import android.app.Activity;
import android.content.Intent;
import android.widget.Toast;
import android.util.Log;

public class CocosAREngineAPI extends CocosARAPIBase {
    private static final String TAG = CocosAREngineAPI.class.getSimpleName();
    private static CocosAREngineAPI api = null;
    
    private CocosARDisplayRotationHelper mDisplayRotationHelper;
    private CocosActivity mActivity;
    private String errorMessage = null;

    private ARSession mSession;
    private ARFrame mFrame;
    private ARCamera mCamera;

    //private float[] mCameraPose = new float[7];
    //private float[] mViewMatrix = new float[16];
    //private float[] mProjMatrix = new float[16];

    private float[] mQuadCoords = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f};
    //private float[] mCameraTexCoords = new float[8];
    private FloatBuffer mQuadCoordsBuffer;
    private FloatBuffer mTexCoordsBuffer;

    // requestInstall(Activity, true) will triggers installation of
    // Google Play Services for AR if necessary.
    private boolean mUserRequestedInstall = true;
    private boolean mActive;

    //private int mTextureId = 0;
    private boolean isRemindInstall = false;

    // plane feature
    private final static int PLANE_INFOS_SIZE = 12;
    //private int planesMaxSize = 5;
    private int planeTag = 0;
    private final HashMap<Integer, ARPlane> planesMap = new HashMap<>();
    private final HashMap<ARPlane, Integer> planesIndexMap = new HashMap<>();
    private List<Integer> mAddedPlanes = new ArrayList<>();
    private List<Integer> mRemovedPlanes = new ArrayList<>();
    private List<Integer> mUpdatedPlanes = new ArrayList<>();

    public static CocosAREngineAPI init() {
        api = new CocosAREngineAPI();
        return api;
    }

    public static void start(final CocosAREngineAPI api) {
        api.checkCamera();
        //if (api.checkSupportAndUpdate() > 0) {
            api.startSession();
        //}
    }
    public static void onDestroy(final CocosAREngineAPI api) {
        api.closeSession();
    }
    public static void resume(final CocosAREngineAPI api) {
        api.checkCamera();
        //if (api.checkSupportAndUpdate() > 0) {
            api.startSession();
        //}
    }
    public static void pause(final CocosAREngineAPI api) {
        api.pauseSession();
    }
    public static void beforeUpdate(final CocosAREngineAPI api) {
        if (api.mSession == null) return;
        //api.onDrawFrame();
    }
    public static void update(final CocosAREngineAPI api) {
        api.updateSession();
    }

    public static boolean checkStart(final CocosAREngineAPI api) {
        if (api != null && api.mSession != null && api.mCamera != null) {
            return true;
        }
        return false;
    }

    public static void setCameraTextureName(final CocosAREngineAPI api, int id) {
        //api.mSession.setCameraTextureName(id);
        api.mTextureId = id;
    }

    public static float[] getCameraPose(final CocosAREngineAPI api) {
        return api.mCameraPose;
    }
    public static float[] getCameraViewMatrix(final CocosAREngineAPI api) {
        api.mCamera.getViewMatrix(api.mViewMatrix, 0);
        return api.mViewMatrix;
    }
    public static float[] getCameraProjectionMatrix(final CocosAREngineAPI api) {
        if (api.mSession != null && api.mCamera != null) api.mCamera.getProjectionMatrix(api.mProjMatrix, 0, 0.01f, 1000.0f);
        return api.mProjMatrix;
    }
    public static float[] getCameraTexCoords(final CocosAREngineAPI api) {
        api.updateCameraTexCoords();
        return api.mCameraTexCoords;
    }

    // plane feature
    public static void updatePlanesInfo(final CocosAREngineAPI api) {
        api.updatePlaneDetection();
    }
    public static float[] getAddedPlanesInfo(final CocosAREngineAPI api) {
        return api.getPlanesInfoFromList(api.mAddedPlanes);
    }
    public static int[] getRemovedPlanesInfo(final CocosAREngineAPI api) {
        int size = api.mRemovedPlanes.size();
        //int[] result = new int[size];
        int[] result = new int[5];
        Integer[] temp = api.mRemovedPlanes.toArray(new Integer[size]);
        //size = size > 5 ? 5 : size; 
        //for (int n = 0; n < size; ++n) {
        for (int n = 0; n < 5; ++n) {
            if( n < size)
                result[n] = temp[n];
            else
                result[n] = -1;
        }
        return result;
    }
    public static float[] getUpdatedPlanesInfo(final CocosAREngineAPI api) {
        return api.getPlanesInfoFromList(api.mUpdatedPlanes);
    }
    public static int getAddedPlanesCount(final CocosAREngineAPI api) {
        return api.mAddedPlanes.size();
    }
    public static int getRemovedPlanesCount(final CocosAREngineAPI api) {
        return api.mRemovedPlanes.size();
    }
    public static int getUpdatedPlanesCount(final CocosAREngineAPI api) {
        return api.mUpdatedPlanes.size();
    }

    // for CocosARDisplayRotationHelper
    @Override
    public void setDisplayGeometry(int displayRotation, int width, int height) {
        mSession.setDisplayGeometry(displayRotation, width, height);
    }

    private void updateCameraPose() {
        if(mCamera == null ) return;

        ARPose pose = mCamera.getDisplayOrientedPose();
        mCameraPose[0] = pose.tx();
        mCameraPose[1] = pose.ty();
        mCameraPose[2] = pose.tz();
        mCameraPose[3] = pose.qx();
        mCameraPose[4] = pose.qy();
        mCameraPose[5] = pose.qz();
        mCameraPose[6] = pose.qw();
    }

    private void updateCameraTexCoords() {
        if (mFrame.hasDisplayGeometryChanged()) {
            // If display rotation changed (also includes view size change), we need to re-query the UV
            // coordinates for the screen rect, as they may have changed as well.

            mFrame.transformDisplayUvCoords(mQuadCoordsBuffer, mTexCoordsBuffer);
            //mCameraTexCoords = mTexCoordsBuffer.array();
            //System.arraycopy(mCameraTexCoords, 0, mTexCoordsBuffer.array(), 0, 8);
            mCameraTexCoords[0] = mTexCoordsBuffer.get(0);
            mCameraTexCoords[1] = mTexCoordsBuffer.get(1);
            mCameraTexCoords[2] = mTexCoordsBuffer.get(2);
            mCameraTexCoords[3] = mTexCoordsBuffer.get(3);
            mCameraTexCoords[4] = mTexCoordsBuffer.get(4);
            mCameraTexCoords[5] = mTexCoordsBuffer.get(5);
            mCameraTexCoords[6] = mTexCoordsBuffer.get(6);
            mCameraTexCoords[7] = mTexCoordsBuffer.get(7);
        }
    }

    private void checkCamera() {
        Activity activity = GlobalObject.getActivity();
        /*
        if (!CocosARCameraPermissionHelper.hasCameraPermission(activity)) {
            CocosARCameraPermissionHelper.requestCameraPermission(activity);
        }//*/
    }

    private boolean arEngineAbilityCheck() {
        Activity activity = GlobalObject.getActivity();
        boolean isInstallArEngineApk = AREnginesApk.isAREngineApkReady(activity);
        if (!isInstallArEngineApk && isRemindInstall) {
            Toast.makeText(activity, "Please agree to install.", Toast.LENGTH_LONG).show();
            activity.finish();
        }
        Log.d(TAG, "Is Install AR Engine Apk: " + isInstallArEngineApk);
        if (!isInstallArEngineApk) {
            activity.startActivity(new Intent(activity, CocosAREngineServerConnectActivity.class));
            isRemindInstall = true;
        }
        return AREnginesApk.isAREngineApkReady(activity);
    }

    @Override
    public void startSession() {
        if (mActivity == null) {
            mActivity = (CocosActivity) GlobalObject.getActivity();
        }
        errorMessage = null;
        if (mSession == null) {
            try {
                if (!arEngineAbilityCheck()) {
                    mActivity.finish();
                    return;
                }

                mSession = new ARSession(mActivity);
                ARWorldTrackingConfig config = new ARWorldTrackingConfig(mSession);
                config.setFocusMode(ARConfigBase.FocusMode.AUTO_FOCUS);
                mSession.configure(config);

            } catch (Exception capturedException) {
                setMessageWhenError(capturedException);
            }
            if (errorMessage != null) {
                closeSession();
                return;
            }
        }

        if (mDisplayRotationHelper == null) {
            mDisplayRotationHelper = new CocosARDisplayRotationHelper(GlobalObject.getActivity());
        }
        mDisplayRotationHelper.registerDisplayListener();

        initBuffers();

        try {
            mSession.resume();
            int width = mActivity.getSurfaceView().getWidth();
            int height = mActivity.getSurfaceView().getHeight();
            mDisplayRotationHelper.updateViewportChanged(width, height);
        } catch (ARCameraNotAvailableException e) {
            mSession = null;
            return;
        }
    }

    @Override
    public void closeSession() {
        if (mSession != null) {
            mDisplayRotationHelper.unregisterDisplayListener();
            mSession.stop();
            mSession = null;
        }
    }

    @Override
    public void resumeSession() {
        if (mActivity == null) {
            mActivity = (CocosActivity) GlobalObject.getActivity();
        }
        errorMessage = null;
        if (mSession == null) {
            try {
                if (!arEngineAbilityCheck()) {
                    mActivity.finish();
                    return;
                }

                mSession = new ARSession(mActivity);
                ARWorldTrackingConfig config = new ARWorldTrackingConfig(mSession);
                config.setFocusMode(ARConfigBase.FocusMode.AUTO_FOCUS);
                mSession.configure(config);

            } catch (Exception capturedException) {
                setMessageWhenError(capturedException);
            }
            if (errorMessage != null) {
                closeSession();
                return;
            }
        }

        if (mDisplayRotationHelper == null) {
            mDisplayRotationHelper = new CocosARDisplayRotationHelper(GlobalObject.getActivity());
        }
        mDisplayRotationHelper.registerDisplayListener();

        initBuffers();

        try {
            mSession.resume();
            int width = mActivity.getSurfaceView().getWidth();
            int height = mActivity.getSurfaceView().getHeight();
            mDisplayRotationHelper.updateViewportChanged(width, height);

        } catch (ARCameraNotAvailableException e) {
            mSession = null;
            return;
        }
    }

    @Override
    public void pauseSession() {
        if (mSession != null) {
            mDisplayRotationHelper.unregisterDisplayListener();
            mSession.pause();
        }
    }

    @Override
    public void updateSession() {
        if (mSession == null) return;

        mDisplayRotationHelper.updateDisplayGeometry(this);

        try {
            mSession.setCameraTextureName(mTextureId);
            mFrame = mSession.update();
            mCamera = mFrame.getCamera();
            updateCameraPose();
        } catch (ARCameraNotAvailableException e) {
            e.printStackTrace();
        }
    }

    @Override
    public int getAPIState() {
        if (mSession != null && mCamera != null) {
            return 2;
        }
        return -1;
    }

    private void initBuffers() {
        /*
        The reason for creating a ByteBuffer first is that
        you want to use the allocateDirect call to create a direct byte buffer,
        which benefits from the accelerated operations.
        You then create a FloatBuffer from this that shares the same memory.
        The FloatBuffer doesn't itself have an allocateDirect method for some reason,
        which is why you have to go via ByteBuffer.
        */
        ByteBuffer quadCoordsByteBuffer = ByteBuffer.allocateDirect(32);
        quadCoordsByteBuffer.order(ByteOrder.nativeOrder());
        mQuadCoordsBuffer = quadCoordsByteBuffer.asFloatBuffer();
        mQuadCoordsBuffer.put(mQuadCoords);
        mQuadCoordsBuffer.position(0);
        ByteBuffer texCoordsByteBuffer = ByteBuffer.allocateDirect(32);
        texCoordsByteBuffer.order(ByteOrder.nativeOrder());
        mTexCoordsBuffer = texCoordsByteBuffer.asFloatBuffer();
    }

    private void setMessageWhenError(Exception catchException) {
        if (catchException instanceof ARUnavailableServiceNotInstalledException) {
            mActivity.startActivity(new Intent(mActivity, CocosAREngineServerConnectActivity.class));
        } else if (catchException instanceof ARUnavailableServiceApkTooOldException) {
            errorMessage = "Please update HuaweiARService.apk";
        } else if (catchException instanceof ARUnavailableClientSdkTooOldException) {
            errorMessage = "Please update this app";
        } else if (catchException instanceof ARUnSupportedConfigurationException) {
            errorMessage = "The configuration is not supported by the device!";
        } else {
            errorMessage = "unknown exception throws!";
        }
    }

    /*
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] results) {
        Activity activity = GlobalObject.getActivity();
        /*
        if (!CocosARCameraPermissionHelper.hasCameraPermission(activity)) {
        Toast.makeText(
                activity,
                "Camera permission is needed to run this application",
                Toast.LENGTH_LONG)
            .show();
        if (!CocosARCameraPermissionHelper.shouldShowRequestPermissionRationale(activity)) {
            // Permission denied with checking "Do not ask again".
            CocosARCameraPermissionHelper.launchPermissionSettings(activity);
        }
        //finish();
        }//
    }*/

    //#region ar session

    //#endregion

    //#region ar camera
    @Override
    public float[] getCameraPose() {
        return mCameraPose;
    }
    @Override
    public float[] getCameraViewMatrix() {
        mCamera.getViewMatrix(mViewMatrix, 0);
        return mViewMatrix;
    }
    @Override
    public float[] getCameraProjectionMatrix() {
        if (mCamera != null) mCamera.getProjectionMatrix(mProjMatrix, 0, mNearClipPlane, mFarClipPlane);
        return mProjMatrix;
    }
    @Override
    public float[] getCameraTexCoords() {
        updateCameraTexCoords();
        return mCameraTexCoords;
    }
    //#endregion

    //#region plane detection

    protected boolean checkPlaneType(ARPlane.PlaneType planeType) {
        if(planeType == ARPlane.PlaneType.UNKNOWN_FACING)
            return false;

        if(mPlaneDetectionMode == CocosARAPIBase.PlaneDetectionMode.ALL)
            return true;

        if(planeType == ARPlane.PlaneType.HORIZONTAL_UPWARD_FACING && mPlaneDetectionMode.contains(CocosARAPIBase.PlaneDetectionMode.HORIZONTAL_UPWARD))
            return true;

        if(planeType == ARPlane.PlaneType.HORIZONTAL_DOWNWARD_FACING && mPlaneDetectionMode.contains(CocosARAPIBase.PlaneDetectionMode.HORIZONTAL_DOWNWARD))
            return true;

        if(planeType == ARPlane.PlaneType.VERTICAL_FACING && mPlaneDetectionMode.contains(CocosARAPIBase.PlaneDetectionMode.VERTICAL))
            return true;

        return false;
    }

    @Override
    public void updatePlaneDetection() {
        if (mSession == null || mCamera == null) return;

        Collection<ARPlane> allPlanes = mSession.getAllTrackables(ARPlane.class);
        
        // Planes must be sorted by distance from camera so that we draw closer planes first, and
        // they occlude the farther planes.
        List<SortablePlane> sortedPlanes = new ArrayList<>();

        ARPose cameraPose = mCamera.getDisplayOrientedPose();
        for (ARPlane plane : allPlanes) {
            //if (plane.getTrackingState() != TrackingState.TRACKING || plane.getSubsumedBy() != null) {
            if (plane.getTrackingState() != ARTrackable.TrackingState.TRACKING) {
              continue;
            }
            
            if (!checkPlaneType(plane.getType())) continue;

            float distance = calculateDistanceToPlane(plane.getCenterPose(), cameraPose);
            if (distance < 0) { // Plane is back-facing.
              continue;
            }
            sortedPlanes.add(new SortablePlane(distance, plane));
        }
        Collections.sort(
            sortedPlanes,
            new Comparator<SortablePlane>() {
                @Override
                public int compare(SortablePlane a, SortablePlane b) {
                    return Float.compare(b.distance, a.distance);
                }
            }
        );
        
        //*
        int size = sortedPlanes.size();
        size = size > mMaxPlaneProcessCount ? mMaxPlaneProcessCount : size;
        int count = 0, offset = 0;

        mAddedPlanes.clear();
        mUpdatedPlanes.clear();
        mRemovedPlanes.clear();

        for (SortablePlane sortedPlane : sortedPlanes) {
            if (count >= size) break;

            ARPlane plane = sortedPlane.plane;
            Integer planeIndex = planesIndexMap.get(plane);
            ARPlane subsumedByPlane = plane.getSubsumedBy();

            if (planeIndex == null) {
                planesMap.put(planeTag, plane);
                planesIndexMap.put(plane, planeTag);
                planeIndex = planeTag++;

                // add
                mAddedPlanes.add(planeIndex);
            } else {
                if(subsumedByPlane != null) {
                    // remove
                    mRemovedPlanes.add(planeIndex);
                } else {
                    // update
                    mUpdatedPlanes.add(planeIndex);
                }
            }

            ++count;
        }
    }

    @Override
    public float[] getAddedPlanesInfo() {
        return getPlanesInfoFromList(mAddedPlanes);
    }

    @Override
    public int[] getRemovedPlanesInfo() {
        int size = mRemovedPlanes.size();
        int[] result = new int[size];
        Integer[] temp = mRemovedPlanes.toArray(new Integer[size]);
        for (int n = 0; n < size; ++n) {
            result[n] = temp[n];
        }
        return result;
    }

    @Override
    public float[] getUpdatedPlanesInfo() {
        return getPlanesInfoFromList(mUpdatedPlanes);
    }

    private float[] getPlanesInfoFromList(List<Integer> planeIndices) {
        float[] planesInfo = new float[PLANE_INFOS_SIZE * planeIndices.size()];
        int offset = 0;
        for (int index : planeIndices) {
            ARPlane plane = planesMap.get(index);
            copyPlaneToArray(plane, index, planesInfo, offset);
            offset += PLANE_INFOS_SIZE;
        }
        return planesInfo;
    }

    private static class SortablePlane {
        final float distance;
        final ARPlane plane;
    
        SortablePlane(float distance, ARPlane plane) {
            this.distance = distance;
            this.plane = plane;
        }
    }

    // Calculate the normal distance to plane from cameraPose, the given planePose should have y axis
    // parallel to plane's normal, for example plane's center pose or hit test pose.
    public static float calculateDistanceToPlane(ARPose planePose, ARPose cameraPose) {
        float[] normal = new float[3];
        float cameraX = cameraPose.tx();
        float cameraY = cameraPose.ty();
        float cameraZ = cameraPose.tz();
        // Get transformed Y axis of plane's coordinate system.
        planePose.getTransformedAxis(1, 1.0f, normal, 0);
        // Compute dot product of plane's normal with vector from camera to plane center.
        return (cameraX - planePose.tx()) * normal[0]
            + (cameraY - planePose.ty()) * normal[1]
            + (cameraZ - planePose.tz()) * normal[2];
    }

    //#endregion

    private static void copyPoseToArray(ARPose src, float[] arr) {
        copyPoseToArray(src, arr, 0);
    }

    private static void copyPoseToArray(ARPose src, float[] arr, int offset) {
        arr[offset] = src.tx();
        arr[offset+1] = src.ty();
        arr[offset+2] = src.tz();
        arr[offset+3] = src.qx();
        arr[offset+4] = src.qy();
        arr[offset+5] = src.qz();
        arr[offset+6] = src.qw();
    }

    private static void copyPlaneToArray(ARPlane src, int index, float[] arr, int offset) {
        arr[offset++] = index;
        arr[offset++] = src.getType().ordinal();
        arr[offset++] = src.getTrackingState().ordinal();
        arr[offset++] = src.getExtentX();
        arr[offset++] = src.getExtentZ();
        ARPose pose = src.getCenterPose();
        copyPoseToArray(pose, arr, offset);
    }
}