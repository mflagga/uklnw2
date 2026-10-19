#include "decl.hpp"

void geneigsolve(int N, double **H, double **S, double **c, double *E){
    gsl_eigen_gensymmv_workspace *test = gsl_eigen_gensymmv_alloc(N);
    // kopiowanie macierzy
    gsl_matrix *Hgsl = gsl_matrix_alloc(N,N);
    gsl_matrix *Sgsl = gsl_matrix_alloc(N,N);
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            gsl_matrix_set(Hgsl,i,j,H[i][j]);
            gsl_matrix_set(Sgsl,i,j,S[i][j]);
        }
    }
    // alokacja rozwiazania 
    gsl_matrix *cgsl = gsl_matrix_alloc(N,N);
    gsl_vector *Egsl = gsl_vector_alloc(N);
    // rozwiazanie
    gsl_eigen_gensymmv(Hgsl,Sgsl,Egsl,cgsl,test);
    // sortowanie rozwiazania
    gsl_eigen_gensymmv_sort(Egsl,cgsl,GSL_EIGEN_SORT_VAL_ASC);
    // kopia rozwiazania
    for (int i=0;i<N;i++){
        E[i] = gsl_vector_get(Egsl,i);
        for (int j=0;j<N;j++){
            c[i][j] = gsl_matrix_get(cgsl,i,j);
        }
    }
    // czstki
    gsl_vector_free(Egsl);
    gsl_matrix_free(cgsl);
    gsl_matrix_free(Sgsl);
    gsl_matrix_free(Hgsl);
    gsl_eigen_gensymmv_free(test);
}

void eigsolve(int N, double **A, double **v, double *lambda){
    gsl_eigen_symmv_workspace *test = gsl_eigen_symmv_alloc(N);
    // kopiwoanie macierzy
    gsl_matrix *Agsl = gsl_matrix_alloc(N,N);
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            gsl_matrix_set(Agsl,i,j,A[i][j]);
        }
    }
    // alokacja rozwiazania
    gsl_matrix *vgsl = gsl_matrix_alloc(N,N);
    gsl_vector *lgsl = gsl_vector_alloc(N);
    // rozwiazanie
    gsl_eigen_symmv(Agsl,lgsl,vgsl,test);
    // sortowanie rozw
    gsl_eigen_symmv_sort(lgsl,vgsl,GSL_EIGEN_SORT_VAL_ASC);
    // kopiwoanie rozwiazania
    for (int i=0;i<N;i++){
        lambda[i] = gsl_vector_get(lgsl,i);
        for (int j=0;j<N;j++){
            v[i][j] = gsl_matrix_get(vgsl,i,j);
        }
    }
    // czytski
    gsl_vector_free(lgsl);
    gsl_matrix_free(vgsl);
    gsl_matrix_free(Agsl);
    gsl_eigen_symmv_free(test);
}
