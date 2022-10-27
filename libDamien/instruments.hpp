///  @file     instruments.hpp
///  @author   Ahmed Rayyan
///  @date     June 29, 2022
///  @brief    defining interface of common financial instruments
#ifndef INSTRUMENTS_HPP
#define INSTRUMENTS_HPP

#include <libDamien/common.hpp>

// class inheritances structure is loosely based on the book 
// "C++ for Financial Mathematics" by John Armstrong

class Priceable{
  //class representing anything that has a price, which depends on the current
  //information of the financial universe. for now, the (current) interest rate,
  //assumed constant, is that information.
public:
  virtual ~Priceable(){};

  double getRiskFreeRate() const {return RiskFreeRate;}
  void setRiskFreeRate(double rf_rate) {this->RiskFreeRate = rf_rate;}

  virtual double Price(double time) const = 0; //the price at this current moment
private:
  double RiskFreeRate;
};

class ZeroCouponBond : public Priceable{
  //instrument which pays 1 dollar at maturity. the price is given by
  // P(t) = exp(-r(T-t))
public:
  double getMaturity() const {return Maturity;}
  void setMaturity(double maturity) {this->Maturity = maturity;}

  double Payoff() const {return 1.0;}
  double Price(double time) const override;
private:
  double Maturity;
};

class Stock : public Priceable{
  //instrument which represents equity in a company, entitling the owner to
  //profit sharing of future cash flows in the form of a dividend. the price is given by
  //given by the market now. the dispersion of the market price is the volatility.
public:
  Stock(std::string label):StockLabel(label){};

  double getCurrentPrice() const {return CurrentPrice;}
  double getDividendRate() const {return DividendRate;}
  double getVolatility() const {return Volatility;}
  void setCurrentPrice(double price) {this->CurrentPrice = price;}
  void setDividendRate(double div_rate) {this->DividendRate = div_rate;}
  void setVolatility(double vol) {this->Volatility = vol;}

  double Price(double /*time*/) const override {return CurrentPrice;}

private:
  std::string StockLabel;
  double CurrentPrice;
  double Volatility;
  double DividendRate;
};

class DerivativeWithStrike : public Priceable{
  //instrument with a payoff at maturity given by the relationship of an underlying
  //instrument's price (just Stock for now) with a strike price.
public:
  double getStrike() const {return StrikePrice;}
  double getMaturity() const {return Maturity;}
  std::shared_ptr<Stock> getUnderlyingStock() const {return UnderlyingStock;}
  void setStrike(double strike) {this->StrikePrice = strike;}
  void setMaturity(double tte) {this->Maturity = tte;}
  void setUnderlyingStock(std::shared_ptr<Stock> stock) {this->UnderlyingStock = stock;}

  virtual double Payoff(const Eigen::VectorXd& spot_prices) const = 0;

private:
  double StrikePrice;
  double Maturity;
  std::shared_ptr<Stock> UnderlyingStock;
};

class ForwardContract : public DerivativeWithStrike{
  //instrument with a payoff at maturity T given by S(T) - K
  //the price is given by the discounted forward price
  //p(r;S,d;K,T;t) = exp(-r(T-t)) [S*exp( (r-d)(T-t) )- K]
public:
  double Payoff(const Eigen::VectorXd& spot_prices) const override;
  double Price(double time) const override;
};

class ContinuousTimeOption : public DerivativeWithStrike{
  //options are derivative with strikes which give the owner certain
  //rights, but not obligations, regarding the underlying instruments.
  //continuous time here refers to t /elementof Reals (as opposed to
  //t /elementof Integers).
public:
  virtual ~ContinuousTimeOption(){};
  virtual bool isPathDependent() const = 0;
};

class PathIndependentOption : public ContinuousTimeOption{
  //options with payoffs which depend only on the stock price at maturity (as
  //opposed to the history of the stock within some period)
public:
  virtual ~PathIndependentOption(){};

  bool isPathDependent() const override {return false;};
  double Payoff(const Eigen::VectorXd& price_path) const override {
    return Payoff(price_path(Eigen::indexing::last));
  }
  virtual double Payoff(double spot) const = 0;

};

class CallOption : public PathIndependentOption {
  //options with payoffs max(S - K, 0) at maturity. price is given by the
  //Black-Scholes-Merton analytical expression
public:
  double Payoff(double spot) const override;

  double Price(double time) const override;
};

class PutOption : public PathIndependentOption {
public:
  //options with payoffs max(K - S, 0) at maturity. price is given by the
  //Black-Scholes-Merton analytical expression
  double Payoff(double spot) const override;
  double Price(double time) const override;
};

class DigitalCallOption : public PathIndependentOption {
public:
  //cash-or-nothing option with payoff Heaviside(S-K) at maturity. price is given
  //by the Black-Scholes-Merton analytical expression
  double Payoff(double spot) const override;
  double Price(double time) const override;
};

class DigitalPutOption : public PathIndependentOption {
public:
  //cash-or-nothing option with payoff Heaviside(K-S) at maturity. price is given
  //by the Black-Scholes-Merton analytical expression
  double Payoff(double spot) const override;
  double Price(double time) const override;
};


#endif // INSTRUMENTS_HPP
