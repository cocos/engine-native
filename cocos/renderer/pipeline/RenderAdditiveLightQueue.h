#pragma once

#include "core/CoreStd.h"

namespace cc {
class SubModel;
struct PSOCreateInfo;
class Light;
class RenderObject;
class Pass;
struct MacroPatch;

namespace pipeline {

class RenderAdditiveLightQueue : public gfx::Object {
public:
    RenderAdditiveLightQueue() = default;
    ~RenderAdditiveLightQueue() = default;
    
    void add(RenderObject *renderObj, uint subModelIdx, Pass *pass, uint beginIdx, uint endIdx);
    void clear(const gfx::vector<Light *>::type &validLights,
               const gfx::vector<gfx::GFXBuffer *>::type &lightBuffers,
               const gfx::vector<uint>::type &lightIndices);
    void recordCommandBuffer(gfx::GFXDevice *device, gfx::GFXRenderPass *renderPass, gfx::GFXCommandBuffer *cmdBuff);
    
private:
    void attach(RenderObject *renderObj, uint subModelIdx, gfx::GFXBuffer *lightBuffer,
                uint lightIdx, Pass *pass, gfx::vector<MacroPatch>::type patches);

private:
    gfx::vector<gfx::vector<SubModel *>::type>::type _sortedSubModelsArray;
    gfx::vector<gfx::vector<PSOCreateInfo>::type>::type _sortedPSOCIArray;
    gfx::vector<Light *>::type _validLights;
    gfx::vector<gfx::GFXBuffer *>::type _lightBuffers;
    gfx::vector<uint>::type _lightIndices;
    uint _phaseID = 0;
};

} // namespace pipeline
} // namespace cc
