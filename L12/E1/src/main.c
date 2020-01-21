#include <stdio.h>

#include "../include/Graph.h"
#include "../include/best_sol.h"


int main(int argc, char *argv[]) {
	FILE *fp = fopen(argv[1],"r");
	Graph G = GRAPHload(fp);

	printf("\n******Insieme di archi  da rimuovere per cui il grafo è un DAG******");

	Sol soluzione = max_DAG(G,GRAPHgetEdges(G),GRAPHgetnEdges(G));

	for (int i = 0; i <	soluzione.card_min; i++){	//dopo questa operaizone il Grafo viene trasformato in un DAG
		GRAPHremoveE(G,soluzione.sol.sol[i].v,soluzione.sol.sol[i].w);
	}
	GRAPHstore(G,stdout);
	
	for (int i = 0; i < GRAPHgetVn(G); i++){
		GRAPHspBF(G,i);
	}

	GRAPHfree(G);
	SOLfree(soluzione);
	return(0);
}
