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
    //static const RenderStageInfo &getInitializeInfo();

    ARBackGroundStage() = default;
    ~ARBackGroundStage() override;

    void activate(RenderPipeline* pipeline, RenderFlow *flow) override;
    void destroy() override;
    void render(scene::Camera *camera) override;

protected:
    //static RenderStageInfo initInfo;
    RenderPipeline *_pipeline = nullptr;

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

}  // namespace pipeline
}  // namespace cc