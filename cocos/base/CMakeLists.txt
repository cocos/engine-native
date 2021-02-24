set(TARGET_NAME Core)
set(CMAKE_CXX_STANDARD 17)
message(STATUS "Target: ${TARGET_NAME}...")

file(GLOB_RECURSE HEADER_FILES *.h)
file(GLOB_RECURSE SOURCE_CPP_FILES *.cpp *.cc)
file(GLOB_RECURSE SOURCE_C_FILES *.c)

if(COCOS_PLATFORM_IOS OR COCOS_PLATFORM_OSX)
	file(GLOB_RECURSE SOURCE_MM_FILES *.m *.mm)
endif()

file(GLOB PLATFORM_SUPPORT_BASE
  ${COCOS_SRC_PATH}/platform/FileUtils.h
  ${COCOS_SRC_PATH}/platform/FileUtils.cpp
)

if(COCOS_PLATFORM_WIN32)
  file(GLOB PLATFORM_SUPPORT_TARGET
    ${COCOS_SRC_PATH}/platform/win32/FileUtils-win32.h
    ${COCOS_SRC_PATH}/platform/win32/FileUtils-win32.cpp
  )
elseif(COCOS_PLATFORM_ANDROID)
  file(GLOB PLATFORM_SUPPORT_TARGET
    ${COCOS_SRC_PATH}/platform/android/FileUtils-android.h
    ${COCOS_SRC_PATH}/platform/android/FileUtils-android.cpp
  )
elseif(COCOS_PLATFORM_IOS OR COCOS_PLATFORM_OSX)
  file(GLOB PLATFORM_SUPPORT_TARGET
    ${COCOS_SRC_PATH}/platform/apple/FileUtils-apple.h
    ${COCOS_SRC_PATH}/platform/apple/FileUtils-apple.mm
  )
endif()

set(ALL_FILES
	${HEADER_FILES}
	${SOURCE_CPP_FILES}
	${SOURCE_C_FILES}
  ${CC_EXTERNAL_SROUCES}
  ${PLATFORM_SUPPORT_BASE}
  ${PLATFORM_SUPPORT_TARGET}
)

if(COCOS_PLATFORM_IOS OR COCOS_PLATFORM_OSX)
	set(ALL_FILES ${ALL_FILES} ${SOURCE_MM_FILES})
endif()

if(COCOS_UNICODE)
	add_definitions("-DUNICODE -D_UNICODE")
endif()

if (COCOS_STATIC)
	add_library(${TARGET_NAME} STATIC ${HEADER_FILES} ${ALL_FILES})
else()
	add_library(${TARGET_NAME} SHARED ${HEADER_FILES} ${ALL_FILES})
endif()

target_link_libraries(${TARGET_NAME} ${CC_EXTERNAL_LIBS})

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME CCCore)
set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME_DEBUG CCCore_d)

message(STATUS "${TARGET_NAME} configuration completed.")

target_compile_definitions(${TARGET_NAME} PUBLIC
    $<$<CONFIG:Debug>:CC_DEBUG=1>
)
