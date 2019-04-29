/******************************************************************************
 * Spine Runtimes Software License v2.5
 *
 * Copyright (c) 2013-2016, Esoteric Software
 * All rights reserved.
 *
 * You are granted a perpetual, non-exclusive, non-sublicensable, and
 * non-transferable license to use, install, execute, and perform the Spine
 * Runtimes software and derivative works solely for personal or internal
 * use. Without the written permission of Esoteric Software (see Section 2 of
 * the Spine Software License Agreement), you may not (a) modify, translate,
 * adapt, or develop new applications using the Spine Runtimes or otherwise
 * create derivative works or improvements of the Spine Runtimes or (b) remove,
 * delete, alter, or obscure any trademarks or any copyright, trademark, patent,
 * or other intellectual property or proprietary rights notices on or in the
 * Software, including any copy thereof. Redistributions in binary or source
 * form must include this license and terms.
 *
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, BUSINESS INTERRUPTION, OR LOSS OF
 * USE, DATA, OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#pragma once

#include "spine/spine.h"
#include "spine-creator-support/SkeletonRenderer.h"
#include "spine-creator-support/SkeletonAnimation.h"
#include "middleware-adapter.h"

namespace spine {
    typedef cocos2d::middleware::Texture2D* (*CustomTextureLoader)(const char* path);
    // set custom texture loader for _spAtlasPage_createTexture
    void spAtlasPage_setCustomTextureLoader(CustomTextureLoader texLoader);

    class Cocos2dAtlasAttachmentLoader: public AtlasAttachmentLoader {
	public:
		Cocos2dAtlasAttachmentLoader(Atlas* atlas);
		virtual ~Cocos2dAtlasAttachmentLoader();
		virtual void configureAttachment(Attachment* attachment);
	};
	
	class Cocos2dTextureLoader: public TextureLoader {
	public:
		Cocos2dTextureLoader();
		
		virtual ~Cocos2dTextureLoader();
		
		virtual void load(AtlasPage& page, const String& path);
		
		virtual void unload(void* texture);
	};
	
	class Cocos2dExtension: public DefaultSpineExtension {
	public:
		Cocos2dExtension();
		
		virtual ~Cocos2dExtension();
        
		virtual void _free(void *mem, const char *file, int line);
	protected:
		virtual char *_readFile(const String &path, int *length);
	};
    
    typedef void (*SpineObjectDisposeCallback)(void*);
    void setSpineObjectDisposeCallback(SpineObjectDisposeCallback callback);
}
