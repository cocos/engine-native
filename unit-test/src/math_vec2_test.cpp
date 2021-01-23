#include "gtest/gtest.h"
#include "cocos/math/Vec2.h"

TEST(mathVec2Test, test1) {
	cc::Vec2 vec2(1, 2);

	EXPECT_EQ(vec2.isZero(), false);
}
