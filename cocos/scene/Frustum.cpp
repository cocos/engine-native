#include "scene/Frustum.h"
#include "scene/Define.h"

namespace cc {
namespace scene {
static const std::vector<cc::Vec3> VEC_VAL{
    {1, 1, 1},
    {-1, 1, 1},
    {-1, -1, 1},
    {1, -1, 1},
    {1, 1, -1},
    {-1, 1, -1},
    {-1, -1, -1},
    {1, -1, -1}
};

static ShapeEnums type = ShapeEnums::SHAPE_FRUSTUM;

void Frustum::update(const Mat4 &m, const Mat4 &inv) {
    // left plane
    planes[0].n.set(m.m[3] + m.m[0], m.m[7] + m.m[4], m.m[11] + m.m[8]);
    planes[0].d = -(m.m[15] + m.m[12]);
    // right plane
    planes[1].n.set(m.m[3] - m.m[0], m.m[7] - m.m[4], m.m[11] - m.m[8]);
    planes[1].d = -(m.m[15] - m.m[12]);
    // bottom plane
    planes[2].n.set(m.m[3] + m.m[1], m.m[7] + m.m[5], m.m[11] + m.m[9]);
    planes[2].d = -(m.m[15] + m.m[13]);
    // top plane
    planes[3].n.set(m.m[3] - m.m[1], m.m[7] - m.m[5], m.m[11] - m.m[9]);
    planes[3].d = -(m.m[15] - m.m[13]);
    // near plane
    planes[4].n.set(m.m[3] + m.m[2], m.m[7] + m.m[6], m.m[11] + m.m[10]);
    planes[4].d = -(m.m[15] + m.m[14]);
    // far plane
    planes[5].n.set(m.m[3] - m.m[2], m.m[7] - m.m[6], m.m[11] - m.m[10]);
    planes[5].d = -(m.m[15] - m.m[14]);

    if (type != ShapeEnums::SHAPE_FRUSTUM_ACCURATE) {
        return;
    }

    for (Plane &plane : planes) {
        float invDist = 1 / plane.n.length();
        plane.n *= invDist;
        plane.d *= invDist;
    }
    for (int i = 0; i < 8; i++) {
        vertices[i].transformMat4(VEC_VAL[i], inv);
    }
}
} // namespace scene
} // namespace cc