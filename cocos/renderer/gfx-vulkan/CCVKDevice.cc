#include "CCVKStd.h"
#include "CCVKDevice.h"
#include "CCVKStateCache.h"
#include "CCVKContext.h"
#include "CCVKWindow.h"
#include "CCVKQueue.h"
#include "CCVKCommandAllocator.h"
#include "CCVKCommandBuffer.h"
#include "CCVKBuffer.h"
#include "CCVKTexture.h"
#include "CCVKTextureView.h"
#include "CCVKSampler.h"
#include "CCVKShader.h"
#include "CCVKInputAssembler.h"
#include "CCVKRenderPass.h"
#include "CCVKFramebuffer.h"
#include "CCVKBindingLayout.h"
#include "CCVKPipelineLayout.h"
#include "CCVKPipelineState.h"

NS_CC_BEGIN

CCVKDevice::CCVKDevice()
{
}

CCVKDevice::~CCVKDevice()
{
}

bool CCVKDevice::initialize(const GFXDeviceInfo& info)
{
    _gfxAPI = GFXAPI::VULKAN;
    _deviceName = "Vulkan";
    _width = info.width;
    _height = info.height;
    _nativeWidth = info.nativeWidth;
    _nativeHeight = info.nativeHeight;
    _windowHandle = info.windowHandle;

    stateCache = CC_NEW(CCVKStateCache);

    GFXContextInfo ctx_info;
    ctx_info.windowHandle = _windowHandle;
    ctx_info.sharedCtx = info.sharedCtx;

    _context = CC_NEW(CCVKContext(this));
    if (!_context->initialize(ctx_info))
    {
        destroy();
        return false;
    }

    String extStr = (const char*)glGetString(GL_EXTENSIONS);
    _extensions = StringUtil::Split(extStr, " ");

    _features[(int)GFXFeature::TEXTURE_FLOAT] = true;
    _features[(int)GFXFeature::TEXTURE_HALF_FLOAT] = true;
    _features[(int)GFXFeature::FORMAT_R11G11B10F] = true;
    _features[(int)GFXFeature::FORMAT_D24S8] = true;
    _features[(int)GFXFeature::MSAA] = true;
    _features[(int)GFXFeature::INSTANCED_ARRAYS] = true;

    if (checkExtension("color_buffer_float"))
        _features[(int)GFXFeature::COLOR_FLOAT] = true;
    
    if (checkExtension("color_buffer_half_float"))
        _features[(int)GFXFeature::COLOR_HALF_FLOAT] = true;
    
    if (checkExtension("texture_float_linear"))
        _features[(int)GFXFeature::TEXTURE_FLOAT_LINEAR] = true;
    
    if (checkExtension("texture_half_float_linear"))
        _features[(int)GFXFeature::TEXTURE_HALF_FLOAT_LINEAR] = true;

    String compressed_fmts;

    if (checkExtension("compressed_ETC1"))
    {
        _features[(int)GFXFeature::FORMAT_ETC1] = true;
        compressed_fmts += "etc1 ";
    }

    _features[(int)GFXFeature::FORMAT_ETC2] = true;
    compressed_fmts += "etc2 ";

    if (checkExtension("texture_compression_pvrtc"))
    {
        _features[(int)GFXFeature::FORMAT_PVRTC] = true;
        compressed_fmts += "pvrtc ";
    }

    if (checkExtension("texture_compression_astc"))
    {
        _features[(int)GFXFeature::FORMAT_ASTC] = true;
        compressed_fmts += "astc ";
    }

    _renderer = (const char*)glGetString(GL_RENDERER);
    _vendor = (const char*)glGetString(GL_VENDOR);
    _version = (const char*)glGetString(GL_VERSION);

    CC_LOG_INFO("RENDERER: %s", _renderer.c_str());
    CC_LOG_INFO("VENDOR: %s", _vendor.c_str());
    CC_LOG_INFO("VERSION: %s", _version.c_str());
    CC_LOG_INFO("SCREEN_SIZE: %d x %d", _width, _height);
    CC_LOG_INFO("NATIVE_SIZE: %d x %d", _nativeWidth, _nativeHeight);
    CC_LOG_INFO("USE_VAO: %s", _useVAO ? "true" : "false");
    CC_LOG_INFO("COMPRESSED_FORMATS: %s", compressed_fmts.c_str());

    GFXWindowInfo window_info;
    window_info.colorFmt = _context->getColorFormat();
    window_info.depthStencilFmt = _context->getDepthStencilFormat();
    window_info.isOffscreen = false;
    _window = createWindow(window_info);

    GFXQueueInfo queue_info;
    queue_info.type = GFXQueueType::GRAPHICS;
    _queue = createQueue(queue_info);

    GFXCommandAllocatorInfo cmd_alloc_info;
    _cmdAllocator = createCommandAllocator(cmd_alloc_info);

    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_maxVertexAttributes);
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &_maxVertexUniformVectors);
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &_maxFragmentUniformVectors);
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &_maxTextureUnits);
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &_maxVertexTextureUnits);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTextureSize);
    glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &_maxCubeMapTextureSize);
    glGetIntegerv(GL_DEPTH_BITS, &_depthBits);
    glGetIntegerv(GL_STENCIL_BITS, &_stencilBits);
    glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &_maxCubeMapTextureSize);

    return true;
}

