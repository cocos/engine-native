#pragma once
#include "../gfx-base/GFXDef-common.h"
namespace cc {
namespace gfx {

//emscripten export struct with pointers.
class TextureInfoInstance {
public:
    TextureInfoInstance() = default;

    inline void setType(TextureType type) { info.type = type; }
    inline void setUsage(TextureUsage usage) { info.usage = usage; }
    inline void setFormat(Format format) { info.format = format; }
    inline void setWidth(uint32_t width) { info.width = width; }
    inline void setHeight(uint32_t height) { info.height = height; }
    inline void setFlags(TextureFlagBit flags) { info.flags = flags; }
    inline void setLevelCount(uint levelCount) { info.levelCount = levelCount; }
    inline void setLayerCount(uint layerCount) { info.layerCount = layerCount; }
    inline void setSamples(SampleCount sample) { info.samples = sample; }
    inline void setDepth(uint32_t depth) { info.depth = depth; }
    inline void setImageBuffer(intptr_t imgBuff) { info.externalRes = reinterpret_cast<void*>(imgBuff); }

    explicit operator const TextureInfo() const { return info; }

private:
    TextureInfo info;
};

class TextureViewInfoInstance {
public:
    TextureViewInfoInstance() = default;

    inline void setTexture(Texture* tex) { info.texture = tex; }
    inline void setType(TextureType type) { info.type = type; }
    inline void setFormat(Format format) { info.format = format; }
    inline void setBaseLevel(uint baseLevel) { info.baseLevel = baseLevel; }
    inline void setLevelCount(uint levelCount) { info.levelCount = levelCount; }
    inline void setBaseLayer(uint baseLayer) { info.baseLayer = baseLayer; }
    inline void setLayerCount(uint layerCount) { info.layerCount = layerCount; }

    explicit operator const TextureViewInfo() const { return info; }

private:
    TextureViewInfo info;
};

class SwapchainInfoInstance {
public:
    SwapchainInfoInstance() = default;

    inline void setWindowHandle(void* hwnd) { info.windowHandle = hwnd; }
    inline void setVsyncMode(VsyncMode mode) { info.vsyncMode = mode; }
    inline void setWidth(uint32_t width) { info.width = width; }
    inline void setHeight(uint32_t height) { info.height = height; }

    explicit operator const SwapchainInfo() const { return info; }

private:
    SwapchainInfo info;
};

class FramebufferInfoInstance {
public:
    FramebufferInfoInstance() = default;

    inline void setRenderPass(RenderPass* renderPass) { info.renderPass = renderPass; }
    inline void setColorTextures(TextureList colors) { info.colorTextures = colors; }
    inline void setDepthStencilTexture(Texture* tex) { info.depthStencilTexture = tex; }

    explicit operator const FramebufferInfo() const { return info; }

private:
    FramebufferInfo info;
};

class BufferViewInfoInstance {
public:
    BufferViewInfoInstance() = default;

    inline void setBuffer(Buffer* buffer) { info.buffer = buffer; }
    inline void setOffset(uint32_t offset) { info.offset = offset; }
    inline void setRange(uint32_t range) { info.range = range; }

    explicit operator const BufferViewInfo() const { return info; }

private:
    BufferViewInfo info;
};

class DescriptorSetInfoInstance {
public:
    DescriptorSetInfoInstance() = default;
    inline void setDescriptorSetLayout(DescriptorSetLayout* layout) { info.layout = layout; }

    explicit operator const DescriptorSetInfo() const { return info; }

private:
    DescriptorSetInfo info;
};

// struct PipelineLayoutInfo {
//     DescriptorSetLayoutList setLayouts;
// };

// struct DescriptorSetLayoutInfo {
//     DescriptorSetLayoutBindingList bindings;
// };

class DescriptorSetLayoutBindingInstance {
public:
    inline void setBinding(uint32_t binding) { dsBinding.binding = binding; }
    inline void setDescriptorType(DescriptorType type) { dsBinding.descriptorType = type; }
    inline void setCount(uint32_t count) { dsBinding.count = count; }
    inline void setStageFlags(ShaderStageFlags flag) { dsBinding.stageFlags = flag; }
    inline void setSamplerList(SamplerList samplers) { dsBinding.immutableSamplers = samplers; }

    explicit operator const DescriptorSetLayoutBinding() const { return dsBinding; }

private:
    DescriptorSetLayoutBinding dsBinding;
};

class PipelineStateInfoInstance {
public:
    inline void setShader(Shader* shader) { info.shader = shader; }
    inline void setPipelineLayout(PipelineLayout* pipelineLayout) { info.pipelineLayout = pipelineLayout; }
    inline void setRenderPass(RenderPass* renderPass) { info.renderPass = renderPass; }
    inline void setInputState(InputState inputState) { info.inputState = inputState; }
    inline void setRasterizerState(RasterizerState rasterizerState) { info.rasterizerState = rasterizerState; }
    inline void setDepthStencilState(DepthStencilState depthStencilState) { info.depthStencilState = depthStencilState; }
    inline void setBlendState(BlendState blendState) { info.blendState = blendState; }
    inline void setPrimitiveMode(PrimitiveMode primitive) { info.primitive = primitive; }
    inline void setDynamicStateFlags(DynamicStateFlags dynamicStates) { info.dynamicStates = dynamicStates; }
    inline void setPipelineBindPoint(PipelineBindPoint bindPoint) { info.bindPoint = bindPoint; }
    inline void setSubpass(uint32_t subpass) { info.subpass = subpass; }

    explicit operator const PipelineStateInfo() const { return info; }

private:
    PipelineStateInfo info;
};

class InputAssemblerInfoInstance {
public:
    inline void setAttributes(AttributeList attributes) { info.attributes = attributes; }
    inline void setBuffers(BufferList buffers) { info.vertexBuffers = buffers; }
    inline void setIndexBuffer(Buffer* buffer) { info.indexBuffer = buffer; }
    inline void setIndirectBuffer(Buffer* buffer) { info.indirectBuffer = buffer; }

    explicit operator const InputAssemblerInfo() const { return info; }

private:
    InputAssemblerInfo info;
};

class CommandBufferInfoInstance {
public:
    inline void setQueue(Queue* q) { info.queue = q; }
    inline void setType(CommandBufferType type) { info.type = type; }

    explicit operator const CommandBufferInfo() const { return info; }

private:
    CommandBufferInfo info;
};

class DispatchInfoInstance {
public:
    inline void setGroupCountX(uint32_t groupCountX) { info.groupCountX = groupCountX; }
    inline void setGroupCountY(uint32_t groupCountY) { info.groupCountY = groupCountY; }
    inline void setGroupCountZ(uint32_t groupCountZ) { info.groupCountZ = groupCountZ; }
    inline void setIndirectBuffer(Buffer* indirectBuffer) { info.indirectBuffer = indirectBuffer; }
    inline void setIndirectOffset(uint32_t offset) { info.indirectOffset = offset; }

    explicit operator const DispatchInfo() const { return info; }

private:
    DispatchInfo info;
};

} // namespace gfx
} // namespace cc
