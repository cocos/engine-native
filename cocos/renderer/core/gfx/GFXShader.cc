#include "CoreStd.h"
#include "GFXShader.h"

namespace cc {
namespace gfx {

GFXShader::GFXShader(Device *device)
: GFXObject(GFXObjectType::SHADER), _device(device) {
}

GFXShader::~GFXShader() {
}

} // namespace gfx
} // namespace cc
