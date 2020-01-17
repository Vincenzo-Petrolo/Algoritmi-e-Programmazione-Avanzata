#include <stdio.h>

#include "../include/Graph.h"
#include "../include/best_sol.h"

#define FILE_NAME "grafo2.txt"

int main(int argc, char *argv[]) {
	FILE *fp = fopen(FILE_NAME,"r");
	Graph G = GRAPHload(fp);

	Sol soluzione = max_DAG(G,GRAPHgetEdges(G),GRAPHgetnEdges(G));
	printf("\nInsieme di archi per cui il grafo è un DAG");

	for (int i = 0; i < soluzione.n_sol; i++){
		printf("\nInsieme %d : { ",i);
		for (int j = 0; j < soluzione.card_min; j++){
			printf("(%d,%d) ",soluzione.set_best_sol[i][j].v,
							soluzione.set_best_sol[i][j].w);
		}
		printf("}\n");
	}

	for (int i = 0; i <	soluzione.card_min; i++){	//dopo questa operaizone il Grafo viene trasformato in un DAG
		GRAPHremoveE(G,soluzione.sol.sol[i].v,soluzione.sol.sol[i].w);
	}
	GRAPHstore(G,stdout);
	
	for (int i = 0; i < GRAPHgetnEdges(G); i++){
		GRAPHspBF(G,i);
	}
	

	return(0);
}