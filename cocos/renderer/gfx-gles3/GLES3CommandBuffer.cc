#include "GLES3Std.h"
#include "GLES3CommandBuffer.h"
#include "GLES3CommandAllocator.h"
#include "GLES3Framebuffer.h"
#include "GLES3PipelineState.h"
#include "GLES3BindingLayout.h"
#include "GLES3InputAssembler.h"
#include "GLES3Buffer.h"
#include "GLES3Texture.h"

NS_CC_BEGIN

GLES3CommandBuffer::GLES3CommandBuffer(GFXDevice* device)
    : GFXCommandBuffer(device) {
}

GLES3CommandBuffer::~GLES3CommandBuffer() {
}

bool GLES3CommandBuffer::initialize(const GFXCommandBufferInfo& info) {
  
  if (!info.allocator) {
    return false;
  }
  
  _allocator = info.allocator;
  _gles3Allocator = (GLES3CommandAllocator*)info.allocator;
  _type = info.type;

  _cmdPackage = CC_NEW(GLES3CmdPackage);
  
  return true;
}

void GLES3CommandBuffer::destroy() {
  if (_gles3Allocator) {
    _gles3Allocator->clearCmds(_cmdPackage);
    _gles3Allocator = nullptr;
  }
  _allocator = nullptr;

  CC_SAFE_DELETE(_cmdPackage);
}

void GLES3CommandBuffer::begin() {
  _gles3Allocator->clearCmds(_cmdPackage);
  _curGPUPipelineState = nullptr;
  _curGPUBlendLayout = nullptr;
  _curGPUInputAssember = nullptr;
  _numDrawCalls = 0;
  _numTriangles = 0;
}

void GLES3CommandBuffer::end() {
  if (_isStateInvalid) {
    BindStates();
  }
  _isInRenderPass = false;
}

void GLES3CommandBuffer::beginRenderPass(GFXFramebuffer* fbo, const GFXRect& render_area, GFXClearFlags clear_flags, GFXColor* colors, uint count, float depth, int stencil) {
  _isInRenderPass = true;
  
  GLES3CmdBeginRenderPass* cmd = _gles3Allocator->beginRenderPassCmdPool.alloc();
  cmd->gpu_fbo = ((GLES3Framebuffer*)fbo)->gpuFBO();
  cmd->render_area = render_area;
  cmd->clear_flags = clear_flags;
  cmd->num_clear_colors = count;
  for (uint i = 0; i < count; ++i) {
    cmd->clear_colors[i] = colors[i];
  }
  cmd->clear_depth = depth;
  cmd->clear_stencil = stencil;
    _curViewport.left = render_area.x;
    _curViewport.top = render_area.y;
    _curViewport.width = render_area.width;
    _curViewport.height = render_area.height;
  _cmdPackage->begin_render_pass_cmds.push(cmd);
  _cmdPackage->cmd_types.push(GFXCmdType::BEGIN_RENDER_PASS);
}

void GLES3CommandBuffer::endRenderPass() {
  _isInRenderPass = false;
  _cmdPackage->cmd_types.push(GFXCmdType::END_RENDER_PASS);
}

void GLES3CommandBuffer::bindPipelineState(GFXPipelineState* pso) {
  _curGPUPipelineState = ((GLES3PipelineState*)pso)->gpuPipelineState();
  _isStateInvalid = true;
}


void GLES3CommandBuffer::bindBindingLayout(GFXBindingLayout* layout) {
  _curGPUBlendLayout = ((GLES3BindingLayout*)layout)->gpuBindingLayout();
  _isStateInvalid = true;
}

void GLES3CommandBuffer::bindInputAssembler(GFXInputAssembler* ia) {
  _curGPUInputAssember = ((GLES3InputAssembler*)ia)->gpuInputAssembler();
  _isStateInvalid = true;
}

void GLES3CommandBuffer::setViewport(const GFXViewport& vp) {
  
  if ((_curViewport.left != vp.left) ||
      (_curViewport.top != vp.top) ||
      (_curViewport.width != vp.width) ||
      (_curViewport.height != vp.height) ||
      math::IsNotEqualF(_curViewport.minDepth, vp.minDepth) ||
      math::IsNotEqualF(_curViewport.maxDepth, vp.maxDepth)) {
    _curViewport = vp;
    _isStateInvalid = true;
  }
}

void GLES3CommandBuffer::setScissor(const GFXRect& rect) {
  if ((_curScissor.x != rect.x) ||
      (_curScissor.y != rect.y) ||
      (_curScissor.width != rect.width) ||
      (_curScissor.height != rect.height)) {
    _curScissor = rect;
    _isStateInvalid = true;
  }
}

void GLES3CommandBuffer::setLineWidth(const float width) {
  if (math::IsNotEqualF(_curLineWidth, width)) {
    _curLineWidth = width;
    _isStateInvalid = true;
  }
}

