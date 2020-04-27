#include "VKStd.h"
#include "VKCommands.h"
#include "VKDevice.h"
#include "VKQueue.h"
#include "VKContext.h"
#include "VKStateCache.h"

#define BUFFER_OFFSET(idx) (static_cast<char*>(0) + (idx))

NS_CC_BEGIN

namespace
{
    VkFormat MapVkFormat(GFXFormat format)
    {
        switch (format)
        {
        case GFXFormat::R8: return VK_FORMAT_R8_UNORM;
        case GFXFormat::R8SN: return VK_FORMAT_R8_SNORM;
        case GFXFormat::R8UI: return VK_FORMAT_R8_UINT;
        case GFXFormat::R8I: return VK_FORMAT_R8_SINT;
        case GFXFormat::RG8: return VK_FORMAT_R8G8_UNORM;
        case GFXFormat::RG8SN: return VK_FORMAT_R8G8_SNORM;
        case GFXFormat::RG8UI: return VK_FORMAT_R8G8_UINT;
        case GFXFormat::RG8I: return VK_FORMAT_R8G8_SINT;
        case GFXFormat::RGB8: return VK_FORMAT_R8G8B8_UNORM;
        case GFXFormat::RGB8SN: return VK_FORMAT_R8G8B8_SNORM;
        case GFXFormat::RGB8UI: return VK_FORMAT_R8G8B8_UINT;
        case GFXFormat::RGB8I: return VK_FORMAT_R8G8B8_SINT;
        case GFXFormat::RGBA8: return VK_FORMAT_R8G8B8A8_UNORM;
        case GFXFormat::BGRA8: return VK_FORMAT_B8G8R8A8_UNORM;
        case GFXFormat::RGBA8SN: return VK_FORMAT_R8G8B8A8_SNORM;
        case GFXFormat::RGBA8UI: return VK_FORMAT_R8G8B8A8_UINT;
        case GFXFormat::RGBA8I: return VK_FORMAT_R8G8B8A8_SINT;
        case GFXFormat::R16I: return VK_FORMAT_R16_SINT;
        case GFXFormat::R16UI: return VK_FORMAT_R16_UINT;
        case GFXFormat::R16F: return VK_FORMAT_R16_SFLOAT;
        case GFXFormat::RG16I: return VK_FORMAT_R16G16_SINT;
        case GFXFormat::RG16UI: return VK_FORMAT_R16G16_UINT;
        case GFXFormat::RG16F: return VK_FORMAT_R16G16_SFLOAT;
        case GFXFormat::RGB16I: return VK_FORMAT_R16G16B16_SINT;
        case GFXFormat::RGB16UI: return VK_FORMAT_R16G16B16_UINT;
        case GFXFormat::RGB16F: return VK_FORMAT_R16G16B16_SFLOAT;
        case GFXFormat::RGBA16I: return VK_FORMAT_R16G16B16A16_SINT;
        case GFXFormat::RGBA16UI: return VK_FORMAT_R16G16B16A16_UINT;
        case GFXFormat::RGBA16F: return VK_FORMAT_R16G16B16A16_SFLOAT;
        case GFXFormat::R32I: return VK_FORMAT_R32_SINT;
        case GFXFormat::R32UI: return VK_FORMAT_R32_UINT;
        case GFXFormat::R32F: return VK_FORMAT_R32_SFLOAT;
        case GFXFormat::RG32I: return VK_FORMAT_R32G32_SINT;
        case GFXFormat::RG32UI: return VK_FORMAT_R32G32_UINT;
        case GFXFormat::RG32F: return VK_FORMAT_R32G32_SFLOAT;
        case GFXFormat::RGB32I: return VK_FORMAT_R32G32B32_SINT;
        case GFXFormat::RGB32UI: return VK_FORMAT_R32G32B32_UINT;
        case GFXFormat::RGB32F: return VK_FORMAT_R32G32B32_SFLOAT;
        case GFXFormat::RGBA32I: return VK_FORMAT_R32G32B32A32_SINT;
        case GFXFormat::RGBA32UI: return VK_FORMAT_R32G32B32A32_UINT;
        case GFXFormat::RGBA32F: return VK_FORMAT_R32G32B32A32_SFLOAT;

        case GFXFormat::R5G6B5: return VK_FORMAT_R5G6B5_UNORM_PACK16;
        case GFXFormat::R11G11B10F: return VK_FORMAT_B10G11R11_UFLOAT_PACK32;
        case GFXFormat::RGB5A1: return VK_FORMAT_R5G5B5A1_UNORM_PACK16;
        case GFXFormat::RGBA4: return VK_FORMAT_R4G4B4A4_UNORM_PACK16;
        case GFXFormat::RGB10A2: return VK_FORMAT_A2B10G10R10_UNORM_PACK32;
        case GFXFormat::RGB10A2UI: return VK_FORMAT_A2B10G10R10_UINT_PACK32;
        case GFXFormat::RGB9E5: return VK_FORMAT_E5B9G9R9_UFLOAT_PACK32;
        case GFXFormat::D16: return VK_FORMAT_D16_UNORM;
        case GFXFormat::D16S8: return VK_FORMAT_D16_UNORM_S8_UINT;
        case GFXFormat::D24: return VK_FORMAT_X8_D24_UNORM_PACK32;
        case GFXFormat::D24S8: return VK_FORMAT_D24_UNORM_S8_UINT;
        case GFXFormat::D32F: return VK_FORMAT_D32_SFLOAT;
        case GFXFormat::D32F_S8: return VK_FORMAT_D32_SFLOAT_S8_UINT;

        case GFXFormat::BC1: return VK_FORMAT_BC1_RGB_UNORM_BLOCK;
        case GFXFormat::BC1_ALPHA: return VK_FORMAT_BC1_RGBA_UNORM_BLOCK;
        case GFXFormat::BC1_SRGB: return VK_FORMAT_BC1_RGB_SRGB_BLOCK;
        case GFXFormat::BC1_SRGB_ALPHA: return VK_FORMAT_BC1_RGBA_SRGB_BLOCK;
        case GFXFormat::BC2: return VK_FORMAT_BC2_UNORM_BLOCK;
        case GFXFormat::BC2_SRGB: return VK_FORMAT_BC2_SRGB_BLOCK;
        case GFXFormat::BC3: return VK_FORMAT_BC3_UNORM_BLOCK;
        case GFXFormat::BC3_SRGB: return VK_FORMAT_BC3_SRGB_BLOCK;
        case GFXFormat::BC4: return VK_FORMAT_BC4_UNORM_BLOCK;
        case GFXFormat::BC4_SNORM: return VK_FORMAT_BC4_SNORM_BLOCK;
        case GFXFormat::BC5: return VK_FORMAT_BC5_UNORM_BLOCK;
        case GFXFormat::BC5_SNORM: return VK_FORMAT_BC5_SNORM_BLOCK;
        case GFXFormat::BC6H_UF16: return VK_FORMAT_BC6H_UFLOAT_BLOCK;
        case GFXFormat::BC6H_SF16: return VK_FORMAT_BC6H_SFLOAT_BLOCK;
        case GFXFormat::BC7: return VK_FORMAT_BC7_UNORM_BLOCK;
        case GFXFormat::BC7_SRGB: return VK_FORMAT_BC7_SRGB_BLOCK;

        case GFXFormat::ETC2_RGB8: return VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK;
        case GFXFormat::ETC2_SRGB8: return VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK;
        case GFXFormat::ETC2_RGB8_A1: return VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK;
        case GFXFormat::ETC2_SRGB8_A1: return VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK;
        case GFXFormat::ETC2_RGBA8: return VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK;
        case GFXFormat::ETC2_SRGB8_A8: return VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK;
        case GFXFormat::EAC_R11: return VK_FORMAT_EAC_R11_UNORM_BLOCK;
        case GFXFormat::EAC_R11SN: return VK_FORMAT_EAC_R11_SNORM_BLOCK;
        case GFXFormat::EAC_RG11: return VK_FORMAT_EAC_R11G11_UNORM_BLOCK;
        case GFXFormat::EAC_RG11SN: return VK_FORMAT_EAC_R11G11_SNORM_BLOCK;

        case GFXFormat::PVRTC_RGB2: return VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG;
        case GFXFormat::PVRTC_RGBA2: return VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG;
        case GFXFormat::PVRTC_RGB4: return VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG;
        case GFXFormat::PVRTC_RGBA4: return VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG;
        case GFXFormat::PVRTC2_2BPP: return VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG;
        case GFXFormat::PVRTC2_4BPP: return VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG;
        default:
        {
            CCASSERT(false, "Unsupported GFXFormat, convert to VkFormat failed.");
            return VK_FORMAT_B8G8R8A8_UNORM;
        }
        }
    }

