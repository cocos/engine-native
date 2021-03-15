/****************************************************************************
 Copyright (c) 2019-2021 Xiamen Yaji Software Co., Ltd.

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

#include "base/CoreStd.h"

#include "GFXFramebuffer.h"
#include "GFXTexture.h"

namespace cc {
namespace gfx {

Framebuffer::Framebuffer(Device *device)
: GFXObject(ObjectType::FRAMEBUFFER),
  _device(device) {
}

Framebuffer::~Framebuffer() {
}

uint Framebuffer::computeHash(const FramebufferInfo& info) {
    uint seed = info.colorTextures.size() + info.colorMipmapLevels.size() + 2;
    for (const Texture *attachment : info.colorTextures) {
        seed ^= (uint)attachment->getTextureID() + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    for (uint level : info.colorMipmapLevels) {
        seed ^= (uint)level + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    seed ^= (uint)info.depthStencilTexture->getTextureID() + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= (uint)info.depthStencilMipmapLevel + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
}

} // namespace gfx
} // namespace cc