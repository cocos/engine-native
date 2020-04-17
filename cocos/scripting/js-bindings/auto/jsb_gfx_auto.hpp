#pragma once
#include "base/ccConfig.h"
#include <type_traits>
#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "cocos/scripting/js-bindings/manual/jsb_conversions.hpp"
#include "renderer/core/Core.h"

extern se::Object* __jsb_cocos2d_GFXOffset_proto;
extern se::Class* __jsb_cocos2d_GFXOffset_class;

bool js_register_cocos2d_GFXOffset(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXOffset *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXOffset);

extern se::Object* __jsb_cocos2d_GFXRect_proto;
extern se::Class* __jsb_cocos2d_GFXRect_class;

bool js_register_cocos2d_GFXRect(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXRect *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXRect);

extern se::Object* __jsb_cocos2d_GFXExtent_proto;
extern se::Class* __jsb_cocos2d_GFXExtent_class;

bool js_register_cocos2d_GFXExtent(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXExtent *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXExtent);

extern se::Object* __jsb_cocos2d_GFXTextureSubres_proto;
extern se::Class* __jsb_cocos2d_GFXTextureSubres_class;

bool js_register_cocos2d_GFXTextureSubres(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXTextureSubres *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXTextureSubres);

extern se::Object* __jsb_cocos2d_GFXTextureCopy_proto;
extern se::Class* __jsb_cocos2d_GFXTextureCopy_class;

bool js_register_cocos2d_GFXTextureCopy(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXTextureCopy *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXTextureCopy);

extern se::Object* __jsb_cocos2d_GFXBufferTextureCopy_proto;
extern se::Class* __jsb_cocos2d_GFXBufferTextureCopy_class;

bool js_register_cocos2d_GFXBufferTextureCopy(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXBufferTextureCopy *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXBufferTextureCopy);

extern se::Object* __jsb_cocos2d_GFXViewport_proto;
extern se::Class* __jsb_cocos2d_GFXViewport_class;

bool js_register_cocos2d_GFXViewport(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXViewport *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXViewport);

extern se::Object* __jsb_cocos2d_GFXColor_proto;
extern se::Class* __jsb_cocos2d_GFXColor_class;

bool js_register_cocos2d_GFXColor(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXColor *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXColor);

extern se::Object* __jsb_cocos2d_GFXDeviceInfo_proto;
extern se::Class* __jsb_cocos2d_GFXDeviceInfo_class;

bool js_register_cocos2d_GFXDeviceInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXDeviceInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXDeviceInfo);

extern se::Object* __jsb_cocos2d_GFXWindowInfo_proto;
extern se::Class* __jsb_cocos2d_GFXWindowInfo_class;

bool js_register_cocos2d_GFXWindowInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXWindowInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXWindowInfo);

extern se::Object* __jsb_cocos2d_GFXContextInfo_proto;
extern se::Class* __jsb_cocos2d_GFXContextInfo_class;

bool js_register_cocos2d_GFXContextInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXContextInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXContextInfo);

extern se::Object* __jsb_cocos2d_GFXBufferInfo_proto;
extern se::Class* __jsb_cocos2d_GFXBufferInfo_class;

bool js_register_cocos2d_GFXBufferInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXBufferInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXBufferInfo);

extern se::Object* __jsb_cocos2d_GFXDrawInfo_proto;
extern se::Class* __jsb_cocos2d_GFXDrawInfo_class;

bool js_register_cocos2d_GFXDrawInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXDrawInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXDrawInfo);

extern se::Object* __jsb_cocos2d_GFXIndirectBuffer_proto;
extern se::Class* __jsb_cocos2d_GFXIndirectBuffer_class;

bool js_register_cocos2d_GFXIndirectBuffer(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXIndirectBuffer *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXIndirectBuffer);

extern se::Object* __jsb_cocos2d_GFXTextureInfo_proto;
extern se::Class* __jsb_cocos2d_GFXTextureInfo_class;

bool js_register_cocos2d_GFXTextureInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXTextureInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXTextureInfo);

