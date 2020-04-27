#include "VKStd.h"
#include "VKCommandBuffer.h"
#include "VKCommands.h"
#include "VKCommandAllocator.h"
#include "VKFramebuffer.h"

#include "VKPipelineState.h"
#include "VKBindingLayout.h"
#include "VKInputAssembler.h"

NS_CC_BEGIN

CCVKCommandBuffer::CCVKCommandBuffer(GFXDevice* device)
    : GFXCommandBuffer(device)
{
}

CCVKCommandBuffer::~CCVKCommandBuffer()
{
}

bool CCVKCommandBuffer::initialize(const GFXCommandBufferInfo& info)
{
    if (!info.allocator)
    {
        return false;
    }

    _allocator = info.allocator;
    _type = info.type;

    _gpuCommandBuffer = CC_NEW(CCVKGPUCommandBuffer);
    _gpuCommandBuffer->type = _type;
    _gpuCommandBuffer->commandPool = ((CCVKCommandAllocator*)_allocator)->gpuCommandPool();
    CCVKCmdFuncAllocateCommandBuffer((CCVKDevice*)_device, _gpuCommandBuffer);

    _status = GFXStatus::SUCCESS;
    return true;
}

void CCVKCommandBuffer::destroy()
{
    if (_gpuCommandBuffer)
    {
        CCVKCmdFuncFreeCommandBuffer((CCVKDevice*)_device, _gpuCommandBuffer);
        CC_DELETE(_gpuCommandBuffer);
        _gpuCommandBuffer = nullptr;
    }

    _allocator = nullptr;
    _status = GFXStatus::UNREADY;
}

void CCVKCommandBuffer::begin()
{
    _curGPUPipelineState = nullptr;
    _curGPUBlendLayout = nullptr;
    _curGPUInputAssember = nullptr;
    _numDrawCalls = 0;
    _numInstances = 0;
    _numTriangles = 0;

    VkCommandBufferBeginInfo beginInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    if (_type == GFXCommandBufferType::SECONDARY)
    {
        VkCommandBufferInheritanceInfo inheritance{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO };
        // TODO
        //beginInfo.pInheritanceInfo = &inheritance;
    }

    VK_CHECK(vkBeginCommandBuffer(_gpuCommandBuffer->vkCommandBuffer, &beginInfo));
}

void CCVKCommandBuffer::end()
{
    if (_isStateInvalid)
    {
        BindStates();
    }
    _isInRenderPass = false;

    VK_CHECK(vkEndCommandBuffer(_gpuCommandBuffer->vkCommandBuffer));
}

