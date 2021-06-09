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

void Model::_uploadMat4AsVec4x3(Mat4 &mat, uint8_t *v1, uint8_t *v2, uint8_t *v3) {
    v1[0] = mat.m[0]; v1[1] = mat.m[1]; v1[2] = mat.m[2]; v1[3] = mat.m[12];
    v2[0] = mat.m[4]; v2[1] = mat.m[5]; v2[2] = mat.m[6]; v2[3] = mat.m[13];
    v3[0] = mat.m[8]; v3[1] = mat.m[9]; v3[2] = mat.m[10]; v3[3] = mat.m[14];
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

std::array<float, pipeline::UBOLocal::COUNT> bufferView;
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
        std::vector<uint8_t *> attrs = _instanceAttributeBlock->views;
        _uploadMat4AsVec4x3(worldMatrix, attrs[idx], attrs[idx + 1], attrs[idx + 2]);
    } else if (_localBuffer) {
        memcpy(bufferView.data() + pipeline::UBOLocal::MAT_WORLD_OFFSET, worldMatrix.m, sizeof(Mat4));
        m4_1 = worldMatrix.getInversed();
        float det = m4_1.determinant();
        float factor = 1.0 / sqrt(det);
        m4_1.scale(factor);
        memcpy(bufferView.data() + pipeline::UBOLocal::MAT_WORLD_IT_OFFSET, worldMatrix.m, sizeof(Mat4));
        _localBuffer->update(bufferView.data(), pipeline::UBOLocal::SIZE);
    }
}

void Model::addSubModel(SubModel *subModel) {
    _subModels.push_back(subModel);
}

} // namespace scene
} // namespace cc
