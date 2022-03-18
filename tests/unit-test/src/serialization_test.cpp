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
#include <fstream>
#include "cocos/math/Color.h"
#include "cocos/core/serialization/serialization.h"
#include <bitsery/adapter/measure_size.h>
#include <bitsery/ext/value_range.h>
#include <bitsery/serializer.h>
#include <bitsery/deserializer.h>
#include "gtest/gtest.h"

//some helper types
using Buffer = std::vector<char>;
using BufferWriter = cc::serialization::BufferWriter<Buffer>;
using BufferReader = cc::serialization::BufferReader<Buffer>;

class SerializationContext {
public:
    using TSerializer = cc::serialization::BinaryOutputArchive<BufferWriter>;
    using TDeserializer = cc::serialization::BinaryInputArchive<BufferReader>;

    Buffer buf{};
    std::unique_ptr<TSerializer> ser{};
    std::unique_ptr<TDeserializer> des{};

    TSerializer& createSerializer() {
        if (!ser) {
            ser = std::unique_ptr<TSerializer>(new TSerializer{buf});
        }
        return *ser;
    }


    TDeserializer& createDeserializer() {
        size_t writtenBytes = 0;
        if (ser) {
            ser->getAdapter().flush();
            writtenBytes = ser->getAdapter().writtenBytesCount();
        }
        if (!des) {
            des = std::unique_ptr<TDeserializer>(new TDeserializer{buf.begin(), writtenBytes});
        }
        return *des;
    }

    size_t getBufferSize() const {
        return ser->getAdapter().writtenBytesCount();
    }

    //since all containers .size() method returns size_t, it cannot be directly serialized, because size_t is platform dependant
    //this function returns number of bytes written to buffer, when reading/writing size of container
    static size_t containerSizeSerializedBytesCount(size_t elemsCount) {
        if (elemsCount < 0x80u)
            return 1;
        if (elemsCount < 0x4000u)
            return 2;
        return 4;
    }

};


using bitsery::ReaderError;

struct DisableAdapterErrorsConfig {
    static constexpr bitsery::EndiannessType Endianness         = bitsery::DefaultConfig::Endianness;
    static constexpr bool                    CheckAdapterErrors = false;
    static constexpr bool                    CheckDataErrors    = true;
};

struct MyStruct1 {
    MyStruct1(int32_t v1, int32_t v2) : i1{v1}, i2{v2} {}

    MyStruct1() : MyStruct1{0, 0} {}

    int32_t i1;
    int32_t i2;

    bool operator==(const MyStruct1 &rhs) const {
        return i1 == rhs.i1 && i2 == rhs.i2;
    }
    friend bool operator<(const MyStruct1 &lhs, const MyStruct1 &rhs) {
        return lhs.i1 < rhs.i1 || (lhs.i1 == rhs.i1 && lhs.i2 < rhs.i2);
    }

    static constexpr size_t SIZE = sizeof(MyStruct1::i1) + sizeof(MyStruct1::i2);
};

template <typename S>
void serialize(S &s, MyStruct1 &o) {
    s.template value<sizeof(o.i1)>(o.i1);
    s.template value<sizeof(o.i2)>(o.i2);
}

enum class MyEnumClass : int32_t {
    E1,
    E2,
    E3,
    E4,
    E5,
    E6
};

struct MyStruct2 {
    enum MyEnum {
        V1,
        V2,
        V3,
        V4,
        V5,
        V6
    };

    MyStruct2(MyEnum e, MyStruct1 s) : e1{e}, s1{s} {}

    MyStruct2() : MyStruct2{V1, {0, 0}} {}

    MyEnum    e1;
    MyStruct1 s1;

    bool operator==(const MyStruct2 &rhs) const {
        return e1 == rhs.e1 && s1 == rhs.s1;
    }

    static constexpr size_t SIZE = MyStruct1::SIZE + sizeof(MyStruct2::e1);
};

template <typename S>
void serialize(S &s, MyStruct2 &o) {
    s.template value<sizeof(o.e1)>(o.e1);
    s.object(o.s1);
}

template<class IArchive, class OArchive>
void testColor () {
    std::vector<cc::Color> colors;
    for (uint16_t i = 0; i < 100; i++) {
        colors.push_back(cc::Color(std::rand(), std::rand(), std::rand(), std::rand()));
    }
    std::ostringstream ss{};
    {
        OArchive oa(ss);
        for (uint16_t i = 0; i < 100; i++) {
            SERIALIZE_WITH_NAME(oa, "color" + std::to_string(i), colors[i]);
        }
    }

    {
        cc::Color                           temp;
        std::istringstream                  is{ss.str()};
        IArchive                            iar(is);
        for (uint16_t i = 0; i < 100; i++) {
            SERIALIZE_WITH_NAME(iar, "color" + std::to_string(i), temp);
            EXPECT_EQ(colors[i].a, temp.a);
            EXPECT_EQ(colors[i].r, temp.r);
            EXPECT_EQ(colors[i].g, temp.g);
            EXPECT_EQ(colors[i].b, temp.b);
        }
    }
}

template <class IArchive, class OArchive>
void testRandomAccess() {
    std::vector<cc::Color> colors;
    for (uint16_t i = 0; i < 100; i++) {
        colors.push_back(cc::Color(std::rand(), std::rand(), std::rand(), std::rand()));
    }
    std::vector<std::streampos> pos;
    std::ostringstream           os;
    {
        OArchive                      oa(os);
        for (uint16_t i = 0; i < 100; i++) {
            pos.push_back(os.tellp());
            SERIALIZE_WITH_NAME(oa, "color" + std::to_string(i), colors[i]);
        }
    }

    {
        cc::Color          temp;
        std::stringstream             is(os.str());
        IArchive                      iar(is);
        for (uint16_t i = 1; i < 100; i += 2) {
            is.seekg(pos[i]);
            SERIALIZE_WITH_NAME(iar, "color" + std::to_string(i), temp);
            EXPECT_EQ(colors[i].a, temp.a);
            EXPECT_EQ(colors[i].r, temp.r);
            EXPECT_EQ(colors[i].g, temp.g);
            EXPECT_EQ(colors[i].b, temp.b);
        }
    }
}

TEST(serializationTest, serializationTest1) {
    
    //testColor<cc::serialization::TextInputArchive, cc::serialization::TextOutputArchive>();
    testColor<cc::serialization::StreamedBinaryInputArchive, cc::serialization::StreamedBinaryOutputArchive>();
    //testRandomAccess<cc::serialization::TextInputArchive, cc::serialization::TextOutputArchive>();
    testRandomAccess<cc::serialization::StreamedBinaryInputArchive, cc::serialization::StreamedBinaryOutputArchive>();
    
    /*std::vector<cc::Color>               colors;
    for (uint32_t i = 0; i < 1000000; i++) {
        colors.push_back(cc::Color(std::rand(), std::rand(), std::rand(), std::rand()));
    }
    {
        std::ofstream                        os("C:\\Users\\Administrator\\Desktop\\data.txt", std::ios::binary);
        cc::serialization::StreamedBinaryOutputArchive oar(os);
        for (uint32_t i = 0; i < 1000000; i++) {
            oar.serialize("color" + std::to_string(i), colors[i]);
        }
    }*/
    
}

TEST(OutputBuffer, WhenInitialBufferIsEmptyThenResizeInAdapterConstructor) {
    //setup data
    Buffer buf{};
    EXPECT_EQ(buf.size(), 0);
    BufferWriter adapter{buf};
    EXPECT_GE(buf.size(), 1);
}

TEST(OutputBuffer, WhenSetWritePositionThenResizeUnderlyingBufferIfRequired) {
    //setup data
    Buffer        buf{};
    BufferWriter w{buf};
    const auto    initialSize = buf.size();
    EXPECT_EQ(buf.size(), initialSize);
    EXPECT_EQ(w.currentWritePos(), 0);
    w.currentWritePos(initialSize + 10);
    EXPECT_EQ(w.currentWritePos(), initialSize + 10);
    EXPECT_GE(buf.size(), initialSize + 10);
}

TEST(OutputBuffer, WhenSettingCurrentPositionBeforeBufferEndThenWrittenBytesCountIsNotAffected) {
    //setup data
    Buffer        buf{};
    BufferWriter w{buf};
    const auto    initialSize = buf.size();
    EXPECT_EQ(buf.size(), initialSize);
    EXPECT_EQ(w.writtenBytesCount(), 0);
    w.currentWritePos(initialSize + 10);
    w.writeBytes<8>(static_cast<uint64_t>(1));
    EXPECT_EQ(w.writtenBytesCount(), initialSize + 10 + 8);
    w.currentWritePos(0);
    EXPECT_EQ(w.writtenBytesCount(), initialSize + 10 + 8);
}

TEST(OutputBuffer, CanWorkWithFixedSizeBuffer) {
    //setup data
    std::array<uint8_t, 10>                               buf{};
    cc::serialization::BufferWriter<std::array<uint8_t, 10>> w{buf};
    const auto                                            initialSize = buf.size();
    EXPECT_EQ(buf.size(), initialSize);
    EXPECT_EQ(w.currentWritePos(), 0);
    w.currentWritePos(5);
    EXPECT_EQ(w.currentWritePos(), 5);
}

