#include "params.h"
#include "simulation.h"
#include "functions.h"

double f (double t, double y) {
 return - y;
}
 
double g (double t, double y) {
 return 1;
}

int main() {

 double t0 = 0.0;
 double y0 = 0.0;
 double sigma = 0.1;
 double tf = 10;
 int seed = 0;
 int n = 1000;     
 int N = 1000;

 ScalarParams scalar_params = {t0, y0, sigma, tf, n, N};
 VectorParams vector_params = {f, g};
 
 Simulation sim(scalar_params, vector_params); 
 
 vector<double> t = sim.GetTimeVector(); 
 vector<vector<double>> result_matrix = sim.Simulate(seed);
 vector<double> var = EnsembleVar(result_matrix);
 vector<double> corr = EnsembleCorr(result_matrix);
 
 vector<vector<double>> data_var(2);
 data_var[0] = t;
 data_var[1] = var;
 WriteToFile (data_var, "data_var.txt");

 vector<vector<double>> data_corr(2);
 data_corr[0] = t;
 data_corr[1] = corr;
 WriteToFile (data_corr, "data_corr.txt");

 return 0;
}

