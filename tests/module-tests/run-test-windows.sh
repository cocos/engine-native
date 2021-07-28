#!/bin/bash

set -x
set -e

if [ -f "$HW_NDK/build/cmake/ohos.toolchain.cmake" ]; then

    cmake -B build-ohos \
    -DCMAKE_TOOLCHAIN_FILE="$HW_NDK/build/cmake/ohos.toolchain.cmake" \
    -DCMAKE_MAKE_PROGRAM=ninja \
    -GNinja \
    -DOHOS_ARCH=arm64-v8a 

    for target in test-log test-bindings test-math test-fs 
    do
        cmake --build build-ohos --target $target
    done

fi

if [ -f "$NDK_ROOT/build/cmake/android.toolchain.cmake" ]; then
    ANDOIR_TOOLCHAIN_FILE="$NDK_ROOT/build/cmake/android.toolchain.cmake"
else
    ANDOIR_TOOLCHAIN_FILE="$ANDROID_NDK/build/cmake/android.toolchain.cmake"
fi

cmake -B build-win32 -A win32 
cmake -B build-android \
 -DCMAKE_TOOLCHAIN_FILE="$ANDOIR_TOOLCHAIN_FILE" \
 -DANDROID_PLATFORM=android-21 \
 -DCMAKE_MAKE_PROGRAM=ninja \
 -DANDROID_LD=lld \
 -GNinja


for target in test-log test-bindings test-math test-fs 
do
cmake --build build-android --target $target
cmake --build build-win32 --target $target --config Release 
done

./build-win32/log/Release/test-log.exe
./build-win32/math/Release/test-math.exe
./build-win32/bindings/Release/test-bindings.exe
./build-win32/filesystem/Release/test-fs.exe

# cmake --build build-win32

