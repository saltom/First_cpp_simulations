#include "simulation.h"

Simulation::Simulation(const Params& params) : params(params) { 

 double current_time = params.t0;
 double dt = (params.tf - params.t0) / params.n;   
 time_vector.push_back(current_time);  

 for (int i = 1; i < params.n; ++i) {
  current_time += dt;  
  time_vector.push_back(current_time);
 } // constructor generates time
}

vector<double> Simulation::GetTimeVector() const {
    return time_vector;
}

vector<vector<double>> Simulation::GenerateRandomMatrix(int seed) { 

 vector<vector<double>> random_matrix(params.N, vector<double>(params.n));;
 mt19937 gen;

 if (seed == -1) {     //if seed is not provided a random one is chosen
  random_device rd;
  gen.seed(rd());
 }
 
 else {
  gen.seed(seed);
 } 
 
 normal_distribution<> distr(0.0, params.sigma); 

 for (int j = 0; j < params.N; ++j) {
  for (int i = 0; i < params.n; ++i) {  
   random_matrix[j][i] = distr(gen); 
  }
 }

return random_matrix;
}

vector<double> Simulation::EulerMaruyama(double (*f)(double, double), double (*g)(double, double), const vector<double> & random_array) {

 vector<double> y;
 double dt = (params.tf - params.t0) / params.n;  
 y.push_back(params.y0);
 double current_y = params.y0;
 double dt_sqrt = sqrt(dt);
 
 for (int i = 0; i < params.n; ++i) {  
  current_y += f(time_vector[i], current_y) * dt + g(time_vector[i], current_y) * random_array[i] * dt_sqrt;
  y.push_back(current_y);
 }

return y;
}

vector<vector<double>> Simulation::Simulate(double (*f)(double, double), double (*g)(double, double), int seed) {
//passing here seed to ensure reproducibility over N realizations without compromising ensemble variance

 vector<vector<double>> realization_matrix(params.N);
 vector<vector<double>> random_matrix = GenerateRandomMatrix(seed);

 for (int j = 0; j < params.N; ++j) {
  realization_matrix[j] = EulerMaruyama(f, g, random_matrix[j]); 
    }
    
 return realization_matrix;
}








