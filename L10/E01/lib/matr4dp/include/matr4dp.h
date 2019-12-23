#ifndef __MATRICE__4DP__H__
#define __MATRICE__4DP__H__

#include <stdio.h>
#include <stdlib.h>

typedef int Item;

typedef Item***** matrice_p;

typedef struct quaternione {
    int a;
    int i;
    int j;
    int k;
}quaternione_t;


void    matr4d_init(matrice_p matrice_ptr,quaternione_t quaternione);
void    matr4d_free(matrice_p matrice_ptr,quaternione_t quaternione);

void    matr4d_fill(matrice_p matrice_ptr,quaternione_t quaternione,int n);
void    inserisci_matr4dp(matrice_p matr4d,quaternione_t coordinate,int n);

int     estrai_matr4dp(matrice_p matr4d,quaternione_t coordinate);

quaternione_t    quaternioni_init(int a,int i,int j,int k);

#endif