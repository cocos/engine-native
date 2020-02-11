cmake_minimum_required (VERSION 3.8)

set (LIBCOCOS2D_ROOT_DIR "${COCOS_SDK_ROOT}")
set (LIBCOCOS2D_SOURCE_ROOT_DIR "${LIBCOCOS2D_ROOT_DIR}/cocos")

file (GLOB_RECURSE LIBCOCOS2D_SOURCE
    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/audio/AudioEngine.cpp"
    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/base/*.cpp"
    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/cocos2d.cpp"
    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/math/*.cpp"

    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/network/CCDownloader-curl.cpp"
    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/network/CCDownloader.cpp"
    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/network/HttpClient.cpp"
    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/network/HttpCookie.cpp"
    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/network/SocketIO.cpp"
    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/network/Uri.cpp"
    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/network/WebSocket-libwebsockets.cpp"

    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/platform/CCFileUtils.cpp"
    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/platform/CCImage.cpp"
    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/platform/CCSAXParser.cpp"
    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/platform/desktop/CCGLView-desktop.cpp"
    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/renderer/core/*.cc"
    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/renderer/core/*.cpp"

    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_audioengine_auto.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_auto.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_extension_auto.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_network_auto.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/event/EventDispatcher.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/config.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/HandleObject.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/MappingUtils.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/RefCounter.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/State.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/v8/Class.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/v8/debugger/env.cc"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/v8/debugger/http_parser.c"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/v8/debugger/inspector_agent.cc"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/v8/debugger/inspector_io.cc"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/v8/debugger/inspector_socket.cc"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/v8/debugger/inspector_socket_server.cc"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/v8/debugger/node.cc"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/v8/debugger/node_debug_options.cc"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/v8/debugger/SHA1.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/v8/debugger/util.cc"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/v8/Object.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/v8/ObjectWrap.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/v8/ScriptEngine.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/v8/Utils.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/jswrapper/Value.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/manual/jsb_classtype.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/manual/jsb_cocos2dx_manual.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/manual/jsb_cocos2dx_network_manual.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/manual/jsb_conversions.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/manual/jsb_global.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/manual/jsb_helper.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/manual/jsb_opengl_manual.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/manual/jsb_opengl_utils.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/manual/jsb_platfrom_win32.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/manual/jsb_socketio.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/manual/jsb_websocket.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/scripting/js-bindings/manual/jsb_xmlhttprequest.cpp"

    "${LIBCOCOS2D_SOURCE_ROOT_DIR}/storage/local-storage/LocalStorage.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/extensions/assets-manager/*.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/external/sources/ConvertUTF/*.c"
    "${LIBCOCOS2D_ROOT_DIR}/external/sources/ConvertUTF/*.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/external/sources/tinyxml2/*.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/external/sources/unzip/*.cpp"
    "${LIBCOCOS2D_ROOT_DIR}/external/sources/xxtea/*.cpp"
)

if (WIN32)
    set (VS_GLOBAL_ROOTNAMESPACE "cocos2d-x.win32")
    set (VS_GLOBAL_KEYWORD "Win32Proj")
    set (VS_GLOBAL_PROJECT_TYPES "{98A51BA8-FC3A-415B-AC8F-8C7BD464E93E}")
    file (GLOB_RECURSE LIBCOCOS2D_SOURCE_AUDIO_WIN32 "${LIBCOCOS2D_SOURCE_ROOT_DIR}/audio/win32/*.cpp")
    list (APPEND LIBCOCOS2D_SOURCE
        ${LIBCOCOS2D_SOURCE_AUDIO_WIN32}
        "${LIBCOCOS2D_SOURCE_ROOT_DIR}/platform/win32/CCApplication-win32.cpp"
        "${LIBCOCOS2D_SOURCE_ROOT_DIR}/platform/win32/CCCanvasRenderingContext2D-win32.cpp"
        "${LIBCOCOS2D_SOURCE_ROOT_DIR}/platform/win32/CCDevice-win32.cpp"
        "${LIBCOCOS2D_SOURCE_ROOT_DIR}/platform/win32/CCFileUtils-win32.cpp"
        "${LIBCOCOS2D_SOURCE_ROOT_DIR}/platform/win32/CCUtils-win32.cpp"
        "${LIBCOCOS2D_SOURCE_ROOT_DIR}/ui/edit-box/EditBox-win32.cpp"
    )
endif ()

add_library (libcocos2d ${LIBCOCOS2D_SOURCE})
target_compile_definitions (libcocos2d PUBLIC
    CC_STATIC
    COCOS2D_DEBUG=1
    JS_HAVE____INTN
    JS_INTPTR_TYPE=int
    GLFW_EXPOSE_NATIVE_WGL
    __MWERKS__ # NECCESSARY ?
    CC_CORE_EXPORTS
)
target_include_directories (libcocos2d PUBLIC
    "${LIBCOCOS2D_ROOT_DIR}"
    "${LIBCOCOS2D_ROOT_DIR}/cocos"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/renderer"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/renderer/core"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/renderer/gfx"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/platform"
    "${LIBCOCOS2D_ROOT_DIR}/cocos/editor-support"
    "${LIBCOCOS2D_ROOT_DIR}/external/sources"
    "${LIBCOCOS2D_ROOT_DIR}/external/sources/khronos"
    "${LIBCOCOS2D_ROOT_DIR}/external/sources/tommyds"
    "${LIBCOCOS2D_ROOT_DIR}/external/unzip"
    "${LIBCOCOS2D_ROOT_DIR}/external/sources/firefox"
)
if (MSVC)
    target_compile_options(libcocos2d PRIVATE /W3 /wd4138 /wd4267 /wd4251 /wd4244)

    # cocos2dx.props
    target_compile_definitions (libcocos2d PUBLIC
        WIN32
        _WIN32
        _WINDOWS
        _UNICODE
        UNICODE
        _USRDLL
        _LIB
        XP_WIN
        _CRT_SECURE_NO_WARNINGS
        GLFW_EXPOSE_NATIVE_WIN32
        _VARIADIC_MAX=10
    )
    set_target_properties(libcocos2d PROPERTIES LINK_FLAGS "/INCREMENTAL:NO")
    set (CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    target_include_directories (libcocos2d PUBLIC
        "${LIBCOCOS2D_ROOT_DIR}/external/sources/jemalloc/include-win"
        "${LIBCOCOS2D_ROOT_DIR}/external/sources/jemalloc/include-win/msvc_compat"
        "${LIBCOCOS2D_ROOT_DIR}/external/win32/include"
        "${LIBCOCOS2D_ROOT_DIR}/external/win32/include/freetype"
        "${LIBCOCOS2D_ROOT_DIR}/external/win32/include/zlib"
        "${LIBCOCOS2D_ROOT_DIR}/external/win32/include/v8"
        "${LIBCOCOS2D_ROOT_DIR}/external/win32/include/uv"
        "${LIBCOCOS2D_ROOT_DIR}/external/win32/include/chipmunk"
    )
    target_link_directories (libcocos2d PUBLIC
        "${LIBCOCOS2D_ROOT_DIR}/external/win32/libs"
    )
    target_link_libraries(libcocos2d PUBLIC
        opengl32.lib
        glew32.lib
        libzlib.lib
        libiconv.lib
        freetype.lib
        winmm.lib
        ws2_32.lib
        Psapi.lib
        Iphlpapi.lib
        Userenv.lib
        libcurl.lib
        websockets.lib
        libwebp.lib
        sqlite3.lib
        OpenAL32.lib
        libmpg123.lib
        libvorbisfile.lib
        libuv.lib
        v8.dll.lib
        v8_libbase.dll.lib
        v8_libplatform.dll.lib
    )
endif ()