void GLES3CommandBuffer::setDepthBias(float constant, float clamp, float slope) {
  if (math::IsNotEqualF(_curDepthBias.constant, constant) ||
      math::IsNotEqualF(_curDepthBias.clamp, clamp) ||
      math::IsNotEqualF(_curDepthBias.slope, slope)) {
    _curDepthBias.constant = constant;
    _curDepthBias.clamp = clamp;
    _curDepthBias.slope = slope;
    _isStateInvalid = true;
  }
}

void GLES3CommandBuffer::setBlendConstants(const GFXColor& constants) {
  if (math::IsNotEqualF(_curBlendConstants.r, constants.r) ||
      math::IsNotEqualF(_curBlendConstants.g, constants.g) ||
      math::IsNotEqualF(_curBlendConstants.b, constants.b) ||
      math::IsNotEqualF(_curBlendConstants.a, constants.a)) {
    _curBlendConstants.r = constants.r;
    _curBlendConstants.g = constants.g;
    _curBlendConstants.b = constants.b;
    _curBlendConstants.a = constants.a;
    _isStateInvalid = true;
  }
}

void GLES3CommandBuffer::setDepthBound(float min_bounds, float max_bounds) {
  if (math::IsNotEqualF(_curDepthBounds.min_bounds, min_bounds) ||
      math::IsNotEqualF(_curDepthBounds.max_bounds, max_bounds)) {
    _curDepthBounds.min_bounds = min_bounds;
    _curDepthBounds.max_bounds = max_bounds;
    _isStateInvalid = true;
  }
}

void GLES3CommandBuffer::setStencilWriteMask(GFXStencilFace face, uint mask) {
  if ((_curStencilWriteMask.face != face) ||
      (_curStencilWriteMask.write_mask != mask)) {
    _curStencilWriteMask.face = face;
    _curStencilWriteMask.write_mask = mask;
    _isStateInvalid = true;
  }
}

void GLES3CommandBuffer::setStencilCompareMask(GFXStencilFace face, int ref, uint mask) {
  if ((_curStencilCompareMask.face != face) ||
      (_curStencilCompareMask.refrence != ref) ||
      (_curStencilCompareMask.compare_mask != mask)) {
    _curStencilCompareMask.face = face;
    _curStencilCompareMask.refrence = ref;
    _curStencilCompareMask.compare_mask = mask;
    _isStateInvalid = true;
  }
}

void GLES3CommandBuffer::draw(GFXInputAssembler* ia) {
  if ((_type == GFXCommandBufferType::PRIMARY && _isInRenderPass) ||
      (_type == GFXCommandBufferType::SECONDARY)) {
    if (_isStateInvalid) {
      BindStates();
    }
    
    GLES3CmdDraw* cmd = _gles3Allocator->drawCmdPool.alloc();
    ((GLES3InputAssembler*)ia)->ExtractCmdDraw(cmd);
    _cmdPackage->draw_cmds.push(cmd);
    _cmdPackage->cmd_types.push(GFXCmdType::DRAW);
    
    ++_numDrawCalls;
    if(_curGPUPipelineState) {
      switch (_curGPUPipelineState->glPrimitive) {
        case GL_TRIANGLES: {
          _numTriangles += ia->indexCount() / 3 * std::max(ia->instanceCount(), 1U);
          break;
        }
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLE_FAN: {
          _numTriangles += (ia->indexCount() - 2) * std::max(ia->instanceCount(), 1U);
          break;
        }
        default:
          break;
      }
    }
  } else {
    CC_LOG_ERROR("Command 'draw' must be recorded inside a render pass.");
  }
}

void GLES3CommandBuffer::updateBuffer(GFXBuffer* buff, void* data, uint size, uint offset) {
  if ((_type == GFXCommandBufferType::PRIMARY && _isInRenderPass) ||
      (_type == GFXCommandBufferType::SECONDARY)) {
    GLES3GPUBuffer* gpuBuffer = ((GLES3Buffer*)buff)->gpuBuffer();
    if (gpuBuffer) {
      GLES3CmdUpdateBuffer* cmd = _gles3Allocator->updateBufferCmdPool.alloc();
      cmd->gpuBuffer = gpuBuffer;
      cmd->buffer = (uint8_t*)data;
      cmd->size = size;
      cmd->offset = offset;
      
      _cmdPackage->update_buffer_cmds.push(cmd);
      _cmdPackage->cmd_types.push(GFXCmdType::UPDATE_BUFFER);
    }
  } else {
    CC_LOG_ERROR("Command 'updateBuffer' must be recorded inside a render pass.");
  }
}

