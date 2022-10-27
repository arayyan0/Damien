///  @file     instruments.test.cpp
///  @author   Ahmed Rayyan
///  @date     June 25, 2022
///  @brief    instruments unit testing
#include <libDamien/instruments.hpp>
#include <gtest/gtest.h>

TEST(ZeroCouponBond, ValueAtMaturity){
	BSMTest1 test1;
	ZeroCouponBond bond;
	double time_at_maturity = 0.0;
	bond.setRiskFreeRate(test1.rf_rate);
	bond.setMaturity(time_at_maturity);
	EXPECT_DOUBLE_EQ(bond.Price(test1.time),bond.Payoff());
}

TEST(OptionPayoffs, CallPrice){
	BSMTest1 test1;

	std::string label = "XYZ";
	Stock stock(label);
	stock.setCurrentPrice(test1.current_price);
	stock.setVolatility(test1.vol);
	stock.setDividendRate(test1.div);

	auto ptr = std::make_shared<Stock>(stock);

	CallOption call;
	call.setRiskFreeRate(test1.rf_rate);
	call.setUnderlyingStock(ptr);
	call.setStrike(test1.strike);
	call.setMaturity(test1.maturity);
	EXPECT_NEAR(call.Price(test1.time),test1.callprice,LOW_TOL_EPS);
}

TEST(OptionPayoffs, CallPriceAtMaturity){
	BSMTest1 test1;

	//recall that proximity to maturity is tested to HIGH_TOL_EPS=1e-4
	double time1 = test1.maturity-1e-2;
	double time2 = test1.maturity-1e-5;
	//for time2 and tolerance=HIGH_TOL_EPS=1e-4, option has expired.

	std::string label = "XYZ";
	Stock stock(label);
	stock.setCurrentPrice(test1.current_price);
	stock.setVolatility(test1.vol);
	stock.setDividendRate(test1.div);

	auto ptr = std::make_shared<Stock>(stock);

	CallOption call;
	call.setRiskFreeRate(test1.rf_rate);
	call.setUnderlyingStock(ptr);
	call.setStrike(test1.strike);
	call.setMaturity(test1.maturity);
	EXPECT_GT(call.Price(time1),0.0);
	EXPECT_DOUBLE_EQ(call.Price(time2),0.0);
}

TEST(OptionPayoffs, PutCallParity){
	BSMTest1 test1;

	std::string label = "XYZ";
	Stock stock(label);
	stock.setCurrentPrice(test1.current_price);
	stock.setVolatility(test1.vol);
	stock.setDividendRate(test1.div);

	auto ptr = std::make_shared<Stock>(stock);

	ForwardContract fwd;
	fwd.setRiskFreeRate(test1.rf_rate);
	fwd.setUnderlyingStock(ptr);
	fwd.setStrike(test1.strike);
	fwd.setMaturity(test1.maturity);

	CallOption call;
	call.setRiskFreeRate(test1.rf_rate);
	call.setUnderlyingStock(ptr);
	call.setStrike(test1.strike);
	call.setMaturity(test1.maturity);

	PutOption put;
	put.setRiskFreeRate(test1.rf_rate);
	put.setUnderlyingStock(ptr);
	put.setStrike(test1.strike);
	put.setMaturity(test1.maturity);
	EXPECT_NEAR(call.Price(test1.time) - put.Price(test1.time),fwd.Price(test1.time),LOW_TOL_EPS);
}

TEST(OptionPayoffs, DigitalCallPrice){
	BSMTest1 test1;

	std::string label = "XYZ";
	Stock stock(label);
	stock.setCurrentPrice(test1.current_price);
	stock.setVolatility(test1.vol);
	stock.setDividendRate(test1.div);

	auto ptr = std::make_shared<Stock>(stock);

	DigitalCallOption dcall;
	dcall.setRiskFreeRate(test1.rf_rate);
	dcall.setUnderlyingStock(ptr);
	dcall.setStrike(test1.strike);
	dcall.setMaturity(test1.maturity);
	EXPECT_NEAR(dcall.Price(test1.time),test1.dcallprice,LOW_TOL_EPS);
}

// TEST(OptionPayoffs, DigitalPutCallParity){
// 	BSMTest1 test1;
//
// 	std::string label = "XYZ";
// 	Stock stock(label);
// 	stock.setCurrentPrice(test1.current_price);
// 	stock.setVolatility(test1.vol);
// 	stock.setDividendRate(test1.div);
//
// 	auto ptr = std::make_shared<Stock>(stock);
//
// 	ZeroCouponBond zcb;
// 	zcb.setRiskFreeRate(test1.rf_rate);
// 	zcb.setMaturity(test1.maturity);
//
// 	DigitalCallOption dcall;
// 	dcall.setRiskFreeRate(test1.rf_rate);
// 	dcall.setUnderlyingStock(ptr);
// 	dcall.setStrike(test1.strike);
// 	dcall.setMaturity(test1.maturity);
//
// 	DigitalPutOption dput;
// 	dput.setRiskFreeRate(test1.rf_rate);
// 	dput.setUnderlyingStock(ptr);
// 	dput.setStrike(test1.strike);
// 	dput.setMaturity(test1.maturity);
// 	EXPECT_NEAR(dcall.Price(test1.time) + dput.Price(test1.time),zcb.Price(test1.time),LOW_TOL_EPS);
// }
