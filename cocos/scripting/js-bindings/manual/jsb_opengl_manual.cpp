/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "jsb_opengl_manual.hpp"
#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "cocos/scripting/js-bindings/manual/jsb_conversions.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_global.h"
#include "cocos/scripting/js-bindings/manual/jsb_opengl_utils.hpp"
#include "platform/CCGL.h"

#include <regex>

namespace {

    GLint __defaultFbo = 0;

    template<typename T>
    class GLData
    {
    public:
        GLData()
        : _data(nullptr)
        , _count(0)
        , _isOwnData(false)
        {
        }

        ~GLData()
        {
            if (_isOwnData)
            {
                free(_data);
            }
        }

        void setData(T* data, size_t count, bool isOwnData)
        {
            _data = data;
            _count = count;
            _isOwnData = isOwnData;
        }

        T* data() const { return _data; }
        size_t count() const { return _count; }

    private:

        // Disable copy/move constructor, copy/move assigment
        GLData(const GLData&);
        GLData(GLData&&);
        GLData& operator=(const GLData&);
        GLData& operator=(GLData&&);

        T* _data;
        size_t _count;
        bool _isOwnData;
    };

}

template<typename T>
static bool JSB_jsval_typedarray_to_data(const se::Value& v, GLData<T>& data)
{
    if (v.isObject())
    {
        se::Object* obj = v.toObject();
        if (obj->isArray())
        {
            uint32_t length = 0;
            if (obj->getArrayLength(&length) && length > 0)
            {
                T* d = (T*)malloc(length * sizeof(T));
                se::Value tmp;
                for (uint32_t i = 0; i < length; ++i)
                {
                    if (obj->getArrayElement(i, &tmp))
                    {
                        if (std::is_same<T, int32_t>::value)
                        {
                            d[i] = tmp.toInt32();
                        }
                        else if (std::is_same<T, float>::value)
                        {
                            d[i] = tmp.toFloat();
                        }
                    }
                }
                data.setData(d, length, true);
                return true;
            }
            SE_LOGE("Failed to get array data");
        }
        else if (obj->isTypedArray())
        {
            size_t bytes = 0;
            uint8_t* ptr = nullptr;

            if (obj->getTypedArrayData(&ptr, &bytes) && bytes > 0)
            {
                data.setData((T*)ptr, bytes / sizeof(T), false);
                return true;
            }

            SE_LOGE("Failed to get typed array data");
        }
        else if (obj->isArrayBuffer())
        {
            size_t bytes = 0;
            uint8_t* ptr = nullptr;

            if (obj->getArrayBufferData(&ptr, &bytes) && bytes > 0)
            {
                data.setData((T*)ptr, bytes / sizeof(T), false);
                return true;
            }

            SE_LOGE("Failed to get typed array data");
        }
    }

    return false;
}

static bool JSB_get_arraybufferview_dataptr(const se::Value& v, GLsizei *count, GLvoid **data)
{
    assert(count != nullptr && data != nullptr);

    if (v.isObject())
    {
        uint8_t* ptr = nullptr;
        size_t length = 0;
        se::Object* obj = v.toObject();
        if (obj->isTypedArray())
        {
            if (obj->getTypedArrayData(&ptr, &length) && ptr != nullptr && length > 0)
            {
                *data = ptr;
                *count = (GLsizei)length;
                return true;
            }
        }
        else if (obj->isArrayBuffer())
        {
            if (obj->getArrayBufferData(&ptr, &length) && ptr != nullptr && length > 0)
            {
                *data = ptr;
                *count = (GLsizei)length;
                return true;
            }
        }
        else
        {
            SE_LOGE("JSB_get_arraybufferview_dataptr: isn't a typed array!\n");
        }
    }
    else if (v.isNullOrUndefined())
    {
        *count = 0;
        *data = nullptr;
        return true;
    }
    else
    {
        assert(false);
    }
    return false;
}

// Arguments: GLenum
// Ret value: void
static bool JSB_glActiveTexture(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glActiveTexture((GLenum)arg0));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glActiveTexture)

// Arguments: GLuint, GLuint
// Ret value: void
static bool JSB_glAttachShader(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glAttachShader((GLuint)arg0 , (GLuint)arg1  ));

    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glAttachShader)

