# Damien
Damien is an option pricing package written in C++. It is named after Damien 'Day Day' Price, a character in the HBO television show "The Wire."

The main motivation is twofold: learn the theory of option pricing, and practice proper software development. For the latter purpose, I organize the project along Boris Kolpackov's Canonical Project Structure, build the project using CMake, and implement unit testing using GoogleTest. 

Damien aims to price financial instruments via three methods: analytic expressions given by the standard Black-Scholes-Merton equations, and binomial tree and Monte Carlo methods when no such expression exists. Damien will leverage thread-safe random number generation and MPI/OpenMP protocols to boost numerical performance.  

## Building Damien

Building the project is simple. From the root folder run the following three commands:

```
config_type= <Release or Debug>
mkdir -p build/$config_type && cmake -DCMAKE_BUILD_TYPE=$config_type -H. -Bbuild/$config_type
cd build/$config_type
make
```
Using the ```debug``` option adds the ```-g``` flag for GDB debugging.

## To-do

1) Implement Monte Carlo pricing for general option
    * implement plotting of price paths
        * plot price paths over time
        * plot histogram of terminal prices and vertical line at strike
        * plot histogram of discounted payoffs and overlay with a gaussian w/ mean and std
        * plot cumulative mean as a function of Monte Carlo time vs line at BSM value
    * initialize RandomEngine optimally
    * implement threadsafe parallelization (check out TRNG package)
    * implement path dependent options, including Asian and Knockout/in options

2) Implement binomial asset pricing model
