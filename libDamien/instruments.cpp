///  @file     instruments.cpp
///  @author   Ahmed Rayyan
///  @date     June 29, 2022
///  @brief    implementation of common financial instruments
#include <libDamien/instruments.hpp>

double ZeroCouponBond::Price(double time) const
{
  return exp(- getRiskFreeRate() * (Maturity-time));
}

double ForwardContract::Payoff(const Eigen::VectorXd& spot_prices) const
{
  return spot_prices(Eigen::indexing::last) - getStrike();
}

double ForwardContract::Price(double time) const
{
  double S = getUnderlyingStock()->getCurrentPrice();
  double d = getUnderlyingStock()->getDividendRate();
  double tau = getMaturity() - time;
  double K = getStrike();
  double r = getRiskFreeRate();

  return exp(-r*tau)*(exp((r-d)*tau)*S - K);
}

double CallOption::Payoff(double spot) const
{
  return std::max(spot - getStrike(),0.0);
}

double CallOption::Price(double time) const
{
  double S   = getUnderlyingStock()->getCurrentPrice();
  double tau = getMaturity() - time;
  if (tau < HIGH_TOL_EPS){
    cout << "Too close to maturity within dt="
         << HIGH_TOL_EPS
         << ". Will use Payoff() to price option instead." << endl;
    return Payoff(S);
  } else {
    double sigma = getUnderlyingStock()->getVolatility();
    double d     = getUnderlyingStock()->getDividendRate();
    double K     = getStrike();
    double r     = getRiskFreeRate();

    double d2 = (log(S/K) + (r - d - 0.5*sigma*sigma)*tau)/sigma/sqrt(tau);
    double d1 = d2+sigma*sqrt(tau);
    return S*exp(-d*tau)*NormalCumulative(d1)-K*exp(-r*tau)*NormalCumulative(d2);
  };
}

double PutOption::Payoff(double spot) const
{
  return std::max(getStrike() - spot,0.0);
}

double PutOption::Price(double time) const
{
  double S   = getUnderlyingStock()->getCurrentPrice();
  double tau = getMaturity() - time;
  if (tau < HIGH_TOL_EPS){
    cout << "Too close to maturity within dt="
         << HIGH_TOL_EPS
         << ". Will use Payoff() to price option instead." << endl;
    return Payoff(S);
  } else {
    double sigma = getUnderlyingStock()->getVolatility();
    double d     = getUnderlyingStock()->getDividendRate();
    double K     = getStrike();
    double r     = getRiskFreeRate();

    double d2 = (log(S/K) + (r - d - 0.5*sigma*sigma)*tau)/sigma/sqrt(tau);
    double d1 = d2+sigma*sqrt(tau);
    return K*exp(-r*tau)*NormalCumulative(-d2)-S*exp(-d*tau)*NormalCumulative(-d1);
  };
}

double DigitalCallOption::Payoff(double spot) const
{
  return Heaviside(spot - getStrike());
}

double DigitalCallOption::Price(double time) const
{
  double S   = getUnderlyingStock()->getCurrentPrice();
  double tau = getMaturity() - time;
  if (tau < HIGH_TOL_EPS){
    cout << "Too close to maturity within dt="
         << HIGH_TOL_EPS
         << ". Will use Payoff() to price option instead." << endl;
    return Payoff(S);
  } else {
    double sigma = getUnderlyingStock()->getVolatility();
    double d     = getUnderlyingStock()->getDividendRate();
    double K     = getStrike();
    double r     = getRiskFreeRate();

    double d2 = (log(S/K) + (r - d - 0.5*sigma*sigma)*tau)/sigma/sqrt(tau);
    return exp(-r*tau)*NormalCumulative(d2);
  };
}

double DigitalPutOption::Payoff(double spot) const
{
  return Heaviside(getStrike() - spot);
}

double DigitalPutOption::Price(double time) const
{
  double S   = getUnderlyingStock()->getCurrentPrice();
  double tau = getMaturity() - time;
  if (tau < HIGH_TOL_EPS){
    cout << "Too close to maturity within dt="
         << HIGH_TOL_EPS
         << ". Will use Payoff() to price option instead." << endl;
    return Payoff(S);
  } else {
    double sigma = getUnderlyingStock()->getVolatility();
    double d     = getUnderlyingStock()->getDividendRate();
    double K     = getStrike();
    double r     = getRiskFreeRate();

    double d2 = (log(S/K) + (r - d - 0.5*sigma*sigma)*tau)/sigma/sqrt(tau);
    return exp(-r*tau)*NormalCumulative(-d2);
  };
}
