#ifndef DECL_HPP_
#define DECL_HPP_

#include <iostream>
#include <cmath>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>
#include <fstream>

double phi(int i, double x, double alpha, double *X);
void geneigsolve(int N, double **H, double **S, double **c, double *E);
void rozw(int N, double d, int idN, int idd, std::ofstream &pkt1Ek, std::ofstream &pkt1dE0, std::ofstream &pkt1dEsum, double beta, int idb, std::ofstream &pkt2kappa);
void eigsolve(int N, double **A, double **v, double *lambda);
// double max(int n, double *arr);
// double min(int n, double *arr);

#endif
