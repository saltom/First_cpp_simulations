#include "simulation.h"

Simulation::Simulation(const ScalarParams& scalar_params, const VectorParams& vector_params) : scalar_params(scalar_params), vector_params(vector_params) { } // constructor only initializes params

vector<double> Simulation::GenerateTime() {
    
 vector<double> t(scalar_params.n);
 t[0] = scalar_params.t0;
 double dt = (scalar_params.tf - scalar_params.t0) / scalar_params.n;  

 for (int i = 0; i < scalar_params.n - 1; ++i) {
  t[i + 1] = t[i] + dt;
 }

 return t;
}

vector<vector<double>> Simulation::GenerateRandomMatrix(int seed = -1) { 

 vector<vector<double>> random_matrix(scalar_params.N, vector<double>(scalar_params.n));;
 mt19937 gen;

 if (seed == -1) {     //if seed is not provided a random one is chosen
  random_device rd;
  gen.seed(rd());
 }
 
 else {
  gen.seed(seed);
 } 
 
 normal_distribution<> distr(0.0, scalar_params.sigma); 

 for (int j=0; j<scalar_params.N; ++j) {
  for (int i = 0; i < scalar_params.n; ++i) {  
   random_matrix[j][i] = distr(gen); 
  }
 }

return random_matrix;
}

vector<double> Simulation::EulerMaruyama(const vector<double>& t, const vector<double> & random_array) {

 vector<double> y;
 double dt = (scalar_params.tf - scalar_params.t0) / scalar_params.n;  
 y.push_back(scalar_params.y0);
 double current_y = scalar_params.y0;
 double dt_sqrt = sqrt(dt);
 
 for (int i = 0; i < scalar_params.n; ++i) {  
  current_y += vector_params.f(t[i], current_y) * dt + vector_params.g(t[i], current_y) * random_array[i] * dt_sqrt;
  y.push_back(current_y);
 }

return y;
}

vector<vector<double>> Simulation::Simulate(const vector<double>& t, int seed = -1) {
//passing here seed to ensure reproducibility over N realizations without compromising ensemble variance

 vector<vector<double>> realization_matrix(scalar_params.N);
 vector<vector<double>> random_matrix = GenerateRandomMatrix(seed);

 for (int j = 0; j < scalar_params.N; ++j) {
  realization_matrix[j] = EulerMaruyama(t, random_matrix[j]); 
    }
    
 return realization_matrix;
}








