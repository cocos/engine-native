set(CC_PLATFORM_OPENHARMONY 14)
add_definitions(-DCC_PLATFORM_OPENHARMONY=${CC_PLATFORM_OPENHARMONY})

set(CC_PLATFORM ${CC_PLATFORM_OPENHARMONY})
add_definitions(-DOPENHARMONY=${CC_PLATFORM_OPENHARMONY})
add_definitions(-DCC_PLATFORM=${CC_PLATFORM})
set(CMAKE_CXX_FLAGS "-fvisibility=hidden -fvisibility-inlines-hidden ${CMAKE_CXX_FLAGS}")
if("${OHOS_ARCH}" STREQUAL "armeabi-v7a")
    set(CMAKE_CXX_FLAGS "-march=armv7a ${CMAKE_CXX_FLAGS}")
endif()

MESSAGE(STATUS "platform: ${CMAKE_SYSTEM_NAME}")

################################# engine source code ##################################
set(CC_COCOS_SOURCES)
set(ENGINE_NAME cocos_engine)

# Should be enable someday in the future
# set(CMAKE_CXX_FLAGS "${WERROR_FLAGS}")

################################# options ############################################
option(CC_USE_GFX_RENDERER         "GFX Render"                         ON)
option(CC_USE_VIDEO                "Enable VideoPlayer Component"       ON)
option(CC_USE_WEBVIEW              "Enable WebView Component"           ON)
option(CC_USE_AUDIO                "Enable Audio"                       ON)
option(CC_USE_SOCKET               "Enable WebSocket & SocketIO"        ON)
option(CC_USE_WEBSOCKET_SERVER     "Enable WebSocket Server"            OFF)
option(CC_USE_MIDDLEWARE           "Enable Middleware"                  ON)
option(CC_USE_SPINE                "Enable Spine"                       ON)
option(CC_USE_DRAGONBONES          "Enable Dragonbones"                 ON)
option(CC_USE_SE_NAPI              "Enable Dragonbones"                 ON)
option(CC_USE_PARTICLE             "Enable Particle"                    ON)


################################# external source code ################################
set(EXTERNAL_ROOT ${CMAKE_CURRENT_LIST_DIR}/external)
if(NOT EXISTS ${EXTERNAL_ROOT}/CMakeLists.txt)
    message(FATAL_ERROR "Please download external libraries! File ${CMAKE_CURRENT_LIST_DIR}/external/CMakeLists.txt not exist!")
endif()

include_directories(${EXTERNAL_ROOT}/sources)
include(${EXTERNAL_ROOT}/CMakeLists.txt)

################################# cocos engine source code ################################

##### cocos2d
list(APPEND CC_COCOS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/cocos/cocos2d.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/cocos2d.h
)

##### platform
list(APPEND CC_COCOS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/CCPlatformDefine.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/CCPlatformDefine-openharmony.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/WorkerMessageQueue.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/WorkerMessageQueue.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/FileUtils-openharmony.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/FileUtils-openharmony.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/CCGL-openharmony.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/CCDevice-openharmony.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/OpenHarmonyPlatform.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/OpenHarmonyPlatform.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/render/egl_core.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/render/egl_core.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/CCDevice.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/CCApplication.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/CCCanvasRenderingContext2D.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/CCFileUtils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/CCFileUtils.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/CCGL.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/CCImage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/CCImage.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/CCPlatformConfig.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/CCSAXParser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/CCSAXParser.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/CCStdC.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/AppDelegate.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/AppDelegate.h
)

##### base
list(APPEND CC_COCOS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/astc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/astc.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/base64.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/base64.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCAutoreleasePool.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCAutoreleasePool.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/ccCArray.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/ccCArray.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/ccConfig.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCConfiguration.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCConfiguration.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCData.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCData.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCGLUtils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCGLUtils.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCLog.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCLog.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/ccMacros.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCMap.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/ccRandom.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/ccRandom.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCRef.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCRef.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCRefPtr.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCRenderTexture.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCRenderTexture.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCScheduler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCScheduler.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCThreadPool.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCThreadPool.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/ccTypes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/ccTypes.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/ccUTF8.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/ccUTF8.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/ccUtils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/ccUtils.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCValue.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCValue.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/CCVector.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/csscolorparser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/csscolorparser.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/etc1.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/etc1.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/etc2.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/etc2.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/pvr.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/pvr.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/TGAlib.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/TGAlib.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/uthash.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/utlist.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/ZipUtils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/base/ZipUtils.h
)

