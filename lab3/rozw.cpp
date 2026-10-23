#include "decl.hpp"

void rozw(int Ne, int Ne_zapis){
    // alokacja inicjalizacja
    double *x = new double[Ne];
    for (int e=0;e<Ne;e++) x[e] = -1.0+e*2.0/Ne;
    double he=x[1]-x[0];
    double **F = new double*[Ne];
    for (int e=0;e<Ne;e++) F[e]=new double[3];
    for (int e=0;e<Ne;e++){
        for (int a=1;a<=3;a++){
            F[e][a-1] = 0.5*he*kwGaussF(x[e],x[e]+he,a,he);
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
    // rozwiazania
    if (Ne==Ne_zapis){
        // rozwiązanie dla węzłów
        std::ofstream wez("wez.csv");
        double xi, xx, u, dok;
        for (int i=0;i<2*Ne+1;i++){
            xx=-1.0+i*he/2.0;
            u=U[i];
            dok = dokl(xx);
            wez<<xx<<','<<u<<','<<dok<<','<<dok-u<<'\n';
        }
        wez.close();
        // rozwiązanie poza węzłami
        std::ofstream fun("fun.csv");
        int Nxi=300;
        for (int e=0;e<Ne;e++){
            for (int i=0;i<Nxi;i++){
                xi=-1.0+i*2.0/(Nxi-1);
                u=0.0;
                for (int a=0;a<3;a++){
                    u += U[nlg(e,a)]*N(a+1,xi);
                }
                xx = xodxi(xi,x[e],x[e]+he,he);
                dok = dokl(xx);
                fun<<xx<<','<<u<<','<<dok<<','<<dok-u<<'\n';
            }
        }
        fun.close();
        // druga pochodna
        double u2;
        double d2N[3]={1.0,-2.0,1.0};
        std::ofstream dp("dp.csv");
        for (int e=0;e<Ne;e++){
            for (int i=0;i<Nxi;i++){
                xi=-1.0+i*2.0/(Nxi-1);
                u2=0.0;
                for (int a=0;a<3;a++){
                    u2 += U[nlg(e,a)]*d2N[a];
                }
                u2 *= std::pow(2.0/he,2);
                xx = xodxi(xi,x[e],x[e]+he,he);
                dp<<xx<<','<<u2<<','<<-rho(xx)<<'\n';
            }
        }
        dp.close();
    }
    // funkcjonal energii
    double S{};
    for (int i=0;i<2*Ne+1;i++) S += U[i]*Fprawd[i];
    std::cout<<"n="<<Ne<<"; S="<<-0.5*S<<'\n';
    // czystki
    delete [] U;
    for (int e=0;e<Ne;e++) delete [] F[e];
    delete [] F;
    delete [] x;
    for (int i=0;i<2*Ne+1;i++) delete [] Kprawd[i];
    delete [] Kprawd;
    delete [] Fprawd;
}
