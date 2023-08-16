enable_language(C ASM)
set(DEVELOPMENT_TEAM    ""  CACHE STRING "APPLE Developtment Team")
set(RES_DIR             ""  CACHE STRING "Resource path")
set(COCOS_X_PATH        ""  CACHE STRING "Path to engine/native/")

set(TARGET_OSX_VERSION "10.14" CACHE STRING "Target MacOSX version" FORCE)
set(TARGET_IOS_VERSION "11.0"  CACHE STRING "Target iOS version" FORCE)

set(CMAKE_CXX_STANDARD 17)

if(NOT COCOS_X_PATH)
    message(FATAL_ERROR "COCOS_X_PATH is not set!")
endif()

include(${COCOS_X_PATH}/CMakeLists.txt)