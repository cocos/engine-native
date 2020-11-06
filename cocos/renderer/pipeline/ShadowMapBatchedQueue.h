#pragma once
#include "core/CoreStd.h"

namespace cc {
namespace pipeline {
struct SubModelView;
struct PassView;
struct RenderObject;
class RenderInstancedQueue;
class RenderBatchedQueue;
class ForwardPipeline;
class Device;
struct Shadows;
struct Light;
struct ModelView;

class CC_DLL ShadowMapBatchedQueue : public Object {
public:
    ShadowMapBatchedQueue(ForwardPipeline *);
    ~ShadowMapBatchedQueue() = default;
    void destroy();

    void clear();
    void gatherLightPasses(const Light *, gfx::CommandBuffer *cmdBufferer);
    void add(const ModelView *);
    void recordCommandBuffer(gfx::Device *device, gfx::RenderPass *renderPass, gfx::CommandBuffer *cmdBuffer) const;

private:
    void updateUBOs(const Light *, gfx::CommandBuffer *cmdBufferer) const;

private:
    ForwardPipeline *_pipeline = nullptr;
    gfx::Device *_device = nullptr;
    vector<const SubModelView *> _subModels;
    vector<const PassView *> _passes;
    vector<gfx::Shader *> _shaders;
    RenderInstancedQueue *_instancedQueue = nullptr;
    RenderBatchedQueue *_batchedQueue = nullptr;
    gfx::Buffer *_buffer = nullptr;
};
} // namespace pipeline
} // namespace cc
