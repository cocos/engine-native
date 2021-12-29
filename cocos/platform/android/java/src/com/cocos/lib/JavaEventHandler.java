//Script to add into com.cocos.game package, backup here
package com.cocos.lib;

import java.util.ArrayList;
import java.util.HashMap;

public class JavaEventHandler {
    public interface JavaCallback {
        void onTrigger(String arg);
    }

    public static JavaEventHandler getInstance() {
        if (instance == null) {
            instance = new JavaEventHandler();
        }
        return instance;
    }

    public void addCallback(String event, JavaCallback cb) {
        if (eventMap.get(event) == null) {
            eventMap.put(event, new ArrayList<JavaCallback>());
        }
        eventMap.get(event).add(cb);
    }

    public void removeCallback(String event, JavaCallback cb) {
        ArrayList<JavaCallback> arr = eventMap.get(event);
        if (arr == null) {
            return;
        }
        arr.remove(cb);
    }

    public boolean removeEvent(String event) {
        ArrayList<JavaCallback> arr = this.eventMap.get(event);
        if (arr == null) {
            return false;
        }
        arr.clear();
        this.eventMap.remove(event);
        return true;
    }

    public void dispatchScriptEvent(String event, String arg0) {
        JsbBridge.sendToScript(event, arg0);
    }

    public void dispatchScriptEvent(String event) {
        JsbBridge.sendToScript(event);
    }

    private JavaEventHandler() {
        JsbBridge.setCallback(new JsbBridge.ICallback() {
            @Override
            public void onScript(String arg0, String arg1) {
                triggerEvents(arg0, arg1);
            }
        });
    }

    private final HashMap<String, ArrayList<JavaCallback>> eventMap = new HashMap<>();
    private static JavaEventHandler instance;

    private void triggerEvents(String event, String arg) {
        ArrayList<JavaCallback> arr = eventMap.get(event);
        if (arr == null)
            return;
        for (JavaCallback m : arr) {
            m.onTrigger(arg);
        }
    }
}
