#ifndef DECL_HPP_
#define DECL_HPP_

#include <iostream>
#include <cmath>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
#include <fstream>

double N(int a, double xi);
int nlg(int e, int a);
double rho(double x);
double xodxi(double xi, double xLe, double xRe, double he);
double kwGaussF(double xl, double xr, int a, double he);
void LUsolve(double **A, double *x, double *b, int n);
double G(double t);
double dokl(double x);
void rozw(int Ne, int Ne_zapis);

#endif
