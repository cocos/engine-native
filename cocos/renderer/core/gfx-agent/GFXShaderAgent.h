#pragma once

#include "GFXAgent.h"
#include "../gfx/GFXShader.h"

namespace cc {
namespace gfx {

class CC_DLL ShaderAgent final : public Agent<Shader> {
public:
    using Agent::Agent;
    ShaderAgent(Device *device) = delete;
    ~ShaderAgent() override;

    bool initialize(const ShaderInfo &info) override;
    void destroy() override;
};

} // namespace gfx
} // namespace cc