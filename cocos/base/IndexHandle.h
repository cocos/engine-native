/****************************************************************************
 Copyright (c) 2020-2021 Xiamen Yaji Software Co., Ltd.

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

#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>

namespace cc {

template <typename Index, typename Enable = std::enable_if_t<std::is_integral_v<Index>>>
class IndexHandle {
public:
    struct Hasher {
        inline size_t operator()(IndexHandle const &s) const noexcept { return s._index; }
    };

    using IndexType = Index;

    IndexHandle() noexcept = default;
    explicit IndexHandle(IndexType const index) noexcept : _index(index) {}

    inline bool IsValid() const noexcept;
    inline void Clear() noexcept;

    inline bool operator<(IndexHandle const &rhs) const noexcept;
    inline bool operator==(IndexHandle const &rhs) const noexcept;
    inline bool operator!=(IndexHandle const &rhs) const noexcept;
    inline      operator IndexType() const noexcept;

    static IndexType constexpr sUninitialized{std::numeric_limits<IndexType>::max()};

private:
    IndexType _index{sUninitialized};
};

template <typename Index, typename Enable>
bool IndexHandle<Index, Enable>::IsValid() const noexcept {
    return _index != sUninitialized;
}

template <typename Index, typename Enable>
void IndexHandle<Index, Enable>::Clear() noexcept {
    _index = sUninitialized;
}

template <typename Index, typename Enable>
bool IndexHandle<Index, Enable>::operator<(IndexHandle const &rhs) const noexcept {
    return _index < rhs._index;
}

template <typename Index, typename Enable>
bool IndexHandle<Index, Enable>::operator==(IndexHandle const &rhs) const noexcept {
    return (_index == rhs._index);
}

template <typename Index, typename Enable>
bool IndexHandle<Index, Enable>::operator!=(IndexHandle const &rhs) const noexcept {
    return !operator==(rhs);
}

template <typename Index, typename Enable>
IndexHandle<Index, Enable>::operator IndexType() const noexcept {
    return _index;
}

} // namespace cc