extern se::Object* __jsb_cocos2d_GFXTextureViewInfo_proto;
extern se::Class* __jsb_cocos2d_GFXTextureViewInfo_class;

bool js_register_cocos2d_GFXTextureViewInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXTextureViewInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXTextureViewInfo);

extern se::Object* __jsb_cocos2d_GFXSamplerInfo_proto;
extern se::Class* __jsb_cocos2d_GFXSamplerInfo_class;

bool js_register_cocos2d_GFXSamplerInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXSamplerInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXSamplerInfo);

extern se::Object* __jsb_cocos2d_GFXShaderMacro_proto;
extern se::Class* __jsb_cocos2d_GFXShaderMacro_class;

bool js_register_cocos2d_GFXShaderMacro(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXShaderMacro *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXShaderMacro);

extern se::Object* __jsb_cocos2d_GFXUniform_proto;
extern se::Class* __jsb_cocos2d_GFXUniform_class;

bool js_register_cocos2d_GFXUniform(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXUniform *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXUniform);

extern se::Object* __jsb_cocos2d_GFXUniformBlock_proto;
extern se::Class* __jsb_cocos2d_GFXUniformBlock_class;

bool js_register_cocos2d_GFXUniformBlock(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXUniformBlock *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXUniformBlock);

extern se::Object* __jsb_cocos2d_GFXUniformSampler_proto;
extern se::Class* __jsb_cocos2d_GFXUniformSampler_class;

bool js_register_cocos2d_GFXUniformSampler(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXUniformSampler *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXUniformSampler);

extern se::Object* __jsb_cocos2d_GFXShaderStage_proto;
extern se::Class* __jsb_cocos2d_GFXShaderStage_class;

bool js_register_cocos2d_GFXShaderStage(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXShaderStage *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXShaderStage);

extern se::Object* __jsb_cocos2d_GFXShaderInfo_proto;
extern se::Class* __jsb_cocos2d_GFXShaderInfo_class;

bool js_register_cocos2d_GFXShaderInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXShaderInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXShaderInfo);

extern se::Object* __jsb_cocos2d_GFXAttribute_proto;
extern se::Class* __jsb_cocos2d_GFXAttribute_class;

bool js_register_cocos2d_GFXAttribute(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXAttribute *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXAttribute);

extern se::Object* __jsb_cocos2d_GFXInputAssemblerInfo_proto;
extern se::Class* __jsb_cocos2d_GFXInputAssemblerInfo_class;

bool js_register_cocos2d_GFXInputAssemblerInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXInputAssemblerInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXInputAssemblerInfo);

extern se::Object* __jsb_cocos2d_GFXColorAttachment_proto;
extern se::Class* __jsb_cocos2d_GFXColorAttachment_class;

bool js_register_cocos2d_GFXColorAttachment(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXColorAttachment *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXColorAttachment);

extern se::Object* __jsb_cocos2d_GFXDepthStencilAttachment_proto;
extern se::Class* __jsb_cocos2d_GFXDepthStencilAttachment_class;

bool js_register_cocos2d_GFXDepthStencilAttachment(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXDepthStencilAttachment *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXDepthStencilAttachment);

extern se::Object* __jsb_cocos2d_GFXSubPass_proto;
extern se::Class* __jsb_cocos2d_GFXSubPass_class;

bool js_register_cocos2d_GFXSubPass(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXSubPass *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXSubPass);

extern se::Object* __jsb_cocos2d_GFXRenderPassInfo_proto;
extern se::Class* __jsb_cocos2d_GFXRenderPassInfo_class;

bool js_register_cocos2d_GFXRenderPassInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXRenderPassInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXRenderPassInfo);

extern se::Object* __jsb_cocos2d_GFXFramebufferInfo_proto;
extern se::Class* __jsb_cocos2d_GFXFramebufferInfo_class;

bool js_register_cocos2d_GFXFramebufferInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXFramebufferInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXFramebufferInfo);

