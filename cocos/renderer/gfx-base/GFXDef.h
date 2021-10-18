/****************************************************************************
 Copyright (c) 2019-2021 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#pragma once

#include <functional>
#include "GFXDef-common.h"

namespace cc {
namespace gfx {

template <typename T, typename Enable = std::enable_if_t<std::is_class<T>::value>>
struct Hasher final { size_t operator()(const T& info) const; };

// make this boost::hash compatible
template <typename T, typename Enable = std::enable_if_t<std::is_class<T>::value>>
size_t hash_value(const T& info) { return Hasher<T>()(info); } // NOLINT(readability-identifier-naming)

bool operator==(const ColorAttachment& lhs, const ColorAttachment& rhs);
bool operator==(const DepthStencilAttachment& lhs, const DepthStencilAttachment& rhs);
bool operator==(const SubpassInfo& lhs, const SubpassInfo& rhs);
bool operator==(const SubpassDependency& lhs, const SubpassDependency& rhs);
bool operator==(const RenderPassInfo& lhs, const RenderPassInfo& rhs);
bool operator==(const FramebufferInfo& lhs, const FramebufferInfo& rhs);
bool operator==(const Viewport& lhs, const Viewport& rhs);
bool operator==(const Rect& lhs, const Rect& rhs);
bool operator==(const Color& lhs, const Color& rhs);
bool operator==(const Offset& lhs, const Offset& rhs);
bool operator==(const Extent& lhs, const Extent& rhs);
bool operator==(const Size& lhs, const Size& rhs);
bool operator==(const TextureInfo& lhs, const TextureInfo& rhs);
bool operator==(const TextureViewInfo& lhs, const TextureViewInfo& rhs);
bool operator==(const BufferInfo& lhs, const BufferInfo& rhs);

bool operator!=(const Viewport& lhs, const Viewport& rhs);
bool operator!=(const Rect& lhs, const Rect& rhs);

struct SwapchainTextureInfo final {
    Swapchain* swapchain{nullptr};
    Format     format{Format::UNKNOWN};
    uint32_t   width{0};
    uint32_t   height{0};
};

constexpr TextureUsage TEXTURE_USAGE_TRANSIENT = static_cast<TextureUsage>(
    static_cast<uint32_t>(TextureUsageBit::COLOR_ATTACHMENT) |
    static_cast<uint32_t>(TextureUsageBit::DEPTH_STENCIL_ATTACHMENT) |
    static_cast<uint32_t>(TextureUsageBit::INPUT_ATTACHMENT));

constexpr DescriptorType DESCRIPTOR_BUFFER_TYPE = static_cast<DescriptorType>(
    static_cast<uint32_t>(DescriptorType::STORAGE_BUFFER) |
    static_cast<uint32_t>(DescriptorType::DYNAMIC_STORAGE_BUFFER) |
    static_cast<uint32_t>(DescriptorType::UNIFORM_BUFFER) |
    static_cast<uint32_t>(DescriptorType::DYNAMIC_UNIFORM_BUFFER));

constexpr DescriptorType DESCRIPTOR_TEXTURE_TYPE = static_cast<DescriptorType>(
    static_cast<uint32_t>(DescriptorType::SAMPLER_TEXTURE) |
    static_cast<uint32_t>(DescriptorType::SAMPLER) |
    static_cast<uint32_t>(DescriptorType::TEXTURE) |
    static_cast<uint32_t>(DescriptorType::STORAGE_IMAGE) |
    static_cast<uint32_t>(DescriptorType::INPUT_ATTACHMENT));

constexpr DescriptorType DESCRIPTOR_DYNAMIC_TYPE = static_cast<DescriptorType>(
    static_cast<uint32_t>(DescriptorType::DYNAMIC_STORAGE_BUFFER) |
    static_cast<uint32_t>(DescriptorType::DYNAMIC_UNIFORM_BUFFER));

constexpr uint32_t DRAW_INFO_SIZE = 28U;

extern const FormatInfo GFX_FORMAT_INFOS[];
extern const uint32_t   GFX_TYPE_SIZES[];

uint32_t formatSize(Format format, uint32_t width, uint32_t height, uint32_t depth);

uint32_t formatSurfaceSize(Format format, uint32_t width, uint32_t height, uint32_t depth, uint32_t mips);

} // namespace gfx
} // namespace cc
