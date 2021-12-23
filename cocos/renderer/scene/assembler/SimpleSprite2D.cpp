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

#include "SimpleSprite2D.hpp"
#include "../RenderFlow.hpp"

RENDERER_BEGIN

SimpleSprite2D::SimpleSprite2D()
{
    
}

SimpleSprite2D::~SimpleSprite2D()
{
    
}

void SimpleSprite2D::fillBuffers(NodeProxy* node, ModelBatcher* batcher, std::size_t index)
{
    RenderData* data = _datas->getRenderData(0);
    if (!data)
    {
        return;
    }
    
    MeshBuffer* buffer = batcher->getBuffer(_vfmt);
    
    // must retrieve offset before request
    auto& bufferOffset = buffer->request(4, 6);
    uint32_t vBufferOffset = bufferOffset.vByte / sizeof(float);
    uint32_t indexId = bufferOffset.index;
    uint32_t vertexId = bufferOffset.vertex;
    
    if (*_dirty & VERTICES_DIRTY || node->isDirty(RenderFlow::WORLD_TRANSFORM_CHANGED | RenderFlow::NODE_OPACITY_CHANGED))
    {
        float vl = _localData[0],
        vr = _localData[2],
        vb = _localData[1],
        vt = _localData[3];
        
        const Mat4& worldMat = node->getWorldMatrix();
        size_t dataPerVertex = _bytesPerVertex / sizeof(float);
        float* srcWorldVerts = (float*)data->getVertices();
        
        // left bottom
        float u = srcWorldVerts[2];
        worldMat.transformVector(vl, vb, 0.0f, 1.0f, (cocos2d::Vec3*)srcWorldVerts);
        srcWorldVerts[2] = u;

        // right bottom
        srcWorldVerts += dataPerVertex;
        u = srcWorldVerts[2];
        worldMat.transformVector(vr, vb, 0.0f, 1.0f, (cocos2d::Vec3*)srcWorldVerts);
        srcWorldVerts[2] = u;

        // left top
        srcWorldVerts += dataPerVertex;
        u = srcWorldVerts[2];
        worldMat.transformVector(vl, vt, 0.0f, 1.0f, (cocos2d::Vec3*)srcWorldVerts);
        srcWorldVerts[2] = u;

        // right top
        srcWorldVerts += dataPerVertex;
        u = srcWorldVerts[2];
        worldMat.transformVector(vr, vt, 0.0f, 1.0f, (cocos2d::Vec3*)srcWorldVerts);
        srcWorldVerts[2] = u;
        
        *_dirty &= ~VERTICES_DIRTY;
    }
    
    float* dstWorldVerts = buffer->vData + vBufferOffset;
    memcpy(dstWorldVerts, data->getVertices(), 4 * _bytesPerVertex);

    uint8_t* ptrAlpha = (uint8_t*)data->getVertices() + _alphaOffset;
    size_t dataPerVertex = _bytesPerVertex / sizeof(uint8_t);
    uint8_t* ptrColor = (uint8_t*)dstWorldVerts + _vfColor->offset;

    for (uint32_t i = 0; i < 4; ++i)
    {
        float alpha = *(ptrAlpha) / 255.0;

        uint8_t valueB = *(ptrAlpha - 1) * alpha;
        uint8_t valueG = *(ptrAlpha - 2) * alpha;
        uint8_t valueR = *(ptrAlpha - 3) * alpha;

        *ptrColor       = valueR;
        *(ptrColor + 1) = valueG;
        *(ptrColor + 2) = valueB;

        ptrAlpha += dataPerVertex;
        ptrColor += dataPerVertex;
    }

    // Copy index buffer with vertex offset
    uint16_t* srcIndices = (uint16_t*)data->getIndices();
    uint16_t* dstIndices = buffer->iData;
    for (auto i = 0, j = 0; i < 6; ++i, ++j)
    {
        dstIndices[indexId++] = vertexId + srcIndices[j];
    }
}

void SimpleSprite2D::updateOpacity(std::size_t index, uint8_t opacity)
{
    // has no color info in vertex buffer
    if(!_vfColor || !_datas || !_vfmt)
    {
        return;
    }
    
    const IARenderData& ia = _iaDatas[index];
    std::size_t meshIndex = ia.meshIndex >= 0 ? ia.meshIndex : index;
    
    RenderData* data = _datas->getRenderData(meshIndex);
    if (!data)
    {
        return;
    }
    
    CCASSERT(data->getVBytes() % _bytesPerVertex == 0, "Assembler::updateOpacity vertices data doesn't follow vertex format");
    uint32_t vertexCount = (uint32_t)data->getVBytes() / _bytesPerVertex;
    
    size_t dataPerVertex = _bytesPerVertex / sizeof(uint8_t);
    uint8_t* ptrAlpha = (uint8_t*)data->getVertices() + _alphaOffset;
    for (uint32_t i = 0; i < vertexCount; ++i)
    {
       *ptrAlpha = opacity;
       ptrAlpha += dataPerVertex;
    }
    
    *_dirty &= ~VERTICES_OPACITY_CHANGED;
}

RENDERER_END