extern se::Object* __jsb_cocos2d_GFXBinding_proto;
extern se::Class* __jsb_cocos2d_GFXBinding_class;

bool js_register_cocos2d_GFXBinding(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXBinding *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXBinding);

extern se::Object* __jsb_cocos2d_GFXBindingLayoutInfo_proto;
extern se::Class* __jsb_cocos2d_GFXBindingLayoutInfo_class;

bool js_register_cocos2d_GFXBindingLayoutInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXBindingLayoutInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXBindingLayoutInfo);

extern se::Object* __jsb_cocos2d_GFXBindingUnit_proto;
extern se::Class* __jsb_cocos2d_GFXBindingUnit_class;

bool js_register_cocos2d_GFXBindingUnit(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXBindingUnit *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXBindingUnit);

extern se::Object* __jsb_cocos2d_GFXPushConstantRange_proto;
extern se::Class* __jsb_cocos2d_GFXPushConstantRange_class;

bool js_register_cocos2d_GFXPushConstantRange(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXPushConstantRange *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXPushConstantRange);

extern se::Object* __jsb_cocos2d_GFXPipelineLayoutInfo_proto;
extern se::Class* __jsb_cocos2d_GFXPipelineLayoutInfo_class;

bool js_register_cocos2d_GFXPipelineLayoutInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXPipelineLayoutInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXPipelineLayoutInfo);

extern se::Object* __jsb_cocos2d_GFXInputState_proto;
extern se::Class* __jsb_cocos2d_GFXInputState_class;

bool js_register_cocos2d_GFXInputState(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXInputState *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXInputState);

extern se::Object* __jsb_cocos2d_GFXRasterizerState_proto;
extern se::Class* __jsb_cocos2d_GFXRasterizerState_class;

bool js_register_cocos2d_GFXRasterizerState(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXRasterizerState *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXRasterizerState);

extern se::Object* __jsb_cocos2d_GFXDepthStencilState_proto;
extern se::Class* __jsb_cocos2d_GFXDepthStencilState_class;

bool js_register_cocos2d_GFXDepthStencilState(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXDepthStencilState *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXDepthStencilState);

extern se::Object* __jsb_cocos2d_GFXBlendTarget_proto;
extern se::Class* __jsb_cocos2d_GFXBlendTarget_class;

bool js_register_cocos2d_GFXBlendTarget(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXBlendTarget *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXBlendTarget);

extern se::Object* __jsb_cocos2d_GFXBlendState_proto;
extern se::Class* __jsb_cocos2d_GFXBlendState_class;

bool js_register_cocos2d_GFXBlendState(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXBlendState *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXBlendState);

extern se::Object* __jsb_cocos2d_GFXPipelineStateInfo_proto;
extern se::Class* __jsb_cocos2d_GFXPipelineStateInfo_class;

bool js_register_cocos2d_GFXPipelineStateInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXPipelineStateInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXPipelineStateInfo);

extern se::Object* __jsb_cocos2d_GFXCommandBufferInfo_proto;
extern se::Class* __jsb_cocos2d_GFXCommandBufferInfo_class;

bool js_register_cocos2d_GFXCommandBufferInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXCommandBufferInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXCommandBufferInfo);

extern se::Object* __jsb_cocos2d_GFXQueueInfo_proto;
extern se::Class* __jsb_cocos2d_GFXQueueInfo_class;

bool js_register_cocos2d_GFXQueueInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXQueueInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXQueueInfo);

extern se::Object* __jsb_cocos2d_GFXFormatInfo_proto;
extern se::Class* __jsb_cocos2d_GFXFormatInfo_class;

bool js_register_cocos2d_GFXFormatInfo(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXFormatInfo *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXFormatInfo);

extern se::Object* __jsb_cocos2d_GFXMemoryStatus_proto;
extern se::Class* __jsb_cocos2d_GFXMemoryStatus_class;

bool js_register_cocos2d_GFXMemoryStatus(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXMemoryStatus *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXMemoryStatus);

