/****************************************************************************
 * Copyright (c) 2020 Xiamen Yaji Software Co., Ltd.
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

import ohos.aafwk.ability.AbilitySlice;
import ohos.aafwk.content.Intent;
import ohos.agp.components.Component;
import ohos.agp.components.StackLayout;
import ohos.agp.components.surfaceprovider.SurfaceProvider;
import ohos.agp.graphics.Surface;
import ohos.agp.graphics.SurfaceOps;
import ohos.global.resource.ResourceManager;
import ohos.multimodalinput.event.KeyEvent;
import ohos.multimodalinput.event.TouchEvent;
import ohos.system.version.SystemVersion;

import java.io.File;
import java.util.Optional;

public class CocosAbilitySlice extends AbilitySlice implements SurfaceOps.Callback, Component.TouchEventListener , Component.KeyEventListener, Component.FocusChangedListener {
    private boolean mDestroyed;
    private SurfaceProvider mSurfaceHolder;
    private Optional<Surface> mSurface = Optional.empty();
    private StackLayout mFrameLayout;
    private CocosVideoHelper mVideoHelper = null;
    private CocosOrientationHelper mOrientationHelper = null;

    private boolean engineInit = false;

    private CocosKeyCodeHandler mKeyCodeHandler;
    private CocosSensorHandler mSensorHandler;


    private native void onCreateNative(AbilitySlice activity, String assetPath, ResourceManager resourceManager, int sdkVersion);

    private native void onSurfaceCreatedNative(Surface surface);

    private native void onSurfaceChangedNative(int width, int height);

    private native void onSurfaceDestroyNative();

    private native void onPauseNative();

    private native void onResumeNative();

    private native void onStopNative();

    private native void onStartNative();

    private native void onLowMemoryNative();

    private native void onWindowFocusChangedNative(boolean hasFocus);

    @Override
    protected void onStart(Intent savedInstanceState) {
        super.onStart(savedInstanceState);
        GlobalObject.setAbilitySlice(this);
        CocosHelper.registerBatteryLevelReceiver(this);
        CocosHelper.init(this);
        CanvasRenderingContext2DImpl.init(this);
        onLoadNativeLibraries();


//        this.setVolumeControlStream(AudioManager.STREAM_MUSIC);
//        getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_ADJUST_NOTHING);
        initView();

        onCreateNative(this, getAssetPath(),  getResourceManager(), SystemVersion.getApiVersion());

        mKeyCodeHandler = new CocosKeyCodeHandler(this);
        mSensorHandler = new CocosSensorHandler();


//        setImmersiveMode();
//        Utils.hideVirtualButton();

        mOrientationHelper = new CocosOrientationHelper(this);
    }
    private String getAssetPath() {
        return getApplicationContext().getFilesDir().getPath();
    }

//    private void setImmersiveMode() {
//        WindowManager.LayoutParams lp = getWindow().getAttributes();
//        try {
//            Field field = lp.getClass().getField("layoutInDisplayCutoutMode");
//            //Field constValue = lp.getClass().getDeclaredField("LAYOUT_IN_DISPLAY_CUTOUT_MODE_NEVER");
//            Field constValue = lp.getClass().getDeclaredField("LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES");
//            field.setInt(lp, constValue.getInt(null));
//
//            // https://developer.android.com/training/system-ui/immersive
//            int flag = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
//                    | View.SYSTEM_UI_FLAG_FULLSCREEN
//                    | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
//                    | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
//                    | View.SYSTEM_UI_FLAG_LAYOUT_STABLE;
//
//            flag |= View.class.getDeclaredField("SYSTEM_UI_FLAG_IMMERSIVE_STICKY").getInt(null);
//            View view = getWindow().getDecorView();
//            view.setSystemUiVisibility(flag);
//
//        } catch (NoSuchFieldException e) {
//            e.printStackTrace();
//        } catch (IllegalAccessException e) {
//            e.printStackTrace();
//        }
//    }

    private static String getAbsolutePath(File file) {
        return (file != null) ? file.getAbsolutePath() : null;
    }

    protected void initView() {
        StackLayout.LayoutConfig frameLayoutParams = new StackLayout.LayoutConfig(
                StackLayout.LayoutConfig.MATCH_PARENT,
                StackLayout.LayoutConfig.MATCH_PARENT);
        mFrameLayout = new StackLayout(getContext());
        mFrameLayout.setLayoutConfig(frameLayoutParams);

        mSurfaceHolder = new SurfaceProvider( getContext());
        mSurfaceHolder.getSurfaceOps().get().addCallback(this);
        mSurfaceHolder.setLayoutConfig(new StackLayout.LayoutConfig(
                StackLayout.LayoutConfig.MATCH_PARENT,
                StackLayout.LayoutConfig.MATCH_PARENT
        ));
        mSurfaceHolder.setTouchEventListener(this);
        mSurfaceHolder.setKeyEventListener(this);

        mSurfaceHolder.setFocusable(Component.FOCUS_ENABLE);
        mSurfaceHolder.setFocusChangedListener(this);


        mFrameLayout.addComponent(mSurfaceHolder);
//
//        if (mWebViewHelper == null) {
//            mWebViewHelper = new CocosWebViewHelper(mFrameLayout);
//        }

        if (mVideoHelper == null) {
            mVideoHelper = new CocosVideoHelper(this, mFrameLayout);
        }


        setUIContent(mFrameLayout);
    }

    public SurfaceProvider getSurfaceView() {
        return this.mSurfaceHolder;
    }

    @Override
    protected void onStop() {
        mDestroyed = true;
        if (mSurfaceHolder != null) {
            onSurfaceDestroyNative();
            mSurfaceHolder = null;
        }
        super.onStop();
    }

    @Override
    protected void onInactive() {
        super.onInactive();
        mSensorHandler.onPause();
        mOrientationHelper.onPause();
        onPauseNative();
    }

    @Override
    protected void onActive() {
        super.onActive();
        onStartNative();
        mSensorHandler.onResume();
        mOrientationHelper.onResume();
        onResumeNative();

    }

    @Override
    protected void onBackground() {
        super.onBackground();
        onStopNative();
    }

    // TODO: low memory listener
//    @Override
//    public void onLowMemory() {
//        super.onLowMemory();
//        if (!mDestroyed) {
//            onLowMemoryNative();
//        }
//    }

    @Override
    public void onFocusChange(Component component, boolean b) {
        //NOTICE: may not be equivalent to onWindowFocusChanged on Android
        if (!mDestroyed) {
            onWindowFocusChangedNative(b);
        }
    }

    @Override
    public void surfaceCreated(SurfaceOps holder) {
        if (!mDestroyed) {
            mSurface = Optional.of(holder.getSurface());
            onSurfaceCreatedNative(holder.getSurface());

            engineInit = true;
        }
    }

    @Override
    public void surfaceChanged(SurfaceOps surfaceOps, int format, int width, int height) {
        if (!mDestroyed) {
            mSurface = Optional.empty();
            onSurfaceChangedNative(width, height);
        }
    }

    @Override
    public void surfaceDestroyed(SurfaceOps surfaceOps) {
        mSurfaceHolder = null;
        if (!mDestroyed) {
            onSurfaceDestroyNative();
            engineInit = false;
        }
    }

    private void onLoadNativeLibraries() {
        try {
            //TODO: Read library name from configuration
            System.loadLibrary("cocos");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        return mKeyCodeHandler.onKeyDown(keyCode, event) || super.onKeyDown(keyCode, event);
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
        return mKeyCodeHandler.onKeyUp(keyCode, event) || super.onKeyUp(keyCode, event);
    }

    @Override
    public boolean onTouchEvent(Component component, TouchEvent touchEvent) {
        return false;
    }

    @Override
    public boolean onKeyEvent(Component component, KeyEvent keyEvent) {
        return false;
    }
}
