#include "CoreStd.h"
#include "GFXShader.h"
#include "GFXDevice.h"

namespace cc {
namespace gfx {

Shader::Shader(Device *device)
: GFXObject(ObjectType::SHADER), _device(device) {
    _hash = device->genShaderId();
}

Shader::~Shader() {
}

} // namespace gfx
} // namespace cc
