/****************************************************************************
 Copyright (c) 2020-2021 Xiamen Yaji Software Co., Ltd.

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

#include "WGPUBuffer.h"
#include <webgpu/webgpu.h>
#include "WGPUDevice.h"
#include "WGPUObject.h"
#include "WGPUUtils.h"

namespace cc {
namespace gfx {

namespace anoymous {
CCWGPUBuffer *defaultBuffer = nullptr;
} // namespace anoymous

using namespace emscripten;

CCWGPUBuffer::CCWGPUBuffer() : wrapper<Buffer>(val::object()) {
}

void CCWGPUBuffer::doInit(const BufferInfo &info) {
    _gpuBufferObject = CC_NEW(CCWGPUBufferObject);

    if (hasFlag(_usage, BufferUsageBit::INDIRECT)) {
        size_t drawInfoCount = _size / sizeof(DrawInfo);
        _gpuBufferObject->indexedIndirectObjs.resize(drawInfoCount);
        _gpuBufferObject->indirectObjs.resize(drawInfoCount);
    }

    _size = ceil(info.size / 4.0) * 4;

    WGPUBufferDescriptor descriptor = {
        .nextInChain      = nullptr,
        .label            = nullptr,
        .usage            = toWGPUBufferUsage(info.usage),
        .size             = _size,
        .mappedAtCreation = false, //hasFlag(info.memUsage, MemoryUsageBit::DEVICE),
    };

    _gpuBufferObject->mapped = descriptor.mappedAtCreation;

    if (info.memUsage == MemoryUsage::DEVICE) {
        descriptor.usage |= WGPUBufferUsage_CopyDst;
    } else if (info.memUsage == MemoryUsage::HOST) {
        descriptor.usage |= WGPUBufferUsage_CopySrc;
    } else if (info.memUsage == (MemoryUsage::HOST | MemoryUsage::DEVICE)) {
        descriptor.usage |= WGPUBufferUsage_CopySrc | WGPUBufferUsage_CopyDst;
    }

    _gpuBufferObject->wgpuBuffer = wgpuDeviceCreateBuffer(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &descriptor);
} // namespace gfx

void CCWGPUBuffer::doInit(const BufferViewInfo &info) {
    _gpuBufferObject             = CC_NEW(CCWGPUBufferObject);
    _gpuBufferObject->wgpuBuffer = static_cast<CCWGPUBuffer *>(info.buffer)->gpuBufferObject()->wgpuBuffer;
}

void CCWGPUBuffer::doDestroy() {
    if (_gpuBufferObject) {
        if (_gpuBufferObject->wgpuBuffer) {
            wgpuBufferDestroy(_gpuBufferObject->wgpuBuffer);
        }
        CC_DELETE(_gpuBufferObject);
    }
}

void CCWGPUBuffer::doResize(uint size, uint count) {
    if (_isBufferView) {
        CC_LOG_ERROR("Resize is not support on buffer view!");
        return;
    }
    if (_gpuBufferObject->wgpuBuffer) {
        wgpuBufferDestroy(_gpuBufferObject->wgpuBuffer);
    }

    if (hasFlag(_usage, BufferUsageBit::INDIRECT)) {
        const size_t drawInfoCount = _size / sizeof(DrawInfo);
        _gpuBufferObject->indexedIndirectObjs.resize(drawInfoCount);
        _gpuBufferObject->indirectObjs.resize(drawInfoCount);
    }

    _size = ceil(size / 4.0) * 4;

    WGPUBufferDescriptor descriptor = {
        .nextInChain      = nullptr,
        .label            = nullptr,
        .usage            = toWGPUBufferUsage(_usage),
        .size             = _size,
        .mappedAtCreation = false, //hasFlag(_memUsage, MemoryUsageBit::DEVICE),
    };
    _gpuBufferObject->wgpuBuffer = wgpuDeviceCreateBuffer(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &descriptor);
} // namespace gfx

void bufferUpdateCallback(WGPUBufferMapAsyncStatus status, void *userdata) {
    if (status == WGPUBufferMapAsyncStatus_Success) {
        wgpuBufferUnmap(static_cast<WGPUBuffer>(userdata));
    }
}

void CCWGPUBuffer::update(const void *buffer, uint size) {
    // if (_memUsage & MemoryUsageBit::DEVICE) {
    //     auto *mappedBuffer = wgpuBufferGetMappedRange(_gpuBufferObject->wgpuBuffer, 0, size);
    //     memcpy(mappedBuffer, buffer, size);
    //     size_t offset = _isBufferView ? _offset : 0;
    //     wgpuBufferMapAsync(_gpuBufferObject->wgpuBuffer, WGPUMapMode_Write, offset, size, bufferUpdateCallback, _gpuBufferObject->wgpuBuffer);
    // } else {
    //     WGPUBufferDescriptor descriptor = {
    //         .nextInChain      = nullptr,
    //         .label            = nullptr,
    //         .usage            = toWGPUBufferUsage(_info.usage),
    //         .size             = size,
    //         .mappedAtCreation = true,
    //     };
    //     WGPUBuffer stagingBuffer = wgpuDeviceCreateBuffer(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuDevice, &descriptor);
    //     auto *     mappedBuffer  = wgpuBufferGetMappedRange(stagingBuffer, 0, size);
    //     memcpy(mappedBuffer, buffer, size);
    //     wgpuBufferMapAsync(mappedBuffer, WGPUMapMode_Write, 0, size, bufferUpdateCallback, mappedBuffer);
    // }

    size_t      offset      = _isBufferView ? _offset : 0;
    void const *data        = buffer;
    uint32_t    alignedSize = ceil(size / 4.0) * 4;
    size_t      buffSize    = alignedSize;
    if (hasFlag(_usage, BufferUsageBit::INDIRECT)) {
        size_t drawInfoCount = size / (sizeof(DrawInfo));
        auto * drawInfos     = static_cast<const DrawInfo *>(buffer);

        if (drawInfoCount > 0) {
            if (drawInfos[0].indexCount) {
                auto &indexedIndirectObjs = _gpuBufferObject->indexedIndirectObjs;
                for (size_t i = 0; i < drawInfoCount; i++) {
                    indexedIndirectObjs[i].indexCount    = drawInfos[i].indexCount;
                    indexedIndirectObjs[i].instanceCount = drawInfos[i].instanceCount /*  ? drawInfos[i]->instanceCoun : 1 */;
                    indexedIndirectObjs[i].firstIndex    = drawInfos[i].firstIndex;
                    indexedIndirectObjs[i].baseVertex    = drawInfos[i].vertexOffset;
                    indexedIndirectObjs[i].firstInstance = 0; //check definition of indexedIndirectObj;
                    drawInfos++;
                }
                data     = indexedIndirectObjs.data();
                buffSize = indexedIndirectObjs.size() * sizeof(CCWGPUDrawIndexedIndirectObject);
            } else {
                auto &indirectObjs = _gpuBufferObject->indirectObjs;
                for (size_t i = 0; i < drawInfoCount; i++) {
                    indirectObjs[i].vertexCount   = drawInfos[i].vertexCount;
                    indirectObjs[i].instanceCount = drawInfos[i].instanceCount;
                    indirectObjs[i].firstIndex    = drawInfos[i].firstIndex;
                    indirectObjs[i].firstInstance = 0; // check definition of indirectObj;
                    drawInfos++;
                }
                data     = indirectObjs.data();
                buffSize = indirectObjs.size() * sizeof(CCWGPUDrawIndirectObject);
            }
        }
    }
    wgpuQueueWriteBuffer(CCWGPUDevice::getInstance()->gpuDeviceObject()->wgpuQueue, _gpuBufferObject->wgpuBuffer, offset, data, buffSize);
    wgpuBufferUnmap(_gpuBufferObject->wgpuBuffer);
}

void CCWGPUBuffer::check() {
    if (_gpuBufferObject->mapped) {
        wgpuBufferUnmap(_gpuBufferObject->wgpuBuffer);
        _gpuBufferObject->mapped = false;
    }
}

CCWGPUBuffer *CCWGPUBuffer::defaultBuffer() {
    if (!anoymous::defaultBuffer) {
        BufferInfo info = {
            .usage    = BufferUsageBit::NONE,
            .memUsage = MemoryUsageBit::NONE,
            .size     = 2,
            .flags    = BufferFlagBit::NONE,
        };
        anoymous::defaultBuffer = CC_NEW(CCWGPUBuffer);
        anoymous::defaultBuffer->initialize(info);
    }
    return anoymous::defaultBuffer;
}

} // namespace gfx
} // namespace cc
