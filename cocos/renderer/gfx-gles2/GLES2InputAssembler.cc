#include "GLES2Std.h"
#include "GLES2InputAssembler.h"
#include "GLES2Commands.h"
#include "GLES2Buffer.h"

NS_CC_BEGIN

GLES2InputAssembler::GLES2InputAssembler(GFXDevice* device)
    : GFXInputAssembler(device),
      gpu_input_assembler_(nullptr) {
}

GLES2InputAssembler::~GLES2InputAssembler() {
}

bool GLES2InputAssembler::initialize(const GFXInputAssemblerInfo &info) {
  
  _attributes = info.attributes;
  _vertexBuffers = info.vertexBuffers;
  _indexBuffer = info.indexBuffer;
  _indirectBuffer = info.indirectBuffer;
  
  if (_indexBuffer) {
    _indexCount = _indexBuffer->count();
  } else if (_vertexBuffers.size()) {
    _vertexCount = _vertexBuffers[0]->count();
  }
  
  gpu_input_assembler_ = CC_NEW(GLES2GPUInputAssembler);
  gpu_input_assembler_->attribs = _attributes;
  gpu_input_assembler_->gpu_vertex_buffers.resize(_vertexBuffers.size());
  for (size_t i = 0; i < gpu_input_assembler_->gpu_vertex_buffers.size(); ++i) {
    GLES2Buffer* vb = (GLES2Buffer*)_vertexBuffers[i];
    gpu_input_assembler_->gpu_vertex_buffers[i] = vb->gpu_buffer();
  }
    if(info.indexBuffer)
        gpu_input_assembler_->gpu_index_buffer = static_cast<GLES2Buffer*>(info.indexBuffer)->gpu_buffer();
  
  GLES2CmdFuncCreateInputAssembler((GLES2Device*)_device, gpu_input_assembler_);
  
  return true;
}

void GLES2InputAssembler::destroy() {
  if (gpu_input_assembler_) {
    GLES2CmdFuncDestroyInputAssembler((GLES2Device*)_device, gpu_input_assembler_);
    CC_DELETE(gpu_input_assembler_);
    gpu_input_assembler_ = nullptr;
  }
}

void GLES2InputAssembler::ExtractCmdDraw(GLES2CmdDraw* cmd) {
  cmd->draw_info.vertexCount = _vertexCount;
  cmd->draw_info.firstVertex = _firstVertex;
  cmd->draw_info.indexCount = _indexCount;
  cmd->draw_info.firstIndex = _firstIndex;
  cmd->draw_info.vertexOffset = _vertexOffset;
  cmd->draw_info.instanceCount = _instanceCount;
  cmd->draw_info.firstInstance = _firstInstance;
}

NS_CC_END
