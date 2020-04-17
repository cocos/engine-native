#include "scripting/js-bindings/auto/jsb_gfx_auto.hpp"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "renderer/core/Core.h"

#ifndef JSB_ALLOC
#define JSB_ALLOC(kls, ...) new (std::nothrow) kls(__VA_ARGS__)
#endif

#ifndef JSB_FREE
#define JSB_FREE(ptr) delete ptr
#endif


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXObjectType *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXObjectType>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXObjectType>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXObjectType(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("UNKNOWN", se::Value(0));
    enum_kls->setProperty("BUFFER", se::Value(1));
    enum_kls->setProperty("TEXTURE", se::Value(2));
    enum_kls->setProperty("TEXTURE_VIEW", se::Value(3));
    enum_kls->setProperty("RENDER_PASS", se::Value(4));
    enum_kls->setProperty("FRAMEBUFFER", se::Value(5));
    enum_kls->setProperty("SAMPLER", se::Value(6));
    enum_kls->setProperty("SHADER", se::Value(7));
    enum_kls->setProperty("PIPELINE_LAYOUT", se::Value(8));
    enum_kls->setProperty("PIPELINE_STATE", se::Value(9));
    enum_kls->setProperty("BINDING_LAYOUT", se::Value(10));
    enum_kls->setProperty("INPUT_ASSEMBLER", se::Value(11));
    enum_kls->setProperty("COMMAND_ALLOCATOR", se::Value(12));
    enum_kls->setProperty("COMMAND_BUFFER", se::Value(13));
    enum_kls->setProperty("QUEUE", se::Value(14));
    enum_kls->setProperty("WINDOW", se::Value(15));
    obj->setProperty("GFXObjectType", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXStatus *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXStatus>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXStatus>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXStatus(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("UNREADY", se::Value(0));
    enum_kls->setProperty("FAILED", se::Value(1));
    enum_kls->setProperty("SUCCESS", se::Value(2));
    obj->setProperty("GFXStatus", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXAPI *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXAPI>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXAPI>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXAPI(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("UNKNOWN", se::Value(0));
    enum_kls->setProperty("GL", se::Value(1));
    enum_kls->setProperty("GLES2", se::Value(2));
    enum_kls->setProperty("GLES3", se::Value(3));
    enum_kls->setProperty("METAL", se::Value(4));
    enum_kls->setProperty("VULKAN", se::Value(5));
    enum_kls->setProperty("DX12", se::Value(6));
    enum_kls->setProperty("WEBGL", se::Value(7));
    enum_kls->setProperty("WEBGL2", se::Value(8));
    obj->setProperty("GFXAPI", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXFeature *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXFeature>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXFeature>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXFeature(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("COLOR_FLOAT", se::Value(0));
    enum_kls->setProperty("COLOR_HALF_FLOAT", se::Value(1));
    enum_kls->setProperty("TEXTURE_FLOAT", se::Value(2));
    enum_kls->setProperty("TEXTURE_HALF_FLOAT", se::Value(3));
    enum_kls->setProperty("TEXTURE_FLOAT_LINEAR", se::Value(4));
    enum_kls->setProperty("TEXTURE_HALF_FLOAT_LINEAR", se::Value(5));
    enum_kls->setProperty("FORMAT_R11G11B10F", se::Value(6));
    enum_kls->setProperty("FORMAT_D24S8", se::Value(7));
    enum_kls->setProperty("FORMAT_ETC1", se::Value(8));
    enum_kls->setProperty("FORMAT_ETC2", se::Value(9));
    enum_kls->setProperty("FORMAT_DXT", se::Value(10));
    enum_kls->setProperty("FORMAT_PVRTC", se::Value(11));
    enum_kls->setProperty("FORMAT_ASTC", se::Value(12));
    enum_kls->setProperty("MSAA", se::Value(13));
    enum_kls->setProperty("ELEMENT_INDEX_UINT", se::Value(14));
    enum_kls->setProperty("INSTANCED_ARRAYS", se::Value(15));
    enum_kls->setProperty("COUNT", se::Value(16));
    obj->setProperty("GFXFeature", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXFormat *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXFormat>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXFormat>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXFormat(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("UNKNOWN", se::Value(0));
    enum_kls->setProperty("A8", se::Value(1));
    enum_kls->setProperty("L8", se::Value(2));
    enum_kls->setProperty("LA8", se::Value(3));
    enum_kls->setProperty("R8", se::Value(4));
    enum_kls->setProperty("R8SN", se::Value(5));
    enum_kls->setProperty("R8UI", se::Value(6));
    enum_kls->setProperty("R8I", se::Value(7));
    enum_kls->setProperty("R16F", se::Value(8));
    enum_kls->setProperty("R16UI", se::Value(9));
    enum_kls->setProperty("R16I", se::Value(10));
    enum_kls->setProperty("R32F", se::Value(11));
    enum_kls->setProperty("R32UI", se::Value(12));
    enum_kls->setProperty("R32I", se::Value(13));
    enum_kls->setProperty("RG8", se::Value(14));
    enum_kls->setProperty("RG8SN", se::Value(15));
    enum_kls->setProperty("RG8UI", se::Value(16));
    enum_kls->setProperty("RG8I", se::Value(17));
    enum_kls->setProperty("RG16F", se::Value(18));
    enum_kls->setProperty("RG16UI", se::Value(19));
    enum_kls->setProperty("RG16I", se::Value(20));
    enum_kls->setProperty("RG32F", se::Value(21));
    enum_kls->setProperty("RG32UI", se::Value(22));
    enum_kls->setProperty("RG32I", se::Value(23));
    enum_kls->setProperty("RGB8", se::Value(24));
    enum_kls->setProperty("SRGB8", se::Value(25));
    enum_kls->setProperty("RGB8SN", se::Value(26));
    enum_kls->setProperty("RGB8UI", se::Value(27));
    enum_kls->setProperty("RGB8I", se::Value(28));
    enum_kls->setProperty("RGB16F", se::Value(29));
    enum_kls->setProperty("RGB16UI", se::Value(30));
    enum_kls->setProperty("RGB16I", se::Value(31));
    enum_kls->setProperty("RGB32F", se::Value(32));
    enum_kls->setProperty("RGB32UI", se::Value(33));
    enum_kls->setProperty("RGB32I", se::Value(34));
    enum_kls->setProperty("RGBA8", se::Value(35));
    enum_kls->setProperty("BGRA8", se::Value(36));
    enum_kls->setProperty("SRGB8_A8", se::Value(37));
    enum_kls->setProperty("RGBA8SN", se::Value(38));
    enum_kls->setProperty("RGBA8UI", se::Value(39));
    enum_kls->setProperty("RGBA8I", se::Value(40));
    enum_kls->setProperty("RGBA16F", se::Value(41));
    enum_kls->setProperty("RGBA16UI", se::Value(42));
    enum_kls->setProperty("RGBA16I", se::Value(43));
    enum_kls->setProperty("RGBA32F", se::Value(44));
    enum_kls->setProperty("RGBA32UI", se::Value(45));
    enum_kls->setProperty("RGBA32I", se::Value(46));
    enum_kls->setProperty("R5G6B5", se::Value(47));
    enum_kls->setProperty("R11G11B10F", se::Value(48));
    enum_kls->setProperty("RGB5A1", se::Value(49));
    enum_kls->setProperty("RGBA4", se::Value(50));
    enum_kls->setProperty("RGB10A2", se::Value(51));
    enum_kls->setProperty("RGB10A2UI", se::Value(52));
    enum_kls->setProperty("RGB9E5", se::Value(53));
    enum_kls->setProperty("D16", se::Value(54));
    enum_kls->setProperty("D16S8", se::Value(55));
    enum_kls->setProperty("D24", se::Value(56));
    enum_kls->setProperty("D24S8", se::Value(57));
    enum_kls->setProperty("D32F", se::Value(58));
    enum_kls->setProperty("D32F_S8", se::Value(59));
    enum_kls->setProperty("BC1", se::Value(60));
    enum_kls->setProperty("BC1_ALPHA", se::Value(61));
    enum_kls->setProperty("BC1_SRGB", se::Value(62));
    enum_kls->setProperty("BC1_SRGB_ALPHA", se::Value(63));
    enum_kls->setProperty("BC2", se::Value(64));
    enum_kls->setProperty("BC2_SRGB", se::Value(65));
    enum_kls->setProperty("BC3", se::Value(66));
    enum_kls->setProperty("BC3_SRGB", se::Value(67));
    enum_kls->setProperty("BC4", se::Value(68));
    enum_kls->setProperty("BC4_SNORM", se::Value(69));
    enum_kls->setProperty("BC5", se::Value(70));
    enum_kls->setProperty("BC5_SNORM", se::Value(71));
    enum_kls->setProperty("BC6H_UF16", se::Value(72));
    enum_kls->setProperty("BC6H_SF16", se::Value(73));
    enum_kls->setProperty("BC7", se::Value(74));
    enum_kls->setProperty("BC7_SRGB", se::Value(75));
    enum_kls->setProperty("ETC_RGB8", se::Value(76));
    enum_kls->setProperty("ETC2_RGB8", se::Value(77));
    enum_kls->setProperty("ETC2_SRGB8", se::Value(78));
    enum_kls->setProperty("ETC2_RGB8_A1", se::Value(79));
    enum_kls->setProperty("ETC2_SRGB8_A1", se::Value(80));
    enum_kls->setProperty("ETC2_RGBA8", se::Value(81));
    enum_kls->setProperty("ETC2_SRGB8_A8", se::Value(82));
    enum_kls->setProperty("EAC_R11", se::Value(83));
    enum_kls->setProperty("EAC_R11SN", se::Value(84));
    enum_kls->setProperty("EAC_RG11", se::Value(85));
    enum_kls->setProperty("EAC_RG11SN", se::Value(86));
    enum_kls->setProperty("PVRTC_RGB2", se::Value(87));
    enum_kls->setProperty("PVRTC_RGBA2", se::Value(88));
    enum_kls->setProperty("PVRTC_RGB4", se::Value(89));
    enum_kls->setProperty("PVRTC_RGBA4", se::Value(90));
    enum_kls->setProperty("PVRTC2_2BPP", se::Value(91));
    enum_kls->setProperty("PVRTC2_4BPP", se::Value(92));
    enum_kls->setProperty("COUNT", se::Value(93));
    obj->setProperty("GFXFormat", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXFormatType *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXFormatType>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXFormatType>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXFormatType(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("NONE", se::Value(0));
    enum_kls->setProperty("UNORM", se::Value(1));
    enum_kls->setProperty("SNORM", se::Value(2));
    enum_kls->setProperty("UINT", se::Value(3));
    enum_kls->setProperty("INT", se::Value(4));
    enum_kls->setProperty("UFLOAT", se::Value(5));
    enum_kls->setProperty("FLOAT", se::Value(6));
    obj->setProperty("GFXFormatType", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXType *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXType>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXType>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXType(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("UNKNOWN", se::Value(0));
    enum_kls->setProperty("BOOL", se::Value(1));
    enum_kls->setProperty("BOOL2", se::Value(2));
    enum_kls->setProperty("BOOL3", se::Value(3));
    enum_kls->setProperty("BOOL4", se::Value(4));
    enum_kls->setProperty("INT", se::Value(5));
    enum_kls->setProperty("INT2", se::Value(6));
    enum_kls->setProperty("INT3", se::Value(7));
    enum_kls->setProperty("INT4", se::Value(8));
    enum_kls->setProperty("UINT", se::Value(9));
    enum_kls->setProperty("UINT2", se::Value(10));
    enum_kls->setProperty("UINT3", se::Value(11));
    enum_kls->setProperty("UINT4", se::Value(12));
    enum_kls->setProperty("FLOAT", se::Value(13));
    enum_kls->setProperty("FLOAT2", se::Value(14));
    enum_kls->setProperty("FLOAT3", se::Value(15));
    enum_kls->setProperty("FLOAT4", se::Value(16));
    enum_kls->setProperty("MAT2", se::Value(17));
    enum_kls->setProperty("MAT2X3", se::Value(18));
    enum_kls->setProperty("MAT2X4", se::Value(19));
    enum_kls->setProperty("MAT3X2", se::Value(20));
    enum_kls->setProperty("MAT3", se::Value(21));
    enum_kls->setProperty("MAT3X4", se::Value(22));
    enum_kls->setProperty("MAT4X2", se::Value(23));
    enum_kls->setProperty("MAT4X3", se::Value(24));
    enum_kls->setProperty("MAT4", se::Value(25));
    enum_kls->setProperty("SAMPLER1D", se::Value(26));
    enum_kls->setProperty("SAMPLER1D_ARRAY", se::Value(27));
    enum_kls->setProperty("SAMPLER2D", se::Value(28));
    enum_kls->setProperty("SAMPLER2D_ARRAY", se::Value(29));
    enum_kls->setProperty("SAMPLER3D", se::Value(30));
    enum_kls->setProperty("SAMPLER_CUBE", se::Value(31));
    enum_kls->setProperty("COUNT", se::Value(32));
    obj->setProperty("GFXType", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXBufferUsageBit *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXBufferUsageBit>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXBufferUsageBit>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXBufferUsageBit(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("NONE", se::Value(0));
    enum_kls->setProperty("TRANSFER_SRC", se::Value(1));
    enum_kls->setProperty("TRANSFER_DST", se::Value(2));
    enum_kls->setProperty("INDEX", se::Value(4));
    enum_kls->setProperty("VERTEX", se::Value(8));
    enum_kls->setProperty("UNIFORM", se::Value(16));
    enum_kls->setProperty("STORAGE", se::Value(32));
    enum_kls->setProperty("INDIRECT", se::Value(64));
    obj->setProperty("GFXBufferUsageBit", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXBufferFlagBit *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXBufferFlagBit>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXBufferFlagBit>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXBufferFlagBit(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("NONE", se::Value(0));
    enum_kls->setProperty("BAKUP_BUFFER", se::Value(4));
    obj->setProperty("GFXBufferFlagBit", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXBufferAccessBit *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXBufferAccessBit>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXBufferAccessBit>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXBufferAccessBit(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("NONE", se::Value(0));
    enum_kls->setProperty("READ", se::Value(1));
    enum_kls->setProperty("WRITE", se::Value(2));
    obj->setProperty("GFXBufferAccessBit", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXMemoryUsageBit *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXMemoryUsageBit>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXMemoryUsageBit>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXMemoryUsageBit(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("NONE", se::Value(0));
    enum_kls->setProperty("DEVICE", se::Value(1));
    enum_kls->setProperty("HOST", se::Value(2));
    obj->setProperty("GFXMemoryUsageBit", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXTextureType *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXTextureType>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXTextureType>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXTextureType(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("TEX1D", se::Value(0));
    enum_kls->setProperty("TEX2D", se::Value(1));
    enum_kls->setProperty("TEX3D", se::Value(2));
    obj->setProperty("GFXTextureType", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXTextureUsageBit *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXTextureUsageBit>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXTextureUsageBit>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXTextureUsageBit(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("NONE", se::Value(0));
    enum_kls->setProperty("TRANSFER_SRC", se::Value(1));
    enum_kls->setProperty("TRANSFER_DST", se::Value(2));
    enum_kls->setProperty("SAMPLED", se::Value(4));
    enum_kls->setProperty("STORAGE", se::Value(8));
    enum_kls->setProperty("COLOR_ATTACHMENT", se::Value(16));
    enum_kls->setProperty("DEPTH_STENCIL_ATTACHMENT", se::Value(32));
    enum_kls->setProperty("TRANSIENT_ATTACHMENT", se::Value(64));
    enum_kls->setProperty("INPUT_ATTACHMENT", se::Value(128));
    obj->setProperty("GFXTextureUsageBit", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXTextureFlagBit *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXTextureFlagBit>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXTextureFlagBit>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXTextureFlagBit(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("NONE", se::Value(0));
    enum_kls->setProperty("GEN_MIPMAP", se::Value(1));
    enum_kls->setProperty("CUBEMAP", se::Value(2));
    enum_kls->setProperty("BAKUP_BUFFER", se::Value(4));
    obj->setProperty("GFXTextureFlagBit", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXSampleCount *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXSampleCount>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXSampleCount>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXSampleCount(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("X1", se::Value(0));
    enum_kls->setProperty("X2", se::Value(1));
    enum_kls->setProperty("X4", se::Value(2));
    enum_kls->setProperty("X8", se::Value(3));
    enum_kls->setProperty("X16", se::Value(4));
    enum_kls->setProperty("X32", se::Value(5));
    enum_kls->setProperty("X64", se::Value(6));
    obj->setProperty("GFXSampleCount", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXTextureViewType *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXTextureViewType>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXTextureViewType>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXTextureViewType(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("TV1D", se::Value(0));
    enum_kls->setProperty("TV2D", se::Value(1));
    enum_kls->setProperty("TV3D", se::Value(2));
    enum_kls->setProperty("CUBE", se::Value(3));
    enum_kls->setProperty("TV1D_ARRAY", se::Value(4));
    enum_kls->setProperty("TV2D_ARRAY", se::Value(5));
    obj->setProperty("GFXTextureViewType", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXFilter *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXFilter>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXFilter>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXFilter(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("NONE", se::Value(0));
    enum_kls->setProperty("POINT", se::Value(1));
    enum_kls->setProperty("LINEAR", se::Value(2));
    enum_kls->setProperty("ANISOTROPIC", se::Value(3));
    obj->setProperty("GFXFilter", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXAddress *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXAddress>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXAddress>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXAddress(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("WRAP", se::Value(0));
    enum_kls->setProperty("MIRROR", se::Value(1));
    enum_kls->setProperty("CLAMP", se::Value(2));
    enum_kls->setProperty("BORDER", se::Value(3));
    obj->setProperty("GFXAddress", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXComparisonFunc *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXComparisonFunc>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXComparisonFunc>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXComparisonFunc(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("NEVER", se::Value(0));
    enum_kls->setProperty("LESS", se::Value(1));
    enum_kls->setProperty("EQUAL", se::Value(2));
    enum_kls->setProperty("LESS_EQUAL", se::Value(3));
    enum_kls->setProperty("GREATER", se::Value(4));
    enum_kls->setProperty("NOT_EQUAL", se::Value(5));
    enum_kls->setProperty("GREATER_EQUAL", se::Value(6));
    enum_kls->setProperty("ALWAYS", se::Value(7));
    obj->setProperty("GFXComparisonFunc", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXStencilOp *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXStencilOp>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXStencilOp>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXStencilOp(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("ZERO", se::Value(0));
    enum_kls->setProperty("KEEP", se::Value(1));
    enum_kls->setProperty("REPLACE", se::Value(2));
    enum_kls->setProperty("INCR", se::Value(3));
    enum_kls->setProperty("DECR", se::Value(4));
    enum_kls->setProperty("INVERT", se::Value(5));
    enum_kls->setProperty("INCR_WRAP", se::Value(6));
    enum_kls->setProperty("DECR_WRAP", se::Value(7));
    obj->setProperty("GFXStencilOp", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXBlendFactor *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXBlendFactor>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXBlendFactor>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXBlendFactor(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("ZERO", se::Value(0));
    enum_kls->setProperty("ONE", se::Value(1));
    enum_kls->setProperty("SRC_ALPHA", se::Value(2));
    enum_kls->setProperty("DST_ALPHA", se::Value(3));
    enum_kls->setProperty("ONE_MINUS_SRC_ALPHA", se::Value(4));
    enum_kls->setProperty("ONE_MINUS_DST_ALPHA", se::Value(5));
    enum_kls->setProperty("SRC_COLOR", se::Value(6));
    enum_kls->setProperty("DST_COLOR", se::Value(7));
    enum_kls->setProperty("ONE_MINUS_SRC_COLOR", se::Value(8));
    enum_kls->setProperty("ONE_MINUS_DST_COLOR", se::Value(9));
    enum_kls->setProperty("SRC_ALPHA_SATURATE", se::Value(10));
    enum_kls->setProperty("CONSTANT_COLOR", se::Value(11));
    enum_kls->setProperty("ONE_MINUS_CONSTANT_COLOR", se::Value(12));
    enum_kls->setProperty("CONSTANT_ALPHA", se::Value(13));
    enum_kls->setProperty("ONE_MINUS_CONSTANT_ALPHA", se::Value(14));
    obj->setProperty("GFXBlendFactor", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXBlendOp *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXBlendOp>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXBlendOp>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXBlendOp(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("ADD", se::Value(0));
    enum_kls->setProperty("SUB", se::Value(1));
    enum_kls->setProperty("REV_SUB", se::Value(2));
    enum_kls->setProperty("MIN", se::Value(3));
    enum_kls->setProperty("MAX", se::Value(4));
    obj->setProperty("GFXBlendOp", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXColorMask *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXColorMask>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXColorMask>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXColorMask(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("NONE", se::Value(0));
    enum_kls->setProperty("R", se::Value(1));
    enum_kls->setProperty("G", se::Value(2));
    enum_kls->setProperty("B", se::Value(4));
    enum_kls->setProperty("A", se::Value(8));
    enum_kls->setProperty("ALL", se::Value(15));
    obj->setProperty("GFXColorMask", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXShaderType *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXShaderType>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXShaderType>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXShaderType(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("VERTEX", se::Value(0));
    enum_kls->setProperty("CONTROL", se::Value(1));
    enum_kls->setProperty("EVALUATION", se::Value(2));
    enum_kls->setProperty("GEOMETRY", se::Value(3));
    enum_kls->setProperty("FRAGMENT", se::Value(4));
    enum_kls->setProperty("COMPUTE", se::Value(5));
    enum_kls->setProperty("COUNT", se::Value(6));
    obj->setProperty("GFXShaderType", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXLoadOp *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXLoadOp>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXLoadOp>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXLoadOp(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("LOAD", se::Value(0));
    enum_kls->setProperty("CLEAR", se::Value(1));
    enum_kls->setProperty("DISCARD", se::Value(2));
    obj->setProperty("GFXLoadOp", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXStoreOp *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXStoreOp>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXStoreOp>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXStoreOp(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("STORE", se::Value(0));
    enum_kls->setProperty("DISCARD", se::Value(1));
    obj->setProperty("GFXStoreOp", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXTextureLayout *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXTextureLayout>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXTextureLayout>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXTextureLayout(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("UNDEFINED", se::Value(0));
    enum_kls->setProperty("GENERAL", se::Value(1));
    enum_kls->setProperty("COLOR_ATTACHMENT_OPTIMAL", se::Value(2));
    enum_kls->setProperty("DEPTH_STENCIL_ATTACHMENT_OPTIMAL", se::Value(3));
    enum_kls->setProperty("DEPTH_STENCIL_READONLY_OPTIMAL", se::Value(4));
    enum_kls->setProperty("SHADER_READONLY_OPTIMAL", se::Value(5));
    enum_kls->setProperty("TRANSFER_SRC_OPTIMAL", se::Value(6));
    enum_kls->setProperty("TRANSFER_DST_OPTIMAL", se::Value(7));
    enum_kls->setProperty("PREINITIALIZED", se::Value(8));
    enum_kls->setProperty("PRESENT_SRC", se::Value(9));
    obj->setProperty("GFXTextureLayout", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXPipelineBindPoint *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXPipelineBindPoint>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXPipelineBindPoint>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXPipelineBindPoint(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("GRAPHICS", se::Value(0));
    enum_kls->setProperty("COMPUTE", se::Value(1));
    enum_kls->setProperty("RAY_TRACING", se::Value(2));
    obj->setProperty("GFXPipelineBindPoint", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXPrimitiveMode *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXPrimitiveMode>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXPrimitiveMode>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXPrimitiveMode(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("POINT_LIST", se::Value(0));
    enum_kls->setProperty("LINE_LIST", se::Value(1));
    enum_kls->setProperty("LINE_STRIP", se::Value(2));
    enum_kls->setProperty("LINE_LOOP", se::Value(3));
    enum_kls->setProperty("LINE_LIST_ADJACENCY", se::Value(4));
    enum_kls->setProperty("LINE_STRIP_ADJACENCY", se::Value(5));
    enum_kls->setProperty("ISO_LINE_LIST", se::Value(6));
    enum_kls->setProperty("TRIANGLE_LIST", se::Value(7));
    enum_kls->setProperty("TRIANGLE_STRIP", se::Value(8));
    enum_kls->setProperty("TRIANGLE_FAN", se::Value(9));
    enum_kls->setProperty("TRIANGLE_LIST_ADJACENCY", se::Value(10));
    enum_kls->setProperty("TRIANGLE_STRIP_ADJACENCY", se::Value(11));
    enum_kls->setProperty("TRIANGLE_PATCH_ADJACENCY", se::Value(12));
    enum_kls->setProperty("QUAD_PATCH_LIST", se::Value(13));
    obj->setProperty("GFXPrimitiveMode", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXPolygonMode *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXPolygonMode>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXPolygonMode>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXPolygonMode(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("FILL", se::Value(0));
    enum_kls->setProperty("POINT", se::Value(1));
    enum_kls->setProperty("LINE", se::Value(2));
    obj->setProperty("GFXPolygonMode", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXShadeModel *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXShadeModel>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXShadeModel>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXShadeModel(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("GOURAND", se::Value(0));
    enum_kls->setProperty("FLAT", se::Value(1));
    obj->setProperty("GFXShadeModel", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXCullMode *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXCullMode>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXCullMode>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXCullMode(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("NONE", se::Value(0));
    enum_kls->setProperty("FRONT", se::Value(1));
    enum_kls->setProperty("BACK", se::Value(2));
    obj->setProperty("GFXCullMode", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXDynamicState *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXDynamicState>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXDynamicState>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXDynamicState(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("VIEWPORT", se::Value(0));
    enum_kls->setProperty("SCISSOR", se::Value(1));
    enum_kls->setProperty("LINE_WIDTH", se::Value(2));
    enum_kls->setProperty("DEPTH_BIAS", se::Value(3));
    enum_kls->setProperty("BLEND_CONSTANTS", se::Value(4));
    enum_kls->setProperty("DEPTH_BOUNDS", se::Value(5));
    enum_kls->setProperty("STENCIL_WRITE_MASK", se::Value(6));
    enum_kls->setProperty("STENCIL_COMPARE_MASK", se::Value(7));
    obj->setProperty("GFXDynamicState", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXStencilFace *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXStencilFace>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXStencilFace>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXStencilFace(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("FRONT", se::Value(0));
    enum_kls->setProperty("BACK", se::Value(1));
    enum_kls->setProperty("ALL", se::Value(2));
    obj->setProperty("GFXStencilFace", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXBindingType *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXBindingType>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXBindingType>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXBindingType(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("UNKNOWN", se::Value(0));
    enum_kls->setProperty("UNIFORM_BUFFER", se::Value(1));
    enum_kls->setProperty("SAMPLER", se::Value(2));
    enum_kls->setProperty("STORAGE_BUFFER", se::Value(3));
    obj->setProperty("GFXBindingType", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXQueueType *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXQueueType>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXQueueType>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXQueueType(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("GRAPHICS", se::Value(0));
    enum_kls->setProperty("COMPUTE", se::Value(1));
    enum_kls->setProperty("TRANSFER", se::Value(2));
    obj->setProperty("GFXQueueType", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXCommandBufferType *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXCommandBufferType>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXCommandBufferType>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXCommandBufferType(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("PRIMARY", se::Value(0));
    enum_kls->setProperty("SECONDARY", se::Value(1));
    obj->setProperty("GFXCommandBufferType", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXClearFlagBit *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXClearFlagBit>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXClearFlagBit>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXClearFlagBit(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("NONE", se::Value(0));
    enum_kls->setProperty("COLOR", se::Value(1));
    enum_kls->setProperty("DEPTH", se::Value(2));
    enum_kls->setProperty("STENCIL", se::Value(4));
    enum_kls->setProperty("DEPTH_STENCIL", se::Value(6));
    enum_kls->setProperty("ALL", se::Value(7));
    obj->setProperty("GFXClearFlagBit", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXVsyncMode *to)
{
    typedef typename std::underlying_type_t<cocos2d::GFXVsyncMode>  under_type;
    under_type tmp;
    if(sevalue_to_native(from, &tmp)) { *to = static_cast<cocos2d::GFXVsyncMode>(tmp); return true;}
    return false;
}

int js_register_gfx_GFXVsyncMode(se::Object* obj)
{
    auto enum_kls = se::Object::createPlainObject();
    enum_kls->setProperty("OFF", se::Value(0));
    enum_kls->setProperty("ON", se::Value(1));
    enum_kls->setProperty("RELAXED", se::Value(2));
    enum_kls->setProperty("MAILBOX", se::Value(3));
    enum_kls->setProperty("HALF", se::Value(4));
    obj->setProperty("GFXVsyncMode", se::Value(enum_kls));

    se::ScriptEngine::getInstance()->clearException();
    return true;
}
se::Object* __jsb_cocos2d_GFXOffset_proto = nullptr;
se::Class* __jsb_cocos2d_GFXOffset_class = nullptr;

static bool js_gfx_GFXOffset_get_x(se::State& s)
{
    cocos2d::GFXOffset* cobj = (cocos2d::GFXOffset*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXOffset_get_x : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->x, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXOffset_get_x)

static bool js_gfx_GFXOffset_set_x(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXOffset* cobj = (cocos2d::GFXOffset*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXOffset_set_x : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->x); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXOffset_set_x : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXOffset_set_x)

static bool js_gfx_GFXOffset_get_y(se::State& s)
{
    cocos2d::GFXOffset* cobj = (cocos2d::GFXOffset*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXOffset_get_y : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->y, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXOffset_get_y)

static bool js_gfx_GFXOffset_set_y(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXOffset* cobj = (cocos2d::GFXOffset*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXOffset_set_y : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->y); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXOffset_set_y : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXOffset_set_y)

static bool js_gfx_GFXOffset_get_z(se::State& s)
{
    cocos2d::GFXOffset* cobj = (cocos2d::GFXOffset*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXOffset_get_z : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->z, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXOffset_get_z)

static bool js_gfx_GFXOffset_set_z(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXOffset* cobj = (cocos2d::GFXOffset*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXOffset_set_z : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->z); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXOffset_set_z : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXOffset_set_z)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXOffset * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXOffset*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("x", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->x));
    }
    json->getProperty("y", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->y));
    }
    json->getProperty("z", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->z));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXOffset_finalize)

static bool js_gfx_GFXOffset_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXOffset* cobj = JSB_ALLOC(cocos2d::GFXOffset);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXOffset* cobj = JSB_ALLOC(cocos2d::GFXOffset);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 3)
    {
        cocos2d::GFXOffset* cobj = JSB_ALLOC(cocos2d::GFXOffset);
        int arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->x = arg0;
        }
        int arg1 = {};
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->y = arg1;
        }
        int arg2 = {};
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->z = arg2;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXOffset_constructor, __jsb_cocos2d_GFXOffset_class, js_cocos2d_GFXOffset_finalize)




static bool js_cocos2d_GFXOffset_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXOffset)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXOffset* cobj = (cocos2d::GFXOffset*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXOffset_finalize)

bool js_register_gfx_GFXOffset(se::Object* obj)
{
    auto cls = se::Class::create("GFXOffset", obj, nullptr, _SE(js_gfx_GFXOffset_constructor));

    cls->defineProperty("x", _SE(js_gfx_GFXOffset_get_x), _SE(js_gfx_GFXOffset_set_x));
    cls->defineProperty("y", _SE(js_gfx_GFXOffset_get_y), _SE(js_gfx_GFXOffset_set_y));
    cls->defineProperty("z", _SE(js_gfx_GFXOffset_get_z), _SE(js_gfx_GFXOffset_set_z));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXOffset_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXOffset>(cls);

    __jsb_cocos2d_GFXOffset_proto = cls->getProto();
    __jsb_cocos2d_GFXOffset_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXRect_proto = nullptr;
se::Class* __jsb_cocos2d_GFXRect_class = nullptr;

static bool js_gfx_GFXRect_get_x(se::State& s)
{
    cocos2d::GFXRect* cobj = (cocos2d::GFXRect*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRect_get_x : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->x, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRect_get_x)

static bool js_gfx_GFXRect_set_x(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRect* cobj = (cocos2d::GFXRect*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRect_set_x : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->x); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRect_set_x : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRect_set_x)

static bool js_gfx_GFXRect_get_y(se::State& s)
{
    cocos2d::GFXRect* cobj = (cocos2d::GFXRect*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRect_get_y : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->y, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRect_get_y)

static bool js_gfx_GFXRect_set_y(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRect* cobj = (cocos2d::GFXRect*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRect_set_y : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->y); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRect_set_y : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRect_set_y)

static bool js_gfx_GFXRect_get_width(se::State& s)
{
    cocos2d::GFXRect* cobj = (cocos2d::GFXRect*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRect_get_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->width, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRect_get_width)

static bool js_gfx_GFXRect_set_width(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRect* cobj = (cocos2d::GFXRect*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRect_set_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->width); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRect_set_width : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRect_set_width)

static bool js_gfx_GFXRect_get_height(se::State& s)
{
    cocos2d::GFXRect* cobj = (cocos2d::GFXRect*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRect_get_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->height, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRect_get_height)

static bool js_gfx_GFXRect_set_height(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRect* cobj = (cocos2d::GFXRect*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRect_set_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->height); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRect_set_height : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRect_set_height)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXRect * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXRect*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("x", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->x));
    }
    json->getProperty("y", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->y));
    }
    json->getProperty("width", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->width));
    }
    json->getProperty("height", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->height));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXRect_finalize)

static bool js_gfx_GFXRect_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXRect* cobj = JSB_ALLOC(cocos2d::GFXRect);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXRect* cobj = JSB_ALLOC(cocos2d::GFXRect);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 4)
    {
        cocos2d::GFXRect* cobj = JSB_ALLOC(cocos2d::GFXRect);
        int arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->x = arg0;
        }
        int arg1 = {};
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->y = arg1;
        }
        unsigned int arg2 = {};
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->width = arg2;
        }
        unsigned int arg3 = {};
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->height = arg3;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXRect_constructor, __jsb_cocos2d_GFXRect_class, js_cocos2d_GFXRect_finalize)




static bool js_cocos2d_GFXRect_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXRect)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXRect* cobj = (cocos2d::GFXRect*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXRect_finalize)

bool js_register_gfx_GFXRect(se::Object* obj)
{
    auto cls = se::Class::create("GFXRect", obj, nullptr, _SE(js_gfx_GFXRect_constructor));

    cls->defineProperty("x", _SE(js_gfx_GFXRect_get_x), _SE(js_gfx_GFXRect_set_x));
    cls->defineProperty("y", _SE(js_gfx_GFXRect_get_y), _SE(js_gfx_GFXRect_set_y));
    cls->defineProperty("width", _SE(js_gfx_GFXRect_get_width), _SE(js_gfx_GFXRect_set_width));
    cls->defineProperty("height", _SE(js_gfx_GFXRect_get_height), _SE(js_gfx_GFXRect_set_height));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXRect_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXRect>(cls);

    __jsb_cocos2d_GFXRect_proto = cls->getProto();
    __jsb_cocos2d_GFXRect_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXExtent_proto = nullptr;
se::Class* __jsb_cocos2d_GFXExtent_class = nullptr;

static bool js_gfx_GFXExtent_get_width(se::State& s)
{
    cocos2d::GFXExtent* cobj = (cocos2d::GFXExtent*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXExtent_get_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->width, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXExtent_get_width)

static bool js_gfx_GFXExtent_set_width(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXExtent* cobj = (cocos2d::GFXExtent*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXExtent_set_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->width); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXExtent_set_width : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXExtent_set_width)

static bool js_gfx_GFXExtent_get_height(se::State& s)
{
    cocos2d::GFXExtent* cobj = (cocos2d::GFXExtent*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXExtent_get_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->height, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXExtent_get_height)

static bool js_gfx_GFXExtent_set_height(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXExtent* cobj = (cocos2d::GFXExtent*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXExtent_set_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->height); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXExtent_set_height : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXExtent_set_height)

static bool js_gfx_GFXExtent_get_depth(se::State& s)
{
    cocos2d::GFXExtent* cobj = (cocos2d::GFXExtent*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXExtent_get_depth : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->depth, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXExtent_get_depth)

static bool js_gfx_GFXExtent_set_depth(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXExtent* cobj = (cocos2d::GFXExtent*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXExtent_set_depth : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->depth); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXExtent_set_depth : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXExtent_set_depth)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXExtent * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXExtent*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("width", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->width));
    }
    json->getProperty("height", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->height));
    }
    json->getProperty("depth", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->depth));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXExtent_finalize)

static bool js_gfx_GFXExtent_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXExtent* cobj = JSB_ALLOC(cocos2d::GFXExtent);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXExtent* cobj = JSB_ALLOC(cocos2d::GFXExtent);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 3)
    {
        cocos2d::GFXExtent* cobj = JSB_ALLOC(cocos2d::GFXExtent);
        unsigned int arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->width = arg0;
        }
        unsigned int arg1 = {};
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->height = arg1;
        }
        unsigned int arg2 = {};
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->depth = arg2;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXExtent_constructor, __jsb_cocos2d_GFXExtent_class, js_cocos2d_GFXExtent_finalize)




static bool js_cocos2d_GFXExtent_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXExtent)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXExtent* cobj = (cocos2d::GFXExtent*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXExtent_finalize)

bool js_register_gfx_GFXExtent(se::Object* obj)
{
    auto cls = se::Class::create("GFXExtent", obj, nullptr, _SE(js_gfx_GFXExtent_constructor));

    cls->defineProperty("width", _SE(js_gfx_GFXExtent_get_width), _SE(js_gfx_GFXExtent_set_width));
    cls->defineProperty("height", _SE(js_gfx_GFXExtent_get_height), _SE(js_gfx_GFXExtent_set_height));
    cls->defineProperty("depth", _SE(js_gfx_GFXExtent_get_depth), _SE(js_gfx_GFXExtent_set_depth));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXExtent_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXExtent>(cls);

    __jsb_cocos2d_GFXExtent_proto = cls->getProto();
    __jsb_cocos2d_GFXExtent_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXTextureSubres_proto = nullptr;
se::Class* __jsb_cocos2d_GFXTextureSubres_class = nullptr;

static bool js_gfx_GFXTextureSubres_get_baseMipLevel(se::State& s)
{
    cocos2d::GFXTextureSubres* cobj = (cocos2d::GFXTextureSubres*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureSubres_get_baseMipLevel : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->baseMipLevel, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureSubres_get_baseMipLevel)

static bool js_gfx_GFXTextureSubres_set_baseMipLevel(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureSubres* cobj = (cocos2d::GFXTextureSubres*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureSubres_set_baseMipLevel : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->baseMipLevel); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureSubres_set_baseMipLevel : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureSubres_set_baseMipLevel)

static bool js_gfx_GFXTextureSubres_get_levelCount(se::State& s)
{
    cocos2d::GFXTextureSubres* cobj = (cocos2d::GFXTextureSubres*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureSubres_get_levelCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->levelCount, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureSubres_get_levelCount)

static bool js_gfx_GFXTextureSubres_set_levelCount(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureSubres* cobj = (cocos2d::GFXTextureSubres*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureSubres_set_levelCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->levelCount); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureSubres_set_levelCount : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureSubres_set_levelCount)

static bool js_gfx_GFXTextureSubres_get_baseArrayLayer(se::State& s)
{
    cocos2d::GFXTextureSubres* cobj = (cocos2d::GFXTextureSubres*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureSubres_get_baseArrayLayer : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->baseArrayLayer, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureSubres_get_baseArrayLayer)

static bool js_gfx_GFXTextureSubres_set_baseArrayLayer(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureSubres* cobj = (cocos2d::GFXTextureSubres*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureSubres_set_baseArrayLayer : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->baseArrayLayer); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureSubres_set_baseArrayLayer : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureSubres_set_baseArrayLayer)

static bool js_gfx_GFXTextureSubres_get_layerCount(se::State& s)
{
    cocos2d::GFXTextureSubres* cobj = (cocos2d::GFXTextureSubres*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureSubres_get_layerCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->layerCount, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureSubres_get_layerCount)

static bool js_gfx_GFXTextureSubres_set_layerCount(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureSubres* cobj = (cocos2d::GFXTextureSubres*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureSubres_set_layerCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->layerCount); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureSubres_set_layerCount : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureSubres_set_layerCount)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXTextureSubres * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXTextureSubres*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("baseMipLevel", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->baseMipLevel));
    }
    json->getProperty("levelCount", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->levelCount));
    }
    json->getProperty("baseArrayLayer", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->baseArrayLayer));
    }
    json->getProperty("layerCount", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->layerCount));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXTextureSubres_finalize)

static bool js_gfx_GFXTextureSubres_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXTextureSubres* cobj = JSB_ALLOC(cocos2d::GFXTextureSubres);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXTextureSubres* cobj = JSB_ALLOC(cocos2d::GFXTextureSubres);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 4)
    {
        cocos2d::GFXTextureSubres* cobj = JSB_ALLOC(cocos2d::GFXTextureSubres);
        unsigned int arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->baseMipLevel = arg0;
        }
        unsigned int arg1 = {};
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->levelCount = arg1;
        }
        unsigned int arg2 = {};
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->baseArrayLayer = arg2;
        }
        unsigned int arg3 = {};
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->layerCount = arg3;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXTextureSubres_constructor, __jsb_cocos2d_GFXTextureSubres_class, js_cocos2d_GFXTextureSubres_finalize)




static bool js_cocos2d_GFXTextureSubres_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXTextureSubres)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXTextureSubres* cobj = (cocos2d::GFXTextureSubres*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXTextureSubres_finalize)

bool js_register_gfx_GFXTextureSubres(se::Object* obj)
{
    auto cls = se::Class::create("GFXTextureSubres", obj, nullptr, _SE(js_gfx_GFXTextureSubres_constructor));

    cls->defineProperty("baseMipLevel", _SE(js_gfx_GFXTextureSubres_get_baseMipLevel), _SE(js_gfx_GFXTextureSubres_set_baseMipLevel));
    cls->defineProperty("levelCount", _SE(js_gfx_GFXTextureSubres_get_levelCount), _SE(js_gfx_GFXTextureSubres_set_levelCount));
    cls->defineProperty("baseArrayLayer", _SE(js_gfx_GFXTextureSubres_get_baseArrayLayer), _SE(js_gfx_GFXTextureSubres_set_baseArrayLayer));
    cls->defineProperty("layerCount", _SE(js_gfx_GFXTextureSubres_get_layerCount), _SE(js_gfx_GFXTextureSubres_set_layerCount));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXTextureSubres_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXTextureSubres>(cls);

    __jsb_cocos2d_GFXTextureSubres_proto = cls->getProto();
    __jsb_cocos2d_GFXTextureSubres_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXTextureCopy_proto = nullptr;
se::Class* __jsb_cocos2d_GFXTextureCopy_class = nullptr;

static bool js_gfx_GFXTextureCopy_get_srcSubres(se::State& s)
{
    cocos2d::GFXTextureCopy* cobj = (cocos2d::GFXTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureCopy_get_srcSubres : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->srcSubres, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureCopy_get_srcSubres)

static bool js_gfx_GFXTextureCopy_set_srcSubres(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureCopy* cobj = (cocos2d::GFXTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureCopy_set_srcSubres : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->srcSubres); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureCopy_set_srcSubres : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureCopy_set_srcSubres)

static bool js_gfx_GFXTextureCopy_get_srcOffset(se::State& s)
{
    cocos2d::GFXTextureCopy* cobj = (cocos2d::GFXTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureCopy_get_srcOffset : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->srcOffset, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureCopy_get_srcOffset)

static bool js_gfx_GFXTextureCopy_set_srcOffset(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureCopy* cobj = (cocos2d::GFXTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureCopy_set_srcOffset : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->srcOffset); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureCopy_set_srcOffset : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureCopy_set_srcOffset)

static bool js_gfx_GFXTextureCopy_get_dstSubres(se::State& s)
{
    cocos2d::GFXTextureCopy* cobj = (cocos2d::GFXTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureCopy_get_dstSubres : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->dstSubres, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureCopy_get_dstSubres)

static bool js_gfx_GFXTextureCopy_set_dstSubres(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureCopy* cobj = (cocos2d::GFXTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureCopy_set_dstSubres : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->dstSubres); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureCopy_set_dstSubres : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureCopy_set_dstSubres)

static bool js_gfx_GFXTextureCopy_get_dstOffset(se::State& s)
{
    cocos2d::GFXTextureCopy* cobj = (cocos2d::GFXTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureCopy_get_dstOffset : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->dstOffset, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureCopy_get_dstOffset)

static bool js_gfx_GFXTextureCopy_set_dstOffset(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureCopy* cobj = (cocos2d::GFXTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureCopy_set_dstOffset : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->dstOffset); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureCopy_set_dstOffset : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureCopy_set_dstOffset)

static bool js_gfx_GFXTextureCopy_get_extent(se::State& s)
{
    cocos2d::GFXTextureCopy* cobj = (cocos2d::GFXTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureCopy_get_extent : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->extent, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureCopy_get_extent)

static bool js_gfx_GFXTextureCopy_set_extent(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureCopy* cobj = (cocos2d::GFXTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureCopy_set_extent : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->extent); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureCopy_set_extent : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureCopy_set_extent)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXTextureCopy * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXTextureCopy*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("srcSubres", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->srcSubres));
    }
    json->getProperty("srcOffset", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->srcOffset));
    }
    json->getProperty("dstSubres", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->dstSubres));
    }
    json->getProperty("dstOffset", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->dstOffset));
    }
    json->getProperty("extent", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->extent));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXTextureCopy_finalize)

static bool js_gfx_GFXTextureCopy_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXTextureCopy* cobj = JSB_ALLOC(cocos2d::GFXTextureCopy);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXTextureCopy* cobj = JSB_ALLOC(cocos2d::GFXTextureCopy);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 5)
    {
        cocos2d::GFXTextureCopy* cobj = JSB_ALLOC(cocos2d::GFXTextureCopy);
        cocos2d::GFXTextureSubres arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->srcSubres = arg0;
        }
        cocos2d::GFXOffset arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->srcOffset = arg1;
        }
        cocos2d::GFXTextureSubres arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->dstSubres = arg2;
        }
        cocos2d::GFXOffset arg3;
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->dstOffset = arg3;
        }
        cocos2d::GFXExtent arg4;
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->extent = arg4;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXTextureCopy_constructor, __jsb_cocos2d_GFXTextureCopy_class, js_cocos2d_GFXTextureCopy_finalize)




static bool js_cocos2d_GFXTextureCopy_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXTextureCopy)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXTextureCopy* cobj = (cocos2d::GFXTextureCopy*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXTextureCopy_finalize)

bool js_register_gfx_GFXTextureCopy(se::Object* obj)
{
    auto cls = se::Class::create("GFXTextureCopy", obj, nullptr, _SE(js_gfx_GFXTextureCopy_constructor));

    cls->defineProperty("srcSubres", _SE(js_gfx_GFXTextureCopy_get_srcSubres), _SE(js_gfx_GFXTextureCopy_set_srcSubres));
    cls->defineProperty("srcOffset", _SE(js_gfx_GFXTextureCopy_get_srcOffset), _SE(js_gfx_GFXTextureCopy_set_srcOffset));
    cls->defineProperty("dstSubres", _SE(js_gfx_GFXTextureCopy_get_dstSubres), _SE(js_gfx_GFXTextureCopy_set_dstSubres));
    cls->defineProperty("dstOffset", _SE(js_gfx_GFXTextureCopy_get_dstOffset), _SE(js_gfx_GFXTextureCopy_set_dstOffset));
    cls->defineProperty("extent", _SE(js_gfx_GFXTextureCopy_get_extent), _SE(js_gfx_GFXTextureCopy_set_extent));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXTextureCopy_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXTextureCopy>(cls);

    __jsb_cocos2d_GFXTextureCopy_proto = cls->getProto();
    __jsb_cocos2d_GFXTextureCopy_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXBufferTextureCopy_proto = nullptr;
se::Class* __jsb_cocos2d_GFXBufferTextureCopy_class = nullptr;

static bool js_gfx_GFXBufferTextureCopy_get_buffOffset(se::State& s)
{
    cocos2d::GFXBufferTextureCopy* cobj = (cocos2d::GFXBufferTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferTextureCopy_get_buffOffset : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->buffOffset, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBufferTextureCopy_get_buffOffset)

static bool js_gfx_GFXBufferTextureCopy_set_buffOffset(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBufferTextureCopy* cobj = (cocos2d::GFXBufferTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferTextureCopy_set_buffOffset : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->buffOffset); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBufferTextureCopy_set_buffOffset : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBufferTextureCopy_set_buffOffset)

static bool js_gfx_GFXBufferTextureCopy_get_buffStride(se::State& s)
{
    cocos2d::GFXBufferTextureCopy* cobj = (cocos2d::GFXBufferTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferTextureCopy_get_buffStride : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->buffStride, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBufferTextureCopy_get_buffStride)

static bool js_gfx_GFXBufferTextureCopy_set_buffStride(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBufferTextureCopy* cobj = (cocos2d::GFXBufferTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferTextureCopy_set_buffStride : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->buffStride); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBufferTextureCopy_set_buffStride : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBufferTextureCopy_set_buffStride)

static bool js_gfx_GFXBufferTextureCopy_get_buffTexHeight(se::State& s)
{
    cocos2d::GFXBufferTextureCopy* cobj = (cocos2d::GFXBufferTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferTextureCopy_get_buffTexHeight : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->buffTexHeight, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBufferTextureCopy_get_buffTexHeight)

static bool js_gfx_GFXBufferTextureCopy_set_buffTexHeight(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBufferTextureCopy* cobj = (cocos2d::GFXBufferTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferTextureCopy_set_buffTexHeight : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->buffTexHeight); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBufferTextureCopy_set_buffTexHeight : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBufferTextureCopy_set_buffTexHeight)

static bool js_gfx_GFXBufferTextureCopy_get_texOffset(se::State& s)
{
    cocos2d::GFXBufferTextureCopy* cobj = (cocos2d::GFXBufferTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferTextureCopy_get_texOffset : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->texOffset, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBufferTextureCopy_get_texOffset)

static bool js_gfx_GFXBufferTextureCopy_set_texOffset(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBufferTextureCopy* cobj = (cocos2d::GFXBufferTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferTextureCopy_set_texOffset : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->texOffset); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBufferTextureCopy_set_texOffset : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBufferTextureCopy_set_texOffset)

static bool js_gfx_GFXBufferTextureCopy_get_texExtent(se::State& s)
{
    cocos2d::GFXBufferTextureCopy* cobj = (cocos2d::GFXBufferTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferTextureCopy_get_texExtent : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->texExtent, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBufferTextureCopy_get_texExtent)

static bool js_gfx_GFXBufferTextureCopy_set_texExtent(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBufferTextureCopy* cobj = (cocos2d::GFXBufferTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferTextureCopy_set_texExtent : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->texExtent); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBufferTextureCopy_set_texExtent : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBufferTextureCopy_set_texExtent)

static bool js_gfx_GFXBufferTextureCopy_get_texSubres(se::State& s)
{
    cocos2d::GFXBufferTextureCopy* cobj = (cocos2d::GFXBufferTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferTextureCopy_get_texSubres : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->texSubres, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBufferTextureCopy_get_texSubres)

static bool js_gfx_GFXBufferTextureCopy_set_texSubres(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBufferTextureCopy* cobj = (cocos2d::GFXBufferTextureCopy*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferTextureCopy_set_texSubres : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->texSubres); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBufferTextureCopy_set_texSubres : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBufferTextureCopy_set_texSubres)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXBufferTextureCopy * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXBufferTextureCopy*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("buffOffset", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->buffOffset));
    }
    json->getProperty("buffStride", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->buffStride));
    }
    json->getProperty("buffTexHeight", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->buffTexHeight));
    }
    json->getProperty("texOffset", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->texOffset));
    }
    json->getProperty("texExtent", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->texExtent));
    }
    json->getProperty("texSubres", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->texSubres));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXBufferTextureCopy_finalize)

static bool js_gfx_GFXBufferTextureCopy_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXBufferTextureCopy* cobj = JSB_ALLOC(cocos2d::GFXBufferTextureCopy);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXBufferTextureCopy* cobj = JSB_ALLOC(cocos2d::GFXBufferTextureCopy);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 6)
    {
        cocos2d::GFXBufferTextureCopy* cobj = JSB_ALLOC(cocos2d::GFXBufferTextureCopy);
        unsigned int arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->buffOffset = arg0;
        }
        unsigned int arg1 = {};
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->buffStride = arg1;
        }
        unsigned int arg2 = {};
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->buffTexHeight = arg2;
        }
        cocos2d::GFXOffset arg3;
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->texOffset = arg3;
        }
        cocos2d::GFXExtent arg4;
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->texExtent = arg4;
        }
        cocos2d::GFXTextureSubres arg5;
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->texSubres = arg5;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXBufferTextureCopy_constructor, __jsb_cocos2d_GFXBufferTextureCopy_class, js_cocos2d_GFXBufferTextureCopy_finalize)




static bool js_cocos2d_GFXBufferTextureCopy_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXBufferTextureCopy)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXBufferTextureCopy* cobj = (cocos2d::GFXBufferTextureCopy*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXBufferTextureCopy_finalize)

bool js_register_gfx_GFXBufferTextureCopy(se::Object* obj)
{
    auto cls = se::Class::create("GFXBufferTextureCopy", obj, nullptr, _SE(js_gfx_GFXBufferTextureCopy_constructor));

    cls->defineProperty("buffOffset", _SE(js_gfx_GFXBufferTextureCopy_get_buffOffset), _SE(js_gfx_GFXBufferTextureCopy_set_buffOffset));
    cls->defineProperty("buffStride", _SE(js_gfx_GFXBufferTextureCopy_get_buffStride), _SE(js_gfx_GFXBufferTextureCopy_set_buffStride));
    cls->defineProperty("buffTexHeight", _SE(js_gfx_GFXBufferTextureCopy_get_buffTexHeight), _SE(js_gfx_GFXBufferTextureCopy_set_buffTexHeight));
    cls->defineProperty("texOffset", _SE(js_gfx_GFXBufferTextureCopy_get_texOffset), _SE(js_gfx_GFXBufferTextureCopy_set_texOffset));
    cls->defineProperty("texExtent", _SE(js_gfx_GFXBufferTextureCopy_get_texExtent), _SE(js_gfx_GFXBufferTextureCopy_set_texExtent));
    cls->defineProperty("texSubres", _SE(js_gfx_GFXBufferTextureCopy_get_texSubres), _SE(js_gfx_GFXBufferTextureCopy_set_texSubres));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXBufferTextureCopy_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXBufferTextureCopy>(cls);

    __jsb_cocos2d_GFXBufferTextureCopy_proto = cls->getProto();
    __jsb_cocos2d_GFXBufferTextureCopy_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXViewport_proto = nullptr;
se::Class* __jsb_cocos2d_GFXViewport_class = nullptr;

static bool js_gfx_GFXViewport_get_left(se::State& s)
{
    cocos2d::GFXViewport* cobj = (cocos2d::GFXViewport*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXViewport_get_left : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->left, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXViewport_get_left)

static bool js_gfx_GFXViewport_set_left(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXViewport* cobj = (cocos2d::GFXViewport*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXViewport_set_left : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->left); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXViewport_set_left : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXViewport_set_left)

static bool js_gfx_GFXViewport_get_top(se::State& s)
{
    cocos2d::GFXViewport* cobj = (cocos2d::GFXViewport*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXViewport_get_top : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->top, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXViewport_get_top)

static bool js_gfx_GFXViewport_set_top(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXViewport* cobj = (cocos2d::GFXViewport*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXViewport_set_top : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->top); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXViewport_set_top : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXViewport_set_top)

static bool js_gfx_GFXViewport_get_width(se::State& s)
{
    cocos2d::GFXViewport* cobj = (cocos2d::GFXViewport*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXViewport_get_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->width, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXViewport_get_width)

static bool js_gfx_GFXViewport_set_width(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXViewport* cobj = (cocos2d::GFXViewport*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXViewport_set_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->width); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXViewport_set_width : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXViewport_set_width)

static bool js_gfx_GFXViewport_get_height(se::State& s)
{
    cocos2d::GFXViewport* cobj = (cocos2d::GFXViewport*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXViewport_get_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->height, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXViewport_get_height)

static bool js_gfx_GFXViewport_set_height(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXViewport* cobj = (cocos2d::GFXViewport*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXViewport_set_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->height); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXViewport_set_height : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXViewport_set_height)

static bool js_gfx_GFXViewport_get_minDepth(se::State& s)
{
    cocos2d::GFXViewport* cobj = (cocos2d::GFXViewport*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXViewport_get_minDepth : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->minDepth, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXViewport_get_minDepth)

static bool js_gfx_GFXViewport_set_minDepth(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXViewport* cobj = (cocos2d::GFXViewport*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXViewport_set_minDepth : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->minDepth); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXViewport_set_minDepth : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXViewport_set_minDepth)

static bool js_gfx_GFXViewport_get_maxDepth(se::State& s)
{
    cocos2d::GFXViewport* cobj = (cocos2d::GFXViewport*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXViewport_get_maxDepth : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->maxDepth, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXViewport_get_maxDepth)

static bool js_gfx_GFXViewport_set_maxDepth(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXViewport* cobj = (cocos2d::GFXViewport*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXViewport_set_maxDepth : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->maxDepth); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXViewport_set_maxDepth : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXViewport_set_maxDepth)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXViewport * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXViewport*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("left", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->left));
    }
    json->getProperty("top", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->top));
    }
    json->getProperty("width", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->width));
    }
    json->getProperty("height", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->height));
    }
    json->getProperty("minDepth", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->minDepth));
    }
    json->getProperty("maxDepth", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->maxDepth));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXViewport_finalize)

static bool js_gfx_GFXViewport_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXViewport* cobj = JSB_ALLOC(cocos2d::GFXViewport);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXViewport* cobj = JSB_ALLOC(cocos2d::GFXViewport);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 6)
    {
        cocos2d::GFXViewport* cobj = JSB_ALLOC(cocos2d::GFXViewport);
        int arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->left = arg0;
        }
        int arg1 = {};
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->top = arg1;
        }
        unsigned int arg2 = {};
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->width = arg2;
        }
        unsigned int arg3 = {};
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->height = arg3;
        }
        float arg4 = {};
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->minDepth = arg4;
        }
        float arg5 = {};
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->maxDepth = arg5;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXViewport_constructor, __jsb_cocos2d_GFXViewport_class, js_cocos2d_GFXViewport_finalize)




static bool js_cocos2d_GFXViewport_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXViewport)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXViewport* cobj = (cocos2d::GFXViewport*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXViewport_finalize)

bool js_register_gfx_GFXViewport(se::Object* obj)
{
    auto cls = se::Class::create("GFXViewport", obj, nullptr, _SE(js_gfx_GFXViewport_constructor));

    cls->defineProperty("left", _SE(js_gfx_GFXViewport_get_left), _SE(js_gfx_GFXViewport_set_left));
    cls->defineProperty("top", _SE(js_gfx_GFXViewport_get_top), _SE(js_gfx_GFXViewport_set_top));
    cls->defineProperty("width", _SE(js_gfx_GFXViewport_get_width), _SE(js_gfx_GFXViewport_set_width));
    cls->defineProperty("height", _SE(js_gfx_GFXViewport_get_height), _SE(js_gfx_GFXViewport_set_height));
    cls->defineProperty("minDepth", _SE(js_gfx_GFXViewport_get_minDepth), _SE(js_gfx_GFXViewport_set_minDepth));
    cls->defineProperty("maxDepth", _SE(js_gfx_GFXViewport_get_maxDepth), _SE(js_gfx_GFXViewport_set_maxDepth));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXViewport_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXViewport>(cls);

    __jsb_cocos2d_GFXViewport_proto = cls->getProto();
    __jsb_cocos2d_GFXViewport_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXColor_proto = nullptr;
se::Class* __jsb_cocos2d_GFXColor_class = nullptr;

static bool js_gfx_GFXColor_get_r(se::State& s)
{
    cocos2d::GFXColor* cobj = (cocos2d::GFXColor*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColor_get_r : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->r, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXColor_get_r)

static bool js_gfx_GFXColor_set_r(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXColor* cobj = (cocos2d::GFXColor*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColor_set_r : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->r); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXColor_set_r : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXColor_set_r)

static bool js_gfx_GFXColor_get_g(se::State& s)
{
    cocos2d::GFXColor* cobj = (cocos2d::GFXColor*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColor_get_g : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->g, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXColor_get_g)

static bool js_gfx_GFXColor_set_g(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXColor* cobj = (cocos2d::GFXColor*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColor_set_g : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->g); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXColor_set_g : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXColor_set_g)

static bool js_gfx_GFXColor_get_b(se::State& s)
{
    cocos2d::GFXColor* cobj = (cocos2d::GFXColor*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColor_get_b : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->b, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXColor_get_b)

static bool js_gfx_GFXColor_set_b(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXColor* cobj = (cocos2d::GFXColor*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColor_set_b : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->b); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXColor_set_b : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXColor_set_b)

static bool js_gfx_GFXColor_get_a(se::State& s)
{
    cocos2d::GFXColor* cobj = (cocos2d::GFXColor*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColor_get_a : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->a, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXColor_get_a)

static bool js_gfx_GFXColor_set_a(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXColor* cobj = (cocos2d::GFXColor*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColor_set_a : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->a); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXColor_set_a : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXColor_set_a)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXColor * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXColor*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("r", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->r));
    }
    json->getProperty("g", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->g));
    }
    json->getProperty("b", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->b));
    }
    json->getProperty("a", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->a));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXColor_finalize)

static bool js_gfx_GFXColor_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXColor* cobj = JSB_ALLOC(cocos2d::GFXColor);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXColor* cobj = JSB_ALLOC(cocos2d::GFXColor);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 4)
    {
        cocos2d::GFXColor* cobj = JSB_ALLOC(cocos2d::GFXColor);
        float arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->r = arg0;
        }
        float arg1 = {};
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->g = arg1;
        }
        float arg2 = {};
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->b = arg2;
        }
        float arg3 = {};
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->a = arg3;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXColor_constructor, __jsb_cocos2d_GFXColor_class, js_cocos2d_GFXColor_finalize)




static bool js_cocos2d_GFXColor_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXColor)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXColor* cobj = (cocos2d::GFXColor*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXColor_finalize)

bool js_register_gfx_GFXColor(se::Object* obj)
{
    auto cls = se::Class::create("GFXColor", obj, nullptr, _SE(js_gfx_GFXColor_constructor));

    cls->defineProperty("r", _SE(js_gfx_GFXColor_get_r), _SE(js_gfx_GFXColor_set_r));
    cls->defineProperty("g", _SE(js_gfx_GFXColor_get_g), _SE(js_gfx_GFXColor_set_g));
    cls->defineProperty("b", _SE(js_gfx_GFXColor_get_b), _SE(js_gfx_GFXColor_set_b));
    cls->defineProperty("a", _SE(js_gfx_GFXColor_get_a), _SE(js_gfx_GFXColor_set_a));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXColor_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXColor>(cls);

    __jsb_cocos2d_GFXColor_proto = cls->getProto();
    __jsb_cocos2d_GFXColor_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXDeviceInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXDeviceInfo_class = nullptr;

static bool js_gfx_GFXDeviceInfo_get_windowHandle(se::State& s)
{
    cocos2d::GFXDeviceInfo* cobj = (cocos2d::GFXDeviceInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDeviceInfo_get_windowHandle : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->windowHandle, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDeviceInfo_get_windowHandle)

static bool js_gfx_GFXDeviceInfo_set_windowHandle(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDeviceInfo* cobj = (cocos2d::GFXDeviceInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDeviceInfo_set_windowHandle : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->windowHandle); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDeviceInfo_set_windowHandle : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDeviceInfo_set_windowHandle)

static bool js_gfx_GFXDeviceInfo_get_width(se::State& s)
{
    cocos2d::GFXDeviceInfo* cobj = (cocos2d::GFXDeviceInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDeviceInfo_get_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->width, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDeviceInfo_get_width)

static bool js_gfx_GFXDeviceInfo_set_width(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDeviceInfo* cobj = (cocos2d::GFXDeviceInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDeviceInfo_set_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->width); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDeviceInfo_set_width : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDeviceInfo_set_width)

static bool js_gfx_GFXDeviceInfo_get_height(se::State& s)
{
    cocos2d::GFXDeviceInfo* cobj = (cocos2d::GFXDeviceInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDeviceInfo_get_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->height, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDeviceInfo_get_height)

static bool js_gfx_GFXDeviceInfo_set_height(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDeviceInfo* cobj = (cocos2d::GFXDeviceInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDeviceInfo_set_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->height); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDeviceInfo_set_height : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDeviceInfo_set_height)

static bool js_gfx_GFXDeviceInfo_get_nativeWidth(se::State& s)
{
    cocos2d::GFXDeviceInfo* cobj = (cocos2d::GFXDeviceInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDeviceInfo_get_nativeWidth : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->nativeWidth, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDeviceInfo_get_nativeWidth)

static bool js_gfx_GFXDeviceInfo_set_nativeWidth(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDeviceInfo* cobj = (cocos2d::GFXDeviceInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDeviceInfo_set_nativeWidth : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->nativeWidth); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDeviceInfo_set_nativeWidth : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDeviceInfo_set_nativeWidth)

static bool js_gfx_GFXDeviceInfo_get_nativeHeight(se::State& s)
{
    cocos2d::GFXDeviceInfo* cobj = (cocos2d::GFXDeviceInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDeviceInfo_get_nativeHeight : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->nativeHeight, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDeviceInfo_get_nativeHeight)

static bool js_gfx_GFXDeviceInfo_set_nativeHeight(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDeviceInfo* cobj = (cocos2d::GFXDeviceInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDeviceInfo_set_nativeHeight : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->nativeHeight); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDeviceInfo_set_nativeHeight : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDeviceInfo_set_nativeHeight)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXDeviceInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXDeviceInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("windowHandle", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->windowHandle));
    }
    json->getProperty("width", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->width));
    }
    json->getProperty("height", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->height));
    }
    json->getProperty("nativeWidth", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->nativeWidth));
    }
    json->getProperty("nativeHeight", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->nativeHeight));
    }
    json->getProperty("sharedCtx", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->sharedCtx));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXDeviceInfo_finalize)

static bool js_gfx_GFXDeviceInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXDeviceInfo* cobj = JSB_ALLOC(cocos2d::GFXDeviceInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXDeviceInfo* cobj = JSB_ALLOC(cocos2d::GFXDeviceInfo);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 6)
    {
        cocos2d::GFXDeviceInfo* cobj = JSB_ALLOC(cocos2d::GFXDeviceInfo);
        uintptr_t arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->windowHandle = arg0;
        }
        unsigned int arg1 = {};
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->width = arg1;
        }
        unsigned int arg2 = {};
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->height = arg2;
        }
        unsigned int arg3 = {};
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->nativeWidth = arg3;
        }
        unsigned int arg4 = {};
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->nativeHeight = arg4;
        }
        cocos2d::GFXContext* arg5 = nullptr;
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->sharedCtx = arg5;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXDeviceInfo_constructor, __jsb_cocos2d_GFXDeviceInfo_class, js_cocos2d_GFXDeviceInfo_finalize)




static bool js_cocos2d_GFXDeviceInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXDeviceInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXDeviceInfo* cobj = (cocos2d::GFXDeviceInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXDeviceInfo_finalize)

bool js_register_gfx_GFXDeviceInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXDeviceInfo", obj, nullptr, _SE(js_gfx_GFXDeviceInfo_constructor));

    cls->defineProperty("windowHandle", _SE(js_gfx_GFXDeviceInfo_get_windowHandle), _SE(js_gfx_GFXDeviceInfo_set_windowHandle));
    cls->defineProperty("width", _SE(js_gfx_GFXDeviceInfo_get_width), _SE(js_gfx_GFXDeviceInfo_set_width));
    cls->defineProperty("height", _SE(js_gfx_GFXDeviceInfo_get_height), _SE(js_gfx_GFXDeviceInfo_set_height));
    cls->defineProperty("nativeWidth", _SE(js_gfx_GFXDeviceInfo_get_nativeWidth), _SE(js_gfx_GFXDeviceInfo_set_nativeWidth));
    cls->defineProperty("nativeHeight", _SE(js_gfx_GFXDeviceInfo_get_nativeHeight), _SE(js_gfx_GFXDeviceInfo_set_nativeHeight));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXDeviceInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXDeviceInfo>(cls);

    __jsb_cocos2d_GFXDeviceInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXDeviceInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXWindowInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXWindowInfo_class = nullptr;

static bool js_gfx_GFXWindowInfo_get_title(se::State& s)
{
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_get_title : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->title, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXWindowInfo_get_title)

static bool js_gfx_GFXWindowInfo_set_title(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_set_title : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->title); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXWindowInfo_set_title : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXWindowInfo_set_title)

static bool js_gfx_GFXWindowInfo_get_left(se::State& s)
{
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_get_left : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->left, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXWindowInfo_get_left)

static bool js_gfx_GFXWindowInfo_set_left(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_set_left : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->left); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXWindowInfo_set_left : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXWindowInfo_set_left)

static bool js_gfx_GFXWindowInfo_get_top(se::State& s)
{
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_get_top : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->top, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXWindowInfo_get_top)

static bool js_gfx_GFXWindowInfo_set_top(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_set_top : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->top); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXWindowInfo_set_top : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXWindowInfo_set_top)

static bool js_gfx_GFXWindowInfo_get_width(se::State& s)
{
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_get_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->width, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXWindowInfo_get_width)

static bool js_gfx_GFXWindowInfo_set_width(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_set_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->width); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXWindowInfo_set_width : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXWindowInfo_set_width)

static bool js_gfx_GFXWindowInfo_get_height(se::State& s)
{
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_get_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->height, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXWindowInfo_get_height)

static bool js_gfx_GFXWindowInfo_set_height(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_set_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->height); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXWindowInfo_set_height : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXWindowInfo_set_height)

static bool js_gfx_GFXWindowInfo_get_colorFmt(se::State& s)
{
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_get_colorFmt : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->colorFmt, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXWindowInfo_get_colorFmt)

static bool js_gfx_GFXWindowInfo_set_colorFmt(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_set_colorFmt : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->colorFmt); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXWindowInfo_set_colorFmt : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXWindowInfo_set_colorFmt)

static bool js_gfx_GFXWindowInfo_get_depthStencilFmt(se::State& s)
{
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_get_depthStencilFmt : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->depthStencilFmt, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXWindowInfo_get_depthStencilFmt)

static bool js_gfx_GFXWindowInfo_set_depthStencilFmt(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_set_depthStencilFmt : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->depthStencilFmt); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXWindowInfo_set_depthStencilFmt : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXWindowInfo_set_depthStencilFmt)

static bool js_gfx_GFXWindowInfo_get_isOffscreen(se::State& s)
{
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_get_isOffscreen : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->isOffscreen, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXWindowInfo_get_isOffscreen)

static bool js_gfx_GFXWindowInfo_set_isOffscreen(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_set_isOffscreen : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->isOffscreen); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXWindowInfo_set_isOffscreen : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXWindowInfo_set_isOffscreen)

static bool js_gfx_GFXWindowInfo_get_isFullscreen(se::State& s)
{
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_get_isFullscreen : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->isFullscreen, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXWindowInfo_get_isFullscreen)

static bool js_gfx_GFXWindowInfo_set_isFullscreen(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_set_isFullscreen : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->isFullscreen); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXWindowInfo_set_isFullscreen : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXWindowInfo_set_isFullscreen)

static bool js_gfx_GFXWindowInfo_get_vsyncMode(se::State& s)
{
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_get_vsyncMode : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->vsyncMode, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXWindowInfo_get_vsyncMode)

static bool js_gfx_GFXWindowInfo_set_vsyncMode(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_set_vsyncMode : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->vsyncMode); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXWindowInfo_set_vsyncMode : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXWindowInfo_set_vsyncMode)

static bool js_gfx_GFXWindowInfo_get_windowHandle(se::State& s)
{
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_get_windowHandle : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->windowHandle, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXWindowInfo_get_windowHandle)

static bool js_gfx_GFXWindowInfo_set_windowHandle(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindowInfo_set_windowHandle : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->windowHandle); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXWindowInfo_set_windowHandle : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXWindowInfo_set_windowHandle)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXWindowInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXWindowInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("title", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->title));
    }
    json->getProperty("left", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->left));
    }
    json->getProperty("top", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->top));
    }
    json->getProperty("width", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->width));
    }
    json->getProperty("height", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->height));
    }
    json->getProperty("colorFmt", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->colorFmt));
    }
    json->getProperty("depthStencilFmt", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->depthStencilFmt));
    }
    json->getProperty("isOffscreen", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->isOffscreen));
    }
    json->getProperty("isFullscreen", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->isFullscreen));
    }
    json->getProperty("vsyncMode", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->vsyncMode));
    }
    json->getProperty("windowHandle", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->windowHandle));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXWindowInfo_finalize)

static bool js_gfx_GFXWindowInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXWindowInfo* cobj = JSB_ALLOC(cocos2d::GFXWindowInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXWindowInfo* cobj = JSB_ALLOC(cocos2d::GFXWindowInfo);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 11)
    {
        cocos2d::GFXWindowInfo* cobj = JSB_ALLOC(cocos2d::GFXWindowInfo);
        cocos2d::String arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->title = arg0;
        }
        int arg1 = {};
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->left = arg1;
        }
        int arg2 = {};
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->top = arg2;
        }
        unsigned int arg3 = {};
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->width = arg3;
        }
        unsigned int arg4 = {};
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->height = arg4;
        }
        cocos2d::GFXFormat arg5;
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->colorFmt = arg5;
        }
        cocos2d::GFXFormat arg6;
        if (!args[6].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[6], &arg6); //is_reference False;
            cobj->depthStencilFmt = arg6;
        }
        bool arg7;
        if (!args[7].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[7], &arg7); //is_reference False;
            cobj->isOffscreen = arg7;
        }
        bool arg8;
        if (!args[8].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[8], &arg8); //is_reference False;
            cobj->isFullscreen = arg8;
        }
        cocos2d::GFXVsyncMode arg9;
        if (!args[9].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[9], &arg9); //is_reference False;
            cobj->vsyncMode = arg9;
        }
        uintptr_t arg10 = {};
        if (!args[10].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[10], &arg10); //is_reference False;
            cobj->windowHandle = arg10;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXWindowInfo_constructor, __jsb_cocos2d_GFXWindowInfo_class, js_cocos2d_GFXWindowInfo_finalize)




static bool js_cocos2d_GFXWindowInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXWindowInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXWindowInfo* cobj = (cocos2d::GFXWindowInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXWindowInfo_finalize)

bool js_register_gfx_GFXWindowInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXWindowInfo", obj, nullptr, _SE(js_gfx_GFXWindowInfo_constructor));

    cls->defineProperty("title", _SE(js_gfx_GFXWindowInfo_get_title), _SE(js_gfx_GFXWindowInfo_set_title));
    cls->defineProperty("left", _SE(js_gfx_GFXWindowInfo_get_left), _SE(js_gfx_GFXWindowInfo_set_left));
    cls->defineProperty("top", _SE(js_gfx_GFXWindowInfo_get_top), _SE(js_gfx_GFXWindowInfo_set_top));
    cls->defineProperty("width", _SE(js_gfx_GFXWindowInfo_get_width), _SE(js_gfx_GFXWindowInfo_set_width));
    cls->defineProperty("height", _SE(js_gfx_GFXWindowInfo_get_height), _SE(js_gfx_GFXWindowInfo_set_height));
    cls->defineProperty("colorFmt", _SE(js_gfx_GFXWindowInfo_get_colorFmt), _SE(js_gfx_GFXWindowInfo_set_colorFmt));
    cls->defineProperty("depthStencilFmt", _SE(js_gfx_GFXWindowInfo_get_depthStencilFmt), _SE(js_gfx_GFXWindowInfo_set_depthStencilFmt));
    cls->defineProperty("isOffscreen", _SE(js_gfx_GFXWindowInfo_get_isOffscreen), _SE(js_gfx_GFXWindowInfo_set_isOffscreen));
    cls->defineProperty("isFullscreen", _SE(js_gfx_GFXWindowInfo_get_isFullscreen), _SE(js_gfx_GFXWindowInfo_set_isFullscreen));
    cls->defineProperty("vsyncMode", _SE(js_gfx_GFXWindowInfo_get_vsyncMode), _SE(js_gfx_GFXWindowInfo_set_vsyncMode));
    cls->defineProperty("windowHandle", _SE(js_gfx_GFXWindowInfo_get_windowHandle), _SE(js_gfx_GFXWindowInfo_set_windowHandle));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXWindowInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXWindowInfo>(cls);

    __jsb_cocos2d_GFXWindowInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXWindowInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXContextInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXContextInfo_class = nullptr;

static bool js_gfx_GFXContextInfo_get_windowHandle(se::State& s)
{
    cocos2d::GFXContextInfo* cobj = (cocos2d::GFXContextInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXContextInfo_get_windowHandle : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->windowHandle, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXContextInfo_get_windowHandle)

static bool js_gfx_GFXContextInfo_set_windowHandle(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXContextInfo* cobj = (cocos2d::GFXContextInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXContextInfo_set_windowHandle : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->windowHandle); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXContextInfo_set_windowHandle : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXContextInfo_set_windowHandle)

static bool js_gfx_GFXContextInfo_get_vsyncMode(se::State& s)
{
    cocos2d::GFXContextInfo* cobj = (cocos2d::GFXContextInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXContextInfo_get_vsyncMode : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->vsyncMode, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXContextInfo_get_vsyncMode)

static bool js_gfx_GFXContextInfo_set_vsyncMode(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXContextInfo* cobj = (cocos2d::GFXContextInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXContextInfo_set_vsyncMode : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->vsyncMode); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXContextInfo_set_vsyncMode : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXContextInfo_set_vsyncMode)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXContextInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXContextInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("windowHandle", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->windowHandle));
    }
    json->getProperty("sharedCtx", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->sharedCtx));
    }
    json->getProperty("vsyncMode", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->vsyncMode));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXContextInfo_finalize)

static bool js_gfx_GFXContextInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXContextInfo* cobj = JSB_ALLOC(cocos2d::GFXContextInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXContextInfo* cobj = JSB_ALLOC(cocos2d::GFXContextInfo);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 3)
    {
        cocos2d::GFXContextInfo* cobj = JSB_ALLOC(cocos2d::GFXContextInfo);
        uintptr_t arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->windowHandle = arg0;
        }
        cocos2d::GFXContext* arg1 = nullptr;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->sharedCtx = arg1;
        }
        cocos2d::GFXVsyncMode arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->vsyncMode = arg2;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXContextInfo_constructor, __jsb_cocos2d_GFXContextInfo_class, js_cocos2d_GFXContextInfo_finalize)




static bool js_cocos2d_GFXContextInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXContextInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXContextInfo* cobj = (cocos2d::GFXContextInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXContextInfo_finalize)

bool js_register_gfx_GFXContextInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXContextInfo", obj, nullptr, _SE(js_gfx_GFXContextInfo_constructor));

    cls->defineProperty("windowHandle", _SE(js_gfx_GFXContextInfo_get_windowHandle), _SE(js_gfx_GFXContextInfo_set_windowHandle));
    cls->defineProperty("vsyncMode", _SE(js_gfx_GFXContextInfo_get_vsyncMode), _SE(js_gfx_GFXContextInfo_set_vsyncMode));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXContextInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXContextInfo>(cls);

    __jsb_cocos2d_GFXContextInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXContextInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXBufferInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXBufferInfo_class = nullptr;

static bool js_gfx_GFXBufferInfo_get_usage(se::State& s)
{
    cocos2d::GFXBufferInfo* cobj = (cocos2d::GFXBufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferInfo_get_usage : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->usage, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBufferInfo_get_usage)

static bool js_gfx_GFXBufferInfo_set_usage(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBufferInfo* cobj = (cocos2d::GFXBufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferInfo_set_usage : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->usage); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBufferInfo_set_usage : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBufferInfo_set_usage)

static bool js_gfx_GFXBufferInfo_get_memUsage(se::State& s)
{
    cocos2d::GFXBufferInfo* cobj = (cocos2d::GFXBufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferInfo_get_memUsage : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->memUsage, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBufferInfo_get_memUsage)

static bool js_gfx_GFXBufferInfo_set_memUsage(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBufferInfo* cobj = (cocos2d::GFXBufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferInfo_set_memUsage : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->memUsage); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBufferInfo_set_memUsage : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBufferInfo_set_memUsage)

static bool js_gfx_GFXBufferInfo_get_stride(se::State& s)
{
    cocos2d::GFXBufferInfo* cobj = (cocos2d::GFXBufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferInfo_get_stride : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stride, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBufferInfo_get_stride)

static bool js_gfx_GFXBufferInfo_set_stride(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBufferInfo* cobj = (cocos2d::GFXBufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferInfo_set_stride : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stride); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBufferInfo_set_stride : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBufferInfo_set_stride)

static bool js_gfx_GFXBufferInfo_get_size(se::State& s)
{
    cocos2d::GFXBufferInfo* cobj = (cocos2d::GFXBufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferInfo_get_size : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->size, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBufferInfo_get_size)

static bool js_gfx_GFXBufferInfo_set_size(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBufferInfo* cobj = (cocos2d::GFXBufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferInfo_set_size : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->size); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBufferInfo_set_size : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBufferInfo_set_size)

static bool js_gfx_GFXBufferInfo_get_flags(se::State& s)
{
    cocos2d::GFXBufferInfo* cobj = (cocos2d::GFXBufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferInfo_get_flags : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->flags, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBufferInfo_get_flags)

static bool js_gfx_GFXBufferInfo_set_flags(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBufferInfo* cobj = (cocos2d::GFXBufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBufferInfo_set_flags : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->flags); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBufferInfo_set_flags : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBufferInfo_set_flags)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXBufferInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXBufferInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("usage", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->usage));
    }
    json->getProperty("memUsage", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->memUsage));
    }
    json->getProperty("stride", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stride));
    }
    json->getProperty("size", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->size));
    }
    json->getProperty("flags", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->flags));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXBufferInfo_finalize)

static bool js_gfx_GFXBufferInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXBufferInfo* cobj = JSB_ALLOC(cocos2d::GFXBufferInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXBufferInfo* cobj = JSB_ALLOC(cocos2d::GFXBufferInfo);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 5)
    {
        cocos2d::GFXBufferInfo* cobj = JSB_ALLOC(cocos2d::GFXBufferInfo);
        cocos2d::GFXBufferUsageBit arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->usage = arg0;
        }
        cocos2d::GFXMemoryUsageBit arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->memUsage = arg1;
        }
        unsigned int arg2 = {};
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->stride = arg2;
        }
        unsigned int arg3 = {};
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->size = arg3;
        }
        cocos2d::GFXBufferFlagBit arg4;
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->flags = arg4;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXBufferInfo_constructor, __jsb_cocos2d_GFXBufferInfo_class, js_cocos2d_GFXBufferInfo_finalize)




static bool js_cocos2d_GFXBufferInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXBufferInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXBufferInfo* cobj = (cocos2d::GFXBufferInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXBufferInfo_finalize)

bool js_register_gfx_GFXBufferInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXBufferInfo", obj, nullptr, _SE(js_gfx_GFXBufferInfo_constructor));

    cls->defineProperty("usage", _SE(js_gfx_GFXBufferInfo_get_usage), _SE(js_gfx_GFXBufferInfo_set_usage));
    cls->defineProperty("memUsage", _SE(js_gfx_GFXBufferInfo_get_memUsage), _SE(js_gfx_GFXBufferInfo_set_memUsage));
    cls->defineProperty("stride", _SE(js_gfx_GFXBufferInfo_get_stride), _SE(js_gfx_GFXBufferInfo_set_stride));
    cls->defineProperty("size", _SE(js_gfx_GFXBufferInfo_get_size), _SE(js_gfx_GFXBufferInfo_set_size));
    cls->defineProperty("flags", _SE(js_gfx_GFXBufferInfo_get_flags), _SE(js_gfx_GFXBufferInfo_set_flags));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXBufferInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXBufferInfo>(cls);

    __jsb_cocos2d_GFXBufferInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXBufferInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXDrawInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXDrawInfo_class = nullptr;

static bool js_gfx_GFXDrawInfo_get_vertexCount(se::State& s)
{
    cocos2d::GFXDrawInfo* cobj = (cocos2d::GFXDrawInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDrawInfo_get_vertexCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->vertexCount, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDrawInfo_get_vertexCount)

static bool js_gfx_GFXDrawInfo_set_vertexCount(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDrawInfo* cobj = (cocos2d::GFXDrawInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDrawInfo_set_vertexCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->vertexCount); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDrawInfo_set_vertexCount : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDrawInfo_set_vertexCount)

static bool js_gfx_GFXDrawInfo_get_firstVertex(se::State& s)
{
    cocos2d::GFXDrawInfo* cobj = (cocos2d::GFXDrawInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDrawInfo_get_firstVertex : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->firstVertex, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDrawInfo_get_firstVertex)

static bool js_gfx_GFXDrawInfo_set_firstVertex(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDrawInfo* cobj = (cocos2d::GFXDrawInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDrawInfo_set_firstVertex : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->firstVertex); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDrawInfo_set_firstVertex : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDrawInfo_set_firstVertex)

static bool js_gfx_GFXDrawInfo_get_indexCount(se::State& s)
{
    cocos2d::GFXDrawInfo* cobj = (cocos2d::GFXDrawInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDrawInfo_get_indexCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->indexCount, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDrawInfo_get_indexCount)

static bool js_gfx_GFXDrawInfo_set_indexCount(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDrawInfo* cobj = (cocos2d::GFXDrawInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDrawInfo_set_indexCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->indexCount); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDrawInfo_set_indexCount : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDrawInfo_set_indexCount)

static bool js_gfx_GFXDrawInfo_get_firstIndex(se::State& s)
{
    cocos2d::GFXDrawInfo* cobj = (cocos2d::GFXDrawInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDrawInfo_get_firstIndex : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->firstIndex, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDrawInfo_get_firstIndex)

static bool js_gfx_GFXDrawInfo_set_firstIndex(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDrawInfo* cobj = (cocos2d::GFXDrawInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDrawInfo_set_firstIndex : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->firstIndex); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDrawInfo_set_firstIndex : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDrawInfo_set_firstIndex)

static bool js_gfx_GFXDrawInfo_get_vertexOffset(se::State& s)
{
    cocos2d::GFXDrawInfo* cobj = (cocos2d::GFXDrawInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDrawInfo_get_vertexOffset : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->vertexOffset, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDrawInfo_get_vertexOffset)

static bool js_gfx_GFXDrawInfo_set_vertexOffset(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDrawInfo* cobj = (cocos2d::GFXDrawInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDrawInfo_set_vertexOffset : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->vertexOffset); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDrawInfo_set_vertexOffset : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDrawInfo_set_vertexOffset)

static bool js_gfx_GFXDrawInfo_get_instanceCount(se::State& s)
{
    cocos2d::GFXDrawInfo* cobj = (cocos2d::GFXDrawInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDrawInfo_get_instanceCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->instanceCount, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDrawInfo_get_instanceCount)

static bool js_gfx_GFXDrawInfo_set_instanceCount(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDrawInfo* cobj = (cocos2d::GFXDrawInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDrawInfo_set_instanceCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->instanceCount); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDrawInfo_set_instanceCount : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDrawInfo_set_instanceCount)

static bool js_gfx_GFXDrawInfo_get_firstInstance(se::State& s)
{
    cocos2d::GFXDrawInfo* cobj = (cocos2d::GFXDrawInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDrawInfo_get_firstInstance : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->firstInstance, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDrawInfo_get_firstInstance)

static bool js_gfx_GFXDrawInfo_set_firstInstance(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDrawInfo* cobj = (cocos2d::GFXDrawInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDrawInfo_set_firstInstance : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->firstInstance); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDrawInfo_set_firstInstance : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDrawInfo_set_firstInstance)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXDrawInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXDrawInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("vertexCount", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->vertexCount));
    }
    json->getProperty("firstVertex", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->firstVertex));
    }
    json->getProperty("indexCount", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->indexCount));
    }
    json->getProperty("firstIndex", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->firstIndex));
    }
    json->getProperty("vertexOffset", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->vertexOffset));
    }
    json->getProperty("instanceCount", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->instanceCount));
    }
    json->getProperty("firstInstance", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->firstInstance));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXDrawInfo_finalize)

static bool js_gfx_GFXDrawInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXDrawInfo* cobj = JSB_ALLOC(cocos2d::GFXDrawInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXDrawInfo* cobj = JSB_ALLOC(cocos2d::GFXDrawInfo);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 7)
    {
        cocos2d::GFXDrawInfo* cobj = JSB_ALLOC(cocos2d::GFXDrawInfo);
        unsigned int arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->vertexCount = arg0;
        }
        unsigned int arg1 = {};
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->firstVertex = arg1;
        }
        unsigned int arg2 = {};
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->indexCount = arg2;
        }
        unsigned int arg3 = {};
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->firstIndex = arg3;
        }
        unsigned int arg4 = {};
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->vertexOffset = arg4;
        }
        unsigned int arg5 = {};
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->instanceCount = arg5;
        }
        unsigned int arg6 = {};
        if (!args[6].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[6], &arg6); //is_reference False;
            cobj->firstInstance = arg6;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXDrawInfo_constructor, __jsb_cocos2d_GFXDrawInfo_class, js_cocos2d_GFXDrawInfo_finalize)




static bool js_cocos2d_GFXDrawInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXDrawInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXDrawInfo* cobj = (cocos2d::GFXDrawInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXDrawInfo_finalize)

bool js_register_gfx_GFXDrawInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXDrawInfo", obj, nullptr, _SE(js_gfx_GFXDrawInfo_constructor));

    cls->defineProperty("vertexCount", _SE(js_gfx_GFXDrawInfo_get_vertexCount), _SE(js_gfx_GFXDrawInfo_set_vertexCount));
    cls->defineProperty("firstVertex", _SE(js_gfx_GFXDrawInfo_get_firstVertex), _SE(js_gfx_GFXDrawInfo_set_firstVertex));
    cls->defineProperty("indexCount", _SE(js_gfx_GFXDrawInfo_get_indexCount), _SE(js_gfx_GFXDrawInfo_set_indexCount));
    cls->defineProperty("firstIndex", _SE(js_gfx_GFXDrawInfo_get_firstIndex), _SE(js_gfx_GFXDrawInfo_set_firstIndex));
    cls->defineProperty("vertexOffset", _SE(js_gfx_GFXDrawInfo_get_vertexOffset), _SE(js_gfx_GFXDrawInfo_set_vertexOffset));
    cls->defineProperty("instanceCount", _SE(js_gfx_GFXDrawInfo_get_instanceCount), _SE(js_gfx_GFXDrawInfo_set_instanceCount));
    cls->defineProperty("firstInstance", _SE(js_gfx_GFXDrawInfo_get_firstInstance), _SE(js_gfx_GFXDrawInfo_set_firstInstance));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXDrawInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXDrawInfo>(cls);

    __jsb_cocos2d_GFXDrawInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXDrawInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXIndirectBuffer_proto = nullptr;
se::Class* __jsb_cocos2d_GFXIndirectBuffer_class = nullptr;

static bool js_gfx_GFXIndirectBuffer_get_drawInfos(se::State& s)
{
    cocos2d::GFXIndirectBuffer* cobj = (cocos2d::GFXIndirectBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXIndirectBuffer_get_drawInfos : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->drawInfos, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXIndirectBuffer_get_drawInfos)

static bool js_gfx_GFXIndirectBuffer_set_drawInfos(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXIndirectBuffer* cobj = (cocos2d::GFXIndirectBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXIndirectBuffer_set_drawInfos : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->drawInfos); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXIndirectBuffer_set_drawInfos : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXIndirectBuffer_set_drawInfos)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXIndirectBuffer * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXIndirectBuffer*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("drawInfos", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->drawInfos));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXIndirectBuffer_finalize)

static bool js_gfx_GFXIndirectBuffer_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXIndirectBuffer* cobj = JSB_ALLOC(cocos2d::GFXIndirectBuffer);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1)
    {
        cocos2d::GFXIndirectBuffer* cobj = JSB_ALLOC(cocos2d::GFXIndirectBuffer);
        std::vector<cocos2d::GFXDrawInfo> arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->drawInfos = arg0;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXIndirectBuffer_constructor, __jsb_cocos2d_GFXIndirectBuffer_class, js_cocos2d_GFXIndirectBuffer_finalize)




static bool js_cocos2d_GFXIndirectBuffer_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXIndirectBuffer)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXIndirectBuffer* cobj = (cocos2d::GFXIndirectBuffer*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXIndirectBuffer_finalize)

bool js_register_gfx_GFXIndirectBuffer(se::Object* obj)
{
    auto cls = se::Class::create("GFXIndirectBuffer", obj, nullptr, _SE(js_gfx_GFXIndirectBuffer_constructor));

    cls->defineProperty("drawInfos", _SE(js_gfx_GFXIndirectBuffer_get_drawInfos), _SE(js_gfx_GFXIndirectBuffer_set_drawInfos));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXIndirectBuffer_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXIndirectBuffer>(cls);

    __jsb_cocos2d_GFXIndirectBuffer_proto = cls->getProto();
    __jsb_cocos2d_GFXIndirectBuffer_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXTextureInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXTextureInfo_class = nullptr;

static bool js_gfx_GFXTextureInfo_get_type(se::State& s)
{
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_get_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->type, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureInfo_get_type)

static bool js_gfx_GFXTextureInfo_set_type(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_set_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->type); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureInfo_set_type : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureInfo_set_type)

static bool js_gfx_GFXTextureInfo_get_usage(se::State& s)
{
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_get_usage : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->usage, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureInfo_get_usage)

static bool js_gfx_GFXTextureInfo_set_usage(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_set_usage : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->usage); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureInfo_set_usage : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureInfo_set_usage)

static bool js_gfx_GFXTextureInfo_get_format(se::State& s)
{
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_get_format : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->format, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureInfo_get_format)

static bool js_gfx_GFXTextureInfo_set_format(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_set_format : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->format); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureInfo_set_format : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureInfo_set_format)

static bool js_gfx_GFXTextureInfo_get_width(se::State& s)
{
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_get_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->width, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureInfo_get_width)

static bool js_gfx_GFXTextureInfo_set_width(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_set_width : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->width); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureInfo_set_width : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureInfo_set_width)

static bool js_gfx_GFXTextureInfo_get_height(se::State& s)
{
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_get_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->height, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureInfo_get_height)

static bool js_gfx_GFXTextureInfo_set_height(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_set_height : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->height); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureInfo_set_height : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureInfo_set_height)

static bool js_gfx_GFXTextureInfo_get_depth(se::State& s)
{
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_get_depth : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->depth, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureInfo_get_depth)

static bool js_gfx_GFXTextureInfo_set_depth(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_set_depth : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->depth); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureInfo_set_depth : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureInfo_set_depth)

static bool js_gfx_GFXTextureInfo_get_arrayLayer(se::State& s)
{
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_get_arrayLayer : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->arrayLayer, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureInfo_get_arrayLayer)

static bool js_gfx_GFXTextureInfo_set_arrayLayer(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_set_arrayLayer : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->arrayLayer); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureInfo_set_arrayLayer : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureInfo_set_arrayLayer)

static bool js_gfx_GFXTextureInfo_get_mipLevel(se::State& s)
{
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_get_mipLevel : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->mipLevel, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureInfo_get_mipLevel)

static bool js_gfx_GFXTextureInfo_set_mipLevel(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_set_mipLevel : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->mipLevel); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureInfo_set_mipLevel : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureInfo_set_mipLevel)

static bool js_gfx_GFXTextureInfo_get_samples(se::State& s)
{
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_get_samples : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->samples, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureInfo_get_samples)

static bool js_gfx_GFXTextureInfo_set_samples(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_set_samples : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->samples); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureInfo_set_samples : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureInfo_set_samples)

static bool js_gfx_GFXTextureInfo_get_flags(se::State& s)
{
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_get_flags : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->flags, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureInfo_get_flags)

static bool js_gfx_GFXTextureInfo_set_flags(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureInfo_set_flags : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->flags); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureInfo_set_flags : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureInfo_set_flags)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXTextureInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXTextureInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("type", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->type));
    }
    json->getProperty("usage", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->usage));
    }
    json->getProperty("format", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->format));
    }
    json->getProperty("width", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->width));
    }
    json->getProperty("height", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->height));
    }
    json->getProperty("depth", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->depth));
    }
    json->getProperty("arrayLayer", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->arrayLayer));
    }
    json->getProperty("mipLevel", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->mipLevel));
    }
    json->getProperty("samples", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->samples));
    }
    json->getProperty("flags", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->flags));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXTextureInfo_finalize)

static bool js_gfx_GFXTextureInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXTextureInfo* cobj = JSB_ALLOC(cocos2d::GFXTextureInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXTextureInfo* cobj = JSB_ALLOC(cocos2d::GFXTextureInfo);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 10)
    {
        cocos2d::GFXTextureInfo* cobj = JSB_ALLOC(cocos2d::GFXTextureInfo);
        cocos2d::GFXTextureType arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->type = arg0;
        }
        cocos2d::GFXTextureUsageBit arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->usage = arg1;
        }
        cocos2d::GFXFormat arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->format = arg2;
        }
        unsigned int arg3 = {};
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->width = arg3;
        }
        unsigned int arg4 = {};
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->height = arg4;
        }
        unsigned int arg5 = {};
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->depth = arg5;
        }
        unsigned int arg6 = {};
        if (!args[6].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[6], &arg6); //is_reference False;
            cobj->arrayLayer = arg6;
        }
        unsigned int arg7 = {};
        if (!args[7].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[7], &arg7); //is_reference False;
            cobj->mipLevel = arg7;
        }
        cocos2d::GFXSampleCount arg8;
        if (!args[8].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[8], &arg8); //is_reference False;
            cobj->samples = arg8;
        }
        cocos2d::GFXTextureFlagBit arg9;
        if (!args[9].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[9], &arg9); //is_reference False;
            cobj->flags = arg9;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXTextureInfo_constructor, __jsb_cocos2d_GFXTextureInfo_class, js_cocos2d_GFXTextureInfo_finalize)




static bool js_cocos2d_GFXTextureInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXTextureInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXTextureInfo* cobj = (cocos2d::GFXTextureInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXTextureInfo_finalize)

bool js_register_gfx_GFXTextureInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXTextureInfo", obj, nullptr, _SE(js_gfx_GFXTextureInfo_constructor));

    cls->defineProperty("type", _SE(js_gfx_GFXTextureInfo_get_type), _SE(js_gfx_GFXTextureInfo_set_type));
    cls->defineProperty("usage", _SE(js_gfx_GFXTextureInfo_get_usage), _SE(js_gfx_GFXTextureInfo_set_usage));
    cls->defineProperty("format", _SE(js_gfx_GFXTextureInfo_get_format), _SE(js_gfx_GFXTextureInfo_set_format));
    cls->defineProperty("width", _SE(js_gfx_GFXTextureInfo_get_width), _SE(js_gfx_GFXTextureInfo_set_width));
    cls->defineProperty("height", _SE(js_gfx_GFXTextureInfo_get_height), _SE(js_gfx_GFXTextureInfo_set_height));
    cls->defineProperty("depth", _SE(js_gfx_GFXTextureInfo_get_depth), _SE(js_gfx_GFXTextureInfo_set_depth));
    cls->defineProperty("arrayLayer", _SE(js_gfx_GFXTextureInfo_get_arrayLayer), _SE(js_gfx_GFXTextureInfo_set_arrayLayer));
    cls->defineProperty("mipLevel", _SE(js_gfx_GFXTextureInfo_get_mipLevel), _SE(js_gfx_GFXTextureInfo_set_mipLevel));
    cls->defineProperty("samples", _SE(js_gfx_GFXTextureInfo_get_samples), _SE(js_gfx_GFXTextureInfo_set_samples));
    cls->defineProperty("flags", _SE(js_gfx_GFXTextureInfo_get_flags), _SE(js_gfx_GFXTextureInfo_set_flags));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXTextureInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXTextureInfo>(cls);

    __jsb_cocos2d_GFXTextureInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXTextureInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXTextureViewInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXTextureViewInfo_class = nullptr;

static bool js_gfx_GFXTextureViewInfo_get_texture(se::State& s)
{
    cocos2d::GFXTextureViewInfo* cobj = (cocos2d::GFXTextureViewInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureViewInfo_get_texture : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->texture, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureViewInfo_get_texture)

static bool js_gfx_GFXTextureViewInfo_set_texture(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureViewInfo* cobj = (cocos2d::GFXTextureViewInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureViewInfo_set_texture : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->texture); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureViewInfo_set_texture : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureViewInfo_set_texture)

static bool js_gfx_GFXTextureViewInfo_get_type(se::State& s)
{
    cocos2d::GFXTextureViewInfo* cobj = (cocos2d::GFXTextureViewInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureViewInfo_get_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->type, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureViewInfo_get_type)

static bool js_gfx_GFXTextureViewInfo_set_type(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureViewInfo* cobj = (cocos2d::GFXTextureViewInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureViewInfo_set_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->type); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureViewInfo_set_type : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureViewInfo_set_type)

static bool js_gfx_GFXTextureViewInfo_get_format(se::State& s)
{
    cocos2d::GFXTextureViewInfo* cobj = (cocos2d::GFXTextureViewInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureViewInfo_get_format : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->format, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureViewInfo_get_format)

static bool js_gfx_GFXTextureViewInfo_set_format(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureViewInfo* cobj = (cocos2d::GFXTextureViewInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureViewInfo_set_format : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->format); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureViewInfo_set_format : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureViewInfo_set_format)

static bool js_gfx_GFXTextureViewInfo_get_baseLevel(se::State& s)
{
    cocos2d::GFXTextureViewInfo* cobj = (cocos2d::GFXTextureViewInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureViewInfo_get_baseLevel : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->baseLevel, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureViewInfo_get_baseLevel)

static bool js_gfx_GFXTextureViewInfo_set_baseLevel(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureViewInfo* cobj = (cocos2d::GFXTextureViewInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureViewInfo_set_baseLevel : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->baseLevel); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureViewInfo_set_baseLevel : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureViewInfo_set_baseLevel)

static bool js_gfx_GFXTextureViewInfo_get_levelCount(se::State& s)
{
    cocos2d::GFXTextureViewInfo* cobj = (cocos2d::GFXTextureViewInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureViewInfo_get_levelCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->levelCount, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureViewInfo_get_levelCount)

static bool js_gfx_GFXTextureViewInfo_set_levelCount(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureViewInfo* cobj = (cocos2d::GFXTextureViewInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureViewInfo_set_levelCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->levelCount); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureViewInfo_set_levelCount : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureViewInfo_set_levelCount)

static bool js_gfx_GFXTextureViewInfo_get_baseLayer(se::State& s)
{
    cocos2d::GFXTextureViewInfo* cobj = (cocos2d::GFXTextureViewInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureViewInfo_get_baseLayer : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->baseLayer, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureViewInfo_get_baseLayer)

static bool js_gfx_GFXTextureViewInfo_set_baseLayer(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureViewInfo* cobj = (cocos2d::GFXTextureViewInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureViewInfo_set_baseLayer : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->baseLayer); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureViewInfo_set_baseLayer : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureViewInfo_set_baseLayer)

static bool js_gfx_GFXTextureViewInfo_get_layerCount(se::State& s)
{
    cocos2d::GFXTextureViewInfo* cobj = (cocos2d::GFXTextureViewInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureViewInfo_get_layerCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->layerCount, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureViewInfo_get_layerCount)

static bool js_gfx_GFXTextureViewInfo_set_layerCount(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXTextureViewInfo* cobj = (cocos2d::GFXTextureViewInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureViewInfo_set_layerCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->layerCount); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureViewInfo_set_layerCount : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXTextureViewInfo_set_layerCount)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXTextureViewInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXTextureViewInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("texture", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->texture));
    }
    json->getProperty("type", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->type));
    }
    json->getProperty("format", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->format));
    }
    json->getProperty("baseLevel", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->baseLevel));
    }
    json->getProperty("levelCount", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->levelCount));
    }
    json->getProperty("baseLayer", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->baseLayer));
    }
    json->getProperty("layerCount", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->layerCount));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXTextureViewInfo_finalize)

static bool js_gfx_GFXTextureViewInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXTextureViewInfo* cobj = JSB_ALLOC(cocos2d::GFXTextureViewInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXTextureViewInfo* cobj = JSB_ALLOC(cocos2d::GFXTextureViewInfo);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 7)
    {
        cocos2d::GFXTextureViewInfo* cobj = JSB_ALLOC(cocos2d::GFXTextureViewInfo);
        cocos2d::GFXTexture* arg0 = nullptr;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->texture = arg0;
        }
        cocos2d::GFXTextureViewType arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->type = arg1;
        }
        cocos2d::GFXFormat arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->format = arg2;
        }
        unsigned int arg3 = {};
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->baseLevel = arg3;
        }
        unsigned int arg4 = {};
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->levelCount = arg4;
        }
        unsigned int arg5 = {};
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->baseLayer = arg5;
        }
        unsigned int arg6 = {};
        if (!args[6].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[6], &arg6); //is_reference False;
            cobj->layerCount = arg6;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXTextureViewInfo_constructor, __jsb_cocos2d_GFXTextureViewInfo_class, js_cocos2d_GFXTextureViewInfo_finalize)




static bool js_cocos2d_GFXTextureViewInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXTextureViewInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXTextureViewInfo* cobj = (cocos2d::GFXTextureViewInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXTextureViewInfo_finalize)

bool js_register_gfx_GFXTextureViewInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXTextureViewInfo", obj, nullptr, _SE(js_gfx_GFXTextureViewInfo_constructor));

    cls->defineProperty("texture", _SE(js_gfx_GFXTextureViewInfo_get_texture), _SE(js_gfx_GFXTextureViewInfo_set_texture));
    cls->defineProperty("type", _SE(js_gfx_GFXTextureViewInfo_get_type), _SE(js_gfx_GFXTextureViewInfo_set_type));
    cls->defineProperty("format", _SE(js_gfx_GFXTextureViewInfo_get_format), _SE(js_gfx_GFXTextureViewInfo_set_format));
    cls->defineProperty("baseLevel", _SE(js_gfx_GFXTextureViewInfo_get_baseLevel), _SE(js_gfx_GFXTextureViewInfo_set_baseLevel));
    cls->defineProperty("levelCount", _SE(js_gfx_GFXTextureViewInfo_get_levelCount), _SE(js_gfx_GFXTextureViewInfo_set_levelCount));
    cls->defineProperty("baseLayer", _SE(js_gfx_GFXTextureViewInfo_get_baseLayer), _SE(js_gfx_GFXTextureViewInfo_set_baseLayer));
    cls->defineProperty("layerCount", _SE(js_gfx_GFXTextureViewInfo_get_layerCount), _SE(js_gfx_GFXTextureViewInfo_set_layerCount));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXTextureViewInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXTextureViewInfo>(cls);

    __jsb_cocos2d_GFXTextureViewInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXTextureViewInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXSamplerInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXSamplerInfo_class = nullptr;

static bool js_gfx_GFXSamplerInfo_get_name(se::State& s)
{
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSamplerInfo_get_name)

static bool js_gfx_GFXSamplerInfo_set_name(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSamplerInfo_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSamplerInfo_set_name)

static bool js_gfx_GFXSamplerInfo_get_minFilter(se::State& s)
{
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_get_minFilter : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->minFilter, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSamplerInfo_get_minFilter)

static bool js_gfx_GFXSamplerInfo_set_minFilter(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_set_minFilter : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->minFilter); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSamplerInfo_set_minFilter : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSamplerInfo_set_minFilter)

static bool js_gfx_GFXSamplerInfo_get_magFilter(se::State& s)
{
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_get_magFilter : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->magFilter, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSamplerInfo_get_magFilter)

static bool js_gfx_GFXSamplerInfo_set_magFilter(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_set_magFilter : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->magFilter); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSamplerInfo_set_magFilter : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSamplerInfo_set_magFilter)

static bool js_gfx_GFXSamplerInfo_get_mipFilter(se::State& s)
{
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_get_mipFilter : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->mipFilter, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSamplerInfo_get_mipFilter)

static bool js_gfx_GFXSamplerInfo_set_mipFilter(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_set_mipFilter : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->mipFilter); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSamplerInfo_set_mipFilter : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSamplerInfo_set_mipFilter)

static bool js_gfx_GFXSamplerInfo_get_addressU(se::State& s)
{
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_get_addressU : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->addressU, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSamplerInfo_get_addressU)

static bool js_gfx_GFXSamplerInfo_set_addressU(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_set_addressU : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->addressU); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSamplerInfo_set_addressU : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSamplerInfo_set_addressU)

static bool js_gfx_GFXSamplerInfo_get_addressV(se::State& s)
{
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_get_addressV : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->addressV, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSamplerInfo_get_addressV)

static bool js_gfx_GFXSamplerInfo_set_addressV(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_set_addressV : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->addressV); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSamplerInfo_set_addressV : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSamplerInfo_set_addressV)

static bool js_gfx_GFXSamplerInfo_get_addressW(se::State& s)
{
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_get_addressW : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->addressW, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSamplerInfo_get_addressW)

static bool js_gfx_GFXSamplerInfo_set_addressW(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_set_addressW : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->addressW); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSamplerInfo_set_addressW : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSamplerInfo_set_addressW)

static bool js_gfx_GFXSamplerInfo_get_maxAnisotropy(se::State& s)
{
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_get_maxAnisotropy : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->maxAnisotropy, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSamplerInfo_get_maxAnisotropy)

static bool js_gfx_GFXSamplerInfo_set_maxAnisotropy(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_set_maxAnisotropy : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->maxAnisotropy); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSamplerInfo_set_maxAnisotropy : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSamplerInfo_set_maxAnisotropy)

static bool js_gfx_GFXSamplerInfo_get_cmpFunc(se::State& s)
{
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_get_cmpFunc : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->cmpFunc, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSamplerInfo_get_cmpFunc)

static bool js_gfx_GFXSamplerInfo_set_cmpFunc(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_set_cmpFunc : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->cmpFunc); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSamplerInfo_set_cmpFunc : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSamplerInfo_set_cmpFunc)

static bool js_gfx_GFXSamplerInfo_get_borderColor(se::State& s)
{
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_get_borderColor : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->borderColor, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSamplerInfo_get_borderColor)

static bool js_gfx_GFXSamplerInfo_set_borderColor(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_set_borderColor : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->borderColor); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSamplerInfo_set_borderColor : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSamplerInfo_set_borderColor)

static bool js_gfx_GFXSamplerInfo_get_minLOD(se::State& s)
{
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_get_minLOD : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->minLOD, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSamplerInfo_get_minLOD)

static bool js_gfx_GFXSamplerInfo_set_minLOD(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_set_minLOD : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->minLOD); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSamplerInfo_set_minLOD : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSamplerInfo_set_minLOD)

static bool js_gfx_GFXSamplerInfo_get_maxLOD(se::State& s)
{
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_get_maxLOD : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->maxLOD, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSamplerInfo_get_maxLOD)

static bool js_gfx_GFXSamplerInfo_set_maxLOD(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_set_maxLOD : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->maxLOD); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSamplerInfo_set_maxLOD : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSamplerInfo_set_maxLOD)

static bool js_gfx_GFXSamplerInfo_get_mipLODBias(se::State& s)
{
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_get_mipLODBias : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->mipLODBias, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSamplerInfo_get_mipLODBias)

static bool js_gfx_GFXSamplerInfo_set_mipLODBias(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSamplerInfo_set_mipLODBias : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->mipLODBias); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSamplerInfo_set_mipLODBias : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSamplerInfo_set_mipLODBias)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXSamplerInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXSamplerInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("name", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name));
    }
    json->getProperty("minFilter", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->minFilter));
    }
    json->getProperty("magFilter", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->magFilter));
    }
    json->getProperty("mipFilter", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->mipFilter));
    }
    json->getProperty("addressU", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->addressU));
    }
    json->getProperty("addressV", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->addressV));
    }
    json->getProperty("addressW", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->addressW));
    }
    json->getProperty("maxAnisotropy", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->maxAnisotropy));
    }
    json->getProperty("cmpFunc", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->cmpFunc));
    }
    json->getProperty("borderColor", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->borderColor));
    }
    json->getProperty("minLOD", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->minLOD));
    }
    json->getProperty("maxLOD", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->maxLOD));
    }
    json->getProperty("mipLODBias", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->mipLODBias));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXSamplerInfo_finalize)

static bool js_gfx_GFXSamplerInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXSamplerInfo* cobj = JSB_ALLOC(cocos2d::GFXSamplerInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXSamplerInfo* cobj = JSB_ALLOC(cocos2d::GFXSamplerInfo);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 13)
    {
        cocos2d::GFXSamplerInfo* cobj = JSB_ALLOC(cocos2d::GFXSamplerInfo);
        cocos2d::String arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->name = arg0;
        }
        cocos2d::GFXFilter arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->minFilter = arg1;
        }
        cocos2d::GFXFilter arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->magFilter = arg2;
        }
        cocos2d::GFXFilter arg3;
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->mipFilter = arg3;
        }
        cocos2d::GFXAddress arg4;
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->addressU = arg4;
        }
        cocos2d::GFXAddress arg5;
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->addressV = arg5;
        }
        cocos2d::GFXAddress arg6;
        if (!args[6].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[6], &arg6); //is_reference False;
            cobj->addressW = arg6;
        }
        unsigned int arg7 = {};
        if (!args[7].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[7], &arg7); //is_reference False;
            cobj->maxAnisotropy = arg7;
        }
        cocos2d::GFXComparisonFunc arg8;
        if (!args[8].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[8], &arg8); //is_reference False;
            cobj->cmpFunc = arg8;
        }
        cocos2d::GFXColor arg9;
        if (!args[9].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[9], &arg9); //is_reference False;
            cobj->borderColor = arg9;
        }
        unsigned int arg10 = {};
        if (!args[10].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[10], &arg10); //is_reference False;
            cobj->minLOD = arg10;
        }
        unsigned int arg11 = {};
        if (!args[11].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[11], &arg11); //is_reference False;
            cobj->maxLOD = arg11;
        }
        float arg12 = {};
        if (!args[12].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[12], &arg12); //is_reference False;
            cobj->mipLODBias = arg12;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXSamplerInfo_constructor, __jsb_cocos2d_GFXSamplerInfo_class, js_cocos2d_GFXSamplerInfo_finalize)




static bool js_cocos2d_GFXSamplerInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXSamplerInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXSamplerInfo* cobj = (cocos2d::GFXSamplerInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXSamplerInfo_finalize)

bool js_register_gfx_GFXSamplerInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXSamplerInfo", obj, nullptr, _SE(js_gfx_GFXSamplerInfo_constructor));

    cls->defineProperty("name", _SE(js_gfx_GFXSamplerInfo_get_name), _SE(js_gfx_GFXSamplerInfo_set_name));
    cls->defineProperty("minFilter", _SE(js_gfx_GFXSamplerInfo_get_minFilter), _SE(js_gfx_GFXSamplerInfo_set_minFilter));
    cls->defineProperty("magFilter", _SE(js_gfx_GFXSamplerInfo_get_magFilter), _SE(js_gfx_GFXSamplerInfo_set_magFilter));
    cls->defineProperty("mipFilter", _SE(js_gfx_GFXSamplerInfo_get_mipFilter), _SE(js_gfx_GFXSamplerInfo_set_mipFilter));
    cls->defineProperty("addressU", _SE(js_gfx_GFXSamplerInfo_get_addressU), _SE(js_gfx_GFXSamplerInfo_set_addressU));
    cls->defineProperty("addressV", _SE(js_gfx_GFXSamplerInfo_get_addressV), _SE(js_gfx_GFXSamplerInfo_set_addressV));
    cls->defineProperty("addressW", _SE(js_gfx_GFXSamplerInfo_get_addressW), _SE(js_gfx_GFXSamplerInfo_set_addressW));
    cls->defineProperty("maxAnisotropy", _SE(js_gfx_GFXSamplerInfo_get_maxAnisotropy), _SE(js_gfx_GFXSamplerInfo_set_maxAnisotropy));
    cls->defineProperty("cmpFunc", _SE(js_gfx_GFXSamplerInfo_get_cmpFunc), _SE(js_gfx_GFXSamplerInfo_set_cmpFunc));
    cls->defineProperty("borderColor", _SE(js_gfx_GFXSamplerInfo_get_borderColor), _SE(js_gfx_GFXSamplerInfo_set_borderColor));
    cls->defineProperty("minLOD", _SE(js_gfx_GFXSamplerInfo_get_minLOD), _SE(js_gfx_GFXSamplerInfo_set_minLOD));
    cls->defineProperty("maxLOD", _SE(js_gfx_GFXSamplerInfo_get_maxLOD), _SE(js_gfx_GFXSamplerInfo_set_maxLOD));
    cls->defineProperty("mipLODBias", _SE(js_gfx_GFXSamplerInfo_get_mipLODBias), _SE(js_gfx_GFXSamplerInfo_set_mipLODBias));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXSamplerInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXSamplerInfo>(cls);

    __jsb_cocos2d_GFXSamplerInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXSamplerInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXShaderMacro_proto = nullptr;
se::Class* __jsb_cocos2d_GFXShaderMacro_class = nullptr;

static bool js_gfx_GFXShaderMacro_get_macro(se::State& s)
{
    cocos2d::GFXShaderMacro* cobj = (cocos2d::GFXShaderMacro*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderMacro_get_macro : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->macro, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXShaderMacro_get_macro)

static bool js_gfx_GFXShaderMacro_set_macro(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXShaderMacro* cobj = (cocos2d::GFXShaderMacro*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderMacro_set_macro : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->macro); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXShaderMacro_set_macro : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXShaderMacro_set_macro)

static bool js_gfx_GFXShaderMacro_get_value(se::State& s)
{
    cocos2d::GFXShaderMacro* cobj = (cocos2d::GFXShaderMacro*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderMacro_get_value : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->value, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXShaderMacro_get_value)

static bool js_gfx_GFXShaderMacro_set_value(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXShaderMacro* cobj = (cocos2d::GFXShaderMacro*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderMacro_set_value : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->value); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXShaderMacro_set_value : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXShaderMacro_set_value)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXShaderMacro * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXShaderMacro*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("macro", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->macro));
    }
    json->getProperty("value", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->value));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXShaderMacro_finalize)

static bool js_gfx_GFXShaderMacro_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXShaderMacro* cobj = JSB_ALLOC(cocos2d::GFXShaderMacro);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXShaderMacro* cobj = JSB_ALLOC(cocos2d::GFXShaderMacro);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 2)
    {
        cocos2d::GFXShaderMacro* cobj = JSB_ALLOC(cocos2d::GFXShaderMacro);
        cocos2d::String arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->macro = arg0;
        }
        cocos2d::String arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->value = arg1;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXShaderMacro_constructor, __jsb_cocos2d_GFXShaderMacro_class, js_cocos2d_GFXShaderMacro_finalize)




static bool js_cocos2d_GFXShaderMacro_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXShaderMacro)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXShaderMacro* cobj = (cocos2d::GFXShaderMacro*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXShaderMacro_finalize)

bool js_register_gfx_GFXShaderMacro(se::Object* obj)
{
    auto cls = se::Class::create("GFXShaderMacro", obj, nullptr, _SE(js_gfx_GFXShaderMacro_constructor));

    cls->defineProperty("macro", _SE(js_gfx_GFXShaderMacro_get_macro), _SE(js_gfx_GFXShaderMacro_set_macro));
    cls->defineProperty("value", _SE(js_gfx_GFXShaderMacro_get_value), _SE(js_gfx_GFXShaderMacro_set_value));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXShaderMacro_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXShaderMacro>(cls);

    __jsb_cocos2d_GFXShaderMacro_proto = cls->getProto();
    __jsb_cocos2d_GFXShaderMacro_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXUniform_proto = nullptr;
se::Class* __jsb_cocos2d_GFXUniform_class = nullptr;

static bool js_gfx_GFXUniform_get_name(se::State& s)
{
    cocos2d::GFXUniform* cobj = (cocos2d::GFXUniform*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniform_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXUniform_get_name)

static bool js_gfx_GFXUniform_set_name(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXUniform* cobj = (cocos2d::GFXUniform*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniform_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXUniform_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXUniform_set_name)

static bool js_gfx_GFXUniform_get_type(se::State& s)
{
    cocos2d::GFXUniform* cobj = (cocos2d::GFXUniform*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniform_get_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->type, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXUniform_get_type)

static bool js_gfx_GFXUniform_set_type(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXUniform* cobj = (cocos2d::GFXUniform*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniform_set_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->type); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXUniform_set_type : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXUniform_set_type)

static bool js_gfx_GFXUniform_get_count(se::State& s)
{
    cocos2d::GFXUniform* cobj = (cocos2d::GFXUniform*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniform_get_count : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->count, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXUniform_get_count)

static bool js_gfx_GFXUniform_set_count(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXUniform* cobj = (cocos2d::GFXUniform*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniform_set_count : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->count); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXUniform_set_count : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXUniform_set_count)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXUniform * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXUniform*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("name", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name));
    }
    json->getProperty("type", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->type));
    }
    json->getProperty("count", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->count));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXUniform_finalize)

static bool js_gfx_GFXUniform_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXUniform* cobj = JSB_ALLOC(cocos2d::GFXUniform);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXUniform* cobj = JSB_ALLOC(cocos2d::GFXUniform);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 3)
    {
        cocos2d::GFXUniform* cobj = JSB_ALLOC(cocos2d::GFXUniform);
        cocos2d::String arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->name = arg0;
        }
        cocos2d::GFXType arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->type = arg1;
        }
        unsigned int arg2 = {};
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->count = arg2;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXUniform_constructor, __jsb_cocos2d_GFXUniform_class, js_cocos2d_GFXUniform_finalize)




static bool js_cocos2d_GFXUniform_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXUniform)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXUniform* cobj = (cocos2d::GFXUniform*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXUniform_finalize)

bool js_register_gfx_GFXUniform(se::Object* obj)
{
    auto cls = se::Class::create("GFXUniform", obj, nullptr, _SE(js_gfx_GFXUniform_constructor));

    cls->defineProperty("name", _SE(js_gfx_GFXUniform_get_name), _SE(js_gfx_GFXUniform_set_name));
    cls->defineProperty("type", _SE(js_gfx_GFXUniform_get_type), _SE(js_gfx_GFXUniform_set_type));
    cls->defineProperty("count", _SE(js_gfx_GFXUniform_get_count), _SE(js_gfx_GFXUniform_set_count));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXUniform_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXUniform>(cls);

    __jsb_cocos2d_GFXUniform_proto = cls->getProto();
    __jsb_cocos2d_GFXUniform_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXUniformBlock_proto = nullptr;
se::Class* __jsb_cocos2d_GFXUniformBlock_class = nullptr;

static bool js_gfx_GFXUniformBlock_get_binding(se::State& s)
{
    cocos2d::GFXUniformBlock* cobj = (cocos2d::GFXUniformBlock*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniformBlock_get_binding : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->binding, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXUniformBlock_get_binding)

static bool js_gfx_GFXUniformBlock_set_binding(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXUniformBlock* cobj = (cocos2d::GFXUniformBlock*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniformBlock_set_binding : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->binding); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXUniformBlock_set_binding : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXUniformBlock_set_binding)

static bool js_gfx_GFXUniformBlock_get_name(se::State& s)
{
    cocos2d::GFXUniformBlock* cobj = (cocos2d::GFXUniformBlock*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniformBlock_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXUniformBlock_get_name)

static bool js_gfx_GFXUniformBlock_set_name(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXUniformBlock* cobj = (cocos2d::GFXUniformBlock*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniformBlock_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXUniformBlock_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXUniformBlock_set_name)

static bool js_gfx_GFXUniformBlock_get_uniforms(se::State& s)
{
    cocos2d::GFXUniformBlock* cobj = (cocos2d::GFXUniformBlock*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniformBlock_get_uniforms : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->uniforms, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXUniformBlock_get_uniforms)

static bool js_gfx_GFXUniformBlock_set_uniforms(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXUniformBlock* cobj = (cocos2d::GFXUniformBlock*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniformBlock_set_uniforms : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->uniforms); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXUniformBlock_set_uniforms : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXUniformBlock_set_uniforms)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXUniformBlock * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXUniformBlock*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("binding", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->binding));
    }
    json->getProperty("name", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name));
    }
    json->getProperty("uniforms", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->uniforms));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXUniformBlock_finalize)

static bool js_gfx_GFXUniformBlock_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXUniformBlock* cobj = JSB_ALLOC(cocos2d::GFXUniformBlock);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXUniformBlock* cobj = JSB_ALLOC(cocos2d::GFXUniformBlock);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 3)
    {
        cocos2d::GFXUniformBlock* cobj = JSB_ALLOC(cocos2d::GFXUniformBlock);
        unsigned int arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->binding = arg0;
        }
        cocos2d::String arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->name = arg1;
        }
        std::vector<cocos2d::GFXUniform> arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->uniforms = arg2;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXUniformBlock_constructor, __jsb_cocos2d_GFXUniformBlock_class, js_cocos2d_GFXUniformBlock_finalize)




static bool js_cocos2d_GFXUniformBlock_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXUniformBlock)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXUniformBlock* cobj = (cocos2d::GFXUniformBlock*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXUniformBlock_finalize)

bool js_register_gfx_GFXUniformBlock(se::Object* obj)
{
    auto cls = se::Class::create("GFXUniformBlock", obj, nullptr, _SE(js_gfx_GFXUniformBlock_constructor));

    cls->defineProperty("binding", _SE(js_gfx_GFXUniformBlock_get_binding), _SE(js_gfx_GFXUniformBlock_set_binding));
    cls->defineProperty("name", _SE(js_gfx_GFXUniformBlock_get_name), _SE(js_gfx_GFXUniformBlock_set_name));
    cls->defineProperty("uniforms", _SE(js_gfx_GFXUniformBlock_get_uniforms), _SE(js_gfx_GFXUniformBlock_set_uniforms));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXUniformBlock_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXUniformBlock>(cls);

    __jsb_cocos2d_GFXUniformBlock_proto = cls->getProto();
    __jsb_cocos2d_GFXUniformBlock_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXUniformSampler_proto = nullptr;
se::Class* __jsb_cocos2d_GFXUniformSampler_class = nullptr;

static bool js_gfx_GFXUniformSampler_get_binding(se::State& s)
{
    cocos2d::GFXUniformSampler* cobj = (cocos2d::GFXUniformSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniformSampler_get_binding : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->binding, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXUniformSampler_get_binding)

static bool js_gfx_GFXUniformSampler_set_binding(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXUniformSampler* cobj = (cocos2d::GFXUniformSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniformSampler_set_binding : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->binding); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXUniformSampler_set_binding : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXUniformSampler_set_binding)

static bool js_gfx_GFXUniformSampler_get_name(se::State& s)
{
    cocos2d::GFXUniformSampler* cobj = (cocos2d::GFXUniformSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniformSampler_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXUniformSampler_get_name)

static bool js_gfx_GFXUniformSampler_set_name(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXUniformSampler* cobj = (cocos2d::GFXUniformSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniformSampler_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXUniformSampler_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXUniformSampler_set_name)

static bool js_gfx_GFXUniformSampler_get_type(se::State& s)
{
    cocos2d::GFXUniformSampler* cobj = (cocos2d::GFXUniformSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniformSampler_get_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->type, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXUniformSampler_get_type)

static bool js_gfx_GFXUniformSampler_set_type(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXUniformSampler* cobj = (cocos2d::GFXUniformSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniformSampler_set_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->type); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXUniformSampler_set_type : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXUniformSampler_set_type)

static bool js_gfx_GFXUniformSampler_get_count(se::State& s)
{
    cocos2d::GFXUniformSampler* cobj = (cocos2d::GFXUniformSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniformSampler_get_count : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->count, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXUniformSampler_get_count)

static bool js_gfx_GFXUniformSampler_set_count(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXUniformSampler* cobj = (cocos2d::GFXUniformSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXUniformSampler_set_count : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->count); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXUniformSampler_set_count : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXUniformSampler_set_count)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXUniformSampler * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXUniformSampler*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("binding", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->binding));
    }
    json->getProperty("name", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name));
    }
    json->getProperty("type", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->type));
    }
    json->getProperty("count", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->count));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXUniformSampler_finalize)

static bool js_gfx_GFXUniformSampler_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXUniformSampler* cobj = JSB_ALLOC(cocos2d::GFXUniformSampler);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXUniformSampler* cobj = JSB_ALLOC(cocos2d::GFXUniformSampler);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 4)
    {
        cocos2d::GFXUniformSampler* cobj = JSB_ALLOC(cocos2d::GFXUniformSampler);
        unsigned int arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->binding = arg0;
        }
        cocos2d::String arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->name = arg1;
        }
        cocos2d::GFXType arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->type = arg2;
        }
        unsigned int arg3 = {};
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->count = arg3;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXUniformSampler_constructor, __jsb_cocos2d_GFXUniformSampler_class, js_cocos2d_GFXUniformSampler_finalize)




static bool js_cocos2d_GFXUniformSampler_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXUniformSampler)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXUniformSampler* cobj = (cocos2d::GFXUniformSampler*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXUniformSampler_finalize)

bool js_register_gfx_GFXUniformSampler(se::Object* obj)
{
    auto cls = se::Class::create("GFXUniformSampler", obj, nullptr, _SE(js_gfx_GFXUniformSampler_constructor));

    cls->defineProperty("binding", _SE(js_gfx_GFXUniformSampler_get_binding), _SE(js_gfx_GFXUniformSampler_set_binding));
    cls->defineProperty("name", _SE(js_gfx_GFXUniformSampler_get_name), _SE(js_gfx_GFXUniformSampler_set_name));
    cls->defineProperty("type", _SE(js_gfx_GFXUniformSampler_get_type), _SE(js_gfx_GFXUniformSampler_set_type));
    cls->defineProperty("count", _SE(js_gfx_GFXUniformSampler_get_count), _SE(js_gfx_GFXUniformSampler_set_count));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXUniformSampler_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXUniformSampler>(cls);

    __jsb_cocos2d_GFXUniformSampler_proto = cls->getProto();
    __jsb_cocos2d_GFXUniformSampler_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXShaderStage_proto = nullptr;
se::Class* __jsb_cocos2d_GFXShaderStage_class = nullptr;

static bool js_gfx_GFXShaderStage_get_type(se::State& s)
{
    cocos2d::GFXShaderStage* cobj = (cocos2d::GFXShaderStage*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderStage_get_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->type, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXShaderStage_get_type)

static bool js_gfx_GFXShaderStage_set_type(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXShaderStage* cobj = (cocos2d::GFXShaderStage*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderStage_set_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->type); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXShaderStage_set_type : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXShaderStage_set_type)

static bool js_gfx_GFXShaderStage_get_source(se::State& s)
{
    cocos2d::GFXShaderStage* cobj = (cocos2d::GFXShaderStage*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderStage_get_source : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->source, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXShaderStage_get_source)

static bool js_gfx_GFXShaderStage_set_source(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXShaderStage* cobj = (cocos2d::GFXShaderStage*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderStage_set_source : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->source); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXShaderStage_set_source : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXShaderStage_set_source)

static bool js_gfx_GFXShaderStage_get_macros(se::State& s)
{
    cocos2d::GFXShaderStage* cobj = (cocos2d::GFXShaderStage*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderStage_get_macros : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->macros, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXShaderStage_get_macros)

static bool js_gfx_GFXShaderStage_set_macros(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXShaderStage* cobj = (cocos2d::GFXShaderStage*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderStage_set_macros : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->macros); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXShaderStage_set_macros : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXShaderStage_set_macros)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXShaderStage * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXShaderStage*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("type", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->type));
    }
    json->getProperty("source", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->source));
    }
    json->getProperty("macros", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->macros));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXShaderStage_finalize)

static bool js_gfx_GFXShaderStage_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXShaderStage* cobj = JSB_ALLOC(cocos2d::GFXShaderStage);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXShaderStage* cobj = JSB_ALLOC(cocos2d::GFXShaderStage);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 3)
    {
        cocos2d::GFXShaderStage* cobj = JSB_ALLOC(cocos2d::GFXShaderStage);
        cocos2d::GFXShaderType arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->type = arg0;
        }
        cocos2d::String arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->source = arg1;
        }
        std::vector<cocos2d::GFXShaderMacro> arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->macros = arg2;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXShaderStage_constructor, __jsb_cocos2d_GFXShaderStage_class, js_cocos2d_GFXShaderStage_finalize)




static bool js_cocos2d_GFXShaderStage_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXShaderStage)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXShaderStage* cobj = (cocos2d::GFXShaderStage*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXShaderStage_finalize)

bool js_register_gfx_GFXShaderStage(se::Object* obj)
{
    auto cls = se::Class::create("GFXShaderStage", obj, nullptr, _SE(js_gfx_GFXShaderStage_constructor));

    cls->defineProperty("type", _SE(js_gfx_GFXShaderStage_get_type), _SE(js_gfx_GFXShaderStage_set_type));
    cls->defineProperty("source", _SE(js_gfx_GFXShaderStage_get_source), _SE(js_gfx_GFXShaderStage_set_source));
    cls->defineProperty("macros", _SE(js_gfx_GFXShaderStage_get_macros), _SE(js_gfx_GFXShaderStage_set_macros));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXShaderStage_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXShaderStage>(cls);

    __jsb_cocos2d_GFXShaderStage_proto = cls->getProto();
    __jsb_cocos2d_GFXShaderStage_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXShaderInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXShaderInfo_class = nullptr;

static bool js_gfx_GFXShaderInfo_get_name(se::State& s)
{
    cocos2d::GFXShaderInfo* cobj = (cocos2d::GFXShaderInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderInfo_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXShaderInfo_get_name)

static bool js_gfx_GFXShaderInfo_set_name(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXShaderInfo* cobj = (cocos2d::GFXShaderInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderInfo_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXShaderInfo_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXShaderInfo_set_name)

static bool js_gfx_GFXShaderInfo_get_stages(se::State& s)
{
    cocos2d::GFXShaderInfo* cobj = (cocos2d::GFXShaderInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderInfo_get_stages : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stages, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXShaderInfo_get_stages)

static bool js_gfx_GFXShaderInfo_set_stages(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXShaderInfo* cobj = (cocos2d::GFXShaderInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderInfo_set_stages : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stages); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXShaderInfo_set_stages : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXShaderInfo_set_stages)

static bool js_gfx_GFXShaderInfo_get_blocks(se::State& s)
{
    cocos2d::GFXShaderInfo* cobj = (cocos2d::GFXShaderInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderInfo_get_blocks : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->blocks, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXShaderInfo_get_blocks)

static bool js_gfx_GFXShaderInfo_set_blocks(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXShaderInfo* cobj = (cocos2d::GFXShaderInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderInfo_set_blocks : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->blocks); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXShaderInfo_set_blocks : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXShaderInfo_set_blocks)

static bool js_gfx_GFXShaderInfo_get_samplers(se::State& s)
{
    cocos2d::GFXShaderInfo* cobj = (cocos2d::GFXShaderInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderInfo_get_samplers : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->samplers, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXShaderInfo_get_samplers)

static bool js_gfx_GFXShaderInfo_set_samplers(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXShaderInfo* cobj = (cocos2d::GFXShaderInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShaderInfo_set_samplers : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->samplers); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXShaderInfo_set_samplers : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXShaderInfo_set_samplers)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXShaderInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXShaderInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("name", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name));
    }
    json->getProperty("stages", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stages));
    }
    json->getProperty("blocks", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->blocks));
    }
    json->getProperty("samplers", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->samplers));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXShaderInfo_finalize)

static bool js_gfx_GFXShaderInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXShaderInfo* cobj = JSB_ALLOC(cocos2d::GFXShaderInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXShaderInfo* cobj = JSB_ALLOC(cocos2d::GFXShaderInfo);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 4)
    {
        cocos2d::GFXShaderInfo* cobj = JSB_ALLOC(cocos2d::GFXShaderInfo);
        cocos2d::String arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->name = arg0;
        }
        std::vector<cocos2d::GFXShaderStage> arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->stages = arg1;
        }
        std::vector<cocos2d::GFXUniformBlock> arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->blocks = arg2;
        }
        std::vector<cocos2d::GFXUniformSampler> arg3;
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->samplers = arg3;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXShaderInfo_constructor, __jsb_cocos2d_GFXShaderInfo_class, js_cocos2d_GFXShaderInfo_finalize)




static bool js_cocos2d_GFXShaderInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXShaderInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXShaderInfo* cobj = (cocos2d::GFXShaderInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXShaderInfo_finalize)

bool js_register_gfx_GFXShaderInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXShaderInfo", obj, nullptr, _SE(js_gfx_GFXShaderInfo_constructor));

    cls->defineProperty("name", _SE(js_gfx_GFXShaderInfo_get_name), _SE(js_gfx_GFXShaderInfo_set_name));
    cls->defineProperty("stages", _SE(js_gfx_GFXShaderInfo_get_stages), _SE(js_gfx_GFXShaderInfo_set_stages));
    cls->defineProperty("blocks", _SE(js_gfx_GFXShaderInfo_get_blocks), _SE(js_gfx_GFXShaderInfo_set_blocks));
    cls->defineProperty("samplers", _SE(js_gfx_GFXShaderInfo_get_samplers), _SE(js_gfx_GFXShaderInfo_set_samplers));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXShaderInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXShaderInfo>(cls);

    __jsb_cocos2d_GFXShaderInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXShaderInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXAttribute_proto = nullptr;
se::Class* __jsb_cocos2d_GFXAttribute_class = nullptr;

static bool js_gfx_GFXAttribute_get_name(se::State& s)
{
    cocos2d::GFXAttribute* cobj = (cocos2d::GFXAttribute*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXAttribute_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXAttribute_get_name)

static bool js_gfx_GFXAttribute_set_name(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXAttribute* cobj = (cocos2d::GFXAttribute*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXAttribute_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXAttribute_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXAttribute_set_name)

static bool js_gfx_GFXAttribute_get_format(se::State& s)
{
    cocos2d::GFXAttribute* cobj = (cocos2d::GFXAttribute*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXAttribute_get_format : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->format, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXAttribute_get_format)

static bool js_gfx_GFXAttribute_set_format(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXAttribute* cobj = (cocos2d::GFXAttribute*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXAttribute_set_format : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->format); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXAttribute_set_format : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXAttribute_set_format)

static bool js_gfx_GFXAttribute_get_isNormalized(se::State& s)
{
    cocos2d::GFXAttribute* cobj = (cocos2d::GFXAttribute*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXAttribute_get_isNormalized : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->isNormalized, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXAttribute_get_isNormalized)

static bool js_gfx_GFXAttribute_set_isNormalized(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXAttribute* cobj = (cocos2d::GFXAttribute*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXAttribute_set_isNormalized : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->isNormalized); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXAttribute_set_isNormalized : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXAttribute_set_isNormalized)

static bool js_gfx_GFXAttribute_get_stream(se::State& s)
{
    cocos2d::GFXAttribute* cobj = (cocos2d::GFXAttribute*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXAttribute_get_stream : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stream, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXAttribute_get_stream)

static bool js_gfx_GFXAttribute_set_stream(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXAttribute* cobj = (cocos2d::GFXAttribute*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXAttribute_set_stream : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stream); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXAttribute_set_stream : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXAttribute_set_stream)

static bool js_gfx_GFXAttribute_get_isInstanced(se::State& s)
{
    cocos2d::GFXAttribute* cobj = (cocos2d::GFXAttribute*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXAttribute_get_isInstanced : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->isInstanced, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXAttribute_get_isInstanced)

static bool js_gfx_GFXAttribute_set_isInstanced(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXAttribute* cobj = (cocos2d::GFXAttribute*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXAttribute_set_isInstanced : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->isInstanced); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXAttribute_set_isInstanced : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXAttribute_set_isInstanced)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXAttribute * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXAttribute*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("name", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name));
    }
    json->getProperty("format", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->format));
    }
    json->getProperty("isNormalized", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->isNormalized));
    }
    json->getProperty("stream", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stream));
    }
    json->getProperty("isInstanced", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->isInstanced));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXAttribute_finalize)

static bool js_gfx_GFXAttribute_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXAttribute* cobj = JSB_ALLOC(cocos2d::GFXAttribute);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXAttribute* cobj = JSB_ALLOC(cocos2d::GFXAttribute);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 5)
    {
        cocos2d::GFXAttribute* cobj = JSB_ALLOC(cocos2d::GFXAttribute);
        cocos2d::String arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->name = arg0;
        }
        cocos2d::GFXFormat arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->format = arg1;
        }
        bool arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->isNormalized = arg2;
        }
        unsigned int arg3 = {};
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->stream = arg3;
        }
        bool arg4;
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->isInstanced = arg4;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXAttribute_constructor, __jsb_cocos2d_GFXAttribute_class, js_cocos2d_GFXAttribute_finalize)




static bool js_cocos2d_GFXAttribute_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXAttribute)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXAttribute* cobj = (cocos2d::GFXAttribute*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXAttribute_finalize)

bool js_register_gfx_GFXAttribute(se::Object* obj)
{
    auto cls = se::Class::create("GFXAttribute", obj, nullptr, _SE(js_gfx_GFXAttribute_constructor));

    cls->defineProperty("name", _SE(js_gfx_GFXAttribute_get_name), _SE(js_gfx_GFXAttribute_set_name));
    cls->defineProperty("format", _SE(js_gfx_GFXAttribute_get_format), _SE(js_gfx_GFXAttribute_set_format));
    cls->defineProperty("isNormalized", _SE(js_gfx_GFXAttribute_get_isNormalized), _SE(js_gfx_GFXAttribute_set_isNormalized));
    cls->defineProperty("stream", _SE(js_gfx_GFXAttribute_get_stream), _SE(js_gfx_GFXAttribute_set_stream));
    cls->defineProperty("isInstanced", _SE(js_gfx_GFXAttribute_get_isInstanced), _SE(js_gfx_GFXAttribute_set_isInstanced));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXAttribute_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXAttribute>(cls);

    __jsb_cocos2d_GFXAttribute_proto = cls->getProto();
    __jsb_cocos2d_GFXAttribute_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXInputAssemblerInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXInputAssemblerInfo_class = nullptr;

static bool js_gfx_GFXInputAssemblerInfo_get_attributes(se::State& s)
{
    cocos2d::GFXInputAssemblerInfo* cobj = (cocos2d::GFXInputAssemblerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssemblerInfo_get_attributes : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->attributes, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXInputAssemblerInfo_get_attributes)

static bool js_gfx_GFXInputAssemblerInfo_set_attributes(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXInputAssemblerInfo* cobj = (cocos2d::GFXInputAssemblerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssemblerInfo_set_attributes : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->attributes); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssemblerInfo_set_attributes : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXInputAssemblerInfo_set_attributes)

static bool js_gfx_GFXInputAssemblerInfo_get_vertexBuffers(se::State& s)
{
    cocos2d::GFXInputAssemblerInfo* cobj = (cocos2d::GFXInputAssemblerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssemblerInfo_get_vertexBuffers : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->vertexBuffers, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXInputAssemblerInfo_get_vertexBuffers)

static bool js_gfx_GFXInputAssemblerInfo_set_vertexBuffers(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXInputAssemblerInfo* cobj = (cocos2d::GFXInputAssemblerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssemblerInfo_set_vertexBuffers : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->vertexBuffers); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssemblerInfo_set_vertexBuffers : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXInputAssemblerInfo_set_vertexBuffers)

static bool js_gfx_GFXInputAssemblerInfo_get_indexBuffer(se::State& s)
{
    cocos2d::GFXInputAssemblerInfo* cobj = (cocos2d::GFXInputAssemblerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssemblerInfo_get_indexBuffer : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->indexBuffer, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXInputAssemblerInfo_get_indexBuffer)

static bool js_gfx_GFXInputAssemblerInfo_set_indexBuffer(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXInputAssemblerInfo* cobj = (cocos2d::GFXInputAssemblerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssemblerInfo_set_indexBuffer : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->indexBuffer); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssemblerInfo_set_indexBuffer : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXInputAssemblerInfo_set_indexBuffer)

static bool js_gfx_GFXInputAssemblerInfo_get_indirectBuffer(se::State& s)
{
    cocos2d::GFXInputAssemblerInfo* cobj = (cocos2d::GFXInputAssemblerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssemblerInfo_get_indirectBuffer : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->indirectBuffer, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXInputAssemblerInfo_get_indirectBuffer)

static bool js_gfx_GFXInputAssemblerInfo_set_indirectBuffer(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXInputAssemblerInfo* cobj = (cocos2d::GFXInputAssemblerInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssemblerInfo_set_indirectBuffer : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->indirectBuffer); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssemblerInfo_set_indirectBuffer : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXInputAssemblerInfo_set_indirectBuffer)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXInputAssemblerInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXInputAssemblerInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("attributes", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->attributes));
    }
    json->getProperty("vertexBuffers", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->vertexBuffers));
    }
    json->getProperty("indexBuffer", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->indexBuffer));
    }
    json->getProperty("indirectBuffer", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->indirectBuffer));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXInputAssemblerInfo_finalize)

static bool js_gfx_GFXInputAssemblerInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXInputAssemblerInfo* cobj = JSB_ALLOC(cocos2d::GFXInputAssemblerInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXInputAssemblerInfo* cobj = JSB_ALLOC(cocos2d::GFXInputAssemblerInfo);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 4)
    {
        cocos2d::GFXInputAssemblerInfo* cobj = JSB_ALLOC(cocos2d::GFXInputAssemblerInfo);
        std::vector<cocos2d::GFXAttribute> arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->attributes = arg0;
        }
        std::vector<cocos2d::GFXBuffer *> arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->vertexBuffers = arg1;
        }
        cocos2d::GFXBuffer* arg2 = nullptr;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->indexBuffer = arg2;
        }
        cocos2d::GFXBuffer* arg3 = nullptr;
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->indirectBuffer = arg3;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXInputAssemblerInfo_constructor, __jsb_cocos2d_GFXInputAssemblerInfo_class, js_cocos2d_GFXInputAssemblerInfo_finalize)




static bool js_cocos2d_GFXInputAssemblerInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXInputAssemblerInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXInputAssemblerInfo* cobj = (cocos2d::GFXInputAssemblerInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXInputAssemblerInfo_finalize)

bool js_register_gfx_GFXInputAssemblerInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXInputAssemblerInfo", obj, nullptr, _SE(js_gfx_GFXInputAssemblerInfo_constructor));

    cls->defineProperty("attributes", _SE(js_gfx_GFXInputAssemblerInfo_get_attributes), _SE(js_gfx_GFXInputAssemblerInfo_set_attributes));
    cls->defineProperty("vertexBuffers", _SE(js_gfx_GFXInputAssemblerInfo_get_vertexBuffers), _SE(js_gfx_GFXInputAssemblerInfo_set_vertexBuffers));
    cls->defineProperty("indexBuffer", _SE(js_gfx_GFXInputAssemblerInfo_get_indexBuffer), _SE(js_gfx_GFXInputAssemblerInfo_set_indexBuffer));
    cls->defineProperty("indirectBuffer", _SE(js_gfx_GFXInputAssemblerInfo_get_indirectBuffer), _SE(js_gfx_GFXInputAssemblerInfo_set_indirectBuffer));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXInputAssemblerInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXInputAssemblerInfo>(cls);

    __jsb_cocos2d_GFXInputAssemblerInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXInputAssemblerInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXColorAttachment_proto = nullptr;
se::Class* __jsb_cocos2d_GFXColorAttachment_class = nullptr;

static bool js_gfx_GFXColorAttachment_get_format(se::State& s)
{
    cocos2d::GFXColorAttachment* cobj = (cocos2d::GFXColorAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColorAttachment_get_format : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->format, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXColorAttachment_get_format)

static bool js_gfx_GFXColorAttachment_set_format(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXColorAttachment* cobj = (cocos2d::GFXColorAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColorAttachment_set_format : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->format); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXColorAttachment_set_format : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXColorAttachment_set_format)

static bool js_gfx_GFXColorAttachment_get_loadOp(se::State& s)
{
    cocos2d::GFXColorAttachment* cobj = (cocos2d::GFXColorAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColorAttachment_get_loadOp : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->loadOp, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXColorAttachment_get_loadOp)

static bool js_gfx_GFXColorAttachment_set_loadOp(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXColorAttachment* cobj = (cocos2d::GFXColorAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColorAttachment_set_loadOp : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->loadOp); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXColorAttachment_set_loadOp : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXColorAttachment_set_loadOp)

static bool js_gfx_GFXColorAttachment_get_storeOp(se::State& s)
{
    cocos2d::GFXColorAttachment* cobj = (cocos2d::GFXColorAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColorAttachment_get_storeOp : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->storeOp, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXColorAttachment_get_storeOp)

static bool js_gfx_GFXColorAttachment_set_storeOp(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXColorAttachment* cobj = (cocos2d::GFXColorAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColorAttachment_set_storeOp : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->storeOp); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXColorAttachment_set_storeOp : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXColorAttachment_set_storeOp)

static bool js_gfx_GFXColorAttachment_get_sampleCount(se::State& s)
{
    cocos2d::GFXColorAttachment* cobj = (cocos2d::GFXColorAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColorAttachment_get_sampleCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->sampleCount, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXColorAttachment_get_sampleCount)

static bool js_gfx_GFXColorAttachment_set_sampleCount(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXColorAttachment* cobj = (cocos2d::GFXColorAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColorAttachment_set_sampleCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->sampleCount); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXColorAttachment_set_sampleCount : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXColorAttachment_set_sampleCount)

static bool js_gfx_GFXColorAttachment_get_beginLayout(se::State& s)
{
    cocos2d::GFXColorAttachment* cobj = (cocos2d::GFXColorAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColorAttachment_get_beginLayout : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->beginLayout, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXColorAttachment_get_beginLayout)

static bool js_gfx_GFXColorAttachment_set_beginLayout(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXColorAttachment* cobj = (cocos2d::GFXColorAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColorAttachment_set_beginLayout : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->beginLayout); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXColorAttachment_set_beginLayout : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXColorAttachment_set_beginLayout)

static bool js_gfx_GFXColorAttachment_get_endLayout(se::State& s)
{
    cocos2d::GFXColorAttachment* cobj = (cocos2d::GFXColorAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColorAttachment_get_endLayout : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->endLayout, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXColorAttachment_get_endLayout)

static bool js_gfx_GFXColorAttachment_set_endLayout(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXColorAttachment* cobj = (cocos2d::GFXColorAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXColorAttachment_set_endLayout : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->endLayout); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXColorAttachment_set_endLayout : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXColorAttachment_set_endLayout)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXColorAttachment * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXColorAttachment*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("format", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->format));
    }
    json->getProperty("loadOp", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->loadOp));
    }
    json->getProperty("storeOp", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->storeOp));
    }
    json->getProperty("sampleCount", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->sampleCount));
    }
    json->getProperty("beginLayout", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->beginLayout));
    }
    json->getProperty("endLayout", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->endLayout));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXColorAttachment_finalize)

static bool js_gfx_GFXColorAttachment_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXColorAttachment* cobj = JSB_ALLOC(cocos2d::GFXColorAttachment);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXColorAttachment* cobj = JSB_ALLOC(cocos2d::GFXColorAttachment);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 6)
    {
        cocos2d::GFXColorAttachment* cobj = JSB_ALLOC(cocos2d::GFXColorAttachment);
        cocos2d::GFXFormat arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->format = arg0;
        }
        cocos2d::GFXLoadOp arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->loadOp = arg1;
        }
        cocos2d::GFXStoreOp arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->storeOp = arg2;
        }
        unsigned int arg3 = {};
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->sampleCount = arg3;
        }
        cocos2d::GFXTextureLayout arg4;
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->beginLayout = arg4;
        }
        cocos2d::GFXTextureLayout arg5;
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->endLayout = arg5;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXColorAttachment_constructor, __jsb_cocos2d_GFXColorAttachment_class, js_cocos2d_GFXColorAttachment_finalize)




static bool js_cocos2d_GFXColorAttachment_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXColorAttachment)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXColorAttachment* cobj = (cocos2d::GFXColorAttachment*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXColorAttachment_finalize)

bool js_register_gfx_GFXColorAttachment(se::Object* obj)
{
    auto cls = se::Class::create("GFXColorAttachment", obj, nullptr, _SE(js_gfx_GFXColorAttachment_constructor));

    cls->defineProperty("format", _SE(js_gfx_GFXColorAttachment_get_format), _SE(js_gfx_GFXColorAttachment_set_format));
    cls->defineProperty("loadOp", _SE(js_gfx_GFXColorAttachment_get_loadOp), _SE(js_gfx_GFXColorAttachment_set_loadOp));
    cls->defineProperty("storeOp", _SE(js_gfx_GFXColorAttachment_get_storeOp), _SE(js_gfx_GFXColorAttachment_set_storeOp));
    cls->defineProperty("sampleCount", _SE(js_gfx_GFXColorAttachment_get_sampleCount), _SE(js_gfx_GFXColorAttachment_set_sampleCount));
    cls->defineProperty("beginLayout", _SE(js_gfx_GFXColorAttachment_get_beginLayout), _SE(js_gfx_GFXColorAttachment_set_beginLayout));
    cls->defineProperty("endLayout", _SE(js_gfx_GFXColorAttachment_get_endLayout), _SE(js_gfx_GFXColorAttachment_set_endLayout));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXColorAttachment_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXColorAttachment>(cls);

    __jsb_cocos2d_GFXColorAttachment_proto = cls->getProto();
    __jsb_cocos2d_GFXColorAttachment_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXDepthStencilAttachment_proto = nullptr;
se::Class* __jsb_cocos2d_GFXDepthStencilAttachment_class = nullptr;

static bool js_gfx_GFXDepthStencilAttachment_get_format(se::State& s)
{
    cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilAttachment_get_format : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->format, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilAttachment_get_format)

static bool js_gfx_GFXDepthStencilAttachment_set_format(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilAttachment_set_format : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->format); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilAttachment_set_format : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilAttachment_set_format)

static bool js_gfx_GFXDepthStencilAttachment_get_depthLoadOp(se::State& s)
{
    cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilAttachment_get_depthLoadOp : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->depthLoadOp, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilAttachment_get_depthLoadOp)

static bool js_gfx_GFXDepthStencilAttachment_set_depthLoadOp(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilAttachment_set_depthLoadOp : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->depthLoadOp); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilAttachment_set_depthLoadOp : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilAttachment_set_depthLoadOp)

static bool js_gfx_GFXDepthStencilAttachment_get_depthStoreOp(se::State& s)
{
    cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilAttachment_get_depthStoreOp : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->depthStoreOp, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilAttachment_get_depthStoreOp)

static bool js_gfx_GFXDepthStencilAttachment_set_depthStoreOp(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilAttachment_set_depthStoreOp : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->depthStoreOp); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilAttachment_set_depthStoreOp : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilAttachment_set_depthStoreOp)

static bool js_gfx_GFXDepthStencilAttachment_get_stencilLoadOp(se::State& s)
{
    cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilAttachment_get_stencilLoadOp : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilLoadOp, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilAttachment_get_stencilLoadOp)

static bool js_gfx_GFXDepthStencilAttachment_set_stencilLoadOp(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilAttachment_set_stencilLoadOp : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilLoadOp); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilAttachment_set_stencilLoadOp : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilAttachment_set_stencilLoadOp)

static bool js_gfx_GFXDepthStencilAttachment_get_stencilStoreOp(se::State& s)
{
    cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilAttachment_get_stencilStoreOp : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilStoreOp, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilAttachment_get_stencilStoreOp)

static bool js_gfx_GFXDepthStencilAttachment_set_stencilStoreOp(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilAttachment_set_stencilStoreOp : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilStoreOp); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilAttachment_set_stencilStoreOp : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilAttachment_set_stencilStoreOp)

static bool js_gfx_GFXDepthStencilAttachment_get_sampleCount(se::State& s)
{
    cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilAttachment_get_sampleCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->sampleCount, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilAttachment_get_sampleCount)

static bool js_gfx_GFXDepthStencilAttachment_set_sampleCount(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilAttachment_set_sampleCount : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->sampleCount); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilAttachment_set_sampleCount : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilAttachment_set_sampleCount)

static bool js_gfx_GFXDepthStencilAttachment_get_beginLayout(se::State& s)
{
    cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilAttachment_get_beginLayout : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->beginLayout, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilAttachment_get_beginLayout)

static bool js_gfx_GFXDepthStencilAttachment_set_beginLayout(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilAttachment_set_beginLayout : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->beginLayout); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilAttachment_set_beginLayout : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilAttachment_set_beginLayout)

static bool js_gfx_GFXDepthStencilAttachment_get_endLayout(se::State& s)
{
    cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilAttachment_get_endLayout : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->endLayout, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilAttachment_get_endLayout)

static bool js_gfx_GFXDepthStencilAttachment_set_endLayout(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilAttachment_set_endLayout : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->endLayout); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilAttachment_set_endLayout : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilAttachment_set_endLayout)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXDepthStencilAttachment * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXDepthStencilAttachment*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("format", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->format));
    }
    json->getProperty("depthLoadOp", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->depthLoadOp));
    }
    json->getProperty("depthStoreOp", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->depthStoreOp));
    }
    json->getProperty("stencilLoadOp", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilLoadOp));
    }
    json->getProperty("stencilStoreOp", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilStoreOp));
    }
    json->getProperty("sampleCount", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->sampleCount));
    }
    json->getProperty("beginLayout", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->beginLayout));
    }
    json->getProperty("endLayout", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->endLayout));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXDepthStencilAttachment_finalize)

static bool js_gfx_GFXDepthStencilAttachment_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXDepthStencilAttachment* cobj = JSB_ALLOC(cocos2d::GFXDepthStencilAttachment);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXDepthStencilAttachment* cobj = JSB_ALLOC(cocos2d::GFXDepthStencilAttachment);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 8)
    {
        cocos2d::GFXDepthStencilAttachment* cobj = JSB_ALLOC(cocos2d::GFXDepthStencilAttachment);
        cocos2d::GFXFormat arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->format = arg0;
        }
        cocos2d::GFXLoadOp arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->depthLoadOp = arg1;
        }
        cocos2d::GFXStoreOp arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->depthStoreOp = arg2;
        }
        cocos2d::GFXLoadOp arg3;
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->stencilLoadOp = arg3;
        }
        cocos2d::GFXStoreOp arg4;
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->stencilStoreOp = arg4;
        }
        unsigned int arg5 = {};
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->sampleCount = arg5;
        }
        cocos2d::GFXTextureLayout arg6;
        if (!args[6].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[6], &arg6); //is_reference False;
            cobj->beginLayout = arg6;
        }
        cocos2d::GFXTextureLayout arg7;
        if (!args[7].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[7], &arg7); //is_reference False;
            cobj->endLayout = arg7;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXDepthStencilAttachment_constructor, __jsb_cocos2d_GFXDepthStencilAttachment_class, js_cocos2d_GFXDepthStencilAttachment_finalize)




static bool js_cocos2d_GFXDepthStencilAttachment_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXDepthStencilAttachment)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXDepthStencilAttachment* cobj = (cocos2d::GFXDepthStencilAttachment*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXDepthStencilAttachment_finalize)

bool js_register_gfx_GFXDepthStencilAttachment(se::Object* obj)
{
    auto cls = se::Class::create("GFXDepthStencilAttachment", obj, nullptr, _SE(js_gfx_GFXDepthStencilAttachment_constructor));

    cls->defineProperty("format", _SE(js_gfx_GFXDepthStencilAttachment_get_format), _SE(js_gfx_GFXDepthStencilAttachment_set_format));
    cls->defineProperty("depthLoadOp", _SE(js_gfx_GFXDepthStencilAttachment_get_depthLoadOp), _SE(js_gfx_GFXDepthStencilAttachment_set_depthLoadOp));
    cls->defineProperty("depthStoreOp", _SE(js_gfx_GFXDepthStencilAttachment_get_depthStoreOp), _SE(js_gfx_GFXDepthStencilAttachment_set_depthStoreOp));
    cls->defineProperty("stencilLoadOp", _SE(js_gfx_GFXDepthStencilAttachment_get_stencilLoadOp), _SE(js_gfx_GFXDepthStencilAttachment_set_stencilLoadOp));
    cls->defineProperty("stencilStoreOp", _SE(js_gfx_GFXDepthStencilAttachment_get_stencilStoreOp), _SE(js_gfx_GFXDepthStencilAttachment_set_stencilStoreOp));
    cls->defineProperty("sampleCount", _SE(js_gfx_GFXDepthStencilAttachment_get_sampleCount), _SE(js_gfx_GFXDepthStencilAttachment_set_sampleCount));
    cls->defineProperty("beginLayout", _SE(js_gfx_GFXDepthStencilAttachment_get_beginLayout), _SE(js_gfx_GFXDepthStencilAttachment_set_beginLayout));
    cls->defineProperty("endLayout", _SE(js_gfx_GFXDepthStencilAttachment_get_endLayout), _SE(js_gfx_GFXDepthStencilAttachment_set_endLayout));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXDepthStencilAttachment_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXDepthStencilAttachment>(cls);

    __jsb_cocos2d_GFXDepthStencilAttachment_proto = cls->getProto();
    __jsb_cocos2d_GFXDepthStencilAttachment_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXSubPass_proto = nullptr;
se::Class* __jsb_cocos2d_GFXSubPass_class = nullptr;

static bool js_gfx_GFXSubPass_get_bindPoint(se::State& s)
{
    cocos2d::GFXSubPass* cobj = (cocos2d::GFXSubPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSubPass_get_bindPoint : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->bindPoint, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSubPass_get_bindPoint)

static bool js_gfx_GFXSubPass_set_bindPoint(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSubPass* cobj = (cocos2d::GFXSubPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSubPass_set_bindPoint : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->bindPoint); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSubPass_set_bindPoint : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSubPass_set_bindPoint)

static bool js_gfx_GFXSubPass_get_inputs(se::State& s)
{
    cocos2d::GFXSubPass* cobj = (cocos2d::GFXSubPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSubPass_get_inputs : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->inputs, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSubPass_get_inputs)

static bool js_gfx_GFXSubPass_set_inputs(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSubPass* cobj = (cocos2d::GFXSubPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSubPass_set_inputs : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->inputs); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSubPass_set_inputs : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSubPass_set_inputs)

static bool js_gfx_GFXSubPass_get_colors(se::State& s)
{
    cocos2d::GFXSubPass* cobj = (cocos2d::GFXSubPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSubPass_get_colors : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->colors, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSubPass_get_colors)

static bool js_gfx_GFXSubPass_set_colors(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSubPass* cobj = (cocos2d::GFXSubPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSubPass_set_colors : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->colors); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSubPass_set_colors : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSubPass_set_colors)

static bool js_gfx_GFXSubPass_get_resolves(se::State& s)
{
    cocos2d::GFXSubPass* cobj = (cocos2d::GFXSubPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSubPass_get_resolves : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->resolves, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSubPass_get_resolves)

static bool js_gfx_GFXSubPass_set_resolves(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSubPass* cobj = (cocos2d::GFXSubPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSubPass_set_resolves : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->resolves); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSubPass_set_resolves : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSubPass_set_resolves)

static bool js_gfx_GFXSubPass_get_depthStencil(se::State& s)
{
    cocos2d::GFXSubPass* cobj = (cocos2d::GFXSubPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSubPass_get_depthStencil : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->depthStencil, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSubPass_get_depthStencil)

static bool js_gfx_GFXSubPass_set_depthStencil(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSubPass* cobj = (cocos2d::GFXSubPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSubPass_set_depthStencil : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->depthStencil); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSubPass_set_depthStencil : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSubPass_set_depthStencil)

static bool js_gfx_GFXSubPass_get_preserves(se::State& s)
{
    cocos2d::GFXSubPass* cobj = (cocos2d::GFXSubPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSubPass_get_preserves : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->preserves, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXSubPass_get_preserves)

static bool js_gfx_GFXSubPass_set_preserves(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXSubPass* cobj = (cocos2d::GFXSubPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSubPass_set_preserves : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->preserves); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXSubPass_set_preserves : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXSubPass_set_preserves)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXSubPass * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXSubPass*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("bindPoint", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->bindPoint));
    }
    json->getProperty("inputs", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->inputs));
    }
    json->getProperty("colors", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->colors));
    }
    json->getProperty("resolves", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->resolves));
    }
    json->getProperty("depthStencil", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->depthStencil));
    }
    json->getProperty("preserves", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->preserves));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXSubPass_finalize)

static bool js_gfx_GFXSubPass_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXSubPass* cobj = JSB_ALLOC(cocos2d::GFXSubPass);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXSubPass* cobj = JSB_ALLOC(cocos2d::GFXSubPass);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 6)
    {
        cocos2d::GFXSubPass* cobj = JSB_ALLOC(cocos2d::GFXSubPass);
        cocos2d::GFXPipelineBindPoint arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->bindPoint = arg0;
        }
        std::array<unsigned char, 4> arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->inputs = arg1;
        }
        std::array<unsigned char, 4> arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->colors = arg2;
        }
        std::array<unsigned char, 4> arg3;
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->resolves = arg3;
        }
        uint8_t arg4;
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->depthStencil = arg4;
        }
        std::array<unsigned char, 4> arg5;
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->preserves = arg5;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXSubPass_constructor, __jsb_cocos2d_GFXSubPass_class, js_cocos2d_GFXSubPass_finalize)




static bool js_cocos2d_GFXSubPass_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXSubPass)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXSubPass* cobj = (cocos2d::GFXSubPass*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXSubPass_finalize)

bool js_register_gfx_GFXSubPass(se::Object* obj)
{
    auto cls = se::Class::create("GFXSubPass", obj, nullptr, _SE(js_gfx_GFXSubPass_constructor));

    cls->defineProperty("bindPoint", _SE(js_gfx_GFXSubPass_get_bindPoint), _SE(js_gfx_GFXSubPass_set_bindPoint));
    cls->defineProperty("inputs", _SE(js_gfx_GFXSubPass_get_inputs), _SE(js_gfx_GFXSubPass_set_inputs));
    cls->defineProperty("colors", _SE(js_gfx_GFXSubPass_get_colors), _SE(js_gfx_GFXSubPass_set_colors));
    cls->defineProperty("resolves", _SE(js_gfx_GFXSubPass_get_resolves), _SE(js_gfx_GFXSubPass_set_resolves));
    cls->defineProperty("depthStencil", _SE(js_gfx_GFXSubPass_get_depthStencil), _SE(js_gfx_GFXSubPass_set_depthStencil));
    cls->defineProperty("preserves", _SE(js_gfx_GFXSubPass_get_preserves), _SE(js_gfx_GFXSubPass_set_preserves));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXSubPass_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXSubPass>(cls);

    __jsb_cocos2d_GFXSubPass_proto = cls->getProto();
    __jsb_cocos2d_GFXSubPass_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXRenderPassInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXRenderPassInfo_class = nullptr;

static bool js_gfx_GFXRenderPassInfo_get_colorAttachments(se::State& s)
{
    cocos2d::GFXRenderPassInfo* cobj = (cocos2d::GFXRenderPassInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRenderPassInfo_get_colorAttachments : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->colorAttachments, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRenderPassInfo_get_colorAttachments)

static bool js_gfx_GFXRenderPassInfo_set_colorAttachments(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRenderPassInfo* cobj = (cocos2d::GFXRenderPassInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRenderPassInfo_set_colorAttachments : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->colorAttachments); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRenderPassInfo_set_colorAttachments : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRenderPassInfo_set_colorAttachments)

static bool js_gfx_GFXRenderPassInfo_get_depthStencilAttachment(se::State& s)
{
    cocos2d::GFXRenderPassInfo* cobj = (cocos2d::GFXRenderPassInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRenderPassInfo_get_depthStencilAttachment : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->depthStencilAttachment, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRenderPassInfo_get_depthStencilAttachment)

static bool js_gfx_GFXRenderPassInfo_set_depthStencilAttachment(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRenderPassInfo* cobj = (cocos2d::GFXRenderPassInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRenderPassInfo_set_depthStencilAttachment : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->depthStencilAttachment); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRenderPassInfo_set_depthStencilAttachment : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRenderPassInfo_set_depthStencilAttachment)

static bool js_gfx_GFXRenderPassInfo_get_subPasses(se::State& s)
{
    cocos2d::GFXRenderPassInfo* cobj = (cocos2d::GFXRenderPassInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRenderPassInfo_get_subPasses : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->subPasses, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRenderPassInfo_get_subPasses)

static bool js_gfx_GFXRenderPassInfo_set_subPasses(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRenderPassInfo* cobj = (cocos2d::GFXRenderPassInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRenderPassInfo_set_subPasses : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->subPasses); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRenderPassInfo_set_subPasses : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRenderPassInfo_set_subPasses)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXRenderPassInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXRenderPassInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("colorAttachments", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->colorAttachments));
    }
    json->getProperty("depthStencilAttachment", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->depthStencilAttachment));
    }
    json->getProperty("subPasses", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->subPasses));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXRenderPassInfo_finalize)

static bool js_gfx_GFXRenderPassInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXRenderPassInfo* cobj = JSB_ALLOC(cocos2d::GFXRenderPassInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXRenderPassInfo* cobj = JSB_ALLOC(cocos2d::GFXRenderPassInfo);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 3)
    {
        cocos2d::GFXRenderPassInfo* cobj = JSB_ALLOC(cocos2d::GFXRenderPassInfo);
        std::vector<cocos2d::GFXColorAttachment> arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->colorAttachments = arg0;
        }
        cocos2d::GFXDepthStencilAttachment arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->depthStencilAttachment = arg1;
        }
        std::vector<cocos2d::GFXSubPass> arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->subPasses = arg2;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXRenderPassInfo_constructor, __jsb_cocos2d_GFXRenderPassInfo_class, js_cocos2d_GFXRenderPassInfo_finalize)




static bool js_cocos2d_GFXRenderPassInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXRenderPassInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXRenderPassInfo* cobj = (cocos2d::GFXRenderPassInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXRenderPassInfo_finalize)

bool js_register_gfx_GFXRenderPassInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXRenderPassInfo", obj, nullptr, _SE(js_gfx_GFXRenderPassInfo_constructor));

    cls->defineProperty("colorAttachments", _SE(js_gfx_GFXRenderPassInfo_get_colorAttachments), _SE(js_gfx_GFXRenderPassInfo_set_colorAttachments));
    cls->defineProperty("depthStencilAttachment", _SE(js_gfx_GFXRenderPassInfo_get_depthStencilAttachment), _SE(js_gfx_GFXRenderPassInfo_set_depthStencilAttachment));
    cls->defineProperty("subPasses", _SE(js_gfx_GFXRenderPassInfo_get_subPasses), _SE(js_gfx_GFXRenderPassInfo_set_subPasses));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXRenderPassInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXRenderPassInfo>(cls);

    __jsb_cocos2d_GFXRenderPassInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXRenderPassInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXFramebufferInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXFramebufferInfo_class = nullptr;

static bool js_gfx_GFXFramebufferInfo_get_renderPass(se::State& s)
{
    cocos2d::GFXFramebufferInfo* cobj = (cocos2d::GFXFramebufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFramebufferInfo_get_renderPass : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->renderPass, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXFramebufferInfo_get_renderPass)

static bool js_gfx_GFXFramebufferInfo_set_renderPass(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXFramebufferInfo* cobj = (cocos2d::GFXFramebufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFramebufferInfo_set_renderPass : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->renderPass); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXFramebufferInfo_set_renderPass : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXFramebufferInfo_set_renderPass)

static bool js_gfx_GFXFramebufferInfo_get_colorViews(se::State& s)
{
    cocos2d::GFXFramebufferInfo* cobj = (cocos2d::GFXFramebufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFramebufferInfo_get_colorViews : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->colorViews, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXFramebufferInfo_get_colorViews)

static bool js_gfx_GFXFramebufferInfo_set_colorViews(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXFramebufferInfo* cobj = (cocos2d::GFXFramebufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFramebufferInfo_set_colorViews : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->colorViews); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXFramebufferInfo_set_colorViews : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXFramebufferInfo_set_colorViews)

static bool js_gfx_GFXFramebufferInfo_get_depthStencilView(se::State& s)
{
    cocos2d::GFXFramebufferInfo* cobj = (cocos2d::GFXFramebufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFramebufferInfo_get_depthStencilView : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->depthStencilView, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXFramebufferInfo_get_depthStencilView)

static bool js_gfx_GFXFramebufferInfo_set_depthStencilView(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXFramebufferInfo* cobj = (cocos2d::GFXFramebufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFramebufferInfo_set_depthStencilView : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->depthStencilView); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXFramebufferInfo_set_depthStencilView : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXFramebufferInfo_set_depthStencilView)

static bool js_gfx_GFXFramebufferInfo_get_isOffscreen(se::State& s)
{
    cocos2d::GFXFramebufferInfo* cobj = (cocos2d::GFXFramebufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFramebufferInfo_get_isOffscreen : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->isOffscreen, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXFramebufferInfo_get_isOffscreen)

static bool js_gfx_GFXFramebufferInfo_set_isOffscreen(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXFramebufferInfo* cobj = (cocos2d::GFXFramebufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFramebufferInfo_set_isOffscreen : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->isOffscreen); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXFramebufferInfo_set_isOffscreen : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXFramebufferInfo_set_isOffscreen)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXFramebufferInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXFramebufferInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("renderPass", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->renderPass));
    }
    json->getProperty("colorViews", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->colorViews));
    }
    json->getProperty("depthStencilView", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->depthStencilView));
    }
    json->getProperty("isOffscreen", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->isOffscreen));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXFramebufferInfo_finalize)

static bool js_gfx_GFXFramebufferInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXFramebufferInfo* cobj = JSB_ALLOC(cocos2d::GFXFramebufferInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXFramebufferInfo* cobj = JSB_ALLOC(cocos2d::GFXFramebufferInfo);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 4)
    {
        cocos2d::GFXFramebufferInfo* cobj = JSB_ALLOC(cocos2d::GFXFramebufferInfo);
        cocos2d::GFXRenderPass* arg0 = nullptr;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->renderPass = arg0;
        }
        std::vector<cocos2d::GFXTextureView *> arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->colorViews = arg1;
        }
        cocos2d::GFXTextureView* arg2 = nullptr;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->depthStencilView = arg2;
        }
        bool arg3;
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->isOffscreen = arg3;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXFramebufferInfo_constructor, __jsb_cocos2d_GFXFramebufferInfo_class, js_cocos2d_GFXFramebufferInfo_finalize)




static bool js_cocos2d_GFXFramebufferInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXFramebufferInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXFramebufferInfo* cobj = (cocos2d::GFXFramebufferInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXFramebufferInfo_finalize)

bool js_register_gfx_GFXFramebufferInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXFramebufferInfo", obj, nullptr, _SE(js_gfx_GFXFramebufferInfo_constructor));

    cls->defineProperty("renderPass", _SE(js_gfx_GFXFramebufferInfo_get_renderPass), _SE(js_gfx_GFXFramebufferInfo_set_renderPass));
    cls->defineProperty("colorViews", _SE(js_gfx_GFXFramebufferInfo_get_colorViews), _SE(js_gfx_GFXFramebufferInfo_set_colorViews));
    cls->defineProperty("depthStencilView", _SE(js_gfx_GFXFramebufferInfo_get_depthStencilView), _SE(js_gfx_GFXFramebufferInfo_set_depthStencilView));
    cls->defineProperty("isOffscreen", _SE(js_gfx_GFXFramebufferInfo_get_isOffscreen), _SE(js_gfx_GFXFramebufferInfo_set_isOffscreen));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXFramebufferInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXFramebufferInfo>(cls);

    __jsb_cocos2d_GFXFramebufferInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXFramebufferInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXBinding_proto = nullptr;
se::Class* __jsb_cocos2d_GFXBinding_class = nullptr;

static bool js_gfx_GFXBinding_get_binding(se::State& s)
{
    cocos2d::GFXBinding* cobj = (cocos2d::GFXBinding*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBinding_get_binding : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->binding, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBinding_get_binding)

static bool js_gfx_GFXBinding_set_binding(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBinding* cobj = (cocos2d::GFXBinding*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBinding_set_binding : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->binding); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBinding_set_binding : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBinding_set_binding)

static bool js_gfx_GFXBinding_get_type(se::State& s)
{
    cocos2d::GFXBinding* cobj = (cocos2d::GFXBinding*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBinding_get_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->type, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBinding_get_type)

static bool js_gfx_GFXBinding_set_type(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBinding* cobj = (cocos2d::GFXBinding*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBinding_set_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->type); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBinding_set_type : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBinding_set_type)

static bool js_gfx_GFXBinding_get_name(se::State& s)
{
    cocos2d::GFXBinding* cobj = (cocos2d::GFXBinding*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBinding_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBinding_get_name)

static bool js_gfx_GFXBinding_set_name(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBinding* cobj = (cocos2d::GFXBinding*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBinding_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBinding_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBinding_set_name)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXBinding * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXBinding*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("binding", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->binding));
    }
    json->getProperty("type", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->type));
    }
    json->getProperty("name", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXBinding_finalize)

static bool js_gfx_GFXBinding_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXBinding* cobj = JSB_ALLOC(cocos2d::GFXBinding);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXBinding* cobj = JSB_ALLOC(cocos2d::GFXBinding);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 3)
    {
        cocos2d::GFXBinding* cobj = JSB_ALLOC(cocos2d::GFXBinding);
        unsigned int arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->binding = arg0;
        }
        cocos2d::GFXBindingType arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->type = arg1;
        }
        cocos2d::String arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->name = arg2;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXBinding_constructor, __jsb_cocos2d_GFXBinding_class, js_cocos2d_GFXBinding_finalize)




static bool js_cocos2d_GFXBinding_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXBinding)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXBinding* cobj = (cocos2d::GFXBinding*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXBinding_finalize)

bool js_register_gfx_GFXBinding(se::Object* obj)
{
    auto cls = se::Class::create("GFXBinding", obj, nullptr, _SE(js_gfx_GFXBinding_constructor));

    cls->defineProperty("binding", _SE(js_gfx_GFXBinding_get_binding), _SE(js_gfx_GFXBinding_set_binding));
    cls->defineProperty("type", _SE(js_gfx_GFXBinding_get_type), _SE(js_gfx_GFXBinding_set_type));
    cls->defineProperty("name", _SE(js_gfx_GFXBinding_get_name), _SE(js_gfx_GFXBinding_set_name));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXBinding_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXBinding>(cls);

    __jsb_cocos2d_GFXBinding_proto = cls->getProto();
    __jsb_cocos2d_GFXBinding_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXBindingLayoutInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXBindingLayoutInfo_class = nullptr;

static bool js_gfx_GFXBindingLayoutInfo_get_bindings(se::State& s)
{
    cocos2d::GFXBindingLayoutInfo* cobj = (cocos2d::GFXBindingLayoutInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingLayoutInfo_get_bindings : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->bindings, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBindingLayoutInfo_get_bindings)

static bool js_gfx_GFXBindingLayoutInfo_set_bindings(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBindingLayoutInfo* cobj = (cocos2d::GFXBindingLayoutInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingLayoutInfo_set_bindings : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->bindings); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBindingLayoutInfo_set_bindings : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBindingLayoutInfo_set_bindings)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXBindingLayoutInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXBindingLayoutInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("bindings", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->bindings));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXBindingLayoutInfo_finalize)

static bool js_gfx_GFXBindingLayoutInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXBindingLayoutInfo* cobj = JSB_ALLOC(cocos2d::GFXBindingLayoutInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1)
    {
        cocos2d::GFXBindingLayoutInfo* cobj = JSB_ALLOC(cocos2d::GFXBindingLayoutInfo);
        std::vector<cocos2d::GFXBinding> arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->bindings = arg0;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXBindingLayoutInfo_constructor, __jsb_cocos2d_GFXBindingLayoutInfo_class, js_cocos2d_GFXBindingLayoutInfo_finalize)




static bool js_cocos2d_GFXBindingLayoutInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXBindingLayoutInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXBindingLayoutInfo* cobj = (cocos2d::GFXBindingLayoutInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXBindingLayoutInfo_finalize)

bool js_register_gfx_GFXBindingLayoutInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXBindingLayoutInfo", obj, nullptr, _SE(js_gfx_GFXBindingLayoutInfo_constructor));

    cls->defineProperty("bindings", _SE(js_gfx_GFXBindingLayoutInfo_get_bindings), _SE(js_gfx_GFXBindingLayoutInfo_set_bindings));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXBindingLayoutInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXBindingLayoutInfo>(cls);

    __jsb_cocos2d_GFXBindingLayoutInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXBindingLayoutInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXBindingUnit_proto = nullptr;
se::Class* __jsb_cocos2d_GFXBindingUnit_class = nullptr;

static bool js_gfx_GFXBindingUnit_get_binding(se::State& s)
{
    cocos2d::GFXBindingUnit* cobj = (cocos2d::GFXBindingUnit*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingUnit_get_binding : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->binding, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBindingUnit_get_binding)

static bool js_gfx_GFXBindingUnit_set_binding(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBindingUnit* cobj = (cocos2d::GFXBindingUnit*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingUnit_set_binding : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->binding); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBindingUnit_set_binding : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBindingUnit_set_binding)

static bool js_gfx_GFXBindingUnit_get_type(se::State& s)
{
    cocos2d::GFXBindingUnit* cobj = (cocos2d::GFXBindingUnit*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingUnit_get_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->type, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBindingUnit_get_type)

static bool js_gfx_GFXBindingUnit_set_type(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBindingUnit* cobj = (cocos2d::GFXBindingUnit*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingUnit_set_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->type); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBindingUnit_set_type : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBindingUnit_set_type)

static bool js_gfx_GFXBindingUnit_get_name(se::State& s)
{
    cocos2d::GFXBindingUnit* cobj = (cocos2d::GFXBindingUnit*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingUnit_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBindingUnit_get_name)

static bool js_gfx_GFXBindingUnit_set_name(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBindingUnit* cobj = (cocos2d::GFXBindingUnit*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingUnit_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBindingUnit_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBindingUnit_set_name)

static bool js_gfx_GFXBindingUnit_get_buffer(se::State& s)
{
    cocos2d::GFXBindingUnit* cobj = (cocos2d::GFXBindingUnit*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingUnit_get_buffer : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->buffer, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBindingUnit_get_buffer)

static bool js_gfx_GFXBindingUnit_set_buffer(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBindingUnit* cobj = (cocos2d::GFXBindingUnit*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingUnit_set_buffer : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->buffer); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBindingUnit_set_buffer : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBindingUnit_set_buffer)

static bool js_gfx_GFXBindingUnit_get_texView(se::State& s)
{
    cocos2d::GFXBindingUnit* cobj = (cocos2d::GFXBindingUnit*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingUnit_get_texView : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->texView, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBindingUnit_get_texView)

static bool js_gfx_GFXBindingUnit_set_texView(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBindingUnit* cobj = (cocos2d::GFXBindingUnit*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingUnit_set_texView : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->texView); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBindingUnit_set_texView : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBindingUnit_set_texView)

static bool js_gfx_GFXBindingUnit_get_sampler(se::State& s)
{
    cocos2d::GFXBindingUnit* cobj = (cocos2d::GFXBindingUnit*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingUnit_get_sampler : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->sampler, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBindingUnit_get_sampler)

static bool js_gfx_GFXBindingUnit_set_sampler(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBindingUnit* cobj = (cocos2d::GFXBindingUnit*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingUnit_set_sampler : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->sampler); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBindingUnit_set_sampler : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBindingUnit_set_sampler)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXBindingUnit * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXBindingUnit*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("binding", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->binding));
    }
    json->getProperty("type", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->type));
    }
    json->getProperty("name", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name));
    }
    json->getProperty("buffer", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->buffer));
    }
    json->getProperty("texView", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->texView));
    }
    json->getProperty("sampler", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->sampler));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXBindingUnit_finalize)

static bool js_gfx_GFXBindingUnit_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXBindingUnit* cobj = JSB_ALLOC(cocos2d::GFXBindingUnit);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXBindingUnit* cobj = JSB_ALLOC(cocos2d::GFXBindingUnit);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 6)
    {
        cocos2d::GFXBindingUnit* cobj = JSB_ALLOC(cocos2d::GFXBindingUnit);
        unsigned int arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->binding = arg0;
        }
        cocos2d::GFXBindingType arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->type = arg1;
        }
        cocos2d::String arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->name = arg2;
        }
        cocos2d::GFXBuffer* arg3 = nullptr;
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->buffer = arg3;
        }
        cocos2d::GFXTextureView* arg4 = nullptr;
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->texView = arg4;
        }
        cocos2d::GFXSampler* arg5 = nullptr;
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->sampler = arg5;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXBindingUnit_constructor, __jsb_cocos2d_GFXBindingUnit_class, js_cocos2d_GFXBindingUnit_finalize)




static bool js_cocos2d_GFXBindingUnit_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXBindingUnit)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXBindingUnit* cobj = (cocos2d::GFXBindingUnit*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXBindingUnit_finalize)

bool js_register_gfx_GFXBindingUnit(se::Object* obj)
{
    auto cls = se::Class::create("GFXBindingUnit", obj, nullptr, _SE(js_gfx_GFXBindingUnit_constructor));

    cls->defineProperty("binding", _SE(js_gfx_GFXBindingUnit_get_binding), _SE(js_gfx_GFXBindingUnit_set_binding));
    cls->defineProperty("type", _SE(js_gfx_GFXBindingUnit_get_type), _SE(js_gfx_GFXBindingUnit_set_type));
    cls->defineProperty("name", _SE(js_gfx_GFXBindingUnit_get_name), _SE(js_gfx_GFXBindingUnit_set_name));
    cls->defineProperty("buffer", _SE(js_gfx_GFXBindingUnit_get_buffer), _SE(js_gfx_GFXBindingUnit_set_buffer));
    cls->defineProperty("texView", _SE(js_gfx_GFXBindingUnit_get_texView), _SE(js_gfx_GFXBindingUnit_set_texView));
    cls->defineProperty("sampler", _SE(js_gfx_GFXBindingUnit_get_sampler), _SE(js_gfx_GFXBindingUnit_set_sampler));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXBindingUnit_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXBindingUnit>(cls);

    __jsb_cocos2d_GFXBindingUnit_proto = cls->getProto();
    __jsb_cocos2d_GFXBindingUnit_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXPushConstantRange_proto = nullptr;
se::Class* __jsb_cocos2d_GFXPushConstantRange_class = nullptr;

static bool js_gfx_GFXPushConstantRange_get_shaderType(se::State& s)
{
    cocos2d::GFXPushConstantRange* cobj = (cocos2d::GFXPushConstantRange*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPushConstantRange_get_shaderType : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->shaderType, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXPushConstantRange_get_shaderType)

static bool js_gfx_GFXPushConstantRange_set_shaderType(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXPushConstantRange* cobj = (cocos2d::GFXPushConstantRange*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPushConstantRange_set_shaderType : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->shaderType); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXPushConstantRange_set_shaderType : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXPushConstantRange_set_shaderType)

static bool js_gfx_GFXPushConstantRange_get_offset(se::State& s)
{
    cocos2d::GFXPushConstantRange* cobj = (cocos2d::GFXPushConstantRange*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPushConstantRange_get_offset : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->offset, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXPushConstantRange_get_offset)

static bool js_gfx_GFXPushConstantRange_set_offset(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXPushConstantRange* cobj = (cocos2d::GFXPushConstantRange*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPushConstantRange_set_offset : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->offset); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXPushConstantRange_set_offset : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXPushConstantRange_set_offset)

static bool js_gfx_GFXPushConstantRange_get_count(se::State& s)
{
    cocos2d::GFXPushConstantRange* cobj = (cocos2d::GFXPushConstantRange*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPushConstantRange_get_count : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->count, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXPushConstantRange_get_count)

static bool js_gfx_GFXPushConstantRange_set_count(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXPushConstantRange* cobj = (cocos2d::GFXPushConstantRange*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPushConstantRange_set_count : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->count); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXPushConstantRange_set_count : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXPushConstantRange_set_count)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXPushConstantRange * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXPushConstantRange*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("shaderType", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->shaderType));
    }
    json->getProperty("offset", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->offset));
    }
    json->getProperty("count", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->count));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXPushConstantRange_finalize)

static bool js_gfx_GFXPushConstantRange_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXPushConstantRange* cobj = JSB_ALLOC(cocos2d::GFXPushConstantRange);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXPushConstantRange* cobj = JSB_ALLOC(cocos2d::GFXPushConstantRange);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 3)
    {
        cocos2d::GFXPushConstantRange* cobj = JSB_ALLOC(cocos2d::GFXPushConstantRange);
        cocos2d::GFXShaderType arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->shaderType = arg0;
        }
        unsigned int arg1 = {};
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->offset = arg1;
        }
        unsigned int arg2 = {};
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->count = arg2;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXPushConstantRange_constructor, __jsb_cocos2d_GFXPushConstantRange_class, js_cocos2d_GFXPushConstantRange_finalize)




static bool js_cocos2d_GFXPushConstantRange_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXPushConstantRange)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXPushConstantRange* cobj = (cocos2d::GFXPushConstantRange*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXPushConstantRange_finalize)

bool js_register_gfx_GFXPushConstantRange(se::Object* obj)
{
    auto cls = se::Class::create("GFXPushConstantRange", obj, nullptr, _SE(js_gfx_GFXPushConstantRange_constructor));

    cls->defineProperty("shaderType", _SE(js_gfx_GFXPushConstantRange_get_shaderType), _SE(js_gfx_GFXPushConstantRange_set_shaderType));
    cls->defineProperty("offset", _SE(js_gfx_GFXPushConstantRange_get_offset), _SE(js_gfx_GFXPushConstantRange_set_offset));
    cls->defineProperty("count", _SE(js_gfx_GFXPushConstantRange_get_count), _SE(js_gfx_GFXPushConstantRange_set_count));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXPushConstantRange_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXPushConstantRange>(cls);

    __jsb_cocos2d_GFXPushConstantRange_proto = cls->getProto();
    __jsb_cocos2d_GFXPushConstantRange_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXPipelineLayoutInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXPipelineLayoutInfo_class = nullptr;

static bool js_gfx_GFXPipelineLayoutInfo_get_pushConstantsRanges(se::State& s)
{
    cocos2d::GFXPipelineLayoutInfo* cobj = (cocos2d::GFXPipelineLayoutInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineLayoutInfo_get_pushConstantsRanges : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->pushConstantsRanges, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineLayoutInfo_get_pushConstantsRanges)

static bool js_gfx_GFXPipelineLayoutInfo_set_pushConstantsRanges(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXPipelineLayoutInfo* cobj = (cocos2d::GFXPipelineLayoutInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineLayoutInfo_set_pushConstantsRanges : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->pushConstantsRanges); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineLayoutInfo_set_pushConstantsRanges : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXPipelineLayoutInfo_set_pushConstantsRanges)

static bool js_gfx_GFXPipelineLayoutInfo_get_layouts(se::State& s)
{
    cocos2d::GFXPipelineLayoutInfo* cobj = (cocos2d::GFXPipelineLayoutInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineLayoutInfo_get_layouts : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->layouts, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineLayoutInfo_get_layouts)

static bool js_gfx_GFXPipelineLayoutInfo_set_layouts(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXPipelineLayoutInfo* cobj = (cocos2d::GFXPipelineLayoutInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineLayoutInfo_set_layouts : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->layouts); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineLayoutInfo_set_layouts : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXPipelineLayoutInfo_set_layouts)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXPipelineLayoutInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXPipelineLayoutInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("pushConstantsRanges", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->pushConstantsRanges));
    }
    json->getProperty("layouts", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->layouts));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXPipelineLayoutInfo_finalize)

static bool js_gfx_GFXPipelineLayoutInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXPipelineLayoutInfo* cobj = JSB_ALLOC(cocos2d::GFXPipelineLayoutInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXPipelineLayoutInfo* cobj = JSB_ALLOC(cocos2d::GFXPipelineLayoutInfo);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 2)
    {
        cocos2d::GFXPipelineLayoutInfo* cobj = JSB_ALLOC(cocos2d::GFXPipelineLayoutInfo);
        std::vector<cocos2d::GFXPushConstantRange> arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->pushConstantsRanges = arg0;
        }
        std::vector<cocos2d::GFXBindingLayout *> arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->layouts = arg1;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXPipelineLayoutInfo_constructor, __jsb_cocos2d_GFXPipelineLayoutInfo_class, js_cocos2d_GFXPipelineLayoutInfo_finalize)




static bool js_cocos2d_GFXPipelineLayoutInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXPipelineLayoutInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXPipelineLayoutInfo* cobj = (cocos2d::GFXPipelineLayoutInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXPipelineLayoutInfo_finalize)

bool js_register_gfx_GFXPipelineLayoutInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXPipelineLayoutInfo", obj, nullptr, _SE(js_gfx_GFXPipelineLayoutInfo_constructor));

    cls->defineProperty("pushConstantsRanges", _SE(js_gfx_GFXPipelineLayoutInfo_get_pushConstantsRanges), _SE(js_gfx_GFXPipelineLayoutInfo_set_pushConstantsRanges));
    cls->defineProperty("layouts", _SE(js_gfx_GFXPipelineLayoutInfo_get_layouts), _SE(js_gfx_GFXPipelineLayoutInfo_set_layouts));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXPipelineLayoutInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXPipelineLayoutInfo>(cls);

    __jsb_cocos2d_GFXPipelineLayoutInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXPipelineLayoutInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXInputState_proto = nullptr;
se::Class* __jsb_cocos2d_GFXInputState_class = nullptr;

static bool js_gfx_GFXInputState_get_attributes(se::State& s)
{
    cocos2d::GFXInputState* cobj = (cocos2d::GFXInputState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputState_get_attributes : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->attributes, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXInputState_get_attributes)

static bool js_gfx_GFXInputState_set_attributes(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXInputState* cobj = (cocos2d::GFXInputState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputState_set_attributes : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->attributes); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXInputState_set_attributes : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXInputState_set_attributes)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXInputState * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXInputState*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("attributes", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->attributes));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXInputState_finalize)

static bool js_gfx_GFXInputState_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXInputState* cobj = JSB_ALLOC(cocos2d::GFXInputState);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1)
    {
        cocos2d::GFXInputState* cobj = JSB_ALLOC(cocos2d::GFXInputState);
        std::vector<cocos2d::GFXAttribute> arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->attributes = arg0;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXInputState_constructor, __jsb_cocos2d_GFXInputState_class, js_cocos2d_GFXInputState_finalize)




static bool js_cocos2d_GFXInputState_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXInputState)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXInputState* cobj = (cocos2d::GFXInputState*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXInputState_finalize)

bool js_register_gfx_GFXInputState(se::Object* obj)
{
    auto cls = se::Class::create("GFXInputState", obj, nullptr, _SE(js_gfx_GFXInputState_constructor));

    cls->defineProperty("attributes", _SE(js_gfx_GFXInputState_get_attributes), _SE(js_gfx_GFXInputState_set_attributes));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXInputState_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXInputState>(cls);

    __jsb_cocos2d_GFXInputState_proto = cls->getProto();
    __jsb_cocos2d_GFXInputState_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXRasterizerState_proto = nullptr;
se::Class* __jsb_cocos2d_GFXRasterizerState_class = nullptr;

static bool js_gfx_GFXRasterizerState_get_isDiscard(se::State& s)
{
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_get_isDiscard : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->isDiscard, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRasterizerState_get_isDiscard)

static bool js_gfx_GFXRasterizerState_set_isDiscard(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_set_isDiscard : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->isDiscard); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRasterizerState_set_isDiscard : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRasterizerState_set_isDiscard)

static bool js_gfx_GFXRasterizerState_get_polygonMode(se::State& s)
{
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_get_polygonMode : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->polygonMode, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRasterizerState_get_polygonMode)

static bool js_gfx_GFXRasterizerState_set_polygonMode(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_set_polygonMode : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->polygonMode); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRasterizerState_set_polygonMode : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRasterizerState_set_polygonMode)

static bool js_gfx_GFXRasterizerState_get_shadeModel(se::State& s)
{
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_get_shadeModel : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->shadeModel, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRasterizerState_get_shadeModel)

static bool js_gfx_GFXRasterizerState_set_shadeModel(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_set_shadeModel : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->shadeModel); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRasterizerState_set_shadeModel : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRasterizerState_set_shadeModel)

static bool js_gfx_GFXRasterizerState_get_cullMode(se::State& s)
{
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_get_cullMode : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->cullMode, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRasterizerState_get_cullMode)

static bool js_gfx_GFXRasterizerState_set_cullMode(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_set_cullMode : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->cullMode); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRasterizerState_set_cullMode : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRasterizerState_set_cullMode)

static bool js_gfx_GFXRasterizerState_get_isFrontFaceCCW(se::State& s)
{
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_get_isFrontFaceCCW : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->isFrontFaceCCW, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRasterizerState_get_isFrontFaceCCW)

static bool js_gfx_GFXRasterizerState_set_isFrontFaceCCW(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_set_isFrontFaceCCW : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->isFrontFaceCCW); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRasterizerState_set_isFrontFaceCCW : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRasterizerState_set_isFrontFaceCCW)

static bool js_gfx_GFXRasterizerState_get_depthBias(se::State& s)
{
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_get_depthBias : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->depthBias, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRasterizerState_get_depthBias)

static bool js_gfx_GFXRasterizerState_set_depthBias(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_set_depthBias : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->depthBias); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRasterizerState_set_depthBias : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRasterizerState_set_depthBias)

static bool js_gfx_GFXRasterizerState_get_depthBiasClamp(se::State& s)
{
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_get_depthBiasClamp : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->depthBiasClamp, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRasterizerState_get_depthBiasClamp)

static bool js_gfx_GFXRasterizerState_set_depthBiasClamp(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_set_depthBiasClamp : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->depthBiasClamp); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRasterizerState_set_depthBiasClamp : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRasterizerState_set_depthBiasClamp)

static bool js_gfx_GFXRasterizerState_get_depthBiasSlop(se::State& s)
{
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_get_depthBiasSlop : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->depthBiasSlop, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRasterizerState_get_depthBiasSlop)

static bool js_gfx_GFXRasterizerState_set_depthBiasSlop(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_set_depthBiasSlop : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->depthBiasSlop); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRasterizerState_set_depthBiasSlop : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRasterizerState_set_depthBiasSlop)

static bool js_gfx_GFXRasterizerState_get_isDepthClip(se::State& s)
{
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_get_isDepthClip : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->isDepthClip, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRasterizerState_get_isDepthClip)

static bool js_gfx_GFXRasterizerState_set_isDepthClip(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_set_isDepthClip : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->isDepthClip); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRasterizerState_set_isDepthClip : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRasterizerState_set_isDepthClip)

static bool js_gfx_GFXRasterizerState_get_isMultisample(se::State& s)
{
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_get_isMultisample : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->isMultisample, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRasterizerState_get_isMultisample)

static bool js_gfx_GFXRasterizerState_set_isMultisample(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_set_isMultisample : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->isMultisample); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRasterizerState_set_isMultisample : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRasterizerState_set_isMultisample)

static bool js_gfx_GFXRasterizerState_get_lineWidth(se::State& s)
{
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_get_lineWidth : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->lineWidth, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXRasterizerState_get_lineWidth)

static bool js_gfx_GFXRasterizerState_set_lineWidth(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRasterizerState_set_lineWidth : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->lineWidth); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXRasterizerState_set_lineWidth : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXRasterizerState_set_lineWidth)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXRasterizerState * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXRasterizerState*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("isDiscard", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->isDiscard));
    }
    json->getProperty("polygonMode", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->polygonMode));
    }
    json->getProperty("shadeModel", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->shadeModel));
    }
    json->getProperty("cullMode", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->cullMode));
    }
    json->getProperty("isFrontFaceCCW", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->isFrontFaceCCW));
    }
    json->getProperty("depthBias", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->depthBias));
    }
    json->getProperty("depthBiasClamp", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->depthBiasClamp));
    }
    json->getProperty("depthBiasSlop", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->depthBiasSlop));
    }
    json->getProperty("isDepthClip", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->isDepthClip));
    }
    json->getProperty("isMultisample", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->isMultisample));
    }
    json->getProperty("lineWidth", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->lineWidth));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXRasterizerState_finalize)

static bool js_gfx_GFXRasterizerState_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXRasterizerState* cobj = JSB_ALLOC(cocos2d::GFXRasterizerState);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXRasterizerState* cobj = JSB_ALLOC(cocos2d::GFXRasterizerState);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 11)
    {
        cocos2d::GFXRasterizerState* cobj = JSB_ALLOC(cocos2d::GFXRasterizerState);
        bool arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->isDiscard = arg0;
        }
        cocos2d::GFXPolygonMode arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->polygonMode = arg1;
        }
        cocos2d::GFXShadeModel arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->shadeModel = arg2;
        }
        cocos2d::GFXCullMode arg3;
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->cullMode = arg3;
        }
        bool arg4;
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->isFrontFaceCCW = arg4;
        }
        float arg5 = {};
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->depthBias = arg5;
        }
        float arg6 = {};
        if (!args[6].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[6], &arg6); //is_reference False;
            cobj->depthBiasClamp = arg6;
        }
        float arg7 = {};
        if (!args[7].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[7], &arg7); //is_reference False;
            cobj->depthBiasSlop = arg7;
        }
        bool arg8;
        if (!args[8].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[8], &arg8); //is_reference False;
            cobj->isDepthClip = arg8;
        }
        bool arg9;
        if (!args[9].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[9], &arg9); //is_reference False;
            cobj->isMultisample = arg9;
        }
        float arg10 = {};
        if (!args[10].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[10], &arg10); //is_reference False;
            cobj->lineWidth = arg10;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXRasterizerState_constructor, __jsb_cocos2d_GFXRasterizerState_class, js_cocos2d_GFXRasterizerState_finalize)




static bool js_cocos2d_GFXRasterizerState_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXRasterizerState)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXRasterizerState* cobj = (cocos2d::GFXRasterizerState*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXRasterizerState_finalize)

bool js_register_gfx_GFXRasterizerState(se::Object* obj)
{
    auto cls = se::Class::create("GFXRasterizerState", obj, nullptr, _SE(js_gfx_GFXRasterizerState_constructor));

    cls->defineProperty("isDiscard", _SE(js_gfx_GFXRasterizerState_get_isDiscard), _SE(js_gfx_GFXRasterizerState_set_isDiscard));
    cls->defineProperty("polygonMode", _SE(js_gfx_GFXRasterizerState_get_polygonMode), _SE(js_gfx_GFXRasterizerState_set_polygonMode));
    cls->defineProperty("shadeModel", _SE(js_gfx_GFXRasterizerState_get_shadeModel), _SE(js_gfx_GFXRasterizerState_set_shadeModel));
    cls->defineProperty("cullMode", _SE(js_gfx_GFXRasterizerState_get_cullMode), _SE(js_gfx_GFXRasterizerState_set_cullMode));
    cls->defineProperty("isFrontFaceCCW", _SE(js_gfx_GFXRasterizerState_get_isFrontFaceCCW), _SE(js_gfx_GFXRasterizerState_set_isFrontFaceCCW));
    cls->defineProperty("depthBias", _SE(js_gfx_GFXRasterizerState_get_depthBias), _SE(js_gfx_GFXRasterizerState_set_depthBias));
    cls->defineProperty("depthBiasClamp", _SE(js_gfx_GFXRasterizerState_get_depthBiasClamp), _SE(js_gfx_GFXRasterizerState_set_depthBiasClamp));
    cls->defineProperty("depthBiasSlop", _SE(js_gfx_GFXRasterizerState_get_depthBiasSlop), _SE(js_gfx_GFXRasterizerState_set_depthBiasSlop));
    cls->defineProperty("isDepthClip", _SE(js_gfx_GFXRasterizerState_get_isDepthClip), _SE(js_gfx_GFXRasterizerState_set_isDepthClip));
    cls->defineProperty("isMultisample", _SE(js_gfx_GFXRasterizerState_get_isMultisample), _SE(js_gfx_GFXRasterizerState_set_isMultisample));
    cls->defineProperty("lineWidth", _SE(js_gfx_GFXRasterizerState_get_lineWidth), _SE(js_gfx_GFXRasterizerState_set_lineWidth));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXRasterizerState_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXRasterizerState>(cls);

    __jsb_cocos2d_GFXRasterizerState_proto = cls->getProto();
    __jsb_cocos2d_GFXRasterizerState_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXDepthStencilState_proto = nullptr;
se::Class* __jsb_cocos2d_GFXDepthStencilState_class = nullptr;

static bool js_gfx_GFXDepthStencilState_get_depthTest(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_depthTest : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->depthTest, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_depthTest)

static bool js_gfx_GFXDepthStencilState_set_depthTest(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_depthTest : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->depthTest); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_depthTest : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_depthTest)

static bool js_gfx_GFXDepthStencilState_get_depthWrite(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_depthWrite : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->depthWrite, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_depthWrite)

static bool js_gfx_GFXDepthStencilState_set_depthWrite(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_depthWrite : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->depthWrite); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_depthWrite : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_depthWrite)

static bool js_gfx_GFXDepthStencilState_get_depthFunc(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_depthFunc : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->depthFunc, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_depthFunc)

static bool js_gfx_GFXDepthStencilState_set_depthFunc(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_depthFunc : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->depthFunc); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_depthFunc : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_depthFunc)

static bool js_gfx_GFXDepthStencilState_get_stencilTestFront(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_stencilTestFront : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilTestFront, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_stencilTestFront)

static bool js_gfx_GFXDepthStencilState_set_stencilTestFront(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_stencilTestFront : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilTestFront); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_stencilTestFront : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_stencilTestFront)

static bool js_gfx_GFXDepthStencilState_get_stencilFuncFront(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_stencilFuncFront : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilFuncFront, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_stencilFuncFront)

static bool js_gfx_GFXDepthStencilState_set_stencilFuncFront(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_stencilFuncFront : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilFuncFront); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_stencilFuncFront : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_stencilFuncFront)

static bool js_gfx_GFXDepthStencilState_get_stencilReadMaskFront(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_stencilReadMaskFront : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilReadMaskFront, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_stencilReadMaskFront)

static bool js_gfx_GFXDepthStencilState_set_stencilReadMaskFront(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_stencilReadMaskFront : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilReadMaskFront); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_stencilReadMaskFront : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_stencilReadMaskFront)

static bool js_gfx_GFXDepthStencilState_get_stencilWriteMaskFront(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_stencilWriteMaskFront : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilWriteMaskFront, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_stencilWriteMaskFront)

static bool js_gfx_GFXDepthStencilState_set_stencilWriteMaskFront(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_stencilWriteMaskFront : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilWriteMaskFront); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_stencilWriteMaskFront : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_stencilWriteMaskFront)

static bool js_gfx_GFXDepthStencilState_get_stencilFailOpFront(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_stencilFailOpFront : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilFailOpFront, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_stencilFailOpFront)

static bool js_gfx_GFXDepthStencilState_set_stencilFailOpFront(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_stencilFailOpFront : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilFailOpFront); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_stencilFailOpFront : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_stencilFailOpFront)

static bool js_gfx_GFXDepthStencilState_get_stencilZFailOpFront(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_stencilZFailOpFront : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilZFailOpFront, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_stencilZFailOpFront)

static bool js_gfx_GFXDepthStencilState_set_stencilZFailOpFront(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_stencilZFailOpFront : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilZFailOpFront); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_stencilZFailOpFront : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_stencilZFailOpFront)

static bool js_gfx_GFXDepthStencilState_get_stencilPassOpFront(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_stencilPassOpFront : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilPassOpFront, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_stencilPassOpFront)

static bool js_gfx_GFXDepthStencilState_set_stencilPassOpFront(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_stencilPassOpFront : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilPassOpFront); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_stencilPassOpFront : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_stencilPassOpFront)

static bool js_gfx_GFXDepthStencilState_get_stencilRefFront(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_stencilRefFront : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilRefFront, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_stencilRefFront)

static bool js_gfx_GFXDepthStencilState_set_stencilRefFront(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_stencilRefFront : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilRefFront); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_stencilRefFront : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_stencilRefFront)

static bool js_gfx_GFXDepthStencilState_get_stencilTestBack(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_stencilTestBack : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilTestBack, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_stencilTestBack)

static bool js_gfx_GFXDepthStencilState_set_stencilTestBack(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_stencilTestBack : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilTestBack); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_stencilTestBack : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_stencilTestBack)

static bool js_gfx_GFXDepthStencilState_get_stencilFuncBack(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_stencilFuncBack : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilFuncBack, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_stencilFuncBack)

static bool js_gfx_GFXDepthStencilState_set_stencilFuncBack(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_stencilFuncBack : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilFuncBack); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_stencilFuncBack : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_stencilFuncBack)

static bool js_gfx_GFXDepthStencilState_get_stencilReadMaskBack(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_stencilReadMaskBack : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilReadMaskBack, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_stencilReadMaskBack)

static bool js_gfx_GFXDepthStencilState_set_stencilReadMaskBack(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_stencilReadMaskBack : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilReadMaskBack); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_stencilReadMaskBack : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_stencilReadMaskBack)

static bool js_gfx_GFXDepthStencilState_get_stencilWriteMaskBack(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_stencilWriteMaskBack : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilWriteMaskBack, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_stencilWriteMaskBack)

static bool js_gfx_GFXDepthStencilState_set_stencilWriteMaskBack(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_stencilWriteMaskBack : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilWriteMaskBack); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_stencilWriteMaskBack : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_stencilWriteMaskBack)

static bool js_gfx_GFXDepthStencilState_get_stencilFailOpBack(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_stencilFailOpBack : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilFailOpBack, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_stencilFailOpBack)

static bool js_gfx_GFXDepthStencilState_set_stencilFailOpBack(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_stencilFailOpBack : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilFailOpBack); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_stencilFailOpBack : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_stencilFailOpBack)

static bool js_gfx_GFXDepthStencilState_get_stencilZFailOpBack(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_stencilZFailOpBack : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilZFailOpBack, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_stencilZFailOpBack)

static bool js_gfx_GFXDepthStencilState_set_stencilZFailOpBack(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_stencilZFailOpBack : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilZFailOpBack); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_stencilZFailOpBack : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_stencilZFailOpBack)

static bool js_gfx_GFXDepthStencilState_get_stencilPassOpBack(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_stencilPassOpBack : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilPassOpBack, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_stencilPassOpBack)

static bool js_gfx_GFXDepthStencilState_set_stencilPassOpBack(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_stencilPassOpBack : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilPassOpBack); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_stencilPassOpBack : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_stencilPassOpBack)

static bool js_gfx_GFXDepthStencilState_get_stencilRefBack(se::State& s)
{
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_get_stencilRefBack : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->stencilRefBack, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXDepthStencilState_get_stencilRefBack)

static bool js_gfx_GFXDepthStencilState_set_stencilRefBack(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDepthStencilState_set_stencilRefBack : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->stencilRefBack); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXDepthStencilState_set_stencilRefBack : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXDepthStencilState_set_stencilRefBack)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXDepthStencilState * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXDepthStencilState*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("depthTest", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->depthTest));
    }
    json->getProperty("depthWrite", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->depthWrite));
    }
    json->getProperty("depthFunc", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->depthFunc));
    }
    json->getProperty("stencilTestFront", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilTestFront));
    }
    json->getProperty("stencilFuncFront", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilFuncFront));
    }
    json->getProperty("stencilReadMaskFront", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilReadMaskFront));
    }
    json->getProperty("stencilWriteMaskFront", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilWriteMaskFront));
    }
    json->getProperty("stencilFailOpFront", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilFailOpFront));
    }
    json->getProperty("stencilZFailOpFront", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilZFailOpFront));
    }
    json->getProperty("stencilPassOpFront", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilPassOpFront));
    }
    json->getProperty("stencilRefFront", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilRefFront));
    }
    json->getProperty("stencilTestBack", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilTestBack));
    }
    json->getProperty("stencilFuncBack", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilFuncBack));
    }
    json->getProperty("stencilReadMaskBack", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilReadMaskBack));
    }
    json->getProperty("stencilWriteMaskBack", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilWriteMaskBack));
    }
    json->getProperty("stencilFailOpBack", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilFailOpBack));
    }
    json->getProperty("stencilZFailOpBack", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilZFailOpBack));
    }
    json->getProperty("stencilPassOpBack", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilPassOpBack));
    }
    json->getProperty("stencilRefBack", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->stencilRefBack));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXDepthStencilState_finalize)

static bool js_gfx_GFXDepthStencilState_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXDepthStencilState* cobj = JSB_ALLOC(cocos2d::GFXDepthStencilState);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXDepthStencilState* cobj = JSB_ALLOC(cocos2d::GFXDepthStencilState);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 19)
    {
        cocos2d::GFXDepthStencilState* cobj = JSB_ALLOC(cocos2d::GFXDepthStencilState);
        bool arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->depthTest = arg0;
        }
        bool arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->depthWrite = arg1;
        }
        cocos2d::GFXComparisonFunc arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->depthFunc = arg2;
        }
        bool arg3;
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->stencilTestFront = arg3;
        }
        cocos2d::GFXComparisonFunc arg4;
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->stencilFuncFront = arg4;
        }
        unsigned int arg5 = {};
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->stencilReadMaskFront = arg5;
        }
        unsigned int arg6 = {};
        if (!args[6].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[6], &arg6); //is_reference False;
            cobj->stencilWriteMaskFront = arg6;
        }
        cocos2d::GFXStencilOp arg7;
        if (!args[7].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[7], &arg7); //is_reference False;
            cobj->stencilFailOpFront = arg7;
        }
        cocos2d::GFXStencilOp arg8;
        if (!args[8].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[8], &arg8); //is_reference False;
            cobj->stencilZFailOpFront = arg8;
        }
        cocos2d::GFXStencilOp arg9;
        if (!args[9].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[9], &arg9); //is_reference False;
            cobj->stencilPassOpFront = arg9;
        }
        unsigned int arg10 = {};
        if (!args[10].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[10], &arg10); //is_reference False;
            cobj->stencilRefFront = arg10;
        }
        bool arg11;
        if (!args[11].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[11], &arg11); //is_reference False;
            cobj->stencilTestBack = arg11;
        }
        cocos2d::GFXComparisonFunc arg12;
        if (!args[12].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[12], &arg12); //is_reference False;
            cobj->stencilFuncBack = arg12;
        }
        unsigned int arg13 = {};
        if (!args[13].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[13], &arg13); //is_reference False;
            cobj->stencilReadMaskBack = arg13;
        }
        unsigned int arg14 = {};
        if (!args[14].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[14], &arg14); //is_reference False;
            cobj->stencilWriteMaskBack = arg14;
        }
        cocos2d::GFXStencilOp arg15;
        if (!args[15].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[15], &arg15); //is_reference False;
            cobj->stencilFailOpBack = arg15;
        }
        cocos2d::GFXStencilOp arg16;
        if (!args[16].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[16], &arg16); //is_reference False;
            cobj->stencilZFailOpBack = arg16;
        }
        cocos2d::GFXStencilOp arg17;
        if (!args[17].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[17], &arg17); //is_reference False;
            cobj->stencilPassOpBack = arg17;
        }
        unsigned int arg18 = {};
        if (!args[18].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[18], &arg18); //is_reference False;
            cobj->stencilRefBack = arg18;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXDepthStencilState_constructor, __jsb_cocos2d_GFXDepthStencilState_class, js_cocos2d_GFXDepthStencilState_finalize)




static bool js_cocos2d_GFXDepthStencilState_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXDepthStencilState)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXDepthStencilState* cobj = (cocos2d::GFXDepthStencilState*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXDepthStencilState_finalize)

bool js_register_gfx_GFXDepthStencilState(se::Object* obj)
{
    auto cls = se::Class::create("GFXDepthStencilState", obj, nullptr, _SE(js_gfx_GFXDepthStencilState_constructor));

    cls->defineProperty("depthTest", _SE(js_gfx_GFXDepthStencilState_get_depthTest), _SE(js_gfx_GFXDepthStencilState_set_depthTest));
    cls->defineProperty("depthWrite", _SE(js_gfx_GFXDepthStencilState_get_depthWrite), _SE(js_gfx_GFXDepthStencilState_set_depthWrite));
    cls->defineProperty("depthFunc", _SE(js_gfx_GFXDepthStencilState_get_depthFunc), _SE(js_gfx_GFXDepthStencilState_set_depthFunc));
    cls->defineProperty("stencilTestFront", _SE(js_gfx_GFXDepthStencilState_get_stencilTestFront), _SE(js_gfx_GFXDepthStencilState_set_stencilTestFront));
    cls->defineProperty("stencilFuncFront", _SE(js_gfx_GFXDepthStencilState_get_stencilFuncFront), _SE(js_gfx_GFXDepthStencilState_set_stencilFuncFront));
    cls->defineProperty("stencilReadMaskFront", _SE(js_gfx_GFXDepthStencilState_get_stencilReadMaskFront), _SE(js_gfx_GFXDepthStencilState_set_stencilReadMaskFront));
    cls->defineProperty("stencilWriteMaskFront", _SE(js_gfx_GFXDepthStencilState_get_stencilWriteMaskFront), _SE(js_gfx_GFXDepthStencilState_set_stencilWriteMaskFront));
    cls->defineProperty("stencilFailOpFront", _SE(js_gfx_GFXDepthStencilState_get_stencilFailOpFront), _SE(js_gfx_GFXDepthStencilState_set_stencilFailOpFront));
    cls->defineProperty("stencilZFailOpFront", _SE(js_gfx_GFXDepthStencilState_get_stencilZFailOpFront), _SE(js_gfx_GFXDepthStencilState_set_stencilZFailOpFront));
    cls->defineProperty("stencilPassOpFront", _SE(js_gfx_GFXDepthStencilState_get_stencilPassOpFront), _SE(js_gfx_GFXDepthStencilState_set_stencilPassOpFront));
    cls->defineProperty("stencilRefFront", _SE(js_gfx_GFXDepthStencilState_get_stencilRefFront), _SE(js_gfx_GFXDepthStencilState_set_stencilRefFront));
    cls->defineProperty("stencilTestBack", _SE(js_gfx_GFXDepthStencilState_get_stencilTestBack), _SE(js_gfx_GFXDepthStencilState_set_stencilTestBack));
    cls->defineProperty("stencilFuncBack", _SE(js_gfx_GFXDepthStencilState_get_stencilFuncBack), _SE(js_gfx_GFXDepthStencilState_set_stencilFuncBack));
    cls->defineProperty("stencilReadMaskBack", _SE(js_gfx_GFXDepthStencilState_get_stencilReadMaskBack), _SE(js_gfx_GFXDepthStencilState_set_stencilReadMaskBack));
    cls->defineProperty("stencilWriteMaskBack", _SE(js_gfx_GFXDepthStencilState_get_stencilWriteMaskBack), _SE(js_gfx_GFXDepthStencilState_set_stencilWriteMaskBack));
    cls->defineProperty("stencilFailOpBack", _SE(js_gfx_GFXDepthStencilState_get_stencilFailOpBack), _SE(js_gfx_GFXDepthStencilState_set_stencilFailOpBack));
    cls->defineProperty("stencilZFailOpBack", _SE(js_gfx_GFXDepthStencilState_get_stencilZFailOpBack), _SE(js_gfx_GFXDepthStencilState_set_stencilZFailOpBack));
    cls->defineProperty("stencilPassOpBack", _SE(js_gfx_GFXDepthStencilState_get_stencilPassOpBack), _SE(js_gfx_GFXDepthStencilState_set_stencilPassOpBack));
    cls->defineProperty("stencilRefBack", _SE(js_gfx_GFXDepthStencilState_get_stencilRefBack), _SE(js_gfx_GFXDepthStencilState_set_stencilRefBack));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXDepthStencilState_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXDepthStencilState>(cls);

    __jsb_cocos2d_GFXDepthStencilState_proto = cls->getProto();
    __jsb_cocos2d_GFXDepthStencilState_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXBlendTarget_proto = nullptr;
se::Class* __jsb_cocos2d_GFXBlendTarget_class = nullptr;

static bool js_gfx_GFXBlendTarget_get_blend(se::State& s)
{
    cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendTarget_get_blend : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->blend, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBlendTarget_get_blend)

static bool js_gfx_GFXBlendTarget_set_blend(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendTarget_set_blend : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->blend); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBlendTarget_set_blend : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBlendTarget_set_blend)

static bool js_gfx_GFXBlendTarget_get_blendSrc(se::State& s)
{
    cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendTarget_get_blendSrc : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->blendSrc, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBlendTarget_get_blendSrc)

static bool js_gfx_GFXBlendTarget_set_blendSrc(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendTarget_set_blendSrc : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->blendSrc); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBlendTarget_set_blendSrc : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBlendTarget_set_blendSrc)

static bool js_gfx_GFXBlendTarget_get_blendDst(se::State& s)
{
    cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendTarget_get_blendDst : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->blendDst, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBlendTarget_get_blendDst)

static bool js_gfx_GFXBlendTarget_set_blendDst(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendTarget_set_blendDst : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->blendDst); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBlendTarget_set_blendDst : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBlendTarget_set_blendDst)

static bool js_gfx_GFXBlendTarget_get_blendEq(se::State& s)
{
    cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendTarget_get_blendEq : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->blendEq, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBlendTarget_get_blendEq)

static bool js_gfx_GFXBlendTarget_set_blendEq(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendTarget_set_blendEq : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->blendEq); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBlendTarget_set_blendEq : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBlendTarget_set_blendEq)

static bool js_gfx_GFXBlendTarget_get_blendSrcAlpha(se::State& s)
{
    cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendTarget_get_blendSrcAlpha : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->blendSrcAlpha, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBlendTarget_get_blendSrcAlpha)

static bool js_gfx_GFXBlendTarget_set_blendSrcAlpha(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendTarget_set_blendSrcAlpha : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->blendSrcAlpha); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBlendTarget_set_blendSrcAlpha : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBlendTarget_set_blendSrcAlpha)

static bool js_gfx_GFXBlendTarget_get_blendDstAlpha(se::State& s)
{
    cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendTarget_get_blendDstAlpha : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->blendDstAlpha, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBlendTarget_get_blendDstAlpha)

static bool js_gfx_GFXBlendTarget_set_blendDstAlpha(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendTarget_set_blendDstAlpha : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->blendDstAlpha); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBlendTarget_set_blendDstAlpha : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBlendTarget_set_blendDstAlpha)

static bool js_gfx_GFXBlendTarget_get_blendAlphaEq(se::State& s)
{
    cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendTarget_get_blendAlphaEq : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->blendAlphaEq, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBlendTarget_get_blendAlphaEq)

static bool js_gfx_GFXBlendTarget_set_blendAlphaEq(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendTarget_set_blendAlphaEq : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->blendAlphaEq); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBlendTarget_set_blendAlphaEq : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBlendTarget_set_blendAlphaEq)

static bool js_gfx_GFXBlendTarget_get_blendColorMask(se::State& s)
{
    cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendTarget_get_blendColorMask : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->blendColorMask, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBlendTarget_get_blendColorMask)

static bool js_gfx_GFXBlendTarget_set_blendColorMask(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendTarget_set_blendColorMask : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->blendColorMask); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBlendTarget_set_blendColorMask : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBlendTarget_set_blendColorMask)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXBlendTarget * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXBlendTarget*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("blend", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->blend));
    }
    json->getProperty("blendSrc", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->blendSrc));
    }
    json->getProperty("blendDst", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->blendDst));
    }
    json->getProperty("blendEq", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->blendEq));
    }
    json->getProperty("blendSrcAlpha", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->blendSrcAlpha));
    }
    json->getProperty("blendDstAlpha", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->blendDstAlpha));
    }
    json->getProperty("blendAlphaEq", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->blendAlphaEq));
    }
    json->getProperty("blendColorMask", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->blendColorMask));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXBlendTarget_finalize)

static bool js_gfx_GFXBlendTarget_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXBlendTarget* cobj = JSB_ALLOC(cocos2d::GFXBlendTarget);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXBlendTarget* cobj = JSB_ALLOC(cocos2d::GFXBlendTarget);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 8)
    {
        cocos2d::GFXBlendTarget* cobj = JSB_ALLOC(cocos2d::GFXBlendTarget);
        bool arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->blend = arg0;
        }
        cocos2d::GFXBlendFactor arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->blendSrc = arg1;
        }
        cocos2d::GFXBlendFactor arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->blendDst = arg2;
        }
        cocos2d::GFXBlendOp arg3;
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->blendEq = arg3;
        }
        cocos2d::GFXBlendFactor arg4;
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->blendSrcAlpha = arg4;
        }
        cocos2d::GFXBlendFactor arg5;
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->blendDstAlpha = arg5;
        }
        cocos2d::GFXBlendOp arg6;
        if (!args[6].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[6], &arg6); //is_reference False;
            cobj->blendAlphaEq = arg6;
        }
        cocos2d::GFXColorMask arg7;
        if (!args[7].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[7], &arg7); //is_reference False;
            cobj->blendColorMask = arg7;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXBlendTarget_constructor, __jsb_cocos2d_GFXBlendTarget_class, js_cocos2d_GFXBlendTarget_finalize)




static bool js_cocos2d_GFXBlendTarget_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXBlendTarget)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXBlendTarget* cobj = (cocos2d::GFXBlendTarget*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXBlendTarget_finalize)

bool js_register_gfx_GFXBlendTarget(se::Object* obj)
{
    auto cls = se::Class::create("GFXBlendTarget", obj, nullptr, _SE(js_gfx_GFXBlendTarget_constructor));

    cls->defineProperty("blend", _SE(js_gfx_GFXBlendTarget_get_blend), _SE(js_gfx_GFXBlendTarget_set_blend));
    cls->defineProperty("blendSrc", _SE(js_gfx_GFXBlendTarget_get_blendSrc), _SE(js_gfx_GFXBlendTarget_set_blendSrc));
    cls->defineProperty("blendDst", _SE(js_gfx_GFXBlendTarget_get_blendDst), _SE(js_gfx_GFXBlendTarget_set_blendDst));
    cls->defineProperty("blendEq", _SE(js_gfx_GFXBlendTarget_get_blendEq), _SE(js_gfx_GFXBlendTarget_set_blendEq));
    cls->defineProperty("blendSrcAlpha", _SE(js_gfx_GFXBlendTarget_get_blendSrcAlpha), _SE(js_gfx_GFXBlendTarget_set_blendSrcAlpha));
    cls->defineProperty("blendDstAlpha", _SE(js_gfx_GFXBlendTarget_get_blendDstAlpha), _SE(js_gfx_GFXBlendTarget_set_blendDstAlpha));
    cls->defineProperty("blendAlphaEq", _SE(js_gfx_GFXBlendTarget_get_blendAlphaEq), _SE(js_gfx_GFXBlendTarget_set_blendAlphaEq));
    cls->defineProperty("blendColorMask", _SE(js_gfx_GFXBlendTarget_get_blendColorMask), _SE(js_gfx_GFXBlendTarget_set_blendColorMask));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXBlendTarget_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXBlendTarget>(cls);

    __jsb_cocos2d_GFXBlendTarget_proto = cls->getProto();
    __jsb_cocos2d_GFXBlendTarget_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXBlendState_proto = nullptr;
se::Class* __jsb_cocos2d_GFXBlendState_class = nullptr;

static bool js_gfx_GFXBlendState_get_isA2C(se::State& s)
{
    cocos2d::GFXBlendState* cobj = (cocos2d::GFXBlendState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendState_get_isA2C : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->isA2C, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBlendState_get_isA2C)

static bool js_gfx_GFXBlendState_set_isA2C(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBlendState* cobj = (cocos2d::GFXBlendState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendState_set_isA2C : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->isA2C); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBlendState_set_isA2C : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBlendState_set_isA2C)

static bool js_gfx_GFXBlendState_get_isIndepend(se::State& s)
{
    cocos2d::GFXBlendState* cobj = (cocos2d::GFXBlendState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendState_get_isIndepend : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->isIndepend, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBlendState_get_isIndepend)

static bool js_gfx_GFXBlendState_set_isIndepend(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBlendState* cobj = (cocos2d::GFXBlendState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendState_set_isIndepend : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->isIndepend); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBlendState_set_isIndepend : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBlendState_set_isIndepend)

static bool js_gfx_GFXBlendState_get_blendColor(se::State& s)
{
    cocos2d::GFXBlendState* cobj = (cocos2d::GFXBlendState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendState_get_blendColor : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->blendColor, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBlendState_get_blendColor)

static bool js_gfx_GFXBlendState_set_blendColor(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBlendState* cobj = (cocos2d::GFXBlendState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendState_set_blendColor : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->blendColor); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBlendState_set_blendColor : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBlendState_set_blendColor)

static bool js_gfx_GFXBlendState_get_targets(se::State& s)
{
    cocos2d::GFXBlendState* cobj = (cocos2d::GFXBlendState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendState_get_targets : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->targets, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXBlendState_get_targets)

static bool js_gfx_GFXBlendState_set_targets(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXBlendState* cobj = (cocos2d::GFXBlendState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBlendState_set_targets : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->targets); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXBlendState_set_targets : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXBlendState_set_targets)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXBlendState * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXBlendState*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("isA2C", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->isA2C));
    }
    json->getProperty("isIndepend", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->isIndepend));
    }
    json->getProperty("blendColor", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->blendColor));
    }
    json->getProperty("targets", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->targets));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXBlendState_finalize)

static bool js_gfx_GFXBlendState_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXBlendState* cobj = JSB_ALLOC(cocos2d::GFXBlendState);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXBlendState* cobj = JSB_ALLOC(cocos2d::GFXBlendState);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 4)
    {
        cocos2d::GFXBlendState* cobj = JSB_ALLOC(cocos2d::GFXBlendState);
        bool arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->isA2C = arg0;
        }
        bool arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->isIndepend = arg1;
        }
        cocos2d::GFXColor arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->blendColor = arg2;
        }
        std::vector<cocos2d::GFXBlendTarget> arg3;
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->targets = arg3;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXBlendState_constructor, __jsb_cocos2d_GFXBlendState_class, js_cocos2d_GFXBlendState_finalize)




static bool js_cocos2d_GFXBlendState_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXBlendState)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXBlendState* cobj = (cocos2d::GFXBlendState*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXBlendState_finalize)

bool js_register_gfx_GFXBlendState(se::Object* obj)
{
    auto cls = se::Class::create("GFXBlendState", obj, nullptr, _SE(js_gfx_GFXBlendState_constructor));

    cls->defineProperty("isA2C", _SE(js_gfx_GFXBlendState_get_isA2C), _SE(js_gfx_GFXBlendState_set_isA2C));
    cls->defineProperty("isIndepend", _SE(js_gfx_GFXBlendState_get_isIndepend), _SE(js_gfx_GFXBlendState_set_isIndepend));
    cls->defineProperty("blendColor", _SE(js_gfx_GFXBlendState_get_blendColor), _SE(js_gfx_GFXBlendState_set_blendColor));
    cls->defineProperty("targets", _SE(js_gfx_GFXBlendState_get_targets), _SE(js_gfx_GFXBlendState_set_targets));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXBlendState_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXBlendState>(cls);

    __jsb_cocos2d_GFXBlendState_proto = cls->getProto();
    __jsb_cocos2d_GFXBlendState_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXPipelineStateInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXPipelineStateInfo_class = nullptr;

static bool js_gfx_GFXPipelineStateInfo_get_primitive(se::State& s)
{
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_get_primitive : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->primitive, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineStateInfo_get_primitive)

static bool js_gfx_GFXPipelineStateInfo_set_primitive(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_set_primitive : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->primitive); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineStateInfo_set_primitive : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXPipelineStateInfo_set_primitive)

static bool js_gfx_GFXPipelineStateInfo_get_shader(se::State& s)
{
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_get_shader : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->shader, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineStateInfo_get_shader)

static bool js_gfx_GFXPipelineStateInfo_set_shader(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_set_shader : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->shader); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineStateInfo_set_shader : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXPipelineStateInfo_set_shader)

static bool js_gfx_GFXPipelineStateInfo_get_inputState(se::State& s)
{
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_get_inputState : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->inputState, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineStateInfo_get_inputState)

static bool js_gfx_GFXPipelineStateInfo_set_inputState(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_set_inputState : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->inputState); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineStateInfo_set_inputState : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXPipelineStateInfo_set_inputState)

static bool js_gfx_GFXPipelineStateInfo_get_rasterizerState(se::State& s)
{
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_get_rasterizerState : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->rasterizerState, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineStateInfo_get_rasterizerState)

static bool js_gfx_GFXPipelineStateInfo_set_rasterizerState(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_set_rasterizerState : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->rasterizerState); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineStateInfo_set_rasterizerState : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXPipelineStateInfo_set_rasterizerState)

static bool js_gfx_GFXPipelineStateInfo_get_depthStencilState(se::State& s)
{
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_get_depthStencilState : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->depthStencilState, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineStateInfo_get_depthStencilState)

static bool js_gfx_GFXPipelineStateInfo_set_depthStencilState(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_set_depthStencilState : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->depthStencilState); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineStateInfo_set_depthStencilState : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXPipelineStateInfo_set_depthStencilState)

static bool js_gfx_GFXPipelineStateInfo_get_blendState(se::State& s)
{
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_get_blendState : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->blendState, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineStateInfo_get_blendState)

static bool js_gfx_GFXPipelineStateInfo_set_blendState(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_set_blendState : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->blendState); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineStateInfo_set_blendState : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXPipelineStateInfo_set_blendState)

static bool js_gfx_GFXPipelineStateInfo_get_dynamicStates(se::State& s)
{
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_get_dynamicStates : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->dynamicStates, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineStateInfo_get_dynamicStates)

static bool js_gfx_GFXPipelineStateInfo_set_dynamicStates(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_set_dynamicStates : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->dynamicStates); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineStateInfo_set_dynamicStates : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXPipelineStateInfo_set_dynamicStates)

static bool js_gfx_GFXPipelineStateInfo_get_layout(se::State& s)
{
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_get_layout : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->layout, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineStateInfo_get_layout)

static bool js_gfx_GFXPipelineStateInfo_set_layout(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_set_layout : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->layout); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineStateInfo_set_layout : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXPipelineStateInfo_set_layout)

static bool js_gfx_GFXPipelineStateInfo_get_renderPass(se::State& s)
{
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_get_renderPass : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->renderPass, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineStateInfo_get_renderPass)

static bool js_gfx_GFXPipelineStateInfo_set_renderPass(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineStateInfo_set_renderPass : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->renderPass); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineStateInfo_set_renderPass : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXPipelineStateInfo_set_renderPass)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXPipelineStateInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXPipelineStateInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("primitive", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->primitive));
    }
    json->getProperty("shader", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->shader));
    }
    json->getProperty("inputState", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->inputState));
    }
    json->getProperty("rasterizerState", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->rasterizerState));
    }
    json->getProperty("depthStencilState", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->depthStencilState));
    }
    json->getProperty("blendState", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->blendState));
    }
    json->getProperty("dynamicStates", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->dynamicStates));
    }
    json->getProperty("layout", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->layout));
    }
    json->getProperty("renderPass", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->renderPass));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXPipelineStateInfo_finalize)

static bool js_gfx_GFXPipelineStateInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXPipelineStateInfo* cobj = JSB_ALLOC(cocos2d::GFXPipelineStateInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXPipelineStateInfo* cobj = JSB_ALLOC(cocos2d::GFXPipelineStateInfo);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 9)
    {
        cocos2d::GFXPipelineStateInfo* cobj = JSB_ALLOC(cocos2d::GFXPipelineStateInfo);
        cocos2d::GFXPrimitiveMode arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->primitive = arg0;
        }
        cocos2d::GFXShader* arg1 = nullptr;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->shader = arg1;
        }
        cocos2d::GFXInputState arg2;
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->inputState = arg2;
        }
        cocos2d::GFXRasterizerState arg3;
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->rasterizerState = arg3;
        }
        cocos2d::GFXDepthStencilState arg4;
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->depthStencilState = arg4;
        }
        cocos2d::GFXBlendState arg5;
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->blendState = arg5;
        }
        std::vector<cocos2d::GFXDynamicState> arg6;
        if (!args[6].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[6], &arg6); //is_reference False;
            cobj->dynamicStates = arg6;
        }
        cocos2d::GFXPipelineLayout* arg7 = nullptr;
        if (!args[7].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[7], &arg7); //is_reference False;
            cobj->layout = arg7;
        }
        cocos2d::GFXRenderPass* arg8 = nullptr;
        if (!args[8].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[8], &arg8); //is_reference False;
            cobj->renderPass = arg8;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXPipelineStateInfo_constructor, __jsb_cocos2d_GFXPipelineStateInfo_class, js_cocos2d_GFXPipelineStateInfo_finalize)




static bool js_cocos2d_GFXPipelineStateInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXPipelineStateInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXPipelineStateInfo* cobj = (cocos2d::GFXPipelineStateInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXPipelineStateInfo_finalize)

bool js_register_gfx_GFXPipelineStateInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXPipelineStateInfo", obj, nullptr, _SE(js_gfx_GFXPipelineStateInfo_constructor));

    cls->defineProperty("primitive", _SE(js_gfx_GFXPipelineStateInfo_get_primitive), _SE(js_gfx_GFXPipelineStateInfo_set_primitive));
    cls->defineProperty("shader", _SE(js_gfx_GFXPipelineStateInfo_get_shader), _SE(js_gfx_GFXPipelineStateInfo_set_shader));
    cls->defineProperty("inputState", _SE(js_gfx_GFXPipelineStateInfo_get_inputState), _SE(js_gfx_GFXPipelineStateInfo_set_inputState));
    cls->defineProperty("rasterizerState", _SE(js_gfx_GFXPipelineStateInfo_get_rasterizerState), _SE(js_gfx_GFXPipelineStateInfo_set_rasterizerState));
    cls->defineProperty("depthStencilState", _SE(js_gfx_GFXPipelineStateInfo_get_depthStencilState), _SE(js_gfx_GFXPipelineStateInfo_set_depthStencilState));
    cls->defineProperty("blendState", _SE(js_gfx_GFXPipelineStateInfo_get_blendState), _SE(js_gfx_GFXPipelineStateInfo_set_blendState));
    cls->defineProperty("dynamicStates", _SE(js_gfx_GFXPipelineStateInfo_get_dynamicStates), _SE(js_gfx_GFXPipelineStateInfo_set_dynamicStates));
    cls->defineProperty("layout", _SE(js_gfx_GFXPipelineStateInfo_get_layout), _SE(js_gfx_GFXPipelineStateInfo_set_layout));
    cls->defineProperty("renderPass", _SE(js_gfx_GFXPipelineStateInfo_get_renderPass), _SE(js_gfx_GFXPipelineStateInfo_set_renderPass));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXPipelineStateInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXPipelineStateInfo>(cls);

    __jsb_cocos2d_GFXPipelineStateInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXPipelineStateInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXCommandBufferInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXCommandBufferInfo_class = nullptr;

static bool js_gfx_GFXCommandBufferInfo_get_allocator(se::State& s)
{
    cocos2d::GFXCommandBufferInfo* cobj = (cocos2d::GFXCommandBufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBufferInfo_get_allocator : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->allocator, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXCommandBufferInfo_get_allocator)

static bool js_gfx_GFXCommandBufferInfo_set_allocator(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXCommandBufferInfo* cobj = (cocos2d::GFXCommandBufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBufferInfo_set_allocator : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->allocator); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBufferInfo_set_allocator : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXCommandBufferInfo_set_allocator)

static bool js_gfx_GFXCommandBufferInfo_get_type(se::State& s)
{
    cocos2d::GFXCommandBufferInfo* cobj = (cocos2d::GFXCommandBufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBufferInfo_get_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->type, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXCommandBufferInfo_get_type)

static bool js_gfx_GFXCommandBufferInfo_set_type(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXCommandBufferInfo* cobj = (cocos2d::GFXCommandBufferInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBufferInfo_set_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->type); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBufferInfo_set_type : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXCommandBufferInfo_set_type)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXCommandBufferInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXCommandBufferInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("allocator", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->allocator));
    }
    json->getProperty("type", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->type));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXCommandBufferInfo_finalize)

static bool js_gfx_GFXCommandBufferInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXCommandBufferInfo* cobj = JSB_ALLOC(cocos2d::GFXCommandBufferInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXCommandBufferInfo* cobj = JSB_ALLOC(cocos2d::GFXCommandBufferInfo);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 2)
    {
        cocos2d::GFXCommandBufferInfo* cobj = JSB_ALLOC(cocos2d::GFXCommandBufferInfo);
        cocos2d::GFXCommandAllocator* arg0 = nullptr;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->allocator = arg0;
        }
        cocos2d::GFXCommandBufferType arg1;
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->type = arg1;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXCommandBufferInfo_constructor, __jsb_cocos2d_GFXCommandBufferInfo_class, js_cocos2d_GFXCommandBufferInfo_finalize)




static bool js_cocos2d_GFXCommandBufferInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXCommandBufferInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXCommandBufferInfo* cobj = (cocos2d::GFXCommandBufferInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXCommandBufferInfo_finalize)

bool js_register_gfx_GFXCommandBufferInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXCommandBufferInfo", obj, nullptr, _SE(js_gfx_GFXCommandBufferInfo_constructor));

    cls->defineProperty("allocator", _SE(js_gfx_GFXCommandBufferInfo_get_allocator), _SE(js_gfx_GFXCommandBufferInfo_set_allocator));
    cls->defineProperty("type", _SE(js_gfx_GFXCommandBufferInfo_get_type), _SE(js_gfx_GFXCommandBufferInfo_set_type));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXCommandBufferInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXCommandBufferInfo>(cls);

    __jsb_cocos2d_GFXCommandBufferInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXCommandBufferInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXQueueInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXQueueInfo_class = nullptr;

static bool js_gfx_GFXQueueInfo_get_type(se::State& s)
{
    cocos2d::GFXQueueInfo* cobj = (cocos2d::GFXQueueInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXQueueInfo_get_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->type, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXQueueInfo_get_type)

static bool js_gfx_GFXQueueInfo_set_type(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXQueueInfo* cobj = (cocos2d::GFXQueueInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXQueueInfo_set_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->type); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXQueueInfo_set_type : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXQueueInfo_set_type)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXQueueInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXQueueInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("type", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->type));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXQueueInfo_finalize)

static bool js_gfx_GFXQueueInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXQueueInfo* cobj = JSB_ALLOC(cocos2d::GFXQueueInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1)
    {
        cocos2d::GFXQueueInfo* cobj = JSB_ALLOC(cocos2d::GFXQueueInfo);
        cocos2d::GFXQueueType arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->type = arg0;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXQueueInfo_constructor, __jsb_cocos2d_GFXQueueInfo_class, js_cocos2d_GFXQueueInfo_finalize)




static bool js_cocos2d_GFXQueueInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXQueueInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXQueueInfo* cobj = (cocos2d::GFXQueueInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXQueueInfo_finalize)

bool js_register_gfx_GFXQueueInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXQueueInfo", obj, nullptr, _SE(js_gfx_GFXQueueInfo_constructor));

    cls->defineProperty("type", _SE(js_gfx_GFXQueueInfo_get_type), _SE(js_gfx_GFXQueueInfo_set_type));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXQueueInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXQueueInfo>(cls);

    __jsb_cocos2d_GFXQueueInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXQueueInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXFormatInfo_proto = nullptr;
se::Class* __jsb_cocos2d_GFXFormatInfo_class = nullptr;

static bool js_gfx_GFXFormatInfo_get_name(se::State& s)
{
    cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFormatInfo_get_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->name, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXFormatInfo_get_name)

static bool js_gfx_GFXFormatInfo_set_name(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFormatInfo_set_name : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->name); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXFormatInfo_set_name : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXFormatInfo_set_name)

static bool js_gfx_GFXFormatInfo_get_size(se::State& s)
{
    cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFormatInfo_get_size : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->size, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXFormatInfo_get_size)

static bool js_gfx_GFXFormatInfo_set_size(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFormatInfo_set_size : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->size); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXFormatInfo_set_size : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXFormatInfo_set_size)

static bool js_gfx_GFXFormatInfo_get_count(se::State& s)
{
    cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFormatInfo_get_count : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->count, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXFormatInfo_get_count)

static bool js_gfx_GFXFormatInfo_set_count(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFormatInfo_set_count : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->count); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXFormatInfo_set_count : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXFormatInfo_set_count)

static bool js_gfx_GFXFormatInfo_get_type(se::State& s)
{
    cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFormatInfo_get_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->type, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXFormatInfo_get_type)

static bool js_gfx_GFXFormatInfo_set_type(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFormatInfo_set_type : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->type); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXFormatInfo_set_type : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXFormatInfo_set_type)

static bool js_gfx_GFXFormatInfo_get_hasAlpha(se::State& s)
{
    cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFormatInfo_get_hasAlpha : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->hasAlpha, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXFormatInfo_get_hasAlpha)

static bool js_gfx_GFXFormatInfo_set_hasAlpha(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFormatInfo_set_hasAlpha : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->hasAlpha); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXFormatInfo_set_hasAlpha : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXFormatInfo_set_hasAlpha)

static bool js_gfx_GFXFormatInfo_get_hasDepth(se::State& s)
{
    cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFormatInfo_get_hasDepth : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->hasDepth, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXFormatInfo_get_hasDepth)

static bool js_gfx_GFXFormatInfo_set_hasDepth(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFormatInfo_set_hasDepth : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->hasDepth); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXFormatInfo_set_hasDepth : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXFormatInfo_set_hasDepth)

static bool js_gfx_GFXFormatInfo_get_hasStencil(se::State& s)
{
    cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFormatInfo_get_hasStencil : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->hasStencil, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXFormatInfo_get_hasStencil)

static bool js_gfx_GFXFormatInfo_set_hasStencil(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFormatInfo_set_hasStencil : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->hasStencil); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXFormatInfo_set_hasStencil : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXFormatInfo_set_hasStencil)

static bool js_gfx_GFXFormatInfo_get_isCompressed(se::State& s)
{
    cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFormatInfo_get_isCompressed : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->isCompressed, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXFormatInfo_get_isCompressed)

static bool js_gfx_GFXFormatInfo_set_isCompressed(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFormatInfo_set_isCompressed : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->isCompressed); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXFormatInfo_set_isCompressed : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXFormatInfo_set_isCompressed)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXFormatInfo * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXFormatInfo*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("name", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->name));
    }
    json->getProperty("size", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->size));
    }
    json->getProperty("count", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->count));
    }
    json->getProperty("type", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->type));
    }
    json->getProperty("hasAlpha", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->hasAlpha));
    }
    json->getProperty("hasDepth", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->hasDepth));
    }
    json->getProperty("hasStencil", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->hasStencil));
    }
    json->getProperty("isCompressed", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->isCompressed));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXFormatInfo_finalize)

static bool js_gfx_GFXFormatInfo_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXFormatInfo* cobj = JSB_ALLOC(cocos2d::GFXFormatInfo);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXFormatInfo* cobj = JSB_ALLOC(cocos2d::GFXFormatInfo);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 8)
    {
        cocos2d::GFXFormatInfo* cobj = JSB_ALLOC(cocos2d::GFXFormatInfo);
        cocos2d::String arg0;
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->name = arg0;
        }
        unsigned int arg1 = {};
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->size = arg1;
        }
        unsigned int arg2 = {};
        if (!args[2].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
            cobj->count = arg2;
        }
        cocos2d::GFXFormatType arg3;
        if (!args[3].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
            cobj->type = arg3;
        }
        bool arg4;
        if (!args[4].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
            cobj->hasAlpha = arg4;
        }
        bool arg5;
        if (!args[5].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
            cobj->hasDepth = arg5;
        }
        bool arg6;
        if (!args[6].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[6], &arg6); //is_reference False;
            cobj->hasStencil = arg6;
        }
        bool arg7;
        if (!args[7].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[7], &arg7); //is_reference False;
            cobj->isCompressed = arg7;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXFormatInfo_constructor, __jsb_cocos2d_GFXFormatInfo_class, js_cocos2d_GFXFormatInfo_finalize)




static bool js_cocos2d_GFXFormatInfo_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXFormatInfo)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXFormatInfo* cobj = (cocos2d::GFXFormatInfo*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXFormatInfo_finalize)

bool js_register_gfx_GFXFormatInfo(se::Object* obj)
{
    auto cls = se::Class::create("GFXFormatInfo", obj, nullptr, _SE(js_gfx_GFXFormatInfo_constructor));

    cls->defineProperty("name", _SE(js_gfx_GFXFormatInfo_get_name), _SE(js_gfx_GFXFormatInfo_set_name));
    cls->defineProperty("size", _SE(js_gfx_GFXFormatInfo_get_size), _SE(js_gfx_GFXFormatInfo_set_size));
    cls->defineProperty("count", _SE(js_gfx_GFXFormatInfo_get_count), _SE(js_gfx_GFXFormatInfo_set_count));
    cls->defineProperty("type", _SE(js_gfx_GFXFormatInfo_get_type), _SE(js_gfx_GFXFormatInfo_set_type));
    cls->defineProperty("hasAlpha", _SE(js_gfx_GFXFormatInfo_get_hasAlpha), _SE(js_gfx_GFXFormatInfo_set_hasAlpha));
    cls->defineProperty("hasDepth", _SE(js_gfx_GFXFormatInfo_get_hasDepth), _SE(js_gfx_GFXFormatInfo_set_hasDepth));
    cls->defineProperty("hasStencil", _SE(js_gfx_GFXFormatInfo_get_hasStencil), _SE(js_gfx_GFXFormatInfo_set_hasStencil));
    cls->defineProperty("isCompressed", _SE(js_gfx_GFXFormatInfo_get_isCompressed), _SE(js_gfx_GFXFormatInfo_set_isCompressed));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXFormatInfo_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXFormatInfo>(cls);

    __jsb_cocos2d_GFXFormatInfo_proto = cls->getProto();
    __jsb_cocos2d_GFXFormatInfo_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXMemoryStatus_proto = nullptr;
se::Class* __jsb_cocos2d_GFXMemoryStatus_class = nullptr;

static bool js_gfx_GFXMemoryStatus_get_bufferSize(se::State& s)
{
    cocos2d::GFXMemoryStatus* cobj = (cocos2d::GFXMemoryStatus*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXMemoryStatus_get_bufferSize : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->bufferSize, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXMemoryStatus_get_bufferSize)

static bool js_gfx_GFXMemoryStatus_set_bufferSize(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXMemoryStatus* cobj = (cocos2d::GFXMemoryStatus*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXMemoryStatus_set_bufferSize : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->bufferSize); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXMemoryStatus_set_bufferSize : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXMemoryStatus_set_bufferSize)

static bool js_gfx_GFXMemoryStatus_get_textureSize(se::State& s)
{
    cocos2d::GFXMemoryStatus* cobj = (cocos2d::GFXMemoryStatus*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXMemoryStatus_get_textureSize : Invalid Native Object");

    CC_UNUSED bool ok = true;
    se::Value jsret;
    ok &= nativevalue_to_se(cobj->textureSize, jsret);
    s.rval() = jsret;
    return true;
}
SE_BIND_PROP_GET(js_gfx_GFXMemoryStatus_get_textureSize)

static bool js_gfx_GFXMemoryStatus_set_textureSize(se::State& s)
{
    const auto& args = s.args();
    cocos2d::GFXMemoryStatus* cobj = (cocos2d::GFXMemoryStatus*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXMemoryStatus_set_textureSize : Invalid Native Object");

    CC_UNUSED bool ok = true;
    ok &= sevalue_to_native(args[0], &cobj->textureSize); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXMemoryStatus_set_textureSize : Error processing new value");
    return true;
}
SE_BIND_PROP_SET(js_gfx_GFXMemoryStatus_set_textureSize)


template<>
bool sevalue_to_native(const se::Value &from, cocos2d::GFXMemoryStatus * to)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = (cocos2d::GFXMemoryStatus*)json->getPrivateData();
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    json->getProperty("bufferSize", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->bufferSize));
    }
    json->getProperty("textureSize", &field);
    if(!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->textureSize));
    }
    return ok;
}

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXMemoryStatus_finalize)

static bool js_gfx_GFXMemoryStatus_constructor(se::State& s)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();

    if(argc == 0) 
    {
        cocos2d::GFXMemoryStatus* cobj = JSB_ALLOC(cocos2d::GFXMemoryStatus);
        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 1 && args[0].isObject())
    {
        se::Object *json = args[0].toObject();
        se::Value field;

        cocos2d::GFXMemoryStatus* cobj = JSB_ALLOC(cocos2d::GFXMemoryStatus);
        ok &= sevalue_to_native(args[0], cobj);
        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }
    else if(argc == 2)
    {
        cocos2d::GFXMemoryStatus* cobj = JSB_ALLOC(cocos2d::GFXMemoryStatus);
        unsigned int arg0 = {};
        if (!args[0].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
            cobj->bufferSize = arg0;
        }
        unsigned int arg1 = {};
        if (!args[1].isNullOrUndefined()) {
            ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
            cobj->textureSize = arg1;
        }

        if(!ok) {
            JSB_FREE(cobj);
            SE_REPORT_ERROR("Argument convertion error");
            return false;
        }

        s.thisObject()->setPrivateData(cobj);
        se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
        return true;
    }

    SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
    return false;
}
SE_BIND_CTOR(js_gfx_GFXMemoryStatus_constructor, __jsb_cocos2d_GFXMemoryStatus_class, js_cocos2d_GFXMemoryStatus_finalize)




static bool js_cocos2d_GFXMemoryStatus_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXMemoryStatus)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXMemoryStatus* cobj = (cocos2d::GFXMemoryStatus*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXMemoryStatus_finalize)

bool js_register_gfx_GFXMemoryStatus(se::Object* obj)
{
    auto cls = se::Class::create("GFXMemoryStatus", obj, nullptr, _SE(js_gfx_GFXMemoryStatus_constructor));

    cls->defineProperty("bufferSize", _SE(js_gfx_GFXMemoryStatus_get_bufferSize), _SE(js_gfx_GFXMemoryStatus_set_bufferSize));
    cls->defineProperty("textureSize", _SE(js_gfx_GFXMemoryStatus_get_textureSize), _SE(js_gfx_GFXMemoryStatus_set_textureSize));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXMemoryStatus_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXMemoryStatus>(cls);

    __jsb_cocos2d_GFXMemoryStatus_proto = cls->getProto();
    __jsb_cocos2d_GFXMemoryStatus_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXObject_proto = nullptr;
se::Class* __jsb_cocos2d_GFXObject_class = nullptr;

static bool js_gfx_GFXObject_getType(se::State& s)
{
    cocos2d::GFXObject* cobj = (cocos2d::GFXObject*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXObject_getType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getType();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXObject_getType : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXObject_getType)

static bool js_gfx_GFXObject_getStatus(se::State& s)
{
    cocos2d::GFXObject* cobj = (cocos2d::GFXObject*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXObject_getStatus : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getStatus();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXObject_getStatus : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXObject_getStatus)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXObject_finalize)

static bool js_gfx_GFXObject_constructor(se::State& s) // constructor.c
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    cocos2d::GFXObjectType arg0;
    ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
    SE_PRECONDITION2(ok, false, "js_gfx_GFXObject_constructor : Error processing arguments");
    cocos2d::GFXObject* cobj = JSB_ALLOC(cocos2d::GFXObject, arg0);
    s.thisObject()->setPrivateData(cobj);
    se::NonRefNativePtrCreatedByCtorMap::emplace(cobj);
    return true;
}
SE_BIND_CTOR(js_gfx_GFXObject_constructor, __jsb_cocos2d_GFXObject_class, js_cocos2d_GFXObject_finalize)




static bool js_cocos2d_GFXObject_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXObject)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXObject* cobj = (cocos2d::GFXObject*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXObject_finalize)

bool js_register_gfx_GFXObject(se::Object* obj)
{
    auto cls = se::Class::create("GFXObject", obj, nullptr, _SE(js_gfx_GFXObject_constructor));

    cls->defineProperty("status", _SE(js_gfx_GFXObject_getStatus), nullptr);
    cls->defineProperty("gfxType", _SE(js_gfx_GFXObject_getType), nullptr);
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXObject_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXObject>(cls);

    __jsb_cocos2d_GFXObject_proto = cls->getProto();
    __jsb_cocos2d_GFXObject_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXDevice_proto = nullptr;
se::Class* __jsb_cocos2d_GFXDevice_class = nullptr;

static bool js_gfx_GFXDevice_getMaxUniformBlockSize(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getMaxUniformBlockSize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getMaxUniformBlockSize();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getMaxUniformBlockSize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getMaxUniformBlockSize)

static bool js_gfx_GFXDevice_getMaxVertexTextureUnits(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getMaxVertexTextureUnits : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getMaxVertexTextureUnits();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getMaxVertexTextureUnits : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getMaxVertexTextureUnits)

static bool js_gfx_GFXDevice_getNumInstances(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getNumInstances : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getNumInstances();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getNumInstances : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getNumInstances)

static bool js_gfx_GFXDevice_getMaxVertexUniformVectors(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getMaxVertexUniformVectors : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getMaxVertexUniformVectors();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getMaxVertexUniformVectors : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getMaxVertexUniformVectors)

static bool js_gfx_GFXDevice_getGfxAPI(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getGfxAPI : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getGfxAPI();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getGfxAPI : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getGfxAPI)

static bool js_gfx_GFXDevice_getCommandAllocator(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getCommandAllocator : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXCommandAllocator* result = cobj->getCommandAllocator();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getCommandAllocator : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getCommandAllocator)

static bool js_gfx_GFXDevice_hasFeature(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_hasFeature : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXFeature, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_hasFeature : Error processing arguments");
        bool result = cobj->hasFeature(HolderType<cocos2d::GFXFeature, false>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_hasFeature : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_hasFeature)

static bool js_gfx_GFXDevice_getContext(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getContext : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXContext* result = cobj->getContext();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getContext : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getContext)

static bool js_gfx_GFXDevice_getWidth(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getWidth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getWidth();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getWidth : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getWidth)

static bool js_gfx_GFXDevice_setReverseCW(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_setReverseCW : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<bool, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_setReverseCW : Error processing arguments");
        cobj->setReverseCW(HolderType<bool, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_PROP_SET(js_gfx_GFXDevice_setReverseCW)

static bool js_gfx_GFXDevice_getQueue(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getQueue : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXQueue* result = cobj->getQueue();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getQueue : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getQueue)

static bool js_gfx_GFXDevice_getMaxVertexAttributes(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getMaxVertexAttributes : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getMaxVertexAttributes();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getMaxVertexAttributes : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getMaxVertexAttributes)

static bool js_gfx_GFXDevice_getDepthStencilFormat(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getDepthStencilFormat : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getDepthStencilFormat();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getDepthStencilFormat : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_getDepthStencilFormat)

static bool js_gfx_GFXDevice_getNumTris(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getNumTris : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getNumTris();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getNumTris : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getNumTris)

static bool js_gfx_GFXDevice_getRenderer(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getRenderer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::String& result = cobj->getRenderer();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getRenderer : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getRenderer)

static bool js_gfx_GFXDevice_getStencilBits(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getStencilBits : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getStencilBits();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getStencilBits : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getStencilBits)

static bool js_gfx_GFXDevice_getDeviceName(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getDeviceName : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::String& result = cobj->getDeviceName();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getDeviceName : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getDeviceName)

static bool js_gfx_GFXDevice_getVendor(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getVendor : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::String& result = cobj->getVendor();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getVendor : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getVendor)

static bool js_gfx_GFXDevice_getHeight(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getHeight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getHeight();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getHeight : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getHeight)

static bool js_gfx_GFXDevice_getMaxFragmentUniformVectors(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getMaxFragmentUniformVectors : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getMaxFragmentUniformVectors();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getMaxFragmentUniformVectors : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getMaxFragmentUniformVectors)

static bool js_gfx_GFXDevice_createPipelineState(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_createPipelineState : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXPipelineStateInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createPipelineState : Error processing arguments");
        cocos2d::GFXPipelineState* result = cobj->createPipelineState(HolderType<cocos2d::GFXPipelineStateInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createPipelineState : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_createPipelineState)

static bool js_gfx_GFXDevice_createCommandBuffer(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_createCommandBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXCommandBufferInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createCommandBuffer : Error processing arguments");
        cocos2d::GFXCommandBuffer* result = cobj->createCommandBuffer(HolderType<cocos2d::GFXCommandBufferInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createCommandBuffer : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_createCommandBuffer)

static bool js_gfx_GFXDevice_present(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_present : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->present();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_present)

static bool js_gfx_GFXDevice_createTexture(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_createTexture : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXTextureInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createTexture : Error processing arguments");
        cocos2d::GFXTexture* result = cobj->createTexture(HolderType<cocos2d::GFXTextureInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createTexture : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_createTexture)

static bool js_gfx_GFXDevice_destroy(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_destroy)

static bool js_gfx_GFXDevice_getColorFormat(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getColorFormat : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getColorFormat();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getColorFormat : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_getColorFormat)

static bool js_gfx_GFXDevice_createFramebuffer(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_createFramebuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXFramebufferInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createFramebuffer : Error processing arguments");
        cocos2d::GFXFramebuffer* result = cobj->createFramebuffer(HolderType<cocos2d::GFXFramebufferInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createFramebuffer : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_createFramebuffer)

static bool js_gfx_GFXDevice_getMaxTextureSize(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getMaxTextureSize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getMaxTextureSize();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getMaxTextureSize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getMaxTextureSize)

static bool js_gfx_GFXDevice_createRenderPass(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_createRenderPass : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXRenderPassInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createRenderPass : Error processing arguments");
        cocos2d::GFXRenderPass* result = cobj->createRenderPass(HolderType<cocos2d::GFXRenderPassInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createRenderPass : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_createRenderPass)

static bool js_gfx_GFXDevice_createPipelineLayout(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_createPipelineLayout : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXPipelineLayoutInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createPipelineLayout : Error processing arguments");
        cocos2d::GFXPipelineLayout* result = cobj->createPipelineLayout(HolderType<cocos2d::GFXPipelineLayoutInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createPipelineLayout : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_createPipelineLayout)

static bool js_gfx_GFXDevice_createWindow(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_createWindow : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXWindowInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createWindow : Error processing arguments");
        cocos2d::GFXWindow* result = cobj->createWindow(HolderType<cocos2d::GFXWindowInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createWindow : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_createWindow)

static bool js_gfx_GFXDevice_getMaxCubeMapTextureSize(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getMaxCubeMapTextureSize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getMaxCubeMapTextureSize();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getMaxCubeMapTextureSize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getMaxCubeMapTextureSize)

static bool js_gfx_GFXDevice_getShaderIdGen(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getShaderIdGen : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getShaderIdGen();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getShaderIdGen : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getShaderIdGen)

static bool js_gfx_GFXDevice_getMaxUniformBufferBindings(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getMaxUniformBufferBindings : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getMaxUniformBufferBindings();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getMaxUniformBufferBindings : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getMaxUniformBufferBindings)

static bool js_gfx_GFXDevice_createShader(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_createShader : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXShaderInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createShader : Error processing arguments");
        cocos2d::GFXShader* result = cobj->createShader(HolderType<cocos2d::GFXShaderInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createShader : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_createShader)

static bool js_gfx_GFXDevice_createInputAssembler(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_createInputAssembler : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXInputAssemblerInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createInputAssembler : Error processing arguments");
        cocos2d::GFXInputAssembler* result = cobj->createInputAssembler(HolderType<cocos2d::GFXInputAssemblerInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createInputAssembler : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_createInputAssembler)

static bool js_gfx_GFXDevice_defineMacro(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_defineMacro : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<cocos2d::String, true>::local_type arg0 = {};
        HolderType<cocos2d::String, true>::local_type arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        ok &= sevalue_to_native(args[1], &arg1); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_defineMacro : Error processing arguments");
        cobj->defineMacro(HolderType<cocos2d::String, true>::value(arg0), HolderType<cocos2d::String, true>::value(arg1));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_defineMacro)

static bool js_gfx_GFXDevice_createSampler(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_createSampler : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXSamplerInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createSampler : Error processing arguments");
        cocos2d::GFXSampler* result = cobj->createSampler(HolderType<cocos2d::GFXSamplerInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createSampler : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_createSampler)

static bool js_gfx_GFXDevice_createBuffer(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_createBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXBufferInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createBuffer : Error processing arguments");
        cocos2d::GFXBuffer* result = cobj->createBuffer(HolderType<cocos2d::GFXBufferInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createBuffer : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_createBuffer)

static bool js_gfx_GFXDevice_getNativeHeight(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getNativeHeight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getNativeHeight();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getNativeHeight : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getNativeHeight)

static bool js_gfx_GFXDevice_initialize(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXDeviceInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_initialize : Error processing arguments");
        bool result = cobj->initialize(HolderType<cocos2d::GFXDeviceInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_initialize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_initialize)

static bool js_gfx_GFXDevice_resize(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_resize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<unsigned int, false>::local_type arg0 = {};
        HolderType<unsigned int, false>::local_type arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_resize : Error processing arguments");
        cobj->resize(HolderType<unsigned int, false>::value(arg0), HolderType<unsigned int, false>::value(arg1));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_resize)

static bool js_gfx_GFXDevice_createQueue(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_createQueue : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXQueueInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createQueue : Error processing arguments");
        cocos2d::GFXQueue* result = cobj->createQueue(HolderType<cocos2d::GFXQueueInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createQueue : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_createQueue)

static bool js_gfx_GFXDevice_getDepthBits(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getDepthBits : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getDepthBits();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getDepthBits : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getDepthBits)

static bool js_gfx_GFXDevice_getMemoryStatus(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getMemoryStatus : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXMemoryStatus& result = cobj->getMemoryStatus();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getMemoryStatus : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getMemoryStatus)

static bool js_gfx_GFXDevice_getMaxTextureUnits(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getMaxTextureUnits : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getMaxTextureUnits();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getMaxTextureUnits : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getMaxTextureUnits)

static bool js_gfx_GFXDevice_getReverseCW(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getReverseCW : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->getReverseCW();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getReverseCW : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getReverseCW)

static bool js_gfx_GFXDevice_getMainWindow(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getMainWindow : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXWindow* result = cobj->getMainWindow();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getMainWindow : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getMainWindow)

static bool js_gfx_GFXDevice_getNumDrawCalls(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getNumDrawCalls : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getNumDrawCalls();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getNumDrawCalls : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getNumDrawCalls)

static bool js_gfx_GFXDevice_getNativeWidth(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_getNativeWidth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getNativeWidth();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_getNativeWidth : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXDevice_getNativeWidth)

static bool js_gfx_GFXDevice_createBindingLayout(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_createBindingLayout : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXBindingLayoutInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createBindingLayout : Error processing arguments");
        cocos2d::GFXBindingLayout* result = cobj->createBindingLayout(HolderType<cocos2d::GFXBindingLayoutInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createBindingLayout : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_createBindingLayout)

static bool js_gfx_GFXDevice_createTextureView(se::State& s)
{
    cocos2d::GFXDevice* cobj = (cocos2d::GFXDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXDevice_createTextureView : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXTextureViewInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createTextureView : Error processing arguments");
        cocos2d::GFXTextureView* result = cobj->createTextureView(HolderType<cocos2d::GFXTextureViewInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_createTextureView : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXDevice_createTextureView)




bool js_register_gfx_GFXDevice(se::Object* obj)
{
    auto cls = se::Class::create("GFXDevice", obj, nullptr, nullptr);

    cls->defineProperty("deviceName", _SE(js_gfx_GFXDevice_getDeviceName), nullptr);
    cls->defineProperty("numInstances", _SE(js_gfx_GFXDevice_getNumInstances), nullptr);
    cls->defineProperty("maxTextureUnits", _SE(js_gfx_GFXDevice_getMaxTextureUnits), nullptr);
    cls->defineProperty("height", _SE(js_gfx_GFXDevice_getHeight), nullptr);
    cls->defineProperty("shaderIdGen", _SE(js_gfx_GFXDevice_getShaderIdGen), nullptr);
    cls->defineProperty("renderer", _SE(js_gfx_GFXDevice_getRenderer), nullptr);
    cls->defineProperty("maxUniformBufferBindings", _SE(js_gfx_GFXDevice_getMaxUniformBufferBindings), nullptr);
    cls->defineProperty("vendor", _SE(js_gfx_GFXDevice_getVendor), nullptr);
    cls->defineProperty("depthBits", _SE(js_gfx_GFXDevice_getDepthBits), nullptr);
    cls->defineProperty("reverseCW", _SE(js_gfx_GFXDevice_getReverseCW), _SE(js_gfx_GFXDevice_setReverseCW));
    cls->defineProperty("maxFragmentUniformVectors", _SE(js_gfx_GFXDevice_getMaxFragmentUniformVectors), nullptr);
    cls->defineProperty("maxVertexAttributes", _SE(js_gfx_GFXDevice_getMaxVertexAttributes), nullptr);
    cls->defineProperty("width", _SE(js_gfx_GFXDevice_getWidth), nullptr);
    cls->defineProperty("commandAllocator", _SE(js_gfx_GFXDevice_getCommandAllocator), nullptr);
    cls->defineProperty("maxVertexUniformVectors", _SE(js_gfx_GFXDevice_getMaxVertexUniformVectors), nullptr);
    cls->defineProperty("maxCubeMapTextureSize", _SE(js_gfx_GFXDevice_getMaxCubeMapTextureSize), nullptr);
    cls->defineProperty("maxVertexTextureUnits", _SE(js_gfx_GFXDevice_getMaxVertexTextureUnits), nullptr);
    cls->defineProperty("nativeWidth", _SE(js_gfx_GFXDevice_getNativeWidth), nullptr);
    cls->defineProperty("numDrawCalls", _SE(js_gfx_GFXDevice_getNumDrawCalls), nullptr);
    cls->defineProperty("memoryStatus", _SE(js_gfx_GFXDevice_getMemoryStatus), nullptr);
    cls->defineProperty("gfxAPI", _SE(js_gfx_GFXDevice_getGfxAPI), nullptr);
    cls->defineProperty("maxUniformBlockSize", _SE(js_gfx_GFXDevice_getMaxUniformBlockSize), nullptr);
    cls->defineProperty("maxTextureSize", _SE(js_gfx_GFXDevice_getMaxTextureSize), nullptr);
    cls->defineProperty("nativeHeight", _SE(js_gfx_GFXDevice_getNativeHeight), nullptr);
    cls->defineProperty("numTris", _SE(js_gfx_GFXDevice_getNumTris), nullptr);
    cls->defineProperty("stencilBits", _SE(js_gfx_GFXDevice_getStencilBits), nullptr);
    cls->defineProperty("queue", _SE(js_gfx_GFXDevice_getQueue), nullptr);
    cls->defineProperty("context", _SE(js_gfx_GFXDevice_getContext), nullptr);
    cls->defineProperty("mainWindow", _SE(js_gfx_GFXDevice_getMainWindow), nullptr);
    cls->defineFunction("hasFeature", _SE(js_gfx_GFXDevice_hasFeature));
    cls->defineFunction("getDepthStencilFormat", _SE(js_gfx_GFXDevice_getDepthStencilFormat));
    cls->defineFunction("createPipelineState", _SE(js_gfx_GFXDevice_createPipelineState));
    cls->defineFunction("createCommandBuffer", _SE(js_gfx_GFXDevice_createCommandBuffer));
    cls->defineFunction("present", _SE(js_gfx_GFXDevice_present));
    cls->defineFunction("createTexture", _SE(js_gfx_GFXDevice_createTexture));
    cls->defineFunction("destroy", _SE(js_gfx_GFXDevice_destroy));
    cls->defineFunction("getColorFormat", _SE(js_gfx_GFXDevice_getColorFormat));
    cls->defineFunction("createFramebuffer", _SE(js_gfx_GFXDevice_createFramebuffer));
    cls->defineFunction("createRenderPass", _SE(js_gfx_GFXDevice_createRenderPass));
    cls->defineFunction("createPipelineLayout", _SE(js_gfx_GFXDevice_createPipelineLayout));
    cls->defineFunction("createWindow", _SE(js_gfx_GFXDevice_createWindow));
    cls->defineFunction("createShader", _SE(js_gfx_GFXDevice_createShader));
    cls->defineFunction("createInputAssembler", _SE(js_gfx_GFXDevice_createInputAssembler));
    cls->defineFunction("defineMacro", _SE(js_gfx_GFXDevice_defineMacro));
    cls->defineFunction("createSampler", _SE(js_gfx_GFXDevice_createSampler));
    cls->defineFunction("createBuffer", _SE(js_gfx_GFXDevice_createBuffer));
    cls->defineFunction("initialize", _SE(js_gfx_GFXDevice_initialize));
    cls->defineFunction("resize", _SE(js_gfx_GFXDevice_resize));
    cls->defineFunction("createQueue", _SE(js_gfx_GFXDevice_createQueue));
    cls->defineFunction("createBindingLayout", _SE(js_gfx_GFXDevice_createBindingLayout));
    cls->defineFunction("createTextureView", _SE(js_gfx_GFXDevice_createTextureView));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXDevice>(cls);

    __jsb_cocos2d_GFXDevice_proto = cls->getProto();
    __jsb_cocos2d_GFXDevice_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXWindow_proto = nullptr;
se::Class* __jsb_cocos2d_GFXWindow_class = nullptr;

static bool js_gfx_GFXWindow_getTop(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_getTop : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getTop();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_getTop : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXWindow_getTop)

static bool js_gfx_GFXWindow_getDepthStencilTexture(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_getDepthStencilTexture : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXTexture* result = cobj->getDepthStencilTexture();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_getDepthStencilTexture : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXWindow_getDepthStencilTexture)

static bool js_gfx_GFXWindow_getDepthStencilFormat(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_getDepthStencilFormat : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getDepthStencilFormat();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_getDepthStencilFormat : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXWindow_getDepthStencilFormat)

static bool js_gfx_GFXWindow_getLeft(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_getLeft : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = cobj->getLeft();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_getLeft : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXWindow_getLeft)

static bool js_gfx_GFXWindow_getColorTexView(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_getColorTexView : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXTextureView* result = cobj->getColorTexView();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_getColorTexView : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXWindow_getColorTexView)

static bool js_gfx_GFXWindow_getColorFormat(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_getColorFormat : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getColorFormat();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_getColorFormat : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXWindow_getColorFormat)

static bool js_gfx_GFXWindow_getNativeHeight(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_getNativeHeight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getNativeHeight();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_getNativeHeight : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXWindow_getNativeHeight)

static bool js_gfx_GFXWindow_getHeight(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_getHeight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getHeight();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_getHeight : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXWindow_getHeight)

static bool js_gfx_GFXWindow_getColorTexture(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_getColorTexture : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXTexture* result = cobj->getColorTexture();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_getColorTexture : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXWindow_getColorTexture)

static bool js_gfx_GFXWindow_getWidth(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_getWidth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getWidth();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_getWidth : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXWindow_getWidth)

static bool js_gfx_GFXWindow_isOffscreen(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_isOffscreen : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isOffscreen();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_isOffscreen : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXWindow_isOffscreen)

static bool js_gfx_GFXWindow_getFramebuffer(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_getFramebuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXFramebuffer* result = cobj->getFramebuffer();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_getFramebuffer : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXWindow_getFramebuffer)

static bool js_gfx_GFXWindow_getTitle(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_getTitle : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::String& result = cobj->getTitle();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_getTitle : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXWindow_getTitle)

static bool js_gfx_GFXWindow_initialize(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXWindowInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_initialize : Error processing arguments");
        bool result = cobj->initialize(HolderType<cocos2d::GFXWindowInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_initialize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXWindow_initialize)

static bool js_gfx_GFXWindow_destroy(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXWindow_destroy)

static bool js_gfx_GFXWindow_getRenderPass(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_getRenderPass : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXRenderPass* result = cobj->getRenderPass();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_getRenderPass : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXWindow_getRenderPass)

static bool js_gfx_GFXWindow_getDevice(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_getDevice : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXDevice* result = cobj->getDevice();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_getDevice : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXWindow_getDevice)

static bool js_gfx_GFXWindow_getNativeWidth(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_getNativeWidth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getNativeWidth();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_getNativeWidth : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXWindow_getNativeWidth)

static bool js_gfx_GFXWindow_resize(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_resize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<unsigned int, false>::local_type arg0 = {};
        HolderType<unsigned int, false>::local_type arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_resize : Error processing arguments");
        cobj->resize(HolderType<unsigned int, false>::value(arg0), HolderType<unsigned int, false>::value(arg1));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXWindow_resize)

static bool js_gfx_GFXWindow_getDepthStencilTexView(se::State& s)
{
    cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXWindow_getDepthStencilTexView : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXTextureView* result = cobj->getDepthStencilTexView();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXWindow_getDepthStencilTexView : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXWindow_getDepthStencilTexView)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXWindow_finalize)

static bool js_gfx_GFXWindow_constructor(se::State& s) // constructor.c
{
    //#3 cocos2d::GFXWindow: is_skip_construtor True
    se::ScriptEngine::getInstance()->evalString("throw new Error(\"cocos2d::GFXWindow constructor is skipped\")");
    return false;
}
SE_BIND_CTOR(js_gfx_GFXWindow_constructor, __jsb_cocos2d_GFXWindow_class, js_cocos2d_GFXWindow_finalize)



extern se::Object* __jsb_cocos2d_GFXObject_proto;

static bool js_cocos2d_GFXWindow_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXWindow)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXWindow* cobj = (cocos2d::GFXWindow*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXWindow_finalize)

bool js_register_gfx_GFXWindow(se::Object* obj)
{
    auto cls = se::Class::create("GFXWindow", obj, __jsb_cocos2d_GFXObject_proto, _SE(js_gfx_GFXWindow_constructor));

    cls->defineProperty("nativeHeight", _SE(js_gfx_GFXWindow_getNativeHeight), nullptr);
    cls->defineProperty("depthStencilTexView", _SE(js_gfx_GFXWindow_getDepthStencilTexView), nullptr);
    cls->defineProperty("nativeWidth", _SE(js_gfx_GFXWindow_getNativeWidth), nullptr);
    cls->defineProperty("title", _SE(js_gfx_GFXWindow_getTitle), nullptr);
    cls->defineProperty("isOffscreen", _SE(js_gfx_GFXWindow_isOffscreen), nullptr);
    cls->defineProperty("top", _SE(js_gfx_GFXWindow_getTop), nullptr);
    cls->defineProperty("height", _SE(js_gfx_GFXWindow_getHeight), nullptr);
    cls->defineProperty("width", _SE(js_gfx_GFXWindow_getWidth), nullptr);
    cls->defineProperty("colorTexView", _SE(js_gfx_GFXWindow_getColorTexView), nullptr);
    cls->defineProperty("depthStencilTexture", _SE(js_gfx_GFXWindow_getDepthStencilTexture), nullptr);
    cls->defineProperty("device", _SE(js_gfx_GFXWindow_getDevice), nullptr);
    cls->defineProperty("renderPass", _SE(js_gfx_GFXWindow_getRenderPass), nullptr);
    cls->defineProperty("framebuffer", _SE(js_gfx_GFXWindow_getFramebuffer), nullptr);
    cls->defineProperty("colorFormat", _SE(js_gfx_GFXWindow_getColorFormat), nullptr);
    cls->defineProperty("colorTexture", _SE(js_gfx_GFXWindow_getColorTexture), nullptr);
    cls->defineProperty("left", _SE(js_gfx_GFXWindow_getLeft), nullptr);
    cls->defineFunction("getDepthStencilFormat", _SE(js_gfx_GFXWindow_getDepthStencilFormat));
    cls->defineFunction("initialize", _SE(js_gfx_GFXWindow_initialize));
    cls->defineFunction("destroy", _SE(js_gfx_GFXWindow_destroy));
    cls->defineFunction("resize", _SE(js_gfx_GFXWindow_resize));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXWindow_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXWindow>(cls);

    __jsb_cocos2d_GFXWindow_proto = cls->getProto();
    __jsb_cocos2d_GFXWindow_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXBuffer_proto = nullptr;
se::Class* __jsb_cocos2d_GFXBuffer_class = nullptr;

static bool js_gfx_GFXBuffer_getBufferView(se::State& s)
{
    cocos2d::GFXBuffer* cobj = (cocos2d::GFXBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBuffer_getBufferView : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned char* result = cobj->getBufferView();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBuffer_getBufferView : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXBuffer_getBufferView)

static bool js_gfx_GFXBuffer_getUsage(se::State& s)
{
    cocos2d::GFXBuffer* cobj = (cocos2d::GFXBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBuffer_getUsage : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getUsage();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBuffer_getUsage : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXBuffer_getUsage)

static bool js_gfx_GFXBuffer_getMemUsage(se::State& s)
{
    cocos2d::GFXBuffer* cobj = (cocos2d::GFXBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBuffer_getMemUsage : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getMemUsage();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBuffer_getMemUsage : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXBuffer_getMemUsage)

static bool js_gfx_GFXBuffer_getSize(se::State& s)
{
    cocos2d::GFXBuffer* cobj = (cocos2d::GFXBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBuffer_getSize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getSize();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBuffer_getSize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXBuffer_getSize)

static bool js_gfx_GFXBuffer_getCount(se::State& s)
{
    cocos2d::GFXBuffer* cobj = (cocos2d::GFXBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBuffer_getCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getCount();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBuffer_getCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXBuffer_getCount)

static bool js_gfx_GFXBuffer_initialize(se::State& s)
{
    cocos2d::GFXBuffer* cobj = (cocos2d::GFXBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBuffer_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXBufferInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBuffer_initialize : Error processing arguments");
        bool result = cobj->initialize(HolderType<cocos2d::GFXBufferInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBuffer_initialize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXBuffer_initialize)

static bool js_gfx_GFXBuffer_destroy(se::State& s)
{
    cocos2d::GFXBuffer* cobj = (cocos2d::GFXBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBuffer_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXBuffer_destroy)

static bool js_gfx_GFXBuffer_getStride(se::State& s)
{
    cocos2d::GFXBuffer* cobj = (cocos2d::GFXBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBuffer_getStride : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getStride();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBuffer_getStride : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXBuffer_getStride)

static bool js_gfx_GFXBuffer_getDevice(se::State& s)
{
    cocos2d::GFXBuffer* cobj = (cocos2d::GFXBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBuffer_getDevice : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXDevice* result = cobj->getDevice();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBuffer_getDevice : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXBuffer_getDevice)

static bool js_gfx_GFXBuffer_getFlags(se::State& s)
{
    cocos2d::GFXBuffer* cobj = (cocos2d::GFXBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBuffer_getFlags : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getFlags();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBuffer_getFlags : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXBuffer_getFlags)

static bool js_gfx_GFXBuffer_resize(se::State& s)
{
    cocos2d::GFXBuffer* cobj = (cocos2d::GFXBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBuffer_resize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBuffer_resize : Error processing arguments");
        cobj->resize(HolderType<unsigned int, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXBuffer_resize)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXBuffer_finalize)

static bool js_gfx_GFXBuffer_constructor(se::State& s) // constructor.c
{
    //#3 cocos2d::GFXBuffer: is_skip_construtor True
    se::ScriptEngine::getInstance()->evalString("throw new Error(\"cocos2d::GFXBuffer constructor is skipped\")");
    return false;
}
SE_BIND_CTOR(js_gfx_GFXBuffer_constructor, __jsb_cocos2d_GFXBuffer_class, js_cocos2d_GFXBuffer_finalize)



extern se::Object* __jsb_cocos2d_GFXObject_proto;

static bool js_cocos2d_GFXBuffer_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXBuffer)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXBuffer* cobj = (cocos2d::GFXBuffer*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXBuffer_finalize)

bool js_register_gfx_GFXBuffer(se::Object* obj)
{
    auto cls = se::Class::create("GFXBuffer", obj, __jsb_cocos2d_GFXObject_proto, _SE(js_gfx_GFXBuffer_constructor));

    cls->defineProperty("count", _SE(js_gfx_GFXBuffer_getCount), nullptr);
    cls->defineProperty("memUsage", _SE(js_gfx_GFXBuffer_getMemUsage), nullptr);
    cls->defineProperty("stride", _SE(js_gfx_GFXBuffer_getStride), nullptr);
    cls->defineProperty("bufferView", _SE(js_gfx_GFXBuffer_getBufferView), nullptr);
    cls->defineProperty("usage", _SE(js_gfx_GFXBuffer_getUsage), nullptr);
    cls->defineProperty("flags", _SE(js_gfx_GFXBuffer_getFlags), nullptr);
    cls->defineProperty("device", _SE(js_gfx_GFXBuffer_getDevice), nullptr);
    cls->defineProperty("size", _SE(js_gfx_GFXBuffer_getSize), nullptr);
    cls->defineFunction("initialize", _SE(js_gfx_GFXBuffer_initialize));
    cls->defineFunction("destroy", _SE(js_gfx_GFXBuffer_destroy));
    cls->defineFunction("resize", _SE(js_gfx_GFXBuffer_resize));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXBuffer_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXBuffer>(cls);

    __jsb_cocos2d_GFXBuffer_proto = cls->getProto();
    __jsb_cocos2d_GFXBuffer_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXTexture_proto = nullptr;
se::Class* __jsb_cocos2d_GFXTexture_class = nullptr;

static bool js_gfx_GFXTexture_getSize(se::State& s)
{
    cocos2d::GFXTexture* cobj = (cocos2d::GFXTexture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTexture_getSize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getSize();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTexture_getSize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTexture_getSize)

static bool js_gfx_GFXTexture_getDepth(se::State& s)
{
    cocos2d::GFXTexture* cobj = (cocos2d::GFXTexture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTexture_getDepth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getDepth();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTexture_getDepth : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTexture_getDepth)

static bool js_gfx_GFXTexture_getType(se::State& s)
{
    cocos2d::GFXTexture* cobj = (cocos2d::GFXTexture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTexture_getType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getType();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTexture_getType : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTexture_getType)

static bool js_gfx_GFXTexture_getHeight(se::State& s)
{
    cocos2d::GFXTexture* cobj = (cocos2d::GFXTexture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTexture_getHeight : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getHeight();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTexture_getHeight : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTexture_getHeight)

static bool js_gfx_GFXTexture_getBuffer(se::State& s)
{
    cocos2d::GFXTexture* cobj = (cocos2d::GFXTexture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTexture_getBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned char* result = cobj->getBuffer();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTexture_getBuffer : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTexture_getBuffer)

static bool js_gfx_GFXTexture_getWidth(se::State& s)
{
    cocos2d::GFXTexture* cobj = (cocos2d::GFXTexture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTexture_getWidth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getWidth();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTexture_getWidth : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTexture_getWidth)

static bool js_gfx_GFXTexture_getMipLevel(se::State& s)
{
    cocos2d::GFXTexture* cobj = (cocos2d::GFXTexture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTexture_getMipLevel : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getMipLevel();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTexture_getMipLevel : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTexture_getMipLevel)

static bool js_gfx_GFXTexture_getArrayLayer(se::State& s)
{
    cocos2d::GFXTexture* cobj = (cocos2d::GFXTexture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTexture_getArrayLayer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getArrayLayer();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTexture_getArrayLayer : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTexture_getArrayLayer)

static bool js_gfx_GFXTexture_getUsage(se::State& s)
{
    cocos2d::GFXTexture* cobj = (cocos2d::GFXTexture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTexture_getUsage : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getUsage();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTexture_getUsage : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTexture_getUsage)

static bool js_gfx_GFXTexture_initialize(se::State& s)
{
    cocos2d::GFXTexture* cobj = (cocos2d::GFXTexture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTexture_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXTextureInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTexture_initialize : Error processing arguments");
        bool result = cobj->initialize(HolderType<cocos2d::GFXTextureInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTexture_initialize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXTexture_initialize)

static bool js_gfx_GFXTexture_destroy(se::State& s)
{
    cocos2d::GFXTexture* cobj = (cocos2d::GFXTexture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTexture_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXTexture_destroy)

static bool js_gfx_GFXTexture_getSamples(se::State& s)
{
    cocos2d::GFXTexture* cobj = (cocos2d::GFXTexture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTexture_getSamples : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getSamples();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTexture_getSamples : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTexture_getSamples)

static bool js_gfx_GFXTexture_getFormat(se::State& s)
{
    cocos2d::GFXTexture* cobj = (cocos2d::GFXTexture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTexture_getFormat : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getFormat();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTexture_getFormat : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTexture_getFormat)

static bool js_gfx_GFXTexture_getFlags(se::State& s)
{
    cocos2d::GFXTexture* cobj = (cocos2d::GFXTexture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTexture_getFlags : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getFlags();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTexture_getFlags : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTexture_getFlags)

static bool js_gfx_GFXTexture_resize(se::State& s)
{
    cocos2d::GFXTexture* cobj = (cocos2d::GFXTexture*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTexture_resize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<unsigned int, false>::local_type arg0 = {};
        HolderType<unsigned int, false>::local_type arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTexture_resize : Error processing arguments");
        cobj->resize(HolderType<unsigned int, false>::value(arg0), HolderType<unsigned int, false>::value(arg1));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXTexture_resize)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXTexture_finalize)

static bool js_gfx_GFXTexture_constructor(se::State& s) // constructor.c
{
    //#3 cocos2d::GFXTexture: is_skip_construtor True
    se::ScriptEngine::getInstance()->evalString("throw new Error(\"cocos2d::GFXTexture constructor is skipped\")");
    return false;
}
SE_BIND_CTOR(js_gfx_GFXTexture_constructor, __jsb_cocos2d_GFXTexture_class, js_cocos2d_GFXTexture_finalize)



extern se::Object* __jsb_cocos2d_GFXObject_proto;

static bool js_cocos2d_GFXTexture_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXTexture)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXTexture* cobj = (cocos2d::GFXTexture*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXTexture_finalize)

bool js_register_gfx_GFXTexture(se::Object* obj)
{
    auto cls = se::Class::create("GFXTexture", obj, __jsb_cocos2d_GFXObject_proto, _SE(js_gfx_GFXTexture_constructor));

    cls->defineProperty("arrayLayer", _SE(js_gfx_GFXTexture_getArrayLayer), nullptr);
    cls->defineProperty("format", _SE(js_gfx_GFXTexture_getFormat), nullptr);
    cls->defineProperty("buffer", _SE(js_gfx_GFXTexture_getBuffer), nullptr);
    cls->defineProperty("mipLevel", _SE(js_gfx_GFXTexture_getMipLevel), nullptr);
    cls->defineProperty("height", _SE(js_gfx_GFXTexture_getHeight), nullptr);
    cls->defineProperty("width", _SE(js_gfx_GFXTexture_getWidth), nullptr);
    cls->defineProperty("depth", _SE(js_gfx_GFXTexture_getDepth), nullptr);
    cls->defineProperty("flags", _SE(js_gfx_GFXTexture_getFlags), nullptr);
    cls->defineProperty("samples", _SE(js_gfx_GFXTexture_getSamples), nullptr);
    cls->defineProperty("usage", _SE(js_gfx_GFXTexture_getUsage), nullptr);
    cls->defineProperty("type", _SE(js_gfx_GFXTexture_getType), nullptr);
    cls->defineProperty("size", _SE(js_gfx_GFXTexture_getSize), nullptr);
    cls->defineFunction("initialize", _SE(js_gfx_GFXTexture_initialize));
    cls->defineFunction("destroy", _SE(js_gfx_GFXTexture_destroy));
    cls->defineFunction("resize", _SE(js_gfx_GFXTexture_resize));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXTexture_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXTexture>(cls);

    __jsb_cocos2d_GFXTexture_proto = cls->getProto();
    __jsb_cocos2d_GFXTexture_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXTextureView_proto = nullptr;
se::Class* __jsb_cocos2d_GFXTextureView_class = nullptr;

static bool js_gfx_GFXTextureView_getTexture(se::State& s)
{
    cocos2d::GFXTextureView* cobj = (cocos2d::GFXTextureView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureView_getTexture : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXTexture* result = cobj->getTexture();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureView_getTexture : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureView_getTexture)

static bool js_gfx_GFXTextureView_getType(se::State& s)
{
    cocos2d::GFXTextureView* cobj = (cocos2d::GFXTextureView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureView_getType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getType();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureView_getType : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureView_getType)

static bool js_gfx_GFXTextureView_getBaseLevel(se::State& s)
{
    cocos2d::GFXTextureView* cobj = (cocos2d::GFXTextureView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureView_getBaseLevel : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getBaseLevel();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureView_getBaseLevel : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureView_getBaseLevel)

static bool js_gfx_GFXTextureView_initialize(se::State& s)
{
    cocos2d::GFXTextureView* cobj = (cocos2d::GFXTextureView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureView_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXTextureViewInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureView_initialize : Error processing arguments");
        bool result = cobj->initialize(HolderType<cocos2d::GFXTextureViewInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureView_initialize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXTextureView_initialize)

static bool js_gfx_GFXTextureView_destroy(se::State& s)
{
    cocos2d::GFXTextureView* cobj = (cocos2d::GFXTextureView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureView_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXTextureView_destroy)

static bool js_gfx_GFXTextureView_getBaseLayer(se::State& s)
{
    cocos2d::GFXTextureView* cobj = (cocos2d::GFXTextureView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureView_getBaseLayer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getBaseLayer();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureView_getBaseLayer : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureView_getBaseLayer)

static bool js_gfx_GFXTextureView_getDevice(se::State& s)
{
    cocos2d::GFXTextureView* cobj = (cocos2d::GFXTextureView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureView_getDevice : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXDevice* result = cobj->getDevice();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureView_getDevice : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureView_getDevice)

static bool js_gfx_GFXTextureView_getFormat(se::State& s)
{
    cocos2d::GFXTextureView* cobj = (cocos2d::GFXTextureView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureView_getFormat : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getFormat();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureView_getFormat : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureView_getFormat)

static bool js_gfx_GFXTextureView_getLayerCount(se::State& s)
{
    cocos2d::GFXTextureView* cobj = (cocos2d::GFXTextureView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureView_getLayerCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getLayerCount();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureView_getLayerCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureView_getLayerCount)

static bool js_gfx_GFXTextureView_getLevelCount(se::State& s)
{
    cocos2d::GFXTextureView* cobj = (cocos2d::GFXTextureView*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXTextureView_getLevelCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getLevelCount();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXTextureView_getLevelCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXTextureView_getLevelCount)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXTextureView_finalize)

static bool js_gfx_GFXTextureView_constructor(se::State& s) // constructor.c
{
    //#3 cocos2d::GFXTextureView: is_skip_construtor True
    se::ScriptEngine::getInstance()->evalString("throw new Error(\"cocos2d::GFXTextureView constructor is skipped\")");
    return false;
}
SE_BIND_CTOR(js_gfx_GFXTextureView_constructor, __jsb_cocos2d_GFXTextureView_class, js_cocos2d_GFXTextureView_finalize)



extern se::Object* __jsb_cocos2d_GFXObject_proto;

static bool js_cocos2d_GFXTextureView_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXTextureView)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXTextureView* cobj = (cocos2d::GFXTextureView*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXTextureView_finalize)

bool js_register_gfx_GFXTextureView(se::Object* obj)
{
    auto cls = se::Class::create("GFXTextureView", obj, __jsb_cocos2d_GFXObject_proto, _SE(js_gfx_GFXTextureView_constructor));

    cls->defineProperty("baseLevel", _SE(js_gfx_GFXTextureView_getBaseLevel), nullptr);
    cls->defineProperty("format", _SE(js_gfx_GFXTextureView_getFormat), nullptr);
    cls->defineProperty("levelCount", _SE(js_gfx_GFXTextureView_getLevelCount), nullptr);
    cls->defineProperty("texture", _SE(js_gfx_GFXTextureView_getTexture), nullptr);
    cls->defineProperty("layerCount", _SE(js_gfx_GFXTextureView_getLayerCount), nullptr);
    cls->defineProperty("device", _SE(js_gfx_GFXTextureView_getDevice), nullptr);
    cls->defineProperty("baseLayer", _SE(js_gfx_GFXTextureView_getBaseLayer), nullptr);
    cls->defineProperty("type", _SE(js_gfx_GFXTextureView_getType), nullptr);
    cls->defineFunction("initialize", _SE(js_gfx_GFXTextureView_initialize));
    cls->defineFunction("destroy", _SE(js_gfx_GFXTextureView_destroy));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXTextureView_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXTextureView>(cls);

    __jsb_cocos2d_GFXTextureView_proto = cls->getProto();
    __jsb_cocos2d_GFXTextureView_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXSampler_proto = nullptr;
se::Class* __jsb_cocos2d_GFXSampler_class = nullptr;

static bool js_gfx_GFXSampler_getAddressW(se::State& s)
{
    cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSampler_getAddressW : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getAddressW();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXSampler_getAddressW : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXSampler_getAddressW)

static bool js_gfx_GFXSampler_getMaxAnisotropy(se::State& s)
{
    cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSampler_getMaxAnisotropy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getMaxAnisotropy();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXSampler_getMaxAnisotropy : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXSampler_getMaxAnisotropy)

static bool js_gfx_GFXSampler_getMipLODBias(se::State& s)
{
    cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSampler_getMipLODBias : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        float result = cobj->getMipLODBias();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXSampler_getMipLODBias : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXSampler_getMipLODBias)

static bool js_gfx_GFXSampler_getCmpFunc(se::State& s)
{
    cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSampler_getCmpFunc : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getCmpFunc();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXSampler_getCmpFunc : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXSampler_getCmpFunc)

static bool js_gfx_GFXSampler_getBorderColor(se::State& s)
{
    cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSampler_getBorderColor : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::GFXColor& result = cobj->getBorderColor();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXSampler_getBorderColor : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXSampler_getBorderColor)

static bool js_gfx_GFXSampler_getName(se::State& s)
{
    cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSampler_getName : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::String& result = cobj->getName();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXSampler_getName : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXSampler_getName)

static bool js_gfx_GFXSampler_getMipFilter(se::State& s)
{
    cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSampler_getMipFilter : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getMipFilter();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXSampler_getMipFilter : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXSampler_getMipFilter)

static bool js_gfx_GFXSampler_getAddressV(se::State& s)
{
    cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSampler_getAddressV : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getAddressV();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXSampler_getAddressV : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXSampler_getAddressV)

static bool js_gfx_GFXSampler_getAddressU(se::State& s)
{
    cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSampler_getAddressU : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getAddressU();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXSampler_getAddressU : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXSampler_getAddressU)

static bool js_gfx_GFXSampler_getMagFilter(se::State& s)
{
    cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSampler_getMagFilter : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getMagFilter();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXSampler_getMagFilter : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXSampler_getMagFilter)

static bool js_gfx_GFXSampler_initialize(se::State& s)
{
    cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSampler_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXSamplerInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXSampler_initialize : Error processing arguments");
        bool result = cobj->initialize(HolderType<cocos2d::GFXSamplerInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXSampler_initialize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXSampler_initialize)

static bool js_gfx_GFXSampler_destroy(se::State& s)
{
    cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSampler_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXSampler_destroy)

static bool js_gfx_GFXSampler_getDevice(se::State& s)
{
    cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSampler_getDevice : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXDevice* result = cobj->getDevice();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXSampler_getDevice : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXSampler_getDevice)

static bool js_gfx_GFXSampler_getMinLOD(se::State& s)
{
    cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSampler_getMinLOD : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getMinLOD();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXSampler_getMinLOD : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXSampler_getMinLOD)

static bool js_gfx_GFXSampler_getMinFilter(se::State& s)
{
    cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSampler_getMinFilter : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getMinFilter();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXSampler_getMinFilter : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXSampler_getMinFilter)

static bool js_gfx_GFXSampler_getMaxLOD(se::State& s)
{
    cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXSampler_getMaxLOD : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getMaxLOD();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXSampler_getMaxLOD : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXSampler_getMaxLOD)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXSampler_finalize)

static bool js_gfx_GFXSampler_constructor(se::State& s) // constructor.c
{
    //#3 cocos2d::GFXSampler: is_skip_construtor True
    se::ScriptEngine::getInstance()->evalString("throw new Error(\"cocos2d::GFXSampler constructor is skipped\")");
    return false;
}
SE_BIND_CTOR(js_gfx_GFXSampler_constructor, __jsb_cocos2d_GFXSampler_class, js_cocos2d_GFXSampler_finalize)



extern se::Object* __jsb_cocos2d_GFXObject_proto;

static bool js_cocos2d_GFXSampler_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXSampler)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXSampler* cobj = (cocos2d::GFXSampler*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXSampler_finalize)

bool js_register_gfx_GFXSampler(se::Object* obj)
{
    auto cls = se::Class::create("GFXSampler", obj, __jsb_cocos2d_GFXObject_proto, _SE(js_gfx_GFXSampler_constructor));

    cls->defineProperty("borderColor", _SE(js_gfx_GFXSampler_getBorderColor), nullptr);
    cls->defineProperty("mipFilter", _SE(js_gfx_GFXSampler_getMipFilter), nullptr);
    cls->defineProperty("minFilter", _SE(js_gfx_GFXSampler_getMinFilter), nullptr);
    cls->defineProperty("name", _SE(js_gfx_GFXSampler_getName), nullptr);
    cls->defineProperty("maxLOD", _SE(js_gfx_GFXSampler_getMaxLOD), nullptr);
    cls->defineProperty("magFilter", _SE(js_gfx_GFXSampler_getMagFilter), nullptr);
    cls->defineProperty("addressU", _SE(js_gfx_GFXSampler_getAddressU), nullptr);
    cls->defineProperty("addressV", _SE(js_gfx_GFXSampler_getAddressV), nullptr);
    cls->defineProperty("addressW", _SE(js_gfx_GFXSampler_getAddressW), nullptr);
    cls->defineProperty("cmpFunc", _SE(js_gfx_GFXSampler_getCmpFunc), nullptr);
    cls->defineProperty("maxAnisotropy", _SE(js_gfx_GFXSampler_getMaxAnisotropy), nullptr);
    cls->defineProperty("mipLODBias", _SE(js_gfx_GFXSampler_getMipLODBias), nullptr);
    cls->defineProperty("device", _SE(js_gfx_GFXSampler_getDevice), nullptr);
    cls->defineProperty("minLOD", _SE(js_gfx_GFXSampler_getMinLOD), nullptr);
    cls->defineFunction("initialize", _SE(js_gfx_GFXSampler_initialize));
    cls->defineFunction("destroy", _SE(js_gfx_GFXSampler_destroy));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXSampler_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXSampler>(cls);

    __jsb_cocos2d_GFXSampler_proto = cls->getProto();
    __jsb_cocos2d_GFXSampler_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXShader_proto = nullptr;
se::Class* __jsb_cocos2d_GFXShader_class = nullptr;

static bool js_gfx_GFXShader_getStages(se::State& s)
{
    cocos2d::GFXShader* cobj = (cocos2d::GFXShader*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShader_getStages : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cocos2d::GFXShaderStage>& result = cobj->getStages();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXShader_getStages : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXShader_getStages)

static bool js_gfx_GFXShader_getName(se::State& s)
{
    cocos2d::GFXShader* cobj = (cocos2d::GFXShader*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShader_getName : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::String& result = cobj->getName();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXShader_getName : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXShader_getName)

static bool js_gfx_GFXShader_getHash(se::State& s)
{
    cocos2d::GFXShader* cobj = (cocos2d::GFXShader*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShader_getHash : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getHash();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXShader_getHash : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXShader_getHash)

static bool js_gfx_GFXShader_getSamplers(se::State& s)
{
    cocos2d::GFXShader* cobj = (cocos2d::GFXShader*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShader_getSamplers : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cocos2d::GFXUniformSampler>& result = cobj->getSamplers();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXShader_getSamplers : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXShader_getSamplers)

static bool js_gfx_GFXShader_initialize(se::State& s)
{
    cocos2d::GFXShader* cobj = (cocos2d::GFXShader*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShader_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXShaderInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXShader_initialize : Error processing arguments");
        bool result = cobj->initialize(HolderType<cocos2d::GFXShaderInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXShader_initialize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXShader_initialize)

static bool js_gfx_GFXShader_destroy(se::State& s)
{
    cocos2d::GFXShader* cobj = (cocos2d::GFXShader*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShader_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXShader_destroy)

static bool js_gfx_GFXShader_getDevice(se::State& s)
{
    cocos2d::GFXShader* cobj = (cocos2d::GFXShader*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShader_getDevice : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXDevice* result = cobj->getDevice();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXShader_getDevice : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXShader_getDevice)

static bool js_gfx_GFXShader_getBlocks(se::State& s)
{
    cocos2d::GFXShader* cobj = (cocos2d::GFXShader*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXShader_getBlocks : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cocos2d::GFXUniformBlock>& result = cobj->getBlocks();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXShader_getBlocks : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXShader_getBlocks)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXShader_finalize)

static bool js_gfx_GFXShader_constructor(se::State& s) // constructor.c
{
    //#3 cocos2d::GFXShader: is_skip_construtor True
    se::ScriptEngine::getInstance()->evalString("throw new Error(\"cocos2d::GFXShader constructor is skipped\")");
    return false;
}
SE_BIND_CTOR(js_gfx_GFXShader_constructor, __jsb_cocos2d_GFXShader_class, js_cocos2d_GFXShader_finalize)



extern se::Object* __jsb_cocos2d_GFXObject_proto;

static bool js_cocos2d_GFXShader_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXShader)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXShader* cobj = (cocos2d::GFXShader*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXShader_finalize)

bool js_register_gfx_GFXShader(se::Object* obj)
{
    auto cls = se::Class::create("GFXShader", obj, __jsb_cocos2d_GFXObject_proto, _SE(js_gfx_GFXShader_constructor));

    cls->defineProperty("blocks", _SE(js_gfx_GFXShader_getBlocks), nullptr);
    cls->defineProperty("name", _SE(js_gfx_GFXShader_getName), nullptr);
    cls->defineProperty("samplers", _SE(js_gfx_GFXShader_getSamplers), nullptr);
    cls->defineProperty("device", _SE(js_gfx_GFXShader_getDevice), nullptr);
    cls->defineProperty("hash", _SE(js_gfx_GFXShader_getHash), nullptr);
    cls->defineProperty("stages", _SE(js_gfx_GFXShader_getStages), nullptr);
    cls->defineFunction("initialize", _SE(js_gfx_GFXShader_initialize));
    cls->defineFunction("destroy", _SE(js_gfx_GFXShader_destroy));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXShader_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXShader>(cls);

    __jsb_cocos2d_GFXShader_proto = cls->getProto();
    __jsb_cocos2d_GFXShader_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXInputAssembler_proto = nullptr;
se::Class* __jsb_cocos2d_GFXInputAssembler_class = nullptr;

static bool js_gfx_GFXInputAssembler_getFirstIndex(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_getFirstIndex : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getFirstIndex();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_getFirstIndex : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXInputAssembler_getFirstIndex)

static bool js_gfx_GFXInputAssembler_getVertexOffset(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_getVertexOffset : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getVertexOffset();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_getVertexOffset : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXInputAssembler_getVertexOffset)

static bool js_gfx_GFXInputAssembler_getVertexCount(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_getVertexCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getVertexCount();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_getVertexCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXInputAssembler_getVertexCount)

static bool js_gfx_GFXInputAssembler_setIndexCount(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_setIndexCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_setIndexCount : Error processing arguments");
        cobj->setIndexCount(HolderType<unsigned int, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_PROP_SET(js_gfx_GFXInputAssembler_setIndexCount)

static bool js_gfx_GFXInputAssembler_setFirstInstance(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_setFirstInstance : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_setFirstInstance : Error processing arguments");
        cobj->setFirstInstance(HolderType<unsigned int, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_PROP_SET(js_gfx_GFXInputAssembler_setFirstInstance)

static bool js_gfx_GFXInputAssembler_destroy(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXInputAssembler_destroy)

static bool js_gfx_GFXInputAssembler_getDevice(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_getDevice : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXDevice* result = cobj->getDevice();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_getDevice : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXInputAssembler_getDevice)

static bool js_gfx_GFXInputAssembler_setVertexOffset(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_setVertexOffset : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_setVertexOffset : Error processing arguments");
        cobj->setVertexOffset(HolderType<unsigned int, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_PROP_SET(js_gfx_GFXInputAssembler_setVertexOffset)

static bool js_gfx_GFXInputAssembler_getInstanceCount(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_getInstanceCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getInstanceCount();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_getInstanceCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXInputAssembler_getInstanceCount)

static bool js_gfx_GFXInputAssembler_getIndexCount(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_getIndexCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getIndexCount();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_getIndexCount : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXInputAssembler_getIndexCount)

static bool js_gfx_GFXInputAssembler_getIndirectBuffer(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_getIndirectBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXBuffer* result = cobj->getIndirectBuffer();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_getIndirectBuffer : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXInputAssembler_getIndirectBuffer)

static bool js_gfx_GFXInputAssembler_getVertexBuffers(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_getVertexBuffers : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cocos2d::GFXBuffer *>& result = cobj->getVertexBuffers();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_getVertexBuffers : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXInputAssembler_getVertexBuffers)

static bool js_gfx_GFXInputAssembler_initialize(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXInputAssemblerInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_initialize : Error processing arguments");
        bool result = cobj->initialize(HolderType<cocos2d::GFXInputAssemblerInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_initialize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXInputAssembler_initialize)

static bool js_gfx_GFXInputAssembler_setFirstVertex(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_setFirstVertex : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_setFirstVertex : Error processing arguments");
        cobj->setFirstVertex(HolderType<unsigned int, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_PROP_SET(js_gfx_GFXInputAssembler_setFirstVertex)

static bool js_gfx_GFXInputAssembler_getFirstVertex(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_getFirstVertex : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getFirstVertex();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_getFirstVertex : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXInputAssembler_getFirstVertex)

static bool js_gfx_GFXInputAssembler_setVertexCount(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_setVertexCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_setVertexCount : Error processing arguments");
        cobj->setVertexCount(HolderType<unsigned int, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_PROP_SET(js_gfx_GFXInputAssembler_setVertexCount)

static bool js_gfx_GFXInputAssembler_getAttributes(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_getAttributes : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cocos2d::GFXAttribute>& result = cobj->getAttributes();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_getAttributes : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXInputAssembler_getAttributes)

static bool js_gfx_GFXInputAssembler_getIndexBuffer(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_getIndexBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXBuffer* result = cobj->getIndexBuffer();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_getIndexBuffer : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXInputAssembler_getIndexBuffer)

static bool js_gfx_GFXInputAssembler_setFirstIndex(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_setFirstIndex : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_setFirstIndex : Error processing arguments");
        cobj->setFirstIndex(HolderType<unsigned int, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_PROP_SET(js_gfx_GFXInputAssembler_setFirstIndex)

static bool js_gfx_GFXInputAssembler_setInstanceCount(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_setInstanceCount : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<unsigned int, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_setInstanceCount : Error processing arguments");
        cobj->setInstanceCount(HolderType<unsigned int, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_PROP_SET(js_gfx_GFXInputAssembler_setInstanceCount)

static bool js_gfx_GFXInputAssembler_getFirstInstance(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_getFirstInstance : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getFirstInstance();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXInputAssembler_getFirstInstance : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXInputAssembler_getFirstInstance)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXInputAssembler_finalize)

static bool js_gfx_GFXInputAssembler_constructor(se::State& s) // constructor.c
{
    //#3 cocos2d::GFXInputAssembler: is_skip_construtor True
    se::ScriptEngine::getInstance()->evalString("throw new Error(\"cocos2d::GFXInputAssembler constructor is skipped\")");
    return false;
}
SE_BIND_CTOR(js_gfx_GFXInputAssembler_constructor, __jsb_cocos2d_GFXInputAssembler_class, js_cocos2d_GFXInputAssembler_finalize)



extern se::Object* __jsb_cocos2d_GFXObject_proto;

static bool js_cocos2d_GFXInputAssembler_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXInputAssembler)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXInputAssembler_finalize)

bool js_register_gfx_GFXInputAssembler(se::Object* obj)
{
    auto cls = se::Class::create("GFXInputAssembler", obj, __jsb_cocos2d_GFXObject_proto, _SE(js_gfx_GFXInputAssembler_constructor));

    cls->defineProperty("instanceCount", _SE(js_gfx_GFXInputAssembler_getInstanceCount), _SE(js_gfx_GFXInputAssembler_setInstanceCount));
    cls->defineProperty("vertexBuffers", _SE(js_gfx_GFXInputAssembler_getVertexBuffers), nullptr);
    cls->defineProperty("firstInstance", _SE(js_gfx_GFXInputAssembler_getFirstInstance), _SE(js_gfx_GFXInputAssembler_setFirstInstance));
    cls->defineProperty("vertexOffset", _SE(js_gfx_GFXInputAssembler_getVertexOffset), _SE(js_gfx_GFXInputAssembler_setVertexOffset));
    cls->defineProperty("vertexCount", _SE(js_gfx_GFXInputAssembler_getVertexCount), _SE(js_gfx_GFXInputAssembler_setVertexCount));
    cls->defineProperty("indexBuffer", _SE(js_gfx_GFXInputAssembler_getIndexBuffer), nullptr);
    cls->defineProperty("device", _SE(js_gfx_GFXInputAssembler_getDevice), nullptr);
    cls->defineProperty("attributes", _SE(js_gfx_GFXInputAssembler_getAttributes), nullptr);
    cls->defineProperty("indexCount", _SE(js_gfx_GFXInputAssembler_getIndexCount), _SE(js_gfx_GFXInputAssembler_setIndexCount));
    cls->defineProperty("firstIndex", _SE(js_gfx_GFXInputAssembler_getFirstIndex), _SE(js_gfx_GFXInputAssembler_setFirstIndex));
    cls->defineProperty("indirectBuffer", _SE(js_gfx_GFXInputAssembler_getIndirectBuffer), nullptr);
    cls->defineProperty("firstVertex", _SE(js_gfx_GFXInputAssembler_getFirstVertex), _SE(js_gfx_GFXInputAssembler_setFirstVertex));
    cls->defineFunction("destroy", _SE(js_gfx_GFXInputAssembler_destroy));
    cls->defineFunction("initialize", _SE(js_gfx_GFXInputAssembler_initialize));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXInputAssembler_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXInputAssembler>(cls);

    __jsb_cocos2d_GFXInputAssembler_proto = cls->getProto();
    __jsb_cocos2d_GFXInputAssembler_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXRenderPass_proto = nullptr;
se::Class* __jsb_cocos2d_GFXRenderPass_class = nullptr;

static bool js_gfx_GFXRenderPass_getColorAttachments(se::State& s)
{
    cocos2d::GFXRenderPass* cobj = (cocos2d::GFXRenderPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRenderPass_getColorAttachments : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cocos2d::GFXColorAttachment>& result = cobj->getColorAttachments();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXRenderPass_getColorAttachments : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXRenderPass_getColorAttachments)

static bool js_gfx_GFXRenderPass_getSubPasses(se::State& s)
{
    cocos2d::GFXRenderPass* cobj = (cocos2d::GFXRenderPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRenderPass_getSubPasses : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cocos2d::GFXSubPass>& result = cobj->getSubPasses();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXRenderPass_getSubPasses : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXRenderPass_getSubPasses)

static bool js_gfx_GFXRenderPass_initialize(se::State& s)
{
    cocos2d::GFXRenderPass* cobj = (cocos2d::GFXRenderPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRenderPass_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXRenderPassInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXRenderPass_initialize : Error processing arguments");
        bool result = cobj->initialize(HolderType<cocos2d::GFXRenderPassInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXRenderPass_initialize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXRenderPass_initialize)

static bool js_gfx_GFXRenderPass_destroy(se::State& s)
{
    cocos2d::GFXRenderPass* cobj = (cocos2d::GFXRenderPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRenderPass_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXRenderPass_destroy)

static bool js_gfx_GFXRenderPass_getDevice(se::State& s)
{
    cocos2d::GFXRenderPass* cobj = (cocos2d::GFXRenderPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRenderPass_getDevice : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXDevice* result = cobj->getDevice();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXRenderPass_getDevice : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXRenderPass_getDevice)

static bool js_gfx_GFXRenderPass_getDepthStencilAttachment(se::State& s)
{
    cocos2d::GFXRenderPass* cobj = (cocos2d::GFXRenderPass*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXRenderPass_getDepthStencilAttachment : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::GFXDepthStencilAttachment& result = cobj->getDepthStencilAttachment();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXRenderPass_getDepthStencilAttachment : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXRenderPass_getDepthStencilAttachment)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXRenderPass_finalize)

static bool js_gfx_GFXRenderPass_constructor(se::State& s) // constructor.c
{
    //#3 cocos2d::GFXRenderPass: is_skip_construtor True
    se::ScriptEngine::getInstance()->evalString("throw new Error(\"cocos2d::GFXRenderPass constructor is skipped\")");
    return false;
}
SE_BIND_CTOR(js_gfx_GFXRenderPass_constructor, __jsb_cocos2d_GFXRenderPass_class, js_cocos2d_GFXRenderPass_finalize)



extern se::Object* __jsb_cocos2d_GFXObject_proto;

static bool js_cocos2d_GFXRenderPass_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXRenderPass)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXRenderPass* cobj = (cocos2d::GFXRenderPass*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXRenderPass_finalize)

bool js_register_gfx_GFXRenderPass(se::Object* obj)
{
    auto cls = se::Class::create("GFXRenderPass", obj, __jsb_cocos2d_GFXObject_proto, _SE(js_gfx_GFXRenderPass_constructor));

    cls->defineProperty("device", _SE(js_gfx_GFXRenderPass_getDevice), nullptr);
    cls->defineProperty("colorAttachments", _SE(js_gfx_GFXRenderPass_getColorAttachments), nullptr);
    cls->defineProperty("depthStencilAttachment", _SE(js_gfx_GFXRenderPass_getDepthStencilAttachment), nullptr);
    cls->defineProperty("subPasses", _SE(js_gfx_GFXRenderPass_getSubPasses), nullptr);
    cls->defineFunction("initialize", _SE(js_gfx_GFXRenderPass_initialize));
    cls->defineFunction("destroy", _SE(js_gfx_GFXRenderPass_destroy));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXRenderPass_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXRenderPass>(cls);

    __jsb_cocos2d_GFXRenderPass_proto = cls->getProto();
    __jsb_cocos2d_GFXRenderPass_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXFramebuffer_proto = nullptr;
se::Class* __jsb_cocos2d_GFXFramebuffer_class = nullptr;

static bool js_gfx_GFXFramebuffer_getDepthStencilView(se::State& s)
{
    cocos2d::GFXFramebuffer* cobj = (cocos2d::GFXFramebuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFramebuffer_getDepthStencilView : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXTextureView* result = cobj->getDepthStencilView();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXFramebuffer_getDepthStencilView : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXFramebuffer_getDepthStencilView)

static bool js_gfx_GFXFramebuffer_isOffscreen(se::State& s)
{
    cocos2d::GFXFramebuffer* cobj = (cocos2d::GFXFramebuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFramebuffer_isOffscreen : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        bool result = cobj->isOffscreen();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXFramebuffer_isOffscreen : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXFramebuffer_isOffscreen)

static bool js_gfx_GFXFramebuffer_getColorViews(se::State& s)
{
    cocos2d::GFXFramebuffer* cobj = (cocos2d::GFXFramebuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFramebuffer_getColorViews : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cocos2d::GFXTextureView *>& result = cobj->getColorViews();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXFramebuffer_getColorViews : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXFramebuffer_getColorViews)

static bool js_gfx_GFXFramebuffer_initialize(se::State& s)
{
    cocos2d::GFXFramebuffer* cobj = (cocos2d::GFXFramebuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFramebuffer_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXFramebufferInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXFramebuffer_initialize : Error processing arguments");
        bool result = cobj->initialize(HolderType<cocos2d::GFXFramebufferInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXFramebuffer_initialize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXFramebuffer_initialize)

static bool js_gfx_GFXFramebuffer_destroy(se::State& s)
{
    cocos2d::GFXFramebuffer* cobj = (cocos2d::GFXFramebuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFramebuffer_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXFramebuffer_destroy)

static bool js_gfx_GFXFramebuffer_getRenderPass(se::State& s)
{
    cocos2d::GFXFramebuffer* cobj = (cocos2d::GFXFramebuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFramebuffer_getRenderPass : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXRenderPass* result = cobj->getRenderPass();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXFramebuffer_getRenderPass : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXFramebuffer_getRenderPass)

static bool js_gfx_GFXFramebuffer_getDevice(se::State& s)
{
    cocos2d::GFXFramebuffer* cobj = (cocos2d::GFXFramebuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXFramebuffer_getDevice : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXDevice* result = cobj->getDevice();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXFramebuffer_getDevice : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXFramebuffer_getDevice)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXFramebuffer_finalize)

static bool js_gfx_GFXFramebuffer_constructor(se::State& s) // constructor.c
{
    //#3 cocos2d::GFXFramebuffer: is_skip_construtor True
    se::ScriptEngine::getInstance()->evalString("throw new Error(\"cocos2d::GFXFramebuffer constructor is skipped\")");
    return false;
}
SE_BIND_CTOR(js_gfx_GFXFramebuffer_constructor, __jsb_cocos2d_GFXFramebuffer_class, js_cocos2d_GFXFramebuffer_finalize)



extern se::Object* __jsb_cocos2d_GFXObject_proto;

static bool js_cocos2d_GFXFramebuffer_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXFramebuffer)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXFramebuffer* cobj = (cocos2d::GFXFramebuffer*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXFramebuffer_finalize)

bool js_register_gfx_GFXFramebuffer(se::Object* obj)
{
    auto cls = se::Class::create("GFXFramebuffer", obj, __jsb_cocos2d_GFXObject_proto, _SE(js_gfx_GFXFramebuffer_constructor));

    cls->defineFunction("getDepthStencilView", _SE(js_gfx_GFXFramebuffer_getDepthStencilView));
    cls->defineFunction("isOffscreen", _SE(js_gfx_GFXFramebuffer_isOffscreen));
    cls->defineFunction("getColorViews", _SE(js_gfx_GFXFramebuffer_getColorViews));
    cls->defineFunction("initialize", _SE(js_gfx_GFXFramebuffer_initialize));
    cls->defineFunction("destroy", _SE(js_gfx_GFXFramebuffer_destroy));
    cls->defineFunction("getRenderPass", _SE(js_gfx_GFXFramebuffer_getRenderPass));
    cls->defineFunction("getDevice", _SE(js_gfx_GFXFramebuffer_getDevice));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXFramebuffer_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXFramebuffer>(cls);

    __jsb_cocos2d_GFXFramebuffer_proto = cls->getProto();
    __jsb_cocos2d_GFXFramebuffer_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXBindingLayout_proto = nullptr;
se::Class* __jsb_cocos2d_GFXBindingLayout_class = nullptr;

static bool js_gfx_GFXBindingLayout_bindTextureView(se::State& s)
{
    cocos2d::GFXBindingLayout* cobj = (cocos2d::GFXBindingLayout*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingLayout_bindTextureView : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<unsigned int, false>::local_type arg0 = {};
        HolderType<cocos2d::GFXTextureView*, false>::local_type arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBindingLayout_bindTextureView : Error processing arguments");
        cobj->bindTextureView(HolderType<unsigned int, false>::value(arg0), HolderType<cocos2d::GFXTextureView*, false>::value(arg1));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXBindingLayout_bindTextureView)

static bool js_gfx_GFXBindingLayout_bindBuffer(se::State& s)
{
    cocos2d::GFXBindingLayout* cobj = (cocos2d::GFXBindingLayout*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingLayout_bindBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<unsigned int, false>::local_type arg0 = {};
        HolderType<cocos2d::GFXBuffer*, false>::local_type arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBindingLayout_bindBuffer : Error processing arguments");
        cobj->bindBuffer(HolderType<unsigned int, false>::value(arg0), HolderType<cocos2d::GFXBuffer*, false>::value(arg1));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXBindingLayout_bindBuffer)

static bool js_gfx_GFXBindingLayout_getBindingUnits(se::State& s)
{
    cocos2d::GFXBindingLayout* cobj = (cocos2d::GFXBindingLayout*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingLayout_getBindingUnits : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cocos2d::GFXBindingUnit>& result = cobj->getBindingUnits();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBindingLayout_getBindingUnits : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXBindingLayout_getBindingUnits)

static bool js_gfx_GFXBindingLayout_bindSampler(se::State& s)
{
    cocos2d::GFXBindingLayout* cobj = (cocos2d::GFXBindingLayout*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingLayout_bindSampler : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<unsigned int, false>::local_type arg0 = {};
        HolderType<cocos2d::GFXSampler*, false>::local_type arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBindingLayout_bindSampler : Error processing arguments");
        cobj->bindSampler(HolderType<unsigned int, false>::value(arg0), HolderType<cocos2d::GFXSampler*, false>::value(arg1));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXBindingLayout_bindSampler)

static bool js_gfx_GFXBindingLayout_update(se::State& s)
{
    cocos2d::GFXBindingLayout* cobj = (cocos2d::GFXBindingLayout*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingLayout_update : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->update();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXBindingLayout_update)

static bool js_gfx_GFXBindingLayout_initialize(se::State& s)
{
    cocos2d::GFXBindingLayout* cobj = (cocos2d::GFXBindingLayout*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingLayout_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXBindingLayoutInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBindingLayout_initialize : Error processing arguments");
        bool result = cobj->initialize(HolderType<cocos2d::GFXBindingLayoutInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBindingLayout_initialize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXBindingLayout_initialize)

static bool js_gfx_GFXBindingLayout_destroy(se::State& s)
{
    cocos2d::GFXBindingLayout* cobj = (cocos2d::GFXBindingLayout*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingLayout_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXBindingLayout_destroy)

static bool js_gfx_GFXBindingLayout_getDevice(se::State& s)
{
    cocos2d::GFXBindingLayout* cobj = (cocos2d::GFXBindingLayout*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBindingLayout_getDevice : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXDevice* result = cobj->getDevice();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBindingLayout_getDevice : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXBindingLayout_getDevice)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXBindingLayout_finalize)

static bool js_gfx_GFXBindingLayout_constructor(se::State& s) // constructor.c
{
    //#3 cocos2d::GFXBindingLayout: is_skip_construtor True
    se::ScriptEngine::getInstance()->evalString("throw new Error(\"cocos2d::GFXBindingLayout constructor is skipped\")");
    return false;
}
SE_BIND_CTOR(js_gfx_GFXBindingLayout_constructor, __jsb_cocos2d_GFXBindingLayout_class, js_cocos2d_GFXBindingLayout_finalize)



extern se::Object* __jsb_cocos2d_GFXObject_proto;

static bool js_cocos2d_GFXBindingLayout_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXBindingLayout)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXBindingLayout* cobj = (cocos2d::GFXBindingLayout*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXBindingLayout_finalize)

bool js_register_gfx_GFXBindingLayout(se::Object* obj)
{
    auto cls = se::Class::create("GFXBindingLayout", obj, __jsb_cocos2d_GFXObject_proto, _SE(js_gfx_GFXBindingLayout_constructor));

    cls->defineProperty("device", _SE(js_gfx_GFXBindingLayout_getDevice), nullptr);
    cls->defineProperty("bindingUnits", _SE(js_gfx_GFXBindingLayout_getBindingUnits), nullptr);
    cls->defineFunction("bindTextureView", _SE(js_gfx_GFXBindingLayout_bindTextureView));
    cls->defineFunction("bindBuffer", _SE(js_gfx_GFXBindingLayout_bindBuffer));
    cls->defineFunction("bindSampler", _SE(js_gfx_GFXBindingLayout_bindSampler));
    cls->defineFunction("update", _SE(js_gfx_GFXBindingLayout_update));
    cls->defineFunction("initialize", _SE(js_gfx_GFXBindingLayout_initialize));
    cls->defineFunction("destroy", _SE(js_gfx_GFXBindingLayout_destroy));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXBindingLayout_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXBindingLayout>(cls);

    __jsb_cocos2d_GFXBindingLayout_proto = cls->getProto();
    __jsb_cocos2d_GFXBindingLayout_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXPipelineLayout_proto = nullptr;
se::Class* __jsb_cocos2d_GFXPipelineLayout_class = nullptr;

static bool js_gfx_GFXPipelineLayout_getLayouts(se::State& s)
{
    cocos2d::GFXPipelineLayout* cobj = (cocos2d::GFXPipelineLayout*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineLayout_getLayouts : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cocos2d::GFXBindingLayout *>& result = cobj->getLayouts();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineLayout_getLayouts : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineLayout_getLayouts)

static bool js_gfx_GFXPipelineLayout_initialize(se::State& s)
{
    cocos2d::GFXPipelineLayout* cobj = (cocos2d::GFXPipelineLayout*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineLayout_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXPipelineLayoutInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineLayout_initialize : Error processing arguments");
        bool result = cobj->initialize(HolderType<cocos2d::GFXPipelineLayoutInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineLayout_initialize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXPipelineLayout_initialize)

static bool js_gfx_GFXPipelineLayout_destroy(se::State& s)
{
    cocos2d::GFXPipelineLayout* cobj = (cocos2d::GFXPipelineLayout*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineLayout_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXPipelineLayout_destroy)

static bool js_gfx_GFXPipelineLayout_getDevice(se::State& s)
{
    cocos2d::GFXPipelineLayout* cobj = (cocos2d::GFXPipelineLayout*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineLayout_getDevice : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXDevice* result = cobj->getDevice();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineLayout_getDevice : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineLayout_getDevice)

static bool js_gfx_GFXPipelineLayout_getPushConstantsRanges(se::State& s)
{
    cocos2d::GFXPipelineLayout* cobj = (cocos2d::GFXPipelineLayout*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineLayout_getPushConstantsRanges : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cocos2d::GFXPushConstantRange>& result = cobj->getPushConstantsRanges();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineLayout_getPushConstantsRanges : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXPipelineLayout_getPushConstantsRanges)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXPipelineLayout_finalize)

static bool js_gfx_GFXPipelineLayout_constructor(se::State& s) // constructor.c
{
    //#3 cocos2d::GFXPipelineLayout: is_skip_construtor True
    se::ScriptEngine::getInstance()->evalString("throw new Error(\"cocos2d::GFXPipelineLayout constructor is skipped\")");
    return false;
}
SE_BIND_CTOR(js_gfx_GFXPipelineLayout_constructor, __jsb_cocos2d_GFXPipelineLayout_class, js_cocos2d_GFXPipelineLayout_finalize)



extern se::Object* __jsb_cocos2d_GFXObject_proto;

static bool js_cocos2d_GFXPipelineLayout_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXPipelineLayout)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXPipelineLayout* cobj = (cocos2d::GFXPipelineLayout*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXPipelineLayout_finalize)

bool js_register_gfx_GFXPipelineLayout(se::Object* obj)
{
    auto cls = se::Class::create("GFXPipelineLayout", obj, __jsb_cocos2d_GFXObject_proto, _SE(js_gfx_GFXPipelineLayout_constructor));

    cls->defineProperty("device", _SE(js_gfx_GFXPipelineLayout_getDevice), nullptr);
    cls->defineProperty("layouts", _SE(js_gfx_GFXPipelineLayout_getLayouts), nullptr);
    cls->defineFunction("initialize", _SE(js_gfx_GFXPipelineLayout_initialize));
    cls->defineFunction("destroy", _SE(js_gfx_GFXPipelineLayout_destroy));
    cls->defineFunction("getPushConstantsRanges", _SE(js_gfx_GFXPipelineLayout_getPushConstantsRanges));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXPipelineLayout_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXPipelineLayout>(cls);

    __jsb_cocos2d_GFXPipelineLayout_proto = cls->getProto();
    __jsb_cocos2d_GFXPipelineLayout_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXPipelineState_proto = nullptr;
se::Class* __jsb_cocos2d_GFXPipelineState_class = nullptr;

static bool js_gfx_GFXPipelineState_getRasterizerState(se::State& s)
{
    cocos2d::GFXPipelineState* cobj = (cocos2d::GFXPipelineState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineState_getRasterizerState : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::GFXRasterizerState& result = cobj->getRasterizerState();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineState_getRasterizerState : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineState_getRasterizerState)

static bool js_gfx_GFXPipelineState_getShader(se::State& s)
{
    cocos2d::GFXPipelineState* cobj = (cocos2d::GFXPipelineState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineState_getShader : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXShader* result = cobj->getShader();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineState_getShader : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineState_getShader)

static bool js_gfx_GFXPipelineState_getInputState(se::State& s)
{
    cocos2d::GFXPipelineState* cobj = (cocos2d::GFXPipelineState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineState_getInputState : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::GFXInputState& result = cobj->getInputState();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineState_getInputState : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineState_getInputState)

static bool js_gfx_GFXPipelineState_getPrimitive(se::State& s)
{
    cocos2d::GFXPipelineState* cobj = (cocos2d::GFXPipelineState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineState_getPrimitive : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getPrimitive();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineState_getPrimitive : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineState_getPrimitive)

static bool js_gfx_GFXPipelineState_getDepthStencilState(se::State& s)
{
    cocos2d::GFXPipelineState* cobj = (cocos2d::GFXPipelineState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineState_getDepthStencilState : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::GFXDepthStencilState& result = cobj->getDepthStencilState();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineState_getDepthStencilState : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineState_getDepthStencilState)

static bool js_gfx_GFXPipelineState_getBlendState(se::State& s)
{
    cocos2d::GFXPipelineState* cobj = (cocos2d::GFXPipelineState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineState_getBlendState : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::GFXBlendState& result = cobj->getBlendState();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineState_getBlendState : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineState_getBlendState)

static bool js_gfx_GFXPipelineState_getPipelineLayout(se::State& s)
{
    cocos2d::GFXPipelineState* cobj = (cocos2d::GFXPipelineState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineState_getPipelineLayout : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::GFXPipelineLayout* result = cobj->getPipelineLayout();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineState_getPipelineLayout : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineState_getPipelineLayout)

static bool js_gfx_GFXPipelineState_initialize(se::State& s)
{
    cocos2d::GFXPipelineState* cobj = (cocos2d::GFXPipelineState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineState_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXPipelineStateInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineState_initialize : Error processing arguments");
        bool result = cobj->initialize(HolderType<cocos2d::GFXPipelineStateInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineState_initialize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXPipelineState_initialize)

static bool js_gfx_GFXPipelineState_destroy(se::State& s)
{
    cocos2d::GFXPipelineState* cobj = (cocos2d::GFXPipelineState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineState_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXPipelineState_destroy)

static bool js_gfx_GFXPipelineState_getRenderPass(se::State& s)
{
    cocos2d::GFXPipelineState* cobj = (cocos2d::GFXPipelineState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineState_getRenderPass : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const cocos2d::GFXRenderPass* result = cobj->getRenderPass();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineState_getRenderPass : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineState_getRenderPass)

static bool js_gfx_GFXPipelineState_getDevice(se::State& s)
{
    cocos2d::GFXPipelineState* cobj = (cocos2d::GFXPipelineState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineState_getDevice : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXDevice* result = cobj->getDevice();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineState_getDevice : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXPipelineState_getDevice)

static bool js_gfx_GFXPipelineState_getDynamicStates(se::State& s)
{
    cocos2d::GFXPipelineState* cobj = (cocos2d::GFXPipelineState*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXPipelineState_getDynamicStates : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        const std::vector<cocos2d::GFXDynamicState>& result = cobj->getDynamicStates();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXPipelineState_getDynamicStates : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXPipelineState_getDynamicStates)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXPipelineState_finalize)

static bool js_gfx_GFXPipelineState_constructor(se::State& s) // constructor.c
{
    //#3 cocos2d::GFXPipelineState: is_skip_construtor True
    se::ScriptEngine::getInstance()->evalString("throw new Error(\"cocos2d::GFXPipelineState constructor is skipped\")");
    return false;
}
SE_BIND_CTOR(js_gfx_GFXPipelineState_constructor, __jsb_cocos2d_GFXPipelineState_class, js_cocos2d_GFXPipelineState_finalize)



extern se::Object* __jsb_cocos2d_GFXObject_proto;

static bool js_cocos2d_GFXPipelineState_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXPipelineState)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXPipelineState* cobj = (cocos2d::GFXPipelineState*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXPipelineState_finalize)

bool js_register_gfx_GFXPipelineState(se::Object* obj)
{
    auto cls = se::Class::create("GFXPipelineState", obj, __jsb_cocos2d_GFXObject_proto, _SE(js_gfx_GFXPipelineState_constructor));

    cls->defineProperty("primitive", _SE(js_gfx_GFXPipelineState_getPrimitive), nullptr);
    cls->defineProperty("rasterizerState", _SE(js_gfx_GFXPipelineState_getRasterizerState), nullptr);
    cls->defineProperty("shader", _SE(js_gfx_GFXPipelineState_getShader), nullptr);
    cls->defineProperty("blendState", _SE(js_gfx_GFXPipelineState_getBlendState), nullptr);
    cls->defineProperty("pipelineLayout", _SE(js_gfx_GFXPipelineState_getPipelineLayout), nullptr);
    cls->defineProperty("renderPass", _SE(js_gfx_GFXPipelineState_getRenderPass), nullptr);
    cls->defineProperty("device", _SE(js_gfx_GFXPipelineState_getDevice), nullptr);
    cls->defineProperty("inputState", _SE(js_gfx_GFXPipelineState_getInputState), nullptr);
    cls->defineProperty("depthStencilState", _SE(js_gfx_GFXPipelineState_getDepthStencilState), nullptr);
    cls->defineFunction("initialize", _SE(js_gfx_GFXPipelineState_initialize));
    cls->defineFunction("destroy", _SE(js_gfx_GFXPipelineState_destroy));
    cls->defineFunction("getDynamicStates", _SE(js_gfx_GFXPipelineState_getDynamicStates));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXPipelineState_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXPipelineState>(cls);

    __jsb_cocos2d_GFXPipelineState_proto = cls->getProto();
    __jsb_cocos2d_GFXPipelineState_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXCommandAllocator_proto = nullptr;
se::Class* __jsb_cocos2d_GFXCommandAllocator_class = nullptr;

static bool js_gfx_GFXCommandAllocator_destroy(se::State& s)
{
    cocos2d::GFXCommandAllocator* cobj = (cocos2d::GFXCommandAllocator*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandAllocator_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandAllocator_destroy)

static bool js_gfx_GFXCommandAllocator_getDevice(se::State& s)
{
    cocos2d::GFXCommandAllocator* cobj = (cocos2d::GFXCommandAllocator*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandAllocator_getDevice : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXDevice* result = cobj->getDevice();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandAllocator_getDevice : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandAllocator_getDevice)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXCommandAllocator_finalize)

static bool js_gfx_GFXCommandAllocator_constructor(se::State& s) // constructor.c
{
    //#3 cocos2d::GFXCommandAllocator: is_skip_construtor True
    se::ScriptEngine::getInstance()->evalString("throw new Error(\"cocos2d::GFXCommandAllocator constructor is skipped\")");
    return false;
}
SE_BIND_CTOR(js_gfx_GFXCommandAllocator_constructor, __jsb_cocos2d_GFXCommandAllocator_class, js_cocos2d_GFXCommandAllocator_finalize)



extern se::Object* __jsb_cocos2d_GFXObject_proto;

static bool js_cocos2d_GFXCommandAllocator_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXCommandAllocator)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXCommandAllocator* cobj = (cocos2d::GFXCommandAllocator*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXCommandAllocator_finalize)

bool js_register_gfx_GFXCommandAllocator(se::Object* obj)
{
    auto cls = se::Class::create("GFXCommandAllocator", obj, __jsb_cocos2d_GFXObject_proto, _SE(js_gfx_GFXCommandAllocator_constructor));

    cls->defineFunction("destroy", _SE(js_gfx_GFXCommandAllocator_destroy));
    cls->defineFunction("getDevice", _SE(js_gfx_GFXCommandAllocator_getDevice));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXCommandAllocator_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXCommandAllocator>(cls);

    __jsb_cocos2d_GFXCommandAllocator_proto = cls->getProto();
    __jsb_cocos2d_GFXCommandAllocator_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXCommandBuffer_proto = nullptr;
se::Class* __jsb_cocos2d_GFXCommandBuffer_class = nullptr;

static bool js_gfx_GFXCommandBuffer_draw(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_draw : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXInputAssembler*, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_draw : Error processing arguments");
        cobj->draw(HolderType<cocos2d::GFXInputAssembler*, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_draw)

static bool js_gfx_GFXCommandBuffer_setBlendConstants(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_setBlendConstants : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXColor, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_setBlendConstants : Error processing arguments");
        cobj->setBlendConstants(HolderType<cocos2d::GFXColor, true>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_setBlendConstants)

static bool js_gfx_GFXCommandBuffer_setDepthBound(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_setDepthBound : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<float, false>::local_type arg0 = {};
        HolderType<float, false>::local_type arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_setDepthBound : Error processing arguments");
        cobj->setDepthBound(HolderType<float, false>::value(arg0), HolderType<float, false>::value(arg1));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_setDepthBound)

static bool js_gfx_GFXCommandBuffer_getAllocator(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_getAllocator : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXCommandAllocator* result = cobj->getAllocator();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_getAllocator : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXCommandBuffer_getAllocator)

static bool js_gfx_GFXCommandBuffer_copyBufferToTexture(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_copyBufferToTexture : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 4) {
        HolderType<cocos2d::GFXBuffer*, false>::local_type arg0 = {};
        HolderType<cocos2d::GFXTexture*, false>::local_type arg1 = {};
        HolderType<cocos2d::GFXTextureLayout, false>::local_type arg2 = {};
        HolderType<std::vector<cocos2d::GFXBufferTextureCopy>, true>::local_type arg3 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
        ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
        ok &= sevalue_to_native(args[3], &arg3); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_copyBufferToTexture : Error processing arguments");
        cobj->copyBufferToTexture(HolderType<cocos2d::GFXBuffer*, false>::value(arg0), HolderType<cocos2d::GFXTexture*, false>::value(arg1), HolderType<cocos2d::GFXTextureLayout, false>::value(arg2), HolderType<std::vector<cocos2d::GFXBufferTextureCopy>, true>::value(arg3));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_copyBufferToTexture)

static bool js_gfx_GFXCommandBuffer_setLineWidth(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_setLineWidth : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<float, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_setLineWidth : Error processing arguments");
        cobj->setLineWidth(HolderType<float, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_setLineWidth)

static bool js_gfx_GFXCommandBuffer_updateBuffer(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_updateBuffer : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<cocos2d::GFXBuffer*, false>::local_type arg0 = {};
        HolderType<void*, false>::local_type arg1 = {};
        HolderType<unsigned int, false>::local_type arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
        ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_updateBuffer : Error processing arguments");
        cobj->updateBuffer(HolderType<cocos2d::GFXBuffer*, false>::value(arg0), HolderType<void*, false>::value(arg1), HolderType<unsigned int, false>::value(arg2));
        return true;
    }
    if (argc == 4) {
        HolderType<cocos2d::GFXBuffer*, false>::local_type arg0 = {};
        HolderType<void*, false>::local_type arg1 = {};
        HolderType<unsigned int, false>::local_type arg2 = {};
        HolderType<unsigned int, false>::local_type arg3 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
        ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
        ok &= sevalue_to_native(args[3], &arg3); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_updateBuffer : Error processing arguments");
        cobj->updateBuffer(HolderType<cocos2d::GFXBuffer*, false>::value(arg0), HolderType<void*, false>::value(arg1), HolderType<unsigned int, false>::value(arg2), HolderType<unsigned int, false>::value(arg3));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 4);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_updateBuffer)

static bool js_gfx_GFXCommandBuffer_end(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_end : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->end();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_end)

static bool js_gfx_GFXCommandBuffer_setStencilWriteMask(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_setStencilWriteMask : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        HolderType<cocos2d::GFXStencilFace, false>::local_type arg0 = {};
        HolderType<unsigned int, false>::local_type arg1 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_setStencilWriteMask : Error processing arguments");
        cobj->setStencilWriteMask(HolderType<cocos2d::GFXStencilFace, false>::value(arg0), HolderType<unsigned int, false>::value(arg1));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_setStencilWriteMask)

static bool js_gfx_GFXCommandBuffer_getNumInstances(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_getNumInstances : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getNumInstances();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_getNumInstances : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXCommandBuffer_getNumInstances)

static bool js_gfx_GFXCommandBuffer_setStencilCompareMask(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_setStencilCompareMask : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<cocos2d::GFXStencilFace, false>::local_type arg0 = {};
        HolderType<int, false>::local_type arg1 = {};
        HolderType<unsigned int, false>::local_type arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
        ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_setStencilCompareMask : Error processing arguments");
        cobj->setStencilCompareMask(HolderType<cocos2d::GFXStencilFace, false>::value(arg0), HolderType<int, false>::value(arg1), HolderType<unsigned int, false>::value(arg2));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_setStencilCompareMask)

static bool js_gfx_GFXCommandBuffer_bindInputAssembler(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_bindInputAssembler : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXInputAssembler*, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_bindInputAssembler : Error processing arguments");
        cobj->bindInputAssembler(HolderType<cocos2d::GFXInputAssembler*, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_bindInputAssembler)

static bool js_gfx_GFXCommandBuffer_bindPipelineState(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_bindPipelineState : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXPipelineState*, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_bindPipelineState : Error processing arguments");
        cobj->bindPipelineState(HolderType<cocos2d::GFXPipelineState*, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_bindPipelineState)

static bool js_gfx_GFXCommandBuffer_destroy(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_destroy)

static bool js_gfx_GFXCommandBuffer_getDevice(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_getDevice : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXDevice* result = cobj->getDevice();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_getDevice : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXCommandBuffer_getDevice)

static bool js_gfx_GFXCommandBuffer_getNumTris(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_getNumTris : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getNumTris();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_getNumTris : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXCommandBuffer_getNumTris)

static bool js_gfx_GFXCommandBuffer_setViewport(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_setViewport : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXViewport, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_setViewport : Error processing arguments");
        cobj->setViewport(HolderType<cocos2d::GFXViewport, true>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_setViewport)

static bool js_gfx_GFXCommandBuffer_setDepthBias(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_setDepthBias : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        HolderType<float, false>::local_type arg0 = {};
        HolderType<float, false>::local_type arg1 = {};
        HolderType<float, false>::local_type arg2 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1); //is_reference False;
        ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_setDepthBias : Error processing arguments");
        cobj->setDepthBias(HolderType<float, false>::value(arg0), HolderType<float, false>::value(arg1), HolderType<float, false>::value(arg2));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_setDepthBias)

static bool js_gfx_GFXCommandBuffer_begin(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_begin : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->begin();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_begin)

static bool js_gfx_GFXCommandBuffer_getType(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_getType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getType();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_getType : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXCommandBuffer_getType)

static bool js_gfx_GFXCommandBuffer_bindBindingLayout(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_bindBindingLayout : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXBindingLayout*, false>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_bindBindingLayout : Error processing arguments");
        cobj->bindBindingLayout(HolderType<cocos2d::GFXBindingLayout*, false>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_bindBindingLayout)

static bool js_gfx_GFXCommandBuffer_endRenderPass(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_endRenderPass : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->endRenderPass();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_endRenderPass)

static bool js_gfx_GFXCommandBuffer_initialize(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXCommandBufferInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_initialize : Error processing arguments");
        bool result = cobj->initialize(HolderType<cocos2d::GFXCommandBufferInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_initialize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_initialize)

static bool js_gfx_GFXCommandBuffer_setScissor(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_setScissor : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXRect, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_setScissor : Error processing arguments");
        cobj->setScissor(HolderType<cocos2d::GFXRect, true>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_setScissor)

static bool js_gfx_GFXCommandBuffer_beginRenderPass(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_beginRenderPass : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 6) {
        HolderType<cocos2d::GFXFramebuffer*, false>::local_type arg0 = {};
        HolderType<cocos2d::GFXRect, true>::local_type arg1 = {};
        HolderType<cocos2d::GFXClearFlagBit, false>::local_type arg2 = {};
        HolderType<std::vector<cocos2d::GFXColor>, true>::local_type arg3 = {};
        HolderType<float, false>::local_type arg4 = {};
        HolderType<int, false>::local_type arg5 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference False;
        ok &= sevalue_to_native(args[1], &arg1); //is_reference True;
        ok &= sevalue_to_native(args[2], &arg2); //is_reference False;
        ok &= sevalue_to_native(args[3], &arg3); //is_reference True;
        ok &= sevalue_to_native(args[4], &arg4); //is_reference False;
        ok &= sevalue_to_native(args[5], &arg5); //is_reference False;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_beginRenderPass : Error processing arguments");
        cobj->beginRenderPass(HolderType<cocos2d::GFXFramebuffer*, false>::value(arg0), HolderType<cocos2d::GFXRect, true>::value(arg1), HolderType<cocos2d::GFXClearFlagBit, false>::value(arg2), HolderType<std::vector<cocos2d::GFXColor>, true>::value(arg3), HolderType<float, false>::value(arg4), HolderType<int, false>::value(arg5));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 6);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_beginRenderPass)

static bool js_gfx_GFXCommandBuffer_getNumDrawCalls(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_getNumDrawCalls : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        unsigned int result = cobj->getNumDrawCalls();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_getNumDrawCalls : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXCommandBuffer_getNumDrawCalls)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXCommandBuffer_finalize)

static bool js_gfx_GFXCommandBuffer_constructor(se::State& s) // constructor.c
{
    //#3 cocos2d::GFXCommandBuffer: is_skip_construtor True
    se::ScriptEngine::getInstance()->evalString("throw new Error(\"cocos2d::GFXCommandBuffer constructor is skipped\")");
    return false;
}
SE_BIND_CTOR(js_gfx_GFXCommandBuffer_constructor, __jsb_cocos2d_GFXCommandBuffer_class, js_cocos2d_GFXCommandBuffer_finalize)



extern se::Object* __jsb_cocos2d_GFXObject_proto;

static bool js_cocos2d_GFXCommandBuffer_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXCommandBuffer)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXCommandBuffer_finalize)

bool js_register_gfx_GFXCommandBuffer(se::Object* obj)
{
    auto cls = se::Class::create("GFXCommandBuffer", obj, __jsb_cocos2d_GFXObject_proto, _SE(js_gfx_GFXCommandBuffer_constructor));

    cls->defineProperty("numInstances", _SE(js_gfx_GFXCommandBuffer_getNumInstances), nullptr);
    cls->defineProperty("numDrawCalls", _SE(js_gfx_GFXCommandBuffer_getNumDrawCalls), nullptr);
    cls->defineProperty("numTris", _SE(js_gfx_GFXCommandBuffer_getNumTris), nullptr);
    cls->defineProperty("device", _SE(js_gfx_GFXCommandBuffer_getDevice), nullptr);
    cls->defineProperty("type", _SE(js_gfx_GFXCommandBuffer_getType), nullptr);
    cls->defineProperty("allocator", _SE(js_gfx_GFXCommandBuffer_getAllocator), nullptr);
    cls->defineFunction("draw", _SE(js_gfx_GFXCommandBuffer_draw));
    cls->defineFunction("setBlendConstants", _SE(js_gfx_GFXCommandBuffer_setBlendConstants));
    cls->defineFunction("setDepthBound", _SE(js_gfx_GFXCommandBuffer_setDepthBound));
    cls->defineFunction("copyBufferToTexture", _SE(js_gfx_GFXCommandBuffer_copyBufferToTexture));
    cls->defineFunction("setLineWidth", _SE(js_gfx_GFXCommandBuffer_setLineWidth));
    cls->defineFunction("updateBuffer", _SE(js_gfx_GFXCommandBuffer_updateBuffer));
    cls->defineFunction("end", _SE(js_gfx_GFXCommandBuffer_end));
    cls->defineFunction("setStencilWriteMask", _SE(js_gfx_GFXCommandBuffer_setStencilWriteMask));
    cls->defineFunction("setStencilCompareMask", _SE(js_gfx_GFXCommandBuffer_setStencilCompareMask));
    cls->defineFunction("bindInputAssembler", _SE(js_gfx_GFXCommandBuffer_bindInputAssembler));
    cls->defineFunction("bindPipelineState", _SE(js_gfx_GFXCommandBuffer_bindPipelineState));
    cls->defineFunction("destroy", _SE(js_gfx_GFXCommandBuffer_destroy));
    cls->defineFunction("setViewport", _SE(js_gfx_GFXCommandBuffer_setViewport));
    cls->defineFunction("setDepthBias", _SE(js_gfx_GFXCommandBuffer_setDepthBias));
    cls->defineFunction("begin", _SE(js_gfx_GFXCommandBuffer_begin));
    cls->defineFunction("bindBindingLayout", _SE(js_gfx_GFXCommandBuffer_bindBindingLayout));
    cls->defineFunction("endRenderPass", _SE(js_gfx_GFXCommandBuffer_endRenderPass));
    cls->defineFunction("initialize", _SE(js_gfx_GFXCommandBuffer_initialize));
    cls->defineFunction("setScissor", _SE(js_gfx_GFXCommandBuffer_setScissor));
    cls->defineFunction("beginRenderPass", _SE(js_gfx_GFXCommandBuffer_beginRenderPass));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXCommandBuffer_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXCommandBuffer>(cls);

    __jsb_cocos2d_GFXCommandBuffer_proto = cls->getProto();
    __jsb_cocos2d_GFXCommandBuffer_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

se::Object* __jsb_cocos2d_GFXQueue_proto = nullptr;
se::Class* __jsb_cocos2d_GFXQueue_class = nullptr;

static bool js_gfx_GFXQueue_getType(se::State& s)
{
    cocos2d::GFXQueue* cobj = (cocos2d::GFXQueue*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXQueue_getType : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        int result = (int)cobj->getType();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXQueue_getType : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXQueue_getType)

static bool js_gfx_GFXQueue_submit(se::State& s)
{
    cocos2d::GFXQueue* cobj = (cocos2d::GFXQueue*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXQueue_submit : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::vector<cocos2d::GFXCommandBuffer *>, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXQueue_submit : Error processing arguments");
        cobj->submit(HolderType<std::vector<cocos2d::GFXCommandBuffer *>, true>::value(arg0));
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXQueue_submit)

static bool js_gfx_GFXQueue_initialize(se::State& s)
{
    cocos2d::GFXQueue* cobj = (cocos2d::GFXQueue*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXQueue_initialize : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<cocos2d::GFXQueueInfo, true>::local_type arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0); //is_reference True;
        SE_PRECONDITION2(ok, false, "js_gfx_GFXQueue_initialize : Error processing arguments");
        bool result = cobj->initialize(HolderType<cocos2d::GFXQueueInfo, true>::value(arg0));
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXQueue_initialize : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXQueue_initialize)

static bool js_gfx_GFXQueue_destroy(se::State& s)
{
    cocos2d::GFXQueue* cobj = (cocos2d::GFXQueue*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXQueue_destroy : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        cobj->destroy();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXQueue_destroy)

static bool js_gfx_GFXQueue_getDevice(se::State& s)
{
    cocos2d::GFXQueue* cobj = (cocos2d::GFXQueue*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXQueue_getDevice : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 0) {
        cocos2d::GFXDevice* result = cobj->getDevice();
        ok &= nativevalue_to_se(result, s.rval());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXQueue_getDevice : Error processing arguments");
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_PROP_GET(js_gfx_GFXQueue_getDevice)

SE_DECLARE_FINALIZE_FUNC(js_cocos2d_GFXQueue_finalize)

static bool js_gfx_GFXQueue_constructor(se::State& s) // constructor.c
{
    //#3 cocos2d::GFXQueue: is_skip_construtor True
    se::ScriptEngine::getInstance()->evalString("throw new Error(\"cocos2d::GFXQueue constructor is skipped\")");
    return false;
}
SE_BIND_CTOR(js_gfx_GFXQueue_constructor, __jsb_cocos2d_GFXQueue_class, js_cocos2d_GFXQueue_finalize)



extern se::Object* __jsb_cocos2d_GFXObject_proto;

static bool js_cocos2d_GFXQueue_finalize(se::State& s)
{
    CCLOGINFO("jsbindings: finalizing JS object %p (cocos2d::GFXQueue)", s.nativeThisObject());
    auto iter = se::NonRefNativePtrCreatedByCtorMap::find(s.nativeThisObject());
    if (iter != se::NonRefNativePtrCreatedByCtorMap::end())
    {
        se::NonRefNativePtrCreatedByCtorMap::erase(iter);
        cocos2d::GFXQueue* cobj = (cocos2d::GFXQueue*)s.nativeThisObject();
        JSB_FREE(cobj);
    }
    return true;
}
SE_BIND_FINALIZE_FUNC(js_cocos2d_GFXQueue_finalize)

bool js_register_gfx_GFXQueue(se::Object* obj)
{
    auto cls = se::Class::create("GFXQueue", obj, __jsb_cocos2d_GFXObject_proto, _SE(js_gfx_GFXQueue_constructor));

    cls->defineProperty("device", _SE(js_gfx_GFXQueue_getDevice), nullptr);
    cls->defineProperty("type", _SE(js_gfx_GFXQueue_getType), nullptr);
    cls->defineFunction("submit", _SE(js_gfx_GFXQueue_submit));
    cls->defineFunction("initialize", _SE(js_gfx_GFXQueue_initialize));
    cls->defineFunction("destroy", _SE(js_gfx_GFXQueue_destroy));
    cls->defineFinalizeFunction(_SE(js_cocos2d_GFXQueue_finalize));
    cls->install();
    JSBClassType::registerClass<cocos2d::GFXQueue>(cls);

    __jsb_cocos2d_GFXQueue_proto = cls->getProto();
    __jsb_cocos2d_GFXQueue_class = cls;

    se::ScriptEngine::getInstance()->clearException();
    return true;
}

bool register_all_gfx(se::Object* obj)
{
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("gfx", &nsVal))
    {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("gfx", nsVal);
    }
    se::Object* ns = nsVal.toObject();

    js_register_gfx_GFXFeature(ns);
    js_register_gfx_GFXContextInfo(ns);
    js_register_gfx_GFXAddress(ns);
    js_register_gfx_GFXObject(ns);
    js_register_gfx_GFXCommandAllocator(ns);
    js_register_gfx_GFXBindingUnit(ns);
    js_register_gfx_GFXPipelineStateInfo(ns);
    js_register_gfx_GFXSampler(ns);
    js_register_gfx_GFXFormatInfo(ns);
    js_register_gfx_GFXShader(ns);
    js_register_gfx_GFXPipelineLayout(ns);
    js_register_gfx_GFXFramebufferInfo(ns);
    js_register_gfx_GFXTextureInfo(ns);
    js_register_gfx_GFXQueueInfo(ns);
    js_register_gfx_GFXSubPass(ns);
    js_register_gfx_GFXPushConstantRange(ns);
    js_register_gfx_GFXCommandBuffer(ns);
    js_register_gfx_GFXBufferAccessBit(ns);
    js_register_gfx_GFXTexture(ns);
    js_register_gfx_GFXQueue(ns);
    js_register_gfx_GFXInputAssemblerInfo(ns);
    js_register_gfx_GFXTextureCopy(ns);
    js_register_gfx_GFXRect(ns);
    js_register_gfx_GFXTextureType(ns);
    js_register_gfx_GFXRenderPassInfo(ns);
    js_register_gfx_GFXTextureSubres(ns);
    js_register_gfx_GFXAttribute(ns);
    js_register_gfx_GFXBufferTextureCopy(ns);
    js_register_gfx_GFXStencilOp(ns);
    js_register_gfx_GFXBuffer(ns);
    js_register_gfx_GFXType(ns);
    js_register_gfx_GFXPipelineLayoutInfo(ns);
    js_register_gfx_GFXBufferFlagBit(ns);
    js_register_gfx_GFXPrimitiveMode(ns);
    js_register_gfx_GFXBindingLayoutInfo(ns);
    js_register_gfx_GFXTextureView(ns);
    js_register_gfx_GFXBinding(ns);
    js_register_gfx_GFXBlendTarget(ns);
    js_register_gfx_GFXBindingType(ns);
    js_register_gfx_GFXClearFlagBit(ns);
    js_register_gfx_GFXTextureUsageBit(ns);
    js_register_gfx_GFXInputState(ns);
    js_register_gfx_GFXIndirectBuffer(ns);
    js_register_gfx_GFXBlendOp(ns);
    js_register_gfx_GFXFramebuffer(ns);
    js_register_gfx_GFXColor(ns);
    js_register_gfx_GFXBlendState(ns);
    js_register_gfx_GFXFormatType(ns);
    js_register_gfx_GFXTextureViewType(ns);
    js_register_gfx_GFXUniform(ns);
    js_register_gfx_GFXTextureViewInfo(ns);
    js_register_gfx_GFXFormat(ns);
    js_register_gfx_GFXLoadOp(ns);
    js_register_gfx_GFXShadeModel(ns);
    js_register_gfx_GFXStatus(ns);
    js_register_gfx_GFXWindow(ns);
    js_register_gfx_GFXStoreOp(ns);
    js_register_gfx_GFXColorAttachment(ns);
    js_register_gfx_GFXCommandBufferType(ns);
    js_register_gfx_GFXUniformSampler(ns);
    js_register_gfx_GFXUniformBlock(ns);
    js_register_gfx_GFXVsyncMode(ns);
    js_register_gfx_GFXDeviceInfo(ns);
    js_register_gfx_GFXBlendFactor(ns);
    js_register_gfx_GFXBufferUsageBit(ns);
    js_register_gfx_GFXDynamicState(ns);
    js_register_gfx_GFXCullMode(ns);
    js_register_gfx_GFXPipelineBindPoint(ns);
    js_register_gfx_GFXMemoryStatus(ns);
    js_register_gfx_GFXBindingLayout(ns);
    js_register_gfx_GFXBufferInfo(ns);
    js_register_gfx_GFXShaderMacro(ns);
    js_register_gfx_GFXQueueType(ns);
    js_register_gfx_GFXAPI(ns);
    js_register_gfx_GFXShaderType(ns);
    js_register_gfx_GFXExtent(ns);
    js_register_gfx_GFXMemoryUsageBit(ns);
    js_register_gfx_GFXWindowInfo(ns);
    js_register_gfx_GFXTextureFlagBit(ns);
    js_register_gfx_GFXFilter(ns);
    js_register_gfx_GFXPolygonMode(ns);
    js_register_gfx_GFXDevice(ns);
    js_register_gfx_GFXTextureLayout(ns);
    js_register_gfx_GFXStencilFace(ns);
    js_register_gfx_GFXInputAssembler(ns);
    js_register_gfx_GFXRenderPass(ns);
    js_register_gfx_GFXShaderStage(ns);
    js_register_gfx_GFXPipelineState(ns);
    js_register_gfx_GFXSampleCount(ns);
    js_register_gfx_GFXRasterizerState(ns);
    js_register_gfx_GFXColorMask(ns);
    js_register_gfx_GFXShaderInfo(ns);
    js_register_gfx_GFXOffset(ns);
    js_register_gfx_GFXObjectType(ns);
    js_register_gfx_GFXCommandBufferInfo(ns);
    js_register_gfx_GFXViewport(ns);
    js_register_gfx_GFXDepthStencilState(ns);
    js_register_gfx_GFXDepthStencilAttachment(ns);
    js_register_gfx_GFXDrawInfo(ns);
    js_register_gfx_GFXSamplerInfo(ns);
    js_register_gfx_GFXComparisonFunc(ns);
    return true;
}

