#ifndef __GRAFO__H__
#define __GRAFO__H__

#include <stdio.h>
#include <stdlib.h>

#include "../include/item.h"
#include "../include/st.h"
#include "../include/item.h"

#define MAX_NAME 30


typedef struct arco{
    Item vertice1;
    Item vertice2;
    int peso;
}arco_t;

typedef struct grafo *Grafo;

Grafo grafo_init(int V);    
void  grafo_free(Grafo G);

Grafo grafo_load(char* nome_file);
int   grafo_get_index(Grafo G,Item k);
void  grafo_insert_e(Grafo G,int id1,int id2,int peso);
void  grafo_remove_e(Grafo G,int id1,int id2);


#endif