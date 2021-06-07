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

#include "scene/Model.h"
#include "./SubModel.h"
#include "renderer/pipeline/Define.h"

Mat4 m4_1;
namespace cc {
namespace scene {

Model::~Model() {
    delete _worldBounds;
}

void Model::updateTransform() {
    Node *node = getTransform();
    if (node->getFlagsChanged() || node->getDirtyFlag()) {
        node->updateWorldTransform();
        _transformUpdated = true;
        if (_worldBounds) {
            _modelBounds.transform(node->getWorldMatrix(), node->getWorldPosition(), node->getWorldRotation(), node->getWorldScale(), _worldBounds);
        }
    }
}

void Model::updateUBOs(uint32_t stamp) {
    for (SubModel *subModel : _subModels) {
        subModel->update();
    }

    _updateStamp = stamp;
    if (!_transformUpdated) {
        return;
    }
    _transformUpdated = false;
    Mat4 worldMatrix  = getTransform()->getWorldMatrix();
    int  idx          = _instmatWorldIdx;
    if (idx >= 0) {
        // getInstanceAttributes()
    } else if (_localBuffer) {
        memcpy(_localData + pipeline::UBOLocal::MAT_WORLD_OFFSET, worldMatrix.m, sizeof(Mat4));
        m4_1 = worldMatrix.getInversed();
        float det = m4_1.determinant();
        float factor = 1.0 / sqrt(det);
        m4_1.scale(factor);
        memcpy(_localData + pipeline::UBOLocal::MAT_WORLD_IT_OFFSET, worldMatrix.m, sizeof(Mat4));
    }
}

void Model::addSubModel(SubModel *subModel) {
    _subModels.push_back(subModel);
}

} // namespace scene
} // namespace cc