void CCVKCommandBuffer::beginRenderPass(GFXFramebuffer* fbo, const GFXRect& render_area,
    GFXClearFlags clear_flags, const std::vector<GFXColor>& colors, float depth, int stencil)
{
    _isInRenderPass = true;

    CCVKGPUFramebuffer* gpuFBO = ((CCVKFramebuffer*)fbo)->gpuFBO();

    VkClearValue clearValues[2];
    clearValues[0].color = { colors[0].r, colors[0].g, colors[0].b, colors[0].a };
    clearValues[1].depthStencil = { depth, (uint32_t)stencil };

    VkRenderPassBeginInfo passBeginInfo{ VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO };
    passBeginInfo.renderPass = gpuFBO->gpuRenderPass->vkRenderPass;
    passBeginInfo.framebuffer = gpuFBO->isOffscreen ? gpuFBO->vkFramebuffer : gpuFBO->swapchain->vkSwapchainFramebuffers[gpuFBO->swapchain->curImageIndex];
    passBeginInfo.renderArea.extent.width = render_area.width;
    passBeginInfo.renderArea.extent.height = render_area.height;
    passBeginInfo.clearValueCount = 2;
    passBeginInfo.pClearValues = clearValues;
    vkCmdBeginRenderPass(gpuCommandBuffer()->vkCommandBuffer, &passBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void CCVKCommandBuffer::endRenderPass()
{
    _isInRenderPass = false;		
    vkCmdEndRenderPass(_gpuCommandBuffer->vkCommandBuffer);
}

void CCVKCommandBuffer::bindPipelineState(GFXPipelineState* pso)
{
    _curGPUPipelineState = ((CCVKPipelineState*)pso)->gpuPipelineState();
    _isStateInvalid = true;
}


void CCVKCommandBuffer::bindBindingLayout(GFXBindingLayout* layout)
{
    _curGPUBlendLayout = ((CCVKBindingLayout*)layout)->gpuBindingLayout();
    _isStateInvalid = true;
}

void CCVKCommandBuffer::bindInputAssembler(GFXInputAssembler* ia)
{
    _curGPUInputAssember = ((CCVKInputAssembler*)ia)->gpuInputAssembler();
    _isStateInvalid = true;
}

void CCVKCommandBuffer::setViewport(const GFXViewport& vp)
{
    if ((_curViewport.left != vp.left) ||
        (_curViewport.top != vp.top) ||
        (_curViewport.width != vp.width) ||
        (_curViewport.height != vp.height) ||
        math::IsNotEqualF(_curViewport.minDepth, vp.minDepth) ||
        math::IsNotEqualF(_curViewport.maxDepth, vp.maxDepth))
    {
        _curViewport = vp;
        _isStateInvalid = true;
    }
}

void CCVKCommandBuffer::setScissor(const GFXRect& rect)
{
    if ((_curScissor.x != rect.x) ||
        (_curScissor.y != rect.y) ||
        (_curScissor.width != rect.width) ||
        (_curScissor.height != rect.height))
    {
        _curScissor = rect;
        _isStateInvalid = true;
    }
}

void CCVKCommandBuffer::setLineWidth(const float width)
{
    if (math::IsNotEqualF(_curLineWidth, width))
    {
        _curLineWidth = width;
        _isStateInvalid = true;
    }
}

void CCVKCommandBuffer::setDepthBias(float constant, float clamp, float slope)
{
    if (math::IsNotEqualF(_curDepthBias.constant, constant) ||
        math::IsNotEqualF(_curDepthBias.clamp, clamp) ||
        math::IsNotEqualF(_curDepthBias.slope, slope))
    {
        _curDepthBias.constant = constant;
        _curDepthBias.clamp = clamp;
        _curDepthBias.slope = slope;
        _isStateInvalid = true;
    }
}

void CCVKCommandBuffer::setBlendConstants(const GFXColor& constants)
{
    if (math::IsNotEqualF(_curBlendConstants.r, constants.r) ||
        math::IsNotEqualF(_curBlendConstants.g, constants.g) ||
        math::IsNotEqualF(_curBlendConstants.b, constants.b) ||
        math::IsNotEqualF(_curBlendConstants.a, constants.a))
    {
        _curBlendConstants.r = constants.r;
        _curBlendConstants.g = constants.g;
        _curBlendConstants.b = constants.b;
        _curBlendConstants.a = constants.a;
        _isStateInvalid = true;
    }
}

void CCVKCommandBuffer::setDepthBound(float min_bounds, float max_bounds)
{
    if (math::IsNotEqualF(_curDepthBounds.min_bounds, min_bounds) ||
        math::IsNotEqualF(_curDepthBounds.max_bounds, max_bounds))
    {
        _curDepthBounds.min_bounds = min_bounds;
        _curDepthBounds.max_bounds = max_bounds;
        _isStateInvalid = true;
    }
}

void CCVKCommandBuffer::setStencilWriteMask(GFXStencilFace face, uint mask)
{
    if ((_curStencilWriteMask.face != face) ||
        (_curStencilWriteMask.write_mask != mask))
    {
        _curStencilWriteMask.face = face;
        _curStencilWriteMask.write_mask = mask;
        _isStateInvalid = true;
    }
}

void CCVKCommandBuffer::setStencilCompareMask(GFXStencilFace face, int ref, uint mask)
{
    if ((_curStencilCompareMask.face != face) ||
        (_curStencilCompareMask.refrence != ref) ||
        (_curStencilCompareMask.compare_mask != mask))
    {
        _curStencilCompareMask.face = face;
        _curStencilCompareMask.refrence = ref;
        _curStencilCompareMask.compare_mask = mask;
        _isStateInvalid = true;
    }
}

void CCVKCommandBuffer::draw(GFXInputAssembler* ia)
{
    if ((_type == GFXCommandBufferType::PRIMARY && _isInRenderPass) ||
        (_type == GFXCommandBufferType::SECONDARY))
    {
        if (_isStateInvalid)
        {
            BindStates();
        }

    }
    else
    {
        CC_LOG_ERROR("Command 'draw' must be recorded inside a render pass.");
    }
}

void CCVKCommandBuffer::updateBuffer(GFXBuffer* buff, void* data, uint size, uint offset)
{
    if ((_type == GFXCommandBufferType::PRIMARY && _isInRenderPass) ||
        (_type == GFXCommandBufferType::SECONDARY))
    {
    }
    else
    {
        CC_LOG_ERROR("Command 'updateBuffer' must be recorded inside a render pass.");
    }
}

void CCVKCommandBuffer::copyBufferToTexture(GFXBuffer* src, GFXTexture* dst, GFXTextureLayout layout, const GFXBufferTextureCopyList& regions)
{
    if ((_type == GFXCommandBufferType::PRIMARY && _isInRenderPass) ||
        (_type == GFXCommandBufferType::SECONDARY))
    {
    }
    else
    {
        CC_LOG_ERROR("Command 'copyBufferToTexture' must be recorded inside a render pass.");
    }
}

void CCVKCommandBuffer::execute(const std::vector<GFXCommandBuffer*>& cmd_buffs, uint32_t count)
{
    for (uint i = 0; i < count; ++i)
    {
        CCVKCommandBuffer* cmd_buff = (CCVKCommandBuffer*)cmd_buffs[i];

        _numDrawCalls += cmd_buff->getNumDrawCalls();
        _numInstances += cmd_buff->getNumInstances();
        _numTriangles += cmd_buff->getNumTris();
    }
}

void CCVKCommandBuffer::BindStates()
{
    _isStateInvalid = false;
}

NS_CC_END
