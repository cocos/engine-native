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
#include <math.h>
#include "cocos/math/Mat3.h"
#include "cocos/math/Mat4.h"
#include "cocos/math/Math.h"
#include "cocos/math/Quaternion.h"
#include "cocos/math/Vec2.h"
#include "cocos/math/Color.h"
#include "cocos/core/serialization/serialization.h"
#include "gtest/gtest.h"

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
    
    std::vector<cc::Color>               colors;
    for (uint32_t i = 0; i < 1000000; i++) {
        colors.push_back(cc::Color(std::rand(), std::rand(), std::rand(), std::rand()));
    }
    {
        std::ofstream                        os("C:\\Users\\Administrator\\Desktop\\data.txt", std::ios::binary);
        cc::serialization::StreamedBinaryOutputArchive oar(os);
        for (uint32_t i = 0; i < 1000000; i++) {
            oar.serialize("color", 2);
        }
    }
    
}