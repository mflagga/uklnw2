#include "decl.hpp"

int main(void){
    // preliczniki
    // double bohr_to_nm=0.05292;
    // double nm_to_bohr=1.0/bohr_to_nm;
    // double hartree_to_meV=27211.6;
    // double meV_to_hartree=1.0/hartree_to_meV;

    std::ofstream Efile("Efile.csv");
    std::ofstream psifile("psifile.csv");
    std::ofstream psiprimfile("psiprimfile.csv");

    int Nearr[]={6,24,48};
    for (int Ne:Nearr){
        rozw(Ne,Efile,psifile,psiprimfile);
    }
    
    Efile.close();
    psifile.close();
    psiprimfile.close();

    // return zero
    return 0;
}
