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
#include <rapidjson/prettywriter.h>

using namespace bitsery;
namespace cc {
namespace serialization {

template <typename TWriter>
class RapidJSONWriterWrapper {
    using char Ch;
    RapidJSONWriterWrapper(TWriter &writer) : _writer(writer) {}

    void Put(Ch c) {
        _writer.writeBytes<sizeof Ch>(c);
    }

    void Flush() {
        _writer.flush();
    }

    // Not implemented
    char Peek() const {
        assert(false);
        return 0;
    }
    char Take() {
        assert(false);
        return 0;
    }
    size_t Tell() const {
        assert(false);
        return 0;
    }
    char *PutBegin() {
        assert(false);
        return 0;
    }
    size_t PutEnd(char *) {
        assert(false);
        return 0;
    }

private:
    RapidJSONWriterWrapper(const RapidJSONWriterWrapper &);
    RapidJSONWriterWrapper &operator=(const RapidJSONWriterWrapper &);

    TWriter &_writer;
};


template <typename TWriter>
class JSONOutputArchive : public Archive {
public:
    enum class NodeType { StartObject,
                          InObject,
                          StartArray,
                          InArray };
    using TConfig = typename TWriter::TConfig;
    using WriterWrapper = RapidJSONWriterWrapper<TWriter>;
    using JSONWriter = rapidjson::PrettyWriter<WriterWrapper>;

    constexpr bool isSaving() { return true; }

    /*
         * object function
         */
    template <typename T>
    void object(const T &obj) {
        details::SerializeFunction<JSONOutputArchive, T>::invoke(*this, const_cast<T &>(obj));
    }

    /*
         * functionality, that enables simpler serialization syntax, by including additional header
         */

    template <typename T>
    void operator()(std::string const &name, T &&value) {
        details::BriefSyntaxFunction<JSONOutputArchive, T>::invoke(*this, std::forward<T>(value));
    }

    template <typename T>
    void operator()(const char *name, T &&value) {
        details::BriefSyntaxFunction<JSONOutputArchive, T>::invoke(*this, std::forward<T>(value));
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
    explicit JSONOutputArchive(TArgs &&...args)
    : _adapter{std::forward<TArgs>(args)...}, _writerWrapper(_adapter), _jsonWriter(_writerWrapper) {
        _jsonWriter.SetMaxDecimalPlaces(JSONWriter::kDefaultMaxDecimalPlaces);
        _jsonWriter.SetIndent(' ', 4);
        _nameCounter.push(0);
        _nodeStack.push(NodeType::StartObject);
    }

    ~JSONOutputArchive() {
        if (_nodeStack.top() == NodeType::InObject)
            _jsonWriter.EndObject();
        else if (_nodeStack.top() == NodeType::InArray)
            _jsonWriter.EndArray();
    }

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
        assert((length + (traits::TextTraits<T>::addNUL ? 1u : 0u)) <= maxSize);
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
        _jsonWriter.Bool(v);
    }

    TWriter _adapter;
    WriterWrapper        _writerWrapper; //!< Rapidjson write stream
    JSONWriter           _jsonWriter;      //!< Rapidjson writer
    std::string          _nextName;    //!< The next name
    std::stack<uint32_t> _nameCounter; //!< Counter for creating unique names for unnamed nodes
    std::stack<NodeType> _nodeStack;
};
using StreamedJSONOutputArchive = JSONOutputArchive<bitsery::OutputStreamAdapter>;
} // namespace serialization
} // namespace cc