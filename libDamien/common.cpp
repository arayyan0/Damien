///  @file     common.cpp
///  @author   Ahmed Rayyan
///  @date     June 22, 2022
///  @brief    defining common functions/variables implementation
#include <libDamien/common.hpp>

double Heaviside(double s)
{
  //implementation of Heaviside function theta(s) with convention theta(0) = 1.
  return s >= 0.0 ? 1.0 : 0.0;
}

double NormalCumulative(double s)
{
  //implementation of cumulative distribution function for Gaussian, ie.
  // N(s) = int_0^s [exp(-x^2 / 2) / sqrt(2 pi)] dx
  return 0.5*(1.0 + erf(s*M_SQRT1_2));
}

std::mt19937 SeededMersenneTwister(){
  //returns a seeded mersenne twister engine
  auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::mt19937 mt_rand(seed);
  return mt_rand;
}

void OutputVectorOfDoubles(const std::vector<double>& vec){
  //given a vector of doubles {a,b,c,d,...}, function returns
  //Vector output:
  //a b c d ...
  //------------
  //future: construct any_printable type to expand more generally.
  cout << "Vector output:" << endl;
  for (auto var : vec){
    cout << var << " ";
  }
  cout << " " << endl;
  cout << "------------" << endl;
}
