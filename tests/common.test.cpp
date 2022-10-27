///  @file     common.test.cpp
///  @author   Ahmed Rayyan
///  @date     June 25, 2022
///  @brief    common functions/variables unit testing
#include <libDamien/common.hpp>
#include <gtest/gtest.h>

TEST(Heaviside, PositiveValues) {
	double s = 10;
	double expected_result = 1;
	EXPECT_DOUBLE_EQ(Heaviside(s),expected_result);
}

TEST(Heaviside, NegativeValues) {
	double s = -10;
	double expected_result = 0;
	EXPECT_DOUBLE_EQ(Heaviside(s),expected_result);
}

TEST(Heaviside, AtZero) {
	double s = 0;
	double expected_result = 1;
	EXPECT_DOUBLE_EQ(Heaviside(s),expected_result);
}

TEST(NormalCumulative, ZScoreZero){
	double x = 0.00;
	double expected_result = 0.5000;
	EXPECT_DOUBLE_EQ(NormalCumulative(x),expected_result);
}

TEST(NormalCumulative, ZScoreOne){
	double x = 1.00;
	double expected_result = 0.84134475;
	EXPECT_NEAR(NormalCumulative(x),expected_result,MID_TOL_EPS);
}

TEST(NormalCumulative, ZScoreTwo){
	double x = 2.00;
	double expected_result = 0.97724987;
	EXPECT_NEAR(NormalCumulative(x),expected_result,MID_TOL_EPS);
}

TEST(NormalCumulative, ZScoreThree){
	double x = 3.00;
	double expected_result = 0.99865010;
	EXPECT_NEAR(NormalCumulative(x),expected_result,MID_TOL_EPS);
}
