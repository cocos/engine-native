#include "SceneCulling.h"
#include "../Define.h"
#include "../RenderView.h"
#include "../helper/SharedMemory.h"
#include "ForwardPipeline.h"
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

void sceneCulling(ForwardPipeline *pipeline, RenderView *view) {
    const auto camera = view->getCamera();
//    auto a1 = offsetof(Camera, width);
//    auto a2 = offsetof(Camera, height);
//    auto a3 = offsetof(Camera, exposure);
//    auto a4 = offsetof(Camera, clearFlag);
//    auto a5 = offsetof(Camera, clearDepth);
//    auto a6 = offsetof(Camera, clearStencil);
//    auto a7 = offsetof(Camera, nodeID);
//    auto a8 = offsetof(Camera, sceneID);
//    auto a9 = offsetof(Camera, frustumID);
//    auto a10 = offsetof(Camera, forward);
//    auto a101 = offsetof(Camera, position);
//    auto a11 = offsetof(Camera, viewportX);
//    auto a12 = offsetof(Camera, viewportY);
//    auto a13 = offsetof(Camera, viewportWidth);
//    auto a14 = offsetof(Camera, viewportHeight);
//    auto a15 = offsetof(Camera, clearColor);
//    auto a16 = offsetof(Camera, matView);
//    auto a17 = offsetof(Camera, matViewProj);
//    auto a18 = offsetof(Camera, matViewProjInv);
//    auto a19 = offsetof(Camera, matProj);
//    auto a20 = offsetof(Camera, matProjInv);
    
    
    auto offsetof = camera->offsetOf();
    const auto scene = GET_SCENE(camera->getSceneID());
    RenderObjectList renderObjects;
    RenderObjectList shadowObjects;

    const auto mainLight = GET_MAIN_LIGHT(scene->mainLightID);
    const auto planarShadows = GET_PLANAR_SHADOW(scene->planarShadowID);
    if (mainLight) {
        //TODO coulsonwang
        //        if (planarShadows.enabled) {
        //            planarShadows.updateDirLight(mainLight);
        //        }
    }

    if (GET_SKYBOX(scene->skyboxID)->enabled && (camera->getClearFlag() & SKYBOX_FLAG)) {
        renderObjects.emplace_back(genRenderObject(GET_SKYBOX(scene->skyboxID), camera));
    }

    const auto stamp = Application::getInstance()->getTotalFrames();
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

    //TODO coulsonwang
    //        if (planarShadows->enabled) {
    //            planarShadows.updateShadowList(camera.frustum, stamp, (camera.visibility & Layers.BitMask.DEFAULT) !== 0);
    //        }
    pipeline->setRenderObjcts(renderObjects);
    pipeline->setShadowObjects(shadowObjects);
}

} // namespace pipeline
} // namespace cc
