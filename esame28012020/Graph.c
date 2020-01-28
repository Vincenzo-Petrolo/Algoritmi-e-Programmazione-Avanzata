#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "ST.h"
#include "Queue.h"
#include "Graph.h"


struct graph {
  int V; 
  int E; 
  int **madj; 
  Edge *edges;
	ST tab; 
};

static void comb_semplici(  Graph G,
                            int m,
                            int *sol,
                            int *best_sol,
                            int start,
                            int pos,
                            int *trovato,
                            int k);

static void powset_combsemplici(  Graph G,
                                  int m,
                                  int start,
                                  int pos,
                                  int *trovato,
                                  int *sol,
                                  int *best_sol);


static Edge EDGEcreate(	int v, 
                        int w, 
                        int wt);

static int **MATRIXint(			int r, 
                            int c, 
                            int val);

static void  insertE(			Graph G,
                          Edge e);

static void  removeE(			Graph G, 
                          Edge e);


unsigned long int factorialR(int n){
  if (n == 0)
      return 1;
  return factorialR(n-1) * n;
}

unsigned long int coeffBinomiale(int n,int k){
  return(factorialR(n)/(factorialR(k)*factorialR(n-k))) +0.5;
}


static Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

static int **MATRIXint(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int *));
  if (t == NULL)
    return NULL;
  for (i=0; i < r; i++) {
    t[i] = malloc(c * sizeof(int));
    if (t[i] == NULL)
      return NULL;
  }
  for (i=0; i < r; i++)
    for (j=0; j < c; j++)
      t[i][j] = val;
  return t;
}

Graph GRAPHinit(int V) {
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;
  G->V = V;
  G->E = 0;
  G->madj = MATRIXint(V, V, 0);
  return G;
}

void GRAPHfree(Graph G) {
  int i;

  for (i=0; i<G->V; i++)
    free(G->madj[i]);
  free(G->madj);
  STfree(G->tab);
  free(G->edges);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int n,v,w,counter = 0;
  char label[10+1],label2[10+1];
  Graph G;

  fscanf(fin, "%d", &n);
  G = GRAPHinit(n);
  G->edges = malloc(coeffBinomiale(n,2)*sizeof(Edge));
  G->tab = STinit(n);

  for (int i=0; i<n; i++) {
    fscanf(fin, "%s", label);
    STinsert(G->tab, label, i);
  }

  while(fscanf(fin, "%s %s", label, label2) != EOF) { 
    GRAPHinsertE(G,STsearch(G->tab,label) , STsearch(G->tab,label2), 1);
    G->edges[counter] = EDGEcreate(STsearch(G->tab,label),STsearch(G->tab,label2),1);
    counter++;
  }
  G->E = counter;
  return G;
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;

  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = wt;
  G->madj[w][v] = wt;
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, w, E = 0;
  for (v=0; v < G->V; v++)
    for (w=v+1; w < G->V; w++)
      if (G->madj[v][w] == 1)
        a[E++] = EDGEcreate(v, w,1);
}

void GRAPHstore(Graph G, FILE *fout) {
  int i;
  Edge *a;

  a = malloc(G->E * sizeof(Edge));
  if (a == NULL)
    return;

  GRAPHedges(G, a);

  fprintf(fout, "%d\n", G->V);
  for (i = 0; i < G->V; i++)
    fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));

  for (i = 0; i < G->E; i++)
    fprintf(fout, "%s  %s %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);

}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
  insertE(G, EDGEcreate(id1, id2, wt));
}

void GRAPHremoveE(Graph G, int id1, int id2) {
  removeE(G, EDGEcreate(id1, id2, 0));
}

static void  removeE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  if (G->madj[v][w] != 0)
    G->E--;
  G->madj[v][w] = 0;
  G->madj[w][v] = 0;
}

void j_edge_connected(Graph G,int j){
  int i,trovato = 0;
  int *sol  = malloc(G->E*sizeof(int));
  int *best_sol = malloc(G->E*sizeof(int));

  for ( i = j; i < G->E; i++){
    powset_combsemplici(G,i,0,0,&trovato,sol,best_sol);
    if (trovato == 1){
      for (int j = 0; j < i; j++){
        GRAPHremoveE(G,G->edges[best_sol[j]].v,G->edges[best_sol[j]].w);
      }
      GRAPHstore(G,stdout);
      free(sol);
      free(best_sol);
      return;
    }
  }
  printf("\nInsieme non trovato!");
  free(sol);
  free(best_sol);
  return;
}

