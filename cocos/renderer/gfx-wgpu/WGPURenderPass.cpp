#include "WGPURenderPass.h"
#include <webgpu/webgpu.h>
#include "WGPUDevice.h"
#include "WGPUObject.h"
#include "WGPUUtils.h"

namespace cc {
namespace gfx {

using namespace emscripten;

class CCWGPURenderPassHelper {
public:
    explicit CCWGPURenderPassHelper(const RenderPassInfo& info) {
        for (size_t i = 0; i < info.colorAttachments.size(); i++) {
            colors[i].loadOp     = toWGPULoadOp(info.colorAttachments[i].loadOp);
            colors[i].storeOp    = toWGPUStoreOp(info.colorAttachments[i].storeOp);
            colors[i].clearColor = defaultClearColor;
        }

        // now 1 depth stencil only
        depthStencils[0].depthLoadOp     = toWGPULoadOp(info.depthStencilAttachment.depthLoadOp);
        depthStencils[0].depthStoreOp    = toWGPUStoreOp(info.depthStencilAttachment.depthStoreOp);
        depthStencils[0].stencilLoadOp   = toWGPULoadOp(info.depthStencilAttachment.stencilLoadOp);
        depthStencils[0].stencilStoreOp  = toWGPUStoreOp(info.depthStencilAttachment.stencilStoreOp);
        depthStencils[0].clearDepth      = defaultClearDepth;
        depthStencils[0].depthReadOnly   = false;
        depthStencils[0].stencilReadOnly = false;

        renderPassDesc = new WGPURenderPassDescriptor;

        //TODO_Zeqiang: Metal-like subpass
        renderPassDesc->colorAttachmentCount   = info.colorAttachments.size();
        renderPassDesc->colorAttachments       = colors.data();
        renderPassDesc->depthStencilAttachment = depthStencils.data();
    }

    ~CCWGPURenderPassHelper() {
        if (renderPassDesc) {
            delete renderPassDesc;
            renderPassDesc = nullptr;
        }
    }

    std::array<WGPURenderPassColorAttachment, CC_WGPU_MAX_ATTACHMENTS>        colors;
    std::array<WGPURenderPassDepthStencilAttachment, CC_WGPU_MAX_ATTACHMENTS> depthStencils;
    WGPURenderPassDescriptor*                                                 renderPassDesc = nullptr;
};

CCWGPURenderPass::CCWGPURenderPass() : wrapper<RenderPass>(val::object()) {
}

void CCWGPURenderPass::doInit(const RenderPassInfo& info) {
    _renderPassObject                 = new CCWGPURenderPassObject();
    _rpHelper                         = new CCWGPURenderPassHelper(info);
    _renderPassObject->renderPassDesc = _rpHelper->renderPassDesc;
}

void CCWGPURenderPass::doDestroy() {
    if (_renderPassObject) {
        delete _renderPassObject;
        _renderPassObject = nullptr;
    }
    if (_rpHelper) {
        delete _rpHelper;
        _rpHelper = nullptr;
    }
}

} // namespace gfx
} // namespace cc