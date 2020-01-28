#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"



int main(int argc, char *argv[]) {
	FILE *fp = fopen(argv[1],"r");
	int n,j,k;
	Graph G = GRAPHload(fp);
#define DBG 1
	printf("\nInserisci  il valore k: ");
	scanf("%d",&k);
	k_core(G,k);
#if DBG 
	printf("\nInserisci il valore j: ");
	scanf("%d",&j);
	j_edge_connected(G,j);
#endif
	GRAPHfree(G);
	return(0);
}