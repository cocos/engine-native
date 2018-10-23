/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
#include "IOBuffer.hpp"

namespace cocos2d{

IOBuffer::IOBuffer(se::Object::TypedArrayType arrayType):_bufferSize(40960),
_curPos(0),
_readPos(0),
_arrayType(arrayType){
    _typeArray = se::Object::createTypedArray(_arrayType, nullptr, _bufferSize);
    _typeArray->root();
    _typeArray->getTypedArrayData(&_buffer, (size_t*)&_bufferSize);
}

IOBuffer::~IOBuffer(){
    _typeArray->unroot();
    _typeArray->decRef();
}

void IOBuffer::writeUint32(int pos,uint32_t val){
    if(_bufferSize<pos+sizeof(uint32_t)){
        CCLOG("se::IOBuffer writeUint32 has out of range");
        return;
    }
    uint32_t* pBuffer = (uint32_t*)(_buffer+pos);
    *pBuffer = val;
}

void IOBuffer::writeBytes(const char* bytes,int bytesLen){
    checkSpace(bytesLen);
    memcpy(_buffer+_curPos,bytes,bytesLen);
    _curPos+=bytesLen;
}

void IOBuffer::writeUint32(uint32_t val){
    checkSpace(sizeof(uint32_t));
    uint32_t* pBuffer = (uint32_t*)(_buffer+_curPos);
    *pBuffer = val;
    _curPos+=sizeof(uint32_t);
}

void IOBuffer::writeFloat32(int pos,float val){
    if(_bufferSize<pos+sizeof(float)){
        CCLOG("se::IOBuffer writeFloat32 has out of range");
        return;
    }
    float* pBuffer = (float*)(_buffer+pos);
    *pBuffer = val;
}

void IOBuffer::writeFloat32(float val){
    checkSpace(sizeof(float));
    float* pBuffer = (float*)(_buffer+_curPos);
    *pBuffer = val;
    _curPos+=sizeof(float);
}

void IOBuffer::writeUint16(uint16_t val){
    checkSpace(sizeof(uint16_t));
    uint16_t* pBuffer = (uint16_t*)(_buffer+_curPos);
    *pBuffer = val;
    _curPos+=sizeof(uint16_t);
}

uint32_t IOBuffer::getUint32(){
    uint32_t* pBuffer = (uint32_t*)(_buffer+_readPos);
    _readPos+=sizeof(uint32_t);
    return *pBuffer;
}

uint16_t IOBuffer::getUint16(){
    uint16_t* pBuffer = (uint16_t*)(_buffer+_readPos);
    _readPos+=sizeof(uint16_t);
    return *pBuffer;
}

float IOBuffer::getFloat32(){
    float* pBuffer = (float*)(_buffer+_readPos);
    _readPos+=sizeof(float);
    return *pBuffer;
}

char IOBuffer::getUint8(){
    char* pBuffer = (char*)(_buffer+_readPos);
    _readPos+=sizeof(char);
    return *pBuffer;
}

void IOBuffer::reset(){
    _curPos = 0;
    _readPos = 0;
}

se::Object* IOBuffer::getTypeArray(){
    return _typeArray;
}

int IOBuffer::length(){
    return _curPos;
}

int IOBuffer::getCurPos(){
    return _curPos;
}

void IOBuffer::checkSpace(int needLen){
    int hasLen = _bufferSize - _curPos;
    if(hasLen<needLen){
        int addLen = needLen - hasLen + 128;
        int newLen = _bufferSize + addLen;
        se::Object* newTypeBuffer = se::Object::createTypedArray(_arrayType, nullptr, newLen);
        newTypeBuffer->root();
        
        uint8_t* newBuffer = nullptr;
        newTypeBuffer->getTypedArrayData(&newBuffer, (size_t*)&newLen);
        memcpy(newBuffer, _buffer, _bufferSize);
        
        _typeArray->unroot();
        _typeArray->decRef();
        
        _typeArray = newTypeBuffer;
        _buffer = newBuffer;
        _bufferSize = newLen;
    }
}
    
}
