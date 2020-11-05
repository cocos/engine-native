#pragma once

namespace se {
enum class PoolType {
    // objects
    ATTRIBUTE,
    DESCRIPTOR_SETS,
    SHADER,
    INPUT_ASSEMBLER,
    PIPELINE_LAYOUT,
    FRAMEBUFFER,

    // buffers
    PASS = 100,
    SUB_MODEL,
    MODEL,
    SCENE,
    CAMERA,
    NODE,
    ROOT,
    AABB,
    RENDER_WINDOW,
    FRUSTUM,
    AMBIENT,
    FOG,
    SKYBOX,
    SHADOW,
    LIGHT,
    SPHERE,
    INSTANCED_ATTRIBUTE,
    FLAT_BUFFER,
    SUB_MESH,
    RASTERIZER_STATE,
    DEPTH_STENCIL_STATE,
    BLEND_TARGET,
    BLEND_STATE,

    // array
    SUB_MODEL_ARRAY = 200,
    MODEL_ARRAY,
    ATTRIBUTE_ARRAY,
    FLAT_BUFFER_ARRAY,
    INSTANCED_ATTRIBUTE_ARRAY,
    LIGHT_ARRAY,
    BLEND_TARGET_ARRAY,

    // raw buffer
    RAW_BUFFER = 300,
    UNKNOWN
};
}