    VkSampleCountFlagBits MapVkSampleCount(uint sampleCount)
    {
        if      (sampleCount ==  1) return VK_SAMPLE_COUNT_1_BIT;
        else if (sampleCount ==  2) return VK_SAMPLE_COUNT_2_BIT;
        else if (sampleCount ==  4) return VK_SAMPLE_COUNT_4_BIT;
        else if (sampleCount ==  8) return VK_SAMPLE_COUNT_8_BIT;
        else if (sampleCount == 16) return VK_SAMPLE_COUNT_16_BIT;
        else if (sampleCount == 32) return VK_SAMPLE_COUNT_32_BIT;
        else if (sampleCount == 64) return VK_SAMPLE_COUNT_64_BIT;
        else                        return VK_SAMPLE_COUNT_1_BIT;
    }

    VkAttachmentLoadOp MapVkLoadOp(GFXLoadOp loadOp)
    {
        switch (loadOp)
        {
        case GFXLoadOp::CLEAR: return VK_ATTACHMENT_LOAD_OP_CLEAR;
        case GFXLoadOp::LOAD: return VK_ATTACHMENT_LOAD_OP_LOAD;
        case GFXLoadOp::DISCARD: return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        default:
        {
            CCASSERT(false, "Unsupported GFXLoadOp, convert to VkLoadOp failed.");
            return VK_ATTACHMENT_LOAD_OP_LOAD;
        }
        }
    }