##### 2d
list(APPEND CC_COCOS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/cocos/2d/CCFontAtlas.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/2d/CCFontAtlas.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/2d/CCFontFreetype.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/2d/CCFontFreetype.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/2d/CCLabelLayout.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/2d/CCLabelLayout.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/2d/CCTTFLabelAtlasCache.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/2d/CCTTFLabelAtlasCache.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/2d/CCTTFLabelRenderer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/2d/CCTTFLabelRenderer.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/2d/CCTTFTypes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/2d/CCTTFTypes.h
)

##### math
list(APPEND CC_COCOS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/CCGeometry.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/CCGeometry.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/CCMath.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/CCMathBase.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/CCVertex.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/CCVertex.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/Mat3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/Mat3.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/Mat4.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/Mat4.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/MathUtil.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/MathUtil.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/Quaternion.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/Quaternion.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/Vec2.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/Vec2.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/Vec3.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/Vec3.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/Vec4.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/math/Vec4.h
)

##### network
list(APPEND CC_COCOS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/cocos/network/CCDownloader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/network/CCDownloader.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/network/CCDownloader-curl.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/network/CCDownloader-curl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/network/CCIDownloaderImpl.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/network/HttpClient.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/network/HttpClient.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/network/HttpCookie.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/network/HttpCookie.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/network/HttpRequest.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/network/HttpResponse.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/network/Uri.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/network/Uri.h
)

##### js-bindg event
list(APPEND CC_COCOS_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/event/CustomEventTypes.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/event/EventDispatcher.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/event/EventDispatcher.h
)

##### jswrapper
list(APPEND CC_COCOS_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/config.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/config.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/HandleObject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/HandleObject.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/MappingUtils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/MappingUtils.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/Object.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/RefCounter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/RefCounter.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/SeApi.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/State.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/State.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/Value.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/Value.hpp
)

##### napi script engine
list(APPEND CC_COCOS_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/napi/Class.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/napi/Class.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/napi/CommonHeader.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/napi/HelperMacros.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/napi/HelperMacros.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/napi/native_common.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/napi/Object.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/napi/Object.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/napi/ScriptEngine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/napi/ScriptEngine.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/napi/SeApi.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/napi/Utils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/napi/Utils.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/napi/NapiHelper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/napi/NapiHelper.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/napi/NapiInit.cpp
)

##### CCDevice CCApplication modules:screen、system
list(APPEND CC_COCOS_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/modules/CCApplication-openharmony.cpp
)

##### js-bindings manual
list(APPEND CC_COCOS_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_classtype.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_classtype.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_cocos2dx_manual.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_cocos2dx_manual.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_cocos2dx_network_manual.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_cocos2dx_network_manual.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_conversions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_conversions.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_global.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_global.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_helper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_helper.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_module_register.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_module_register.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_node.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_opengl_manual.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_opengl_manual.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_opengl_utils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_opengl_utils.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_platform.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_websocket.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_websocket.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_xmlhttprequest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_xmlhttprequest.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_platform_openharmony.cpp
)

##### js-bindings auto
list(APPEND CC_COCOS_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_auto.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_auto.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_editor_support_auto.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_editor_support_auto.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_extension_auto.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_extension_auto.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_network_auto.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_network_auto.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_particle_auto.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_webview_auto.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_gfx_auto.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_gfx_manual.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_renderer_manual.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_renderer_auto.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_cocos2dx_extension_manual.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_spine_manual.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_spine_auto.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_dragonbones_auto.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_dragonbones_manual.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_webview_auto.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_audioengine_auto.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_websocket.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_socketio.hpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_websocket_server.hpp
)

##### canvas rendering
list(APPEND CC_COCOS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/modules/CCCanvasRenderingContext2D-openharmony.cpp
)

##### localstorage
list(APPEND CC_COCOS_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/cocos/storage/local-storage/LocalStorage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/storage/local-storage/LocalStorage.h
)

##### edit-box
list(APPEND CC_COCOS_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/cocos/ui/edit-box/EditBox.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/ui/edit-box/EditBox-openharmony.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/ui/edit-box/EditBox-openharmony.cpp
)

