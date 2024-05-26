#include "simulation.h"

Simulation::Simulation(const Params& params) : params(params) {      // constructor generates time and lag 

 double current_time = params.t0;
 double current_lag = -params.tf;
 double dt = (params.tf - params.t0) / params.n;   
 time_vector.push_back(current_time);  
 lag_vector.push_back(current_lag);
 int lag_number = 2 * params.n - 1;

 for (int i = 1; i < params.n; ++i) {
  current_time += dt;  
  time_vector.push_back(current_time);
 }
 
 for (int i = 1; i < lag_number; ++i) {
  current_lag += dt;  
  lag_vector.push_back(current_lag);
 }
  
}

vector<double> Simulation::GetTimeVector() const {
    return time_vector;
}

vector<double> Simulation::GetLagVector() const {
    return lag_vector;
}

vector<vector<double>> Simulation::RandomMatrix(double sigma, int seed) { 

 vector<vector<double>> random_matrix(params.N, vector<double>(params.n));;
 mt19937 gen;

 if (seed == -1) {     //if seed is not provided a random one is chosen
  random_device rd;
  gen.seed(rd());
 }
 
 else {
  gen.seed(seed);
 } 
 
 normal_distribution<> distr(0.0, sigma); 

 for (int j = 0; j < params.N; ++j) {
  for (int i = 0; i < params.n; ++i) {  
   random_matrix[j][i] = distr(gen); 
  }
 }

return random_matrix;
}

vector<vector<vector<double>>> Simulation::CorrelatedMatrices(double sigma1, double sigma2, double rho, int seed) { 

 vector<vector<vector<double>>> random_matrices;
 mt19937 gen;

 if (seed == -1) {     
  random_device rd;
  gen.seed(rd());
 }
 
 else {
  gen.seed(seed);
 } 
 
 normal_distribution<> distr(0.0, 1.0); 

 double a = sigma1;      //Cholesky decomposition
 double b = rho * sigma2;
 double c = sigma2 * sqrt(1 - std::pow(rho, 2));

 vector<vector<double>> matrix1(params.N, vector<double>(params.n));
 vector<vector<double>> matrix2(params.N, vector<double>(params.n));

 for (int j = 0; j < params.N; ++j) {
  for (int i = 0; i < params.n; ++i) {
  
   double x1 = distr(gen);
   double x2 = distr(gen);
   double z1 = a * x1;
   double z2 = b * x1 + c * x2;

   matrix1[j][i] = z1;
   matrix2[j][i] = z2;
  }
 }

 random_matrices.push_back(matrix1);
 random_matrices.push_back(matrix2);
 
 return random_matrices;
} 

vector<double> Simulation::EulerMaruyama(double y0, double (*f)(double, double), double (*g)(double, double), const vector<double> & random_array) {

 vector<double> y;
 double dt = (params.tf - params.t0) / params.n;  
 y.push_back(y0);
 double current_y = y0;
 double dt_sqrt = sqrt(dt);
 
 for (int i = 0; i < params.n; ++i) {  
  current_y += f(time_vector[i], current_y) * dt + g(time_vector[i], current_y) * random_array[i] * dt_sqrt;
  y.push_back(current_y);
 }

return y;
}

vector<vector<double>> Simulation::Simulate(double y0, double (*f)(double, double), double (*g)(double, double), const vector<vector<double>> & random_matrix) {

 vector<vector<double>> realization_matrix(params.N);

 for (int j = 0; j < params.N; ++j) {
  realization_matrix[j] = EulerMaruyama(y0, f, g, random_matrix[j]); 
    }
    
 return realization_matrix;
}








