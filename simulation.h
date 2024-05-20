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
 
 vector<vector<double>> GenerateRandomMatrix(int seed = -1);

 vector<double> EulerMaruyama(double (*f)(double, double), double (*g)(double, double), const vector<double> & random_array);

 vector<vector<double>> Simulate(double (*f)(double, double), double (*g)(double, double), int seed=-1);
 
private:

 Params params;
 
 vector<double> time_vector;

};

#endif 
