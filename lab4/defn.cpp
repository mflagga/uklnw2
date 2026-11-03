#include "decl.hpp"

double kwGaussF(double xl, double xr, int a, int b, double he, double omega, double m){
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
        S += w[alpha]*Vfun(xodxi(xi[alpha],xl,xr,he),omega,m)*N(a,xi[alpha])*N(b,xi[alpha]);
    }
    return S;
}

double xodxi(double xi, double xLe, double xRe, double he){
    return 0.5*(xLe+xRe)+0.5*he*xi;
}

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

double Vfun(double x, double omega, double m){
    return 0.5*m*omega*omega*x*x;
}

int nlg(int e, int a){
    return 2*e+a;
}

double bilinf(int n, double *u, double **A, double *v){
    double *temp=new double[n]{};
    double temp2=0.0;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            temp[i] += A[i][j]*v[j];
        }
        temp2 += u[i]*temp[i];
    }
    delete [] temp;
    return temp2;
}