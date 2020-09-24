#pragma once

namespace cc {
class Mat4;
class Vec4;
class Vec3;
namespace pipeline {

struct RenderObject;
struct Model;
class Camera;
class ForwardPipeline;
class RenderView;
class Shadows;

RenderObject genRenderObject(Model *, const Camera *);

void sceneCulling(ForwardPipeline *, RenderView *);
cc::Mat4 getShadowWorldMatrix(const Shadows *shadows, const cc::Vec4 &rotation, const cc::Vec3 &dir);
} // namespace pipeline
} // namespace cc