extern se::Object* __jsb_cocos2d_GFXObject_proto;
extern se::Class* __jsb_cocos2d_GFXObject_class;

bool js_register_cocos2d_GFXObject(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXObject *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXObject);
SE_DECLARE_FUNC(js_gfx_GFXObject_GFXObject);

extern se::Object* __jsb_cocos2d_GFXDevice_proto;
extern se::Class* __jsb_cocos2d_GFXDevice_class;

bool js_register_cocos2d_GFXDevice(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXDevice *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXDevice);
SE_DECLARE_FUNC(js_gfx_GFXDevice_hasFeature);
SE_DECLARE_FUNC(js_gfx_GFXDevice_getDepthStencilFormat);
SE_DECLARE_FUNC(js_gfx_GFXDevice_createPipelineState);
SE_DECLARE_FUNC(js_gfx_GFXDevice_createCommandBuffer);
SE_DECLARE_FUNC(js_gfx_GFXDevice_present);
SE_DECLARE_FUNC(js_gfx_GFXDevice_createTexture);
SE_DECLARE_FUNC(js_gfx_GFXDevice_destroy);
SE_DECLARE_FUNC(js_gfx_GFXDevice_getColorFormat);
SE_DECLARE_FUNC(js_gfx_GFXDevice_createFramebuffer);
SE_DECLARE_FUNC(js_gfx_GFXDevice_createRenderPass);
SE_DECLARE_FUNC(js_gfx_GFXDevice_createPipelineLayout);
SE_DECLARE_FUNC(js_gfx_GFXDevice_createWindow);
SE_DECLARE_FUNC(js_gfx_GFXDevice_createShader);
SE_DECLARE_FUNC(js_gfx_GFXDevice_createInputAssembler);
SE_DECLARE_FUNC(js_gfx_GFXDevice_defineMacro);
SE_DECLARE_FUNC(js_gfx_GFXDevice_createSampler);
SE_DECLARE_FUNC(js_gfx_GFXDevice_createBuffer);
SE_DECLARE_FUNC(js_gfx_GFXDevice_initialize);
SE_DECLARE_FUNC(js_gfx_GFXDevice_resize);
SE_DECLARE_FUNC(js_gfx_GFXDevice_createQueue);
SE_DECLARE_FUNC(js_gfx_GFXDevice_createBindingLayout);
SE_DECLARE_FUNC(js_gfx_GFXDevice_createTextureView);

extern se::Object* __jsb_cocos2d_GFXWindow_proto;
extern se::Class* __jsb_cocos2d_GFXWindow_class;

bool js_register_cocos2d_GFXWindow(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXWindow *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXWindow);
SE_DECLARE_FUNC(js_gfx_GFXWindow_getDepthStencilFormat);
SE_DECLARE_FUNC(js_gfx_GFXWindow_initialize);
SE_DECLARE_FUNC(js_gfx_GFXWindow_destroy);
SE_DECLARE_FUNC(js_gfx_GFXWindow_resize);
SE_DECLARE_FUNC(js_gfx_GFXWindow_GFXWindow);

extern se::Object* __jsb_cocos2d_GFXBuffer_proto;
extern se::Class* __jsb_cocos2d_GFXBuffer_class;

bool js_register_cocos2d_GFXBuffer(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXBuffer *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXBuffer);
SE_DECLARE_FUNC(js_gfx_GFXBuffer_initialize);
SE_DECLARE_FUNC(js_gfx_GFXBuffer_destroy);
SE_DECLARE_FUNC(js_gfx_GFXBuffer_resize);
SE_DECLARE_FUNC(js_gfx_GFXBuffer_GFXBuffer);

extern se::Object* __jsb_cocos2d_GFXTexture_proto;
extern se::Class* __jsb_cocos2d_GFXTexture_class;

bool js_register_cocos2d_GFXTexture(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXTexture *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXTexture);
SE_DECLARE_FUNC(js_gfx_GFXTexture_initialize);
SE_DECLARE_FUNC(js_gfx_GFXTexture_destroy);
SE_DECLARE_FUNC(js_gfx_GFXTexture_resize);
SE_DECLARE_FUNC(js_gfx_GFXTexture_GFXTexture);

