#include "jsb_gfx_manual.hpp"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#include "scripting/js-bindings/manual/jsb_global.h"
#include "scripting/js-bindings/jswrapper/SeApi.h"
#include "scripting/js-bindings/auto/jsb_gfx_auto.hpp"
#include "platform/CCPlatformConfig.h"
#include "scripting/js-bindings/auto/jsb_gles3_auto.hpp"
#include "renderer/gfx-gles3/GFXGLES3.h"

#if (CC_PLATFORM == CC_PLATFORM_ANDROID)
#define USE_GLES2
#endif

#ifdef USE_GLES2
#include "scripting/js-bindings/auto/jsb_gles2_auto.hpp"
#include "renderer/gfx-gles2/GFXGLES2.h"
#endif

#if (CC_PLATFORM == CC_PLATFORM_MAC_OSX)
#include "scripting/js-bindings/auto/jsb_mtl_auto.hpp"
#include "renderer/gfx-metal/GFXMTL.h"
#endif

#include <fstream>
#include <sstream>

#define GFX_MAX_VERTEX_ATTRIBUTES 16
#define GFX_MAX_TEXTURE_UNITS 16
#define GFX_MAX_ATTACHMENTS 4
#define GFX_MAX_BUFFER_BINDINGS 24
#define GFX_INVALID_BINDING ((uint8_t)-1)
#define GFX_INVALID_HANDLE ((uint)-1)

bool js_GFXDevice_copyBuffersToTexture(se::State& s, cocos2d::GFXDevice* cobj)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        cocos2d::GFXDataArray arg0;
        cocos2d::GFXTexture* arg1 = nullptr;
        std::vector<cocos2d::GFXBufferTextureCopy> arg2;
        if (args[0].isObject())
        {
            se::Object* dataObj = args[0].toObject();
            SE_PRECONDITION2(dataObj->isArray(), false, "Buffers must be an array!");
            uint32_t length = 0;
            dataObj->getArrayLength(&length);
            arg0.datas.resize(length);
            
            se::Value value;
            for (uint32_t i = 0; i < length; ++i)
            {
                if (dataObj->getArrayElement(i, &value))
                {
                    uint8_t* ptr = nullptr;
                    CC_UNUSED size_t dataLength = 0;
                    se::Object* obj = value.toObject();
                    if (obj->isArrayBuffer())
                    {
                        ok = obj->getArrayBufferData(&ptr, &dataLength);
                        SE_PRECONDITION2(ok, false, "getArrayBufferData failed!");
                    }
                    else if (obj->isTypedArray())
                    {
                        ok = obj->getTypedArrayData(&ptr, &dataLength);
                        SE_PRECONDITION2(ok, false, "getTypedArrayData failed!");
                    }
                    else
                    {
                        assert(false);
                    }
                    arg0.datas[i] = ptr;
                }
            }
        }
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_copyBuffersToTexture : Error processing arguments");
        cobj->copyBuffersToTexture(arg0, arg1, arg2);
        return true;
    }
    
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}

bool js_GFXDevice_copyTexImagesToTexture(se::State& s, cocos2d::GFXDevice* cobj)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 3) {
        cocos2d::GFXDataArray arg0;
        cocos2d::GFXTexture* arg1 = nullptr;
        std::vector<cocos2d::GFXBufferTextureCopy> arg2;
        if (args[0].isObject())
        {
            se::Object* dataObj = args[0].toObject();
            SE_PRECONDITION2(dataObj->isArray(), false, "Buffers must be an array!");
            uint32_t length = 0;
            dataObj->getArrayLength(&length);
            arg0.datas.resize(length);
            
            se::Value value;
            for (uint32_t i = 0; i < length; ++i)
            {
                if (dataObj->getArrayElement(i, &value))
                {
                    CC_UNUSED size_t dataLength = 0;
                    cocos2d::Data bufferData;
                    ok &= seval_to_Data(value, &bufferData);
                    arg0.datas[i] = bufferData.takeBuffer();
                }
            }
        }
        else
        {
            ok &= false;
        }
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXDevice_copyBuffersToTexture : Error processing arguments");
        cobj->copyBuffersToTexture(arg0, arg1, arg2);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}

