#include "decl.hpp"

double phi(int i, double x){
    return (x*x-1)*std::pow(x,i);
}

double bfun(int i, double x){
    return phi(i,x)*std::exp(-60*x*x);
}

double kwGauss(double a, double b, int i){
    double S{};
    double xi[8]={
        -0.9602898564975363,
        -0.7966664774136267,
        -0.5255324099163290,
        -0.1834346424956498,
        0.1834346424956498,
        0.5255324099163290,
        0.7966664774136267,
        0.9602898564975363
    };
    double w[8]={
        0.1012285362903763,
        0.2223810344533745,
        0.3137066458778873,
        0.3626837833783620,
        0.3626837833783620,
        0.3137066458778873,
        0.2223810344533745,
        0.1012285362903763
    };
    for (int alpha=0; alpha<8; alpha++){
        S += w[alpha]*bfun(i,0.5*(a+b)+0.5*(b-a)*xi[alpha]);
    }
    return 0.5*(b-a)*S;
}

void linSysSolve(double **A, double *x, double *b, int n){
    gsl_matrix *Agsl = gsl_matrix_alloc(n,n);
    gsl_vector *xgsl = gsl_vector_alloc(n);
    gsl_vector *bgsl = gsl_vector_alloc(n);
    for (int i=0;i<n;i++){
        gsl_vector_set(bgsl,i,b[i]);
        for (int j=0;j<n;j++){
            gsl_matrix_set(Agsl,i,j,A[i][j]);
        }
    }
    gsl_permutation *p = gsl_permutation_alloc(n);
    int s;
    gsl_linalg_LU_decomp(Agsl,p,&s);
    gsl_linalg_LU_solve(Agsl,p,bgsl,xgsl);
    for (int i=0;i<n;i++) x[i] = gsl_vector_get(xgsl,i);
    gsl_matrix_free(Agsl);
    gsl_vector_free(xgsl);
    gsl_vector_free(bgsl);
    gsl_permutation_free(p);
}

double Sn(int n, double *c, double *b){
    double s{};
    for (int i=0;i<n;i++){
        s += c[i]*b[i];
    }
    return -0.5*s;
}
