#include "VKStd.h"
#include "VKCommandBuffer.h"
#include "VKCommandAllocator.h"
#include "VKFramebuffer.h"
#include "VKPipelineState.h"
#include "VKBindingLayout.h"
#include "VKInputAssembler.h"
#include "VKDevice.h"
#include "VKBuffer.h"
#include "VKTexture.h"

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
    _vkAllocator = (CCVKCommandAllocator*)info.allocator;
    _type = info.type;

    //VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
    //switch (_type)
    //{
    //case GFXCommandBufferType::PRIMARY: level = VK_COMMAND_BUFFER_LEVEL_PRIMARY; break;
    //case GFXCommandBufferType::SECONDARY: level = VK_COMMAND_BUFFER_LEVEL_SECONDARY; break;
    //}

    //VkCommandBufferAllocateInfo allocateInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
    //allocateInfo.commandPool = _vkAllocator->getCommandPool();
    //allocateInfo.commandBufferCount = 1;
    //allocateInfo.level = level;

    //VK_CHECK(vkAllocateCommandBuffers(((CCVKDevice*)_device)->getHandle(), &allocateInfo, &_handle));

    _status = GFXStatus::SUCCESS;
    return true;
}

void CCVKCommandBuffer::destroy()
{
    //if (_vkAllocator)
    //{
    //    vkFreeCommandBuffers(((CCVKDevice*)_device)->getHandle(), _vkAllocator->getCommandPool(), 1, &_handle);
    //    _vkAllocator = nullptr;
    //}
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

    //VkCommandBufferBeginInfo beginInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
    //beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    //if (_type == GFXCommandBufferType::SECONDARY)
    //{
    //    VkCommandBufferInheritanceInfo inheritance{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO };
    //    // TODO
    //    //beginInfo.pInheritanceInfo = &inheritance;
    //}

    //VK_CHECK(vkBeginCommandBuffer(_handle, &beginInfo));
}

void CCVKCommandBuffer::end()
{
    if (_isStateInvalid)
    {
        BindStates();
    }
    _isInRenderPass = false;

    //vkEndCommandBuffer(_handle);
}

void CCVKCommandBuffer::beginRenderPass(GFXFramebuffer* fbo, const GFXRect& render_area, GFXClearFlags clear_flags, const std::vector<GFXColor>& colors, float depth, int stencil)
{
    _isInRenderPass = true;
    /*
    std::vector<SubpassInfo> subpass_infos(subpasses.size());
    auto                     subpass_info_it = subpass_infos.begin();
    for (auto &subpass : subpasses)
    {
        subpass_info_it->input_attachments = subpass->get_input_attachments();
        subpass_info_it->output_attachments = subpass->get_output_attachments();
        subpass_info_it->color_resolve_attachments = subpass->get_color_resolve_attachments();
        subpass_info_it->disable_depth_stencil_attachment = subpass->get_disable_depth_stencil_attachment();
        subpass_info_it->depth_stencil_resolve_mode = subpass->get_depth_stencil_resolve_mode();
        subpass_info_it->depth_stencil_resolve_attachment = subpass->get_depth_stencil_resolve_attachment();

        ++subpass_info_it;
    }
    current_render_pass.render_pass = &get_device().get_resource_cache().request_render_pass(render_target.get_attachments(), load_store_infos, subpass_infos);
    current_render_pass.framebuffer = &get_device().get_resource_cache().request_framebuffer(render_target, *current_render_pass.render_pass);

    // Begin render pass
    VkRenderPassBeginInfo begin_info{ VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO };
    begin_info.renderPass = current_render_pass.render_pass->get_handle();
    begin_info.framebuffer = current_render_pass.framebuffer->get_handle();
    begin_info.renderArea.extent = render_target.get_extent();
    begin_info.clearValueCount = to_u32(clear_values.size());
    begin_info.pClearValues = clear_values.data();

    const auto &framebuffer_extent = current_render_pass.framebuffer->get_extent();

    // Test the requested render area to confirm that it is optimal and could not cause a performance reduction
    if (!is_render_size_optimal(framebuffer_extent, begin_info.renderArea))
    {
        // Only prints the warning if the framebuffer or render area are different since the last time the render size was not optimal
        if (framebuffer_extent.width != last_framebuffer_extent.width || framebuffer_extent.height != last_framebuffer_extent.height ||
            begin_info.renderArea.extent.width != last_render_area_extent.width || begin_info.renderArea.extent.height != last_render_area_extent.height)
        {
            LOGW("Render target extent is not an optimal size, this may result in reduced performance.");
        }

        last_framebuffer_extent = current_render_pass.framebuffer->get_extent();
        last_render_area_extent = begin_info.renderArea.extent;
    }

    vkCmdBeginRenderPass(get_handle(), &begin_info, contents);

    // Update blend state attachments for first subpass
    auto blend_state = pipeline_state.get_color_blend_state();
    blend_state.attachments.resize(current_render_pass.render_pass->get_color_output_count(pipeline_state.get_subpass_index()));
    pipeline_state.set_color_blend_state(blend_state);
    */

}

void CCVKCommandBuffer::endRenderPass()
{
    _isInRenderPass = false;
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
