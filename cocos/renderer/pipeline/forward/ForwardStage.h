#pragma once

#include "../RenderStage.h"

NS_PP_BEGIN

class RenderFlow;
class RenderView;

class CC_DLL ForwardStage : public RenderStage {
public:
    ForwardStage();
    ~ForwardStage();

    virtual void activate(RenderFlow *flow) override;
    virtual void destroy() override;
    virtual void resize(uint width, uint height) override;
    virtual void rebuild() override;
    virtual void render(RenderView *view) override;
};

NS_PP_END
