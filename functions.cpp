#include "functions.h"
#include <iostream>
#include <cmath>
#include <algorithm>

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

 vector<double> var = EnsembleVar(realization_matrix); 
 double sum = 0;
 
 for (int i = 0; i < n; ++i) {
  sum += var[i];
 }
 
 double norm = sum/n; 

 vector<double> corr = EnsembleMean(correlation_matrix);
 vector<double> norm_corr(n);
 
 for (int i = 0; i < n; ++i) {
  norm_corr[i] = corr[i]/norm;
 }
 
 return norm_corr;
}

vector<double> Crosscorrelation(const vector<double>& time_series1, const vector<double>& time_series2) {   
   
 int n1 = time_series1.size();
 int n2 = time_series2.size();
 int minLag = -(n2 - 1); 
 int maxLag = n1 - 1;    
 vector<double> crosscorr(maxLag - minLag + 1);

 for (int lag = minLag; lag <= maxLag; ++lag) {
  double sum = 0.0;
  int count = 0;

  for (int i = 0; i < n1; ++i) {
   int j = i + lag; 
   
   if (j >= 0 && j < n2) {
    sum += time_series1[i] * time_series2[j];
    ++count;
   }
  }

  if (count > 0) {
   crosscorr[lag - minLag] = sum / count; 
  }
  
  else {
   crosscorr[lag - minLag] = 0; 
  }
    }

    return crosscorr;
}

vector<double> EnsembleCross(const vector<vector<double>>& realization_matrix1, const vector<vector<double>>& realization_matrix2) {  

 int n1 = realization_matrix1[0].size();
 int n2 = realization_matrix2[0].size(); 
 int N = min(realization_matrix1.size(), realization_matrix2.size()); 
  
 vector<vector<double>> correlation_matrix(N);
 
 for (int j=0; j<N; ++j){
  correlation_matrix[j] = Crosscorrelation(realization_matrix1[j], realization_matrix2[j]);
 }

 vector<double> var1 = EnsembleVar(realization_matrix1); 
 vector<double> var2 = EnsembleVar(realization_matrix2);  
 
 double sum1 = 0;
 double sum2 = 0; 
 
 for (int i = 0; i < n1; ++i) {
  sum1 += sqrt(var1[i]);      
 }
 double norm1 = sum1/n1; 
 
 for (int i = 0; i < n2; ++i) {
  sum2 += sqrt(var2[i]);
 } 
 double norm2 = sum2/n2;
 
 double norm = norm1*norm2; 
 int n = n1 + n2 -1;   

 vector<double> cross = EnsembleMean(correlation_matrix);
 vector<double> norm_cross(n);
 
 for (int i = 0; i < n; ++i) {
  norm_cross[i] = cross[i]/norm;
 }
 
 return norm_cross;
}
