TEST(InputBuffer, CorrectlySetsAndGetsCurrentReadPosition) {
    Buffer buf{};
    buf.resize(100);
    BufferReader r{buf.begin(), 10};
    r.currentReadPos(5);
    EXPECT_EQ(r.currentReadPos(), 5);
    r.currentReadPos(0);
    EXPECT_EQ(r.currentReadPos(), 0);
    uint8_t tmp;
    r.readBytes<1>(tmp);
    EXPECT_EQ(r.currentReadPos(), 1);
}

TEST(InputBuffer, WhenSetReadPositionOutOfRangeThenDataOverflow) {
    Buffer buf{};
    buf.resize(100);
    BufferReader r{buf.begin(), 10};
    r.currentReadPos(10);
    EXPECT_EQ(r.error(), ReaderError::NoError);
    r.currentReadPos(11);
    EXPECT_EQ(r.error(), ReaderError::DataOverflow);
}

TEST(InputBuffer, WhenSetReadEndPositionOutOfRangeThenDataOverflow) {
    Buffer buf{};
    buf.resize(100);
    BufferReader r{buf.begin(), 10};
    r.currentReadEndPos(11);
    EXPECT_EQ(r.error(), ReaderError::DataOverflow);
}

TEST(InputBuffer, WhenReadEndPositionIsNotSetThenReturnZeroAsBufferEndPosition) {
    Buffer buf{};
    buf.resize(100);
    BufferReader r{buf.begin(), 10};
    EXPECT_EQ(r.currentReadEndPos(), 0);
    r.currentReadEndPos(5);
    EXPECT_EQ(r.currentReadEndPos(), 5);
    EXPECT_EQ(r.error(), ReaderError::NoError);
}

TEST(InputBuffer, WhenReadEndPositionIsNotZeroThenDataOverflowErrorWillBeIgnored) {
    Buffer buf{};
    buf.resize(100);
    BufferReader r{buf.begin(), 1};
    r.currentReadEndPos(1);
    uint32_t tmp{};
    r.readBytes<4>(tmp);
    EXPECT_EQ(tmp, 0);
    EXPECT_EQ(r.error(), ReaderError::NoError);
    r.currentReadEndPos(0);
    r.readBytes<4>(tmp);
    EXPECT_EQ(tmp, 0);
    EXPECT_EQ(r.error(), ReaderError::DataOverflow);
}

TEST(InputBuffer, WhenReadingPastReadEndPositionOrBufferEndThenReadPositionDoesntChange) {
    Buffer buf{};
    buf.resize(10);
    BufferReader r{buf.begin(), 3};
    uint32_t     tmp{};
    r.currentReadEndPos(2);
    r.readBytes<4>(tmp);
    EXPECT_EQ(r.currentReadPos(), 0);
    EXPECT_EQ(r.error(), ReaderError::NoError);
    EXPECT_EQ(tmp, 0);
    r.currentReadEndPos(0);
    r.readBytes<4>(tmp);
    EXPECT_EQ(r.currentReadPos(), 0);
    EXPECT_EQ(r.error(), ReaderError::DataOverflow);
    EXPECT_EQ(tmp, 0);
}

TEST(InputBuffer, WhenReaderHasErrorsThenSettingReadPosAndReadEndPosIsIgnoredAndGettingAlwaysReturnsZero) {
    Buffer buf{};
    buf.resize(10);
    BufferReader r{buf.begin(), 10};
    uint32_t     tmp{};
    r.readBytes<4>(tmp);
    r.currentReadEndPos(5);
    EXPECT_EQ(r.currentReadPos(), 4);
    EXPECT_EQ(r.currentReadEndPos(), 5);
    EXPECT_EQ(r.error(), ReaderError::NoError);
    r.currentReadEndPos(11);
    EXPECT_EQ(r.error(), ReaderError::DataOverflow);
    EXPECT_EQ(r.currentReadPos(), 0);
    EXPECT_EQ(r.currentReadEndPos(), 0);
    r.currentReadPos(1);
    r.currentReadEndPos(1);
    EXPECT_EQ(r.currentReadPos(), 0);
    EXPECT_EQ(r.currentReadEndPos(), 0);
}

TEST(InputBuffer, ConstDataForBufferAllAdapters) {
    //create and write to buffer
    uint16_t      data = 7549;
    Buffer        bufWrite{};
    BufferWriter bw{bufWrite};
    bw.writeBytes<2>(data);
    bw.flush();
    const Buffer buf{bufWrite};

    //read from buffer

    cc::serialization::BufferReader<const Buffer> r1{buf.begin(), buf.end()};

    uint16_t res1{};
    r1.readBytes<2>(res1);
    EXPECT_EQ(res1, data);
}

#ifndef NDEBUG
TEST(InputBuffer, WhenAdapterErrorsIsDisabledThenCanChangeAnyReadPositionAndReadsAsserts) {
    //create and write to buffer
    uint64_t      data = 0x1122334455667788;
    Buffer        buf{};
    BufferWriter bw{buf};
    bw.writeBytes<8>(data);
    bw.flush();

    bitsery::InputBufferAdapter<Buffer, DisableAdapterErrorsConfig> r1{buf.begin(), 2};
    uint16_t                                                        res1{};
    r1.readBytes<2>(res1);
    EXPECT_EQ(res1, 0x7788); // default config is little endian
    EXPECT_EQ(r1.currentReadPos(), 2);
    r1.currentReadPos(4);
    EXPECT_EQ(r1.currentReadPos(), 4);
    EXPECT_DEATH(r1.readBytes<2>(res1), ""); // default config is little endian
}
#endif

TEST(InputStream, WhenAdapterErrorsIsDisabledThenReadingPastEndDoesntSetErrorAndDoesntReturnZero) {
    //create and write to buffer
    std::stringstream            ss{};
    bitsery::OutputStreamAdapter bw{ss};
    uint32_t                     data = 0x12345678;
    bw.writeBytes<4>(data);
    bw.flush();

    bitsery::BasicInputStreamAdapter<char, DisableAdapterErrorsConfig, std::char_traits<char>> br{ss};
    uint32_t                                                                                   res{};
    br.readBytes<4>(res);
    EXPECT_EQ(res, data);
    br.readBytes<4>(res);
    EXPECT_EQ(res, data);
    EXPECT_EQ(br.isCompletedSuccessfully(), true);
}

template <template <typename...> class TAdapter>
struct InBufferConfig {
    using Data    = std::vector<char>;
    using Adapter = TAdapter<Data>;

    Data    data{};
    Adapter createReader(const std::vector<char> &buffer) {
        data = buffer;
        return Adapter{data.begin(), data.size()};
    }
};

template <typename TAdapter>
struct InStreamConfig {
    using Data    = std::stringstream;
    using Adapter = TAdapter;

    Data    data{};
    Adapter createReader(const std::vector<char> &buffer) {
        std::string str(buffer.begin(), buffer.end());
        data = std::stringstream{str};
        return Adapter{data};
    }
};

template <typename TAdapterWithData>
class AdapterConfig : public testing::Test {
public:
    TAdapterWithData config{};
};

using AdapterInputTypes = ::testing::Types<
    InBufferConfig<cc::serialization::BufferReader>,
    InStreamConfig<cc::serialization::StreamReader>>;

template <typename TConfig>
class InputAll : public AdapterConfig<TConfig> {
};

TYPED_TEST_SUITE(InputAll, AdapterInputTypes, );

TYPED_TEST(InputAll, SettingMultipleErrorsAlwaysReturnsFirstError) {
    auto r = this->config.createReader({0, 0, 0, 0});
    EXPECT_EQ(r.error(), ReaderError::NoError);
    r.error(ReaderError::InvalidPointer);
    EXPECT_EQ(r.error(), ReaderError::InvalidPointer);
    r.error(ReaderError::DataOverflow);
    EXPECT_EQ(r.error(), ReaderError::InvalidPointer);
    r.error(ReaderError::NoError);
    EXPECT_EQ(r.error(), ReaderError::InvalidPointer);
}

TYPED_TEST(InputAll, CanBeMoveConstructedAndMoveAssigned) {
    auto    r = this->config.createReader({1, 2, 3});
    uint8_t res{};
    r.template readBytes<1>(res);
    EXPECT_EQ(res, 1);
    // move construct
    auto r1 = std::move(r);
    r1.template readBytes<1>(res);
    EXPECT_EQ(res, 2);
    // move assign
    r = std::move(r1);
    r.template readBytes<1>(res);
    EXPECT_EQ(res, 3);
}

TYPED_TEST(InputAll, WhenAlignHasNonZerosThenInvalidDataError) {
    auto                                                         r = this->config.createReader({0x7F});
    bitsery::details::InputAdapterBitPackingWrapper<decltype(r)> bpr{r};

    uint8_t tmp{0xFF};
    bpr.readBits(tmp, 3);
    bpr.align();
    EXPECT_EQ(bpr.error(), ReaderError::InvalidData);
}