##### editor-support
list(APPEND CC_COCOS_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/IOBuffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/IOBuffer.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/IOTypedArray.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/IOTypedArray.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/MeshBuffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/MeshBuffer.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/middleware-adapter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/middleware-adapter.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/MiddlewareMacro.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/MiddlewareManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/MiddlewareManager.h
    ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/TypedArrayPool.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/TypedArrayPool.h
)

##### extensions
list(APPEND CC_COCOS_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/extensions/cocos-ext.h
    ${CMAKE_CURRENT_LIST_DIR}/extensions/ExtensionExport.h
    ${CMAKE_CURRENT_LIST_DIR}/extensions/ExtensionMacros.h
    ${CMAKE_CURRENT_LIST_DIR}/extensions/assets-manager/AssetsManagerEx.cpp
    ${CMAKE_CURRENT_LIST_DIR}/extensions/assets-manager/AssetsManagerEx.h
    ${CMAKE_CURRENT_LIST_DIR}/extensions/assets-manager/CCAsyncTaskPool.cpp
    ${CMAKE_CURRENT_LIST_DIR}/extensions/assets-manager/CCAsyncTaskPool.h
    ${CMAKE_CURRENT_LIST_DIR}/extensions/assets-manager/CCEventAssetsManagerEx.cpp
    ${CMAKE_CURRENT_LIST_DIR}/extensions/assets-manager/CCEventAssetsManagerEx.h
    ${CMAKE_CURRENT_LIST_DIR}/extensions/assets-manager/Manifest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/extensions/assets-manager/Manifest.h
)

##### USE_GFX_RENDERER
if(CC_USE_GFX_RENDERER)
    list(APPEND CC_COCOS_SOURCES 
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/Types.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/Types.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/Macro.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/DeviceGraphics.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/DeviceGraphics.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/FrameBuffer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/FrameBuffer.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/GFX.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/GFX.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/GFXUtils.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/GFXUtils.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/GraphicsHandle.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/GraphicsHandle.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/IndexBuffer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/IndexBuffer.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/Program.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/Program.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/RenderBuffer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/RenderBuffer.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/RenderTarget.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/RenderTarget.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/State.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/State.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/Texture.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/Texture.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/Texture2D.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/Texture2D.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/VertexBuffer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/VertexBuffer.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/VertexFormat.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx/VertexFormat.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/BaseRenderer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/BaseRenderer.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Camera.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Camera.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Config.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Config.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Effect.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Effect.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/EffectBase.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/EffectBase.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/EffectVariant.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/EffectVariant.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/ForwardRenderer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/ForwardRenderer.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/INode.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/InputAssembler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/InputAssembler.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Light.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Light.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Model.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Model.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Pass.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Pass.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/ProgramLib.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/ProgramLib.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Renderer.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/RendererUtils.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/RendererUtils.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Scene.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Scene.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Technique.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/Technique.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/View.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer/View.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/Assembler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/Assembler.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/AssemblerBase.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/AssemblerBase.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/AssemblerSprite.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/AssemblerSprite.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/CustomAssembler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/CustomAssembler.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/MaskAssembler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/MaskAssembler.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/MeshAssembler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/MeshAssembler.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/Particle3DAssembler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/Particle3DAssembler.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/RenderData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/RenderData.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/RenderDataList.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/RenderDataList.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/SimpleSprite2D.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/SimpleSprite2D.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/SimpleSprite3D.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/SimpleSprite3D.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/SlicedSprite2D.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/SlicedSprite2D.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/SlicedSprite3D.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/SlicedSprite3D.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/TiledMapAssembler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler/TiledMapAssembler.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/MemPool.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/MemPool.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/MeshBuffer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/MeshBuffer.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/ModelBatcher.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/ModelBatcher.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/NodeMemPool.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/NodeMemPool.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/NodeProxy.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/NodeProxy.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/ParallelTask.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/ParallelTask.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/RenderFlow.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/RenderFlow.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/scene-bindings.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/StencilManager.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/StencilManager.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/memop/RecyclePool.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_gfx_auto.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_renderer_auto.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_renderer_manual.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_gfx_manual.cpp
    )
endif() # USE_GFX_RENDERER

