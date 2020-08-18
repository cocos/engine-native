#ifndef CC_GFXGLES3_GLES3_BUFFER_H_
#define CC_GFXGLES3_GLES3_BUFFER_H_

namespace cc {
namespace gfx {

class GLES3GPUBuffer;

class CC_GLES3_API GLES3Buffer : public Buffer {
public:
    GLES3Buffer(Device *device);
    ~GLES3Buffer();

public:
    virtual bool initialize(const BufferInfo &info) override;
    virtual bool initialize(const BufferViewInfo &info) override;
    virtual void destroy() override;
    virtual void resize(uint size) override;
    virtual void update(void *buffer, uint offset, uint size) override;

    CC_INLINE GLES3GPUBuffer *gpuBuffer() const { return _gpuBuffer; }
    CC_INLINE bool isBufferView() const { return _isBufferView; }

private:
    bool _isBufferView = false;
    GLES3GPUBuffer *_gpuBuffer = nullptr;
};

} // namespace gfx
} // namespace cc

#endif
