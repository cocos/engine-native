#include "CCVKStd.h"
#include "CCVKCommandBuffer.h"
#include "CCVKCommandAllocator.h"
#include "CCVKFramebuffer.h"
#include "CCVKPipelineState.h"
#include "CCVKBindingLayout.h"
#include "CCVKInputAssembler.h"
#include "CCVKBuffer.h"
#include "CCVKTexture.h"

NS_CC_BEGIN

CCVKCommandBuffer::CCVKCommandBuffer(GFXDevice* device)
    : GFXCommandBuffer(device) {
}

CCVKCommandBuffer::~CCVKCommandBuffer() {
}

bool CCVKCommandBuffer::initialize(const GFXCommandBufferInfo& info) {
  
  if (!info.allocator) {
    return false;
  }
  
  _allocator = info.allocator;
  _CCVKAllocator = (CCVKCommandAllocator*)info.allocator;
  _type = info.type;

  _cmdPackage = CC_NEW(CCVKCmdPackage);
    _status = GFXStatus::SUCCESS;
  
  return true;
}

void CCVKCommandBuffer::destroy() {
  if (_CCVKAllocator) {
    _CCVKAllocator->clearCmds(_cmdPackage);
    _CCVKAllocator = nullptr;
  }
  _allocator = nullptr;
    _status = GFXStatus::UNREADY;

  CC_SAFE_DELETE(_cmdPackage);
}

void CCVKCommandBuffer::begin() {
  _CCVKAllocator->clearCmds(_cmdPackage);
  _curGPUPipelineState = nullptr;
  _curGPUBlendLayout = nullptr;
  _curGPUInputAssember = nullptr;
  _numDrawCalls = 0;
  _numInstances = 0;
  _numTriangles = 0;
}

void CCVKCommandBuffer::end() {
  if (_isStateInvalid) {
    BindStates();
  }
  _isInRenderPass = false;
}

void CCVKCommandBuffer::beginRenderPass(GFXFramebuffer* fbo, const GFXRect& render_area, GFXClearFlags clear_flags, const std::vector<GFXColor>& colors, float depth, int stencil) {
  _isInRenderPass = true;
  
  CCVKCmdBeginRenderPass* cmd = _CCVKAllocator->beginRenderPassCmdPool.alloc();
  cmd->gpuFBO = ((CCVKFramebuffer*)fbo)->gpuFBO();
  cmd->render_area = render_area;
  cmd->clear_flags = clear_flags;
  cmd->num_clear_colors = (uint32_t)colors.size();
  for (uint i = 0; i < colors.size(); ++i) {
    cmd->clear_colors[i] = colors[i];
  }
  cmd->clear_depth = depth;
  cmd->clear_stencil = stencil;
  _cmdPackage->beginRenderPassCmds.push(cmd);
  _cmdPackage->cmds.push(GFXCmdType::BEGIN_RENDER_PASS);
}

void CCVKCommandBuffer::endRenderPass() {
  _isInRenderPass = false;
  _cmdPackage->cmds.push(GFXCmdType::END_RENDER_PASS);
}

void CCVKCommandBuffer::bindPipelineState(GFXPipelineState* pso) {
  _curGPUPipelineState = ((CCVKPipelineState*)pso)->gpuPipelineState();
  _isStateInvalid = true;
}


void CCVKCommandBuffer::bindBindingLayout(GFXBindingLayout* layout) {
  _curGPUBlendLayout = ((CCVKBindingLayout*)layout)->gpuBindingLayout();
  _isStateInvalid = true;
}

void CCVKCommandBuffer::bindInputAssembler(GFXInputAssembler* ia) {
  _curGPUInputAssember = ((CCVKInputAssembler*)ia)->gpuInputAssembler();
  _isStateInvalid = true;
}

