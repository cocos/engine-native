#include "ARBackGroundStage.h"
#include "../forward/ForwardPipeline.h"
#include "GLES2/gl2.h"
#include "pipeline/PipelineStateManager.h"
#include "gfx-base/GFXCommandBuffer.h"
#include "gfx-base/GFXDef.h"

#include "ar/ARModule.h"
#include "gfx-base/GFXDevice.h"

namespace cc {
namespace pipeline {

#define GL_TEXTURE_EXTERNAL_OES 0x8D65

//#define USE_ARMODULE 1

// ARCore
const auto VS_ANDROID = "attribute vec4 vPosition;\n attribute vec2 vCoord;\n uniform mat4 vMatrix;\n uniform mat4 vCoordMatrix;\n varying vec2 textureCoordinate;\n void main(){\n gl_Position = vMatrix*vPosition;\n textureCoordinate = (vCoordMatrix*vec4(vCoord,0,1)).xy;\n }";

// AREngine Demo
//const auto VS_ANDROID = "attribute vec4 vPosition;\n attribute vec2 vCoord;\n uniform mat4 vMatrix;\n uniform mat4 vCoordMatrix;\n varying vec2 textureCoordinate;\n void main(){\n gl_Position = vMatrix*vPosition;\n textureCoordinate = (vCoordMatrix*vec4(vCoord,0,1)).xy;\n textureCoordinate = vec2(textureCoordinate.x, 1.0-textureCoordinate.y);\n }";

const auto FS_ANDROID = "#extension GL_OES_EGL_image_external:require\n precision mediump float;\n varying vec2 textureCoordinate;\n uniform samplerExternalOES vTexture;\n void main() {\n gl_FragColor = texture2D(vTexture, textureCoordinate);\n }";

ARBackGroundStage::~ARBackGroundStage() = default;

GLuint createShader(const GLenum type, const GLchar *source) {
    const auto shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE) {
        CC_LOG_ERROR("compile shader error");
        glDeleteShader(shader);
    } else {
        return shader;
    }

    return -1;
}

GLuint createProgram(const GLuint vs, const GLuint fs){
    const auto program = glCreateProgram();
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    GLint linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if(!linked) {
        GLint infoLen = 0;

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);

        if(infoLen > 1) {
            GLchar* infoLog = nullptr;

            glGetProgramInfoLog(program, infoLen, nullptr, infoLog);
            CC_LOG_ERROR("Error linking program:\n%s\n", infoLog);

            free(infoLog);
        }
        glDeleteProgram(program);
    } else {
        return program;
    }

    return -1;
}

void ARBackGroundStage::initProgram(){
    const auto vs = createShader(GL_VERTEX_SHADER, VS_ANDROID);
    const auto fs = createShader(GL_FRAGMENT_SHADER, FS_ANDROID);
    _program = createProgram(vs, fs);
}

void ARBackGroundStage::initTexture(){
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, _texture);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void ARBackGroundStage::initBuffer(){
    glUseProgram(_program);

    _positionIndex = glGetAttribLocation(_program, "vPosition");
    _texcoordIndex = glGetAttribLocation(_program, "vCoord");

    glGenBuffers(1, &_positionBuffer);
    glGenBuffers(1, &_texcoordBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, _positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(_positionIndex);
    glVertexAttribPointer(_positionIndex, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, _texcoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_uvs), _uvs, GL_STATIC_DRAW);
    glEnableVertexAttribArray(_texcoordIndex);
    glVertexAttribPointer(_texcoordIndex, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void ARBackGroundStage::activate(RenderPipeline *pipeline, RenderFlow *flow) {
    RenderStage::activate(pipeline, flow);

    this->initProgram();
    this->initBuffer();
    this->initTexture();
}

void ARBackGroundStage::destroy(){

}

void ARBackGroundStage::render(scene::Camera *camera) {

    // UI_3D: 8388608 0x00800000 (1 << 23)
    // DEFAULT: 1073741824 0x40000000 (1 << 30)
    //*
    const scene::Node *camNode = camera->node;
    const int flag = (static_cast<int>(camNode->getLayer())) & 0x00800000;
    if(flag == 0) return;

    auto *const armodule = cc::ar::ARModule::get();
    if(!armodule) return;
    if(!_setTexFlag) {
        armodule->setCameraTextureName(static_cast<int>(_texture));

        _setTexFlag = true;
    }
    auto *const data = armodule->getCameraTexCoords();

    glViewport(0, 0, static_cast<GLsizei>(camera->width), static_cast<GLsizei>(camera->height));
    glClearColor(0.875, 0.875, 0.875, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDepthMask(false);
    glLinkProgram(_program);
    glUseProgram(_program);
    
    glBindTexture(GL_TEXTURE_EXTERNAL_OES, _texture);

    GLint location = glGetUniformLocation(_program, "vMatrix");
    glUniformMatrix4fv(location, 1, GL_FALSE, _matProj);

    location = glGetUniformLocation(_program, "vCoordMatrix");
    glUniformMatrix4fv(location, 1, GL_FALSE, _coordMat);
    
    glBindBuffer(GL_ARRAY_BUFFER, _positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(_positionIndex);
    glVertexAttribPointer(_positionIndex, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    for (size_t i = 0; i < 8; i++)
    {
        _uvs[i] = data[i];
    }

    glBindBuffer(GL_ARRAY_BUFFER, _texcoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_uvs), _uvs, GL_STATIC_DRAW);
    glEnableVertexAttribArray(_texcoordIndex);
    glVertexAttribPointer(_texcoordIndex, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDepthMask(true);
    glEnable(GL_DEPTH_TEST);
}

}  // namespace pipeline
}  // namespace cc