void CCVKDevice::destroy()
{
    CC_SAFE_DESTROY(_cmdAllocator);
    CC_SAFE_DESTROY(_queue);
    CC_SAFE_DESTROY(_window);
    CC_SAFE_DESTROY(_context);
    CC_SAFE_DELETE(stateCache);
}

void CCVKDevice::resize(uint width, uint height)
{
  
}

void CCVKDevice::present()
{
    ((CCVKCommandAllocator*)_cmdAllocator)->releaseCmds();
    CCVKQueue* queue = (CCVKQueue*)_queue;
    _numDrawCalls = queue->_numDrawCalls;
    _numInstances = queue->_numInstances;
    _numTriangles = queue->_numTriangles;

    _context->present();

    // Clear queue stats
    queue->_numDrawCalls = 0;
    queue->_numInstances = 0;
    queue->_numTriangles = 0;
}

GFXWindow* CCVKDevice::createWindow(const GFXWindowInfo& info)
{
    GFXWindow* gfx_window = CC_NEW(CCVKWindow(this));
    if (gfx_window->initialize(info))
        return gfx_window;

    CC_SAFE_DESTROY(gfx_window);
    return nullptr;
}

GFXQueue* CCVKDevice::createQueue(const GFXQueueInfo& info)
{
    GFXQueue* gfx_queue = CC_NEW(CCVKQueue(this));
    if (gfx_queue->initialize(info))
        return gfx_queue;

    CC_SAFE_DESTROY(gfx_queue);
    return nullptr;
}

GFXCommandAllocator* CCVKDevice::createCommandAllocator(const GFXCommandAllocatorInfo& info)
{
    GFXCommandAllocator* gfx_cmd_allocator = CC_NEW(CCVKCommandAllocator(this));
    if (gfx_cmd_allocator->initialize(info))
        return gfx_cmd_allocator;

    CC_SAFE_DESTROY(gfx_cmd_allocator);
    return nullptr;
}

GFXCommandBuffer* CCVKDevice::createCommandBuffer(const GFXCommandBufferInfo& info)
{
    GFXCommandBuffer* gfx_cmd_buff = CC_NEW(CCVKCommandBuffer(this));
    if (gfx_cmd_buff->initialize(info))
        return gfx_cmd_buff;

    CC_SAFE_DESTROY(gfx_cmd_buff)
    return nullptr;
}

GFXBuffer* CCVKDevice::createBuffer(const GFXBufferInfo& info)
{
    GFXBuffer* gfx_buffer = CC_NEW(CCVKBuffer(this));
    if (gfx_buffer->initialize(info))
        return gfx_buffer;

    CC_SAFE_DESTROY(gfx_buffer);
    return nullptr;
}

