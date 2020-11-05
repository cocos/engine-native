#pragma once
#include "../RenderFlow.h"
namespace cc {
namespace pipeline {
class ForwardPipeline;
class Vec2;

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
    void resizeShadowMap(const Light *light, const Vec2 &size) const;

    void initShadowFrameBuffer(ForwardPipeline *pipeline, const Light *light);

private:
    static RenderFlowInfo _initInfo;

    gfx::RenderPass *_renderPass = nullptr;
};
} // namespace pipeline
} // namespace cc
