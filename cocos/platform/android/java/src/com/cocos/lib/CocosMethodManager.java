/*
 * Copyright (c) 2013-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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
 */
package com.cocos.lib;

import org.json.JSONObject;

import java.util.HashMap;

//Java JavaScript Bridge Simplified
public class CocosMethodManager {
    private static final HashMap<String, IMethod> methodMap = new HashMap<>();
    public static void applyMethod(String methodName, String arg){
        if(methodMap.get(methodName)==null){
          return;
        }
        methodMap.get(methodName).apply(arg);
    }

    /**Add a method which you would like to expose to script writers
     * @param methodName the name for this method/function
     * @param f IMethod, the method which will be actually applied.
     * @return if success
     * */
    public static Boolean addMethod(String methodName, IMethod f){
        if(methodMap.get(methodName)!=null){
            return false;
        }
        methodMap.put(methodName,f);
        return true;
    }
    /**
     * Remove method with name, return IMethod to user
     * @param methodName the name key
     * */
    public static IMethod removeMethod(String methodName){
        if(methodMap.get(methodName)!=null)
            return methodMap.remove(methodName);
        return null;
    }

    /**
     * Java dispatch Js event, use native c++ code
     * @param methodName in js function map
     * @return Boolean if dispatch custom js event success.
     */
    public static native void informScript(String methodName, String arg);
    public static void informScript(String methodName){
        informScript(methodName, null);
    }
}