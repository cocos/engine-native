#include "CheckData.h"
#include <vector>
#include "helper/SharedMemory.h"
#include "math/Mat4.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "math/Vec2.h"
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
#include "scene/SubModel.h"
#include "scene/Define.h"
#include "renderer/pipeline/RenderPipeline.h"

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

static void checkVec2(const Vec2 &vec1, const Vec2 &vec2) {
    assert(vec1.x == vec2.x);
    assert(vec1.y == vec2.y);
}

static void checkVec3(const Vec3 &vec1, const Vec3 &vec2) {
    assert(vec1.x == vec2.x);
    assert(vec1.y == vec2.y);
    assert(vec1.z == vec2.z);
}

static void checkVec4(const Vec4 &vec1, const Vec4 &vec2) {
    assert(vec1.x == vec2.x);
    assert(vec1.y == vec2.y);
    assert(vec1.z == vec2.z);
    assert(vec1.w == vec2.w);
}

static void checkFrustum(const Frustum *frustum, const scene::Frustum &newFrustum) {
    for (int i = 0; i < 8; ++i) {
        checkVec3(frustum->vertices[i], newFrustum.vertices[i]);
    }
    for (int i = 0; i < 6; ++i) {
        checkVec3(frustum->planes[i].normal, newFrustum.planes[i].n);
        assert(frustum->planes[i].distance == newFrustum.planes[i].d);
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
    const uint32_t        count            = lightArrayID ? lightArrayID[0] : 0;
    assert(count == static_cast<uint32_t>(spotLights.size()));
    for (uint32_t i = 1; i <= count; ++i) {
        auto *spotLight = cc::pipeline::Scene::getSpotLight(lightArrayID[i]);
        checkSpotLight(spotLight, spotLights[i-1]);
    }
}

static void checkSphereLights(const uint *lightArrayID, const std::vector<scene::SphereLight *> &sphereoLights) {
    const uint32_t        count            = lightArrayID ? lightArrayID[0] : 0;
    assert(count == static_cast<uint32_t>(sphereoLights.size()));
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
    for (int i = 0; i < batch1->passCount; ++i) {
        checkPass(batch1->getPassView(i), batch2->passes[i]);
        assert(batch1->getShader(i) == batch2->shaders[i]);
    }
    assert(batch1->getDescriptorSet() == batch2->descriptorSet);
    assert(batch1->getInputAssembler() == batch2->inputAssembler);
}

static void checkUIBatches(const uint *uiBaches, const std::vector<scene::DrawBatch2D *> &drawBatches) {
    const uint32_t count = uiBaches ? uiBaches[0] : 0;
    assert(count == static_cast<uint32_t>(drawBatches.size()));
    for (uint32_t i = 1; i <= count; ++i) {
        auto *uiBatch = GET_UI_BATCH(uiBaches[i]);
        checkUIBatch(uiBatch, drawBatches[i-1]);
    }
}

static void checkBuffer(const uint8_t *b1, const uint8_t *b2, uint32_t size) {
    for (uint32_t i = 0; i < size; ++i) {
        assert(b1[i] == b2[i]);
    }
}

static void checkRenderingSubMesh(const RenderingSubMesh *subMesh1, const scene::RenderingSubMesh *subMesh2) {
    const uint *flatBuffers1 = subMesh1->getFlatBufferArrayID();
    const auto &flatBuffers2 = subMesh2->flatBuffers;
    const uint32_t count = flatBuffers1 ? flatBuffers1[0] : 0;
    assert(count == static_cast<uint32_t>(flatBuffers2.size()));
    uint32_t size = 0;
    for (uint32_t i = 1; i < count; ++i) {
        auto *f1 = GET_FLAT_BUFFER(i);
        const auto &f2 = flatBuffers2[i-1];
        assert(f1->stride == f2.stride);
        assert(f1->count == f2.count);
        checkBuffer(f1->getBuffer(&size), f2.data, f2.size);
    }
}

static void checkSubModel(SubModelView *subModel1, const scene::SubModel *subModel2) {
    assert(subModel1->priority == static_cast<uint32_t>(subModel2->getPriority()));
    assert(subModel1->passCount == static_cast<uint32_t>(subModel2->getPasses().size()));
    
    for (uint32_t i = 0; i < subModel1->passCount; ++i) {
        checkPass(subModel1->getPassView(i), subModel2->getPass(i));
        assert(subModel1->getShader(i) == subModel2->getShader(i));
    }
    assert(subModel1->getPlanarShader() == subModel2->getPlanarShader());
    assert(subModel1->getPlanarInstanceShader() == subModel2->getPlanarInstanceShader());
    assert(subModel1->getDescriptorSet() == subModel2->getDescriptorSet());
    assert(subModel1->getInputAssembler() == subModel2->getInputAssembler());
    checkRenderingSubMesh(subModel1->getSubMesh(), subModel2->getSubMesh());
}

static void checkSubModles(const uint *subModles1, const std::vector<scene::SubModel *> &subModles2) {
    const uint32_t count = subModles1 ? subModles1[0] : 0;
    assert(count == static_cast<uint32_t>(subModles2.size()));
    for (uint32_t i = 1; i < count; ++i) {
        checkSubModel(GET_SUBMODEL(subModles1[i]), subModles2[i-1]);
    }
}

static void checkAttribute(const gfx::Attribute *attr1, const gfx::Attribute &attr2) {
    assert(attr1->format == attr2.format);
    assert(attr1->name == attr2.name);
    assert(attr1->isNormalized == attr2.isNormalized);
    assert(attr1->isInstanced == attr2.isInstanced);
    assert(attr1->location == attr2.location);
}

static void checkInstancedAttributes(const uint *attrs1, const std::vector<gfx::Attribute> &attrs2) {
    const uint32_t count = attrs1 ? attrs1[0] : 0;
    assert(count == static_cast<uint32_t>(attrs2.size()));
    for (uint32_t i = 1; i < count; ++i) {
        checkAttribute(GET_ATTRIBUTE(attrs1[i]), attrs2[i-1]);
    }
}

static void checkModel(const ModelView *model1, const scene::Model *model2) {
    checkBool(model1->enabled, model2->getEnabled());
    assert(model1->visFlags == model2->getVisFlags());
    checkBool(model1->castShadow, model2->getCastShadow());
    checkBool(model1->receiveShadow, model2->getReceiveShadow());
    if (model1->worldBoundsID) {
        checkAABB(GET_AABB(model1->worldBoundsID), *model2->getWorldBounds());
    }
    
    checkNode(GET_NODE(model1->nodeID), model2->getNode());
    checkNode(GET_NODE(model1->transformID), model2->getTransform());
    checkSubModles(model1->getSubModelID(), model2->getSubModels());
    checkInstancedAttributes(model1->getInstancedAttributeID(), model2->getInstanceAttributes());
    
    uint size{0};
    const uint8_t *instanceBuffer = model1->getInstancedBuffer(&size);
    checkBuffer(instanceBuffer, model2->getInstancedBuffer(), size);
}

static void checkModels(const uint *models1, const std::vector<scene::Model *> &models2) {
    const uint32_t count = models1 ? models1[0] : 0;
    assert(count == static_cast<uint32_t>(models2.size()));
    for (uint32_t i = 1; i <= count; ++i) {
        auto *model = GET_MODEL(models1[i]);
        checkModel(model, models2[i-1]);
    }
}

static void checkScene(Scene *scene, scene::RenderScene *newScene) {
    if (scene->mainLightID) {
        checkMainLight(GET_LIGHT(scene->mainLightID), newScene->getMainLight());
    }
    
    checkSpotLights(scene->getSpotLightArrayID(), newScene->getSpotLights());
    checkSphereLights(scene->getSphereLightArrayID(), newScene->getSphereLights());
    checkUIBatches(scene->getUIBatches(), newScene->getDrawBatch2Ds());
//    checkModels(scene->getModels(), newScene->getModels());
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

static void checkFog(const Fog *fog1, const scene::Fog *fog2) {
    checkBool(fog1->enabled, fog2->enabled);
    assert(fog1->fogType == fog2->type);
    assert(fog1->fogDensity == fog2->density);
    assert(fog1->fogStart == fog2->start);
    assert(fog1->fogEnd == fog2->end);
    assert(fog1->fogAtten == fog2->atten);
    assert(fog1->fogTop == fog2->top);
    assert(fog1->fogRange == fog2->range);
    checkVec4(fog1->fogColor, fog2->color);
}

static void checkAmbient(const Ambient *ambient1, const scene::Ambient *ambient2) {
    checkBool(ambient1->enabled, ambient2->enabled);
    assert(ambient1->skyIllum == ambient2->skyIllum);
    checkVec4(ambient1->skyColor, ambient2->skyColor);
    checkVec4(ambient1->groundAlbedo, ambient2->groundAlbedo);
}

static void checkSkyBox(const Skybox *skyBox1, const scene::SkyBox *skyBox2) {
    checkBool(skyBox1->enabled, skyBox2->enabled);
    checkBool(skyBox1->isRGBE, skyBox2->isRGBE);
    checkBool(skyBox1->useIBL, skyBox2->useIBL);
    checkModel(GET_MODEL(skyBox1->modelID), skyBox2->model);
}

static void checkShadow(const Shadows *shadow1, const scene::Shadow *shadow2) {
    checkBool(shadow1->enabled, shadow2->enabled);
    checkBool(shadow1->dirty, shadow2->dirty);
    checkBool(shadow1->shadowMapDirty, shadow2->shadowMapDirty);
    checkBool(shadow1->selfShadow, shadow2->selfShadow);
    checkBool(shadow1->autoAdapt, shadow2->autoAdapt);
    assert(shadow1->shadowType == static_cast<uint32_t>(shadow2->shadowType));
    assert(shadow1->distance == shadow2->distance);
    checkPass(GET_PASS(shadow1->instancePass), shadow2->instancePass);
    checkPass(GET_PASS(shadow1->planarPass), shadow2->planarPass);
    assert(shadow1->nearValue == shadow2->nearValue);
    assert(shadow1->farValue == shadow2->farValue);
    assert(shadow1->aspect == shadow2->aspect);
    assert(shadow1->pcfType == shadow2->pcfType);
    assert(shadow1->bias == shadow2->bias);
    assert(shadow1->packing == shadow2->packing);
    assert(shadow1->linear == shadow2->linear);
    assert(shadow1->normalBias == shadow2->normalBias);
    assert(shadow1->orthoSize == shadow2->orthoSize);
    checkVec4(shadow1->color, shadow2->color);
    checkVec2(shadow1->size, shadow2->size);
    checkVec3(shadow1->normal, shadow2->normal);
    checkMat4(shadow1->matLight, shadow2->matLight);
}

static void checkPipelineSceneData() {
    auto *sceneData = RenderPipeline::getInstance()->getPipelineSceneData();
    auto *sharedData = sceneData->getSharedData();
    
    auto handle = sceneData->getSharedSceneDataHandle();
    auto *oldSharedData = GET_PIPELINE_SHARED_SCENE_DATA(handle);
    
    checkBool(oldSharedData->isHDR, sharedData->isHDR);
    assert(oldSharedData->shadingScale == sharedData->shadingScale);
    assert(oldSharedData->fpScale == sharedData->fpScale);
    assert(GET_SHADER(oldSharedData->deferredPostPassShader) == sharedData->deferredPostPassShader);
    assert(GET_SHADER(oldSharedData->deferredLightPassShader) == sharedData->deferredLightPassShader);
    checkPass(GET_PASS(oldSharedData->deferredLightPass), sharedData->deferredLightPass);
    checkPass(GET_PASS(oldSharedData->deferredPostPass), sharedData->deferredPostPass);
    checkFog(GET_FOG(oldSharedData->fog), sharedData->fog);
    checkAmbient(GET_AMBIENT(oldSharedData->ambient), sharedData->ambient);
    checkSkyBox(GET_SKYBOX(oldSharedData->skybox), sharedData->skybox);
    checkShadow(GET_SHADOWS(oldSharedData->shadow), sharedData->shadow);
}

void checkRoot() {
    const auto *root1 = GET_ROOT();
    const auto *root2 = scene::Root::instance;
    assert(root1->cumulativeTime == root2->cumulativeTime);
}

void checkData(const vector<uint> &cameras, const vector<scene::Camera *> &newCameras) {
    assert(cameras.size() == newCameras.size());
    
    int i = 0;
    for (uint cameraID : cameras) {
        auto *camera = GET_CAMERA(cameraID);
        checkCamera(camera, newCameras[i]);
        ++i;
    }
    
    checkPipelineSceneData();
}

}
}
