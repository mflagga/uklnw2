#include "decl.hpp"

int main(){
    double bohr_to_nm=0.05292;
    double nm_to_bohr=1.0/bohr_to_nm;
    double hartree_to_meV=27211.6;
    double meV_to_hartree=1.0/hartree_to_meV;
    double d;
    int N;
    std::ofstream pkt1Ek("pkt1Ek.csv");
    std::ofstream pkt1dE0("pkt1dE0.csv");
    std::ofstream pkt1dEsum("pkt1dEsum.csv");
    for (int idx=0;idx<5;idx++){
        N=11+5*idx;
        for (int idy=0;idy<5;idy++){
            d=(3.0+1.0*idy)*nm_to_bohr;
            rozw(N,d,idx,idy,pkt1Ek,pkt1dE0,pkt1dEsum);
        }
    }
    pkt1Ek.close();
    pkt1dE0.close();
    pkt1dEsum.close();
    // return zero
    return 0;
}
