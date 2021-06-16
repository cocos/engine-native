/****************************************************************************
 Copyright (c) 2021 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos.com
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.
 
 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "scene/SkinningModel.h"

namespace cc {
namespace scene {
namespace {
    Vec3                                            v3Min;
    Vec3                                            v3Max;
    Mat4                                            worldMatrix;
    AABB                                            ab1;
    Vec3                                            v31;
    Vec3                                            v32;
    Mat4                                            m41;
    std::vector<JointTransform>                     transStacks;
    std::array<float, pipeline::UBOSkinning::COUNT> dataArray;

    void uploadJointData(uint32_t base, const Mat4& mat, float* dst) {
        memcpy(reinterpret_cast<void*>(dst + base), mat.m, sizeof(float) * 12);
        dst[base + 3] = mat.m[12];
        dst[base + 7] = mat.m[13];
        dst[base + 11] = mat.m[14];
    }
    void updateWorldMatrix(const JointInfo& info, uint32_t stamp) {
        int i = -1;
        worldMatrix.setIdentity();
        auto currTransform = info.transform;
        uint32_t parentSize    = info.parents.size();
        transStacks.clear();
        while (currTransform.node)
        {
            if(currTransform.stamp == stamp || currTransform.stamp + 1 == stamp && !currTransform.node->getFlagsChanged()) {
                worldMatrix.set(currTransform.world);
                currTransform.stamp = stamp;
                break;
            }
            currTransform.stamp = stamp;
            transStacks.push_back(currTransform);
            i++;
            if (i >= parentSize) {
                break;
            }
            currTransform = info.parents[i];
        }
        while(i > -1) {
            currTransform = transStacks[i--];
            auto* node = currTransform.node;
            node->updateWorldTransform();
            Mat4::fromRTS(node->getWorldRotation(), node->getWorldPosition(), node->getWorldScale(), &currTransform.local);
            Mat4::multiply(worldMatrix, currTransform.local, &currTransform.world);
            worldMatrix.set(currTransform.world);
        }
    }
}  // namespace
    void SkinningModel::updateUBOs(uint32_t stamp) {
        Model::updateUBOs(stamp);
        if(!_needUpdate) {
            return;
        }
        uint32_t bIdx = 0;
        for (const JointInfo& jointInfo : _joints) {
            Mat4::multiply(jointInfo.transform.world, jointInfo.bindpose, &m41);
            for (uint32_t buffer : jointInfo.buffers) {
                uploadJointData(jointInfo.indices[bIdx] * 12, m41, &dataArray[buffer]);
                bIdx++;
            }
            bIdx = 0;
        }
        bIdx = 0;
        for(gfx::Buffer* buffer: _buffers) {
            _buffers[bIdx]->update(&dataArray[bIdx], _buffers[bIdx]->getSize());
            bIdx++;
        }
    }

    void SkinningModel::updateTransform(uint32_t stamp) {
        auto* root = getTransform();
        if (root->getFlagsChanged() || root->getDirtyFlag()) {
            root->updateWorldTransform();
            _transformUpdated = true;
        }
        v3Min.set(INFINITY, INFINITY, INFINITY);
        v3Max.set(-INFINITY, -INFINITY, -INFINITY);
        for (const JointInfo& jointInfo : _joints) {
            updateWorldMatrix(jointInfo, stamp);
            jointInfo.bound.transform(worldMatrix, &ab1);
            ab1.getBoundary(&v31, &v32);
            Vec3::min(v3Min, v31, &v3Min);
            Vec3::max(v3Max, v32, &v3Max);
        }
        if (_worldBounds) {
            AABB::fromPoints(v3Min, v3Max, &_modelBounds);
            _modelBounds.transform(root->getNodeLayout()->worldMatrix, _worldBounds);
        }
    }
} // namespace scene
} // namespace cc