##### CC_USE_SPINE
if(CC_USE_SPINE)
    list(APPEND CC_COCOS_SOURCES 
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Animation.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Animation.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/AnimationState.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/AnimationState.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/AnimationStateData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/AnimationStateData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Atlas.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Atlas.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/AtlasAttachmentLoader.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/AtlasAttachmentLoader.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Attachment.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Attachment.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/AttachmentLoader.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/AttachmentLoader.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/AttachmentTimeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/AttachmentTimeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/AttachmentType.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/BlendMode.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Bone.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Bone.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/BoneData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/BoneData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/BoundingBoxAttachment.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/BoundingBoxAttachment.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/ClippingAttachment.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/ClippingAttachment.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Color.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/ColorTimeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/ColorTimeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Constraint.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Constraint.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/ConstraintData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/ConstraintData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/ContainerUtil.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/CurveTimeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/CurveTimeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Debug.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/DeformTimeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/DeformTimeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/dll.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/DrawOrderTimeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/DrawOrderTimeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Event.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Event.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/EventData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/EventData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/EventTimeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/EventTimeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Extension.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Extension.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/HashMap.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/HasRendererObject.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/IkConstraint.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/IkConstraint.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/IkConstraintData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/IkConstraintData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/IkConstraintTimeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/IkConstraintTimeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Json.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Json.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/LinkedMesh.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/LinkedMesh.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/MathUtil.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/MathUtil.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/MeshAttachment.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/MeshAttachment.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/MixBlend.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/MixDirection.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/PathAttachment.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/PathAttachment.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/PathConstraint.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/PathConstraint.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/PathConstraintData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/PathConstraintData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/PathConstraintMixTimeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/PathConstraintMixTimeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/PathConstraintPositionTimeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/PathConstraintPositionTimeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/PathConstraintSpacingTimeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/PathConstraintSpacingTimeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/PointAttachment.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/PointAttachment.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Pool.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/PositionMode.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/RegionAttachment.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/RegionAttachment.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/RotateMode.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/RotateTimeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/RotateTimeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/RTTI.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/RTTI.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/ScaleTimeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/ScaleTimeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/ShearTimeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/ShearTimeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Skeleton.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Skeleton.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/SkeletonBinary.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/SkeletonBinary.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/SkeletonBounds.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/SkeletonBounds.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/SkeletonClipping.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/SkeletonClipping.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/SkeletonData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/SkeletonData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/SkeletonJson.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/SkeletonJson.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Skin.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Skin.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Slot.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Slot.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/SlotData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/SlotData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/SpacingMode.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/spine.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/SpineObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/SpineObject.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/SpineString.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/TextureLoader.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/TextureLoader.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Timeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Timeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/TimelineType.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/TransformConstraint.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/TransformConstraint.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/TransformConstraintData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/TransformConstraintData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/TransformConstraintTimeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/TransformConstraintTimeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/TransformMode.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/TranslateTimeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/TranslateTimeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Triangulator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Triangulator.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/TwoColorTimeline.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/TwoColorTimeline.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Updatable.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Updatable.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Vector.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/VertexAttachment.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/VertexAttachment.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/VertexEffect.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/VertexEffect.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine/Vertices.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/AttachmentVertices.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/AttachmentVertices.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/AttachUtil.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/AttachUtil.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/SkeletonAnimation.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/SkeletonAnimation.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/SkeletonCache.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/SkeletonCache.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/SkeletonCacheAnimation.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/SkeletonCacheAnimation.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/SkeletonCacheMgr.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/SkeletonCacheMgr.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/SkeletonDataMgr.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/SkeletonDataMgr.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/SkeletonRenderer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/SkeletonRenderer.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/spine-cocos2dx.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/spine-cocos2dx.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/VertexEffectDelegate.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support/VertexEffectDelegate.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_spine_manual.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_spine_auto.cpp
    )
endif() # CC_USE_SPINE

