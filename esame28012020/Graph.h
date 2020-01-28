#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>

typedef struct edge {   
    int v; 
    int w; 
    int wt; 
} Edge;

typedef struct graph *Graph;


Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);


Graph GRAPHload(        FILE *fin);
void  GRAPHedges(       Graph G, 
                        Edge *a);

void  GRAPHstore(       Graph G, 
                        FILE *fout);

void  GRAPHinsertE(     Graph G, 
                        int id1, 
                        int id2, 
                        int wt);

void  GRAPHremoveE(     Graph G, 
                        int id1, 
                        int id2);

void k_core(            Graph G,
                        int k);

void GRAPH_removeV(     Graph G,
                        int i);

void GRAPH_insertV(     Graph G,
                        int i);

int GRAPH_degree(       Graph G,
                        int k,
                        int *sol,
                        int n);

int GRAPHcc(            Graph G);

int GRAPH_connected(   Graph G);

void j_edge_connected(Graph G,int j);


#endif
