///  @file     pricers.test.cpp
///  @author   Ahmed Rayyan
///  @date     June 30, 2022
///  @brief    pricer unit testing
#include <libDamien/pricers.hpp>
#include <gtest/gtest.h>

TEST(MonteCarloPricer, CallPrice){
  BSMTest1 test1;

  std::string label = "XYZ";
  Stock stock(label);
  stock.setRiskFreeRate(test1.rf_rate);
  stock.setCurrentPrice(test1.current_price);
  stock.setVolatility(test1.vol);
  stock.setDividendRate(test1.div);

  auto ptr = std::make_shared<Stock>(stock);

  CallOption call;
  call.setRiskFreeRate(stock.getRiskFreeRate());
  call.setUnderlyingStock(ptr);
  call.setStrike(test1.strike);
  call.setMaturity(test1.maturity);

  std::mt19937 mt_rand = SeededMersenneTwister();
  auto engine_ptr = std::make_shared<std::mt19937>(mt_rand);

  MonteCarloPricer pricer;
  pricer.setRandomEngine(engine_ptr);

  int n_trials = 1e5;
  int n_steps = 100;
  double stdev;
  double mean = pricer.Price(call, test1.time, n_trials, n_steps, stdev);
  EXPECT_TRUE((test1.callprice > mean-1.96*stdev) && (test1.callprice < mean+1.96*stdev));
}

TEST(MonteCarloPricer, DigitalCallPrice){
  BSMTest1 test1;

  std::string label = "XYZ";
  Stock stock(label);
  stock.setRiskFreeRate(test1.rf_rate);
  stock.setCurrentPrice(test1.current_price);
  stock.setVolatility(test1.vol);
  stock.setDividendRate(test1.div);

  auto ptr = std::make_shared<Stock>(stock);

  DigitalCallOption call;
  call.setRiskFreeRate(stock.getRiskFreeRate());
  call.setUnderlyingStock(ptr);
  call.setStrike(test1.strike);
  call.setMaturity(test1.maturity);

  std::mt19937 mt_rand = SeededMersenneTwister();
  auto engine_ptr = std::make_shared<std::mt19937>(mt_rand);

  MonteCarloPricer pricer;
  pricer.setRandomEngine(engine_ptr);

  int n_trials = 1e5;
  int n_steps = 100;
  double stdev;
  double mean = pricer.Price(call, test1.time, n_trials, n_steps, stdev);
  EXPECT_TRUE((test1.dcallprice > mean-1.96*stdev) && (test1.dcallprice < mean+1.96*stdev));
}
