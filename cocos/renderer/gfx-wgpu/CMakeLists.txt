cmake_minimum_required(VERSION 2.8)

set(APP_NAME "CocosGame" CACHE STRING "Project Name")
project(${APP_NAME}WASM)

file(GLOB sources *.cpp)
file(GLOB_RECURSE headers *.h)

include(${CMAKE_CURRENT_LIST_DIR}/../../../cmake/predefine.cmake)
set(CWD ${CMAKE_CURRENT_LIST_DIR}/../../../)

message("yoooooooooooooooooooooooooooooooooooooooooooooooooo")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-nonportable-include-path -fno-exceptions -fno-rtti")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -D_DEBUG=1 -Wno-unused -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g0 -DNDEBUG=1 -flto -O3")

message("${headers}")
message("${sources}")
message("${CWD}cocos/renderer")

cocos_source_files(MODULE ccutils
	cocos/platform/win32/Utils-win32.cpp
	cocos/platform/win32/Utils-win32.h
)

cocos_source_files(
    cocos/base/Agent.h
    cocos/base/astc.cpp
    cocos/base/astc.h
    cocos/base/AutoreleasePool.cpp
    cocos/base/AutoreleasePool.h
    cocos/base/base64.cpp
    cocos/base/base64.h
    cocos/base/CachedArray.h
    cocos/base/Config.h
    cocos/base/CoreStd.h
    cocos/base/csscolorparser.cpp
    cocos/base/csscolorparser.h
    cocos/base/etc1.cpp
    cocos/base/etc1.h
    cocos/base/etc2.cpp
    cocos/base/etc2.h
    cocos/base/IndexHandle.h
    cocos/base/Locked.h
    cocos/base/Macros.h
    cocos/base/Map.h
    cocos/base/Object.h
    cocos/base/Random.h
    cocos/base/Ref.cpp
    cocos/base/Ref.h
    cocos/base/Scheduler.cpp
    cocos/base/Scheduler.h
    cocos/base/StringHandle.cpp
    cocos/base/StringHandle.h
    cocos/base/StringPool.h
    cocos/base/StringUtil.cpp
    cocos/base/StringUtil.h
    cocos/base/ThreadPool.cpp
    cocos/base/ThreadPool.h
    cocos/base/TypeDef.h
    cocos/base/Vector.h
)

##### base
cocos_source_files(
    cocos/base/Agent.h
    cocos/base/astc.cpp
    cocos/base/astc.h
    cocos/base/AutoreleasePool.cpp
    cocos/base/AutoreleasePool.h
    cocos/base/base64.cpp
    cocos/base/base64.h
    cocos/base/CachedArray.h
    cocos/base/Config.h
    cocos/base/CoreStd.h
    cocos/base/csscolorparser.cpp
    cocos/base/csscolorparser.h
    cocos/base/etc1.cpp
    cocos/base/etc1.h
    cocos/base/etc2.cpp
    cocos/base/etc2.h
    cocos/base/IndexHandle.h
    cocos/base/Locked.h
    cocos/base/Macros.h
    cocos/base/Map.h
    cocos/base/Object.h
    cocos/base/Random.h
    cocos/base/Ref.cpp
    cocos/base/Ref.h
    cocos/base/Scheduler.cpp
    cocos/base/Scheduler.h
    cocos/base/StringHandle.cpp
    cocos/base/StringHandle.h
    cocos/base/StringPool.h
    cocos/base/StringUtil.cpp
    cocos/base/StringUtil.h
    cocos/base/ThreadPool.cpp
    cocos/base/ThreadPool.h
    cocos/base/TypeDef.h
    cocos/base/Vector.h
)

