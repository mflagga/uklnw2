#include "decl.hpp"

int main(void){

    int N=300;
    int nn=7;

    double **u = new double*[nn];
    for (int i=0;i<nn;i++) u[i] = new double[N];

    std::ofstream ufile("ufile.csv");
    std::ofstream Snfile("Snfile.csv");
    std::ofstream nfile("nfile.csv");
    
    int k;
    for (int n=0;n<=12;n+=2){
        k=n/2;
        if (n) nfile<<',';
        nfile<<n;
        rozw(n,ufile,Snfile,N,u[k]);
    }

    ufile.close();
    Snfile.close();
    nfile.close();

    // obliczenie całki
    double *D = new double[nn-1];

    // zapis do Dnfile

    // czystki 
    for (int i=0;i<nn;i++) delete [] u[i];
    delete [] u;
    delete [] D;
    
    // return zero
    return 0;
}
