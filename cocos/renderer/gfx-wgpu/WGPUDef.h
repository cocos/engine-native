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

} // namespace gfx
} // namespace cc
