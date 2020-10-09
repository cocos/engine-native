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

#include "MeshBuffer.h"
#include "base/CCGLUtils.h"
#include "renderer/gfx/DeviceGraphics.h"

using namespace cocos2d;
using namespace cocos2d::renderer;

MIDDLEWARE_BEGIN


MeshBuffer::MeshBuffer(int vertexFormat)
    :MeshBuffer(vertexFormat, INIT_INDEX_BUFFER_SIZE,MAX_VERTEX_BUFFER_SIZE)
{
}

MeshBuffer::MeshBuffer(int vertexFormat, size_t indexSize, size_t vertexSize)
: _vertexFormat(vertexFormat)
, _ib(indexSize)
, _vb(vertexSize * vertexFormat * sizeof(float))
{
    _vb.setMaxSize(MAX_VERTEX_BUFFER_SIZE * _vertexFormat * sizeof(float));
    _ib.setMaxSize(INIT_INDEX_BUFFER_SIZE);
    _vb.setFullCallback([this]
    {
        uploadVB();
        uploadIB();
        _vb.reset();
        _ib.reset();
        next();
    });
    
    auto glIB = new IndexBuffer();
    glIB->init(DeviceGraphics::getInstance(), IndexFormat::UINT16, Usage::STATIC, nullptr, 0, (uint32_t)_ib.getCapacity() / sizeof(unsigned short));
    _glIBArr.push_back(glIB);
    
    auto glVB = new VertexBuffer();
    switch(_vertexFormat)
    {
        case VF_XYUVC:
            glVB->init(DeviceGraphics::getInstance(), VertexFormat::XY_UV_Color, Usage::DYNAMIC, nullptr, 0, (uint32_t)_vb.getCapacity() / VertexFormat::XY_UV_Color->getBytes());
            break;
        case VF_XYUVCC:
            glVB->init(DeviceGraphics::getInstance(), VertexFormat::XY_UV_Two_Color, Usage::DYNAMIC, nullptr, 0, (uint32_t)_vb.getCapacity() / VertexFormat::XY_UV_Two_Color->getBytes());
            break;
        default:
            CCASSERT(false, "MeshBuffer constructor unknow vertex format");
            break;
    }
    
    _glVBArr.push_back(glVB);
}

MeshBuffer::~MeshBuffer()
{
    auto num = _glVBArr.size();
    for (auto i = 0; i < num; i++)
    {
        _glIBArr[i]->release();
        _glVBArr[i]->release();
    }
    _glIBArr.clear();
    _glVBArr.clear();
}

void MeshBuffer::uploadVB()
{
    auto length = _vb.length();
    if (length == 0) return;

    auto glVB = _glVBArr[_bufferPos];
    glVB->update(0, _vb.getBuffer(), length);
}

void MeshBuffer::uploadIB()
{
    auto length = _ib.length();
    if (length == 0) return;
    
    auto glIB = _glIBArr[_bufferPos];
    glIB->update(0, _ib.getBuffer(), length);
}

void MeshBuffer::next()
{
    _bufferPos++;
    if (_glIBArr.size() <= _bufferPos)
    {
        auto glIB = new IndexBuffer();
        glIB->init(DeviceGraphics::getInstance(), IndexFormat::UINT16, Usage::STATIC, nullptr, 0, (uint32_t)_ib.getCapacity() / sizeof(unsigned short));
        _glIBArr.push_back(glIB);
    }
    
    if (_glVBArr.size() <= _bufferPos)
    {
        auto glVB = new VertexBuffer();
        
        switch(_vertexFormat)
        {
            case VF_XYUVC:
                glVB->init(DeviceGraphics::getInstance(), VertexFormat::XY_UV_Color, Usage::DYNAMIC, nullptr, 0, (uint32_t)_vb.getCapacity() / VertexFormat::XY_UV_Color->getBytes());
                break;
            case VF_XYUVCC:
                glVB->init(DeviceGraphics::getInstance(), VertexFormat::XY_UV_Two_Color, Usage::DYNAMIC, nullptr, 0, (uint32_t)_vb.getCapacity() / VertexFormat::XY_UV_Two_Color->getBytes());
                break;
            default:
                CCASSERT(false, "MeshBuffer constructor unknow vertex format");
                break;
        }
        
        _glVBArr.push_back(glVB);
    }
}

void MeshBuffer::reset()
{
    _bufferPos = 0;
    _vb.reset();
    _ib.reset();
}

MIDDLEWARE_END
