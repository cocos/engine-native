#pragma once
#include "../RenderStage.h"
//#include "../gfx-gles3/gles3w.h"
//#include "gfx-gles-common/gles3w.h"
#include "gfx-gles3/GLES3Wrangler.h"
#include "gfx-gles3/GLES3Context.h"

namespace cc {
namespace pipeline {

class CC_DLL ARBackGroundStage : public RenderStage {
public:
    static const RenderStageInfo &getInitializeInfo();

    ARBackGroundStage();
    ~ARBackGroundStage();

    //virtual bool initialize(const RenderStageInfo &info) override;
    virtual void activate(RenderPipeline* pipeline, RenderFlow *flow) override;
    virtual void destroy() override;
    virtual void render(scene::Camera *camera) override;

protected:
    static RenderStageInfo _initInfo;
    RenderPipeline *_pipeline = nullptr;

    //gfx::GLES3Context *_renderContext = nullptr;

    GLuint _program;
    GLuint _texture;

    uint _phaseID = 0;

private:
    GLint _positionIndex;
    GLint _texcoordIndex;

    GLuint _positionBuffer;
    GLuint _texcoordBuffer;

    const GLfloat _vertices[16] = {
        -1, -1, 0, 1, 
        -1, 1, 0, 1, 
        1, -1, 0, 1, 
        1, 1, 0, 1};

    GLfloat _uvs[8] = {
        0, 0, 
        0, 1, 
        1, 0, 
        1, 1};

    const GLfloat _matProj[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, -1, 1};

    const GLfloat _coordMat[16] = {
        1, 0, 0, 0, 
        0, 1, 0, 0, 
        0, 0, 1, 0, 
        0, 0, 0, 1};

    bool _setTexFlag = false;

    void initProgram();
    void initTexture();
    void initBuffer();
};

}
}