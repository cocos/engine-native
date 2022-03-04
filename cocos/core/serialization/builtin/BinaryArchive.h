#pragma once
#include "Archive.h"

namespace cc {
namespace serialization {
template <typename Adapter>
class BinaryArchive : public Archive {
public:
    template <typename... TArgs>
    explicit BinaryArchive(TArgs &&...args)
    : _adapter{std::forward<TArgs>(args)...} {
    }

protected:
    Adapter _adapter;
};
}
}