add_subdirectory(gfx-base)
add_subdirectory(gfx-agent)

add_subdirectory(gfx-gles-common)
add_subdirectory(gfx-gles2)
add_subdirectory(gfx-gles3)
add_subdirectory(gfx-vulkan)

if(COCOS_PLATFORM_IOS OR COCOS_PLATFORM_OSX)
    add_subdirectory(gfx-metal)
endif()
