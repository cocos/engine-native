#include "SharedMemory.h"
#include "../math/MathUtil.h"

namespace cc {
namespace pipeline {

const se::PoolType ModelView::type = se::PoolType::MODEL;
const se::PoolType SubModelView::type = se::PoolType::SUB_MODEL;
const se::PoolType PassView::type = se::PoolType::PASS;
const se::PoolType Camera::type = se::PoolType::CAMERA;
const se::PoolType AABB::type = se::PoolType::AABB;
const se::PoolType Frustum::type = se::PoolType::FRUSTUM;
const se::PoolType Scene::type = se::PoolType::SCENE;
const se::PoolType Light::type = se::PoolType::LIGHT;
const se::PoolType Ambient::type = se::PoolType::AMBIENT;
const se::PoolType Fog::type = se::PoolType::FOG;
const se::PoolType Skybox::type = se::PoolType::SKYBOX;
const se::PoolType InstancedAttributeView::type = se::PoolType::INSTANCED_ATTRIBUTE;
const se::PoolType FlatBufferView::type = se::PoolType::FLAT_BUFFER;
const se::PoolType RenderingSubMesh::type = se::PoolType::SUB_MESH;
const se::PoolType Node::type = se::PoolType::NODE;
const se::PoolType Root::type = se::PoolType::ROOT;
const se::PoolType RenderWindow::type = se::PoolType::RENDER_WINDOW;
const se::PoolType Shadows::type = se::PoolType::SHADOW;
const se::PoolType Sphere::type = se::PoolType::SPHERE;

void AABB::getBoundary(cc::Vec3 &minPos, cc::Vec3 &maxPos) const {
    minPos = center - halfExtents;
    maxPos = center + halfExtents;
}

void AABB::merge(const AABB &aabb) {
    Vec3 minA = center - halfExtents;
    Vec3 minB = aabb.center - aabb.halfExtents;
    Vec3 maxA = center + halfExtents;
    Vec3 maxB = aabb.center + aabb.halfExtents;
    Vec3 maxP = maxA.max(maxB);
    Vec3 minP = minA.min(minB);

    Vec3 addP = maxP + minP;
    Vec3 subP = maxP - minP;
    center = addP * 0.5f;
    halfExtents = subP * 0.5f;
}

void Sphere::mergePoint(const cc::Vec3 &point) {
    if (radius < 0.0f) {
        center = point;
        radius = 0.0;
        return;
    }

    auto offset = point - center;
    auto distance = offset.length();

    if (distance > radius) {
        auto half = (distance - radius) * 0.5f;
        radius += half;
        offset.scale(half / distance);
        center += offset;
    }
}

void Sphere::define(const AABB &aabb) {
    cc::Vec3 minPos, maxPos;
    aabb.getBoundary(minPos, maxPos);

    // Initialize sphere
    center.set(minPos);
    radius = 0.0f;

    // Calculate sphere
    Vec3 offset = maxPos - center;
    const float dist = offset.length();

    const float half = dist * 0.5f;
    radius += dist * 0.5f;
    center += (half / dist) * offset;
}

void Sphere::mergeAABB(const AABB *aabb) {
    cc::Vec3 minPos, maxPos;
    aabb->getBoundary(minPos, maxPos);
    mergePoint(minPos);
    mergePoint(maxPos);
}
} // namespace pipeline
} // namespace cc
