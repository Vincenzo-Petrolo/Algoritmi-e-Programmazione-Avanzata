#include <stdio.h>

#include "../include/menu.h"
#include "../include/grafo.h"
#include "../include/item.h"
#include "../include/lista.h"
#include "../include/st.h"


int main(int argc, char *argv[]) {

	Grafo G;
	comando cmd;
	int scelta;
	char elab1[MAX_NAME],elab2[MAX_NAME],elab3[MAX_NAME];
	G = grafo_load("grafo.txt");
	#define DBG 1
	#if DBG 
	const char* menu[31] = {"stampa","sottografo","lista","fine"}; 
	stampa_menu(menu,3);
	
	while ((cmd = leggi_comando(menu)) != R_FINE){
		stampa_menu(menu,3);
		switch (cmd){
			case R_MOSTRA:
				stampa_grafo(G,stdout);
				break;
			case R_SOTTOGRAFO:
				printf("\nInserisci i nomi dei tre elaboratori: ");
				scanf("%s%s%s",elab1,elab2,elab3);
				printf("\nScrivi 1 (matrice) 0 (lista): ");
				scanf("%d",&scelta);
				if (scelta == 1)
					if (sottografo_m(G,elab1,elab2,elab3))
						printf("\nI vertici sono adiacenti a coppie!");
				if (scelta == 0)
					if (sottografo_l(G,elab1,elab2,elab3))
						printf("\nI vertici sono adiacenti a coppie!");
				break;
			case R_LISTA:
				G = madj_2_ladj(G);
				break;
			default:
				printf("\nComando errato!");
				break;
		}
	}
	#endif
	grafo_free(G);
	return(0);
}