#pragma once
#include <webgpu/webgpu.h>
#include "cocos/base/Macros.h"
#include "gfx-base/GFXDef-common.h"
namespace cc {
namespace gfx {

static WGPULoadOp toWGPULoadOp(LoadOp op) {
    switch (op) {
        case LoadOp::CLEAR:
            return WGPULoadOp::WGPULoadOp_Clear;
        case LoadOp::LOAD:
            return WGPULoadOp::WGPULoadOp_Load;
        case LoadOp::DISCARD:
            return WGPULoadOp::WGPULoadOp_Force32;
        default:
            return WGPULoadOp::WGPULoadOp_Force32;
    }
}

static WGPUStoreOp toWGPUStoreOp(StoreOp op) {
    switch (op) {
        case StoreOp::STORE:
            return WGPUStoreOp::WGPUStoreOp_Store;
        case StoreOp::DISCARD:
            return WGPUStoreOp::WGPUStoreOp_Clear;
        default:
            return WGPUStoreOp::WGPUStoreOp_Force32;
    }
}

static constexpr WGPUColor defaultClearColor{0.2, 0.2, 0.2, 1.0};

static constexpr float defaultClearDepth = 1.0f;

} // namespace gfx
} // namespace cc