extern se::Object* __jsb_cocos2d_GFXTextureView_proto;
extern se::Class* __jsb_cocos2d_GFXTextureView_class;

bool js_register_cocos2d_GFXTextureView(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXTextureView *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXTextureView);
SE_DECLARE_FUNC(js_gfx_GFXTextureView_initialize);
SE_DECLARE_FUNC(js_gfx_GFXTextureView_destroy);
SE_DECLARE_FUNC(js_gfx_GFXTextureView_GFXTextureView);

extern se::Object* __jsb_cocos2d_GFXSampler_proto;
extern se::Class* __jsb_cocos2d_GFXSampler_class;

bool js_register_cocos2d_GFXSampler(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXSampler *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXSampler);
SE_DECLARE_FUNC(js_gfx_GFXSampler_initialize);
SE_DECLARE_FUNC(js_gfx_GFXSampler_destroy);
SE_DECLARE_FUNC(js_gfx_GFXSampler_GFXSampler);

extern se::Object* __jsb_cocos2d_GFXShader_proto;
extern se::Class* __jsb_cocos2d_GFXShader_class;

bool js_register_cocos2d_GFXShader(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXShader *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXShader);
SE_DECLARE_FUNC(js_gfx_GFXShader_initialize);
SE_DECLARE_FUNC(js_gfx_GFXShader_destroy);
SE_DECLARE_FUNC(js_gfx_GFXShader_GFXShader);

extern se::Object* __jsb_cocos2d_GFXInputAssembler_proto;
extern se::Class* __jsb_cocos2d_GFXInputAssembler_class;

bool js_register_cocos2d_GFXInputAssembler(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXInputAssembler *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXInputAssembler);
SE_DECLARE_FUNC(js_gfx_GFXInputAssembler_destroy);
SE_DECLARE_FUNC(js_gfx_GFXInputAssembler_initialize);
SE_DECLARE_FUNC(js_gfx_GFXInputAssembler_GFXInputAssembler);

extern se::Object* __jsb_cocos2d_GFXRenderPass_proto;
extern se::Class* __jsb_cocos2d_GFXRenderPass_class;

bool js_register_cocos2d_GFXRenderPass(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXRenderPass *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXRenderPass);
SE_DECLARE_FUNC(js_gfx_GFXRenderPass_initialize);
SE_DECLARE_FUNC(js_gfx_GFXRenderPass_destroy);
SE_DECLARE_FUNC(js_gfx_GFXRenderPass_GFXRenderPass);

extern se::Object* __jsb_cocos2d_GFXFramebuffer_proto;
extern se::Class* __jsb_cocos2d_GFXFramebuffer_class;

bool js_register_cocos2d_GFXFramebuffer(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXFramebuffer *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXFramebuffer);
SE_DECLARE_FUNC(js_gfx_GFXFramebuffer_getDepthStencilView);
SE_DECLARE_FUNC(js_gfx_GFXFramebuffer_isOffscreen);
SE_DECLARE_FUNC(js_gfx_GFXFramebuffer_getColorViews);
SE_DECLARE_FUNC(js_gfx_GFXFramebuffer_initialize);
SE_DECLARE_FUNC(js_gfx_GFXFramebuffer_destroy);
SE_DECLARE_FUNC(js_gfx_GFXFramebuffer_getRenderPass);
SE_DECLARE_FUNC(js_gfx_GFXFramebuffer_getDevice);
SE_DECLARE_FUNC(js_gfx_GFXFramebuffer_GFXFramebuffer);

extern se::Object* __jsb_cocos2d_GFXBindingLayout_proto;
extern se::Class* __jsb_cocos2d_GFXBindingLayout_class;

