#pragma once

namespace cc {
namespace gfx {

class CCMTLPipelineLayout : public GFXPipelineLayout {
public:
    CCMTLPipelineLayout(Device *device);
    ~CCMTLPipelineLayout();

    virtual bool initialize(const GFXPipelineLayoutInfo &info) override;
    virtual void destroy() override;
};

} // namespace gfx
} // namespace cc
