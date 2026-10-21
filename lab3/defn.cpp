#include "decl.hpp"

// double N1(double xi){
//     return 0.5*(xi*(xi-1.0));
// }

// double N2(double xi){
    //     return 1.0-xi*xi;
    // }
    
    // double N3(double xi){
        //     return 0.5*(xi*(xi+1.0));
// }

double N(int a, double xi){
    if (a==1){
        return 0.5*(xi*(xi-1.0));
    }
    else if (a==2){
        return 1.0-xi*xi;
    }
    else if (a==3){
        return 0.5*(xi*(xi+1.0));
    }
    else return 0.0;
}

int nlg(int e, int a){
    return 2*e+a;
}

double rho(double x){
    return std::exp(-60.0*x*x);
}

double gfun(int a, double xi,double xl, double xr, double he){
    return rho(xodxi(xi,xl,xr,he))*N(a,xi);
}

double xodxi(double xi, double xLe, double xRe, double he){
    return 0.5*(xLe+xRe)+0.5*he*xi;
}

double kwGaussF(double xl, double xr, int a, double he){
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
        S += w[alpha]*gfun(a,0.5*(xl+xr)+0.5*(xr-xl)*xi[alpha],xl,xr,he);
    }
    return 0.5*(xr-xl)*S;
}

void LUsolve(double **A, double *x, double *b, int n){
    gsl_matrix *Agsl = gsl_matrix_alloc(n,n);
    gsl_vector *xgsl= gsl_vector_alloc(n);
    gsl_vector *bgsl=gsl_vector_alloc(n);
    gsl_permutation *p = gsl_permutation_alloc(n);
    int signum;
    for (int i=0;i<n;i++){
        gsl_vector_set(bgsl,i,b[i]);
        for (int j=0;j<n;j++){
            gsl_matrix_set(Agsl,i,j,A[i][j]);
        }
    }
    gsl_linalg_LU_decomp(Agsl,p,&signum);
    gsl_linalg_LU_solve(Agsl,p,bgsl,xgsl);
    for (int i=0;i<n;i++){
        x[i] = gsl_vector_get(xgsl,i);
    }
    gsl_permutation_free(p);
    gsl_vector_free(bgsl);
    gsl_vector_free(xgsl);
    gsl_matrix_free(Agsl);
}