TYPED_TEST(InputAll, WhenAllBytesAreReadWithoutErrorsThenIsCompletedSuccessfully) {
    //setup data

    uint32_t tb = 94545646;
    int16_t  tc = -8778;
    uint8_t  td = 200;

    //create and write to buffer
    Buffer        buf{};
    BufferWriter bw{buf};

    bw.writeBytes<4>(tb);
    bw.writeBytes<2>(tc);
    bw.writeBytes<1>(td);
    bw.flush();
    buf.resize(bw.writtenBytesCount());

    auto br = this->config.createReader(buf);

    uint32_t rb = 94545646;
    int16_t  rc = -8778;
    uint8_t  rd = 200;

    br.template readBytes<4>(rb);
    EXPECT_EQ(br.error(), bitsery::ReaderError::NoError);
    br.template readBytes<2>(rc);
    EXPECT_EQ(br.error(), bitsery::ReaderError::NoError);
    EXPECT_EQ(br.isCompletedSuccessfully(), false);
    br.template readBytes<1>(rd);
    EXPECT_EQ(br.error(), bitsery::ReaderError::NoError);
    EXPECT_EQ(br.isCompletedSuccessfully(), true);

    EXPECT_EQ(rb, tb);
    EXPECT_EQ(rc, tc);
    EXPECT_EQ(rd, td);
}

TYPED_TEST(InputAll, WhenReadingMoreThanAvailableThenDataOverflow) {
    //setup data
    uint8_t t1 = 111;

    Buffer        buf{};
    BufferWriter w{buf};
    w.writeBytes<1>(t1);
    w.flush();
    buf.resize(w.writtenBytesCount());

    auto r = this->config.createReader(buf);

    uint8_t r1{};
    EXPECT_EQ(r.isCompletedSuccessfully(), false);
    EXPECT_EQ(r.error(), ReaderError::NoError);
    r.template readBytes<1>(r1);
    EXPECT_EQ(r.isCompletedSuccessfully(), true);
    EXPECT_EQ(r.error(), ReaderError::NoError);
    EXPECT_EQ(r1, t1);
    r.template readBytes<1>(r1);
    r.template readBytes<1>(r1);
    EXPECT_EQ(r1, 0);
    EXPECT_EQ(r.isCompletedSuccessfully(), false);
    EXPECT_EQ(r.error(), ReaderError::DataOverflow);
}

TYPED_TEST(InputAll, WhenReaderHasErrorsAllThenReadsReturnZero) {
    //setup data
    uint8_t t1 = 111;

    Buffer        buf{};
    BufferWriter w{buf};
    w.writeBytes<1>(t1);
    w.writeBytes<1>(t1);
    w.flush();
    buf.resize(w.writtenBytesCount());

    auto r = this->config.createReader(buf);

    uint8_t r1{};
    r.template readBytes<1>(r1);
    EXPECT_EQ(r1, t1);
    r.error(ReaderError::InvalidPointer);
    r.template readBytes<1>(r1);
    EXPECT_EQ(r1, 0);
}

template <template <typename...> class TAdapter>
struct OutBufferConfig {
    using Data    = std::vector<char>;
    using Adapter = TAdapter<Data>;

    Data    data{};
    Adapter createWriter() {
        return Adapter{data};
    }

    cc::serialization::BufferReader<Data> getReader() {
        return cc::serialization::BufferReader<Data>{data.begin(), data.end()};
    }
};

template <typename TAdapter>
struct OutStreamConfig {
    using Data    = std::stringstream;
    using Adapter = TAdapter;

    Data    data{};
    Adapter createWriter() {
        return Adapter{data};
    }

    cc::serialization::StreamReader getReader() {
        return cc::serialization::StreamReader{data};
    }
};

using AdapterOutputTypes = ::testing::Types<
    OutBufferConfig<cc::serialization::BufferWriter>,
    OutStreamConfig<cc::serialization::StreamWriter>
    /* OutStreamConfig<bitsery::OutputBufferedStreamAdapter>*/>;

template <typename TConfig>
class OutputAll : public AdapterConfig<TConfig> {
};

TYPED_TEST_SUITE(OutputAll, AdapterOutputTypes, );

TYPED_TEST(OutputAll, CanBeMoveConstructedAndMoveAssigned) {
    auto    w = this->config.createWriter();
    uint8_t data{1};
    w.template writeBytes<1>(data);
    // move construct
    auto w1 = std::move(w);
    data    = 2;
    w1.template writeBytes<1>(data);
    // move assignment
    w    = std::move(w1);
    data = 3;
    w.template writeBytes<1>(data);
    w.flush();

    auto r = this->config.getReader();
    r.template readBytes<1>(data);
    EXPECT_EQ(data, 1);
    r.template readBytes<1>(data);
    EXPECT_EQ(data, 2);
    r.template readBytes<1>(data);
    EXPECT_EQ(data, 3);
}

template <typename T>
class OutputStreamBuffered : public testing::Test {
public:
    using Buffer  = T;
    using Adapter = bitsery::BasicBufferedOutputStreamAdapter<char, bitsery::DefaultConfig, std::char_traits<char>, Buffer>;

    static constexpr size_t InternalBufferSize = 128;

    std::stringstream stream{};

    Adapter writer{stream, 128};
};

using BufferedAdapterInternalBufferTypes = ::testing::Types<
    std::vector<char>,
    std::array<char, 128>,
    std::string>;

TYPED_TEST_SUITE(OutputStreamBuffered, BufferedAdapterInternalBufferTypes, );

TYPED_TEST(OutputStreamBuffered, WhenInternalBufferIsFullThenWriteBufferToStream) {
    uint8_t x{};
    for (auto i = 0u; i < TestFixture::InternalBufferSize; ++i)
        this->writer.template writeBytes<1>(x);
    EXPECT_TRUE(this->stream.str().empty());
    this->writer.template writeBytes<1>(x);
    EXPECT_EQ(this->stream.str().size(), TestFixture::InternalBufferSize);
}

TYPED_TEST(OutputStreamBuffered, WhenFlushThenWriteImmediately) {
    uint8_t x{};
    this->writer.template writeBytes<1>(x);
    EXPECT_EQ(this->stream.str().size(), 0);
    this->writer.flush();
    EXPECT_EQ(this->stream.str().size(), 1);
    this->writer.flush();
    EXPECT_EQ(this->stream.str().size(), 1);
}

TYPED_TEST(OutputStreamBuffered, WhenBufferIsStackAllocatedThenBufferSizeViaCtorHasNoEffect) {
    //create writer with half the internal buffer size
    //for std::vector it should overflow, and for std::array it should have no effect
    typename TestFixture::Adapter w{this->stream, TestFixture::InternalBufferSize / 2};

    uint8_t x{};
    for (auto i = 0u; i < TestFixture::InternalBufferSize; ++i)
        w.template writeBytes<1>(x);
    static constexpr bool ShouldWriteToStream = bitsery::traits::ContainerTraits<typename TestFixture::Buffer>::isResizable;
    EXPECT_NE(this->stream.str().empty(), ShouldWriteToStream);
}

TEST(AdapterWriterMeasureSize, CorrectlyMeasuresWrittenBytesCountForSerialization) {
    bitsery::MeasureSize w{};
    EXPECT_EQ(w.writtenBytesCount(), 0);
    w.writeBytes<8>(uint64_t{0});
    EXPECT_EQ(w.writtenBytesCount(), 8);
    w.writeBuffer<8, uint64_t>(nullptr, 9);
    EXPECT_EQ(w.writtenBytesCount(), 80);
    w.currentWritePos(10);
    w.writeBytes<4>(uint32_t{0});
    EXPECT_EQ(w.writtenBytesCount(), 80);
    EXPECT_EQ(w.currentWritePos(), 14);
    w.currentWritePos(80);
    EXPECT_EQ(w.writtenBytesCount(), 80);
    w.writeBits(uint32_t{0}, 7u);
    EXPECT_EQ(w.writtenBytesCount(), 80);
    w.align();
    EXPECT_EQ(w.writtenBytesCount(), 81);
    w.writeBits(uint32_t{0}, 7u);
    w.flush();
    EXPECT_EQ(w.writtenBytesCount(), 82);
    // doesn't compile on older compilers if I write bitsery::MeasureSize::BitPackingEnabled directly in EXPECT_THAT macro.
    constexpr bool bpEnabled = bitsery::MeasureSize::BitPackingEnabled;
    EXPECT_EQ(bpEnabled, true);
}


TEST(BriefSyntax, FundamentalTypesAndBool) {
    int                  ti = 8745;
    MyEnumClass          te = MyEnumClass::E4;
    float                tf = 485.042f;
    double               td = -454184.48445;
    bool                 tb = true;
    SerializationContext ctx{};
    auto &                ser = ctx.createSerializer();
    ser("ti", ti);
    ser("te", te);
    ser("tf", tf);
    ser("td", td);
    ser("tb", tb);

    //result
    int         ri{};
    MyEnumClass re{};
    float       rf{};
    double      rd{};
    bool        rb{};
    auto &       des = ctx.createDeserializer();
    des("ri", ri);
    des("re", re);
    des("rf", rf);
    des("rd", rd);
    des("rb", rb);

    //test
    EXPECT_EQ(ri, ti);
    EXPECT_EQ(re, te);
    EXPECT_EQ(rf, tf);
    EXPECT_EQ(rd, td);
    EXPECT_EQ(rb, tb);
}

TEST(BriefSyntax, UseObjectFncInsteadOfValueN) {
    int                  ti = 8745;
    MyEnumClass          te = MyEnumClass::E4;
    float                tf = 485.042f;
    double               td = -454184.48445;
    bool                 tb = true;
    SerializationContext ctx;
    auto &               ser = ctx.createSerializer();
    ser.object(ti);
    ser.object(te);
    ser.object(tf);
    ser.object(td);
    ser.object(tb);

    //result
    int         ri{};
    MyEnumClass re{};
    float       rf{};
    double      rd{};
    bool        rb{};
    auto &      des = ctx.createDeserializer();
    des.object(ri);
    des.object(re);
    des.object(rf);
    des.object(rd);
    des.object(rb);

    //test
    EXPECT_EQ(ri, ti);
    EXPECT_EQ(re, te);
    EXPECT_EQ(rf, tf);
    EXPECT_EQ(rd, td);
    EXPECT_EQ(rb, tb);
}

