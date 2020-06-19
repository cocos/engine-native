#pragma once

#include "core/CoreStd.h"

namespace cc {
struct PSOCreateInfo;

namespace gfx {
class Device;
class GFXInputAssembler;
class GFXPipelineState;
class GFXRenderPass;
};

namespace pipeline {

class CC_DLL PipelineStateManager {
public:
    static gfx::GFXPipelineState *getOrCreatePipelineStage(gfx::Device *device,
                                                           const PSOCreateInfo &PSOInfo,
                                                           gfx::GFXRenderPass *renderPass,
                                                           gfx::GFXInputAssembler *inputAssembler);
    
private:
    static map<uint, gfx::GFXPipelineState *> _PSOHashMap;
};

} // namespace pipeline
} // namespace cc
