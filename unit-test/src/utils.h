//
//  utils.h
//  CocosTest
//
//  Created by rosa on 2021/3/22.
//

#ifndef utils_h
#define utils_h
#include "cocos/math/Math.h"
static std::string logLabel;
static bool IsEqualF(float l, float r) {
    return cc::math::IsEqualF(l, r);
};
static void ExpectEq(bool lf, bool rt) {
    EXPECT_EQ(lf, rt) << "ERROR in: " <<logLabel;
}

#endif /* utils_h */
