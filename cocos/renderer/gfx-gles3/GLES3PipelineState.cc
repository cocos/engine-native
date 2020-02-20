#include "GLES3Std.h"
#include "GLES3PipelineState.h"
#include "GLES3Commands.h"
#include "GLES3Shader.h"
#include "GLES3RenderPass.h"
#include "GLES3PipelineLayout.h"

NS_CC_BEGIN

const GLenum GLES3Primitives []  = {
  GL_POINTS,
  GL_LINES,
  GL_LINE_STRIP,
  GL_LINE_LOOP,
  GL_NONE,
  GL_NONE,
  GL_NONE,
  GL_TRIANGLES,
  GL_TRIANGLE_STRIP,
  GL_TRIANGLE_FAN,
  GL_NONE,
  GL_NONE,
  GL_NONE,
  GL_NONE,
};

GLES3PipelineState::GLES3PipelineState(GFXDevice* device)
    : GFXPipelineState(device),
      gpu_pso_(nullptr) {
}

GLES3PipelineState::~GLES3PipelineState() {
}

bool GLES3PipelineState::initialize(const GFXPipelineStateInfo &info) {
  
  _primitive = info.primitive;
  _shader = info.shader;
  _inputState = info.inputState;
  _rasterizerState = info.rasterizerState;
  _depthStencilState = info.depthStencilState;
  _blendState = info.blendState;
  _dynamicStates = info.dynamicStates;
  _layout = info.layout;
  _renderPass = info.renderPass;
  
  gpu_pso_ = CC_NEW(GLES3GPUPipelineState);
  gpu_pso_->gl_primitive = GLES3Primitives[(int)_primitive];
  gpu_pso_->gpu_shader = ((GLES3Shader*)_shader)->gpu_shader();
  gpu_pso_->rs = _rasterizerState;
  gpu_pso_->dss = _depthStencilState;
  gpu_pso_->bs = _blendState;
  gpu_pso_->dynamicStates = _dynamicStates;
  gpu_pso_->gpu_layout = ((GLES3PipelineLayout*)_layout)->gpu_pipeline_layout();
  gpu_pso_->gpu_render_pass = ((GLES3RenderPass*)_renderPass)->gpu_render_pass();
  
  return true;
}

void GLES3PipelineState::destroy() {
  if (gpu_pso_) {
    CC_DELETE(gpu_pso_);
    gpu_pso_ = nullptr;
  }
}

NS_CC_END
