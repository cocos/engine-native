#pragma once
/****************************************************************************
 Copyright (c) 2021 Xiamen Yaji Software Co., Ltd.

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
//MIT License
//
//Copyright (c) 2017 Mindaugas Vinkelis
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

/**
* reference: https://github.com/fraillt/bitsery
* We customize bitsery to meet our needs:
* 1. Class versioning
* 2. Json serialization
* 3. Other general serialization process
* 4. Remove we don't need
* 5. Rename to our perference
*/
#pragma once
#include "Archive.h"
#include "bitsery/details/serialization_common.h"
#include "bitsery/details/adapter_common.h"
#include <bitsery/adapter/stream.h>
#include <bitsery/brief_syntax.h>
#include <bitsery/brief_syntax/array.h>
#include <bitsery/brief_syntax/atomic.h>
#include <bitsery/brief_syntax/chrono.h>
#include <bitsery/brief_syntax/deque.h>
#include <bitsery/brief_syntax/forward_list.h>
#include <bitsery/brief_syntax/list.h>
#include <bitsery/brief_syntax/map.h>
#include <bitsery/brief_syntax/memory.h>
#include <bitsery/brief_syntax/queue.h>
#include <bitsery/brief_syntax/set.h>
#include <bitsery/brief_syntax/stack.h>
#include <bitsery/brief_syntax/string.h>
#include <bitsery/brief_syntax/unordered_map.h>
#include <bitsery/brief_syntax/unordered_set.h>
#include <bitsery/brief_syntax/vector.h>

using namespace bitsery;
namespace cc {
namespace serialization {
template <typename TWriter>
class BinaryOutputArchive : public Archive {
public:
    using TConfig       = typename TWriter::TConfig;

    constexpr bool isSaving() { return true; }

    /*
         * object function
         */
    template <typename T>
    void object(const T &obj) {
        details::SerializeFunction<BinaryOutputArchive, T>::invoke(*this, const_cast<T &>(obj));
    }

    /*
         * functionality, that enables simpler serialization syntax, by including additional header
         */

    template <typename T>
    void operator()(std::string const &name, T && value) {
        details::BriefSyntaxFunction<BinaryOutputArchive, T>::invoke(*this, std::forward<T>(value));
    }

    template <typename T>
    void operator()(const char *name, T && value) {
        details::BriefSyntaxFunction<BinaryOutputArchive, T>::invoke(*this, std::forward<T>(value));
    }

    /*
         * value overloads
         */

    template <size_t VSIZE, typename T>
    void value(const T &v) {
        static_assert(details::IsFundamentalType<T>::value, "Value must be integral, float or enum type.");
        using TValue = typename details::IntegralFromFundamental<T>::TValue;
        this->_adapter.template writeBytes<VSIZE>(reinterpret_cast<const TValue &>(v));
    }

    /*
         * boolValue
         */

    void boolValue(bool v) {
        procBoolValue(v);
    }

    /*
         * text overloads
         */

    template <size_t VSIZE, typename T>
    void text(const T &str, size_t maxSize) {
        static_assert(details::IsTextTraitsDefined<T>::value,
                      "Please define TextTraits or include from <bitsery/traits/...>");
        static_assert(traits::ContainerTraits<T>::isResizable,
                      "use text(const T&) overload without `maxSize` for static container");
        procText<VSIZE>(str, maxSize);
    }

    template <size_t VSIZE, typename T>
    void text(const T &str) {
        static_assert(details::IsTextTraitsDefined<T>::value,
                      "Please define TextTraits or include from <bitsery/traits/...>");
        static_assert(!traits::ContainerTraits<T>::isResizable,
                      "use text(const T&, size_t) overload with `maxSize` for dynamic containers");
        procText<VSIZE>(str, traits::ContainerTraits<T>::size(str));
    }

    /*
         * container overloads
         */

    //dynamic size containers

