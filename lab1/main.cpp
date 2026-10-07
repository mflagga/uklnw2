#include "decl.hpp"

int main(void){

    std::ofstream ufile("ufile.csv");
    std::ofstream Snfile("Snfile.csv");
    std::ofstream nfile("nfile.csv");
    
    for (int n=0;n<=12;n+=2){
        if (n) nfile<<',';
        nfile<<n;
        rozw(n,ufile,Snfile);
    }

    ufile.close();
    Snfile.close();
    nfile.close();

    // wczytanie plików 

    // obliczenie całki

    // zapis do Dnfile
    
    // return zero
    return 0;
}
