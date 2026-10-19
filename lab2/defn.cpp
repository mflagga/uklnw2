#include "decl.hpp"

// double phi(int i, double x, double alpha, double *X){
//     return std::exp(-alpha*std::pow(x-X[i],2));
// }

// double max(int n, double *arr){
//     double temp = arr[0];
//     for (int i=1;i<n;i++){
//         if (arr[i]>temp) temp=arr[i];
//     }
//     return temp;
// }

// double min(int n, double *arr){
//     double temp = arr[0];
//     for (int i=1;i<n;i++){
//         if (arr[i]<temp) temp=arr[i];
//     }
//     return temp;
// }

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
