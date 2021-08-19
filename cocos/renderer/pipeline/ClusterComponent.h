#pragma once

#include "RenderPipeline.h"
#include "renderer/gfx-base/GFXDef.h"
#include "renderer/gfx-base/GFXDevice.h"
#include "scene/Pass.h"
#include "scene/RenderScene.h"

namespace cc {
namespace pipeline {
struct ShaderStrings {
    String glsl4;
    String glsl3;
    String glsl1;
};

class ClusterComponent {
public:
    explicit ClusterComponent(RenderPipeline* pipeline) : _pipeline(pipeline){};
    ~ClusterComponent();

    static constexpr uint CLUSTERS_X = 16;
    static constexpr uint CLUSTERS_Y = 8;
    static constexpr uint CLUSTERS_Z = 24;

    // limit number of threads (D3D only allows up to 1024, there might also be shared memory limitations)
    // shader will be run by 6 work groups
    static constexpr uint CLUSTERS_X_THREADS = 16;
    static constexpr uint CLUSTERS_Y_THREADS = 8;
    static constexpr uint CLUSTERS_Z_THREADS = 4;

    static constexpr uint CLUSTER_COUNT = CLUSTERS_X * CLUSTERS_Y * CLUSTERS_Z;

    static constexpr uint MAX_LIGHTS_PER_CLUSTER = 100;

    static constexpr uint MAX_LIGHTS_GLOBAL = 1000;

    void initialize(gfx::Device* dev);

    void update(scene::Camera* camera, uint cameraIndex);

    void clusterLightCulling();

    inline const gfx::DescriptorSet* getBuildingDescriptorSet() { return _buildingDescriptorSet; }
    inline const gfx::PipelineState* getBuildingPipelineState() { return _buildingPipelineState; }
    inline const gfx::DescriptorSet* getResetCounterDescriptorSet() { return _resetCounterDescriptorSet; }
    inline const gfx::PipelineState* getResetCounterPipelineState() { return _resetCounterPipelineState; }
    inline const gfx::DescriptorSet* getCullingDescriptorSet() { return _cullingDescriptorSet; }
    inline const gfx::PipelineState* getCullingPipelineState() { return _cullingPipelineState; }

    inline const gfx::Buffer* getConstantsBuffer() { return _constantsBuffer; }
    inline const gfx::Buffer* getClusterBuffer() { return _clustersBuffer; }
    inline const gfx::Buffer* getLightingIndicesBuffer() { return _lightIndicesBuffer; }
    inline const gfx::Buffer* getLightingGridBuffer() { return _lightGridBuffer; }
    inline const gfx::Buffer* getAtomicIndexBuffer() { return _atomicIndexBuffer; }

    inline const gfx::DispatchInfo& getBuildingDispatchInfo() { return _buildingDispatchInfo; }
    inline const gfx::DispatchInfo& getResetCounterDispatchInfo() { return _resetDispatchInfo; }
    inline const gfx::DispatchInfo& getCullingDispatchInfo() { return _cullingDispatchInfo; }

    inline bool isInitialized() const { return _initialized; }

private:
    String& getShaderSource(ShaderStrings& sources);

    void initBuildingSatge();

    void initResetStage();

    void initCullingStage();

    void updateLights(scene::Camera* camera);

    static bool isProjMatChange(Mat4& curProj, Mat4& oldProj) {
        for (uint i = 0; i < sizeof(curProj.m) / sizeof(float); i++) {
            if (math::IsNotEqualF(curProj.m[i], oldProj.m[i])) {
                return true;
            }
        }
        return false;
    }

    gfx::Device* _device{nullptr};

    RenderPipeline* _pipeline = nullptr;

    gfx::Shader*              _buildingShader{nullptr};
    gfx::DescriptorSetLayout* _buildingDescriptorSetLayout{nullptr};
    gfx::PipelineLayout*      _buildingPipelineLayout{nullptr};
    gfx::PipelineState*       _buildingPipelineState{nullptr};
    gfx::DescriptorSet*       _buildingDescriptorSet{nullptr};

    gfx::Shader*              _resetCounterShader{nullptr};
    gfx::DescriptorSetLayout* _resetCounterDescriptorSetLayout{nullptr};
    gfx::PipelineLayout*      _resetCounterPipelineLayout{nullptr};
    gfx::PipelineState*       _resetCounterPipelineState{nullptr};
    gfx::DescriptorSet*       _resetCounterDescriptorSet{nullptr};

    gfx::Shader*              _cullingShader{nullptr};
    gfx::DescriptorSetLayout* _cullingDescriptorSetLayout{nullptr};
    gfx::PipelineLayout*      _cullingPipelineLayout{nullptr};
    gfx::PipelineState*       _cullingPipelineState{nullptr};
    gfx::DescriptorSet*       _cullingDescriptorSet{nullptr};

    static constexpr uint NEAR_FAR_OFFSET     = 0;
    static constexpr uint VIEW_PORT_OFFSET    = 4;
    static constexpr uint MAT_VIEW_OFFSET     = 8;
    static constexpr uint MAT_PROJ_INV_OFFSET = 24;

    std::array<float, (2 * sizeof(Vec4) + 2 * sizeof(Mat4)) / sizeof(float)> _constants{};
    gfx::Buffer*                                                             _constantsBuffer{nullptr};

    vector<scene::Light*> _validLights;
    std::vector<float>    _lightBufferData;
    gfx::Buffer*          _lightBuffer{nullptr};

    gfx::Buffer* _clustersBuffer{nullptr};
    gfx::Buffer* _lightIndicesBuffer{nullptr};
    gfx::Buffer* _lightGridBuffer{nullptr};
    gfx::Buffer* _atomicIndexBuffer{nullptr};

    gfx::GlobalBarrier* _resetBarrier{nullptr};

    gfx::DispatchInfo _buildingDispatchInfo;
    gfx::DispatchInfo _resetDispatchInfo;
    gfx::DispatchInfo _cullingDispatchInfo;

    uint  _lightBufferStride = 0;
    uint  _lightBufferCount  = 16;
    float _lightMeterScale   = 10000.0F;

    // only rebuild clusters when camera project matrix changed
    bool         _rebuildClusters{false};
    vector<Mat4> _oldCamProjMats;

    bool _initialized{false};
};

} // namespace pipeline
} // namespace cc
