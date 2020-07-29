package org.cocos2dx.lib;


import com.android.dx.Code;
import com.android.dx.DexMaker;
import com.android.dx.FieldId;
import com.android.dx.Local;
import com.android.dx.MethodId;
import com.android.dx.TypeId;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.math.BigInteger;
import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.jar.JarEntry;
import java.util.jar.JarOutputStream;

public class ByteCodeGenerator {


    public static final String NATIVE_ID = "__native_id__";
    public static final String PROXY_METHOD_NAME = "dispatchToJS_";

    static int object_id = 10000;

    private static Map<String, Class<?>> cachedClassMap = new ConcurrentHashMap<>();

    static class MethodRecord {
        public int modifiers;
        public String signature;
        public Method method;
        public String name;
    }


    public static <T, G extends T> Object newInstance(String superClassName, String[] interfaces) {

        ByteCodeGenerator bc = new ByteCodeGenerator();
        bc.setSuperClass(superClassName);
        bc.setInterfaces(interfaces);
        bc.setClassName("pkg/anonymous/K_" + bc.getHashKeyForAnonymousClass());

        Class<?> generatedClass = null;

        if(cachedClassMap.containsKey(bc.getHashKeyForAnonymousClass())) {
            generatedClass = cachedClassMap.get(bc.getHashKeyForAnonymousClass());
            try {
                Object ret = generatedClass.newInstance();
                if(ret != null) {
                    return ret;
                }
            } catch (InstantiationException e) {
                e.printStackTrace();
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }
        }


        if (bc.getJarFile().exists()) {
            ClassLoader loader = bc.cacheClassLoader(bc.getJarFile());
            try {
                generatedClass = loader.loadClass(bc.getClassNameWithDots());
                try {
                    Object ret = generatedClass.newInstance();
                    if(ret != null) {
                        cachedClassMap.put(bc.getHashKeyForAnonymousClass(), generatedClass);
                        return ret;
                    }
                } catch (InstantiationException e) {
                    e.printStackTrace();
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                }
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
        }

        DexMaker maker = new DexMaker();
        TypeId<?> superClass = TypeId.get("L" + bc.superClass + ";");
        TypeId<?>[] interfaceTypes = new TypeId<?>[bc.interfaces.size()];
        for (int i = 0; i < bc.interfaces.size(); i++) {
            String interfaceName = bc.interfaces.get(i);
            interfaceTypes[i] = TypeId.get("L" + interfaceName + ";");
        }
        TypeId<?> generatedType = TypeId.get("L" + bc.getClassName() + ";");
        maker.declare(generatedType, bc.getClassNameWithDots() + ".generated", Modifier.PUBLIC, superClass, interfaceTypes);

        FieldId<G, Integer> thisNativeIdField = (FieldId<G, Integer>) generatedType.getField(TypeId.INT, NATIVE_ID);
        maker.declare(thisNativeIdField, Modifier.PUBLIC, null);
        {
            MethodId<T, ?> superInit = (MethodId<T, ?>) superClass.getConstructor();
            MethodId<?, ?> thisInit = generatedType.getConstructor();

            Code constructorCode = maker.declare(thisInit, Modifier.PUBLIC);
            Local<Integer> constructorNativeId = constructorCode.newLocal(TypeId.INT);
            Local<G> thisObj = (Local<G>) constructorCode.getThis(generatedType);
            MethodId<ByteCodeGenerator, Integer> getIdMethod = TypeId.get(ByteCodeGenerator.class).getMethod(TypeId.INT, "getId");
            MethodId<ByteCodeGenerator, Void> registerThis = TypeId.get(ByteCodeGenerator.class).getMethod(TypeId.VOID, "registerInstance", TypeId.OBJECT, TypeId.INT);
            constructorCode.invokeDirect(superInit, null, thisObj);
            constructorCode.invokeStatic(getIdMethod, constructorNativeId);
            constructorCode.iput(thisNativeIdField, thisObj, constructorNativeId);
            constructorCode.invokeStatic(registerThis, null, thisObj, constructorNativeId);
            constructorCode.returnVoid();
        }

        List<MethodRecord> virtualMethods = bc.findAllVirtualMethod();
        for (MethodRecord m : virtualMethods) {
            TypeId<?> returnType = TypeId.get(m.method.getReturnType());
            TypeId<?>[] argTypes = getMethodArguments(m.method);
            MethodId<?, ?> mId = generatedType.getMethod(returnType, m.name, argTypes);

            int modifier = m.modifiers & (~Modifier.ABSTRACT);
            Code funcCode = maker.declare(mId, modifier);

            Local<G> funcThisObj = (Local<G>) funcCode.getThis(generatedType);
            Local<Object[]> argList = funcCode.newLocal(TypeId.get(Object[].class));
            Local<Integer> nativeId = funcCode.newLocal(TypeId.INT);
            Local<?> finalRet = funcCode.newLocal(returnType);

            Local<Integer> intRet = null;
            Local<Boolean> boolRet = null;
            Local<Short> shortRet = null;
            Local<Byte> byteRet = null;
            Local<Character> charRet = null;
            Local<Long> longRet = null;
            Local<Float> floatRet = null;
            Local<Double> doubleRet = null;
            Local<Object> objectRet = null;
            if (returnType == TypeId.INT) {
                intRet = funcCode.newLocal(TypeId.INT);
            } else if (returnType == TypeId.BOOLEAN) {
                boolRet = funcCode.newLocal(TypeId.BOOLEAN);
            } else if (returnType == TypeId.SHORT) {
                shortRet = funcCode.newLocal(TypeId.SHORT);
            } else if (returnType == TypeId.BYTE) {
                byteRet = funcCode.newLocal(TypeId.BYTE);
            } else if (returnType == TypeId.CHAR) {
                charRet = funcCode.newLocal(TypeId.CHAR);
            } else if (returnType == TypeId.LONG) {
                longRet = funcCode.newLocal(TypeId.LONG);
            } else if (returnType == TypeId.FLOAT) {
                floatRet = funcCode.newLocal(TypeId.FLOAT);
            } else if (returnType == TypeId.DOUBLE) {
                doubleRet = funcCode.newLocal(TypeId.DOUBLE);
            } else if (returnType != TypeId.VOID) {
                objectRet = funcCode.newLocal(TypeId.OBJECT);
            }

            Local<Integer> arraySize = funcCode.newLocal(TypeId.INT);
            Local<Integer> arrayIdx = funcCode.newLocal(TypeId.INT);
            Local<?> argConvert = funcCode.newLocal(TypeId.OBJECT);
            Local<Integer> nativeIdInteger = funcCode.newLocal(TypeId.get(Integer.class));

            funcCode.loadConstant(arraySize, argTypes.length + 2);
            funcCode.loadConstant(arrayIdx, 0);

            // new Object[arraySize]
            funcCode.newArray(argList, arraySize);
            // nativeId = get __native_id__
            funcCode.iget(thisNativeIdField, nativeId, funcThisObj);
            // nativeId = new Integer
            funcCode.newInstance(nativeIdInteger, TypeId.get(Integer.class).getConstructor(TypeId.INT), nativeId);
            // arrList[0] = nativeId
            funcCode.aput(argList, arrayIdx, nativeIdInteger);
            // i = 1
            funcCode.loadConstant(arrayIdx, 1);
            // arrList[i] = this;
            funcCode.aput(argList, arrayIdx, funcThisObj);

            for (int i = 0; i < argTypes.length; i++) {
                funcCode.loadConstant(arrayIdx, 2 + i);
                TypeId<?> argType = argTypes[i];
                Local<?> argI = funcCode.getParameter(i, argTypes[i]);
                if (argType == TypeId.INT) {
                    funcCode.newInstance((Local<Integer>) argConvert, TypeId.get(Integer.class).getConstructor(TypeId.INT), (Local<Integer>) argI);
                } else if (argType == TypeId.BOOLEAN) {
                    funcCode.newInstance((Local<Boolean>) argConvert, TypeId.get(Boolean.class).getConstructor(TypeId.BOOLEAN), (Local<Boolean>) argI);
                } else if (argType == TypeId.BYTE) {
                    funcCode.newInstance((Local<Byte>) argConvert, TypeId.get(Byte.class).getConstructor(TypeId.BYTE), (Local<Byte>) argI);
                } else if (argType == TypeId.CHAR) {
                    funcCode.newInstance((Local<Character>) argConvert, TypeId.get(Character.class).getConstructor(TypeId.CHAR), (Local<Character>) argI);
                } else if (argType == TypeId.SHORT) {
                    funcCode.newInstance((Local<Short>) argConvert, TypeId.get(Short.class).getConstructor(TypeId.SHORT), (Local<Short>) argI);
                } else if (argType == TypeId.LONG) {
                    funcCode.newInstance((Local<Long>) argConvert, TypeId.get(Long.class).getConstructor(TypeId.LONG), (Local<Long>) argI);
                } else if (argType == TypeId.FLOAT) {
                    funcCode.newInstance((Local<Float>) argConvert, TypeId.get(Float.class).getConstructor(TypeId.FLOAT), (Local<Float>) argI);
                } else if (argType == TypeId.DOUBLE) {
                    funcCode.newInstance((Local<Double>) argConvert, TypeId.get(Double.class).getConstructor(TypeId.DOUBLE), (Local<Double>) argI);
                } else { //object
                    funcCode.cast((Local<Object>) argConvert, argI);
                }
                funcCode.aput(argList, arrayIdx, argConvert);
            }

            final String dispatchPrefix = PROXY_METHOD_NAME;

            if (returnType == TypeId.VOID) {
                MethodId<?, ?> dispatch = TypeId.get(JSFunctionProxy.class).getMethod(TypeId.VOID, dispatchPrefix + "V", TypeId.get(Object[].class));
                funcCode.invokeStatic(dispatch, null, argList);
                funcCode.returnVoid();
            } else if (returnType == TypeId.INT) {
                MethodId<?, Integer> dispatch = TypeId.get(JSFunctionProxy.class).getMethod(TypeId.INT, dispatchPrefix + "I", TypeId.get(Object[].class));
                funcCode.invokeStatic(dispatch, intRet, argList);
                funcCode.returnValue(intRet);
            } else if (returnType == TypeId.BOOLEAN) {
                MethodId<?, Boolean> dispatch = TypeId.get(JSFunctionProxy.class).getMethod(TypeId.BOOLEAN, dispatchPrefix + "Z", TypeId.get(Object[].class));
                funcCode.invokeStatic(dispatch, boolRet, argList);
                funcCode.returnValue(boolRet);
            } else if (returnType == TypeId.SHORT) {
                MethodId<?, Short> dispatch = TypeId.get(JSFunctionProxy.class).getMethod(TypeId.SHORT, dispatchPrefix + "S", TypeId.get(Object[].class));
                funcCode.invokeStatic(dispatch, shortRet, argList);
                funcCode.returnValue(shortRet);
            } else if (returnType == TypeId.BYTE) {
                MethodId<?, Byte> dispatch = TypeId.get(JSFunctionProxy.class).getMethod(TypeId.BYTE, dispatchPrefix + "B", TypeId.get(Object[].class));
                funcCode.invokeStatic(dispatch, byteRet, argList);
                funcCode.returnValue(byteRet);
            } else if (returnType == TypeId.CHAR) {
                MethodId<?, Character> dispatch = TypeId.get(JSFunctionProxy.class).getMethod(TypeId.CHAR, dispatchPrefix + "C", TypeId.get(Object[].class));
                funcCode.invokeStatic(dispatch, charRet, argList);
                funcCode.returnValue(charRet);
            } else if (returnType == TypeId.LONG) {
                MethodId<?, Long> dispatch = TypeId.get(JSFunctionProxy.class).getMethod(TypeId.LONG, dispatchPrefix + "J", TypeId.get(Object[].class));
                funcCode.invokeStatic(dispatch, longRet, argList);
                funcCode.returnValue(longRet);
            } else if (returnType == TypeId.FLOAT) {
                MethodId<?, Float> dispatch = TypeId.get(JSFunctionProxy.class).getMethod(TypeId.FLOAT, dispatchPrefix + "F", TypeId.get(Object[].class));
                funcCode.invokeStatic(dispatch, floatRet, argList);
                funcCode.returnValue(floatRet);
            } else if (returnType == TypeId.DOUBLE) {
                MethodId<?, Double> dispatch = TypeId.get(JSFunctionProxy.class).getMethod(TypeId.DOUBLE, dispatchPrefix + "D", TypeId.get(Object[].class));
                funcCode.invokeStatic(dispatch, doubleRet, argList);
                funcCode.returnValue(doubleRet);
            } else {
                MethodId<?, Object> dispatch = TypeId.get(JSFunctionProxy.class).getMethod(TypeId.OBJECT, dispatchPrefix + "L", TypeId.get(Object[].class));
                funcCode.invokeStatic(dispatch, objectRet, argList);
                funcCode.cast(finalRet, objectRet);
                funcCode.returnValue(finalRet);
            }
        }

        // Create the dex file and load it.
        File outputDir = new File(getJarCacheDir(), bc.getHashKeyForAnonymousClass());
        if(!outputDir.exists()){
            outputDir.mkdirs();
        }

        try {
            generatedClass = bc.packDexToJavaThenLoadClass(maker.generate());
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        }


        try {
            Object ret = generatedClass.newInstance();
            if(ret != null) {
                cachedClassMap.put(bc.getHashKeyForAnonymousClass(), generatedClass);
            }
            return ret;
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        }

        return null;
    }

    public static TypeId<?>[] getMethodArguments(Method m) {
        Class<?> []types = m.getParameterTypes();
        TypeId<?> []ret = new TypeId<?>[types.length];
        for (int i = 0; i < types.length; i++) {
            ret[i] = TypeId.get(types[i]);
        }
        return ret;
    }


    private String superClass = "java/lang/Object";
    private ArrayList<String> interfaces = new ArrayList<>();
    private String className;

    public ByteCodeGenerator() {
    }

    public void setClassName(String className) {
        if (className != null && !className.isEmpty()) {
            this.className = className.replaceAll("\\.", "/");
        }
    }

    public String getClassName() {
        return this.className;
    }

    public String getClassNameWithDots() {
        return className.replaceAll("/", ".");
    }

    public void setSuperClass(String superClass) {
        if (superClass != null && !superClass.isEmpty()) {
            this.superClass = superClass;
        }
    }

    public String getSuperClassDot() {
        return superClass.replaceAll("/", ".");
    }

    public void setInterfaces(String interfaces[]) {
        for (String itf : interfaces) {
            this.interfaces.add(itf.replaceAll("\\.", "/"));
        }
    }

    /**
     * ID for objects generated by `newInstance`
     *
     * @return ID
     */
    public static int getId() {
        return object_id++;
    }

    /**
     * Create folders for bytecode/class data
     */
    static public void init() {
//        renameAndDelete(ByteCodeGenerator.getDexDir());
//        renameAndDelete(ByteCodeGenerator.getGenClassDir());
//        renameAndDelete(ByteCodeGenerator.getJarCacheDir());
    }

    private static void renameAndDelete(File dir) {
        if (!dir.exists()) return;
        if (dir.isDirectory()) {
            String oldPath = dir.getAbsolutePath();
            if (oldPath.endsWith("/")) oldPath = oldPath.substring(0, oldPath.length() - 1);
            File tmpDir = new File(oldPath + "_to_delete");
            if (tmpDir.exists()) deleteFilesInFolder(tmpDir);
            dir.renameTo(tmpDir);
            new Thread(new Runnable() {
                @Override
                public void run() {
                    deleteFilesInFolder(tmpDir);
                }
            }).start();
        } else {
            throw new RuntimeException(dir.toString() + " is expected to be a directory!");
        }
    }

    @SuppressWarnings("ResultOfMethodCallIgnored")
    private static void deleteFilesInFolder(File dir) {
        if (dir.isDirectory()) {
            String[] children = dir.list();
            for (String child : children) {
                File sub = new File(dir, child);
                if (sub.isFile()) {
                    sub.delete();
                } else {
                    deleteFilesInFolder(sub);
                }
            }
        }

        dir.delete();
    }

    native static public void registerInstance(Object self, int id);

    /**
     * Redirect Java callback to JS object function attribute
     *
     * @param finish
     * @param methodName
     * @param args
     * @return
     */
    native static public Object callJS(AtomicBoolean finish, String methodName, Object[] args);


    /**
     * Query all `abstract` methods
     *
     * @return
     */
    private List<MethodRecord> findAllVirtualMethod() {
        List<Method> methods = this.superClass.equals("java/lang/Object") ? new ArrayList<>() : this.queryVirutalMethodsForInterface(this.getSuperClassDot());
        for (String itf : this.interfaces) {
            methods.addAll(this.queryVirutalMethodsForInterface(itf));
        }
        List<MethodRecord> ret = new ArrayList<>();
        for (Method m : methods) {
            ret.add(recordAbstractMethod(m));
        }
        return ret;
    }

    private MethodRecord recordAbstractMethod(Method m) {
        MethodRecord vm = new MethodRecord();
        vm.modifiers = m.getModifiers();
        vm.method = m;
        vm.name = m.getName();
        return vm;
    }

    /**
     * Query all abstract methods for single class
     *
     * @param classPath
     * @return
     */
    private List<Method> queryVirutalMethodsForInterface(String classPath) {
        ArrayList<Method> methods = new ArrayList<>();
        try {
            if (classPath.contains("/")) classPath = classPath.replaceAll("/", ".");
            Class<?> c = Class.forName(classPath);
            Method[] all = c.getMethods();
            for (Method m : all) {
                int modifiers = m.getModifiers();
                if ((modifiers & Modifier.ABSTRACT) != 0
                        && (modifiers & Modifier.STATIC) == 0
                        && (modifiers & Modifier.PUBLIC) != 0) {
                    // System.out.println("impl method " + m.getName());
                    methods.add(m);
                }
            }
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
        return methods;
    }

    public static File getDexDir() {
        return new File(Cocos2dxHelper.getCacheDir().getPath() + "/j2j/dex");
    }

    public static File getGenClassDir() {
        return new File(Cocos2dxHelper.getCacheDir().getPath() + "/j2j/genclasses");
    }

    public static File getJarCacheDir() {
        return new File(Cocos2dxHelper.getCacheDir().getPath() + "/j2j/jarCache");
    }

    public String getHashKeyForAnonymousClass() {
        // With the java libraries
        ArrayList<String> list = new ArrayList<>();
        list.add(this.superClass.trim());
        for (String intf : this.interfaces) {
            list.add(intf.trim());
        }
        Collections.sort(list);
        StringBuilder sb = new StringBuilder();
        for (String it : list) {
            sb.append(it);
        }

        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-1");
            digest.reset();
            digest.update(sb.toString().getBytes("utf8"));
            return String.format("%040x", new BigInteger(1, digest.digest()));
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    private File getJarFile() {
        File jarCacheDir = getJarCacheDir();
        if (!jarCacheDir.exists()) {
            jarCacheDir.mkdirs();
        }
        return new File(jarCacheDir, "GenJar_" + this.getHashKeyForAnonymousClass() + ".jar");
    }

    private Class<?> packDexToJavaThenLoadClass(byte[] dex) throws IOException, ClassNotFoundException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException {

        File result = getJarFile();
        JarOutputStream jarOut = new JarOutputStream(new FileOutputStream(result));
        jarOut.putNextEntry(new JarEntry("classes.dex"));
        jarOut.write(dex);
        jarOut.closeEntry();
        jarOut.close();
        return cacheClassLoader(result).loadClass(this.getClassNameWithDots());
    }

    public ClassLoader cacheClassLoader(File jarFile) {

        try {
            ClassLoader loader = (ClassLoader) Class.forName("dalvik.system.DexClassLoader")
                    .getConstructor(String.class, String.class, String.class, ClassLoader.class)
                    .newInstance(jarFile.getPath(), jarFile.getParentFile().getAbsolutePath(), null, getClass().getClassLoader());
            return loader;
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
        return null;
    }
}
