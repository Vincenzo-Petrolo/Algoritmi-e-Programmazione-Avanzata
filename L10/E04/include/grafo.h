#ifndef __GRAFO__H__
#define __GRAFO__H__

#include <stdio.h>
#include <stdlib.h>

#include "../include/item.h"
#include "../include/st.h"
#include "../include/item.h"
#include "../include/lista.h"

#define MAX_NAME 30


typedef struct arco{
    Item vertice1;
    Item vertice2;
    int peso;
}arco_t;

typedef struct grafo *Grafo;

Grafo grafo_init(int V);    
void  grafo_free(Grafo G);

Grafo   grafo_load(char* nome_file);
int     grafo_get_index(Grafo G,Key k);
void    grafo_insert_e(Grafo G,int id1,int id2,int peso);
void    grafo_remove_e(Grafo G,int id1,int id2);
Grafo   madj_2_ladj(Grafo G);
void    stampa_grafo(Grafo G,FILE *fout);
boolean sottografo_m(Grafo G,Key elab1,Key elab2,Key elab3);
boolean sottografo_l(Grafo G,Key elab1,Key elab2,Key elab3);




#endif