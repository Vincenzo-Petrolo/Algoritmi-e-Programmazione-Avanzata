#include <stdio.h>

#include "../lib/f_ric/include/f_ric.h"
#include "../lib/matr4dp/include/matr4dp.h"
#include "../lib/pietre/include/pietre.h"

#define FILE_NAME "test.txt"

int main(int argc, char *argv[]) {

	Item**** matrice;
	quaternione_t quaternioni;
	struct pietre_bag pietre;
	struct pietre_bag prese;	
	int soluzioni[4];
	int best_soluzione;
	int i;
	FILE* fp = fopen(FILE_NAME,"r");

	fscanf(fp,"%d%d%d%d",&(quaternioni.a),&(quaternioni.i),&(quaternioni.j),&(quaternioni.k));
	fclose(fp);
	#define DBG 1
	
	matr4d_init(&matrice,quaternioni);
	matr4d_fill(&matrice,quaternioni,-1);
	#if DBG

	pietre_init(&pietre,quaternioni.a,quaternioni.i,quaternioni.j,quaternioni.k);
	pietre_init(&prese,0,0,0,0);

	soluzioni[0] 	= fZ(&pietre,&prese,&matrice);

	pietre_init(&pietre,quaternioni.a,quaternioni.i,quaternioni.j,quaternioni.k);
	pietre_init(&prese,0,0,0,0);

	soluzioni[1]	= fR(&pietre,&prese,&matrice);

	pietre_init(&pietre,quaternioni.a,quaternioni.i,quaternioni.j,quaternioni.k);
	pietre_init(&prese,0,0,0,0);

	soluzioni[2]	= fT(&pietre,&prese,&matrice);

	pietre_init(&pietre,quaternioni.a,quaternioni.i,quaternioni.j,quaternioni.k);
	pietre_init(&prese,0,0,0,0);

	soluzioni[3]	= fS(&prese,&pietre,&matrice);

	best_soluzione = 0;
	
	for (i = 0; i < 4; i++) {
		if (soluzioni[i] > best_soluzione)
			best_soluzione = soluzioni[i];
	}
	printf("\nLunghezza massima : %d",best_soluzione);
	#endif

	matr4d_free(&matrice,quaternioni);

	printf("\n");
	return(0);
}