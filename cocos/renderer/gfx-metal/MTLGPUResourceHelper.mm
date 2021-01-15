/****************************************************************************
Copyright (c) 2020 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "MTLStd.h"

#import <Foundation/Foundation.h>
#import <Metal/Metal.h>
#import "MTLGPUResourceHelper.h"
#import "MTLTexture.h"
#import "MTLBuffer.h"
namespace cc {
namespace gfx {

std::function<void(void)> CCMTLGPUResourceHelper::getTextureDestroyFunc(GFXObject* obj, Execution exec){
    switch (exec) {
        case INSTANT:
        {
            CCMTLTexture* ccTex = static_cast<CCMTLTexture*>(obj);
            return [=](){
                if (ccTex->_buffer) {
                    CC_FREE(ccTex->_buffer);
                    ccTex->_device->getMemoryStatus().textureSize -= ccTex->_size;
                    ccTex->_buffer = nullptr;
                }

                if (ccTex->_mtlTexture) {
                    [ccTex->_mtlTexture release];
                    ccTex->_mtlTexture = nil;
                    ccTex->_device->getMemoryStatus().textureSize -= ccTex->_size;
                }
            };
        }
            break;
        case DELAY:
        {
            //copy construtor to hand over assets, do not use  move constructor(CCMTLTexture&&) because objc type in it!
            CCMTLTexture ccTexture(*(static_cast<CCMTLTexture*>(obj)));
            return [=](){
                if (ccTexture._buffer) {
                    CC_FREE(ccTexture._buffer);
                    ccTexture._device->getMemoryStatus().textureSize -= ccTexture._size;
                }

                if (ccTexture._mtlTexture) {
                    [ccTexture._mtlTexture release];
                    ccTexture._device->getMemoryStatus().textureSize -= ccTexture._size;
                }
            };
        }
            
        default:
            break;
    }
}

std::function<void(void)> CCMTLGPUResourceHelper::getBufferDestroyFunc(GFXObject* obj, Execution exec){
    switch (exec) {
        case INSTANT:
        {
            CCMTLBuffer* ccBuffer = static_cast<CCMTLBuffer*>(obj);
            return [=](){
                if (ccBuffer->_isBufferView) {
                    return;
                }

                if (ccBuffer->_mtlBuffer) {
                    [ccBuffer->_mtlBuffer release];
                    ccBuffer->_mtlBuffer = nil;
                }

                if (ccBuffer->_buffer) {
                    CC_FREE(ccBuffer->_buffer);
                    ccBuffer->_device->getMemoryStatus().bufferSize -= ccBuffer->_size;
                    ccBuffer->_buffer = nullptr;
                }
                ccBuffer->_device->getMemoryStatus().bufferSize -= ccBuffer->_size;
            };
        }
            break;
        case DELAY:
        {
            CCMTLBuffer* ccBuffer = static_cast<CCMTLBuffer*>(obj);
            CCMTLBuffer ccBuf(*ccBuffer);
            return [=]() {
                if (ccBuf._isBufferView) {
                    return;
                }

                if (ccBuf._mtlBuffer) {
                    [ccBuf._mtlBuffer release];
                }

                if (ccBuf._buffer) {
                    CC_FREE(ccBuf._buffer);
                }
                
                ccBuf._device->getMemoryStatus().bufferSize -= ccBuffer->_size;
            };
        }
            break;
            
        default:
            break;
    }
}

} // namespace gfx
} // namespace cc
