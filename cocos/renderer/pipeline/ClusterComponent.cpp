#include "ClusterComponent.h"
#include "Define.h"

namespace cc {
namespace pipeline {
ClusterComponent::~ClusterComponent() {
    CC_SAFE_DESTROY(_buildingShader);
    CC_SAFE_DESTROY(_buildingDescriptorSetLayout);
    CC_SAFE_DESTROY(_buildingPipelineLayout);
    CC_SAFE_DESTROY(_buildingPipelineState);
    CC_SAFE_DESTROY(_buildingDescriptorSet);

    CC_SAFE_DESTROY(_resetCounterShader);
    CC_SAFE_DESTROY(_resetCounterDescriptorSetLayout);
    CC_SAFE_DESTROY(_resetCounterPipelineLayout);
    CC_SAFE_DESTROY(_resetCounterPipelineState);
    CC_SAFE_DESTROY(_resetCounterDescriptorSet);

    CC_SAFE_DESTROY(_cullingShader);
    CC_SAFE_DESTROY(_cullingDescriptorSetLayout);
    CC_SAFE_DESTROY(_cullingPipelineLayout);
    CC_SAFE_DESTROY(_cullingPipelineState);
    CC_SAFE_DESTROY(_cullingDescriptorSet);

    CC_SAFE_DESTROY(_constantsBuffer);
    CC_SAFE_DESTROY(_lightBuffer);
    CC_SAFE_DESTROY(_clustersBuffer);
    CC_SAFE_DESTROY(_lightIndicesBuffer);
    CC_SAFE_DESTROY(_lightGridBuffer);
    CC_SAFE_DESTROY(_atomicIndexBuffer);

    delete _resetBarrier;
}

void ClusterComponent::initialize(gfx::Device* dev) {
    _device = dev;
    if (!_device->hasFeature(gfx::Feature::COMPUTE_SHADER)) return;

    uint maxInvocations = _device->getCapabilities().maxComputeWorkGroupInvocations;
    CCASSERT(CLUSTERS_X_THREADS * CLUSTERS_Y_THREADS * CLUSTERS_Z_THREADS <= maxInvocations, "maxInvocations is too small");
    CC_LOG_INFO(" work group size: %dx%dx%d", CLUSTERS_X_THREADS, CLUSTERS_Y_THREADS, CLUSTERS_Z_THREADS);

    _constantsBuffer = _device->createBuffer({
        gfx::BufferUsageBit::UNIFORM,
        gfx::MemoryUsageBit::HOST | gfx::MemoryUsageBit::DEVICE,
        2 * sizeof(Vec4) + 2 * sizeof(Mat4),
        2 * sizeof(Vec4) + 2 * sizeof(Mat4),
        gfx::BufferFlagBit::NONE,
    });

    _lightBufferStride = 4 * sizeof(Vec4);
    _lightBuffer       = _device->createBuffer({
        gfx::BufferUsageBit::STORAGE,
        gfx::MemoryUsageBit::HOST | gfx::MemoryUsageBit::DEVICE,
        _lightBufferStride * MAX_LIGHTS_GLOBAL,
        _lightBufferStride,
        gfx::BufferFlagBit::NONE,
    });
    _lightBufferData.resize(16 * MAX_LIGHTS_GLOBAL);

    // each cluster has 2 vec4, min + max position for AABB
    uint clusterBufferSize = 2 * sizeof(Vec4) * CLUSTER_COUNT;
    _clustersBuffer        = _device->createBuffer({
        gfx::BufferUsageBit::STORAGE,
        gfx::MemoryUsageBit::HOST | gfx::MemoryUsageBit::DEVICE,
        clusterBufferSize,
        clusterBufferSize,
        gfx::BufferFlagBit::NONE,
    });

    //  light indices belonging to clusters
    uint lightIndicesBufferSize = MAX_LIGHTS_PER_CLUSTER * CLUSTER_COUNT * sizeof(int);
    _lightIndicesBuffer         = _device->createBuffer({
        gfx::BufferUsageBit::STORAGE,
        gfx::MemoryUsageBit::HOST | gfx::MemoryUsageBit::DEVICE,
        lightIndicesBufferSize,
        lightIndicesBufferSize,
        gfx::BufferFlagBit::NONE,
    });

    //  for each cluster: (start index in b_clusterLightIndices, number of point lights, empty, empty)
    uint lightGridBufferSize = CLUSTER_COUNT * 4 * sizeof(uint);
    _lightGridBuffer         = _device->createBuffer({
        gfx::BufferUsageBit::STORAGE,
        gfx::MemoryUsageBit::HOST | gfx::MemoryUsageBit::DEVICE,
        lightGridBufferSize,
        lightGridBufferSize,
        gfx::BufferFlagBit::NONE,
    });

    // atomic counter for building the light grid
    // must be reset to 0 every frame
    uint atomicIndexBufferSize = sizeof(uint);
    _atomicIndexBuffer         = _device->createBuffer({
        gfx::BufferUsageBit::STORAGE,
        gfx::MemoryUsageBit::HOST | gfx::MemoryUsageBit::DEVICE,
        atomicIndexBufferSize,
        atomicIndexBufferSize,
        gfx::BufferFlagBit::NONE,
    });

    _buildingDispatchInfo = {CLUSTERS_X / CLUSTERS_X_THREADS, CLUSTERS_Y / CLUSTERS_Y_THREADS, CLUSTERS_Z / CLUSTERS_Z_THREADS};
    _resetDispatchInfo    = {1, 1, 1};
    _cullingDispatchInfo  = {CLUSTERS_X / CLUSTERS_X_THREADS, CLUSTERS_Y / CLUSTERS_Y_THREADS, CLUSTERS_Z / CLUSTERS_Z_THREADS};

    gfx::GlobalBarrierInfo resetBarrierInfo = {
        {
            gfx::AccessType::COMPUTE_SHADER_WRITE,
        },
        {
            gfx::AccessType::COMPUTE_SHADER_READ_OTHER,
        }};
    _resetBarrier = _device->createGlobalBarrier(resetBarrierInfo);

    initBuildingSatge();
    initResetStage();
    initCullingStage();

    _initialized = true;
}

void ClusterComponent::update(scene::Camera* camera, uint cameraIndex) {
    if (!_initialized) return;

    auto* const sceneData  = _pipeline->getPipelineSceneData();
    auto* const sharedData = sceneData->getSharedData();

    _constants[NEAR_FAR_OFFSET + 0]  = static_cast<float>(camera->nearClip);
    _constants[NEAR_FAR_OFFSET + 1]  = static_cast<float>(camera->farClip);
    _constants[VIEW_PORT_OFFSET + 0] = camera->viewPort.x * static_cast<float>(camera->width) * sharedData->shadingScale;
    _constants[VIEW_PORT_OFFSET + 1] = camera->viewPort.y * static_cast<float>(camera->height) * sharedData->shadingScale;
    _constants[VIEW_PORT_OFFSET + 2] = camera->viewPort.z * static_cast<float>(camera->width) * sharedData->shadingScale;
    _constants[VIEW_PORT_OFFSET + 3] = camera->viewPort.w * static_cast<float>(camera->height) * sharedData->shadingScale;

    memcpy(_constants.data() + MAT_VIEW_OFFSET, camera->matView.m, sizeof(cc::Mat4));
    memcpy(_constants.data() + MAT_PROJ_INV_OFFSET, camera->matProjInv.m, sizeof(cc::Mat4));

    _constantsBuffer->update(_constants.data(), 2 * sizeof(Vec4) + 2 * sizeof(Mat4));
    updateLights(camera);

    _cullingDescriptorSet->bindBuffer(0, _constantsBuffer);
    _cullingDescriptorSet->bindBuffer(1, _lightBuffer);
    _cullingDescriptorSet->update();

    if (cameraIndex >= _oldCamProjMats.size()) {
        _rebuildClusters = true;
        uint nextLength  = std::max(nextPow2(static_cast<uint>(cameraIndex)), uint(1));
        _oldCamProjMats.resize(nextLength, Mat4::ZERO);
        _oldCamProjMats[cameraIndex] = camera->matProj;
    } else {
        _rebuildClusters             = ClusterComponent::isProjMatChange(camera->matProj, _oldCamProjMats[cameraIndex]);
        _oldCamProjMats[cameraIndex] = camera->matProj;
    }

    if (_rebuildClusters) {
        _buildingDescriptorSet->bindBuffer(0, _constantsBuffer);
        _buildingDescriptorSet->update();
    }
}

void ClusterComponent::updateLights(scene::Camera* camera) {
    if (!_pipeline) {
        return;
    }

    _validLights.clear();

    scene::Sphere     sphere;
    const auto* const scene = camera->scene;
    for (auto* light : scene->getSphereLights()) {
        sphere.setCenter(light->getPosition());
        sphere.setRadius(light->getRange());
        if (sphere.sphereFrustum(camera->frustum)) {
            _validLights.emplace_back(static_cast<scene::Light*>(light));
        }
    }

    for (auto* light : scene->getSpotLights()) {
        sphere.setCenter(light->getPosition());
        sphere.setRadius(light->getRange());
        if (sphere.sphereFrustum(camera->frustum)) {
            _validLights.emplace_back(static_cast<scene::Light*>(light));
        }
    }

    const auto  exposure        = camera->exposure;
    const auto  validLightCount = _validLights.size();
    auto* const sceneData       = _pipeline->getPipelineSceneData();
    auto* const sharedData      = sceneData->getSharedData();

    if (validLightCount > _lightBufferCount) {
        _lightBufferCount = nextPow2(static_cast<uint>(validLightCount));
        _lightBuffer->resize(_lightBufferStride * _lightBufferCount);
        _lightBufferData.resize(16 * _lightBufferCount);
    }

    for (unsigned l = 0, offset = 0; l < validLightCount; l++, offset += 16) {
        auto*       light       = _validLights[l];
        const bool  isSpotLight = scene::LightType::SPOT == light->getType();
        const auto* spotLight   = isSpotLight ? static_cast<scene::SpotLight*>(light) : nullptr;
        const auto* sphereLight = isSpotLight ? nullptr : static_cast<scene::SphereLight*>(light);

        auto        index         = offset + UBOForwardLight::LIGHT_POS_OFFSET;
        const auto& position      = isSpotLight ? spotLight->getPosition() : sphereLight->getPosition();
        _lightBufferData[index++] = position.x;
        _lightBufferData[index++] = position.y;
        _lightBufferData[index]   = position.z;

        index                     = offset + UBOForwardLight::LIGHT_SIZE_RANGE_ANGLE_OFFSET;
        _lightBufferData[index++] = isSpotLight ? spotLight->getSize() : sphereLight->getSize();
        _lightBufferData[index]   = isSpotLight ? spotLight->getRange() : sphereLight->getRange();

        index             = offset + UBOForwardLight::LIGHT_COLOR_OFFSET;
        const auto& color = light->getColor();
        if (light->getUseColorTemperature()) {
            const auto& tempRGB       = light->getColorTemperatureRGB();
            _lightBufferData[index++] = color.x * tempRGB.x;
            _lightBufferData[index++] = color.y * tempRGB.y;
            _lightBufferData[index++] = color.z * tempRGB.z;
        } else {
            _lightBufferData[index++] = color.x;
            _lightBufferData[index++] = color.y;
            _lightBufferData[index++] = color.z;
        }

        float illuminance = isSpotLight ? spotLight->getIlluminance() : sphereLight->getIlluminance();
        if (sharedData->isHDR) {
            _lightBufferData[index] = illuminance * sharedData->fpScale * _lightMeterScale;
        } else {
            _lightBufferData[index] = illuminance * exposure * _lightMeterScale;
        }

        switch (light->getType()) {
            case scene::LightType::SPHERE:
                _lightBufferData[offset + UBOForwardLight::LIGHT_POS_OFFSET + 3]              = 0;
                _lightBufferData[offset + UBOForwardLight::LIGHT_SIZE_RANGE_ANGLE_OFFSET + 2] = 0;
                break;
            case scene::LightType::SPOT: {
                _lightBufferData[offset + UBOForwardLight::LIGHT_POS_OFFSET + 3]              = 1.0F;
                _lightBufferData[offset + UBOForwardLight::LIGHT_SIZE_RANGE_ANGLE_OFFSET + 2] = spotLight->getSpotAngle();

                index                     = offset + UBOForwardLight::LIGHT_DIR_OFFSET;
                const auto& direction     = spotLight->getDirection();
                _lightBufferData[index++] = direction.x;
                _lightBufferData[index++] = direction.y;
                _lightBufferData[index]   = direction.z;
            } break;
            default:
                break;
        }
    }
    // the count of lights is set to cc_lightDir[0].w
    _lightBufferData[3 * 4 + 3] = static_cast<float>(validLightCount);

    gfx::CommandBuffer* cmdBuf = _pipeline->getCommandBuffers()[0];
    cmdBuf->updateBuffer(_lightBuffer, _lightBufferData.data(), static_cast<uint>(_lightBufferData.size() * sizeof(float)));
}

void ClusterComponent::initBuildingSatge() {
    ShaderStrings sources;
    sources.glsl4 = StringUtil::format(
        R"(
		#define CLUSTERS_X 16
		#define CLUSTERS_Y 8

		layout(set=0, binding=0, std140) uniform CCConst {
		  vec4 cc_nearFar;
		  vec4 cc_viewPort;
		  mat4 cc_matView;
		  mat4 cc_matProjInv;
		};
		layout(set=0, binding=1, std430) buffer b_clustersBuffer { vec4 b_clusters[]; };

		vec4 screen2Eye(vec4 coord) {
			vec3 ndc = vec3(
				2.0 * (coord.x - cc_viewPort.x) / cc_viewPort.z - 1.0,
				2.0 * (coord.y - cc_viewPort.y) / cc_viewPort.w - 1.0,
				2.0 * coord.z - 1.0);
			vec4 eye = ((cc_matProjInv) * (vec4(ndc, 1.0)));
			eye      = eye / eye.w;
			return eye;
		}

		layout(local_size_x=16, local_size_y=8, local_size_z=4) in;
		void main() {
			uint clusterIndex = gl_GlobalInvocationID.z * uvec3(16, 8, 4).x * uvec3(16, 8, 4).y +
								gl_GlobalInvocationID.y * uvec3(16, 8, 4).x + gl_GlobalInvocationID.x;
			float clusterSizeX = ceil(cc_viewPort.z / float(CLUSTERS_X));
			float clusterSizeY = ceil(cc_viewPort.w / float(CLUSTERS_Y));
			vec4  minScreen    = vec4(vec2(gl_GlobalInvocationID.xy) * vec2(clusterSizeX, clusterSizeY), 1.0, 1.0);
			vec4  maxScreen    = vec4(vec2(gl_GlobalInvocationID.xy + uvec2(1, 1)) * vec2(clusterSizeX, clusterSizeY), 1.0, 1.0);
			vec3  minEye       = screen2Eye(minScreen).xyz;
			vec3  maxEye       = screen2Eye(maxScreen).xyz;
			float clusterNear  = -cc_nearFar.x * pow(cc_nearFar.y / cc_nearFar.x, float(gl_GlobalInvocationID.z) / float(24));
			float clusterFar   = -cc_nearFar.x * pow(cc_nearFar.y / cc_nearFar.x, float(gl_GlobalInvocationID.z + 1u) / float(24));
			vec3  minNear      = minEye * clusterNear / minEye.z;
			vec3  minFar       = minEye * clusterFar / minEye.z;
			vec3  maxNear      = maxEye * clusterNear / maxEye.z;
			vec3  maxFar       = maxEye * clusterFar / maxEye.z;
			vec3  minBounds    = min(min(minNear, minFar), min(maxNear, maxFar));
			vec3  maxBounds    = max(max(minNear, minFar), max(maxNear, maxFar));

			b_clusters[2u * clusterIndex + 0u] = vec4(minBounds, 1.0);
			b_clusters[2u * clusterIndex + 1u] = vec4(maxBounds, 1.0);
		})");
    sources.glsl3 = StringUtil::format(
        R"(
		#define CLUSTERS_X 16
		#define CLUSTERS_Y 8

		layout(std140) uniform CCConst {
		  vec4 cc_nearFar;
		  vec4 cc_viewPort;
		  mat4 cc_matView;
		  mat4 cc_matProjInv;
		};
		layout(std430, binding=1) buffer b_clustersBuffer { vec4 b_clusters[]; };

		vec4 screen2Eye(vec4 coord) {
			vec3 ndc = vec3(
				2.0 * (coord.x - cc_viewPort.x) / cc_viewPort.z - 1.0,
				2.0 * (coord.y - cc_viewPort.y) / cc_viewPort.w - 1.0,
				2.0 * coord.z - 1.0);
			vec4 eye = ((cc_matProjInv) * (vec4(ndc, 1.0)));
			eye      = eye / eye.w;
			return eye;
		}

		layout(local_size_x=16, local_size_y=8, local_size_z=4) in;
		void main() {
			uint clusterIndex = gl_GlobalInvocationID.z * uvec3(16, 8, 4).x * uvec3(16, 8, 4).y +
								gl_GlobalInvocationID.y * uvec3(16, 8, 4).x + gl_GlobalInvocationID.x;
			float clusterSizeX = ceil(cc_viewPort.z / float(CLUSTERS_X));
			float clusterSizeY = ceil(cc_viewPort.w / float(CLUSTERS_Y));
			vec4  minScreen    = vec4(vec2(gl_GlobalInvocationID.xy) * vec2(clusterSizeX, clusterSizeY), 1.0, 1.0);
			vec4  maxScreen    = vec4(vec2(gl_GlobalInvocationID.xy + uvec2(1, 1)) * vec2(clusterSizeX, clusterSizeY), 1.0, 1.0);
			vec3  minEye       = screen2Eye(minScreen).xyz;
			vec3  maxEye       = screen2Eye(maxScreen).xyz;
			float clusterNear  = -cc_nearFar.x * pow(cc_nearFar.y / cc_nearFar.x, float(gl_GlobalInvocationID.z) / float(24));
			float clusterFar   = -cc_nearFar.x * pow(cc_nearFar.y / cc_nearFar.x, float(gl_GlobalInvocationID.z + 1u) / float(24));
			vec3  minNear      = minEye * clusterNear / minEye.z;
			vec3  minFar       = minEye * clusterFar / minEye.z;
			vec3  maxNear      = maxEye * clusterNear / maxEye.z;
			vec3  maxFar       = maxEye * clusterFar / maxEye.z;
			vec3  minBounds    = min(min(minNear, minFar), min(maxNear, maxFar));
			vec3  maxBounds    = max(max(minNear, minFar), max(maxNear, maxFar));

			b_clusters[2u * clusterIndex + 0u] = vec4(minBounds, 1.0);
			b_clusters[2u * clusterIndex + 1u] = vec4(maxBounds, 1.0);
		})");
    // no compute support in GLES2

    gfx::ShaderInfo shaderInfo;
    shaderInfo.name   = "Compute ";
    shaderInfo.stages = {{gfx::ShaderStageFlagBit::COMPUTE, getShaderSource(sources)}};
    shaderInfo.blocks = {
        {0, 0, "CCConst", {{"cc_nearFar", gfx::Type::FLOAT4, 1}, {"cc_viewPort", gfx::Type::FLOAT4, 1}, {"cc_matView", gfx::Type::MAT4, 1}, {"cc_matProjInv", gfx::Type::MAT4, 1}}, 1},
    };
    shaderInfo.buffers = {{0, 1, "b_clustersBuffer", 1, gfx::MemoryAccessBit::WRITE_ONLY}};
    _buildingShader    = _device->createShader(shaderInfo);

    gfx::DescriptorSetLayoutInfo dslInfo;
    dslInfo.bindings.push_back({0, gfx::DescriptorType::UNIFORM_BUFFER, 1, gfx::ShaderStageFlagBit::COMPUTE});
    dslInfo.bindings.push_back({1, gfx::DescriptorType::STORAGE_BUFFER, 1, gfx::ShaderStageFlagBit::COMPUTE});

    _buildingDescriptorSetLayout = _device->createDescriptorSetLayout(dslInfo);
    _buildingDescriptorSet       = _device->createDescriptorSet({_buildingDescriptorSetLayout});
    _buildingDescriptorSet->bindBuffer(0, _constantsBuffer);
    _buildingDescriptorSet->bindBuffer(1, _clustersBuffer);
    _buildingDescriptorSet->update();

    _buildingPipelineLayout = _device->createPipelineLayout({{_buildingDescriptorSetLayout}});

    gfx::PipelineStateInfo pipelineInfo;
    pipelineInfo.shader         = _buildingShader;
    pipelineInfo.pipelineLayout = _buildingPipelineLayout;
    pipelineInfo.bindPoint      = gfx::PipelineBindPoint::COMPUTE;

    _buildingPipelineState = _device->createPipelineState(pipelineInfo);
}

void ClusterComponent::initResetStage() {
    ShaderStrings sources;
    sources.glsl4 = StringUtil::format(
        R"(
        layout(std430, binding = 0) buffer b_globalIndexBuffer { uint b_globalIndex[]; };
        layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
        void main()
        {
            if (gl_GlobalInvocationID.x == 0u) {
                b_globalIndex[0] = 0u;
            }
        }
        )");
    sources.glsl3 = StringUtil::format(
        R"(
        layout(std430, binding = 0) buffer b_globalIndexBuffer { uint b_globalIndex[]; };
        layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
        void main()
        {
            if (gl_GlobalInvocationID.x == 0u) {
                b_globalIndex[0] = 0u;
            }
        }
        )");
    // no compute support in GLES2

    gfx::ShaderInfo shaderInfo;
    shaderInfo.name     = "Compute ";
    shaderInfo.stages   = {{gfx::ShaderStageFlagBit::COMPUTE, getShaderSource(sources)}};
    shaderInfo.buffers  = {{0, 0, "b_globalIndexBuffer", 1, gfx::MemoryAccessBit::WRITE_ONLY}};
    _resetCounterShader = _device->createShader(shaderInfo);

    gfx::DescriptorSetLayoutInfo dslInfo;
    dslInfo.bindings.push_back({0, gfx::DescriptorType::STORAGE_BUFFER, 1, gfx::ShaderStageFlagBit::COMPUTE});

    _resetCounterDescriptorSetLayout = _device->createDescriptorSetLayout(dslInfo);
    _resetCounterDescriptorSet       = _device->createDescriptorSet({_resetCounterDescriptorSetLayout});
    _resetCounterDescriptorSet->bindBuffer(0, _atomicIndexBuffer);
    _resetCounterDescriptorSet->update();

    _resetCounterPipelineLayout = _device->createPipelineLayout({{_resetCounterDescriptorSetLayout}});

    gfx::PipelineStateInfo pipelineInfo;
    pipelineInfo.shader         = _resetCounterShader;
    pipelineInfo.pipelineLayout = _resetCounterPipelineLayout;
    pipelineInfo.bindPoint      = gfx::PipelineBindPoint::COMPUTE;

    _resetCounterPipelineState = _device->createPipelineState(pipelineInfo);
}

void ClusterComponent::initCullingStage() {
    ShaderStrings sources;
    sources.glsl4 = StringUtil::format(
        R"(
		layout(set=0, binding=0, std140) uniform CCConst {
		  vec4 cc_nearFar;
		  vec4 cc_viewPort;
		  mat4 cc_matView;
		  mat4 cc_matProjInv;
		};
		layout(set=0, binding=1, std430) readonly buffer b_ccLightsBuffer { vec4 b_ccLights[]; };
		layout(set=0, binding=2, std430) buffer b_clusterLightIndicesBuffer { uint b_clusterLightIndices[]; };
		layout(set=0, binding=3, std430) buffer b_clusterLightGridBuffer { uvec4 b_clusterLightGrid[]; };
		layout(set=0, binding=4, std430) buffer b_clustersBuffer { vec4 b_clusters[]; };
		layout(set=0, binding=5, std430) buffer b_globalIndexBuffer { uint b_globalIndex[]; };
		struct CCLight {
			vec4 cc_lightPos;
			vec4 cc_lightColor;
			vec4 cc_lightSizeRangeAngle;
			vec4 cc_lightDir;
		};
		uint ccLightCount()
		{
			return uint(b_ccLights[3].w);
		}
		CCLight getCCLight(uint i)
		{
			CCLight light;
			light.cc_lightPos = b_ccLights[4u * i + 0u];
			light.cc_lightColor = b_ccLights[4u * i + 1u];
			light.cc_lightSizeRangeAngle = b_ccLights[4u * i + 2u];
			light.cc_lightDir = b_ccLights[4u * i + 3u];
			return light;
		}
		struct Cluster {
			vec3 minBounds;
			vec3 maxBounds;
		};
		struct LightGrid {
			uint offset;
			uint ccLights;
		};
		Cluster getCluster(uint index)
		{
			Cluster cluster;
			cluster.minBounds = b_clusters[2u * index + 0u].xyz;
			cluster.maxBounds = b_clusters[2u * index + 1u].xyz;
			return cluster;
		}
		bool ccLightIntersectsCluster(CCLight light, Cluster cluster)
		{
			if (light.cc_lightPos.w > 0.0) {
				vec3 halfExtents = (cluster.maxBounds - cluster.minBounds) * 0.5;
				vec3 center = (cluster.minBounds + cluster.maxBounds) * 0.5;
				float sphereRadius = sqrt(dot(halfExtents, halfExtents));
				light.cc_lightDir = ((cc_matView) * (vec4(light.cc_lightDir.xyz, 1.0)));
				light.cc_lightDir.xyz = normalize((light.cc_lightDir - ((cc_matView) * (vec4(0,0,0, 1.0)))).xyz).xyz;
				vec3 v = center - light.cc_lightPos.xyz;
				float lenSq = dot(v, v);
				float v1Len = dot(v, light.cc_lightDir.xyz);
				float cosAngle = light.cc_lightSizeRangeAngle.z;
				float sinAngle = sqrt(1.0 - cosAngle * cosAngle);
				float distanceClosestPoint = cosAngle * sqrt(lenSq - v1Len * v1Len) - v1Len * sinAngle;
				bool angleCull = distanceClosestPoint > sphereRadius;
				bool frontCull = v1Len > sphereRadius + light.cc_lightSizeRangeAngle.y;
				bool backCull = v1Len < -sphereRadius;
				return !(angleCull || frontCull || backCull);

			}
			vec3 closest = max(cluster.minBounds, min(light.cc_lightPos.xyz, cluster.maxBounds));
			vec3 dist = closest - light.cc_lightPos.xyz;
			return dot(dist, dist) <= (light.cc_lightSizeRangeAngle.y * light.cc_lightSizeRangeAngle.y);
		}
		shared CCLight lights[(16 * 8 * 4)];
		layout(local_size_x = 16, local_size_y = 8, local_size_z = 4) in;
		void main()
		{
			uint visibleLights[100];
			uint visibleCount = 0u;
			uint clusterIndex = gl_GlobalInvocationID.z * uvec3(16, 8, 4).x * uvec3(16, 8, 4).y +
				gl_GlobalInvocationID.y * uvec3(16, 8, 4).x + gl_GlobalInvocationID.x;
			Cluster cluster = getCluster(clusterIndex);
			uint lightCount = ccLightCount();
			uint lightOffset = 0u;
			while (lightOffset < lightCount) {
				uint batchSize = min((16u * 8u * 4u), lightCount - lightOffset);
				if (uint(gl_LocalInvocationIndex) < batchSize) {
					uint lightIndex = lightOffset + gl_LocalInvocationIndex;
					CCLight light = getCCLight(lightIndex);
					light.cc_lightPos.xyz = ((cc_matView) * (vec4(light.cc_lightPos.xyz, 1.0))).xyz;
					lights[gl_LocalInvocationIndex] = light;
				}
				barrier();
				for (uint i = 0u; i < batchSize; i++) {
					if (visibleCount < 100u && ccLightIntersectsCluster(lights[i], cluster)) {
						visibleLights[visibleCount] = lightOffset + i;
						visibleCount++;
					}
				}
				lightOffset += batchSize;
			}
			barrier();
			uint offset = 0u;
			offset = atomicAdd(b_globalIndex[0], visibleCount);
			for (uint i = 0u; i < visibleCount; i++) {
				b_clusterLightIndices[offset + i] = visibleLights[i];
			}
			b_clusterLightGrid[clusterIndex] = uvec4(offset, visibleCount, 0, 0);
		})");
    sources.glsl3 = StringUtil::format(
        R"(
		layout(std140) uniform CCConst {
		  vec4 cc_nearFar;
		  vec4 cc_viewPort;
		  mat4 cc_matView;
		  mat4 cc_matProjInv;
		};
		layout(std430, binding=1) readonly buffer b_ccLightsBuffer { vec4 b_ccLights[]; };
		layout(std430, binding=2) buffer b_clusterLightIndicesBuffer { uint b_clusterLightIndices[]; };
		layout(std430, binding=3) buffer b_clusterLightGridBuffer { uvec4 b_clusterLightGrid[]; };
		layout(std430, binding=4) buffer b_clustersBuffer { vec4 b_clusters[]; };
		layout(std430, binding=5) buffer b_globalIndexBuffer { uint b_globalIndex[]; };
		struct CCLight {
			vec4 cc_lightPos;
			vec4 cc_lightColor;
			vec4 cc_lightSizeRangeAngle;
			vec4 cc_lightDir;
		};
		uint ccLightCount()
		{
			return uint(b_ccLights[3].w);
		}
		CCLight getCCLight(uint i)
		{
			CCLight light;
			light.cc_lightPos = b_ccLights[4u * i + 0u];
			light.cc_lightColor = b_ccLights[4u * i + 1u];
			light.cc_lightSizeRangeAngle = b_ccLights[4u * i + 2u];
			light.cc_lightDir = b_ccLights[4u * i + 3u];
			return light;
		}
		struct Cluster {
			vec3 minBounds;
			vec3 maxBounds;
		};
		struct LightGrid {
			uint offset;
			uint ccLights;
		};
		Cluster getCluster(uint index)
		{
			Cluster cluster;
			cluster.minBounds = b_clusters[2u * index + 0u].xyz;
			cluster.maxBounds = b_clusters[2u * index + 1u].xyz;
			return cluster;
		}
		bool ccLightIntersectsCluster(CCLight light, Cluster cluster)
		{
			if (light.cc_lightPos.w > 0.0) {
				vec3 halfExtents = (cluster.maxBounds - cluster.minBounds) * 0.5;
				vec3 center = (cluster.minBounds + cluster.maxBounds) * 0.5;
				float sphereRadius = sqrt(dot(halfExtents, halfExtents));
				light.cc_lightDir = ((cc_matView) * (vec4(light.cc_lightDir.xyz, 1.0)));
				light.cc_lightDir.xyz = normalize((light.cc_lightDir - ((cc_matView) * (vec4(0,0,0, 1.0)))).xyz).xyz;
				vec3 v = center - light.cc_lightPos.xyz;
				float lenSq = dot(v, v);
				float v1Len = dot(v, light.cc_lightDir.xyz);
				float cosAngle = light.cc_lightSizeRangeAngle.z;
				float sinAngle = sqrt(1.0 - cosAngle * cosAngle);
				float distanceClosestPoint = cosAngle * sqrt(lenSq - v1Len * v1Len) - v1Len * sinAngle;
				bool angleCull = distanceClosestPoint > sphereRadius;
				bool frontCull = v1Len > sphereRadius + light.cc_lightSizeRangeAngle.y;
				bool backCull = v1Len < -sphereRadius;
				return !(angleCull || frontCull || backCull);

			}
			vec3 closest = max(cluster.minBounds, min(light.cc_lightPos.xyz, cluster.maxBounds));
			vec3 dist = closest - light.cc_lightPos.xyz;
			return dot(dist, dist) <= (light.cc_lightSizeRangeAngle.y * light.cc_lightSizeRangeAngle.y);
		}
		shared CCLight lights[(16 * 8 * 4)];
		layout(local_size_x = 16, local_size_y = 8, local_size_z = 4) in;
		void main()
		{
			uint visibleLights[100];
			uint visibleCount = 0u;
			uint clusterIndex = gl_GlobalInvocationID.z * uvec3(16, 8, 4).x * uvec3(16, 8, 4).y +
				gl_GlobalInvocationID.y * uvec3(16, 8, 4).x + gl_GlobalInvocationID.x;
			Cluster cluster = getCluster(clusterIndex);
			uint lightCount = ccLightCount();
			uint lightOffset = 0u;
			while (lightOffset < lightCount) {
				uint batchSize = min((16u * 8u * 4u), lightCount - lightOffset);
				if (uint(gl_LocalInvocationIndex) < batchSize) {
					uint lightIndex = lightOffset + gl_LocalInvocationIndex;
					CCLight light = getCCLight(lightIndex);
					light.cc_lightPos.xyz = ((cc_matView) * (vec4(light.cc_lightPos.xyz, 1.0))).xyz;
					lights[gl_LocalInvocationIndex] = light;
				}
				barrier();
				for (uint i = 0u; i < batchSize; i++) {
					if (visibleCount < 100u && ccLightIntersectsCluster(lights[i], cluster)) {
						visibleLights[visibleCount] = lightOffset + i;
						visibleCount++;
					}
				}
				lightOffset += batchSize;
			}
			barrier();
			uint offset = 0u;
			offset = atomicAdd(b_globalIndex[0], visibleCount);
			for (uint i = 0u; i < visibleCount; i++) {
				b_clusterLightIndices[offset + i] = visibleLights[i];
			}
			b_clusterLightGrid[clusterIndex] = uvec4(offset, visibleCount, 0, 0);
		})");
    // no compute support in GLES2

    gfx::ShaderInfo shaderInfo;
    shaderInfo.name   = "Compute ";
    shaderInfo.stages = {{gfx::ShaderStageFlagBit::COMPUTE, getShaderSource(sources)}};
    shaderInfo.blocks = {
        {0, 0, "CCConst", {{"cc_nearFar", gfx::Type::FLOAT4, 1}, {"cc_viewPort", gfx::Type::FLOAT4, 1}, {"cc_matView", gfx::Type::MAT4, 1}, {"cc_matProjInv", gfx::Type::MAT4, 1}}, 1},
    };
    shaderInfo.buffers = {{0, 1, "b_ccLightsBuffer", 1, gfx::MemoryAccessBit::READ_ONLY},
                          {0, 2, "b_clusterLightIndicesBuffer", 1, gfx::MemoryAccessBit::WRITE_ONLY},
                          {0, 3, "b_clusterLightGridBuffer", 1, gfx::MemoryAccessBit::WRITE_ONLY},
                          {0, 4, "b_clustersBuffer", 1, gfx::MemoryAccessBit::READ_ONLY},
                          {0, 5, "b_globalIndexBuffer", 1, gfx::MemoryAccessBit::READ_WRITE}};
    _cullingShader     = _device->createShader(shaderInfo);

    gfx::DescriptorSetLayoutInfo dslInfo;
    dslInfo.bindings.push_back({0, gfx::DescriptorType::UNIFORM_BUFFER, 1, gfx::ShaderStageFlagBit::COMPUTE});
    dslInfo.bindings.push_back({1, gfx::DescriptorType::STORAGE_BUFFER, 1, gfx::ShaderStageFlagBit::COMPUTE});
    dslInfo.bindings.push_back({2, gfx::DescriptorType::STORAGE_BUFFER, 1, gfx::ShaderStageFlagBit::COMPUTE});
    dslInfo.bindings.push_back({3, gfx::DescriptorType::STORAGE_BUFFER, 1, gfx::ShaderStageFlagBit::COMPUTE});
    dslInfo.bindings.push_back({4, gfx::DescriptorType::STORAGE_BUFFER, 1, gfx::ShaderStageFlagBit::COMPUTE});
    dslInfo.bindings.push_back({5, gfx::DescriptorType::STORAGE_BUFFER, 1, gfx::ShaderStageFlagBit::COMPUTE});

    _cullingDescriptorSetLayout = _device->createDescriptorSetLayout(dslInfo);
    _cullingDescriptorSet       = _device->createDescriptorSet({_cullingDescriptorSetLayout});
    _cullingDescriptorSet->bindBuffer(0, _constantsBuffer);
    _cullingDescriptorSet->bindBuffer(1, _lightBuffer);
    _cullingDescriptorSet->bindBuffer(2, _lightIndicesBuffer);
    _cullingDescriptorSet->bindBuffer(3, _lightGridBuffer);
    _cullingDescriptorSet->bindBuffer(4, _clustersBuffer);
    _cullingDescriptorSet->bindBuffer(5, _atomicIndexBuffer);
    _cullingDescriptorSet->update();

    _cullingPipelineLayout = _device->createPipelineLayout({{_cullingDescriptorSetLayout}});

    gfx::PipelineStateInfo pipelineInfo;
    pipelineInfo.shader         = _cullingShader;
    pipelineInfo.pipelineLayout = _cullingPipelineLayout;
    pipelineInfo.bindPoint      = gfx::PipelineBindPoint::COMPUTE;

    _cullingPipelineState = _device->createPipelineState(pipelineInfo);
}

void ClusterComponent::clusterLightCulling() {
    if (!_initialized) return;

    auto* const  sceneData  = _pipeline->getPipelineSceneData();
    auto* const  sharedData = sceneData->getSharedData();
    scene::Pass* pass       = sharedData->deferredLightPass;
    auto*        cmdBuff    = _pipeline->getCommandBuffers()[0];

    if (_rebuildClusters) {
        // building cluster
        cmdBuff->bindPipelineState(const_cast<gfx::PipelineState*>(_buildingPipelineState));
        cmdBuff->bindDescriptorSet(0, const_cast<gfx::DescriptorSet*>(_buildingDescriptorSet));
        cmdBuff->dispatch(_buildingDispatchInfo);
    }

    // reset global index
    cmdBuff->bindPipelineState(const_cast<gfx::PipelineState*>(_resetCounterPipelineState));
    cmdBuff->bindDescriptorSet(0, const_cast<gfx::DescriptorSet*>(_resetCounterDescriptorSet));
    cmdBuff->dispatch(_resetDispatchInfo);
    cmdBuff->pipelineBarrier(_resetBarrier);
    // light culling
    cmdBuff->bindPipelineState(const_cast<gfx::PipelineState*>(_cullingPipelineState));
    cmdBuff->bindDescriptorSet(0, const_cast<gfx::DescriptorSet*>(_cullingDescriptorSet));
    cmdBuff->dispatch(_cullingDispatchInfo);

    gfx::DescriptorSet* materialDescriptorSet = pass->getDescriptorSet();
    materialDescriptorSet->bindBuffer(CLUSTER_LIGHT_BINDING, _lightBuffer);
    materialDescriptorSet->bindBuffer(CLUSTER_LIGHT_INDEX_BINDING, _lightIndicesBuffer);
    materialDescriptorSet->bindBuffer(CLUSTER_LIGHT_GRID_BINDING, _lightGridBuffer);
    materialDescriptorSet->update();
}

String& ClusterComponent::getShaderSource(ShaderStrings& sources) {
    switch (_device->getGfxAPI()) {
        case gfx::API::GLES2:
            return sources.glsl1;
        case gfx::API::GLES3:
            return sources.glsl3;
        case gfx::API::METAL:
        case gfx::API::VULKAN:
            return sources.glsl4;
        default: break;
    }
    return sources.glsl4;
}

} // namespace pipeline
} // namespace cc
