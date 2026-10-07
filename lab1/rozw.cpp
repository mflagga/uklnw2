#include "decl.hpp"

void rozw(int n, std::ofstream &ufile, std::ofstream &Snfile){
    // macierz A
    double **A = new double*[n+1];
    for (int i=0;i<=n;i++) A[i] = new double[n+1];
    for (int i=0;i<=n;i++){
        for (int j=0;j<=n;j++){
            if ((i+j)%2){
                A[i][j]=0.0;
            }
            else{
                A[i][j]=double(8*(2*i*j+i+j-1))/((i+j-1)*(i+j+1)*(i+j+3));
            }
        }
    }
    // wektor b
    int Nint = 20;
    double *x = new double[Nint+1];
    for (int k=0;k<=Nint;k++) x[k]=-1+k*2/Nint;
    double *b = new double[n+1];
    for (int i=0;i<=n;i++){
        b[i] = 0.0;
        for (int k=0;k<Nint;k++){
            b[i] += kwGauss(x[k],x[k+1],i);
        }
    }
    // rozwiazanie Ac=b
    double *c = new double[n+1];
    linSysSolve(A,c,b,n+1);
    // rozwiazanie na u
    int N=300;
    double *t = new double[N];
    double *u = new double[N];
    for (int i=0;i<N;i++){
        t[i] = -1.0+i*2.0/(N-1);
        u[i]=0.0;
        for (int j=0;j<=n;j++){
            u[i] += c[j]*phi(j,t[i]);
        }
    }
    // zapisanie u i t
    // std::ofstream tfile("tfile.csv");
    // std::string filename = "un" + std::to_string(n) + ".csv";
    // std::ofstream ufile(filename);
    // for (int i=0;i<N;i++){
    //     if (i) {
    //         ufile<<',';
    //         tfile<<',';
    //     }
    //     ufile<<u[i];
    //     tfile<<t[i];
    // }
    // ufile.close();
    // tfile.close();

    // zapis t
    std::ofstream tfile("tfile.csv");
    for (int i=0;i<N;i++){
        if (i) tfile<<',';
        tfile<<t[i];
    }
    tfile.close();
    // dopis un
    for (int i=0;i<N;i++){
        if (i) ufile<<',';
        ufile<<u[i];
    }
    ufile<<'\n';
    // dopis Sn
    if (n) Snfile<<',';
    Snfile<<Sn(n+1,c,b);

    // czystki
    for (int i=0;i<=n;i++) delete [] A[i];
    delete [] A;
    delete [] x;
    delete [] b;
    delete [] c;
    delete [] t;
    delete [] u;
}