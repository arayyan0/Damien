///  @file     common.hpp
///  @author   Ahmed Rayyan
///  @date     June 22, 2022
///  @brief    defining common functions/variables interface
#ifndef COMMON_HPP
#define COMMON_HPP

#include <algorithm>
#include <chrono>
#include <cmath>
#include <Eigen/Dense>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <string>

#define _USE_MATH_DEFINES

using std::cout;
using std::endl;

const double LOW_TOL_EPS  = 1e-12;
const double MID_TOL_EPS  = 1e-8;
const double HIGH_TOL_EPS = 1e-4;

struct BSMTest1{
  //example parameter set I found in Mark Joshi's first book
  double rf_rate = 5.0/100.0;
  double maturity = 1.0;
  double current_price = 100.0;
  double vol = 20.0/100.0;
  double div = 2.0/100.0;
  double strike = 110.0;
  double time = 0.0;

  double callprice = 5.188581753780;
  double dcallprice = 0.318522248853;
};

double Heaviside(double s);
double NormalCumulative(double s);

std::mt19937 SeededMersenneTwister();

void OutputVectorOfDoubles(const std::vector<double>& vec);

#endif // COMMON_HPP