##### renderer
cocos_source_files(
                 cocos/renderer/GFXDeviceManager.h

                 cocos/renderer/gfx-base/GFXObject.h
                 cocos/renderer/gfx-base/GFXObject.cpp
                 cocos/renderer/gfx-base/GFXBase.h
                 cocos/renderer/gfx-base/GFXBuffer.cpp
                 cocos/renderer/gfx-base/GFXBuffer.h
                 cocos/renderer/gfx-base/GFXCommandBuffer.cpp
                 cocos/renderer/gfx-base/GFXCommandBuffer.h
                 cocos/renderer/gfx-base/GFXContext.cpp
                 cocos/renderer/gfx-base/GFXContext.h
                 cocos/renderer/gfx-base/GFXDef.cpp
                 cocos/renderer/gfx-base/GFXDef.h
                 cocos/renderer/gfx-base/GFXDef-common.h
                 cocos/renderer/gfx-base/GFXDevice.cpp
                 cocos/renderer/gfx-base/GFXDevice.h
                 cocos/renderer/gfx-base/GFXFramebuffer.cpp
                 cocos/renderer/gfx-base/GFXFramebuffer.h
                 cocos/renderer/gfx-base/GFXGlobalBarrier.cpp
                 cocos/renderer/gfx-base/GFXGlobalBarrier.h
                 cocos/renderer/gfx-base/GFXInputAssembler.cpp
                 cocos/renderer/gfx-base/GFXInputAssembler.h
                 cocos/renderer/gfx-base/GFXDescriptorSet.cpp
                 cocos/renderer/gfx-base/GFXDescriptorSet.h
                 cocos/renderer/gfx-base/GFXDescriptorSetLayout.cpp
                 cocos/renderer/gfx-base/GFXDescriptorSetLayout.h
                 cocos/renderer/gfx-base/GFXPipelineLayout.cpp
                 cocos/renderer/gfx-base/GFXPipelineLayout.h
                 cocos/renderer/gfx-base/GFXPipelineState.cpp
                 cocos/renderer/gfx-base/GFXPipelineState.h
                 cocos/renderer/gfx-base/GFXQueue.cpp
                 cocos/renderer/gfx-base/GFXQueue.h
                 cocos/renderer/gfx-base/GFXRenderPass.cpp
                 cocos/renderer/gfx-base/GFXRenderPass.h
                 cocos/renderer/gfx-base/GFXSampler.cpp
                 cocos/renderer/gfx-base/GFXSampler.h
                 cocos/renderer/gfx-base/GFXShader.cpp
                 cocos/renderer/gfx-base/GFXShader.h
                 cocos/renderer/gfx-base/GFXTexture.cpp
                 cocos/renderer/gfx-base/GFXTexture.h
                 cocos/renderer/gfx-base/GFXTextureBarrier.cpp
                 cocos/renderer/gfx-base/GFXTextureBarrier.h

                 cocos/renderer/gfx-agent/BufferAgent.h
                 cocos/renderer/gfx-agent/BufferAgent.cpp
                 cocos/renderer/gfx-agent/CommandBufferAgent.h
                 cocos/renderer/gfx-agent/CommandBufferAgent.cpp
                 cocos/renderer/gfx-agent/DescriptorSetAgent.h
                 cocos/renderer/gfx-agent/DescriptorSetAgent.cpp
                 cocos/renderer/gfx-agent/DescriptorSetLayoutAgent.h
                 cocos/renderer/gfx-agent/DescriptorSetLayoutAgent.cpp
                 cocos/renderer/gfx-agent/DeviceAgent.h
                 cocos/renderer/gfx-agent/DeviceAgent.cpp
                 cocos/renderer/gfx-agent/FramebufferAgent.h
                 cocos/renderer/gfx-agent/FramebufferAgent.cpp
                 cocos/renderer/gfx-agent/InputAssemblerAgent.h
                 cocos/renderer/gfx-agent/InputAssemblerAgent.cpp
                 cocos/renderer/gfx-agent/PipelineLayoutAgent.h
                 cocos/renderer/gfx-agent/PipelineLayoutAgent.cpp
                 cocos/renderer/gfx-agent/PipelineStateAgent.h
                 cocos/renderer/gfx-agent/PipelineStateAgent.cpp
                 cocos/renderer/gfx-agent/QueueAgent.h
                 cocos/renderer/gfx-agent/QueueAgent.cpp
                 cocos/renderer/gfx-agent/RenderPassAgent.h
                 cocos/renderer/gfx-agent/RenderPassAgent.cpp
                 cocos/renderer/gfx-agent/SamplerAgent.h
                 cocos/renderer/gfx-agent/SamplerAgent.cpp
                 cocos/renderer/gfx-agent/ShaderAgent.h
                 cocos/renderer/gfx-agent/ShaderAgent.cpp
                 cocos/renderer/gfx-agent/TextureAgent.h
                 cocos/renderer/gfx-agent/TextureAgent.cpp

                 cocos/renderer/gfx-validator/BufferValidator.h
                 cocos/renderer/gfx-validator/BufferValidator.cpp
                 cocos/renderer/gfx-validator/CommandBufferValidator.h
                 cocos/renderer/gfx-validator/CommandBufferValidator.cpp
                 cocos/renderer/gfx-validator/DescriptorSetValidator.h
                 cocos/renderer/gfx-validator/DescriptorSetValidator.cpp
                 cocos/renderer/gfx-validator/DescriptorSetLayoutValidator.h
                 cocos/renderer/gfx-validator/DescriptorSetLayoutValidator.cpp
                 cocos/renderer/gfx-validator/DeviceValidator.h
                 cocos/renderer/gfx-validator/DeviceValidator.cpp
                 cocos/renderer/gfx-validator/FramebufferValidator.h
                 cocos/renderer/gfx-validator/FramebufferValidator.cpp
                 cocos/renderer/gfx-validator/InputAssemblerValidator.h
                 cocos/renderer/gfx-validator/InputAssemblerValidator.cpp
                 cocos/renderer/gfx-validator/PipelineLayoutValidator.h
                 cocos/renderer/gfx-validator/PipelineLayoutValidator.cpp
                 cocos/renderer/gfx-validator/PipelineStateValidator.h
                 cocos/renderer/gfx-validator/PipelineStateValidator.cpp
                 cocos/renderer/gfx-validator/QueueValidator.h
                 cocos/renderer/gfx-validator/QueueValidator.cpp
                 cocos/renderer/gfx-validator/RenderPassValidator.h
                 cocos/renderer/gfx-validator/RenderPassValidator.cpp
                 cocos/renderer/gfx-validator/SamplerValidator.h
                 cocos/renderer/gfx-validator/SamplerValidator.cpp
                 cocos/renderer/gfx-validator/ShaderValidator.h
                 cocos/renderer/gfx-validator/ShaderValidator.cpp
                 cocos/renderer/gfx-validator/TextureValidator.h
                 cocos/renderer/gfx-validator/TextureValidator.cpp
                 cocos/renderer/gfx-validator/ValidationUtils.h
                 cocos/renderer/gfx-validator/ValidationUtils.cpp

                 cocos/renderer/gfx-empty/EmptyBuffer.h
                 cocos/renderer/gfx-empty/EmptyBuffer.cpp
                 cocos/renderer/gfx-empty/EmptyCommandBuffer.h
                 cocos/renderer/gfx-empty/EmptyCommandBuffer.cpp
                 cocos/renderer/gfx-empty/EmptyContext.h
                 cocos/renderer/gfx-empty/EmptyContext.cpp
                 cocos/renderer/gfx-empty/EmptyDescriptorSet.h
                 cocos/renderer/gfx-empty/EmptyDescriptorSet.cpp
                 cocos/renderer/gfx-empty/EmptyDescriptorSetLayout.h
                 cocos/renderer/gfx-empty/EmptyDescriptorSetLayout.cpp
                 cocos/renderer/gfx-empty/EmptyDevice.h
                 cocos/renderer/gfx-empty/EmptyDevice.cpp
                 cocos/renderer/gfx-empty/EmptyFramebuffer.h
                 cocos/renderer/gfx-empty/EmptyFramebuffer.cpp
                 cocos/renderer/gfx-empty/EmptyInputAssembler.h
                 cocos/renderer/gfx-empty/EmptyInputAssembler.cpp
                 cocos/renderer/gfx-empty/EmptyPipelineLayout.h
                 cocos/renderer/gfx-empty/EmptyPipelineLayout.cpp
                 cocos/renderer/gfx-empty/EmptyPipelineState.h
                 cocos/renderer/gfx-empty/EmptyPipelineState.cpp
                 cocos/renderer/gfx-empty/EmptyQueue.h
                 cocos/renderer/gfx-empty/EmptyQueue.cpp
                 cocos/renderer/gfx-empty/EmptyRenderPass.h
                 cocos/renderer/gfx-empty/EmptyRenderPass.cpp
                 cocos/renderer/gfx-empty/EmptySampler.h
                 cocos/renderer/gfx-empty/EmptySampler.cpp
                 cocos/renderer/gfx-empty/EmptyShader.h
                 cocos/renderer/gfx-empty/EmptyShader.cpp
                 cocos/renderer/gfx-empty/EmptyTexture.h
                 cocos/renderer/gfx-empty/EmptyTexture.cpp

                 cocos/renderer/pipeline/BatchedBuffer.cpp
                 cocos/renderer/pipeline/BatchedBuffer.h
                 cocos/renderer/pipeline/Define.h
                 cocos/renderer/pipeline/Define.cpp
                 cocos/renderer/pipeline/GlobalDescriptorSetManager.h
                 cocos/renderer/pipeline/GlobalDescriptorSetManager.cpp
                 cocos/renderer/pipeline/InstancedBuffer.cpp
                 cocos/renderer/pipeline/InstancedBuffer.h
                 cocos/renderer/pipeline/PipelineStateManager.cpp
                 cocos/renderer/pipeline/PipelineStateManager.h
                 cocos/renderer/pipeline/RenderAdditiveLightQueue.cpp
                 cocos/renderer/pipeline/RenderAdditiveLightQueue.h
                 cocos/renderer/pipeline/RenderBatchedQueue.cpp
                 cocos/renderer/pipeline/RenderBatchedQueue.h
                 cocos/renderer/pipeline/RenderFlow.cpp
                 cocos/renderer/pipeline/RenderFlow.h
                 cocos/renderer/pipeline/RenderInstancedQueue.cpp
                 cocos/renderer/pipeline/RenderInstancedQueue.h
                 cocos/renderer/pipeline/RenderPipeline.cpp
                 cocos/renderer/pipeline/RenderPipeline.h
                 cocos/renderer/pipeline/RenderQueue.cpp
                 cocos/renderer/pipeline/RenderQueue.h
                 cocos/renderer/pipeline/RenderStage.cpp
                 cocos/renderer/pipeline/RenderStage.h
                 cocos/renderer/pipeline/PlanarShadowQueue.cpp
                 cocos/renderer/pipeline/PlanarShadowQueue.h
                 cocos/renderer/pipeline/ShadowMapBatchedQueue.cpp
                 cocos/renderer/pipeline/ShadowMapBatchedQueue.h
                 cocos/renderer/pipeline/PipelineUBO.cpp
                 cocos/renderer/pipeline/PipelineUBO.h
                 cocos/renderer/pipeline/PipelineSceneData.cpp
                 cocos/renderer/pipeline/PipelineSceneData.h
                 cocos/renderer/pipeline/forward/ForwardFlow.cpp
                 cocos/renderer/pipeline/forward/ForwardFlow.h
                 cocos/renderer/pipeline/forward/ForwardPipeline.cpp
                 cocos/renderer/pipeline/forward/ForwardPipeline.h
                 cocos/renderer/pipeline/forward/ForwardStage.cpp
                 cocos/renderer/pipeline/forward/ForwardStage.h
                 cocos/renderer/pipeline/SceneCulling.cpp
                 cocos/renderer/pipeline/SceneCulling.h
                 cocos/renderer/pipeline/forward/UIPhase.cpp
                 cocos/renderer/pipeline/forward/UIPhase.h
                 cocos/renderer/pipeline/deferred/DeferredPipeline.cpp
                 cocos/renderer/pipeline/deferred/DeferredPipeline.h
                 cocos/renderer/pipeline/deferred/GbufferFlow.cpp
                 cocos/renderer/pipeline/deferred/GbufferFlow.h
                 cocos/renderer/pipeline/deferred/GbufferStage.cpp
                 cocos/renderer/pipeline/deferred/GbufferStage.h
                 cocos/renderer/pipeline/deferred/LightingFlow.cpp
                 cocos/renderer/pipeline/deferred/LightingFlow.h
                 cocos/renderer/pipeline/deferred/LightingStage.cpp
                 cocos/renderer/pipeline/deferred/LightingStage.h
                 cocos/renderer/pipeline/deferred/PostprocessStage.cpp
                 cocos/renderer/pipeline/deferred/PostprocessStage.h
                 cocos/renderer/pipeline/deferred/ReflectionComp.cpp
                 cocos/renderer/pipeline/deferred/ReflectionComp.h
                 cocos/renderer/pipeline/shadow/ShadowFlow.cpp
                 cocos/renderer/pipeline/shadow/ShadowFlow.h
                 cocos/renderer/pipeline/shadow/ShadowStage.cpp
                 cocos/renderer/pipeline/shadow/ShadowStage.h
                 cocos/renderer/pipeline/helper/DefineMap.h
                 cocos/renderer/pipeline/helper/DefineMap.cpp
)