    VkAttachmentStoreOp MapVkStoreOp(GFXStoreOp storeOp)
    {
        switch (storeOp)
        {
        case GFXStoreOp::STORE: return VK_ATTACHMENT_STORE_OP_STORE;
        case GFXStoreOp::DISCARD: return VK_ATTACHMENT_STORE_OP_DONT_CARE;
        default:
        {
            CCASSERT(false, "Unsupported GFXStoreOp, convert to VkStoreOp failed.");
            return VK_ATTACHMENT_STORE_OP_STORE;
        }
        }
    }

    VkImageLayout MapVkImageLayout(GFXTextureLayout layout)
    {
        switch (layout)
        {
        case GFXTextureLayout::UNDEFINED: return VK_IMAGE_LAYOUT_UNDEFINED;
        case GFXTextureLayout::GENERAL: return VK_IMAGE_LAYOUT_GENERAL;
        case GFXTextureLayout::COLOR_ATTACHMENT_OPTIMAL: return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        case GFXTextureLayout::DEPTH_STENCIL_ATTACHMENT_OPTIMAL: return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        case GFXTextureLayout::DEPTH_STENCIL_READONLY_OPTIMAL: return VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
        case GFXTextureLayout::SHADER_READONLY_OPTIMAL: return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        case GFXTextureLayout::TRANSFER_SRC_OPTIMAL: return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
        case GFXTextureLayout::TRANSFER_DST_OPTIMAL: return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        case GFXTextureLayout::PREINITIALIZED: return VK_IMAGE_LAYOUT_PREINITIALIZED;
        case GFXTextureLayout::PRESENT_SRC: return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        default:
        {
            CCASSERT(false, "Unsupported GFXTextureLayout, convert to VkImageLayout failed.");
            return VK_IMAGE_LAYOUT_GENERAL;
        }
        }
    }

    VkPipelineBindPoint MapVkPipelineBindPoint(GFXPipelineBindPoint bindPoint)
    {
        switch (bindPoint)
        {
        case GFXPipelineBindPoint::GRAPHICS: return VK_PIPELINE_BIND_POINT_GRAPHICS;
        case GFXPipelineBindPoint::COMPUTE: return VK_PIPELINE_BIND_POINT_COMPUTE;
        case GFXPipelineBindPoint::RAY_TRACING: return VK_PIPELINE_BIND_POINT_RAY_TRACING_NV;
        default:
        {
            CCASSERT(false, "Unsupported GFXPipelineBindPoint, convert to VkPipelineBindPoint failed.");
            return VK_PIPELINE_BIND_POINT_GRAPHICS;
        }
        }
    }

