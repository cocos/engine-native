#include "VKStd.h"
#include "VKPipelineState.h"
#include "VKCommands.h"
#include "VKShader.h"
#include "VKRenderPass.h"
#include "VKPipelineLayout.h"

NS_CC_BEGIN

//const GLenum CCVKPrimitives []  = {
//  GL_POINTS,
//  GL_LINES,
//  GL_LINE_STRIP,
//  GL_LINE_LOOP,
//  GL_NONE,
//  GL_NONE,
//  GL_NONE,
//  GL_TRIANGLES,
//  GL_TRIANGLE_STRIP,
//  GL_TRIANGLE_FAN,
//  GL_NONE,
//  GL_NONE,
//  GL_NONE,
//  GL_NONE,
//};

CCVKPipelineState::CCVKPipelineState(GFXDevice* device)
    : GFXPipelineState(device) {
}

CCVKPipelineState::~CCVKPipelineState() {
}

bool CCVKPipelineState::initialize(const GFXPipelineStateInfo &info) {
  
  _primitive = info.primitive;
  _shader = info.shader;
  _inputState = info.inputState;
  _rasterizerState = info.rasterizerState;
  _depthStencilState = info.depthStencilState;
  _blendState = info.blendState;
  _dynamicStates = info.dynamicStates;
  _layout = info.layout;
  _renderPass = info.renderPass;
  
  _gpuPipelineState = CC_NEW(CCVKGPUPipelineState);
  //_gpuPipelineState->glPrimitive = CCVKPrimitives[(int)_primitive];
  _gpuPipelineState->gpuShader = ((CCVKShader*)_shader)->gpuShader();
  _gpuPipelineState->rs = _rasterizerState;
  _gpuPipelineState->dss = _depthStencilState;
  _gpuPipelineState->bs = _blendState;
  _gpuPipelineState->dynamicStates = _dynamicStates;
  _gpuPipelineState->gpuLayout = ((CCVKPipelineLayout*)_layout)->gpuPipelineLayout();
  _gpuPipelineState->gpuRenderPass = ((CCVKRenderPass*)_renderPass)->gpuRenderPass();
    
    _status = GFXStatus::SUCCESS;
  
  return true;
}

void CCVKPipelineState::destroy() {
  if (_gpuPipelineState) {
    CC_DELETE(_gpuPipelineState);
    _gpuPipelineState = nullptr;
  }
    _status = GFXStatus::UNREADY;
}

NS_CC_END
