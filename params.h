#ifndef PARAMS_H
#define PARAMS_H

struct ScalarParams {

 double t0;
 double y0;
 double sigma;
 double tf;
 int n;
 int N;


};

struct VectorParams {

 double (*f)(double, double);
 double (*g)(double, double);

};

#endif 
