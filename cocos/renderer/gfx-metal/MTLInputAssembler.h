#pragma once

namespace cc {
namespace gfx {

class CCMTLCmdDraw;
class CCMTLGPUInputAssembler;

class CCMTLInputAssembler : public InputAssembler {
    friend class CCMTLQueue;

public:
    CCMTLInputAssembler(Device *device);
    ~CCMTLInputAssembler();

    virtual bool initialize(const InputAssemblerInfo &info) override;
    virtual void destroy() override;

    void extractDrawInfo(CCMTLCmdDraw *) const;

    CC_INLINE CCMTLGPUInputAssembler *getGPUInputAssembler() const { return _GPUInputAssembler; }

private:
    CCMTLGPUInputAssembler *_GPUInputAssembler = nullptr;
};

} // namespace gfx
} // namespace cc