if (EMSCRIPTEN)
	file(GLOB_RECURSE platform_sources src/ems/*)
	set(CMAKE_EXECUTABLE_SUFFIX ".js")

	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -s ASSERTIONS=2 -s DEMANGLE_SUPPORT=1 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=2")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s ASSERTIONS=0 -s DISABLE_EXCEPTION_CATCHING=1 -s EVAL_CTORS=1 --closure 1")

	set(CMAKE_EXE_LINKER_FLAGS "-s WASM=1 -s USE_WEBGPU=1 -s NO_EXIT_RUNTIME=1 -s STRICT=1")

	# Linker flags to optimize for smallest output code size
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s ENVIRONMENT=web -s MINIMAL_RUNTIME=2 -s TEXTDECODER=2 -s ABORTING_MALLOC=0 -s ALLOW_MEMORY_GROWTH=0 -s SUPPORT_ERRNO=0 -s MALLOC=emmalloc -s NO_FILESYSTEM=1 --output_eol=linux --no-entry")
elseif (WIN32)
	file(GLOB_RECURSE platform_sources src/win/*)
elseif (APPLE)
	file(GLOB_RECURSE platform_sources src/mac/*)
endif()

add_executable(${APP_NAME}WASM ${sources} ${platform_sources} ${headers})

target_include_directories(
	${APP_NAME}WASM PRIVATE "${CMAKE_CURRENT_LIST_DIR}/inc"
	${CC_EXTERNAL_INCLUDES}
	${CWD}
	${CWD}/cocos
	${CWD}/cocos/renderer
	${CWD}/cocos/platform
	${CWD}/cocos/renderer/core
	#$<$<BOOL:USE_SE_JSC>:${CWD}/cocos/bindings/jswrapper>
	${CC_EXTERNAL_PRIVATE_INCLUDES}
)

message("${CWD}cocos/renderer")