TEST(BriefSyntax, MixDifferentSyntax) {
    int                  ti = 8745;
    MyEnumClass          te = MyEnumClass::E4;
    float                tf = 485.042f;
    double               td = -454184.48445;
    bool                 tb = true;
    SerializationContext ctx;
    auto &               ser = ctx.createSerializer();
    ser.value<sizeof(ti)>(ti);
    ser("te", te);
    ser("tf", tf);
    ser("td", td);
    ser.object(tb);

    //result
    int         ri{};
    MyEnumClass re{};
    float       rf{};
    double      rd{};
    bool        rb{};
    auto &      des = ctx.createDeserializer();
    des("ri", ri);
    des("re", re);
    des("rf", rf);
    des.value<8>(rd);
    des.object(rb);

    //test
    EXPECT_EQ(ri, ti);
    EXPECT_EQ(re, te);
    EXPECT_EQ(rf, tf);
    EXPECT_EQ(rd, td);
    EXPECT_EQ(rb, tb);
}

template <typename T>
T procBriefSyntax(const T &testData) {
    SerializationContext ctx;
    auto & ser = ctx.createSerializer();
    ser("testData", testData);
    T res{};
    auto & des = ctx.createDeserializer();
    des("res", res);
    return res;
}

template <typename T>
T &&procBriefSyntaxRvalue(T &&init_value, const T &testData) {
    SerializationContext ctx;
    auto & ser = ctx.createSerializer();
    
    ser("testData", testData);
    auto & des = ctx.createDeserializer();
    
    des("testData", init_value);
    return std::move(init_value);
}

template <typename T>
T procBriefSyntaxWithMaxSize(const T &testData) {
    SerializationContext ctx;
    auto &               ser = ctx.createSerializer();
    ser("testData", bitsery::maxSize(testData, 100));
    T res{};
    auto &des = ctx.createDeserializer();
    des("testData", bitsery::maxSize(res, 100));
    return res;
}

TEST(BriefSyntax, CStyleArrayForValueTypesAsContainer) {
    const int t1[3]{8748, -484, 45};
    int       r1[3]{0, 0, 0};

    SerializationContext ctx;
    auto &               ser = ctx.createSerializer();
    ser("t1", bitsery::asContainer(t1));
    auto & des = ctx.createDeserializer();
    
    des("r1", bitsery::asContainer(r1));
    for (uint16_t i = 0; i < 3; i++) {
        EXPECT_EQ(r1[i], t1[i]);
    }
    
}

TEST(BriefSyntax, CStyleArrayForIntegralTypesAsText) {
    const char t1[3]{"hi"};
    char       r1[3]{0, 0, 0};

    SerializationContext ctx;
    auto &               ser = ctx.createSerializer();
    ser("t1", bitsery::asText(t1));
    auto & des = ctx.createDeserializer();
    des("r1", bitsery::asText(r1));

    for (uint16_t i = 0; i < 3; i++) {
        EXPECT_EQ(r1[i], t1[i]);
    }
}

TEST(BriefSyntax, CStyleArray) {
    const MyEnumClass t1[3]{MyEnumClass::E1, MyEnumClass::E4, MyEnumClass::E2};
    MyEnumClass       r1[3]{};

    SerializationContext ctx;
    auto & ser = ctx.createSerializer();
    
    ser("t1", t1);
    auto &des = ctx.createDeserializer();
    des("r1", r1);

    for (uint16_t i = 0; i < 3; i++) {
        EXPECT_EQ(r1[i], t1[i]);
    }
}

TEST(BriefSyntax, StdString) {
    std::string t1{"my nice string"};
    std::string t2{};

    EXPECT_EQ(procBriefSyntax(t1), t1);
    EXPECT_EQ(procBriefSyntax(t2), t2);
    EXPECT_EQ(procBriefSyntaxWithMaxSize(t1), t1);
    EXPECT_EQ(procBriefSyntaxWithMaxSize(t2), t2);
}

//TEST(BriefSyntax, StdArray) {
//    std::array<int, 3> t1{8748, -484, 45};
//    std::array<int, 0> t2{};
//
//    EXPECT_EQ(procBriefSyntax(t1), t1);
//    EXPECT_EQ(procBriefSyntax(t2), t2);
//}
//
TEST(BriefSyntax, StdVector) {
    std::vector<int>   t1{8748, -484, 45};
    std::vector<float> t2{5.f, 0.198f};

    EXPECT_EQ(procBriefSyntax(t1), t1);
    EXPECT_EQ(procBriefSyntax(t2), t2);
    EXPECT_EQ(procBriefSyntaxWithMaxSize(t1), t1);
    EXPECT_EQ(procBriefSyntaxWithMaxSize(t2), t2);
}

//TEST(BriefSyntax, StdList) {
//    std::list<int>   t1{8748, -484, 45};
//    std::list<float> t2{5.f, 0.198f};
//
//    EXPECT_EQ(procBriefSyntax(t1), t1);
//    EXPECT_EQ(procBriefSyntax(t2), t2);
//    EXPECT_EQ(procBriefSyntaxWithMaxSize(t1), t1);
//    EXPECT_EQ(procBriefSyntaxWithMaxSize(t2), t2);
//}
//
//TEST(BriefSyntax, StdForwardList) {
//    std::forward_list<int>   t1{8748, -484, 45};
//    std::forward_list<float> t2{5.f, 0.198f};
//
//    EXPECT_EQ(procBriefSyntax(t1), t1);
//    EXPECT_EQ(procBriefSyntax(t2), t2);
//    EXPECT_EQ(procBriefSyntaxWithMaxSize(t1), t1);
//    EXPECT_EQ(procBriefSyntaxWithMaxSize(t2), t2);
//}
//
//TEST(BriefSyntax, StdDeque) {
//    std::deque<int>   t1{8748, -484, 45};
//    std::deque<float> t2{5.f, 0.198f};
//
//    EXPECT_EQ(procBriefSyntax(t1), t1);
//    EXPECT_EQ(procBriefSyntax(t2), t2);
//    EXPECT_EQ(procBriefSyntaxWithMaxSize(t1), t1);
//    EXPECT_EQ(procBriefSyntaxWithMaxSize(t2), t2);
//}
//
//TEST(BriefSyntax, StdQueue) {
//    std::queue<std::string> t1;
//    t1.push("first");
//    t1.push("second string");
//
//    EXPECT_EQ(procBriefSyntax(t1), t1);
//    EXPECT_EQ(procBriefSyntaxWithMaxSize(t1), t1);
//}
//
//TEST(BriefSyntax, StdPriorityQueue) {
//    std::priority_queue<std::string> t1;
//    t1.push("first");
//    t1.push("second string");
//    t1.push("third");
//    t1.push("fourth");
//    auto r1 = procBriefSyntax(t1);
//    //we cannot compare priority queue directly
//
//    EXPECT_EQ(r1.size(), t1.size());
//    for (auto i = 0u; i < r1.size(); ++i) {
//        EXPECT_EQ(r1.top(), t1.top());
//        r1.pop();
//        t1.pop();
//    }
//}
//
//TEST(BriefSyntax, StdStack) {
//    std::stack<std::string> t1;
//    t1.push("first");
//    t1.push("second string");
//
//    EXPECT_EQ(procBriefSyntax(t1), t1);
//    EXPECT_EQ(procBriefSyntaxWithMaxSize(t1), t1);
//}
//
//TEST(BriefSyntax, StdUnorderedMap) {
//    std::unordered_map<int, int> t1;
//    t1.emplace(3423, 624);
//    t1.emplace(-5484, -845);
//
//    EXPECT_EQ(procBriefSyntax(t1), t1);
//    EXPECT_EQ(procBriefSyntaxWithMaxSize(t1), t1);
//}

//TEST(BriefSyntax, StdUnorderedMultiMap) {
//    std::unordered_multimap<std::string, int> t1;
//    t1.emplace("one", 624);
//    t1.emplace("two", -845);
//    t1.emplace("one", 897);
//
//    EXPECT_TRUE(procBriefSyntax(t1) == t1);
//    EXPECT_TRUE(procBriefSyntaxWithMaxSize(t1) == t1);
//}

//TEST(BriefSyntax, StdMap) {
//    std::map<int, int> t1;
//    t1.emplace(3423, 624);
//    t1.emplace(-5484, -845);
//
//    EXPECT_EQ(procBriefSyntax(t1), t1);
//    EXPECT_EQ(procBriefSyntaxWithMaxSize(t1), t1);
//}

//TEST(BriefSyntax, StdMultiMap) {
//    std::multimap<std::string, int> t1;
//    t1.emplace("one", 624);
//    t1.emplace("two", -845);
//    t1.emplace("one", 897);
//
//    auto res = procBriefSyntax(t1);
//    //same key values is not ordered, and operator == compares each element at same position
//    //so we need to compare our selves
//    EXPECT_EQ(res.size(), 3);
//    for (auto it = t1.begin(); it != t1.end();) {
//        const auto lr = t1.equal_range(it->first);
//        const auto rr = res.equal_range(it->first);
//        EXPECT_TRUE(std::distance(lr.first, lr.second) == std::distance(rr.first, rr.second));
//        EXPECT_TRUE(std::is_permutation(lr.first, lr.second, rr.first));
//        it = lr.second;
//    }
//}