##### CC_USE_DRAGONBONES
if(CC_USE_DRAGONBONES)
    list(APPEND CC_COCOS_SOURCES 
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/DragonBonesHeaders.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/animation/Animation.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/animation/Animation.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/animation/AnimationState.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/animation/AnimationState.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/animation/BaseTimelineState.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/animation/BaseTimelineState.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/animation/IAnimatable.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/animation/TimelineState.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/animation/TimelineState.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/animation/WorldClock.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/animation/WorldClock.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/armature/Armature.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/armature/Armature.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/armature/Bone.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/armature/Bone.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/armature/Constraint.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/armature/Constraint.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/armature/DeformVertices.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/armature/DeformVertices.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/armature/IArmatureProxy.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/armature/Slot.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/armature/Slot.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/armature/TransformObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/armature/TransformObject.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/core/BaseObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/core/BaseObject.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/core/DragonBones.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/core/DragonBones.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/event/EventObject.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/event/EventObject.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/event/IEventDispatcher.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/factory/BaseFactory.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/factory/BaseFactory.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/geom/ColorTransform.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/geom/Matrix.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/geom/Point.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/geom/Point.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/geom/Rectangle.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/geom/Transform.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/geom/Transform.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/AnimationConfig.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/AnimationConfig.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/AnimationData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/AnimationData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/ArmatureData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/ArmatureData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/BoundingBoxData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/BoundingBoxData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/CanvasData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/CanvasData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/ConstraintData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/ConstraintData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/DisplayData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/DisplayData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/DragonBonesData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/DragonBonesData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/SkinData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/SkinData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/TextureAtlasData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/TextureAtlasData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/UserData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/model/UserData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/parser/BinaryDataParser.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/parser/BinaryDataParser.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/parser/DataParser.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/parser/DataParser.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/parser/JSONDataParser.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones/parser/JSONDataParser.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/ArmatureCache.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/ArmatureCache.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/ArmatureCacheMgr.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/ArmatureCacheMgr.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/AttachUtil.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/AttachUtil.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/CCArmatureCacheDisplay.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/CCArmatureCacheDisplay.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/CCArmatureDisplay.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/CCArmatureDisplay.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/CCDragonBonesHeaders.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/CCFactory.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/CCFactory.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/CCSlot.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/CCSlot.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/CCTextureAtlasData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/dragonbones-creator-support/CCTextureAtlasData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_dragonbones_manual.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_dragonbones_auto.cpp
    )
endif() # CC_USE_DRAGONBONES

##### USE_WEBVIEW
if(CC_USE_WEBVIEW)
    list(APPEND CC_COCOS_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_webview_auto.hpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_webview_auto.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/ui/webview/WebViewImpl-openharmony.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/ui/webview/WebViewImpl-openharmony.cpp
    )
endif() # USE_WEBVIEW

##### USE_AUDIO
if(CC_USE_AUDIO)
    list(APPEND CC_COCOS_SOURCES 
        ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_audioengine_auto.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/AudioEngine.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AssetFd.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AssetFd.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/audio.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioBufferProvider.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioDecoder.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioDecoder.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioDecoderMp3.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioDecoderMp3.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioDecoderOgg.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioDecoderOgg.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioDecoderProvider.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioDecoderProvider.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioDecoderSLES.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioDecoderSLES.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioDecoderWav.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioDecoderWav.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioEngine-inl.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioEngine-inl.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioMixer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioMixer.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioMixerController.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioMixerController.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioMixerOps.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioPlayerProvider.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioPlayerProvider.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioResampler.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioResampler.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioResamplerCubic.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioResamplerCubic.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/AudioResamplerPublic.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/IAudioPlayer.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/ICallerThreadUtils.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/IVolumeProvider.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/mp3reader.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/mp3reader.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/OpenSLHelper.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/PcmAudioPlayer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/PcmAudioPlayer.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/PcmAudioService.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/PcmAudioService.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/PcmBufferProvider.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/PcmBufferProvider.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/PcmData.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/PcmData.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/tinysndfile.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/tinysndfile.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/Track.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/Track.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/UrlAudioPlayer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/UrlAudioPlayer.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/audio_utils/format.c
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/audio_utils/minifloat.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/audio_utils/primitives.c
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/audio_utils/include/audio_utils/format.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/audio_utils/include/audio_utils/minifloat.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/audio_utils/include/audio_utils/primitives.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/audio_utils/private/private.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/cutils/bitops.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/cutils/log.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/utils/Compat.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/utils/Errors.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/utils/Utils.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android/utils/Utils.h
    )
endif() # USE_AUDIO

##### USE_SOCKET
if(CC_USE_SOCKET)
    list(APPEND CC_COCOS_SOURCES 
        ${CMAKE_CURRENT_LIST_DIR}/cocos/network/SocketIO.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/network/SocketIO.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/network/WebSocket.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/network/WebSocket-libwebsockets.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/network/WebSocketServer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/network/WebSocketServer.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_socketio.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_websocket.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/manual/jsb_websocket_server.cpp
    )
