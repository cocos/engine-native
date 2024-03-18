# the minimum version of CMake.

cmake_minimum_required(VERSION 3.8)
set(CC_LIB_NAME cocos)
set(CC_PROJ_SOURCES)
set(CC_COCOS_SOURCES)
set(CC_COMMON_SOURCES)
set(CC_ALL_SOURCES)

option(APP_NAME "Project Name" "test-cases")
project(${APP_NAME} CXX)

set(CMAKE_CXX_FLAGS_DEBUG  "-Werror=return-type -ferror-limit=0")

enable_language(C ASM)
set(CMAKE_CXX_STANDARD 17)

include(${COCOS_X_PATH}/CMakeLists.txt)

list(APPEND CC_ALL_SOURCES ${CC_COCOS_SOURCES} ${CC_COMMON_SOURCES} ${CC_PROJ_SOURCES})
add_library(${CC_LIB_NAME} SHARED ${CC_ALL_SOURCES})

# setup default flags
cc_apply_definations(${CC_LIB_NAME})

find_library( # Sets the name of the path variable.
EGL-lib
# Specifies the name of the NDK library that
# you want CMake to locate.
EGL )
find_library( # Sets the name of the path variable.
GLESv3-lib
# Specifies the name of the NDK library that
# you want CMake to locate.
GLESv3)

find_library( hilog-lib
hilog_ndk.z )

find_library( # Sets the name of the path variable.
              libace-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              ace_ndk.z )
find_library( # Sets the name of the path variable.
              libnapi-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              ace_napi.z )
find_library( # Sets the name of the path variable.
              libuv-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              uv )

find_library( # Sets the name of the path variable.
              rawfile-lib
              # Specifies the name of the NDK library that
              # you want CMake to locate.
              rawfile.z )
message(STATUS, "rawfile=${rawfile-lib}")
target_link_libraries(${CC_LIB_NAME} PUBLIC
${EGL-lib} ${GLESv3-lib} ${hilog-lib} ${libace-lib} ${libnapi-lib} ${libuv-lib} ${rawfile-lib} libnative_drawing.so libc++.a libOpenSLES.so
${CC_EXTERNAL_LIBS}
)



#cc_openharmony_before_target(${CC_LIB_NAME})

#cc_openharmony_after_target(${CC_LIB_NAME})