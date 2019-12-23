#include "../include/matr4dp.h"


void    matr4d_init(matrice_p matrice_ptr,quaternione_t quaternione){
    int i,j,k,z;

    *matrice_ptr = (Item****) malloc((quaternione.a +1 )* sizeof(Item***) );
    for (i = 0; i <= quaternione.a; i++) {
        (*matrice_ptr)[i] = (Item***) malloc((quaternione.i +1 ) * sizeof(Item**) );
        for ( j = 0; j <= quaternione.i; j++) {
            (*matrice_ptr)[i][j] = (Item**) malloc((quaternione.j +1) * sizeof(Item*) );
            for ( k = 0; k <= quaternione.j; k++) {
                (*matrice_ptr)[i][j][k] = (Item*) malloc((quaternione.k +1) * sizeof(Item));
            }
        }
    }
}
void    matr4d_free(matrice_p matrice_ptr,quaternione_t quaternione) {
    int i,j,k,z;

    for (i = 0; i <= quaternione.a; i++) {
        for ( j = 0; j <= quaternione.i; j++) {
            for ( k = 0; k <= quaternione.j; k++) {
                free((*matrice_ptr)[i][j][k]);
            }
            free((*matrice_ptr)[i][j]);
        }
        free((*matrice_ptr)[i]);
    }
    free(*matrice_ptr);
}
void    matr4d_fill(matrice_p matrice_ptr,quaternione_t quaternione,int n){
    quaternione_t tmp;
    for ( tmp.a = 0; tmp.a <= quaternione.a; tmp.a++){
        for ( tmp.i = 0; tmp.i <= quaternione.i; tmp.i++){
            for ( tmp.j = 0; tmp.j <= quaternione.j; tmp.j++){
                for ( tmp.k = 0; tmp.k <= quaternione.k; tmp.k++){
                    inserisci_matr4dp(matrice_ptr,tmp,n);
                }
            }
        }   
    }
}
#define DBG 1

void    inserisci_matr4dp(matrice_p matrice_ptr,quaternione_t coordinate,int n){
#if DBG
    (*matrice_ptr)[coordinate.a][coordinate.i][coordinate.j][coordinate.k] = n;
#endif
}

int     estrai_matr4dp(matrice_p matrice_ptr,quaternione_t coordinate) {
    return (*matrice_ptr)[coordinate.a][coordinate.i][coordinate.j][coordinate.k];
}

quaternione_t    quaternioni_init(int a,int i,int j,int k){
    quaternione_t tmp;
    tmp.a = a;tmp.i = i;tmp.j = j;tmp.k = k;
    return tmp;
}