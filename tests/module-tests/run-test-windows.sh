#!/bin/bash

set -x
set -e
cmake -B build-win32 -A win32 
cmake -B build-android \
 -DCMAKE_TOOLCHAIN_FILE="$NDK_ROOT/build/cmake/android.toolchain.cmake" \
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
