#ifndef CC_GFXCCVK_GPU_OBJECTS_H_
#define CC_GFXCCVK_GPU_OBJECTS_H_

#include "volk.h"

NS_CC_BEGIN

class CCVKGPUDevice : public Object
{
public:
    VkDevice vkDevice{ VK_NULL_HANDLE };
    std::vector<VkLayerProperties> layers;
    std::vector<VkExtensionProperties> extensions;
    uint32_t curImageIndex = 0;
    VkSwapchainKHR vkSwapchain = VK_NULL_HANDLE;
    std::vector<VkSemaphore> vkSemaphores;
};

class CCVKGPUContext
{
public:
    VkInstance vkInstance = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT vkDebugUtilsMessenger = VK_NULL_HANDLE;
    VkDebugReportCallbackEXT vkDebugReport = VK_NULL_HANDLE;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkPhysicalDeviceFeatures physicalDeviceFeatures{};
    VkPhysicalDeviceProperties physicalDeviceProperties{};
    VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties{};
    std::vector<VkQueueFamilyProperties> queueFamilyProperties;
    std::vector<VkBool32> queueFamilyPresentables;

    VkSurfaceKHR vkSurface = VK_NULL_HANDLE;

    VkSwapchainCreateInfoKHR swapchainCreateInfo{ VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR };
};

class CCVKGPUCommandPool : public Object
{
public:
    VkCommandPool vkCommandPool{ VK_NULL_HANDLE };
};

class CCVKGPUQueue : public Object
{
public:
    GFXQueueType type;
    VkQueue vkQueue;
    uint32_t queueFamilyIndex;
};

class CCVKGPUBuffer : public Object
{
public:
    GFXBufferUsage usage = GFXBufferUsage::NONE;
    GFXMemoryUsage memUsage = GFXMemoryUsage::NONE;
    uint size = 0;
    uint stride = 0;
    uint count = 0;
    //GLenum glTarget = 0;
    //GLuint glBuffer = 0;
    uint8_t* buffer = nullptr;
    GFXDrawInfoList indirects;
};
typedef vector<CCVKGPUBuffer*>::type CCVKGPUBufferList;

class CCVKGPUTexture : public Object
{
public:
    GFXTextureType type = GFXTextureType::TEX2D;
    GFXTextureViewType viewType = GFXTextureViewType::TV2D;
    GFXFormat format = GFXFormat::UNKNOWN;
    GFXTextureUsage usage = GFXTextureUsageBit::NONE;
    uint width = 0;
    uint height = 0;
    uint depth = 1;
    uint size = 0;
    uint arrayLayer = 1;
    uint mipLevel = 1;
    GFXSampleCount samples = GFXSampleCount::X1;
    GFXTextureFlags flags = GFXTextureFlagBit::NONE;
    bool isPowerOf2 = false;
    VkImage vkImage = VK_NULL_HANDLE;
    VkDeviceMemory vkDeviceMemory = VK_NULL_HANDLE;
    //GLenum glTarget = 0;
    //GLenum glInternelFmt = 0;
    //GLenum glFormat = 0;
    //GLenum glType = 0;
    //GLenum glUsage = 0;
    //GLuint glTexture = 0;
    //GLenum glWrapS = 0;
    //GLenum glWrapT = 0;
    //GLenum glMinFilter = 0;
    //GLenum glMagFilter = 0;
};

class CCVKGPUTextureView : public Object
{
public:
    CCVKGPUTexture* gpuTexture = nullptr;
    GFXTextureViewType type = GFXTextureViewType::TV2D;
    GFXFormat format = GFXFormat::UNKNOWN;
    uint baseLevel = 0;
    uint levelCount = 1;
    VkImageView vkImageView = VK_NULL_HANDLE;
};

typedef vector<CCVKGPUTextureView*>::type CCVKGPUTextureViewList;

class CCVKGPUSampler : public Object {
 public:
  GFXFilter minFilter = GFXFilter::NONE;
  GFXFilter magFilter = GFXFilter::NONE;
  GFXFilter mipFilter = GFXFilter::NONE;
  GFXAddress addressU = GFXAddress::CLAMP;
  GFXAddress addressV = GFXAddress::CLAMP;
  GFXAddress addressW = GFXAddress::CLAMP;
  uint minLOD = 0;
  uint maxLOD = 1000;
  //GLuint gl_sampler = 0;
  //GLenum glMinFilter = 0;
  //GLenum glMagFilter = 0;
  //GLenum glWrapS = 0;
  //GLenum glWrapT = 0;
  //GLenum glWrapR = 0;
};