//TEST(BriefSyntax, StdUnorderedSet) {
//    std::unordered_set<std::string> t1;
//    t1.emplace("one");
//    t1.emplace("two");
//    t1.emplace("three");
//
//    EXPECT_TRUE(procBriefSyntax(t1) == t1);
//    EXPECT_TRUE(procBriefSyntaxWithMaxSize(t1) == t1);
//}
//
//TEST(BriefSyntax, StdUnorderedMultiSet) {
//    std::unordered_multiset<std::string> t1;
//    t1.emplace("one");
//    t1.emplace("two");
//    t1.emplace("three");
//    t1.emplace("one");
//
//    EXPECT_TRUE(procBriefSyntax(t1) == t1);
//    EXPECT_TRUE(procBriefSyntaxWithMaxSize(t1) == t1);
//}

//TEST(BriefSyntax, StdSet) {
//    std::set<std::string> t1;
//    t1.emplace("one");
//    t1.emplace("two");
//    t1.emplace("three");
//
//    EXPECT_TRUE(procBriefSyntax(t1) == t1);
//    EXPECT_TRUE(procBriefSyntaxWithMaxSize(t1) == t1);
//}

//TEST(BriefSyntax, StdMultiSet) {
//    std::multiset<std::string> t1;
//    t1.emplace("one");
//    t1.emplace("two");
//    t1.emplace("three");
//    t1.emplace("one");
//    t1.emplace("two");
//
//    EXPECT_TRUE(procBriefSyntax(t1) == t1);
//    EXPECT_TRUE(procBriefSyntaxWithMaxSize(t1) == t1);
//}

//TEST(BriefSyntax, StdSmartPtr) {
//    std::shared_ptr<int>         dataShared1(new int{4});
//    std::weak_ptr<int>           dataWeak1(dataShared1);
//    std::unique_ptr<std::string> dataUnique1{new std::string{"hello world"}};
//
//    bitsery::ext::PointerLinkingContext                            plctx1{};
//    BasicSerializationContext<bitsery::ext::PointerLinkingContext> ctx;
//    ctx.createSerializer(plctx1)(dataShared1, dataWeak1, dataUnique1);
//
//    std::shared_ptr<int>         resShared1{};
//    std::weak_ptr<int>           resWeak1{};
//    std::unique_ptr<std::string> resUnique1{};
//    ctx.createDeserializer(plctx1)(resShared1, resWeak1, resUnique1);
//    //clear shared state from pointer linking context
//    plctx1.clearSharedState();
//
//    EXPECT_TRUE(plctx1.isValid());
//    EXPECT_EQ(*resShared1, *dataShared1);
//    EXPECT_EQ(*resWeak1.lock(), *dataWeak1.lock());
//    EXPECT_EQ(*resUnique1, *dataUnique1);
//}

//TEST(BriefSyntax, StdDuration) {
//    std::chrono::duration<int64_t, std::milli> t1{54654};
//    EXPECT_TRUE(procBriefSyntax(t1) == t1);
//}
//
//TEST(BriefSyntax, StdTimePoint) {
//    using Duration = std::chrono::duration<double, std::milli>;
//    using TP       = std::chrono::time_point<std::chrono::system_clock, Duration>;
//
//    TP data{Duration{874656.4798}};
//    EXPECT_TRUE(procBriefSyntax(data) == data);
//}
//
//TEST(BriefSyntax, StdAtomic) {
//    std::atomic<int32_t> atm0{54654};
//    EXPECT_TRUE(procBriefSyntaxRvalue(std::atomic<int32_t>{}, atm0) == atm0);
//
//    std::atomic<bool> atm1{false};
//    EXPECT_TRUE(procBriefSyntaxRvalue(std::atomic<bool>{}, atm1) == atm1);
//
//    std::atomic<bool> atm2{true};
//    EXPECT_TRUE(procBriefSyntaxRvalue(std::atomic<bool>{}, atm2) == atm2);
//
//    std::atomic<uint16_t> atm3;
//    atm3.store(0x1337);
//    EXPECT_TRUE(procBriefSyntaxRvalue(std::atomic<uint16_t>{}, atm3).load() == 0x1337);
//}

//TEST(BriefSyntax, NestedTypes) {
//    std::unordered_map<std::string, std::vector<std::string>> t1;
//    t1.emplace("my key", std::vector<std::string>{"very", "nice", "string"});
//    t1.emplace("other key", std::vector<std::string>{"just a string"});
//
//    EXPECT_EQ(procBriefSyntax(t1), t1);
//    EXPECT_EQ(procBriefSyntaxWithMaxSize(t1), t1);
//}

TEST(SerializeBooleans, BoolAsByte) {
    SerializationContext ctx;
    bool                 t1{true};
    bool                 t2{false};
    bool                 res1;
    bool                 res2;
    auto &               ser = ctx.createSerializer();
    ser.boolValue(t1);
    ser.boolValue(t2);
    auto &des = ctx.createDeserializer();
    des.boolValue(res1);
    des.boolValue(res2);

    EXPECT_EQ(res1, t1);
    EXPECT_EQ(res2, t2);
    EXPECT_EQ(ctx.getBufferSize(), 2);
}

TEST(SerializeBooleans, WhenReadingBoolByteReadsMoreThanOneThenInvalidDataErrorAndResultIsFalse) {
    SerializationContext ctx;
    auto &               ser = ctx.createSerializer();
    ser.value<1>(uint8_t{1});
    ser.value<1>(uint8_t{2});
    bool  res{};
    auto &des = ctx.createDeserializer();
    des.boolValue(res);
    EXPECT_EQ(res, true);
    des.boolValue(res);
    EXPECT_EQ(res, false);
    EXPECT_EQ(ctx.des->getAdapter().error(), bitsery::ReaderError::InvalidData);
}

TEST(SerializeText, BasicString) {
    SerializationContext ctx;
    std::string          t1 = "some random text";
    std::string          res;

    ctx.createSerializer().text<sizeof(std::string::value_type)>(t1, 1000);
    ctx.createDeserializer().text<sizeof(std::string::value_type)>(res, 1000);

    EXPECT_EQ(res, t1);
}

TEST(SerializeText, WhenSizeOfTypeNotEqualsOneThenSetSizeExplicitly) {
    SerializationContext        ctx;
    constexpr auto              VSIZE = sizeof(char32_t);
    std::basic_string<char32_t> t1    = U"some random text";
    std::basic_string<char32_t> res;
    static_assert(VSIZE > 1, "on this system, all character types has sizeof == 1, cannot run this tests");

    ctx.createSerializer().text<VSIZE>(t1, 1000);
    ctx.createDeserializer().text<VSIZE>(res, 1000);

    EXPECT_EQ(res, t1);
}

TEST(SerializeText, BasicStringUseSizeMethodNotNullterminatedLength) {
    SerializationContext ctx;
    std::wstring         t1(L"some random text\0xxxxxx", 20);
    std::wstring         wres;
    constexpr auto       VSIZE = sizeof(std::wstring::value_type);

    ctx.createSerializer().text<VSIZE>(t1, 1000);
    ctx.createDeserializer().text<VSIZE>(wres, 1000);

    EXPECT_EQ(wres, t1);
    EXPECT_EQ(wres.size(), t1.size());
    EXPECT_GT(wres.size(), std::char_traits<std::wstring::value_type>::length(t1.data()));

    SerializationContext ctx2;
    std::string          t2("\0no one cares what is there", 10);
    std::string          res;
    ctx2.createSerializer().text<sizeof(std::string::value_type)>(t2, 1000);
    ctx2.createDeserializer().text<sizeof(std::string::value_type)>(res, 1000);

    EXPECT_EQ(res, t2);
    EXPECT_EQ(res.size(), t2.size());

    SerializationContext ctx3;
    std::string          t3("never ending buffer that doesnt fit in this string", 10);
    ctx3.createSerializer().text<sizeof(std::string::value_type)>(t3, 1000);
    ctx3.createDeserializer().text<sizeof(std::string::value_type)>(res, 1000);
    EXPECT_EQ(res, t3);
    EXPECT_EQ(res.size(), 10);
}

constexpr int CARR_LENGTH = 10;

TEST(SerializeText, CArraySerializesTextLength) {
    SerializationContext ctx;
    char                 t1[CARR_LENGTH]{"some text"};
    char                 r1[CARR_LENGTH]{};

    ctx.createSerializer().text<1>(t1);
    ctx.createDeserializer().text<1>(r1);

    EXPECT_EQ(ctx.getBufferSize(), ctx.containerSizeSerializedBytesCount(CARR_LENGTH) +
                                        std::char_traits<char>::length(t1));
    for (uint16_t i = 0; i < CARR_LENGTH; i++) {
        EXPECT_EQ(r1[i], t1[i]);
    }
    
    //zero length string
    t1[0] = 0;
    SerializationContext ctx2;
    ctx2.createSerializer().text<1>(t1);
    ctx2.createDeserializer().text<1>(r1);

    EXPECT_EQ(ctx2.getBufferSize(), ctx2.containerSizeSerializedBytesCount(CARR_LENGTH));
    // TODO
    EXPECT_EQ(r1[0], t1[0]);
}