GFXTexture* CCVKDevice::createTexture(const GFXTextureInfo& info)
{
    GFXTexture* gfx_texture = CC_NEW(CCVKTexture(this));
    if (gfx_texture->initialize(info))
        return gfx_texture;

    CC_SAFE_DESTROY(gfx_texture);
    return nullptr;
}

GFXTextureView* CCVKDevice::createTextureView(const GFXTextureViewInfo& info)
{
    GFXTextureView* gfx_tex_view = CC_NEW(CCVKTextureView(this));
    if (gfx_tex_view->initialize(info))
        return gfx_tex_view;

    CC_SAFE_DESTROY(gfx_tex_view);
    return nullptr;
}

GFXSampler* CCVKDevice::createSampler(const GFXSamplerInfo& info)
{
    GFXSampler* gfx_sampler = CC_NEW(CCVKSampler(this));
    if (gfx_sampler->initialize(info))
        return gfx_sampler;

    CC_SAFE_DESTROY(gfx_sampler);
    return nullptr;
}

GFXShader* CCVKDevice::createShader(const GFXShaderInfo& info)
{
    GFXShader* gfx_shader = CC_NEW(CCVKShader(this));
    if (gfx_shader->initialize(info))
        return gfx_shader;

    CC_SAFE_DESTROY(gfx_shader);
    return nullptr;
}

GFXInputAssembler* CCVKDevice::createInputAssembler(const GFXInputAssemblerInfo& info)
{
    GFXInputAssembler* gfx_input_assembler = CC_NEW(CCVKInputAssembler(this));
    if (gfx_input_assembler->initialize(info))
        return gfx_input_assembler;

    CC_SAFE_DESTROY(gfx_input_assembler);
    return nullptr;
}

GFXRenderPass* CCVKDevice::createRenderPass(const GFXRenderPassInfo& info)
{
    GFXRenderPass* gfx_render_pass = CC_NEW(CCVKRenderPass(this));
    if (gfx_render_pass->initialize(info))
        return gfx_render_pass;

    CC_SAFE_DESTROY(gfx_render_pass);
    return nullptr;
}

GFXFramebuffer* CCVKDevice::createFramebuffer(const GFXFramebufferInfo& info)
{
    GFXFramebuffer* gfx_framebuffer = CC_NEW(CCVKFramebuffer(this));
    if (gfx_framebuffer->initialize(info))
        return gfx_framebuffer;

    CC_SAFE_DESTROY(gfx_framebuffer);
    return nullptr;
}

GFXBindingLayout* CCVKDevice::createBindingLayout(const GFXBindingLayoutInfo& info)
{
    GFXBindingLayout* gfx_binding_layout = CC_NEW(CCVKBindingLayout(this));
    if (gfx_binding_layout->initialize(info))
        return gfx_binding_layout;

    CC_SAFE_DESTROY(gfx_binding_layout);
    return nullptr;
}


GFXPipelineState* CCVKDevice::createPipelineState(const GFXPipelineStateInfo& info)
{
    GFXPipelineState* pipelineState = CC_NEW(CCVKPipelineState(this));
    if (pipelineState->initialize(info))
        return pipelineState;

    CC_SAFE_DESTROY(pipelineState);
    return nullptr;
}

GFXPipelineLayout* CCVKDevice::createPipelineLayout(const GFXPipelineLayoutInfo& info)
{
    GFXPipelineLayout* layout = CC_NEW(CCVKPipelineLayout(this));
    if (layout->initialize(info))
        return layout;

    CC_SAFE_DESTROY(layout);
    return nullptr;
}

void CCVKDevice::copyBuffersToTexture(const GFXDataArray& buffers, GFXTexture* dst, const GFXBufferTextureCopyList& regions)
{
    
   CCVKCmdFuncCopyBuffersToTexture(this, buffers.datas.data(), ((CCVKTexture*)dst)->gpuTexture(), regions);
}

NS_CC_END
