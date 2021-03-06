#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "../include/ST.h"
#include "../include/Queue.h"
#include "../include/Graph.h"

#define MAXC 2
const int maxWT = INT_MIN;

struct graph {
  int V; 
  int E; 
  int **madj; 
  Edge *archi;
	ST tab; 
};


static       Edge EDGEcreate(	int v, 
								int w, 
								int wt);

static int **MATRIXint(			int r, 
								int c, 
								int val);

static void  insertE(			Graph G,
								Edge e);

static void  removeE(			Graph G, 
								Edge e);

static int   pathR(				Graph G, 
								int v, 
								int w, 
								int *visited);

static void  bfs(				Graph G, 
								Edge e, 
								int *time, 
								int *pre, 
								int *st);

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
  G->archi = malloc(2*coeffBinomiale(V,2)*sizeof(Edge));  //in un grafo diretto ci possono essere massimo 2 volte gli archi di un grafo completo(semplice ovvero non orientato)
  if (G->madj == NULL)
    return NULL;
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}

void GRAPHfree(Graph G) {
  int i;

  for (i=0; i<G->V; i++)
    free(G->madj[i]);
  free(G->madj);
  STfree(G->tab);
  free(G->archi);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int V, i, id1, id2, wt;
  char label1[MAXC], label2[MAXC];
  Graph G;

  fscanf(fin, "%d", &V);
  G = GRAPHinit(V);

  for (i=0; i<V; i++) {
    fscanf(fin, "%s", label1);
    STinsert(G->tab, label1, i);
  }
  i = 0;

  while(fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    G->archi[i].v = id1;G->archi[i].w = id2;G->archi[i].wt = wt;
    if (id1 >= 0 && id2 >=0)
      GRAPHinsertE(G, id1, id2, wt);
    i++;
  }
  G->E = i;
  
  return G;
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;

  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = wt;
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


int GRAPHgetIndex(Graph G, char *label) {
  int id;
  id = STsearch(G->tab, label);
  if (id == -1) {
    id = STsize(G->tab);
    STinsert(G->tab, label, id);
  }
  return id;
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
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, w, E = 0;
  for (v=0; v < G->V; v++)
    for (w=0; w < G->V; w++)
      if (G->madj[v][w] != 0)
        a[E++] = EDGEcreate(v, w, G->madj[v][w]);
}

void GRAPHpath(Graph G, int id1, int id2) {
  int t, found, *visited;

  visited = malloc(G->V*sizeof(int));
  if (visited == NULL)
    return;
  for ( t = 0 ; t < G->V ; t++)
    visited[t] = 0;

  if (id1 < 0 || id2 < 0)
    return;

  found = pathR(G, id1, id2, visited);
  if (found == 0)
    printf("\n Path not found!\n");
}


static int pathR(Graph G, int v, int w, int *visited) {
  int t;
  if (v == w)
    return 1;
  visited[v] = 1;
  for ( t = 0 ; t < G->V ; t++)
    if (G->madj[v][t] !=0)
      if (visited[t] == 0)
        if (pathR(G, t, w, visited)) {
          printf("edge (%s, %s) belongs to path \n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, t));
          return 1;
        }
  return 0;
}

void GRAPHbfs(Graph G, int id) {
  int v, time=0, *pre, *st;
  pre = malloc(G->V*sizeof(int));
  st = malloc(G->V*sizeof(int));
  if ((pre == NULL) || (st == NULL))
    return;

  for (v=0; v < G->V; v++) {
    pre[v] = -1;
    st[v] = -1;
  }
  bfs(G, EDGEcreate(id,id,0), &time, pre, st);

  printf("\n Resulting BFS tree \n");
  for (v=0; v < G->V; v++)
    if (st[v] != -1)
      printf("%s's parent is: %s \n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, st[v]));
}


void bfs(Graph G, Edge e, int *time, int *pre, int *st) {
  int v;
  Q q = Qinit();
  Qput(q, e);
  while (!Qempty(q))
    if (pre[(e = Qget(q)).w] == -1) {
      pre[e.w] = (*time)++;
      st[e.w] = e.v;
      for (v = 0; v < G->V; v++)
        if (G->madj[e.w][v] != 0)
          if (pre[v] == -1)
            Qput(q, EDGEcreate(e.w, v, G->madj[e.w][v]));
    }
  Qfree(q);
}

static boolean is_dag(Graph G,int *pre, Edge e,int *post, int *time){ //di fatto analogo alla dfsR ma con ritorno di un valore booleano
	int i;
	pre[e.w] = (*time)++;

  	boolean cond = TRUE;

	for ( i = 0; i < G->V ; i++){
		if (G->madj[e.w][i] != 0){ 	                              //se esiste l'arco
			if (pre[i] == -1){		                                  //vertice non ancora scoperto
				cond *= is_dag(G,pre,EDGEcreate(e.w,i,0),post,time);	//allora mi sposto sul vertice i
			}
			else {
				if (post[i] == -1){
					return FALSE;
				}
			}
		}
	}
	post[e.w] = (*time)++;
	return cond;
}

boolean DAGVerify(Graph G, int id) {
	int v, time=0, *pre, *post;

	pre 	= malloc(G->V * sizeof(int));
	post 	= malloc(G->V * sizeof(int));

	for (v=0;v<G->V;v++) {
		pre[v]=-1; 
		post[v]=-1; 
	}

	if (is_dag(G,pre,EDGEcreate(id,id,0),post,&time) == FALSE)
		return FALSE;

	for (v=0; v < G->V; v++)
		if (pre[v]==-1)
			if (is_dag(G,pre,EDGEcreate(v,v,0),post,&time) == FALSE)
				return FALSE;

	return TRUE;
}

Edge*   GRAPHgetEdges(  Graph G){
  return G->archi;
}

int     GRAPHgetnEdges( Graph G){
  return G->E;
}

void GRAPHspBF(Graph G, int id){
	int v, w, negcycfound;
	int *st, *d;
	st = malloc(G->V*sizeof(int));
	d = malloc(G->V*sizeof(int));

	for (v = 0; v < G->V; v++) {
		st[v]= -1;
		d[v] = maxWT;
	}

	d[id] = 0;
	st[id] = id;

	for (w=0; w<G->V-1; w++)
		for (v=0; v<G->V; v++)
			if (d[v] >= maxWT)
				for (int i = 0; i < G->V; i++){
					if (G->madj[v][i] != 0){
						if (d[i] < d[v] + G->madj[v][i]){
							d[i] 	= d[v] + G->madj[v][i];
							st[i]	= v;
						}
					}
				}

	negcycfound = 0;
	for (v=0; v<G->V; v++)
		if (d[v] >= maxWT)
			for (int i = 0; i < G->V-1; i++){
				if (G->madj[v][i] != 0){
					if (d[i] < d[v] + G->madj[v][i]){
						negcycfound = 1;
					}
				}
			}

	if (negcycfound == 0) {
		printf("\n*******Distanza Massima*******\n");
		printf("\n Max.dist. da %s\n",STsearchByIndex (G->tab, id));
		for (v = 0; v < G->V; v++)
    if (d[v] < 0)
			printf("%s: Infinito\n", STsearchByIndex (G->tab, v));
    else
			printf("%s: %d\n", STsearchByIndex (G->tab, v), d[v]);
	}
	else printf("\n Negative cycle found!\n");
}

int     GRAPHgetVn(     Graph G){
  return G->V;
}
