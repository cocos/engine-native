//Script to add into com.cocos.game package, backup here
package com.cocos.lib;

import java.util.ArrayList;
import java.util.HashMap;

public class JsJavaEventHandler {
    public interface javaCallback{
        void onTrigger(String arg);
    }
    public static JsJavaEventHandler getInstance(){
        if(instance == null)
        {
            instance = new JsJavaEventHandler();
        }
        return instance;
    }
    public void addCallback(String event, javaCallback cb){
        if(eventMap.get(event) == null){
            eventMap.put(event, new ArrayList<javaCallback>());
        }
        eventMap.get(event).add(cb);
    }
    public void removeCallback(String event, javaCallback cb){
        if(eventMap.get(event) == null){
            return;
        }
        ArrayList<javaCallback> arr = eventMap.get(event);
        arr.remove(cb);
    }
    public boolean removeEvent (String event) {
        ArrayList<javaCallback> arr = this.eventMap.get(event);
        if (arr == null) {
            return false;
        }
        arr.clear();
        return true;
    }
    public void dispatchScriptEvent (String event, String arg0){
        JsbBridge.sendToScript(event,arg0);
    }
    public void dispatchScriptEvent (String event){
        JsbBridge.sendToScript(event);
    }

    private JsJavaEventHandler(){
        JsbBridge.setCallback(new JsbBridge.ICallback() {
            @Override
            public void onScript(String arg0, String arg1) {
                triggerEvents(arg0, arg1);
            }
        });
    }
    private HashMap<String, ArrayList<javaCallback> > eventMap = new HashMap<>();
    private static JsJavaEventHandler instance;
    private void triggerEvents(String event, String arg){
        ArrayList<javaCallback> arr = eventMap.get(event);
        for(javaCallback m: arr){
            m.onTrigger(arg);
        }
    }
}
