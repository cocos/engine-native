#ifndef CC_CORE_GFX_PIPELINE_STATE_H_
#define CC_CORE_GFX_PIPELINE_STATE_H_

#include "GFXDef.h"

namespace cc {
namespace gfx {

class CC_DLL PipelineState : public GFXObject {
public:
    PipelineState(Device *device);
    virtual ~PipelineState();

public:
    virtual bool initialize(const PipelineStateInfo &info) = 0;
    virtual void destroy() = 0;

    CC_INLINE Device *getDevice() const { return _device; }
    CC_INLINE GFXShader *getShader() const { return _shader; }
    CC_INLINE GFXPrimitiveMode getPrimitive() const { return _primitive; }
    CC_INLINE const GFXInputState &getInputState() const { return _inputState; }
    CC_INLINE const GFXRasterizerState &getRasterizerState() const { return _rasterizerState; }
    CC_INLINE const GFXDepthStencilState &getDepthStencilState() const { return _depthStencilState; }
    CC_INLINE const GFXBlendState &getBlendState() const { return _blendState; }
    CC_INLINE const GFXDynamicStateList &getDynamicStates() const { return _dynamicStates; }
    CC_INLINE const PipelineLayout *getPipelineLayout() const { return _layout; }
    CC_INLINE const RenderPass *getRenderPass() const { return _renderPass; }

protected:
    Device *_device = nullptr;
    GFXShader *_shader = nullptr;
    GFXPrimitiveMode _primitive = GFXPrimitiveMode::TRIANGLE_LIST;
    GFXInputState _inputState;
    GFXRasterizerState _rasterizerState;
    GFXDepthStencilState _depthStencilState;
    GFXBlendState _blendState;
    GFXDynamicStateList _dynamicStates;
    PipelineLayout *_layout = nullptr;
    RenderPass *_renderPass = nullptr;
};

} // namespace gfx
} // namespace cc

#endif // CC_CORE_GFX_PIPELINE_STATE_H_
