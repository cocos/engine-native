#include "InstancedBuffer.h"
#include "gfx/GFXBuffer.h"
#include "gfx/GFXDevice.h"
#include "gfx/GFXInputAssembler.h"
#include "helper/SharedMemory.h"

namespace cc {
namespace pipeline {
map<const PassView *, std::shared_ptr<InstancedBuffer>> InstancedBuffer::_buffers;
std::shared_ptr<InstancedBuffer> &InstancedBuffer::get(const PassView *pass) {
    if (_buffers.find(pass) == _buffers.end()) {
        _buffers[pass] = std::shared_ptr<InstancedBuffer>(CC_NEW(InstancedBuffer(pass)), [](InstancedBuffer *ptr) { CC_SAFE_DELETE(ptr); });
    }
    return _buffers[pass];
}

InstancedBuffer::InstancedBuffer(const PassView *pass)
:_pass(pass){
}

InstancedBuffer::~InstancedBuffer() {
    destroy();
}

void InstancedBuffer::destroy() {
    for (auto &instance : _instancedItems) {
        instance.vb->destroy();
        instance.ia->destroy();
    }
    _instancedItems.clear();
}

void InstancedBuffer::merge(const ModelView *model, const SubModelView *subModel, uint passIdx) {
    size_t stride = 0;
    const auto instancedBuffer = model->getInstancedBuffer(stride);
    
    if (!stride) { return; } // we assume per-instance attributes are always present
    auto sourceIA = subModel->getIn
//    const lightingMap = subModel.descriptorSet.getTexture(UNIFORM_LIGHTMAP_TEXTURE_BINDING);
//    const hShader = SubModelPool.get(subModel.handle, SubModelView.SHADER_0 + passIdx) as ShaderHandle;
//    const hDescriptorSet = SubModelPool.get(subModel.handle, SubModelView.DESCRIPTOR_SET);
//    for (let i = 0; i < this.instances.length; ++i) {
//        const instance = this.instances[i];
//        if (instance.ia.indexBuffer !== sourceIA.indexBuffer || instance.count >= MAX_CAPACITY) { continue; }
//
//        // check same binding
//        if (instance.lightingMap !== lightingMap) {
//            continue;
//        }
//
//        if (instance.stride !== stride) {
//            // console.error(`instanced buffer stride mismatch! ${stride}/${instance.stride}`);
//            return;
//        }
//        if (instance.count >= instance.capacity) { // resize buffers
//            instance.capacity <<= 1;
//            const newSize = instance.stride * instance.capacity;
//            const oldData = instance.data;
//            instance.data = new Uint8Array(newSize);
//            instance.data.set(oldData);
//            instance.vb.resize(newSize);
//        }
//        if (instance.hShader !== hShader) { instance.hShader = hShader; }
//        if (instance.hDescriptorSet !== hDescriptorSet) { instance.hDescriptorSet = hDescriptorSet; }
//        instance.data.set(attrs.buffer, instance.stride * instance.count++);
//        this.hasPendingModels = true;
//        return;
//    }
//
//    // Create a new instance
//    const vb = this._device.createBuffer(new GFXBufferInfo(
//        GFXBufferUsageBit.VERTEX | GFXBufferUsageBit.TRANSFER_DST,
//        GFXMemoryUsageBit.HOST | GFXMemoryUsageBit.DEVICE,
//        stride * INITIAL_CAPACITY,
//        stride,
//    ));
//    const data = new Uint8Array(stride * INITIAL_CAPACITY);
//    const vertexBuffers = sourceIA.vertexBuffers.slice();
//    const attributes = sourceIA.attributes.slice();
//    const indexBuffer = sourceIA.indexBuffer;
//
//    for (let i = 0; i < attrs.list.length; i++) {
//        const attr = attrs.list[i];
//        const newAttr = new GFXAttribute(attr.name, attr.format, attr.isNormalized, vertexBuffers.length, true);
//        attributes.push(newAttr);
//    }
//    data.set(attrs.buffer);
//
//    vertexBuffers.push(vb);
//    const iaInfo = new GFXInputAssemblerInfo(attributes, vertexBuffers, indexBuffer);
//    const ia = this._device.createInputAssembler(iaInfo);
//    this.instances.push({ count: 1, capacity: INITIAL_CAPACITY, vb, data, ia, stride, hShader, hDescriptorSet, lightingMap});
//    this.hasPendingModels = true;
}

void InstancedBuffer::uploadBuffers() {
    for (auto &instance : _instancedItems) {
        if (!instance.count) continue;

        instance.vb->update(instance.data.get(), 0, instance.vb->getSize());
        instance.ia->setInstanceCount(instance.count);
    }
}

void InstancedBuffer::clear() {
    for (auto &instance : _instancedItems) {
        instance.count = 0;
    }
}

} // namespace pipeline
} // namespace cc
