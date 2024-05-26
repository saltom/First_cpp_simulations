#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <fstream>

using namespace std;

void WriteToFile (const vector<vector<double>>& data, const string& filename);

vector<double> EnsembleMean(const vector<vector<double>> matrix);
 
vector<double> EnsembleVar(const vector<vector<double>> matrix);

vector<double> Autocorrelation (const vector<double>& time_series);

vector<double> EnsembleCorr(const vector<vector<double>>& realization_matrix);

vector<double> Crosscorrelation(const vector<double>& time_series1, const vector<double>& time_series2);

vector<double> EnsembleCross(const vector<vector<double>>& realization_matrix1, const vector<vector<double>>& realization_matrix2);

#endif 
