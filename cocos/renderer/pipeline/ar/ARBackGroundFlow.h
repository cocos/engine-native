#pragma once

#include "../RenderFlow.h"

namespace cc {
namespace pipeline {

class ARBackGroundStage;

class ARBackGroundFlow : public RenderFlow {
public:
    static const RenderFlowInfo &getInitializeInfo();

    ARBackGroundFlow() = default;
    ~ARBackGroundFlow() override;
    
    bool initialize(const RenderFlowInfo &info) override;
    void activate(RenderPipeline *pipeline) override;
    void destroy() override;
    void render(scene::Camera *camera) override;

private:
    static RenderFlowInfo initInfo;

    ARBackGroundStage *_arBackGroundStage = nullptr;
};

} // namespace pipeline
} // namespace cc