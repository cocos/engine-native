#include "Define.h"
#include "gfx/GFXDevice.h"
#include "helper/SharedMemory.h"

namespace cc {
namespace pipeline {

DescriptorSetLayoutInfos globalDescriptorSetLayout;
DescriptorSetLayoutInfos localDescriptorSetLayout;
const SamplerInfo UNIFORM_SHADOWMAP = {
    {static_cast<uint>(SetIndex::GLOBAL),
     static_cast<uint>(PipelineGlobalBindings::SAMPLER_SHADOWMAP),
     "cc_shadowMap",
     gfx::Type::SAMPLER2D,
     1},
    {
        gfx::DescriptorType::SAMPLER,
        1,
        gfx::ShaderStageFlagBit::FRAGMENT,
    }};

static gfx::UniformBlock block;
static gfx::DescriptorSetLayoutBinding binding;
BlockInfo UBOGlobal::BLOCK = {
    {static_cast<uint>(SetIndex::GLOBAL),
     static_cast<uint>(PipelineGlobalBindings::UBO_GLOBAL),
     "CCGlobal",
     {
         {"cc_time", gfx::Type::FLOAT4, 1},
         {"cc_screenSize", gfx::Type::FLOAT4, 1},
         {"cc_screenScale", gfx::Type::FLOAT4, 1},
         {"cc_nativeSize", gfx::Type::FLOAT4, 1},
         {"cc_matView", gfx::Type::MAT4, 1},
         {"cc_matViewInv", gfx::Type::MAT4, 1},
         {"cc_matProj", gfx::Type::MAT4, 1},
         {"cc_matProjInv", gfx::Type::MAT4, 1},
         {"cc_matViewProj", gfx::Type::MAT4, 1},
         {"cc_matViewProjInv", gfx::Type::MAT4, 1},
         {"cc_cameraPos", gfx::Type::FLOAT4, 1},
         {"cc_exposure", gfx::Type::FLOAT4, 1},
         {"cc_mainLitDir", gfx::Type::FLOAT4, 1},
         {"cc_mainLitColor", gfx::Type::FLOAT4, 1},
         {"cc_ambientSky", gfx::Type::FLOAT4, 1},
         {"cc_ambientGround", gfx::Type::FLOAT4, 1},
         {"cc_fogColor", gfx::Type::FLOAT4, 1},
         {"cc_fogBase", gfx::Type::FLOAT4, 1},
         {"cc_fogAdd", gfx::Type::FLOAT4, 1},
     },
     1},
    {
        gfx::DescriptorType::UNIFORM_BUFFER,
        1,
        gfx::ShaderStageFlagBit::ALL,
    }};

BlockInfo UBOShadow::BLOCK = {
    {static_cast<uint>(SetIndex::GLOBAL),
     static_cast<uint>(PipelineGlobalBindings::UBO_SHADOW),
     "CCShadow",
     {
         {"cc_matLightPlaneProj", gfx::Type::MAT4, 1},
         {"cc_matLightViewProj", gfx::Type::MAT4, 1},
         {"cc_shadowColor", gfx::Type::FLOAT4, 1},
     },
     1},
    {
        gfx::DescriptorType::UNIFORM_BUFFER,
        1,
        gfx::ShaderStageFlagBit::ALL,
    }};

BlockInfo UBOLocalBatched::BLOCK = {
    {static_cast<uint>(SetIndex::LOCAL),
     static_cast<uint>(ModelLocalBindings::UBO_LOCAL),
     "CCLocalBatched",
     {
         {"cc_matWorlds", gfx::Type::MAT4, 1},
     },
     1},
    {
        gfx::DescriptorType::UNIFORM_BUFFER,
        1,
        gfx::ShaderStageFlagBit::ALL,
    }};

uint genSamplerHash(const gfx::SamplerInfo &info) {
    uint hash = 0;
    hash |= static_cast<uint>(info.minFilter);
    hash |= static_cast<uint>(info.magFilter) << 2;
    hash |= static_cast<uint>(info.mipFilter) << 4;
    hash |= static_cast<uint>(info.addressU) << 6;
    hash |= static_cast<uint>(info.addressV) << 8;
    hash |= static_cast<uint>(info.addressW) << 10;
    hash |= static_cast<uint>(info.maxAnisotropy) << 12;
    hash |= static_cast<uint>(info.cmpFunc) << 16;
    hash |= static_cast<uint>(info.minLOD) << 20;
    hash |= static_cast<uint>(info.maxLOD) << 24;
    hash |= static_cast<uint>(info.mipLODBias) << 28;
    return 0;
}

static uint defaultSamplerHash = genSamplerHash(gfx::SamplerInfo());

map<uint, gfx::Sampler *> samplerCache;
gfx::Sampler *getSampler(uint hash) {
    if (hash == 0) {
        hash = defaultSamplerHash;
    }

    auto sampler = samplerCache[hash];
    if (sampler) {
        return sampler;
    }

    gfx::SamplerInfo info;
    info.minFilter = static_cast<gfx::Filter>(hash & 3);
    info.magFilter = static_cast<gfx::Filter>((hash >> 2) & 3);
    info.mipFilter = static_cast<gfx::Filter>((hash >> 4) & 3);
    info.addressU = static_cast<gfx::Address>((hash >> 6) & 3);
    info.addressV = static_cast<gfx::Address>((hash >> 8) & 3);
    info.addressW = static_cast<gfx::Address>((hash >> 10) & 3);
    info.maxAnisotropy = ((hash >> 12) & 15);
    info.cmpFunc = static_cast<gfx::ComparisonFunc>((hash >> 16) & 15);
    info.minLOD = ((hash >> 20) & 15);
    info.maxLOD = ((hash >> 24) & 15);
    info.mipLODBias = ((hash >> 28) & 15);

    sampler = gfx::Device::getInstance()->createSampler(std::move(info));
    return sampler;
}

int aabb_plane(const AABB *aabb, const Plane *plane) {
    auto r = aabb->halfExtents.x * std::abs(plane->normal.x) +
             aabb->halfExtents.y * std::abs(plane->normal.y) +
             aabb->halfExtents.z * std::abs(plane->normal.z);
    auto dot = Vec3::dot(plane->normal, aabb->center);
    if (dot + r < plane->distance) {
        return -1;
    } else if (dot - r > plane->distance) {
        return 0;
    }
    return 1;
};

bool aabb_frustum(const AABB *aabb, const Frustum *frustum) {
    const size_t plantCount = 6;
    for (size_t i = 0; i < plantCount; i++) {
        // frustum plane normal points to the inside
        //        if (aabb_plane(aabb, GET_PLANE(i)) == -1) {
        //            return 0;
        //        }
    } // completely outside
    return 1;
}

uint SKYBOX_FLAG = static_cast<uint>(gfx::ClearFlagBit::STENCIL) << 1;

map<String, uint> PassPhase::phases;
uint PassPhase::phaseNum = 0;

} // namespace pipeline
} // namespace cc
