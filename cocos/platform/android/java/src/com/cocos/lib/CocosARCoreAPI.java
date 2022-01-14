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
import com.google.ar.core.exceptions.UnavailableUserDeclinedInstallationException;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import android.content.Context;
import android.app.Activity;
import android.widget.Toast;
import android.os.Handler;
import android.util.Log;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

public class CocosARCoreAPI extends CocosARAPIBase implements ActivityCompat.OnRequestPermissionsResultCallback {
    private static final String TAG = CocosARCoreAPI.class.getSimpleName();
    private static CocosARCoreAPI api = null;
    
    private CocosARDisplayRotationHelper mDisplayRotationHelper;

    private Session mSession;
    private Frame mFrame;
    private Camera mCamera;

    //private float[] mCameraPose = new float[7];
    //private float[] mViewMatrix = new float[16];
    //private float[] mProjMatrix = new float[16];

    private float[] mQuadCoords = {-1f, -1f, -1f, 1f, 1f, -1f, 1f, 1f};
    //private float[] mCameraTexCoords = new float[8];

    // requestInstall(Activity, true) will triggers installation of
    // Google Play Services for AR if necessary.
    private boolean mUserRequestedInstall = true;
    private boolean mActive;

    // plane feature
    private final static int PLANE_INFOS_SIZE = 12;
    private int planesMaxSize = 5;
    private int planeTag = 0;
    private final HashMap<Integer, Plane> planesMap = new HashMap<>();
    private final HashMap<Plane, Integer> planesIndexMap = new HashMap<>();
    private List<Integer> mAddedPlanes = new ArrayList<>();
    private List<Integer> mRemovedPlanes = new ArrayList<>();
    private List<Integer> mUpdatedPlanes = new ArrayList<>();

    public static CocosARCoreAPI init() {
        api = new CocosARCoreAPI();
        return api;
    }

    public static void start(final CocosARCoreAPI api) {
        api.checkCamera();
        if (api.checkSupportAndUpdate() > 0) {
            api.startSession();
        }
    }
    public static void onDestroy(final CocosARCoreAPI api) {
        api.closeSession();
    }
    public static void resume(final CocosARCoreAPI api) {
        api.checkCamera();
        if (api.checkSupportAndUpdate() > 0) {
            api.startSession();
        }
    }
    public static void pause(final CocosARCoreAPI api) {
        api.pauseSession();
    }

    public static void beforeUpdate(final CocosARCoreAPI api) {
        if (api.mSession == null) return;
        api.updateSession();
        //api.updateCameraPose();
        //api.updateCameraTexCoords();
    }

    public static void update(final CocosARCoreAPI api) {
        if (api.mSession == null) return;
        api.updateSession();
        //api.updateCameraPose();
        //api.updateCameraTexCoords();
    }

    public static boolean checkStart(final CocosARCoreAPI api) {
        if (api != null && api.mSession != null) {
            return true;
        }
        return false;
    }

    public static void setCameraTextureName(final CocosARCoreAPI api, int id) {
        //api.mSession.setCameraTextureName(id);
        api.mTextureId = id;
    }

    public static float[] getCameraPose(final CocosARCoreAPI api) {
        return api.mCameraPose;
    }
    public static float[] getCameraViewMatrix(final CocosARCoreAPI api) {
        api.mCamera.getViewMatrix(api.mViewMatrix, 0);
        return api.mViewMatrix;
    }
    public static float[] getCameraProjectionMatrix(final CocosARCoreAPI api) {
        if (api.mSession != null) api.mCamera.getProjectionMatrix(api.mProjMatrix, 0, 0.01f, 1000.0f);
        return api.mProjMatrix;
    }
    public static float[] getCameraTexCoords(final CocosARCoreAPI api) {
        //api.updateCameraTexCoords();
        return api.mCameraTexCoords;
    }

