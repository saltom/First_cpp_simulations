#ifndef SIMULATION_H
#define SIMULATION_H

#include "params.h"
#include <vector>
#include <iostream>
#include <random>
#include <cmath>

using namespace std;

class Simulation {

public:

 Simulation(const Params& params);   //constructor
 
 vector<double> GetTimeVector() const; 
 
 vector<vector<double>> RandomMatrix(double sigma, int seed = -1);
 
 vector<vector<vector<double>>> CorrelatedMatrices(double sigma1, double sigma2, double rho, int seed=-1); 

 vector<double> EulerMaruyama(double y0, double (*f)(double, double), double (*g)(double, double), const vector<double> & random_array);

 vector<vector<double>> Simulate(double y0, double (*f)(double, double), double (*g)(double, double), const vector<vector<double>> & random_matrix);
 
private:

 Params params;
 
 vector<double> time_vector;

};

#endif 
