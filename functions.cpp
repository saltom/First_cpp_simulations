#include "functions.h"
#include <iostream>
#include <cmath>

void WriteToFile(const vector<vector<double>>& data, const string& filename) {  

 int NumRows = data[0].size();  
 int NumCols = data.size();   
 ofstream file(filename);
 
 if (file.is_open()) {
  
 for (int i = 0; i < NumRows; ++i) {
  for (int j = 0; j < NumCols; ++j) {
   file << data[j][i];
   if (j < NumCols - 1) file << ",";  
   }
  file << "\n";
 }

  file.close();
}
 
 else {
  cerr << "Unable to open file\n";  
 }
}

vector<double> EnsembleMean(const vector<vector<double>> matrix) {

 int N = matrix.size();
 int n = matrix[0].size();
 vector<double> mean(n);
 
 for (int i=0; i<n; ++i) {
  double sum = 0.0;
 
  for (int j = 0; j < N; ++j) { 
   sum += matrix[j][i];
  }
  
  mean[i] = sum / N;
 }
 
return mean;
}

vector<double> EnsembleVar(const vector<vector<double>> matrix) {

 int N = matrix.size();
 int n = matrix[0].size(); 

 vector<double> var(n);
 vector<double> mean = EnsembleMean(matrix);

 for (int i=0; i<n; ++i) {
  double temp = 0.0;
 
  for (int j = 0; j < N; ++j) { 
   temp += pow((matrix[j][i] - mean[i]), 2);
  }
  
  var[i] = temp / N;
 }
 
 return var;
} 

vector<double> Autocorrelation (const vector<double>& time_series) {
 
 int n = time_series.size();
 vector<double> autocorr(n);

 for (int lag = 0; lag < n; ++lag) {
  double sum = 0.0;
  int count = n - lag;  

  for (int i = 0; i < count; ++i) {
   sum += time_series[i] * time_series[i + lag];
  }

  autocorr[lag] = sum/count;
 }

 return autocorr;
}

vector<double> EnsembleCorr(const vector<vector<double>>& realization_matrix) {  

 int N = realization_matrix.size();
 int n = realization_matrix[0].size();
  
 vector<vector<double>> correlation_matrix(N);
 
 for (int j=0; j<N; ++j){
  correlation_matrix[j] = Autocorrelation(realization_matrix[j]);
 }

 vector<double> steady_state_var = EnsembleVar(realization_matrix); 
 double sum = 0;
 for (int i = 0; i < n; ++i) {
  sum += steady_state_var[i];
 }
 double norm = sum/n; 

 vector<double> corr = EnsembleMean(correlation_matrix);
 vector<double> norm_corr(n);
 
 for (int i = 0; i < n; ++i) {
  norm_corr[i] = corr[i]/norm;
 }
 
 return norm_corr;
}
