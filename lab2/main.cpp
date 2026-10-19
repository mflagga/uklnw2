#include "decl.hpp"

int main(){

    std::ofstream nul;

    /* energia */

    double bohr_to_nm=0.05292;
    double nm_to_bohr=1.0/bohr_to_nm;
    // double hartree_to_meV=27211.6;
    // double meV_to_hartree=1.0/hartree_to_meV;
    double d;
    int N;
    double beta=0.25;
    std::ofstream pkt1Ek("pkt1Ek.csv");
    std::ofstream pkt1dE0("pkt1dE0.csv");
    std::ofstream pkt1dEsum("pkt1dEsum.csv");
    for (int idN=0;idN<5;idN++){
        N=11+5*idN;
        for (int idd=0;idd<5;idd++){
            d=(3.0+1.0*idd)*nm_to_bohr;
            rozw(N,d,idN,idd,pkt1Ek,pkt1dE0,pkt1dEsum,beta,0,nul);
        }
    }
    pkt1Ek.close();
    pkt1dE0.close();
    pkt1dEsum.close();

    /* macierz przekrywania */

    std::ofstream pkt2kappa("pkt2kappa.csv");

    for (int idN=0;idN<5;idN++){
        N=11+5*idN;
        for (int idd=0;idd<5;idd++){
            d=(3.0+1.0*idd)*nm_to_bohr;
            for (int idb=0;idb<5;idb++){
                beta=0.1+(idb*0.1);
                rozw(N,d,idN,idd,nul,nul,nul,beta,idb,pkt2kappa);
            }
        }
    }

    pkt2kappa.close();

    // return zero
    return 0;
}
