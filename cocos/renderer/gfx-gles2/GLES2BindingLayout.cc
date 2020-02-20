#include "GLES2Std.h"
#include "GLES2BindingLayout.h"
#include "GLES2Commands.h"
#include "GLES2Buffer.h"
#include "GLES2TextureView.h"
#include "GLES2Sampler.h"

NS_CC_BEGIN

GLES2BindingLayout::GLES2BindingLayout(GFXDevice* device)
    : GFXBindingLayout(device),
      gpu_binding_layout_(nullptr) {
}

GLES2BindingLayout::~GLES2BindingLayout() {
}

bool GLES2BindingLayout::initialize(const GFXBindingLayoutInfo &info) {
  
  if (info.bindings.size()) {
    _bindingUnits.resize(info.bindings.size());
    for (size_t i = 0; i < _bindingUnits.size(); ++i) {
      GFXBindingUnit& bindingUnit = _bindingUnits[i];
      const GFXBinding& binding = info.bindings[i];
      bindingUnit.binding = binding.binding;
      bindingUnit.type = binding.type;
      bindingUnit.name = binding.name;
    }
  }
  
  gpu_binding_layout_ = CC_NEW(GLES2GPUBindingLayout);
  gpu_binding_layout_->gpu_bindings.resize(_bindingUnits.size());
  for (size_t i = 0; i < gpu_binding_layout_->gpu_bindings.size(); ++i) {
    GLES2GPUBinding& gpu_binding = gpu_binding_layout_->gpu_bindings[i];
    const GFXBindingUnit& bindingUnit = _bindingUnits[i];
    gpu_binding.binding = bindingUnit.binding;
    gpu_binding.type = bindingUnit.type;
    gpu_binding.name = bindingUnit.name;
  }
  
  return true;
}

void GLES2BindingLayout::destroy() {
  if (gpu_binding_layout_) {
    CC_DELETE(gpu_binding_layout_);
    gpu_binding_layout_ = nullptr;
  }
}

void GLES2BindingLayout::update() {
  if (_isDirty && gpu_binding_layout_) {
    for (size_t i = 0; i < _bindingUnits.size(); ++i) {
      GFXBindingUnit& bindingUnit = _bindingUnits[i];
      switch (bindingUnit.type) {
        case GFXBindingType::UNIFORM_BUFFER: {
          if (bindingUnit.buffer) {
            gpu_binding_layout_->gpu_bindings[i].gpu_buffer = ((GLES2Buffer*)bindingUnit.buffer)->gpu_buffer();
          }
          break;
        }
        case GFXBindingType::SAMPLER: {
          if (bindingUnit.texView) {
            gpu_binding_layout_->gpu_bindings[i].gpu_tex_view = ((GLES2TextureView*)bindingUnit.texView)->gpu_tex_view();
          }
          if (bindingUnit.sampler) {
            gpu_binding_layout_->gpu_bindings[i].gpu_sampler = ((GLES2Sampler*)bindingUnit.sampler)->gpu_sampler();
          }
          break;
        }
        default:;
      }
    }
    _isDirty = false;
  }
}

NS_CC_END
