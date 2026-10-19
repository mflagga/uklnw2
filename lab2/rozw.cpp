#include "decl.hpp"

void rozw(int N, double d, int idN, int idd, std::ofstream &pkt1Ek, std::ofstream &pkt1dE0, std::ofstream &pkt1dEsum, double beta, int idb, std::ofstream &pkt2kappa, std::ofstream &pkt3ff){
    // preliczniki
    double bohr_to_nm=0.05292;
    double nm_to_bohr=1.0/bohr_to_nm;
    double hartree_to_meV=27211.6;
    double meV_to_hartree=1.0/hartree_to_meV;
    // double hbar=1.0;
    double mstar=0.067;
    // parametry
    double omega=10.0*meV_to_hartree;
    // double d=6.0*nm_to_bohr;
    // int N=11;
    // double beta=0.25;
    double alpha=beta/(d*d);
    double p=2*alpha;
    // alokacja inicjalizacja
    double *X = new double[N];
    for (int i=0;i<N;i++) X[i]=d*(i-(N-1)/2.0);
    double **S = new double*[N];
    double **T = new double*[N];
    double **P = new double*[N];
    double **V = new double*[N];
    double **H = new double*[N];
    for (int i=0;i<N;i++){
        S[i] = new double[N];
        T[i] = new double[N];
        P[i] = new double[N];
        V[i] = new double[N];
        H[i] = new double[N];
        for (int j=0;j<N;j++){
            S[i][j] = std::sqrt(M_PI/p)*std::exp(-alpha*alpha*std::pow(X[i]-X[j],2)/p);
            T[i][j] = 1.0/(2*mstar)*S[i][j]*(2.0*alpha*alpha/p-4*std::pow(alpha,4)*std::pow(X[i]-X[j],2)/(p*p));
            P[i][j] = (alpha*X[i] + alpha*X[j])/p;
            V[i][j] = 0.5*mstar*omega*omega*S[i][j]*(std::pow(P[i][j],2)+1.0/(2*p));
            H[i][j] = T[i][j] + V[i][j];
        }
    }
    // rozwiazanie 
    double **c = new double*[N];
    for (int i=0;i<N;i++) c[i] = new double[N];
    double *E = new double[N];
    if (beta>0.24 && beta<0.26) geneigsolve(N,H,S,c,E);
    // for (int i=0;i<N;i++){
    //     std::cout<<E[i]*hartree_to_meV<<'\n';
    // }
    double Esum{};
    for (int i=0;i<5;i++){
        if (idN || idd || i) pkt1Ek<<',';
        pkt1Ek<<E[i]*hartree_to_meV;
        Esum += E[i];
    }
    if (idN || idd) pkt1dE0<<',';
    pkt1dE0<<E[0]*hartree_to_meV-5.0;
    if (idN || idd) pkt1dEsum<<',';
    pkt1dEsum<<Esum*hartree_to_meV-125.0;
    // macierz przekrywania 
    double *s = new double[N];
    double **u = new double*[N];
    for (int i=0;i<N;i++) u[i] = new double[N];
    eigsolve(N,S,u,s);
    double kappa = s[N-1]/s[0];
    if (idN || idd || idb) pkt2kappa<<',';
    pkt2kappa<<kappa;
    // f falowe
    if (beta>0.24 && beta<0.26){
        int nx=300;
        double xa=-70.0*nm_to_bohr;
        double xb=-xa;
        double dx=(xb-xa)/(nx-1);
        double *x = new double[nx];
        for (int i=0;i<nx;i++) x[i] = xa+i*dx;
        double *psi = new double[nx];
        double norm;
        for (int k=0;k<5;k++){
            for (int i=0;i<nx;i++) psi[i]=0.0;
            norm=0.0;
            for (int i=0;i<nx;i++){
                for (int j=0;j<N;j++){
                    psi[i] += c[j][k]*std::exp(-alpha*std::pow(x[i]-X[j],2));
                }
                norm+=psi[i]*psi[i]*dx;
            }
            for (int i=0;i<nx;i++){
                psi[i] *= 1.0/std::sqrt(norm);
                if (i) pkt3ff<<',';
                pkt3ff<<psi[i]*1.0/std::sqrt(bohr_to_nm);
            }
            pkt3ff<<'\n';
        }
        delete [] x;
        delete [] psi;
    }
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
    delete [] s;
    for (int i=0;i<N;i++) delete [] u[i];
    delete [] u;
}