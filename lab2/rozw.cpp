#include "decl.hpp"

void rozw(int N, double d, int idx, int idy, std::ofstream &pkt1Ek, std::ofstream &pkt1dE0, std::ofstream &pkt1dEsum){
    // preliczniki
    double bohr_to_nm=0.05292;
    double nm_to_bohr=1.0/bohr_to_nm;
    double hartree_to_meV=27211.6;
    double meV_to_hartree=1.0/hartree_to_meV;
    double hbar=1.0;
    double mstar=0.067;
    // parametry
    double omega=10.0*meV_to_hartree;
    // double d=6.0*nm_to_bohr;
    // int N=11;
    double beta=0.25;
    double alpha=beta/(d*d);
    double p=2*alpha;
    // alokacja inicjalizacja
    double *X = new double[N];
    for (int i=0;i<N;i++) X[i]=d*(i-1.0-(N+1)/2.0);
    double **S = new double*[N];
    for (int i=0;i<N;i++) S[i] = new double[N];
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            S[i][j] = std::sqrt(M_PI/p)*std::exp(-alpha*alpha*std::pow(X[i]-X[j],2)/p);
        }
    }
    double **T = new double*[N];
    for (int i=0;i<N;i++) T[i] = new double[N];
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            T[i][j] = 1.0/(2*mstar)*S[i][j]*(2.0*alpha*alpha/p-4*std::pow(alpha,4)*std::pow(X[i]-X[j],2)/(p*p));
        }
    }
    double **P = new double*[N];
    for (int i=0;i<N;i++) P[i] = new double[N];
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            P[i][j] = (alpha*X[i] + alpha*X[j])/p;
        }
    }
    double **V = new double*[N];
    for (int i=0;i<N;i++) V[i] = new double[N];
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            V[i][j] = 0.5*mstar*omega*omega*S[i][j]*(std::pow(P[i][j],2)+1.0/(2*p));
        }
    }
    double **H = new double*[N];
    for (int i=0;i<N;i++) H[i] = new double[N];
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            H[i][j] = T[i][j] +V[i][j];
        }
    }
    // rozwiazanie 
    double **c = new double*[N];
    for (int i=0;i<N;i++) c[i] = new double[N];
    double *E = new double[N];
    eigsolve(N,H,S,c,E);
    // for (int i=0;i<N;i++){
    //     std::cout<<E[i]*hartree_to_meV<<'\n';
    // }
    double Esum{};
    for (int i=0;i<5;i++){
        if (idx || idy || i) pkt1Ek<<',';
        pkt1Ek<<E[i]*hartree_to_meV;
        Esum += E[i];
    }
    if (idx || idy) pkt1dE0<<',';
    pkt1dE0<<E[0]*hartree_to_meV-5.0;
    if (idx || idy) pkt1dEsum<<',';
    pkt1dEsum<<Esum*hartree_to_meV-125.0;
    // czystki
    delete [] X;
    for (int i=0;i<N;i++) delete [] S[i];
    delete [] S;
    for (int i=0;i<N;i++) delete [] T[i];
    delete [] T;
    for (int i=0;i<N;i++) delete [] P[i];
    delete [] P;
    for (int i=0;i<N;i++) delete [] V[i];
    delete [] V;
    for (int i=0;i<N;i++) delete [] H[i];
    delete [] H;
    for (int i=0;i<N;i++) delete [] c[i];
    delete [] c;
    delete [] E;
}