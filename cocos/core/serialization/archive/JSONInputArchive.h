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
#pragma once
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
#include "Archive.h"
#include "bitsery/details/adapter_common.h"
#include "bitsery/details/serialization_common.h"

using namespace bitsery;
namespace cc {
namespace serialization {

template <typename TReader>
class JSONInputArchive : public Archive {
public:
    using TConfig = typename TReader::TConfig;

    constexpr bool isLoading() { return true; }

    /*
     * object function
     */

    template <typename T>
    void object(T &&obj) {
        details::SerializeFunction<JSONInputArchive, T>::invoke(*this, std::forward<T>(obj));
    }

    /*
         * functionality, that enables simpler serialization syntax, by including additional header
         */

    template <typename T>
    void operator()(std::string const &name, T &&value) {
        details::BriefSyntaxFunction<JSONInputArchive, T>::invoke(*this, std::forward<T>(value));
    }

    template <typename T>
    void operator()(const char *name, T &&value) {
        details::BriefSyntaxFunction<JSONInputArchive, T>::invoke(*this, std::forward<T>(value));
    }

    /*
         * value
         */

    template <size_t VSIZE, typename T>
    void value(T &v) {
        static_assert(details::IsFundamentalType<T>::value, "Value must be integral, float or enum type.");
        using TValue = typename details::IntegralFromFundamental<T>::TValue;
        this->_adapter.template readBytes<VSIZE>(reinterpret_cast<TValue &>(v));
    }

    /*
         * boolValue
         */
    void boolValue(bool &v) {
        procBoolValue(v,
                      std::integral_constant<bool, TReader::BitPackingEnabled>{},
                      std::integral_constant<bool, TReader::TConfig::CheckDataErrors>{});
    }

    /*
         * text overloads
         */

    template <size_t VSIZE, typename T>
    void text(T &str, size_t maxSize) {
        static_assert(details::IsTextTraitsDefined<T>::value,
                      "Please define TextTraits or include from <bitsery/traits/...>");
        static_assert(traits::ContainerTraits<T>::isResizable,
                      "use text(T&) overload without `maxSize` for static containers");
        size_t length;
        readSize(length, maxSize);
        traits::ContainerTraits<T>::resize(str, length + (traits::TextTraits<T>::addNUL ? 1u : 0u));
        procText<VSIZE>(str, length);
    }

    template <size_t VSIZE, typename T>
    void text(T &str) {
        static_assert(details::IsTextTraitsDefined<T>::value,
                      "Please define TextTraits or include from <bitsery/traits/...>");
        static_assert(!traits::ContainerTraits<T>::isResizable,
                      "use text(T&, size_t) overload with `maxSize` for dynamic containers");
        size_t length;
        readSize(length, traits::ContainerTraits<T>::size(str));
        procText<VSIZE>(str, length);
    }

    /*
         * container overloads
         */

    //dynamic size containers

    template <size_t VSIZE, typename T>
    void container(T &obj, size_t maxSize) {
        static_assert(details::IsContainerTraitsDefined<T>::value,
                      "Please define ContainerTraits or include from <bitsery/traits/...>");
        static_assert(traits::ContainerTraits<T>::isResizable,
                      "use container(T&) overload without `maxSize` for static containers");
        size_t size{};
        readSize(size, maxSize);
        traits::ContainerTraits<T>::resize(obj, size);
        procContainer<VSIZE>(std::begin(obj), std::end(obj), std::integral_constant<bool, traits::ContainerTraits<T>::isContiguous>{});
    }

    template <typename T>
    void container(T &obj, size_t maxSize) {
        static_assert(details::IsContainerTraitsDefined<T>::value,
                      "Please define ContainerTraits or include from <bitsery/traits/...>");
        static_assert(traits::ContainerTraits<T>::isResizable,
                      "use container(T&) overload without `maxSize` for static containers");
        size_t size{};
        readSize(size, maxSize);
        traits::ContainerTraits<T>::resize(obj, size);
        procContainer(std::begin(obj), std::end(obj));
    }
    //fixed size containers

    template <size_t VSIZE, typename T>
    void container(T &obj) {
        static_assert(details::IsContainerTraitsDefined<T>::value,
                      "Please define ContainerTraits or include from <bitsery/traits/...>");
        static_assert(!traits::ContainerTraits<T>::isResizable,
                      "use container(T&, size_t) overload with `maxSize` for dynamic containers");
        static_assert(VSIZE > 0, "");
        procContainer<VSIZE>(std::begin(obj), std::end(obj), std::integral_constant<bool, traits::ContainerTraits<T>::isContiguous>{});
    }

    template <typename T>
    void container(T &obj) {
        static_assert(details::IsContainerTraitsDefined<T>::value,
                      "Please define ContainerTraits or include from <bitsery/traits/...>");
        static_assert(!traits::ContainerTraits<T>::isResizable,
                      "use container(T&, size_t) overload with `maxSize` for dynamic containers");
        procContainer(std::begin(obj), std::end(obj));
    }

    template <typename... TArgs>
    explicit JSONInputArchive(TArgs &&...args)
    : _adapter{std::forward<TArgs>(args)...} {}

    TReader &getAdapter() {
        return _adapter;
    }

private:
    void readSize(size_t &size, size_t maxSize) {
        details::readSize(this->_adapter, size, maxSize,
                          std::integral_constant<bool, TReader::TConfig::CheckDataErrors>{});
    }

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
        if (first != last) {
            const auto distance = std::distance(first, last);
            this->_adapter.template readBuffer<VSIZE>(reinterpret_cast<TIntegral *>(&(*first)), static_cast<size_t>(distance));
        }
    }

    //process object types
    template <typename It>
    void procContainer(It first, It last) {
        for (; first != last; ++first)
            object(*first);
    }

    template <size_t VSIZE, typename T>
    void procText(T &str, size_t length) {
        auto begin = std::begin(str);
        //end of string, not end of container
        using diff_t = typename std::iterator_traits<decltype(begin)>::difference_type;
        auto end     = std::next(begin, static_cast<diff_t>(length));
        procContainer<VSIZE>(begin, end, std::integral_constant<bool, traits::ContainerTraits<T>::isContiguous>{});
        //null terminated character at the end
        if (traits::TextTraits<T>::addNUL)
            *end = {};
    }

    //proc bool writing bit or byte, depending on if BitPackingEnabled or not
    template <typename HandleDataErrors>
    void procBoolValue(bool &v, std::true_type, HandleDataErrors) {
        uint8_t tmp{};
        this->_adapter.readBits(tmp, 1);
        v = tmp == 1;
    }

    void procBoolValue(bool &v, std::false_type, std::true_type) {
        uint8_t tmp{};
        this->_adapter.template readBytes<1>(tmp);
        if (tmp > 1)
            this->_adapter.error(ReaderError::InvalidData);
        v = tmp == 1;
    }

    void procBoolValue(bool &v, std::false_type, std::false_type) {
        uint8_t tmp{};
        this->_adapter.template readBytes<1>(tmp);
        v = tmp > 0;
    }

    TReader _adapter;
};
using StreamedJSONInputArchive = JSONInputArchive<bitsery::InputStreamAdapter>;
} // namespace serialization
} // namespace cc