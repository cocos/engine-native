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
#pragma once

#include "IOBuffer.h"
#include "IOTypedArray.h"
#include <vector>

MIDDLEWARE_BEGIN

class MeshBuffer
{
public:
    MeshBuffer(int vertexFormat);
    MeshBuffer(int vertexFormat, size_t indexSize, size_t vertexSize);

    virtual ~MeshBuffer();

    se_object_ptr getVBTypedArray(std::size_t bufferPos) {
        if (_vbArr.size() <= bufferPos) return nullptr;
        return _vbArr[bufferPos]->getTypeArray();
    }
    
    se_object_ptr getIBTypedArray(std::size_t bufferPos) {
        if (_ibArr.size() <= bufferPos) return nullptr;
        return _ibArr[bufferPos]->getTypeArray();
    }

	std::size_t getVBTypedArrayLength(std::size_t bufferPos) {
		if (_vbArr.size() <= bufferPos) return 0;
		return _vbArr[bufferPos]->length();
	}

	std::size_t getIBTypedArrayLength(std::size_t bufferPos) {
		if (_ibArr.size() <= bufferPos) return 0;
		return _ibArr[bufferPos]->length();
	}

	std::size_t getBufferCount() {
		return _bufferPos + 1;
	}
    
	std::size_t getBufferPos() {
		return _bufferPos;
	}

    IOBuffer& getVB() {
        return _vb;
    }
    
    IOBuffer& getIB() {
        return _ib;
    }
    
    void uploadVB();
    void uploadIB();
    void reset();
private:
    void next();
private:
    std::vector<IOTypedArray*> _ibArr;
    std::vector<IOTypedArray*> _vbArr;
    
    std::size_t _bufferPos = 0;
    IOBuffer _vb;
    IOBuffer _ib;
    int _vertexFormat = 0;
};

MIDDLEWARE_END
