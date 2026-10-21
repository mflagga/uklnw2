#include "decl.hpp"

int main(){
    int Ne=5;
    // alokacja inicjalizacja
    double *x = new double[Ne];
    for (int e=0;e<Ne;e++) x[e] = -1.0+2.0/Ne;
    double he=x[1]-x[0];
    double **F = new double*[Ne];
    for (int e=0;e<Ne;e++) F[e]=new double[3];
    for (int e=0;e<Ne;e++){
        for (int a=1;a<=3;a++){
            F[e][a-1] = 0.5*he*kwGaussF(-1.0,1.0,a,he);
        }
    }
    double K[3][3]={{7.0, -8.0, 1.0}, {-8.0, 16.0, -8.0}, {1.0, -8.0, 7.0}};
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            K[i][j] *= 1.0/(3.0*he);
        }
    }
    // globalne wektory
    double *Fprawd=new double[2*Ne+1]{};
    double **Kprawd= new double*[2*Ne+1];
    for (int i=0;i<2*Ne+1;i++) Kprawd[i]=new double[2*Ne+1]{};
    for (int e=0;e<Ne;e++){
        for (int a=0;a<3;a++){
            for (int b=0;b<3;b++){
                Kprawd[nlg(e,a)][nlg(e,b)] += K[a][b];
            }
            Fprawd[nlg(e,a)] += F[e][a];
        }
    }
    // modyfikacja
    for (int i=0;i<2*Ne+1;i++){
        Kprawd[0][i]=0.0;
        Kprawd[2*Ne][i]=0.0;
    }
    Kprawd[0][0]=1.0;
    Kprawd[2*Ne][2*Ne]=1.0;
    Fprawd[0]=0.0;
    Fprawd[2*Ne]=0.0;
    double *U=new double[2*Ne+1];
    LUsolve(Kprawd,U,Fprawd,2*Ne+1);
    double *u=new double[2*Ne+1]{};
    // zostało skleić rozwiązanie dla u.
    // czystki
    delete [] U;
    delete [] u;
    for (int e=0;e<Ne;e++) delete [] F[e];
    delete [] F;
    delete [] x;
    for (int i=0;i<2*Ne+1;i++) delete [] Kprawd[i];
    delete [] Kprawd;
    delete [] Fprawd;
    return 0;
}
