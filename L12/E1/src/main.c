#include <stdio.h>

#include "../include/Graph.h"
#include "../include/best_sol.h"

#define FILE_NAME "grafo.txt"

int main(int argc, char *argv[]) {
	FILE *fp = fopen(FILE_NAME,"r");
	Graph G = GRAPHload(fp);

	Sol soluzione = max_DAG(G,GRAPHgetEdges(G),GRAPHgetnEdges(G));
	
	return(0);
}