#ifdef USE_GLES2
static bool js_gfx_GLES2Device_copyBuffersToTexture(se::State& s)
{
    cocos2d::GLES2Device* cobj = (cocos2d::GLES2Device*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GLES2Device_copyBuffersToTexture : Invalid Native Object");
    return js_GFXDevice_copyBuffersToTexture(s, cobj);
}
SE_BIND_FUNC(js_gfx_GLES2Device_copyBuffersToTexture)

static bool js_gfx_GLES2Device_copyTexImagesToTexture(se::State& s)
{
    cocos2d::GLES2Device* cobj = (cocos2d::GLES2Device*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GLES2Device_copyTexImagesToTexture : Invalid Native Object");
    return js_GFXDevice_copyTexImagesToTexture(s, cobj);
}
SE_BIND_FUNC(js_gfx_GLES2Device_copyTexImagesToTexture);
#endif // USE_GLES2

#if (CC_PLATFORM == CC_PLATFORM_MAC_OSX)
static bool js_gfx_CCMTLDevice_copyBuffersToTexture(se::State& s)
{
    cocos2d::CCMTLDevice* cobj = (cocos2d::CCMTLDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_CCMTLDevice_copyBuffersToTexture : Invalid Native Object");
    return js_GFXDevice_copyBuffersToTexture(s, cobj);
}
SE_BIND_FUNC(js_gfx_CCMTLDevice_copyBuffersToTexture)

static bool js_gfx_CCMTLDevice_copyTexImagesToTexture(se::State& s)
{
    cocos2d::CCMTLDevice* cobj = (cocos2d::CCMTLDevice*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_CCMTLDevice_copyTexImagesToTexture : Invalid Native Object");
    return js_GFXDevice_copyTexImagesToTexture(s, cobj);
}
SE_BIND_FUNC(js_gfx_CCMTLDevice_copyTexImagesToTexture);
#endif // #if (CC_PLATFORM == CC_PLATFORM_MAC_OSX)

static bool js_gfx_GLES3Device_copyBuffersToTexture(se::State& s)
{
    cocos2d::GLES3Device* cobj = (cocos2d::GLES3Device*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GLES3Device_copyBuffersToTexture : Invalid Native Object");
    return js_GFXDevice_copyBuffersToTexture(s, cobj);
}
SE_BIND_FUNC(js_gfx_GLES3Device_copyBuffersToTexture)

static bool js_gfx_GLES3Device_copyTexImagesToTexture(se::State& s)
{
    cocos2d::GLES3Device* cobj = (cocos2d::GLES3Device*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GLES3Device_copyTexImagesToTexture : Invalid Native Object");
    return js_GFXDevice_copyTexImagesToTexture(s, cobj);
}
SE_BIND_FUNC(js_gfx_GLES3Device_copyTexImagesToTexture);

static bool js_gfx_GFXBuffer_update(se::State& s)
{
    cocos2d::GFXBuffer* cobj = (cocos2d::GFXBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXBuffer_update : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;

    uint8_t* arg0 = nullptr;
    CC_UNUSED size_t dataLength = 0;
    se::Object* obj = args[0].toObject();
    if (obj->isArrayBuffer())
    {
        ok = obj->getArrayBufferData(&arg0, &dataLength);
        SE_PRECONDITION2(ok, false, "getArrayBufferData failed!");
    }
    else if (obj->isTypedArray())
    {
        ok = obj->getTypedArrayData(&arg0, &dataLength);
        SE_PRECONDITION2(ok, false, "getTypedArrayData failed!");
    }
    else
    {
        ok = false;
    }
    
    if (argc == 1) {
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBuffer_update : Error processing arguments");
        cobj->update(arg0, 0, static_cast<uint>(dataLength));
        return true;
    }
    if (argc == 2) {
        unsigned int arg1 = 0;
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBuffer_update : Error processing arguments");
        cobj->update(arg0, arg1, static_cast<uint>(dataLength));
        return true;
    }
    if (argc == 3) {
        unsigned int arg1 = 0;
        unsigned int arg2 = 0;
        ok &= sevalue_to_native(args[1], &arg1, s.thisObject());
        ok &= sevalue_to_native(args[2], &arg2, s.thisObject());
        SE_PRECONDITION2(ok, false, "js_gfx_GFXBuffer_update : Error processing arguments");
        cobj->update(arg0, arg1, arg2);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 3);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXBuffer_update)

static bool js_gfx_GFXCommandBuffer_execute(se::State& s)
{
    cocos2d::GFXCommandBuffer* cobj = (cocos2d::GFXCommandBuffer*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXCommandBuffer_execute : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 2) {
        std::vector<cocos2d::GFXCommandBuffer *> cmdBufs;
        unsigned int count = 0;
        ok &= sevalue_to_native(args[1], &count, s.thisObject());
        
        se::Object* jsarr = args[0].toObject();
        assert(jsarr->isArray());
        uint32_t len = 0;
        ok &= jsarr->getArrayLength(&len);
        if (len < count)
        {
            ok = false;
        }
        if (ok)
        {
            cmdBufs.resize(count);
            
            se::Value tmp;
            for (uint32_t i = 0; i < count; ++i)
            {
                ok = jsarr->getArrayElement(i, &tmp);
                if (!ok || !tmp.isObject())
                {
                    cmdBufs.clear();
                    break;
                }
                
                cocos2d::GFXCommandBuffer *cmdBuf = (cocos2d::GFXCommandBuffer*)tmp.toObject()->getPrivateData();
                cmdBufs[i] = cmdBuf;
            }
        }
        
        SE_PRECONDITION2(ok, false, "js_gfx_GFXCommandBuffer_execute : Error processing arguments");
        cobj->execute(cmdBufs, count);
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 2);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXCommandBuffer_execute)

static bool js_gfx_GFXInputAssembler_extractDrawInfo(se::State& s)
{
    cocos2d::GFXInputAssembler* cobj = (cocos2d::GFXInputAssembler*)s.nativeThisObject();
    SE_PRECONDITION2(cobj, false, "js_gfx_GFXInputAssembler_extractDrawInfo : Invalid Native Object");
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 1) {
        cocos2d::GFXDrawInfo nativeDrawInfo;
        cobj->extractDrawInfo(nativeDrawInfo);
        
        se::Object* drawInfo = args[0].toObject();
        se::Value attrValue(nativeDrawInfo.vertexCount);
        drawInfo->setProperty("vertexCount", attrValue);
        
        attrValue.setUint32(nativeDrawInfo.firstVertex);
        drawInfo->setProperty("firstVertex", attrValue);
        
        attrValue.setUint32(nativeDrawInfo.indexCount);
        drawInfo->setProperty("indexCount", attrValue);
        
        attrValue.setUint32(nativeDrawInfo.firstIndex);
        drawInfo->setProperty("firstIndex", attrValue);
        
        attrValue.setUint32(nativeDrawInfo.vertexOffset);
        drawInfo->setProperty("vertexOffset", attrValue);
        
        attrValue.setUint32(nativeDrawInfo.instanceCount);
        drawInfo->setProperty("instanceCount", attrValue);
        
        attrValue.setUint32(nativeDrawInfo.firstInstance);
        drawInfo->setProperty("firstInstance", attrValue);

        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_gfx_GFXInputAssembler_extractDrawInfo)

bool register_all_gfx_manual(se::Object* obj)
{    
    __jsb_cocos2d_GFXBuffer_proto->defineFunction("update", _SE(js_gfx_GFXBuffer_update));
            
    __jsb_cocos2d_GFXCommandBuffer_proto->defineFunction("execute", _SE(js_gfx_GFXCommandBuffer_execute));

    __jsb_cocos2d_GFXInputAssembler_proto->defineFunction("extractDrawInfo", _SE(js_gfx_GFXInputAssembler_extractDrawInfo));
        
#ifdef USE_GLES2
    register_all_gles2(obj);
    __jsb_cocos2d_GLES2Device_proto->defineFunction("copyBuffersToTexture", _SE(js_gfx_GLES2Device_copyBuffersToTexture));
    __jsb_cocos2d_GLES2Device_proto->defineFunction("copyTexImagesToTexture", _SE(js_gfx_GLES2Device_copyTexImagesToTexture));
#endif // USE_GLES2
    
    register_all_gles3(obj);
    __jsb_cocos2d_GLES3Device_proto->defineFunction("copyBuffersToTexture", _SE(js_gfx_GLES3Device_copyBuffersToTexture));
    __jsb_cocos2d_GLES3Device_proto->defineFunction("copyTexImagesToTexture", _SE(js_gfx_GLES3Device_copyTexImagesToTexture));
    
#if (CC_PLATFORM == CC_PLATFORM_MAC_OSX)
    register_all_mtl(obj);
    __jsb_cocos2d_CCMTLDevice_proto->defineFunction("copyBuffersToTexture", _SE(js_gfx_CCMTLDevice_copyBuffersToTexture));
    __jsb_cocos2d_CCMTLDevice_proto->defineFunction("copyTexImagesToTexture", _SE(js_gfx_CCMTLDevice_copyTexImagesToTexture));
#endif
    
    return true;
}
