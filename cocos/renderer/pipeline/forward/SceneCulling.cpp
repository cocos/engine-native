#include "SceneCulling.h"
#include "../Define.h"
#include "../RenderView.h"
#include "../helper/SharedMemory.h"
#include "ForwardPipeline.h"
#include "gfx/GFXBuffer.h"
#include "gfx/GFXDescriptorSet.h"
#include "math/Quaternion.h"
#include "platform/Application.h"

namespace cc {
namespace pipeline {

RenderObject genRenderObject(ModelView *model, const Camera *camera) {
    float depth = 0;
    if (model->nodeID != 0) {
        const auto node = GET_NODE(model->nodeID);
        cc::Vec3 position;
        cc::Vec3::subtract(node->getWorldPosition(), camera->getPosition(), &position);
        depth = position.dot(camera->getForward());
    }

    return {depth, model};
}

cc::Mat4 getShadowWorldMatrix(const Shadows *shadows, const cc::Vec4 &rotation, const cc::Vec3 &dir) {
    Vec3 translation(dir);
    translation.negate();
    const auto sphere = GET_SPHERE(shadows->getSphereID());
    const auto distance = std::sqrt(2) * sphere->getRadius();
    translation.scale(distance);
    translation.add(sphere->getCenter());

    return std::move(Mat4::fromRT(rotation, translation));
}

void updateDirLight(const Shadows *shadows, const Light *light, gfx::DescriptorSet *descriptorSet) {
    const auto node = GET_NODE(light->getNodeID());
    if (!node->hasFlagsChanged() && !shadows->isDirty()) {
        return;
    }

    //    shadows.dirty = false; //todo coulsonwang
    const auto rotation = node->getWorldRotation();
    Quaternion _qt(rotation.x, rotation.y, rotation.z, rotation.w);
    Vec3 forward(0, 0, -1.0f);
    forward.transformQuat(_qt);
    const auto &normal = shadows->getNormal();
    const auto distance = shadows->getDistance() + 0.001f; // avoid z-fighting
    const auto NdL = normal.dot(forward);
    const auto scale = 1.0f / NdL;
    const auto lx = forward.x * scale;
    const auto ly = forward.y * scale;
    const auto lz = forward.z * scale;
    const auto nx = normal.x;
    const auto ny = normal.y;
    const auto nz = normal.z;
    float matLight[16];
    matLight[0] = 1 - nx * lx;
    matLight[1] = -nx * ly;
    matLight[2] = -nx * lz;
    matLight[3] = 0;
    matLight[4] = -ny * lx;
    matLight[5] = 1 - ny * ly;
    matLight[6] = -ny * lz;
    matLight[7] = 0;
    matLight[8] = -nz * lx;
    matLight[9] = -nz * ly;
    matLight[10] = 1 - nz * lz;
    matLight[11] = 0;
    matLight[12] = lx * distance;
    matLight[13] = ly * distance;
    matLight[14] = lz * distance;
    matLight[15] = 1;

    descriptorSet->getBuffer(UBOShadow::BLOCK.binding)->update(matLight, UBOShadow::MAT_LIGHT_PLANE_PROJ_OFFSET, sizeof(matLight));
}

void sceneCulling(ForwardPipeline *pipeline, RenderView *view) {
    const auto camera = view->getCamera();
    const auto shadows = pipeline->getShadows();
    const auto skybox = pipeline->getSkybox();
    const auto scene = GET_SCENE(camera->getSceneID());

    const Light *mainLight = nullptr;
    if (scene->mainLightID) mainLight = GET_LIGHT(scene->mainLightID);
    RenderObjectList renderObjects;
    RenderObjectList shadowObjects;

    if (shadows->isEnabled() && shadows->isDirty()) {
        float color[3] = {shadows->getColor().x, shadows->getColor().y, shadows->getColor().z};
        pipeline->getDescriptorSet()->getBuffer(UBOShadow::BLOCK.binding)->update(color, UBOShadow::SHADOW_COLOR_OFFSET, sizeof(color));
    }

    if (mainLight && shadows->getShadowType() == static_cast<uint>(ShadowType::PLANAR)) {
        updateDirLight(shadows, mainLight, pipeline->getDescriptorSet());
    }

    if (skybox->isEnabled() && skybox->getModelID() && (camera->getClearFlag() & SKYBOX_FLAG)) {
        renderObjects.emplace_back(genRenderObject(GET_MODEL(skybox->getModelID()), camera));
    }

    uint32_t *models = GET_MODEL_ARRAY(scene->modelsID);
    uint32_t modelCount = models[0];
    for (size_t i = 1; i <= modelCount; i++) {
        const auto model = GET_MODEL(models[i]);

        // filter model by view visibility
        if (model->enabled) {
            const auto visibility = view->getVisibility();
            const auto vis = visibility & static_cast<uint>(LayerList::UI_2D);
            const auto node = GET_NODE(model->nodeID);
            if (vis) {
                if ((model->nodeID && (visibility == node->getLayer())) ||
                    visibility == model->visFlags) {
                    renderObjects.emplace_back(genRenderObject(model, camera));
                }
            } else {

                if ((model->nodeID && ((visibility & node->getLayer()) == node->getLayer())) ||
                    (visibility & model->visFlags)) {

                    // shadow render Object
                    if (model->castShadow) {
                        //                        sphere.mergeAABB(shadowSphere, shadowSphere, model.worldBounds!); //TODO coulsonwang
                        shadowObjects.emplace_back(genRenderObject(model, camera));
                    }

                    // frustum culling
                    if (model->worldBoundsID && !aabb_frustum(GET_AABB(model->worldBoundsID), GET_FRUSTUM(camera->getFrustumID()))) {
                        continue;
                    }

                    renderObjects.emplace_back(genRenderObject(model, camera));
                }
            }
        }
    }

    pipeline->setRenderObjcts(renderObjects);
    pipeline->setShadowObjects(shadowObjects);
}

} // namespace pipeline
} // namespace cc
