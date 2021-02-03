/****************************************************************************
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

import ohos.agp.render.Paint;
import ohos.data.DatabaseHelper;
import ohos.data.preferences.Preferences;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Set;

public class CocosLocalStorage {

    private static final String TAG = "CocosLocalStorage";

    private static String DATABASE_NAME = "jsb.sqlite";
    private static String TABLE_NAME = "data";
    private static final int DATABASE_VERSION = 1;

    private static DatabaseHelper mDatabaseOpenHelper = null;
    private static Preferences mDatabase = null;

    public static boolean init(String dbName, String tableName) {
        if (GlobalObject.getAbilitySlice() != null) {
            DATABASE_NAME = dbName;
            TABLE_NAME = tableName;
            mDatabaseOpenHelper = new DatabaseHelper(GlobalObject.getAbilitySlice());
            mDatabase = mDatabaseOpenHelper.getPreferences(getTableName());
            return true;
        }
        return false;
    }

    private static String getTableName() {
        return DATABASE_NAME + "." + TABLE_NAME;
    }

    public static void destroy() {
        if (mDatabase != null) {
            mDatabase.clear();
            mDatabaseOpenHelper.deletePreferences(getTableName());
        }
    }

    public static void setItem(String key, String value) {
        mDatabase.putString(key, value);
    }

    public static String getItem(String key) {
        return mDatabase.getString(key, null);
    }

    public static void removeItem(String key) {
        mDatabase.delete(key);
    }

    public static void clear() {
        mDatabase.clear();
    }

    public static String getKey(int nIndex) {
        //TODO: need opt for performance
        List<String> sets = new ArrayList<String>(mDatabase.getAll().keySet());
        return nIndex >= 0 && nIndex < sets.size() ? sets.get(nIndex) : null;
    }

    public static int getLength() {
        //TODO: need opt
        return mDatabase.getAll().size();
    }
}
