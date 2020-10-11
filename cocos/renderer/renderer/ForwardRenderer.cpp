/****************************************************************************
 Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "ForwardRenderer.h"

#include "gfx/DeviceGraphics.h"
#include "gfx/Texture2D.h"
#include "gfx/VertexBuffer.h"
#include "gfx/IndexBuffer.h"
#include "gfx/FrameBuffer.h"
#include "ProgramLib.h"
#include "View.h"
#include "Scene.h"
#include "Effect.h"
#include "InputAssembler.h"
#include "Pass.h"
#include "Camera.h"
#include "Light.h"
#include <algorithm>

#include "CCApplication.h"

#include "math/MathUtil.h"

RENDERER_BEGIN

#define CC_MAX_LIGHTS 4
#define CC_MAX_SHADOW_LIGHTS 2

ForwardRenderer::ForwardRenderer()
{
    _arrayPool = new RecyclePool<float>([]()mutable->float*{return new float[16];}, 8);
    
    _defines["CC_NUM_LIGHTS"] = Value(0);
    _defines["CC_NUM_SHADOW_LIGHTS"] = Value(0);
    
    _definesHash = 0;
}

ForwardRenderer::~ForwardRenderer()
{
    _lights.clear();
    _shadowLights.clear();
    _defines.clear();
    
    delete _arrayPool;
    _arrayPool = nullptr;
}

bool ForwardRenderer::init(DeviceGraphics* device, std::vector<ProgramLib::Template>& programTemplates, Texture2D* defaultTexture, int width, int height)
{
    BaseRenderer::init(device, programTemplates, defaultTexture);
    registerStage("opaque", std::bind(&ForwardRenderer::opaqueStage, this, std::placeholders::_1, std::placeholders::_2));
    registerStage("shadowcast", std::bind(&ForwardRenderer::shadowStage, this, std::placeholders::_1, std::placeholders::_2));
    registerStage("transparent", std::bind(&ForwardRenderer::transparentStage, this, std::placeholders::_1, std::placeholders::_2));
    return true;
}

void ForwardRenderer::resetData()
{
    _arrayPool->reset();
    reset();
}

void ForwardRenderer::render(Scene* scene, float deltaTime)
{
    resetData();
    
    
    _time[0] += deltaTime;
    _time[1] = deltaTime;
    _time[2] ++;
    _device->setUniformfv(cc_time, 4, _time, 4);
    
    updateLights(scene);
    scene->sortCameras();
    auto& cameras = scene->getCameras();
    auto &viewSize = Application::getInstance()->getViewSize();
    for (auto& camera : cameras)
    {
        View* view = requestView();
        camera->extractView(*view, viewSize.x, viewSize.y);
    }

    for (size_t i = 0, len = _views->getLength(); i < len; ++i) {
        const View* view = _views->getData(i);
        BaseRenderer::render(*view, scene);
    }
    
    scene->removeModels();
}

void ForwardRenderer::renderCamera(Camera* camera, Scene* scene)
{
    resetData();
    updateLights(scene);
    
    auto &viewSize = Application::getInstance()->getViewSize();
    View* cameraView = requestView();
    camera->extractView(*cameraView, viewSize.x, viewSize.y);

    for (size_t i = 0, len = _views->getLength(); i < len; ++i) {
        const View* view = _views->getData(i);
        BaseRenderer::render(*view, scene);
    }
    
    scene->removeModels();
}

void ForwardRenderer::updateLights(Scene* scene)
{
    _lights.clear();
    _shadowLights.clear();
    
    const Vector<Light*> lights = scene->getLights();
    for (const auto& light : lights)
    {
        light->update(_device);
        if (light->getShadowType() != Light::ShadowType::NONE)
        {
            if (_shadowLights.size() < CC_MAX_SHADOW_LIGHTS) {
                _shadowLights.pushBack(light);
            }
            
            View* view = requestView();
            std::vector<std::string> stages;
            stages.push_back("shadowcast");
            light->extractView(*view, stages);
            
            _lights.insert(0, light);
        }
        else {
            _lights.pushBack(light);
        }
    }
    
    if (lights.size() > 0)
    {
        updateDefines();
    }
    
    _numLights = lights.size();
}

void ForwardRenderer::updateDefines()
{
    _definesKey = "";
    for (size_t i = 0; i < _lights.size(); i++)
    {
        Light* light = _lights.at(i);
        
        _defines["CC_LIGHT_" + std::to_string(i)+ "_TYPE"] = (int)light->getType();
        _defines["CC_SHADOW_" + std::to_string(i)+ "_TYPE"] = (int)light->getShadowType();
        
        _definesKey += std::to_string((int)light->getType());
        _definesKey += std::to_string((int)light->getShadowType());
    }
    
    _defines["CC_NUM_LIGHTS"] = std::min(CC_MAX_LIGHTS, (int)_lights.size());
    _defines["CC_NUM_SHADOW_LIGHTS"] = std::min(CC_MAX_LIGHTS, (int)_shadowLights.size());
    
    _definesKey += std::to_string(_lights.size());
    _definesKey += std::to_string(_shadowLights.size());

    _definesHash = std::hash<std::string>{}(_definesKey);
}

void ForwardRenderer::submitLightsUniforms()
{
    size_t lCount = _lights.size();
    if (lCount > 0)
    {
        size_t count = std::min(CC_MAX_LIGHTS, (int)lCount);
        float* directions = _arrayPool->add();
        float* colors = _arrayPool->add();
        float* positionAndRanges = _arrayPool->add();
        Vec3 lightVec3;
        Vec3 colorVec3;
        Vec3 posVec3;
        for (int i = 0; i < count; ++i)
        {
            int index = i * 4;
            auto* light = _lights.at(i);
            lightVec3.set(light->getDirectionUniform());
            *(directions + index) = lightVec3.x;
            *(directions + index + 1) = lightVec3.y;
            *(directions + index + 2) = lightVec3.z;
            
            colorVec3.set(light->getColorUniform());
            *(colors + index) = colorVec3.x;
            *(colors + index + 1) = colorVec3.y;
            *(colors + index + 2) = colorVec3.z;
            
            posVec3.set(light->getPositionUniform());
            *(positionAndRanges + index) = posVec3.x;
            *(positionAndRanges + index + 1) = posVec3.y;
            *(positionAndRanges + index + 2) = posVec3.z;
            *(positionAndRanges + index + 3) = light->getRange();
            
            if (light->getType() == Light::LightType::SPOT) {
                *(directions + index + 3) = light->getSpotAngleUniform();
                *(colors + index + 3) = light->getSpotExp();
            }
            else {
                *(directions + index + 3) = 0;
                *(colors + index + 3) = 0;
            }
        }
        _device->setUniformfv(cc_lightDirection, count * 4, directions, count);
        _device->setUniformfv(cc_lightColor, count * 4, colors, count);
        _device->setUniformfv(cc_lightPositionAndRange, count * 4, positionAndRanges, count);
    }
}

void ForwardRenderer::submitShadowStageUniforms(const View& view)
{
    static float* shadowInfo = new float[4];
    shadowInfo[0] = view.shadowLight->getShadowMinDepth();
    shadowInfo[1] = view.shadowLight->getShadowMaxDepth();
    shadowInfo[2] = view.shadowLight->getShadowDepthScale();
    shadowInfo[3] = view.shadowLight->getShadowDarkness();
    
    _device->setUniformMat4(cc_shadow_map_lightViewProjMatrix, view.matViewProj);
    _device->setUniformfv(cc_shadow_map_info, 4, shadowInfo, 1);
    _device->setUniformf(cc_shadow_map_bias, view.shadowLight->getShadowBias());
}

void ForwardRenderer::submitOtherStagesUniforms()
{
    size_t count = _shadowLights.size();
    float* shadowLightInfo = _arrayPool->add();
    static float* shadowLightProjs = new float[4 * 16];
    
    for (size_t i = 0; i < count; ++i)
    {
        Light* light = _shadowLights.at(i);
        const Mat4& view = light->getViewProjMatrix();
        memcpy(shadowLightProjs + i * 16, view.m, sizeof(float) * 16);
        
        int index = (int)i * 4;
        *(shadowLightInfo + index) = light->getShadowMinDepth();
        *(shadowLightInfo + index + 1) = light->getShadowMaxDepth();
        *(shadowLightInfo + index + 2) = light->getShadowResolution();
        *(shadowLightInfo + index + 3) = light->getShadowDarkness();
    }
    
    _device->setUniformfv(cc_shadow_lightViewProjMatrix, count * 16, shadowLightProjs, count);
    _device->setUniformfv(cc_shadow_info, count * 4, shadowLightInfo, count);
}

bool ForwardRenderer::compareItems(const StageItem &a, const StageItem &b)
{
    size_t pa = a.passes.size();
    size_t pb = b.passes.size();
    
    if (pa != pb) {
        return pa > pb;
    }
    
    return a.sortKey > b.sortKey;
}

void ForwardRenderer::sortItems(std::vector<StageItem>& items)
{
    std::sort(items.begin(), items.end(), compareItems);
}

void ForwardRenderer::drawItems(const std::vector<StageItem>& items)
{
    size_t count = _shadowLights.size();
    if (count == 0 && _numLights == 0)
    {
        for (size_t i = 0, l = items.size(); i < l; i++)
        {
            draw(items.at(i));
        }
    }
    else
    {
        for (const auto& item : items)
        {
            for(size_t i = 0; i < count; i++)
            {
                Light* light = _shadowLights.at(i);
                _device->setTexture(cc_shadow_map[i], light->getShadowMap(), allocTextureUnit());
            }
            draw(item);
        }
    }
}

void ForwardRenderer::opaqueStage(const View& view, std::vector<StageItem>& items)
{
    // update uniforms
    _device->setUniformMat4(cc_matView, view.matView);
    _device->setUniformMat4(cc_matViewInv,view.matViewInv);
    _device->setUniformMat4(cc_matProj, view.matProj);
    _device->setUniformMat4(cc_matViewProj, view.matViewProj);
    static Vec3 cameraPos3;
    static Vec4 cameraPos4;
    view.getPosition(cameraPos3);
    cameraPos4.set(cameraPos3.x, cameraPos3.y, cameraPos3.z, 0);
    _device->setUniformVec4(cc_cameraPos, cameraPos4);
    submitLightsUniforms();
    submitOtherStagesUniforms();
    drawItems(items);
}

void ForwardRenderer::shadowStage(const View& view, std::vector<StageItem>& items)
{
    // update rendering
    submitShadowStageUniforms(view);
    
    for (auto& item : items)
    {
        const Value* def = item.effect->getDefine("CC_CASTING_SHADOW");
        if (def && def->asBool()) {
            draw(item);
        }
    }
}

void ForwardRenderer::transparentStage(const View& view, const std::vector<StageItem>& items)
{
    // update uniforms
    _device->setUniformMat4(cc_matView, view.matView);
    _device->setUniformMat4(cc_matViewInv,view.matViewInv);
    _device->setUniformMat4(cc_matProj, view.matProj);
    _device->setUniformMat4(cc_matViewProj, view.matViewProj);
    static Vec3 cameraPos3;
    static Vec4 cameraPos4;
    view.getPosition(cameraPos3);
    cameraPos4.set(cameraPos3.x, cameraPos3.y, cameraPos3.z, 0);
    _device->setUniformVec4(cc_cameraPos, cameraPos4);
    
    static Vec3 camFwd;
    static Vec3 tmpVec3;
    view.getForward(camFwd);
    
    submitLightsUniforms();
    submitOtherStagesUniforms();
    
    NodeProxy* node;
    // calculate zdist
    for (auto& item : const_cast<std::vector<StageItem>&>(items))
    {
        // TODO: we should use mesh center instead!
        node = const_cast<NodeProxy*>(item.model->getNode());
        if (node != nullptr)
        {
            node->getWorldPosition(&tmpVec3);
        }
        else
        {
            tmpVec3.set(0, 0, 0);
        }
        
        Vec3::subtract(tmpVec3, tmpVec3, &cameraPos3);
        item.sortKey = -Vec3::dot(tmpVec3, camFwd);
    }
    
    sortItems(const_cast<std::vector<StageItem>&>(items));
    drawItems(items);
}

RENDERER_END