bool js_register_cocos2d_GFXBindingLayout(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXBindingLayout *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXBindingLayout);
SE_DECLARE_FUNC(js_gfx_GFXBindingLayout_bindTextureView);
SE_DECLARE_FUNC(js_gfx_GFXBindingLayout_bindBuffer);
SE_DECLARE_FUNC(js_gfx_GFXBindingLayout_bindSampler);
SE_DECLARE_FUNC(js_gfx_GFXBindingLayout_update);
SE_DECLARE_FUNC(js_gfx_GFXBindingLayout_initialize);
SE_DECLARE_FUNC(js_gfx_GFXBindingLayout_destroy);
SE_DECLARE_FUNC(js_gfx_GFXBindingLayout_GFXBindingLayout);

extern se::Object* __jsb_cocos2d_GFXPipelineLayout_proto;
extern se::Class* __jsb_cocos2d_GFXPipelineLayout_class;

bool js_register_cocos2d_GFXPipelineLayout(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXPipelineLayout *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXPipelineLayout);
SE_DECLARE_FUNC(js_gfx_GFXPipelineLayout_getLayouts);
SE_DECLARE_FUNC(js_gfx_GFXPipelineLayout_initialize);
SE_DECLARE_FUNC(js_gfx_GFXPipelineLayout_destroy);
SE_DECLARE_FUNC(js_gfx_GFXPipelineLayout_getPushConstantsRanges);
SE_DECLARE_FUNC(js_gfx_GFXPipelineLayout_GFXPipelineLayout);

extern se::Object* __jsb_cocos2d_GFXPipelineState_proto;
extern se::Class* __jsb_cocos2d_GFXPipelineState_class;

bool js_register_cocos2d_GFXPipelineState(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXPipelineState *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXPipelineState);
SE_DECLARE_FUNC(js_gfx_GFXPipelineState_initialize);
SE_DECLARE_FUNC(js_gfx_GFXPipelineState_destroy);
SE_DECLARE_FUNC(js_gfx_GFXPipelineState_getDynamicStates);
SE_DECLARE_FUNC(js_gfx_GFXPipelineState_GFXPipelineState);

extern se::Object* __jsb_cocos2d_GFXCommandAllocator_proto;
extern se::Class* __jsb_cocos2d_GFXCommandAllocator_class;

bool js_register_cocos2d_GFXCommandAllocator(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXCommandAllocator *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXCommandAllocator);
SE_DECLARE_FUNC(js_gfx_GFXCommandAllocator_destroy);
SE_DECLARE_FUNC(js_gfx_GFXCommandAllocator_getDevice);
SE_DECLARE_FUNC(js_gfx_GFXCommandAllocator_GFXCommandAllocator);

extern se::Object* __jsb_cocos2d_GFXCommandBuffer_proto;
extern se::Class* __jsb_cocos2d_GFXCommandBuffer_class;

bool js_register_cocos2d_GFXCommandBuffer(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXCommandBuffer *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXCommandBuffer);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_draw);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_setBlendConstants);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_setDepthBound);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_copyBufferToTexture);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_setLineWidth);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_updateBuffer);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_end);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_setStencilWriteMask);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_setStencilCompareMask);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_bindInputAssembler);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_bindPipelineState);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_destroy);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_setViewport);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_setDepthBias);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_begin);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_bindBindingLayout);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_endRenderPass);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_initialize);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_setScissor);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_beginRenderPass);
SE_DECLARE_FUNC(js_gfx_GFXCommandBuffer_GFXCommandBuffer);

extern se::Object* __jsb_cocos2d_GFXQueue_proto;
extern se::Class* __jsb_cocos2d_GFXQueue_class;

bool js_register_cocos2d_GFXQueue(se::Object* obj);
bool register_all_gfx(se::Object* obj);

template<>
bool sevalue_to_native(const se::Value &, cocos2d::GFXQueue *);
JSB_REGISTER_OBJECT_TYPE(cocos2d::GFXQueue);
SE_DECLARE_FUNC(js_gfx_GFXQueue_submit);
SE_DECLARE_FUNC(js_gfx_GFXQueue_initialize);
SE_DECLARE_FUNC(js_gfx_GFXQueue_destroy);
SE_DECLARE_FUNC(js_gfx_GFXQueue_GFXQueue);

