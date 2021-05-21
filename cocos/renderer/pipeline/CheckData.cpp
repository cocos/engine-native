#include "CheckData.h"
#include <vector>
#include "helper/SharedMemory.h"
#include "math/Mat4.h"
#include "math/Vec3.h"
#include "scene/RenderScene.h"
#include "scene/RenderWindow.h"
#include "scene/Frustum.h"
#include "scene/Node.h"
#include "scene/Light.h"
#include "scene/DirectionalLight.h"
#include "scene/SpotLight.h"
#include "scene/SphereLight.h"
#include "scene/AABB.h"
#include "scene/Pass.h"
#include "scene/Model.h"

namespace cc {
namespace pipeline {

static void checkMat4(const Mat4 &mat1, const Mat4 &mat2) {
    assert(mat1.m[0] == mat2.m[0]);
    assert(mat1.m[1] == mat2.m[1]);
    assert(mat1.m[2] == mat2.m[2]);
    assert(mat1.m[3] == mat2.m[3]);
    assert(mat1.m[4] == mat2.m[4]);
    assert(mat1.m[5] == mat2.m[5]);
    assert(mat1.m[6] == mat2.m[6]);
    assert(mat1.m[7] == mat2.m[7]);
    assert(mat1.m[8] == mat2.m[8]);
    assert(mat1.m[9] == mat2.m[9]);
    assert(mat1.m[10] == mat2.m[10]);
    assert(mat1.m[11] == mat2.m[11]);
    assert(mat1.m[12] == mat2.m[12]);
    assert(mat1.m[13] == mat2.m[13]);
    assert(mat1.m[14] == mat2.m[14]);
    assert(mat1.m[15] == mat2.m[15]);
}

static void checkBool(uint32_t value, bool b) {
    assert((value == 1) == b);
}

static void checkVec3(const Vec3 &vec1, const Vec3 &vec2) {
    assert(vec1.x == vec2.x);
    assert(vec1.y == vec2.y);
    assert(vec1.z == vec2.z);
}

static void checkFrustum(const Frustum *frustum, const scene::Frustum &newFrustum) {
    for (int i = 0; i < 8; ++i) {
        checkVec3(frustum->vertices[i], newFrustum.vertices[i]);
    }
    for (int i = 0; i < 6; ++i) {
        checkVec3(frustum->planes[i].normal, newFrustum.planes[i].normal);
        assert(frustum->planes[i].distance == newFrustum.planes[i].distance);
    }
}

static void checkAABB(const AABB *aabb1, const scene::AABB &aabb2) {
    checkVec3(aabb1->center, aabb2.center);
    checkVec3(aabb1->halfExtents, aabb2.halfExtents);
}

static void checkNode(Node *node, scene::Node *newNode) {
    //TODO(minggo)
}

static void checkWindow(RenderWindow *window, scene::RenderWindow *newWindow) {
    checkBool(window->hasOnScreenAttachments == 1, newWindow->hasOnScreenAttachments);
    checkBool(window->hasOffScreenAttachments, newWindow->hasOffScreenAttachments);
    assert(GET_FRAMEBUFFER(window->framebufferID) == newWindow->frameBuffer);
}

static void checkLight(const Light *light1, const scene::Light *light2) {
    checkBool(light1->useColorTemperature, light2->getUseColorTemperature());
    checkNode(GET_NODE(light1->nodeID), light2->getNode());
    assert(light1->lightType == static_cast<uint32_t>(light2->getType()));
    checkVec3(light1->color, light2->getColor());
    checkVec3(light1->colorTemperatureRGB, light2->getColorTemperatureRGB());
}

static void checkMainLight(const Light *light1, scene::DirectionalLight *light2) {
    assert(light1->luminance == light2->getIlluminance());
    checkVec3(light1->direction, light2->getDirection());
    checkLight(light1, light2);
}

static void checkSpotLight(const Light *light1, scene::SpotLight *light2) {
    assert(light1->luminance == light2->getIlluminance());
    assert(light1->range == light2->getRange());
    assert(light1->size == light2->getSize());
    assert(light1->spotAngle == light2->getAngle());
    assert(light1->aspect == light2->getAspect());
    checkVec3(light1->position, light2->getPosition());
    checkVec3(light1->direction, light2->getDirection());
    checkFrustum(light1->getFrustum(), light2->getFrustum());
    checkAABB(light1->getAABB(), light2->getAABB());
    checkLight(light1, light2);
}

static void checkSphereLight(const Light *light1, scene::SphereLight *light2) {
    assert(light1->luminance == light2->getIlluminance());
    assert(light1->range == light2->getRange());
    assert(light1->size == light2->getSize());
    checkVec3(light1->position, light2->getPosition());
    checkAABB(light1->getAABB(), light2->getAABB());
    checkLight(light1, light2);
}

static void checkSpotLights(const uint *lightArrayID, const std::vector<scene::SpotLight *> &spotLights) {
    const auto        count            = lightArrayID ? lightArrayID[0] : 0;
    assert(count == spotLights.size());
    for (uint32_t i = 1; i <= count; ++i) {
        auto *spotLight = cc::pipeline::Scene::getSpotLight(lightArrayID[i]);
        checkSpotLight(spotLight, spotLights[i-1]);
    }
}

static void checkSphereLights(const uint *lightArrayID, const std::vector<scene::SphereLight *> &sphereoLights) {
    const auto        count            = lightArrayID ? lightArrayID[0] : 0;
    assert(count == sphereoLights.size());
    for (uint32_t i = 1; i <= count; ++i) {
        auto *spotLight = cc::pipeline::Scene::getSpotLight(lightArrayID[i]);
        checkSphereLight(spotLight, sphereoLights[i-1]);
    }
}

static void checkPass(const PassView *pass1, const scene::Pass *pass2) {
    //TODO(minggo)
}

static void checkUIBatch(const UIBatch *batch1, const scene::DrawBatch2D *batch2) {
    assert(batch1->visFlags == batch2->visFlags);
    assert(batch1->passCount == batch2->passes.size());
    for (int i = 0; i < 4; ++i) {
        checkPass(batch1->getPassView(i), batch2->passes[i]);
        assert(batch1->getShader(i) == batch2->shaders[i]);
    }
    assert(batch1->getDescriptorSet() == batch2->descriptSet);
    assert(batch1->getInputAssembler() == batch2->inputAssembler);
}

static void checkUIBatches(const uint *uiBaches, const std::vector<scene::DrawBatch2D *> &drawBatches) {
    const auto count = uiBaches ? uiBaches[0] : 0;
    assert(count == drawBatches.size());
    for (uint32_t i = 1; i <= count; ++i) {
        auto *uiBatch = GET_UI_BATCH(uiBaches[i]);
        checkUIBatch(uiBatch, drawBatches[i-1]);
    }
}

static void checkModel(const ModelView *model1, const scene::Model *model2) {
    //TODO(minggo)
    checkBool(model1->enabled, model2->getEnabled());
    assert(model1->visFlags == model2->getVisFlags());
    checkBool(model1->castShadow, model2->getCastShadow());
    checkBool(model1->receiveShadow, model2->getReceiveShadow());
    checkAABB(GET_AABB(model1->worldBoundsID), *model2->getWorldBounds());
    checkNode(GET_NODE(model1->nodeID), model2->getNode());
    checkNode(GET_NODE(model1->transformID), model2->getTransform());
}

static void checkModels(const uint *models1, const std::vector<scene::Model *> &models2) {
    const auto count = models1 ? models1[0] : 0;
    assert(count == models2.size());
    for (uint32_t i = 1; i <= count; ++i) {
        auto *model = GET_MODEL(models1[i]);
        checkModel(model, models2[i-1]);
    }
}

static void checkScene(Scene *scene, scene::RenderScene *newScene) {
    checkMainLight(GET_LIGHT(scene->modelsID), newScene->getMainLight());
    checkSpotLights(scene->getSpotLightArrayID(), newScene->getSpotLights());
    checkSphereLights(scene->getSphereLightArrayID(), newScene->getSphereLights());
    checkUIBatches(scene->getUIBatches(), newScene->getDrawBatch2Ds());
    checkModels(scene->getModels(), newScene->getModels());
}

static void checkCamera(Camera *camera, scene::Camera *newCamera) {
    assert(camera->width == newCamera->width);
    assert(camera->height == newCamera->height);
    assert(camera->exposure == newCamera->exposure);
    assert(camera->clearFlag == newCamera->clearFlag);
    assert(camera->clearDepth == newCamera->clearDepth);
    assert(camera->clearStencil == newCamera->clearStencil);
    assert(camera->visibility == newCamera->visibility);
    assert(camera->forward == newCamera->forward);
    assert(camera->position == newCamera->position);
    assert(camera->viewportX == newCamera->viewPort.x);
    assert(camera->viewportY == newCamera->viewPort.y);
    assert(camera->viewportWidth == newCamera->viewPort.z);
    assert(camera->viewportHeight == newCamera->viewPort.w);
    assert(camera->clearColor == newCamera->clearColor);
    checkMat4(camera->matView, newCamera->matView);
    checkMat4(camera->matViewProj, newCamera->matViewProj);
    checkMat4(camera->matProjInv, newCamera->matProjInv);
    checkMat4(camera->matProj, newCamera->matProj);
    checkMat4(camera->matProjInv, newCamera->matProjInv);
    checkMat4(camera->matViewProjOffscreen, newCamera->matViewProjOffscreen);
    checkMat4(camera->matViewProjInvOffscreen, newCamera->matViewProjInvOffscreen);
    checkMat4(camera->matProjOffscreen, newCamera->matProjOffscreen);
    checkMat4(camera->matProjInvOffscreen, newCamera->matProjInvOffscreen);
    
    checkNode(GET_NODE(camera->nodeID), newCamera->node);
    checkScene(GET_SCENE(camera->sceneID), newCamera->scene);
    checkWindow(GET_WINDOW(camera->windowID), newCamera->window);
    checkFrustum(GET_FRUSTUM(camera->frustumID), newCamera->frustum);
}

void checkData(const vector<uint> &cameras, const vector<scene::Camera *> &newCameras) {
    assert(cameras.size() == newCameras.size());
    
    int i = 0;
    for (uint cameraID : cameras) {
        auto *camera = GET_CAMERA(cameraID);
        checkCamera(camera, newCameras[i]);
        ++i;
    }
}

}
}
