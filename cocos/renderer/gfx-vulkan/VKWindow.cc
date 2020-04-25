#include "VKStd.h"
#include "VKWindow.h"
#include "VKCommands.h"
#include "VKTexture.h"

NS_CC_BEGIN

CCVKWindow::CCVKWindow(GFXDevice* device)
    : GFXWindow(device)
{
}

CCVKWindow::~CCVKWindow()
{
}

bool CCVKWindow::initialize(const GFXWindowInfo &info)
{
    _title = info.title;
    _left = info.left;
    _top = info.top;
    _width = info.width;
    _height = info.height;
    _nativeWidth = _width;
    _nativeHeight = _height;
    _colorFmt = info.colorFmt;
    _depthStencilFmt = info.depthStencilFmt;
    _isOffscreen = info.isOffscreen;
    _isFullscreen = info.isFullscreen;

    // Create render pass

    GFXRenderPassInfo renderPassInfo;

    GFXColorAttachment colorAttachment;
    colorAttachment.format = _colorFmt;
    colorAttachment.loadOp = GFXLoadOp::CLEAR;
    colorAttachment.storeOp = GFXStoreOp::STORE;
    colorAttachment.sampleCount = 1;
    colorAttachment.beginLayout = GFXTextureLayout::COLOR_ATTACHMENT_OPTIMAL;
    colorAttachment.endLayout = GFXTextureLayout::COLOR_ATTACHMENT_OPTIMAL;
    renderPassInfo.colorAttachments.emplace_back(colorAttachment);

    GFXDepthStencilAttachment& depthStencilAttachment = renderPassInfo.depthStencilAttachment;
    renderPassInfo.depthStencilAttachment.format = _depthStencilFmt;
    depthStencilAttachment.depthLoadOp = GFXLoadOp::CLEAR;
    depthStencilAttachment.depthStoreOp = GFXStoreOp::STORE;
    depthStencilAttachment.stencilLoadOp = GFXLoadOp::CLEAR;
    depthStencilAttachment.stencilStoreOp = GFXStoreOp::STORE;
    depthStencilAttachment.sampleCount = 1;
    depthStencilAttachment.beginLayout = GFXTextureLayout::DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    depthStencilAttachment.endLayout = GFXTextureLayout::DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    _renderPass = _device->createRenderPass(renderPassInfo);

    if (_depthStencilFmt != GFXFormat::UNKNOWN)
    {
        GFXTextureInfo depthStecnilTexInfo;
        depthStecnilTexInfo.type = GFXTextureType::TEX2D;
        depthStecnilTexInfo.usage = GFXTextureUsageBit::DEPTH_STENCIL_ATTACHMENT | GFXTextureUsageBit::SAMPLED;
        depthStecnilTexInfo.format = _depthStencilFmt;
        depthStecnilTexInfo.width = _width;
        depthStecnilTexInfo.height = _height;
        depthStecnilTexInfo.depth = 1;
        depthStecnilTexInfo.arrayLayer = 1;
        depthStecnilTexInfo.mipLevel = 1;
        _depthStencilTex = _device->createTexture(depthStecnilTexInfo);

        GFXTextureViewInfo depthStecnilTexViewInfo;
        depthStecnilTexViewInfo.texture = _depthStencilTex;
        depthStecnilTexViewInfo.type = GFXTextureViewType::TV2D;
        depthStecnilTexViewInfo.format = _depthStencilFmt;
        depthStecnilTexViewInfo.baseLevel = 0;
        depthStecnilTexViewInfo.levelCount = 1;
        depthStecnilTexViewInfo.baseLayer = 0;
        depthStecnilTexViewInfo.layerCount = 1;
        _depthStencilTexView = _device->createTextureView(depthStecnilTexViewInfo);
    }

    // Create texture & texture views
    if (_isOffscreen) {
        if (_colorFmt != GFXFormat::UNKNOWN)
        {
            GFXTextureInfo colorTexInfo;
            colorTexInfo.type = GFXTextureType::TEX2D;
            colorTexInfo.usage = GFXTextureUsageBit::COLOR_ATTACHMENT | GFXTextureUsageBit::SAMPLED;
            colorTexInfo.format = _colorFmt;
            colorTexInfo.width = _width;
            colorTexInfo.height = _height;
            colorTexInfo.depth = 1;
            colorTexInfo.arrayLayer = 1;
            colorTexInfo.mipLevel = 1;
            _colorTex = _device->createTexture(colorTexInfo);

            GFXTextureViewInfo colorTexViewInfo;
            colorTexViewInfo.texture = _colorTex;
            colorTexViewInfo.type = GFXTextureViewType::TV2D;
            colorTexViewInfo.format = _colorFmt;
            colorTexViewInfo.baseLevel = 0;
            colorTexViewInfo.levelCount = 1;
            colorTexViewInfo.baseLayer = 0;
            colorTexViewInfo.layerCount = 1;
            _colorTexView = _device->createTextureView(colorTexViewInfo);
        }

        GFXFramebufferInfo fboInfo;
        fboInfo.renderPass = _renderPass;
        if (_colorTexView)
        {
            fboInfo.colorViews.push_back(_colorTexView);
        }
        fboInfo.depthStencilView = _depthStencilTexView;
        fboInfo.isOffscreen = _isOffscreen;
        _framebuffer = _device->createFramebuffer(fboInfo);
    }
    else
    {
        std::vector<CCVKGPUTexture*> gpuTextures;
        CCVKCmdFuncGetSwapchainTextures((CCVKDevice*)_device, gpuTextures);
        for (auto gpuTexture : gpuTextures)
        {
            CCVKTexture* texture = CC_NEW(CCVKTexture(_device));
            gpuTexture->width = _width;
            gpuTexture->height = _height;
            gpuTexture->format = _colorFmt;
            texture->setSwapchainImage(gpuTexture);
            _swapchainTextures.push_back(texture);

            GFXTextureViewInfo textureViewInfo;
            textureViewInfo.texture = texture;
            textureViewInfo.type = GFXTextureViewType::TV2D;
            textureViewInfo.format = _colorFmt;
            textureViewInfo.baseLevel = 0;
            textureViewInfo.levelCount = 1;
            textureViewInfo.baseLayer = 0;
            textureViewInfo.layerCount = 1;
            GFXTextureView* textureView = _device->createTextureView(textureViewInfo);
            _swapchainTextureViews.push_back(textureView);

            GFXFramebufferInfo fboInfo;
            fboInfo.renderPass = _renderPass;
            fboInfo.colorViews.push_back(textureView);
            fboInfo.depthStencilView = _depthStencilTexView;
            fboInfo.isOffscreen = _isOffscreen;
            GFXFramebuffer* framebuffer = _device->createFramebuffer(fboInfo);
            _swapchainFramebuffers.push_back(framebuffer);
        }
    }
    
    _status = GFXStatus::SUCCESS;

    return true;
}