void CCVKCommandBuffer::setViewport(const GFXViewport& vp) {
  
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

void CCVKCommandBuffer::setScissor(const GFXRect& rect) {
  if ((_curScissor.x != rect.x) ||
      (_curScissor.y != rect.y) ||
      (_curScissor.width != rect.width) ||
      (_curScissor.height != rect.height)) {
    _curScissor = rect;
    _isStateInvalid = true;
  }
}

void CCVKCommandBuffer::setLineWidth(const float width) {
  if (math::IsNotEqualF(_curLineWidth, width)) {
    _curLineWidth = width;
    _isStateInvalid = true;
  }
}

void CCVKCommandBuffer::setDepthBias(float constant, float clamp, float slope) {
  if (math::IsNotEqualF(_curDepthBias.constant, constant) ||
      math::IsNotEqualF(_curDepthBias.clamp, clamp) ||
      math::IsNotEqualF(_curDepthBias.slope, slope)) {
    _curDepthBias.constant = constant;
    _curDepthBias.clamp = clamp;
    _curDepthBias.slope = slope;
    _isStateInvalid = true;
  }
}

void CCVKCommandBuffer::setBlendConstants(const GFXColor& constants) {
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

void CCVKCommandBuffer::setDepthBound(float min_bounds, float max_bounds) {
  if (math::IsNotEqualF(_curDepthBounds.min_bounds, min_bounds) ||
      math::IsNotEqualF(_curDepthBounds.max_bounds, max_bounds)) {
    _curDepthBounds.min_bounds = min_bounds;
    _curDepthBounds.max_bounds = max_bounds;
    _isStateInvalid = true;
  }
}

void CCVKCommandBuffer::setStencilWriteMask(GFXStencilFace face, uint mask) {
  if ((_curStencilWriteMask.face != face) ||
      (_curStencilWriteMask.write_mask != mask)) {
    _curStencilWriteMask.face = face;
    _curStencilWriteMask.write_mask = mask;
    _isStateInvalid = true;
  }
}

void CCVKCommandBuffer::setStencilCompareMask(GFXStencilFace face, int ref, uint mask) {
  if ((_curStencilCompareMask.face != face) ||
      (_curStencilCompareMask.refrence != ref) ||
      (_curStencilCompareMask.compare_mask != mask)) {
    _curStencilCompareMask.face = face;
    _curStencilCompareMask.refrence = ref;
    _curStencilCompareMask.compare_mask = mask;
    _isStateInvalid = true;
  }
}

void CCVKCommandBuffer::draw(GFXInputAssembler* ia) {
  if ((_type == GFXCommandBufferType::PRIMARY && _isInRenderPass) ||
      (_type == GFXCommandBufferType::SECONDARY)) {
    if (_isStateInvalid) {
      BindStates();
    }
    
    CCVKCmdDraw* cmd = _CCVKAllocator->drawCmdPool.alloc();
    ((CCVKInputAssembler*)ia)->ExtractCmdDraw(cmd);
    _cmdPackage->drawCmds.push(cmd);
    _cmdPackage->cmds.push(GFXCmdType::DRAW);
    
    ++_numDrawCalls;
    _numInstances += ia->getInstanceCount();
    if(_curGPUPipelineState) {
      switch (_curGPUPipelineState->glPrimitive) {
        case GL_TRIANGLES: {
          _numTriangles += ia->getIndexCount() / 3 * std::max(ia->getInstanceCount(), 1U);
          break;
        }
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLE_FAN: {
          _numTriangles += (ia->getIndexCount() - 2) * std::max(ia->getInstanceCount(), 1U);
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

void CCVKCommandBuffer::updateBuffer(GFXBuffer* buff, void* data, uint size, uint offset) {
  if ((_type == GFXCommandBufferType::PRIMARY && _isInRenderPass) ||
      (_type == GFXCommandBufferType::SECONDARY)) {
    CCVKGPUBuffer* gpuBuffer = ((CCVKBuffer*)buff)->gpuBuffer();
    if (gpuBuffer) {
      CCVKCmdUpdateBuffer* cmd = _CCVKAllocator->updateBufferCmdPool.alloc();
      cmd->gpuBuffer = gpuBuffer;
      cmd->buffer = (uint8_t*)data;
      cmd->size = size;
      cmd->offset = offset;
      
      _cmdPackage->updateBufferCmds.push(cmd);
      _cmdPackage->cmds.push(GFXCmdType::UPDATE_BUFFER);
    }
  } else {
    CC_LOG_ERROR("Command 'updateBuffer' must be recorded inside a render pass.");
  }
}

void CCVKCommandBuffer::copyBufferToTexture(GFXBuffer* src, GFXTexture* dst, GFXTextureLayout layout, const GFXBufferTextureCopyList& regions) {
  if ((_type == GFXCommandBufferType::PRIMARY && _isInRenderPass) ||
      (_type == GFXCommandBufferType::SECONDARY)) {
    CCVKGPUBuffer* gpuBuffer = ((CCVKBuffer*)src)->gpuBuffer();
    CCVKGPUTexture* gpuTexture = ((CCVKTexture*)dst)->gpuTexture();
    if (gpuBuffer && gpuTexture) {
      CCVKCmdCopyBufferToTexture* cmd = _CCVKAllocator->copyBufferToTextureCmdPool.alloc();
      cmd->gpuBuffer = gpuBuffer;
      cmd->gpuTexture = gpuTexture;
      cmd->dst_layout = layout;
      cmd->regions.resize(regions.size());
      for (uint i = 0; i < static_cast<uint>(regions.size()); ++i) {
        cmd->regions[i] = regions[i];
      }
      
      _cmdPackage->copyBufferToTextureCmds.push(cmd);
      _cmdPackage->cmds.push(GFXCmdType::COPY_BUFFER_TO_TEXTURE);
    }
  } else {
    CC_LOG_ERROR("Command 'copyBufferToTexture' must be recorded inside a render pass.");
  }
}

void CCVKCommandBuffer::execute(const std::vector<GFXCommandBuffer*>& cmd_buffs, uint32_t count) {
  for (uint i = 0; i < count; ++i) {
    CCVKCommandBuffer* cmd_buff = (CCVKCommandBuffer*)cmd_buffs[i];
    
    for (uint j = 0; j < cmd_buff->_cmdPackage->beginRenderPassCmds.size(); ++j) {
      CCVKCmdBeginRenderPass* cmd = cmd_buff->_cmdPackage->beginRenderPassCmds[j];
      ++cmd->ref_count;
      _cmdPackage->beginRenderPassCmds.push(cmd);
    }
    for (uint j = 0; j < cmd_buff->_cmdPackage->bindStatesCmds.size(); ++j) {
      CCVKCmdBindStates* cmd = cmd_buff->_cmdPackage->bindStatesCmds[j];
      ++cmd->ref_count;
      _cmdPackage->bindStatesCmds.push(cmd);
    }
    for (uint j = 0; j < cmd_buff->_cmdPackage->drawCmds.size(); ++j) {
      CCVKCmdDraw* cmd = cmd_buff->_cmdPackage->drawCmds[j];
      ++cmd->ref_count;
      _cmdPackage->drawCmds.push(cmd);
    }
    for (uint j = 0; j < cmd_buff->_cmdPackage->updateBufferCmds.size(); ++j) {
      CCVKCmdUpdateBuffer* cmd = cmd_buff->_cmdPackage->updateBufferCmds[j];
      ++cmd->ref_count;
      _cmdPackage->updateBufferCmds.push(cmd);
    }
    for (uint j = 0; j < cmd_buff->_cmdPackage->copyBufferToTextureCmds.size(); ++j) {
      CCVKCmdCopyBufferToTexture* cmd = cmd_buff->_cmdPackage->copyBufferToTextureCmds[j];
      ++cmd->ref_count;
      _cmdPackage->copyBufferToTextureCmds.push(cmd);
    }
    _cmdPackage->cmds.concat(cmd_buff->_cmdPackage->cmds);
    
    _numDrawCalls += cmd_buff->getNumDrawCalls();
    _numInstances += cmd_buff->getNumInstances();
    _numTriangles += cmd_buff->getNumTris();
  }
}

void CCVKCommandBuffer::BindStates() {
  CCVKCmdBindStates* cmd = _CCVKAllocator->bindStatesCmdPool.alloc();
  cmd->gpuPipelineState = _curGPUPipelineState;
  cmd->gpuBindingLayout = _curGPUBlendLayout;
  cmd->gpuInputAssembler = _curGPUInputAssember;
  cmd->viewport = _curViewport;
  cmd->scissor = _curScissor;
  cmd->lineWidth = _curLineWidth;
  cmd->depthBias = _curDepthBias;
  cmd->blendConstants.r = _curBlendConstants.r;
  cmd->blendConstants.g = _curBlendConstants.g;
  cmd->blendConstants.b = _curBlendConstants.b;
  cmd->blendConstants.a = _curBlendConstants.a;
  cmd->depthBounds = _curDepthBounds;
  cmd->stencilWriteMask = _curStencilWriteMask;
  cmd->stencilCompareMask = _curStencilCompareMask;
  
  _cmdPackage->bindStatesCmds.push(cmd);
  _cmdPackage->cmds.push(GFXCmdType::BIND_STATES);
  _isStateInvalid = false;
}

NS_CC_END