// Arguments: GLuint, GLuint, char*
// Ret value: void
static bool JSB_glBindAttribLocation(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 3, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1; std::string arg2;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    ok &= seval_to_std_string(args[2], &arg2 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glBindAttribLocation((GLuint)arg0 , (GLuint)arg1 , arg2.c_str()  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glBindAttribLocation)

// Arguments: GLenum, GLuint
// Ret value: void
static bool JSB_glBindBuffer(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glBindBuffer((GLenum)arg0 , (GLuint)arg1  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glBindBuffer)

// Arguments: GLenum, GLuint
// Ret value: void
static bool JSB_glBindFramebuffer(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1;

    ok &= seval_to_uint32(args[0], &arg0 );

    if (args[1].isNullOrUndefined())
    {
        arg1 = __defaultFbo;
    }
    else
    {
        ok &= seval_to_uint32(args[1], &arg1 );
        SE_PRECONDITION2(ok, false, "Error processing arguments");
    }

    JSB_GL_CHECK(glBindFramebuffer((GLenum)arg0 , (GLuint)arg1  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glBindFramebuffer)

// Arguments: GLenum, GLuint
// Ret value: void
static bool JSB_glBindRenderbuffer(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glBindRenderbuffer((GLenum)arg0 , (GLuint)arg1  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glBindRenderbuffer)

// Arguments: GLenum, GLuint
// Ret value: void
static bool JSB_glBindTexture(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glBindTexture((GLenum)arg0 , (GLuint)arg1  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glBindTexture)

// Arguments: GLclampf, GLclampf, GLclampf, GLclampf
// Ret value: void
static bool JSB_glBlendColor(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 4, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; int32_t arg1; int32_t arg2; int32_t arg3;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glBlendColor((GLclampf)arg0 , (GLclampf)arg1 , (GLclampf)arg2 , (GLclampf)arg3  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glBlendColor)

// Arguments: GLenum
// Ret value: void
static bool JSB_glBlendEquation(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glBlendEquation((GLenum)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glBlendEquation)

// Arguments: GLenum, GLenum
// Ret value: void
static bool JSB_glBlendEquationSeparate(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glBlendEquationSeparate((GLenum)arg0 , (GLenum)arg1  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glBlendEquationSeparate)

// Arguments: GLenum, GLenum
// Ret value: void
static bool JSB_glBlendFunc(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glBlendFunc((GLenum)arg0 , (GLenum)arg1  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glBlendFunc)

// Arguments: GLenum, GLenum, GLenum, GLenum
// Ret value: void
static bool JSB_glBlendFuncSeparate(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 4, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1; uint32_t arg2; uint32_t arg3;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    ok &= seval_to_uint32(args[2], &arg2 );
    ok &= seval_to_uint32(args[3], &arg3 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glBlendFuncSeparate((GLenum)arg0 , (GLenum)arg1 , (GLenum)arg2 , (GLenum)arg3  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glBlendFuncSeparate)

// Arguments: GLenum, ArrayBufferView, GLenum
// Ret value: void
static bool JSB_glBufferData(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 3, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0 = 0;
    void* arg1 = nullptr;
    uint32_t arg2 = 0;
    GLsizei count = 0;
    ok &= seval_to_uint32(args[0], &arg0 );
    if (args[1].isNumber())
    {
        count = args[1].toUint32();
    }
    else
    {
        ok &= JSB_get_arraybufferview_dataptr(args[1], &count, &arg1);
    }
    ok &= seval_to_uint32(args[2], &arg2 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glBufferData((GLenum)arg0 , count, (GLvoid*)arg1 , (GLenum)arg2  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glBufferData)

// Arguments: GLenum, GLintptr, ArrayBufferView
// Ret value: void
static bool JSB_glBufferSubData(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 3, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0 = 0;
    int32_t arg1 = 0;
    void* arg2 = nullptr;
    GLsizei count = 0;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    if (args[2].isNumber())
    {
        count = args[2].toUint32();
    }
    else
    {
        ok &= JSB_get_arraybufferview_dataptr(args[2], &count, &arg2);
    }

    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glBufferSubData((GLenum)arg0 , (GLintptr)arg1 , count, (GLvoid*)arg2  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glBufferSubData)

// Arguments: GLenum
// Ret value: GLenum
static bool JSB_glCheckFramebufferStatus(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");
    GLenum ret_val;

    ret_val = glCheckFramebufferStatus((GLenum)arg0);
    s.rval().setUint32((uint32_t)ret_val);
    return true;
}
SE_BIND_FUNC(JSB_glCheckFramebufferStatus)

// Arguments: GLbitfield
// Ret value: void
static bool JSB_glClear(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glClear((GLbitfield)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glClear)

// Arguments: GLclampf, GLclampf, GLclampf, GLclampf
// Ret value: void
static bool JSB_glClearColor(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 4, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; int32_t arg1; int32_t arg2; int32_t arg3;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glClearColor((GLclampf)arg0 , (GLclampf)arg1 , (GLclampf)arg2 , (GLclampf)arg3  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glClearColor)

// Arguments: GLclampf
// Ret value: void
static bool JSB_glClearDepthf(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0;

    ok &= seval_to_int32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glClearDepthf((GLclampf)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glClearDepthf)

// Arguments: GLint
// Ret value: void
static bool JSB_glClearStencil(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0;

    ok &= seval_to_int32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glClearStencil((GLint)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glClearStencil)

// Arguments: GLboolean, GLboolean, GLboolean, GLboolean
// Ret value: void
static bool JSB_glColorMask(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 4, false, "Invalid number of arguments" );
    bool ok = true;
    uint16_t arg0; uint16_t arg1; uint16_t arg2; uint16_t arg3;

    ok &= seval_to_uint16(args[0], &arg0 );
    ok &= seval_to_uint16(args[1], &arg1 );
    ok &= seval_to_uint16(args[2], &arg2 );
    ok &= seval_to_uint16(args[3], &arg3 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glColorMask((GLboolean)arg0 , (GLboolean)arg1 , (GLboolean)arg2 , (GLboolean)arg3  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glColorMask)

// Arguments: GLuint
// Ret value: void
static bool JSB_glCompileShader(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glCompileShader((GLuint)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glCompileShader)

// Arguments: GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, ArrayBufferView
// Ret value: void
static bool JSB_glCompressedTexImage2D(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 8, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; int32_t arg1; uint32_t arg2; int32_t arg3; int32_t arg4; int32_t arg5; int32_t arg6; void* arg7;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_uint32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    ok &= seval_to_int32(args[4], &arg4 );
    ok &= seval_to_int32(args[5], &arg5 );
    ok &= seval_to_int32(args[6], &arg6 );
    GLsizei count;
    ok &= JSB_get_arraybufferview_dataptr(args[7], &count, &arg7);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glCompressedTexImage2D((GLenum)arg0 , (GLint)arg1 , (GLenum)arg2 , (GLsizei)arg3 , (GLsizei)arg4 , (GLint)arg5 , (GLsizei)arg6 , (GLvoid*)arg7  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glCompressedTexImage2D)

// Arguments: GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, ArrayBufferView
// Ret value: void
static bool JSB_glCompressedTexSubImage2D(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 9, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; int32_t arg1; int32_t arg2; int32_t arg3; int32_t arg4; int32_t arg5; uint32_t arg6; int32_t arg7; void* arg8;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    ok &= seval_to_int32(args[4], &arg4 );
    ok &= seval_to_int32(args[5], &arg5 );
    ok &= seval_to_uint32(args[6], &arg6 );
    ok &= seval_to_int32(args[7], &arg7 );
    GLsizei count;
    ok &= JSB_get_arraybufferview_dataptr(args[8], &count, &arg8);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glCompressedTexSubImage2D((GLenum)arg0 , (GLint)arg1 , (GLint)arg2 , (GLint)arg3 , (GLsizei)arg4 , (GLsizei)arg5 , (GLenum)arg6 , (GLsizei)arg7 , (GLvoid*)arg8  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glCompressedTexSubImage2D)

// Arguments: GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint
// Ret value: void
static bool JSB_glCopyTexImage2D(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 8, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; int32_t arg1; uint32_t arg2; int32_t arg3; int32_t arg4; int32_t arg5; int32_t arg6; int32_t arg7;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_uint32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    ok &= seval_to_int32(args[4], &arg4 );
    ok &= seval_to_int32(args[5], &arg5 );
    ok &= seval_to_int32(args[6], &arg6 );
    ok &= seval_to_int32(args[7], &arg7 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glCopyTexImage2D((GLenum)arg0 , (GLint)arg1 , (GLenum)arg2 , (GLint)arg3 , (GLint)arg4 , (GLsizei)arg5 , (GLsizei)arg6 , (GLint)arg7  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glCopyTexImage2D)

// Arguments: GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei
// Ret value: void
static bool JSB_glCopyTexSubImage2D(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 8, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; int32_t arg1; int32_t arg2; int32_t arg3; int32_t arg4; int32_t arg5; int32_t arg6; int32_t arg7;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    ok &= seval_to_int32(args[4], &arg4 );
    ok &= seval_to_int32(args[5], &arg5 );
    ok &= seval_to_int32(args[6], &arg6 );
    ok &= seval_to_int32(args[7], &arg7 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glCopyTexSubImage2D((GLenum)arg0 , (GLint)arg1 , (GLint)arg2 , (GLint)arg3 , (GLint)arg4 , (GLint)arg5 , (GLsizei)arg6 , (GLsizei)arg7  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glCopyTexSubImage2D)

// Arguments:
// Ret value: GLuint
static bool JSB_glCreateProgram(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 0, false, "Invalid number of arguments" );
    GLuint ret_val;

    ret_val = glCreateProgram();
    s.rval().setUint32((uint32_t)ret_val);
    return true;
}
SE_BIND_FUNC(JSB_glCreateProgram)

// Arguments: GLenum
// Ret value: GLuint
static bool JSB_glCreateShader(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");
    GLuint ret_val;

    ret_val = glCreateShader((GLenum)arg0);
    s.rval().setUint32((uint32_t)ret_val);
    return true;
}
SE_BIND_FUNC(JSB_glCreateShader)

// Arguments: GLenum
// Ret value: void
static bool JSB_glCullFace(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glCullFace((GLenum)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glCullFace)

// Arguments: GLuint
// Ret value: void
static bool JSB_glDeleteProgram(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glDeleteProgram((GLuint)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glDeleteProgram)

// Arguments: GLuint
// Ret value: void
static bool JSB_glDeleteShader(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glDeleteShader((GLuint)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glDeleteShader)

// Arguments: GLenum
// Ret value: void
static bool JSB_glDepthFunc(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glDepthFunc((GLenum)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glDepthFunc)

// Arguments: GLboolean
// Ret value: void
static bool JSB_glDepthMask(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint16_t arg0;

    ok &= seval_to_uint16(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glDepthMask((GLboolean)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glDepthMask)

// Arguments: GLclampf, GLclampf
// Ret value: void
static bool JSB_glDepthRangef(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; int32_t arg1;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glDepthRangef((GLclampf)arg0 , (GLclampf)arg1  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glDepthRangef)

// Arguments: GLuint, GLuint
// Ret value: void
static bool JSB_glDetachShader(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glDetachShader((GLuint)arg0 , (GLuint)arg1  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glDetachShader)

// Arguments: GLenum
// Ret value: void
static bool JSB_glDisable(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glDisable((GLenum)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glDisable)

// Arguments: GLuint
// Ret value: void
static bool JSB_glDisableVertexAttribArray(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glDisableVertexAttribArray((GLuint)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glDisableVertexAttribArray)

// Arguments: GLenum, GLint, GLsizei
// Ret value: void
static bool JSB_glDrawArrays(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 3, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; int32_t arg1; int32_t arg2;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glDrawArrays((GLenum)arg0 , (GLint)arg1 , (GLsizei)arg2  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glDrawArrays)

// Arguments: GLenum, GLsizei, GLenum, ArrayBufferView
// Ret value: void
static bool JSB_glDrawElements(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 4, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; int32_t arg1; uint32_t arg2; void* arg3 = nullptr;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_uint32(args[2], &arg2 );

    const se::Value& offsetVal = args[3];

    if (offsetVal.isNumber())
    {
        int offset = 0;
        ok &= seval_to_int32(offsetVal, &offset);
        arg3 = (void*)(intptr_t)offset;
    }
    else if (offsetVal.isObject())
    {
        GLsizei count;
        ok &= JSB_get_arraybufferview_dataptr(args[3], &count, &arg3);
    }

    SE_PRECONDITION2(ok, false, "Error processing arguments");
    JSB_GL_CHECK(glDrawElements((GLenum)arg0 , (GLsizei)arg1 , (GLenum)arg2 , (GLvoid*)arg3  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glDrawElements)

// Arguments: GLenum
// Ret value: void
static bool JSB_glEnable(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glEnable((GLenum)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glEnable)

// Arguments: GLuint
// Ret value: void
static bool JSB_glEnableVertexAttribArray(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glEnableVertexAttribArray((GLuint)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glEnableVertexAttribArray)

// Arguments:
// Ret value: void
static bool JSB_glFinish(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 0, false, "Invalid number of arguments" );
    JSB_GL_CHECK(glFinish( ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glFinish)

// Arguments:
// Ret value: void
static bool JSB_glFlush(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 0, false, "Invalid number of arguments" );
    JSB_GL_CHECK(glFlush( ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glFlush)

// Arguments: GLenum, GLenum, GLenum, GLuint
// Ret value: void
static bool JSB_glFramebufferRenderbuffer(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 4, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1; uint32_t arg2; uint32_t arg3;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    ok &= seval_to_uint32(args[2], &arg2 );
    ok &= seval_to_uint32(args[3], &arg3 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glFramebufferRenderbuffer((GLenum)arg0 , (GLenum)arg1 , (GLenum)arg2 , (GLuint)arg3  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glFramebufferRenderbuffer)

// Arguments: GLenum, GLenum, GLenum, GLuint, GLint
// Ret value: void
static bool JSB_glFramebufferTexture2D(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 5, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1; uint32_t arg2; uint32_t arg3; int32_t arg4;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    ok &= seval_to_uint32(args[2], &arg2 );
    ok &= seval_to_uint32(args[3], &arg3 );
    ok &= seval_to_int32(args[4], &arg4 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glFramebufferTexture2D((GLenum)arg0 , (GLenum)arg1 , (GLenum)arg2 , (GLuint)arg3 , (GLint)arg4  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glFramebufferTexture2D)

// Arguments: GLenum
// Ret value: void
static bool JSB_glFrontFace(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glFrontFace((GLenum)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glFrontFace)

// Arguments: GLenum
// Ret value: void
static bool JSB_glGenerateMipmap(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glGenerateMipmap((GLenum)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glGenerateMipmap)

// Arguments: GLuint, char*
// Ret value: int
static bool JSB_glGetAttribLocation(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; std::string arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_std_string(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");
    int ret_val = glGetAttribLocation((GLuint)arg0 , arg1.c_str());
    JSB_GL_CHECK_ERROR();
    s.rval().setInt32(ret_val);
    return true;
}
SE_BIND_FUNC(JSB_glGetAttribLocation)

// Arguments:
// Ret value: GLenum
static bool JSB_glGetError(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 0, false, "Invalid number of arguments" );
    GLenum ret_val;

    ret_val = glGetError();
    s.rval().setUint32((uint32_t)ret_val);
    return true;
}
SE_BIND_FUNC(JSB_glGetError)

// Arguments: GLuint, char*
// Ret value: int
static bool JSB_glGetUniformLocation(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; std::string arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_std_string(args[1], &arg1 );

    SE_PRECONDITION2(ok, false, "Error processing arguments");
    int ret_val;

    ret_val = glGetUniformLocation((GLuint)arg0 , arg1.c_str());
    JSB_GL_CHECK_ERROR();
    s.rval().setInt32(ret_val);
    return true;
}
SE_BIND_FUNC(JSB_glGetUniformLocation)

// Arguments: GLenum, GLenum
// Ret value: void
static bool JSB_glHint(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glHint((GLenum)arg0 , (GLenum)arg1  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glHint)

// Arguments: GLuint
// Ret value: GLboolean
static bool JSB_glIsBuffer(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");
    GLboolean ret_val;

    ret_val = glIsBuffer((GLuint)arg0);
    s.rval().setInt32((int32_t)ret_val);
    return true;
}
SE_BIND_FUNC(JSB_glIsBuffer)

// Arguments: GLenum
// Ret value: GLboolean
static bool JSB_glIsEnabled(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");
    GLboolean ret_val;

    ret_val = glIsEnabled((GLenum)arg0);
    s.rval().setInt32((int32_t)ret_val);
    return true;
}
SE_BIND_FUNC(JSB_glIsEnabled)

// Arguments: GLuint
// Ret value: GLboolean
static bool JSB_glIsFramebuffer(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");
    GLboolean ret_val;

    ret_val = glIsFramebuffer((GLuint)arg0);
    s.rval().setInt32((int32_t)ret_val);
    return true;
}
SE_BIND_FUNC(JSB_glIsFramebuffer)

// Arguments: GLuint
// Ret value: GLboolean
static bool JSB_glIsProgram(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");
    GLboolean ret_val;

    ret_val = glIsProgram((GLuint)arg0);
    s.rval().setInt32((int32_t)ret_val);
    return true;
}
SE_BIND_FUNC(JSB_glIsProgram)

// Arguments: GLuint
// Ret value: GLboolean
static bool JSB_glIsRenderbuffer(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");
    GLboolean ret_val;

    ret_val = glIsRenderbuffer((GLuint)arg0);
    s.rval().setInt32((int32_t)ret_val);
    return true;
}
SE_BIND_FUNC(JSB_glIsRenderbuffer)

// Arguments: GLuint
// Ret value: GLboolean
static bool JSB_glIsShader(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");
    GLboolean ret_val;

    ret_val = glIsShader((GLuint)arg0);
    s.rval().setInt32((int32_t)ret_val);
    return true;
}
SE_BIND_FUNC(JSB_glIsShader)

// Arguments: GLuint
// Ret value: GLboolean
static bool JSB_glIsTexture(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");
    GLboolean ret_val;

    ret_val = glIsTexture((GLuint)arg0);
    s.rval().setInt32((int32_t)ret_val);
    return true;
}
SE_BIND_FUNC(JSB_glIsTexture)

// Arguments: GLfloat
// Ret value: void
static bool JSB_glLineWidth(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0;

    ok &= seval_to_int32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glLineWidth((GLfloat)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glLineWidth)

// Arguments: GLuint
// Ret value: void
static bool JSB_glLinkProgram(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glLinkProgram((GLuint)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glLinkProgram)

// Arguments: GLenum, GLint
// Ret value: void
static bool JSB_glPixelStorei(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; int32_t arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    if (arg0 == GL_UNPACK_FLIP_Y_WEBGL)
    {
        SE_LOGE("cjh FIXME: support GL_UNPACK_FLIP_Y_WEBGL\n");
        return true;
    }

    if (arg0 == GL_UNPACK_PREMULTIPLY_ALPHA_WEBGL)
    {
        SE_LOGE("cjh FIXME: support GL_UNPACK_PREMULTIPLY_ALPHA_WEBGL\n");
        return true;
    }

    JSB_GL_CHECK(glPixelStorei((GLenum)arg0 , (GLint)arg1  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glPixelStorei)

// Arguments: GLfloat, GLfloat
// Ret value: void
static bool JSB_glPolygonOffset(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; int32_t arg1;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glPolygonOffset((GLfloat)arg0 , (GLfloat)arg1  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glPolygonOffset)

// Arguments: GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, ArrayBufferView
// Ret value: void
static bool JSB_glReadPixels(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 7, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; int32_t arg1; int32_t arg2; int32_t arg3; uint32_t arg4; uint32_t arg5; void* arg6;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    ok &= seval_to_uint32(args[4], &arg4 );
    ok &= seval_to_uint32(args[5], &arg5 );
    GLsizei count;
    ok &= JSB_get_arraybufferview_dataptr(args[6], &count, &arg6);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glReadPixels((GLint)arg0 , (GLint)arg1 , (GLsizei)arg2 , (GLsizei)arg3 , (GLenum)arg4 , (GLenum)arg5 , (GLvoid*)arg6  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glReadPixels)

// Arguments:
// Ret value: void
static bool JSB_glReleaseShaderCompiler(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 0, false, "Invalid number of arguments" );
    JSB_GL_CHECK(glReleaseShaderCompiler( ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glReleaseShaderCompiler)

// Arguments: GLenum, GLenum, GLsizei, GLsizei
// Ret value: void
static bool JSB_glRenderbufferStorage(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 4, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1; int32_t arg2; int32_t arg3;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glRenderbufferStorage((GLenum)arg0 , (GLenum)arg1 , (GLsizei)arg2 , (GLsizei)arg3  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glRenderbufferStorage)

// Arguments: GLclampf, GLboolean
// Ret value: void
static bool JSB_glSampleCoverage(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; uint16_t arg1;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_uint16(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glSampleCoverage((GLclampf)arg0 , (GLboolean)arg1  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glSampleCoverage)

// Arguments: GLint, GLint, GLsizei, GLsizei
// Ret value: void
static bool JSB_glScissor(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 4, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; int32_t arg1; int32_t arg2; int32_t arg3;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glScissor((GLint)arg0 , (GLint)arg1 , (GLsizei)arg2 , (GLsizei)arg3  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glScissor)

// Arguments: GLenum, GLint, GLuint
// Ret value: void
static bool JSB_glStencilFunc(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 3, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; int32_t arg1; uint32_t arg2;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_uint32(args[2], &arg2 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glStencilFunc((GLenum)arg0 , (GLint)arg1 , (GLuint)arg2  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glStencilFunc)

// Arguments: GLenum, GLenum, GLint, GLuint
// Ret value: void
static bool JSB_glStencilFuncSeparate(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 4, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1; int32_t arg2; uint32_t arg3;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_uint32(args[3], &arg3 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glStencilFuncSeparate((GLenum)arg0 , (GLenum)arg1 , (GLint)arg2 , (GLuint)arg3  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glStencilFuncSeparate)

// Arguments: GLuint
// Ret value: void
static bool JSB_glStencilMask(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glStencilMask((GLuint)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glStencilMask)

// Arguments: GLenum, GLuint
// Ret value: void
static bool JSB_glStencilMaskSeparate(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glStencilMaskSeparate((GLenum)arg0 , (GLuint)arg1  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glStencilMaskSeparate)

// Arguments: GLenum, GLenum, GLenum
// Ret value: void
static bool JSB_glStencilOp(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 3, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1; uint32_t arg2;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    ok &= seval_to_uint32(args[2], &arg2 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glStencilOp((GLenum)arg0 , (GLenum)arg1 , (GLenum)arg2  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glStencilOp)

// Arguments: GLenum, GLenum, GLenum, GLenum
// Ret value: void
static bool JSB_glStencilOpSeparate(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 4, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1; uint32_t arg2; uint32_t arg3;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    ok &= seval_to_uint32(args[2], &arg2 );
    ok &= seval_to_uint32(args[3], &arg3 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glStencilOpSeparate((GLenum)arg0 , (GLenum)arg1 , (GLenum)arg2 , (GLenum)arg3  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glStencilOpSeparate)

// Arguments: GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, ArrayBufferView
// Ret value: void
static bool JSB_glTexImage2D(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 9, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; int32_t arg1; int32_t arg2; int32_t arg3; int32_t arg4; int32_t arg5; uint32_t arg6; uint32_t arg7; void* arg8;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    ok &= seval_to_int32(args[4], &arg4 );
    ok &= seval_to_int32(args[5], &arg5 );
    ok &= seval_to_uint32(args[6], &arg6 );
    ok &= seval_to_uint32(args[7], &arg7 );
    GLsizei count;
    ok &= JSB_get_arraybufferview_dataptr(args[8], &count, &arg8);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glTexImage2D((GLenum)arg0 , (GLint)arg1 , (GLint)arg2 , (GLsizei)arg3 , (GLsizei)arg4 , (GLint)arg5 , (GLenum)arg6 , (GLenum)arg7 , (GLvoid*)arg8  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glTexImage2D)

// Arguments: GLenum, GLenum, GLfloat
// Ret value: void
static bool JSB_glTexParameterf(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 3, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1; int32_t arg2;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glTexParameterf((GLenum)arg0 , (GLenum)arg1 , (GLfloat)arg2  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glTexParameterf)

// Arguments: GLenum, GLenum, GLint
// Ret value: void
static bool JSB_glTexParameteri(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 3, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; uint32_t arg1; int32_t arg2;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glTexParameteri((GLenum)arg0 , (GLenum)arg1 , (GLint)arg2  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glTexParameteri)

// Arguments: GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, ArrayBufferView
// Ret value: void
static bool JSB_glTexSubImage2D(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 9, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; int32_t arg1; int32_t arg2; int32_t arg3; int32_t arg4; int32_t arg5; uint32_t arg6; uint32_t arg7; void* arg8;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    ok &= seval_to_int32(args[4], &arg4 );
    ok &= seval_to_int32(args[5], &arg5 );
    ok &= seval_to_uint32(args[6], &arg6 );
    ok &= seval_to_uint32(args[7], &arg7 );
    GLsizei count;
    ok &= JSB_get_arraybufferview_dataptr(args[8], &count, &arg8);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glTexSubImage2D((GLenum)arg0 , (GLint)arg1 , (GLint)arg2 , (GLint)arg3 , (GLsizei)arg4 , (GLsizei)arg5 , (GLenum)arg6 , (GLenum)arg7 , (GLvoid*)arg8  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glTexSubImage2D)

// Arguments: GLint, GLfloat
// Ret value: void
static bool JSB_glUniform1f(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; int32_t arg1;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniform1f((GLint)arg0 , (GLfloat)arg1  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniform1f)

// Arguments: GLint, GLsizei, TypedArray/Sequence
// Ret value: void
static bool JSB_glUniform1fv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0;;

    ok &= seval_to_int32(args[0], &arg0 );
    GLData<float> data;
    ok &= JSB_jsval_typedarray_to_data<float>(args[1], data);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniform1fv((GLint)arg0 , (GLsizei)data.count() , (GLfloat*)data.data()));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniform1fv)

// Arguments: GLint, GLint
// Ret value: void
static bool JSB_glUniform1i(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; int32_t arg1;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniform1i((GLint)arg0 , (GLint)arg1  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniform1i)

// Arguments: GLint, GLsizei, TypedArray/Sequence
// Ret value: void
static bool JSB_glUniform1iv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0;

    ok &= seval_to_int32(args[0], &arg0 );
    GLData<int32_t> data;
    ok &= JSB_jsval_typedarray_to_data<int32_t>(args[1], data);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniform1iv((GLint)arg0 , (GLsizei)data.count() , (GLint*)data.data()));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniform1iv)

// Arguments: GLint, GLfloat, GLfloat
// Ret value: void
static bool JSB_glUniform2f(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 3, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; int32_t arg1; int32_t arg2;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniform2f((GLint)arg0 , (GLfloat)arg1 , (GLfloat)arg2  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniform2f)

// Arguments: GLint, GLsizei, TypedArray/Sequence
// Ret value: void
static bool JSB_glUniform2fv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0;

    ok &= seval_to_int32(args[0], &arg0 );
    GLData<float> data;
    ok &= JSB_jsval_typedarray_to_data<float>(args[1], data);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniform2fv((GLint)arg0 , (GLsizei)(data.count()/2) , (GLfloat*)data.data() ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniform2fv)

// Arguments: GLint, GLint, GLint
// Ret value: void
static bool JSB_glUniform2i(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 3, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; int32_t arg1; int32_t arg2;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniform2i((GLint)arg0 , (GLint)arg1 , (GLint)arg2  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniform2i)

// Arguments: GLint, GLsizei, TypedArray/Sequence
// Ret value: void
static bool JSB_glUniform2iv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0;

    ok &= seval_to_int32(args[0], &arg0 );
    GLData<int32_t> data;
    ok &= JSB_jsval_typedarray_to_data<int32_t>(args[1], data);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniform2iv((GLint)arg0 , (GLsizei)(data.count()/2) , (GLint*)data.data()));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniform2iv)

// Arguments: GLint, GLfloat, GLfloat, GLfloat
// Ret value: void
static bool JSB_glUniform3f(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 4, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; int32_t arg1; int32_t arg2; int32_t arg3;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniform3f((GLint)arg0 , (GLfloat)arg1 , (GLfloat)arg2 , (GLfloat)arg3  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniform3f)

// Arguments: GLint, GLsizei, TypedArray/Sequence
// Ret value: void
static bool JSB_glUniform3fv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0;

    ok &= seval_to_int32(args[0], &arg0 );
    GLData<float> data;
    ok &= JSB_jsval_typedarray_to_data<float>(args[1], data);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniform3fv((GLint)arg0 , (GLsizei)(data.count()/3) , (GLfloat*)data.data()));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniform3fv)

// Arguments: GLint, GLint, GLint, GLint
// Ret value: void
static bool JSB_glUniform3i(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 4, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; int32_t arg1; int32_t arg2; int32_t arg3;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniform3i((GLint)arg0 , (GLint)arg1 , (GLint)arg2 , (GLint)arg3  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniform3i)

// Arguments: GLint, GLsizei, TypedArray/Sequence
// Ret value: void
static bool JSB_glUniform3iv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0;

    ok &= seval_to_int32(args[0], &arg0 );
    GLData<int32_t> data;
    ok &= JSB_jsval_typedarray_to_data<int32_t>(args[1], data);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniform3iv((GLint)arg0 , (GLsizei)(data.count()/3) , (GLint*)data.data()));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniform3iv)

// Arguments: GLint, GLfloat, GLfloat, GLfloat, GLfloat
// Ret value: void
static bool JSB_glUniform4f(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 5, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; int32_t arg1; int32_t arg2; int32_t arg3; int32_t arg4;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    ok &= seval_to_int32(args[4], &arg4 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniform4f((GLint)arg0 , (GLfloat)arg1 , (GLfloat)arg2 , (GLfloat)arg3 , (GLfloat)arg4  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniform4f)

// Arguments: GLint, GLsizei, TypedArray/Sequence
// Ret value: void
static bool JSB_glUniform4fv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0;;

    ok &= seval_to_int32(args[0], &arg0 );
    GLData<float> data;
    ok &= JSB_jsval_typedarray_to_data<float>(args[1], data);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniform4fv((GLint)arg0 , (GLsizei)(data.count()/4) , (GLfloat*)data.data()));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniform4fv)

// Arguments: GLint, GLint, GLint, GLint, GLint
// Ret value: void
static bool JSB_glUniform4i(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 5, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; int32_t arg1; int32_t arg2; int32_t arg3; int32_t arg4;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    ok &= seval_to_int32(args[4], &arg4 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniform4i((GLint)arg0 , (GLint)arg1 , (GLint)arg2 , (GLint)arg3 , (GLint)arg4  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniform4i)

// Arguments: GLint, GLsizei, TypedArray/Sequence
// Ret value: void
static bool JSB_glUniform4iv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0;

    ok &= seval_to_int32(args[0], &arg0 );
    GLData<int32_t> data;
    ok &= JSB_jsval_typedarray_to_data<int32_t>(args[1], data);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniform4iv((GLint)arg0 , (GLsizei)(data.count()/4) , (GLint*)data.data()));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniform4iv)

// Arguments: GLint, GLboolean, TypedArray/Sequence
// Ret value: void
static bool JSB_glUniformMatrix2fv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 3, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; uint16_t arg1;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_uint16(args[1], &arg1 );
    GLData<float> data;
    ok &= JSB_jsval_typedarray_to_data<float>(args[2], data);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniformMatrix2fv(arg0, (GLsizei)(data.count()/4), (GLboolean)arg1 , (GLfloat*)data.data()));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniformMatrix2fv)

// Arguments: GLint, GLboolean, TypedArray/Sequence
// Ret value: void
static bool JSB_glUniformMatrix3fv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 3, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; uint16_t arg1;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_uint16(args[1], &arg1 );
    GLData<float> data;
    ok &= JSB_jsval_typedarray_to_data<float>(args[2], data);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniformMatrix3fv(arg0, (GLsizei)(data.count()/9), (GLboolean)arg1 , (GLfloat*)data.data()));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniformMatrix3fv)

// Arguments: GLint, GLboolean, TypedArray/Sequence
// Ret value: void
static bool JSB_glUniformMatrix4fv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 3, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; uint16_t arg1;;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_uint16(args[1], &arg1 );
    GLData<float> data;
    ok &= JSB_jsval_typedarray_to_data<float>(args[2], data);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUniformMatrix4fv(arg0, (GLsizei)(data.count()/16), (GLboolean)arg1 , (GLfloat*)data.data()));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUniformMatrix4fv)

// Arguments: GLuint
// Ret value: void
static bool JSB_glUseProgram(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glUseProgram((GLuint)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glUseProgram)

// Arguments: GLuint
// Ret value: void
static bool JSB_glValidateProgram(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 1, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glValidateProgram((GLuint)arg0  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glValidateProgram)

// Arguments: GLuint, GLfloat
// Ret value: void
static bool JSB_glVertexAttrib1f(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; int32_t arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glVertexAttrib1f((GLuint)arg0 , (GLfloat)arg1  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glVertexAttrib1f)

// Arguments: GLuint, TypedArray/Sequence
// Ret value: void
static bool JSB_glVertexAttrib1fv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    GLData<float> data;
    ok &= JSB_jsval_typedarray_to_data<float>(args[1], data);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glVertexAttrib1fv((GLuint)arg0 , (GLfloat*)data.data()));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glVertexAttrib1fv)

// Arguments: GLuint, GLfloat, GLfloat
// Ret value: void
static bool JSB_glVertexAttrib2f(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 3, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; int32_t arg1; int32_t arg2;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glVertexAttrib2f((GLuint)arg0 , (GLfloat)arg1 , (GLfloat)arg2  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glVertexAttrib2f)

// Arguments: GLuint, TypedArray/Sequence
// Ret value: void
static bool JSB_glVertexAttrib2fv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    GLData<float> data;
    ok &= JSB_jsval_typedarray_to_data<float>(args[1], data);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glVertexAttrib2fv((GLuint)arg0 , (GLfloat*)data.data()  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glVertexAttrib2fv)

// Arguments: GLuint, GLfloat, GLfloat, GLfloat
// Ret value: void
static bool JSB_glVertexAttrib3f(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 4, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; int32_t arg1; int32_t arg2; int32_t arg3;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glVertexAttrib3f((GLuint)arg0 , (GLfloat)arg1 , (GLfloat)arg2 , (GLfloat)arg3  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glVertexAttrib3f)

// Arguments: GLuint, TypedArray/Sequence
// Ret value: void
static bool JSB_glVertexAttrib3fv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    GLData<float> data;
    ok &= JSB_jsval_typedarray_to_data<float>(args[1], data);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glVertexAttrib3fv((GLuint)arg0 , (GLfloat*)data.data()));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glVertexAttrib3fv)

// Arguments: GLuint, GLfloat, GLfloat, GLfloat, GLfloat
// Ret value: void
static bool JSB_glVertexAttrib4f(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 5, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; int32_t arg1; int32_t arg2; int32_t arg3; int32_t arg4;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    ok &= seval_to_int32(args[4], &arg4 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glVertexAttrib4f((GLuint)arg0 , (GLfloat)arg1 , (GLfloat)arg2 , (GLfloat)arg3 , (GLfloat)arg4  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glVertexAttrib4f)

// Arguments: GLuint, TypedArray/Sequence
// Ret value: void
static bool JSB_glVertexAttrib4fv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 2, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    GLData<float> data;
    ok &= JSB_jsval_typedarray_to_data<float>(args[1], data);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glVertexAttrib4fv((GLuint)arg0 , (GLfloat*)data.data()));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glVertexAttrib4fv)

// Arguments: GLuint, GLint, GLenum, GLboolean, GLsizei, GLvoid*
// Ret value: void
static bool JSB_glVertexAttribPointer(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 6, false, "Invalid number of arguments" );
    bool ok = true;
    uint32_t arg0; int32_t arg1; uint32_t arg2; uint16_t arg3; int32_t arg4; int32_t arg5;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_uint32(args[2], &arg2 );
    ok &= seval_to_uint16(args[3], &arg3 );
    ok &= seval_to_int32(args[4], &arg4 );
    ok &= seval_to_int32(args[5], &arg5 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glVertexAttribPointer((GLuint)arg0 , (GLint)arg1 , (GLenum)arg2 , (GLboolean)arg3 , (GLsizei)arg4 , (GLvoid*)arg5  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glVertexAttribPointer)

// Arguments: GLint, GLint, GLsizei, GLsizei
// Ret value: void
static bool JSB_glViewport(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2( argc == 4, false, "Invalid number of arguments" );
    bool ok = true;
    int32_t arg0; int32_t arg1; int32_t arg2; int32_t arg3;

    ok &= seval_to_int32(args[0], &arg0 );
    ok &= seval_to_int32(args[1], &arg1 );
    ok &= seval_to_int32(args[2], &arg2 );
    ok &= seval_to_int32(args[3], &arg3 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glViewport((GLint)arg0 , (GLint)arg1 , (GLsizei)arg2 , (GLsizei)arg3  ));
    s.rval().setUndefined();
    return true;
}
SE_BIND_FUNC(JSB_glViewport)


// Helper functions that link "glGenXXXs" (OpenGL ES 2.0 spec), with "gl.createXXX" (WebGL spec)
static bool JSB_glGenTextures(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 0, false, "Invalid number of arguments" );

    GLuint texture;
    JSB_GL_CHECK(glGenTextures(1, &texture));

    s.rval().setUint32(texture);
    return true;
}
SE_BIND_FUNC(JSB_glGenTextures)

static bool JSB_glGenBuffers(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 0, false, "Invalid number of arguments" );

    GLuint buffer;
    JSB_GL_CHECK(glGenBuffers(1, &buffer));
    s.rval().setUint32(buffer);
    return true;
}
SE_BIND_FUNC(JSB_glGenBuffers)

static bool JSB_glGenRenderbuffers(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 0, false, "Invalid number of arguments" );

    GLuint renderbuffers;
    JSB_GL_CHECK(glGenRenderbuffers(1, &renderbuffers));
    s.rval().setUint32(renderbuffers);
    return true;
}
SE_BIND_FUNC(JSB_glGenRenderbuffers)

static bool JSB_glGenFramebuffers(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 0, false, "Invalid number of arguments" );

    GLuint framebuffers;
    JSB_GL_CHECK(glGenFramebuffers(1, &framebuffers));
    s.rval().setUint32(framebuffers);
    return true;
}
SE_BIND_FUNC(JSB_glGenFramebuffers)

static bool JSB_glDeleteTextures(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 1, false, "Invalid number of arguments" );

    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glDeleteTextures(1, &arg0));

    return true;
}
SE_BIND_FUNC(JSB_glDeleteTextures)

static bool JSB_glDeleteBuffers(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 1, false, "Invalid number of arguments" );

    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glDeleteBuffers(1, &arg0));

    return true;
}
SE_BIND_FUNC(JSB_glDeleteBuffers)

static bool JSB_glDeleteRenderbuffers(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 1, false, "Invalid number of arguments" );

    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    JSB_GL_CHECK(glDeleteRenderbuffers(1, &arg0));

    return true;
}
SE_BIND_FUNC(JSB_glDeleteRenderbuffers)

static bool JSB_glDeleteFramebuffers(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 1, false, "Invalid number of arguments" );

    bool ok = true;
    uint32_t arg0;

    if (args[0].isNullOrUndefined())
    {
        arg0 = __defaultFbo;
    }
    else
    {
        ok &= seval_to_uint32(args[0], &arg0 );
        SE_PRECONDITION2(ok, false, "Error processing arguments");
    }

    JSB_GL_CHECK(glDeleteFramebuffers(1, &arg0));

    return true;
}
SE_BIND_FUNC(JSB_glDeleteFramebuffers)

static bool JSB_glShaderSource(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 2, false, "Invalid number of arguments" );

    bool ok = true;
    uint32_t arg0; std::string shaderSource;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_std_string(args[1], &shaderSource);
    SE_PRECONDITION2(ok, false, "Error processing arguments");

#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    shaderSource = std::regex_replace(shaderSource, std::regex("precision\\s+(lowp|mediump|highp)\\s+float\\s*?;"), "");
    shaderSource = std::regex_replace(shaderSource, std::regex("\\s(lowp|mediump|highp)\\s"), " ");
#endif

    const GLchar* sources[] = { shaderSource.c_str() };
    JSB_GL_CHECK(glShaderSource(arg0, 1, sources, nullptr));

    return true;
}
SE_BIND_FUNC(JSB_glShaderSource)

static bool JSB_glGetShaderiv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 2, false, "Invalid number of arguments" );

    bool ok = true;
    uint32_t arg0, arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    GLint ret = 0;
    JSB_GL_CHECK(glGetShaderiv(arg0, arg1, &ret));

    if (arg1 == GL_DELETE_STATUS || arg1 == GL_COMPILE_STATUS)
    {
        s.rval().setBoolean(ret != 0);
    }
    else
    {
        s.rval().setInt32(ret);
    }
    return true;
}
SE_BIND_FUNC(JSB_glGetShaderiv)

static bool JSB_glGetProgramiv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 2, false, "Invalid number of arguments" );

    bool ok = true;
    uint32_t arg0, arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    GLint ret;
    JSB_GL_CHECK(glGetProgramiv(arg0, arg1, &ret));
    s.rval().setInt32(ret);
    return true;
}
SE_BIND_FUNC(JSB_glGetProgramiv)

static bool JSB_glGetProgramInfoLog(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 1, false, "Invalid number of arguments" );

    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    GLsizei length;
    JSB_GL_CHECK(glGetProgramiv(arg0, GL_INFO_LOG_LENGTH, &length));
    GLchar* src = new (std::nothrow) GLchar[length];
    JSB_GL_CHECK(glGetProgramInfoLog(arg0, length, NULL, src));

    s.rval().setString(src);
    CC_SAFE_DELETE_ARRAY(src);
    return true;
}
SE_BIND_FUNC(JSB_glGetProgramInfoLog)

// DOMString? getShaderInfoLog(WebGLShader? shader);
static bool JSB_glGetShaderInfoLog(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 1, false, "Invalid number of arguments" );

    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    GLsizei length;
    JSB_GL_CHECK(glGetShaderiv(arg0, GL_INFO_LOG_LENGTH, &length));
    GLchar* src = new (std::nothrow) GLchar[length];
    JSB_GL_CHECK(glGetShaderInfoLog(arg0, length, NULL, src));

    s.rval().setString(src);
    CC_SAFE_DELETE_ARRAY(src);
    return true;
}
SE_BIND_FUNC(JSB_glGetShaderInfoLog)

// DOMString? getShaderSource(WebGLShader? shader);
static bool JSB_glGetShaderSource(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 1, false, "Invalid number of arguments" );

    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    GLsizei length;
    JSB_GL_CHECK(glGetShaderiv(arg0, GL_SHADER_SOURCE_LENGTH, &length));
    GLchar* src = new (std::nothrow) GLchar[length];
    JSB_GL_CHECK(glGetShaderSource(arg0, length, NULL, src));

    s.rval().setString(src);
    CC_SAFE_DELETE_ARRAY(src);
    return true;
}
SE_BIND_FUNC(JSB_glGetShaderSource)

//  interface WebGLActiveInfo {
//      readonly attribute GLint size;
//      readonly attribute GLenum type;
//      readonly attribute DOMString name;
// WebGLActiveInfo? getActiveAttrib(WebGLProgram? program, GLuint index);
static bool JSB_glGetActiveAttrib(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 2, false, "Invalid number of arguments" );

    bool ok = true;
    uint32_t arg0, arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    GLsizei length;
    JSB_GL_CHECK(glGetProgramiv(arg0, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length));
    GLchar* buffer = new (std::nothrow) GLchar[length];
    GLint size = -1;
    GLenum type = -1;

    JSB_GL_CHECK(glGetActiveAttrib(arg0, arg1, length, NULL, &size, &type, buffer));

    se::HandleObject object(se::Object::createPlainObject());
    object->setProperty("size", se::Value((int32_t)size));
    object->setProperty("type", se::Value((int32_t)type));
    object->setProperty("name", se::Value((char*)buffer));
    s.rval().setObject(object.get());

    CC_SAFE_DELETE_ARRAY(buffer);

    return true;
}
SE_BIND_FUNC(JSB_glGetActiveAttrib)


//  interface WebGLActiveInfo {
//      readonly attribute GLint size;
//      readonly attribute GLenum type;
//      readonly attribute DOMString name;
//  };
// WebGLActiveInfo? getActiveUniform(WebGLProgram? program, GLuint index);
static bool JSB_glGetActiveUniform(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 2, false, "Invalid number of arguments" );

    bool ok = true;
    uint32_t arg0, arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    GLsizei length;
    JSB_GL_CHECK(glGetProgramiv(arg0, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length));
    GLchar* buffer = new (std::nothrow) GLchar[length];
    GLint size = -1;
    GLenum type = -1;

    JSB_GL_CHECK(glGetActiveUniform(arg0, arg1, length, NULL, &size, &type, buffer));

    se::HandleObject object(se::Object::createPlainObject());
    object->setProperty("size", se::Value((int32_t)size));
    object->setProperty("type", se::Value((int32_t)type));
    object->setProperty("name", se::Value((char*)buffer));
    s.rval().setObject(object.get());

    CC_SAFE_DELETE_ARRAY(buffer);
    return true;
}
SE_BIND_FUNC(JSB_glGetActiveUniform)

// sequence<WebGLShader>? getAttachedShaders(WebGLProgram? program);
static bool JSB_glGetAttachedShaders(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 1, false, "Invalid number of arguments" );

    bool ok = true;
    uint32_t arg0;

    ok &= seval_to_uint32(args[0], &arg0 );
    SE_PRECONDITION2(ok, false, "Error processing arguments");

    GLsizei length;
    JSB_GL_CHECK(glGetProgramiv(arg0, GL_ATTACHED_SHADERS, &length));
    GLuint* buffer = new (std::nothrow) GLuint[length];
    memset(buffer, 0, length * sizeof(GLuint));
    //Fix bug 2448, it seems that glGetAttachedShaders will crash if we send NULL to the third parameter (eg Windows), same as in lua binding
    GLsizei realShaderCount = 0;
    JSB_GL_CHECK(glGetAttachedShaders(arg0, length, &realShaderCount, buffer));

    se::HandleObject jsobj(se::Object::createArrayObject(length));
    for( int i=0; i<length; i++)
    {
        jsobj->setArrayElement(i, se::Value(buffer[i]));
    }

    s.rval().setObject(jsobj.get());
    CC_SAFE_DELETE_ARRAY(buffer);
    return true;

}
SE_BIND_FUNC(JSB_glGetAttachedShaders)

// sequence<DOMString>? getSupportedExtensions();
static bool JSB_glGetSupportedExtensions(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 0, false, "Invalid number of arguments" );

    const GLubyte *extensions = glGetString(GL_EXTENSIONS);

    se::HandleObject jsobj(se::Object::createArrayObject(1));

    // copy, to be able to add '\0'
    size_t len = strlen((char*)extensions);
    GLubyte* copy = new (std::nothrow) GLubyte[len+1];
    copy[len] = '\0';
    strncpy((char*)copy, (const char*)extensions, len );

    size_t start_extension = 0;
    uint32_t element = 0;
    for( size_t i=0; i<len+1; i++) {
        if( copy[i]==' ' || copy[i]==',' || i==len ) {
            copy[i] = 0;

            jsobj->setArrayElement(element, se::Value((const char*)&copy[start_extension]));

            start_extension = i+1;
            ++element;
            ++i;
        }
    }

    s.rval().setObject(jsobj.get());
    CC_SAFE_DELETE_ARRAY(copy);
    return true;

}
SE_BIND_FUNC(JSB_glGetSupportedExtensions)

// any getTexParameter(GLenum target, GLenum pname);
static bool JSB_glGetTexParameterfv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 2, false,"JSB_glGetTexParameterfv: Invalid number of arguments" );

    bool ok = true;
    uint32_t arg0, arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );

    SE_PRECONDITION2(ok, false, "JSB_glGetTexParameterfv: Error processing arguments");

    GLfloat param;
    JSB_GL_CHECK(glGetTexParameterfv(arg0, arg1, &param));

    s.rval().setFloat(param);
    return true;
}
SE_BIND_FUNC(JSB_glGetTexParameterfv)

// any getUniform(WebGLProgram? program, WebGLUniformLocation? location);
static bool JSB_glGetUniformfv(se::State& s) {
    const auto& args = s.args();
    int argc = (int)args.size();
    SE_PRECONDITION2(argc == 2, false,"JSB_glGetUniformfv: Invalid number of arguments" );

    bool ok = true;
    uint32_t arg0, arg1;

    ok &= seval_to_uint32(args[0], &arg0 );
    ok &= seval_to_uint32(args[1], &arg1 );

    SE_PRECONDITION2(ok, false, "JSB_glGetUniformfv: Error processing arguments");

    GLint activeUniforms;
    JSB_GL_CHECK(glGetProgramiv(arg0, GL_ACTIVE_UNIFORMS, &activeUniforms));

    GLsizei length;
    JSB_GL_CHECK(glGetProgramiv(arg0, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length));
    GLchar* namebuffer = new (std::nothrow) GLchar[length+1];
    GLint size = -1;
    GLenum type = -1;

    bool isLocationFound = false;
    for (int i = 0; i  <  activeUniforms; ++i)
    {
        JSB_GL_CHECK(glGetActiveUniform(arg0, i, length, NULL, &size, &type, namebuffer));
        if(arg1 == glGetUniformLocation(arg0, namebuffer))
        {
            isLocationFound = true;
            break;
        }
    }

    if(!isLocationFound)
    {
        size = -1;
        type = -1;
    }
    CC_SAFE_DELETE_ARRAY(namebuffer);

    int usize = 0;
    int utype = 0;
    switch(type) {

            // float
        case GL_FLOAT:
            usize = 1;
            utype = GL_FLOAT;
            break;
        case GL_FLOAT_MAT2:
            usize = 2 * 2;
            utype = GL_FLOAT;
            break;
        case GL_FLOAT_MAT3:
            usize = 3 * 3;
            utype = GL_FLOAT;
            break;
        case GL_FLOAT_MAT4:
            usize = 4 * 4;
            utype = GL_FLOAT;
            break;
        case GL_FLOAT_VEC2:
            usize = 2;
            utype = GL_FLOAT;
            break;
        case GL_FLOAT_VEC3:
            usize = 3;
            utype = GL_FLOAT;
            break;
        case GL_FLOAT_VEC4:
            usize = 4;
            utype = GL_FLOAT;
            break;

            // int
        case GL_INT:
            usize = 1;
            utype = GL_INT;
            break;
        case GL_INT_VEC2:
            usize = 2;
            utype = GL_INT;
            break;
        case GL_INT_VEC3:
            usize = 3;
            utype = GL_INT;
            break;
        case GL_INT_VEC4:
            usize = 4;
            utype = GL_INT;
            break;

        default:
            SE_REPORT_ERROR("glGetUniformfv: Uniform Type (%d) not supported", (int)type);
            return false;
    }

    if( utype == GL_FLOAT)
    {
        GLfloat* param = new (std::nothrow) GLfloat[usize];
        JSB_GL_CHECK(glGetUniformfv(arg0, arg1, param));

        se::HandleObject obj(se::Object::createTypedArray(se::Object::TypedArrayType::FLOAT32, param, usize * sizeof(GLfloat)));
        s.rval().setObject(obj);
        CC_SAFE_DELETE_ARRAY(param);
        return true;
    }
    else if( utype == GL_INT )
    {
        GLint* param = new (std::nothrow) GLint[usize];
        JSB_GL_CHECK(glGetUniformiv(arg0, arg1, param));

        se::HandleObject obj(se::Object::createTypedArray(se::Object::TypedArrayType::INT32, param, usize * sizeof(GLint)));
        s.rval().setObject(obj);
        CC_SAFE_DELETE_ARRAY(param);
        return true;
    }

    SE_REPORT_ERROR("Supported type: %d", utype);
    return false;
}
SE_BIND_FUNC(JSB_glGetUniformfv)

#ifndef GL_MAX_FRAGMENT_UNIFORM_VECTORS
#define GL_MAX_FRAGMENT_UNIFORM_VECTORS 0x8dfd
#endif

static bool JSB_glGetParameter(se::State& s)
{
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc < 1)
    {
        SE_REPORT_ERROR("Wrong argument count passed to gl.getParameter, expected: %d, get: %d", 1, argc);
        return false;
    }

    int pname = args[0].toInt32();

    int intbuffer[4];
    float floatvalue;

    auto& ret = s.rval();

    switch( pname ) {
            // Need to emulate MAX_FRAGMENT/VERTEX_UNIFORM_VECTORS and MAX_VARYING_VECTORS
            // because desktop GL's corresponding queries return the number of components
            // whereas GLES2 return the number of vectors (each vector has 4 components).
            // Therefore, the value returned by desktop GL needs to be divided by 4.
        case GL_MAX_FRAGMENT_UNIFORM_VECTORS:
        {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
            GL_CHECK(glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, intbuffer));
            s.rval().setInt32(intbuffer[0] / 4);
#else
            GL_CHECK(glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, intbuffer));
            s.rval().setInt32(intbuffer[0]);
#endif
        }
            break;
            // Float32Array (with 0 elements)
        case GL_COMPRESSED_TEXTURE_FORMATS:
            ret.setObject(se::Object::createTypedArray(se::Object::TypedArrayType::FLOAT32, nullptr, 0), true);
            break;

            // Float32Array (with 2 elements)
        case GL_ALIASED_LINE_WIDTH_RANGE:
        case GL_ALIASED_POINT_SIZE_RANGE:
        case GL_DEPTH_RANGE:
        {
            GLfloat params[2];
            JSB_GL_CHECK(glGetFloatv(pname, params));
            ret.setObject(se::Object::createTypedArray(se::Object::TypedArrayType::FLOAT32, params, sizeof(params)), true);
        }
            break;

            // Float32Array (with 4 values)
        case GL_BLEND_COLOR:
        case GL_COLOR_CLEAR_VALUE:
        {
            GLfloat params[4];
            JSB_GL_CHECK(glGetFloatv(pname, params));
            ret.setObject(se::Object::createTypedArray(se::Object::TypedArrayType::FLOAT32, params, sizeof(params)), true);
        }
            break;

            // Int32Array (with 2 values)
        case GL_MAX_VIEWPORT_DIMS:
        {
            GLfloat params[2];
            JSB_GL_CHECK(glGetFloatv(pname, params));
            int intParams[2] = {(int)params[0], (int)params[1]};
            ret.setObject(se::Object::createTypedArray(se::Object::TypedArrayType::INT32, intParams, sizeof(intParams)), true);
        }
            break;

            // Int32Array (with 4 values)
        case GL_SCISSOR_BOX:
        case GL_VIEWPORT:
        {
            GLfloat params[4];
            JSB_GL_CHECK(glGetFloatv(pname, params));
            int intParams[4] = {(int)params[0], (int)params[1], (int)params[2], (int)params[3]};
            ret.setObject(se::Object::createTypedArray(se::Object::TypedArrayType::INT32, intParams, sizeof(intParams)), true);
        }
            break;

            // boolean[] (with 4 values)
        case GL_COLOR_WRITEMASK:
        {
            JSB_GL_CHECK(glGetIntegerv(pname, intbuffer));
            se::HandleObject arr(se::Object::createArrayObject(4));
            for(int i = 0; i < 4; i++ ) {
                arr->setArrayElement(i, se::Value(intbuffer[i]));
            }
            ret.setObject(arr, true);
        }
            break;

            // WebGLBuffer
        case GL_ARRAY_BUFFER_BINDING:
        case GL_ELEMENT_ARRAY_BUFFER_BINDING:
            //        JSB_GL_CHECK(glGetIntegerv(pname, intbuffer));
            //        ret = [buffers[@(intbuffer[0])] pointerValue];
            break;

            // WebGLProgram
        case GL_CURRENT_PROGRAM:
            //        glGetIntegerv(pname, intbuffer);
            //        ret = [programs[@(intbuffer[0])] pointerValue];
            break;

            // WebGLFramebuffer
        case GL_FRAMEBUFFER_BINDING:
            //        glGetIntegerv(pname, intbuffer);
            //        ret = [framebuffers[@(intbuffer[0])] pointerValue];
            break;

            // WebGLRenderbuffer
        case GL_RENDERBUFFER_BINDING:
            //        glGetIntegerv(pname, intbuffer);
            //        ret = [renderbuffers[@(intbuffer[0])] pointerValue];
            break;

            // WebGLTexture
        case GL_TEXTURE_BINDING_2D:
        case GL_TEXTURE_BINDING_CUBE_MAP:
            //        glGetIntegerv(pname, intbuffer);
            //        ret = [textures[@(intbuffer[0])] pointerValue];
            break;

            // Ejecta/WebGL specific
        case GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS:
            // device may support more, but we only map 8 here
            //        ret = JSValueMakeNumber(ctx, EJ_CANVAS_MAX_TEXTURE_UNITS);
            break;

        case GL_UNPACK_FLIP_Y_WEBGL:
            //        ret = JSValueMakeBoolean(ctx, unpackFlipY);
            break;

        case GL_UNPACK_PREMULTIPLY_ALPHA_WEBGL:
            SE_LOGD("GL_UNPACK_PREMULTIPLY_ALPHA_WEBGL: ...\n");
            //        ret = JSValueMakeBoolean(ctx, premultiplyAlpha);
            break;

        case GL_UNPACK_COLORSPACE_CONVERSION_WEBGL:
            //        ret = JSValueMakeBoolean(ctx, false);
            break;

            // string
        case GL_RENDERER:
        case GL_SHADING_LANGUAGE_VERSION:
        case GL_VENDOR:
        case GL_VERSION:
            ret.setString((char *)glGetString(pname));
            break;

            // single float
        case GL_DEPTH_CLEAR_VALUE:
        case GL_LINE_WIDTH:
        case GL_POLYGON_OFFSET_FACTOR:
        case GL_POLYGON_OFFSET_UNITS:
        case GL_SAMPLE_COVERAGE_VALUE:
            JSB_GL_CHECK(glGetFloatv(pname, &floatvalue));
            ret.setFloat(floatvalue);
            break;

            // single int/long/bool - everything else
        default:
            JSB_GL_CHECK(glGetIntegerv(pname, intbuffer));
            ret.setInt32(intbuffer[0]);
            break;
    }

    // That was fun!
    return true;
}
SE_BIND_FUNC(JSB_glGetParameter)

static bool JSB_glGetShaderPrecisionFormat(se::State& s)
{
    const auto& args = s.args();
    int argc = (int)args.size();
    if (argc < 2)
    {
        SE_REPORT_ERROR("Wrong argument count passed to gl.getParameter, expected: %d, get: %d", 1, argc);
        return false;
    }

    uint32_t shadertype;
    uint32_t precisiontype;

    bool ok = seval_to_uint32(args[0], &shadertype);
    SE_PRECONDITION2(ok, false, "Convert shadertype failed!");
    ok = seval_to_uint32(args[1], &precisiontype);
    SE_PRECONDITION2(ok, false, "Convert precisiontype failed!");

    if( shadertype != GL_VERTEX_SHADER && shadertype != GL_FRAGMENT_SHADER ) {
        SE_REPORT_ERROR("Unsupported shadertype: %u", shadertype);
        return false;
    }

    GLint rangeMin = 0, rangeMax = 0, precision = 0;
#if CC_TARGET_PLATFORM != CC_PLATFORM_MAC && CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    switch( precisiontype ) {
        case GL_LOW_INT:
        case GL_MEDIUM_INT:
        case GL_HIGH_INT:
            // These values are for a 32-bit twos-complement integer format.
            rangeMin = 31;
            rangeMax = 30;
            precision = 0;
            break;
        case GL_LOW_FLOAT:
        case GL_MEDIUM_FLOAT:
        case GL_HIGH_FLOAT:
            // These values are for an IEEE single-precision floating-point format.
            rangeMin = 127;
            rangeMax = 127;
            precision = 23;
            break;
        default:
            SE_REPORT_ERROR("Unsupported precisiontype: %u", precisiontype);
            return false;
    }
#endif

    se::HandleObject obj(se::Object::createPlainObject());
    obj->setProperty("rangeMin", se::Value(rangeMin));
    obj->setProperty("rangeMax", se::Value(rangeMax));
    obj->setProperty("precision", se::Value(precision));
    s.rval().setObject(obj);
    return true;
}
SE_BIND_FUNC(JSB_glGetShaderPrecisionFormat)

bool JSB_register_opengl(se::Object* obj)
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &__defaultFbo);

    // New WebGL functions, not present on OpenGL ES 2.0
    __glObj->defineFunction("getSupportedExtensions", _SE(JSB_glGetSupportedExtensions));
    __glObj->defineFunction("activeTexture", _SE(JSB_glActiveTexture));
    __glObj->defineFunction("_attachShader", _SE(JSB_glAttachShader));
    __glObj->defineFunction("_bindAttribLocation", _SE(JSB_glBindAttribLocation));
    __glObj->defineFunction("_bindBuffer", _SE(JSB_glBindBuffer));
    __glObj->defineFunction("_bindFramebuffer", _SE(JSB_glBindFramebuffer));
    __glObj->defineFunction("_bindRenderbuffer", _SE(JSB_glBindRenderbuffer));
    __glObj->defineFunction("_bindTexture", _SE(JSB_glBindTexture));
    __glObj->defineFunction("blendColor", _SE(JSB_glBlendColor));
    __glObj->defineFunction("blendEquation", _SE(JSB_glBlendEquation));
    __glObj->defineFunction("blendEquationSeparate", _SE(JSB_glBlendEquationSeparate));
    __glObj->defineFunction("blendFunc", _SE(JSB_glBlendFunc));
    __glObj->defineFunction("blendFuncSeparate", _SE(JSB_glBlendFuncSeparate));
    __glObj->defineFunction("bufferData", _SE(JSB_glBufferData));
    __glObj->defineFunction("bufferSubData", _SE(JSB_glBufferSubData));
    __glObj->defineFunction("checkFramebufferStatus", _SE(JSB_glCheckFramebufferStatus));
    __glObj->defineFunction("clear", _SE(JSB_glClear));
    __glObj->defineFunction("clearColor", _SE(JSB_glClearColor));
    __glObj->defineFunction("clearDepth", _SE(JSB_glClearDepthf));
    __glObj->defineFunction("clearStencil", _SE(JSB_glClearStencil));
    __glObj->defineFunction("colorMask", _SE(JSB_glColorMask));
    __glObj->defineFunction("_compileShader", _SE(JSB_glCompileShader));
    __glObj->defineFunction("compressedTexImage2D", _SE(JSB_glCompressedTexImage2D));
    __glObj->defineFunction("compressedTexSubImage2D", _SE(JSB_glCompressedTexSubImage2D));
    __glObj->defineFunction("copyTexImage2D", _SE(JSB_glCopyTexImage2D));
    __glObj->defineFunction("copyTexSubImage2D", _SE(JSB_glCopyTexSubImage2D));
    __glObj->defineFunction("_createProgram", _SE(JSB_glCreateProgram));
    __glObj->defineFunction("_createShader", _SE(JSB_glCreateShader));
    __glObj->defineFunction("cullFace", _SE(JSB_glCullFace));
    __glObj->defineFunction("_deleteBuffer", _SE(JSB_glDeleteBuffers));
    __glObj->defineFunction("_deleteFramebuffer", _SE(JSB_glDeleteFramebuffers));
    __glObj->defineFunction("_deleteProgram", _SE(JSB_glDeleteProgram));
    __glObj->defineFunction("_deleteRenderbuffer", _SE(JSB_glDeleteRenderbuffers));
    __glObj->defineFunction("_deleteShader", _SE(JSB_glDeleteShader));
    __glObj->defineFunction("_deleteTexture", _SE(JSB_glDeleteTextures));
    __glObj->defineFunction("depthFunc", _SE(JSB_glDepthFunc));
    __glObj->defineFunction("depthMask", _SE(JSB_glDepthMask));
    __glObj->defineFunction("depthRange", _SE(JSB_glDepthRangef));
    __glObj->defineFunction("detachShader", _SE(JSB_glDetachShader));
    __glObj->defineFunction("disable", _SE(JSB_glDisable));
    __glObj->defineFunction("disableVertexAttribArray", _SE(JSB_glDisableVertexAttribArray));
    __glObj->defineFunction("drawArrays", _SE(JSB_glDrawArrays));
    __glObj->defineFunction("drawElements", _SE(JSB_glDrawElements));
    __glObj->defineFunction("enable", _SE(JSB_glEnable));
    __glObj->defineFunction("enableVertexAttribArray", _SE(JSB_glEnableVertexAttribArray));
    __glObj->defineFunction("finish", _SE(JSB_glFinish));
    __glObj->defineFunction("flush", _SE(JSB_glFlush));
    __glObj->defineFunction("framebufferRenderbuffer", _SE(JSB_glFramebufferRenderbuffer));
    __glObj->defineFunction("framebufferTexture2D", _SE(JSB_glFramebufferTexture2D));
    __glObj->defineFunction("frontFace", _SE(JSB_glFrontFace));
    __glObj->defineFunction("_createBuffer", _SE(JSB_glGenBuffers));
    __glObj->defineFunction("_createFramebuffer", _SE(JSB_glGenFramebuffers));
    __glObj->defineFunction("_createRenderbuffer", _SE(JSB_glGenRenderbuffers));
    __glObj->defineFunction("_createTexture", _SE(JSB_glGenTextures));
    __glObj->defineFunction("generateMipmap", _SE(JSB_glGenerateMipmap));
    __glObj->defineFunction("_getActiveAttrib", _SE(JSB_glGetActiveAttrib));
    __glObj->defineFunction("_getActiveUniform", _SE(JSB_glGetActiveUniform));
    __glObj->defineFunction("_getAttachedShaders", _SE(JSB_glGetAttachedShaders));
    __glObj->defineFunction("_getAttribLocation", _SE(JSB_glGetAttribLocation));
    __glObj->defineFunction("getError", _SE(JSB_glGetError));
    __glObj->defineFunction("_getProgramInfoLog", _SE(JSB_glGetProgramInfoLog));
    __glObj->defineFunction("_getProgramParameter", _SE(JSB_glGetProgramiv));
    __glObj->defineFunction("_getShaderInfoLog", _SE(JSB_glGetShaderInfoLog));
    __glObj->defineFunction("_getShaderSource", _SE(JSB_glGetShaderSource));
    __glObj->defineFunction("_getShaderParameter", _SE(JSB_glGetShaderiv));
    __glObj->defineFunction("getTexParameter", _SE(JSB_glGetTexParameterfv));
    __glObj->defineFunction("_getUniformLocation", _SE(JSB_glGetUniformLocation));
    __glObj->defineFunction("_getUniform", _SE(JSB_glGetUniformfv));
    __glObj->defineFunction("hint", _SE(JSB_glHint));
    __glObj->defineFunction("isBuffer", _SE(JSB_glIsBuffer));
    __glObj->defineFunction("isEnabled", _SE(JSB_glIsEnabled));
    __glObj->defineFunction("isFramebuffer", _SE(JSB_glIsFramebuffer));
    __glObj->defineFunction("isProgram", _SE(JSB_glIsProgram));
    __glObj->defineFunction("isRenderbuffer", _SE(JSB_glIsRenderbuffer));
    __glObj->defineFunction("isShader", _SE(JSB_glIsShader));
    __glObj->defineFunction("isTexture", _SE(JSB_glIsTexture));
    __glObj->defineFunction("lineWidth", _SE(JSB_glLineWidth));
    __glObj->defineFunction("_linkProgram", _SE(JSB_glLinkProgram));
    __glObj->defineFunction("pixelStorei", _SE(JSB_glPixelStorei));
    __glObj->defineFunction("polygonOffset", _SE(JSB_glPolygonOffset));
    __glObj->defineFunction("readPixels", _SE(JSB_glReadPixels));
    __glObj->defineFunction("releaseShaderCompiler", _SE(JSB_glReleaseShaderCompiler));
    __glObj->defineFunction("renderbufferStorage", _SE(JSB_glRenderbufferStorage));
    __glObj->defineFunction("sampleCoverage", _SE(JSB_glSampleCoverage));
    __glObj->defineFunction("scissor", _SE(JSB_glScissor));
    __glObj->defineFunction("_shaderSource", _SE(JSB_glShaderSource));
    __glObj->defineFunction("stencilFunc", _SE(JSB_glStencilFunc));
    __glObj->defineFunction("stencilFuncSeparate", _SE(JSB_glStencilFuncSeparate));
    __glObj->defineFunction("stencilMask", _SE(JSB_glStencilMask));
    __glObj->defineFunction("stencilMaskSeparate", _SE(JSB_glStencilMaskSeparate));
    __glObj->defineFunction("stencilOp", _SE(JSB_glStencilOp));
    __glObj->defineFunction("stencilOpSeparate", _SE(JSB_glStencilOpSeparate));
    __glObj->defineFunction("texImage2D", _SE(JSB_glTexImage2D));
    __glObj->defineFunction("texParameterf", _SE(JSB_glTexParameterf));
    __glObj->defineFunction("texParameteri", _SE(JSB_glTexParameteri));
    __glObj->defineFunction("texSubImage2D", _SE(JSB_glTexSubImage2D));
    __glObj->defineFunction("uniform1f", _SE(JSB_glUniform1f));
    __glObj->defineFunction("uniform1fv", _SE(JSB_glUniform1fv));
    __glObj->defineFunction("uniform1i", _SE(JSB_glUniform1i));
    __glObj->defineFunction("uniform1iv", _SE(JSB_glUniform1iv));
    __glObj->defineFunction("uniform2f", _SE(JSB_glUniform2f));
    __glObj->defineFunction("uniform2fv", _SE(JSB_glUniform2fv));
    __glObj->defineFunction("uniform2i", _SE(JSB_glUniform2i));
    __glObj->defineFunction("uniform2iv", _SE(JSB_glUniform2iv));
    __glObj->defineFunction("uniform3f", _SE(JSB_glUniform3f));
    __glObj->defineFunction("uniform3fv", _SE(JSB_glUniform3fv));
    __glObj->defineFunction("uniform3i", _SE(JSB_glUniform3i));
    __glObj->defineFunction("uniform3iv", _SE(JSB_glUniform3iv));
    __glObj->defineFunction("uniform4f", _SE(JSB_glUniform4f));
    __glObj->defineFunction("uniform4fv", _SE(JSB_glUniform4fv));
    __glObj->defineFunction("uniform4i", _SE(JSB_glUniform4i));
    __glObj->defineFunction("uniform4iv", _SE(JSB_glUniform4iv));
    __glObj->defineFunction("uniformMatrix2fv", _SE(JSB_glUniformMatrix2fv));
    __glObj->defineFunction("uniformMatrix3fv", _SE(JSB_glUniformMatrix3fv));
    __glObj->defineFunction("uniformMatrix4fv", _SE(JSB_glUniformMatrix4fv));
    __glObj->defineFunction("_useProgram", _SE(JSB_glUseProgram));
    __glObj->defineFunction("_validateProgram", _SE(JSB_glValidateProgram));
    __glObj->defineFunction("vertexAttrib1f", _SE(JSB_glVertexAttrib1f));
    __glObj->defineFunction("vertexAttrib1fv", _SE(JSB_glVertexAttrib1fv));
    __glObj->defineFunction("vertexAttrib2f", _SE(JSB_glVertexAttrib2f));
    __glObj->defineFunction("vertexAttrib2fv", _SE(JSB_glVertexAttrib2fv));
    __glObj->defineFunction("vertexAttrib3f", _SE(JSB_glVertexAttrib3f));
    __glObj->defineFunction("vertexAttrib3fv", _SE(JSB_glVertexAttrib3fv));
    __glObj->defineFunction("vertexAttrib4f", _SE(JSB_glVertexAttrib4f));
    __glObj->defineFunction("vertexAttrib4fv", _SE(JSB_glVertexAttrib4fv));
    __glObj->defineFunction("vertexAttribPointer", _SE(JSB_glVertexAttribPointer));
    __glObj->defineFunction("viewport", _SE(JSB_glViewport));
    __glObj->defineFunction("getParameter", _SE(JSB_glGetParameter));
    __glObj->defineFunction("getShaderPrecisionFormat", _SE(JSB_glGetShaderPrecisionFormat));

    return true;
    
}

