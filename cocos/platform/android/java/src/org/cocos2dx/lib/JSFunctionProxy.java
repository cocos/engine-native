package org.cocos2dx.lib;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;

public class JSFunctionProxy {

    final static int MAX_WAIT = 300000;
    final static int TICK = 3; //millis

    public static void dispatchToJS_V(final Object[] args) {
        String methodName = Thread.currentThread().getStackTrace()[3].getMethodName();

        final AtomicBoolean finished = new AtomicBoolean(false);

        if (Cocos2dxHelper.inRendererThread()) {
            ByteCodeGenerator.callJS(finished, methodName, args);
            return;
        } else {
            Cocos2dxHelper.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    ByteCodeGenerator.callJS(finished, methodName, args);
                }
            });
            int maxWait = MAX_WAIT;
            while (!finished.get() && maxWait > 0) {
                try {
                    Thread.sleep(TICK);
                    maxWait -= TICK;
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    break;
                }
            }
        }
    }

    public static Object dispatchToJS_L(final Object[] args) {
        String methodName = Thread.currentThread().getStackTrace()[3].getMethodName();

        final AtomicBoolean finished = new AtomicBoolean(false);
        final List<Object> result = new ArrayList<>();
        if (Cocos2dxHelper.inRendererThread()) {
            return ByteCodeGenerator.callJS(finished, methodName, args);
        } else {
            Cocos2dxHelper.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    result.add(ByteCodeGenerator.callJS(finished, methodName, args));
                }
            });
            int maxWait = MAX_WAIT;
            while (!finished.get() && maxWait > 0) {
                try {
                    Thread.sleep(TICK);
                    maxWait -= TICK;
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    break;
                }
            }
        }
        return result.isEmpty() ? null : result.get(0);
    }

    public static boolean dispatchToJS_Z(final Object[] args) {
        String methodName = Thread.currentThread().getStackTrace()[3].getMethodName();

        final AtomicBoolean finished = new AtomicBoolean(false);
        final List<Boolean> result = new ArrayList<>();
        if (Cocos2dxHelper.inRendererThread()) {
            return (Boolean) ByteCodeGenerator.callJS(finished, methodName, args);
        } else {
            Cocos2dxHelper.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    result.add((Boolean)ByteCodeGenerator.callJS(finished, methodName, args));
                }
            });
            int maxWait = MAX_WAIT;
            while (!finished.get() && maxWait > 0) {
                try {
                    Thread.sleep(TICK);
                    maxWait -= TICK;
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    break;
                }
            }
        }
        return result.isEmpty() ? false : result.get(0);
    }

    public static byte dispatchToJS_B(final Object[] args) {
        String methodName = Thread.currentThread().getStackTrace()[3].getMethodName();

        final AtomicBoolean finished = new AtomicBoolean(false);
        final List<Byte> result = new ArrayList<>();
        if (Cocos2dxHelper.inRendererThread()) {
            return (byte)((Double) ByteCodeGenerator.callJS(finished, methodName, args)).intValue();
        } else {
            Cocos2dxHelper.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    result.add((byte)((Double) ByteCodeGenerator.callJS(finished, methodName, args)).intValue());
                }
            });
            int maxWait = MAX_WAIT;
            while (!finished.get() && maxWait > 0) {
                try {
                    Thread.sleep(TICK);
                    maxWait -= TICK;
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    break;
                }
            }
        }
        return result.isEmpty() ? 0 : result.get(0);
    }

    public static int dispatchToJS_I(final Object[] args) {
        String methodName = Thread.currentThread().getStackTrace()[3].getMethodName();

        final AtomicBoolean finished = new AtomicBoolean(false);
        final List<Integer> result = new ArrayList<>();
        if (Cocos2dxHelper.inRendererThread()) {
            return ((Double) ByteCodeGenerator.callJS(finished, methodName, args)).intValue();
        } else {
            Cocos2dxHelper.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    result.add(((Double) ByteCodeGenerator.callJS(finished, methodName, args)).intValue());
                }
            });
            int maxWait = MAX_WAIT;
            while (!finished.get() && maxWait > 0) {
                try {
                    Thread.sleep(TICK);
                    maxWait -= TICK;
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    break;
                }
            }
        }
        return result.isEmpty() ? 0 : result.get(0);
    }
    public static short dispatchToJS_S(final Object[] args) {
        String methodName = Thread.currentThread().getStackTrace()[3].getMethodName();

        final AtomicBoolean finished = new AtomicBoolean(false);
        final List<Short> result = new ArrayList<>();
        if (Cocos2dxHelper.inRendererThread()) {
            return (short)((Double) ByteCodeGenerator.callJS(finished, methodName, args)).intValue();
        } else {
            Cocos2dxHelper.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    result.add((short)((Double) ByteCodeGenerator.callJS(finished, methodName, args)).intValue());
                }
            });
            int maxWait = MAX_WAIT;
            while (!finished.get() && maxWait > 0) {
                try {
                    Thread.sleep(TICK);
                    maxWait -= TICK;
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    break;
                }
            }
        }
        return result.isEmpty() ? 0 : result.get(0);
    }

    public static long dispatchToJS_J(final Object[] args) {
        String methodName = Thread.currentThread().getStackTrace()[3].getMethodName();

        final AtomicBoolean finished = new AtomicBoolean(false);
        final List<Long> result = new ArrayList<>();
        if (Cocos2dxHelper.inRendererThread()) {
            return ((Double) ByteCodeGenerator.callJS(finished, methodName, args)).longValue();
        } else {
            Cocos2dxHelper.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    result.add(((Double) ByteCodeGenerator.callJS(finished, methodName, args)).longValue());
                }
            });
            int maxWait = MAX_WAIT;
            while (!finished.get() && maxWait > 0) {
                try {
                    Thread.sleep(TICK);
                    maxWait -= TICK;
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    break;
                }
            }
        }
        return result.isEmpty() ? 0 : result.get(0);
    }
    public static float dispatchToJS_F(final Object[] args) {
        String methodName = Thread.currentThread().getStackTrace()[3].getMethodName();

        final AtomicBoolean finished = new AtomicBoolean(false);
        final List<Float> result = new ArrayList<>();
        if (Cocos2dxHelper.inRendererThread()) {
            return ((Double) ByteCodeGenerator.callJS(finished, methodName, args)).floatValue();
        } else {
            Cocos2dxHelper.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    result.add(((Double) ByteCodeGenerator.callJS(finished, methodName, args)).floatValue());
                }
            });
            int maxWait = MAX_WAIT;
            while (!finished.get() && maxWait > 0) {
                try {
                    Thread.sleep(TICK);
                    maxWait -= TICK;
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    break;
                }
            }
        }
        return result.isEmpty() ? 0 : result.get(0);
    }
    public static double dispatchToJS_D(final Object[] args) {
        String methodName = Thread.currentThread().getStackTrace()[3].getMethodName();

        final AtomicBoolean finished = new AtomicBoolean(false);
        final List<Double> result = new ArrayList<>();
        if (Cocos2dxHelper.inRendererThread()) {
            return ((Double) ByteCodeGenerator.callJS(finished, methodName, args)).doubleValue();
        } else {
            Cocos2dxHelper.runOnGLThread(new Runnable() {
                @Override
                public void run() {
                    result.add( ((Double) ByteCodeGenerator.callJS(finished, methodName, args)).doubleValue());
                }
            });
            int maxWait = MAX_WAIT;
            while (!finished.get() && maxWait > 0) {
                try {
                    Thread.sleep(TICK);
                    maxWait -= TICK;
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    break;
                }
            }
        }
        return result.isEmpty() ? 0 : result.get(0);
    }
}
