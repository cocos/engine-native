cmake_minimum_required(VERSION 2.8)

set(APP_NAME "CocosGame" CACHE STRING "Project Name")
project(${APP_NAME}WASM)

set(ENGINE_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../../..)

include(${ENGINE_ROOT_DIR}/cmake/predefine.cmake)

message("yoooooooooooooooooooooooooooooooooooooooooooooooooo")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-nonportable-include-path -fno-exceptions")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -D_DEBUG=1 -Wno-unused -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g0 -DNDEBUG=1 -flto -O3")

AUX_SOURCE_DIRECTORY(
    .
    WGPU_SRC
)

set(PLATFORM_DEPENDS
    ../../../cocos/platform/win32/Utils-win32.cpp
)

AUX_SOURCE_DIRECTORY(
    ../../../cocos/base
    COCOS_BASE
)

AUX_SOURCE_DIRECTORY(
    ../../../cocos/renderer/gfx-base
    GFX_BASE
)

AUX_SOURCE_DIRECTORY(
    ../../../cocos/renderer/gfx-agent
    GFX_AGENT
)

AUX_SOURCE_DIRECTORY(
    ../../../cocos/renderer/gfx-validator
    GFX_VALIDATOR
)

AUX_SOURCE_DIRECTORY(
    ../../../cocos/renderer/gfx-empty
    GFX_EMPTY
)

AUX_SOURCE_DIRECTORY(
    ../../../cocos/renderer/pipeline
    PIPELINE
)

set(RENDERER
    ../../../cocos/renderer/GFXDeviceManager.h
    ${GFX_BASE}
    ${GFX_AGENT}
    ${GFX_VALIDATOR}
    ${GFX_EMPTY}
    ${PIPELINE}
)

set(NATIVE_SRC
    ${COCOS_BASE}
    ${RENDERER}
    ${PLATFORM_DEPENDS}
    ${WGPU_SRC}
)

set(EXPORTS
    ../gfx-base/GFXDevice.cpp 
    ../gfx-base/GFXDevice.h
)

add_executable(${APP_NAME}WASM ${EXPORTS} ${NATIVE_SRC})

target_include_directories(
	${APP_NAME}WASM PRIVATE "${CMAKE_CURRENT_LIST_DIR}/inc"
	${CC_EXTERNAL_INCLUDES}
	${ENGINE_ROOT_DIR}
	${ENGINE_ROOT_DIR}/cocos
    ${ENGINE_ROOT_DIR}/cocos/base
	${ENGINE_ROOT_DIR}/cocos/renderer
	${ENGINE_ROOT_DIR}/cocos/platform
	${ENGINE_ROOT_DIR}/cocos/renderer/core
	#$<$<BOOL:USE_SE_JSC>:${CWD}/cocos/bindings/jswrapper>
	${CC_EXTERNAL_PRIVATE_INCLUDES}
)

message(${ENGINE_ROOT_DIR}/cocos)
set_target_properties(${APP_NAME}WASM PROPERTIES LINK_FLAGS "--bind")
message("${CWD}cocos/renderer")