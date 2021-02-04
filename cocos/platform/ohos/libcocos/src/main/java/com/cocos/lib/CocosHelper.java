/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package com.cocos.lib;

import ohos.aafwk.ability.AbilitySlice;
import ohos.aafwk.content.Intent;
import ohos.agp.window.service.Display;
import ohos.agp.window.service.DisplayManager;
import ohos.app.Context;
import ohos.app.dispatcher.TaskDispatcher;
import ohos.app.dispatcher.task.TaskPriority;
import ohos.batterymanager.BatteryInfo;
import ohos.bundle.AbilityInfo;
import ohos.event.commonevent.*;
import ohos.miscservices.pasteboard.PasteData;
import ohos.miscservices.pasteboard.SystemPasteboard;
import ohos.net.NetManager;
import ohos.rpc.RemoteException;
import ohos.system.DeviceInfo;
import ohos.system.version.SystemVersion;
import ohos.utils.net.Uri;
import ohos.vibrator.agent.VibratorAgent;
import ohos.vibrator.bean.VibrationPattern;
import ohos.wifi.WifiDevice;

import java.util.*;


public class CocosHelper {
    // ===========================================================
    // Constants
    // ===========================================================
    private static final String TAG = CocosHelper.class.getSimpleName();

    // ===========================================================
    // Fields
    // ===========================================================

    private static AbilitySlice sAbilitySlice;
    private static VibratorAgent sVibrateService;
    private static Optional<BatteryReceiver> sBatteryReceiver = Optional.empty();

    public static final int NETWORK_TYPE_NONE = 0;
    public static final int NETWORK_TYPE_LAN  = 1;
    public static final int NETWORK_TYPE_WWAN = 2;

    // The absolute path to the OBB if it exists.
    private static String sObbFilePath = "";


    private static List<Runnable> sTaskOnGameThread = Collections.synchronizedList(new ArrayList<>());

    /**
     * Battery receiver to getting battery level.
     */
    static class BatteryReceiver extends CommonEventSubscriber {
        public float sBatteryLevel = 0.0f;

        public BatteryReceiver(CommonEventSubscribeInfo subscribeInfo) {
            super(subscribeInfo);
        }

        @Override
        public void onReceiveEvent(CommonEventData commonEventData) {
            Intent intent = commonEventData.getIntent();
            if(intent != null) {
                int capacity =  intent.getIntParam(BatteryInfo.OHOS_BATTERY_CAPACITY, 100);
                float level = capacity / 100.0f;
                sBatteryLevel = Math.min(Math.max(level, 0.0f), 1.0f);
            }

        }
    }

