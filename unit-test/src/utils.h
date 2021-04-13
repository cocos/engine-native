#pragma once
#include "cocos/math/Math.h"
static std::string logLabel;
static bool IsEqualF(float l, float r) {
    return cc::math::IsEqualF(l, r);
};
static void ExpectEq(bool lf, bool rt) {
    EXPECT_EQ(lf, rt) << "ERROR in: " <<logLabel;
}
