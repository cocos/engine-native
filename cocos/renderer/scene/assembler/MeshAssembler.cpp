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

#include "MeshAssembler.hpp"
#include "../ModelBatcher.hpp"

RENDERER_BEGIN

MeshAssembler::MeshAssembler()
{
    _useModel = true;
}

MeshAssembler::~MeshAssembler()
{
    RENDERER_SAFE_RELEASE(_renderNode);
}

void MeshAssembler::handle(NodeProxy *node, ModelBatcher *batcher, Scene *scene)
{
    if (_renderNode != nullptr)
    {
        batcher->commitIA(_renderNode, this, node->getCullingMask());
    }
    else
    {
        batcher->commitIA(node, this, node->getCullingMask());
    }
    
    batcher->flushIA();
}

void MeshAssembler::setNode(NodeProxy* node)
{
    if (_renderNode == node)
    {
        return;
    }
    
    if (_renderNode != nullptr)
    {
        _renderNode->release();
    }
    _renderNode = node;
    if (_renderNode != nullptr)
    {
        _renderNode->retain();
    }
}

void MeshAssembler::updateIAData(std::size_t index, VertexFormat* vfmt, se_object_ptr vertices, se_object_ptr indices)
{
    _datas.updateMesh(index, vertices, indices);
    auto data = _datas.getRenderData(index);
    
    auto ia = adjustIA(index);
    
    auto ib = ia->getIndexBuffer();
    if (!ib) {
        ib = new IndexBuffer();
        ib->autorelease();
        ib->init(DeviceGraphics::getInstance(), IndexFormat::UINT16, Usage::STATIC, data->getIndices(), data->getIBytes(), (uint32_t)data->getIBytes() / sizeof(unsigned short));
        ia->setIndexBuffer(ib);
    }
    else {
        ib->update(0, data->getIndices(), data->getIBytes());
    }
    
    auto vb = ia->getVertexBuffer();
    if (!vb) {
        vb = new VertexBuffer();
        vb->autorelease();
        vb->init(DeviceGraphics::getInstance(), vfmt, Usage::STATIC, data->getVertices(), data->getVBytes(), (uint32_t)data->getVBytes() / vfmt->getBytes());
        ia->setVertexBuffer(vb);
    }
    else {
        vb->update(0, data->getVertices(), data->getVBytes());
    }
    
    ia->setCount(ib->getCount());
}

void MeshAssembler::reset()
{
    CustomAssembler::reset();
    
    _datas.clear();
}

RENDERER_END