    static void registerBatteryLevelReceiver(Context context) {
        if(sBatteryReceiver.isPresent()) return;

        MatchingSkills ms = new MatchingSkills();
        ms.addEvent(CommonEventSupport.COMMON_EVENT_BATTERY_CHANGED);
        CommonEventSubscribeInfo subscribeInfo = new CommonEventSubscribeInfo(ms);
        sBatteryReceiver = Optional.of(new BatteryReceiver(subscribeInfo));
        try {
            CommonEventManager.subscribeCommonEvent(sBatteryReceiver.get());
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    static void unregisterBatteryLevelReceiver(Context context) {
        if(sBatteryReceiver.isPresent()) {
            try {
                CommonEventManager.unsubscribeCommonEvent(sBatteryReceiver.get());
            } catch (RemoteException e) {
                e.printStackTrace();
            }
            sBatteryReceiver = Optional.empty();
        }
    }

    public static void runOnGameThread(final Runnable runnable) {
        sTaskOnGameThread.add(runnable);
    }

    static void flushTasksOnGameThread() {
        while(sTaskOnGameThread.size() > 0) {
            Runnable r = sTaskOnGameThread.remove(0);
            if(r != null) {
                r.run();
            }
        }
    }

    public static int getNetworkType() {

        NetManager netManager =  NetManager.getInstance(sAbilitySlice.getContext());
        if(!netManager.hasDefaultNet()) return NETWORK_TYPE_NONE;

        WifiDevice wifiDevice = WifiDevice.getInstance(sAbilitySlice.getContext());
        if(null == wifiDevice) return NETWORK_TYPE_NONE;

        if(wifiDevice.isWifiActive() && wifiDevice.isConnected()) {
            return NETWORK_TYPE_LAN;
        }
        return NETWORK_TYPE_WWAN;
    }

    // ===========================================================
    // Constructors
    // ===========================================================

    private static boolean sInited = false;
    public static void init(final AbilitySlice activity) {
        sAbilitySlice = activity;
        if (!sInited) {
            CocosHelper.sVibrateService = new VibratorAgent();

            sInited = true;
        }
    }

    public static float getBatteryLevel() {
        return sBatteryReceiver.map(x -> x.sBatteryLevel).orElse(1.0f);
    }
    public static String getObbFilePath() { return CocosHelper.sObbFilePath; }
    public static String getWritablePath() {
        return sAbilitySlice.getApplicationContext().getFilesDir().getAbsolutePath();
    }
    public static String getCurrentLanguage() {
        return Locale.getDefault().getLanguage();
    }
    public static String getCurrentLanguageCode() {
        return Locale.getDefault().toString();
    }
    public static String getDeviceModel(){
        return DeviceInfo.getModel();
    }
    public static String getSystemVersion() {
        return SystemVersion.getVersion();
    }

    public static void vibrate(float durSec) {
        List<Integer> vlist = sVibrateService.getVibratorIdList();
        if(vlist.isEmpty()) return;
        int durationMs = (int)(1000 * durSec);
        int vibrateId = -1;
        for(Integer vId : vlist) {
            // TODO: choose preferred vibration effect
            if(sVibrateService.isEffectSupport(vId, VibrationPattern.VIBRATOR_TYPE_CAMERA_CLICK)){
                vibrateId = vId;
                break;
            }
        }
        if(vibrateId < 0) {
            sVibrateService.startOnce(durationMs);
        }else {
            sVibrateService.startOnce(durationMs, vibrateId);
        }
    }

    public static boolean openURL(String url) {
        boolean ret = false;
        try {
            Intent i = new Intent();
            i.formatUri(Uri.parse(url));
            sAbilitySlice.startAbility(i);
            ret = true;
        } catch (Exception e) {
        }
        return ret;
    }

    public static void copyTextToClipboard(final String text){
        TaskDispatcher dispatcher = sAbilitySlice.getGlobalTaskDispatcher(TaskPriority.DEFAULT);
        dispatcher.asyncDispatch(new Runnable() {
            @Override
            public void run() {
                PasteData pasteData = PasteData.creatPlainTextData(text);
                SystemPasteboard.getSystemPasteboard(sAbilitySlice.getContext()).setPasteData(pasteData);
            }
        });
    }

    public static void runOnUIThread(final Runnable r) {
        TaskDispatcher dispatcher = sAbilitySlice.getGlobalTaskDispatcher(TaskPriority.DEFAULT);
        dispatcher.asyncDispatch(r);
    }

    public static int getDeviceRotation() {
        try {
            return sAbilitySlice.getDisplayOrientation();
        } catch (NullPointerException e) {
            e.printStackTrace();
        }
        return AbilityInfo.DisplayOrientation.UNSPECIFIED.ordinal();
    }


    public static float[] getSafeArea() {
        return new float[]{0,0,0,0};
    }

    public static int getDPI() {
        Optional<Display> disp = DisplayManager.getInstance().getDefaultDisplay(getContext());
        if(disp.isPresent()) {
            return (int)disp.get().getAttributes().xDpi;
        }
        return -1;
    }

    public static Context getContext() {
        return sAbilitySlice.getContext();
    }
}