#ifndef NDEBUG
TEST(SerializeText, WhenCArrayNotNullterminatedThenAssert) {
    SerializationContext ctx;
    char16_t             t1[CARR_LENGTH]{u"some text"};
    //make last character not nullterminated
    t1[CARR_LENGTH - 1] = 'x';
    EXPECT_DEATH(ctx.createSerializer().text<2>(t1), "");
}
#endif

TEST(SerializeText, WhenContainerOrTextSizeIsMoreThanMaxThenInvalidDataError) {
    SerializationContext ctx;
    std::string          tmp = "larger text then allowed";
    ctx.createSerializer().text<1>(tmp, 100);
    ctx.createDeserializer().text<1>(tmp, 10);
    EXPECT_EQ(ctx.des->getAdapter().error(), bitsery::ReaderError::InvalidData);
}

struct X {
    X(){};
    X(int v) : x{v} {}
    std::string s{};
    int         x{};
    bool        operator==(const X &r) const {
        return r.x == x && r.s == s;
    }
};

struct Y {
    int                y{};
    std::array<int, 3> arr{};
    std::vector<X>     vx{};
    std::string        s{};
};
struct Z {
    X x{};
    Y y{};
};

template <typename S>
void serialize(S &s, Z &o) {
    s.object(o.x);
    s.object(o.y);
}

template <typename S>
void serialize(S &s, X &o) {
    s.template value<sizeof(o.x)>(o.x);
    s.template text<1>(o.s, 1000);
}

template <typename S>
void serialize(S &s, Y &o) {
    s.template text<1>(o.s, 10000);
    s.template value<sizeof(o.y)>(o.y);
    s("arr", o.arr);
    s("vx", o.vx);
}

TEST(SerializeObject, GeneralConceptTest) {
    //std::string buf;
    SerializationContext ctx;
    Y                    y{};
    y.y       = 3423;
    y.arr[0]  = 111;
    y.arr[1]  = 222;
    y.arr[2]  = 333;
    y.vx.push_back(X(234));
    y.vx.push_back(X(6245));
    y.vx.push_back(X(613461));
    y.s = "labal diena";

    Z z{};
    z.y = y;
    z.x = X{234};

    auto &ser = ctx.createSerializer();
    ser.object(y);
    ser.object(z);

    Y yres{};
    Z zres{};

    auto &des = ctx.createDeserializer();
    des.object(yres);
    des.object(zres);

    EXPECT_EQ(yres.y, y.y);
    EXPECT_EQ(yres.vx, y.vx);
    EXPECT_EQ(yres.arr, y.arr);
    
    EXPECT_EQ(yres.s, y.s);

    EXPECT_EQ(zres.y.y, z.y.y);
    EXPECT_EQ(zres.y.vx, z.y.vx);
    EXPECT_EQ(zres.y.arr, z.y.arr);
    EXPECT_EQ(zres.y.s, z.y.s);
    EXPECT_EQ(zres.x.s, z.x.s);
    EXPECT_EQ(zres.x.x, z.x.x);
}

bool SerializeDeserializeContainerSize(SerializationContext &ctx, const size_t size) {
    std::vector<char> t1(size);
    auto &            ser = ctx.createSerializer();
    ser.container(t1, size + 1);
    t1.clear();
    auto &des = ctx.createDeserializer();
    des.container(t1, size + 1);
    return t1.size() == size;
}

TEST(SerializeSize, WhenLengthLessThan128Then1Byte) {
    SerializationContext ctx1{};
    EXPECT_TRUE(SerializeDeserializeContainerSize(ctx1, 127));
    SerializationContext ctx2;
    EXPECT_TRUE(SerializeDeserializeContainerSize(ctx2, 128));
}

TEST(SerializeSize, WhenLengthLessThan16384Then2Bytes) {
    SerializationContext ctx1;
    EXPECT_TRUE(SerializeDeserializeContainerSize(ctx1, 16383));
    SerializationContext ctx2;
    EXPECT_TRUE(SerializeDeserializeContainerSize(ctx2, 16384));
}

TEST(SerializeSize, WhenGreaterThan16383Then4Bytes) {
    SerializationContext ctx1;
    EXPECT_TRUE(SerializeDeserializeContainerSize(ctx1, 16384));
    SerializationContext ctx2;
    EXPECT_TRUE(SerializeDeserializeContainerSize(ctx2, 66384));
}

template <typename T>
bool SerializeDeserializeValue(const T &v) {
    T                    res{};
    SerializationContext ctx;
    ctx.createSerializer().value<sizeof(T)>(v);
    ctx.createDeserializer().value<sizeof(T)>(res);
    return v == res;
}

TEST(SerializeValues, IntegerTypes) {
    EXPECT_EQ(SerializeDeserializeValue(-449874), true);
    EXPECT_EQ(SerializeDeserializeValue(34u), true);
}

TEST(SerializeValues, EnumTypes) {
    enum E1 {
        A1,
        B1,
        C1,
        D1
    };
    EXPECT_EQ(SerializeDeserializeValue(E1::C1), true);
    enum class E2 {
        A2,
        B2,
        C2,
        D2
    };
    EXPECT_EQ(SerializeDeserializeValue(E2::B2), true);
    enum class E3 : short {
        A3,
        B3,
        C3 = 4568,
        D3
    };
    EXPECT_EQ(SerializeDeserializeValue(E3::C3), true);
}

TEST(SerializeValues, FloatingPointTypes) {
    EXPECT_EQ(SerializeDeserializeValue(-484.465), true);
    EXPECT_EQ(SerializeDeserializeValue(0.00000015f), true);
}

TEST(SerializeValues, ValueSizeOverload1Byte) {
    int8_t           v{54};
    int8_t           res;
    constexpr size_t TSIZE = sizeof(v);

    SerializationContext ctx;
    ctx.createSerializer().value<1>(v);
    ctx.createDeserializer().value<1>(res);

    EXPECT_EQ(res, v);
    EXPECT_EQ(TSIZE, ctx.getBufferSize());
}

TEST(SerializeValues, ValueSizeOverload2Byte) {
    int16_t          v{54};
    int16_t          res;
    constexpr size_t TSIZE = sizeof(v);

    SerializationContext ctx;
    ctx.createSerializer().value<2>(v);
    ctx.createDeserializer().value<2>(res);

    EXPECT_EQ(res, v);
    EXPECT_EQ(TSIZE, ctx.getBufferSize());
}

TEST(SerializeValues, ValueSizeOverload4Byte) {
    float            v{54.498f};
    float            res;
    constexpr size_t TSIZE = sizeof(v);

    SerializationContext ctx;
    ctx.createSerializer().value<4>(v);
    ctx.createDeserializer().value<4>(res);

    EXPECT_EQ(res, v);
    EXPECT_EQ(TSIZE, ctx.getBufferSize());
}

TEST(SerializeValues, ValueSizeOverload8Byte) {
    int64_t          v{54};
    int64_t          res;
    constexpr size_t TSIZE = sizeof(v);

    SerializationContext ctx;
    ctx.createSerializer().value<8>(v);
    ctx.createDeserializer().value<8>(res);

    EXPECT_EQ(res, v);
    EXPECT_EQ(TSIZE, ctx.getBufferSize());
}

constexpr EndiannessType getInverseEndianness(EndiannessType e) {
    return e == EndiannessType::LittleEndian
               ? EndiannessType::BigEndian
               : EndiannessType::LittleEndian;
}

struct InverseEndiannessConfig {
    static constexpr bitsery::EndiannessType Endianness         = getInverseEndianness(DefaultConfig::Endianness);
    static constexpr bool                    CheckDataErrors    = true;
    static constexpr bool                    CheckAdapterErrors = true;
};

struct IntegralTypesB {
    int64_t  a;
    uint32_t b;
    int16_t  c;
    uint8_t  d;
    int8_t   e;
};

using InverseReader = bitsery::InputBufferAdapter<Buffer, InverseEndiannessConfig>;

TEST(DataEndianness, WhenWriteBytesThenBytesAreSwapped) {
    //fill initial values
    IntegralTypesB src{};
    src.a = static_cast<int64_t>(0x1122334455667788u);
    src.b = 0xBBCCDDEEu;
    src.c = static_cast<int16_t>(0xCCDDu);
    src.d = static_cast<uint8_t>(0xDDu);
    src.e = static_cast<int8_t>(0xEEu);

    //fill expected result after swap
    IntegralTypesB resInv{};
    resInv.a = static_cast<int64_t>(0x8877665544332211u);
    resInv.b = 0xEEDDCCBBu;
    resInv.c = static_cast<int16_t>(0xDDCCu);
    resInv.d = static_cast<uint8_t>(0xDDu);
    resInv.e = static_cast<int8_t>(0xEEu);

    //create and write to buffer
    Buffer buf{};
    BufferWriter bw{buf};
    bw.writeBytes<8>(src.a);
    bw.writeBytes<4>(src.b);
    bw.writeBytes<2>(src.c);
    bw.writeBytes<1>(src.d);
    bw.writeBytes<1>(src.e);
    bw.flush();
    //read from buffer using inverse endianness config
    InverseReader br{buf.begin(), bw.writtenBytesCount()};
    IntegralTypesB res{};
    br.readBytes<8>(res.a);
    br.readBytes<4>(res.b);
    br.readBytes<2>(res.c);
    br.readBytes<1>(res.d);
    br.readBytes<1>(res.e);
    //check results
    EXPECT_EQ(res.a, resInv.a);
    EXPECT_EQ(res.b, resInv.b);
    EXPECT_EQ(res.c, resInv.c);
    EXPECT_EQ(res.d, resInv.d);
    EXPECT_EQ(res.e, resInv.e);
}

