#pragma once

namespace cc {
namespace gfx {

class CCMTLBindingLayout : public GFXBindingLayout {
public:
    CCMTLBindingLayout(Device *device);
    virtual ~CCMTLBindingLayout();

    virtual bool initialize(const GFXBindingLayoutInfo &info) override;
    virtual void destroy() override;
    virtual void update() override;
};

} // namespace gfx
} // namespace cc
