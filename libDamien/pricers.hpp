///  @file     pricers.hpp
///  @author   Ahmed Rayyan
///  @date     June 30, 2022
///  @brief    defining interface of various option pricers
#ifndef PRICERS_HPP
#define PRICERS_HPP

#include <libDamien/common.hpp>
#include <libDamien/instruments.hpp>

class MonteCarloPricer{
public:
  std::shared_ptr<std::mt19937> getRandomEngine() const {return RandomEngine;}
  void setRandomEngine(std::shared_ptr<std::mt19937> rand_eng) {this->RandomEngine = rand_eng;}
  double Price(const DerivativeWithStrike& contract,
                                    double time,
                                       int n_trials,
                                       int n_steps,
                                   double& stdev) const;

  Eigen::MatrixXd GeneratePricePaths(std::shared_ptr<Stock> stock,
                                                        int n_trials,
                                                        int n_steps,
                                                     double time_period,
                                                     double drift) const;

  Eigen::MatrixXd GenerateRiskNeutralPricePaths(std::shared_ptr<Stock> stock,
                                                                   int n_trials,
                                                                   int n_steps,
                                                                double time_period) const;

  void GenerateStatistics(const Eigen::VectorXd& samples,
                                         double& mean,
                                         double& std) const;

private:
  std::shared_ptr<std::mt19937> RandomEngine;
};


#endif // PRICER_HPP