struct CCVKGPUInput
{
    uint binding = 0;
    String name;
    GFXType type = GFXType::UNKNOWN;
    uint stride = 0;
    uint count = 0;
    uint size = 0;
    //GLenum glType = 0;
    //GLint glLoc = -1;
};
typedef vector<CCVKGPUInput>::type CCVKGPUInputList;

struct CCVKGPUUniform
{
    uint binding = GFX_INVALID_BINDING;
    String name;
    GFXType type = GFXType::UNKNOWN;
    uint stride = 0;
    uint count = 0;
    uint size = 0;
    uint offset = 0;
    //GLenum glType = 0;
    //GLint glLoc = -1;
};
typedef vector<CCVKGPUUniform>::type CCVKGPUUniformList;

struct CCVKGPUUniformBlock
{
    uint binding = 0;
    uint idx = 0;
    String name;
    uint size = 0;
    CCVKGPUUniformList glUniforms;
    CCVKGPUUniformList glActiveUniforms;
};
typedef vector<CCVKGPUUniformBlock>::type CCVKGPUUniformBlockList;

struct CCVKGPUUniformSampler
{
    uint binding = 0;
    String name;
    GFXType type = GFXType::UNKNOWN;
    vector<int>::type units;
    //GLenum glType = 0;
    //GLint glLoc = -1;
};
typedef vector<CCVKGPUUniformSampler>::type CCVKGPUUniformSamplerList;

struct CCVKGPUShaderStage
{
    CCVKGPUShaderStage(GFXShaderType t, String s, GFXShaderMacroList m)
        : type(t)
        , source(s)
        , macros(m)
        //, glShader(shader)
    {
    }
    GFXShaderType type;
    String source;
    GFXShaderMacroList macros;
    //GLuint glShader = 0;
};
typedef vector<CCVKGPUShaderStage>::type CCVKGPUShaderStageList;

class CCVKGPUShader : public Object
{
public:
    String name;
    GFXUniformBlockList blocks;
    GFXUniformSamplerList samplers;
    //GLuint glProgram = 0;
    CCVKGPUShaderStageList gpuStages;
    CCVKGPUInputList glInputs;
    CCVKGPUUniformBlockList glBlocks;
    CCVKGPUUniformSamplerList glSamplers;
};

struct CCVKGPUAttribute
{
    String name;
    //GLuint glBuffer = 0;
    //GLenum glType = 0;
    uint size = 0;
    uint count = 0;
    uint stride = 1;
    uint componentCount = 1;
    bool isNormalized = false;
    bool isInstanced = false;
    uint offset = 0;
};
typedef vector<CCVKGPUAttribute>::type CCVKGPUAttributeList;

class CCVKGPUInputAssembler : public Object
{
public:
    GFXAttributeList attributes;
    CCVKGPUBufferList gpuVertexBuffers;
    CCVKGPUBuffer* gpuIndexBuffer = nullptr;
    CCVKGPUBuffer* gpuIndirectBuffer = nullptr;
    CCVKGPUAttributeList glAttribs;
    //GLenum glIndexType = 0;
    //map<GLuint, GLuint>::type glVAOs;
};

class CCVKGPURenderPass : public Object
{
public:
    GFXColorAttachmentList colorAttachments;
    GFXDepthStencilAttachment depthStencilAttachment;
    GFXSubPassList subPasses;
    VkRenderPass vkRenderPass;
};

class CCVKGPUFramebuffer : public Object
{
public:
    CCVKGPURenderPass* gpuRenderPass = nullptr;
    CCVKGPUTextureViewList gpuColorViews;
    CCVKGPUTextureView* gpuDepthStencilView = nullptr;
    bool isOffscreen = false;
    VkFramebuffer vkFramebuffer = VK_NULL_HANDLE;
};

class CCVKGPUPipelineLayout : public Object
{
public:
};

class CCVKGPUPipelineState : public Object
{
public:
    //GLenum glPrimitive = GL_TRIANGLES;
    CCVKGPUShader* gpuShader = nullptr;
    GFXRasterizerState rs;
    GFXDepthStencilState dss;
    GFXBlendState bs;
    GFXDynamicStateList dynamicStates;
    CCVKGPUPipelineLayout* gpuLayout = nullptr;
    CCVKGPURenderPass* gpuRenderPass = nullptr;
};

struct CCVKGPUBinding
{
    uint binding = GFX_INVALID_BINDING;
    GFXBindingType type = GFXBindingType::UNKNOWN;
    String name;
    CCVKGPUBuffer* gpuBuffer = nullptr;
    CCVKGPUTextureView* gpuTexView = nullptr;
    CCVKGPUSampler* gpuSampler = nullptr;
};
typedef vector<CCVKGPUBinding>::type CCVKGPUBindingList;

class CCVKGPUBindingLayout : public Object
{
public:
    CCVKGPUBindingList gpuBindings;
};

NS_CC_END

#endif
