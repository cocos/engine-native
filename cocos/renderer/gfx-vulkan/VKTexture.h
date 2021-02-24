/****************************************************************************
 Copyright (c) 2020-2021 Xiamen Yaji Software Co., Ltd.

 http://www.cocos.com

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated engine source code (the "Software"), a limited,
 worldwide, royalty-free, non-assignable, revocable and non-exclusive license
 to use Cocos Creator solely to develop games on your target platforms. You shall
 not use Cocos Creator software for developing other software or tools that's
 used for developing games. You are not granted to publish, distribute,
 sublicense, and/or sell copies of Cocos Creator.

 The software or tools in this License Agreement are licensed, not sold.
 Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
****************************************************************************/

#ifndef CC_GFXVULKAN_TEXTURE_H_
#define CC_GFXVULKAN_TEXTURE_H_

#include "renderer/gfx-base/GFXTexture.h"

namespace cc {
namespace gfx {

class CCVKGPUTexture;
class CCVKGPUTextureView;

class CC_VULKAN_API CCVKTexture final : public Texture {
public:
    CCVKTexture(Device *device);
    ~CCVKTexture();

public:
    bool initialize(const TextureInfo &info);
    bool initialize(const TextureViewInfo &info);
    void destroy();
    void resize(uint width, uint height);

    CC_INLINE CCVKGPUTexture *gpuTexture() const { return _gpuTexture; }
    CC_INLINE CCVKGPUTextureView *gpuTextureView() const { return _gpuTextureView; }

private:
    void createTextureView();

    CCVKGPUTexture *_gpuTexture = nullptr;
    CCVKGPUTextureView *_gpuTextureView = nullptr;
};

} // namespace gfx
} // namespace cc

#endif