endif() # USE_SOCKET 

##### USE_PARTICLE
if(CC_USE_PARTICLE)
    list(APPEND CC_COCOS_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/particle/ParticleSimulator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/particle/ParticleSimulator.h
        ${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/auto/jsb_cocos2dx_particle_auto.cpp
    )
endif() # USE_PARTICLE

##### external source
list(APPEND CC_COCOS_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/external/sources/xxtea/xxtea.cpp
    ${CMAKE_CURRENT_LIST_DIR}/external/sources/xxtea/xxtea.h
    ${CMAKE_CURRENT_LIST_DIR}/external/sources/tinyxml2/tinyxml2.cpp
    ${CMAKE_CURRENT_LIST_DIR}/external/sources/tinyxml2/tinyxml2.h
    ${CMAKE_CURRENT_LIST_DIR}/external/sources/unzip/ioapi_mem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/external/sources/unzip/ioapi_mem.h
    ${CMAKE_CURRENT_LIST_DIR}/external/sources/unzip/ioapi.cpp
    ${CMAKE_CURRENT_LIST_DIR}/external/sources/unzip/ioapi.h
    ${CMAKE_CURRENT_LIST_DIR}/external/sources/unzip/unzip.cpp
    ${CMAKE_CURRENT_LIST_DIR}/external/sources/unzip/unzip.h
    ${CMAKE_CURRENT_LIST_DIR}/external/sources/ConvertUTF/ConvertUTFWrapper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/external/sources/ConvertUTF/ConvertUTF.c
    ${CMAKE_CURRENT_LIST_DIR}/external/sources/ConvertUTF/ConvertUTF.h
    ${CMAKE_CURRENT_LIST_DIR}/external/sources/edtaa3func/edtaa3func.cpp
    ${CMAKE_CURRENT_LIST_DIR}/external/sources/edtaa3func/edtaa3func.h
)

##### External sources
list(APPEND CC_COCOS_SOURCES ${CC_EXTERNAL_SOURCES})

################################# cc_apply_definations ###################################
function(cc_apply_definations target)
    target_compile_definitions(${target} PUBLIC
        $<IF:$<BOOL:${CC_USE_GFX_RENDERER}>,USE_GFX_RENDERER=1,USE_GFX_RENDERER=0>
        $<IF:$<BOOL:${CC_USE_VIDEO}>,USE_VIDEO=1,USE_VIDEO=0>
        $<IF:$<BOOL:${CC_USE_WEBVIEW}>,USE_WEBVIEW=1,USE_WEBVIEW=0>
        $<IF:$<BOOL:${CC_USE_AUDIO}>,USE_AUDIO=1,USE_AUDIO=0>
        $<IF:$<BOOL:${CC_USE_SOCKET}>,USE_SOCKET=1,USE_SOCKET=0>
        $<IF:$<BOOL:${CC_USE_WEBSOCKET_SERVER}>,USE_WEBSOCKET_SERVER=1,USE_WEBSOCKET_SERVER=0>
        $<IF:$<BOOL:${CC_USE_MIDDLEWARE}>,USE_MIDDLEWARE=1,USE_MIDDLEWARE=0>
        $<IF:$<BOOL:${CC_USE_SPINE}>,USE_SPINE=1,USE_SPINE=0>
        $<IF:$<BOOL:${CC_USE_DRAGONBONES}>,USE_DRAGONBONES=1,USE_DRAGONBONES=0>
        $<IF:$<BOOL:${CC_USE_SE_NAPI}>,USE_SE_NAPI=1,USE_SE_NAPI=0>
        $<IF:$<BOOL:${CC_USE_PARTICLE}>,USE_PARTICLE=1,USE_PARTICLE=0>
    )
endfunction()

include_directories(${CC_EXTERNAL_INCLUDES})
include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/2d)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/audio/android)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/base)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/editor-support/spine-creator-support)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/math)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/network)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/platform)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/renderer)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/gfx)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/renderer)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/memop)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/renderer/scene/assembler)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/storage/local-storage)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/ui/edit-box)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/ui/webview)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/scripting/js-bindings/jswrapper/napi)
include_directories(${CMAKE_CURRENT_LIST_DIR}/cocos/platform/openharmony/napi)
