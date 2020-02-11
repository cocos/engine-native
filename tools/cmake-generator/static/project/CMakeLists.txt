
cmake_minimum_required (VERSION 3.8)

project (${CREATOR_PROJECT_NAME})

include ("../libcocos2d/CMakeLists.txt")

file (GLOB MY_PROJECT_SOURCE
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/manual/jsb_module_register.cpp"
    "Classes/AppDelegate.cpp"
    "win32/main.cpp"
)

file (GLOB MY_PROJECT_HEADER
    "Classes/AppDelegate.h"
    "win32/main.h"
    "win32/resource.h"
)

file (GLOB MY_PROJECT_RESOURCES
    "win32/game.rc"
)

add_executable (${CREATOR_PROJECT_NAME} WIN32 ${MY_PROJECT_SOURCE} ${MY_PROJECT_RESOURCES})
target_include_directories(${CREATOR_PROJECT_NAME} PRIVATE
    "Classes"
    "${LIBCOCOS2D_ROOT_DIR}"
    "${LIBCOCOS2D_ROOT_DIR}/cocos"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/base"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/storage"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/editor-support"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/auto"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/manual"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/audio/include"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/platform"
    "${LIBCOCOS2D_ROOT_DIR}/extensions"
)
target_link_libraries (${CREATOR_PROJECT_NAME} PRIVATE
    libcocos2d
)
if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${CREATOR_PROJECT_NAME})

    target_include_directories(${CREATOR_PROJECT_NAME} PRIVATE
        "Classes"
    )

    file (GLOB CREATOR_PROJECT_DLLS
        "${LIBCOCOS2D_ROOT_DIR}/external/win32/libs/*.dll"
    )

    foreach(CREATOR_PROJECT_DLL IN LISTS CREATOR_PROJECT_DLLS)
        add_custom_command(TARGET ${CREATOR_PROJECT_NAME} POST_BUILD        # Adds a post-build event to MyTest
            COMMAND ${CMAKE_COMMAND} -E
                copy_if_different
                    "${CREATOR_PROJECT_DLL}"
                    "$<TARGET_FILE_DIR:${CREATOR_PROJECT_NAME}>"
        )
    endforeach ()
endif ()