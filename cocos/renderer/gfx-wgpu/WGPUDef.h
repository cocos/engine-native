#pragma once
#include "../gfx-base/GFXDef-common.h"
namespace cc {
namespace gfx {

//emscripten export struct with pointers.
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

    operator TextureViewInfo() { return info; }

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

    operator FramebufferInfo() { return info; }

private:
    FramebufferInfo info;
};

} // namespace gfx
} // namespace cc
