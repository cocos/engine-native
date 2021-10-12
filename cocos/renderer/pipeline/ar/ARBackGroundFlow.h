#pragma once

#include "../RenderFlow.h"

namespace cc {
namespace pipeline {

class ARBackGroundStage;
struct Camera;

class ARBackGroundFlow : public RenderFlow {
public:
    static const RenderFlowInfo &getInitializeInfo();

    ARBackGroundFlow() = default;
    virtual ~ARBackGroundFlow();
    
    virtual bool initialize(const RenderFlowInfo &info) override;
    virtual void activate(RenderPipeline *pipeline) override;
    virtual void destroy() override;
    virtual void render(scene::Camera *camera) override;

private:
    static RenderFlowInfo _initInfo;

    ARBackGroundStage *_ARBackGroundStage = nullptr;
};

} // namespace pipeline
} // namespace cc