    // plane feature
    public static void updatePlanesInfo(final CocosARCoreAPI api) {
        api.updatePlaneDetection();
    }
    public static float[] getAddedPlanesInfo(final CocosARCoreAPI api) {
        return api.getPlanesInfoFromList(api.mAddedPlanes);
    }
    public static int[] getRemovedPlanesInfo(final CocosARCoreAPI api) {
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
    public static float[] getUpdatedPlanesInfo(final CocosARCoreAPI api) {
        return api.getPlanesInfoFromList(api.mUpdatedPlanes);
    }
    public static int getAddedPlanesCount(final CocosARCoreAPI api) {
        return api.mAddedPlanes.size();
    }
    public static int getRemovedPlanesCount(final CocosARCoreAPI api) {
        return api.mRemovedPlanes.size();
    }
    public static int getUpdatedPlanesCount(final CocosARCoreAPI api) {
        return api.mUpdatedPlanes.size();
    }

    // for CocosARDisplayRotationHelper
    @Override
    public void setDisplayGeometry(int displayRotation, int width, int height) {
        mSession.setDisplayGeometry(displayRotation, width, height);
    }

    private void updateCameraPose() {
        if(mCamera == null) return;

        Pose pose = mCamera.getDisplayOrientedPose();
        mCameraPose[0] = pose.tx();
        mCameraPose[1] = pose.ty();
        mCameraPose[2] = pose.tz();
        mCameraPose[3] = pose.qx();
        mCameraPose[4] = pose.qy();
        mCameraPose[5] = pose.qz();
        mCameraPose[6] = pose.qw();
    }

    private void updateCameraTexCoords() {
        if(mFrame == null) return;

        if (mFrame.hasDisplayGeometryChanged()) {
            // If display rotation changed (also includes view size change), we need to re-query the UV
            // coordinates for the screen rect, as they may have changed as well.
            mFrame.transformCoordinates2d(
                Coordinates2d.OPENGL_NORMALIZED_DEVICE_COORDINATES,
                mQuadCoords,
                Coordinates2d.TEXTURE_NORMALIZED,
                mCameraTexCoords);
        }
    }

    private void checkCamera() {
        Activity activity = GlobalObject.getActivity();
        if (!CocosARCameraPermissionHelper.hasCameraPermission(activity)) {
            CocosARCameraPermissionHelper.requestCameraPermission(activity);
        }
    }

    // -1 not supported, 0 not installed, 1 ready
    private int checkSupportAndUpdate() {
        Activity activity = GlobalObject.getActivity();
        ArCoreApk.Availability availability = ArCoreApk.getInstance().checkAvailability(activity);
        if (availability.isTransient()) {
            // Continue to query availability at 5Hz while compatibility is checked in the background.
            new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                checkSupportAndUpdate();
            }
            }, 200);
        }

        switch (availability) {
            case SUPPORTED_INSTALLED:
              break;
            case SUPPORTED_APK_TOO_OLD:
            case SUPPORTED_NOT_INSTALLED:
              try {
                // Request ARCore installation or update if needed.
                ArCoreApk.InstallStatus installStatus =
                    ArCoreApk.getInstance().requestInstall(activity, /*userRequestedInstall=*/ true);
                switch (installStatus) {
                  case INSTALL_REQUESTED:
                    Log.e(TAG, "ARCore installation requested.");
                    return 0;
                  case INSTALLED:
                    break;
                }
              } catch (UnavailableDeviceNotCompatibleException e) {
                Log.e(TAG, "ARCore not installed", e);
                return 0;
              } catch (UnavailableUserDeclinedInstallationException e) {
                  Log.e(TAG, "ARCore not installed", e);
                  return 0;
              }
              break;
            case UNKNOWN_ERROR:
            case UNKNOWN_CHECKING:
            case UNKNOWN_TIMED_OUT:
            case UNSUPPORTED_DEVICE_NOT_CAPABLE:
              Log.e(
                  TAG,
                  "ARCore is not supported on this device, ArCoreApk.checkAvailability() returned "
                      + availability);
              return -1;
          }
          return 1;
    }

    @Override
    public void startSession() {
        CocosActivity activity = (CocosActivity)GlobalObject.getActivity();
        if (mSession == null) {
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
        }
        /*if (mSession == null) {
            Activity activity = GlobalObject.getActivity();
            switch (ArCoreApk.getInstance().requestInstall(activity, mUserRequestedInstall)) {
                case INSTALLED:
                    // Success: Safe to create the AR session.
                    mSession = new Session(activity);
                    break;
                case INSTALL_REQUESTED:
                    // When this method returns `INSTALL_REQUESTED`:
                    // 1. ARCore pauses this activity.
                    // 2. ARCore prompts the user to install or update Google Play
                    //    Services for AR (market://details?id=com.google.ar.core).
                    // 3. ARCore downloads the latest device profile data.
                    // 4. ARCore resumes this activity. The next invocation of
                    //    requestInstall() will either return `INSTALLED` or throw an
                    //    exception if the installation or update did not succeed.
                    mUserRequestedInstall = false;
                    return;
            }
        }*/
        if (mDisplayRotationHelper == null) {
            mDisplayRotationHelper = new CocosARDisplayRotationHelper(GlobalObject.getActivity());
        }
        mDisplayRotationHelper.registerDisplayListener();

        try {
            mSession.resume();
            //CocosActivity activity = (CocosActivity)GlobalObject.getActivity();
            int width = activity.getSurfaceView().getWidth();
            int height = activity.getSurfaceView().getHeight();
            mDisplayRotationHelper.updateViewportChanged(width, height);

        } catch (CameraNotAvailableException e) {
            mSession = null;
            return;
        }
    }

    @Override
    public void closeSession() {
        mSession.close();
        mSession = null;
    }

    @Override
    public void resumeSession() {

    }

    @Override
    public void pauseSession() {
        mSession.pause();
        mDisplayRotationHelper.unregisterDisplayListener();
    }

    @Override
    public void updateSession() {
        mDisplayRotationHelper.updateDisplayGeometry(this);

        try {
            mSession.setCameraTextureName(mTextureId);
            mFrame = mSession.update();
        } catch (CameraNotAvailableException e) {
            e.printStackTrace();
        }

        mCamera = mFrame.getCamera();
        updateCameraPose();
        updateCameraTexCoords();
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] results) {
        Activity activity = GlobalObject.getActivity();
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
        }
    }

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
        //updateCameraTexCoords();
        return mCameraTexCoords;
    }
    @Override
    public int getAPIState() {
        if (mSession != null && mCamera != null) {
            return 1;
        }
        return -1;
    }
    //#endregion

    //#region plane detection
    protected boolean checkPlaneType(Plane.Type planeType) {
        if(mPlaneDetectionMode == CocosARAPIBase.PlaneDetectionMode.ALL)
            return true;

        if(planeType == Plane.Type.HORIZONTAL_UPWARD_FACING && mPlaneDetectionMode.contains(CocosARAPIBase.PlaneDetectionMode.HORIZONTAL_UPWARD))
            return true;

        if(planeType == Plane.Type.HORIZONTAL_DOWNWARD_FACING && mPlaneDetectionMode.contains(CocosARAPIBase.PlaneDetectionMode.HORIZONTAL_DOWNWARD))
            return true;

        if(planeType == Plane.Type.VERTICAL && mPlaneDetectionMode.contains(CocosARAPIBase.PlaneDetectionMode.VERTICAL))
            return true;

        return false;
    }

    @Override
    public void updatePlaneDetection() {
        if (mSession == null || mCamera == null) return;

        Collection<Plane> allPlanes = mSession.getAllTrackables(Plane.class);
        
        // Planes must be sorted by distance from camera so that we draw closer planes first, and
        // they occlude the farther planes.
        List<SortablePlane> sortedPlanes = new ArrayList<>();

        Pose cameraPose = mCamera.getDisplayOrientedPose();
        for (Plane plane : allPlanes) {
            if (plane.getTrackingState() != TrackingState.TRACKING) {
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
        
        int size = sortedPlanes.size();
        size = size > mMaxPlaneProcessCount ? mMaxPlaneProcessCount : size;
        int count = 0, offset = 0;

        mAddedPlanes.clear();
        mUpdatedPlanes.clear();
        mRemovedPlanes.clear();

        for (SortablePlane sortedPlane : sortedPlanes) {
            if (count >= size) continue;

            Plane plane = sortedPlane.plane;
            Integer planeIndex = planesIndexMap.get(plane);
            Plane subsumedByPlane = plane.getSubsumedBy();

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
                    continue;
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
        int maxSize = 5;
        int n = 0;
        for (int index : planeIndices) {
            if (n >= maxSize) break;
            Plane plane = planesMap.get(index);
            copyPlaneToArray(plane, index, planesInfo, offset);
            offset += PLANE_INFOS_SIZE;
            ++n;
        }
        return planesInfo;
    }

    private static class SortablePlane {
        final float distance;
        final Plane plane;
    
        SortablePlane(float distance, Plane plane) {
            this.distance = distance;
            this.plane = plane;
        }
    }

    // Calculate the normal distance to plane from cameraPose, the given planePose should have y axis
    // parallel to plane's normal, for example plane's center pose or hit test pose.
    public static float calculateDistanceToPlane(Pose planePose, Pose cameraPose) {
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

    private static void copyPoseToArray(Pose src, float[] arr) {
        copyPoseToArray(src, arr, 0);
    }

    private static void copyPoseToArray(Pose src, float[] arr, int offset) {
        arr[offset] = src.tx();
        arr[offset+1] = src.ty();
        arr[offset+2] = src.tz();
        arr[offset+3] = src.qx();
        arr[offset+4] = src.qy();
        arr[offset+5] = src.qz();
        arr[offset+6] = src.qw();
    }

    private static void copyPlaneToArray(Plane src, int index, float[] arr, int offset) {
        arr[offset++] = index;
        arr[offset++] = src.getType().ordinal();
        arr[offset++] = src.getTrackingState().ordinal();
        arr[offset++] = src.getExtentX();
        arr[offset++] = src.getExtentZ();
        Pose pose = src.getCenterPose();
        copyPoseToArray(pose, arr, offset);
    }
}