TEST(DataEndianness, WhenWrite1ByteValuesThenEndiannessIsIgnored) {
    //fill initial values
    constexpr size_t SIZE      = 4;
    uint8_t          src[SIZE] = {0xAA, 0xBB, 0xCC, 0xDD};
    uint8_t          res[SIZE] = {};
    //create and write to buffer
    Buffer buf{};
    BufferWriter bw{buf};
    bw.writeBuffer<1>(src, SIZE);
    bw.flush();
    //read from buffer using inverse endianness config
    InverseReader br{buf.begin(), bw.writtenBytesCount()};
    br.readBuffer<1>(res, SIZE);
    //result is identical, because we write separate values, of size 1byte, that requires no swapping
    //check results
    for (uint32_t i = 0; i < SIZE; i++) {
        EXPECT_EQ(res[i], src[i]);
    }
}

TEST(DataEndianness, WhenWriteMoreThan1ByteValuesThenValuesAreSwapped) {
    //fill initial values
    constexpr size_t SIZE         = 4;
    uint16_t         src[SIZE]    = {0xAA00, 0xBB11, 0xCC22, 0xDD33};
    uint16_t         resInv[SIZE] = {0x00AA, 0x11BB, 0x22CC, 0x33DD};
    uint16_t         res[SIZE]    = {};
    //create and write to buffer
    Buffer buf{};
    BufferWriter bw{buf};
    bw.writeBuffer<2>(src, SIZE);
    bw.flush();
    //read from buffer using inverse endianness config
    InverseReader br{buf.begin(), bw.writtenBytesCount()};
    br.readBuffer<2>(res, SIZE);
    //result is identical, because we write separate values, of size 1byte, that requires no swapping
    //check results
    for (uint32_t i = 0; i < SIZE; i++) {
        EXPECT_EQ(res[i], resInv[i]);
    }
}

template <typename T>
constexpr size_t getBits(T v) {
    return bitsery::details::calcRequiredBits<T>({}, v);
}

struct IntegralUnsignedTypes {
    uint64_t a;
    uint32_t b;
    uint16_t c;
    uint8_t  d;
};

TEST(DataEndianness, WhenValueTypeIs1ByteThenBitOperationsIsNotAffectedByEndianness) {
    //fill initial values
    constexpr IntegralUnsignedTypes src{
        0x0000334455667788,
        0x00CCDDEE,
        0x00DD,
        0x0F,
    };

    constexpr size_t aBITS = getBits(src.a) + 8;
    constexpr size_t bBITS = getBits(src.b) + 0;
    constexpr size_t cBITS = getBits(src.c) + 5;
    constexpr size_t dBITS = getBits(src.d) + 2;
    //create and write to buffer
    Buffer                                                   buf{};
    BufferWriter                                                   bw{buf};
    bitsery::details::OutputAdapterBitPackingWrapper<BufferWriter> bpw{bw};
    bpw.writeBits(src.a, aBITS);
    bpw.writeBits(src.b, bBITS);
    bpw.writeBits(src.c, cBITS);
    bpw.writeBits(src.d, dBITS);
    bpw.flush();
    //read from buffer using inverse endianness config
    InverseReader                                                  br{buf.begin(), bpw.writtenBytesCount()};
    bitsery::details::InputAdapterBitPackingWrapper<InverseReader> bpr{br};
    IntegralUnsignedTypes                                          res{};
    bpr.readBits(res.a, aBITS);
    bpr.readBits(res.b, bBITS);
    bpr.readBits(res.c, cBITS);
    bpr.readBits(res.d, dBITS);
    //check results
    EXPECT_EQ(res.a, src.a);
    EXPECT_EQ(res.b, src.b);
    EXPECT_EQ(res.c, src.c);
    EXPECT_EQ(res.d, src.d);
}

using AdapterBitPackingWriter = bitsery::details::OutputAdapterBitPackingWrapper<BufferWriter>;
using AdapterBitPackingReader = bitsery::details::InputAdapterBitPackingWrapper<BufferReader>;


// *** bits operations

TEST(DataBitsAndBytesOperations, WriteAndReadBitsMaxTypeValues) {
    Buffer                  buf;
    BufferWriter                  bw{buf};
    AdapterBitPackingWriter bpw{bw};
    bpw.writeBits(std::numeric_limits<uint64_t>::max(), 64);
    bpw.writeBits(std::numeric_limits<uint32_t>::max(), 32);
    bpw.writeBits(std::numeric_limits<uint16_t>::max(), 16);
    bpw.writeBits(std::numeric_limits<uint8_t>::max(), 8);
    bpw.flush();

    BufferReader                  br{buf.begin(), bpw.writtenBytesCount()};
    AdapterBitPackingReader bpr{br};
    uint64_t                v64{};
    uint32_t                v32{};
    uint16_t                v16{};
    uint8_t                 v8{};
    bpr.readBits(v64, 64);
    bpr.readBits(v32, 32);
    bpr.readBits(v16, 16);
    bpr.readBits(v8, 8);

    EXPECT_EQ(v64, (std::numeric_limits<uint64_t>::max()));
    EXPECT_EQ(v32, (std::numeric_limits<uint32_t>::max()));
    EXPECT_EQ(v16, (std::numeric_limits<uint16_t>::max()));
    EXPECT_EQ(v8, (std::numeric_limits<uint8_t>::max()));
}

struct IntegralUnsignedTypesB {
    uint32_t a;
    uint16_t b;
    uint8_t  c;
    uint8_t  d;
    uint64_t e;
};


TEST(DataBitsAndBytesOperations, WriteAndReadBits) {
    //setup data
    constexpr IntegralUnsignedTypesB data{
        485454,      //bits 19
        45978,       //bits 16
        0,           //bits 1
        36,          //bits 6
        479845648946 //bits 39
    };

    constexpr size_t aBITS = getBits(data.a) + 2;
    constexpr size_t bBITS = getBits(data.b) + 0;
    constexpr size_t cBITS = getBits(data.c) + 2;
    constexpr size_t dBITS = getBits(data.d) + 1;
    constexpr size_t eBITS = getBits(data.e) + 8;

    //create and write to buffer
    Buffer                  buf;
    BufferWriter                  bw{buf};
    AdapterBitPackingWriter bpw{bw};

    bpw.writeBits(data.a, aBITS);
    bpw.writeBits(data.b, bBITS);
    bpw.writeBits(data.c, cBITS);
    bpw.writeBits(data.d, dBITS);
    bpw.writeBits(data.e, eBITS);
    bpw.flush();
    auto writtenSize = bpw.writtenBytesCount();
    auto bytesCount  = ((aBITS + bBITS + cBITS + dBITS + eBITS) / 8) + 1;
    EXPECT_EQ(writtenSize, (bytesCount));
    //read from buffer
    BufferReader                  br{buf.begin(), writtenSize};
    AdapterBitPackingReader bpr{br};

    IntegralUnsignedTypesB res{};

    bpr.readBits(res.a, aBITS);
    bpr.readBits(res.b, bBITS);
    bpr.readBits(res.c, cBITS);
    bpr.readBits(res.d, dBITS);
    bpr.readBits(res.e, eBITS);

    EXPECT_EQ(res.a, (data.a));
    EXPECT_EQ(res.b, (data.b));
    EXPECT_EQ(res.c, (data.c));
    EXPECT_EQ(res.d, (data.d));
    EXPECT_EQ(res.e, (data.e));
}

TEST(DataBitsAndBytesOperations, WrittenSizeIsCountedPerByteNotPerBit) {
    //setup data

    //create and write to buffer
    Buffer                  buf;
    BufferWriter                  bw{buf};
    AdapterBitPackingWriter bpw{bw};

    bpw.writeBits(7u, 3);
    bpw.flush();
    auto writtenSize = bpw.writtenBytesCount();
    EXPECT_EQ(writtenSize, (1));

    //read from buffer
    BufferReader                  br{buf.begin(), writtenSize};
    AdapterBitPackingReader bpr{br};
    uint16_t                tmp;
    bpr.readBits(tmp, 4);
    bpr.readBits(tmp, 2);
    bpr.readBits(tmp, 2);
    EXPECT_EQ(bpr.error(), (bitsery::ReaderError::NoError));
    bpr.readBits(tmp, 2);
    EXPECT_EQ(bpr.error(), (bitsery::ReaderError::DataOverflow)); //false

    //part of next byte
    BufferReader                  br1{buf.begin(), writtenSize};
    AdapterBitPackingReader bpr1{br1};
    bpr1.readBits(tmp, 2);
    EXPECT_EQ(bpr1.error(), (bitsery::ReaderError::NoError));
    bpr1.readBits(tmp, 7);
    EXPECT_EQ(bpr1.error(), (bitsery::ReaderError::DataOverflow)); //false

    //bigger than byte
    BufferReader                  br2{buf.begin(), writtenSize};
    AdapterBitPackingReader bpr2{br2};
    bpr2.readBits(tmp, 9);
    EXPECT_EQ(bpr2.error(), (bitsery::ReaderError::DataOverflow)); //false
}

