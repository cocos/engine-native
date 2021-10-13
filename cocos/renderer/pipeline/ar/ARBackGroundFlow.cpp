#include "ARBackGroundFlow.h"
#include "ARBackGroundStage.h"
#include "../forward/ForwardPipeline.h"
//#include "../SceneCulling.h"

namespace cc {
namespace pipeline {
RenderFlowInfo ARBackGroundFlow::initInfo = {
    "ARBackGroundFlow",
    static_cast<uint>(ForwardFlowPriority::FORWARD) - 100,
    static_cast<uint>(RenderFlowTag::SCENE),
    {},
};
const RenderFlowInfo &ARBackGroundFlow::getInitializeInfo() { return ARBackGroundFlow::initInfo; }

ARBackGroundFlow::~ARBackGroundFlow() = default;

bool ARBackGroundFlow::initialize(const RenderFlowInfo &info) {
#if USE_AR_MODULE
    RenderFlow::initialize(info);

    if (_stages.empty()) {
        auto *arStage = CC_NEW(ARBackGroundStage);
        _stages.emplace_back(arStage);
    }

    return true;
#else
    return false;
#endif
}

void ARBackGroundFlow::activate(RenderPipeline *pipeline) {
    RenderFlow::activate(pipeline);
}

void ARBackGroundFlow::render(scene::Camera *camera) {
    RenderFlow::render(camera);
}

void ARBackGroundFlow::destroy() {
    RenderFlow::destroy();
}

} // namespace pipeline
} // namespace cc