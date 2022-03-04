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

#define SERIALIZATION_VERSION 1
#define SERIALIZE_FUNCTION_NAME serialize
#define SERIALIZATION_BACKEND_CEREAL 1
#define SERIALIZATION_BACKEND_YAS 2
#define SERIALIZATION_BACKEND_BITSERY 3
#define SERIALIZATION_BACKEND_BUILTIN 4

#define SERIALIZATION_BACKEND SERIALIZATION_BACKEND_BUILTIN

#if SERIALIZATION_BACKEND == SERIALIZATION_BACKEND_CEREAL
    #define CEREAL_SERIALIZE_FUNCTION_NAME SERIALIZE_FUNCTION_NAME
    #include "cereal/macros.hpp"
    #include "cereal/access.hpp"
    #include "cereal/cereal.hpp"
    #include "cereal/archives/portable_binary.hpp"
    #include "cereal/types/vector.hpp"
    #define REGISTER_SERIALIZATION()         \
    private:                                \
        friend class cereal::access;        \
        template <class Archive>            \
        void SERIALIZE_FUNCTION_NAME(Archive &archive)

    #define SERIALIZE(ARCHIVE, T)                 ARCHIVE(cereal::make_nvp(#T, T))
    #define SERIALIZE_WITH_NAME(ARCHIVE, NAME, T) ARCHIVE(cereal::make_nvp(NAME, T))
    #define SERIALIZE_SUPER(ARCHIVE)              ARCHIVE(cereal::virtual_base_class<Super>(this))

    #define CEREAL_RAPIDJSON_NAMESPACE myRepidJson
    #include "cereal/archives/json.hpp"
         
    
namespace cc {
namespace serialization {

    using TextOutputArchive = cereal::JSONOutputArchive;
    using TextInputArchive = cereal::JSONInputArchive;
    using BinaryOutputArchive = cereal::PortableBinaryOutputArchive;
    using BinaryInputArchive = cereal::PortableBinaryInputArchive;
    using MemOstream = std::ostringstream;
    using MemIstream = std::istringstream;
}
} // namespace cc
#elif SERIALIZATION_BACKEND == SERIALIZATION_BACKEND_YAS
    #include "yas/serialize.hpp"
    #include "yas/object.hpp"
    #include "yas/std_types.hpp"
    #include "yas/binary_iarchive.hpp"
    #include "yas/binary_oarchive.hpp"
    #include "yas/json_iarchive.hpp"
    #include "yas/json_oarchive.hpp"
    #define REGISTER_SERIALIZATION() \
    public:                         \
        template <class Archive>     \
        void SERIALIZE_FUNCTION_NAME(Archive &archive)

    #define SERIALIZE(ARCHIVE, T)                 ARCHIVE(T)
    #define SERIALIZE_WITH_NAME(ARCHIVE, NAME, T) ARCHIVE(T)
    #define SERIALIZE_SUPER(ARCHIVE)              ARCHIVE(yas::base_object<Super>(*this));

namespace cc {
namespace serialization {

    using TextOutputArchive   = yas::json_oarchive<yas::std_ostream_adapter, yas::json | yas::ehost>;
    using TextInputArchive    = yas::json_iarchive<yas::std_istream_adapter, yas::json | yas::ehost>;
    using BinaryOutputArchive = yas::binary_oarchive<yas::std_ostream_adapter>;
    using BinaryInputArchive  = yas::binary_iarchive<yas::std_istream_adapter>;
    using MemOstream = yas::std_ostream_adapter;
    using MemIstream = yas::std_istream_adapter;
} // namespace serialization
} // namespace cc
#elif SERIALIZATION_BACKEND == SERIALIZATION_BACKEND_BITSERY
    #include "bitsery/brief_syntax.h"
    #include "bitsery/common.h"
    #include "bitsery/serializer.h"
    #include "bitsery/deserializer.h"
    #include "bitsery/adapter/stream.h"
    #include <bitsery/adapter/buffer.h>
    #include <bitsery/traits/vector.h>
    #include <bitsery/traits/array.h>
    #include <bitsery/traits/string.h>
    #define REGISTER_SERIALIZATION() \
    protected:                         \
        friend class bitsery::Access; \
        template <class Archive> inline \
        void SERIALIZE_FUNCTION_NAME(Archive &archive)

    #define SERIALIZE(ARCHIVE, T)                 ARCHIVE(T)
    #define SERIALIZE_WITH_NAME(ARCHIVE, NAME, T) ARCHIVE(T)

namespace cc {
namespace serialization {

using TextOutputArchive   = bitsery::Serializer<bitsery::OutputStreamAdapter>;
using TextInputArchive    = bitsery::Deserializer<bitsery::InputStreamAdapter>;
using BinaryOutputArchive = bitsery::Serializer<bitsery::OutputStreamAdapter>;
using BinaryInputArchive  = bitsery::Deserializer<bitsery::InputStreamAdapter>;
using MemOstream = bitsery::OutputStreamAdapter;
using MemIstream = bitsery::InputStreamAdapter;
} // namespace serialization
} // namespace cc
#else
    #include "bitsery/adapter/buffer.h"
    #include "bitsery/traits/array.h"
    #include "bitsery/traits/string.h"
    #include "bitsery/traits/vector.h"
    #include "bitsery/adapter/stream.h"
    #include "bitsery/brief_syntax.h"
    #include "bitsery/common.h"
    #include "builtin/BinaryOutputArchive.h"
    #include "builtin/BinaryInputArchive.h"
    #define REGISTER_SERIALIZATION()  \
    protected:                        \
        friend class bitsery::Access; \
        template <class Archive>      \
        inline void SERIALIZE_FUNCTION_NAME(Archive &archive)

    #define SERIALIZE(ARCHIVE, T)                 ARCHIVE(#T, T)
    #define SERIALIZE_WITH_NAME(ARCHIVE, NAME, T) ARCHIVE(NAME,T)

namespace cc {
namespace serialization {

// using TextOutputArchive   = bitsery::Serializer<bitsery::OutputStreamAdapter>;
// using TextInputArchive    = bitsery::Deserializer<bitsery::InputStreamAdapter>;
} // namespace serialization
} // namespace cc
#endif

#define SERIALIZATION_IMPL(TYPE)                                                          \
template void TYPE::SERIALIZE_FUNCTION_NAME(cc::serialization::StreamedBinaryOutputArchive &archive); \
template void TYPE::SERIALIZE_FUNCTION_NAME(cc::serialization::StreamedBinaryInputArchive &archive);  \
template void TYPE::SERIALIZE_FUNCTION_NAME(bitsery::Serializer<bitsery::OutputStreamAdapter> &archive);

