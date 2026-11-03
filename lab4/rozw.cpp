#include "decl.hpp"

void rozw(int Ne, std::ofstream &Efile, std::ofstream &psifile, std::ofstream &psiprimfile){
    // preliczniki
    double bohr_to_nm=0.05292;
    double nm_to_bohr=1.0/bohr_to_nm;
    double hartree_to_meV=27211.6;
    double meV_to_hartree=1.0/hartree_to_meV;
    double omega= 10.0*meV_to_hartree;
    double m=0.067;
    double xmin=-64.0*nm_to_bohr;
    double xmax=-xmin;
    double *x = new double[Ne];
    for (int i=0;i<Ne;i++) x[i] = xmin + i*(xmax-xmin)/(Ne);
    double he = x[1]-x[0];
    // macierz A
    double A[3][3] = {{7.0,-8.0,1.0}, {-8.0, 16.0, -8.0}, {1.0, -8.0, 7.0}};
    for (int a=0;a<3;a++){
        for (int b=0;b<3;b++){
            A[a][b] /= 6.0*m*he;
        }
    }
    // macierz S
    double S[3][3] = {{4.0, 2.0, -1.0}, {2.0, 16.0, 2.0}, {-1.0, 2.0, 4.0}};
    for (int a=0;a<3;a++){
        for (int b=0;b<3;b++){
            S[a][b] *= he/30.0;
        }
    }

    // globalne
    double Vab;
    double **Hprawd = new double*[2*Ne+1];
    for (int i=0;i<2*Ne+1;i++) Hprawd[i] = new double[2*Ne+1]{};
    double **Sprawd = new double*[2*Ne+1];
    for (int i=0;i<2*Ne+1;i++) Sprawd[i] = new double[2*Ne+1]{};
    for (int e=0;e<Ne;e++){
        for (int a=0;a<3;a++){
            for (int b=0;b<3;b++){
                Vab = 0.5*he*kwGaussF(x[e],x[e]+he,a+1,b+1,he,omega,m);
                Hprawd[nlg(e,a)][nlg(e,b)] += A[a][b] + Vab;
                Sprawd[nlg(e,a)][nlg(e,b)] += S[a][b];
            }
        }
    }
    for (int i=0;i<2*Ne+1;i++){
        Hprawd[i][0]=0.0;
        Hprawd[0][i]=0.0;
        Hprawd[2*Ne][i]=0.0;
        Hprawd[i][2*Ne]=0.0;
        Sprawd[i][0]=0.0;
        Sprawd[0][i]=0.0;
        Sprawd[2*Ne][i]=0.0;
        Sprawd[i][2*Ne]=0.0;
    }
    Hprawd[0][0]=-omega;
    Hprawd[2*Ne][2*Ne]=-omega;
    Sprawd[0][0]=1.0;
    Sprawd[2*Ne][2*Ne]=1.0;

    // rozwiazenie
    double **c = new double*[2*Ne+1];
    for (int i=0;i<2*Ne+1;i++) c[i] = new double[2*Ne+1];
    double *E = new double[2*Ne+1];
    geneigsolve(2*Ne+1,Hprawd,Sprawd,c,E);

    // zapisanie
    for (int i=2;i<8;i++){
        if (i-2) Efile<<',';
        Efile<<E[i]*hartree_to_meV-((i-2)*10+5);

    }
    Efile<<'\n';
    psifile<<'\n';
    psiprimfile<<'\n';

    // czystki
    delete [] x;
    for (int i=0;i<2*Ne+1;i++) delete [] Hprawd[i];
    delete [] Hprawd;
    for (int i=0;i<2*Ne+1;i++) delete [] Sprawd[i];
    delete [] Sprawd;
    for (int i=0;i<2*Ne+1;i++) delete [] c[i];
    delete [] c;
    delete [] E;
}
