#include "GLES3Std.h"
#include "GLES3BindingLayout.h"
#include "GLES3Commands.h"
#include "GLES3Buffer.h"
#include "GLES3TextureView.h"
#include "GLES3Sampler.h"

NS_CC_BEGIN

GLES3BindingLayout::GLES3BindingLayout(GFXDevice* device)
    : GFXBindingLayout(device),
      gpu_binding_layout_(nullptr) {
}

GLES3BindingLayout::~GLES3BindingLayout() {
}

bool GLES3BindingLayout::initialize(const GFXBindingLayoutInfo &info) {
  
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
  
  gpu_binding_layout_ = CC_NEW(GLES3GPUBindingLayout);
  gpu_binding_layout_->gpu_bindings.resize(_bindingUnits.size());
  for (size_t i = 0; i < gpu_binding_layout_->gpu_bindings.size(); ++i) {
    GLES3GPUBinding& gpu_binding = gpu_binding_layout_->gpu_bindings[i];
    const GFXBindingUnit& bindingUnit = _bindingUnits[i];
    gpu_binding.binding = bindingUnit.binding;
    gpu_binding.type = bindingUnit.type;
    gpu_binding.name = bindingUnit.name;
  }
  
  return true;
}

void GLES3BindingLayout::destroy() {
  if (gpu_binding_layout_) {
    CC_DELETE(gpu_binding_layout_);
    gpu_binding_layout_ = nullptr;
  }
}

void GLES3BindingLayout::update() {
  if (_isDirty && gpu_binding_layout_) {
    for (size_t i = 0; i < _bindingUnits.size(); ++i) {
      GFXBindingUnit& bindingUnit = _bindingUnits[i];
      switch (bindingUnit.type) {
        case GFXBindingType::UNIFORM_BUFFER: {
          if (bindingUnit.buffer) {
            gpu_binding_layout_->gpu_bindings[i].gpu_buffer = ((GLES3Buffer*)bindingUnit.buffer)->gpu_buffer();
          }
          break;
        }
        case GFXBindingType::SAMPLER: {
          if (bindingUnit.texView) {
            gpu_binding_layout_->gpu_bindings[i].gpu_tex_view = ((GLES3TextureView*)bindingUnit.texView)->gpu_tex_view();
          }
          if (bindingUnit.sampler) {
            gpu_binding_layout_->gpu_bindings[i].gpu_sampler = ((GLES3Sampler*)bindingUnit.sampler)->gpu_sampler();
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
