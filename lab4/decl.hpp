#ifndef DECL_HPP_
#define DECL_HPP_

#include <iostream>
#include <cmath>
#include <gsl/gsl_eigen.h>
#include <fstream>

double Vfun(double x, double omega, double m);
double N(int a, double xi);
double xodxi(double xi, double xLe, double xRe, double he);
double kwGaussF(double xl, double xr, int a, int b, double he, double omega, double m);
int nlg(int e, int a);
double bilinf(int n, double *u, double **A, double *v);
void geneigsolve(int N, double **H, double **S, double **c, double *E);
void rozw(int Ne, std::ofstream &Efile, std::ofstream &psifile, std::ofstream &psiprimfile, int Nezapis);

#endif
