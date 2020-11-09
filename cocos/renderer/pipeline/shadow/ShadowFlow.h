#pragma once
#include "../RenderFlow.h"
#include "math/Vec2.h"
namespace cc {
namespace pipeline {
class ForwardPipeline;
struct Light;

class CC_DLL ShadowFlow : public RenderFlow {
public:
    ShadowFlow() = default;
    virtual ~ShadowFlow();

    static const RenderFlowInfo &getInitializeInfo();

    virtual bool initialize(const RenderFlowInfo &info) override;

    virtual void activate(RenderPipeline *pipeline) override;

    virtual void render(RenderView *view) override;

    virtual void destroy() override;

private:
    void resizeShadowMap(const Light *light, const cc::Vec2 &size) const;

    void initShadowFrameBuffer(ForwardPipeline *pipeline, const Light *light);

private:
    static RenderFlowInfo _initInfo;

    gfx::RenderPass *_renderPass = nullptr;

    vector<const Light *> _validLights;
};
} // namespace pipeline
} // namespace cc
