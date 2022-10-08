/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#pragma once

#include "platform/CCPlatformConfig.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#define glClearDepth                glClearDepthf
#define glDepthRange                glDepthRangef
//#define glDeleteVertexArrays        glDeleteVertexArraysOES
#define glGenVertexArrays           glGenVertexArraysOES
#define glBindVertexArray           glBindVertexArrayOES
//#define glMapBuffer                 glMapBufferOES
//#define glUnmapBuffer               glUnmapBufferOES
//
#define GL_DEPTH24_STENCIL8         GL_DEPTH24_STENCIL8_OES
//#define GL_DEPTH_STENCIL            GL_DEPTH_STENCIL_OES
//#define GL_WRITE_ONLY               GL_WRITE_ONLY_OES

//#define GL_MAX_SAMPLES_APPLE    GL_MAX_SAMPLES

#define GL_COMPRESSED_RGBA_ASTC_4x4_KHR                         0x93B0
#define GL_COMPRESSED_RGBA_ASTC_5x4_KHR                         0x93B1
#define GL_COMPRESSED_RGBA_ASTC_5x5_KHR                         0x93B2
#define GL_COMPRESSED_RGBA_ASTC_6x5_KHR                         0x93B3
#define GL_COMPRESSED_RGBA_ASTC_6x6_KHR                         0x93B4
#define GL_COMPRESSED_RGBA_ASTC_8x5_KHR                         0x93B5
#define GL_COMPRESSED_RGBA_ASTC_8x6_KHR                         0x93B6
#define GL_COMPRESSED_RGBA_ASTC_8x8_KHR                         0x93B7
#define GL_COMPRESSED_RGBA_ASTC_10x5_KHR                        0x93B8
#define GL_COMPRESSED_RGBA_ASTC_10x6_KHR                        0x93B9
#define GL_COMPRESSED_RGBA_ASTC_10x8_KHR                        0x93BA
#define GL_COMPRESSED_RGBA_ASTC_10x10_KHR                       0x93BB
#define GL_COMPRESSED_RGBA_ASTC_12x10_KHR                       0x93BC
#define GL_COMPRESSED_RGBA_ASTC_12x12_KHR                       0x93BD
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR                 0x93D0
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR                 0x93D1
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR                 0x93D2
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR                 0x93D3
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR                 0x93D4
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR                 0x93D5
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR                 0x93D6
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR                 0x93D7
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR                0x93D8
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR                0x93D9
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR                0x93DA
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR               0x93DB
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR               0x93DC
#define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR               0x93DD

#endif // CC_PLATFORM_IOS