    template <size_t VSIZE, typename T>
    void container(const T &obj, size_t maxSize) {
        static_assert(details::IsContainerTraitsDefined<T>::value,
                      "Please define ContainerTraits or include from <bitsery/traits/...>");
        static_assert(traits::ContainerTraits<T>::isResizable,
                      "use container(const T&) overload without `maxSize` for static containers");
        static_assert(VSIZE > 0, "");
        auto size = traits::ContainerTraits<T>::size(obj);
        (void)maxSize; // unused in release
        assert(size <= maxSize);
        details::writeSize(this->_adapter, size);

        procContainer<VSIZE>(std::begin(obj), std::end(obj), std::integral_constant<bool, traits::ContainerTraits<T>::isContiguous>{});
    }

    template <typename T>
    void container(const T &obj, size_t maxSize) {
        static_assert(details::IsContainerTraitsDefined<T>::value,
                      "Please define ContainerTraits or include from <bitsery/traits/...>");
        static_assert(traits::ContainerTraits<T>::isResizable,
                      "use container(const T&) overload without `maxSize` for static containers");
        auto size = traits::ContainerTraits<T>::size(obj);
        (void)maxSize; // unused in release
        assert(size <= maxSize);
        details::writeSize(this->_adapter, size);
        procContainer(std::begin(obj), std::end(obj));
    }

    //fixed size containers

    template <size_t VSIZE, typename T>
    void container(const T &obj) {
        static_assert(details::IsContainerTraitsDefined<T>::value,
                      "Please define ContainerTraits or include from <bitsery/traits/...>");
        static_assert(!traits::ContainerTraits<T>::isResizable,
                      "use container(const T&, size_t) overload with `maxSize` for dynamic containers");
        static_assert(VSIZE > 0, "");
        procContainer<VSIZE>(std::begin(obj), std::end(obj), std::integral_constant<bool, traits::ContainerTraits<T>::isContiguous>{});
    }

    template <typename T>
    void container(const T &obj) {
        static_assert(details::IsContainerTraitsDefined<T>::value,
                      "Please define ContainerTraits or include from <bitsery/traits/...>");
        static_assert(!traits::ContainerTraits<T>::isResizable,
                      "use container(const T&, size_t) overload with `maxSize` for dynamic containers");
        procContainer(std::begin(obj), std::end(obj));
    }

    template <typename... TArgs>
    explicit BinaryOutputArchive(TArgs &&...args)
    : _adapter{std::forward<TArgs>(args)...} {}

    TWriter &getAdapter() {
        return _adapter;
    }

private:
    //process value types
    //false_type means that we must process all elements individually
    template <size_t VSIZE, typename It>
    void procContainer(It first, It last, std::false_type) {
        for (; first != last; ++first)
            value<VSIZE>(*first);
    }

    //process value types
    //true_type means, that we can copy whole buffer
    template <size_t VSIZE, typename It>
    void procContainer(It first, It last, std::true_type) {
        using TValue    = typename std::decay<decltype(*first)>::type;
        using TIntegral = typename details::IntegralFromFundamental<TValue>::TValue;
        if (first != last)
            this->_adapter.template writeBuffer<VSIZE>(reinterpret_cast<const TIntegral *>(&(*first)),
                                                       static_cast<size_t>(std::distance(first, last)));
    }

    //process text,
    template <size_t VSIZE, typename T>
    void procText(const T &str) {
        const size_t length = traits::TextTraits<T>::length(str);
        details::writeSize(this->_adapter, length);
        auto begin   = std::begin(str);
        using diff_t = typename std::iterator_traits<decltype(begin)>::difference_type;
        procContainer<VSIZE>(begin, std::next(begin, static_cast<diff_t>(length)), std::integral_constant<bool, traits::ContainerTraits<T>::isContiguous>{});
    }

    //process object types
    template <typename It>
    void procContainer(It first, It last) {
        for (; first != last; ++first)
            object(*first);
    }

    void procBoolValue(bool v) {
        this->_adapter.template writeBytes<1>(static_cast<unsigned char>(v ? 1 : 0));
    }

    TWriter _adapter;
};
using StreamedBinaryOutputArchive = BinaryOutputArchive<bitsery::OutputStreamAdapter>;
} // namespace serialization
} // namespace cc
