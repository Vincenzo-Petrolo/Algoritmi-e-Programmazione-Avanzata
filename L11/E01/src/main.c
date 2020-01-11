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
	char codice_titolo[200];
	link head; 
	link ptr;
	data_t data;
	quotazioni_t *pointer;

	stampa_menu(menu1,2);
	while ( ( scelta = leggi_comando(menu1)) != R_FINE ){
		switch (scelta){
		case R_FILE:
			printf("\nInserisci il nome del file: ");
			scanf("%s",nome_file);
			fin = fopen(nome_file,"r");
			head = crea_lista_titoli(fin);
			break;
		case R_RICERCA_TITOLO:
			printf("\nInserisci il codice del titolo: ");
			scanf("%s",codice_titolo);
			ptr = cerca_titolo(head,codice_titolo);
			if (ptr != NULL){
				printf("\nTitolo trovato!\n");
				stampa_menu(menu2,2);
				scelta = leggi_comando(menu2);
				switch (scelta){
				case R_QUOTAZIONE:
					printf("\nInserisci la data nel formato aaaa/mm/gg :");
					scanf("%d/%d/%d",&(data.anno),&(data.mese),&(data.giorno));
					pointer = BSTsearch(getBST(ptr),data);
					if (pointer != NULL){
						quot_display(stdout,*pointer);
					}else printf("\nNon trovato\n");					
					break;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}
	}
	

#endif

	return(0);
}