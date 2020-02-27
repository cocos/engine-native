/****************************************************************************
Copyright (c) 2019 Xiamen Yaji Software Co., Ltd.

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

#include "Particle3DAssembler.hpp"
#include "../NodeProxy.hpp"

RENDERER_BEGIN

Particle3DAssembler::Particle3DAssembler()
{
    
}

Particle3DAssembler::~Particle3DAssembler()
{
    CC_SAFE_RELEASE(_trailVfmt);
}

void Particle3DAssembler::setTrailVertexFormat(VertexFormat *vfmt)
{
    if (_trailVfmt == vfmt) return;
    CC_SAFE_RETAIN(vfmt);
    CC_SAFE_RELEASE(_trailVfmt);
    _trailVfmt = vfmt;
    if (_trailVfmt)
    {
        _trailVertexBytes = _trailVfmt->getBytes();
        const VertexFormat::Element* vfPos = _vfmt->getElement(ATTRIB_NAME_POSITION_HASH);
        _trailPosOffset = vfPos->offset / 4;
    }
}

void Particle3DAssembler::fillBuffer(NodeProxy *node, MeshBuffer *buffer, const IARenderData& ia, RenderData* data)
{
    CCASSERT(data->getVBytes() % _bytesPerVertex == 0, "Assembler::fillBuffers vertices data doesn't follow vertex format");
    uint32_t vertexCount = ia.verticesCount >= 0 ? (uint32_t)ia.verticesCount : (uint32_t)data->getVBytes() / _bytesPerVertex;
    uint32_t indexCount = ia.indicesCount >= 0 ? (uint32_t)ia.indicesCount : (uint32_t)data->getIBytes() / sizeof(unsigned short);
    uint32_t vertexStart = (uint32_t)ia.verticesStart;
    
    // must retrieve offset before request
    auto& bufferOffset = buffer->request(vertexCount, indexCount);
    uint32_t vBufferOffset = bufferOffset.vByte / sizeof(float);
    uint32_t indexId = bufferOffset.index;
    uint32_t vertexId = bufferOffset.vertex;
    uint32_t vertexOffset = vertexId - vertexStart;

    float* worldVerts = buffer->vData + vBufferOffset;
    memcpy(worldVerts, data->getVertices() + vertexStart * _bytesPerVertex, vertexCount * _bytesPerVertex);
    
    // Copy index buffer with vertex offset
    uint16_t* indices = (uint16_t*)data->getIndices();
    uint16_t* dst = buffer->iData;
    for (auto i = 0, j = ia.indicesStart; i < indexCount; ++i, ++j)
    {
        dst[indexId++] = vertexOffset + indices[j];
    }
}

void Particle3DAssembler::fillTrailBuffer(NodeProxy *node, MeshBuffer *buffer, const IARenderData& ia, RenderData* data)
{
    CCASSERT(data->getVBytes() % _trailVertexBytes == 0, "Assembler::fillBuffers vertices data doesn't follow vertex format");
    uint32_t vertexCount = ia.verticesCount >= 0 ? (uint32_t)ia.verticesCount : (uint32_t)data->getVBytes() / _trailVertexBytes;
    uint32_t indexCount = ia.indicesCount >= 0 ? (uint32_t)ia.indicesCount : (uint32_t)data->getIBytes() / sizeof(unsigned short);
    uint32_t vertexStart = (uint32_t)ia.verticesStart;
    
    // must retrieve offset before request
    auto& bufferOffset = buffer->request(vertexCount, indexCount);
    uint32_t vBufferOffset = bufferOffset.vByte / sizeof(float);
    uint32_t indexId = bufferOffset.index;
    uint32_t vertexId = bufferOffset.vertex;
    uint32_t vertexOffset = vertexId - vertexStart;

    float* worldVerts = buffer->vData + vBufferOffset;
    memcpy(worldVerts, data->getVertices() + vertexStart * _trailVertexBytes, vertexCount * _trailVertexBytes);
    
    // Copy index buffer with vertex offset
    uint16_t* indices = (uint16_t*)data->getIndices();
    uint16_t* dst = buffer->iData;
    for (auto i = 0, j = ia.indicesStart; i < indexCount; ++i, ++j)
    {
        dst[indexId++] = vertexOffset + indices[j];
    }
}

void Particle3DAssembler::fillBuffers(NodeProxy *node, ModelBatcher *batcher, std::size_t index)
{
    VertexFormat* vfmt = index == 0 ? _vfmt : _trailVfmt;
    
    if (!_datas || !vfmt)
    {
        return;
    }
    
    MeshBuffer* buffer = batcher->getBuffer(vfmt);
    
    const IARenderData& ia = _iaDatas[index];
    std::size_t meshIndex = ia.meshIndex >= 0 ? ia.meshIndex : index;
    
    RenderData* data = _datas->getRenderData(meshIndex);
    if (!data)
    {
        return;
    }
    
    if (index != 0)
    {
        fillTrailBuffer(node, buffer, ia, data);
    }
    else
    {
        fillBuffer(node, buffer, ia, data);
    }
}

RENDERER_END