static void powset_combsemplici(Graph G,int m,int start,int pos,int *trovato,int *sol,int *best_sol){
  int i;

  if (*trovato != 1){
    if (pos >= m){
      for ( i = 0; i < m; i++){
        if (sol[i] != -1){
          GRAPHremoveE(G,G->edges[sol[i]].v,G->edges[sol[i]].w);  
        }
      }

      if (!GRAPH_connected(G)){
        *trovato = 1;
        for ( i = 0; i < m; i++){
          best_sol[i] = sol[i];
        }
      }

      for ( i = 0; i < m; i++){       
        if (sol[i] != -1){            
          GRAPHinsertE(G,G->edges[sol[i]].v,G->edges[sol[i]].w,1);
        }
      }
      return;
    }    
    
    for ( i = start; i < G->E; i++){
      sol[pos] = i;
      powset_combsemplici(G,m,i+1,pos+1,trovato,sol,best_sol);
    }
  }
}

void k_core(Graph G,int k){
  int *sol = malloc(G->V*sizeof(int));
  int *best_sol = malloc(G->V*sizeof(int));
  int trovato = 0;

  for (int i = 0; i < G->V; i++){   //aggiunto
    sol[i] = -1;
  }
  
  for (int i = 3; i < G->V; i++){
    comb_semplici(G,i,sol,best_sol,0,0,&trovato,k);
    if (trovato == 1){
      for (int i = 0; i < G->V; i++){
        if (best_sol[i] != -1){
          GRAPH_removeV(G,best_sol[i]);   //modificato per via dell'errore di sotto
        }
      }
      GRAPHstore(G,stdout);
      for (int i = 0; i < G->V; i++){
        if (best_sol[i] != -1){
          GRAPH_insertV(G,best_sol[i]);   //modificato per via dell'errore di sotto
        }
      }
      return;
    }
  }
  printf("\nNon ho trovato il k-core");
}

static void comb_semplici(Graph G,int m,int *sol,int *best_sol,int start,int pos,int *trovato,int k){
  int i;
  if (*trovato != 1){ 
    if (pos >= m){
      for ( i = 0; i < m; i++){
        if (sol[i] != -1){
          GRAPH_removeV(G,sol[i]);
        }
      }

      if (GRAPH_degree(G,k,sol,m)){
        *trovato = 1;
        for ( i = 0; i < G->V; i++){
          best_sol[i] = sol[i];
        }
      }

      for ( i = 0; i < m; i++){
        if (sol[i] != -1){
          GRAPH_insertV(G,sol[i]);
        }
      }

      return;
    }
    

    for ( i = start; i < G->V; i++){
      sol[pos] = i;
      comb_semplici(G,m,sol,best_sol,i+1,pos+1,trovato,k);
    }      
  }
}

void GRAPH_removeV(Graph G,int i){
  int j;
  for ( j = 0; j < G->V; j++){
    if (G->madj[i][j] != 0){
      G->madj[i][j] = 0;
      G->madj[j][i] = 0;
      G->E--;
    }
  }
}

void GRAPH_insertV(Graph G,int i){
  int j;
  for ( j = 0; j < G->E; j++){
    if (G->edges[j].v == i || G->edges[j].w == i)
      GRAPHinsertE(G,G->edges[j].v,G->edges[j].w,1);
  }
}

int GRAPH_degree(Graph G,int k,int* sol,int n){
  int i,j,counter = 0;
  int flag = 0;

  for ( i = 0; i < G->V; i++){
    counter = 0;flag = 0;
    for (int k = 0; k < n && flag != 1; k++){
      if (i == sol[k]){
        flag = 1;
      }
    }
    if (flag != 1){
      for ( j = 0; j < G->V; j++){
        if (G->madj[i][j] == 1){
          counter++;
        }
      }
      if (counter < k){
        return 0;
      }
    }
  }
  return 1;
}

static void dfsRcc(Graph G, int v, int id, int *cc) {
  cc[v] = id;
  for (int j = 0; j < G->V; j++){
    if (G->madj[v][j] != 0){
      if (cc[j] == -1){
        dfsRcc(G,j,id,cc);
      }
    }
  }
}


int GRAPHcc(Graph G) {
  int v, id = 0, *cc;
  cc = malloc(G->V * sizeof(int));
  
  if (cc == NULL)
    return -1;

  for (v = 0; v < G->V; v++)
    cc[v] = -1;

  for (v = 0; v < G->V; v++)
    if (cc[v] == -1)
      dfsRcc(G, v, id++, cc);
  return id;
}


int GRAPH_connected(Graph G){
  if (GRAPHcc(G) == 1)
    return 1;
  return 0;
}