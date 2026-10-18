#include "decl.hpp"

double phi(int i, double x, double alpha, double *X){
    return std::exp(-alpha*std::pow(x-X[i],2));
}
