#include <stdio.h>
#include "../include/BST.h"
#include "../include/data.h"
#include "../include/LIST.h"
#include "../include/mytypes.h"
#include "../include/ora.h"
#include "../include/quotazioni.h"
#include "../include/titolo.h"
#include "../include/transazioni.h"
#include "../include/menu.h"


int main(int argc, char *argv[]) {

const char *menu1[] = {"upload_file","ricerca_titolo","fine"};
const char *menu2[] = {"ricerca_quot","ricerca_time_int","ricerca_all_time","balance"};

#define DBG 1
#if DBG 
	//menu vari
	FILE *fin;
	int scelta;
	char nome_file[200];
	link head; 
	stampa_menu(menu1,2);
	while ( ( scelta = leggi_comando(menu1)) != R_FINE ){
		switch (scelta){
		case R_FILE:
			printf("\nInserisci il nome del file: ");
			scanf("%s",nome_file);
			fin = fopen(nome_file,"r");
			head = crea_lista_titoli(fin);
			stampa_menu(menu2,2);
			break;
		case R_RICERCA_TITOLO:
			break;
		default:
			break;
		}
	}
	

#endif

	return(0);
}