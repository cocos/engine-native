#pragma once

#include "core/CoreStd.h"
#include "scripting/dop/BufferPool.h"

namespace cc {
namespace pipeline {

struct CC_DLL Pass {
    uint32_t priority = 0;
    uint32_t hash = 0;
    uint32_t phase = 0;
    
    const static se::BufferPool::Type type = se::BufferPool::Type::PASS_INFO;
};

struct CC_DLL Model {
    uint32_t isDynamicBatching = 0;
    uint32_t subModelsCount = 0;
    uint32_t subModelsID = 0;
    
    const static se::BufferPool::Type type = se::BufferPool::Type::MODEL_INFO;
};

struct CC_DLL SubModel {
    uint32_t priority = 0;
    uint32_t materialID = 0;
    uint32_t psociID = 0;
    uint32_t iaID = 0;
    
    uint32_t passesID = 0;
    uint32_t passesCount = 0;
    
    const static se::BufferPool::Type type = se::BufferPool::Type::SUBMODEL_INFO;
};

struct CC_DLL PipelineStateInfo {
    const static se::BufferPool::Type type = se::BufferPool::Type::PSOCI;
};

struct CC_DLL InputAssembler {
    const static se::BufferPool::Type type = se::BufferPool::Type::INPUT_ASSEMBLER_INFO;
};

#define GET_SUBMODLE(index, offset) (SharedMemory::get<SubModel>(index) + offset)
#define GET_PASS(index, offset) (SharedMemory::get<Pass>(index) + offset) //get pass from material

// TODO
//#define GET_PSOCI(index, offset) (SharedMemory::get<PipelineStateInfo>(index) + offset)
//#define GET_IA(index) (SharedMemory::get<InputAssembler>(index))
#define GET_PSOCI(index, offset) (static_cast<gfx::PipelineStateInfo*>(0))
#define GET_IA(index) (static_cast<gfx::InputAssembler*>(0))

class CC_DLL SharedMemory : public Object {
public:
    template <typename T>
    static T *get(uint index) {
        const auto &bufferMap = se::BufferPool::getPoolMap();
        if (bufferMap.count(T::type) != 0) {
            se::BufferPool *bufferPool = bufferMap.at(T::type);
            return bufferPool->getTypedObject<T>(index);
        }
        else {
            return nullptr;
        }
    }
    
private:
    template <typename T>
    static se::BufferPool::Type getBufferType() {
        
    }
};
} //namespace pipeline
} //namespace cc

