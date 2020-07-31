#include "RenderPipeline.h"
#include "RenderFlow.h"
#include "RenderView.h"
#include "renderer/core/gfx/GFXDevice.h"

namespace cc {
namespace pipeline {

bool RenderPipeline::initialize(const RenderPipelineInfo &info) {
    _isUsePostProcess = info.enableHDR;
    _isHDR = info.enableHDR;

    _isUseSMAA = info.enableSMAA;
    _isUseMSAA = info.enableMSAA;

    _renderTextureDescs = std::move(info.renderTextures);
    _framebufferDescs = std::move(info.framebuffers);
    _renderPassDescs = std::move(info.renderPasses);

    return true;
}

bool RenderPipeline::activate() {
    if (!initRenderResource()) {
        CC_LOG_ERROR("RenderPipeline: %s startup failed", _name.c_str());
        return false;
    }

    for (const auto &flow : _flows) {
        if (flow->getType() == RenderFlowType::SCENE) {
            flow->activate(this);
            activateFlow(flow);
        }
    }

    return true;
}

void RenderPipeline::render(RenderView *view) {
    for (const auto &flow : view->getFlows())
        flow->render(view);
}

bool RenderPipeline::initRenderResource() {
    if (_isUsePostProcess) {
        //TODO
    }

    if (_isHDR && _isHDRSupported) {
        //TODO
    }

    if (_isHDR) {
        //TODO
    }

    const auto device = gfx::Device::getInstance();
    _depthStencilFmt = device->getDepthStencilFormat();
    _shadingScale = 1.0f;
    _shadingWidth = device->getWidth();
    _shadingHeight = device->getHeight();

    for (const auto &rtd : _renderTextureDescs) {
        auto texture = device->createTexture({
            rtd.type,
            rtd.usage,
            getTextureFormat(rtd.format, rtd.usage),
            rtd.width == -1 ? _shadingWidth : rtd.width,
            rtd.height == -1 ? _shadingHeight : rtd.height,
        });

        if (!texture)
            return false;
        else
            _renderTextures[rtd.name] = texture;

        _textures[rtd.name] = device->createTexture({
            rtd.type,
            rtd.usage,
            getTextureFormat(rtd.format, rtd.usage),
            rtd.width == -1 ? _shadingWidth : rtd.width,
            rtd.height == -1 ? _shadingHeight : rtd.height,
        });
    }

    for (const auto &rpd : _renderPassDescs) {
        _renderPasses[rpd.index] = device->createRenderPass({rpd.colorAttachments,
                                                             rpd.depthStencilAttachment});
    }

    for (const auto &fbd : _framebufferDescs) {
        if (_renderPasses.count(fbd.renderPass) == 0) {
            CC_LOG_ERROR("RenderPass: %d not found", fbd.renderPass);
            return false;
        }
        const auto renderPass = _renderPasses[fbd.renderPass];
        
        vector<gfx::Texture *> ts;
        for (const auto &colorTexture : fbd.colorTextures) {
            if (_textures.count(colorTexture) == 0) {
                CC_LOG_ERROR("Texture: %s not found", colorTexture.c_str());
                return false;
            }
            ts.push_back(_textures[colorTexture]);
        }
        gfx::Texture *dsv = nullptr;
        if (_textures.count(fbd.depthStencilTexture) != 0) {
            dsv = _textures[fbd.depthStencilTexture];
        }
        _framebuffers[fbd.name] = device->createFramebuffer({
            renderPass,
            ts,
            {},
            dsv,
            0
        });
    }
    
    if (!createQuadInputAssembler())
        return false;
    
    if (!createUBOs())
        return false;
    
    gfx::ColorAttachment colorAttachment;
    gfx::DepthStencilAttachment depthStencilAttachment;
    colorAttachment.format = device->getColorFormat();
    depthStencilAttachment.format = device->getDepthStencilFormat();
    depthStencilAttachment.depthStoreOp = gfx::StoreOp::DISCARD;
    depthStencilAttachment.stencilStoreOp = gfx::StoreOp::DISCARD;
    gfx::RenderPass *windowPass = device->createRenderPass({
        {colorAttachment},
        depthStencilAttachment
    });
    addRenderPass(RenderPassStage::DEFAULT, windowPass);
    
    colorAttachment.loadOp = gfx::LoadOp::LOAD;
    colorAttachment.beginLayout = gfx::TextureLayout::PRESENT_SRC;
    gfx::RenderPass *uiPass = device->createRenderPass({
        {colorAttachment},
        depthStencilAttachment
    });
    addRenderPass(RenderPassStage::UI, uiPass);
    
    _commandBuffers.push_back(device->createCommandBuffer({
        device->getQueue(),
        gfx::CommandBufferType::PRIMARY,
    }));
    
    //TODO
//    _macros.CC_USE_HDR = _isHDR;
//    _macros.CC_SUPPORT_FLOAT_TEXTURE = device->hasFeature(gfx::Feature::TEXTURE_FLOAT);
    
    return true;
}

void RenderPipeline::addRenderPass(RenderPassStage stage, gfx::RenderPass *renderPass) {
    if (renderPass)
        _renderPasses[(uint)stage] = renderPass;
}

} // namespace pipeline
} // namespace cc
