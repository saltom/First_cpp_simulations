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
 
 vector<double> GetTimeVector() const; 
 
 vector<vector<double>> GenerateRandomMatrix(int seed = -1);

 vector<double> EulerMaruyama(const vector<double> & random_array);

 vector<vector<double>> Simulate(int seed=-1);
 
private:

 ScalarParams scalar_params;
 
 VectorParams vector_params;
 
 vector<double> time_vector;

};

#endif 
