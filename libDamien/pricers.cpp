///  @file     pricers.cpp
///  @author   Ahmed Rayyan
///  @date     June 30, 2022
///  @brief    implementation of various option pricers
#include <libDamien/pricers.hpp>

Eigen::MatrixXd MonteCarloPricer::GeneratePricePaths(std::shared_ptr<Stock> stock,
                                                                        int n_trials,
                                                                        int n_steps,
                                                                     double time_period,
                                                                     double drift) const
{
  //initialize matrix of log(price) and begin from log(initial price)
  Eigen::MatrixXd log_price_mat = Eigen::MatrixXd::Zero(n_trials,n_steps+1);
  log_price_mat.col(0) = Eigen::VectorXd::Constant(n_steps,log(stock->getCurrentPrice()));
  // cout << log_price_mat << endl;

  //obtain matrix of Gaussian-distributed numbers with mean 0, std 1
  std::normal_distribution<double> dist(0.0,1.0);
  auto gen = [&dist, this](){return dist(*RandomEngine);};
  std::vector<double> eps_long_vec(n_trials*n_steps);
  std::generate(eps_long_vec.begin(), eps_long_vec.end(), gen);
  Eigen::MatrixXd eps_mat = Eigen::Map<Eigen::VectorXd>(&eps_long_vec[0],
                                                        n_trials*n_steps).reshaped(n_trials,
                                                                                   n_steps);

  double dt = time_period/(double)n_steps;
  double sigma = stock->getVolatility();
  double div = stock->getDividendRate();

  log_price_mat(Eigen::indexing::all, Eigen::seq(1,Eigen::indexing::last))
    = Eigen::MatrixXd::Constant(n_trials,n_steps,(drift - div - 0.5*sigma*sigma)*dt)
     +Eigen::MatrixXd::Constant(n_trials,n_steps,sigma*sqrt(dt)).cwiseProduct(eps_mat);

  for (int j=0; j<n_steps; j++){
      log_price_mat.col(j+1)+=log_price_mat.col(j);
  }

  return log_price_mat.array().exp();
}

Eigen::MatrixXd MonteCarloPricer::GenerateRiskNeutralPricePaths(std::shared_ptr<Stock> stock,
                                                                                   int n_trials,
                                                                                   int n_steps,
                                                                                double time_period) const
{
  return GeneratePricePaths(stock,n_trials,n_steps,time_period,stock->getRiskFreeRate());
}


double MonteCarloPricer::Price(const DerivativeWithStrike& contract,
                                                    double time,
                                                       int n_trials,
                                                       int n_steps,
                                                   double& stdev) const
{
  double tau = contract.getMaturity() - time;
  Eigen::MatrixXd prices_mat = GenerateRiskNeutralPricePaths(
    contract.getUnderlyingStock(), n_trials, n_steps, tau
  );

  Eigen::VectorXd samples(n_trials);

  for (int i=0; i<n_trials; i++){
    samples(i) = contract.Payoff(prices_mat.row(i));
  }
  samples = (samples*exp(-contract.getRiskFreeRate()*tau)).eval();

  double mean;
  GenerateStatistics(samples,mean,stdev);
  return mean;
}

void MonteCarloPricer::GenerateStatistics(const Eigen::VectorXd& samples,
                                                         double& mean,
                                                         double& std) const
{
  int n = samples.size();
  mean = samples.sum()/(double)n;
  std = sqrt( (samples - Eigen::VectorXd::Constant(n, mean)).array().square().sum()/(double)n/(double)(n-1) );
}
