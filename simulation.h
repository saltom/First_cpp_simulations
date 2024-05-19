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

 Simulation(const ScalarParams& scalar_params, const VectorParams& vector_params);   //constructor
 
 vector<double> GenerateTime();
 
 vector<vector<double>> GenerateRandomMatrix(int seed);

 vector<double> EulerMaruyama(const vector<double>& t, const vector<double> & random_array);

 vector<vector<double>> Simulate(const vector<double>& t, int seed);
 
private:

 ScalarParams scalar_params;
 
 VectorParams vector_params;

};

#endif 