    VkImageType MapVkImageType(GFXTextureType type)
    {
        switch (type)
        {
        case GFXTextureType::TEX1D: return VK_IMAGE_TYPE_1D;
        case GFXTextureType::TEX2D: return VK_IMAGE_TYPE_2D;
        case GFXTextureType::TEX3D: return VK_IMAGE_TYPE_3D;
        default:
        {
            CCASSERT(false, "Unsupported GFXTextureType, convert to VkImageType failed.");
            return VK_IMAGE_TYPE_2D;
        }
        }
    }

    VkSampleCountFlagBits MapVkSampleCount(GFXSampleCount count)
    {
        switch (count)
        {
        case GFXSampleCount::X1: return VK_SAMPLE_COUNT_1_BIT;
        case GFXSampleCount::X2: return VK_SAMPLE_COUNT_2_BIT;
        case GFXSampleCount::X4: return VK_SAMPLE_COUNT_4_BIT;
        case GFXSampleCount::X8: return VK_SAMPLE_COUNT_8_BIT;
        case GFXSampleCount::X16: return VK_SAMPLE_COUNT_16_BIT;
        case GFXSampleCount::X32: return VK_SAMPLE_COUNT_32_BIT;
        default:
        {
            CCASSERT(false, "Unsupported GFXTextureType, convert to VkImageType failed.");
            return VK_SAMPLE_COUNT_1_BIT;
        }
        }
    }

    VkImageUsageFlagBits MapVkImageUsageFlagBits(GFXTextureUsage usage)
    {
        uint32_t flags = 0;
        if (usage & GFXTextureUsage::TRANSFER_SRC) flags |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        if (usage & GFXTextureUsage::TRANSFER_DST) flags |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
        if (usage & GFXTextureUsage::SAMPLED) flags |= VK_IMAGE_USAGE_SAMPLED_BIT;
        if (usage & GFXTextureUsage::STORAGE) flags |= VK_IMAGE_USAGE_STORAGE_BIT;
        if (usage & GFXTextureUsage::COLOR_ATTACHMENT) flags |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        if (usage & GFXTextureUsage::DEPTH_STENCIL_ATTACHMENT) flags |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        if (usage & GFXTextureUsage::TRANSIENT_ATTACHMENT) flags |= VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT;
        if (usage & GFXTextureUsage::INPUT_ATTACHMENT) flags |= VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;
        return (VkImageUsageFlagBits)flags;
    }

    uint32_t selectMemoryType(const VkPhysicalDeviceMemoryProperties& memoryProperties, uint32_t memoryTypeBits, VkMemoryPropertyFlags flags)
    {
        for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; ++i)
            if ((memoryTypeBits & (1 << i)) != 0 && (memoryProperties.memoryTypes[i].propertyFlags & flags) == flags)
                return i;

        CCASSERT(false, "No compatible memory type found.");
        return ~0u;
    }

    VkImageViewType MapVkImageViewType(GFXTextureViewType viewType)
    {
        switch (viewType)
        {
        case GFXTextureViewType::TV1D: return VK_IMAGE_VIEW_TYPE_1D;
        case GFXTextureViewType::TV1D_ARRAY: return VK_IMAGE_VIEW_TYPE_1D_ARRAY;
        case GFXTextureViewType::TV2D: return VK_IMAGE_VIEW_TYPE_2D;
        case GFXTextureViewType::TV2D_ARRAY: return VK_IMAGE_VIEW_TYPE_2D_ARRAY;
        case GFXTextureViewType::TV3D: return VK_IMAGE_VIEW_TYPE_3D;
        case GFXTextureViewType::CUBE: return VK_IMAGE_VIEW_TYPE_CUBE;
        default:
        {
            CCASSERT(false, "Unsupported GFXTextureViewType, convert to VkImageViewType failed.");
            return VK_IMAGE_VIEW_TYPE_2D;
        }
        }
    }

    VkImageAspectFlags MapVkImageAspectFlags(GFXFormat format)
    {
        switch (format)
        {
        case GFXFormat::D16:
        case GFXFormat::D24:
        case GFXFormat::D32F:
            return VK_IMAGE_ASPECT_DEPTH_BIT;
        case GFXFormat::D16S8:
        case GFXFormat::D24S8:
        case GFXFormat::D32F_S8:
            return VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
        default: 
            return VK_IMAGE_ASPECT_COLOR_BIT;
        }
    }

    VkCommandBufferLevel MapVkCommandBufferLevel(GFXCommandBufferType type)
    {
        switch (type)
        {
        case GFXCommandBufferType::PRIMARY: return VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        case GFXCommandBufferType::SECONDARY: return VK_COMMAND_BUFFER_LEVEL_SECONDARY;
        default:
        {
            CCASSERT(false, "Unsupported GFXCommandBufferType, convert to VkCommandBufferLevel failed.");
            return VK_COMMAND_BUFFER_LEVEL_SECONDARY;
        }
        }
    }
}

