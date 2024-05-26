#include "params.h"
#include "simulation.h"
#include "functions.h"

double f (double t, double y) {
 return -y;
}
 
double g (double t, double y) {
 return 1;
}

int main() {

 double t0 = 0.0;
 double tf = 10;
 int n = 1000;     
 int N = 1000;  
 double y0 = 0.0;
 double sigma1 = 0.1;
 double sigma2 = 0.1;
 double rho = -1;
 int seed = 0;

 Params params = {t0, tf, n, N};
 Simulation sim(params); 
 
 vector<double> t = sim.GetTimeVector(); 
 vector<double> tau = sim.GetLagVector();  
 vector<vector<vector<double>>> random_matrices =  sim.CorrelatedMatrices(sigma1, sigma2, rho, seed);
 vector<vector<double>> random_matrix_1 = random_matrices[0];
 vector<vector<double>> random_matrix_2 = random_matrices[1]; 
 vector<vector<double>> realization_matrix_1 = sim.Simulate(y0, f, g, random_matrix_1);
 vector<vector<double>> realization_matrix_2 = sim.Simulate(y0, f, g, random_matrix_2); 

 vector<double> var_1 = EnsembleVar(realization_matrix_1);
 vector<double> var_2 = EnsembleVar(realization_matrix_2); 
 vector<double> corr_1 = EnsembleCorr(realization_matrix_1);
 vector<double> corr_2 = EnsembleCorr(realization_matrix_2); 
 
 vector<double> cross = EnsembleCross(realization_matrix_1, realization_matrix_2);
 
 vector<vector<double>> data_var(3);
 data_var[0] = t;
 data_var[1] = var_1;
 data_var[2] = var_2; 
 WriteToFile (data_var, "data_var.txt");

 vector<vector<double>> data_corr(3);
 data_corr[0] = t;
 data_corr[1] = corr_1;
 data_corr[2] = corr_2; 
 WriteToFile (data_corr, "data_corr.txt");
 
 vector<vector<double>> data_cross(2);
 data_cross[0] = tau;
 data_cross[1] = cross;
 
 WriteToFile(data_cross, "data_cross.txt");

 return 0;
}

