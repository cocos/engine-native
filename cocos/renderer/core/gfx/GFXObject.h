#pragma once

#include "GFXDef.h"

namespace cc {
namespace gfx {

class GFXObject : public Object {
public:
    GFXObject(GFXObjectType gfxType);
    virtual ~GFXObject() = default;

    CC_INLINE GFXObjectType getType() const { return _gfxType; }
    CC_INLINE Status getStatus() const { return _status; }

protected:
    GFXObjectType _gfxType = GFXObjectType::UNKNOWN;
    Status _status = Status::UNREADY;
};

} // namespace gfx
} // namespace cc
