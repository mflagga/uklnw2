#ifndef DECL_HPP_
#define DECL_HPP_

#include <iostream>
#include <cmath>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <fstream>

// double N1(double xi);
// double N2(double xi);
// double N3(double xi);
int nlg(int e, int a);
double rho(double x);
void LUsolve(double **A, double *x, double *b, int n);
double N(int a, double xi);
double kwGaussF(double xl, double xr, int a, double he);
double xodxi(double xi, double xLe, double xRe, double he);

#endif
