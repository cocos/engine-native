/****************************************************************************
 Copyright (c) 2020-2021 Xiamen Yaji Software Co., Ltd.

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

#define WIN32_LEAN_AND_MEAN

#include "base/Macros.h"
#include "base/StringUtil.h"
#include "gfx-base/GFXDef.h"

#include "vk_mem_alloc.h"
#include "volk.h"

#include "thsvs_simpler_vulkan_synchronization.h"

#define DEFAULT_TIMEOUT 1000000000 // 1 second

#define BARRIER_DEDUCTION_LEVEL_NONE  0
#define BARRIER_DEDUCTION_LEVEL_BASIC 1
#define BARRIER_DEDUCTION_LEVEL_FULL  2

#ifndef BARRIER_DEDUCTION_LEVEL
    #define BARRIER_DEDUCTION_LEVEL BARRIER_DEDUCTION_LEVEL_BASIC
#endif

namespace cc {
namespace gfx {

extern VkFormat MapVkFormat(Format format);
extern VkAttachmentLoadOp MapVkLoadOp(LoadOp loadOp);
extern VkAttachmentStoreOp MapVkStoreOp(StoreOp storeOp);
extern VkBufferUsageFlagBits MapVkBufferUsageFlagBits(BufferUsage usage);
extern VkImageType MapVkImageType(TextureType type);
extern VkSampleCountFlagBits MapVkSampleCount(SampleCount count);
extern VkFormatFeatureFlags MapVkFormatFeatureFlags(TextureUsage usage);
extern VkImageUsageFlagBits MapVkImageUsageFlagBits(TextureUsage usage);
extern VkImageAspectFlags MapVkImageAspectFlags(Format format);
extern VkImageCreateFlags MapVkImageCreateFlags(TextureType type);
extern VkImageViewType MapVkImageViewType(TextureType viewType);
extern VkCommandBufferLevel MapVkCommandBufferLevel(CommandBufferType type);
extern VkDescriptorType MapVkDescriptorType(DescriptorType type);
extern VkColorComponentFlags MapVkColorComponentFlags(ColorMask colorMask);
extern VkShaderStageFlagBits MapVkShaderStageFlagBits(ShaderStageFlagBit stage);
extern VkShaderStageFlags MapVkShaderStageFlags(ShaderStageFlagBit stages);
extern SurfaceTransform MapSurfaceTransform(VkSurfaceTransformFlagBitsKHR transform);
extern String MapVendorName(uint32_t vendorID);
extern void MapDepthStencilBits(Format format, uint &depthBits, uint &stencilBits);
extern const VkSurfaceTransformFlagsKHR TRANSFORMS_THAT_REQUIRE_FLIPPING;
extern const VkPrimitiveTopology VK_PRIMITIVE_MODES[];
extern const VkCullModeFlags VK_CULL_MODES[];
extern const VkPolygonMode VK_POLYGON_MODES[];
extern const VkCompareOp VK_CMP_FUNCS[];
extern const VkStencilOp VK_STENCIL_OPS[];
extern const VkBlendOp VK_BLEND_OPS[];
extern const VkBlendFactor VK_BLEND_FACTORS[];
extern const VkFilter VK_FILTERS[];
extern const VkSamplerMipmapMode VK_SAMPLER_MIPMAP_MODES[];
extern const VkSamplerAddressMode VK_SAMPLER_ADDRESS_MODES[];
extern const VkPipelineBindPoint VK_PIPELINE_BIND_POINTS[];
extern const ThsvsAccessType THSVS_ACCESS_TYPES[];
extern const VkImageLayout VK_IMAGE_LAYOUTS[];
extern const VkAccessFlags FULL_ACCESS_FLAGS;
extern void fullPipelineBarrier(VkCommandBuffer cmdBuff);
extern VkDeviceSize roundUp(VkDeviceSize numToRound, uint multiple);
extern uint nextPowerOf2(uint v);
extern bool isLayerSupported(const char *required, const vector<VkLayerProperties> &available);
extern bool isExtensionSupported(const char *required, const vector<VkExtensionProperties> &available);

template <typename T, size_t Size>
char (*countofHelper(T (&array)[Size]))[Size];

#define COUNTOF(array) (sizeof(*countofHelper(array)) + 0)

template <class T>
uint toUint(T value) {
    static_assert(std::is_arithmetic<T>::value, "T must be numeric");

    CCASSERT(static_cast<uintmax_t>(value) <= static_cast<uintmax_t>(std::numeric_limits<uint>::max()),
             "value is too big to be converted to uint");

    return static_cast<uint>(value);
}

} // namespace gfx
} // namespace cc