void CCVKWindow::destroy()
{
    for (auto framebuffer : _swapchainFramebuffers)
    {
        CC_SAFE_DESTROY(framebuffer);
    }
    _swapchainFramebuffers.clear();

    for (auto textureView : _swapchainTextureViews)
    {
        CC_SAFE_DESTROY(textureView);
    }
    _swapchainTextureViews.clear();

    for (auto texture : _swapchainTextures)
    {
        CC_SAFE_DESTROY(texture);
    }
    _swapchainTextures.clear();

    CC_SAFE_DESTROY(_renderPass);
    CC_SAFE_DESTROY(_colorTexView);
    CC_SAFE_DESTROY(_colorTex);
    CC_SAFE_DESTROY(_depthStencilTexView);
    CC_SAFE_DESTROY(_depthStencilTex);
    CC_SAFE_DESTROY(_framebuffer);

    _status = GFXStatus::UNREADY;
}

void CCVKWindow::resize(uint width, uint height)
{
    _width = width;
    _height = height;

    if (width > _nativeWidth || height > _nativeHeight)
    {
        _nativeWidth = width;
        _nativeHeight = height;

        if (_depthStencilTex)
        {
            _depthStencilTex->resize(width, height);
            _depthStencilTexView->destroy();

            GFXTextureViewInfo depthStencilTexViewInfo;
            depthStencilTexViewInfo.type = GFXTextureViewType::TV2D;
            depthStencilTexViewInfo.format = _depthStencilFmt;
            _depthStencilTexView->initialize(depthStencilTexViewInfo);
        }

        if (_isOffscreen)
        {
            if (_colorTex)
            {
                _colorTex->resize(width, height);
                _colorTexView->destroy();

                GFXTextureViewInfo colorTexViewInfo;
                colorTexViewInfo.type = GFXTextureViewType::TV2D;
                colorTexViewInfo.format = _colorFmt;
                _colorTexView->initialize(colorTexViewInfo);
            }

            if (_framebuffer)
            {
                _framebuffer->destroy();

                GFXFramebufferInfo fboInfo;
                fboInfo.isOffscreen = _isOffscreen;
                fboInfo.renderPass = _renderPass;
                fboInfo.colorViews.push_back(_colorTexView);
                fboInfo.depthStencilView = _depthStencilTexView;
                _framebuffer->initialize(fboInfo);
            }
        }
        else
        {
        }
    }
}

NS_CC_END
