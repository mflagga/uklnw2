#ifndef DECL_HPP_
#define DECL_HPP_

#include <iostream>
#include <cmath>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include <fstream>
#include <string>
#include <iomanip>

double phi(int i, double x);
double bfun(int i, double x);
double kwGauss(double a, double b, int i);
void linSysSolve(double **A, double *x, double *b, int n);
double Sn(int n, double *c, double *b);
void rozw(int n, std::ofstream &ufile, std::ofstream &Snfile, int N, double *u);

#endif