void CCVKCmdFuncCreateRenderPass(CCVKDevice* device, CCVKGPURenderPass* gpuRenderPass)
{
    uint32_t colorAttachmentCount = gpuRenderPass->colorAttachments.size();
    std::vector<VkAttachmentDescription> attachmentDescriptions(colorAttachmentCount + 1);
    for (uint32_t i = 0u; i < colorAttachmentCount; i++)
    {
        auto &attachment = gpuRenderPass->colorAttachments[i];
        attachmentDescriptions[i].format = MapVkFormat(attachment.format);
        attachmentDescriptions[i].samples = MapVkSampleCount(attachment.sampleCount);
        attachmentDescriptions[i].loadOp = MapVkLoadOp(attachment.loadOp);
        attachmentDescriptions[i].storeOp = MapVkStoreOp(attachment.storeOp);
        attachmentDescriptions[i].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        attachmentDescriptions[i].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachmentDescriptions[i].initialLayout = MapVkImageLayout(attachment.beginLayout);
        attachmentDescriptions[i].finalLayout = MapVkImageLayout(attachment.endLayout);
    }
    auto &depthStencilAttachment = gpuRenderPass->depthStencilAttachment;
    attachmentDescriptions[colorAttachmentCount].format = MapVkFormat(depthStencilAttachment.format);
    attachmentDescriptions[colorAttachmentCount].samples = MapVkSampleCount(depthStencilAttachment.sampleCount);
    attachmentDescriptions[colorAttachmentCount].loadOp = MapVkLoadOp(depthStencilAttachment.depthLoadOp);
    attachmentDescriptions[colorAttachmentCount].storeOp = MapVkStoreOp(depthStencilAttachment.depthStoreOp);
    attachmentDescriptions[colorAttachmentCount].stencilLoadOp = MapVkLoadOp(depthStencilAttachment.stencilLoadOp);
    attachmentDescriptions[colorAttachmentCount].stencilStoreOp = MapVkStoreOp(depthStencilAttachment.stencilStoreOp);
    attachmentDescriptions[colorAttachmentCount].initialLayout = MapVkImageLayout(depthStencilAttachment.beginLayout);
    attachmentDescriptions[colorAttachmentCount].finalLayout = MapVkImageLayout(depthStencilAttachment.endLayout);

    uint32_t subpassCount = gpuRenderPass->subPasses.size();
    std::vector<VkSubpassDescription> subpassDescriptions(1, { VK_PIPELINE_BIND_POINT_GRAPHICS });
    std::vector<VkAttachmentReference> attachmentReferences;
    if (subpassCount) // pass on user-specified subpasses
    {
        subpassDescriptions.resize(subpassCount);
        for (uint32_t i = 0u; i < subpassCount; i++)
        {
            auto &subpass = gpuRenderPass->subPasses[i];
            subpassDescriptions[i].pipelineBindPoint = MapVkPipelineBindPoint(subpass.bindPoint);
            // TODO
        }
    }
    else // generate a default subpass from attachment info
    {
        for (uint32_t i = 0u; i < colorAttachmentCount; i++)
        {
            attachmentReferences.push_back({ i, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL });
        }
        attachmentReferences.push_back({ colorAttachmentCount, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL });
        subpassDescriptions[0].colorAttachmentCount = attachmentReferences.size() - 1;
        subpassDescriptions[0].pColorAttachments = attachmentReferences.data();
        subpassDescriptions[0].pDepthStencilAttachment = &attachmentReferences.back();
    }

    VkRenderPassCreateInfo renderPassCreateInfo{ VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
    renderPassCreateInfo.attachmentCount = attachmentDescriptions.size();
    renderPassCreateInfo.pAttachments = attachmentDescriptions.data();
    renderPassCreateInfo.subpassCount = subpassDescriptions.size();
    renderPassCreateInfo.pSubpasses = subpassDescriptions.data();

    VK_CHECK(vkCreateRenderPass(device->gpuDevice()->vkDevice, &renderPassCreateInfo, nullptr, &gpuRenderPass->vkRenderPass));
}

void CCVKCmdFuncDestroyRenderPass(CCVKDevice* device, CCVKGPURenderPass* gpuRenderPass)
{
    if (gpuRenderPass->vkRenderPass != VK_NULL_HANDLE)
    {
        vkDestroyRenderPass(device->gpuDevice()->vkDevice, gpuRenderPass->vkRenderPass, nullptr);
        gpuRenderPass->vkRenderPass = VK_NULL_HANDLE;
    }
}

void CCVKCmdFuncGetDeviceQueue(CCVKDevice* device, CCVKGPUQueue* gpuQueue)
{
    uint32_t queueType = 0;
    VkBool32 needPresentable = VK_FALSE;
    switch (gpuQueue->type)
    {
    case GFXQueueType::GRAPHICS: queueType = VK_QUEUE_GRAPHICS_BIT; needPresentable = VK_TRUE; break;
    case GFXQueueType::COMPUTE: queueType = VK_QUEUE_COMPUTE_BIT; break;
    case GFXQueueType::TRANSFER: queueType = VK_QUEUE_TRANSFER_BIT; break;
    }

    const CCVKGPUContext* context = ((CCVKContext*)device->getContext())->gpuContext();

    size_t queueCount = context->queueFamilyProperties.size();
    for (uint32_t i = 0U; i < queueCount; ++i)
    {
        const VkQueueFamilyProperties &properties = context->queueFamilyProperties[i];
        const VkBool32 isPresentable = context->queueFamilyPresentables[i];
        if (properties.queueCount > 0 && (properties.queueFlags & queueType) && (!needPresentable || isPresentable))
        {
            vkGetDeviceQueue(device->gpuDevice()->vkDevice, i, 0, &gpuQueue->vkQueue);
            gpuQueue->queueFamilyIndex = i;
            break;
        }
    }
}

void CCVKCmdFuncGetSwapchainTextures(CCVKDevice* device, std::vector<CCVKGPUTexture*>& textures)
{
}

void CCVKCmdFuncCreateCommandPool(CCVKDevice* device, CCVKGPUCommandPool* gpuCommandPool)
{
    VkCommandPoolCreateInfo createInfo{ VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
    createInfo.queueFamilyIndex = ((CCVKQueue*)device->getQueue())->gpuQueue()->queueFamilyIndex;
    createInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;

    VK_CHECK(vkCreateCommandPool(device->gpuDevice()->vkDevice, &createInfo, nullptr, &gpuCommandPool->vkCommandPool));
}

void CCVKCmdFuncDestroyCommandPool(CCVKDevice* device, CCVKGPUCommandPool* gpuCommandPool)
{
    if (gpuCommandPool->vkCommandPool != VK_NULL_HANDLE)
    {
        vkDestroyCommandPool(device->gpuDevice()->vkDevice, gpuCommandPool->vkCommandPool, nullptr);
        gpuCommandPool->vkCommandPool = VK_NULL_HANDLE;
    }
}

void CCVKCmdFuncAllocateCommandBuffer(CCVKDevice* device, CCVKGPUCommandBuffer* gpuCommandBuffer)
{
    CCVKGPUCommandPool* commandPool = gpuCommandBuffer->commandPool;
    VkCommandBufferLevel level = MapVkCommandBufferLevel(gpuCommandBuffer->type);

    if (commandPool->commandBuffers[level].size())
    {
        gpuCommandBuffer->vkCommandBuffer = commandPool->commandBuffers[level].pop();
    }
    else
    {
        VkCommandBufferAllocateInfo allocateInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
        allocateInfo.commandPool = gpuCommandBuffer->commandPool->vkCommandPool;
        allocateInfo.commandBufferCount = 1;
        allocateInfo.level = level;

        VK_CHECK(vkAllocateCommandBuffers(device->gpuDevice()->vkDevice, &allocateInfo, &gpuCommandBuffer->vkCommandBuffer));
    }
}

void CCVKCmdFuncFreeCommandBuffer(CCVKDevice* device, CCVKGPUCommandBuffer* gpuCommandBuffer)
{
    VkCommandBufferLevel level = MapVkCommandBufferLevel(gpuCommandBuffer->type);

    if (gpuCommandBuffer->vkCommandBuffer)
    {
        gpuCommandBuffer->commandPool->commandBuffers[level].push(gpuCommandBuffer->vkCommandBuffer);
        gpuCommandBuffer->vkCommandBuffer = VK_NULL_HANDLE;
    }
}

void CCVKCmdFuncCreateBuffer(CCVKDevice* device, CCVKGPUBuffer* gpuBuffer)
{

}

void CCVKCmdFuncDestroyBuffer(CCVKDevice* device, CCVKGPUBuffer* gpuBuffer)
{

}

void CCVKCmdFuncResizeBuffer(CCVKDevice* device, CCVKGPUBuffer* gpuBuffer)
{

}

void CCVKCmdFuncUpdateBuffer(CCVKDevice* device, CCVKGPUBuffer* gpuBuffer, void* buffer, uint offset, uint size)
{

}

void CCVKCmdFuncCreateTexture(CCVKDevice* device, CCVKGPUTexture* gpuTexture)
{
    auto vkDevice = device->gpuDevice()->vkDevice;

    VkImageCreateInfo createInfo{ VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO };
    createInfo.imageType = MapVkImageType(gpuTexture->type);
    createInfo.format = MapVkFormat(gpuTexture->format);
    createInfo.extent = { gpuTexture->width, gpuTexture->height, gpuTexture->depth };
    createInfo.mipLevels = gpuTexture->mipLevel;
    createInfo.arrayLayers = gpuTexture->arrayLayer;
    createInfo.samples = MapVkSampleCount(gpuTexture->samples);
    createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    createInfo.usage = MapVkImageUsageFlagBits(gpuTexture->usage);
    createInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    VK_CHECK(vkCreateImage(vkDevice, &createInfo, nullptr, &gpuTexture->vkImage));

    VkMemoryRequirements memoryRequirements;
    vkGetImageMemoryRequirements(vkDevice, gpuTexture->vkImage, &memoryRequirements);

    uint32_t memoryTypeIndex = selectMemoryType(
        ((CCVKContext*)device->getContext())->gpuContext()->physicalDeviceMemoryProperties,
        memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    VkMemoryAllocateInfo allocateInfo{ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
    allocateInfo.allocationSize = memoryRequirements.size;
    allocateInfo.memoryTypeIndex = memoryTypeIndex;

    VK_CHECK(vkAllocateMemory(vkDevice, &allocateInfo, nullptr, &gpuTexture->vkDeviceMemory));

    VK_CHECK(vkBindImageMemory(vkDevice, gpuTexture->vkImage, gpuTexture->vkDeviceMemory, 0));
}

void CCVKCmdFuncDestroyTexture(CCVKDevice* device, CCVKGPUTexture* gpuTexture)
{
    auto vkDevice = device->gpuDevice()->vkDevice;

    if (gpuTexture->vkImage)
    {
        vkDestroyImage(vkDevice, gpuTexture->vkImage, nullptr);
        gpuTexture->vkImage = VK_NULL_HANDLE;
    }

    if (gpuTexture->vkDeviceMemory)
    {
        vkFreeMemory(vkDevice, gpuTexture->vkDeviceMemory, nullptr);
        gpuTexture->vkDeviceMemory = VK_NULL_HANDLE;
    }
}

void CCVKCmdFuncResizeTexture(CCVKDevice* device, CCVKGPUTexture* gpuTexture)
{
    CCVKCmdFuncDestroyTexture(device, gpuTexture);
    CCVKCmdFuncCreateTexture(device, gpuTexture);
}

void CCVKCmdFuncCreateTextureView(CCVKDevice* device, CCVKGPUTextureView* gpuTextureView)
{
    VkImageViewCreateInfo createInfo{ VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
    createInfo.image = gpuTextureView->gpuTexture->vkImage;
    createInfo.viewType = MapVkImageViewType(gpuTextureView->type);
    createInfo.format = MapVkFormat(gpuTextureView->format);
    createInfo.subresourceRange.aspectMask = MapVkImageAspectFlags(gpuTextureView->format);
    createInfo.subresourceRange.baseMipLevel = gpuTextureView->baseLevel;
    createInfo.subresourceRange.levelCount = gpuTextureView->levelCount;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    VK_CHECK(vkCreateImageView(device->gpuDevice()->vkDevice, &createInfo, nullptr, &gpuTextureView->vkImageView));
}

void CCVKCmdFuncDestroyTextureView(CCVKDevice* device, CCVKGPUTextureView* gpuTextureView)
{
    if (gpuTextureView->vkImageView != VK_NULL_HANDLE)
    {
        vkDestroyImageView(device->gpuDevice()->vkDevice, gpuTextureView->vkImageView, nullptr);
        gpuTextureView->vkImageView = VK_NULL_HANDLE;
    }
}

void CCVKCmdFuncCreateSampler(CCVKDevice* device, CCVKGPUSampler* gpuSampler)
{

}

void CCVKCmdFuncDestroySampler(CCVKDevice* device, CCVKGPUSampler* gpuSampler)
{

}

void CCVKCmdFuncCreateShader(CCVKDevice* device, CCVKGPUShader* gpuShader)
{

}

void CCVKCmdFuncDestroyShader(CCVKDevice* device, CCVKGPUShader* gpuShader)
{

}

void CCVKCmdFuncCreateInputAssembler(CCVKDevice* device, CCVKGPUInputAssembler* gpuInputAssembler)
{

}

void CCVKCmdFuncDestroyInputAssembler(CCVKDevice* device, CCVKGPUInputAssembler* gpuInputAssembler)
{

}

void CCVKCmdFuncCreateFramebuffer(CCVKDevice* device, CCVKGPUFramebuffer* gpuFBO)
{
    if (!gpuFBO->isOffscreen)
    {
        gpuFBO->swapchain = device->gpuSwapchain();
        return;
    }

    uint32_t colorViewCount = gpuFBO->gpuColorViews.size();
    std::vector<VkImageView> attachments(colorViewCount + (gpuFBO->gpuDepthStencilView ? 1 : 0));
    for (uint32_t i = 0u; i < colorViewCount; i++)
    {
        attachments[i] = gpuFBO->gpuColorViews[i]->vkImageView;
    }
    if (gpuFBO->gpuDepthStencilView)
    {
        attachments[colorViewCount] = gpuFBO->gpuDepthStencilView->vkImageView;
    }

    VkFramebufferCreateInfo createInfo{ VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO };
    createInfo.renderPass = gpuFBO->gpuRenderPass->vkRenderPass;
    createInfo.attachmentCount = attachments.size();
    createInfo.pAttachments = attachments.data();
    createInfo.width = colorViewCount ? gpuFBO->gpuColorViews[0]->gpuTexture->width : 1;
    createInfo.height = colorViewCount ? gpuFBO->gpuColorViews[0]->gpuTexture->height : 1;
    createInfo.layers = 1;

    VkFramebuffer framebuffer = 0;
    VK_CHECK(vkCreateFramebuffer(device->gpuDevice()->vkDevice, &createInfo, nullptr, &framebuffer));
}

void CCVKCmdFuncDestroyFramebuffer(CCVKDevice* device, CCVKGPUFramebuffer* gpuFBO)
{
    if (gpuFBO->vkFramebuffer != VK_NULL_HANDLE)
    {
        vkDestroyFramebuffer(device->gpuDevice()->vkDevice, gpuFBO->vkFramebuffer, nullptr);
        gpuFBO->vkFramebuffer = VK_NULL_HANDLE;
    }
}

void CCVKCmdFuncBeginRenderPass(CCVKDevice* device, CCVKGPUCommandBuffer* commandBuffer)
{

}

void CCVKCmdFuncEndRenderPass(CCVKDevice* device, CCVKGPUCommandBuffer* commandBuffer)
{

}

void CCVKCmdFuncEnd(CCVKDevice* device, CCVKGPUCommandBuffer* commandBuffer)
{

}

void CCVKCmdFuncExecuteCmds(CCVKDevice* device, CCVKCmdPackage* cmd_package)
{

}

void CCVKCmdFuncCopyBuffersToTexture(CCVKDevice* device, uint8_t* const* buffers, CCVKGPUTexture* gpuTexture, const GFXBufferTextureCopyList& regions)
{

}


NS_CC_END
