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

#pragma once

#include "Assembler.hpp"
#include "../ModelBatcher.hpp"

RENDERER_BEGIN

class NodeProxy;
class ModelBatcher;

enum class Space: uint8_t
{
    WORLD = 0,
    LOCAL = 1,
    CUSTOM = 2
};

class Particle3DAssembler: public Assembler
{
public:
    Particle3DAssembler();
    ~Particle3DAssembler();
    
    virtual void fillBuffers(NodeProxy *node, ModelBatcher *batcher, std::size_t index) override;
    void setTrailVertexFormat(VertexFormat* vfmt);
    void setTrailModuleEnable(bool enable) {_trailModuleEnable = enable;};
    
    void setParticleSpace(Space space) {_particleSpace = space;};
    void setTrailSpace(Space space) {_trailSpace = space;};
private:
    void fillBuffer(NodeProxy *node, MeshBuffer *buffer, const IARenderData& ia, RenderData* data);
    void fillTrailBuffer(NodeProxy *node, MeshBuffer *buffer, const IARenderData& ia, RenderData* data);
    
private:
    Space _particleSpace = Space::LOCAL;
    Space _trailSpace = Space::LOCAL;
    
    uint32_t _trailVertexBytes = 0;
    size_t _trailPosOffset = 0;
    bool _trailModuleEnable = false;
    
    VertexFormat* _trailVfmt = nullptr;
};

RENDERER_END
