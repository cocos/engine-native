package org.cocos2dx.lib;

import android.content.Context;
import android.view.OrientationEventListener;

public class Cocos2dxOrientationHelper extends OrientationEventListener {

    private int currentOrientation;

    public Cocos2dxOrientationHelper(Context context) {
        super(context);
        currentOrientation = Cocos2dxHelper.getDeviceRotation();
    }

    public void onPause() {
        this.disable();
    }

    public void onResume() {
        this.enable();
    }

    @Override
    public void onOrientationChanged(int orientation) {
        int curOrientation = Cocos2dxHelper.getDeviceRotation();
        if (curOrientation != currentOrientation) {
            currentOrientation = Cocos2dxHelper.getDeviceRotation();
            nativeOnOrientationChanged(currentOrientation);
        }
    }

    public static native void nativeOnOrientationChanged(int rotation);
}