void GLES3CommandBuffer::copyBufferToTexture(GFXBuffer* src, GFXTexture* dst, GFXTextureLayout layout, GFXBufferTextureCopy* regions, uint count) {
  if ((_type == GFXCommandBufferType::PRIMARY && _isInRenderPass) ||
      (_type == GFXCommandBufferType::SECONDARY)) {
    GLES3GPUBuffer* gpuBuffer = ((GLES3Buffer*)src)->gpuBuffer();
    GLES3GPUTexture* gpuTexture = ((GLES3Texture*)dst)->gpuTexture();
    if (gpuBuffer && gpuTexture) {
      GLES3CmdCopyBufferToTexture* cmd = _gles3Allocator->copyBufferToTextureCmdPool.alloc();
      cmd->gpuBuffer = gpuBuffer;
      cmd->gpuTexture = gpuTexture;
      cmd->dst_layout = layout;
      cmd->regions.resize(count);
      for (uint i = 0; i < count; ++i) {
        cmd->regions[i] = regions[i];
      }
      
      _cmdPackage->copy_buffer_to_texture_cmds.push(cmd);
      _cmdPackage->cmd_types.push(GFXCmdType::COPY_BUFFER_TO_TEXTURE);
    }
  } else {
    CC_LOG_ERROR("Command 'copyBufferToTexture' must be recorded inside a render pass.");
  }
}

void GLES3CommandBuffer::execute(GFXCommandBuffer** cmd_buffs, uint count) {
  for (uint i = 0; i < count; ++i) {
    GLES3CommandBuffer* cmd_buff = (GLES3CommandBuffer*)cmd_buffs[i];
    
    for (uint j = 0; j < cmd_buff->_cmdPackage->begin_render_pass_cmds.size(); ++j) {
      GLES3CmdBeginRenderPass* cmd = cmd_buff->_cmdPackage->begin_render_pass_cmds[j];
      ++cmd->ref_count;
      cmd_buff->_cmdPackage->begin_render_pass_cmds.push(cmd);
    }
    for (uint j = 0; j < cmd_buff->_cmdPackage->bind_states_cmds.size(); ++j) {
      GLES3CmdBindStates* cmd = cmd_buff->_cmdPackage->bind_states_cmds[j];
      ++cmd->ref_count;
      cmd_buff->_cmdPackage->bind_states_cmds.push(cmd);
    }
    for (uint j = 0; j < cmd_buff->_cmdPackage->draw_cmds.size(); ++j) {
      GLES3CmdDraw* cmd = cmd_buff->_cmdPackage->draw_cmds[j];
      ++cmd->ref_count;
      cmd_buff->_cmdPackage->draw_cmds.push(cmd);
    }
    for (uint j = 0; j < cmd_buff->_cmdPackage->update_buffer_cmds.size(); ++j) {
      GLES3CmdUpdateBuffer* cmd = cmd_buff->_cmdPackage->update_buffer_cmds[j];
      ++cmd->ref_count;
      cmd_buff->_cmdPackage->update_buffer_cmds.push(cmd);
    }
    for (uint j = 0; j < cmd_buff->_cmdPackage->copy_buffer_to_texture_cmds.size(); ++j) {
      GLES3CmdCopyBufferToTexture* cmd = cmd_buff->_cmdPackage->copy_buffer_to_texture_cmds[j];
      ++cmd->ref_count;
      cmd_buff->_cmdPackage->copy_buffer_to_texture_cmds.push(cmd);
    }
    _cmdPackage->cmd_types.concat(cmd_buff->_cmdPackage->cmd_types);
    
    _numDrawCalls += cmd_buff->numDrawCalls();
    _numTriangles += cmd_buff->numTris();
  }
}

void GLES3CommandBuffer::BindStates() {
  GLES3CmdBindStates* cmd = _gles3Allocator->bindStatesCmdPool.alloc();
  cmd->gpu_pso = _curGPUPipelineState;
  cmd->gpu_binding_layout = _curGPUBlendLayout;
  cmd->gpu_ia = _curGPUInputAssember;
  cmd->viewport = _curViewport;
  cmd->scissor = _curScissor;
  cmd->lineWidth = _curLineWidth;
  cmd->depthBias = _curDepthBias;
  cmd->blend_constants.r = _curBlendConstants.r;
  cmd->blend_constants.g = _curBlendConstants.g;
  cmd->blend_constants.b = _curBlendConstants.b;
  cmd->blend_constants.a = _curBlendConstants.a;
  cmd->depth_bounds = _curDepthBounds;
  cmd->stencil_write_mask = _curStencilWriteMask;
  cmd->stencil_compare_mask = _curStencilCompareMask;
  
  _cmdPackage->bind_states_cmds.push(cmd);
  _cmdPackage->cmd_types.push(GFXCmdType::BIND_STATES);
  _isStateInvalid = false;
}

NS_CC_END