TEST(DataBitsAndBytesOperations, ConsecutiveCallsToAlignHasNoEffect) {
    Buffer                  buf;
    BufferWriter                  bw{buf};
    AdapterBitPackingWriter bpw{bw};

    bpw.writeBits(3u, 2);
    //3 calls to align after 1st data
    bpw.align();
    bpw.align();
    bpw.align();
    bpw.writeBits(7u, 3);
    //1 call to align after 2nd data
    bpw.align();
    bpw.writeBits(15u, 4);
    bpw.flush();

    unsigned char           tmp;
    BufferReader            br{buf.begin(), bpw.writtenBytesCount()};
    AdapterBitPackingReader bpr{br};
    bpr.readBits(tmp, 2);
    EXPECT_EQ(tmp, 3u);
    bpr.align();
    EXPECT_EQ(bpr.error(), bitsery::ReaderError::NoError);
    bpr.readBits(tmp, 3);
    bpr.align();
    bpr.align();
    bpr.align();
    EXPECT_EQ(tmp, 7u);
    EXPECT_EQ(bpr.error(), bitsery::ReaderError::NoError);

    bpr.readBits(tmp, 4);
    EXPECT_EQ(tmp, 15u);
    EXPECT_EQ(bpr.error(), bitsery::ReaderError::NoError);
}

TEST(DataBitsAndBytesOperations, AlignWritesZerosBits) {
    //setup data

    //create and write to buffer
    Buffer                  buf;
    BufferWriter                  bw{buf};
    AdapterBitPackingWriter bpw{bw};

    //write 2 bits and align
    bpw.writeBits(3u, 2);
    bpw.align();
    bpw.flush();
    auto writtenSize = bpw.writtenBytesCount();
    EXPECT_EQ(writtenSize, 1);
    unsigned char           tmp;
    BufferReader                  br1{buf.begin(), writtenSize};
    AdapterBitPackingReader bpr1{br1};
    bpr1.readBits(tmp, 2);
    //read aligned bits
    bpr1.readBits(tmp, 6);
    EXPECT_EQ(tmp, (0));

    BufferReader                  br2{buf.begin(), writtenSize};
    AdapterBitPackingReader bpr2{br2};
    //read 2 bits
    bpr2.readBits(tmp, 2);
    bpr2.align();
    EXPECT_EQ(bpr2.error(), (bitsery::ReaderError::NoError));
}

// *** bytes operations

struct IntegralTypes {
    int64_t  a;
    uint32_t b;
    int16_t  c;
    uint8_t  d;
    int8_t   e;
    int8_t   f[2];
};

TEST(DataBitsAndBytesOperations, WriteAndReadBytes) {
    //setup data
    IntegralTypes data;
    data.a    = -4894541654564;
    data.b    = 94545646;
    data.c    = -8778;
    data.d    = 200;
    data.e    = -98;
    data.f[0] = 43;
    data.f[1] = -45;

    //create and write to buffer
    Buffer buf{};
    BufferWriter bw{buf};
    bw.writeBytes<4>(data.b);
    bw.writeBytes<2>(data.c);
    bw.writeBytes<1>(data.d);
    bw.writeBytes<8>(data.a);
    bw.writeBytes<1>(data.e);
    bw.writeBuffer<1>(data.f, 2);
    bw.flush();
    auto writtenSize = bw.writtenBytesCount();

    EXPECT_EQ(writtenSize, 18);
    //read from buffer
    BufferReader        br{buf.begin(), writtenSize};
    IntegralTypes res{};
    br.readBytes<4>(res.b);
    br.readBytes<2>(res.c);
    br.readBytes<1>(res.d);
    br.readBytes<8>(res.a);
    br.readBytes<1>(res.e);
    br.readBuffer<1>(res.f, 2);
    EXPECT_EQ(br.error(), bitsery::ReaderError::NoError);
    //assert results

    EXPECT_EQ(data.a, res.a);
    EXPECT_EQ(data.b, res.b);
    EXPECT_EQ(data.c, res.c);
    EXPECT_EQ(data.d, res.d);
    EXPECT_EQ(data.e, res.e);
    EXPECT_EQ(data.f[0], res.f[0]);
    EXPECT_EQ(data.f[1], res.f[1]);
}

TEST(DataBitsAndBytesOperations, WriteAndReadBytesWithBitPackingWrapper) {
    //setup data
    IntegralTypes data;
    data.a    = -4894541654564;
    data.b    = 94545646;
    data.c    = -8778;
    data.d    = 200;
    data.e    = -98;
    data.f[0] = 43;
    data.f[1] = -45;

    //create and write to buffer
    Buffer                  buf{};
    BufferWriter                  bw{buf};
    AdapterBitPackingWriter bpw{bw};
    bpw.writeBytes<4>(data.b);
    bpw.writeBytes<2>(data.c);
    bpw.writeBytes<1>(data.d);
    bpw.writeBytes<8>(data.a);
    bpw.writeBytes<1>(data.e);
    bpw.writeBuffer<1>(data.f, 2);
    bpw.flush();
    auto writtenSize = bpw.writtenBytesCount();

    EXPECT_EQ(writtenSize, (18));
    //read from buffer
    BufferReader                  br{buf.begin(), writtenSize};
    AdapterBitPackingReader bpr{br};
    IntegralTypes           res{};
    bpr.readBytes<4>(res.b);
    bpr.readBytes<2>(res.c);
    bpr.readBytes<1>(res.d);
    bpr.readBytes<8>(res.a);
    bpr.readBytes<1>(res.e);
    bpr.readBuffer<1>(res.f, 2);
    EXPECT_EQ(bpr.error(), bitsery::ReaderError::NoError);
    //assert results

    EXPECT_EQ(data.a, (res.a));
    EXPECT_EQ(data.b, (res.b));
    EXPECT_EQ(data.c, (res.c));
    EXPECT_EQ(data.d, (res.d));
    EXPECT_EQ(data.e, (res.e));
    EXPECT_EQ(data.f[0], res.f[0]);
    EXPECT_EQ(data.f[1], res.f[1]);
}

TEST(DataBitsAndBytesOperations, ReadWriteFncCanAcceptSignedData) {
    //setup data
    constexpr size_t DATA_SIZE = 3;
    int16_t          src[DATA_SIZE]{54, -4877, 30067};
    //create and write to buffer
    Buffer buf{};
    BufferWriter bw{buf};
    bw.writeBuffer<2>(src, DATA_SIZE);
    bw.flush();
    //read from buffer
    BufferReader  br1{buf.begin(), bw.writtenBytesCount()};
    int16_t dst[DATA_SIZE]{};
    br1.readBuffer<2>(dst, DATA_SIZE);
    EXPECT_EQ(br1.error(), (bitsery::ReaderError::NoError));
    EXPECT_EQ(dst[0], src[0]);
    EXPECT_EQ(dst[1], src[1]);
    EXPECT_EQ(dst[2], src[2]);
}

TEST(DataBitsAndBytesOperations, ReadWriteCanWorkOnUnalignedData) {
    //setup data
    constexpr size_t DATA_SIZE = 3;
    int16_t          src[DATA_SIZE]{54, -4877, 30067};
    //create and write to buffer
    Buffer                  buf{};
    BufferWriter                  bw{buf};
    AdapterBitPackingWriter bpw{bw};
    bpw.writeBits(15u, 4);
    bpw.writeBuffer<2>(src, DATA_SIZE);
    bpw.writeBits(12u, 4);
    bpw.flush();
    auto writtenSize = bpw.writtenBytesCount();
    EXPECT_EQ(writtenSize, (sizeof(src) + 1));

    //read from buffer
    BufferReader                  br1{buf.begin(), writtenSize};
    AdapterBitPackingReader bpr1{br1};
    int16_t                 dst[DATA_SIZE]{};
    uint8_t                 tmp{};
    bpr1.readBits(tmp, 4);
    EXPECT_EQ(tmp, (15));
    bpr1.readBuffer<2>(dst, DATA_SIZE);
    EXPECT_EQ(bpr1.error(), (bitsery::ReaderError::NoError));
    EXPECT_EQ(dst[0], src[0]);
    EXPECT_EQ(dst[1], src[1]);
    EXPECT_EQ(dst[2], src[2]);
    bpr1.readBits(tmp, 4);
    EXPECT_EQ(tmp, (12));
}

TEST(DataBitsAndBytesOperations, RegressionTestReadBytesAfterReadBitsWithLotsOfZeroBits) {
    //setup data
    int16_t data[2]{0x0000, 0x7FFF};
    int16_t res[2]{};
    //create and write to buffer
    Buffer                  buf{};
    BufferWriter                  bw{buf};
    AdapterBitPackingWriter bpw{bw};
    bpw.writeBits(2u, 2);
    bpw.writeBytes<2>(data[0]);
    bpw.writeBytes<2>(data[1]);
    bpw.align();
    bpw.flush();

    //read from buffer
    BufferReader                  br{buf.begin(), bpw.writtenBytesCount()};
    AdapterBitPackingReader bpr{br};
    uint8_t                 tmp{};
    bpr.readBits(tmp, 2);
    EXPECT_EQ(tmp, (2));
    bpr.readBytes<2>(res[0]);
    bpr.readBytes<2>(res[1]);
    bpr.align();
    EXPECT_EQ(res[0], (data[0]));
    EXPECT_EQ(res[1], (data[1]));
}